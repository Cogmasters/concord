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

/* ── JSON field assertion ─────────────────────────────────────────── */
/* ASSERT_JSON_STR(json, json_len, key, expected)
 *
 * Fails the current test if the top-level string field KEY is absent
 * or its value differs from EXPECTED.  KEY must be a string literal
 * (it is used in diagnostic messages via token pasting).
 *
 * Uses stack-allocated token/pair buffers sized for 64 tokens; do not
 * use with JSON that has more than ~64 tokens. */
#define ASSERT_JSON_STR(json, json_len, key, expected)                     \
    do {                                                                   \
        jsmn_parser       _jsmn_p;                                         \
        jsmntok_t         _jsmn_t[64];                                     \
        jsmnf_loader      _jsmn_l;                                         \
        jsmnf_table       _jsmn_tb[64];                                    \
        const jsmnf_pair *_jsmn_f;                                         \
        int _jsmn_n, _jsmn_vl;                                             \
        jsmn_init(&_jsmn_p);                                               \
        _jsmn_n = jsmn_parse(&_jsmn_p, (json), (json_len),                \
                             _jsmn_t, 64);                                 \
        ASSERT_GTE(_jsmn_n, 1);                                            \
        jsmnf_init(&_jsmn_l);                                              \
        ASSERT_GTE(jsmnf_load(&_jsmn_l, (json), (json_len),               \
                              _jsmn_tb, 64), 1L);                          \
        _jsmn_f = jsmnf_find(_jsmn_l.root, (key), strlen(key));           \
        ASSERT_NEQm("key '" key "' not found",                             \
                    (const jsmnf_pair *)NULL, _jsmn_f);                    \
        _jsmn_vl = _jsmn_f->v->end - _jsmn_f->v->start;                   \
        ASSERT_EQm("JSON field '" key "' length",                          \
                   (int)strlen(expected), _jsmn_vl);                       \
        ASSERT_EQm("JSON field '" key "' value", 0,                        \
                   strncmp((expected), (json) + _jsmn_f->v->start,         \
                           (size_t)_jsmn_vl));                             \
    } while (0)

#endif /* TEST_UTILS_H */
