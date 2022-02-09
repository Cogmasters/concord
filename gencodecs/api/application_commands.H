/*****************************************************************************
 * Application Commands Datatypes
 * **************************************************************************/

ENUM_BEGIN(discord_application_command_types)
  DESC("Slash commands: a text-based command that shows up when a user" 
       "types `/`")
    ENUMERATOR(DISCORD_APPLICATION_CHAT_INPUT, = 1)
  DESC("A UI-based command that shows up when a user"
       "right clicks or taps on another user")
    ENUMERATOR(DISCORD_APPLICATION_USER, = 2)
  DESC("A UI-based command that shows up when a user"
       "right clicks or tap on a message")
    ENUMERATOR_LAST(DISCORD_APPLICATION_MESSAGE, = 3)
ENUM_END

STRUCT_BEGIN(discord_application_command_option)
  DESC("value of application command option type")
    FIELD_ENUM(discord_application_command_option_types, type)
  DESC("1-100 character description")
    FIELD_PTR(char, *, description)
  DESC("if the parameter is required or optional -- default false")
    FIELD(bool, required, false)
  DESC("choices for string and int types for the user to pick from")
  COND_WRITE(choices != NULL)
    FIELD_STRUCT_PTR(discord_application_command_option_choices, *, choices)
  COND_END
  DESC("if the option is a subcommand or subcommand group type, this nested"
       "options will be the parameters")
  COND_WRITE(options != NULL)
    FIELD_STRUCT_PTR(discord_application_command_options, *, options)
  COND_END
  DESC("if the option is a channel type, the channels shown will be restricted"
       "to these types")
  COND_WRITE(channel_types != NULL)
    FIELD_STRUCT_PTR(snowflakes, *, channel_types)
  COND_END
  DESC("if the option is an INTEGER or NUMBER type, the minimum value permitted")
  COND_WRITE(min_value != NULL)
    FIELD_PTR(char, *, min_value)
  COND_END
  DESC("if the option is an INTEGER or NUMBER type, the maximum value permitted")
  COND_WRITE(min_value != NULL)
    FIELD_PTR(char, *, min_value)
  COND_END
  DESC("enable autocomplete interactions for this option")
    FIELD(bool, autocomplete, false)
STRUCT_END

/*****************************************************************************
 * Application Commands REST parameters
 * **************************************************************************/

STRUCT_BEGIN(discord_create_global_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(char, *, name)
  DESC("1-100 character description")
    FIELD_PTR(char, *, description)
  DESC("the parameters for the command")
  COND_WRITE(options != NULL)
    FIELD_STRUCT_PTR(discord_application_command_options, *, options)
  COND_END
  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(bool, default_permission, true)
  DESC("the type of command, default `1` if not set")
  COND_WRITE(type != 0)
    FIELD_ENUM(discord_application_command_types, type)
  COND_END
STRUCT_END

STRUCT_BEGIN(discord_edit_global_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(char, *, name)
  DESC("1-100 character description")
    FIELD_PTR(char, *, description)
  DESC("the parameters for the command")
  COND_WRITE(options != NULL)
    FIELD_STRUCT_PTR(discord_application_command_options, *, options)
  COND_END
  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(bool, default_permission, true)
STRUCT_END

STRUCT_BEGIN(discord_create_guild_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(char, *, name)
  DESC("1-100 character description")
    FIELD_PTR(char, *, description)
  DESC("the parameters for the command")
  COND_WRITE(options != NULL)
    FIELD_STRUCT_PTR(discord_application_command_options, *, options)
  COND_END
  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(bool, default_permission, true)
  DESC("the type of command, default `1` if not set")
  COND_WRITE(type != 0)
    FIELD_ENUM(discord_application_command_types, type)
  COND_END
STRUCT_END

STRUCT_BEGIN(discord_edit_guild_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(char, *, name)
  DESC("1-100 character description")
    FIELD_PTR(char, *, description)
  DESC("the parameters for the command")
  COND_WRITE(options != NULL)
    FIELD_STRUCT_PTR(discord_application_command_options, *, options)
  COND_END
  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(bool, default_permission, true)
STRUCT_END

STRUCT_BEGIN(discord_edit_application_command_permissions)
  DESC("the permissions for the command in the guild")
  COND_WRITE(permissions != NULL)
    FIELD_STRUCT_PTR(discord_application_command_permissions, *, permissions)
  COND_END
STRUCT_END
