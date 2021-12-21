..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

======================================================================
discord_async_next - execute immediate request function asynchronously
======================================================================

.. doxygentypedef:: discord_on_done
.. doxygenstruct:: discord_async_attr
.. doxygenfunction:: discord_async_next

Example
-------

.. code:: c

    void on_msg_done(struct discord *client, const void *data)
    {
      const struct discord_message *msg = data;

      log_info("Message %" PRIu64 " was created successfully!", msg->id);
    }

    void on_async(struct discord *client, const struct discord_message *msg)
    {
      struct discord_async_attr attr = { .done = &on_msg_done };
      struct discord_create_message_params params = { 0 };

      // next request is low priority (enqueued last)
      attr.high_p = false;
      discord_async_next(client, &attr);
      params.content = "Third";
      discord_create_message(client, msg->channel_id, &params, NULL);

      // next request is high priority (enqueued first)
      attr.high_p = true;
      discord_async_next(client, &attr);
      params.content = "Second";
      discord_create_message(client, msg->channel_id, &params, NULL);

      // next request is low priority (enqueued last)
      attr.high_p = false;
      discord_async_next(client, &attr);
      params.content = "Fourth";
      discord_create_message(client, msg->channel_id, &params, NULL);

      // next request defaults to the default blocking behavior,
      // because its missing a discord_async_next() match
      params.content = "First";
      discord_create_message(client, msg->channel_id, &params, NULL);
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_set_on_command(client, "!do_async", &on_async);
      discord_run(client);
      discord_cleanup(client);
    }
