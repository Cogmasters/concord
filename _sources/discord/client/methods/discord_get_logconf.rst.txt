..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

====================================================
discord_get_logconf - Get client's logging internals
====================================================

.. doxygenfunction:: discord_get_logconf

Example
-------

.. code:: c

    struct discord *client = discord_init(BOT_TOKEN);
    struct logconf *conf = discord_get_logconf(client);

    logconf_set_quiet(conf, false); // write logging to console
    logconf_set_level(conf, LOG_INFO);
    logconf_info(conf, "Logging from the DISCORD module");

    discord_run(client);

    discord_cleanup(client);
