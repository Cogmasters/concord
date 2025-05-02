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

CCORDcode
discord_rest_init(struct discord_rest *rest, const char token[])
{
    struct discord *client = CLIENT(rest, rest);
    CCORDcode code;

    if (!(rest->logger = logmod_get_logger(
              &client->logmod, NOT_EMPTY_STR(token) ? "REST" : "WEBHOOK")))
    {
        logmod_log(ERROR, NULL, "Couldn't create logger for REST");
        return CCORD_INTERNAL_ERROR;
    }
    if (!(rest->io_poller = io_poller_create())) {
        logmod_log(ERROR, rest->logger,
                   "Couldn't initialize IO poller for REST");
        return CCORD_INTERNAL_ERROR;
    }
    if ((code = discord_timers_init(&rest->timers, rest->io_poller))
        != CCORD_OK)
    {
        logmod_log(ERROR, rest->logger, "Couldn't initialize timers for REST");
        return code;
    }
    if ((code = discord_requestor_init(&rest->requestor, token)) != CCORD_OK) {
        logmod_log(ERROR, rest->logger,
                   "Couldn't initialize requestor for REST");
        return code;
    }
    if (!io_poller_curlm_add(rest->io_poller, rest->requestor.mhandle,
                             &_discord_on_rest_perform, rest))
    {
        logmod_log(ERROR, rest->logger,
                   "Couldn't add requestor's multi handle to IO poller");
        return CCORD_INTERNAL_ERROR;
    }
    if (!(rest->tpool = threadpool_create(1, 1024, 0))) {
        logmod_log(ERROR, rest->logger,
                   "Couldn't initialize REST management threadpool");
        return CCORD_INTERNAL_ERROR;
    }
    if (threadpool_add(rest->tpool, &_discord_rest_manager, rest, 0)) {
        logmod_log(ERROR, rest->logger,
                   "Couldn't initialize REST managagement thread");
        return CCORD_INTERNAL_ERROR;
    }
    return CCORD_OK;
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
    if (rest->tpool) {
        threadpool_destroy(rest->tpool, threadpool_graceful);
    }
    /* cleanup discovered buckets */
    discord_timers_cleanup(CLIENT(rest, rest), &rest->timers);
    /* cleanup requests */
    discord_requestor_cleanup(&rest->requestor);
    /* cleanup REST poller */
    if (rest->io_poller) {
        io_poller_destroy(rest->io_poller);
    }
    memset(rest, 0, sizeof *rest);
}

/* template function for performing requests */
CCORDcode
discord_rest_run(struct discord_rest *rest,
                 const struct discord_attributes *attr,
                 const struct ccord_szbuf *body,
                 const enum http_method method,
                 const char endpoint_fmt[],
                 ...)
{
    char endpoint[DISCORD_ENDPT_LEN], key[DISCORD_ROUTE_LEN];
    va_list args;

    /* have it point somewhere */
    if (!attr) {
        static struct discord_attributes blank = { 0 };
        attr = &blank;
    }
    if (!body) {
        static struct ccord_szbuf blank = { NULL, 0, true };
        body = &blank;
    }
    else if (body->start && !body->size) {
        logmod_log(
            ERROR, rest->logger,
            "(Internal error) Request body is empty, please report it.");
        return CCORD_MALFORMED_PAYLOAD;
    }

    /* build the endpoint string */
    va_start(args, endpoint_fmt);
    if ((vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args))
        >= (int)sizeof(endpoint))
    {
        logmod_log(ERROR, rest->logger,
                   "Internal error: Endpoint string too long: %s",
                   endpoint_fmt);
        return va_end(args), CCORD_ERRNO;
    }
    va_end(args);

    /* build the bucket's key */
    va_start(args, endpoint_fmt);
    discord_ratelimiter_build_key(method, key, endpoint_fmt, args);
    va_end(args);

    return discord_request_begin(&rest->requestor, attr, body, method,
                                 endpoint, key);
}
