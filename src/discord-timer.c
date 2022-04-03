
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
    struct discord_timer timer;
    while ((timer.id = priority_queue_pop(q, NULL, &timer))) {
      timer.flags |= DISCORD_TIMER_CANCELED;
      if (timer.cb) timer.cb(client, &timer);
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
    struct discord_timer *timer)
{
    int64_t now = -1;
    if (timer->flags & DISCORD_TIMER_DELETE) {
        unsigned id;
        if (timer->id) {
            id = priority_queue_get(timers->q, timer->id, NULL, timer);
            if (id) return priority_queue_del(timers->q, id) ? id : 0;
        }
        return 0;
    }
    if (timer->delay >= 0)
        now = (int64_t)discord_timestamp_us(client) + 
              ((timer->flags & DISCORD_TIMER_MICROSECONDS)
              ? timer->delay : timer->delay * 1000);
    if (!timer->id) {
        return priority_queue_push(timers->q, &now, timer);
    } else {
        if (timers->currently_being_run
            && timers->currently_being_run->id == timer->id)
            timers->currently_being_run->flags |= DISCORD_TIMER_DONT_UPDATE;
        if (priority_queue_update(timers->q, timer->id, &now, timer))
            return timer->id;
        return 0;
    }
}

#define TIMER_TRY_DELETE                           \
  if (timer.flags & DISCORD_TIMER_DELETE) {        \
        priority_queue_pop(timers->q, NULL, NULL); \
        continue;                                  \
  }

void
discord_timers_run(struct discord *client, struct discord_timers *timers)
{
    int64_t now = (int64_t)discord_timestamp_us(client);
    struct discord_timer timer;
    timers->currently_being_run = &timer;
    for (int64_t trigger; 
        (timer.id = priority_queue_peek(timers->q, &trigger, &timer));)
    {
        if (trigger > now || trigger == -1) break;

        TIMER_TRY_DELETE

        if (timer.repeat > 0)
            timer.repeat--;
        if (timer.cb) timer.cb(client, &timer);
        if (timer.repeat == 0 && (timer.flags & DISCORD_TIMER_DELETE_AUTO))
            timer.flags |= DISCORD_TIMER_DELETE;
        TIMER_TRY_DELETE
        
        int64_t next = -1;
        if (timer.repeat != 0) {
            if (timer.interval > 0)
              next = now + ((timer.flags & DISCORD_TIMER_MICROSECONDS)
                           ? timer.interval : timer.interval * 1000);
        }
        if (priority_queue_peek(timers->q, NULL, NULL) != timer.id)
            continue;
        if (timer.flags & DISCORD_TIMER_DONT_UPDATE)
            continue;
        priority_queue_update(timers->q, timer.id, &next, &timer);
    }
    timers->currently_being_run = NULL;
}

unsigned
discord_timer_ctl(struct discord *client, struct discord_timer *timer)
{
    return _discord_timer_ctl(client, &client->timers.user, timer);
}

unsigned 
discord_internal_timer_ctl(struct discord *client,
                                    struct discord_timer *timer)
{
    return _discord_timer_ctl(client, &client->timers.internal, timer);
}

static unsigned
_discord_timer(struct discord *client, struct discord_timers *timers,
              discord_ev_timer cb, void *data, int64_t delay)
{
    struct discord_timer timer = {
      .cb = cb,
      .data = data,
      .delay = delay,
      .flags = DISCORD_TIMER_DELETE_AUTO,
    };
    return _discord_timer_ctl(client, timers, &timer);
}

unsigned
discord_timer(struct discord *client, discord_ev_timer cb,
              void *data, int64_t delay)
{
    return _discord_timer(client, &client->timers.user, cb, data, delay);
}


unsigned
discord_internal_timer(struct discord *client, discord_ev_timer cb,
                       void *data, int64_t delay)
{
    return _discord_timer(client, &client->timers.internal, cb, data, delay);
}
