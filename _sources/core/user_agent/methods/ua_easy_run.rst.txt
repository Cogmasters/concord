..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h

========================================
ua_easy_run - Quickly perform a transfer
========================================

.. doxygenfunction:: ua_easy_run

Response handle
---------------

.. doxygentypedef:: ua_load_obj_cb
.. doxygenstruct:: ua_resp_handle

Example
-------

.. code:: c

   void done(char *body, size_t len, void *data)
   {
     printf("Success! Receive a response body of %zu bytes!\n", len);
   }

   void fail(char *body, size_t len, void *data)
   {
     printf("Failure! Receive a response body of %zu bytes!\n", len);
   }

   int main(void)
   {
     struct user_agent *ua = ua_init(NULL); 
     ua_set_url(ua, "https://www.example.com");

     struct ua_conn_attr conn_attr = { .method = HTTP_GET };
     struct ua_resp_handle handle = { .ok_cb = &done, .err_cb = &fail };

     ua_easy_run(ua, NULL, &handle, &conn_attr);

     ua_cleanup(ua);
   }
