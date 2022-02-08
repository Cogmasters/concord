#include "gencodecs.h"

#ifdef GENCODECS_HEADER
    GENCODECS_DIRECTIVE(include <inttypes.h>)
    typedef uint64_t u64snowflake;
#endif

#define GENCODECS_READ "application_commands.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "application_commands.params.H"
#include "gencodecs-process.H"
