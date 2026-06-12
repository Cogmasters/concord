#!/usr/bin/env python3
"""Validate that recipe fields stay in sync with Discord's OpenAPI spec.

Parses every field tuple in src/api/*.recipe.h, computes its serialized
name (the alias slot when set, the member name otherwise) and checks that
the name exists as a property somewhere in Discord's published OpenAPI
document (https://github.com/discord/discord-api-spec).

On top of the name check, a TYPE check maps each field's C type onto the
set of JSON types it can serialize to (see C_TYPE_TO_JSON) and verifies
that at least one schema in the spec declares the property with a
compatible type.  Because concord's struct names don't map 1:1 onto the
spec's schema names, both checks are deliberately lenient: a name (or a
name+type pairing) found *anywhere* in the spec passes.  What they catch
is the absolute mismatches — a serialized name appearing nowhere is
almost always a typo, a missing alias (the muted/"mute" class of bug) or
a dropped field; a field whose JSON type matches no schema's declaration
of that property is a mis-modeled type (e.g. an object where the API
wants an array, the issue #190 class of bug).

Known-good exceptions live in scripts/openapi_sync_allowlist.txt: bare
`name` or `struct.name` entries suppress the name check, `type:`-prefixed
entries suppress the type check.

Usage:
    scripts/check_openapi_sync.py [--spec path/to/openapi.json]

Without --spec the current spec is downloaded from the discord-api-spec
repository (requires network).
"""

import argparse
import json
import re
import sys
import urllib.request
from pathlib import Path

SPEC_URL = ("https://raw.githubusercontent.com/discord/discord-api-spec/"
            "main/specs/openapi.json")
REPO_ROOT = Path(__file__).resolve().parent.parent
RECIPES_GLOB = "src/api/*.recipe.h"
ALLOWLIST = REPO_ROOT / "scripts" / "openapi_sync_allowlist.txt"

# slots: (qualifier, container, type, decorator, name, alias, dims, attrs)
FIELD_RE = re.compile(
    r"^\s*\(\s*([A-Za-z_]\w*),\s*([A-Za-z_]\w*),\s*([A-Za-z_]\w*),"
    r"\s*(\*{1,2}|_),\s*([A-Za-z_]\w*),\s*([A-Za-z_]\w*|_),")
STRUCT_RE = re.compile(r"(?:PUBLIC|PRIVATE)\(struct,\s*(\w+),")


LIST_CONTAINER = ("size", "array", "realsize")

# JSON types a recipe C type may serialize to (discord-data-wrap.c is the
# source of truth).  Multi-valued entries reflect genuine wire variety in
# the spec: snowflakes are strings (format snowflake) but a few count-like
# fields are modeled as integers; bitmasks are strings for permissions yet
# integers for flags; unix-ms timestamps appear both as ISO strings and as
# integer milliseconds (e.g. presence 'since').
C_TYPE_TO_JSON = {
    "char": {"string"},
    "int": {"integer"},
    "short": {"integer"},
    "long": {"integer"},
    "size_t": {"integer"},
    "float": {"number"},
    "double": {"number"},
    "bool": {"boolean"},
    "u64snowflake": {"string", "integer"},
    "u64bitmask": {"string", "integer"},
    "u64unix_ms": {"string", "integer"},
    # raw-JSON passthrough: any shape by design
    "json_char": None,
}

# spec-side marker for "couldn't determine a type" (bare $ref chains,
# empty schemas, ...) — treated as compatible with anything
UNKNOWN = "?"


class Field:
    __slots__ = ("struct", "container", "ctype", "decorator", "name",
                 "serialized", "fname", "lineno")

    def __init__(self, struct, container, ctype, decorator, name,
                 serialized, fname, lineno):
        self.struct = struct
        self.container = container
        self.ctype = ctype
        self.decorator = decorator
        self.name = name
        self.serialized = serialized
        self.fname = fname
        self.lineno = lineno


def parse_recipes():
    """Return (fields, list_structs).

    `fields` excludes the members of list containers (exactly the
    size/array/realsize triple): those serialize as JSON arrays, so their
    member names never reach the wire.  `list_structs` is the set of
    struct names that ARE such containers — a field pointing at one of
    them serializes as an array, not an object.
    """
    fields, list_structs = [], set()
    for path in sorted(REPO_ROOT.glob(RECIPES_GLOB)):
        struct, pending = None, []

        def flush():
            nonlocal struct, pending
            if struct:
                if tuple(f.name for f in pending) == LIST_CONTAINER:
                    list_structs.add(struct)
                else:
                    fields.extend(pending)
            struct, pending = None, []

        for lineno, line in enumerate(path.read_text().splitlines(), 1):
            m = STRUCT_RE.search(line)
            if m:
                flush()
                struct = m.group(1)
                continue
            if struct is None:
                continue
            m = FIELD_RE.match(line)
            if m:
                container, ctype, decorator, name, alias = m.groups()[1:6]
                serialized = name if alias == "_" else alias
                pending.append(Field(struct, container, ctype, decorator,
                                     name, serialized, path.name, lineno))
        flush()
    return fields, list_structs


def field_json_types(field, list_structs):
    """JSON types this field can put on the wire, or None for 'anything'."""
    if field.container == "struct":
        return {"array"} if field.ctype in list_structs else {"object"}
    if field.container == "enum":
        # serialized as a number, but the spec models some enums as
        # string-valued (e.g. locales, scopes)
        return {"integer", "string"}
    return C_TYPE_TO_JSON.get(field.ctype)


def _schema_types(schema, schemas, depth=0):
    """JSON types a property schema admits; {UNKNOWN} when undecidable."""
    if depth > 4 or not isinstance(schema, dict):
        return {UNKNOWN}
    found = set()
    t = schema.get("type")
    if isinstance(t, str):
        found.add(t)
    elif isinstance(t, list):  # OpenAPI 3.1 union, e.g. ["string", "null"]
        found.update(x for x in t if isinstance(x, str))
    ref = schema.get("$ref")
    if isinstance(ref, str) and ref.startswith("#/components/schemas/"):
        target = schemas.get(ref.rsplit("/", 1)[-1])
        found.update(_schema_types(target, schemas, depth + 1))
    for combinator in ("oneOf", "anyOf", "allOf"):
        for branch in schema.get(combinator) or []:
            found.update(_schema_types(branch, schemas, depth + 1))
    found.discard("null")
    return found or {UNKNOWN}


def spec_property_types(spec):
    """Map property name -> set of JSON types it has anywhere in the spec.

    Operation parameters (query params like 'limit'/'before' live in
    recipes too) contribute their schema's type under their name.
    """
    schemas = spec.get("components", {}).get("schemas", {})
    types = {}

    def add(name, schema):
        types.setdefault(name, set()).update(
            _schema_types(schema, schemas))

    def walk(node):
        if isinstance(node, dict):
            props = node.get("properties")
            if isinstance(props, dict):
                for name, schema in props.items():
                    add(name, schema)
            if "name" in node and "in" in node:  # OpenAPI parameter object
                if isinstance(node["name"], str):
                    add(node["name"], node.get("schema", {}))
            for value in node.values():
                walk(value)
        elif isinstance(node, list):
            for value in node:
                walk(value)

    walk(spec)
    return types


def load_allowlist():
    """Return (name_allowed, type_allowed) sets."""
    names, types = set(), set()
    if ALLOWLIST.exists():
        for line in ALLOWLIST.read_text().splitlines():
            line = line.split("#", 1)[0].strip()
            if not line:
                continue
            if line.startswith("type:"):
                types.add(line[len("type:"):].strip())
            else:
                names.add(line)
    return names, types


def report_coverage(spec_types, recipe_serialized_names):
    """Reverse direction: spec property names with no recipe field.

    Informational only — the recipes deliberately model the API v9/v10-era
    schema (see test/fixtures/README.md), so this reports how far the spec
    has moved ahead rather than failing the run.
    """
    missing = sorted(set(spec_types) - recipe_serialized_names)
    print(f"\ncoverage: {len(spec_types) - len(missing)}/{len(spec_types)} "
          f"spec property names are modeled by a recipe field; "
          f"{len(missing)} are not:")
    for name in missing:
        print(f"  {name}")
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--spec", help="path to a local openapi.json")
    parser.add_argument("--coverage", action="store_true",
                        help="also report spec property names no recipe "
                             "models (informational, never fails)")
    args = parser.parse_args()

    if args.spec:
        spec = json.loads(Path(args.spec).read_text())
    else:
        with urllib.request.urlopen(SPEC_URL, timeout=60) as resp:
            spec = json.load(resp)

    spec_types = spec_property_types(spec)
    allowed_names, allowed_types = load_allowlist()

    fields, list_structs = parse_recipes()
    unknown, mistyped = [], []
    serialized_names = set()
    for f in fields:
        serialized_names.add(f.serialized)
        key = f"{f.struct}.{f.serialized}"
        if f.serialized not in spec_types:
            if not (f.serialized in allowed_names or key in allowed_names):
                unknown.append((key, f))
            continue
        recipe_types = field_json_types(f, list_structs)
        if recipe_types is None:
            continue
        known = spec_types[f.serialized]
        if UNKNOWN in known or recipe_types & known:
            continue
        if f.serialized in allowed_types or key in allowed_types:
            continue
        mistyped.append((key, f, sorted(recipe_types), sorted(known)))

    print(f"checked {len(fields)} recipe fields against "
          f"{len(spec_types)} spec property names")
    if args.coverage:
        report_coverage(spec_types, serialized_names)

    status = 0
    if unknown:
        status = 1
        print(f"\n{len(unknown)} serialized name(s) not found in the "
              "OpenAPI spec (typo, missing alias, or dropped field?):")
        for key, f in unknown:
            print(f"  {f.fname}:{f.lineno}: {key}"
                  + (f" (member {f.name})" if f.name != f.serialized
                     else ""))
    if mistyped:
        status = 1
        print(f"\n{len(mistyped)} field(s) whose JSON type matches no spec "
              "declaration of that property (mis-modeled type?):")
        for key, f, ours, theirs in mistyped:
            print(f"  {f.fname}:{f.lineno}: {key} serializes as "
                  f"{'/'.join(ours)} but the spec only has "
                  f"{'/'.join(theirs)}")
    if status:
        print("\nIf an entry is legitimately concord-only, add it (or its "
              "qualified struct.name form) to "
              "scripts/openapi_sync_allowlist.txt — prefix with 'type:' "
              "for type-check exceptions")
        return status
    print("all recipe field names and types are present in the spec")
    return 0


if __name__ == "__main__":
    sys.exit(main())
