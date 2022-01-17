#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"

void
print_usage(void)
{
    printf(
        "\n\nThis bot demonstrates how easy it is to manipulate guild"
        " endpoints.\n"
        "1. Type 'guild.role_create <name>' to create a new role\n"
        "2. Type 'guild.role_delete <role_id>' to delete\n"
        "3. Type 'guild.role_member_add <user_id> <role_id>' to assign role "
        "to user\n"
        "4. Type 'guild.role_member_remove <user_id> <role_id>' to remove "
        "role from user\n"
        "5. Type 'guild.role_list' to get a list of this guild roles\n"
        "6. Type 'guild.member_get <id>' to fetch a member by their ID\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Guild-Bot succesfully connected to Discord as %s#%s!",
             bot->username, bot->discriminator);
}

void
log_on_role_create(struct discord *client,
                   u64_snowflake_t guild_id,
                   const struct discord_role *role)
{
    log_warn("Role (%" PRIu64 ") created", role->id);
}

void
log_on_role_update(struct discord *client,
                   u64_snowflake_t guild_id,
                   const struct discord_role *role)
{
    log_warn("Role (%" PRIu64 ") updated", role->id);
}

void
log_on_role_delete(struct discord *client,
                   u64_snowflake_t guild_id,
                   u64_snowflake_t role_id)
{
    log_warn("Role (%" PRIu64 ") deleted", role_id);
}

void
on_role_create(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    char name[128] = "";

    sscanf(msg->content, "%s", name);
    if (!*name) {
        log_error("Couldn't create role `%s`", name);
        return;
    }

    struct discord_create_guild_role params = { .name = name };
    discord_create_guild_role(client, msg->guild_id, &params, NULL);
}

void
on_role_delete(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t role_id = 0;

    sscanf(msg->content, "%" SCNu64, &role_id);
    if (!role_id) {
        log_error("Invalid format for `guild.role_delete <role_id>`");
        return;
    }

    discord_delete_guild_role(client, msg->guild_id, role_id, NULL);
}

void
on_role_member_add(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t user_id = 0, role_id = 0;

    sscanf(msg->content, "%" SCNu64 " %" SCNu64, &user_id, &role_id);
    if (!user_id || !role_id) {
        log_error(
            "Invalid format for `guild.role_member_add <user_id> <role_id>`");
        return;
    }

    discord_add_guild_member_role(client, msg->guild_id, user_id, role_id,
                                  NULL);
}

void
on_role_member_remove(struct discord *client,
                      const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t user_id = 0, role_id = 0;

    sscanf(msg->content, "%" SCNu64 " %" SCNu64, &user_id, &role_id);
    if (!user_id || !role_id) {
        log_error("Invalid format for `guild.role_member_remove <user_id> "
                  "<role_id>`");
        return;
    }

    discord_remove_guild_member_role(client, msg->guild_id, user_id, role_id,
                                     NULL);
}

void
done_get_guild_roles(struct discord *client,
                     void *data,
                     const struct discord_role **roles)
{
    char text[DISCORD_MAX_MESSAGE_LEN];

    char *cur = text;
    char *end = &text[sizeof(text) - 1];
    char *prev;

    for (size_t i = 0; roles[i]; ++i) {
        prev = cur;
        cur += snprintf(cur, end - cur, "<@&%" PRIu64 ">(%" PRIu64 ")\n",
                        roles[i]->id, roles[i]->id);

        if (cur >= end) { // to make sure no role is skipped
            *prev = '\0'; // end string before truncation
            cur = text; // reset

            --i; // retry current iteration

            continue;
        }
    }

    log_info("%s", text);
}

void
fail_get_guild_roles(struct discord *client, CCORDcode code, void *data)
{
    log_error("Couldn't fetch guild roles: %s",
              discord_strerror(code, client));
}

void
on_role_list(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct discord_ret_roles ret = {
        .done = &done_get_guild_roles,
        .fail = &fail_get_guild_roles,
    };
    discord_get_guild_roles(client, msg->guild_id, &ret);
}

void
done_get_guild_member(struct discord *client,
                      void *data,
                      const struct discord_guild_member *member)
{
    log_info("Member %s (%" PRIu64 ") found!", member->user->username,
             member->user->id);
}

void
fail_get_guild_member(struct discord *client, CCORDcode code, void *data)
{
    log_error("Couldn't fetch guild member: %s",
              discord_strerror(code, client));
}

void
on_member_get(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t user_id = 0;

    sscanf(msg->content, "%" SCNu64, &user_id);
    if (!user_id) {
        log_error("Invalid format for `guild.member_get <user_id>`");
        return;
    }

    struct discord_ret_guild_member ret = {
        .done = &done_get_guild_member,
        .fail = &fail_get_guild_member,
    };
    discord_get_guild_member(client, msg->guild_id, user_id, &ret);
}

int
main(int argc, char *argv[])
{
    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    ccord_global_init();
    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Couldn't initialize client");

    discord_set_on_ready(client, &on_ready);
    discord_set_on_guild_role_create(client, &log_on_role_create);
    discord_set_on_guild_role_update(client, &log_on_role_update);
    discord_set_on_guild_role_delete(client, &log_on_role_delete);

    discord_set_prefix(client, "guild.");
    discord_set_on_command(client, "role_create", &on_role_create);
    discord_set_on_command(client, "role_delete", &on_role_delete);
    discord_set_on_command(client, "role_member_add", &on_role_member_add);
    discord_set_on_command(client, "role_member_remove",
                           &on_role_member_remove);
    discord_set_on_command(client, "role_list", &on_role_list);
    discord_set_on_command(client, "member_get", &on_member_get);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
