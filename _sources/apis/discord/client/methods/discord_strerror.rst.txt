..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

================================================================
discord_strerror() - return string describing ``ORCAcode`` value
================================================================

.. doxygengroup:: OrcaDiscordCodes
.. doxygenfunction:: discord_strerror

Example
-------

.. code:: c

    /* Attempt to send a message to a invalid channel (id 0) */
    void on_force_error(struct discord *client, 
                        const struct discord_message *msg)
    {
      ORCAcode code = discord_create_message(client, 0, NULL, NULL);
      log_error("%s", discord_strerror(code, client));
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_set_on_command(client, "!force_error", &on_force_error);
      discord_run(client);
      discord_cleanup(client);
    }
