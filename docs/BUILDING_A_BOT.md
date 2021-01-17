# Building a Basic Ping-Pong Bot

Building a bot is pretty simple with this library, but there are some basic things you have to do before brefore starting:

1. Make sure you have all the build dependencies. The dependencies are listed in the [README](/README.md) of this project.

2. Make sure that you have a bot token. If you do not [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) has instructions on building a bot. But your bot token in `bot.config`, replacing the `YOUR-BOT-TOKEN` with your own token. We will be using this file as needed.

# Ping-pong bot code

The entire code of ping-pong bot is below. We will go over it in further down:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>
#include "settings.h"


void on_ready(discord_t *client, const discord_user_t *self)
{
  fprintf(stderr, "\n\nEcho-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_message_create(
    discord_t *client,
    const discord_user_t *self,
    const discord_message_t *message)
{
  // make sure bot doesn't echoes other bots
  if (true == message->author->bot)
    return;

  char response[] = "pong", reaction[] = "ping";

  if (0 == strcmp(message->content, reaction)){
    discord_send_message(client, message->channel_id, response);
  }
}

int main(int argc, char *argv[])
{
  static struct bot_settings settings;

  if (argc > 1)
    bot_settings_init(&settings, argv[1]);
  else
    bot_settings_init(&settings, "bot.config");

  discord_global_init();

  discord_t *client = discord_init(settings.discord.token);
  assert(NULL != client);

  if (settings.logging.dump_json.enable)
    discord_dump_json(client, settings.logging.dump_json.filename);
  if (settings.logging.dump_curl.enable)
    discord_dump_curl(client, settings.logging.dump_curl.filename);

  discord_setcb_ready(client, &on_ready);
  discord_setcb_message_create(client, &on_message_create);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
```

# Setting up the bot settings

```c
  static struct bot_settings settings;

  if (argc > 1)
    bot_settings_init(&settings, argv[1]);
  else
    bot_settings_init(&settings, "bot.config");
```

## struct bot_settings
`struct bot_settings` : the structure of the settings json once given by `bot_settings_init()`. Check [bot.config](/bot.config) for an example.

## bot_settings_init
`bot_settings_init(struct *bot_settings, char[])` : initializes the struct bot_settings to the contents of the file char[] given.
|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct* bot_settings| the setting struct to use to hold the bot settings|
|char []| the file path to the json given to bot_settings|

# Setting up the bot itself

```c
  discord_global_init();

  discord_t *client = discord_init(settings.discord.token);
  assert(NULL != client);

  if (settings.logging.dump_json.enable)
    discord_dump_json(client, settings.logging.dump_json.filename);
  if (settings.logging.dump_curl.enable)
    discord_dump_curl(client, settings.logging.dump_curl.filename);
```
## discord_global_init
`discord_global_init()` : the funciton to to run before initializing the bot

## discord_init
`discord_init(char[])` : function for initialization of the bot using the bot token

Returns `discord_t`: the client structure

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the bot token string|

## discord_dump_json
`discord_dump_json(discord_t, char[])`: function for dumping the json

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord_t| the client stucture given by discord_init|
|char[]| the file name of where to dump the json|

## discord_dump_curl
`discord_dump_curl(discord_t, char[])`: function for dumping the curl info

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord_t| the client stucture given by discord_init|
|char[]| the file name of where to dump the curl info|

# Starting up the bot
```c
discord_setcb_ready(client, &on_ready);
discord_setcb_message_create(client, &on_message_create);

discord_run(client);
```

## discord_setcb_ready
`discord_setcb_ready(discord_t, *function)`: calls the function when bot has started up and is ready

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord_t| the client stucture given by discord_init|
|*function| the function to run when bot is ready. Must be of structure <br>```void function(discord_t *client, const discord_user_t *self)```|

## discord_setcb_message_create
`discord_setcb_message_create(discord_t, *function)`: calls the function when bot has detected that a user has sent a message

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord_t| the client stucture given by discord_init|
|*function| the function to run when bot is ready. Must be of structure <br>```void function(discord_t *client, const discord_user_t *self, const discord_message_t *message)```|

## discord_run
`discord_run(discord_t)`: function that starts the discord bot itself, runs until error

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord_t| the client stucture given by discord_init|


# Cleaning up the bot

```c
  discord_cleanup(client);

  discord_global_cleanup();
```

## discord_cleanup
`discord_cleanup(discord_t)`: function that cleans up the bot after it runs

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord_t| the client stucture given by discord_init|

## discord_global_cleanup
`discord_global_cleanup()`: function that cleans up the bot after using `discord_global_init()`

# running the bot

For `ping-pong-bot.c`, use `make ping-pong-bot` to compile the bot.
Change the makefile appropriately when needed.