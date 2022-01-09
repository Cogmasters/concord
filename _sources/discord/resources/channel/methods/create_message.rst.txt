..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

==============
Create Message
==============

.. doxygenfunction:: discord_create_message
.. doxygenstruct:: discord_create_message_params

Example
-------

.. code:: c
   
   struct discord_create_message_params params = { .content = "Pong!" };
   discord_create_message(client, msg->channel_id, &params, NULL);
