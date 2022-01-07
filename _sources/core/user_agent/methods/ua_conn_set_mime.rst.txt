..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/user-agent.h

=======================================================
ua_conn_set_mime - build a libcurl based multipart body
=======================================================

.. doxygenfunction:: ua_conn_set_mime

Example
-------

.. code:: c

    void to_mime(curl_mime *mime, void *data)
    {
      char *filename = (char *)data;
      curl_mimepart *part = curl_mime_addpart(mime);
      curl_mime_filedata(part, filename);
      curl_mime_type(part, "application/octet-stream");
      curl_mime_name(part, "txt_file");
    }

    int main(void)
    {
      struct user_agent *ua = ua_init(NULL); 
      ua_set_url(ua, "https://www.example.com");

      struct ua_conn_attr conn_attr = { .method = HTTP_MIMEPOST };
      struct ua_conn *conn = ua_conn_start(ua);
      ua_conn_setup(conn, &conn_attr);

      ua_conn_add_header(conn, "Content-Type", "multipart/form-data");

      char *filename = "foo.txt";
      ua_conn_set_mime(conn, &filename, &to_mime);

      ua_conn_easy_perform(conn);

      ua_conn_stop(conn);
      ua_cleanup(ua);
    }
