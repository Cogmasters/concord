..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/websockets.h

===============================================
ws_timestamp - get WebSockets current timestamp
===============================================

.. doxygenfunction:: ws_timestamp

Example
-------

.. code:: c

    uint64_t time_start, time_end;

    void on_connect(void *data,
                    struct websockets *ws,
                    struct ws_info *info,
                    const char *ws_protocols)
    {
      /* get timestamp of when connection began */
      time_start = ws_timestamp(ws);
    }

    void on_close(void *data,
                  struct websockets *ws,
                  struct ws_info *info,
                  enum ws_close_reason wscode,
                  const char *reason,
                  size_t len)
    {
      /* get timestamp of when connection ended */
      time_end = ws_timestamp(ws);
    }

    int main(void)
    {
      struct ws_callbacks cbs = { .on_connect = &on_connect };
      CURLM *mhandle = curl_multi_init(); 
      struct websockets *ws = ws_init(&cbs, mhandle, NULL);
      ws_set_url(ws, "wss://example.com", NULL);

      /* run the event-loop */
      ws_start(ws);

      uint64_t tstamp;
      bool is_running;
      do {
        is_running = ws_easy_run(ws, 5, &tstamp);
      } while (is_running);

      printf("Connection lasted %ld milliseconds\n", (long)(time_end - time_start));

      ws_end(ws);

      ws_cleanup(ws);
      curl_multi_cleanup(mhandle);
    }
