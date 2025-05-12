#include "gencodecs.h"

#ifdef GENCODECS_HEADER
PP_INCLUDE(<inttypes.h>)
PP_INCLUDE("cog-utils.h")
PP_INCLUDE("types.h")
PP_INCLUDE("concord-error.h")
#endif

/* Custom JSON encoding macros */
#define GENCODECS_JSON_ENCODER_PTR_int(b, buf, size, _var, _type)             \
    for (size_t i = 0; i < DISCORD_METADATA(_var)->size; ++i)                 \
        GENCODECS_JSON_ENCODER_int(b, buf, size, _var[i], _type)
#define GENCODECS_JSON_ENCODER_PTR_json_char(b, buf, size, _var, _type)       \
    if (0 > (code = jsonb_token_auto(b, buf, size, _var,                      \
                                     _var ? strlen(_var) : 0)))               \
    return code
#define GENCODECS_JSON_ENCODER_PTR_uint64_t(b, buf, size, _var, _type)        \
    for (size_t i = 0; i < DISCORD_METADATA(_var)->size; ++i)                 \
        GENCODECS_JSON_ENCODER_uint64_t(b, buf, size, _var[i], _type)
#define GENCODECS_JSON_ENCODER_PTR_u64snowflake GENCODECS_JSON_ENCODER_PTR_uint64_t
#define GENCODECS_JSON_ENCODER_PTR_u64bitmask   GENCODECS_JSON_ENCODER_PTR_uint64_t

#define GENCODECS_JSON_ENCODER_size_t(b, buf, size, _var, _type)              \
    {                                                                         \
        char tok[64];                                                         \
        int toklen;                                                           \
        toklen = sprintf(tok, "%zu", _var);                                   \
        if (0 > (code = jsonb_token_auto(b, buf, size, tok, toklen)))         \
            return code;                                                      \
    }
#define GENCODECS_JSON_ENCODER_uint64_t(b, buf, size, _var, _type)            \
    {                                                                         \
        char tok[64];                                                         \
        int toklen;                                                           \
        toklen = sprintf(tok, "%" PRIu64, _var);                              \
        if (0 > (code = jsonb_string_auto(b, buf, size, tok, toklen)))        \
            return code;                                                      \
    }
#define GENCODECS_JSON_ENCODER_u64snowflake GENCODECS_JSON_ENCODER_uint64_t
#define GENCODECS_JSON_ENCODER_u64bitmask   GENCODECS_JSON_ENCODER_uint64_t
#define GENCODECS_JSON_ENCODER_u64unix_ms(b, buf, size, _var, _type)          \
    {                                                                         \
        char tok[64];                                                         \
        int toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), _var);          \
        if (0 > (code = jsonb_string_auto(b, buf, size, tok, toklen)))        \
            return code;                                                      \
    }

/* Custom JSON decoding macros */
#define GENCODECS_JSON_DECODER_PTR_int(_f, _js, _var, _type)                  \
    for (size_t i = 0; i < DISCORD_METADATA(_var)->size; ++i)                 \
        GENCODECS_JSON_DECODER_int(_f, _js, _var[i], _type)
#define GENCODECS_JSON_DECODER_PTR_json_char(_f, _js, _var, _type)            \
    _var = _gc_strndup(js + _f->v->start, _f->v->end - _f->v->start);         \
    ret += _f->v->end - _f->v->start
#define GENCODECS_JSON_DECODER_PTR_uint64_t(_f, _js, _var, _type)             \
    for (size_t i = 0; i < DISCORD_METADATA(_var)->size; ++i)                 \
        GENCODECS_JSON_DECODER_uint64_t(_f, _js, _var[i], _type)
#define GENCODECS_JSON_DECODER_PTR_u64snowflake GENCODECS_JSON_DECODER_PTR_uint64_t
#define GENCODECS_JSON_DECODER_PTR_u64bitmask   GENCODECS_JSON_DECODER_PTR_uint64_t
#define GENCODECS_JSON_DECODER_size_t(_f, _js, _var, _type)                   \
    if (_f->v->type == JSMN_PRIMITIVE)                                        \
        _var = (size_t)strtoull(_js + _f->v->start, NULL, 10)
#define GENCODECS_JSON_DECODER_uint64_t(_f, _js, _var, _type)                 \
    sscanf(_js + _f->v->start, "%" SCNu64, &_var)
#define GENCODECS_JSON_DECODER_u64snowflake GENCODECS_JSON_DECODER_uint64_t
#define GENCODECS_JSON_DECODER_u64bitmask   GENCODECS_JSON_DECODER_uint64_t
#define GENCODECS_JSON_DECODER_u64unix_ms(_f, _js, _var, _type)               \
    if (_f->v->type == JSMN_STRING)                                           \
    cog_iso8601_to_unix_ms(_js + _f->v->start, _f->v->end - _f->v->start, &_var)

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
#define GENCODECS_READ "all.PRE.h"
#endif

#include "gencodecs-process.PRE.h"
