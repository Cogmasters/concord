/* This file is generated from specs/gateway.json, Please don't edit it. */
/*
(null)
*/


enum close_opcodes {
  CLOSE_REASON_UNKNOWN_ERROR = 4000,
  CLOSE_REASON_UNKNOWN_OPCODE = 4001,
  CLOSE_REASON_DECODE_ERROR = 4002,
  CLOSE_REASON_NOT_AUTHENTICATED = 4003,
  CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  CLOSE_REASON_INVALID_SEQUENCE = 4007,
  CLOSE_REASON_RATE_LIMITED = 4008,
  CLOSE_REASON_SESSION_TIMED_OUT = 4009,
  CLOSE_REASON_INVALID_SHARD = 4010,
  CLOSE_REASON_SHARDING_REQUIRED = 4011,
  CLOSE_REASON_INVALID_API_VERSION = 4012,
  CLOSE_REASON_INVALID_INTENTS = 4013,
  CLOSE_REASON_DISALLOWED_INTENTS = 4014,
};


namespace intents {
enum code {
  GUILDS = 1, // 1 << 0
  GUILD_MEMBERS = 2, // 1 << 1
  GUILD_BANS = 4, // 1 << 2
  GUILD_EMOJIS = 8, // 1 << 3
  GUILD_INTEGRATIONS = 16, // 1 << 4
  GUILD_WEBHOOKS = 32, // 1 << 5
  GUILD_INVITES = 64, // 1 << 6
  GUILD_VOICE_STATES = 128, // 1 << 7
  GUILD_PRESENCES = 256, // 1 << 8
  GUILD_MESSAGES = 512, // 1 << 9
  GUILD_MESSAGE_REACTIONS = 1024, // 1 << 10
  GUILD_MESSAGE_TYPING = 2048, // 1 << 11
  DIRECT_MESSAGES = 4096, // 1 << 12
  DIRECT_MESSAGE_REACTIONS = 8192, // 1 << 13
  DIRECT_MESSAGE_TYPING = 16384, // 1 << 14
};
} // namespace intents


namespace opcodes {
enum code {
  DISPATCH = 0,
  HEARTBEAT = 1,
  IDENTIFY = 2,
  PRESENCE_UPDATE = 3,
  VOICE_STATE_UPDATE = 4,
  RESUME = 6,
  RECONNECT = 7,
  REQUEST_GUILD_MEMBERS = 8,
  INVALID_SESSION = 9,
  HELLO = 10,
  HEARTBEAT_ACK = 11,
};
} // namespace opcodes

namespace identify {
/* Title: Identify Structure */
/* https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes */
/* This is defined at specs/gateway.json:76:22 */
struct dait {
  /* specs/gateway.json:79:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  char *token;

  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  bool compress;

  /* specs/gateway.json:81:19
     '{ "name":"large_threshod","type":{"base":"int"}}'
  */
  int large_threshod;

  /* specs/gateway.json:82:19
     '{ "name":"shard","type":{"base":"char", "dec":"*", "todo":true}}'
  */
  char *shard;

  /* specs/gateway.json:83:19
     '{ "name":"presense","type":{"base":"discord::gateway::status_update::dati", "dec":"*"}}'
  */
  discord::gateway::status_update::dati *presense;

  /* specs/gateway.json:84:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  bool guild_subscriptions;

  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int", "int_alias":"discord::gateway::intents::code"}}'
  */
  discord::gateway::intents::code intents;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
};
extern void dait_cleanup_v(void *p);
extern void dait_cleanup(struct dait *p);
extern void dait_init_v(void *p);
extern void dait_init(struct dait *p);
extern struct dait * dait_alloc();
extern void dait_free_v(void *p);
extern void dait_free(struct dait *p);
extern void dait_from_json_v(char *json, size_t len, void *p);
extern void dait_from_json(char *json, size_t len, struct dait *p);
extern size_t dait_to_json_v(char *json, size_t len, void *p);
extern size_t dait_to_json(char *json, size_t len, struct dait *p);
extern size_t dait_to_query_v(char *json, size_t len, void *p);
extern size_t dait_to_query(char *json, size_t len, struct dait *p);
extern void dait_list_free_v(void **p);
extern void dait_list_free(struct dait **p);
extern void dait_list_from_json_v(char *str, size_t len, void *p);
extern void dait_list_from_json(char *str, size_t len, struct dait ***p);
extern size_t dait_list_to_json_v(char *str, size_t len, void *p);
extern size_t dait_list_to_json(char *str, size_t len, struct dait **p);
extern void dait_use_default_inject_settings(struct dait *p);
} // namespace identify


namespace activity {
namespace types {
enum code {
};
} // namespace types
} // namespace activity

namespace activity {
/* Title: Activity Structure */
/* https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure */
/* This is defined at specs/gateway.json:107:22 */
struct dati {
  /* specs/gateway.json:110:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  char name[512];

  /* specs/gateway.json:111:19
     '{ "name":"code","type":{"base":"int", "int_alias":"discord::gateway::activity::types::code"}}'
  */
  discord::gateway::activity::types::code code;

  /* specs/gateway.json:112:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"}}'
  */
  char url[MAX_URL_LEN];

  /* specs/gateway.json:113:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  u64_unix_ms_t created_at;

  /* specs/gateway.json:114:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t application_id;

  /* specs/gateway.json:115:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}}'
  */
  char *details;

  /* specs/gateway.json:116:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}}'
  */
  char *state;

  /* specs/gateway.json:117:19
     '{ "name":"instance","type":{"base":"bool"}}'
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace activity

namespace status_update {
/* Title: Gateway Status Update Structure */
/* https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure */
/* This is defined at specs/gateway.json:125:22 */
struct dati {
  /* specs/gateway.json:128:19
     '{ "name":"since","type":{"base":"char", "dec":"*"}}'
  */
  char *since;

  /* specs/gateway.json:129:19
     '{ "name":"activities","type":{"base":"discord::gateway::activity::dati", "dec":"ntl"}}'
  */
  discord::gateway::activity::dati **activities;

  /* specs/gateway.json:130:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  char status[16];

  /* specs/gateway.json:131:19
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace status_update
