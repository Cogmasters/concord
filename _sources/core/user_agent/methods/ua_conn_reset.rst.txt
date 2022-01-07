..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h


======================================================
ua_conn_reset - reset a connection for immediate reuse
======================================================

.. doxygenfunction:: ua_conn_reset

Example
-------

.. code:: c

   struct user_agent *ua = ua_init(NULL); 
   ua_set_url(ua, "https://www.example.com");

   struct ua_conn_attr conn_attr = { .method = HTTP_GET };
   struct ua_conn *conn = ua_conn_start(ua);
   ua_conn_setup(conn, &conn_attr);

   bool retry = true;
   while (retry) {
     if (ua_conn_perform(conn) != CCORD_OK)
       break; /* internal error */

     struct ua_info info = { 0 };
     ua_info_extract(conn, &info);

     if (info.code >= 200 && info.code < 300) {
       retry = false;
     }
     else {
       /* transfer failed, reset conn's and try again */
       ua_conn_reset(conn);
     }
     ua_info_cleanup(&info);
   }

   ua_conn_stop(conn);
   ua_cleanup(ua);
