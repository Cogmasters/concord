#define GENCODECS_DATA
#define GENCODECS_INIT
#define GENCODECS_JSON_ENCODER
#define GENCODECS_JSON_DECODER
#include "gencodecs.h"

#ifdef GENCODECS_HEADER
PP_INCLUDE("common.h")
PP_INCLUDE("cog-utils.h")
#endif

#define JSON_ENCODER_PTR_json_char(b, buf, size, _var, _type)                 \
    if (0 > (code = jsonb_token(b, buf, size, _var, strlen(_var))))           \
        return code
#define JSON_ENCODER_u64snowflake(b, buf, size, _var, _type)                  \
        {                                                                     \
            char tok[64];                                                     \
            int toklen;                                                       \
            toklen = sprintf(tok, "%" PRIu64, _var);                          \
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))         \
                return code;                                                  \
        }
#define JSON_ENCODER_u64unix_ms(b, buf, size, _var, _type)                    \
        {                                                                     \
            char tok[64];                                                     \
            int toklen;                                                       \
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), _var);          \
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))         \
                return code;                                                  \
        }

#define JSON_DECODER_PTR_json_char(f, buf, _var, _type)                       \
    if (f) {                                   \
        _var = _gc_strndup(buf + f->val->start, f->val->end - f->val->start); \
        ret += f->val->end - f->val->start;                                   \
    }
#define JSON_DECODER_u64snowflake(f, buf, _var, _type)                        \
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &_var)
#define JSON_DECODER_u64unix_ms(f, buf, _var, _type)                          \
    if (f && f->val->type == JSMN_PRIMITIVE)                                  \
        cog_iso8601_to_unix_ms(buf + f->val->start,                           \
                                 f->val->end - f->val->start, &_var)

#define FIELD_SNOWFLAKE(_name)                                                \
    FIELD_PRINTF(_name, u64snowflake, "\"%" PRIu64 "\"", "%" SCNu64)
#define FIELD_TIMESTAMP(_name)                                                \
    FIELD_CUSTOM(_name, #_name, u64unix_ms, DECOR_BLANK, INIT_BLANK,          \
                 CLEANUP_BLANK, JSON_ENCODER_u64unix_ms,                      \
                 JSON_DECODER_u64unix_ms, (u64unix_ms)0)

#ifndef GENCODECS_READ
#   define GENCODECS_READ "all.H"
#endif

#include "gencodecs-process.H"
