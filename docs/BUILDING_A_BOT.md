# Building a Basic Ping-Pong Bot

Building a bot is pretty simple with this library, but there are some basic things you have to do before starting:

1. Make sure you have all the build dependencies. The dependencies are listed in the [README](/README.md) of this project.

2. Make sure that you have a bot token. If you do not [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) has instructions on building a bot. Put your bot token in `bot.config`, replacing the `YOUR-BOT-TOKEN` with your own token. We will be using this file as needed.

# Ping-pong bot code

The entire code of ping-pong bot is below. We will go over it in further down:
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

void on_ready(discord::client *client, const user::data *self)
{
  fprintf(stderr, "\n\nPingPong-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_message_create(
    discord::client *client,
    const user::data *self,
    const message::data *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;
  // make sure it doesn't echoes itself
  if (0 == strcmp(self->username, msg->author->username))
    return;

  if (0 == strcmp(msg->content, "ping"))
    message::create(client, msg->channel_id, "pong");
  else if (0 == strcmp(msg->content, "pong"))
    message::create(client, msg->channel_id, "ping");

  (void)self;
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  global_init();

  discord::client *client = fast_init(config_file);
  assert(NULL != client);

  setcb_ready(client, &on_ready);
  setcb_message_create(client, &on_message_create);

  run(client);

  cleanup(client);

  global_cleanup();
}
```

# Setting up the bot settings

You can set it automatically, by using the `fast_init()` function when
initializing a new client. Simply by passing the bot settings file as parameter:
```c++
  // using namespace discord;

  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  client *client = fast_init(config_file);
  assert(NULL != client);
```

Or you can do it manually, and:
```c++
  // using namespace discord;

  static struct bot_settings settings;

  if (argc > 1)
    bot_settings_init(&settings, argv[1]);
  else
    bot_settings_init(&settings, "bot.config");

  client *client = init(settings.discord.token);
  assert(NULL != client);

  if (settings.logging.dump_json.enable)
    dump_json(client, settings.logging.dump_json.filename);
  if (settings.logging.dump_curl.enable)
    dump_curl(client, settings.logging.dump_curl.filename);
```

## struct bot_settings
`struct bot_settings` : the structure of the settings json once given by `bot_settings_init()`. Check [bot.config](/bot.config) for an example.

## bot_settings_init
`bot_settings_init(struct *bot_settings, char[])` : initializes the struct bot_settings to the contents of the file char[] given.
|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct* bot_settings| the setting struct to use to hold the bot settings|
|char []| the file path to the json given to bot_settings|

## discord::global_init
`discord::global_init()` : the function to run before using any other functions, it will set some important global configurations from curl

## discord::fast_init
`discord::fast_init(char[])` : function for initializing the bot using some presets

Returns `discord::client`: the client structure

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the name of the bot settings file|

## discord::init
`discord::init(char[])` : function for initializing the bot with a token

Returns `discord::client`: the client structure

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the bot token string|

## discord::dump_json
`discord::dump_json(discord::client*, char[])`: function for dumping the json

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord::client| the client stucture |
|char[]| the file name of where to dump the json|

## discord::dump_curl
`discord::dump_curl(discord::client*, char[])`: function for dumping the curl info

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord::client| the client stucture |
|char[]| the file name of where to dump the curl info|

# Starting up the bot
```c++
discord::setcb_ready(discord::client*, &on_ready);
discord::setcb_message_create(discord::client*, &on_message_create);

discord::run(discord::client*);
```

## discord::setcb_ready
`discord::setcb_ready(discord::client*, callback*)`: calls the function when bot has started up and is ready

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord::client| the client stucture |
|callback*| the function to run when bot is ready. Must be of structure <br>```void function(discord::client *client, const discord::user::data *self)```|

## discord::setcb_message_create
`discord::setcb_message_create(discord::client*, callback*)`: calls the function when bot has detected that a user has sent a message

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord::client| the client stucture |
|callback*| the function to run when a message is created. Must be of structure <br>```void function(discord_t *client, const discord_user_t *self, const discord_message_t *message)```|

## discord::run
`discord::run(discord::client*)`: the functions that establishes starts the bot by establishing a connection to Discord, runs until error

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord::client| the client stucture  |


# Cleaning up the bot

```c
  discord::cleanup(discord::client);

  discord::global_cleanup();
```

## discord::cleanup
`discord::cleanup(discord::client)`: function that cleans up bot resources

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord::client| the client stucture |

## discord::global_cleanup
`discord::global_cleanup()`: function that cleans up resources set by `discord::global_init()`

# Running the bot

Use `make -f discord.mk` for compiling the source code.

Then run the bot by typing `./bot-ping-pong.exe` on your terminal.

#### Testing the bot
Type "ping" or "pong" in any public channel that the bot is part of.

#### Closing the bot
Close the Terminal that bot-ping-pong is running or press "Ctrl-C" to kill it.
