..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

=========
Scheduler
=========

The event scheduler gives power to the user for overriding or adding his own logic on top of Orca's default event-emitting behavior. This section outlines the scheduler built-in methods so that the user may take full advantage of it.

Thread Pool Work Scheduling
---------------------------

``Orca`` provides a threadpool that can be used to run the event callbacks from.

The default amount of threads in the threadpool is 2, and its maximum pending tasks queue length is 8. Those values may be changed by modifying their respective environment variables: ``ORCA_THREADPOOL_SIZE`` and ``ORCA_THREADPOOL_QUEUE_SIZE``.

.. note::
   The threadpool is shared amongst ALL clients initialized from the same proccess.

.. seealso::
   For a quick example check `Example`_.


Schedule Types
--------------

.. doxygenenum:: discord_event_scheduler

Set Event Scheduler
-------------------

.. doxygenfunction:: discord_set_event_scheduler


Example
-------

.. code:: c

    discord_event_scheduler_t scheduler(struct discord *client,
                                        struct discord_user *bot,
                                        struct sized_buffer *data,
                                        enum discord_gateway_events event)
    {
      switch (event) {
      case DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE:
        return DISCORD_EVENT_WORKER_THREAD;
      case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE:
        return DISCORD_EVENT_IGNORE;
      case DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE: {
        struct discord_channel channel;
        discord_channel_from_json(data->start, data->size, &channel);

        log_info("Channel %s has been created!", channel.name);

        discord_channel_cleanup(&channel);
      } return DISCORD_EVENT_IGNORE;
      case DISCORD_GATEWAY_EVENTS_READY:
      default:
        return DISCORD_EVENT_MAIN_THREAD;
      }
    }

    int main(void)
    {
      // increase threadpool to 4 threads
      setenv("ORCA_THREADPOOL_SIZE", "4", 1);
      // increase threadpool queue length to 128 slots
      setenv("ORCA_THREADPOOL_QUEUE_SIZE", "128", 1);
      struct discord *client = discord_init(TOKEN);

      discord_set_event_scheduler(client, &scheduler);

      // Assigned to main-thread at scheduler() (single-threaded execution)
      discord_set_on_ready(client, &on_ready);
      // Assigned to a worker thread at scheduler() (parallel execution)
      discord_set_on_message_create(client, &on_message_create);
      // Will ignore the callback at scheduler()
      discord_set_on_message_delete(client, &on_message_delete);
      // Will ignore the callback at scheduler(), and include user logic for
      // printing the new channel
      discord_set_on_channel_create(client, &on_channel_create);

      discord_run(client);
    }
