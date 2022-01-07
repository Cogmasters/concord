..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

===================================================
discord_remove_intents - remove events to listen to
===================================================

.. doxygenfunction:: discord_remove_intents

Example
-------

.. code:: c

    struct discord *client = discord_init(BOT_TOKEN);
    // this will implicitly set intents for channel and direct messages
    discord_set_on_message_create(client, &on_msg);
    // keep only the channel messages intent
    discord_remove_intents(client, DISCORD_GATEWAY_DIRECT_MESSAGES);
    discord_run(client);
    discord_cleanup(client);
