/* This file is generated from specs/discord/gateway.json, Please don't edit it. */
/**
 * @file specs-code/discord/gateway.h
 * @see https://discord.com/developers/docs/topics/gateway
 */



// Gateway Close Event Codes
// defined at specs/discord/gateway.json:6:5
/**
 * @see https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-close-event-codes
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_close_opcodes_print(enum discord_gateway_close_opcodes code)`
 *   * :code:`enum discord_gateway_close_opcodes discord_gateway_close_opcodes_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_close_opcodes {
  DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR = 4000,
  DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE = 4001,
  DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR = 4002,
  DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED = 4003,
  DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE = 4007,
  DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED = 4008,
  DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT = 4009,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD = 4010,
  DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED = 4011,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION = 4012,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS = 4013,
  DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS = 4014,
};
extern char* discord_gateway_close_opcodes_print(enum discord_gateway_close_opcodes);
extern enum discord_gateway_close_opcodes discord_gateway_close_opcodes_eval(char*);
extern void discord_gateway_close_opcodes_list_free_v(void **p);
extern void discord_gateway_close_opcodes_list_free(enum discord_gateway_close_opcodes **p);
extern void discord_gateway_close_opcodes_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_close_opcodes_list_from_json(char *str, size_t len, enum discord_gateway_close_opcodes ***p);
extern size_t discord_gateway_close_opcodes_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_close_opcodes_list_to_json(char *str, size_t len, enum discord_gateway_close_opcodes **p);


// Gateway Intents
// defined at specs/discord/gateway.json:28:5
/**
 * @see https://discord.com/developers/docs/topics/gateway#gateway-intents
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_intents_print(enum discord_gateway_intents code)`
 *   * :code:`enum discord_gateway_intents discord_gateway_intents_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_intents {
  DISCORD_GATEWAY_GUILDS = 1, ///< 1 << 0
  DISCORD_GATEWAY_GUILD_MEMBERS = 2, ///< 1 << 1
  DISCORD_GATEWAY_GUILD_BANS = 4, ///< 1 << 2
  DISCORD_GATEWAY_GUILD_EMOJIS = 8, ///< 1 << 3
  DISCORD_GATEWAY_GUILD_INTEGRATIONS = 16, ///< 1 << 4
  DISCORD_GATEWAY_GUILD_WEBHOOKS = 32, ///< 1 << 5
  DISCORD_GATEWAY_GUILD_INVITES = 64, ///< 1 << 6
  DISCORD_GATEWAY_GUILD_VOICE_STATES = 128, ///< 1 << 7
  DISCORD_GATEWAY_GUILD_PRESENCES = 256, ///< 1 << 8
  DISCORD_GATEWAY_GUILD_MESSAGES = 512, ///< 1 << 9
  DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS = 1024, ///< 1 << 10
  DISCORD_GATEWAY_GUILD_MESSAGE_TYPING = 2048, ///< 1 << 11
  DISCORD_GATEWAY_DIRECT_MESSAGES = 4096, ///< 1 << 12
  DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS = 8192, ///< 1 << 13
  DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING = 16384, ///< 1 << 14
};
extern char* discord_gateway_intents_print(enum discord_gateway_intents);
extern enum discord_gateway_intents discord_gateway_intents_eval(char*);
extern void discord_gateway_intents_list_free_v(void **p);
extern void discord_gateway_intents_list_free(enum discord_gateway_intents **p);
extern void discord_gateway_intents_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_intents_list_from_json(char *str, size_t len, enum discord_gateway_intents ***p);
extern size_t discord_gateway_intents_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_intents_list_to_json(char *str, size_t len, enum discord_gateway_intents **p);


// Gateway Opcodes
// defined at specs/discord/gateway.json:51:5
/**
 * @see https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_opcodes_print(enum discord_gateway_opcodes code)`
 *   * :code:`enum discord_gateway_opcodes discord_gateway_opcodes_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_opcodes {
  DISCORD_GATEWAY_DISPATCH = 0,
  DISCORD_GATEWAY_HEARTBEAT = 1,
  DISCORD_GATEWAY_IDENTIFY = 2,
  DISCORD_GATEWAY_PRESENCE_UPDATE = 3,
  DISCORD_GATEWAY_VOICE_STATE_UPDATE = 4,
  DISCORD_GATEWAY_RESUME = 6,
  DISCORD_GATEWAY_RECONNECT = 7,
  DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS = 8,
  DISCORD_GATEWAY_INVALID_SESSION = 9,
  DISCORD_GATEWAY_HELLO = 10,
  DISCORD_GATEWAY_HEARTBEAT_ACK = 11,
};
extern char* discord_gateway_opcodes_print(enum discord_gateway_opcodes);
extern enum discord_gateway_opcodes discord_gateway_opcodes_eval(char*);
extern void discord_gateway_opcodes_list_free_v(void **p);
extern void discord_gateway_opcodes_list_free(enum discord_gateway_opcodes **p);
extern void discord_gateway_opcodes_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_opcodes_list_from_json(char *str, size_t len, enum discord_gateway_opcodes ***p);
extern size_t discord_gateway_opcodes_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_opcodes_list_to_json(char *str, size_t len, enum discord_gateway_opcodes **p);


// Gateway Events
// defined at specs/discord/gateway.json:70:5
/**
 * @see https://discord.com/developers/docs/topics/gateway#commands-and-events-gateway-events
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_events_print(enum discord_gateway_events code)`
 *   * :code:`enum discord_gateway_events discord_gateway_events_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_events {
  DISCORD_GATEWAY_EVENTS_NONE = 0,
  DISCORD_GATEWAY_EVENTS_READY = 1,
  DISCORD_GATEWAY_EVENTS_RESUMED = 2,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_CREATE = 3,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_UPDATE = 4,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_DELETE = 5,
  DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE = 6,
  DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE = 7,
  DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE = 8,
  DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE = 9,
  DISCORD_GATEWAY_EVENTS_THREAD_CREATE = 10,
  DISCORD_GATEWAY_EVENTS_THREAD_UPDATE = 11,
  DISCORD_GATEWAY_EVENTS_THREAD_DELETE = 12,
  DISCORD_GATEWAY_EVENTS_THREAD_LIST_SYNC = 13,
  DISCORD_GATEWAY_EVENTS_THREAD_MEMBER_UPDATE = 14,
  DISCORD_GATEWAY_EVENTS_THREAD_MEMBERS_UPDATE = 15,
  DISCORD_GATEWAY_EVENTS_GUILD_CREATE = 16,
  DISCORD_GATEWAY_EVENTS_GUILD_UPDATE = 17,
  DISCORD_GATEWAY_EVENTS_GUILD_DELETE = 18,
  DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD = 19,
  DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE = 20,
  DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE = 21,
  DISCORD_GATEWAY_EVENTS_GUILD_STICKERS_UPDATE = 22,
  DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE = 23,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD = 24,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE = 25,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE = 26,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBERS_CHUNK = 27,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE = 28,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE = 29,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE = 30,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_CREATE = 31,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_UPDATE = 32,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_DELETE = 33,
  DISCORD_GATEWAY_EVENTS_INTERACTION_CREATE = 34,
  DISCORD_GATEWAY_EVENTS_INVITE_CREATE = 35,
  DISCORD_GATEWAY_EVENTS_INVITE_DELETE = 36,
  DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE = 37,
  DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE = 38,
  DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE = 39,
  DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK = 40,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD = 41,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE = 42,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL = 43,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI = 44,
  DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE = 45,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_CREATE = 46,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_DELETE = 47,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_UPDATE = 48,
  DISCORD_GATEWAY_EVENTS_TYPING_START = 49,
  DISCORD_GATEWAY_EVENTS_USER_UPDATE = 50,
  DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE = 51,
  DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE = 52,
  DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE = 53,
};
extern char* discord_gateway_events_print(enum discord_gateway_events);
extern enum discord_gateway_events discord_gateway_events_eval(char*);
extern void discord_gateway_events_list_free_v(void **p);
extern void discord_gateway_events_list_free(enum discord_gateway_events **p);
extern void discord_gateway_events_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_events_list_from_json(char *str, size_t len, enum discord_gateway_events ***p);
extern size_t discord_gateway_events_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_events_list_to_json(char *str, size_t len, enum discord_gateway_events **p);

// Identify Structure
// defined at specs/discord/gateway.json:135:22
/**
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_gateway_identify_init(struct discord_gateway_identify *)`
 *   * Cleanup:

 *     * :code:`void discord_gateway_identify_cleanup(struct discord_gateway_identify *)`
 *     * :code:`void discord_gateway_identify_list_free(struct discord_gateway_identify **)`
 *   * JSON Decoder:

 *     * :code:`void discord_gateway_identify_from_json(char *rbuf, size_t len, struct discord_gateway_identify **)`
 *     * :code:`void discord_gateway_identify_list_from_json(char *rbuf, size_t len, struct discord_gateway_identify ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_gateway_identify_to_json(char *wbuf, size_t len, struct discord_gateway_identify *)`
 *     * :code:`void discord_gateway_identify_list_to_json(char *wbuf, size_t len, struct discord_gateway_identify **)`
 * @endverbatim
 */
struct discord_gateway_identify {
  /* specs/discord/gateway.json:138:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
  char *token;

  /* specs/discord/gateway.json:139:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}' */
  struct discord_gateway_identify_connection *properties;

  /* specs/discord/gateway.json:140:19
     '{ "name":"compress","type":{"base":"bool"}}' */
  bool compress;

  /* specs/discord/gateway.json:141:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
  int large_threshold;

  /* specs/discord/gateway.json:142:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
  bool guild_subscriptions;

  /* specs/discord/gateway.json:143:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  // @todo shard (null);

  /* specs/discord/gateway.json:144:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}' */
  struct discord_gateway_status_update *presence;

  /* specs/discord/gateway.json:145:19
     '{ "name":"intents","type":{"base":"int"}}' */
  int intents;

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
extern void discord_gateway_identify_cleanup_v(void *p);
extern void discord_gateway_identify_cleanup(struct discord_gateway_identify *p);
extern void discord_gateway_identify_init_v(void *p);
extern void discord_gateway_identify_init(struct discord_gateway_identify *p);
extern void discord_gateway_identify_from_json_v(char *json, size_t len, void *pp);
extern void discord_gateway_identify_from_json(char *json, size_t len, struct discord_gateway_identify **pp);
extern size_t discord_gateway_identify_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_to_json(char *json, size_t len, struct discord_gateway_identify *p);
extern size_t discord_gateway_identify_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_to_query(char *json, size_t len, struct discord_gateway_identify *p);
extern void discord_gateway_identify_list_free_v(void **p);
extern void discord_gateway_identify_list_free(struct discord_gateway_identify **p);
extern void discord_gateway_identify_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_identify_list_from_json(char *str, size_t len, struct discord_gateway_identify ***p);
extern size_t discord_gateway_identify_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_identify_list_to_json(char *str, size_t len, struct discord_gateway_identify **p);

// Gateway Status Update Structure
// defined at specs/discord/gateway.json:151:22
/**
 * @see https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_gateway_status_update_init(struct discord_gateway_status_update *)`
 *   * Cleanup:

 *     * :code:`void discord_gateway_status_update_cleanup(struct discord_gateway_status_update *)`
 *     * :code:`void discord_gateway_status_update_list_free(struct discord_gateway_status_update **)`
 *   * JSON Decoder:

 *     * :code:`void discord_gateway_status_update_from_json(char *rbuf, size_t len, struct discord_gateway_status_update **)`
 *     * :code:`void discord_gateway_status_update_list_from_json(char *rbuf, size_t len, struct discord_gateway_status_update ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_gateway_status_update_to_json(char *wbuf, size_t len, struct discord_gateway_status_update *)`
 *     * :code:`void discord_gateway_status_update_list_to_json(char *wbuf, size_t len, struct discord_gateway_status_update **)`
 * @endverbatim
 */
struct discord_gateway_status_update {
  /* specs/discord/gateway.json:154:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }' */
  u64_unix_ms_t since;

  /* specs/discord/gateway.json:156:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}' */
  struct discord_gateway_activity **activities;

  /* specs/discord/gateway.json:158:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}' */
  char status[16];

  /* specs/discord/gateway.json:159:19
     '{ "name":"afk","type":{"base":"bool"}}' */
  bool afk;

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
extern void discord_gateway_status_update_cleanup_v(void *p);
extern void discord_gateway_status_update_cleanup(struct discord_gateway_status_update *p);
extern void discord_gateway_status_update_init_v(void *p);
extern void discord_gateway_status_update_init(struct discord_gateway_status_update *p);
extern void discord_gateway_status_update_from_json_v(char *json, size_t len, void *pp);
extern void discord_gateway_status_update_from_json(char *json, size_t len, struct discord_gateway_status_update **pp);
extern size_t discord_gateway_status_update_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_status_update_to_json(char *json, size_t len, struct discord_gateway_status_update *p);
extern size_t discord_gateway_status_update_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_status_update_to_query(char *json, size_t len, struct discord_gateway_status_update *p);
extern void discord_gateway_status_update_list_free_v(void **p);
extern void discord_gateway_status_update_list_free(struct discord_gateway_status_update **p);
extern void discord_gateway_status_update_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_status_update_list_from_json(char *str, size_t len, struct discord_gateway_status_update ***p);
extern size_t discord_gateway_status_update_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_status_update_list_to_json(char *str, size_t len, struct discord_gateway_status_update **p);

// Identify Connection Properties
// defined at specs/discord/gateway.json:166:22
/**
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_gateway_identify_connection_init(struct discord_gateway_identify_connection *)`
 *   * Cleanup:

 *     * :code:`void discord_gateway_identify_connection_cleanup(struct discord_gateway_identify_connection *)`
 *     * :code:`void discord_gateway_identify_connection_list_free(struct discord_gateway_identify_connection **)`
 *   * JSON Decoder:

 *     * :code:`void discord_gateway_identify_connection_from_json(char *rbuf, size_t len, struct discord_gateway_identify_connection **)`
 *     * :code:`void discord_gateway_identify_connection_list_from_json(char *rbuf, size_t len, struct discord_gateway_identify_connection ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_gateway_identify_connection_to_json(char *wbuf, size_t len, struct discord_gateway_identify_connection *)`
 *     * :code:`void discord_gateway_identify_connection_list_to_json(char *wbuf, size_t len, struct discord_gateway_identify_connection **)`
 * @endverbatim
 */
struct discord_gateway_identify_connection {
  /* specs/discord/gateway.json:169:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}}' */
  char *os;

  /* specs/discord/gateway.json:170:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}}' */
  char *browser;

  /* specs/discord/gateway.json:171:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}}' */
  char *device;

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
extern void discord_gateway_identify_connection_cleanup_v(void *p);
extern void discord_gateway_identify_connection_cleanup(struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_init_v(void *p);
extern void discord_gateway_identify_connection_init(struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_from_json_v(char *json, size_t len, void *pp);
extern void discord_gateway_identify_connection_from_json(char *json, size_t len, struct discord_gateway_identify_connection **pp);
extern size_t discord_gateway_identify_connection_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_connection_to_json(char *json, size_t len, struct discord_gateway_identify_connection *p);
extern size_t discord_gateway_identify_connection_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_connection_to_query(char *json, size_t len, struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_list_free_v(void **p);
extern void discord_gateway_identify_connection_list_free(struct discord_gateway_identify_connection **p);
extern void discord_gateway_identify_connection_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_identify_connection_list_from_json(char *str, size_t len, struct discord_gateway_identify_connection ***p);
extern size_t discord_gateway_identify_connection_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_identify_connection_list_to_json(char *str, size_t len, struct discord_gateway_identify_connection **p);

// Activity Structure
// defined at specs/discord/gateway.json:177:22
/**
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_gateway_activity_init(struct discord_gateway_activity *)`
 *   * Cleanup:

 *     * :code:`void discord_gateway_activity_cleanup(struct discord_gateway_activity *)`
 *     * :code:`void discord_gateway_activity_list_free(struct discord_gateway_activity **)`
 *   * JSON Decoder:

 *     * :code:`void discord_gateway_activity_from_json(char *rbuf, size_t len, struct discord_gateway_activity **)`
 *     * :code:`void discord_gateway_activity_list_from_json(char *rbuf, size_t len, struct discord_gateway_activity ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_gateway_activity_to_json(char *wbuf, size_t len, struct discord_gateway_activity *)`
 *     * :code:`void discord_gateway_activity_list_to_json(char *wbuf, size_t len, struct discord_gateway_activity **)`
 * @endverbatim
 */
struct discord_gateway_activity {
  /* specs/discord/gateway.json:180:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}' */
  char name[512];

  /* specs/discord/gateway.json:181:19
     '{ "name":"type","type":{"base":"int"}}' */
  int type;

  /* specs/discord/gateway.json:182:19
     '{ "name":"url","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}' */
  char *url;

  /* specs/discord/gateway.json:184:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }' */
  u64_unix_ms_t created_at;

  /* specs/discord/gateway.json:186:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }' */
  u64_snowflake_t application_id;

  /* specs/discord/gateway.json:188:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}' */
  char *details;

  /* specs/discord/gateway.json:190:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}' */
  char *state;

  /* specs/discord/gateway.json:192:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}' */
  bool instance;

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
extern void discord_gateway_activity_cleanup_v(void *p);
extern void discord_gateway_activity_cleanup(struct discord_gateway_activity *p);
extern void discord_gateway_activity_init_v(void *p);
extern void discord_gateway_activity_init(struct discord_gateway_activity *p);
extern void discord_gateway_activity_from_json_v(char *json, size_t len, void *pp);
extern void discord_gateway_activity_from_json(char *json, size_t len, struct discord_gateway_activity **pp);
extern size_t discord_gateway_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_activity_to_json(char *json, size_t len, struct discord_gateway_activity *p);
extern size_t discord_gateway_activity_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_activity_to_query(char *json, size_t len, struct discord_gateway_activity *p);
extern void discord_gateway_activity_list_free_v(void **p);
extern void discord_gateway_activity_list_free(struct discord_gateway_activity **p);
extern void discord_gateway_activity_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_activity_list_from_json(char *str, size_t len, struct discord_gateway_activity ***p);
extern size_t discord_gateway_activity_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_activity_list_to_json(char *str, size_t len, struct discord_gateway_activity **p);


// Activity Types
// defined at specs/discord/gateway.json:196:5
/**
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_activity_types_print(enum discord_gateway_activity_types code)`
 *   * :code:`enum discord_gateway_activity_types discord_gateway_activity_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_activity_types {
  DISCORD_GATEWAY_ACTIVITY_GAME = 0,
  DISCORD_GATEWAY_ACTIVITY_STREAMING = 1,
  DISCORD_GATEWAY_ACTIVITY_LISTENING = 2,
  DISCORD_GATEWAY_ACTIVITY_CUSTOM = 4,
  DISCORD_GATEWAY_ACTIVITY_COMPETING = 5,
};
extern char* discord_gateway_activity_types_print(enum discord_gateway_activity_types);
extern enum discord_gateway_activity_types discord_gateway_activity_types_eval(char*);
extern void discord_gateway_activity_types_list_free_v(void **p);
extern void discord_gateway_activity_types_list_free(enum discord_gateway_activity_types **p);
extern void discord_gateway_activity_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_activity_types_list_from_json(char *str, size_t len, enum discord_gateway_activity_types ***p);
extern size_t discord_gateway_activity_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_activity_types_list_to_json(char *str, size_t len, enum discord_gateway_activity_types **p);
