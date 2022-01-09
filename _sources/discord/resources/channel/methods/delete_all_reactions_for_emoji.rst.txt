..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

==============================
Delete All Reactions For Emoji
==============================

.. doxygenfunction:: discord_delete_all_reactions_for_emoji

Example
-------

.. code:: c
   
   discord_create_reaction(client, msg->channel_id, msg->id, 0, "😄");

   discord_delete_all_reactions_for_emoji(client, msg->channel_id, msg->id, 0, "😄");
