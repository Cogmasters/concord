# README

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
   well written instructions from [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token)
   
2. invite your bot to your server
3. run `./echo-bot.exe` in the same folder of `bot.config`

## Test echo-bot
type any message in any channel of the server that the bot is invited.

## Get support
Join our discord server: 
