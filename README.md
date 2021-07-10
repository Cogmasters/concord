<div align="center">
  <br />
  <p>
    <a href="https://cee-studio.github.io/orca"><img src="https://raw.githubusercontent.com/cee-studio/orca-docs/1f3aee92c6d29ba8a51651cebc524c037ce9ae7d/docs/source/images/logo.svg" width="546" alt="orca" style="background-color:red;" /></a>
  </p>
  <br />
  <p>
    <a href="https://discord.gg/2jfycwXVM3"><img src="https://img.shields.io/discord/562694099887587338?color=5865F2&logo=discord&logoColor=white" alt="Discord server" /></a>
  </p>
</div>

**Please give a star if you like this project.**

## About

Easy to use, easy to deploy, easy to debug way to build reliable Discord bots.

### Design

- easy to use for the end users: we use multi-threading and
  synchronous IO to support concurrency so you only need to focus on
  the logic.  We carefully craft the library to use computing
  resources efficiently so performance should never be an issue.

- easy to reason about the code: we use the most native data structures,
   the simplest algorithms, and intuitive interfaces.

- easy to debug (networking and logic) errors: extensive assertion 
  and logging facilities.

- superior reliability

### Implementation

Orca is implemented in plain C. The symbols are organized in a intuitive
fashion to be easily identified by matching to the REST API docs.

There are three purposes for this:

1. Reduce the need of thoroughly documenting every Orca API
2. Reduce our user's cognitive burden of having to read both Orca API
documenation and supported REST API documentations. 
3. The codebase becomes easier to navigate.

Orca's implementation has minimum external dependencies to make bot
deployment deadly simple.


## Build
### For Ubuntu and Debian
#### Install dependencies:

The only dependencies that is needed is curl-7.64.0 or higher built with openssl
```
sudo apt-get install -y build-essential 
sudo apt-get install -y libcurl4-openssl-dev libssl-dev
```

#### Compile

```
make
sudo make install
```

### For Windows

* If you do not have Ubuntu or Debian but have Windows 10, you can install WSL2 and get either Ubuntu or Debian [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).
* If you have Windows but don't want to use WSL2, you can find a tutorial [here](/docs/BUILDING_WITH_WINDOWS.md)

## Example usage

```c
#include <orca/discord.h>

void on_ready(struct discord *client, const struct discord_user *bot) {
  log_info("Logged in as %s#%s!", bot->username, bot->discriminator);
}

void on_message(
  struct discord *client, 
  const struct discord_user *bot, 
  const struct discord_message *msg
){
  if (0 == strcmp(msg->content, "ping")) {
    struct discord_create_message_params params = { .content = "pong" };
    discord_create_message(client, msg->channel_id, &params, NULL);
  }
}

int main(void) {
  struct discord *client = discord_init(BOT_TOKEN);
  discord_set_on_ready(client, &on_ready);
  discord_set_on_message_create(client, &on_message);
  discord_run(client);
}
```
*This is a minimalistic example, refer to `bots/` for a better overview.*

## Get started with bot-echo
1. Get your bot token and paste it to `bot.config` to
   replace `YOUR-BOT-TOKEN`. There are 
   well written instructions from the [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token) about 
   how to get token and add a bot to a server.
   
2. Invite your bot to a testing server. We can invite your bots
   to our testing servers. 

3. Run `./bot-echo.exe` in the same folder of `bot.config`

#### Test bot-echo
Type any message in any public channel of the server that the bot is invited.

#### Terminate bot-echo
Close the Terminal that bot-echo is running or type "Ctrl-C" to kill it.

#### Debug Memory Errors
* The recommanded method: 
  Using SaiphC to build your bot, and run the executable.  All runtime memory errors will be reported. 
  The [instruction](/docs/SAIPH.md) to use SaiphC to build bots.

* Using valgrind, which is more convenient but cannot report all runtime memory errors. 
```
valgrind your-bot.exe 
```

## Links

- [Documentation](https://cee-studio.github.io/orca/)
- [How to make a bot](/docs/BUILDING_A_BOT.md)
- [Discord Server](https://discord.gg/2jfycwXVM3)

## Contributions are welcome!
Check our Discord API's development [Roadmap](docs/DISCORD_ROADMAP.md) and [Coding Guidelines](docs/CODING_GUIDELINES.md) to get started

If you are not familiar with git and are not comfortable with creating pull requests without introducing merge 
commits, please check our [Commit Guidelines](docs/COMMIT_GUIDELINES.md).

Keywords:
libdiscord, discord library in C.
