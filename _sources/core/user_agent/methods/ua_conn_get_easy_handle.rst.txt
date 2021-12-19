..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h

================================================================
ua_conn_get_easy_handle - get the libcurl's easy_handle assigned
================================================================

.. doxygenfunction:: ua_conn_get_easy_handle

Example
-------

.. code:: c

   struct user_agent *ua = ua_init(NULL); 
   ua_set_url(ua, "https://www.example.com");

   struct ua_conn_attr conn_attr = { .method = HTTP_GET };
   struct ua_conn *conn = ua_conn_start(ua);
   ua_conn_setup(conn, &conn_attr);

   CURL *ehandle = ua_conn_get_easy_handle(conn);

   /* display verbose information for debugging */
   curl_easy_setopt(ehandle, CURLOPT_VERBOSE, 1L);

   ua_conn_easy_perform(conn);

   ua_conn_stop(conn);
   ua_cleanup(ua);
