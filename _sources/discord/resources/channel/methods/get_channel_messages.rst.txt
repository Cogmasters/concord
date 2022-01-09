..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

====================
Get Channel Messages
====================

.. doxygenfunction:: discord_get_channel_messages
.. doxygenstruct:: discord_get_channel_messages_params

Example
-------

.. code:: c
   
   struct discord_message **ret;
   
   discord_get_channel_messages(client, msg->channel_id, NULL, &ret);
   
   if (ret)
     for (int i = 0; ret[i]; ++i)
       printf("%s\n", ret[i]->content);
  
   discord_message_list_free(ret);
