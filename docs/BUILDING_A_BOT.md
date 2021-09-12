# Building your first bot

Some basic things you should have covered before proceeding:

1. Make sure you have all of the necessary dependencies. The dependencies cane be found in the [Build Instructions](/README.md#build-instructions).
2. You should have a bot token. If you do not [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) has instructions on how to get one. Add your token to `config.json` by assigning it to discord's "token" field.
3. Make sure `my_bot/` is your working directory, here you have the option to edit `myBot.c` or start your own `.c` file from scratch.


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

## Initialize the bot

You can initialize the bot by providing a `config.json` file:
```c
struct discord *client = discord_config_init("../config.json");
```
You can also initialize it by providing the token directly to `discord_init()`:
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

## Start the bot

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
|discord\_on\_idle\_cb \*callback| the callback to run when the READY event is triggered |

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


## Clean up the bot

```c
discord_cleanup(client);
```

### [discord\_cleanup()](https://cee-studio.github.io/orca/apis/discord.html?highlight=set_on_command#c.discord_cleanup)
`discord_cleanup(struct discord*)`: cleanup client initialized by `discord_init()` or `discord_config_init()`

## Compile the bot

### Using the preset Makefile

```bash
$ make
```
*Note: The preset Makefile will separately compile each file from the `my_bot` folder that has a `.c` extension.* 

### As a standalone executable

```bash
$ gcc myBot.c -o myBot.out -ldiscord -lcurl -lcrypto -lpthread -lm
```

## Execute the bot

Simply run the generated executable like so:

```bash
$ ./myBot.out
```

### Test the bot

By heading to a channel of which your bot has access and then type "ping" or "pong".

### Terminate the bot

With `Ctrl-C` or by closing the Terminal.
