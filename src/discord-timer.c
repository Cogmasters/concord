
#include "discord.h"
#include "discord-internal.h"

static int
cmp_timers(const void *a, const void *b)
{
    const int64_t l = *(int64_t *)a;
    const int64_t r = *(int64_t *)b;
    if (l == r || (l < 0 && r < 0))
        return 0;
    if (l < 0) return 1;
    if (r < 0) return -1;
    return l > r ? 1 : -1;
}

void
discord_timers_init(struct discord *client) 
{
    client->timers.internal.q =
        priority_queue_create(sizeof(int64_t), sizeof(struct discord_timer),
                              cmp_timers, 0);
    client->timers.user.q =
        priority_queue_create(sizeof(int64_t), sizeof(struct discord_timer),
                              cmp_timers, 0);
}

static void
discord_timers_cancel_all(struct discord *client, priority_queue *q)
{
    struct discord_ev_timer ev;
    while ((ev.id = priority_queue_pop(q, NULL, &ev.timer))) {
      ev.timer.flags |= DISCORD_TIMER_CANCELED;
      if (ev.timer.cb) ev.timer.cb(client, &ev);
    }
}

void
discord_timers_cleanup(struct discord *client)
{
    priority_queue_set_max_capacity(client->timers.user.q, 0);
    discord_timers_cancel_all(client, client->timers.user.q);
    priority_queue_destroy(client->timers.user.q);

    priority_queue_set_max_capacity(client->timers.internal.q, 0);
    discord_timers_cancel_all(client, client->timers.internal.q);
    priority_queue_destroy(client->timers.internal.q);
}

unsigned
_discord_timer_ctl(
    struct discord *client,
    struct discord_timers *timers,
    discord_timer_id id,
    struct discord_timer *timer)
{
    int64_t now = -1;

    if (timer->flags & (DISCORD_TIMER_DELETE | DISCORD_TIMER_CANCELED)) {
        if (id) {
            struct discord_timer backup, *t = timer ? timer : &backup;
            if ((id = priority_queue_get(timers->q, id, NULL, t))) {
                int64_t run_now = 0;
                t->flags |= timer->flags 
                            & (DISCORD_TIMER_DELETE | DISCORD_TIMER_CANCELED);
                priority_queue_update(timers->q, id, &run_now, t);
                return id;
            }
        }
        return 0;
    }
    if (timer->delay >= 0)
        now = (int64_t)discord_timestamp_us(client) + 
              ((timer->flags & DISCORD_TIMER_MICROSECONDS)
              ? timer->delay : timer->delay * 1000);
    if (!id) {
        return priority_queue_push(timers->q, &now, timer);
    } else {
        if (priority_queue_update(timers->q, id, &now, timer))
            return id;
        return 0;
    }
}

#define TIMER_TRY_DELETE                           \
  if (ev.timer.flags & DISCORD_TIMER_DELETE) {     \
        priority_queue_del(timers->q, ev.id);         \
        continue;                                  \
  }

void
discord_timers_run(struct discord *client, struct discord_timers *timers)
{
    int64_t now = (int64_t)discord_timestamp_us(client);
    struct discord_ev_timer ev;
    for (int64_t trigger;
         (ev.id = priority_queue_peek(timers->q, &trigger, &ev.timer));)
    {
        if (trigger > now || trigger == -1) return;

        TIMER_TRY_DELETE

        if (ev.timer.repeat > 0)
            ev.timer.repeat--;
        if (ev.timer.cb) ev.timer.cb(client, &ev);
        if ((ev.timer.repeat == 0 && (ev.timer.flags & DISCORD_TIMER_DELETE_AUTO)))
            ev.timer.flags |= DISCORD_TIMER_DELETE;
        TIMER_TRY_DELETE
        
        int64_t next = -1;
        if (ev.timer.repeat != 0) {
            if (ev.timer.interval > 0)
              next = now + ((ev.timer.flags & DISCORD_TIMER_MICROSECONDS)
                           ? ev.timer.interval : ev.timer.interval * 1000);
        }
        priority_queue_update(timers->q, ev.id, &next, &ev.timer);
    }
}

discord_timer_id
discord_timer_ctl(struct discord *client,
                  discord_timer_id timer_id,
                  struct discord_timer *timer)
{
    return _discord_timer_ctl(client, &client->timers.user, timer_id, timer);
}

discord_timer_id
discord_timer(struct discord *client, discord_ev_timer cb,
              void *data, int delay)
{
    struct discord_timer timer = {
      .cb = cb,
      .data = data,
      .delay = delay,
      .flags = DISCORD_TIMER_DELETE_AUTO,
    };
    return discord_timer_ctl(client, 0, &timer);
}
