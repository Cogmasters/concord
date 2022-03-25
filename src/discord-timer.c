
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
    discord_timers_cancel_all(client, client->timers.user.q);
    priority_queue_destroy(client->timers.user.q);

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
    if (timer->delay >= 0)
        now = (int64_t)discord_timestamp_us(client) + 
              ((timer->flags & DISCORD_TIMER_MICROSECONDS)
              ? timer->delay : timer->delay * 1000);
    if (!timer->id) {
        return priority_queue_push(timers->q, &now, timer);
    } else {
        if (priority_queue_update(timers->q, timer->id, &now, &timer))
          return timer->id;
        return 0;
    }
}
#define TIMER_TRY_DELETE                                          \
  if (timer.flags & DISCORD_TIMER_DELETE && timer.repeat == 0) {  \
    priority_queue_pop(timers->q, NULL, NULL);                    \
    continue;                                                     \
  }
void
discord_timers_run(struct discord *client, struct discord_timers *timers)
{
    int64_t now = (int64_t)discord_timestamp_us(client);
    struct discord_timer timer;
    for (int64_t trigger; 
        (timer.id = priority_queue_peek(timers->q, &trigger, &timer));)
    {
        if (trigger > now || trigger == -1) return;

        TIMER_TRY_DELETE

        if (timer.flags & DISCORD_TIMER_DELETE_AUTO) {
          timer.flags |= DISCORD_TIMER_DELETE;
          priority_queue_update(timers->q, timer.id, &now, &timer);
        }

        if (timer.cb) timer.cb(client, &timer);
        TIMER_TRY_DELETE
        
        int64_t next = -1;
        if (timer.repeat != 0) {
            if (timer.repeat > 0)
              timer.repeat--;
            if (timer.interval > 0)
              next = now + ((timer.flags & DISCORD_TIMER_MICROSECONDS)
                           ? timer.interval : timer.interval * 1000);
        }
        if (priority_queue_peek(timers->q, NULL, NULL) != timer.id)
            continue;
        
        priority_queue_update(timers->q, timer.id, &next, &timer);
    }
}
unsigned
discord_timer_ctl(struct discord *client, struct discord_timer *timer)
{
    return _discord_timer_ctl(client, &client->timers.user, timer);
}

unsigned discord_timer(struct discord *client, discord_ev_timer cb,
                       void *data, int64_t delay)
{
    struct discord_timer timer = {
      .cb = cb,
      .data = data,
      .delay = delay,
      .flags = DISCORD_TIMER_DELETE_AUTO,
    };
    return discord_timer_ctl(client, &timer);
}
