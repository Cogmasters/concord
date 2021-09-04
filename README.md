<div align="center">
  <br />
  <p>
    <a href="https://cee-studio.github.io/orca"><img src="https://raw.githubusercontent.com/cee-studio/orca-docs/master/docs/source/images/logo.svg" width="546" alt="orca" style="background-color:red;" /></a>
  </p>
  <br />
  <p>
    Easy to use, easy to deploy, easy to debug.
  </p>
  <p>
    Join our Discord server: <a href="https://discord.gg/2jfycwXVM3"><img src="https://img.shields.io/discord/562694099887587338?color=5865F2&logo=discord&logoColor=white" alt="Discord server" /></a>
  </p>
</div>

## About

Orca is implemented in plain C, its symbols are organized to be easily matched to the documentation of the API being covered.

This is done in order to:
* Reduce the need of thoroughly documenting every Orca API
* Reduce our user's cognitive burden of having to read both Orca API documentation and supported REST API documentations. 
* The codebase becomes easier to navigate.

Orca's implementation has minimum external dependencies to make bot deployment deadly simple.

### Design

- Easy to use for the end users: we provide internal synchronization
  so that the user may provide scalability to his applications without
  having to excessively worry about race-conditions. All transfers made
  with Orca are thread-safe by nature.

- Easy to reason about the code: we use the most native data structures,
   the simplest algorithms, and intuitive interfaces.

- Easy to debug (networking and logic) errors: extensive assertion 
  and logging facilities.

- Superior reliability.

## Build
### For Ubuntu and Debian
#### Install dependencies:

The only dependencies are curl-7.64.0 or higher built with openssl
```
sudo apt-get install -y build-essential 
sudo apt-get install -y libcurl4-openssl-dev libssl-dev
```

### For Void Linux
#### Install dependencies:

Void Linux does not seem to come with the header files necessary for libcurl to run, so
you will need to install them through the `libcurl-devel` package.
```
sudo xbps-install -S libcurl-devel
sudo xbps-install -S wget
```

### Compile

```
make
sudo make install
```

#### Standalone executable
```
gcc myBot.c -o myBot.out -ldiscord -lcurl -lcrypto -lpthread -lm
```

### For Windows

* If you do not have Ubuntu or Debian but have Windows 10, you can install WSL2 and get either Ubuntu or Debian [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

## Example usage

```c
#include <string.h> // strcmp()
#include <orca/discord.h>

void on_ready(struct discord *client, const struct discord_user *bot) {
  log_info("Logged in as %s!", bot->username);
}

void on_message(struct discord *client, const struct discord_user *bot, const struct discord_message *msg) {
  if (0 == strcmp(msg->content, "ping")) {
    struct discord_create_message_params params = { .content = "pong" };
    discord_create_message(client, msg->channel_id, &params, NULL);
  }
}

int main() {
  struct discord *client = discord_init(BOT_TOKEN);
  discord_set_on_ready(client, &on_ready);
  discord_set_on_message_create(client, &on_message);
  discord_run(client);
}
```
*This is a minimalistic example, refer to `bots/` for a better overview.*

## Get started with bot-echo

1. Get your bot token and paste it in `bot.config`, 
   replacing `YOUR-BOT-TOKEN` with it. There are 
   well written instructions from the 
   [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token)
   about how to get your bot token and it to a server.
2. Invite your bot to a testing server. We can invite your
   bot to our testing servers at our [Discord Server](https://discord.gg/2jfycwXVM3).
3. Run `make bots`
4. Go to `bots/` folder and run `./bot-echo.out`

### Test bot-echo
Type a message in any channel the bot is part of.

### Terminate bot-echo
Close the Terminal or type `Ctrl-C` to kill the process.

## Debug Memory Errors
* The recommended method: 
  Using SaiphC to build your bot, and run the executable.  All runtime memory errors will be reported. 
  The [instruction](docs/SAIPHC.md) to use SaiphC to build bots.

* Using valgrind, which is more convenient but cannot report all runtime memory errors. 
```
valgrind ./myBot.out 
```

## Links

- [Documentation](https://cee-studio.github.io/orca/)
- [How to make a bot](docs/BUILDING_A_BOT.md)
- [Contributing](docs/CONTRIBUTING.md)
- [Discord Server](https://discord.gg/2jfycwXVM3)

## Contributing
Check our [Contributing Guidelines](docs/CONTRIBUTING.md) to get started! If you are here for the Discord API, please check our [Discord API Roadmap](docs/DISCORD_ROADMAP.md).

**Give us a star if you like this project!**
