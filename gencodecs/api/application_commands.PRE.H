/*****************************************************************************
 * Application Commands Datatypes
 * **************************************************************************/

ENUM(discord_application_command_types)
  /** Slash commands: a text-based command that shows up when a user 
       types `/` */
    ENUMERATOR(DISCORD_APPLICATION_CHAT_INPUT, = 1)
  /** A UI-based command that shows up when a user
       right clicks or taps on another user */
    ENUMERATOR(DISCORD_APPLICATION_USER, = 2)
  /** A UI-based command that shows up when a user
       right clicks or tap on a message */
    ENUMERATOR_LAST(DISCORD_APPLICATION_MESSAGE, = 3)
ENUM_END

ENUM(discord_application_command_option_types)
    ENUMERATOR(DISCORD_APPLICATION_OPTION_SUB_COMMAND, = 1)
    ENUMERATOR(DISCORD_APPLICATION_OPTION_SUB_COMMAND_GROUP, = 2)
    ENUMERATOR(DISCORD_APPLICATION_OPTION_STRING, = 3)
  /** Any integer between `-2^53` and `2^53` */
    ENUMERATOR(DISCORD_APPLICATION_OPTION_INTEGER, = 4)
    ENUMERATOR(DISCORD_APPLICATION_OPTION_BOOLEAN, = 5)
    ENUMERATOR(DISCORD_APPLICATION_OPTION_USER, = 6)
  /** Includes all channel types + categories */
    ENUMERATOR(DISCORD_APPLICATION_OPTION_CHANNEL, = 7)
    ENUMERATOR(DISCORD_APPLICATION_OPTION_ROLE, = 8)
  /** Includes users and roles */
    ENUMERATOR(DISCORD_APPLICATION_OPTION_MENTIONABLE, = 9)
  /** Any double between `-2^53` and `2^53` */
    ENUMERATOR(DISCORD_APPLICATION_OPTION_NUMBER, = 10)
  /** @ref discord_attachment object */
    ENUMERATOR_LAST(DISCORD_APPLICATION_OPTION_ATTACHMENT, = 11)
ENUM_END

ENUM(discord_application_command_permission_types)
    ENUMERATOR(DISCORD_APPLICATION_PERMISSION_ROLE, = 1)
    ENUMERATOR_LAST(DISCORD_APPLICATION_PERMISSION_USER, = 2)
ENUM_END

PUB_STRUCT(discord_application_command)
  /** unique ID of the command */
    FIELD_SNOWFLAKE(id)
  /** one of application command types */
  COND_WRITE(self->type != 0)
    FIELD_ENUM(type, discord_application_command_types)
  COND_END
  /** unique ID of the parent application */
    FIELD_SNOWFLAKE(application_id)
  COND_WRITE(self->guild_id != 0)
  /** guild ID of the command, if not global */
    FIELD_SNOWFLAKE(guild_id)
  COND_END
  /** 1-32 character name */
    FIELD_PTR(name, char, *)
  /** 1-100 character description for `CHAT_INPUT` commands, empty string
       for `USER` and `MESSAGE` commands */
    FIELD_PTR(description, char, *)
  /** the parameters for the command, max 25 */
  COND_WRITE(self->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END
  /** whether the command is enabled by default when the app is added to a
       guild */
  COND_WRITE(self->default_permission != true)
    FIELD(default_permission, bool, true)
  COND_END
  /** autoincrementing version identifier updated during substantial
       record changes */
    FIELD_SNOWFLAKE(version)
STRUCT_END

PUB_LIST(discord_application_commands)
    LISTTYPE_STRUCT(discord_application_command)
LIST_END

STRUCT(discord_application_command_option)
  /** value of application command option type */
    FIELD_ENUM(type, discord_application_command_option_types)
  /** 1-32 character name */
    FIELD_PTR(name, char, *)
  /** 1-100 character description */
    FIELD_PTR(description, char, *)
  /** if the parameter is required or optional -- default `false` */
  COND_WRITE(self->required != false)
    FIELD(required, bool, false)
  COND_END
  /** choices for string and int types for the user to pick from */
  COND_WRITE(self->choices != NULL)
    FIELD_STRUCT_PTR(choices, discord_application_command_option_choices, *)
  COND_END
  /** if the option is a subcommand or subcommand group type, this nested
       options will be the parameters */
  COND_WRITE(self->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END
  /** if the option is a channel type, the channels shown will be restricted
       to these types */
  COND_WRITE(self->channel_types != NULL)
    FIELD_STRUCT_PTR(channel_types, integers, *)
  COND_END
  /** if the option is an INTEGER or NUMBER type, the minimum value permitted */
  COND_WRITE(self->min_value != NULL)
    FIELD_PTR(min_value, char, *)
  COND_END
  /** if the option is an INTEGER or NUMBER type, the maximum value permitted */
  COND_WRITE(self->max_value != NULL)
    FIELD_PTR(max_value, char, *)
  COND_END
  /** enable autocomplete interactions for this option */
  COND_WRITE(self->choices == NULL)
    FIELD(autocomplete, bool, false)
  COND_END
STRUCT_END

LIST(discord_application_command_options)
    LISTTYPE_STRUCT(discord_application_command_option)
LIST_END

STRUCT(discord_application_command_option_choice)
  /** 1-100 character choice name */
    FIELD_PTR(name, char, *)
  /** value of the choice, up to 100 characters if string @note in case of a
       string the value must be enclosed with escaped commas, ex: `\"hi\"` */
    FIELD_PTR(value, json_char, *)
STRUCT_END

LIST(discord_application_command_option_choices)
    LISTTYPE_STRUCT(discord_application_command_option_choice)
LIST_END

STRUCT(discord_application_command_interaction_data_option)
  /** the name of the parameter */
    FIELD_PTR(name, char, *)
  /** value of the application command option type */
    FIELD_ENUM(type, discord_application_command_option_types)
  /** the value of the option resulting from user input @note in case of a
       string the value must be enclosed with escaped commands, ex: `\"hi\"` */
  COND_WRITE(self->value != NULL && *self->value != '\0')
    FIELD_PTR(value, json_char, *)
  COND_END
  /** present if this option is a group or subcommand */
  COND_WRITE(self->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_interaction_data_options, *)
  COND_END
  /** true if this option is the currently focused option for autocomplete */
    FIELD(focused, bool, false)
STRUCT_END

LIST(discord_application_command_interaction_data_options)
    LISTTYPE_STRUCT(discord_application_command_interaction_data_option)
LIST_END

STRUCT(discord_guild_application_command_permission)
  /** the ID of the command */
    FIELD_SNOWFLAKE(id)
  /** the ID of the application the command belongs to */
    FIELD_SNOWFLAKE(application_id)
  /** the ID of the guild */
    FIELD_SNOWFLAKE(guild_id)
  /** the permissions for the command in the guild */
    FIELD_STRUCT_PTR(permissions, discord_application_command_permissions, *)
STRUCT_END

PUB_LIST(discord_guild_application_command_permissions)
    LISTTYPE_STRUCT(discord_guild_application_command_permission)
LIST_END

PUB_STRUCT(discord_application_command_permission)
  /** the ID of the role or user */
    FIELD_SNOWFLAKE(id)
  /** role or user */
    FIELD_ENUM(type, discord_application_command_permission_types)
  /** `true` to allow, `false` to disallow */
    FIELD(permission, bool, false)
STRUCT_END

PUB_LIST(discord_application_command_permissions)
    LISTTYPE_STRUCT(discord_application_command_permission)
LIST_END

/*****************************************************************************
 * Application Commands REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_create_global_application_command)
  /** 1-32 lowercase character name */
    FIELD_PTR(name, char, *)
  /** 1-100 character description */
    FIELD_PTR(description, char, *)
  /** the parameters for the command */
  COND_WRITE(self->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END
  /** whether the command is enabled by default when the app is added to a
       guild */
    FIELD(default_permission, bool, true)
  /** the type of command, default `1` if not set */
  COND_WRITE(self->type != 0)
    FIELD_ENUM(type, discord_application_command_types)
  COND_END
STRUCT_END

PUB_STRUCT(discord_edit_global_application_command)
  /** 1-32 lowercase character name */
    FIELD_PTR(name, char, *)
  /** 1-100 character description */
    FIELD_PTR(description, char, *)
  /** the parameters for the command */
  COND_WRITE(self->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END
  /** whether the command is enabled by default when the app is added to a
       guild */
    FIELD(default_permission, bool, true)
STRUCT_END

PUB_STRUCT(discord_create_guild_application_command)
  /** 1-32 lowercase character name */
    FIELD_PTR(name, char, *)
  /** 1-100 character description */
    FIELD_PTR(description, char, *)
  /** the parameters for the command */
  COND_WRITE(self->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END
  /** whether the command is enabled by default when the app is added to a
       guild */
    FIELD(default_permission, bool, true)
  /** the type of command, default `1` if not set */
  COND_WRITE(self->type != 0)
    FIELD_ENUM(type, discord_application_command_types)
  COND_END
STRUCT_END

PUB_STRUCT(discord_edit_guild_application_command)
  /** 1-32 lowercase character name */
    FIELD_PTR(name, char, *)
  /** 1-100 character description */
    FIELD_PTR(description, char, *)
  /** the parameters for the command */
  COND_WRITE(self->options != NULL)
    FIELD_STRUCT_PTR(options, discord_application_command_options, *)
  COND_END
  /** whether the command is enabled by default when the app is added to a
       guild */
    FIELD(default_permission, bool, true)
STRUCT_END

PUB_STRUCT(discord_edit_application_command_permissions)
  /** the permissions for the command in the guild */
  COND_WRITE(self->permissions != NULL)
    FIELD_STRUCT_PTR(permissions, discord_application_command_permissions, *)
  COND_END
STRUCT_END
