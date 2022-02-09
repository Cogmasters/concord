#define GENCODECS_STRUCT
#define GENCODECS_STRUCT_INIT
#define GENCODECS_STRUCT_JSON_ENCODER
#define GENCODECS_STRUCT_JSON_DECODER
#include "gencodecs.h"

#ifdef GENCODECS_HEADER
DIRECTIVE(include <inttypes.h>)
typedef uint64_t u64snowflake;
#endif

#define GENCODECS_READ "application_commands.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "application_commands.params.H"
#include "gencodecs-process.H"
