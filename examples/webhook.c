#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "discord.h"
#include "log.h"

static void
print_usage(char *prog)
{
    fprintf(stderr, "Usage: %s -i webhook-id -t webhook-token\n", prog);
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
    u64snowflake webhook_id = 0;
    char *webhook_token = NULL;
    int opt;

    while (-1 != (opt = getopt(argc, argv, "i:t:"))) {
        switch (opt) {
        case 't':
            webhook_token = strdup(optarg);
            break;
        case 'i':
            webhook_id = strtoull(optarg, NULL, 10);
            break;
        default:
            print_usage(argv[0]);
            break;
        }
    }
    if (!webhook_token || !webhook_id) print_usage(argv[0]);

    printf("\n\nThis bot demonstrates how to use webhook endpoints which "
           "require no authentication token\n"
           "\nTYPE ANY KEY TO START BOT\n");
    fgetc(stdin); // wait for input

    ccord_global_init();
    struct discord *client = discord_init(NULL);
    assert(NULL != client && "Couldn't initialize client");

    /* Get Webhook */
    {
        struct discord_ret_webhook ret = { .sync = DISCORD_SYNC_FLAG };
        discord_get_webhook_with_token(client, webhook_id, webhook_token,
                                       &ret);
    }

    /* Execute Webhook */
    {
        struct discord_ret ret = { .sync = true };
        struct discord_execute_webhook params = { .content = "Hello World!" };
        discord_execute_webhook(client, webhook_id, webhook_token, &params,
                                &ret);
    }

    free(webhook_token);
    discord_cleanup(client);
    ccord_global_cleanup();

    return EXIT_SUCCESS;
}
