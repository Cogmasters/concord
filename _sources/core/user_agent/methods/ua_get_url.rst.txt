..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h

====================================
ua_get_url - get user-agent base url
====================================

.. doxygenfunction:: ua_get_url

Example
-------

.. code:: c

   struct user_agent *ua = ua_init(NULL); 

   ua_set_url(ua, "https://www.example.com");

   /* should print https://www.example.com */
   printf("Base URL: %s\n", ua_get_url(ua));
