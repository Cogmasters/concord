#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "websockets.h"
#include "log.h"

void print_usage(char *prog)
{
  fprintf(stderr,
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

void on_connect_cb(void *data,
                   struct websockets *ws,
                   struct ws_info *info,
                   const char *ws_protocols)
{
  (void)data;
  (void)ws;
  (void)info;
  log_info("Connected, WS-Protocols: '%s'", ws_protocols);
}

void on_text_cb(void *data,
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

void on_ping_cb(void *data,
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

void on_pong_cb(void *data,
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

void on_close_cb(void *data,
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

int main(int argc, char *argv[])
{
  char *config_file = "../config.json";
  char *url = NULL;
  int start = 0, end = 10;
  int opt;
  FILE *fp;
  struct logconf conf;
  struct websockets *ws;
  _Bool is_running = false;
  struct ws_callbacks cbs = { .on_connect = &on_connect_cb,
                              .on_text = &on_text_cb,
                              .on_ping = &on_ping_cb,
                              .on_pong = &on_pong_cb,
                              .on_close = &on_close_cb };

  while (-1 != (opt = getopt(argc, argv, "hu:s:e:c:"))) {
    switch (opt) {
    case 'u': url = strdup(optarg); break;
    case 's': start = strtol(optarg, NULL, 10); break;
    case 'e': end = strtol(optarg, NULL, 10); break;
    case 'c': config_file = strdup(optarg); break;
    case 'h':
    default: print_usage(argv[0]); break;
    }
  }
  if (!url) print_usage(argv[0]);

  /* init logging */
  fp = fopen(config_file, "rb");
  logconf_setup(&conf, "TEST", fp);

  /* init websockets handle */
  ws = ws_init(&cbs, &conf);
  ws_set_url(ws, url, NULL);

  /* run the event-loop */
  ws_start(ws);
#if 0 /* set custom headers */
  ws_reqheader_add(ws, "Authorization", "foo");
#endif
  while (1) {
    ws_perform(ws, &is_running, 5);
    if (!is_running) break; /* exit event loop */

    /* connection is established */
  }

  ws_cleanup(ws);
  logconf_cleanup(&conf);
  fclose(fp);
}
