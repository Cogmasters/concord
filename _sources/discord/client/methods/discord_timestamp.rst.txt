..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

=======================================================================
discord_timestamp - get current timestamp (client's concept of ``now``)
=======================================================================

.. doxygenfunction:: discord_timestamp

Example
-------

.. code:: c

    #include <inttypes.h> // PRIu64

    // see https://discord.com/developers/docs/reference#message-formatting-formats
    void on_current_time(struct discord *client,
                         const struct discord_message *msg)
    {
      uint64_t now_ms = discord_timestamp(client);
      char text[256];
      sprintf(text, "<t:%" PRIu64 ">", now_ms / 1000);

      struct discord_create_message_params params = { .content = text };
      discord_create_message(client, msg->channel_id, &params, NULL);
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_set_on_command(client, "!current_time", &on_current_time);
      discord_run(client);
      discord_cleanup(client);
    }
