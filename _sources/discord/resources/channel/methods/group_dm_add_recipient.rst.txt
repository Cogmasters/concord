..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

Group DM Add Recipient
======================

.. doxygenfunction:: discord_group_dm_add_recipient
.. doxygenstruct:: discord_group_dm_add_recipient_params

Example
-------

.. code:: c

   u64_snowflake_t id = 1231231232131ULL; // ficticious channel ID
   
   discord_group_dm_add_recipient(client, id, 
                                  msg->author->id, 
                                  &(struct discord_group_dm_add_recipient_params){
                                    .access_token = "Access token of a user",
                                    .nick = "Nickname of the use that will be added"
                                  });
