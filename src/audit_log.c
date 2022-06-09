#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_get_guild_audit_log(struct discord *client,
                            u64snowflake guild_id,
                            struct discord_get_guild_audit_log *params,
                            struct discord_ret_audit_log *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    if (params) {
        int offset = 0;

        if (params->user_id) {
            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "?user_id=%" PRIu64, params->user_id);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
        if (params->action_type) {
            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "%saction_type=%d", *query ? "&" : "?",
                               params->action_type);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
        if (params->before) {
            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "%sbefore=%" PRIu64, *query ? "&" : "?",
                               params->before);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
        if (params->limit) {
            offset +=
                snprintf(query + offset, sizeof(query) - (size_t)offset,
                         "%slimit=%d", *query ? "&" : "?", params->limit);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
    }

    DISCORD_ATTR_INIT(attr, discord_audit_log, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/audit-logs%s", guild_id,
                            query);
}
