..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

===================
Get Channel Message
===================

.. doxygenfunction:: discord_get_channel_message

Example
-------

.. code:: c

   struct discord_message ret1;
   struct discord_message ret2;

   struct discord_create_message_params params = { .content = "Hey!" };

   discord_create_message(client, msg->channel_id, &params, &ret1);
   
   discord_get_channel_message(client, msg->channel_id, ret1.id, &ret2);
   
   printf("I said: %s", ret2.content);
   
   discord_message_cleanup(&ret1);
   discord_message_cleanup(&ret1);
