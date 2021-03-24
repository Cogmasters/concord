/* This file is generated from specs/gateway.json, Please don't edit it. */
/*
(null)
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


enum discord_gateway_intents {
  DISCORD_GATEWAY_GUILDS = 1, // 1 << 0
  DISCORD_GATEWAY_GUILD_MEMBERS = 2, // 1 << 1
  DISCORD_GATEWAY_GUILD_BANS = 4, // 1 << 2
  DISCORD_GATEWAY_GUILD_EMOJIS = 8, // 1 << 3
  DISCORD_GATEWAY_GUILD_INTEGRATIONS = 16, // 1 << 4
  DISCORD_GATEWAY_GUILD_WEBHOOKS = 32, // 1 << 5
  DISCORD_GATEWAY_GUILD_INVITES = 64, // 1 << 6
  DISCORD_GATEWAY_GUILD_VOICE_STATES = 128, // 1 << 7
  DISCORD_GATEWAY_GUILD_PRESENCES = 256, // 1 << 8
  DISCORD_GATEWAY_GUILD_MESSAGES = 512, // 1 << 9
  DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS = 1024, // 1 << 10
  DISCORD_GATEWAY_GUILD_MESSAGE_TYPING = 2048, // 1 << 11
  DISCORD_GATEWAY_DIRECT_MESSAGES = 4096, // 1 << 12
  DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS = 8192, // 1 << 13
  DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING = 16384, // 1 << 14
};


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

/* Title: Identify Structure */
/* https://discord.com/developers/docs/topics/gateway#identify-identify-structure */
/* This is defined at specs/gateway.json:72:22 */
struct discord_gateway_identify {
  /* specs/gateway.json:75:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  char *token;

  /* specs/gateway.json:76:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
  struct discord_gateway_identify_connection *properties;

  /* specs/gateway.json:77:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  bool compress;

  /* specs/gateway.json:78:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
  int large_threshold;

  /* specs/gateway.json:79:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  bool guild_subscriptions;

  /* specs/gateway.json:80:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  //@todo shard (null);

  /* specs/gateway.json:81:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_identify_status_update", "dec":"*"}}'
  */
  struct discord_gateway_identify_status_update *presence;

  /* specs/gateway.json:82:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
  int intents;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
};
extern void discord_gateway_identify_cleanup_v(void *p);
extern void discord_gateway_identify_cleanup(struct discord_gateway_identify *p);
extern void discord_gateway_identify_init_v(void *p);
extern void discord_gateway_identify_init(struct discord_gateway_identify *p);
extern struct discord_gateway_identify * discord_gateway_identify_alloc();
extern void discord_gateway_identify_free_v(void *p);
extern void discord_gateway_identify_free(struct discord_gateway_identify *p);
extern void discord_gateway_identify_from_json_v(char *json, size_t len, void *p);
extern void discord_gateway_identify_from_json(char *json, size_t len, struct discord_gateway_identify *p);
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

/* Title: Gateway Status Update Structure */
/* https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure */
/* This is defined at specs/gateway.json:89:22 */
struct discord_gateway_identify_status_update {
  /* specs/gateway.json:92:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  u64_unix_ms_t since;

  /* specs/gateway.json:94:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_identify_status_update_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
  struct discord_gateway_identify_status_update_activity **activities;

  /* specs/gateway.json:96:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  char status[16];

  /* specs/gateway.json:97:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
  bool afk;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_gateway_identify_status_update_cleanup_v(void *p);
extern void discord_gateway_identify_status_update_cleanup(struct discord_gateway_identify_status_update *p);
extern void discord_gateway_identify_status_update_init_v(void *p);
extern void discord_gateway_identify_status_update_init(struct discord_gateway_identify_status_update *p);
extern struct discord_gateway_identify_status_update * discord_gateway_identify_status_update_alloc();
extern void discord_gateway_identify_status_update_free_v(void *p);
extern void discord_gateway_identify_status_update_free(struct discord_gateway_identify_status_update *p);
extern void discord_gateway_identify_status_update_from_json_v(char *json, size_t len, void *p);
extern void discord_gateway_identify_status_update_from_json(char *json, size_t len, struct discord_gateway_identify_status_update *p);
extern size_t discord_gateway_identify_status_update_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_to_json(char *json, size_t len, struct discord_gateway_identify_status_update *p);
extern size_t discord_gateway_identify_status_update_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_to_query(char *json, size_t len, struct discord_gateway_identify_status_update *p);
extern void discord_gateway_identify_status_update_list_free_v(void **p);
extern void discord_gateway_identify_status_update_list_free(struct discord_gateway_identify_status_update **p);
extern void discord_gateway_identify_status_update_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_identify_status_update_list_from_json(char *str, size_t len, struct discord_gateway_identify_status_update ***p);
extern size_t discord_gateway_identify_status_update_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_list_to_json(char *str, size_t len, struct discord_gateway_identify_status_update **p);

/* Title: Identify Connection Properties */
/* https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties */
/* This is defined at specs/gateway.json:104:22 */
struct discord_gateway_identify_connection {
  /* specs/gateway.json:107:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
  char *$os;

  /* specs/gateway.json:108:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
  char *$browser;

  /* specs/gateway.json:109:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
  char *$device;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
extern void discord_gateway_identify_connection_cleanup_v(void *p);
extern void discord_gateway_identify_connection_cleanup(struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_init_v(void *p);
extern void discord_gateway_identify_connection_init(struct discord_gateway_identify_connection *p);
extern struct discord_gateway_identify_connection * discord_gateway_identify_connection_alloc();
extern void discord_gateway_identify_connection_free_v(void *p);
extern void discord_gateway_identify_connection_free(struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_from_json_v(char *json, size_t len, void *p);
extern void discord_gateway_identify_connection_from_json(char *json, size_t len, struct discord_gateway_identify_connection *p);
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

/* Title: Activity Structure */
/* https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure */
/* This is defined at specs/gateway.json:116:22 */
struct discord_gateway_identify_status_update_activity {
  /* specs/gateway.json:119:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  char name[512];

  /* specs/gateway.json:120:19
     '{ "name":"type","type":{"base":"int"}}'
  */
  int type;

  /* specs/gateway.json:121:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/gateway.json:123:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  u64_unix_ms_t created_at;

  /* specs/gateway.json:125:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
  u64_snowflake_t application_id;

  /* specs/gateway.json:127:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  char *details;

  /* specs/gateway.json:129:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  char *state;

  /* specs/gateway.json:131:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
  bool instance;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
};
extern void discord_gateway_identify_status_update_activity_cleanup_v(void *p);
extern void discord_gateway_identify_status_update_activity_cleanup(struct discord_gateway_identify_status_update_activity *p);
extern void discord_gateway_identify_status_update_activity_init_v(void *p);
extern void discord_gateway_identify_status_update_activity_init(struct discord_gateway_identify_status_update_activity *p);
extern struct discord_gateway_identify_status_update_activity * discord_gateway_identify_status_update_activity_alloc();
extern void discord_gateway_identify_status_update_activity_free_v(void *p);
extern void discord_gateway_identify_status_update_activity_free(struct discord_gateway_identify_status_update_activity *p);
extern void discord_gateway_identify_status_update_activity_from_json_v(char *json, size_t len, void *p);
extern void discord_gateway_identify_status_update_activity_from_json(char *json, size_t len, struct discord_gateway_identify_status_update_activity *p);
extern size_t discord_gateway_identify_status_update_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_activity_to_json(char *json, size_t len, struct discord_gateway_identify_status_update_activity *p);
extern size_t discord_gateway_identify_status_update_activity_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_activity_to_query(char *json, size_t len, struct discord_gateway_identify_status_update_activity *p);
extern void discord_gateway_identify_status_update_activity_list_free_v(void **p);
extern void discord_gateway_identify_status_update_activity_list_free(struct discord_gateway_identify_status_update_activity **p);
extern void discord_gateway_identify_status_update_activity_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_identify_status_update_activity_list_from_json(char *str, size_t len, struct discord_gateway_identify_status_update_activity ***p);
extern size_t discord_gateway_identify_status_update_activity_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_activity_list_to_json(char *str, size_t len, struct discord_gateway_identify_status_update_activity **p);


enum discord_gateway_identify_status_update_activity_types {
  DISCORD_GATEWAY_IDENTIFY_STATUS_UPDATE_ACTIVITY_GAME = 0,
  DISCORD_GATEWAY_IDENTIFY_STATUS_UPDATE_ACTIVITY_STREAMING = 1,
  DISCORD_GATEWAY_IDENTIFY_STATUS_UPDATE_ACTIVITY_LISTENING = 2,
  DISCORD_GATEWAY_IDENTIFY_STATUS_UPDATE_ACTIVITY_CUSTOM = 4,
  DISCORD_GATEWAY_IDENTIFY_STATUS_UPDATE_ACTIVITY_COMPETING = 5,
};
