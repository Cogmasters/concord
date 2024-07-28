# A Starboard clone made in Concord and C99
## How to use?
### Installing dependencies:
#### We assume you already have Concord installed.
<br />

Debian, Ubuntu and derivatives:
```
# apt install libpq-dev libcurl-dev
```

Arch linux and derivatives:
```
# pacman -S postgresql-libs curl
```

Void linux:
```
# xbps-install postgresql-libs-devel libcurl-devel
```

Fedora, RHEL, Rocky and derivatives:
```
# dnf install libpq-devel libcurl-devel
```

Gentoo:
```
# emerge -a dev-db/libpq net-misc/curl
```

### Configuring

#### From the root of the repository, navigate to the `examples/starboard/` directory, if you're not already there
```bash
$ cd examples/starboard/
```

### Secrets (required)
The secrets are held in `config.json`. This file should not be shared if not edited.
It should look like this:
```json
{
  "logging": {
    "level": "trace",
    "filename": "bot.log",
    "quiet": true,
    "overwrite": true,
    "use_color": true,
    "http": {
      "enable": true,
      "filename": "http.log"
    }
  },
  "discord": {
    "token": "YOUR_TOKEN_HERE"
  },
  "database": {
    "url": "postgresql://user:password@ip:port/starboard"
  }
}
```

### Bot configuration
It is located at `src/config.h`. It contains some default configuration for the starboard. It should look like this:
```h
#ifndef STAR_CONFIG_H
#define STAR_CONFIG_H

// Your Discord User ID
#define CONFIG_OWNER_USER_ID 000000000000000000

// If turned off, every channel becomes a sumbissions channel
#define CONFIG_SELECTIVE_CHANNEL 0

// Emoji, which users have to react with
// Quick pick: 👍  ⭐
#define CONFIG_EMOJI "⭐"

// The number of emojis needed for a submission to be sent to the board
#define CONFIG_EMOJI_AMOUNT 10

// With which emoji, should the bot react automatically on the board message
// Quick pick: 👍  ⭐
#define CONFIG_BOARD_EMOJI "⭐"

#endif // STAR_CONFIG_H
```

### Building
```
$ make
```


### Running
```
$ ./starboard
```

### Channel configuration
#### Make sure you updated `CONFIG_OWNER_USER_ID` in `src/config.h`. If you've just now done this, go back to [Building](#building) and continue.

Now to add a board channel, go to your Discord server and execute:
```
/add channel:#starboard is_board:True
```
Of course, change `#starboard` to your board channel.
<br />

If you enabled `CONFIG_SELECTIVE_CHANNEL`, add a submissions channel:
```
/add channel:#memes is_board:False
```
<br />

To remove a channel:
```
/remove channel:#memes
```

### Thanks and Have fun!
