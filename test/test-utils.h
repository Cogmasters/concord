#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declare jsmn symbols only — implementations are in libdiscord.a */
#define JSMN_HEADER
#include "jsmn.h"
#include "jsmn-find.h"

#include "greatest.h"

/* ── Fixture loading ──────────────────────────────────────────────── */

/* Read the file at PATH into a malloc'd buffer.  On success returns 0
 * and sets *OUT and *OUT_LEN; caller must free(*OUT).  On failure
 * prints the attempted path to stderr and returns -1. */
static inline int
test_load_fixture(const char *path, char **out, size_t *out_len)
{
    FILE *f;
    long  sz;
    char *buf;

    f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "test_load_fixture: cannot open '%s'\n", path);
        return -1;
    }
    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    if (sz < 0) {
        fprintf(stderr, "test_load_fixture: cannot size '%s'\n", path);
        fclose(f);
        return -1;
    }
    rewind(f);
    buf = malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return -1; }
    *out_len = fread(buf, 1, (size_t)sz, f);
    buf[*out_len] = '\0';
    fclose(f);
    *out = buf;
    return 0;
}

/* Load the fixture NAME from test/fixtures/ (tests run with cwd
 * test/).  Returns a malloc'd NUL-terminated buffer, or NULL on
 * failure; caller must free() it. */
static inline char *
test_load_json_fixture(const char *name, size_t *len)
{
    char path[512];
    char *buf = NULL;

    snprintf(path, sizeof(path), "fixtures/%s", name);
    if (0 != test_load_fixture(path, &buf, len)) return NULL;
    return buf;
}

/* ── Parsed JSON document ─────────────────────────────────────────── */
/* Heap-parsed JSON document for repeated path lookups on JSON of any
 * size (unlike ASSERT_JSON_STR below, which is stack-limited). */
typedef struct test_json {
    jsmnf_loader loader;
    jsmnf_table *table; /* heap; freed by test_json_unload() */
    const char *js;
} test_json;

/* Parse JS into TJ.  Returns 0 on success, -1 on parse failure.  On
 * success the caller must call test_json_unload() once done. */
static inline int
test_json_load(test_json *tj, const char *js, size_t len)
{
    size_t table_len = 0;

    tj->table = NULL;
    tj->js = js;
    jsmnf_init(&tj->loader);
    return jsmnf_load_auto(&tj->loader, js, len, &tj->table, &table_len) >= 1
               ? 0
               : -1;
}

static inline void
test_json_unload(test_json *tj)
{
    free(tj->table);
    tj->table = NULL;
}

/* Dotted-path lookup, e.g. "embeds.0.title"; array elements are
 * addressed by decimal index segments.  Returns NULL when any segment
 * is absent or the path exceeds 255 bytes. */
static inline const jsmnf_pair *
test_json_get(const test_json *tj, const char *path)
{
    char buf[256];
    const jsmnf_pair *p = tj->loader.root;
    char *seg, *next;
    size_t n = strlen(path);

    if (n >= sizeof(buf)) return NULL;
    memcpy(buf, path, n + 1);
    for (seg = buf; p && seg; seg = next) {
        next = strchr(seg, '.');
        if (next) *next++ = '\0';
        p = jsmnf_find(p, seg, strlen(seg));
    }
    return p;
}

/* Copy the raw token text at PATH into OUT (NUL-terminated).  String
 * tokens exclude their surrounding quotes (jsmn semantics), which
 * normalizes snowflake/bitmask quoting differences ("64" vs 64).
 * Returns the token length, or -1 if absent or OUTSZ is too small. */
static inline int
test_json_raw(const test_json *tj, const char *path, char *out, size_t outsz)
{
    const jsmnf_pair *p = test_json_get(tj, path);
    int len;

    if (!p) return -1;
    len = p->v->end - p->v->start;
    if ((size_t)len >= outsz) return -1;
    memcpy(out, tj->js + p->v->start, (size_t)len);
    out[len] = '\0';
    return len;
}

/* Path-based assertions over a test_json document.  PATH may be a
 * string literal or a runtime value; it doubles as the failure
 * message. */
#define ASSERT_JSON_HAS(tj, path)                                          \
    ASSERT_NEQm((path), (const jsmnf_pair *)NULL,                          \
                test_json_get((tj), (path)))
#define ASSERT_JSON_ABSENT(tj, path)                                       \
    ASSERT_EQm((path), (const jsmnf_pair *)NULL,                           \
               test_json_get((tj), (path)))
#define ASSERT_JSON_PATH_STR(tj, path, expected)                           \
    do {                                                                   \
        char _tj_raw[4608];                                                \
        ASSERT_NEQm((path), -1,                                            \
                    test_json_raw((tj), (path), _tj_raw,                   \
                                  sizeof(_tj_raw)));                       \
        ASSERT_STR_EQm((path), (expected), _tj_raw);                       \
    } while (0)
/* Assert the token at PATH is textually identical in both documents
 * (after jsmn's quote stripping). */
#define ASSERT_JSON_SAME(tj_exp, tj_got, path)                             \
    do {                                                                   \
        char _tj_exp[4608], _tj_got[4608];                                 \
        ASSERT_NEQm((path), -1,                                            \
                    test_json_raw((tj_exp), (path), _tj_exp,               \
                                  sizeof(_tj_exp)));                       \
        ASSERT_NEQm((path), -1,                                            \
                    test_json_raw((tj_got), (path), _tj_got,               \
                                  sizeof(_tj_got)));                       \
        ASSERT_STR_EQm((path), _tj_exp, _tj_got);                          \
    } while (0)

#endif /* TEST_UTILS_H */
