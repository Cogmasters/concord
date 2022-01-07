..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/websockets.h

==================================================
ws_close_opcode_print - print CLOSE code as string
==================================================

.. doxygenfunction:: ws_close_opcode_print

Example
-------

.. code:: c

    void on_close(void *data,
                  struct websockets *ws,
                  struct ws_info *info,
                  enum ws_close_reason wscode,
                  const char reason[],
                  size_t len)
    {
      printf("%s\n", ws_close_opcode_print(wscode));
    }

    int main(void)
    {
      struct ws_callbacks cbs = { .on_close = &on_close };
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
