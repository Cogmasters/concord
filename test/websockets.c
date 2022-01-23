#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

#include "websockets.h"

#include "log.h"

void
print_usage(char *prog)
{
    fprintf(
        stderr,
        "Usage: %s -u base-url -s start_test -e end-test -c config-file\n\n"
        "First install autobahn test suite (pip2 is required):\n"
        "\tpip2 install autobahntestsuite\n"
        "Then start autobahn:\n"
        "\twstest -m fuzzingserver\n\n"
        "Example:\n"
        "\t%s -u ws://localhost:9001 -s 1 -e 260\n"
        "\t%s -u wss://localhost:9001 -s 1 -e 10\n\n",
        prog, prog, prog);
    exit(EXIT_FAILURE);
}

void
on_connect_cb(void *data,
              struct websockets *ws,
              struct ws_info *info,
              const char *ws_protocols)
{
    (void)data;
    (void)ws;
    (void)info;
    log_info("Connected, WS-Protocols: '%s'", ws_protocols);
}

void
on_text_cb(void *data,
           struct websockets *ws,
           struct ws_info *info,
           const char *text,
           size_t len)
{
    (void)data;
    (void)ws;
    (void)info;
    log_trace("RECEIVE:\n%.*s", (int)len, text);
}

void
on_ping_cb(void *data,
           struct websockets *ws,
           struct ws_info *info,
           const char *reason,
           size_t len)
{
    (void)data;
    (void)ws;
    (void)info;
    log_trace("PING:\n%.*s", (int)len, reason);
    ws_pong(ws, NULL, "just pong", SIZE_MAX);
}

void
on_pong_cb(void *data,
           struct websockets *ws,
           struct ws_info *info,
           const char *reason,
           size_t len)
{
    (void)data;
    (void)ws;
    (void)info;
    log_trace("PONG:\n%.*s", (int)len, reason);
    ws_close(ws, WS_CLOSE_REASON_NORMAL, "close it!", SIZE_MAX);
}

void
on_close_cb(void *data,
            struct websockets *ws,
            struct ws_info *info,
            enum ws_close_reason wscode,
            const char *reason,
            size_t len)
{
    (void)data;
    (void)ws;
    (void)info;
    log_info("Closed connection (%d) : %.*s", wscode, (int)len, reason);
}

int
main(int argc, char *argv[])
{
    char *config_file = "../config.json";
    struct ws_callbacks cbs = {
        .on_connect = &on_connect_cb,
        .on_text = &on_text_cb,
        .on_ping = &on_ping_cb,
        .on_pong = &on_pong_cb,
        .on_close = &on_close_cb,
    };
    struct websockets *ws;
    struct ws_attr attr = { 0 };
    CURLM *mhandle = NULL;
    struct logconf conf;
    uint64_t tstamp;

    char *url = NULL;
    int opt;
    FILE *fp;

    while (-1 != (opt = getopt(argc, argv, "hu:c:"))) {
        switch (opt) {
        case 'u':
            url = strdup(optarg);
            break;
        case 'c':
            config_file = strdup(optarg);
            break;
        case 'h':
        default:
            print_usage(argv[0]);
            break;
        }
    }
    if (!url) print_usage(argv[0]);

    /* init logging */
    fp = fopen(config_file, "rb");
    logconf_setup(&conf, "TEST", fp);

    /* init websockets handle */
    mhandle = curl_multi_init();
    attr.conf = &conf;
    ws = ws_init(&cbs, mhandle, &attr);
    ws_set_url(ws, url, NULL);

    /* run the event-loop */
    ws_start(ws);
    while (true == ws_easy_run(ws, 5, &tstamp))
        ;
    ws_end(ws);

    ws_cleanup(ws);
    curl_multi_cleanup(mhandle);
    logconf_cleanup(&conf);
    fclose(fp);
}
