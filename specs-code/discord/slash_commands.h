/* This file is generated from specs/discord/slash_commands.json, Please don't edit it. */
/**
 * @file specs-code/discord/slash_commands.h
 * @see https://discord.com/developers/docs/interactions/slash-commands#data-models-and-types
 */


// Application Command Structure
// defined at specs/discord/slash_commands.json:9:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-structure

 * - Initializer:
 *   - <tt>discord_application_command_init(struct discord_application_command*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_cleanup(struct discord_application_command*)</tt>
 *   - <tt>discord_application_command_list_free(struct discord_application_command**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_from_json(char *rbuf, size_t len, struct discord_application_command**)</tt>
 *   - <tt>discord_application_command_list_from_json(char *rbuf, size_t len, struct discord_application_command***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_to_json(char *wbuf, size_t len, struct discord_application_command *p)</tt>
 *   - <tt>discord_application_command_list_to_json(char *wbuf, size_t len, struct discord_application_command**)</tt>
 */
struct discord_application_command {
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  u64_snowflake_t id; ///< unique id of the command

  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  u64_snowflake_t application_id; ///< unique id of the parent application

  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */
  u64_snowflake_t guild_id; ///< unique id of the command, if not global

  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  char name[32+1]; ///< 1-32 lowercase character

  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  char description[100+1]; ///< 1-100 character description

  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */
  struct discord_application_command_option **options; ///< the parameters for the command

  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  bool default_permission; ///< whether the command is enabled by default when the app is added to a guild

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};
extern void discord_application_command_cleanup_v(void *p);
extern void discord_application_command_cleanup(struct discord_application_command *p);
extern void discord_application_command_init_v(void *p);
extern void discord_application_command_init(struct discord_application_command *p);
extern void discord_application_command_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_from_json(char *json, size_t len, struct discord_application_command **pp);
extern size_t discord_application_command_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_to_json(char *json, size_t len, struct discord_application_command *p);
extern size_t discord_application_command_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_to_query(char *json, size_t len, struct discord_application_command *p);
extern void discord_application_command_list_free_v(void **p);
extern void discord_application_command_list_free(struct discord_application_command **p);
extern void discord_application_command_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_list_from_json(char *str, size_t len, struct discord_application_command ***p);
extern size_t discord_application_command_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_list_to_json(char *str, size_t len, struct discord_application_command **p);

// Application Command Option Structure
// defined at specs/discord/slash_commands.json:25:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-option-structure

 * - Initializer:
 *   - <tt>discord_application_command_option_init(struct discord_application_command_option*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_option_cleanup(struct discord_application_command_option*)</tt>
 *   - <tt>discord_application_command_option_list_free(struct discord_application_command_option**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_option_from_json(char *rbuf, size_t len, struct discord_application_command_option**)</tt>
 *   - <tt>discord_application_command_option_list_from_json(char *rbuf, size_t len, struct discord_application_command_option***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_option_to_json(char *wbuf, size_t len, struct discord_application_command_option *p)</tt>
 *   - <tt>discord_application_command_option_list_to_json(char *wbuf, size_t len, struct discord_application_command_option**)</tt>
 */
struct discord_application_command_option {
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  enum discord_application_command_option_types type; ///< value of application command option type

  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  char name[32+1]; ///< 1-32 lowercase character

  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  char description[100+1]; ///< 1-100 character description

  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */
  bool required; ///< if the paramter is required or optional -- default false

  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  struct discord_application_command_option_choice **choices; ///< choices for string and int types for the user to pick from

  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  struct discord_application_command_option **options; ///< if the option is a subcommand or subcommand group type, this nested options will be the parameters

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};
extern void discord_application_command_option_cleanup_v(void *p);
extern void discord_application_command_option_cleanup(struct discord_application_command_option *p);
extern void discord_application_command_option_init_v(void *p);
extern void discord_application_command_option_init(struct discord_application_command_option *p);
extern void discord_application_command_option_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_option_from_json(char *json, size_t len, struct discord_application_command_option **pp);
extern size_t discord_application_command_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_to_json(char *json, size_t len, struct discord_application_command_option *p);
extern size_t discord_application_command_option_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_to_query(char *json, size_t len, struct discord_application_command_option *p);
extern void discord_application_command_option_list_free_v(void **p);
extern void discord_application_command_option_list_free(struct discord_application_command_option **p);
extern void discord_application_command_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_option_list_from_json(char *str, size_t len, struct discord_application_command_option ***p);
extern size_t discord_application_command_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_option_list_to_json(char *str, size_t len, struct discord_application_command_option **p);


enum discord_application_command_option_types {
  DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND = 1,
  DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND_GROUP = 2,
  DISCORD_APPLICATION_COMMAND_OPTION_STRING = 3,
  DISCORD_APPLICATION_COMMAND_OPTION_INTEGER = 4,
  DISCORD_APPLICATION_COMMAND_OPTION_BOOLEAN = 5,
  DISCORD_APPLICATION_COMMAND_OPTION_USER = 6,
  DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL = 7,
  DISCORD_APPLICATION_COMMAND_OPTION_ROLE = 8,
  DISCORD_APPLICATION_COMMAND_OPTION_MENTIONABLE = 9,
};
extern char* discord_application_command_option_types_to_string(enum discord_application_command_option_types);
extern enum discord_application_command_option_types discord_application_command_option_types_from_string(char*);
extern bool discord_application_command_option_types_has(enum discord_application_command_option_types, char*);

// Application Command Option Choice Structure
// defined at specs/discord/slash_commands.json:58:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-option-choice-structure

 * - Initializer:
 *   - <tt>discord_application_command_option_choice_init(struct discord_application_command_option_choice*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_option_choice_cleanup(struct discord_application_command_option_choice*)</tt>
 *   - <tt>discord_application_command_option_choice_list_free(struct discord_application_command_option_choice**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_option_choice_from_json(char *rbuf, size_t len, struct discord_application_command_option_choice**)</tt>
 *   - <tt>discord_application_command_option_choice_list_from_json(char *rbuf, size_t len, struct discord_application_command_option_choice***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_option_choice_to_json(char *wbuf, size_t len, struct discord_application_command_option_choice *p)</tt>
 *   - <tt>discord_application_command_option_choice_list_to_json(char *wbuf, size_t len, struct discord_application_command_option_choice**)</tt>
 */
struct discord_application_command_option_choice {
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
  char name[100+1]; ///< 1-100 character choice name

  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */
  char value[100+1]; ///< value of choice, up to 100 characters

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
extern void discord_application_command_option_choice_cleanup_v(void *p);
extern void discord_application_command_option_choice_cleanup(struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_init_v(void *p);
extern void discord_application_command_option_choice_init(struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_option_choice_from_json(char *json, size_t len, struct discord_application_command_option_choice **pp);
extern size_t discord_application_command_option_choice_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_choice_to_json(char *json, size_t len, struct discord_application_command_option_choice *p);
extern size_t discord_application_command_option_choice_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_choice_to_query(char *json, size_t len, struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_list_free_v(void **p);
extern void discord_application_command_option_choice_list_free(struct discord_application_command_option_choice **p);
extern void discord_application_command_option_choice_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_option_choice_list_from_json(char *str, size_t len, struct discord_application_command_option_choice ***p);
extern size_t discord_application_command_option_choice_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_option_choice_list_to_json(char *str, size_t len, struct discord_application_command_option_choice **p);

// Guild Application Command Permissions Structure
// defined at specs/discord/slash_commands.json:69:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-permissions-object-guild-application-command-permissions-structure

 * - Initializer:
 *   - <tt>discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_application_command_permissions_cleanup(struct discord_guild_application_command_permissions*)</tt>
 *   - <tt>discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_application_command_permissions_from_json(char *rbuf, size_t len, struct discord_guild_application_command_permissions**)</tt>
 *   - <tt>discord_guild_application_command_permissions_list_from_json(char *rbuf, size_t len, struct discord_guild_application_command_permissions***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_application_command_permissions_to_json(char *wbuf, size_t len, struct discord_guild_application_command_permissions *p)</tt>
 *   - <tt>discord_guild_application_command_permissions_list_to_json(char *wbuf, size_t len, struct discord_guild_application_command_permissions**)</tt>
 */
struct discord_guild_application_command_permissions {
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  u64_snowflake_t id; ///< the id of the command

  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  u64_snowflake_t application_id; ///< the id of the parent application the command belongs to

  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  u64_snowflake_t guild_id; ///< the id of the guild

  /* specs/discord/slash_commands.json:75:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  struct discord_application_command_permissions **permissions; ///< the permissions for the command in the guild

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
extern void discord_guild_application_command_permissions_cleanup_v(void *p);
extern void discord_guild_application_command_permissions_cleanup(struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_init_v(void *p);
extern void discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_application_command_permissions_from_json(char *json, size_t len, struct discord_guild_application_command_permissions **pp);
extern size_t discord_guild_application_command_permissions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_to_json(char *json, size_t len, struct discord_guild_application_command_permissions *p);
extern size_t discord_guild_application_command_permissions_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_to_query(char *json, size_t len, struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_list_free_v(void **p);
extern void discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions **p);
extern void discord_guild_application_command_permissions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_application_command_permissions_list_from_json(char *str, size_t len, struct discord_guild_application_command_permissions ***p);
extern size_t discord_guild_application_command_permissions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_list_to_json(char *str, size_t len, struct discord_guild_application_command_permissions **p);

// Application Command Permissions Structure
// defined at specs/discord/slash_commands.json:82:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-permissions-object-guild-application-command-permissions-structure

 * - Initializer:
 *   - <tt>discord_application_command_permissions_init(struct discord_application_command_permissions*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_permissions_cleanup(struct discord_application_command_permissions*)</tt>
 *   - <tt>discord_application_command_permissions_list_free(struct discord_application_command_permissions**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_permissions_from_json(char *rbuf, size_t len, struct discord_application_command_permissions**)</tt>
 *   - <tt>discord_application_command_permissions_list_from_json(char *rbuf, size_t len, struct discord_application_command_permissions***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_permissions_to_json(char *wbuf, size_t len, struct discord_application_command_permissions *p)</tt>
 *   - <tt>discord_application_command_permissions_list_to_json(char *wbuf, size_t len, struct discord_application_command_permissions**)</tt>
 */
struct discord_application_command_permissions {
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  u64_snowflake_t id; ///< the id of the command

  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  enum discord_application_command_permission_types type; ///< role or user

  /* specs/discord/slash_commands.json:87:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  bool permission; ///< true to allow, false, to disallow

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};
extern void discord_application_command_permissions_cleanup_v(void *p);
extern void discord_application_command_permissions_cleanup(struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_init_v(void *p);
extern void discord_application_command_permissions_init(struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_permissions_from_json(char *json, size_t len, struct discord_application_command_permissions **pp);
extern size_t discord_application_command_permissions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_permissions_to_json(char *json, size_t len, struct discord_application_command_permissions *p);
extern size_t discord_application_command_permissions_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_permissions_to_query(char *json, size_t len, struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_list_free_v(void **p);
extern void discord_application_command_permissions_list_free(struct discord_application_command_permissions **p);
extern void discord_application_command_permissions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_permissions_list_from_json(char *str, size_t len, struct discord_application_command_permissions ***p);
extern size_t discord_application_command_permissions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_permissions_list_to_json(char *str, size_t len, struct discord_application_command_permissions **p);


enum discord_application_command_permission_types {
  DISCORD_APPLICATION_COMMAND_PERMISSION_ROLE = 1,
  DISCORD_APPLICATION_COMMAND_PERMISSION_USER = 2,
};
extern char* discord_application_command_permission_types_to_string(enum discord_application_command_permission_types);
extern enum discord_application_command_permission_types discord_application_command_permission_types_from_string(char*);
extern bool discord_application_command_permission_types_has(enum discord_application_command_permission_types, char*);

// Interaction Structure
// defined at specs/discord/slash_commands.json:104:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-interaction-structure

 * - Initializer:
 *   - <tt>discord_interaction_init(struct discord_interaction*)</tt>
 * - Cleanup:
 *   - <tt>discord_interaction_cleanup(struct discord_interaction*)</tt>
 *   - <tt>discord_interaction_list_free(struct discord_interaction**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_interaction_from_json(char *rbuf, size_t len, struct discord_interaction**)</tt>
 *   - <tt>discord_interaction_list_from_json(char *rbuf, size_t len, struct discord_interaction***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_interaction_to_json(char *wbuf, size_t len, struct discord_interaction *p)</tt>
 *   - <tt>discord_interaction_list_to_json(char *wbuf, size_t len, struct discord_interaction**)</tt>
 */
struct discord_interaction {
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  u64_snowflake_t id; ///< id of the interaction

  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
  u64_snowflake_t application_id; ///< id of the application this iteraction is for

  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
  enum discord_interaction_request_types type; ///< the request type of the interaction

  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  struct discord_application_command_interaction_data *data; ///< the command data payload

  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
  u64_snowflake_t guild_id; ///< the guild it was sent from

  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
  u64_snowflake_t channel_id; ///< the channel it was sent from

  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  struct discord_guild_member *member; ///< guild member data for the invoking user, including permissions

  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  struct discord_user *user; ///< user object for the invoking user, if invoked in a DM

  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
  char *token; ///< a continuation token for responding to the interaction

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};
extern void discord_interaction_cleanup_v(void *p);
extern void discord_interaction_cleanup(struct discord_interaction *p);
extern void discord_interaction_init_v(void *p);
extern void discord_interaction_init(struct discord_interaction *p);
extern void discord_interaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_from_json(char *json, size_t len, struct discord_interaction **pp);
extern size_t discord_interaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_to_json(char *json, size_t len, struct discord_interaction *p);
extern size_t discord_interaction_to_query_v(char *json, size_t len, void *p);
extern size_t discord_interaction_to_query(char *json, size_t len, struct discord_interaction *p);
extern void discord_interaction_list_free_v(void **p);
extern void discord_interaction_list_free(struct discord_interaction **p);
extern void discord_interaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_list_from_json(char *str, size_t len, struct discord_interaction ***p);
extern size_t discord_interaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_list_to_json(char *str, size_t len, struct discord_interaction **p);


enum discord_interaction_request_types {
  DISCORD_INTERACTION_PING = 1,
  DISCORD_INTERACTION_APPLICATION_COMMAND = 2,
  DISCORD_INTERACTION_MESSAGE_COMPONENT = 3,
};
extern char* discord_interaction_request_types_to_string(enum discord_interaction_request_types);
extern enum discord_interaction_request_types discord_interaction_request_types_from_string(char*);
extern bool discord_interaction_request_types_has(enum discord_interaction_request_types, char*);

// Application Command Interaction Data Structure
// defined at specs/discord/slash_commands.json:134:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-structure

 * - Initializer:
 *   - <tt>discord_application_command_interaction_data_init(struct discord_application_command_interaction_data*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_interaction_data_cleanup(struct discord_application_command_interaction_data*)</tt>
 *   - <tt>discord_application_command_interaction_data_list_free(struct discord_application_command_interaction_data**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_interaction_data_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data**)</tt>
 *   - <tt>discord_application_command_interaction_data_list_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_interaction_data_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data *p)</tt>
 *   - <tt>discord_application_command_interaction_data_list_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data**)</tt>
 */
struct discord_application_command_interaction_data {
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
  u64_snowflake_t id; ///< the ID of the invoked command

  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
  char *name; ///< the name of the invoked command

  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_resolved *resolved; ///< converted users + roles + channels

  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_option **options; ///< the params + values from the user

  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */
  char custom_id[100+1]; ///< a developer-defined identifier for the component, max 100 characters

  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */
  enum discord_component_types type; ///< component type

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};
extern void discord_application_command_interaction_data_cleanup_v(void *p);
extern void discord_application_command_interaction_data_cleanup(struct discord_application_command_interaction_data *p);
extern void discord_application_command_interaction_data_init_v(void *p);
extern void discord_application_command_interaction_data_init(struct discord_application_command_interaction_data *p);
extern void discord_application_command_interaction_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_interaction_data_from_json(char *json, size_t len, struct discord_application_command_interaction_data **pp);
extern size_t discord_application_command_interaction_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_to_json(char *json, size_t len, struct discord_application_command_interaction_data *p);
extern size_t discord_application_command_interaction_data_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_to_query(char *json, size_t len, struct discord_application_command_interaction_data *p);
extern void discord_application_command_interaction_data_list_free_v(void **p);
extern void discord_application_command_interaction_data_list_free(struct discord_application_command_interaction_data **p);
extern void discord_application_command_interaction_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_interaction_data_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data ***p);
extern size_t discord_application_command_interaction_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_interaction_data_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data **p);

// Application Command Interaction Data Resolved Structure
// defined at specs/discord/slash_commands.json:149:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-resolved-structure

 * - Initializer:
 *   - <tt>discord_application_command_interaction_data_resolved_init(struct discord_application_command_interaction_data_resolved*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_interaction_data_resolved_cleanup(struct discord_application_command_interaction_data_resolved*)</tt>
 *   - <tt>discord_application_command_interaction_data_resolved_list_free(struct discord_application_command_interaction_data_resolved**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_interaction_data_resolved_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_resolved**)</tt>
 *   - <tt>discord_application_command_interaction_data_resolved_list_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_resolved***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_interaction_data_resolved_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_resolved *p)</tt>
 *   - <tt>discord_application_command_interaction_data_resolved_list_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_resolved**)</tt>
 */
struct discord_application_command_interaction_data_resolved {
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
  ja_str **users; ///< the ids and User objects

  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
  ja_str **members; ///< the ids and partial Member objects

  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
  ja_str **roles; ///< the ids and Role objects

  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
  ja_str **channels; ///< the ids and partial Channel objects

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
extern void discord_application_command_interaction_data_resolved_cleanup_v(void *p);
extern void discord_application_command_interaction_data_resolved_cleanup(struct discord_application_command_interaction_data_resolved *p);
extern void discord_application_command_interaction_data_resolved_init_v(void *p);
extern void discord_application_command_interaction_data_resolved_init(struct discord_application_command_interaction_data_resolved *p);
extern void discord_application_command_interaction_data_resolved_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_interaction_data_resolved_from_json(char *json, size_t len, struct discord_application_command_interaction_data_resolved **pp);
extern size_t discord_application_command_interaction_data_resolved_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_resolved_to_json(char *json, size_t len, struct discord_application_command_interaction_data_resolved *p);
extern size_t discord_application_command_interaction_data_resolved_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_resolved_to_query(char *json, size_t len, struct discord_application_command_interaction_data_resolved *p);
extern void discord_application_command_interaction_data_resolved_list_free_v(void **p);
extern void discord_application_command_interaction_data_resolved_list_free(struct discord_application_command_interaction_data_resolved **p);
extern void discord_application_command_interaction_data_resolved_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_interaction_data_resolved_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_resolved ***p);
extern size_t discord_application_command_interaction_data_resolved_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_interaction_data_resolved_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_resolved **p);

// Application Command Interaction Data Option Structure
// defined at specs/discord/slash_commands.json:162:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-option-structure

 * - Initializer:
 *   - <tt>discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option*)</tt>
 *   - <tt>discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_interaction_data_option_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_option**)</tt>
 *   - <tt>discord_application_command_interaction_data_option_list_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_option***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_interaction_data_option_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_option *p)</tt>
 *   - <tt>discord_application_command_interaction_data_option_list_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_option**)</tt>
 */
struct discord_application_command_interaction_data_option {
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  char *name; ///< the name of the parameter

  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  enum discord_application_command_option_types type; ///< value of application command option type

  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */
  enum discord_application_command_option_types value; ///< the value of the pair

  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_option **options; ///< present if this option is a group or subcommand

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
extern void discord_application_command_interaction_data_option_cleanup_v(void *p);
extern void discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_init_v(void *p);
extern void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_interaction_data_option_from_json(char *json, size_t len, struct discord_application_command_interaction_data_option **pp);
extern size_t discord_application_command_interaction_data_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_to_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p);
extern size_t discord_application_command_interaction_data_option_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_to_query(char *json, size_t len, struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_list_free_v(void **p);
extern void discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option **p);
extern void discord_application_command_interaction_data_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_interaction_data_option_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_option ***p);
extern size_t discord_application_command_interaction_data_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_option **p);

// Interaction Response Structure
// defined at specs/discord/slash_commands.json:175:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-response-object-interaction-response-structure

 * - Initializer:
 *   - <tt>discord_interaction_response_init(struct discord_interaction_response*)</tt>
 * - Cleanup:
 *   - <tt>discord_interaction_response_cleanup(struct discord_interaction_response*)</tt>
 *   - <tt>discord_interaction_response_list_free(struct discord_interaction_response**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_interaction_response_from_json(char *rbuf, size_t len, struct discord_interaction_response**)</tt>
 *   - <tt>discord_interaction_response_list_from_json(char *rbuf, size_t len, struct discord_interaction_response***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_interaction_response_to_json(char *wbuf, size_t len, struct discord_interaction_response *p)</tt>
 *   - <tt>discord_interaction_response_list_to_json(char *wbuf, size_t len, struct discord_interaction_response**)</tt>
 */
struct discord_interaction_response {
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
  enum discord_interaction_callback_types type; ///< the type of response

  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  struct discord_interaction_application_command_callback_data *data; ///< an optional response message

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
extern void discord_interaction_response_cleanup_v(void *p);
extern void discord_interaction_response_cleanup(struct discord_interaction_response *p);
extern void discord_interaction_response_init_v(void *p);
extern void discord_interaction_response_init(struct discord_interaction_response *p);
extern void discord_interaction_response_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_response_from_json(char *json, size_t len, struct discord_interaction_response **pp);
extern size_t discord_interaction_response_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_response_to_json(char *json, size_t len, struct discord_interaction_response *p);
extern size_t discord_interaction_response_to_query_v(char *json, size_t len, void *p);
extern size_t discord_interaction_response_to_query(char *json, size_t len, struct discord_interaction_response *p);
extern void discord_interaction_response_list_free_v(void **p);
extern void discord_interaction_response_list_free(struct discord_interaction_response **p);
extern void discord_interaction_response_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_response_list_from_json(char *str, size_t len, struct discord_interaction_response ***p);
extern size_t discord_interaction_response_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_response_list_to_json(char *str, size_t len, struct discord_interaction_response **p);


enum discord_interaction_callback_types {
  DISCORD_INTERACTION_CALLBACK_PONG = 1, // ACK a Ping
  DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE = 4, // respond to a interaction with a message
  DISCORD_INTERACTION_CALLBACK_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE = 5, // ACK an interaction and edit a response later, the user sees a loading state
  DISCORD_INTERACTION_CALLBACK_DEFERRED_UPDATE_MESSAGE = 6, // for components, ACK an interaction and edit the original message later; the user does not see a loading state
  DISCORD_INTERACTION_CALLBACK_UPDATE_MESSAGE = 7, // for components, edit the message the component was attached to
};
extern char* discord_interaction_callback_types_to_string(enum discord_interaction_callback_types);
extern enum discord_interaction_callback_types discord_interaction_callback_types_from_string(char*);
extern bool discord_interaction_callback_types_has(enum discord_interaction_callback_types, char*);

// Interaction Application Command Callback Data Structure
// defined at specs/discord/slash_commands.json:200:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-response-object-interaction-application-command-callback-data-structure

 * - Initializer:
 *   - <tt>discord_interaction_application_command_callback_data_init(struct discord_interaction_application_command_callback_data*)</tt>
 * - Cleanup:
 *   - <tt>discord_interaction_application_command_callback_data_cleanup(struct discord_interaction_application_command_callback_data*)</tt>
 *   - <tt>discord_interaction_application_command_callback_data_list_free(struct discord_interaction_application_command_callback_data**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_interaction_application_command_callback_data_from_json(char *rbuf, size_t len, struct discord_interaction_application_command_callback_data**)</tt>
 *   - <tt>discord_interaction_application_command_callback_data_list_from_json(char *rbuf, size_t len, struct discord_interaction_application_command_callback_data***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_interaction_application_command_callback_data_to_json(char *wbuf, size_t len, struct discord_interaction_application_command_callback_data *p)</tt>
 *   - <tt>discord_interaction_application_command_callback_data_list_to_json(char *wbuf, size_t len, struct discord_interaction_application_command_callback_data**)</tt>
 */
struct discord_interaction_application_command_callback_data {
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
  bool tts; ///< is the response TTS

  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
  char *content; ///< message content

  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
  struct discord_embed **embeds; ///< support up to 10 embeds

  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  // @todo allowed_mentions allowed mentions object;

  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
  enum discord_interaction_application_command_callback_data_flags flags; ///< interaction application command callback data flags

  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
  struct discord_component **components; ///< message components

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};
extern void discord_interaction_application_command_callback_data_cleanup_v(void *p);
extern void discord_interaction_application_command_callback_data_cleanup(struct discord_interaction_application_command_callback_data *p);
extern void discord_interaction_application_command_callback_data_init_v(void *p);
extern void discord_interaction_application_command_callback_data_init(struct discord_interaction_application_command_callback_data *p);
extern void discord_interaction_application_command_callback_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_application_command_callback_data_from_json(char *json, size_t len, struct discord_interaction_application_command_callback_data **pp);
extern size_t discord_interaction_application_command_callback_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_application_command_callback_data_to_json(char *json, size_t len, struct discord_interaction_application_command_callback_data *p);
extern size_t discord_interaction_application_command_callback_data_to_query_v(char *json, size_t len, void *p);
extern size_t discord_interaction_application_command_callback_data_to_query(char *json, size_t len, struct discord_interaction_application_command_callback_data *p);
extern void discord_interaction_application_command_callback_data_list_free_v(void **p);
extern void discord_interaction_application_command_callback_data_list_free(struct discord_interaction_application_command_callback_data **p);
extern void discord_interaction_application_command_callback_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_application_command_callback_data_list_from_json(char *str, size_t len, struct discord_interaction_application_command_callback_data ***p);
extern size_t discord_interaction_application_command_callback_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_application_command_callback_data_list_to_json(char *str, size_t len, struct discord_interaction_application_command_callback_data **p);


enum discord_interaction_application_command_callback_data_flags {
  DISCORD_INTERACTION_APPLICATION_COMMAND_CALLBACK_DATA_EPHEMERAL = 64, // only the user receiving the message can see it
};
extern char* discord_interaction_application_command_callback_data_flags_to_string(enum discord_interaction_application_command_callback_data_flags);
extern enum discord_interaction_application_command_callback_data_flags discord_interaction_application_command_callback_data_flags_from_string(char*);
extern bool discord_interaction_application_command_callback_data_flags_has(enum discord_interaction_application_command_callback_data_flags, char*);

// Message Interaction Structure
// defined at specs/discord/slash_commands.json:225:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#message-interaction-object-message-interaction-structure

 * - Initializer:
 *   - <tt>discord_message_interaction_init(struct discord_message_interaction*)</tt>
 * - Cleanup:
 *   - <tt>discord_message_interaction_cleanup(struct discord_message_interaction*)</tt>
 *   - <tt>discord_message_interaction_list_free(struct discord_message_interaction**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_message_interaction_from_json(char *rbuf, size_t len, struct discord_message_interaction**)</tt>
 *   - <tt>discord_message_interaction_list_from_json(char *rbuf, size_t len, struct discord_message_interaction***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_message_interaction_to_json(char *wbuf, size_t len, struct discord_message_interaction *p)</tt>
 *   - <tt>discord_message_interaction_list_to_json(char *wbuf, size_t len, struct discord_message_interaction**)</tt>
 */
struct discord_message_interaction {
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  u64_snowflake_t id; ///< id of the interaction

  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
  enum discord_interaction_request_types type; ///< the request type of the interaction

  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
  char *name; ///< the name of the application command

  /* specs/discord/slash_commands.json:231:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
  struct discord_user *user; ///< the user who invoked the interaction

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
extern void discord_message_interaction_cleanup_v(void *p);
extern void discord_message_interaction_cleanup(struct discord_message_interaction *p);
extern void discord_message_interaction_init_v(void *p);
extern void discord_message_interaction_init(struct discord_message_interaction *p);
extern void discord_message_interaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_interaction_from_json(char *json, size_t len, struct discord_message_interaction **pp);
extern size_t discord_message_interaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_interaction_to_json(char *json, size_t len, struct discord_message_interaction *p);
extern size_t discord_message_interaction_to_query_v(char *json, size_t len, void *p);
extern size_t discord_message_interaction_to_query(char *json, size_t len, struct discord_message_interaction *p);
extern void discord_message_interaction_list_free_v(void **p);
extern void discord_message_interaction_list_free(struct discord_message_interaction **p);
extern void discord_message_interaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_interaction_list_from_json(char *str, size_t len, struct discord_message_interaction ***p);
extern size_t discord_message_interaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_interaction_list_to_json(char *str, size_t len, struct discord_message_interaction **p);
