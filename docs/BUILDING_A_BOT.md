# Building a Basic Ping-Pong Bot

Building a bot is pretty simple with this library, but there are some basic things you have to do before starting:

1. Make sure you have all the build dependencies. The dependencies are listed in the [README](/README.md) of this project.

2. Make sure that you have a bot token. If you do not [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) has instructions on building a bot. Put your bot token in `bot.config`, replacing the `YOUR-BOT-TOKEN` with your own token. We will be using this file as needed.

# Ping-pong bot code

The entire code of ping-pong bot is below. We will go over it in further down:
```c++
#include <stdio.h>
#include <stdlib.h>
#include <libdiscord.h>

void on_ready(discord::client *client, const discord::user::data *self)
{
  fprintf(stderr, "\n\nPingPong-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_ping(
    discord::client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord::channel::message::create::params params = {
    .content = "pong"
  };

  discord::channel::message::create::run(client, msg->channel_id, &params, NULL);

  (void)me;
}

void on_pong(
    discord::client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord::channel::message::create::params params = {
    .content = "ping"
  };

  discord::channel::message::create::run(client, msg->channel_id, &params, NULL);

  (void)me;
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  discord::global_init();

  discord::client *client = discord::config_init(config_file);

  discord::setcb(client, READY, &on_ready);
  discord::setcb_command(client, "ping", &on_ping);
  discord::setcb_command(client, "pong", &on_pong);

  discord::run(client); // run the discord websockets

  discord::cleanup(client);

  discord::global_cleanup();
}
```

# Setting up the bot settings

You can set it automatically by initializing it with the bot.config file located at orca/bots folder. Simply give the file path as a parameter of discord::config_init(), as following:
```c++
  discord::client *client = discord::config_init("bot.config");
```
Or you can initialize directly with discord::init() by giving it the bot token, like so:
```c++
  discord::client *client = discord::init("BOT_TOKEN_HERE");
```

## discord::global_init
`discord::global_init()` : the function to run before using any other functions, it will set some important global configurations from curl

## discord::config_init
`discord::config_init(char[])` : function for initializing the bot using some presets

Returns `discord::client`: the client structure

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the name of the bot config file|

## discord::init
`discord::init(char[])` : function for initializing the bot with a token

Returns `discord::client`: the client structure

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the bot token string|

# Starting up the bot
```c++
discord::setcb(client, READY, &on_ready);
discord::setcb_command(discord::client*, "ping", &on_ping);
discord::setcb_command(discord::client*, "pong", &on_pong);

discord::run(discord::client*);
```

## discord::setcb
`discord::setcb(discord::client*, enum callback_opt, callback*)`: calls callback function when `enum callback_opt` event is triggered

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord::client| the client stucture |
|enum callback_opt| The event expected to trigger a callback response |
|callback*| the function callback to run when its corresponding event is triggered (see discord-common.h for callback definitions) |

## discord::setcb_command
`discord::setcb_command(discord::client*, char[], message_cb*)`: executes callback function when `char[]` command is triggered on chat

|Member Parameters|Description                |
|:----------------|:--------------------------|
|discord::client| the client stucture |
|char[]| The chat command expected to trigger a callback response |
|message_cb*| the message type function callback to run when its corresponding event is triggered (see discord-common.h for message_cb definitions) |

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

Use `make bot` for compiling the source code.

Then run the bot going to the `bots` folder and typing `./bot-ping-pong.exe` on your terminal.

#### Testing the bot
Type "ping" or "pong" in any public channel that the bot is part of.

#### Closing the bot
Close the Terminal that bot-ping-pong is running or press "Ctrl-C" to kill it.
