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
    FIELD_ENUM(type, discord_application_command_option_types)

  DESC("1-100 character description")
    FIELD_PTR(description, char, *)

  DESC("if the parameter is required or optional -- default false")
    FIELD(required, bool, false)

  DESC("choices for string and int types for the user to pick from")
  COND_WRITE(this->choices != NULL)
    FIELD_STRUCT_PTR(choices, discord_application_command_option_choices, *)
  COND_END

  DESC("if the option is a subcommand or subcommand group type, this nested"
       "options will be the parameters")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END

  DESC("if the option is a channel type, the channels shown will be restricted"
       "to these types")
  COND_WRITE(this->channel_types != NULL)
    FIELD_STRUCT_PTR(channel_types, snowflakes, *)
  COND_END

  DESC("if the option is an INTEGER or NUMBER type, the minimum value permitted")
  COND_WRITE(this->min_value != NULL)
    FIELD_PTR(min_value, char, *)
  COND_END

  DESC("if the option is an INTEGER or NUMBER type, the maximum value permitted")
  COND_WRITE(this->max_value != NULL)
    FIELD_PTR(max_value, char, *)
  COND_END

  DESC("enable autocomplete interactions for this option")
    FIELD(autocomplete, bool, false)
STRUCT_END

/*****************************************************************************
 * Application Commands REST parameters
 * **************************************************************************/

STRUCT_BEGIN(discord_create_global_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(name, char, *)

  DESC("1-100 character description")
    FIELD_PTR(description, char, *)

  DESC("the parameters for the command")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END

  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(default_permission, bool, true)

  DESC("the type of command, default `1` if not set")
  COND_WRITE(this->type != 0)
    FIELD_ENUM(type, discord_application_command_types)
  COND_END
STRUCT_END

STRUCT_BEGIN(discord_edit_global_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(name, char, *)

  DESC("1-100 character description")
    FIELD_PTR(description, char, *)

  DESC("the parameters for the command")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END

  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(default_permission, bool, true)
STRUCT_END

STRUCT_BEGIN(discord_create_guild_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(name, char, *)

  DESC("1-100 character description")
    FIELD_PTR(description, char, *)

  DESC("the parameters for the command")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END

  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(default_permission, bool, true)

  DESC("the type of command, default `1` if not set")
  COND_WRITE(this->type != 0)
    FIELD_ENUM(type, discord_application_command_types)
  COND_END
STRUCT_END

STRUCT_BEGIN(discord_edit_guild_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(name, char, *)

  DESC("1-100 character description")
    FIELD_PTR(description, char, *)

  DESC("the parameters for the command")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END

  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(default_permission, bool, true)
STRUCT_END

STRUCT_BEGIN(discord_edit_application_command_permissions)
  DESC("the permissions for the command in the guild")
  COND_WRITE(this->permissions != NULL)
    FIELD_STRUCT_PTR(permissions, discord_application_command_permissions, *)
  COND_END
STRUCT_END
