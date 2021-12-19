..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h

========================================
ua_cleanup - Cleanup a User-Agent handle
========================================

.. doxygenfunction:: ua_cleanup

Example
-------

.. code:: c

   struct user_agent *ua = ua_init(NULL); 
   ua_set_url(ua, "https://www.example.com");

   struct ua_conn_attr conn_attr = { .method = HTTP_GET };

   ua_easy_run(ua, NULL, NULL, &conn_attr);

   ua_cleanup(ua);

