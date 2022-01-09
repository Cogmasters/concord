..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

Follow News Channel
===================

.. doxygenfunction:: discord_follow_news_channel
.. doxygenstruct:: discord_follow_news_channel_params

Example
-------

.. code:: c

   u64_snowflake_t id = 1231231232131ULL; // ficticious channel ID
   
   discord_follow_news_channel(client, id, NULL, NULL);
