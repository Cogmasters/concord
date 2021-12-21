..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

========================================================
discord_set_data - save a pointer to user arbitrary data
========================================================

.. doxygenfunction:: discord_set_data

Example
-------

.. code:: c

    void on_ready(struct discord *client) 
    {
      char *text = discord_get_data(client);
      log_trace("%s", text);
    }

    int main(void)
    {
      struct discord *client = discord_init(BOT_TOKEN);
      discord_set_on_ready(client, &on_ready);

      char text[] = "Hello world!";
      discord_set_data(client, text);

      discord_run(client);

      discord_cleanup(client);
    }
