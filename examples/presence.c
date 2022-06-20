#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "log.h"

void
print_usage(void)
{
    printf(
        "\n\nThis bot demonstrates how easy it is to set the bot presence.\n"
        "1. Start bot\n"
        "2. Check bot status\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Presence-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);

    struct discord_activity activities[] = {
        {
            .name = "with Concord",
            .type = DISCORD_ACTIVITY_GAME,
            .details = "Fixing some bugs",
        },
    };

    struct discord_presence_update status = {
        .activities =
            &(struct discord_activities){
                .size = sizeof(activities) / sizeof *activities,
                .array = activities,
            },
        .status = "idle",
        .afk = false,
        .since = discord_timestamp(client),
    };

    discord_update_presence(client, &status);
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

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
