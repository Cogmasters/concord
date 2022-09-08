#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "discord.h"
#include "log.h"

static void
print_timer_info(struct discord_timer *timer, const char *name)
{
    printf("Timer '%s' id:%u flags:%i "
           "delay:%" PRIi64 " interval:%" PRIi64 " repeat:%" PRIi64 "\n",
           name, timer->id, timer->flags, timer->delay, timer->interval,
           timer->repeat);
}

static void
on_timer_tick(struct discord *client, struct discord_timer *timer)
{
    print_timer_info(timer, "on_timer_tick");

    if (timer->repeat == 1) {
        puts("Canceling repeating timer.");
        timer->flags |= DISCORD_TIMER_CANCELED;
    }
}

static void
on_timer_status_changed(struct discord *client, struct discord_timer *timer)
{
    print_timer_info(timer, "on_timer_status_changed");
    if (timer->flags & DISCORD_TIMER_CANCELED) {
        puts("TIMER CANCELED");
    }
    if (timer->flags & DISCORD_TIMER_DELETE) {
        puts("TIMER DELETED - FREEING DATA");
    }
}

static void
use_same_function(struct discord *client, struct discord_timer *timer)
{
    print_timer_info(timer, "use_same_function");
    if (timer->flags & DISCORD_TIMER_TICK) {
        puts("TIMER TICK");
    }

    if (timer->flags & DISCORD_TIMER_CANCELED) {
        puts("TIMER CANCELED");
    }

    if (timer->flags & DISCORD_TIMER_DELETE) {
        puts("TIMER DELETED - FREEING DATA");
        free(timer->data);
    }
}

int
main(int argc, char *argv[])
{
    const char *config_file = argc > 1 ? argv[1] : "../config.json";
    ccord_global_init();
    struct discord *client = discord_config_init(config_file);

    for (int i = 0; i < 10; i++)
        // one shot auto deleting timer
        discord_timer(client, on_timer_tick, on_timer_status_changed, NULL,
                      i * 1000);

    // repeating auto deleting timer
    discord_timer_interval(client, on_timer_tick, on_timer_status_changed,
                           NULL, 0, 1000, 10);

    discord_timer(client, use_same_function, use_same_function, malloc(1024),
                  1000);
    unsigned id_to_cancel = discord_timer(
        client, use_same_function, use_same_function, malloc(1024), 1000);
    discord_timer_cancel(client, id_to_cancel);

    discord_run(client);

    // discord_cleanup will cancel all timers that are still active
    discord_cleanup(client);
    ccord_global_cleanup();
}
