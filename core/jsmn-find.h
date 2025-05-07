#ifndef JSMN_FIND_H
#define JSMN_FIND_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef JSMN_H
#error "jsmn-find.h should be included after jsmn.h"
#else

#ifdef JSMN_HEADER
#define OA_HASH_HEADER
#endif /* JSMN_HEADER */
#include "oa_hash.h"
#undef OA_HASH_HEADER

#define JSMNF_PAIR_ATTRS_const                                                \
    /** JSON object or array pair attributes */                               \
    OA_HASH_ATTRS(const);                                                     \
    /** JSON object or array fields */                                        \
    const struct jsmnf_pair *const fields;                                    \
    /** key attributes */                                                     \
    const jsmntok_t *const k;                                                 \
    /** value attribute */                                                    \
    const jsmntok_t *const v
#define JSMNF_PAIR_ATTRS_mut                                                  \
    /** JSON object or array pair attributes */                               \
    OA_HASH_ATTRS(mut);                                                       \
    /** JSON object or array fields */                                        \
    struct jsmnf_pair *fields;                                                \
    /** key attributes */                                                     \
    jsmntok_t *k;                                                             \
    /** value attribute */                                                    \
    jsmntok_t *v
#define JSMNF_PAIR_ATTRS(_qualifier) JSMNF_PAIR_ATTRS_##_qualifier

typedef struct jsmnf_pair {
    JSMNF_PAIR_ATTRS(const);
} jsmnf_pair;

/** @brief Bucket @ref jsmnf_pair loader, keeps track of pair array
 *      position */
typedef struct jsmnf_loader {
    /** jsmnf_loader can be cast to jsmn_parser */
    jsmn_parser parser;
    /** next pair to allocate */
    unsigned pairnext;
    /** root pair */
    const jsmnf_pair *root;
} jsmnf_loader;

/** @brief JSON table, not supposed to be accessed by user */
typedef struct jsmnf_table {
    /** @private */
    const struct jsmntok _;
    const struct jsmnf_pair __;
    const struct oa_hash_entry ___;
} jsmnf_table;

/**
 * @brief Initialize a @ref jsmnf_loader
 *
 * @param[out] loader jsmnf_loader to be initialized
 */
JSMN_API void jsmnf_init(jsmnf_loader *loader);

/**
 * @brief Populate the @ref jsmnf_pair pairs from jsmn tokens
 *
 * @param[in,out] loader the @ref jsmnf_loader initialized with jsmnf_init()
 * @param[in] js the JSON data string
 * @param[in] len the raw JSON string length
 * @param[out] tokens jsmn tokens
 * @param[out] table jsmnf_table pairs array
 * @param[in] table_len maximum amount of pairs provided
 *      @attention must not be less than the amount of tokens
 * @return a `enum jsmnerr` value for error or the amount of `pairs` used
 */
JSMN_API long jsmnf_load(jsmnf_loader *loader,
                         const char js[],
                         const size_t len,
                         jsmnf_table table[],
                         const size_t table_len);

/**
 * @brief Find a @ref jsmnf_pair token by its associated key
 *
 * @param[in] head a @ref jsmnf_pair object or array loaded at jsmnf_init()
 * @param[in] key the key too be matched
 * @param[in] length length of the key too be matched
 * @return the @ref jsmnf_pair `head`'s field matched to `key`, or NULL if
 * not encountered
 */
JSMN_API const jsmnf_pair *jsmnf_find(const jsmnf_pair *const head,
                                      const char key[],
                                      const size_t length);

/**
 * @brief Find a @ref jsmnf_pair token by its full key path
 *
 * @param[in] head a @ref jsmnf_pair object or array loaded at jsmnf_init()
 * @param[in] path an array of key path strings, from least to highest depth
 * @param[in] depth the depth level of the last `path` key
 * @return the @ref jsmnf_pair `head`'s field matched to `path`, or NULL if
 * not encountered
 */
JSMN_API const jsmnf_pair *jsmnf_find_path(const jsmnf_pair *const head,
                                           char *const path[],
                                           unsigned depth);

/**
 * @brief Populate and automatically allocate the @ref jsmnf_pair pairs from
 *      jsmn tokens
 * @brief jsmnf_load() counterpart that automatically allocates the necessary
 *      amount of pairs necessary for sorting the JSON tokens
 *
 * @param[in,out] loader the @ref jsmnf_loader initialized with jsmnf_init()
 * @param[in] js the JSON data string
 * @param[in] len the raw JSON string length
 * @param[out] p_table pointer to @ref jsmnf_table to be dynamically increased
 *      @note must be `free()`'d once done being used
 * @param[in,out] table_len maximum amount of pairs provided
 * @return a `enum jsmnerr` value for error or the amount of `pairs` used
 */
JSMN_API long jsmnf_load_auto(jsmnf_loader *loader,
                              const char js[],
                              const size_t len,
                              jsmnf_table **p_table,
                              size_t *num_pairs);

/**
 * @brief `jsmn_parse()` counterpart that automatically allocates the necessary
 *      amount of tokens necessary for parsing the JSON string
 *
 * @param[in,out] parser the `jsmn_parser` initialized with `jsmn_init()`
 * @param[in] js the JSON data string
 * @param[in] len the raw JSON string length
 * @param[out] p_tokens pointer to `jsmntok_t` to be dynamically increased
 *      @note must be `free()`'d once done being used
 * @param[in,out] num_tokens amount of tokens
 * @return a `enum jsmnerr` value for error or the amount of `tokens` used
 */
JSMN_API long jsmn_parse_auto(jsmn_parser *parser,
                              const char js[],
                              const size_t len,
                              jsmntok_t **p_tokens,
                              unsigned *num_tokens);

/**
 * @brief Utility function for unescaping a Unicode string
 *
 * @param[out] buf destination buffer
 * @param[in] bufsize destination buffer size
 * @param[in] src source string to be unescaped
 * @param[in] length source string length
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

#define OA_HASH_STATIC
#include "oa_hash.h"
#undef OA_HASH_STATIC

struct _jsmnf_pair_mut {
    JSMNF_PAIR_ATTRS(mut);
};

JSMN_API void
jsmnf_init(jsmnf_loader *loader)
{
    jsmn_init(&loader->parser);
    loader->pairnext = 0;
}

static long
_jsmnf_load_pairs(struct jsmnf_loader *loader,
                  const char js[],
                  struct _jsmnf_pair_mut *curr,
                  const size_t num_tokens,
                  struct _jsmnf_pair_mut pairs[],
                  struct oa_hash_entry buckets[],
                  const size_t table_len)
{
    int offset = 0;

    if (!num_tokens) return 0;

    switch (curr->v->type) {
    case JSMN_STRING:
    case JSMN_PRIMITIVE:
        break;
    case JSMN_OBJECT:
    case JSMN_ARRAY: {
        const unsigned value_size = (unsigned)curr->v->size,
                       top_idx = loader->pairnext + (1 + value_size),
                       bottom_idx = loader->pairnext;
        int ret;

        if (value_size > (table_len - bottom_idx)
            || top_idx > (table_len - bottom_idx))
        {
            return JSMN_ERROR_NOMEM;
        }

        loader->pairnext = top_idx;

        oa_hash_init((struct oa_hash *)curr, &buckets[bottom_idx],
                     top_idx - bottom_idx);
        if (curr == NULL) {
            abort();
        }
        if (JSMN_OBJECT == curr->v->type) {
            while (curr->length < value_size) {
                struct _jsmnf_pair_mut *fields = pairs + bottom_idx,
                                       *element = fields + curr->length;
                element->k = curr->v + 1 + (offset++);
                if (element->k->size > 0) {
                    element->v = curr->v + 1 + offset;
                    oa_hash_set((struct oa_hash *)curr, js + element->k->start,
                                element->k->end - element->k->start, element);
                    if ((ret = _jsmnf_load_pairs(loader, js, element,
                                                 num_tokens - offset, pairs,
                                                 buckets, table_len))
                        < 0)
                    {
                        return ret;
                    }
                    curr->fields = (struct jsmnf_pair *)fields;
                    offset += ret;
                }
                else {
                    oa_hash_set((struct oa_hash *)curr, js + element->k->start,
                                element->k->end - element->k->start, NULL);
                }
            }
        }
        else if (JSMN_ARRAY == curr->v->type) {
            for (; curr->length < value_size; ++curr->length) {
                static jsmntok_t empty_key = { 0 };
                struct oa_hash_entry *entry = curr->buckets + curr->length;
                struct _jsmnf_pair_mut *fields = pairs + bottom_idx,
                                       *element = fields + curr->length;
                entry->state = OA_HASH_ENTRY_OCCUPIED;
                entry->value = element;
                element->v = curr->v + 1 + offset;
                element->k = &empty_key;
                if ((ret = _jsmnf_load_pairs(loader, js, element,
                                             num_tokens - offset, pairs,
                                             buckets, table_len))
                    < 0)
                {
                    return ret;
                }
                curr->fields = (struct jsmnf_pair *)fields;
                offset += ret;
            }
        }
        break;
    }
    default:
    case JSMN_UNDEFINED:
        return JSMN_ERROR_INVAL;
    }

    return offset + 1;
}

JSMN_API long
jsmnf_load(struct jsmnf_loader *loader,
           const char js[],
           const size_t len,
           struct jsmnf_table table[],
           const size_t table_len)
{
    struct jsmntok *tokens = (struct jsmntok *)table;
    struct _jsmnf_pair_mut
        *pairs = (struct _jsmnf_pair_mut *)(((char *)tokens)
                                            + (table_len * sizeof *tokens)),
        *mut_root = &pairs[0];
    struct oa_hash_entry *buckets =
        (struct oa_hash_entry *)(((char *)pairs)
                                 + (table_len * sizeof *pairs));
    long ret;

    if (loader->pairnext == 0) { /* first run, initialize pairs */
        /* initialize tokens if not already initialized */
        if (loader->parser.toknext == 0) {
            memset(tokens, 0, table_len * sizeof *tokens);
            if ((ret = jsmn_parse(&loader->parser, js, len, tokens, table_len))
                < 0)
            {
                return jsmn_init(&loader->parser), ret;
            }
        }
        memset(pairs, 0, table_len * sizeof *pairs);
        memset(buckets, 0, table_len * sizeof *buckets);
        mut_root->v = tokens + loader->pairnext++;
        loader->root = (struct jsmnf_pair *)mut_root;
    }
    if ((ret = _jsmnf_load_pairs(loader, js, mut_root, loader->parser.toknext,
                                 pairs, buckets, table_len))
        < 0)
    {
        /* TODO: rather than reseting pairnext keep the last 'bucket' ptr
         * stored, so it can continue from there in the next try */
        loader->pairnext = 0;
        loader->root = NULL;
    }
    return ret;
}

JSMN_API const struct jsmnf_pair *
jsmnf_find(const struct jsmnf_pair *head,
           const char key[],
           const size_t length)
{
    if (!head || !head->v) return NULL;
    if (!key && !length) return head;

    if (JSMN_OBJECT == head->v->type) {
        return oa_hash_get((struct oa_hash *)head, key, length);
    }
    if (JSMN_ARRAY == head->v->type) {
        char *endptr;
        const unsigned idx = (unsigned)strtoul(key, &endptr, 10);
        if (endptr != key && (idx < head->length)
            && head->buckets[idx].state == OA_HASH_ENTRY_OCCUPIED)
        {
            return head->buckets[idx].value;
        }
    }
    return NULL;
}

JSMN_API const struct jsmnf_pair *
jsmnf_find_path(const struct jsmnf_pair *head,
                char *const path[],
                unsigned depth)
{
    const struct jsmnf_pair *iter = head, *found = NULL;
    unsigned i;
    for (i = 0; i < depth; ++i) {
        if (!iter || !(found = jsmnf_find(iter, path[i], strlen(path[i]))))
            break;
        iter = found;
    }
    return found;
}

#define RECALLOC_OR_ERROR(ptr, prev_size)                                     \
    do {                                                                      \
        const unsigned new_size = *(prev_size) * 2;                           \
        void *tmp = realloc((ptr), new_size * sizeof *(ptr));                 \
        if (!tmp) return JSMN_ERROR_NOMEM;                                    \
        (ptr) = tmp;                                                          \
        memset((ptr) + *(prev_size), 0,                                       \
               (new_size - *(prev_size)) * sizeof *(ptr));                    \
        *(prev_size) = new_size;                                              \
    } while (0)

JSMN_API long
jsmn_parse_auto(struct jsmn_parser *parser,
                const char js[],
                const size_t len,
                struct jsmntok **p_tokens,
                unsigned *num_tokens)
{
    int ret;

    if (NULL == *p_tokens || 0 == *num_tokens) {
        *p_tokens = calloc(1, sizeof **p_tokens);
        *num_tokens = 1;
    }
    while ((ret = jsmn_parse(parser, js, len, *p_tokens, *num_tokens))
           == JSMN_ERROR_NOMEM)
    {
        RECALLOC_OR_ERROR(*p_tokens, num_tokens);
    }
    return ret;
}

JSMN_API long
jsmnf_load_auto(struct jsmnf_loader *loader,
                const char js[],
                const size_t len,
                struct jsmnf_table **p_table,
                size_t *table_len)
{
    int ret;

    if (NULL == *p_table || 0 == *table_len) {
        if (!(*p_table = calloc(1, sizeof **p_table))) {
            return JSMN_ERROR_NOMEM;
        }
        *table_len = 1;
    }
    while ((ret = jsmnf_load(loader, js, len, *p_table, *table_len))
           == JSMN_ERROR_NOMEM)
    {
        RECALLOC_OR_ERROR(*p_table, table_len);
    }
    return ret;
}

#undef RECALLOC_OR_ERROR

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
#endif /* JSMN_H */

#undef JSMNF_PAIR_ATTRS_const
#undef JSMNF_PAIR_ATTRS_mut
#undef JSMNF_PAIR_ATTRS

#ifdef __cplusplus
}
#endif

#endif /* JSMN_FIND_H */
