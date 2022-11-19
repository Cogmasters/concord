[logging_level]: screenshots/config.json_directives/logging_level.png
[logging_quiet_false]: screenshots/config.json_directives/logging_quiet_false.png
[logging_quiet_true]: screenshots/config.json_directives/logging_quiet_true.png
[logging_use_colors_true]: screenshots/config.json_directives/logging_use_color_true.png
[logging_use_colors_false]: screenshots/config.json_directives/logging_use_color_false.png

# Getting the bot started
## config.json directives
The `config.json` file is a configuration file that can be used to set up your bot. It is read at runtime, so it can be modified without requiring you to recompile your bot application. This guide outlines some of the configuration options you can modify, and also how to add your own.

```json
{
  "logging": {
    "level": "trace",
    "filename": "bot.log",
    "quiet": false,
    "overwrite": true,
    "use_color": true,
    "http": {
      "enable": true,
      "filename": "http.log"
    },
    "disable_modules": ["WEBSOCKETS", "USER_AGENT"]
  },
  "discord": {
    "token": "YOUR-BOT-TOKEN",
    "default_prefix": {
      "enable": false,
      "prefix": "YOUR-COMMANDS-PREFIX"
    }
  }
}
```

### logging

#### level
Defines the logging level that will be shown by Concord
![logging.level set as debug][logging_level]

#### filename
Name of the file that you wish your log to be saved to.

#### quiet
Disables the default concord logging.

True: *(Concord's logging messages will disappear)*
![logging.quiet set to true][logging_quiet_true]

False:
![logging.quiet set to false][logging_quiet_false]


#### overwrite
To avoid your logging files becoming too large, you can set this to true so that whenever the bot logs in, Concord will overwrite any existing logging file.
  
#### use_color
Adds colors to Concord's logging messages, so it will look better and you can see WARNS/ERRORS with ease.

Screenshots of logging.use_color set as true and set as false.

True:
![logging.color set to true][logging_use_colors_true]

False:
![logging.color set to false][logging_use_colors_false]

#### http.enable
Whether it should log HTTP(s) requests performed by Concord.

#### http.filename
The file to log the HTTP(s) requests to.

See `logging.http.enable` for more information.

This will be obsolete if `logging.http.enable` is set to false.

#### disable_modules
Concord's logging modules that should be disabled

Disabling `WEBSOCKETS`:
![Logging disable_modules screenshot websockets](screenshots/config.json_directives/logging_disable_modules_websockets.png "Logging.disable_modules websockets")

Not disabling any:
![Logging disable_modules screenshot none](screenshots/config.json_directives/logging_disable_modules_none.png "Logging.disable_modules none")

### Discord
#### token
The client token that Concord will use to log in

#### default_prefix.enable
Enable a default command prefix for your bot

#### default_prefix.prefix
Set a default command prefix for your bot (this can be overridden by `discord_set_prefix()`)

## Observations
You may also add custom fields to your config.json and then fetch them with the `discord_config_get_field()`:
```c
struct ccord_szbuf_readonly discord_config_get_field(struct discord *client, char *const path[], unsigned depth)
```
*This function will only work if you initialize your bot with the `discord_config_init()`!*

Fetching your custom fields:
```c
const char *fields[] = { "field", "foo" }; // suppose you added `field.foo` to your config.json
struct ccord_szbuf_readonly value = discord_config_get_field(client, fields, sizeof(fields) / sizeof *fields);

char foo[16];
snprintf(foo, sizeof(foo), "%.*s", (int)value.size, value.start);

printf("%s\n", foo); // should print field.foo contents
```
  
*Written by [ThePedro](https://github.com/ThePedroo)*
