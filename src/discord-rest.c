#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "carray.h"
#include "threadpool.h"

#include "discord.h"
#include "discord-internal.h"

static CCORDcode
_discord_rest_perform(struct discord_rest *rest)
{
    CCORDcode code;

    discord_requestor_info_read(&rest->requestor);
    code = discord_requestor_start_pending(&rest->requestor);
    io_poller_wakeup(CLIENT(rest, rest)->io_poller);

    return code;
}

static void
_discord_rest_manager(void *p_rest)
{
    struct discord *client = CLIENT(p_rest, rest);
    struct discord_rest *rest = p_rest;

    struct discord_timers *const timers[] = { &rest->timers };
    int64_t now, trigger;
    int poll_result;

    _discord_rest_perform(rest);

    now = (int64_t)discord_timestamp_us(client);

    trigger = discord_timers_get_next_trigger(timers, 1, now, 60000000);
    poll_result = io_poller_poll(rest->io_poller, (int)(trigger / 1000));

    now = (int64_t)discord_timestamp_us(client);
    if (0 == poll_result) {
        trigger = discord_timers_get_next_trigger(timers, 1, now, 1000);
        if (trigger > 0 && trigger < 1000) cog_sleep_us((long)trigger);
    }
    discord_timers_run(client, &rest->timers);
    io_poller_perform(rest->io_poller);

    threadpool_add(rest->tpool, _discord_rest_manager, rest, 0);
}

static int
_discord_on_rest_perform(struct io_poller *io, CURLM *mhandle, void *p_rest)
{
    (void)io;
    (void)mhandle;
    return _discord_rest_perform(p_rest);
}

void
discord_rest_init(struct discord_rest *rest,
                  struct logconf *conf,
                  const char token[])
{
    if (!token || !*token)
        logconf_branch(&rest->conf, conf, "DISCORD_WEBHOOK");
    else
        logconf_branch(&rest->conf, conf, "DISCORD_HTTP");

    rest->io_poller = io_poller_create();
    discord_timers_init(&rest->timers, rest->io_poller);

    discord_requestor_init(&rest->requestor, &rest->conf, token);
    io_poller_curlm_add(rest->io_poller, rest->requestor.mhandle,
                        &_discord_on_rest_perform, rest);

    rest->tpool = threadpool_create(1, 1024, 0);
    ASSERT_S(!threadpool_add(rest->tpool, &_discord_rest_manager, rest, 0),
             "Couldn't initialize REST managagement thread");
}

void
discord_rest_cleanup(struct discord_rest *rest)
{
    /* wake up every ms until thread shutdown */
    _discord_timer_ctl(CLIENT(rest, rest), &rest->timers,
                       &(struct discord_timer){
                           .interval = 1,
                           .repeat = -1,
                       });
    /* cleanup REST managing thread */
    threadpool_destroy(rest->tpool, threadpool_graceful);
    /* cleanup discovered buckets */
    discord_timers_cleanup(CLIENT(rest, rest), &rest->timers);
    /* cleanup requests */
    discord_requestor_cleanup(&rest->requestor);
    /* cleanup REST poller */
    io_poller_destroy(rest->io_poller);
}

/* template function for performing requests */
CCORDcode
discord_rest_run(struct discord_rest *rest,
                 struct discord_attributes *attr,
                 struct ccord_szbuf *body,
                 enum http_method method,
                 char endpoint_fmt[],
                 ...)
{
    char endpoint[DISCORD_ENDPT_LEN], key[DISCORD_ROUTE_LEN];
    va_list args;
    int len;

    /* have it point somewhere */
    if (!attr) {
        static struct discord_attributes blank = { 0 };
        attr = &blank;
    }
    if (!body) {
        static struct ccord_szbuf blank = { 0 };
        body = &blank;
    }
    else if (body->start && !body->size) {
        logconf_error(&rest->conf, "(Internal error) Request body couldn't "
                                   "be formed, please report it.");
        return CCORD_MALFORMED_PAYLOAD;
    }

    /* build the endpoint string */
    va_start(args, endpoint_fmt);
    len = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
    ASSERT_NOT_OOB(len, sizeof(endpoint));
    va_end(args);

    /* build the bucket's key */
    va_start(args, endpoint_fmt);
    discord_ratelimiter_build_key(method, key, endpoint_fmt, args);
    va_end(args);

    return discord_request_begin(&rest->requestor, attr, body, method,
                                 endpoint, key);
}
