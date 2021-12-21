..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

=========================================================
discord_get_ping - get latency between client and Discord
=========================================================

.. doxygenfunction:: discord_get_ping

Example
-------

.. code:: c

    void on_ping(struct discord *client, const struct discord_message *msg)
    {
      char text[256];
      sprintf(text, "Ping! (%d ms)", discord_get_ping(client));

      struct discord_create_message_params params = { .content = text };
      discord_create_message(client, msg->channel_id, &params, NULL);
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_set_on_command(client, "!ping", &on_ping);
      discord_run(client);
      discord_cleanup(client);
    }
