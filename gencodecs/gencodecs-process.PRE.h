#ifndef GENCODECS_READ
#error "Missing GENCODECS_READ definition"
#else

#define DATA         (1 << 1)
#define JSON_DECODER (1 << 2)
#define JSON_ENCODER (1 << 3)
#define JSON         (JSON_DECODER | JSON_ENCODER)

#define GENCODECS_RECIPE DATA
#include "recipes/struct.h"
#undef GENCODECS_RECIPE

#define GENCODECS_RECIPE JSON_DECODER
#include "recipes/json-decoder.h"
#undef GENCODECS_RECIPE

#define GENCODECS_RECIPE JSON_ENCODER
#include "recipes/json-encoder.h"
#undef GENCODECS_RECIPE

#undef DATA
#undef JSON_DECODER
#undef JSON_ENCODER
#undef JSON

#endif /* GENCODECS_READ */
