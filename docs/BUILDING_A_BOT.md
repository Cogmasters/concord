# Building a Discord Bot

Building a bot is pretty simple using orca, but there are some basic things should have covered before starting:

1. Make sure you have built all dependencies. The dependencies are listed in the [README](/README.md) of this project.

2. You should have a bot token. If you do not [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) has instructions on how to get one. Add your token to `config.json` by replacing `YOUR-BOT-TOKEN` with it.

3. Make sure you are inside of the folder `my_bot`, here you have the option to edit `myBot.c` or start your own from scratch.


# Ping-Pong Bot Source Code

The entire code of ping-pong bot is below. We will go over it in further down:
```c
#include <stdio.h>
#include <stdlib.h>

#include "discord.h"


void on_ready(
  struct discord *client, 
  const struct discord_user *bot) 
{
  log_info("PingPong-Bot succesfully connected to Discord as %s#%s!",
      bot->username, bot->discriminator);
}

void on_ping(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return; // ignore bots

  struct discord_create_message_params params = { .content = "pong" };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_pong(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  if (msg->author->bot) return; // ignore bots

  struct discord_create_message_params params = { .content = "ping" };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

int main()
{
  struct discord *client = discord_config_init("../config.json");

  discord_set_on_ready(client, &on_ready);
  discord_set_on_command(client, "ping", &on_ping);
  discord_set_on_command(client, "pong", &on_pong);

  discord_run(client);

  discord_cleanup(client);

  return 0;
}
```

## Initializing your bot client

You can initialize the bot by providing a `config.json` file:
```c
struct discord *client = discord_config_init("config.json");
```
Or if you do not wish to rely on `config.json`, you can initialize by providing the token directly to `discord_init()`:
```c
struct discord *client = discord_init(BOT_TOKEN);
```

### [discord\_config\_init()](https://cee-studio.github.io/orca/apis/discord.html?highlight=set_on_command#c.discord_config_init)
`discord_config_init(char[])` : initialize the bot with a configuration file

Returns [struct discord](https://cee-studio.github.io/orca/apis/discord.html?highlight=set_on_command#c.discord): the bot client

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the name of the bot config file|

## [discord\_init()](https://cee-studio.github.io/orca/apis/discord.html?highlight=set_on_command#c.discord_init)
`discord_init(char[])` : initialize the bot with a token

Returns [struct discord](https://cee-studio.github.io/orca/apis/discord.html?highlight=set_on_command#c.discord): the bot client

|Member Parameters|Description                |
|:----------------|:--------------------------|
|char[]| the bot token string|

## Starting the bot

```c
discord_set_on_ready(client, &on_ready);
discord_set_on_command(client, "ping", &on_ping);
discord_set_on_command(client, "pong", &on_pong);

discord_run(client);
```

### [discord\_set\_on\_ready()](https://cee-studio.github.io/orca/apis/discord.html?highlight=set_on_command#c.discord_set_on_ready)
`discord_set_on_ready(struct discord*, discord_on_idle_cb*)`: calls `on_ready` callback when the connection is succesfully established

|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct discord| the client stucture |
|on\_idle\_cb \*callback| the callback to run when the READY event is triggered |

### [discord\_set\_on\_command()](https://cee-studio.github.io/orca/apis/discord.html?highlight=set_on_command#c.discord_set_on_command)
`discord_set_on_command(struct discord*, char[], discord_message_cb*)`: runs callback when a command prefix is detected on chat

|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct discord| the client stucture |
|char[]| The chat command expected to trigger a callback response |
|discord\_message\_cb\*| the message type function callback to run when its corresponding event is triggered (see discord-common.h for discord\_message\_cb definitions) |

### [discord\_run()](https://cee-studio.github.io/orca/apis/discord.html#c.discord_run)
`discord_run(struct discord*)`: establishes a connection to Discord, run until error or shutdown

|Member Parameters|Description                |
|:----------------|:--------------------------|
|struct discord| the client stucture  |


## Cleaning up the bot

```c
discord_cleanup(client);
```

### [discord\_cleanup()](https://cee-studio.github.io/orca/apis/discord.html?highlight=set_on_command#c.discord_cleanup)
`discord_cleanup(struct discord*)`: cleanup client initialized by `discord_init()` or `discord_config_init()`

## Building the bot

### With the preset Makefile

```bash
$ make
```
*Note: The preset Makefile will compile each file from the `my_bot` folder containing `.c` extension separately.* 

### As a standalone executable

```bash
$ gcc myBot.c -o myBot.out -ldiscord -lcurl -lcrypto -lpthread -lm
```

## Running the bot

Simply run the generated executable as such:

```bash
$ ./myBot.out
```

### Get the bot's response

By heading to a channel of which your bot has access and type "ping" or "pong" to test it.

### Terminate the bot

With `Ctrl-C` or by closing the Terminal to kill the process.
