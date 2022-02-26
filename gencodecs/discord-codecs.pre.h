#define GENCODECS_DATA
#define GENCODECS_INIT
#define GENCODECS_JSON_ENCODER
#define GENCODECS_JSON_DECODER
#include "gencodecs.h"

#ifdef GENCODECS_HEADER
PP_INCLUDE("common.h")
PP_INCLUDE("cog-utils.h")
#endif

#define RST_PUB_STRUCT(_type) \
"@verbatim embed:rst" \
".. container:: toggle" \
"" \
"  .. container:: header" \
"" \
"    **Methods**" \
"" \
"  - Initializer:" \
"" \
"    - :code:`void discord_channel_init(struct discord_channel *)`" \
"  - Cleanup:" \
"" \
"    - :code:`void discord_channel_cleanup(struct discord_channel *)`" \
"  - JSON Decoder:" \
"" \
"    - :code:`size_t discord_channel_from_json(char *rbuf, size_t len, struct discord_channel *)`" \
"    - :code:`size_t discord_channel_from_jsmnf(jsmnf *root, char *rbuf, struct discord_channel *)`" \
"  - JSON Encoder:" \
"" \
"    - :code:`size_t discord_channel_to_json(char *wbuf, size_t len, struct discord_channel *)`" \
"    - :code:`jsonbcode discord_channel_to_jsonb(jsonb *b, char *wbuf, size_t len, struct discord_channel *)`" \
"@endverbatim"

/* Custom JSON encoding macros */
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

/* Custom JSON decoding macros */
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

/* Custom field macros */
#define FIELD_SNOWFLAKE(_name)                                                \
    FIELD_PRINTF(_name, u64snowflake, "\"%" PRIu64 "\"", "%" SCNu64)
#define FIELD_TIMESTAMP(_name)                                                \
    FIELD_CUSTOM(_name, #_name, u64unix_ms, DECOR_BLANK, INIT_BLANK,          \
                 CLEANUP_BLANK, JSON_ENCODER_u64unix_ms,                      \
                 JSON_DECODER_u64unix_ms, (u64unix_ms)0)

/* if GENCODECS_READ is not specified then generate for all files */
#ifndef GENCODECS_READ
#   define GENCODECS_READ "all.pre.h"
#endif

#include "gencodecs-process.pre.h"
