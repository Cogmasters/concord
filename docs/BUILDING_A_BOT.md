# Building a Basic Ping-Pong Bot

Building a bot is pretty simple with this library, but there are some basic things you have to do before starting:

1. Make sure you have all the build dependencies. The dependencies are listed in the [README](/README.md) of this project.

2. Make sure that you have a bot token. If you do not [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) has instructions on building a bot. Put your bot token in `bot.config`, replacing the `YOUR-BOT-TOKEN` with your own token. We will be using this file as needed.

# Ping-pong bot code

The entire code of ping-pong bot is below. We will go over it in further down:
```c
#include <stdio.h>
#include <stdlib.h>

#include <orca/discord.h>


void on_ready(struct discord *client, const struct discord_user *me) {
  fprintf(stderr, "\n\nPingPong-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void on_ping(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  struct discord_create_message_params params = {.content = "pong"};
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_pong(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  struct discord_create_message_params params = {.content = "ping"};
  discord_create_message(client, msg->channel_id, &params, NULL);
}

int main()
{
  discord_global_init();
  struct discord *client = discord_config_init("bot.config");

  discord_set_on_ready(client, &on_ready);
  discord_set_on_command(client, "ping", &on_ping);
  discord_set_on_command(client, "pong", &on_pong);

  discord_run(client);

  discord_cleanup(client);
  discord_global_cleanup();
}
```

# Setting up the bot settings

You can set it automatically by initializing it with the bot.config file located at orca/bots folder. Simply give the file path as a parameter of discord_config_init(), as following:
```c
  struct discord *client = discord_config_init("bot.config");
```
Or you can initialize directly with discord_init() by giving it the bot token, like so:
```c
  struct discord *client = discord_init("BOT_TOKEN_HERE");
```

## discord_global_init
`discord_global_init()` : the function to run before using any other functions, it will set some important global configurations from curl

## discord_config_init
`discord_config_init(char[])` : function for initializing the bot using some presets

Returns `struct discord`: the client structure

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the name of the bot config file|

## discord_init
`discord_init(char[])` : function for initializing the bot with a token

Returns `struct discord`: the client structure

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the bot token string|

# Starting up the bot
```c
discord_set_on_ready(client, &on_ready);
discord_set_on_command(client, "ping", &on_ping);
discord_set_on_command(client, "pong", &on_pong);

discord_run(struct discord*);
```

## discord_set_on_ready
`discord_set_on_ready(struct discord*, on_idle_cb*)`: calls `on_ready` callback function when Discord's `READY` event is triggered

|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct discord| the client stucture |
|on_idle_cb *callback| the callback to run when the READY event is triggered (see libdiscord.h for more callbacks definitions) |

## discord_set_on_command
`discord_set_on_command(struct discord*, char[], message_cb*)`: executes callback function when `char[]` command is triggered on chat

|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct discord| the client stucture |
|char[]| The chat command expected to trigger a callback response |
|message_cb*| the message type function callback to run when its corresponding event is triggered (see discord-common.h for message_cb definitions) |

## discord_run
`discord_run(struct discord*)`: the functions that starts the bot by establishing a connection to Discord, runs until error

|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct discord| the client stucture  |


# Cleaning up the bot

```c
  discord_cleanup(client);
  discord_global_cleanup();
```

## discord_cleanup
`discord_cleanup(struct discord*)`: function that cleans up bot resources

|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct discord| the client stucture |

## discord_global_cleanup
`discord_global_cleanup()`: function that cleans up resources set by `discord_global_init()`

# Running the bot

Use `make bot` for compiling the source code.

Then run the bot going to the `bots` folder and typing `./bot-ping-pong.exe` on your terminal.

#### Testing the bot
Type "ping" or "pong" in any public channel that the bot is part of.

#### Closing the bot
Close the Terminal that bot-ping-pong is running or press "Ctrl-C" to kill it.
