..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h

===================================================
ua_set_opt - Set connection's default configuration
===================================================

.. doxygenfunction:: ua_set_opt

Example
-------

.. code:: c

    void default_config(struct ua_conn *conn, void *data)
    {
      ua_conn_add_header(conn, "User-Agent", "my_application");
      ua_conn_add_header(conn, "Authorization", "Bearer xyzABC");
    }

    int main(void)
    {
      struct user_agent *ua = ua_init(NULL); 
      ua_set_url(ua, "https://www.example.com");
      ua_set_opt(ua, NULL, &default_config);

      struct ua_conn_attr conn_attr = { .method = HTTP_GET };

      ua_easy_run(ua, NULL, NULL, &conn_attr);

      ua_cleanup(ua);
    }
