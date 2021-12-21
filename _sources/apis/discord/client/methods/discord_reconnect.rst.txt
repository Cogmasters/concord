..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

===================================================
discord_reconnect - reconnect a on-going connection
===================================================

.. doxygenfunction:: discord_reconnect

Example
-------

.. code:: c

    void on_reconnect(struct discord *client, const struct discord_message *msg)
    {
      discord_reconnect(client, true);
      log_info("Client will be reconnected");
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_set_on_command(client, "!reconnect", &on_reconnect);
      discord_run(client);
      discord_cleanup(client);
    }
