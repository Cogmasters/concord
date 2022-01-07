..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h

==============
HTTP - general
==============

Methods
-------

.. doxygenenum:: http_method
.. doxygenfunction:: http_method_print
.. doxygenfunction:: http_method_eval

Status Code
-----------

.. doxygengroup:: HttpStatusCode
.. doxygenfunction:: http_code_print
.. doxygenfunction:: http_reason_print

Example
-------

.. code:: c

   struct user_agent *ua = ua_init(NULL); 
   ua_set_url(ua, "https://www.example.com");

   struct ua_info info = { 0 };
   struct ua_conn_attr conn_attr = { .method = HTTP_GET };

   printf("Send %s\n", http_method_print(conn_attr.method));

   ua_easy_run(ua, &info, NULL, &conn_attr);

   printf("HTTP Status name: %s\n", http_code_print(info.httpcode));
   printf("HTTP Status reason %s\n", http_reason_print(info.httpcode));

   ua_cleanup(ua);
