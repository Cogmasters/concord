..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

=======================================================================
discord_config_init - create a Discord client handle from a config file
=======================================================================

.. doxygenfunction:: discord_config_init

Sample ``config.json``
----------------------

.. code:: json

  {
    "logging": {
      "level": "trace",
      "filename": "bot.log",
      "quiet": false,
      "overwrite": true,
      "use_color": true,
      "http": {
        "enable": true,
        "filename": "http.log"
      },
      "disable_modules": [
        "WEBSOCKETS", 
        "USER_AGENT",
        "DISCORD_HTTP",
      ]
    },
    "discord": {
      "token": "YOUR-BOT-TOKEN",
      "default_prefix": {
        "enable": true,
        "prefix": "!"
      }
    }
  }

Example
-------

.. code:: c

    void on_ready(struct discord *client) 
    {
      log_info("Up and running!");
    }

    int main(void)
    {
      struct discord *client = discord_config_init("config.json");
      discord_set_on_ready(client, &on_ready);
      discord_run(client);
      discord_cleanup(client);
    }
