..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

===============
Event Scheduler
===============

By default every event emitter will execute its callback from the event-loop thread, meaning that during the callback execution the bot will be blocked from reacting to any other events, which quickly becomes a nuisance as your bot increases in size. This sections outlines the built-in methods for providing scalability to your application, so each event may be dealt with asychronously.

Thread Pool Work Scheduling
---------------------------

``Orca-Discord`` provides a threadpool which can be used to run the events callbacks.

The default size for the threadpool and its queue are 2 and 8 respectively, and those can be changed by settings the value of their environment variables counterparts: ``ORCA_THREADPOOL_SIZE`` and ``ORCA_THREADPOOL_QUEUE_SIZE``.

.. note::
   The threadpool is shared amongst all clients.

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

    enum discord_event_scheduler
    scheduler(struct discord *client, 
              struct discord_user *bot,
              struct sized_buffer *event_data,
              enum discord_gateway_events event)
    {
      switch (event) {
      case DISCORD_GATEWAY_EVENTS_READY:
        return DISCORD_EVENT_MAIN_THREAD;
      case DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE:
        return DISCORD_EVENT_WORKER_THREAD;
      default:
        return DISCORD_EVENT_IGNORE;
      }
    }

    int main(void)
    {
      setenv("ORCA_THREADPOOL_SIZE", "4", 1);
      setenv("ORCA_THREADPOOL_QUEUE_SIZE", "128", 1);
      struct discord *client = discord_init(TOKEN);

      discord_set_event_scheduler(client, &scheduler);

      /* Assigned to main-thread at scheduler() (single-threaded) */
      discord_set_on_ready(client, &on_ready);
      /* Assigned to be executed in a worker thread at scheduler() */
      discord_set_on_message_create(client, &on_message_create);
      /* The following will be made to be ignored at scheduler(),
         and won't trigger any callback */
      discord_set_on_message_delete(client, &on_message_delete);
      discord_set_on_channel_create(client, &on_channel_create);

      discord_run(client);
    }
