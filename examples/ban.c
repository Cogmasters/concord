#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* SCNu64 */
#include <assert.h>

#include "discord.h"
#include "log.h"

void
print_usage(void)
{
    printf("\n\nThis bot demonstrates how easy it is to ban/unban members\n"
           "1. Type '!ban <user_id>' to ban user\n"
           "2. Type '!unban <user_id>' to unban user\n"
           "3. Type '!prune_count <days>' to check how many members would be "
           "removed by a prune operation (1-30 days)\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Ban-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
log_on_guild_ban_add(struct discord *client,
                     const struct discord_guild_ban_add *event)
{
    log_info("User `%s#%s` has been banned.", event->user->username,
             event->user->discriminator);
}

void
log_on_guild_ban_remove(struct discord *client,
                        const struct discord_guild_ban_remove *event)
{
    log_info("User `%s#%s` has been unbanned.", event->user->username,
             event->user->discriminator);
}

void
on_ban(struct discord *client, const struct discord_message *event)
{
    u64snowflake target_id = 0ULL;
    sscanf(event->content, "%" SCNu64, &target_id);

    struct discord_create_guild_ban params = {
        .delete_message_days = 1,
        .reason = "Someone really dislikes you!",
    };
    discord_create_guild_ban(client, event->guild_id, target_id, &params,
                             NULL);
}

void
on_unban(struct discord *client, const struct discord_message *event)
{
    u64snowflake target_id = 0ULL;
    sscanf(event->content, "%" SCNu64, &target_id);

    struct discord_remove_guild_ban params = {
        .reason = "Someone really likes you!"
    };
    discord_remove_guild_ban(client, event->guild_id, target_id, &params,
                             NULL);
}

void
done_get_prune_count(struct discord *client,
                     struct discord_response *resp,
                     const struct discord_prune_count *ret)
{
    const struct discord_message *event = resp->keep;
    const long days = (long)resp->data;
    char text[128];

    snprintf(text, sizeof(text),
             "%d members will be removed by that prune operation! (%ld days)",
             ret->pruned, days);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_prune_count(struct discord *client, const struct discord_message *event)
{
    char *endp = NULL;
    const long days = strtol(event->content, &endp, 10);

    if (endp != event->content) {
        struct discord_get_guild_prune_count params = { .days = days };
        discord_get_guild_prune_count(client, event->guild_id, &params,
                                      &(struct discord_ret_prune_count){
                                          .done = done_get_prune_count,
                                          .keep = event,
                                          .data = (void *)days,
                                      });
    }
    else {
        struct discord_create_message params = {
            .content = "Bad command formatting, expect: `!prune_count <days>`"
        };
        discord_create_message(client, event->channel_id, &params, NULL);
    }
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
    discord_set_on_guild_ban_add(client, &log_on_guild_ban_add);
    discord_set_on_guild_ban_remove(client, &log_on_guild_ban_remove);

    discord_set_on_command(client, "!ban", &on_ban);
    discord_set_on_command(client, "!unban", &on_unban);
    discord_set_on_command(client, "!prune_count", &on_prune_count);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
