#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "debug.h"

void
print_usage(void)
{
    printf("\n\nThis bot demonstrates how easy it is to delete"
           " messages.\n"
           "1. Type !spam to spam 10 random messages in chat\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

char *SPAM[] = {
    "Yes I love to spam", // 1
    "Do you?", // 2
    "ROFL", // 3
    "What are you going to do about it?", // 4
    "Are you going to !clear me?", // 5
    "Good luck with that.", // 6
    "Many have tried but..", // 7
    "They all fail.", // 8
    "What makes you think", // 9
    "It should be any different with you?" // 10
};

void
on_spam(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    for (size_t i = 0; i < 10; ++i) {
        struct discord_message ret_msg;
        CCORDcode code;

        // this will block the thread
        struct discord_ret_message ret = { .sync = &ret_msg };
        struct discord_create_message params = { .content = SPAM[i] };
        code = discord_create_message(client, msg->channel_id, &params, &ret);

        if (CCORD_OK == code) discord_message_cleanup(&ret_msg);
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

    discord_set_on_command(client, "!spam", &on_spam);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
