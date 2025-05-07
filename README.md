[migrating-shield]: https://img.shields.io/badge/Gist-Migrating%20from%20v1-yellow
[migrating-link]: https://gist.github.com/lcsmuller/d6aee306bac229a7873f5c243bf7858b
[migrating-orca-link]: https://gist.github.com/lcsmuller/b5137e66d534a57e0075f9d838c9170e
[discord-shield]: https://img.shields.io/discord/928763123362578552?color=5865F2&logo=discord&logoColor=white
[discord-invite]: https://discord.gg/Y7Xa6MA82v
[discord-config-init]: https://cogmasters.github.io/concord/group__DiscordClient.html#ga75bbe1d3eb9e6d03953b6313e5543afb
[discord-config-get-field]: https://cogmasters.github.io/concord/group__DiscordClient.html#gac4486003ffab83de397c0bebb74b3307
[coglink-link]: https://github.com/PerformanC/CogLink

<div align="center">
<img src="https://raw.githubusercontent.com/Cogmasters/concord/bd1436a84af21384d93d92aed32b4c7828d0d793/docs/static/logo.svg" width="250" alt="Concord Logo">
</div>

# Concord - C Discord API library

[ ![discord-shield][] ][discord-invite]
[ ![migrating-shield][] ][migrating-link]

## About

Concord is an asynchronous C99 Discord API library with minimal external dependencies, and a low-level translation of the Discord official documentation to C code.

### Guides

Following are guides created by the community to help you get started with Concord, organized by category:

#### Installation & Setup

- [Compiling on Windows](docs/guides/compiling_on_windows.md) - Build Concord on Windows systems
- [Installing Concord (Termux)](docs/guides/installing_concord_termux.md) - Install on Android using Termux
- [Msys2 and Mingw64](docs/guides/msys2_and_mingw64.md) - Setup using MSYS2 environment
- [Cross Compiling](docs/guides/cross_compiling.md) - Compile for different target platforms
- [Concord on Old Systems](docs/guides/concord_on_old_systems.md) - Support for legacy systems

#### Configuration

- [Config.json Directives](docs/guides/config.json_directives.md) - Configure your bot using JSON
- [Setup with Environment Variables](docs/guides/setup_concord_with_env.md) - Use environment variables

#### Discord Features

- [Embeds](docs/guides/embeds.md) - Create rich message embeds
- [Slash Commands](docs/guides/slash-commands.md) - Implement Discord application commands
- [Event Scheduler](docs/guides/scheduler_event.md) - Control Discord event processing
- [SQLite3 with Concord](docs/guides/sqlite3_db_with_concord.md) - Persist data with SQLite
- [Databases with Concord](docs/guides/databases_with_concord.md) - General database integration

#### Debugging & Troubleshooting

- [Debugging](docs/guides/debugging.md) - Debug your Concord applications

### Examples

*The following are minimalistic examples, refer to [`examples/`](examples/) for a better overview.*

#### Slash Commands (new method)

*Note: you need to replace `GUILD_ID` with an actual guild ID, or this example won't compile!*
You can use a macro to do this: `#define GUILD_ID 1234567898765431`

```c
#include <string.h>
#include <concord/discord.h>

void on_ready(struct discord *client, const struct discord_ready *event) {
    struct discord_create_guild_application_command params = {
        .name = "ping",
        .description = "Ping command!"
    };
    discord_create_guild_application_command(client, event->application->id,
                                             GUILD_ID, &params, NULL);
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return; /* return if interaction isn't a slash command */

    if (strcmp(event->data->name, "ping") == 0) {
          struct discord_interaction_response params = {
                .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
                .data = &(struct discord_interaction_callback_data){
                      .content = "pong"
                }
          };
          discord_create_interaction_response(client, event->id,
                                              event->token, &params, NULL);
    }
}

int main(void) {
    struct discord *client = discord_init(BOT_TOKEN);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);
    discord_run(client);
}
```

#### Message Commands (old method)

```c
#include <string.h>
#include <concord/discord.h>
#include <concord/logmod.h>

void on_ready(struct discord *client, const struct discord_ready *event) {
    logmod_log(INFO, NULL, "Logged in as %s!", event->user->username);
}

void on_message(struct discord *client, const struct discord_message *event) {
    if (strcmp(event->content, "ping") == 0) {
        struct discord_create_message params = { .content = "pong" };
        discord_create_message(client, event->channel_id, &params, NULL);
    }
}

int main(void) {
    struct discord *client = discord_init(BOT_TOKEN);
    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_message_create(client, &on_message);
    discord_run(client);
}
```

## Supported operating systems (minimum requirements)

* GNU/Linux 4.x
* FreeBSD 12
* NetBSD 8.1
* Windows 7 (Cygwin)
* GNU/Hurd 0.9
* Mac OS X 10.9

*Note: big-endian processors running certain OSes like SPARC Solaris, PowerPC AIX, System Z z/OS or Linux, or MIPS IRIX are NOT supported. There are currently a few issues that prevent some of the logic from correctly on big-endian systems. This will be fixed soon.*

## Build Instructions

The only dependency is `curl-8.7.1` or higher with websockets support. Since many system package managers don't provide this specific version with websockets enabled, we recommend compiling from source.

> [!IMPORTANT]
> Libcurl must be compiled with the `--enable-websockets` flag to work with Concord.

### On Windows

* Install **Cygwin**
* During Cygwin installation, select packages: `gcc`, `make`, `git`, `autoconf`, `libtool`, `pkg-config`, `openssl-devel`, `zlib-devel`
* Follow the Windows tutorial [here](docs/guides/compiling_on_windows.md)
* Then compile libcurl from source (instructions below)

### Compiling libcurl from source (recommended for all platforms)

```console
# Install build dependencies
# Ubuntu/Debian:
$ sudo apt-get update && sudo apt-get install -y build-essential autoconf libtool pkg-config libssl-dev zlib1g-dev

# Fedora/RHEL/CentOS:
$ sudo dnf install -y gcc make autoconf libtool pkgconfig openssl-devel zlib-devel

# Arch/Manjaro:
$ sudo pacman -S --needed base-devel openssl zlib

# Alpine:
$ apk add build-base autoconf libtool pkgconfig openssl-dev zlib-dev

# FreeBSD:
$ pkg install autoconf libtool pkgconf openssl

# OS X:
$ xcode-select --install
$ brew install autoconf libtool pkg-config openssl@3
# or with MacPorts:
$ port install autoconf libtool pkgconfig openssl

# Download and compile libcurl
$ curl -LO https://curl.se/download/curl-8.7.1.tar.gz
$ tar -xzf curl-8.7.1.tar.gz
$ cd curl-8.7.1
$ ./configure --with-openssl --enable-websockets
$ make
$ sudo make install

# You might need to inform the system's dynamic linker about the new library location with:
$ echo "/usr/local/lib" > /etc/ld.so.conf.d/curl.conf
$ sudo ldconfig
```

## Setting up your environment

### Clone Concord into your workspace

```console
$ git clone https://github.com/cogmasters/concord.git && cd concord
```

### Compile Concord

```console
$ make
```

### Special notes about Voice Connections

Concord does not support voice connections yet. If you want to use voice connections, you can use [CogLink][coglink-link] instead.
CogLink is a separate project that provides a LavaLink client for Concord. It is not part of the Concord library, but it is designed to work seamlessly with Concord.

### Special notes for non-Linux systems

You might run into trouble with the compiler and linker not finding your Libcurl headers. You can do something like this:
```console
$ CFLAGS=-I<some_path> LDFLAGS=-L<some_path> make
```
For instance, on a FreeBSD system:
```console
$ CFLAGS=-I/usr/local/include LDFLAGS=-L/usr/local/lib make
```
On OS X using MacPorts:
```console
$ CFLAGS=-I/opt/local/include LDFLAGS=-L/opt/local/lib make
```
On OS X using a self-compiled libcurl:
```console
$ CFLAGS=-I/usr/local/include LDFLAGS=-L/usr/local/include make
```
On Windows with Cygwin, you might need to pass both arguments to use POSIX threading:
```console
$ CFLAGS="-pthread -lpthread" make
```

### Special note about linking Concord against another library
In some cases, you might want to link Concord into a shared object, or link it as a shared object into another shared
object. In that case, you will need to compile Concord with `CFLAGS="-fpic" make`. 

## Configuring Concord

[discord\_config\_init()][discord-config-init] is the initialization method that allows configuring your bot without recompiling.

The following outlines `config.json` fields:
```js
{
  "token": "YOUR-BOT-TOKEN", // replace with your bot token
  "log": {                   // logging directives
    "level": "TRACE",           // TRACE, DEBUG, INFO, WARN, ERROR, FATAL
    "trace": "bot.log",         // the log output file (null to disable)
    "quiet": false,             // true to disable logs in console
    "overwrite": true,          // true overwrites the file on each run
    "color": true,              // display color on console
    "http": "http.log",         // the HTTP log output file (null to disable)
    "ws": "ws.log",             // the WebSockets log output file (null to disable)
    "disable": ["WEBSOCKETS", "HTTP"] // disable logging for specific modules
  }
  // here you can add your custom fields *
}
```
\* *Your custom field contents can be fetched with [discord\_config\_get\_field()][discord-config-get-field]*

See more information about the `config.json` file in the [config.json directives](docs/guides/config.json_directives.md) guide.

## Test Copycat-Bot

1. Get your bot token and add it to `config.json`, 
   by assigning it to discord's "token" field. There are 
   well written instructions from 
   [discord-irc](https://github.com/reactiflux/discord-irc/wiki/Creating-a-discord-bot-&-getting-a-token)
   explaining how to get your bot token and adding it to a server.
2. Build example executables:
   ```console
   $ make examples
   ```
3. Run Copycat-Bot:
   ```console
   $ cd examples && ./copycat
   ```

### Get Copycat-Bot Response

Type a message in any channel the bot is part of and the bot should send an exact copy of it in return.

### Terminate Copycat-Bot

With <kbd>Ctrl</kbd>+<kbd>c</kbd> or with <kbd>Ctrl</kbd>+<kbd>|</kbd>

## Configure your build

The following outlines special flags and targets to override the default Makefile build with additional functionalities.

### Special compilation flags

* `-DCCORD_SIGINTCATCH`
    * By default Concord will not shutdown gracefully when a SIGINT is received (i.e. <kbd>Ctrl</kbd>+<kbd>c</kbd>), enable this flag if you wish it to be handled for you.
* `-DCCORD_DEBUG_WEBSOCKETS`
    * Enable verbose debugging for WebSockets communication.
* `-DCCORD_DEBUG_HTTP`
    * Enable verbose debugging for HTTP communication.

*Example:*
```console
$ CFLAGS="-DCCORD_SIGINTCATCH -DCCORD_DEBUG_HTTP" make
```

### Special targets

* `make shared`
    * Produce a dynamically-linked version of Concord. This Makefile is intended for GNU-style compilers, such as `gcc` or `clang`.
* `make shared_osx`
    * Produce a dynamically-linked version of Concord, for OS X and Darwin systems. 
* `make debug`
    * Enable some flags useful while developing, such as `-O0` and `-g`

## Installing Concord

*(note -- `#` means that you should be running as root)*

```console
# make install
```

This will install the headers and library files into $PREFIX. You can override this as such:
```console
# PREFIX=/opt/concord make install
```

### Cross-compiling Concord
To cross-compile Concord, see the manual [here](docs/guides/cross_compiling.md).

### Included dependencies

The following are `stable` and well documented dependencies that are packaged with Concord and can be included to your projects:

| File                                                  | Description                                        |
|-------------------------------------------------------|----------------------------------------------------|
| [cog-utils](https://github.com/Cogmasters/cog-utils)  | General purpose functions aimed at portability     |
| [logmod](https://github.com/lcsmuller/logmod)         | A modular logging library                          |
| [carray](https://github.com/c-ware/carray)\*          | Macro-based implementation of type-safe arrays     |
| [anomap](https://github.com/Anotra/anomap)\*          | Sorted key/value storage for C99                   |
| [oa_hash](https://github.com/lcsmuller/oa-hash)       | A lightweight open-addressing hashtable            |
| [json-build](https://github.com/lcsmuller/json-build) | Tiny, zero-allocation JSON serializer              |
| [jsmn-find](https://github.com/lcsmuller/jsmn-find)   | Tiny, zero-allocation JSON tokenizer               |

\* *Concord uses its own modified version that may be not up to date with the original*

Note that included headers must be `concord/` prefixed:
```c
#include <concord/discord.h>
#include <concord/logmod.h>
```

### Standalone executable

#### GCC 

```console
$ gcc myBot.c -o myBot -pthread -ldiscord -lcurl
```

#### Clang

```console
$ clang myBot.c -o myBot -pthread -ldiscord -lcurl
```

#### UNIX C compilers
##### This includes the following compilers:

* IBM XL C/C++ (AIX, z/OS, IBM i)
* Sun/Oracle Studio (Solaris)
* IRIX MIPSpro C++ (IRIX) -- NOTE: currently not supported
* HP aCC (HP-UX)
* Compaq C (Tru64 UNIX) -- NOTE: also currently not supported
*Note: if you want to actually compile this on one of the systems listed above, please see the "Compiling on old computers" guide.*

```console
$ cc myBot.c -o myBot -ldiscord -lcurl -lpthread
```

Note: some systems such as **Cygwin** require you to do this:
```console
$ gcc myBot.c -o myBot -pthread -lpthread -ldiscord -lcurl
```
(this links against libpthread.a in `/usr/lib`)

## Recommended debuggers

First, make sure your executable is compiled with the `-g` flag to ensure human-readable debugger messages.

### Valgrind

Using valgrind to check for memory leaks:

```console
valgrind --leak-check=full ./myBot
```
For a more comprehensive guide check [Valgrind's Quick Start](https://valgrind.org/docs/manual/quick-start.html).

### GDB

Using GDB to check for runtime errors, such as segmentation faults:

```console
$ gdb ./myBot
```
And then execute your bot from the gdb environment:
```console
(gdb) run
```
If the program has crashed, get a backtrace of the function calls leading to it:
```console
(gdb) bt
```

For a more comprehensive guide check [Beej's Quick Guide to GDB](https://beej.us/guide/bggdb/)

## Support

Problems? Check out our [Discord Server][discord-invite]

## Contributing

All kinds of contributions are welcome, all we ask is to abide to our [guidelines](docs/CONTRIBUTING.md)! If you want to help but is unsure where to get started then our [Discord API Roadmap](docs/DISCORD_ROADMAP.md) is a good starting point. Check our [links](#links) for more helpful information.

## Getting Started

- [Documentation](https://cogmasters.github.io/concord/)
- [Discord API Roadmap](docs/DISCORD_ROADMAP.md)

## Useful links

- [CogLink][coglink-link] - LavaLink client for Concord
- [Migrating from V1][migrating-link]
- [Migrating from Orca][migrating-orca-link]
