/*
 * Special thanks to Christopher Wellons (aka skeeto) for giving valuable
 * feedback that helped improve this lib.
 *
 * See: https://www.reddit.com/r/C_Programming/comments/sf95m3/comment/huojrjn
 */
#ifndef JSON_BUILD_H
#define JSON_BUILD_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef JSONB_STATIC
#define JSONB_API static
#else
#define JSONB_API extern
#endif

#ifndef JSONB_MAX_DEPTH
/**
 * Maximum JSON nesting depth, if default value is unwanted then it should be
 *      defined before json-build.h is included:
 *
 * #define JSONB_MAX_DEPTH 256
 * #include "json-build.h"
 */
#define JSONB_MAX_DEPTH 128
#endif /* JSONB_MAX_DEPTH */

/** @brief json-builder return codes */
typedef enum jsonbcode {
    /** no error, operation was a success */
    JSONB_OK = 0,
    /** string is complete, expects no more inputs */
    JSONB_END,
    /** not enough tokens were provided */
    JSONB_ERROR_NOMEM = -1,
    /** token doesn't match expected value */
    JSONB_ERROR_INPUT = -2,
    /** operation would lead to out of boundaries access */
    JSONB_ERROR_STACK = -3,
    /** buffer overflow */
    JSONB_ERROR_OVERFLOW = -4
} jsonbcode;

/** @brief json-builder serializing state */
enum jsonbstate {
    JSONB_INIT = 0,
    JSONB_ARRAY_OR_OBJECT_OR_VALUE = JSONB_INIT,
    JSONB_OBJECT_KEY_OR_CLOSE,
    JSONB_OBJECT_VALUE,
    JSONB_OBJECT_NEXT_KEY_OR_CLOSE,
    JSONB_ARRAY_VALUE_OR_CLOSE,
    JSONB_ARRAY_NEXT_VALUE_OR_CLOSE,
    JSONB_ERROR,
    JSONB_DONE
};

/** @brief Handle for building a JSON string */
typedef struct jsonb {
    /** state stack to keep track and enforce next inputs */
    enum jsonbstate stack[JSONB_MAX_DEPTH + 1];
    /** pointer to stack top */
    enum jsonbstate *top;
    /** offset in the JSON buffer (current length) */
    size_t pos;
} jsonb;

/**
 * @brief Reset a jsonb handle buffer's position tracker
 *  (for streaming purposes)
 * @note Should be used in conjunction with @ref JSONB_ERROR_NOMEM if the
 *      buffer is meant to be used as a stream
 *
 * @param builder pointer to the @ref jsonb handle
 */
#define jsonb_reset(builder) ((builder)->pos = 0)

/**
 * @brief Initialize a jsonb handle
 *
 * @param builder the handle to be initialized
 */
JSONB_API void jsonb_init(jsonb *builder);

/**
 * @brief Push an object to the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_object(jsonb *builder, char buf[], size_t bufsize);

/**
 * @brief @ref jsonb_object() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_object_auto(jsonb *builder,
                                      char *p_buf[],
                                      size_t *p_bufsize);

/**
 * @brief Pop an object from the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_object_pop(jsonb *builder,
                                     char buf[],
                                     size_t bufsize);

/**
 * @brief @ref jsonb_object_pop() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_object_pop_auto(jsonb *builder,
                                          char *p_buf[],
                                          size_t *p_bufsize);

/**
 * @brief Push a key to the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @param key the key to be inserted
 * @param len the key length
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_key(
    jsonb *builder, char buf[], size_t bufsize, const char key[], size_t len);

/**
 * @brief @ref jsonb_key() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer to the JSON buffer size
 * @param key the key to be inserted
 * @param len the key length
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_key_auto(jsonb *builder,
                                   char *p_buf[],
                                   size_t *p_bufsize,
                                   const char key[],
                                   size_t len);

/**
 * @brief Push an array to the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_array(jsonb *builder, char buf[], size_t bufsize);

/**
 * @brief @ref jsonb_array() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer to the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_array_auto(jsonb *builder,
                                     char *p_buf[],
                                     size_t *p_bufsize);

/**
 * @brief Pop an array from the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_array_pop(jsonb *builder,
                                    char buf[],
                                    size_t bufsize);

/**
 * @brief @ref jsonb_array_pop() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer to the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_array_pop_auto(jsonb *builder,
                                         char *p_buf[],
                                         size_t *p_bufsize);

/**
 * @brief Push a raw JSON token to the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @param token the token to be inserted
 * @param len the token length
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_token(jsonb *builder,
                                char buf[],
                                size_t bufsize,
                                const char token[],
                                size_t len);

/**
 * @brief @ref jsonb_token() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer to the JSON buffer size
 * @param token the token to be inserted
 * @param len the token length
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_token_auto(jsonb *builder,
                                     char *p_buf[],
                                     size_t *p_bufsize,
                                     const char token[],
                                     size_t len);

/**
 * @brief Push a boolean token to the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @param boolean the boolean to be inserted
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_bool(jsonb *builder,
                               char buf[],
                               size_t bufsize,
                               int boolean);

/**
 * @brief @ref jsonb_bool() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer to the JSON buffer size
 * @param boolean the boolean to be inserted
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_bool_auto(jsonb *builder,
                                    char *p_buf[],
                                    size_t *p_bufsize,
                                    int boolean);

/**
 * @brief Push a null token to the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_null(jsonb *builder, char buf[], size_t bufsize);

/**
 * @brief @ref jsonb_null() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer to the JSON buffer size
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_null_auto(jsonb *builder,
                                    char *p_buf[],
                                    size_t *p_bufsize);

/**
 * @brief Push a string token to the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @param str the string to be inserted
 * @param len the string length
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_string(
    jsonb *builder, char buf[], size_t bufsize, const char str[], size_t len);

/**
 * @brief @ref jsonb_string() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer to the JSON buffer size
 * @param str the string to be inserted
 * @param len the string length
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_string_auto(jsonb *builder,
                                      char *p_buf[],
                                      size_t *p_bufsize,
                                      const char str[],
                                      size_t len);

/**
 * @brief Push a number token to the builder
 *
 * @param builder the builder initialized with jsonb_init()
 * @param buf the JSON buffer
 * @param bufsize the JSON buffer size
 * @param number the number to be inserted
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_number(jsonb *builder,
                                 char buf[],
                                 size_t bufsize,
                                 double number);

/**
 * @brief @ref jsonb_number() with dynamic buffer
 *
 * @param builder the builder initialized with jsonb_init()
 * @param p_buf pointer to the JSON buffer
 * @param p_bufsize pointer to the JSON buffer size
 * @param number the number to be inserted
 * @return @ref jsonbcode value
 */
JSONB_API jsonbcode jsonb_number_auto(jsonb *builder,
                                      char *p_buf[],
                                      size_t *p_bufsize,
                                      double number);

#ifndef JSONB_HEADER
#include <stdio.h>
#include <stdlib.h>
#ifndef JSONB_DEBUG
#define TRACE(prev, next) next
#define DECORATOR(a)
#else
static const char *
_jsonb_eval_state(enum jsonbstate state)
{
    switch (state) {
    case JSONB_ARRAY_OR_OBJECT_OR_VALUE: return "array or object or value";
    case JSONB_OBJECT_KEY_OR_CLOSE: return "object key or close";
    case JSONB_OBJECT_NEXT_KEY_OR_CLOSE: return "object next key or close";
    case JSONB_OBJECT_VALUE: return "object value";
    case JSONB_ARRAY_VALUE_OR_CLOSE: return "array value or close";
    case JSONB_ARRAY_NEXT_VALUE_OR_CLOSE: return "array next value or close";
    case JSONB_ERROR: return "error";
    case JSONB_DONE: return "done";
    default: return "unknown";
    }
}
#define TRACE(prev, next)                                                     \
    do {                                                                      \
        enum jsonbstate _prev = prev, _next = next;                           \
        fprintf(stderr, "%s():L%d | %s -> %s\n", __func__, __LINE__,          \
                _jsonb_eval_state(_prev), _jsonb_eval_state(_next));          \
    } while (0)
#define DECORATOR(d) d
#endif /* JSONB_DEBUG */

#define STACK_HEAD(b, state) *(b)->top = (state)
#define STACK_PUSH(b, state) TRACE(*(b)->top, *++(b)->top = (state))
#define STACK_POP(b)         TRACE(*(b)->top, DECORATOR(*)--(b)->top)

#define BUFFER_COPY_CHAR_STATIC(b, c, _pos, buf, bufsize)                     \
    do {                                                                      \
        if ((b)->pos + (_pos) + 1 + 1 > (bufsize)) {                          \
            (buf)[(b)->pos] = '\0';                                           \
            return JSONB_ERROR_NOMEM;                                         \
        }                                                                     \
        (buf)[(b)->pos + (_pos)++] = (c);                                     \
        (buf)[(b)->pos + (_pos)] = '\0';                                      \
    } while (0)
#define BUFFER_COPY_STATIC(b, value, len, _pos, buf, bufsize)                 \
    do {                                                                      \
        size_t i;                                                             \
        if ((b)->pos + (_pos) + (len) + 1 > (bufsize)) {                      \
            (buf)[(b)->pos] = '\0';                                           \
            return JSONB_ERROR_NOMEM;                                         \
        }                                                                     \
        for (i = 0; i < (len); ++i)                                           \
            (buf)[(b)->pos + (_pos) + i] = (value)[i];                        \
        (_pos) += (len);                                                      \
        (buf)[(b)->pos + (_pos)] = '\0';                                      \
    } while (0)
#define BUFFER_COPY_CHAR_REALLOC(b, c, _pos, p_buf, p_bufsize)                \
    do {                                                                      \
        if ((b)->pos + (_pos) + 1 + 1 > *p_bufsize) {                         \
            char *new_buf = NULL;                                             \
            const size_t needed = (b)->pos + (_pos) + 1 + 1;                  \
            size_t new_size = *p_bufsize + (*p_bufsize >> 1); /* 1.5x */      \
            if (new_size < needed) new_size = needed;                         \
            if (new_size < *p_bufsize) return JSONB_ERROR_OVERFLOW;           \
            new_buf = realloc(*p_buf, new_size);                              \
            if (!new_buf) return JSONB_ERROR_NOMEM;                           \
            *p_buf = new_buf;                                                 \
            *p_bufsize = new_size;                                            \
        }                                                                     \
        (*p_buf)[(b)->pos + (_pos)++] = (c);                                  \
        (*p_buf)[(b)->pos + (_pos)] = '\0';                                   \
    } while (0)
#define BUFFER_COPY_REALLOC(b, value, len, _pos, p_buf, p_bufsize)            \
    do {                                                                      \
        size_t i;                                                             \
        if ((b)->pos + (_pos) + (len) + 1 > *p_bufsize) {                     \
            char *new_buf = NULL;                                             \
            const size_t needed = (b)->pos + (_pos) + (len) + 1;              \
            size_t new_size = *p_bufsize + (*p_bufsize >> 1); /* 1.5x */      \
            if (new_size < needed) new_size = needed;                         \
            if (new_size < *p_bufsize) return JSONB_ERROR_OVERFLOW;           \
            new_buf = realloc(*p_buf, new_size);                              \
            if (!new_buf) return JSONB_ERROR_NOMEM;                           \
            *p_buf = new_buf;                                                 \
            *p_bufsize = new_size;                                            \
        }                                                                     \
        for (i = 0; i < (len); ++i)                                           \
            (*p_buf)[(b)->pos + (_pos) + i] = (value)[i];                     \
        (_pos) += (len);                                                      \
        (*p_buf)[(b)->pos + (_pos)] = '\0';                                   \
    } while (0)

JSONB_API void
jsonb_init(jsonb *b)
{
    static jsonb empty_builder;
    *b = empty_builder;
    b->top = b->stack;
}

#define JSONB_OBJECT_EXEC(_type, buf, bufsize)                                \
    enum jsonbstate new_state;                                                \
    size_t pos = 0;                                                           \
    if (b->top - b->stack >= JSONB_MAX_DEPTH) return JSONB_ERROR_STACK;       \
    switch (*b->top) {                                                        \
    case JSONB_ARRAY_NEXT_VALUE_OR_CLOSE:                                     \
        BUFFER_COPY_CHAR_##_type(b, ',', pos, buf, bufsize);                  \
        /* fall-through */                                                    \
    case JSONB_ARRAY_VALUE_OR_CLOSE:                                          \
        new_state = JSONB_ARRAY_NEXT_VALUE_OR_CLOSE;                          \
        break;                                                                \
    case JSONB_OBJECT_VALUE:                                                  \
        new_state = JSONB_OBJECT_NEXT_KEY_OR_CLOSE;                           \
        break;                                                                \
    case JSONB_ARRAY_OR_OBJECT_OR_VALUE:                                      \
        new_state = JSONB_DONE;                                               \
        break;                                                                \
    default:                                                                  \
        STACK_HEAD(b, JSONB_ERROR);                                           \
        /* fall-through */                                                    \
    case JSONB_DONE:                                                          \
    case JSONB_ERROR:                                                         \
        return JSONB_ERROR_INPUT;                                             \
    }                                                                         \
    BUFFER_COPY_CHAR_##_type(b, '{', pos, buf, bufsize);                      \
    STACK_HEAD(b, new_state);                                                 \
    STACK_PUSH(b, JSONB_OBJECT_KEY_OR_CLOSE);                                 \
    b->pos += pos;                                                            \
    return JSONB_OK

JSONB_API jsonbcode
jsonb_object(jsonb *b, char buf[], size_t bufsize)
{
    JSONB_OBJECT_EXEC(STATIC, buf, bufsize);
}

JSONB_API jsonbcode
jsonb_object_auto(jsonb *b, char *p_buf[], size_t *p_bufsize)
{
    JSONB_OBJECT_EXEC(REALLOC, p_buf, p_bufsize);
}

#define JSONB_OBJECT_POP_EXEC(_type, buf, bufsize)                            \
    enum jsonbcode code;                                                      \
    size_t pos = 0;                                                           \
    switch (*b->top) {                                                        \
    case JSONB_OBJECT_KEY_OR_CLOSE:                                           \
    case JSONB_OBJECT_NEXT_KEY_OR_CLOSE:                                      \
        code = b->stack == b->top - 1 ? JSONB_END : JSONB_OK;                 \
        break;                                                                \
    default:                                                                  \
        STACK_HEAD(b, JSONB_ERROR);                                           \
        /* fall-through */                                                    \
    case JSONB_DONE:                                                          \
    case JSONB_ERROR:                                                         \
        return JSONB_ERROR_INPUT;                                             \
    }                                                                         \
    BUFFER_COPY_CHAR_##_type(b, '}', pos, buf, bufsize);                      \
    STACK_POP(b);                                                             \
    b->pos += pos;                                                            \
    return code

JSONB_API jsonbcode
jsonb_object_pop(jsonb *b, char buf[], size_t bufsize)
{
    JSONB_OBJECT_POP_EXEC(STATIC, buf, bufsize);
}

JSONB_API jsonbcode
jsonb_object_pop_auto(jsonb *b, char *p_buf[], size_t *p_bufsize)
{
    JSONB_OBJECT_POP_EXEC(REALLOC, p_buf, p_bufsize);
}

static jsonbcode
_jsonb_escape_STATIC(size_t *pos,
                     char buf[],
                     size_t bufsize,
                     unsigned offset,
                     const char str[],
                     size_t len)
{
    char *esc_tok = NULL, _esc_tok[8] = "\\u00";
    char *esc_buf = NULL;
    int extra_bytes = 0;
    size_t i;

    buf += offset;
    bufsize -= offset;
second_iter:
    /* 1st iteration, esc_buf is NULL and count extra_bytes needed for escaping
     * 2st iteration, esc_buf is not NULL, and does escaping.  */
    for (i = 0; i < len; ++i) {
        unsigned char c = str[i];
        esc_tok = NULL;
        switch (c) {
        case 0x22: esc_tok = "\\\""; break;
        case 0x5C: esc_tok = "\\\\"; break;
        case '\b': esc_tok = "\\b"; break;
        case '\f': esc_tok = "\\f"; break;
        case '\n': esc_tok = "\\n"; break;
        case '\r': esc_tok = "\\r"; break;
        case '\t': esc_tok = "\\t"; break;
        default: if (c <= 0x1F) {
                static const char tohex[] = "0123456789abcdef";
                _esc_tok[4] = tohex[c >> 4];
                _esc_tok[5] = tohex[c & 0xF];
                _esc_tok[6] = 0;
                esc_tok = _esc_tok;
            }
        }
        if (esc_tok) {
            int j;
            for (j = 0; esc_tok[j]; j++) {
                if (!esc_buf) /* count how many extra bytes are needed */
                    continue;
                *esc_buf++ = esc_tok[j];
            }
            extra_bytes += j - 1;
        }
        else if (esc_buf) {
            *esc_buf++ = c;
        }
    }

    if (*pos + len + extra_bytes > bufsize) {
        *buf = '\0';
        return JSONB_ERROR_NOMEM;
    }

    if (esc_buf) {
        *pos += len + extra_bytes;
        return JSONB_OK;
    }
    if (!extra_bytes) {
        size_t j;
        for (j = 0; j < len; ++j)
            buf[*pos + j] = str[j];
        *pos += len;
        return JSONB_OK;
    }
    esc_buf = buf + *pos;
    extra_bytes = 0;
    goto second_iter;
}

static jsonbcode
_jsonb_escape_REALLOC(size_t *pos,
                      char *p_buf[],
                      size_t *p_bufsize,
                      unsigned offset,
                      const char str[],
                      size_t len)
{
    char *esc_tok = NULL, _esc_tok[8] = "\\u00";
    char *esc_buf = NULL;
    int extra_bytes = 0;
    size_t i;

    int second_pass = 0;
    ptrdiff_t esc_buf_offset = 0;

    char *buf;
    size_t bufsize;
restart:
    buf = *p_buf + offset;
    bufsize = *p_bufsize - offset;

    if (second_pass && esc_buf) esc_buf = buf + esc_buf_offset;

second_iter:
    /* 1st iteration, esc_buf is NULL and count extra_bytes needed for escaping
     * 2st iteration, esc_buf is not NULL, and does escaping.  */
    for (i = 0; i < len; ++i) {
        unsigned char c = str[i];
        esc_tok = NULL;
        switch (c) { case 0x22: esc_tok = "\\\""; break;
        case 0x5C: esc_tok = "\\\\"; break;
        case '\b': esc_tok = "\\b"; break;
        case '\f': esc_tok = "\\f"; break;
        case '\n': esc_tok = "\\n"; break;
        case '\r': esc_tok = "\\r"; break;
        case '\t': esc_tok = "\\t"; break;
        default: if (c <= 0x1F) {
                static const char tohex[] = "0123456789abcdef";
                _esc_tok[4] = tohex[c >> 4];
                _esc_tok[5] = tohex[c & 0xF];
                _esc_tok[6] = 0;
                esc_tok = _esc_tok;
            }
        }
        if (esc_tok) {
            int j;
            for (j = 0; esc_tok[j]; j++) {
                if (!esc_buf) /* count how many extra bytes are needed */
                    continue;
                *esc_buf++ = esc_tok[j];
            }
            extra_bytes += j - 1;
        }
        else if (esc_buf) {
            *esc_buf++ = c;
        }
    }

    if (*pos + len + extra_bytes + 1 > bufsize) {
        char *new_buf = NULL;
        const size_t needed = *pos + len + extra_bytes + 1;
        size_t new_size = *p_bufsize + (*p_bufsize >> 1); /* 1.5x */
        if (new_size < needed) new_size = needed;
        if (new_size < *p_bufsize) return JSONB_ERROR_OVERFLOW;
        new_buf = realloc(*p_buf, new_size);
        if (!new_buf) return JSONB_ERROR_NOMEM;
        if (esc_buf) esc_buf_offset = esc_buf - buf;
        *p_buf = new_buf;
        *p_bufsize = new_size;
        second_pass = 1;
        goto restart;
    }

    if (esc_buf) {
        *pos += len + extra_bytes;
        return JSONB_OK;
    }
    if (!extra_bytes) {
        size_t j;
        for (j = 0; j < len; ++j)
            buf[*pos + j] = str[j];
        *pos += len;
        return JSONB_OK;
    }
    esc_buf = buf + *pos;
    extra_bytes = 0;
    goto second_iter;
}

#define JSONB_KEY_EXEC(_type, buf, bufsize, key, len)                         \
    size_t pos = 0;                                                           \
    switch (*b->top) {                                                        \
    case JSONB_OBJECT_NEXT_KEY_OR_CLOSE:                                      \
        BUFFER_COPY_CHAR_##_type(b, ',', pos, buf, bufsize);                  \
        /* fall-through */                                                    \
    case JSONB_OBJECT_KEY_OR_CLOSE: {                                         \
        enum jsonbcode ret;                                                   \
        BUFFER_COPY_CHAR_##_type(b, '"', pos, buf, bufsize);                  \
        ret = _jsonb_escape_##_type(&pos, buf, bufsize, b->pos, key, len);    \
        if (ret != JSONB_OK) return ret;                                      \
        BUFFER_COPY_##_type(b, "\":", 2, pos, buf, bufsize);                  \
        STACK_HEAD(b, JSONB_OBJECT_VALUE);                                    \
    } break;                                                                  \
    default:                                                                  \
        STACK_HEAD(b, JSONB_ERROR);                                           \
        /* fall-through */                                                    \
    case JSONB_DONE:                                                          \
        return JSONB_ERROR_INPUT;                                             \
    }                                                                         \
    b->pos += pos;                                                            \
    return JSONB_OK

JSONB_API jsonbcode
jsonb_key(jsonb *b, char buf[], size_t bufsize, const char key[], size_t len)
{
    JSONB_KEY_EXEC(STATIC, buf, bufsize, key, len);
}

JSONB_API jsonbcode
jsonb_key_auto(
    jsonb *b, char *p_buf[], size_t *p_bufsize, const char key[], size_t len)
{
    JSONB_KEY_EXEC(REALLOC, p_buf, p_bufsize, key, len);
}

#define JSONB_ARRAY_EXEC(_type, buf, bufsize)                                 \
    enum jsonbstate new_state;                                                \
    size_t pos = 0;                                                           \
    if (b->top - b->stack >= JSONB_MAX_DEPTH) return JSONB_ERROR_STACK;       \
    switch (*b->top) {                                                        \
    case JSONB_ARRAY_NEXT_VALUE_OR_CLOSE:                                     \
        BUFFER_COPY_CHAR_##_type(b, ',', pos, buf, bufsize);                  \
        /* fall-through */                                                    \
    case JSONB_ARRAY_VALUE_OR_CLOSE:                                          \
        new_state = JSONB_ARRAY_NEXT_VALUE_OR_CLOSE;                          \
        break;                                                                \
    case JSONB_OBJECT_VALUE:                                                  \
        new_state = JSONB_OBJECT_NEXT_KEY_OR_CLOSE;                           \
        break;                                                                \
    case JSONB_ARRAY_OR_OBJECT_OR_VALUE:                                      \
        new_state = JSONB_DONE;                                               \
        break;                                                                \
    default:                                                                  \
        STACK_HEAD(b, JSONB_ERROR);                                           \
        /* fall-through */                                                    \
    case JSONB_DONE:                                                          \
    case JSONB_ERROR:                                                         \
        return JSONB_ERROR_INPUT;                                             \
    }                                                                         \
    BUFFER_COPY_CHAR_##_type(b, '[', pos, buf, bufsize);                      \
    STACK_HEAD(b, new_state);                                                 \
    STACK_PUSH(b, JSONB_ARRAY_VALUE_OR_CLOSE);                                \
    b->pos += pos;                                                            \
    return JSONB_OK

JSONB_API jsonbcode
jsonb_array(jsonb *b, char buf[], size_t bufsize)
{
    JSONB_ARRAY_EXEC(STATIC, buf, bufsize);
}

JSONB_API jsonbcode
jsonb_array_auto(jsonb *b, char *p_buf[], size_t *p_bufsize)
{
    JSONB_ARRAY_EXEC(REALLOC, p_buf, p_bufsize);
}

#define JSONB_ARRAY_POP_EXEC(_type, buf, bufsize)                             \
    enum jsonbcode code;                                                      \
    size_t pos = 0;                                                           \
    switch (*b->top) {                                                        \
    case JSONB_ARRAY_VALUE_OR_CLOSE:                                          \
    case JSONB_ARRAY_NEXT_VALUE_OR_CLOSE:                                     \
        code = b->stack == b->top - 1 ? JSONB_END : JSONB_OK;                 \
        break;                                                                \
    default:                                                                  \
        STACK_HEAD(b, JSONB_ERROR);                                           \
        /* fall-through */                                                    \
    case JSONB_DONE:                                                          \
    case JSONB_ERROR:                                                         \
        return JSONB_ERROR_INPUT;                                             \
    }                                                                         \
    BUFFER_COPY_CHAR_##_type(b, ']', pos, buf, bufsize);                      \
    STACK_POP(b);                                                             \
    b->pos += pos;                                                            \
    return code

JSONB_API jsonbcode
jsonb_array_pop(jsonb *b, char buf[], size_t bufsize)
{
    JSONB_ARRAY_POP_EXEC(STATIC, buf, bufsize);
}

JSONB_API jsonbcode
jsonb_array_pop_auto(jsonb *b, char *p_buf[], size_t *p_bufsize)
{
    JSONB_ARRAY_POP_EXEC(REALLOC, p_buf, p_bufsize);
}

#define JSONB_TOKEN_EXEC(_type, buf, bufsize, token, len)                     \
    enum jsonbstate next_state;                                               \
    enum jsonbcode code;                                                      \
    size_t pos = 0;                                                           \
    switch (*b->top) {                                                        \
    case JSONB_ARRAY_OR_OBJECT_OR_VALUE:                                      \
        next_state = JSONB_DONE;                                              \
        code = JSONB_END;                                                     \
        break;                                                                \
    case JSONB_ARRAY_NEXT_VALUE_OR_CLOSE:                                     \
        BUFFER_COPY_CHAR_##_type(b, ',', pos, buf, bufsize);                  \
        /* fall-through */                                                    \
    case JSONB_ARRAY_VALUE_OR_CLOSE:                                          \
        next_state = JSONB_ARRAY_NEXT_VALUE_OR_CLOSE;                         \
        code = JSONB_OK;                                                      \
        break;                                                                \
    case JSONB_OBJECT_VALUE:                                                  \
        next_state = JSONB_OBJECT_NEXT_KEY_OR_CLOSE;                          \
        code = JSONB_OK;                                                      \
        break;                                                                \
    default:                                                                  \
        STACK_HEAD(b, JSONB_ERROR);                                           \
        /* fall-through */                                                    \
    case JSONB_DONE:                                                          \
    case JSONB_ERROR:                                                         \
        return JSONB_ERROR_INPUT;                                             \
    }                                                                         \
    BUFFER_COPY_##_type(b, token, len, pos, buf, bufsize);                    \
    STACK_HEAD(b, next_state);                                                \
    b->pos += pos;                                                            \
    return code

JSONB_API jsonbcode
jsonb_token(
    jsonb *b, char buf[], size_t bufsize, const char token[], size_t len)
{
    JSONB_TOKEN_EXEC(STATIC, buf, bufsize, token, len);
}

JSONB_API jsonbcode
jsonb_token_auto(
    jsonb *b, char *p_buf[], size_t *p_bufsize, const char token[], size_t len)
{
    JSONB_TOKEN_EXEC(REALLOC, p_buf, p_bufsize, token, len);
}

JSONB_API jsonbcode
jsonb_bool(jsonb *b, char buf[], size_t bufsize, int boolean)
{
    return boolean ? jsonb_token(b, buf, bufsize, "true", 4)
                   : jsonb_token(b, buf, bufsize, "false", 5);
}

JSONB_API jsonbcode
jsonb_bool_auto(jsonb *b, char *p_buf[], size_t *p_bufsize, int boolean)
{
    return boolean ? jsonb_token_auto(b, p_buf, p_bufsize, "true", 4)
                   : jsonb_token_auto(b, p_buf, p_bufsize, "false", 5);
}

JSONB_API jsonbcode
jsonb_null(jsonb *b, char buf[], size_t bufsize)
{
    return jsonb_token(b, buf, bufsize, "null", 4);
}

JSONB_API jsonbcode
jsonb_null_auto(jsonb *b, char *p_buf[], size_t *p_bufsize)
{
    return jsonb_token_auto(b, p_buf, p_bufsize, "null", 4);
}

#define JSONB_STRING_EXEC(_type, buf, bufsize, str, len)                      \
    enum jsonbstate next_state;                                               \
    enum jsonbcode code, ret;                                                 \
    size_t pos = 0;                                                           \
    switch (*b->top) {                                                        \
    case JSONB_ARRAY_OR_OBJECT_OR_VALUE:                                      \
        next_state = JSONB_DONE;                                              \
        code = JSONB_END;                                                     \
        break;                                                                \
    case JSONB_ARRAY_NEXT_VALUE_OR_CLOSE:                                     \
        BUFFER_COPY_CHAR_##_type(b, ',', pos, buf, bufsize);                  \
        /* fall-through */                                                    \
    case JSONB_ARRAY_VALUE_OR_CLOSE:                                          \
        next_state = JSONB_ARRAY_NEXT_VALUE_OR_CLOSE;                         \
        code = JSONB_OK;                                                      \
        break;                                                                \
    case JSONB_OBJECT_VALUE:                                                  \
        next_state = JSONB_OBJECT_NEXT_KEY_OR_CLOSE;                          \
        code = JSONB_OK;                                                      \
        break;                                                                \
    default:                                                                  \
        STACK_HEAD(b, JSONB_ERROR);                                           \
        /* fall-through */                                                    \
    case JSONB_DONE:                                                          \
    case JSONB_ERROR:                                                         \
        return JSONB_ERROR_INPUT;                                             \
    }                                                                         \
    BUFFER_COPY_CHAR_##_type(b, '"', pos, buf, bufsize);                      \
    ret = _jsonb_escape_##_type(&pos, buf, bufsize, b->pos, str, len);        \
    if (ret != JSONB_OK) return ret;                                          \
    BUFFER_COPY_CHAR_##_type(b, '"', pos, buf, bufsize);                      \
    STACK_HEAD(b, next_state);                                                \
    b->pos += pos;                                                            \
    return code

JSONB_API jsonbcode
jsonb_string(
    jsonb *b, char buf[], size_t bufsize, const char str[], size_t len)
{
    JSONB_STRING_EXEC(STATIC, buf, bufsize, str, len);
}

JSONB_API jsonbcode
jsonb_string_auto(
    jsonb *b, char *p_buf[], size_t *p_bufsize, const char str[], size_t len)
{
    JSONB_STRING_EXEC(REALLOC, p_buf, p_bufsize, str, len);
}

JSONB_API jsonbcode
jsonb_number(jsonb *b, char buf[], size_t bufsize, double number)
{
    char token[32];
    const long len = sprintf(token, "%.17G", number);
    return (len < 0) ? JSONB_ERROR_INPUT
                     : jsonb_token(b, buf, bufsize, token, len);
}

JSONB_API jsonbcode
jsonb_number_auto(jsonb *b, char *p_buf[], size_t *p_bufsize, double number)
{
    char token[32];
    const long len = sprintf(token, "%.17G", number);
    return (len < 0) ? JSONB_ERROR_INPUT
                     : jsonb_token_auto(b, p_buf, p_bufsize, token, len);
}

#undef TRACE
#undef DECORATOR
#undef STACK_HEAD
#undef STACK_PUSH
#undef STACK_POP
#undef BUFFER_COPY_CHAR_STATIC
#undef BUFFER_COPY_STATIC
#undef BUFFER_COPY_CHAR_REALLOC
#undef BUFFER_COPY_REALLOC
#undef JSONB_OBJECT_EXEC
#undef JSONB_OBJECT_POP_EXEC
#undef JSONB_KEY_EXEC
#undef JSONB_ARRAY_EXEC
#undef JSONB_ARRAY_POP_EXEC
#undef JSONB_TOKEN_EXEC
#undef JSONB_STRING_EXEC

#endif /* JSONB_HEADER */

#ifdef __cplusplus
}
#endif

#endif /* JSON_BUILD_H */
