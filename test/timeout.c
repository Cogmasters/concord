#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "discord.h"

void
on_cycle(struct discord *client)
{
    static int64_t cycle = 0;
    printf("cycle %" PRIi64 "\n", ++cycle);
}

void
on_wakeup(struct discord *client)
{
    puts("wakeup");
    discord_set_next_wakeup(client, 3000);
}

void
on_idle(struct discord *client)
{
    static int64_t idle = 0;
    printf("idle %" PRIi64 "\n", ++idle);
}

int
main(int argc, char *argv[])
{
    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    struct discord *client = discord_config_init(config_file);
    discord_set_on_wakeup(client, on_wakeup);
    discord_set_next_wakeup(client, 3000);
    discord_set_on_cycle(client, on_cycle);
#if 0
    discord_set_on_idle(client, on_idle);
#endif
    discord_run(client);
}
