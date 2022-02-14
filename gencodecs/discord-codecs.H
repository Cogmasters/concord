#define GENCODECS_DATA
#define GENCODECS_INIT
#define GENCODECS_JSON_ENCODER
#define GENCODECS_JSON_DECODER
#include "gencodecs.h"

#ifdef GENCODECS_HEADER
PP_INCLUDE(<inttypes.h>)
typedef uint64_t u64snowflake;
typedef char json_char;
#endif

#define JSON_ENCODER_PTR_json_char(b, buf, size, _var, _type)                 \
    JSON_ENCODER_PTR_char(b, buf, size, _var, _type)
#define JSON_ENCODER_u64snowflake(b, buf, size, _var, _type)                  \
    JSON_ENCODER_ullong(b, buf, size, _var, _type)

#define JSON_DECODER_PTR_json_char(f, buf, _var, _type)                       \
    JSON_DECODER_PTR_char(f, buf, _var, _type)
#define JSON_DECODER_u64snowflake(f, buf, _var, _type)                        \
    JSON_DECODER_ullong(f, buf, _var, _type)

#ifndef GENCODECS_READ
#   define GENCODECS_READ "all.H"
#endif

#include "gencodecs-process.H"
