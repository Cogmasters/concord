#include "gencodecs.h"

#ifdef GENCODECS_HEADER
PP_INCLUDE(<inttypes.h>)
PP_INCLUDE("carray.h")
PP_INCLUDE("cog-utils.h")
PP_INCLUDE("types.h")
#endif

/* Custom JSON encoding macros */
#define GENCODECS_JSON_ENCODER_PTR_json_char(b, buf, size, _var, _type)       \
    if (0 > (code = jsonb_token(b, buf, size, _var, strlen(_var))))           \
        return code
#define GENCODECS_JSON_ENCODER_size_t(b, buf, size, _var, _type)              \
        {                                                                     \
            char tok[64];                                                     \
            int toklen;                                                       \
            toklen = sprintf(tok, "%zu", _var);                               \
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))          \
                return code;                                                  \
        }
#define GENCODECS_JSON_ENCODER_uint64_t(b, buf, size, _var, _type)            \
        {                                                                     \
            char tok[64];                                                     \
            int toklen;                                                       \
            toklen = sprintf(tok, "%" PRIu64, _var);                          \
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))         \
                return code;                                                  \
        }
#define GENCODECS_JSON_ENCODER_u64snowflake GENCODECS_JSON_ENCODER_uint64_t
#define GENCODECS_JSON_ENCODER_u64bitmask GENCODECS_JSON_ENCODER_uint64_t
#define GENCODECS_JSON_ENCODER_u64unix_ms(b, buf, size, _var, _type)          \
        {                                                                     \
            char tok[64];                                                     \
            int toklen;                                                       \
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), _var);          \
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))         \
                return code;                                                  \
        }

/* Custom JSON decoding macros */
#define GENCODECS_JSON_DECODER_PTR_json_char(f, buf, _var, _type)             \
    if (f) {                                   \
        _var = _gc_strndup(buf + f->val->start, f->val->end - f->val->start); \
        ret += f->val->end - f->val->start;                                   \
    }
#define GENCODECS_JSON_DECODER_size_t(f, buf, _var, _type)                    \
    if (f && f->val->type == JSMN_PRIMITIVE)                                  \
        _var = (size_t)strtoull(buf + f->val->start, NULL, 10)
#define GENCODECS_JSON_DECODER_uint64_t(f, buf, _var, _type)                  \
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &_var)
#define GENCODECS_JSON_DECODER_u64snowflake GENCODECS_JSON_DECODER_uint64_t
#define GENCODECS_JSON_DECODER_u64bitmask GENCODECS_JSON_DECODER_uint64_t
#define GENCODECS_JSON_DECODER_u64unix_ms(f, buf, _var, _type)                \
    if (f && f->val->type == JSMN_STRING)                                     \
        cog_iso8601_to_unix_ms(buf + f->val->start,                           \
                                 f->val->end - f->val->start, &_var)

/* Custom field macros */
#define FIELD_SNOWFLAKE(_name)                                                \
    FIELD_PRINTF(_name, u64snowflake, "\"%" PRIu64 "\"", "%" SCNu64)
#define FIELD_BITMASK(_name)                                                  \
    FIELD_PRINTF(_name, u64bitmask, "\"%" PRIu64 "\"", "%" SCNu64)
#define FIELD_TIMESTAMP(_name)                                                \
    FIELD_CUSTOM(_name, #_name, u64unix_ms, DECOR_BLANK, INIT_BLANK,          \
                 CLEANUP_BLANK, GENCODECS_JSON_ENCODER_u64unix_ms,            \
                 GENCODECS_JSON_DECODER_u64unix_ms, (u64unix_ms)0)

/* if GENCODECS_READ is not specified then generate for all files */
#ifndef GENCODECS_READ
#   define GENCODECS_READ "all.pre.h"
#endif

#include "gencodecs-process.pre.h"
