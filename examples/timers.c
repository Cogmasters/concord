#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "discord.h"

static void
print_timer_info(struct discord_timer *timer)
{
    printf("Timer id:%u flags:%i "
           "delay:%" PRIi64 " interval:%" PRIi64 " repeat:%" PRIi64 "\n",
           timer->id, timer->flags, timer->delay, timer->interval,
           timer->repeat);
}

static void
one_shot_timer_cb(struct discord *client, struct discord_timer *timer)
{
    print_timer_info(timer);
    if (~timer->flags & DISCORD_TIMER_CANCELED) {
        // if timer is not canceled
        puts(timer->data);

        // timers can be updated in the callback (see below)
        if (0) {
            timer->interval += 100;
            timer->repeat = 1;
            return; // skip free(timer->data);
        }
    }
    else {
        puts("ONE SHOT TIMER CANCELED");
    }
    free(timer->data);
}

static void
repeating_timer_cb(struct discord *client, struct discord_timer *timer)
{
    print_timer_info(timer);
    if (timer->flags & DISCORD_TIMER_CANCELED) {
        printf("TIMER WITH ID %u CANCELED\n", timer->id);
        return;
    }
    printf("SHUTTING DOWN IN %" PRIi64 " SECONDS\n", timer->repeat);
    if (!timer->repeat) {
        discord_shutdown(client);
    }
}

int
main(int argc, char *argv[])
{
    const char *config_file = argc > 1 ? argv[1] : "../config.json";
    ccord_global_init();
    struct discord *client = discord_config_init(config_file);

    discord_timer(client, one_shot_timer_cb, strdup("Hello World"), 1000);
    discord_timer(client, one_shot_timer_cb, strdup("Hello World!!!!!!"),
                  5000);

    // start a one shot timer that will never get a chance to run
    discord_timer(client, one_shot_timer_cb, strdup("Hello World"), 15000);

    discord_timer_interval(client, repeating_timer_cb, NULL, 0, 1000, 10);

    // start 3 timers that will never get a chance to run
    for (int i = 0; i < 3; i++)
        discord_timer(client, repeating_timer_cb, NULL, 20 * 1000);

    discord_run(client);

    // discord_cleanup will cancel all timers that are still active
    discord_cleanup(client);
    ccord_global_cleanup();
}
