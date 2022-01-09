..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

List Active Threads
===================

.. doxygenfunction:: discord_list_active_threads

Example
-------

.. code:: c

   struct discord_thread_response_body body;

   discord_list_active_threads(client, msg->channel_id, &body);
   
   if (body.threads)
     for (int i = 0; body.threads[i]; ++i)
       printf("Thread name: %s\n", body.threads[i]->name);
       
   discord_thread_response_body_cleanup(&body);
