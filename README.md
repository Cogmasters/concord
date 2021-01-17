# README

Orca is a bot framework that is designed with minimum dependencies to
make bot deployment deadly simple.  The primary design goals are:

- easy to reason about the code: we use the most native data structures,
   the simplest algorithms, and intuitive interfaces.

- easy to debug (networking and logic) errors: extensive assertion 
  and logging facilities.

- easy to use for the end users: we use multi-threading and
  synchronous IO to support concurrency so you only need to focus on
  the logic.  We carefully craft the library to use computing
  resources efficiently so performance should never be an issue.

- superior reliability

## Build
### Install dependencies:
For debian and ubuntu
```
sudo apt-get install -y build-essential
sudo apt-get install -y libcurl4-openssl-dev libssl-dev
```


### Compile
```
make echo-bot
```

## Run echo-bot
1. Get your bot token and paste it to `bot.config` to
   replace `YOUR-BOT-TOKEN`. There are 
   well written instructions from the [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) about 
   how to get token and add a bot to a server.
   
2. Invite your bot to a testing server. We can invite your bots
   to our testing servers. 

3. Run `./echo-bot.exe` in the same folder of `bot.config`

## Test echo-bot
Type any message in any channel of the server that the bot is invited.


## Usage example
```c
void on_message(
    discord_t *client,
    discord_user_t *self,
    discord_message_t *message)
{
  // make sure it doesn't echoes itself
  if (strcmp(self->username, message->author->username)){
    discord_send_message(client, message->channel_id, message->content);
  }
}
```

## Supported Features:
  - discord gateway rate limiting
  - discord gateway ws resuming
  - basic discord rest API endpoints
  
## Participate in discussions and get tech support
Join our discord server: https://discord.gg/2jfycwXVM3

## Contributions are welcome!
Check our development [Roadmap](ROADMAP.md) and [Coding Guidelines](CODING_GUIDELINES.md) to get started

