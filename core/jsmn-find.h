#ifndef JSMN_FIND_H
#define JSMN_FIND_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef JSMN_H
#error "jsmn-find.h should be included after jsmn.h"
#endif

#include "uthash.h"

/** @brief store key/value jsmn tokens in a hashtable */
typedef struct jsmnf {
    /** the key of the pair (null if root) */
    jsmntok_t *key;
    /** the value of the pair (null if unexistent) */
    jsmntok_t *val;
    /** the positional index of the pair */
    int idx;
    /** this structure fields */
    struct jsmnf *child;
    /** make this structure fields hashable */
    UT_hash_handle hh;
} jsmnf;

/**
 * @brief Initialize a @ref jsmnf root
 *
 * @return a @ref jsmnf root that should be cleanup up with
 *      jsmnf_cleanup()
 */
JSMN_API jsmnf *jsmnf_init(void);

/**
 * @brief Cleanup a @ref jsmnf handle
 *
 * @param root the @ref jsmnf root initialized with jsmnf_init()
 */
JSMN_API void jsmnf_cleanup(jsmnf *root);

/**
 * @brief Populate the @ref jsmnf root with jsmn tokens
 *
 * @param root the @ref jsmnf structure initialized with jsmnf_init()
 * @param json the raw JSON string
 * @param size the raw JSON length
 * @return a negative number for error, or the number of tokens found
 */
JSMN_API int jsmnf_start(jsmnf *root, const char json[], size_t size);

/**
 * @brief Find a value `jsmntok_t` by its key
 *
 * @param root the @ref jsmnf structure initialized with jsmnf_init()
 * @param key the key too be matched
 * @param size size of the key too be matched
 * @return the key/value pair matched to `key`
 */
JSMN_API jsmnf *jsmnf_find(jsmnf *root, const char key[], size_t size);

/**
 * @brief Find a value `jsmntok_t` by its key path
 *
 * @param root the @ref jsmnf structure initialized with jsmnf_init()
 * @param path an array of key path strings, from least to highest depth
 * @param depth the depth level of the last `path` key
 * @return the key/value pair matched to `path`
 */
JSMN_API jsmnf *jsmnf_find_path(jsmnf *root, char *const path[], int depth);

/**
 * @brief Utility function for unescaping a Unicode string
 *
 * @param p_dest destination buffer
 * @param src source string to be unescaped
 * @param size source string size
 * @return size of unescaped string if succesfull, 0 otherwise
 */
JSMN_API size_t jsmnf_unescape(char **p_dest, char src[], size_t size);

#ifndef JSMN_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct _jsmnroot {
    /**
     * the root jsmnf
     * @note `root` must be the first element so that `struct _jsmnroot` can be
     *      safely cast to `struct jsmnf` */
    jsmnf root;
    /** tokens storage cap */
    size_t real_ntoks;
    /** amount of tokens currently stored */
    size_t ntoks;
};

static jsmnf *
_jsmnf_init(void)
{
    return calloc(1, sizeof(jsmnf));
}

jsmnf *
jsmnf_init(void)
{
    struct _jsmnroot *r = calloc(1, sizeof *r);
    if (!r) return NULL;

    r->real_ntoks = 128;
    r->root.val = malloc(r->real_ntoks * sizeof *r->root.val);
    if (!r->root.val) {
        free(r);
        return NULL;
    }
    return &r->root;
}

static void
_jsmnf_cleanup(jsmnf *head)
{
    if (!head) return;

    if (JSMN_OBJECT == head->val->type || JSMN_ARRAY == head->val->type) {
        jsmnf *iter, *tmp;

        HASH_ITER(hh, head->child, iter, tmp)
        {
            HASH_DEL(head->child, iter);
            _jsmnf_cleanup(iter);
            free(iter);
        }
    }
}

void
jsmnf_cleanup(jsmnf *root)
{
    _jsmnf_cleanup(root);
    free(root->val);
    free(root);
}

static int
_jsmnf_get_pairs(const char js[], jsmntok_t *tok, size_t ntoks, jsmnf *head)
{
    int offset = 0;

    if (!ntoks) return 0;

    switch (tok->type) {
    case JSMN_OBJECT: {
        jsmnf *curr;
        int ret;
        int i;

        for (i = 0; i < tok->size; ++i) {
            curr = _jsmnf_init();
            curr->idx = i;
            curr->key = tok + 1 + offset;

            ret = _jsmnf_get_pairs(js, curr->key, ntoks - offset, curr);
            if (ret < 0) return ret;

            offset += ret;

            if (curr->key->size > 0) {
                curr->val = tok + 1 + offset;

                ret = _jsmnf_get_pairs(js, curr->val, ntoks - offset, curr);
                if (ret < 0) return ret;

                offset += ret;
            }

            HASH_ADD_KEYPTR(hh, head->child, js + curr->key->start,
                            curr->key->end - curr->key->start, curr);
        }
    } break;
    case JSMN_ARRAY: {
        jsmnf *curr;
        int ret;
        int i;

        for (i = 0; i < tok->size; ++i) {
            curr = _jsmnf_init();
            curr->idx = i;
            curr->val = tok + 1 + offset;

            ret = _jsmnf_get_pairs(js, curr->val, ntoks - offset, curr);
            if (ret < 0) return ret;

            offset += ret;

            HASH_ADD_INT(head->child, idx, curr);
        }
    } break;
    case JSMN_STRING:
    case JSMN_PRIMITIVE:
        break;
    case JSMN_UNDEFINED:
    default:
        fprintf(stderr, "Unexpected key: %.*s\n", tok->end - tok->start,
                js + tok->start);
        return -1;
    }
    return offset + 1;
}

int
jsmnf_start(jsmnf *root, const char js[], size_t size)
{
    struct _jsmnroot *r = (struct _jsmnroot *)root;
    jsmn_parser parser;
    int ret;

    /* Prepare parser */
    jsmn_init(&parser);
    while (1) {
        ret = jsmn_parse(&parser, js, size, root->val, r->real_ntoks);

        if (ret >= 0) {
            r->ntoks = parser.toknext;
            ret = _jsmnf_get_pairs(js, root->val, r->ntoks, root);
            break;
        }
        else {
            if (ret != JSMN_ERROR_NOMEM) {
                break;
            }
            else {
                size_t new_ntoks = r->real_ntoks * 2;
                void *tmp;

                tmp = realloc(root->val, new_ntoks * sizeof *root->val);
                if (!tmp) return JSMN_ERROR_NOMEM;

                r->real_ntoks = new_ntoks;
                root->val = tmp;
            }
        }
    }
    return ret;
}

jsmnf *
jsmnf_find(jsmnf *head, const char key[], size_t size)
{
    jsmnf *found = NULL;

    if (!key || !head) return NULL;

    if (JSMN_OBJECT == head->val->type) {
        HASH_FIND(hh, head->child, key, size, found);
    }
    else if (JSMN_ARRAY == head->val->type) {
        char *endptr;
        int idx = (int)strtol(key, &endptr, 10);

        if (endptr == key) return NULL;

        HASH_FIND_INT(head->child, &idx, found);
    }
    return found;
}

jsmnf *
jsmnf_find_path(jsmnf *head, char *const path[], int depth)
{
    jsmnf *iter = head, *found = NULL;
    int i;

    for (i = 0; i < depth; ++i) {
        if (!iter) continue;
        found = jsmnf_find(iter, path[i], strlen(path[i]));
        if (!found) break;
        iter = found;
    }
    return found;
}

static int
read_4_digits(char **str_p, const char *src_end, unsigned *x)
{
    char *str = *str_p;
    char buf[5] = { 0 };
    unsigned v;
    int i;

    if (src_end - str < 4) return 0;

    for (i = 0; i < 4; i++) {
        char c = str[i];

        buf[i] = c;
        if (isxdigit(c)) continue;

        return 0;
    }

    sscanf(buf, "%x", &v);

    *x = v;
    *str_p = str + 4;

    return 1;
}

static int
utf16_is_first_surrogate(unsigned x)
{
    return 0xD800 <= x && x <= 0xDBFF;
}

static int
utf16_is_second_surrogate(unsigned x)
{
    return 0xDC00 <= x && x <= 0xDFFF;
}

static unsigned long
utf16_combine_surrogate(unsigned w1, unsigned w2)
{
    return ((((unsigned long)w1 & 0x3FF) << 10) | (w2 & 0x3FF)) + 0x10000;
}

static const unsigned long utf_illegal = 0xFFFFFFFFu;

static int
utf_valid(unsigned long v)
{
    if (v > 0x10FFFF) return 0;
    if (0xD800 <= v && v <= 0xDFFF) /* surrogates */
        return 0;
    return 1;
}

static int
utf8_is_trail(char ci)
{
    unsigned char c = ci;
    return (c & 0xC0) == 0x80;
}

static int
utf8_trail_length(unsigned char c)
{
    if (c < 128) return 0;
    if (c < 194) return -1;
    if (c < 224) return 1;
    if (c < 240) return 2;
    if (c <= 244) return 3;
    return -1;
}

static int
utf8_width(unsigned long value)
{
    if (value <= 0x7F)
        return 1;
    else if (value <= 0x7FF)
        return 2;
    else if (value <= 0xFFFF)
        return 3;
    else
        return 4;
}

/* See RFC 3629
   Based on: http://www.w3.org/International/questions/qa-forms-utf-8 */
static unsigned long
next(char **p, char *e, int html)
{
    unsigned char lead, tmp;
    int trail_size;
    unsigned long c;

    if (*p == e) return utf_illegal;

    lead = **p;
    (*p)++;

    /* First byte is fully validated here */
    trail_size = utf8_trail_length(lead);

    if (trail_size < 0) return utf_illegal;

    /* Ok as only ASCII may be of size = 0
      also optimize for ASCII text */
    if (trail_size == 0) {
        if (!html || (lead >= 0x20 && lead != 0x7F) || lead == 0x9
            || lead == 0x0A || lead == 0x0D)
            return lead;
        return utf_illegal;
    }

    c = lead & ((1 << (6 - trail_size)) - 1);

    /* Read the rest */
    switch (trail_size) {
    case 3:
        if (*p == e) return utf_illegal;
        tmp = **p;
        (*p)++;
        if (!utf8_is_trail(tmp)) return utf_illegal;
        c = (c << 6) | (tmp & 0x3F);
    /* fall-through */
    case 2:
        if (*p == e) return utf_illegal;
        tmp = **p;
        (*p)++;
        if (!utf8_is_trail(tmp)) return utf_illegal;
        c = (c << 6) | (tmp & 0x3F);
    /* fall-through */
    case 1:
        if (*p == e) return utf_illegal;
        tmp = **p;
        (*p)++;
        if (!utf8_is_trail(tmp)) return utf_illegal;
        c = (c << 6) | (tmp & 0x3F);
    }

    /* Check code point validity: no surrogates and
       valid range */
    if (!utf_valid(c)) return utf_illegal;

    /* make sure it is the most compact representation */
    if (utf8_width(c) != trail_size + 1) return utf_illegal;

    if (html && c < 0xA0) return utf_illegal;
    return c;
}

static int
utf8_validate(char *p, char *e)
{
    while (p != e)
        if (next(&p, e, 0) == utf_illegal) return 0;
    return 1;
}

struct utf8_seq {
    char c[4];
    unsigned len;
};

static void
utf8_encode(unsigned long value, struct utf8_seq *out)
{
    /*struct utf8_seq out={0}; */
    if (value <= 0x7F) {
        out->c[0] = value;
        out->len = 1;
    }
    else if (value <= 0x7FF) {
        out->c[0] = (value >> 6) | 0xC0;
        out->c[1] = (value & 0x3F) | 0x80;
        out->len = 2;
    }
    else if (value <= 0xFFFF) {
        out->c[0] = (value >> 12) | 0xE0;
        out->c[1] = ((value >> 6) & 0x3F) | 0x80;
        out->c[2] = (value & 0x3F) | 0x80;
        out->len = 3;
    }
    else {
        out->c[0] = (value >> 18) | 0xF0;
        out->c[1] = ((value >> 12) & 0x3F) | 0x80;
        out->c[2] = ((value >> 6) & 0x3F) | 0x80;
        out->c[3] = (value & 0x3F) | 0x80;
        out->len = 4;
    }
}

static void *
append(unsigned long x, char *d)
{
    unsigned i;
    struct utf8_seq seq = { { 0 }, 0 };

    utf8_encode(x, &seq);

    for (i = 0; i < seq.len; ++i, d++)
        *d = seq.c[i];

    return d;
}

size_t
jsmnf_unescape(char **p_dest, char src[], size_t size)
{
    enum { TESTING = 1, ALLOCATING, UNESCAPING } state = TESTING;

    char *src_start = src, *src_end = src + size;
    char *out_start = NULL, *d = NULL, *s = NULL;
    unsigned first_surrogate;
    int second_surrogate_expected;
    char c;

second_iter:
    first_surrogate = 0;
    second_surrogate_expected = 0;

    for (s = src_start; s < src_end;) {
        c = *s++;

        if (second_surrogate_expected && c != '\\') goto _err;
        if (0 <= c && c <= 0x1F) goto _err;

        if ('\\' == c) {
            /* break the while loop */
            if (TESTING == state) {
                state = ALLOCATING;
                break;
            }

            /* return if src is a well-formed json string */
            if (s == src_end) goto _err;

            c = *s++;

            if (second_surrogate_expected && c != 'u') goto _err;

            switch (c) {
            case '"': case '\\': case '/':
                *d++ = c;
                break;
            case 'b': *d++ = '\b'; break;
            case 'f': *d++ = '\f'; break;
            case 'n': *d++ = '\n'; break;
            case 'r': *d++ = '\r'; break;
            case 't': *d++ = '\t'; break;
            case 'u': {
                unsigned x;

                if (!read_4_digits(&s, src_end, &x)) goto _err;

                if (second_surrogate_expected) {
                    if (!utf16_is_second_surrogate(x)) goto _err;

                    d = append(utf16_combine_surrogate(first_surrogate, x), d);
                    second_surrogate_expected = 0;
                }
                else if (utf16_is_first_surrogate(x)) {
                    second_surrogate_expected = 1;
                    first_surrogate = x;
                }
                else {
                    d = append(x, d);
                }
            } break;
            default:
                goto _err;
            }
        }
        else if (UNESCAPING == state) {
            *d++ = c;
        }
    }

    switch (state) {
    case UNESCAPING:
        if (!utf8_validate(out_start, d)) goto _err;

        *p_dest = out_start;
        return d - out_start;
    case ALLOCATING:
        out_start = calloc(1, size);
        d = out_start;
        state = UNESCAPING;
        goto second_iter;
    case TESTING:
        *p_dest = src_start;
        return size;
    default:
        break;
    }

_err:
    if (UNESCAPING == state) free(out_start);
    return 0;
}
#endif /* JSMN_HEADER */

#ifdef __cplusplus
}
#endif

#endif /* JSMN_FIND_H */
