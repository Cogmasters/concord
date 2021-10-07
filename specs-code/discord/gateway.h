/* This file is generated from specs/discord/gateway.json, Please don't edit it. */
/**
 * @file specs-code/discord/gateway.h
 * @see https://discord.com/developers/docs/topics/gateway
 */



/* Gateway Close Event Codes */
/* defined at specs/discord/gateway.json:6:5 */
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


/* Gateway Intents */
/* defined at specs/discord/gateway.json:29:5 */
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
  DISCORD_GATEWAY_GUILDS = 1, /**< 1 << 0 */
  DISCORD_GATEWAY_GUILD_MEMBERS = 2, /**< 1 << 1 */
  DISCORD_GATEWAY_GUILD_BANS = 4, /**< 1 << 2 */
  DISCORD_GATEWAY_GUILD_EMOJIS = 8, /**< 1 << 3 */
  DISCORD_GATEWAY_GUILD_INTEGRATIONS = 16, /**< 1 << 4 */
  DISCORD_GATEWAY_GUILD_WEBHOOKS = 32, /**< 1 << 5 */
  DISCORD_GATEWAY_GUILD_INVITES = 64, /**< 1 << 6 */
  DISCORD_GATEWAY_GUILD_VOICE_STATES = 128, /**< 1 << 7 */
  DISCORD_GATEWAY_GUILD_PRESENCES = 256, /**< 1 << 8 */
  DISCORD_GATEWAY_GUILD_MESSAGES = 512, /**< 1 << 9 */
  DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS = 1024, /**< 1 << 10 */
  DISCORD_GATEWAY_GUILD_MESSAGE_TYPING = 2048, /**< 1 << 11 */
  DISCORD_GATEWAY_DIRECT_MESSAGES = 4096, /**< 1 << 12 */
  DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS = 8192, /**< 1 << 13 */
  DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING = 16384, /**< 1 << 14 */
};
extern char* discord_gateway_intents_print(enum discord_gateway_intents);
extern enum discord_gateway_intents discord_gateway_intents_eval(char*);
extern void discord_gateway_intents_list_free_v(void **p);
extern void discord_gateway_intents_list_free(enum discord_gateway_intents **p);
extern void discord_gateway_intents_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_intents_list_from_json(char *str, size_t len, enum discord_gateway_intents ***p);
extern size_t discord_gateway_intents_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_intents_list_to_json(char *str, size_t len, enum discord_gateway_intents **p);


/* Gateway Opcodes */
/* defined at specs/discord/gateway.json:53:5 */
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


/* Gateway Events */
/* defined at specs/discord/gateway.json:73:5 */
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

/* Identify Structure */
/* defined at specs/discord/gateway.json:139:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_identify_init(struct discord_identify *)`
 *   * Cleanup:

 *     * :code:`void discord_identify_cleanup(struct discord_identify *)`
 *     * :code:`void discord_identify_list_free(struct discord_identify **)`
 *   * JSON Decoder:

 *     * :code:`void discord_identify_from_json(char *rbuf, size_t len, struct discord_identify **)`
 *     * :code:`void discord_identify_list_from_json(char *rbuf, size_t len, struct discord_identify ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_identify_to_json(char *wbuf, size_t len, struct discord_identify *)`
 *     * :code:`void discord_identify_list_to_json(char *wbuf, size_t len, struct discord_identify **)`
 * @endverbatim
 */
struct discord_identify {
  /* specs/discord/gateway.json:142:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
  char *token;

  /* specs/discord/gateway.json:143:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */
  struct discord_identify_connection *properties;

  /* specs/discord/gateway.json:144:19
     '{ "name":"compress","type":{"base":"bool"}}' */
  bool compress;

  /* specs/discord/gateway.json:145:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
  int large_threshold;

  /* specs/discord/gateway.json:146:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
  bool guild_subscriptions;

  /* specs/discord/gateway.json:147:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  /* @todo shard (null); */

  /* specs/discord/gateway.json:148:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */
  struct discord_presence_status *presence;

  /* specs/discord/gateway.json:149:19
     '{ "name":"intents","type":{"base":"int"}}' */
  int intents;

};
extern void discord_identify_cleanup_v(void *p);
extern void discord_identify_cleanup(struct discord_identify *p);
extern void discord_identify_init_v(void *p);
extern void discord_identify_init(struct discord_identify *p);
extern void discord_identify_from_json_v(char *json, size_t len, void *pp);
extern void discord_identify_from_json(char *json, size_t len, struct discord_identify **pp);
extern size_t discord_identify_to_json_v(char *json, size_t len, void *p);
extern size_t discord_identify_to_json(char *json, size_t len, struct discord_identify *p);
extern void discord_identify_list_free_v(void **p);
extern void discord_identify_list_free(struct discord_identify **p);
extern void discord_identify_list_from_json_v(char *str, size_t len, void *p);
extern void discord_identify_list_from_json(char *str, size_t len, struct discord_identify ***p);
extern size_t discord_identify_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_identify_list_to_json(char *str, size_t len, struct discord_identify **p);

/* Gateway Voice State Update Structure */
/* defined at specs/discord/gateway.json:156:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#update-voice-state-gateway-voice-state-update-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_voice_state_status_init(struct discord_voice_state_status *)`
 *   * Cleanup:

 *     * :code:`void discord_voice_state_status_cleanup(struct discord_voice_state_status *)`
 *     * :code:`void discord_voice_state_status_list_free(struct discord_voice_state_status **)`
 *   * JSON Decoder:

 *     * :code:`void discord_voice_state_status_from_json(char *rbuf, size_t len, struct discord_voice_state_status **)`
 *     * :code:`void discord_voice_state_status_list_from_json(char *rbuf, size_t len, struct discord_voice_state_status ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_voice_state_status_to_json(char *wbuf, size_t len, struct discord_voice_state_status *)`
 *     * :code:`void discord_voice_state_status_list_to_json(char *wbuf, size_t len, struct discord_voice_state_status **)`
 * @endverbatim
 */
struct discord_voice_state_status {
  /* specs/discord/gateway.json:159:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */
  u64_snowflake_t guild_id; /**< id of the guild */

  /* specs/discord/gateway.json:160:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */
  u64_snowflake_t channel_id; /**< id of the voice channel client wants to join (null if disconnecting) */

  /* specs/discord/gateway.json:161:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */
  bool self_mute; /**< is the client muted */

  /* specs/discord/gateway.json:162:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */
  bool self_deaf; /**< is the client deafened */

};
extern void discord_voice_state_status_cleanup_v(void *p);
extern void discord_voice_state_status_cleanup(struct discord_voice_state_status *p);
extern void discord_voice_state_status_init_v(void *p);
extern void discord_voice_state_status_init(struct discord_voice_state_status *p);
extern void discord_voice_state_status_from_json_v(char *json, size_t len, void *pp);
extern void discord_voice_state_status_from_json(char *json, size_t len, struct discord_voice_state_status **pp);
extern size_t discord_voice_state_status_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_state_status_to_json(char *json, size_t len, struct discord_voice_state_status *p);
extern void discord_voice_state_status_list_free_v(void **p);
extern void discord_voice_state_status_list_free(struct discord_voice_state_status **p);
extern void discord_voice_state_status_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_state_status_list_from_json(char *str, size_t len, struct discord_voice_state_status ***p);
extern size_t discord_voice_state_status_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_state_status_list_to_json(char *str, size_t len, struct discord_voice_state_status **p);

/* Gateway Presence Update Structure */
/* defined at specs/discord/gateway.json:169:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#update-presence-gateway-presence-update-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_presence_status_init(struct discord_presence_status *)`
 *   * Cleanup:

 *     * :code:`void discord_presence_status_cleanup(struct discord_presence_status *)`
 *     * :code:`void discord_presence_status_list_free(struct discord_presence_status **)`
 *   * JSON Decoder:

 *     * :code:`void discord_presence_status_from_json(char *rbuf, size_t len, struct discord_presence_status **)`
 *     * :code:`void discord_presence_status_list_from_json(char *rbuf, size_t len, struct discord_presence_status ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_presence_status_to_json(char *wbuf, size_t len, struct discord_presence_status *)`
 *     * :code:`void discord_presence_status_list_to_json(char *wbuf, size_t len, struct discord_presence_status **)`
 * @endverbatim
 */
struct discord_presence_status {
  /* specs/discord/gateway.json:172:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */
  u64_unix_ms_t since; /**< unix time (in milliseconds) of when the client went idle, or null if the client is not idle */

  /* specs/discord/gateway.json:173:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */
  struct discord_activity **activities; /**< the user's activities */

  /* specs/discord/gateway.json:174:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}, "comment":"the user's new status", "inject_if_not":"" }' */
  char status[16]; /**< the user's new status */

  /* specs/discord/gateway.json:175:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */
  bool afk; /**< whether or not the client is afk */

};
extern void discord_presence_status_cleanup_v(void *p);
extern void discord_presence_status_cleanup(struct discord_presence_status *p);
extern void discord_presence_status_init_v(void *p);
extern void discord_presence_status_init(struct discord_presence_status *p);
extern void discord_presence_status_from_json_v(char *json, size_t len, void *pp);
extern void discord_presence_status_from_json(char *json, size_t len, struct discord_presence_status **pp);
extern size_t discord_presence_status_to_json_v(char *json, size_t len, void *p);
extern size_t discord_presence_status_to_json(char *json, size_t len, struct discord_presence_status *p);
extern void discord_presence_status_list_free_v(void **p);
extern void discord_presence_status_list_free(struct discord_presence_status **p);
extern void discord_presence_status_list_from_json_v(char *str, size_t len, void *p);
extern void discord_presence_status_list_from_json(char *str, size_t len, struct discord_presence_status ***p);
extern size_t discord_presence_status_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_presence_status_list_to_json(char *str, size_t len, struct discord_presence_status **p);

/* Identify Connection Properties */
/* defined at specs/discord/gateway.json:182:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_identify_connection_init(struct discord_identify_connection *)`
 *   * Cleanup:

 *     * :code:`void discord_identify_connection_cleanup(struct discord_identify_connection *)`
 *     * :code:`void discord_identify_connection_list_free(struct discord_identify_connection **)`
 *   * JSON Decoder:

 *     * :code:`void discord_identify_connection_from_json(char *rbuf, size_t len, struct discord_identify_connection **)`
 *     * :code:`void discord_identify_connection_list_from_json(char *rbuf, size_t len, struct discord_identify_connection ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_identify_connection_to_json(char *wbuf, size_t len, struct discord_identify_connection *)`
 *     * :code:`void discord_identify_connection_list_to_json(char *wbuf, size_t len, struct discord_identify_connection **)`
 * @endverbatim
 */
struct discord_identify_connection {
  /* specs/discord/gateway.json:185:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */
  char *os; /**< your operating system */

  /* specs/discord/gateway.json:186:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
  char *browser; /**< your library name */

  /* specs/discord/gateway.json:187:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
  char *device; /**< your library name */

};
extern void discord_identify_connection_cleanup_v(void *p);
extern void discord_identify_connection_cleanup(struct discord_identify_connection *p);
extern void discord_identify_connection_init_v(void *p);
extern void discord_identify_connection_init(struct discord_identify_connection *p);
extern void discord_identify_connection_from_json_v(char *json, size_t len, void *pp);
extern void discord_identify_connection_from_json(char *json, size_t len, struct discord_identify_connection **pp);
extern size_t discord_identify_connection_to_json_v(char *json, size_t len, void *p);
extern size_t discord_identify_connection_to_json(char *json, size_t len, struct discord_identify_connection *p);
extern void discord_identify_connection_list_free_v(void **p);
extern void discord_identify_connection_list_free(struct discord_identify_connection **p);
extern void discord_identify_connection_list_from_json_v(char *str, size_t len, void *p);
extern void discord_identify_connection_list_from_json(char *str, size_t len, struct discord_identify_connection ***p);
extern size_t discord_identify_connection_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_identify_connection_list_to_json(char *str, size_t len, struct discord_identify_connection **p);

/* Activity Structure */
/* defined at specs/discord/gateway.json:193:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_activity_init(struct discord_activity *)`
 *   * Cleanup:

 *     * :code:`void discord_activity_cleanup(struct discord_activity *)`
 *     * :code:`void discord_activity_list_free(struct discord_activity **)`
 *   * JSON Decoder:

 *     * :code:`void discord_activity_from_json(char *rbuf, size_t len, struct discord_activity **)`
 *     * :code:`void discord_activity_list_from_json(char *rbuf, size_t len, struct discord_activity ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_activity_to_json(char *wbuf, size_t len, struct discord_activity *)`
 *     * :code:`void discord_activity_list_to_json(char *wbuf, size_t len, struct discord_activity **)`
 * @endverbatim
 */
struct discord_activity {
  /* specs/discord/gateway.json:196:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}' */
  char name[512];

  /* specs/discord/gateway.json:197:19
     '{ "name":"type","type":{"base":"int"}}' */
  int type;

  /* specs/discord/gateway.json:198:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */
  char *url;

  /* specs/discord/gateway.json:199:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */
  u64_unix_ms_t created_at;

  /* specs/discord/gateway.json:200:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t application_id;

  /* specs/discord/gateway.json:201:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *details;

  /* specs/discord/gateway.json:202:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *state;

  /* specs/discord/gateway.json:203:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  bool instance;

};
extern void discord_activity_cleanup_v(void *p);
extern void discord_activity_cleanup(struct discord_activity *p);
extern void discord_activity_init_v(void *p);
extern void discord_activity_init(struct discord_activity *p);
extern void discord_activity_from_json_v(char *json, size_t len, void *pp);
extern void discord_activity_from_json(char *json, size_t len, struct discord_activity **pp);
extern size_t discord_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_activity_to_json(char *json, size_t len, struct discord_activity *p);
extern void discord_activity_list_free_v(void **p);
extern void discord_activity_list_free(struct discord_activity **p);
extern void discord_activity_list_from_json_v(char *str, size_t len, void *p);
extern void discord_activity_list_from_json(char *str, size_t len, struct discord_activity ***p);
extern size_t discord_activity_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_activity_list_to_json(char *str, size_t len, struct discord_activity **p);


/* Activity Types */
/* defined at specs/discord/gateway.json:206:5 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_activity_types_print(enum discord_activity_types code)`
 *   * :code:`enum discord_activity_types discord_activity_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_activity_types {
  DISCORD_ACTIVITY_GAME = 0,
  DISCORD_ACTIVITY_STREAMING = 1,
  DISCORD_ACTIVITY_LISTENING = 2,
  DISCORD_ACTIVITY_CUSTOM = 4,
  DISCORD_ACTIVITY_COMPETING = 5,
};
extern char* discord_activity_types_print(enum discord_activity_types);
extern enum discord_activity_types discord_activity_types_eval(char*);
extern void discord_activity_types_list_free_v(void **p);
extern void discord_activity_types_list_free(enum discord_activity_types **p);
extern void discord_activity_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_activity_types_list_from_json(char *str, size_t len, enum discord_activity_types ***p);
extern size_t discord_activity_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_activity_types_list_to_json(char *str, size_t len, enum discord_activity_types **p);

/* Session Start Limit Structure */
/* defined at specs/discord/gateway.json:224:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#session-start-limit-object-session-start-limit-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_session_start_limit_init(struct discord_session_start_limit *)`
 *   * Cleanup:

 *     * :code:`void discord_session_start_limit_cleanup(struct discord_session_start_limit *)`
 *     * :code:`void discord_session_start_limit_list_free(struct discord_session_start_limit **)`
 *   * JSON Decoder:

 *     * :code:`void discord_session_start_limit_from_json(char *rbuf, size_t len, struct discord_session_start_limit **)`
 *     * :code:`void discord_session_start_limit_list_from_json(char *rbuf, size_t len, struct discord_session_start_limit ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_session_start_limit_to_json(char *wbuf, size_t len, struct discord_session_start_limit *)`
 *     * :code:`void discord_session_start_limit_list_to_json(char *wbuf, size_t len, struct discord_session_start_limit **)`
 * @endverbatim
 */
struct discord_session_start_limit {
  /* specs/discord/gateway.json:227:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */
  int total; /**< the total number of session starts the current user is allowed */

  /* specs/discord/gateway.json:228:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */
  int remaining; /**< the remaining number of session starts the current user is allowed */

  /* specs/discord/gateway.json:229:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */
  int reset_after; /**< the number of milliseconds after which the limit resets */

  /* specs/discord/gateway.json:230:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */
  int max_concurrency; /**< the number of identify requests allowed per 5 seconds */

};
extern void discord_session_start_limit_cleanup_v(void *p);
extern void discord_session_start_limit_cleanup(struct discord_session_start_limit *p);
extern void discord_session_start_limit_init_v(void *p);
extern void discord_session_start_limit_init(struct discord_session_start_limit *p);
extern void discord_session_start_limit_from_json_v(char *json, size_t len, void *pp);
extern void discord_session_start_limit_from_json(char *json, size_t len, struct discord_session_start_limit **pp);
extern size_t discord_session_start_limit_to_json_v(char *json, size_t len, void *p);
extern size_t discord_session_start_limit_to_json(char *json, size_t len, struct discord_session_start_limit *p);
extern void discord_session_start_limit_list_free_v(void **p);
extern void discord_session_start_limit_list_free(struct discord_session_start_limit **p);
extern void discord_session_start_limit_list_from_json_v(char *str, size_t len, void *p);
extern void discord_session_start_limit_list_from_json(char *str, size_t len, struct discord_session_start_limit ***p);
extern size_t discord_session_start_limit_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_session_start_limit_list_to_json(char *str, size_t len, struct discord_session_start_limit **p);
