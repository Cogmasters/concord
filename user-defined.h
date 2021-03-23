#ifndef USER_DEFINED_H
#define USER_DEFINED_H
// user-defined functions

namespace discord {
namespace user_defined {
namespace bulk_delete_messages {
void run(struct discord_client *client, u64_snowflake_t channel_id, u64_snowflake_t author_id);
}
}
}

#endif //USER_DEFINED_H
