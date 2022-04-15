
#include "discord.h"
#include "discord-internal.h"

#define DISCORD_TIMER_ALLOWED_FLAGS \
    ( DISCORD_TIMER_MILLISECONDS    \
    | DISCORD_TIMER_MICROSECONDS    \
    | DISCORD_TIMER_DELETE          \
    | DISCORD_TIMER_DELETE_AUTO     \
    | DISCORD_TIMER_INTERVAL_FIXED  ) 

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
    struct discord_timer *timer_ret)
{
    struct discord_timer timer;
    memcpy(&timer, timer_ret, sizeof timer);

    int64_t key = -1;
    if (timer.id) {
        if (!priority_queue_get(timers->q, timer.id, &key, NULL))
            return 0;

        if (timer.flags & DISCORD_TIMER_GET) {
            priority_queue_get(timers->q, timer.id, NULL, timer_ret);
            if (timer.flags == DISCORD_TIMER_GET)
                return timer.id;
        }
    }
    
    int64_t now = -1;
    if (timer.delay >= 0)
        now = (int64_t)discord_timestamp_us(client) + 
              ((timer.flags & DISCORD_TIMER_MICROSECONDS)
              ? timer.delay : timer.delay * 1000);
    if (timer.flags & (DISCORD_TIMER_DELETE | DISCORD_TIMER_CANCELED))
        now = 0;
    
    timer.flags &= DISCORD_TIMER_ALLOWED_FLAGS | DISCORD_TIMER_CANCELED;

    if (!timer.id) {
        return priority_queue_push(timers->q, &now, &timer);
    } else {
        if (timers->active.timer && timers->active.timer->id == timer.id)
            timers->active.skip_update_phase = true;
        if (priority_queue_update(timers->q, timer.id, &now, &timer))
            return timer.id;
        return 0;
    }
}

#define TIMER_TRY_DELETE                           \
    if (timer.flags & DISCORD_TIMER_DELETE) {      \
        priority_queue_del(timers->q, timer.id);   \
        continue;                                  \
    }

void
discord_timers_run(struct discord *client, struct discord_timers *timers)
{
    int64_t now = (int64_t)discord_timestamp_us(client);
    struct discord_timer timer;
    timers->active.timer = &timer;
    for (int64_t trigger; 
        (timer.id = priority_queue_peek(timers->q, &trigger, &timer));)
    {
        if (trigger > now || trigger == -1) break;

        if (~timer.flags & DISCORD_TIMER_CANCELED)
            TIMER_TRY_DELETE

        if (timer.repeat > 0 && ~timer.flags & DISCORD_TIMER_CANCELED)
            timer.repeat--;
        timers->active.skip_update_phase = false;
        if (timer.cb) timer.cb(client, &timer);
        if (timers->active.skip_update_phase)
            continue;
        if ((timer.repeat == 0 || timer.flags & DISCORD_TIMER_CANCELED)
            && (timer.flags & DISCORD_TIMER_DELETE_AUTO))
            timer.flags |= DISCORD_TIMER_DELETE;
        TIMER_TRY_DELETE
        
        
        
        int64_t next = -1;
        if (timer.repeat != 0 && timer.delay != -1
            && ~timer.flags & DISCORD_TIMER_CANCELED) {
            if (timer.interval >= 0)
              next = ((timer.flags & DISCORD_TIMER_INTERVAL_FIXED)
                     ? trigger : now) +
                     ((timer.flags & DISCORD_TIMER_MICROSECONDS)
                     ? timer.interval : timer.interval * 1000);
        }
        timer.flags &= DISCORD_TIMER_ALLOWED_FLAGS;
        priority_queue_update(timers->q, timer.id, &next, &timer);
    }
    timers->active.timer = NULL;
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
discord_timer_interval(struct discord *client, discord_ev_timer cb, void *data,
                    int64_t delay, int64_t interval, int64_t repeat)
{
    struct discord_timer timer = {
      .cb = cb,
      .data = data,
      .delay = delay,
      .interval = interval,
      .repeat = repeat,
      .flags = DISCORD_TIMER_DELETE_AUTO,
    };
    return discord_timer_ctl(client, &timer);
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

bool
discord_timer_get(struct discord *client, unsigned id,
                  struct discord_timer *timer)
{
    if (!id) return 0;
    return priority_queue_get(client->timers.user.q, id, NULL, timer);
}

static void
discord_timer_disable_update_if_active(struct discord_timers *timers,
                                       unsigned id)
{
    if (!timers->active.timer)
        return;
    if (timers->active.timer->id == id)
        timers->active.skip_update_phase = true;
}

bool
discord_timer_start(struct discord *client, unsigned id)
{
    struct discord_timer timer;
    discord_timer_disable_update_if_active(&client->timers.user, id);
    if (discord_timer_get(client, id, &timer)) {
        if (timer.delay < 0)
            timer.delay = 0;
        return discord_timer_ctl(client, &timer);
    }
    return false;
}

bool
discord_timer_stop(struct discord *client, unsigned id)
{
    struct discord_timer timer;
    discord_timer_disable_update_if_active(&client->timers.user, id);
    if (discord_timer_get(client, id, &timer)) {
        int64_t disabled = -1;
        return priority_queue_update(client->timers.user.q,
                                     id, &disabled, &timer);
    }
    return false;
}

static bool
discord_timer_add_flags(struct discord *client, unsigned id,
                           enum discord_timer_flags flags)
{
    struct discord_timer timer;
    discord_timer_disable_update_if_active(&client->timers.user, id);
    if (discord_timer_get(client, id, &timer)) {
        timer.flags |= flags;
        int64_t run_now = 0;
        return priority_queue_update(client->timers.user.q,
                                     id, &run_now, &timer);
    }
    return false;
}

bool
discord_timer_cancel(struct discord *client, unsigned id)
{
    return discord_timer_add_flags(client, id, DISCORD_TIMER_CANCELED);
}

bool
discord_timer_delete(struct discord *client, unsigned id)
{
    return discord_timer_add_flags(client, id, DISCORD_TIMER_DELETE);
}

bool
discord_timer_cancel_and_delete(struct discord *client, unsigned id)
{
    return discord_timer_add_flags(client, id, DISCORD_TIMER_DELETE 
                                             | DISCORD_TIMER_CANCELED);
}
