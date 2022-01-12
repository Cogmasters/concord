#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

#include "discord.h"

int
main(int argc, char *argv[])
{
    const char *config_file;
    CCORDcode code;

    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    ccord_global_init();

    struct discord *client = discord_config_init(config_file);
    assert(NULL != client);

    struct discord_user bot;
    discord_user_init(&bot);

    code = discord_get_current_user(client, &(struct discord_attr){
                                                .sync = true,
                                                .sync_ret = &bot,
                                            });
    assert(CCORD_OK == code);

    printf("Greetings, %s#%s!\n", bot.username, bot.discriminator);

    struct discord_guild **guilds = NULL;
    code = discord_get_current_user_guilds(client, &(struct discord_attr){
                                                       .sync = true,
                                                       .sync_ret = &guilds,
                                                   });
    assert(CCORD_OK == code);

    for (size_t i = 0; guilds[i]; ++i)
        fprintf(stderr, "Guild[%s] id:\n\t%" PRIu64 "\n", guilds[i]->name,
                guilds[i]->id);

    // Test discord_strerror()
    code = discord_delete_channel(client, 123,
                                  &(struct discord_attr){
                                      .sync = true,
                                  });
    assert(CCORD_OK != code);
    fprintf(stderr, "%s\n", discord_strerror(code, client));

    code = discord_modify_channel(client, 123, NULL,
                                  &(struct discord_attr){
                                      .sync = true,
                                  });
    assert(CCORD_OK != code);
    fprintf(stderr, "%s\n", discord_strerror(code, client));

    discord_guild_list_free(guilds);
    discord_user_cleanup(&bot);
    discord_cleanup(client);

    ccord_global_cleanup();
}
