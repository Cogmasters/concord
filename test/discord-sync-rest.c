#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

#include "discord.h"

int
main(int argc, char *argv[])
{
    const char *config_file;
    struct discord *client;
    CCORDcode code;

    const u64_snowflake_t FAUX_CHANNEL_ID = 123;
    struct discord_guild **guilds = NULL;
    struct discord_user bot;

    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    ccord_global_init();

    client = discord_config_init(config_file);
    assert(NULL != client);

    code = discord_get_current_user(client, &(struct discord_ret_user){
                                                .sync = &bot,
                                            });
    assert(CCORD_OK == code);
    printf("Greetings, %s#%s!\n", bot.username, bot.discriminator);

    code =
        discord_get_current_user_guilds(client, &(struct discord_ret_guilds){
                                                    .sync = &guilds,
                                                });
    assert(CCORD_OK == code);

    for (size_t i = 0; guilds[i]; ++i)
        fprintf(stderr, "Guild[%s] id:\n\t%" PRIu64 "\n", guilds[i]->name,
                guilds[i]->id);

    // Test discord_strerror()
    code = discord_delete_channel(client, FAUX_CHANNEL_ID,
                                  &(struct discord_ret_channel){
                                      .sync = DISCORD_SYNC_FLAG,
                                  });
    assert(CCORD_OK != code);
    fprintf(stderr, "%s\n", discord_strerror(code, client));

    code = discord_modify_channel(client, FAUX_CHANNEL_ID, NULL,
                                  &(struct discord_ret_channel){
                                      .sync = DISCORD_SYNC_FLAG,
                                  });
    assert(CCORD_OK != code);
    fprintf(stderr, "%s\n", discord_strerror(code, client));

    discord_guild_list_free(guilds);
    discord_user_cleanup(&bot);
    discord_cleanup(client);

    ccord_global_cleanup();
}
