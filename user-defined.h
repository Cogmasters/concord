#ifndef USER_DEFINED_H
#define USER_DEFINED_H
// user-defined functions

void
discord_delete_messages_by_author_id(
  struct discord_client *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t author_id);

#endif //USER_DEFINED_H
