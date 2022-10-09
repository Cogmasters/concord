# Getting the bot started

## config.json directives

The `config.json` file is a configuration file that can be used to start your bots from. Since it's read at runtime, it is especially useful if you want to avoid having to recompile your bot application for each small configuration that gets added. This guide outlines some of the configuration options you can modify, and also how to add your own.

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

  logging.level defines the type of log that will be used to log if you set quiet to false.

  Screenshot of logging.level set as "debug"

  ![Logging level screenshots](screenshots/config.json_directives/logging_level.png "Logging.level")

#### filename

  This sets the file name of the file that you wish your log is saved into it.

#### quiet

  That configuration disables the default concord logging.

  Screenshot as example:

  True:

  ![Logging quiet screenshot false](screenshots/config.json_directives/logging_quiet_false.png "Logging.quiet false")

  False (You can see the Concord's default logging messages disappear):

  ![Logging quiet screenshot true](screenshots/config.json_directives/logging_quiet_true.png "Logging.quiet trut")

#### overwrite

  In case to avoid your logging files getting too big, you can set this to true so that whenever the bot logs in, Concord will empty the logging files.
  
#### use_color

  This adds colors to Concord's logging messages, so it will look better and you can see WARNS/ERRORS with ease.

  Screenshots of logging.use_color set as true and set as false.

  True:

  ![Logging use_colors screenshot true](screenshots/config.json_directives/logging_use_color_true.png "Logging.use_colors true")

  False:

  ![Logging use_colors screenshot false](screenshots/config.json_directives/logging_use_color_false.png "Logging.use_colors false")

#### http.enable

  Enables the capability to log all the information of the HTTP(s) requests made by Concord.

#### http.filename

  The filename of the file that will be used to save the information of the HTTP(s) requests.

  See `logging.http.enable` for more information.

  This will be obsolete if `logging.http.enable` is set to false.

#### disable_modules
  
  Disables one of Concord's default logging instead of disabling all of them like logging.quiet.

  Screenshots of disabling "WEBSOCKETS" and also not disabling any logging:

  Disabling "WEBSOCKETS":

  ![Logging disable_modules screenshot websockets](screenshots/config.json_directives/logging_disable_modules_websockets.png "Logging.disable_modules websockets")

  Not disabling any:

  ![Logging disable_modules screenshot none](screenshots/config.json_directives/logging_disable_modules_none.png "Logging.disable_modules none")

### Discord

#### token

  The token that Concord will use to log in to the bot, in case you use the `discord_config_init` to define the `struct discord *client`.

#### default_prefix.enable

  Will enable the opportunity to set a default prefix.

  See `discord.default_prefix.prefix` for more information.

#### default_prefix.prefix

  Set a default prefix, so `discord_set_on_command` function can be used.

  This will not work in case `discord.default_prefix.enable` is set to false.

## Observations

  You can also put custom fields on your config.json and get its value with the `discord_config_get_field` function. See the following example.

  ```c
  char foo[16];

  struct ccord_szbuf_readonly value = discord_config_get_field(client, (char *[2]){ "field", "foo" }, 2);

  snprintf(foo, sizeof(foo), "%.*s", (int)value.size, value.start);
  ```

  ```c
  struct ccord_szbuf_readonly discord_config_get_field(struct discord *client, char *const path[], unsigned depth)
  ```

  Attention: this function will only work if you initialize your bot with the `discord_config_init`.

  The first argument of `discord_config_get_field` is the `struct discord *client` that `discord_init`/`discord_config_init` (or also, in case the code is inside some kind of event, it might be on the event parameters) returns to you.

  The second argument is a `const x[]` (also known as `array`) the path to the field where you want to get its value.

  The third argument is an `int` value of the depth of the path, for example, if the path was `field -> another_field -> foo` it would be 3
  
*Written by [ThePedro](https://github.com/ThePedroo)*
