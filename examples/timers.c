#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <signal.h>

#include "discord.h"

static int interrupted = 0;

static void
on_sigint(int sig) {
    interrupted = 1;
}

static void
one_shot_timer_cb(struct discord *client, struct discord_ev_timer *ev) {
  printf("one_shot_timer_cb %u triggered with flags %i\n",
         ev->id, ev->timer.flags);

  //DO NOT IGNORE CANCELATION
  if (ev->timer.flags & DISCORD_TIMER_CANCELED) {
      puts("Timer has been canceled");
      return;
  }
  if (interrupted) {
      puts("Shutdown Canceled");
      return;
  }
  puts(ev->timer.data);
  discord_shutdown(client);
}

static void
repeating_timer_cb(struct discord *client, struct discord_ev_timer *ev) {
  printf("repeating_timer_cb %u triggered with flags %i\n",
         ev->id, ev->timer.flags);
  printf("%i %i\n", ev->timer.interval, ev->timer.repeat);
  if (ev->timer.repeat == 0)
      puts("Shutting down soon, press ctrl + c to cancel");
}

int
main(int argc, char *argv[])
{
    const char *config_file = argc > 1 ? argv[1] : "../config.json";

    signal(SIGINT, on_sigint);
    ccord_global_init();

    struct discord *client = discord_config_init(config_file);

    //create one shot auto deleting timer
    unsigned one_shot_timer_id =
        discord_timer(client, one_shot_timer_cb, "Shutting Down", 5000);
    
    discord_timer_ctl(client, 0, &(struct discord_timer) {
        .cb = repeating_timer_cb,
        .data = &one_shot_timer_id,
        .delay = 0, /* start right away */
        .interval = 100,
        .repeat = 10, /* -1 for infinity, 0 for never */
        .flags = DISCORD_TIMER_DELETE_AUTO,
    });

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}