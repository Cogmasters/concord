#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "discord.h"
#include "logmod.h"

uint64_t g_time_ms;

bool g_triggered[2] = { false, false };

void
on_cycle(struct discord *client)
{
    static int64_t cycle = 0;
    if ((discord_timestamp(client) - g_time_ms) > 5000) {
        printf(LMS(BOLD, FOREGROUND, MAGENTA, "cycle %" PRIi64 "\n"), cycle);
        if (g_triggered[0]) {
            g_time_ms = discord_timestamp(client);
            g_triggered[0] = false;
        }
        else {
            g_triggered[1] = true;
        }
    }
    ++cycle;
}

void
on_wakeup(struct discord *client, struct discord_timer *ev)
{
    puts(LMS(BOLD, FOREGROUND, RED, "wakeup"));
}

void
on_idle(struct discord *client)
{
    static int64_t idle = 0;
    if ((discord_timestamp(client) - g_time_ms) > 5000) {
        printf(LMS(BOLD, FOREGROUND, BLACK, "idle %" PRIi64 "\n"), idle);
        if (g_triggered[1]) {
            g_time_ms = discord_timestamp(client);
            g_triggered[1] = false;
        }
        else {
            g_triggered[0] = true;
        }
    }
    ++idle;
}

int
main(int argc, char *argv[])
{
    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    struct discord *client = discord_from_json(config_file);
    g_time_ms = discord_timestamp(client);
    discord_timer_interval(client, on_wakeup, NULL, NULL, 0, 3000, -1);
    discord_set_on_cycle(client, on_cycle);
    discord_set_on_idle(client, on_idle);

    discord_run(client);
}
