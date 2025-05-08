#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>
#include <curl/curl.h>

#include "websockets.h"
#include "cog-utils.h"

#define LOGMOD_APPLICATION_ID "CORE"
#define LOGMOD_CONTEXT_ID     "WEBSOCKETS"
#define LOGMOD_STATIC
#include "logmod.h"

#define CURLM_LOG(ws, mcode)                                                  \
    logmod_log(FATAL, ws->loggers.trace, "(CURLM code: %d) %s", mcode,        \
               curl_multi_strerror(mcode))
#define CASE_RETURN_STR(code)                                                 \
    case code:                                                                \
        return #code

struct websockets {
    /** LogMod handler */
    struct logmod logmod;
    /** the buffer of the received messages */
    char *msg_buf;
    /** the length of the received messages */
    size_t msg_len;
    /** the amount of bytes left to complete the message */
    size_t bytesleft;
    /** if the message is continued */
    bool is_continued;
    /** the expected message type */
    int exp_msg_type;
    /** the headers to be sent */
    struct curl_slist *headers;
    struct {
        /** the websockets agent logging module */
        struct logmod_logger *trace;
        /** the user agent raw websockets logging module */
        struct logmod_logger *raw;
    } loggers;
    /**
     * the client connections status
     * @note `WS_CONNECTING` set at ws_start()
     *       `WS_CONNECTED` set at ws_on_connect()
     *       `WS_DISCONNECTING` set at start of ws_end() or ws_close()
     *       `WS_DISCONNECTED` set after complete shutdown at ws_end()
     * @see ws_get_status()
     */
    enum ws_status status;
    /** perform non-blocking transfers */
    CURLM *mhandle;
    /** perform/receive individual WebSockets tranfers */
    CURL *ehandle;
    /** timestamp updated every ws_timestamp_update() call */
    uint64_t now_tstamp;
    /** WebSockets connection URL @see ws_set_url() */
    char base_url[512 + 1];
    /** WebSockets callbacks */
    struct ws_callbacks cbs;
    /**
     * capture curl error messages
     * @note should only be accessed after a error code returns
     * @see https://curl.se/libcurl/c/CURLOPT_ERRORBUFFER.html
     */
    char errbuf[CURL_ERROR_SIZE];
    /** lock for functions that may be called in other threads */
    pthread_mutex_t lock;
    /** lock for reading/writing the event-loop timestamp */
    pthread_rwlock_t rwlock;

    /**
     * user-triggered actions
     * @note the user may close the active connection via ws_close()
     */
    enum {
        /** no user action taking place */
        WS_ACTION_NONE = 0,
        /** user called ws_close() */
        WS_ACTION_BEGIN_CLOSE,
        /** succesfully closed connection after ws_close() */
        WS_ACTION_END_CLOSE
    } action;

    /** close context filled at ws_close() */
    struct {
        /** opcode reason for closing */
        enum ws_close_reason code;
        /** textual reason for closing */
        char reason[125 + 1];
    } pending_close;
};

const char *
ws_close_opcode_print(enum ws_close_reason opcode)
{
    switch (opcode) {
        CASE_RETURN_STR(WS_CLOSE_REASON_NORMAL);
        CASE_RETURN_STR(WS_CLOSE_REASON_GOING_AWAY);
        CASE_RETURN_STR(WS_CLOSE_REASON_PROTOCOL_ERROR);
        CASE_RETURN_STR(WS_CLOSE_REASON_UNEXPECTED_DATA);
        CASE_RETURN_STR(WS_CLOSE_REASON_NO_REASON);
        CASE_RETURN_STR(WS_CLOSE_REASON_ABRUPTLY);
        CASE_RETURN_STR(WS_CLOSE_REASON_INCONSISTENT_DATA);
        CASE_RETURN_STR(WS_CLOSE_REASON_POLICY_VIOLATION);
        CASE_RETURN_STR(WS_CLOSE_REASON_TOO_BIG);
        CASE_RETURN_STR(WS_CLOSE_REASON_MISSING_EXTENSION);
        CASE_RETURN_STR(WS_CLOSE_REASON_SERVER_ERROR);
        CASE_RETURN_STR(WS_CLOSE_REASON_IANA_REGISTRY_START);
        CASE_RETURN_STR(WS_CLOSE_REASON_IANA_REGISTRY_END);
        CASE_RETURN_STR(WS_CLOSE_REASON_PRIVATE_START);
        CASE_RETURN_STR(WS_CLOSE_REASON_PRIVATE_END);
    default:
        if (opcode > WS_CLOSE_REASON_PRIVATE_START
            && opcode < WS_CLOSE_REASON_PRIVATE_END)
        {
            return "WS_CLOSE_REASON_PRIVATE";
        }
        return "WS_CLOSE_REASON_UNKNOWN";
    }
}

static const char *
_ws_status_print(enum ws_status status)
{
    switch (status) {
        CASE_RETURN_STR(WS_DISCONNECTED);
        CASE_RETURN_STR(WS_CONNECTED);
        CASE_RETURN_STR(WS_DISCONNECTING);
        CASE_RETURN_STR(WS_CONNECTING);
    default:
        return NULL;
    }
}

static CURL *_ws_ehandle_init(struct websockets *ws);

static void
_ws_set_status_nolock(struct websockets *ws, enum ws_status status)
{
    if ((WS_DISCONNECTING == ws->status) && (status != WS_DISCONNECTED)) {
        return;
    }

    switch (status) {
    case WS_DISCONNECTED:
        if (WS_DISCONNECTED == ws->status) {
            logmod_log(INFO, ws->loggers.trace,
                       "Client is already disconnected, skipping "
                       "WS_DISCONNECT");
            break;
        }
        else if (WS_DISCONNECTING != ws->status) {
            logmod_log(WARN, ws->loggers.trace,
                       "Abruptly changed status to WS_DISCONNECTED "
                       "(previous status: %s)",
                       _ws_status_print(ws->status));
        }

        logmod_log(INFO, ws->loggers.trace,
                   "Client disconnected from %s (status: %s)", ws->base_url,
                   _ws_status_print(status));
        break;
    case WS_CONNECTED:
        if (ws->status != WS_CONNECTING) {
            /* if the status is not WS_CONNECTING, it means that
             * ws_start() was not called before the event loop */
            logmod_log(WARN, ws->loggers.trace,
                       "Abruptly changed status to WS_CONNECTED "
                       "(previous status: %s), this may be a bug!",
                       _ws_status_print(ws->status));
        }
        logmod_log(INFO, ws->loggers.trace,
                   "Client connected to %s (status: %s)", ws->base_url,
                   _ws_status_print(status));
        break;
    case WS_DISCONNECTING:
        if (WS_DISCONNECTED == ws->status) {
            logmod_log(WARN, ws->loggers.trace,
                       "Client is already disconnected, skipping "
                       "WS_DISCONNECTING");
            break;
        }

        logmod_log(INFO, ws->loggers.trace,
                   "Client is disconnecting from %s (status: %s)",
                   ws->base_url, _ws_status_print(status));
        break;
    case WS_CONNECTING: /* triggered at ws_start() */
        logmod_log(INFO, ws->loggers.trace,
                   "Client is connecting to %s (status: %s)", ws->base_url,
                   _ws_status_print(status));
        break;
    default:
        logmod_log(WARN, ws->loggers.trace,
                   "Unknown status change to %s (code: %d)",
                   _ws_status_print(status), status);
        break;
    }
    ws->status = status;
}

static void
_ws_set_status(struct websockets *ws, enum ws_status status)
{
    pthread_mutex_lock(&ws->lock);
    _ws_set_status_nolock(ws, status);
    pthread_mutex_unlock(&ws->lock);
}

static void
ws_on_connect_cb(void *p_ws)
{
    struct websockets *ws = p_ws;

    _ws_set_status(ws, WS_CONNECTED);

    logmod_log(INFO, ws->loggers.raw, "WS_RCV_CONNECT [%s] - %s",
               ws->loggers.trace->context_id, ws->base_url);

    logmod_log(TRACE, ws->loggers.trace, "%s CONNECT",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, YELLOW, "RCV"));

    if (ws->cbs.on_connect) ws->cbs.on_connect(ws->cbs.data, ws);
}

static void
ws_on_close_cb(void *p_ws,
               CURL *ehandle,
               unsigned int wscode,
               const char *reason,
               size_t len)
{
    struct websockets *ws = p_ws;
    (void)ehandle;

    _ws_set_status(ws, WS_DISCONNECTING);

    logmod_log(WARN, ws->loggers.raw, "WS_RCV_CLOSE(%d) [%s] - %s\n%.*s",
               wscode, ws->loggers.trace->context_id, ws->base_url, (int)len,
               reason);

    logmod_log(TRACE, ws->loggers.trace, "%s CLOSE(%d) (%zu bytes)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, YELLOW, "RCV"),
               wscode, len);

    if (ws->cbs.on_close)
        ws->cbs.on_close(ws->cbs.data, ws, (enum ws_close_reason)wscode,
                         reason, len);

    ws->action = WS_ACTION_END_CLOSE;

    /* will set status to WS_DISCONNECTED when is_running == false */
}

static void
ws_on_text_cb(void *p_ws, CURL *ehandle, const char *text, size_t len)
{
    struct websockets *ws = p_ws;
    (void)ehandle;

    logmod_log(INFO, ws->loggers.raw, "WS_RCV_TEXT [%s] - %s\n%.*s",
               ws->loggers.trace->context_id, ws->base_url, (int)len, text);

    logmod_log(TRACE, ws->loggers.trace, "%s TEXT (%zu bytes)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, YELLOW, "RCV"),
               len);

    if (ws->cbs.on_text) ws->cbs.on_text(ws->cbs.data, ws, text, len);
}

static void
ws_on_binary_cb(void *p_ws, CURL *ehandle, const void *mem, size_t len)
{
    struct websockets *ws = p_ws;
    (void)ehandle;

    logmod_log(INFO, ws->loggers.raw, "WS_RCV_BINARY [%s] - %s",
               ws->loggers.trace->context_id, ws->base_url);

    logmod_log(TRACE, ws->loggers.trace, "%s BINARY (%zu bytes)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, YELLOW, "RCV"),
               len);

    if (ws->cbs.on_binary) ws->cbs.on_binary(ws->cbs.data, ws, mem, len);
}

static void
ws_on_ping_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
    struct websockets *ws = p_ws;
    (void)ehandle;

    logmod_log(DEBUG, ws->loggers.raw, "WS_RCV_PING [%s] - %s\n%.*s",
               ws->loggers.trace->context_id, ws->base_url, (int)len, reason);

    logmod_log(TRACE, ws->loggers.trace, "%s PING (%zu bytes)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, YELLOW, "RCV"),
               len);

    if (ws->cbs.on_ping) ws->cbs.on_ping(ws->cbs.data, ws, reason, len);
}

static void
ws_on_pong_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
    struct websockets *ws = p_ws;
    (void)ehandle;

    logmod_log(DEBUG, ws->loggers.raw, "WS_RCV_PONG [%s] - %s\n%.*s",
               ws->loggers.trace->context_id, ws->base_url, (int)len, reason);

    logmod_log(TRACE, ws->loggers.trace, "%s PONG (%zu bytes)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, YELLOW, "RCV"),
               len);

    if (ws->cbs.on_pong) ws->cbs.on_pong(ws->cbs.data, ws, reason, len);
}

static bool _ws_close(struct websockets *ws,
                      enum ws_close_reason code,
                      const char reason[]);

static int
_ws_check_action_cb(void *p_userdata,
                    curl_off_t dltotal,
                    curl_off_t dlnow,
                    curl_off_t ultotal,
                    curl_off_t ulnow)
{
    struct websockets *ws = p_userdata;
    int ret;
    (void)dltotal;
    (void)dlnow;
    (void)ultotal;
    (void)ulnow;

    pthread_mutex_lock(&ws->lock);
    switch (ws->action) {
    case WS_ACTION_BEGIN_CLOSE:
        logmod_log(WARN, ws->loggers.trace,
                   "Received pending %s, closing the connection ...",
                   ws_close_opcode_print(ws->pending_close.code));

        _ws_close(ws, ws->pending_close.code, ws->pending_close.reason);
    /* fall-through */
    case WS_ACTION_NONE:
    default:
        ret = 0;
        break;
    case WS_ACTION_END_CLOSE:
        /* END WEBSOCKETS CONNECTION */
        ret = 1;
        break;
    }
    ws->action = WS_ACTION_NONE;
    pthread_mutex_unlock(&ws->lock);

    return ret;
}

size_t _curl_ws_write_cb(char *ptr, size_t size, size_t nmemb, void *userdata);

static size_t
_curl_ws_header_cb(char *buffer, size_t size, size_t nitems, void *userdata)
{
    /* check if it has connected to call the callback */
    struct websockets *ws = userdata;
    const size_t realsize = size * nitems;

    if (realsize == 2 && memcmp(buffer, "\r\n", 2) == 0) {
        /* according to curl-websockets code, this should be where it has
         * connected. */
        ws_on_connect_cb(ws);

        return realsize;
    }

    return realsize;
}

/* init easy handle with some default opt */
static CURL *
_ws_ehandle_init(struct websockets *ws)
{
    CURL *new_ehandle = curl_easy_init();
    if (!new_ehandle) {
        logmod_log(FATAL, ws->loggers.trace,
                   "Failed to initialize WebSockets handler");
        return NULL;
    }

    /* set the URL */
    curl_easy_setopt(new_ehandle, CURLOPT_URL, ws->base_url);
    /* set the function to call when receiving headers */
    curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION, &_curl_ws_header_cb);
    curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, ws);
    /* set the function to call when receiving data */
    curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION, &_curl_ws_write_cb);
    curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, ws);

    /* set error buffer for capturing CURL error descriptions */
    curl_easy_setopt(new_ehandle, CURLOPT_ERRORBUFFER, ws->errbuf);
    /* enable follow redirections */
    curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
    /* enable progress function (a callback that executes constantly) */
    curl_easy_setopt(new_ehandle, CURLOPT_XFERINFOFUNCTION,
                     &_ws_check_action_cb);
    curl_easy_setopt(new_ehandle, CURLOPT_XFERINFODATA, ws);
    curl_easy_setopt(new_ehandle, CURLOPT_NOPROGRESS, 0L);

    logmod_log(INFO, ws->loggers.trace,
               "Initialized WebSockets handler (base_url: %s)", ws->base_url);

    return new_ehandle;
}

static bool
_ws_close(struct websockets *ws,
          enum ws_close_reason code,
          const char reason[])
{
    if (WS_DISCONNECTED == ws->status) {
        logmod_log(WARN, ws->loggers.trace,
                   "%s at SEND CLOSE : Connection already closed",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"));

        return false;
    }
    if (WS_DISCONNECTING == ws->status) {
        logmod_log(WARN, ws->loggers.trace,
                   "%s at SEND CLOSE : Close already taking place",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"));

        return false;
    }
    _ws_set_status_nolock(ws, WS_DISCONNECTING);

    size_t sent = 0;
    if (curl_ws_send(ws->ehandle, reason, strlen(reason), &sent, 0,
                     CURLWS_CLOSE)
        != CURLE_OK)
    {
        logmod_log(ERROR, ws->loggers.trace, "%s at SEND CLOSE(%d): %s",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"),
                   code, reason);
        return false;
    }

    logmod_log(WARN, ws->loggers.raw, "WS_SEND_CLOSE(%d) [%s] - %s\n%s", code,
               ws->loggers.trace->context_id, ws->base_url, reason);

    logmod_log(TRACE, ws->loggers.trace, "%s CLOSE (%s)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, GREEN, "SEND"),
               reason);

    return true;
}

enum ws_status
ws_get_status(struct websockets *ws)
{
    enum ws_status status;

    pthread_mutex_lock(&ws->lock);
    status = ws->status;
    pthread_mutex_unlock(&ws->lock);

    return status;
}

static void
default_on_ping(void *a, struct websockets *ws, const char *reason, size_t len)
{
    (void)a;
    ws_pong(ws, reason, len);
}

size_t
_curl_ws_write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    struct websockets *ws = userdata;
    size_t realsize;

again:
    realsize = size * nmemb;
    if (ws->bytesleft != 0) {
        /* the amount bytes left to complete the message is bigger
             than the entire received message right now, so we
             can safely put everything. */
        if (ws->bytesleft > realsize) {
            ws->msg_buf = realloc(ws->msg_buf, ws->msg_len + realsize + 1);
            memcpy(ws->msg_buf + ws->msg_len, ptr, realsize);
            ws->msg_buf[ws->msg_len + realsize] = '\0';
            ws->msg_len += realsize;
            ws->bytesleft -= realsize;

            return realsize;
        }
        else {
            /* the received amount of bytes is bigger than what we need, so we
                 we need to just copy what is from our frame, then let the next
                 be handled alone. The same happens when it is exactly what we
               need. */
            ws->msg_buf =
                realloc(ws->msg_buf, ws->msg_len + ws->bytesleft + 1);
            memcpy(ws->msg_buf + ws->msg_len, ptr, ws->bytesleft);
            ws->msg_buf[ws->msg_len + ws->bytesleft] = '\0';
            ws->msg_len += ws->bytesleft;

            if (ws->exp_msg_type == CURLWS_TEXT) {
                ws_on_text_cb(ws, ws->ehandle, ws->msg_buf, ws->msg_len);
            }
            else if (ws->exp_msg_type == CURLWS_BINARY) {
                ws_on_binary_cb(ws, ws->ehandle, ws->msg_buf, ws->msg_len);
            }
            else if (ws->exp_msg_type == CURLWS_PING) {
                ws_on_ping_cb(ws, ws->ehandle, ws->msg_buf, ws->msg_len);
            }
            else if (ws->exp_msg_type == CURLWS_PONG) {
                ws_on_pong_cb(ws, ws->ehandle, ws->msg_buf, ws->msg_len);
            }

            /* useless, but just to enphasize that we are done. */
            ws->exp_msg_type = 0;

            if (ws->bytesleft == realsize) {
                ws->bytesleft = 0;

                return realsize;
            }
            else {
                ptr += ws->bytesleft;
                realsize -= ws->bytesleft;
                ws->bytesleft = 0;

                goto again;
            }
        }
    }

    const struct curl_ws_frame *meta = curl_ws_meta(ws->ehandle);

    /* this is a fragmentated message, see FIN:
     * https://datatracker.ietf.org/doc/html/rfc6455#section-5.2 */
    if (meta->flags & CURLWS_CONT) {
        /* if there's more to be read (as fragments!), then we must wait. */
        ws->msg_buf = realloc(ws->msg_buf, ws->msg_len + meta->len + 1);
        memcpy(ws->msg_buf + ws->msg_len, ptr + meta->offset, meta->len);
        ws->msg_buf[ws->msg_len + meta->len] = '\0';
        ws->msg_len += meta->len;
        ws->is_continued = true;

        goto jump_cbs;
    }

    if (ws->is_continued && !(meta->flags & CURLWS_CONT)) {
        /* if this is the last fragment, we now can call the callback. */
        ws->msg_buf = realloc(ws->msg_buf, ws->msg_len + meta->len + 1);
        memcpy(ws->msg_buf + ws->msg_len, ptr + meta->offset, meta->len);
        ws->msg_buf[ws->msg_len + meta->len] = '\0';
        ws->msg_len += meta->len;
        ws->is_continued = false;
    }
    else {
        /* fill normally the buffer. */
        ws->msg_buf = realloc(ws->msg_buf, meta->len + 1);
        memcpy(ws->msg_buf, ptr + meta->offset, meta->len);
        ws->msg_buf[meta->len] = '\0';
        ws->msg_len = meta->len;
    }

    if (meta->bytesleft != 0) {
        ws->bytesleft = meta->bytesleft;
        ws->exp_msg_type = meta->flags;

        goto jump_cbs;
    }

    if (meta->flags & CURLWS_TEXT) {
        ws_on_text_cb(ws, ws->ehandle, ws->msg_buf, ws->msg_len);
    }
    else if (meta->flags & CURLWS_BINARY) {
        ws_on_binary_cb(ws, ws->ehandle, ws->msg_buf, ws->msg_len);
    }
    else if (meta->flags & CURLWS_PING) {
        ws_on_ping_cb(ws, ws->ehandle, ws->msg_buf, ws->msg_len);
    }
    else if (meta->flags & CURLWS_PONG) {
        ws_on_pong_cb(ws, ws->ehandle, ws->msg_buf, ws->msg_len);
    }
    else if (meta->flags & CURLWS_CLOSE) {
        uint8_t *code_ptr = (uint8_t *)ws->msg_buf;
        /* TODO: I don't think that's very portable */
        uint16_t code = (code_ptr[0] << 8) | code_ptr[1];

        /* 2 because it's a 2-byte (2 * 8 == 16) integer */
        ws_on_close_cb(ws, ws->ehandle, code, ws->msg_buf + 2,
                       ws->msg_len - 2);
    }

jump_cbs:

    /* it is not guaranteed that each buffer will contain only frame,
         so, if offset + length isn't equal to the length of the entire
         buffer, it has more than one, so it must be re-read starting
         from the end of this buffer. */
    if (realsize != meta->offset + meta->len) {
        ptr += meta->offset + meta->len;
        realsize -= meta->offset + meta->len;

        goto again;
    }
    else {
        return realsize;
    }
}

struct websockets *
ws_init(struct ws_callbacks *cbs, CURLM *mhandle, struct logmod *logmod)
{
    struct websockets *new_ws;

    if (!(new_ws = calloc(1, sizeof *new_ws))) {
        logmod_log(FATAL, NULL, "Couldn't allocate memory for WebSockets");
        return NULL;
    }
    if (!(new_ws->loggers.trace = logmod_get_logger(
              logmod ? logmod : &new_ws->logmod, "WEBSOCKETS")))
    {
        logmod_log(FATAL, NULL, "Couldn't get logger");
        return ws_cleanup(new_ws), NULL;
    }
    if (!(new_ws->loggers.raw = logmod_get_logger(
              logmod ? logmod : &new_ws->logmod, "WEBSOCKETS_RAW")))
    {
        logmod_log(FATAL, NULL, "Couldn't get logger");
        return ws_cleanup(new_ws), NULL;
    }

    if (cbs) new_ws->cbs = *cbs;
    new_ws->mhandle = mhandle;
    new_ws->headers = NULL;

    new_ws->msg_buf = NULL;
    new_ws->msg_len = 0;

    /** respond ping with a pong by default */
    if (!new_ws->cbs.on_ping) new_ws->cbs.on_ping = &default_on_ping;

    if (pthread_mutex_init(&new_ws->lock, NULL)) {
        logmod_log(FATAL, new_ws->loggers.trace,
                   "Couldn't initialize pthread mutex");
        return ws_cleanup(new_ws), NULL;
    }
    if (pthread_rwlock_init(&new_ws->rwlock, NULL)) {
        logmod_log(FATAL, new_ws->loggers.trace,
                   "Couldn't initialize pthread rwlock");
        return ws_cleanup(new_ws), NULL;
    }
    return new_ws;
}

void
ws_set_url(struct websockets *ws, const char base_url[])
{
    size_t len;

    pthread_mutex_lock(&ws->lock);

    if (!*ws->base_url) {
        logmod_log(INFO, ws->loggers.trace, "Websockets new URL: %s",
                   base_url);
    }
    else {
        logmod_log(INFO, ws->loggers.trace,
                   "Websockets redirecting:\n\tfrom: %s\n\tto: %s",
                   ws->base_url, base_url);
    }

    if ((len = snprintf(ws->base_url, sizeof(ws->base_url), "%s", base_url))
        < 0)
    {
        logmod_log(ERROR, ws->loggers.trace,
                   "Failed to set URL: %s due to snprintf error", base_url);
    }
    pthread_mutex_unlock(&ws->lock);
}

void
ws_cleanup(struct websockets *ws)
{
    static const pthread_mutex_t blank_lock;
    static const pthread_rwlock_t blank_rwlock;

    if (ws->ehandle) {
        curl_easy_cleanup(ws->ehandle);
    }
    if (ws->headers) {
        curl_slist_free_all(ws->headers);
    }
    if (ws->msg_buf) {
        free(ws->msg_buf);
    }
    if (memcmp(&ws->lock, &blank_lock, sizeof(pthread_mutex_t)) != 0) {
        pthread_mutex_destroy(&ws->lock);
    }
    if (memcmp(&ws->rwlock, &blank_rwlock, sizeof(pthread_rwlock_t)) != 0) {
        pthread_rwlock_destroy(&ws->rwlock);
    }
    logmod_cleanup(&ws->logmod);
    free(ws);
}

bool
ws_send_binary(struct websockets *ws, const char msg[], size_t msglen)
{
    logmod_log(INFO, ws->loggers.raw, "WS_SEND_BINARY [%s] - %s\n%.*s",
               ws->loggers.trace->context_id, ws->base_url, (int)msglen, msg);

    logmod_log(TRACE, ws->loggers.trace, "%s BINARY (%zu bytes)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, GREEN, "SEND"),
               msglen);

    if (WS_CONNECTED != ws->status) {
        logmod_log(ERROR, ws->loggers.trace,
                   "%s at SEND BINARY : No active connection",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"));
        return false;
    }

    size_t sent = 0;
    if (curl_ws_send(ws->ehandle, msg, msglen, &sent, 0, CURLWS_BINARY)
        != CURLE_OK)
    {
        logmod_log(
            ERROR, ws->loggers.trace, "%s at SEND BINARY (%zu bytes) %s",
            LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"), msglen,
            !*ws->errbuf ? curl_easy_strerror(CURLE_OK) : ws->errbuf);
        return false;
    }
    return true;
}

bool
ws_send_text(struct websockets *ws, const char text[], size_t len)
{
    logmod_log(INFO, ws->loggers.raw, "WS_SEND_TEXT [%s] - %s\n%.*s",
               ws->loggers.trace->context_id, ws->base_url, (int)len, text);

    logmod_log(TRACE, ws->loggers.trace, "%s TEXT (%zu bytes)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, GREEN, "SEND"),
               len);

    if (WS_CONNECTED != ws->status) {
        logmod_log(ERROR, ws->loggers.trace,
                   "%s at SEND TEXT : No active connection",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"));

        return false;
    }

    size_t sent = 0;
    if (curl_ws_send(ws->ehandle, text, len, &sent, 0, CURLWS_TEXT)
        != CURLE_OK)
    {
        logmod_log(ERROR, ws->loggers.trace, "%s at SEND TEXT (%zu bytes) %s",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"),
                   len,
                   !*ws->errbuf ? curl_easy_strerror(CURLE_OK) : ws->errbuf);

        return false;
    }

    return true;
}

bool
ws_ping(struct websockets *ws, const char *reason, size_t len)
{
    logmod_log(DEBUG, ws->loggers.raw, "WS_SEND_PING [%s] - %s\n%.*s",
               ws->loggers.trace->context_id, ws->base_url, (int)len, reason);

    logmod_log(TRACE, ws->loggers.trace, "%s PING (%zu bytes)",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, GREEN, "SEND"),
               len);

    if (WS_CONNECTED != ws->status) {
        logmod_log(ERROR, ws->loggers.trace, "%s to send PING (%zu bytes)",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"),
                   len);

        return false;
    }

    size_t sent = 0;
    if (curl_ws_send(ws->ehandle, "", 0, &sent, 0, CURLWS_PING) != CURLE_OK) {
        logmod_log(ERROR, ws->loggers.trace, "%s to send PING (%zu bytes) %s",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"),
                   len,
                   !*ws->errbuf ? curl_easy_strerror(CURLE_OK) : ws->errbuf);

        return false;
    }

    return true;
}

bool
ws_pong(struct websockets *ws, const char *reason, size_t len)
{
    logmod_log(DEBUG, ws->loggers.raw, "WS_SEND_PONG [%s] - %s\n%.*s",
               ws->loggers.trace->context_id, ws->base_url, (int)len, reason);

    logmod_log(TRACE, ws->loggers.trace, "%s PONG (%zu bytes) %s",
               LML(ws->loggers.trace, REGULAR, FOREGROUND, GREEN, "SEND"), len,
               !*ws->errbuf ? curl_easy_strerror(CURLE_OK) : ws->errbuf);

    if (WS_CONNECTED != ws->status) {
        logmod_log(ERROR, ws->loggers.trace, "%s to send PONG (%zu bytes) %s",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"),
                   len,
                   !*ws->errbuf ? curl_easy_strerror(CURLE_OK) : ws->errbuf);

        return false;
    }

    size_t sent = 0;
    if (curl_ws_send(ws->ehandle, "", 0, &sent, 0, CURLWS_PONG) != CURLE_OK) {
        logmod_log(ERROR, ws->loggers.trace, "%s to send PONG (%zu bytes) %s",
                   LML(ws->loggers.trace, REGULAR, FOREGROUND, RED, "Failed"),
                   len,
                   !*ws->errbuf ? curl_easy_strerror(CURLE_OK) : ws->errbuf);

        return false;
    }

    return true;
}

CURL *
ws_start(struct websockets *ws)
{
    memset(&ws->pending_close, 0, sizeof ws->pending_close);
    ws->action = WS_ACTION_NONE;

    if (ws_is_alive(ws)) {
        logmod_log(ERROR, ws->loggers.trace,
                   "Attempt to start WebSockets connection that is already "
                   "alive, please close it first");
        return NULL;
    }
    if (ws->ehandle != NULL) {
        logmod_log(ERROR, ws->loggers.trace,
                   "Attempt to reconnect without properly closing the "
                   "connection, likely a bug");
        return NULL;
    }

    if (!ws->ehandle) ws->ehandle = _ws_ehandle_init(ws);
    curl_multi_add_handle(ws->mhandle, ws->ehandle);

    _ws_set_status(ws, WS_CONNECTING);

    return ws->ehandle;
}

// TODO: split the cleanup logic from the shutdown logic
void
ws_end(struct websockets *ws)
{
    struct CURLMsg *curlmsg;
    int msgq = 0;

    /* tag as disconnecting */
    _ws_set_status(ws, WS_DISCONNECTING);

    /* read messages/informationals from the individual transfers */
    curlmsg = curl_multi_info_read(ws->mhandle, &msgq);
    if (curlmsg && ws->ehandle == curlmsg->easy_handle) {
        CURLcode ecode;

        switch (ecode = curlmsg->data.result) {
        case CURLE_OK:
        case CURLE_ABORTED_BY_CALLBACK: /* _ws_check_action_cb() */
            logmod_log(INFO, ws->loggers.trace,
                       "Disconnected gracefully (CURLE code: %d) %s", ecode,
                       !*ws->errbuf ? curl_easy_strerror(ecode) : ws->errbuf);
            break;
        case CURLE_READ_ERROR:
        default:
            logmod_log(ERROR, ws->loggers.trace,
                       "Disconnected abruptly (CURLE code: %d) %s", ecode,
                       !*ws->errbuf ? curl_easy_strerror(ecode) : ws->errbuf);
            break;
        }

        curl_multi_remove_handle(ws->mhandle, ws->ehandle);
    }

    /* reset for next iteration */
    *ws->errbuf = '\0';
    if (ws->ehandle) {
        curl_easy_cleanup(ws->ehandle);
        if (ws->headers) curl_slist_free_all(ws->headers);
        ws->ehandle = NULL;
    }

    _ws_set_status(ws, WS_DISCONNECTED);
}

bool
ws_easy_run(struct websockets *ws, uint64_t wait_ms, uint64_t *tstamp)
{
    int is_running = 0;
    CURLMcode mcode;
    /* unused but curl_multi_wait() demands it */
    int numfds = 0;

    /** update WebSockets concept of "now" */
    *tstamp = ws_timestamp_update(ws);

    /**
     * Perform Read/Write pending sockets activity (if any)
     * @note ws_close() and ws_send_text() are example of pending
     *        write activities
     * @note Callbacks such as ws_on_text(), ws_on_ping(), etc are
     *        example of pending read activities
     * @note Its worth noting that all websockets.c callbacks are
     *        inherently single-threaded. websockets.c doesn't create
     *        new threads.
     */
    if (CURLM_OK == (mcode = curl_multi_perform(ws->mhandle, &is_running))) {
        /* wait for some activity or timeout after "wait_ms" elapsed */
        mcode = curl_multi_wait(ws->mhandle, NULL, 0, wait_ms, &numfds);
    }

    if (mcode != CURLM_OK) CURLM_LOG(ws, mcode);

    return is_running != 0;
}

bool
ws_multi_socket_run(struct websockets *ws, uint64_t *tstamp)
{
    int is_running = 0;
    CURLMcode mcode;

    /** update WebSockets concept of "now" */
    *tstamp = ws_timestamp_update(ws);

    mcode = curl_multi_socket_all(ws->mhandle, &is_running);

    if (mcode != CURLM_OK) CURLM_LOG(ws, mcode);

    return is_running != 0;
}

uint64_t
ws_timestamp(struct websockets *ws)
{
    uint64_t now_tstamp;

    pthread_rwlock_rdlock(&ws->rwlock);
    now_tstamp = ws->now_tstamp;
    pthread_rwlock_unlock(&ws->rwlock);

    return now_tstamp;
}

uint64_t
ws_timestamp_update(struct websockets *ws)
{
    uint64_t now_tstamp;

    pthread_rwlock_wrlock(&ws->rwlock);
    now_tstamp = ws->now_tstamp = cog_timestamp_ms();
    pthread_rwlock_unlock(&ws->rwlock);

    return now_tstamp;
}

void
ws_close(struct websockets *ws,
         const enum ws_close_reason code,
         const char reason[],
         const size_t len)
{
    if (WS_DISCONNECTED == ws->status) {
        logmod_log(WARN, ws->loggers.trace,
                   "Attempt to close WebSockets connection that has already "
                   "ended");
        return;
    }

    logmod_log(WARN, ws->loggers.trace,
               "Attempting to close WebSockets connection with %s : %.*s",
               ws_close_opcode_print(code), (int)len, reason);

    pthread_mutex_lock(&ws->lock);
    ws->action = WS_ACTION_BEGIN_CLOSE;
    ws->pending_close.code = code;

    snprintf(ws->pending_close.reason, sizeof(ws->pending_close.reason),
             "%.*s", (int)len, reason);

    pthread_mutex_unlock(&ws->lock);
}

void
ws_add_header(struct websockets *ws, const char field[], const char value[])
{
    if (!ws_is_alive(ws)) {
        logmod_log(ERROR, ws->loggers.trace,
                   "Attempt to add header to WebSockets connection that is "
                   "not alive");
        return;
    }

    size_t header_len = strlen(field) + strlen(": ") + strlen(value) + 1;
    char *header = malloc(header_len);
    snprintf(header, header_len, "%s: %s", field, value);

    ws->headers = curl_slist_append(ws->headers, header);
    free(header);
}
