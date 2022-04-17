#ifndef GENCODECS_READ

#   error "Missing GENCODECS_READ definition"

#else

#   define GENCODECS_ON_STRUCT
#       include "recipes/struct.h"
#   undef GENCODECS_ON_STRUCT

#   define GENCODECS_ON_JSON
#       define GENCODECS_ON_JSON_DECODER
#           include "recipes/json-decoder.h"
#       undef GENCODECS_ON_JSON_DECODER

#       define GENCODECS_ON_JSON_ENCODER
#           include "recipes/json-encoder.h"
#       undef GENCODECS_ON_JSON_ENCODER
#   undef GENCODECS_ON_JSON

#endif /* GENCODECS_READ */
