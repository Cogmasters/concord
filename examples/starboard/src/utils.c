#include "utils.h"
#include "string.h"
#include "starboard.h"

u64snowflake star_string_to_snowflake(char* string) {
  u64snowflake buf;
  cog_strtou64(string, strlen(string), &buf);
  return buf;
}

int star_snowflake_to_string(char* buffer, u64snowflake snowflake) {
  return snprintf(buffer, STAR_SNOWFLAKE_BUF_SIZE, "%"PRIu64, snowflake);
}

bool star_string_to_bool(char* string) {
  return string[0] == 't' ||
         string[0] == 'T' ||
         string[0] == '1';
}