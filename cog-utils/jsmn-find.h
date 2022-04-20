#ifndef JSMN_FIND_H
#define JSMN_FIND_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef JSMN_H
#error "jsmn-find.h should be included after jsmn.h"
#endif

/** @brief Internally used sized-buffer */
struct _jsmnf_szbuf {
    /** buffer's contents */
    const char *contents;
    /** buffer's length */
    int length;
};

/** @brief JSON object */
typedef struct jsmnf_pair {
    /** amount of children currently filled in */
    int length;
    /** children threshold capacity */
    int capacity;
    /** this pair's children */
    struct jsmnf_pair *buckets;

    /** the key of the pair */
    struct _jsmnf_szbuf key;
    /** the value of the pair */
    struct _jsmnf_szbuf value;
    /** current state of this pair */
    int state;

    /** JSON type @see `jsmntype_t` at jsmn.h */
    jsmntype_t type;
} jsmnf_pair;

/** @brief Bucket (@ref jsmnf_pair) loader, keeps track of pair array
 *      position */
typedef struct jsmnf_loader {
    /** next pair to allocate */
    unsigned pairnext;
} jsmnf_loader;

/**
 * @brief Initialize a @ref jsmnf_loader
 *
 * @param loader jsmnf_loader to be initialized
 */
JSMN_API void jsmnf_init(jsmnf_loader *loader);

/**
 * @brief Populate the @ref jsmnf_pair pairs from jsmn tokens
 *
 * @param loader the @ref jsmnf_loader initialized with jsmnf_init()
 * @param js the raw JSON string
 * @param tokens jsmn tokens initialized with jsmn_parse() / jsmn_parse_auto()
 * @param num_tokens amount of tokens initialized with jsmn_parse() /
 *      jsmn_parse_auto()
 * @param pairs jsmnf_pair pairs array
 * @param num_pairs maximum amount of pairs provided
 * @return a `enum jsmnerr` value for error or the amount of `pairs` used
 */
JSMN_API int jsmnf_load(jsmnf_loader *loader,
                        const char js[],
                        const jsmntok_t tokens[],
                        unsigned num_tokens,
                        jsmnf_pair pairs[],
                        unsigned num_pairs);

/**
 * @brief Find a @ref jsmnf_pair token by its associated key
 *
 * @param head a @ref jsmnf_pair object or array loaded at jsmnf_start()
 * @param key the key too be matched
 * @param length length of the key too be matched
 * @return the @ref jsmnf_pair `head`'s field matched to `key`, or NULL if
 * not encountered
 */
JSMN_API jsmnf_pair *jsmnf_find(jsmnf_pair *head,
                                const char key[],
                                int length);

/**
 * @brief Find a @ref jsmnf_pair token by its full key path
 *
 * @param head a @ref jsmnf_pair object or array loaded at jsmnf_start()
 * @param path an array of key path strings, from least to highest depth
 * @param depth the depth level of the last `path` key
 * @return the @ref jsmnf_pair `head`'s field matched to `path`, or NULL if
 * not encountered
 */
JSMN_API jsmnf_pair *jsmnf_find_path(jsmnf_pair *head,
                                     char *const path[],
                                     int depth);

/**
 * @brief Populate and automatically allocate the @ref jsmnf_pair pairs from
 *      jsmn tokens
 * @brief jsmnf_load() counterpart that automatically allocates the necessary
 *      amount of pairs necessary for sorting the JSON tokens
 *
 * @param loader the @ref jsmnf_loader initialized with jsmnf_init()
 * @param js the raw JSON string
 * @param tokens jsmn tokens initialized with jsmn_parse() / jsmn_parse_auto()
 * @param num_tokens amount of tokens initialized with jsmn_parse() /
 *      jsmn_parse_auto()
 * @param p_pairs pointer to @ref jsmnf_pair to be dynamically increased @note
 *      must be `free()`'d once done being used
 * @param num_pairs initial amount of pairs provided
 * @return a `enum jsmnerr` value for error or the amount of `pairs` used
 */
JSMN_API int jsmnf_load_auto(jsmnf_loader *loader,
                             const char js[],
                             const jsmntok_t tokens[],
                             unsigned num_tokens,
                             jsmnf_pair **p_pairs,
                             unsigned num_pairs);

/**
 * @brief `jsmn_parse()` counterpart that automatically allocates the necessary
 *      amount of tokens necessary for parsing the JSON string
 *
 * @param parser the `jsmn_parser` initialized with `jsmn_init()`
 * @param js the raw JSON string
 * @param len the raw JSON string length
 * @param p_tokens pointer to `jsmntok_t` to be dynamically increased @note
 *      must be `free()`'d once done being used
 * @param num_tokens initial amount of tokens provided
 * @return a `enum jsmnerr` value for error or the amount of `tokens` used
 */
JSMN_API int jsmn_parse_auto(jsmn_parser *parser,
                             const char *js,
                             size_t len,
                             jsmntok_t **p_tokens,
                             unsigned num_tokens);

/**
 * @brief Utility function for unescaping a Unicode string
 *
 * @param buf destination buffer
 * @param bufsize destination buffer size
 * @param src source string to be unescaped
 * @param length source string length
 * @return length of unescaped string if successful or a negative jsmn error
 *      code on failure
 */
JSMN_API long jsmnf_unescape(char buf[],
                             size_t bufsize,
                             const char src[],
                             size_t length);

#ifndef JSMN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chash.h"

#define _jsmnf_key_hash(key, hash)                                            \
    5031;                                                                     \
    do {                                                                      \
        int __CHASH_HINDEX;                                                   \
        for (__CHASH_HINDEX = 0; __CHASH_HINDEX < (key).length;               \
             ++__CHASH_HINDEX) {                                              \
            (hash) =                                                          \
                (((hash) << 1) + (hash)) + (key).contents[__CHASH_HINDEX];    \
        }                                                                     \
    } while (0)

/* compare jsmnf keys */
#define _jsmnf_key_compare(cmp_a, cmp_b)                                      \
    (!strncmp((cmp_a).contents, (cmp_b).contents, (cmp_b).length))

#define _JSMNF_TABLE_HEAP   0
#define _JSMNF_TABLE_BUCKET struct jsmnf_pair
#define _JSMNF_TABLE_FREE_KEY(key)
#define _JSMNF_TABLE_HASH(key, hash) _jsmnf_key_hash(key, hash)
#define _JSMNF_TABLE_FREE_VALUE(value)
#define _JSMNF_TABLE_COMPARE(cmp_a, cmp_b) _jsmnf_key_compare(cmp_a, cmp_b)

JSMN_API void
jsmnf_init(jsmnf_loader *loader)
{
    loader->pairnext = 0;
}

static int
_jsmnf_load_pairs(struct jsmnf_loader *loader,
                  struct jsmnf_pair *curr,
                  const char js[],
                  const struct jsmntok *tok,
                  unsigned num_tokens,
                  struct jsmnf_pair *pairs,
                  unsigned num_pairs)
{
    int offset = 0;

    if (!num_tokens) return 0;

    switch (tok->type) {
    case JSMN_STRING:
    case JSMN_PRIMITIVE:
        break;
    default: { /* should be either JSMN_ARRAY or JSMN_OBJECT */
        const unsigned top_idx = loader->pairnext + 1 + (tok->size * 1.3),
                       bottom_idx = loader->pairnext;
        int ret;

        if (tok->size > (int)(num_pairs - bottom_idx)
            || top_idx > (num_pairs - bottom_idx))
        {
            return JSMN_ERROR_NOMEM;
        }

        loader->pairnext = top_idx;

        (void)chash_init_stack(curr, &pairs[bottom_idx], top_idx - bottom_idx,
                               _JSMNF_TABLE);

        if (JSMN_OBJECT == tok->type) {
            while (curr->length < tok->size) {
                const struct jsmntok *_key = tok + 1 + offset;
                struct jsmnf_pair *found = NULL;
                struct _jsmnf_szbuf key, value = { 0 };

                key.contents = js + _key->start;
                key.length = _key->end - _key->start;

                /* skip Key token */
                offset += 1;

                /* key->size > 0 means we're dealing with an Object or Array
                 */
                if (_key->size > 0) {
                    const struct jsmntok *_value = tok + 1 + offset;

                    value.contents = js + _value->start;
                    value.length = _value->end - _value->start;

                    chash_assign(curr, key, value, _JSMNF_TABLE);
                    (void)chash_lookup_bucket(curr, key, found, _JSMNF_TABLE);

                    ret = _jsmnf_load_pairs(loader, found, js, _value,
                                            num_tokens - offset, pairs,
                                            num_pairs);
                    if (ret < 0) return ret;

                    offset += ret;
                }
                else {
                    chash_assign(curr, key, value, _JSMNF_TABLE);
                    (void)chash_lookup_bucket(curr, key, found, _JSMNF_TABLE);
                }
            }
            break;
        }
        if (JSMN_ARRAY == tok->type) {
            for (; curr->length < tok->size; ++curr->length) {
                const struct jsmntok *_value = tok + 1 + offset;
                struct jsmnf_pair *pair = curr->buckets + curr->length;
                struct _jsmnf_szbuf value;

                value.contents = js + _value->start;
                value.length = _value->end - _value->start;

                ret = _jsmnf_load_pairs(loader, pair, js, _value,
                                        num_tokens - offset, pairs, num_pairs);
                if (ret < 0) return ret;

                offset += ret;

                /* assign array element */
                pair->value = value;
                pair->state = CHASH_FILLED;
                /* unused for array elements */
                pair->key.contents = NULL;
                pair->key.length = 0;
            }
        }
        break;
    }
    /* fall-through */
    case JSMN_UNDEFINED:
        fputs("Error: JSMN_UNDEFINED token detected, jsmn_parse() failure\n",
              stderr);
        return JSMN_ERROR_INVAL;
    }

    curr->type = tok->type;

    return offset + 1;
}

JSMN_API int
jsmnf_load(struct jsmnf_loader *loader,
           const char js[],
           const struct jsmntok tokens[],
           unsigned num_tokens,
           struct jsmnf_pair pairs[],
           unsigned num_pairs)
{
    int ret;

    if (!loader->pairnext) { /* first run, initialize pairs */
        static const struct jsmnf_pair blank_pair = { 0 };
        unsigned i = 0;

        for (; i < num_pairs; ++i)
            pairs[i] = blank_pair;
        /* root */
        pairs[0].value.contents = js + tokens->start;
        pairs[0].value.length = tokens->end - tokens->start;

        ++loader->pairnext;
    }

    ret = _jsmnf_load_pairs(loader, pairs, js, tokens, num_tokens, pairs,
                            num_pairs);
    if (ret < 0) loader->pairnext = 0;
    return ret;
}

JSMN_API struct jsmnf_pair *
jsmnf_find(struct jsmnf_pair *head, const char key[], int length)
{
    struct jsmnf_pair *found = NULL;

    if (!key || !head) return NULL;

    if (JSMN_OBJECT == head->type) {
        struct _jsmnf_szbuf _key;
        int contains;
        _key.contents = key;
        _key.length = length;
        contains = chash_contains(head, _key, contains, _JSMNF_TABLE);
        if (contains) {
            (void)chash_lookup_bucket(head, _key, found, _JSMNF_TABLE);
        }
    }
    else if (JSMN_ARRAY == head->type) {
        char *endptr;
        int idx = (int)strtol(key, &endptr, 10);
        if (endptr != key) found = head->buckets + idx;
    }
    return found;
}

JSMN_API struct jsmnf_pair *
jsmnf_find_path(struct jsmnf_pair *head, char *const path[], int depth)
{
    struct jsmnf_pair *iter = head, *found = NULL;
    int i = 0;
    for (; i < depth; ++i) {
        if (!iter) continue;
        found = jsmnf_find(iter, path[i], strlen(path[i]));
        if (!found) break;
        iter = found;
    }
    return found;
}

JSMN_API int
jsmn_parse_auto(struct jsmn_parser *parser,
                const char *js,
                size_t len,
                struct jsmntok **p_tokens,
                unsigned num_tokens)
{
    int ret;

    if (NULL == *p_tokens) {
        *p_tokens = malloc(sizeof **p_tokens);
        num_tokens = 1;
    }

    while (1) {
        ret = jsmn_parse(parser, js, len, *p_tokens, num_tokens);
        if (ret != JSMN_ERROR_NOMEM) {
            break;
        }
        else {
            const unsigned new_num_tokens = num_tokens * 2;
            void *tmp;

            tmp = realloc(*p_tokens, new_num_tokens * sizeof **p_tokens);
            if (!tmp) return JSMN_ERROR_NOMEM;

            num_tokens = new_num_tokens;
            *p_tokens = tmp;
        }
    }
    return ret;
}

JSMN_API int
jsmnf_load_auto(struct jsmnf_loader *loader,
                const char js[],
                const struct jsmntok tokens[],
                unsigned num_tokens,
                struct jsmnf_pair **p_pairs,
                unsigned num_pairs)
{
    int ret;

    if (NULL == *p_pairs) {
        *p_pairs = malloc(sizeof **p_pairs);
        num_pairs = 1;
    }

    while (1) {
        ret = jsmnf_load(loader, js, tokens, num_tokens, *p_pairs, num_pairs);
        if (ret != JSMN_ERROR_NOMEM) {
            break;
        }
        else {
            const unsigned new_num_pairs = num_pairs * 2;
            void *tmp;

            tmp = realloc(*p_pairs, new_num_pairs * sizeof **p_pairs);
            if (!tmp) return JSMN_ERROR_NOMEM;

            num_pairs = new_num_pairs;
            *p_pairs = tmp;
        }
    }
    return ret;
}

static int
_jsmnf_read_4_digits(char *s, const char *end, unsigned *p_hex)
{
    char buf[5] = { 0 };
    int i;

    if (end - s < 4) return JSMN_ERROR_PART;

    for (i = 0; i < 4; i++) {
        buf[i] = s[i];
        if (('0' <= s[i] && s[i] <= '9') || ('A' <= s[i] && s[i] <= 'F')
            || ('a' <= s[i] && s[i] <= 'f'))
        {
            continue;
        }
        return JSMN_ERROR_INVAL;
    }

    *p_hex = (unsigned)strtoul(buf, NULL, 16);

    return 4;
}

#define _JSMNF_UTF16_IS_FIRST_SURROGATE(c)                                    \
    (0xD800 <= (unsigned)c && (unsigned)c <= 0xDBFF)
#define _JSMNF_UTF16_IS_SECOND_SURROGATE(c)                                   \
    (0xDC00 <= (unsigned)c && (unsigned)c <= 0xDFFF)
#define _JSMNF_UTF16_JOIN_SURROGATE(c1, c2)                                   \
    (((((unsigned long)c1 & 0x3FF) << 10) | ((unsigned)c2 & 0x3FF)) + 0x10000)
#define _JSMNF_UTF8_IS_VALID(c)                                               \
    (((unsigned long)c <= 0x10FFFF)                                           \
     && ((unsigned long)c < 0xD800 || (unsigned long)c > 0xDFFF))
#define _JSMNF_UTF8_IS_TRAIL(c) (((unsigned char)c & 0xC0) == 0x80)
#define _JSMNF_UTF_ILLEGAL      0xFFFFFFFFu

static int
_jsmnf_utf8_trail_length(unsigned char c)
{
    if (c < 128) return 0;
    if (c < 194) return -1;
    if (c < 224) return 1;
    if (c < 240) return 2;
    if (c <= 244) return 3;
    return -1;
}

static int
_jsmnf_utf8_width(unsigned long value)
{
    if (value <= 0x7F) return 1;
    if (value <= 0x7FF) return 2;
    if (value <= 0xFFFF) return 3;
    return 4;
}

/* See RFC 3629
   Based on: http://www.w3.org/International/questions/qa-forms-utf-8 */
static unsigned long
_jsmnf_utf8_next(char **p, const char *end)
{
    unsigned char lead, tmp;
    int trail_size;
    unsigned long c;

    if (*p == end) return _JSMNF_UTF_ILLEGAL;

    lead = **p;
    (*p)++;

    /* First byte is fully validated here */
    trail_size = _jsmnf_utf8_trail_length(lead);

    if (trail_size < 0) return _JSMNF_UTF_ILLEGAL;

    /* Ok as only ASCII may be of size = 0 also optimize for ASCII text */
    if (trail_size == 0) return lead;

    c = lead & ((1 << (6 - trail_size)) - 1);

    /* Read the rest */
    switch (trail_size) {
    case 3:
        if (*p == end) return _JSMNF_UTF_ILLEGAL;
        tmp = **p;
        (*p)++;
        if (!_JSMNF_UTF8_IS_TRAIL(tmp)) return _JSMNF_UTF_ILLEGAL;
        c = (c << 6) | (tmp & 0x3F);
    /* fall-through */
    case 2:
        if (*p == end) return _JSMNF_UTF_ILLEGAL;
        tmp = **p;
        (*p)++;
        if (!_JSMNF_UTF8_IS_TRAIL(tmp)) return _JSMNF_UTF_ILLEGAL;
        c = (c << 6) | (tmp & 0x3F);
    /* fall-through */
    case 1:
        if (*p == end) return _JSMNF_UTF_ILLEGAL;
        tmp = **p;
        (*p)++;
        if (!_JSMNF_UTF8_IS_TRAIL(tmp)) return _JSMNF_UTF_ILLEGAL;
        c = (c << 6) | (tmp & 0x3F);
    }

    /* Check code point validity: no surrogates and valid range */
    if (!_JSMNF_UTF8_IS_VALID(c)) return _JSMNF_UTF_ILLEGAL;

    /* make sure it is the most compact representation */
    if (_jsmnf_utf8_width(c) != trail_size + 1) return _JSMNF_UTF_ILLEGAL;

    return c;
}

static long
_jsmnf_utf8_validate(char *p, const char *end)
{
    const char *start = p;
    while (p != end) {
        if (_jsmnf_utf8_next(&p, end) == _JSMNF_UTF_ILLEGAL)
            return JSMN_ERROR_INVAL;
    }
    return (long)(end - start);
}

static unsigned
_jsmnf_utf8_encode(unsigned long value, char utf8_seq[4])
{
    if (value <= 0x7F) {
        utf8_seq[0] = value;
        return 1;
    }
    if (value <= 0x7FF) {
        utf8_seq[0] = (value >> 6) | 0xC0;
        utf8_seq[1] = (value & 0x3F) | 0x80;
        return 2;
    }
    if (value <= 0xFFFF) {
        utf8_seq[0] = (value >> 12) | 0xE0;
        utf8_seq[1] = ((value >> 6) & 0x3F) | 0x80;
        utf8_seq[2] = (value & 0x3F) | 0x80;
        return 3;
    }
    utf8_seq[0] = (value >> 18) | 0xF0;
    utf8_seq[1] = ((value >> 12) & 0x3F) | 0x80;
    utf8_seq[2] = ((value >> 6) & 0x3F) | 0x80;
    utf8_seq[3] = (value & 0x3F) | 0x80;
    return 4;
}

static int
_jsmnf_utf8_append(unsigned long hex, char *buf_tok, const char *buf_end)
{
    char utf8_seq[4];
    unsigned utf8_seqlen = _jsmnf_utf8_encode(hex, utf8_seq);
    unsigned i;

    if ((buf_tok + utf8_seqlen) >= buf_end) return JSMN_ERROR_NOMEM;

    for (i = 0; i < utf8_seqlen; ++i)
        buf_tok[i] = utf8_seq[i];
    return utf8_seqlen;
}

#define BUF_PUSH(buf_tok, c, buf_end)                                         \
    do {                                                                      \
        if (buf_tok >= buf_end) return JSMN_ERROR_NOMEM;                      \
        *buf_tok++ = c;                                                       \
    } while (0)

JSMN_API long
jsmnf_unescape(char buf[], size_t bufsize, const char src[], size_t len)
{
    char *src_tok = (char *)src, *const src_end = src_tok + len;
    char *buf_tok = buf, *const buf_end = buf + bufsize;
    int second_surrogate_expected = 0;
    unsigned first_surrogate = 0;

    while (*src_tok && src_tok < src_end) {
        char c = *src_tok++;

        if (0 <= c && c <= 0x1F) return JSMN_ERROR_INVAL;

        if (c != '\\') {
            if (second_surrogate_expected) return JSMN_ERROR_INVAL;
            BUF_PUSH(buf_tok, c, buf_end);
            continue;
        }

        /* expects escaping but src is a well-formed string */
        if (!*src_tok || src_tok >= src_end) return JSMN_ERROR_PART;

        c = *src_tok++;

        if (second_surrogate_expected && c != 'u') return JSMN_ERROR_INVAL;

        switch (c) {
        case '"':
        case '\\':
        case '/':
            BUF_PUSH(buf_tok, c, buf_end);
            break;
        case 'b':
            BUF_PUSH(buf_tok, '\b', buf_end);
            break;
        case 'f':
            BUF_PUSH(buf_tok, '\f', buf_end);
            break;
        case 'n':
            BUF_PUSH(buf_tok, '\n', buf_end);
            break;
        case 'r':
            BUF_PUSH(buf_tok, '\r', buf_end);
            break;
        case 't':
            BUF_PUSH(buf_tok, '\t', buf_end);
            break;
        case 'u': {
            unsigned hex;
            int ret = _jsmnf_read_4_digits(src_tok, src_end, &hex);

            if (ret != 4) return ret;

            src_tok += ret;

            if (second_surrogate_expected) {
                if (!_JSMNF_UTF16_IS_SECOND_SURROGATE(hex))
                    return JSMN_ERROR_INVAL;

                ret = _jsmnf_utf8_append(
                    _JSMNF_UTF16_JOIN_SURROGATE(first_surrogate, hex), buf_tok,
                    buf_end);
                if (ret < 0) return ret;

                buf_tok += ret;

                second_surrogate_expected = 0;
            }
            else if (_JSMNF_UTF16_IS_FIRST_SURROGATE(hex)) {
                second_surrogate_expected = 1;
                first_surrogate = hex;
            }
            else {
                ret = _jsmnf_utf8_append(hex, buf_tok, buf_end);
                if (ret < 0) return ret;

                buf_tok += ret;
            }
        } break;
        default:
            return JSMN_ERROR_INVAL;
        }
    }
    return _jsmnf_utf8_validate(buf, buf_tok);
}

#undef BUF_PUSH

#endif /* JSMN_HEADER */

#ifdef __cplusplus
}
#endif

#endif /* JSMN_FIND_H */
