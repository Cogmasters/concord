# Orca: a C bot framework 

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
The only dependencies that is needed is curl-7.66.0 or higher built with openssl

For Ubuntu and Debian
```
sudo apt-get install -y build-essential libssl-dev
sudo apt-get install -y libcurl4-openssl-dev
```

\* If you do not have Ubuntu or Debian but have Windows 10, you can install WSL2 and get either Ubuntu or Debian [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

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

### Test echo-bot
Type any message in any public channel of the server that the bot is invited.

### Terminate echo-bot
Close the Terminal that echo-bot is running or type "Ctrl-C" to kill it.


## Tutorial on how to make a bot

Instructions on how to make a ping-pong bot is found [here](/docs/BUILDING_A_BOT.md).

## Participate in discussions and get tech support
Join our discord server: https://discord.gg/2jfycwXVM3

## Contributions are welcome!
Check our development [Roadmap](docs/ROADMAP.md) and [Coding Guidelines](docs/CODING_GUIDELINES.md) to get started

