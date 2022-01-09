..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

Pin Message
===========

.. doxygenfunction:: discord_pin_message

Example
-------

.. code:: c

   struct discord_message ret;

   struct discord_create_message_params params = { .content = "I'm important, I need to get pinned!" };

   discord_create_message(client, msg->channel_id, &params, &ret);
   
   discord_pin_message(client, msg->channel_id, ret.id);
   
   discord_message_cleanup(&ret);
