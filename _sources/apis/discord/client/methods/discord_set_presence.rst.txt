..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

========================================
discord_set_presence - set client status
========================================

.. doxygenfunction:: discord_set_presence

Example
-------

.. code:: c

    struct discord *client = discord_init(BOT_TOKEN);
    
    struct discord_presence_status status = {
      .activities = (struct discord_activity *[]){
        &(struct discord_activity){
          .name = "Reading the docs...",
          .type = DISCORD_ACTIVITY_GAME
        },
        NULL // END OF ACTIVITIES LIST
      },
      .status = "idle",
      .since = discord_timestamp(client)
    };
    
    discord_set_presence(client, &status);
    discord_run(client);
    discord_cleanup(client);
