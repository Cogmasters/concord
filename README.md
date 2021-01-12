# README

Orca is a discord bot framework that is designed with minimum dependencies to
make bot deployment dead simple.  The primary design goals of this framework are:

- easy to debug (networking and logic) errors with extensive logging facilities.

- easy to reason about the code: we use the most native data structures,
   the simplest algorithms, and intuitive interfaces.

- easy to use for the end users: we use multi-threading and
  synchronous IO to support concurrency so you only need to focus on
  the business logic.  We carefully craft the library to use computing
  resource super efficient so performance should never be an issue
  for you.

- superior reliability

## Build
### Install dependencies:
    - gcc, make
    - libc
    - libcurl (using openssl for SSL/TSL)
For debian and ubuntu
```
apt-get install -y build-essential
apt-get install -y libcurl4-openssl-dev
```

### Compile
```
make echo-bot
```

## Run echo-bot
1. get your bot token and paste it to `bot.config` to
   replace "replace-this-with-your-bot-token". There is a 
   well written instructions from [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) about 
   how to get token and join bot to a server.
   
2. invite your bot to your server
3. run `./echo-bot.exe` in the same folder of `bot.config`

## Test echo-bot
type any message in any channel of the server that the bot is invited.


## Usage example
```c
void on_message(discord_t *client, discord_message_t *message)
{
  discord_user_t *self = discord_user_init();
  assert(NULL != self);

  discord_get_client_user(client, &self);

  // make sure it doesn't echoes itself
  if (strcmp(self->username, message->author->username)){
    discord_send_message(client, message->channel_id, message->content);
  }

  discord_user_cleanup(self);
}
```

## Supported Features:
  - rate limiting
  - ws resuming
  - basic discord rest API endpoints
  
## Get support
Join our discord server:

## Contributions are welcome!
