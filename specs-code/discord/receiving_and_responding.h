/* This file is generated from specs/discord/receiving_and_responding.json, Please don't edit it. */
/**
 * @file specs-code/discord/receiving_and_responding.h
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-data-structure
 */


// Interaction Structure
// defined at specs/discord/receiving_and_responding.json:9:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-interaction-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_interaction_init(struct discord_interaction *)`
 *   * Cleanup:

 *     * :code:`void discord_interaction_cleanup(struct discord_interaction *)`
 *     * :code:`void discord_interaction_list_free(struct discord_interaction **)`
 *   * JSON Decoder:

 *     * :code:`void discord_interaction_from_json(char *rbuf, size_t len, struct discord_interaction **)`
 *     * :code:`void discord_interaction_list_from_json(char *rbuf, size_t len, struct discord_interaction ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_interaction_to_json(char *wbuf, size_t len, struct discord_interaction *)`
 *     * :code:`void discord_interaction_list_to_json(char *wbuf, size_t len, struct discord_interaction **)`
 * @endverbatim
 */
struct discord_interaction {
  /* specs/discord/receiving_and_responding.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  u64_snowflake_t id; ///< id of the interaction

  /* specs/discord/receiving_and_responding.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
  u64_snowflake_t application_id; ///< id of the application this iteraction is for

  /* specs/discord/receiving_and_responding.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
  enum discord_interaction_types type; ///< the request type of the interaction

  /* specs/discord/receiving_and_responding.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  struct discord_interaction_data *data; ///< the command data payload

  /* specs/discord/receiving_and_responding.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
  u64_snowflake_t guild_id; ///< the guild it was sent from

  /* specs/discord/receiving_and_responding.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
  u64_snowflake_t channel_id; ///< the channel it was sent from

  /* specs/discord/receiving_and_responding.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  struct discord_guild_member *member; ///< guild member data for the invoking user, including permissions

  /* specs/discord/receiving_and_responding.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  struct discord_user *user; ///< user object for the invoking user, if invoked in a DM

  /* specs/discord/receiving_and_responding.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
  char *token; ///< a continuation token for responding to the interaction

  /* specs/discord/receiving_and_responding.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */
  struct discord_message *message; ///< for components, the message they were attached to

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[10];
    void *record_defined[10];
    void *record_null[10];
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


// Interaction Type
// defined at specs/discord/receiving_and_responding.json:24:5
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-type
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_interaction_types_print(enum discord_interaction_types code)`
 *   * :code:`enum discord_interaction_types discord_interaction_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_interaction_types {
  DISCORD_INTERACTION_PING = 1,
  DISCORD_INTERACTION_APPLICATION_COMMAND = 2,
  DISCORD_INTERACTION_MESSAGE_COMPONENT = 3,
};
extern char* discord_interaction_types_print(enum discord_interaction_types);
extern enum discord_interaction_types discord_interaction_types_eval(char*);

// Interaction Data Structure
// defined at specs/discord/receiving_and_responding.json:40:22
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-data-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_interaction_data_init(struct discord_interaction_data *)`
 *   * Cleanup:

 *     * :code:`void discord_interaction_data_cleanup(struct discord_interaction_data *)`
 *     * :code:`void discord_interaction_data_list_free(struct discord_interaction_data **)`
 *   * JSON Decoder:

 *     * :code:`void discord_interaction_data_from_json(char *rbuf, size_t len, struct discord_interaction_data **)`
 *     * :code:`void discord_interaction_data_list_from_json(char *rbuf, size_t len, struct discord_interaction_data ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_interaction_data_to_json(char *wbuf, size_t len, struct discord_interaction_data *)`
 *     * :code:`void discord_interaction_data_list_to_json(char *wbuf, size_t len, struct discord_interaction_data **)`
 * @endverbatim
 */
struct discord_interaction_data {
  /* specs/discord/receiving_and_responding.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
  u64_snowflake_t id; ///< the ID of the invoked command

  /* specs/discord/receiving_and_responding.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
  char *name; ///< the name of the invoked command

  /* specs/discord/receiving_and_responding.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */
  enum discord_application_command_types type; ///< the type of the invoked command

  /* specs/discord/receiving_and_responding.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  struct discord_resolved_data *resolved; ///< converted users + roles + channels

  /* specs/discord/receiving_and_responding.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_option **options; ///< the parameters for the command, max 25

  /* specs/discord/receiving_and_responding.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */
  char *custom_id; ///< the custom id of the component

  /* specs/discord/receiving_and_responding.json:49:18
     '{"name":"values", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */
  struct discord_select_option **values; ///< the values the user selected

  /* specs/discord/receiving_and_responding.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */
  u64_snowflake_t target_id; ///< id of a user or message targetted by a user or message command

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
/// @endcond
};
extern void discord_interaction_data_cleanup_v(void *p);
extern void discord_interaction_data_cleanup(struct discord_interaction_data *p);
extern void discord_interaction_data_init_v(void *p);
extern void discord_interaction_data_init(struct discord_interaction_data *p);
extern void discord_interaction_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_data_from_json(char *json, size_t len, struct discord_interaction_data **pp);
extern size_t discord_interaction_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_data_to_json(char *json, size_t len, struct discord_interaction_data *p);
extern size_t discord_interaction_data_to_query_v(char *json, size_t len, void *p);
extern size_t discord_interaction_data_to_query(char *json, size_t len, struct discord_interaction_data *p);
extern void discord_interaction_data_list_free_v(void **p);
extern void discord_interaction_data_list_free(struct discord_interaction_data **p);
extern void discord_interaction_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_data_list_from_json(char *str, size_t len, struct discord_interaction_data ***p);
extern size_t discord_interaction_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_data_list_to_json(char *str, size_t len, struct discord_interaction_data **p);

// Resolved Data Structure
// defined at specs/discord/receiving_and_responding.json:57:22
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-resolved-data-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_resolved_data_init(struct discord_resolved_data *)`
 *   * Cleanup:

 *     * :code:`void discord_resolved_data_cleanup(struct discord_resolved_data *)`
 *     * :code:`void discord_resolved_data_list_free(struct discord_resolved_data **)`
 *   * JSON Decoder:

 *     * :code:`void discord_resolved_data_from_json(char *rbuf, size_t len, struct discord_resolved_data **)`
 *     * :code:`void discord_resolved_data_list_from_json(char *rbuf, size_t len, struct discord_resolved_data ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_resolved_data_to_json(char *wbuf, size_t len, struct discord_resolved_data *)`
 *     * :code:`void discord_resolved_data_list_to_json(char *wbuf, size_t len, struct discord_resolved_data **)`
 * @endverbatim
 */
struct discord_resolved_data {
  /* specs/discord/receiving_and_responding.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
  ja_str **users; ///< the ids and User objects

  /* specs/discord/receiving_and_responding.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
  ja_str **members; ///< the ids and partial Member objects

  /* specs/discord/receiving_and_responding.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
  ja_str **roles; ///< the ids and Role objects

  /* specs/discord/receiving_and_responding.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
  ja_str **channels; ///< the ids and partial Channel objects

  /* specs/discord/receiving_and_responding.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */
  ja_str **messages; ///< the ids and partial Message objects

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
extern void discord_resolved_data_cleanup_v(void *p);
extern void discord_resolved_data_cleanup(struct discord_resolved_data *p);
extern void discord_resolved_data_init_v(void *p);
extern void discord_resolved_data_init(struct discord_resolved_data *p);
extern void discord_resolved_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_resolved_data_from_json(char *json, size_t len, struct discord_resolved_data **pp);
extern size_t discord_resolved_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_resolved_data_to_json(char *json, size_t len, struct discord_resolved_data *p);
extern size_t discord_resolved_data_to_query_v(char *json, size_t len, void *p);
extern size_t discord_resolved_data_to_query(char *json, size_t len, struct discord_resolved_data *p);
extern void discord_resolved_data_list_free_v(void **p);
extern void discord_resolved_data_list_free(struct discord_resolved_data **p);
extern void discord_resolved_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_resolved_data_list_from_json(char *str, size_t len, struct discord_resolved_data ***p);
extern size_t discord_resolved_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_resolved_data_list_to_json(char *str, size_t len, struct discord_resolved_data **p);

// Message Interaction Structure
// defined at specs/discord/receiving_and_responding.json:71:22
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#message-interaction-object-message-interaction-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_interaction_init(struct discord_message_interaction *)`
 *   * Cleanup:

 *     * :code:`void discord_message_interaction_cleanup(struct discord_message_interaction *)`
 *     * :code:`void discord_message_interaction_list_free(struct discord_message_interaction **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_interaction_from_json(char *rbuf, size_t len, struct discord_message_interaction **)`
 *     * :code:`void discord_message_interaction_list_from_json(char *rbuf, size_t len, struct discord_message_interaction ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_interaction_to_json(char *wbuf, size_t len, struct discord_message_interaction *)`
 *     * :code:`void discord_message_interaction_list_to_json(char *wbuf, size_t len, struct discord_message_interaction **)`
 * @endverbatim
 */
struct discord_message_interaction {
  /* specs/discord/receiving_and_responding.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  u64_snowflake_t id; ///< id of the interaction

  /* specs/discord/receiving_and_responding.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
  enum discord_interaction_types type; ///< the request type of the interaction

  /* specs/discord/receiving_and_responding.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
  char *name; ///< the name of the application command

  /* specs/discord/receiving_and_responding.json:77:18
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

// Interaction Response Structure
// defined at specs/discord/receiving_and_responding.json:84:22
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-response-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_interaction_response_init(struct discord_interaction_response *)`
 *   * Cleanup:

 *     * :code:`void discord_interaction_response_cleanup(struct discord_interaction_response *)`
 *     * :code:`void discord_interaction_response_list_free(struct discord_interaction_response **)`
 *   * JSON Decoder:

 *     * :code:`void discord_interaction_response_from_json(char *rbuf, size_t len, struct discord_interaction_response **)`
 *     * :code:`void discord_interaction_response_list_from_json(char *rbuf, size_t len, struct discord_interaction_response ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_interaction_response_to_json(char *wbuf, size_t len, struct discord_interaction_response *)`
 *     * :code:`void discord_interaction_response_list_to_json(char *wbuf, size_t len, struct discord_interaction_response **)`
 * @endverbatim
 */
struct discord_interaction_response {
  /* specs/discord/receiving_and_responding.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
  enum discord_interaction_callback_types type; ///< the type of response

  /* specs/discord/receiving_and_responding.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  struct discord_interaction_callback_data *data; ///< an optional response message

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


// Interaction Callback Type
// defined at specs/discord/receiving_and_responding.json:91:5
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-type
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_interaction_callback_types_print(enum discord_interaction_callback_types code)`
 *   * :code:`enum discord_interaction_callback_types discord_interaction_callback_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_interaction_callback_types {
  DISCORD_INTERACTION_CALLBACK_PONG = 1, ///< ACK a Ping
  DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE = 4, ///< respond to a interaction with a message
  DISCORD_INTERACTION_CALLBACK_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE = 5, ///< ACK an interaction and edit a response later, the user sees a loading state
  DISCORD_INTERACTION_CALLBACK_DEFERRED_UPDATE_MESSAGE = 6, ///< for components, ACK an interaction and edit the original message later; the user does not see a loading state
  DISCORD_INTERACTION_CALLBACK_UPDATE_MESSAGE = 7, ///< for components, edit the message the component was attached to
};
extern char* discord_interaction_callback_types_print(enum discord_interaction_callback_types);
extern enum discord_interaction_callback_types discord_interaction_callback_types_eval(char*);

// Interaction Callback Data Structure
// defined at specs/discord/receiving_and_responding.json:109:22
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_interaction_callback_data_init(struct discord_interaction_callback_data *)`
 *   * Cleanup:

 *     * :code:`void discord_interaction_callback_data_cleanup(struct discord_interaction_callback_data *)`
 *     * :code:`void discord_interaction_callback_data_list_free(struct discord_interaction_callback_data **)`
 *   * JSON Decoder:

 *     * :code:`void discord_interaction_callback_data_from_json(char *rbuf, size_t len, struct discord_interaction_callback_data **)`
 *     * :code:`void discord_interaction_callback_data_list_from_json(char *rbuf, size_t len, struct discord_interaction_callback_data ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_interaction_callback_data_to_json(char *wbuf, size_t len, struct discord_interaction_callback_data *)`
 *     * :code:`void discord_interaction_callback_data_list_to_json(char *wbuf, size_t len, struct discord_interaction_callback_data **)`
 * @endverbatim
 */
struct discord_interaction_callback_data {
  /* specs/discord/receiving_and_responding.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
  bool tts; ///< is the response TTS

  /* specs/discord/receiving_and_responding.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
  char *content; ///< message content

  /* specs/discord/receiving_and_responding.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
  struct discord_embed **embeds; ///< support up to 10 embeds

  /* specs/discord/receiving_and_responding.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  // @todo allowed_mentions allowed mentions object;

  /* specs/discord/receiving_and_responding.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
  enum discord_interaction_callback_data_flags flags; ///< interaction application command callback data flags

  /* specs/discord/receiving_and_responding.json:117:18
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
extern void discord_interaction_callback_data_cleanup_v(void *p);
extern void discord_interaction_callback_data_cleanup(struct discord_interaction_callback_data *p);
extern void discord_interaction_callback_data_init_v(void *p);
extern void discord_interaction_callback_data_init(struct discord_interaction_callback_data *p);
extern void discord_interaction_callback_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_callback_data_from_json(char *json, size_t len, struct discord_interaction_callback_data **pp);
extern size_t discord_interaction_callback_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_callback_data_to_json(char *json, size_t len, struct discord_interaction_callback_data *p);
extern size_t discord_interaction_callback_data_to_query_v(char *json, size_t len, void *p);
extern size_t discord_interaction_callback_data_to_query(char *json, size_t len, struct discord_interaction_callback_data *p);
extern void discord_interaction_callback_data_list_free_v(void **p);
extern void discord_interaction_callback_data_list_free(struct discord_interaction_callback_data **p);
extern void discord_interaction_callback_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_callback_data_list_from_json(char *str, size_t len, struct discord_interaction_callback_data ***p);
extern size_t discord_interaction_callback_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_callback_data_list_to_json(char *str, size_t len, struct discord_interaction_callback_data **p);


// Interaction Callback Data Flags
// defined at specs/discord/receiving_and_responding.json:120:5
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_interaction_callback_data_flags_print(enum discord_interaction_callback_data_flags code)`
 *   * :code:`enum discord_interaction_callback_data_flags discord_interaction_callback_data_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_interaction_callback_data_flags {
  DISCORD_INTERACTION_CALLBACK_DATA_EPHEMERAL = 64, ///< only the user receiving the message can see it
};
extern char* discord_interaction_callback_data_flags_print(enum discord_interaction_callback_data_flags);
extern enum discord_interaction_callback_data_flags discord_interaction_callback_data_flags_eval(char*);
