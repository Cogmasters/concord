..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h

=======================================================
ua_info_extract - extract information on latest request
=======================================================

.. doxygenfunction:: ua_info_extract

Example
-------

.. code:: c

   struct user_agent *ua = ua_init(NULL); 
   ua_set_url(ua, "https://www.example.com");

   struct ua_conn_attr conn_attr = { .method = HTTP_GET };
   struct ua_conn *conn = ua_conn_start(ua);
   ua_conn_setup(conn, &conn_attr);

   if (CCORD_OK == ua_conn_perform(conn)) {
     struct ua_info info = { 0 };
     ua_info_extract(conn, &info);

     struct sized_buffer body = ua_conn_get_body(&info);

     printf("%.*s\n", (int)body.size, body.start);

     ua_info_cleanup(&info);
   }

   ua_conn_stop(conn);
   ua_cleanup(ua);

