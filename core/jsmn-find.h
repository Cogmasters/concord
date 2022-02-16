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
JSMN_API size_t jsmnf_unescape(char **p_dest, const char src[], size_t size);

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

#define UTF16_IS_FIRST_SURROGATE(c)                                           \
    (0xD800 <= (unsigned)c && (unsigned)c <= 0xDBFF)
#define UTF16_IS_SECOND_SURROGATE(c)                                          \
    (0xDC00 <= (unsigned)c && (unsigned)c <= 0xDFFF)
#define UTF16_JOIN_SURROGATE(c1, c2)                                          \
    (((((unsigned long)c1 & 0x3FF) << 10) | ((unsigned)c2 & 0x3FF)) + 0x10000)
#define UTF8_IS_VALID(c)                                                      \
    (((unsigned long)c <= 0x10FFFF)                                           \
     && ((unsigned long)c < 0xD800 || (unsigned long)c > 0xDFFF))
#define UTF8_IS_TRAIL(c) (((unsigned char)c & 0xC0) == 0x80)
#define UTF_ILLEGAL      0xFFFFFFFFu

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
utf8_next(char **p, char *e, int html)
{
    unsigned char lead, tmp;
    int trail_size;
    unsigned long c;

    if (*p == e) return UTF_ILLEGAL;

    lead = **p;
    (*p)++;

    /* First byte is fully validated here */
    trail_size = utf8_trail_length(lead);

    if (trail_size < 0) return UTF_ILLEGAL;

    /* Ok as only ASCII may be of size = 0 also optimize for ASCII text */
    if (trail_size == 0) {
        if (!html || (lead >= 0x20 && lead != 0x7F) || lead == 0x9
            || lead == 0x0A || lead == 0x0D)
            return lead;
        return UTF_ILLEGAL;
    }

    c = lead & ((1 << (6 - trail_size)) - 1);

    /* Read the rest */
    switch (trail_size) {
    case 3:
        if (*p == e) return UTF_ILLEGAL;
        tmp = **p;
        (*p)++;
        if (!UTF8_IS_TRAIL(tmp)) return UTF_ILLEGAL;
        c = (c << 6) | (tmp & 0x3F);
    /* fall-through */
    case 2:
        if (*p == e) return UTF_ILLEGAL;
        tmp = **p;
        (*p)++;
        if (!UTF8_IS_TRAIL(tmp)) return UTF_ILLEGAL;
        c = (c << 6) | (tmp & 0x3F);
    /* fall-through */
    case 1:
        if (*p == e) return UTF_ILLEGAL;
        tmp = **p;
        (*p)++;
        if (!UTF8_IS_TRAIL(tmp)) return UTF_ILLEGAL;
        c = (c << 6) | (tmp & 0x3F);
    }

    /* Check code point validity: no surrogates and valid range */
    if (!UTF8_IS_VALID(c)) return UTF_ILLEGAL;

    /* make sure it is the most compact representation */
    if (utf8_width(c) != trail_size + 1) return UTF_ILLEGAL;

    if (html && c < 0xA0) return UTF_ILLEGAL;
    return c;
}

static int
utf8_validate(char *p, char *e)
{
    while (p != e)
        if (utf8_next(&p, e, 0) == UTF_ILLEGAL) return 0;
    return 1;
}

static void
utf8_encode(unsigned long value, char utf8_seq[4], unsigned *utf8_seqlen)
{
    /* struct utf8_seq out={0}; */
    if (value <= 0x7F) {
        utf8_seq[0] = value;
        *utf8_seqlen = 1;
    }
    else if (value <= 0x7FF) {
        utf8_seq[0] = (value >> 6) | 0xC0;
        utf8_seq[1] = (value & 0x3F) | 0x80;
        *utf8_seqlen = 2;
    }
    else if (value <= 0xFFFF) {
        utf8_seq[0] = (value >> 12) | 0xE0;
        utf8_seq[1] = ((value >> 6) & 0x3F) | 0x80;
        utf8_seq[2] = (value & 0x3F) | 0x80;
        *utf8_seqlen = 3;
    }
    else {
        utf8_seq[0] = (value >> 18) | 0xF0;
        utf8_seq[1] = ((value >> 12) & 0x3F) | 0x80;
        utf8_seq[2] = ((value >> 6) & 0x3F) | 0x80;
        utf8_seq[3] = (value & 0x3F) | 0x80;
        *utf8_seqlen = 4;
    }
}

static char *
utf8_append(unsigned long x, char *d)
{
    unsigned utf8_seqlen;
    char utf8_seq[4];
    unsigned i;

    utf8_encode(x, utf8_seq, &utf8_seqlen);

    for (i = 0; i < utf8_seqlen; ++i)
        *d++ = utf8_seq[i];
    return d;
}

size_t
jsmnf_unescape(char **p_dest, const char src[], size_t size)
{
    enum { TESTING = 1, ALLOCATING, UNESCAPING } state = TESTING;

    char *src_start = (char *)src, *src_end = (char *)src + size;
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
                    if (!UTF16_IS_SECOND_SURROGATE(x)) goto _err;

                    d = utf8_append(UTF16_JOIN_SURROGATE(first_surrogate, x),
                                    d);
                    second_surrogate_expected = 0;
                }
                else if (UTF16_IS_FIRST_SURROGATE(x)) {
                    second_surrogate_expected = 1;
                    first_surrogate = x;
                }
                else {
                    d = utf8_append(x, d);
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
        *p_dest = calloc(1, size);
        memcpy(*p_dest, src_start, size);
        (*p_dest)[size] = '\0';
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
