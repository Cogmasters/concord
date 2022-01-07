..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

======================================================================
discord_async_next - execute immediate request function asynchronously
======================================================================

.. doxygenstruct:: discord_async_ret
.. doxygentypedef:: discord_on_done
.. doxygenstruct:: discord_async_err
.. doxygentypedef:: discord_on_fail
.. doxygenstruct:: discord_async_attr
.. doxygenfunction:: discord_async_next

Example
-------

.. code:: c

    void on_msg_done(struct discord *client, struct discord_async_ret *ret)
    {
      const struct discord_message *msg = ret->ret;

      log_info("Sent: %s", msg->content);
    }

    void on_msg_fail(struct discord *client, struct discord_async_err *err)
    {
      log_error("%s", discord_strerror(err->code, client));
    }

    void on_start(struct discord *client, const struct discord_message *msg)
    {
      struct discord_async_attr attr = { .done = &on_msg_done,
                                         .fail = &on_msg_fail };
      struct discord_create_message_params params = { 0 };

      // next request is low priority (enqueued last)
      attr.high_p = false;
      discord_async_next(client, &attr);
      params.content = "Request A";
      discord_create_message(client, msg->channel_id, &params, NULL);

      // next request is high priority (enqueued first)
      attr.high_p = true;
      discord_async_next(client, &attr);
      params.content = "Request B";
      discord_create_message(client, msg->channel_id, &params, NULL);

      // next request is low priority (enqueued last)
      attr.high_p = false;
      discord_async_next(client, &attr);
      params.content = "Request C";
      discord_create_message(client, msg->channel_id, &params, NULL);

      // next request defaults to the default blocking behavior,
      // because its missing a discord_async_next() match
      params.content = "Request D";
      discord_create_message(client, msg->channel_id, &params, NULL);
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_set_on_command(client, "!start", &on_start);
      discord_run(client);
      discord_cleanup(client);
    }
