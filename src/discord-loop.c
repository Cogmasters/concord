#include <stdlib.h>
#include <errno.h>

#include "discord.h"
#include "discord-internal.h"
#include "cog-utils.h"

static void
discord_wake_timer_cb(struct discord *client, struct discord_timer *timer)
{
    if (~timer->flags & DISCORD_TIMER_CANCELED && client->wakeup_timer.cb)
        client->wakeup_timer.cb(client);
}

void
discord_set_next_wakeup(struct discord *client, int64_t delay)
{
    unsigned id =
        discord_internal_timer_ctl(client, &(struct discord_timer){
                                               .id = client->wakeup_timer.id,
                                               .cb = discord_wake_timer_cb,
                                               .delay = delay,
                                           });
    client->wakeup_timer.id = id;
}

void
discord_set_on_wakeup(struct discord *client, discord_ev_idle callback)
{
    client->wakeup_timer.cb = callback;
    if (client->wakeup_timer.id) {
        discord_internal_timer_ctl(client, &(struct discord_timer){
                                               .id = client->wakeup_timer.id,
                                               .cb = discord_wake_timer_cb,
                                               .delay = -1,
                                           });
    }
}

void
discord_set_on_idle(struct discord *client, discord_ev_idle callback)
{
    client->on_idle = callback;
}

void
discord_set_on_cycle(struct discord *client, discord_ev_idle callback)
{
    client->on_cycle = callback;
}

static inline int64_t
discord_timer_get_next_trigger(struct discord_timers *const timers[],
                               size_t n,
                               int64_t now,
                               int64_t max_time)
{
    if (max_time == 0) return 0;

    for (unsigned i = 0; i < n; i++) {
        int64_t trigger;
        if (priority_queue_peek(timers[i]->q, &trigger, NULL)) {
            if (trigger < 0) continue;

            if (trigger <= now)
                max_time = 0;
            else if (max_time > trigger - now)
                max_time = trigger - now;
        }
    }
    return max_time;
}

#define BREAK_ON_FAIL(function)                                               \
    do {                                                                      \
        if (CCORD_OK != (code = function)) break;                             \
    } while (0)

CCORDcode
discord_run(struct discord *client)
{
    int64_t next_run, now;
    CCORDcode code;
    struct discord_timers *const timers[] = { &client->timers.internal,
                                              &client->timers.user };

    while (1) {
        BREAK_ON_FAIL(discord_gateway_start(&client->gw));

        next_run = (int64_t)discord_timestamp_us(client);
        while (1) {
            int64_t poll_time = 0, poll_result;

            now = (int64_t)discord_timestamp_us(client);

            if (!client->on_idle) {
                poll_time = discord_timer_get_next_trigger(
                    timers, sizeof timers / sizeof *timers, now,
                    now < next_run ? ((next_run - now)) : 0);
            }

            poll_result =
                io_poller_poll(client->io_poller, (int)(poll_time / 1000));

            now = (int64_t)discord_timestamp_us(client);

            if (0 == poll_result) {
                if (ccord_has_sigint != 0) discord_shutdown(client);
                if (client->on_idle) {
                    client->on_idle(client);
                }
                else {
                    poll_time = discord_timer_get_next_trigger(
                        timers, sizeof timers / sizeof *timers, now, 999);
                    if (poll_time) cog_sleep_us(poll_time);
                }
            }

            if (client->on_cycle) client->on_cycle(client);

            for (unsigned i = 0; i < sizeof timers / sizeof *timers; i++)
                discord_timers_run(client, timers[i]);

            if (poll_result >= 0 && !client->on_idle)
                poll_result = io_poller_poll(client->io_poller, 0);

            if (-1 == poll_result) {
                /* TODO: handle poll error here */
            }

            BREAK_ON_FAIL(io_poller_perform(client->io_poller));

            if (next_run <= now) {
                BREAK_ON_FAIL(discord_gateway_perform(&client->gw));
                BREAK_ON_FAIL(discord_adapter_perform(&client->adapter));

                /* enforce a min 1 sec delay between runs */
                next_run = now + 1000000;
            }
        }

        /* stop all pending requests in case of connection shutdown */
        if (true == discord_gateway_end(&client->gw)) {
            discord_adapter_stop_all(&client->adapter);
            break;
        }
    }

    return code;
}

#undef BREAK_ON_FAIL
