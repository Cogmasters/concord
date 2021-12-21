..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

=============================================
discord_add_intents - add events to listen to
=============================================

.. doxygenfunction:: discord_add_intents

Example
-------

.. code:: c

    discord_event_scheduler_t scheduler(struct discord *client,
                                        struct sized_buffer *data,
                                        enum discord_gateway_events event)
    {
      switch (event) {
      case DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE:
      case DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE: {
        struct discord_message msg;
        discord_message_from_json(data->start, data->size, &msg);

        struct discord_create_message_params params = { 
          .content = "A message has been created or updated"
        };
        discord_create_message(client, msg.channel_id, &params, NULL);

        discord_message_cleanup(&msg);
      } break;
      }
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES 
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
      discord_set_event_scheduler(client, &scheduler);
      discord_run(client);
      discord_cleanup(client);
    }
