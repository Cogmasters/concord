..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

Bulk Delete Messages
====================

.. doxygenfunction:: discord_bulk_delete_messages
Example
-------

.. code:: c

   u64_snowflake_t *messages[] = {
     &(u64_snowflake_t){ 1231231232131ULL }, // ficticious message ID
     &(u64_snowflake_t){ 3213213213213ULL }, // ficticious message ID
     NULL
   };

   discord_bulk_delete_messages(client, msg->channel_id, messages);
