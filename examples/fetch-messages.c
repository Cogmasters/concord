#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "log.h"

void
print_usage(void)
{
    printf("\n\nThis bot demonstrates how easy it is to fetch"
           " messages from a particular user (without even connecting"
           " to Discord Gateway).\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

u64snowflake
select_guild(struct discord *client)
{
    struct discord_guilds guilds = { 0 };
    struct discord_ret_guilds ret = { .sync = &guilds };
    CCORDcode code;

    code = discord_get_current_user_guilds(client, &ret);
    assert(CCORD_OK == code && guilds.size != 0 && "Couldn't fetch guilds");

    printf(
        "\n\nSelect the guild that the user you wish to fetch messages from "
        "is part of");

    int i = 0;
    while (i < guilds.size) {
        printf("\n%d. %s", i + 1, guilds.array[i].name);
        ++i;
    }

    while (1) {
        char strnum[10];

        puts("\n\nNUMBER >>");
        fgets(strnum, sizeof(strnum), stdin);

        int num = strtol(strnum, NULL, 10);
        if (num > 0 && num <= i) {
            u64snowflake guild_id = guilds.array[num - 1].id;

            discord_guilds_cleanup(&guilds);

            return guild_id;
        }

        printf("\nPlease, insert a value between 1 and %d", i);
    }
}

u64snowflake
select_member(struct discord *client, u64snowflake guild_id)
{
    // get guilds bot is a part of
    struct discord_guild_members members = { 0 };
    struct discord_ret_guild_members ret = { .sync = &members };
    struct discord_list_guild_members params = { .limit = 1000, .after = 0 };
    CCORDcode code;

    code = discord_list_guild_members(client, guild_id, &params, &ret);
    assert(CCORD_OK == code && members.size != 0
           && "Guild is empty or bot needs to activate its privileged "
              "intents.\n\t"
              "See this guide to activate it: "
              "https://discordpy.readthedocs.io/en/latest/"
              "intents.html#privileged-intents");

    printf("\n\nSelect the member that will have its messages fetched");
    int i = 0;
    while (i < members.size) {
        printf("\n%d. %s", i + 1, members.array[i].user->username);

        if (members.array[i].nick && *members.array[i].nick)
        { // prints nick if available
            printf(" (%s)", members.array[i].nick);
        }
        ++i;
    }

    do {
        char strnum[10]; // 10 digits should be more than enough..

        puts("\n\nNUMBER >>");
        fgets(strnum, sizeof(strnum), stdin);

        int num = strtol(strnum, NULL, 10);
        if (num > 0 && num <= i) {
            u64snowflake user_id = members.array[num - 1].user->id;

            discord_guild_members_cleanup(&members);

            return user_id;
        }

        printf("\nPlease, insert a value between 1 and %d", i);
    } while (1);
}

void
fetch_member_msgs(struct discord *client,
                  u64snowflake guild_id,
                  u64snowflake user_id)
{
    struct discord_channels channels = { 0 };
    CCORDcode code;

    struct discord_ret_channels ret = { .sync = &channels };
    code = discord_get_guild_channels(client, guild_id, &ret);
    assert(CCORD_OK == code && "Couldn't fetch channels from guild");

    struct discord_get_channel_messages params = { .limit = 100 };
    for (int i = 0; i < channels.size; ++i) {
        params.before = 0;

        int n_msg = 0;
        while (n_msg != params.limit) {
            struct discord_messages msgs = { 0 };
            struct discord_ret_messages ret = { .sync = &msgs };

            discord_get_channel_messages(client, channels.array[i].id, &params,
                                         &ret);
            if (!msgs.size) break;

            for (n_msg = 0; n_msg < msgs.size; ++n_msg) {
                if (user_id == msgs.array[n_msg].author->id
                    && *msgs.array[n_msg].content) {
                    printf("%s\n", msgs.array[n_msg].content);
                }
            }

            if (n_msg) params.before = msgs.array[n_msg - 1].id;

            discord_messages_cleanup(&msgs);
        }
    }

    discord_channels_cleanup(&channels);
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

    print_usage();
    fgetc(stdin); // wait for input

    u64snowflake guild_id = select_guild(client);
    u64snowflake user_id = select_member(client, guild_id);

    fetch_member_msgs(client, guild_id, user_id);

    discord_cleanup(client);
    ccord_global_cleanup();
}
