/* This file is generated from discord/application_commands.json, Please don't edit it. */
/**
 * @file specs-code/discord/application_commands.h
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-structure
 */


/* Application Command Structure */
/* defined at discord/application_commands.json:9:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_init(struct discord_application_command *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_cleanup(struct discord_application_command *)`
 *     * :code:`void discord_application_command_list_free(struct discord_application_command **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_from_json(char *rbuf, size_t len, struct discord_application_command *)`
 *     * :code:`void discord_application_command_list_from_json(char *rbuf, size_t len, struct discord_application_command ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_to_json(char *wbuf, size_t len, struct discord_application_command *)`
 *     * :code:`void discord_application_command_list_to_json(char *wbuf, size_t len, struct discord_application_command **)`
 * @endverbatim
 */
struct discord_application_command {
  /* discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  u64_snowflake_t id; /**< unique id of the command */

  /* discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
  enum discord_application_command_types type; /**< the type of the command, defaults 1 if not set */

  /* discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  u64_snowflake_t application_id; /**< unique id of the parent application */

  /* discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
  u64_snowflake_t guild_id; /**< guild id of the command, if not global */

  /* discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 character name"}' */
  char *name; /**< 1-32 character name */

  /* discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
  char *description; /**< 1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands */

  /* discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  struct discord_application_command_option **options; /**< the parameters for the command */

  /* discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  bool default_permission; /**< whether the command is enabled by default when the app is added to a guild */

};
extern void discord_application_command_cleanup_v(void *p);
extern void discord_application_command_cleanup(struct discord_application_command *p);
extern void discord_application_command_init_v(void *p);
extern void discord_application_command_init(struct discord_application_command *p);
extern void discord_application_command_from_json_v(char *json, size_t len, void *p);
extern void discord_application_command_from_json_p(char *json, size_t len, struct discord_application_command **pp);
extern void discord_application_command_from_json(char *json, size_t len, struct discord_application_command *p);
extern size_t discord_application_command_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_to_json(char *json, size_t len, struct discord_application_command *p);
extern void discord_application_command_list_free_v(void **p);
extern void discord_application_command_list_free(struct discord_application_command **p);
extern void discord_application_command_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_list_from_json(char *str, size_t len, struct discord_application_command ***p);
extern size_t discord_application_command_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_list_to_json(char *str, size_t len, struct discord_application_command **p);


/* Application Command Types */
/* defined at discord/application_commands.json:22:5 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_application_command_types_print(enum discord_application_command_types code)`
 *   * :code:`enum discord_application_command_types discord_application_command_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_application_command_types {
  DISCORD_APPLICATION_COMMAND_CHAT_INPUT = 1, /**< Slash commands; a text-based command that shows up when a user types / */
  DISCORD_APPLICATION_COMMAND_USER = 2, /**< A UI-based command that shows up when you right click or tap on a user */
  DISCORD_APPLICATION_COMMAND_MESSAGE = 3, /**< A UI-based command that shows up when you right lick or tap on a message */
};
extern char* discord_application_command_types_print(enum discord_application_command_types);
extern enum discord_application_command_types discord_application_command_types_eval(char*);
extern void discord_application_command_types_list_free_v(void **p);
extern void discord_application_command_types_list_free(enum discord_application_command_types **p);
extern void discord_application_command_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_types_list_from_json(char *str, size_t len, enum discord_application_command_types ***p);
extern size_t discord_application_command_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_types_list_to_json(char *str, size_t len, enum discord_application_command_types **p);

/* Application Command Option Structure */
/* defined at discord/application_commands.json:38:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_option_init(struct discord_application_command_option *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_option_cleanup(struct discord_application_command_option *)`
 *     * :code:`void discord_application_command_option_list_free(struct discord_application_command_option **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_option_from_json(char *rbuf, size_t len, struct discord_application_command_option *)`
 *     * :code:`void discord_application_command_option_list_from_json(char *rbuf, size_t len, struct discord_application_command_option ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_option_to_json(char *wbuf, size_t len, struct discord_application_command_option *)`
 *     * :code:`void discord_application_command_option_list_to_json(char *wbuf, size_t len, struct discord_application_command_option **)`
 * @endverbatim
 */
struct discord_application_command_option {
  /* discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  enum discord_application_command_option_types type; /**< value of application command option type */

  /* discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 lowercase character"}' */
  char *name; /**< 1-32 lowercase character */

  /* discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description"}' */
  char *description; /**< 1-100 character description */

  /* discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
  bool required; /**< if the parameter is required or optional -- default false */

  /* discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  struct discord_application_command_option_choice **choices; /**< choices for string and int types for the user to pick from */

  /* discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  struct discord_application_command_option **options; /**< if the option is a subcommand or subcommand group type, this nested options will be the parameters */

  /* discord/application_commands.json:47:18
     '{"name":"channel_types", "type":{"base":"ja_u64", "dec":"ntl"}, "comment":"if the option is a channel type, the channels shown will be restricted to these types", "inject_if_not":null}' */
  ja_u64 **channel_types; /**< if the option is a channel type, the channels shown will be restricted to these types */

  /* discord/application_commands.json:48:18
     '{"name":"min_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the minimum value permitted", "inject_if_not":null}' */
  json_char_t* min_value; /**< if the option is an INTEGER or NUMBER type, the minimum value permitted */

  /* discord/application_commands.json:49:18
     '{"name":"max_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the maximum value permitted", "inject_if_not":null}' */
  json_char_t* max_value; /**< if the option is an INTEGER or NUMBER type, the maximum value permitted */

  /* discord/application_commands.json:50:18
     '{"name":"autocomplete", "type":{"base":"bool"}, "comment":"enable autocomplete interactions for this option", "inject_if_not":false}' */
  bool autocomplete; /**< enable autocomplete interactions for this option */

};
extern void discord_application_command_option_cleanup_v(void *p);
extern void discord_application_command_option_cleanup(struct discord_application_command_option *p);
extern void discord_application_command_option_init_v(void *p);
extern void discord_application_command_option_init(struct discord_application_command_option *p);
extern void discord_application_command_option_from_json_v(char *json, size_t len, void *p);
extern void discord_application_command_option_from_json_p(char *json, size_t len, struct discord_application_command_option **pp);
extern void discord_application_command_option_from_json(char *json, size_t len, struct discord_application_command_option *p);
extern size_t discord_application_command_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_to_json(char *json, size_t len, struct discord_application_command_option *p);
extern void discord_application_command_option_list_free_v(void **p);
extern void discord_application_command_option_list_free(struct discord_application_command_option **p);
extern void discord_application_command_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_option_list_from_json(char *str, size_t len, struct discord_application_command_option ***p);
extern size_t discord_application_command_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_option_list_to_json(char *str, size_t len, struct discord_application_command_option **p);


/* Application Command Option Type */
/* defined at discord/application_commands.json:53:5 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-type
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_application_command_option_types_print(enum discord_application_command_option_types code)`
 *   * :code:`enum discord_application_command_option_types discord_application_command_option_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_application_command_option_types {
  DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND = 1,
  DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND_GROUP = 2,
  DISCORD_APPLICATION_COMMAND_OPTION_STRING = 3,
  DISCORD_APPLICATION_COMMAND_OPTION_INTEGER = 4, /**< Any integer between -2^53 and 2^53 */
  DISCORD_APPLICATION_COMMAND_OPTION_BOOLEAN = 5,
  DISCORD_APPLICATION_COMMAND_OPTION_USER = 6,
  DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL = 7, /**< Includes all channel types + categories */
  DISCORD_APPLICATION_COMMAND_OPTION_ROLE = 8,
  DISCORD_APPLICATION_COMMAND_OPTION_MENTIONABLE = 9, /**< Includes users and roles */
  DISCORD_APPLICATION_COMMAND_OPTION_NUMBER = 10, /**< Any double between -2^53 and 2^53 */
};
extern char* discord_application_command_option_types_print(enum discord_application_command_option_types);
extern enum discord_application_command_option_types discord_application_command_option_types_eval(char*);
extern void discord_application_command_option_types_list_free_v(void **p);
extern void discord_application_command_option_types_list_free(enum discord_application_command_option_types **p);
extern void discord_application_command_option_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_option_types_list_from_json(char *str, size_t len, enum discord_application_command_option_types ***p);
extern size_t discord_application_command_option_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_option_types_list_to_json(char *str, size_t len, enum discord_application_command_option_types **p);

/* Application Command Option Choice Structure */
/* defined at discord/application_commands.json:76:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-choice-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_option_choice_init(struct discord_application_command_option_choice *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_option_choice_cleanup(struct discord_application_command_option_choice *)`
 *     * :code:`void discord_application_command_option_choice_list_free(struct discord_application_command_option_choice **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_option_choice_from_json(char *rbuf, size_t len, struct discord_application_command_option_choice *)`
 *     * :code:`void discord_application_command_option_choice_list_from_json(char *rbuf, size_t len, struct discord_application_command_option_choice ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_option_choice_to_json(char *wbuf, size_t len, struct discord_application_command_option_choice *)`
 *     * :code:`void discord_application_command_option_choice_list_to_json(char *wbuf, size_t len, struct discord_application_command_option_choice **)`
 * @endverbatim
 */
struct discord_application_command_option_choice {
  /* discord/application_commands.json:79:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character choice name"}' */
  char *name; /**< 1-100 character choice name */

  /* discord/application_commands.json:80:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
  json_char_t* value; /**< value of choice, up to 100 characters if string */

};
extern void discord_application_command_option_choice_cleanup_v(void *p);
extern void discord_application_command_option_choice_cleanup(struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_init_v(void *p);
extern void discord_application_command_option_choice_init(struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_from_json_v(char *json, size_t len, void *p);
extern void discord_application_command_option_choice_from_json_p(char *json, size_t len, struct discord_application_command_option_choice **pp);
extern void discord_application_command_option_choice_from_json(char *json, size_t len, struct discord_application_command_option_choice *p);
extern size_t discord_application_command_option_choice_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_choice_to_json(char *json, size_t len, struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_list_free_v(void **p);
extern void discord_application_command_option_choice_list_free(struct discord_application_command_option_choice **p);
extern void discord_application_command_option_choice_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_option_choice_list_from_json(char *str, size_t len, struct discord_application_command_option_choice ***p);
extern size_t discord_application_command_option_choice_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_option_choice_list_to_json(char *str, size_t len, struct discord_application_command_option_choice **p);

/* Guild Application Command Permissions Structure */
/* defined at discord/application_commands.json:87:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-guild-application-command-permissions-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_application_command_permissions_cleanup(struct discord_guild_application_command_permissions *)`
 *     * :code:`void discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_application_command_permissions_from_json(char *rbuf, size_t len, struct discord_guild_application_command_permissions *)`
 *     * :code:`void discord_guild_application_command_permissions_list_from_json(char *rbuf, size_t len, struct discord_guild_application_command_permissions ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_application_command_permissions_to_json(char *wbuf, size_t len, struct discord_guild_application_command_permissions *)`
 *     * :code:`void discord_guild_application_command_permissions_list_to_json(char *wbuf, size_t len, struct discord_guild_application_command_permissions **)`
 * @endverbatim
 */
struct discord_guild_application_command_permissions {
  /* discord/application_commands.json:90:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  u64_snowflake_t id; /**< the id of the command */

  /* discord/application_commands.json:91:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  u64_snowflake_t application_id; /**< the id of the parent application the command belongs to */

  /* discord/application_commands.json:92:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  u64_snowflake_t guild_id; /**< the id of the guild */

  /* discord/application_commands.json:93:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  struct discord_application_command_permissions **permissions; /**< the permissions for the command in the guild */

};
extern void discord_guild_application_command_permissions_cleanup_v(void *p);
extern void discord_guild_application_command_permissions_cleanup(struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_init_v(void *p);
extern void discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_application_command_permissions_from_json_p(char *json, size_t len, struct discord_guild_application_command_permissions **pp);
extern void discord_guild_application_command_permissions_from_json(char *json, size_t len, struct discord_guild_application_command_permissions *p);
extern size_t discord_guild_application_command_permissions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_to_json(char *json, size_t len, struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_list_free_v(void **p);
extern void discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions **p);
extern void discord_guild_application_command_permissions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_application_command_permissions_list_from_json(char *str, size_t len, struct discord_guild_application_command_permissions ***p);
extern size_t discord_guild_application_command_permissions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_list_to_json(char *str, size_t len, struct discord_guild_application_command_permissions **p);

/* Application Command Permissions Structure */
/* defined at discord/application_commands.json:100:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-application-command-permissions-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_permissions_init(struct discord_application_command_permissions *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_permissions_cleanup(struct discord_application_command_permissions *)`
 *     * :code:`void discord_application_command_permissions_list_free(struct discord_application_command_permissions **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_permissions_from_json(char *rbuf, size_t len, struct discord_application_command_permissions *)`
 *     * :code:`void discord_application_command_permissions_list_from_json(char *rbuf, size_t len, struct discord_application_command_permissions ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_permissions_to_json(char *wbuf, size_t len, struct discord_application_command_permissions *)`
 *     * :code:`void discord_application_command_permissions_list_to_json(char *wbuf, size_t len, struct discord_application_command_permissions **)`
 * @endverbatim
 */
struct discord_application_command_permissions {
  /* discord/application_commands.json:103:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  u64_snowflake_t id; /**< the id of the command */

  /* discord/application_commands.json:104:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  enum discord_application_command_permission_types type; /**< role or user */

  /* discord/application_commands.json:105:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  bool permission; /**< true to allow, false, to disallow */

};
extern void discord_application_command_permissions_cleanup_v(void *p);
extern void discord_application_command_permissions_cleanup(struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_init_v(void *p);
extern void discord_application_command_permissions_init(struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_from_json_v(char *json, size_t len, void *p);
extern void discord_application_command_permissions_from_json_p(char *json, size_t len, struct discord_application_command_permissions **pp);
extern void discord_application_command_permissions_from_json(char *json, size_t len, struct discord_application_command_permissions *p);
extern size_t discord_application_command_permissions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_permissions_to_json(char *json, size_t len, struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_list_free_v(void **p);
extern void discord_application_command_permissions_list_free(struct discord_application_command_permissions **p);
extern void discord_application_command_permissions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_permissions_list_from_json(char *str, size_t len, struct discord_application_command_permissions ***p);
extern size_t discord_application_command_permissions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_permissions_list_to_json(char *str, size_t len, struct discord_application_command_permissions **p);


/* Application Command Permission Type */
/* defined at discord/application_commands.json:108:5 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-application-command-permission-type
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_application_command_permission_types_print(enum discord_application_command_permission_types code)`
 *   * :code:`enum discord_application_command_permission_types discord_application_command_permission_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_application_command_permission_types {
  DISCORD_APPLICATION_COMMAND_PERMISSION_ROLE = 1,
  DISCORD_APPLICATION_COMMAND_PERMISSION_USER = 2,
};
extern char* discord_application_command_permission_types_print(enum discord_application_command_permission_types);
extern enum discord_application_command_permission_types discord_application_command_permission_types_eval(char*);
extern void discord_application_command_permission_types_list_free_v(void **p);
extern void discord_application_command_permission_types_list_free(enum discord_application_command_permission_types **p);
extern void discord_application_command_permission_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_permission_types_list_from_json(char *str, size_t len, enum discord_application_command_permission_types ***p);
extern size_t discord_application_command_permission_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_permission_types_list_to_json(char *str, size_t len, enum discord_application_command_permission_types **p);

/* Application Command Interaction Data Option Structure */
/* defined at discord/application_commands.json:123:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-interaction-data-option-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option *)`
 *     * :code:`void discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_interaction_data_option_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_option *)`
 *     * :code:`void discord_application_command_interaction_data_option_list_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_option ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_interaction_data_option_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_option *)`
 *     * :code:`void discord_application_command_interaction_data_option_list_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_option **)`
 * @endverbatim
 */
struct discord_application_command_interaction_data_option {
  /* discord/application_commands.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  char *name; /**< the name of the parameter */

  /* discord/application_commands.json:127:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  enum discord_application_command_option_types type; /**< value of application command option type */

  /* discord/application_commands.json:128:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
  json_char_t* value; /**< the value of the pair */

  /* discord/application_commands.json:129:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_option **options; /**< present if this option is a group or subcommand */

};
extern void discord_application_command_interaction_data_option_cleanup_v(void *p);
extern void discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_init_v(void *p);
extern void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_from_json_v(char *json, size_t len, void *p);
extern void discord_application_command_interaction_data_option_from_json_p(char *json, size_t len, struct discord_application_command_interaction_data_option **pp);
extern void discord_application_command_interaction_data_option_from_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p);
extern size_t discord_application_command_interaction_data_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_to_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_list_free_v(void **p);
extern void discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option **p);
extern void discord_application_command_interaction_data_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_interaction_data_option_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_option ***p);
extern size_t discord_application_command_interaction_data_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_option **p);
