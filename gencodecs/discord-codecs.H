#define GENCODECS_DATA
#define GENCODECS_INIT
#define GENCODECS_JSON_ENCODER
#define GENCODECS_JSON_DECODER
#include "gencodecs.h"

#ifdef GENCODECS_HEADER
DIRECTIVE(include <inttypes.h>)
typedef uint64_t u64snowflake;
typedef char json_char;
#endif

#define GENCODECS_READ "application.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "audit_log.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "application_commands.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "message_components.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "interactions.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "channel.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "emoji.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "guild.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "guild_template.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "invite.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "sticker.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "user.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "voice.H"
#include "gencodecs-process.H"
#define GENCODECS_READ "webhook.H"
#include "gencodecs-process.H"
