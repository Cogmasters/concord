..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/websockets.h

=================================
ws_pong - send PONG control-frame
=================================

.. doxygenfunction:: ws_pong

Example
-------

.. code:: c

    void on_ping(void *data,
                 struct websockets *ws,
                 struct ws_info *info,
                 const char reason[],
                 size_t len)
    {
      char reason[] = "Who's there?";

      ws_pong(ws, NULL, reason, sizeof(reason));
    }

    int main(void)
    {
      struct ws_callbacks cbs = { .on_ping = &on_ping };
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

      ws_end(ws);

      ws_cleanup(ws);
      curl_multi_cleanup(mhandle);
    }
