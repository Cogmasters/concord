..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

List Private Archived Threads
=============================

.. doxygenfunction:: discord_list_private_archived_threads

Example
-------

.. code:: c

   struct discord_thread_response_body ret;

   discord_list_private_archived_threads(client, msg->channel_id, 0, 5, &ret);
   
   if (ret.threads)
     for (int i = 0; ret.threads[i]; ++i)
       printf("Thread name: %s\n", ret.threads[i]->name);
       
   discord_thread_response_body_cleanup(&ret);
