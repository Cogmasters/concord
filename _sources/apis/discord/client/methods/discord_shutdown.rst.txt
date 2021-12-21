..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

=================================================
discord_shutdown - shutdown a on-going connection
=================================================

.. doxygenfunction:: discord_shutdown

Example
-------

.. code:: c

    void on_shutdown(struct discord *client, const struct discord_message *msg)
    {
      discord_shutdown(client);
      log_info("Shutdown has been triggered");
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_set_on_command(client, "!shutdown", &on_shutdown);
      discord_run(client);
      discord_cleanup(client);
    }
