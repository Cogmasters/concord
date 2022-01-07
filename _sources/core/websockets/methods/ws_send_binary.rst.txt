..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/websockets.h

==========================================
ws_send_binary - send binary control-frame
==========================================

.. doxygenfunction:: ws_send_binary

Example
-------

.. code:: c

    void on_connect(void *data,
                    struct websockets *ws,
                    struct ws_info *info,
                    const char *ws_protocols)
    {
      char text[] = "Hello from the other side";

      ws_send_binary(ws, NULL, text, sizeof(text));
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

      ws_end(ws);

      ws_cleanup(ws);
      curl_multi_cleanup(mhandle);
    }
