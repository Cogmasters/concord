..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

===================
Delete Own Reaction
===================

.. doxygenfunction:: discord_delete_own_reaction

Example
-------

.. code:: c
   
   discord_delete_own_reaction(client, msg->channel_id, msg->id, 0, "😄");
