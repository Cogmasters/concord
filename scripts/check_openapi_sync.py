#!/usr/bin/env python3
"""Validate that recipe field names stay in sync with Discord's OpenAPI spec.

Parses every field tuple in src/api/*.recipe.h, computes its serialized
name (the alias slot when set, the member name otherwise) and checks that
the name exists as a property somewhere in Discord's published OpenAPI
document (https://github.com/discord/discord-api-spec).

This is deliberately a NAME-LEVEL check, not a schema-level one: concord's
struct names don't map 1:1 onto the spec's schema names, but a serialized
field name that appears nowhere in the spec is almost always a typo, a
missing alias (e.g. the muted/"mute" class of bug) or a field Discord has
dropped.  Known-good exceptions live in scripts/openapi_sync_allowlist.txt.

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
    r"^\s*\((?:[^,()]+,\s*){4}([A-Za-z_]\w*),\s*([A-Za-z_]\w*|_),")
STRUCT_RE = re.compile(r"(?:PUBLIC|PRIVATE)\(struct,\s*(\w+),")


LIST_CONTAINER = ("size", "array", "realsize")


def parse_recipes():
    """yield (struct, field, serialized_name, file, lineno)

    List containers (exactly the size/array/realsize triple) serialize as
    JSON arrays — their member names never reach the wire and are skipped.
    """
    for path in sorted(REPO_ROOT.glob(RECIPES_GLOB)):
        struct, fields = None, []

        def flush():
            if struct and tuple(f[1] for f in fields) != LIST_CONTAINER:
                yield from fields

        for lineno, line in enumerate(path.read_text().splitlines(), 1):
            m = STRUCT_RE.search(line)
            if m:
                yield from flush()
                struct, fields = m.group(1), []
                continue
            if struct is None:
                continue
            m = FIELD_RE.match(line)
            if m:
                name, alias = m.group(1), m.group(2)
                serialized = name if alias == "_" else alias
                fields.append((struct, name, serialized, path.name, lineno))
        yield from flush()


def spec_property_names(spec):
    """All schema property names plus operation parameter names (query
    params like 'limit'/'before' live in recipes too)."""
    names = set()

    def walk(node):
        if isinstance(node, dict):
            props = node.get("properties")
            if isinstance(props, dict):
                names.update(props)
        if isinstance(node, dict):
            if "name" in node and "in" in node:  # OpenAPI parameter object
                if isinstance(node["name"], str):
                    names.add(node["name"])
            for value in node.values():
                walk(value)
        elif isinstance(node, list):
            for value in node:
                walk(value)

    walk(spec)
    return names


def load_allowlist():
    allowed = set()
    if ALLOWLIST.exists():
        for line in ALLOWLIST.read_text().splitlines():
            line = line.split("#", 1)[0].strip()
            if line:
                allowed.add(line)
    return allowed


def report_coverage(spec, recipe_serialized_names):
    """Reverse direction: spec property names with no recipe field.

    Informational only — the recipes deliberately model the API v9/v10-era
    schema (see test/fixtures/README.md), so this reports how far the spec
    has moved ahead rather than failing the run.
    """
    known = spec_property_names(spec)
    missing = sorted(known - recipe_serialized_names)
    print(f"\ncoverage: {len(known) - len(missing)}/{len(known)} spec "
          f"property names are modeled by a recipe field; "
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

    known = spec_property_names(spec)
    allowed = load_allowlist()

    unknown = []
    checked = 0
    serialized_names = set()
    for struct, field, serialized, fname, lineno in parse_recipes():
        checked += 1
        serialized_names.add(serialized)
        if serialized in known:
            continue
        key = f"{struct}.{serialized}"
        if serialized in allowed or key in allowed:
            continue
        unknown.append((key, field, fname, lineno))

    print(f"checked {checked} recipe fields against "
          f"{len(known)} spec property names")
    if args.coverage:
        report_coverage(spec, serialized_names)
    if unknown:
        print(f"\n{len(unknown)} serialized name(s) not found in the "
              "OpenAPI spec (typo, missing alias, or dropped field?):")
        for key, field, fname, lineno in unknown:
            print(f"  {fname}:{lineno}: {key}"
                  + (f" (member {field})" if field != key.split('.')[1]
                     else ""))
        print("\nIf a name is legitimately concord-only, add it (or its "
              "qualified struct.name form) to scripts/openapi_sync_allowlist.txt")
        return 1
    print("all recipe field names are present in the spec")
    return 0


if __name__ == "__main__":
    sys.exit(main())
