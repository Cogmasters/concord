..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

======================================================
discord_set_prefix - set a default prefix for commands
======================================================

.. doxygenfunction:: discord_set_prefix

Example
-------

.. code:: c

    struct discord *client = discord_init(BOT_TOKEN);
    discord_set_prefix(client, "#!");
    // triggers at '#!foo'
    discord_set_on_command(client, "foo", &callback1);
    // triggers at '#!?bar'
    discord_set_on_command(client, "?bar", &callback2);
    // triggers at '#!_.baz'
    discord_set_on_command(client, "_.baz", &callback3);
    discord_run(client);
    discord_cleanup(client);
