#include <string.h>
#include <concord/discord.h>
#include <inttypes.h>

void snowflake_to_char(char* buf, u64snowflake snowflake);
u64snowflake char_to_snowflake(char* snowflake);
