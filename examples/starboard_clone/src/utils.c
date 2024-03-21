#include "utils.h"

void snowflake_to_char(char* buf, u64snowflake snowflake) {
  snprintf(buf, 22, "%"PRIu64, snowflake);
}

u64snowflake char_to_snowflake(char* snowflake) {
  u64snowflake val;
  cog_strtou64(snowflake, strlen(snowflake), &val);
  return val;
}
