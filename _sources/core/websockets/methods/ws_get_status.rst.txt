..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/websockets.h

==============================================
ws_get_status - get client's connection status
==============================================

.. doxygenfunction:: ws_get_status

Wrappers
--------

.. doxygendefine:: ws_is_alive
.. doxygendefine:: ws_is_functional

Example
-------

.. code:: c

    CURLM *mhandle = curl_multi_init(); 
    struct websockets *ws = ws_init(&cbs, mhandle, NULL);
    ws_set_url(ws, "wss://example.com", NULL);

    /* run the event-loop */
    ws_start(ws);

    uint64_t tstamp;
    bool is_running;
    do {
      is_running = ws_easy_run(ws, 5, &tstamp);

      if (WS_CONNECTING == ws_get_status(ws)) {
        /* do something */
      }
    } while (is_running);

    ws_end(ws);

    ws_cleanup(ws);
    curl_multi_cleanup(mhandle);
