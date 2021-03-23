#ifndef USER_DEFINED_H
#define USER_DEFINED_H
// user-defined functions

void
discord_user_defined_bulk_delete_message(
  struct discord_client *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t author_id);

#endif //USER_DEFINED_H
