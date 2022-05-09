#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "osname.h"

/* return enumerator as string in case of a match */
#define CASE_RETURN_STR(code)                                                 \
    case code:                                                                \
        return #code

/**
 * @brief Context in case event is scheduled to be triggered
 *        from Concord's worker threads
 */
struct _discord_gateway_context {
    /** the discord gateway client */
    struct discord_gateway *gw;
    /** the event unique id value */
    enum discord_gateway_events event;
};

static struct _discord_gateway_context *
_discord_gateway_context_init(const struct discord_gateway *gw,
                              enum discord_gateway_events event)
{
    struct _discord_gateway_context *cxt = malloc(sizeof *cxt);
    struct discord *clone = discord_clone(CLIENT(gw, gw));

    cxt->gw = &clone->gw;
    cxt->event = event;

    return cxt;
}

static void
_discord_gateway_context_cleanup(struct _discord_gateway_context *cxt)
{
    discord_cleanup(CLIENT(cxt->gw, gw));
    free(cxt);
}

static const char *
_discord_gateway_opcode_print(enum discord_gateway_opcodes opcode)
{
    switch (opcode) {
        CASE_RETURN_STR(DISCORD_GATEWAY_DISPATCH);
        CASE_RETURN_STR(DISCORD_GATEWAY_HEARTBEAT);
        CASE_RETURN_STR(DISCORD_GATEWAY_IDENTIFY);
        CASE_RETURN_STR(DISCORD_GATEWAY_PRESENCE_UPDATE);
        CASE_RETURN_STR(DISCORD_GATEWAY_VOICE_STATE_UPDATE);
        CASE_RETURN_STR(DISCORD_GATEWAY_RESUME);
        CASE_RETURN_STR(DISCORD_GATEWAY_RECONNECT);
        CASE_RETURN_STR(DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS);
        CASE_RETURN_STR(DISCORD_GATEWAY_INVALID_SESSION);
        CASE_RETURN_STR(DISCORD_GATEWAY_HELLO);
        CASE_RETURN_STR(DISCORD_GATEWAY_HEARTBEAT_ACK);
    default:
        return "INVALID_GATEWAY_OPCODE";
    }
}

static const char *
_discord_gateway_close_opcode_print(enum discord_gateway_close_opcodes opcode)
{
    switch (opcode) {
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_RECONNECT);
    default: {
        const char *str;

        str = ws_close_opcode_print((enum ws_close_reason)opcode);
        if (str) return str;

        log_warn("Unknown WebSockets close opcode (code: %d)", opcode);
    }
        return "UNKNOWN_WEBSOCKETS_CLOSE_OPCODE";
    }
}

static void
on_hello(struct discord_gateway *gw)
{
    jsmnf_pair *f;

    gw->timer->interval = 0;
    gw->timer->hbeat = gw->timer->now;

    if ((f = jsmnf_find(gw->payload.data, gw->json, "heartbeat_interval", 18)))
        gw->timer->interval = strtoull(gw->json + f->v.pos, NULL, 10);

    if (gw->session->status & DISCORD_SESSION_RESUMABLE)
        discord_gateway_send_resume(gw, &(struct discord_resume){
                                            .session_id = gw->session->id,
                                            .seq = gw->payload.seq,
                                        });
    else
        discord_gateway_send_identify(gw, &gw->id);
}

static enum discord_gateway_events
_discord_gateway_event_eval(char name[])
{
#define RETURN_IF_MATCH(event, str)                                           \
    if (!strcmp(#event, str)) return DISCORD_EV_##event

    RETURN_IF_MATCH(READY, name);
    RETURN_IF_MATCH(RESUMED, name);
    RETURN_IF_MATCH(APPLICATION_COMMAND_CREATE, name);
    RETURN_IF_MATCH(APPLICATION_COMMAND_UPDATE, name);
    RETURN_IF_MATCH(APPLICATION_COMMAND_DELETE, name);
    RETURN_IF_MATCH(CHANNEL_CREATE, name);
    RETURN_IF_MATCH(CHANNEL_UPDATE, name);
    RETURN_IF_MATCH(CHANNEL_DELETE, name);
    RETURN_IF_MATCH(CHANNEL_PINS_UPDATE, name);
    RETURN_IF_MATCH(THREAD_CREATE, name);
    RETURN_IF_MATCH(THREAD_UPDATE, name);
    RETURN_IF_MATCH(THREAD_DELETE, name);
    RETURN_IF_MATCH(THREAD_LIST_SYNC, name);
    RETURN_IF_MATCH(THREAD_MEMBER_UPDATE, name);
    RETURN_IF_MATCH(THREAD_MEMBERS_UPDATE, name);
    RETURN_IF_MATCH(GUILD_CREATE, name);
    RETURN_IF_MATCH(GUILD_UPDATE, name);
    RETURN_IF_MATCH(GUILD_DELETE, name);
    RETURN_IF_MATCH(GUILD_BAN_ADD, name);
    RETURN_IF_MATCH(GUILD_BAN_REMOVE, name);
    RETURN_IF_MATCH(GUILD_EMOJIS_UPDATE, name);
    RETURN_IF_MATCH(GUILD_STICKERS_UPDATE, name);
    RETURN_IF_MATCH(GUILD_INTEGRATIONS_UPDATE, name);
    RETURN_IF_MATCH(GUILD_MEMBER_ADD, name);
    RETURN_IF_MATCH(GUILD_MEMBER_UPDATE, name);
    RETURN_IF_MATCH(GUILD_MEMBER_REMOVE, name);
    RETURN_IF_MATCH(GUILD_MEMBERS_CHUNK, name);
    RETURN_IF_MATCH(GUILD_ROLE_CREATE, name);
    RETURN_IF_MATCH(GUILD_ROLE_UPDATE, name);
    RETURN_IF_MATCH(GUILD_ROLE_DELETE, name);
    RETURN_IF_MATCH(INTEGRATION_CREATE, name);
    RETURN_IF_MATCH(INTEGRATION_UPDATE, name);
    RETURN_IF_MATCH(INTEGRATION_DELETE, name);
    RETURN_IF_MATCH(INTERACTION_CREATE, name);
    RETURN_IF_MATCH(INVITE_CREATE, name);
    RETURN_IF_MATCH(INVITE_DELETE, name);
    RETURN_IF_MATCH(MESSAGE_CREATE, name);
    RETURN_IF_MATCH(MESSAGE_UPDATE, name);
    RETURN_IF_MATCH(MESSAGE_DELETE, name);
    RETURN_IF_MATCH(MESSAGE_DELETE_BULK, name);
    RETURN_IF_MATCH(MESSAGE_REACTION_ADD, name);
    RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE, name);
    RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE_ALL, name);
    RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE_EMOJI, name);
    RETURN_IF_MATCH(PRESENCE_UPDATE, name);
    RETURN_IF_MATCH(STAGE_INSTANCE_CREATE, name);
    RETURN_IF_MATCH(STAGE_INSTANCE_DELETE, name);
    RETURN_IF_MATCH(STAGE_INSTANCE_UPDATE, name);
    RETURN_IF_MATCH(TYPING_START, name);
    RETURN_IF_MATCH(USER_UPDATE, name);
    RETURN_IF_MATCH(VOICE_STATE_UPDATE, name);
    RETURN_IF_MATCH(VOICE_SERVER_UPDATE, name);
    RETURN_IF_MATCH(WEBHOOKS_UPDATE, name);
    return DISCORD_EV_NONE;

#undef RETURN_IF_MATCH
}

static void
_discord_gateway_dispatch_thread(void *p_cxt)
{
    struct _discord_gateway_context *cxt = p_cxt;

    logconf_info(&cxt->gw->conf,
                 "Thread " ANSICOLOR("starts", ANSI_FG_RED) " to serve %s",
                 cxt->gw->payload.name);

    discord_gateway_dispatch(cxt->gw, cxt->event);

    logconf_info(&cxt->gw->conf,
                 "Thread " ANSICOLOR("exits", ANSI_FG_RED) " from serving %s",
                 cxt->gw->payload.name);

    _discord_gateway_context_cleanup(cxt);
}

static void
on_dispatch(struct discord_gateway *gw)
{
    /* get dispatch event opcode */
    enum discord_gateway_events event;
    enum discord_event_scheduler mode;

    /* XXX: this should only apply for user dispatched payloads? */
#if 0
  /* Ratelimit check */
  if (gw->timer->now - gw->timer->event < 60000) {
    ++gw->session->event_count;
    ASSERT_S(gw->session->event_count < 120,
             "Reach event dispatch threshold (120 every 60 seconds)");
  }
  else {
    gw->timer->event = gw->timer->now;
    gw->session->event_count = 0;
  }
#endif

    switch (event = _discord_gateway_event_eval(gw->payload.name)) {
    case DISCORD_EV_READY: {
        jsmnf_pair *f;

        logconf_info(&gw->conf, "Succesfully started a Discord session!");

        if ((f = jsmnf_find(gw->payload.data, gw->json, "session_id", 10)))
            snprintf(gw->session->id, sizeof(gw->session->id), "%.*s",
                     (int)f->v.len, gw->json + f->v.pos);
        ASSERT_S(*gw->session->id, "Missing session_id from READY event");

        gw->session->is_ready = true;
        gw->session->retry.attempt = 0;

        discord_gateway_send_heartbeat(gw, gw->payload.seq);
    } break;
    case DISCORD_EV_RESUMED:
        logconf_info(&gw->conf, "Succesfully resumed a Discord session!");

        gw->session->is_ready = true;
        gw->session->retry.attempt = 0;

        discord_gateway_send_heartbeat(gw, gw->payload.seq);
        break;
    default:
        break;
    }

    mode = gw->scheduler(CLIENT(gw, gw), gw->json + gw->payload.data->v.pos,
                         gw->payload.data->v.len, event);

    /* user subscribed to event */
    switch (mode) {
    case DISCORD_EVENT_IGNORE:
        break;
    case DISCORD_EVENT_MAIN_THREAD:
        discord_gateway_dispatch(gw, event);
        break;
    case DISCORD_EVENT_WORKER_THREAD: {
        struct _discord_gateway_context *cxt =
            _discord_gateway_context_init(gw, event);
        int ret = work_run(&_discord_gateway_dispatch_thread, cxt);

        if (ret != 0) {
            log_error("Couldn't execute worker-thread (code %d)", ret);
            _discord_gateway_context_cleanup(cxt);
        }
    } break;
    default:
        ERR("Unknown event handling mode (code: %d)", mode);
    }
}

static void
on_invalid_session(struct discord_gateway *gw)
{
    enum ws_close_reason opcode;
    const char *reason;

    gw->session->status = DISCORD_SESSION_SHUTDOWN;

    /* attempt to resume if session isn't invalid */
    if (gw->payload.data->v.len != 5
        || strncmp("false", gw->json + gw->payload.data->v.pos, 5))
    {
        gw->session->status |= DISCORD_SESSION_RESUMABLE;
        reason = "Invalid session, will attempt to resume";
        opcode = (enum ws_close_reason)DISCORD_GATEWAY_CLOSE_REASON_RECONNECT;
    }
    else {
        reason = "Invalid session, can't resume";
        opcode = WS_CLOSE_REASON_NORMAL;
    }
    gw->session->retry.enable = true;

    ws_close(gw->ws, opcode, reason, SIZE_MAX);
}

static void
on_reconnect(struct discord_gateway *gw)
{
    const char reason[] = "Discord expects client to reconnect";

    gw->session->status = DISCORD_SESSION_RESUMABLE | DISCORD_SESSION_SHUTDOWN;
    gw->session->retry.enable = true;

    ws_close(gw->ws,
             (enum ws_close_reason)DISCORD_GATEWAY_CLOSE_REASON_RECONNECT,
             reason, sizeof(reason));
}

static void
on_heartbeat_ack(struct discord_gateway *gw)
{
    /* get request / response interval in milliseconds */
    pthread_rwlock_wrlock(&gw->timer->rwlock);
    gw->timer->ping_ms = (int)(gw->timer->now - gw->timer->hbeat);
    pthread_rwlock_unlock(&gw->timer->rwlock);

    logconf_trace(&gw->conf, "PING: %d ms", gw->timer->ping_ms);
}

static void
on_connect_cb(void *p_gw,
              struct websockets *ws,
              struct ws_info *info,
              const char *ws_protocols)
{
    (void)ws;
    (void)info;
    struct discord_gateway *gw = p_gw;

    logconf_info(&gw->conf, "Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_gw,
            struct websockets *ws,
            struct ws_info *info,
            enum ws_close_reason wscode,
            const char *reason,
            size_t len)
{
    (void)ws;
    (void)info;
    struct discord_gateway *gw = p_gw;
    enum discord_gateway_close_opcodes opcode =
        (enum discord_gateway_close_opcodes)wscode;

    logconf_warn(
        &gw->conf,
        ANSICOLOR("CLOSE %s", ANSI_FG_RED) " (code: %4d, %zu bytes): '%.*s'",
        _discord_gateway_close_opcode_print(opcode), opcode, len, (int)len,
        reason);

    /* user-triggered shutdown */
    if (gw->session->status & DISCORD_SESSION_SHUTDOWN) return;

    /* mark as in the process of being shutdown */
    gw->session->status |= DISCORD_SESSION_SHUTDOWN;

    switch (opcode) {
    default: /* websocket/clouflare opcodes */
        if (WS_CLOSE_REASON_NORMAL == (enum ws_close_reason)opcode) {
            gw->session->status |= DISCORD_SESSION_RESUMABLE;
            gw->session->retry.enable = false;
            break;
        }
        /* fall-through */
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE:
    case DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT:
        logconf_warn(
            &gw->conf,
            "Gateway will attempt to reconnect and start a new session");
        gw->session->status &= ~DISCORD_SESSION_RESUMABLE;
        gw->session->retry.enable = true;
        break;
    case DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED:
    case DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD:
    case DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS:
        logconf_warn(&gw->conf, "Gateway will not attempt to reconnect");
        gw->session->status &= ~DISCORD_SESSION_RESUMABLE;
        gw->session->retry.enable = false;
        break;
    case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR:
    case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE:
    case DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR:
    case DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED:
    case DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED:
    case DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED:
        logconf_warn(
            &gw->conf,
            "Gateway will attempt to reconnect and resume current session");
        gw->session->status |= DISCORD_SESSION_RESUMABLE;
        gw->session->retry.enable = true;
        break;
    }
}

static void
on_text_cb(void *p_gw,
           struct websockets *ws,
           struct ws_info *info,
           const char *text,
           size_t len)
{
    (void)ws;
    struct discord_gateway *gw = p_gw;
    jsmn_parser parser;

    gw->json = (char *)text;
    gw->length = len;

    jsmn_init(&parser);
    if (0 < jsmn_parse_auto(&parser, text, len, &gw->parse.tokens,
                            &gw->parse.ntokens))
    {
        jsmnf_loader loader;

        jsmnf_init(&loader);
        if (0 < jsmnf_load_auto(&loader, text, gw->parse.tokens,
                                parser.toknext, &gw->parse.pairs,
                                &gw->parse.npairs))
        {
            jsmnf_pair *f;

            if ((f = jsmnf_find(gw->parse.pairs, text, "t", 1))) {
                if (JSMN_STRING == f->type)
                    snprintf(gw->payload.name, sizeof(gw->payload.name),
                             "%.*s", (int)f->v.len, gw->json + f->v.pos);
                else
                    *gw->payload.name = '\0';
            }
            if ((f = jsmnf_find(gw->parse.pairs, text, "s", 1))) {
                int seq = (int)strtol(gw->json + f->v.pos, NULL, 10);
                if (seq) gw->payload.seq = seq;
            }
            if ((f = jsmnf_find(gw->parse.pairs, text, "op", 2)))
                gw->payload.opcode = (enum discord_gateway_opcodes)strtol(
                    gw->json + f->v.pos, NULL, 10);
            gw->payload.data = jsmnf_find(gw->parse.pairs, text, "d", 1);
        }
    }

    logconf_trace(
        &gw->conf,
        ANSICOLOR("RCV",
                  ANSI_FG_BRIGHT_YELLOW) " %s%s%s (%zu bytes) [@@@_%zu_@@@]",
        _discord_gateway_opcode_print(gw->payload.opcode),
        *gw->payload.name ? " -> " : "", gw->payload.name, len,
        info->loginfo.counter);

    switch (gw->payload.opcode) {
    case DISCORD_GATEWAY_DISPATCH:
        on_dispatch(gw);
        break;
    case DISCORD_GATEWAY_INVALID_SESSION:
        on_invalid_session(gw);
        break;
    case DISCORD_GATEWAY_RECONNECT:
        on_reconnect(gw);
        break;
    case DISCORD_GATEWAY_HELLO:
        on_hello(gw);
        break;
    case DISCORD_GATEWAY_HEARTBEAT_ACK:
        on_heartbeat_ack(gw);
        break;
    default:
        logconf_error(&gw->conf,
                      "Not yet implemented Gateway Event (code: %d)",
                      gw->payload.opcode);
        break;
    }
}

static discord_event_scheduler_t
default_scheduler_cb(struct discord *a,
                     const char b[],
                     size_t c,
                     enum discord_gateway_events d)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    return DISCORD_EVENT_MAIN_THREAD;
}

static int
on_io_poller_curl(struct io_poller *io, CURLM *mhandle, void *user_data)
{
    (void)io;
    (void)mhandle;
    return discord_gateway_perform(user_data);
}

void
discord_gateway_init(struct discord_gateway *gw,
                     struct logconf *conf,
                     struct sized_buffer *token)
{
    /* Web-Sockets callbacks */
    struct ws_callbacks cbs = { 0 };
    /* Web-Sockets custom attributes */
    struct ws_attr attr = { 0 };
    struct sized_buffer buf;
    /* prefix directive */
    char *path[] = { "discord", "default_prefix" };

    cbs.data = gw;
    cbs.on_connect = &on_connect_cb;
    cbs.on_text = &on_text_cb;
    cbs.on_close = &on_close_cb;

    attr.conf = conf;

    /* Web-Sockets handler */
    gw->mhandle = curl_multi_init();
    io_poller_curlm_add(CLIENT(gw, gw)->io_poller, gw->mhandle,
                        on_io_poller_curl, gw);
    gw->ws = ws_init(&cbs, gw->mhandle, &attr);
    logconf_branch(&gw->conf, conf, "DISCORD_GATEWAY");

    gw->timer = calloc(1, sizeof *gw->timer);
    if (pthread_rwlock_init(&gw->timer->rwlock, NULL))
        ERR("Couldn't initialize pthread rwlock");

    /* client connection status */
    gw->session = calloc(1, sizeof *gw->session);
    gw->session->retry.enable = true;
    gw->session->retry.limit = 5; /* TODO: shouldn't be a hard limit */

    /* connection identify token */
    cog_strndup(token->start, token->size, &gw->id.token);

    /* connection identify properties */
    gw->id.properties = calloc(1, sizeof *gw->id.properties);
    gw->id.properties->os = OSNAME;
    gw->id.properties->browser = "concord";
    gw->id.properties->device = "concord";

    /* the bot initial presence */
    gw->id.presence = calloc(1, sizeof *gw->id.presence);
    gw->id.presence->status = "online";
    gw->id.presence->since = cog_timestamp_ms();
    discord_gateway_send_presence_update(gw, gw->id.presence);

    /* default callbacks */
    gw->scheduler = default_scheduler_cb;

    /* check for default prefix in config file */
    buf = logconf_get_field(conf, path, sizeof(path) / sizeof *path);
    if (buf.size) {
        jsmn_parser parser;
        jsmntok_t tokens[16];

        jsmn_init(&parser);
        if (0 < jsmn_parse(&parser, buf.start, buf.size, tokens,
                           sizeof(tokens) / sizeof *tokens))
        {
            jsmnf_loader loader;
            jsmnf_pair pairs[16];

            jsmnf_init(&loader);
            if (0 < jsmnf_load(&loader, buf.start, tokens, parser.toknext,
                               pairs, sizeof(pairs) / sizeof *pairs))
            {
                bool enable_prefix = false;
                jsmnf_pair *f;

                if ((f = jsmnf_find(pairs, buf.start, "enable", 6)))
                    enable_prefix = ('t' == buf.start[f->v.pos]);

                if (enable_prefix
                    && (f = jsmnf_find(pairs, buf.start, "prefix", 6))) {
                    char prefix[64] = "";

                    snprintf(prefix, sizeof(prefix), "%.*s", (int)f->v.len,
                             buf.start + f->v.pos);
                    discord_set_prefix(CLIENT(gw, gw), prefix);
                }
            }
        }
    }
}

void
discord_gateway_cleanup(struct discord_gateway *gw)
{
    /* cleanup WebSockets handle */
    io_poller_curlm_del(CLIENT(gw, gw)->io_poller, gw->mhandle);
    curl_multi_cleanup(gw->mhandle);
    ws_cleanup(gw->ws);
    /* cleanup timers */
    pthread_rwlock_destroy(&gw->timer->rwlock);
    free(gw->timer);
    /* cleanup bot identification */
    if (gw->id.token) free(gw->id.token);
    free(gw->id.properties);
    free(gw->id.presence);
    /* cleanup client session */
    free(gw->session);
    /* cleanup user commands */
    if (gw->pool) {
        for (size_t i = 0; i < gw->amt; i++)
            free(gw->pool[i].start);
        free(gw->pool);
    }
    if (gw->prefix.start) free(gw->prefix.start);
    if (gw->parse.pairs) free(gw->parse.pairs);
    if (gw->parse.tokens) free(gw->parse.tokens);
}

#ifdef CCORD_DEBUG_WEBSOCKETS
static void
_ws_curl_debug_dump(const char *text,
                    FILE *stream,
                    unsigned char *ptr,
                    size_t size)
{
    unsigned int width = 0x10;
    size_t i;
    size_t c;

    fprintf(stream, "%s, %10.10lu bytes (0x%8.8lx)\n", text,
            (unsigned long)size, (unsigned long)size);

    for (i = 0; i < size; i += width) {

        fprintf(stream, "%4.4lx: ", (unsigned long)i);

        for (c = 0; c < width; c++)
            if (i + c < size)
                fprintf(stream, "%02x ", ptr[i + c]);
            else
                fputs("   ", stream);

        for (c = 0; (c < width) && (i + c < size); c++) {
            /* check for 0D0A; if found, skip past and start a new line of
             * output */
            if ((i + c + 1 < size) && ptr[i + c] == 0x0D
                && ptr[i + c + 1] == 0x0A) {
                i += (c + 2 - width);
                break;
            }
            fprintf(stream, "%c",
                    (ptr[i + c] >= 0x20) && (ptr[i + c] < 0x80) ? ptr[i + c]
                                                                : '.');
            /* check again for 0D0A, to avoid an extra \n if it's at width */
            if ((i + c + 2 < size) && ptr[i + c + 1] == 0x0D
                && ptr[i + c + 2] == 0x0A) {
                i += (c + 3 - width);
                break;
            }
        }
        fputc('\n', stream); /* newline */
    }
    fflush(stream);
}

static int
_ws_curl_debug_trace(
    CURL *handle, curl_infotype type, char *data, size_t size, void *userp)
{
    const char *text;
    (void)handle;
    (void)userp;

    switch (type) {
    case CURLINFO_TEXT:
        fprintf(stderr, "== Info: %s", data);
        /* FALLTHROUGH */
    default:
        return 0;

    case CURLINFO_HEADER_OUT:
        text = "=> Send header";
        break;
    case CURLINFO_DATA_OUT:
        text = "=> Send data";
        break;
    case CURLINFO_SSL_DATA_OUT:
        text = "=> Send SSL data";
        break;
    case CURLINFO_HEADER_IN:
        text = "<= Recv header";
        break;
    case CURLINFO_DATA_IN:
        text = "<= Recv data";
        break;
    case CURLINFO_SSL_DATA_IN:
        text = "<= Recv SSL data";
        break;
    }

    _ws_curl_debug_dump(text, stderr, (unsigned char *)data, size);
    return 0;
}
#endif /* CCORD_DEBUG_WEBSOCKETS */

CCORDcode
discord_gateway_start(struct discord_gateway *gw)
{
    struct discord *client = CLIENT(gw, gw);
    struct sized_buffer json = { 0 };
    char url[1024];
    CURL *ehandle;

    if (gw->session->retry.attempt >= gw->session->retry.limit) {
        logconf_fatal(&gw->conf,
                      "Failed reconnecting to Discord after %d tries",
                      gw->session->retry.limit);

        return CCORD_DISCORD_CONNECTION;
    }
    else if (CCORD_OK != discord_get_gateway_bot(client, &json)) {
        logconf_fatal(&gw->conf, "Couldn't retrieve Gateway Bot information");

        return CCORD_DISCORD_BAD_AUTH;
    }
    else {
        jsmn_parser parser;
        jsmntok_t tokens[32];

        jsmn_init(&parser);
        if (0 < jsmn_parse(&parser, json.start, json.size, tokens,
                           sizeof(tokens) / sizeof *tokens))
        {
            jsmnf_loader loader;
            jsmnf_pair pairs[32];

            jsmnf_init(&loader);
            if (0 < jsmnf_load(&loader, json.start, tokens, parser.toknext,
                               pairs, sizeof(pairs) / sizeof *pairs))
            {
                jsmnf_pair *f;

                if ((f = jsmnf_find(pairs, json.start, "url", 3))) {
                    const char *base_url = json.start + f->v.pos;
                    const int base_url_len = (int)f->v.len;
                    int len;

                    len = snprintf(
                        url, sizeof(url), "%.*s%s" DISCORD_GATEWAY_URL_SUFFIX,
                        base_url_len, base_url,
                        ('/' == base_url[base_url_len - 1]) ? "" : "/");
                    ASSERT_NOT_OOB(len, sizeof(url));
                }
                if ((f = jsmnf_find(pairs, json.start, "shards", 6)))
                    gw->session->shards =
                        (int)strtol(json.start + f->v.pos, NULL, 10);
                if ((f = jsmnf_find(pairs, json.start, "session_start_limit",
                                    19)))
                    discord_session_start_limit_from_jsmnf(
                        f, json.start, &gw->session->start_limit);
            }
        }
    }

    free(json.start);

    if (!gw->session->start_limit.remaining) {
        logconf_fatal(&gw->conf,
                      "Reach sessions threshold (%d),"
                      "Please wait %d seconds and try again",
                      gw->session->start_limit.total,
                      gw->session->start_limit.reset_after / 1000);

        return CCORD_DISCORD_RATELIMIT;
    }

    ws_set_url(gw->ws, url, NULL);
    ehandle = ws_start(gw->ws);

#ifdef CCORD_DEBUG_WEBSOCKETS
    curl_easy_setopt(ehandle, CURLOPT_DEBUGFUNCTION, _ws_curl_debug_trace);
    curl_easy_setopt(ehandle, CURLOPT_VERBOSE, 1L);
#else
    (void)ehandle;
#endif /* CCORD_DEBUG_WEBSOCKETS */

    return CCORD_OK;
}

bool
discord_gateway_end(struct discord_gateway *gw)
{
    ws_end(gw->ws);

    /* keep only resumable information */
    gw->session->status &= DISCORD_SESSION_RESUMABLE;
    gw->session->is_ready = false;

    if (!gw->session->retry.enable) {
        logconf_warn(&gw->conf, "Discord Gateway Shutdown");

        /* reset for next run */
        gw->session->status = DISCORD_SESSION_OFFLINE;
        gw->session->is_ready = false;
        gw->session->retry.enable = false;
        gw->session->retry.attempt = 0;

        return true;
    }

    ++gw->session->retry.attempt;

    logconf_info(&gw->conf, "Reconnect attempt #%d",
                 gw->session->retry.attempt);

    return false;
}

CCORDcode
discord_gateway_perform(struct discord_gateway *gw)
{
    /* check for pending transfer, exit on failure */
    if (!ws_multi_socket_run(gw->ws, &gw->timer->now))
        return CCORD_DISCORD_CONNECTION;

    /* client is in the process of shutting down */
    if (gw->session->status & DISCORD_SESSION_SHUTDOWN) return CCORD_OK;

    /* client is in the process of connecting */
    if (!gw->session->is_ready) return CCORD_OK;

    /* check if timespan since first pulse is greater than
     * minimum heartbeat interval required */
    if (gw->timer->interval < gw->timer->now - gw->timer->hbeat) {
        discord_gateway_send_heartbeat(gw, gw->payload.seq);
    }

    return CCORD_OK;
}

void
discord_gateway_shutdown(struct discord_gateway *gw)
{
    const char reason[] = "Client triggered shutdown";

    /* TODO: MT-Unsafe section */
    gw->session->retry.enable = false;
    gw->session->status = DISCORD_SESSION_SHUTDOWN;

    ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

void
discord_gateway_reconnect(struct discord_gateway *gw, bool resume)
{
    const char reason[] = "Client triggered reconnect";
    enum ws_close_reason opcode;

    /* TODO: MT-Unsafe section */
    gw->session->retry.enable = true;
    gw->session->status = DISCORD_SESSION_SHUTDOWN;
    if (resume) {
        gw->session->status |= DISCORD_SESSION_RESUMABLE;
        opcode = (enum ws_close_reason)DISCORD_GATEWAY_CLOSE_REASON_RECONNECT;
    }
    else {
        opcode = WS_CLOSE_REASON_NORMAL;
    }

    ws_close(gw->ws, opcode, reason, sizeof(reason));
}
