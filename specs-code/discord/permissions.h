/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
/**
 * @file specs-code/discord/permissions.h
 * @see https://discord.com/developers/docs/topics/permissions
 */



enum discord_permissions_bitwise_flags {
  DISCORD_PERMISSIONS_ZERO = 0, // No permission bits
  DISCORD_PERMISSIONS_CREATE_INSTANT_INVITE = 1, // Allows creation of instant invites  T, V
  DISCORD_PERMISSIONS_KICK_MEMBERS = 2, // Allows kicking members
  DISCORD_PERMISSIONS_BAN_MEMBERS = 4, // Allows banning members
  DISCORD_PERMISSIONS_ADMINISTRATOR = 8, // Allows all permissions and bypasses channel permission overwrites   
  DISCORD_PERMISSIONS_MANAGE_CHANNELS = 16, // Allows management and editing of channels   T, V
  DISCORD_PERMISSIONS_MANAGE_GUILD = 32, // Allows management and editing of the guild  
  DISCORD_PERMISSIONS_ADD_REACTIONS = 64, // Allows for the addition of reactions to messages    T
  DISCORD_PERMISSIONS_VIEW_AUDIT_LOG = 128, // Allows for viewing of audit logs    
  DISCORD_PERMISSIONS_PRIORITY_SPEAKER = 256, // Allows for using priority speaker in a voice channel    V
  DISCORD_PERMISSIONS_STREAM = 512, // Allows the user to go live  V
  DISCORD_PERMISSIONS_VIEW_CHANNEL = 1024, // Allows guild members to view a channel, which includes reading messages in text channels    T, V
  DISCORD_PERMISSIONS_SEND_MESSAGES = 2048, // Allows for sending messages in a channel    T
  DISCORD_PERMISSIONS_SEND_TTS_MESSAGES = 4096, // Allows for sending of /tts messages T
  DISCORD_PERMISSIONS_MANAGE_MESSAGES = 8192, // Allows for deletion of other users messages T
  DISCORD_PERMISSIONS_EMBED_LINKS = 16384, // Links sent by users with this permission will be auto-embedded  T
  DISCORD_PERMISSIONS_ATTACH_FILES = 32768, // Allows for uploading images and files   T
  DISCORD_PERMISSIONS_READ_MESSAGE_HISTORY = 65536, // Allows for reading of message history   T
  DISCORD_PERMISSIONS_MENTION_EVERYONE = 131072, // Allows for using the @everyone tag to notify all users in a channel, and the @here tag to notify all online users in a channel  T
  DISCORD_PERMISSIONS_USE_EXTERNAL_EMOJIS = 262144, // Allows the usage of custom emojis from other servers    T
  DISCORD_PERMISSIONS_VIEW_GUILD_INSIGHTS = 524288, // Allows for viewing guild insights   
  DISCORD_PERMISSIONS_CONNECT = 1048576, // Allows for joining of a voice channel   V
  DISCORD_PERMISSIONS_SPEAK = 2097152, // Allows for speaking in a voice channel  V
  DISCORD_PERMISSIONS_MUTE_MEMBERS = 4194304, // Allows for muting members in a voice channel    V
  DISCORD_PERMISSIONS_DEAFEN_MEMBERS = 8388608, // Allows for deafening of members in a voice channel  V
  DISCORD_PERMISSIONS_MOVE_MEMBERS = 16777216, // Allows for moving of members between voice channels V
  DISCORD_PERMISSIONS_USE_VAD = 33554432, // Allows for using voice-activity-detection in a voice channel    V
  DISCORD_PERMISSIONS_CHANGE_NICKNAME = 67108864, // Allows for modification of own nickname 
  DISCORD_PERMISSIONS_MANAGE_NICKNAMES = 134217728, // Allows for modification of other users nicknames    
  DISCORD_PERMISSIONS_MANAGE_ROLES = 268435456, // Allows management and editing of roles  T, V
  DISCORD_PERMISSIONS_MANAGE_WEBHOOKS = 536870912, // Allows management and editing of webhooks   T, V
  DISCORD_PERMISSIONS_MANAGE_EMOJIS = 1073741824, // Allows management and editing of emojis
};
extern char* discord_permissions_bitwise_flags_to_string(enum discord_permissions_bitwise_flags);
extern enum discord_permissions_bitwise_flags discord_permissions_bitwise_flags_from_string(char*);
extern bool discord_permissions_bitwise_flags_has(enum discord_permissions_bitwise_flags, char*);

// Role Structure
// defined at specs/discord/permissions.json:49:22
/**
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-structure
 * - Initializer:
 *   - <tt>discord_permissions_role_init(struct discord_permissions_role*)</tt>
 * - Cleanup:
 *   - <tt>discord_permissions_role_cleanup(struct discord_permissions_role*)</tt>
 *   - <tt>discord_permissions_role_list_free(struct discord_permissions_role**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_permissions_role_from_json(char *rbuf, size_t len, struct discord_permissions_role**)</tt>
 *   - <tt>discord_permissions_role_list_from_json(char *rbuf, size_t len, struct discord_permissions_role***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_permissions_role_to_json(char *wbuf, size_t len, struct discord_permissions_role *p)</tt>
 *   - <tt>discord_permissions_role_list_to_json(char *wbuf, size_t len, struct discord_permissions_role**)</tt>
 */
struct discord_permissions_role {
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */
  char name[DISCORD_MAX_NAME_LEN];

  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  int color;

  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  bool hoist;

  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  int position;

  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  char *permissions;

  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  bool managed;

  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  bool mentionable;

  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
  struct discord_permissions_role_tags *tags;

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
extern void discord_permissions_role_cleanup_v(void *p);
extern void discord_permissions_role_cleanup(struct discord_permissions_role *p);
extern void discord_permissions_role_init_v(void *p);
extern void discord_permissions_role_init(struct discord_permissions_role *p);
extern void discord_permissions_role_from_json_v(char *json, size_t len, void *pp);
extern void discord_permissions_role_from_json(char *json, size_t len, struct discord_permissions_role **pp);
extern size_t discord_permissions_role_to_json_v(char *json, size_t len, void *p);
extern size_t discord_permissions_role_to_json(char *json, size_t len, struct discord_permissions_role *p);
extern size_t discord_permissions_role_to_query_v(char *json, size_t len, void *p);
extern size_t discord_permissions_role_to_query(char *json, size_t len, struct discord_permissions_role *p);
extern void discord_permissions_role_list_free_v(void **p);
extern void discord_permissions_role_list_free(struct discord_permissions_role **p);
extern void discord_permissions_role_list_from_json_v(char *str, size_t len, void *p);
extern void discord_permissions_role_list_from_json(char *str, size_t len, struct discord_permissions_role ***p);
extern size_t discord_permissions_role_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_permissions_role_list_to_json(char *str, size_t len, struct discord_permissions_role **p);

// Role Tags Structure
// defined at specs/discord/permissions.json:67:22
/**
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-tags-structure
 * - Initializer:
 *   - <tt>discord_permissions_role_tags_init(struct discord_permissions_role_tags*)</tt>
 * - Cleanup:
 *   - <tt>discord_permissions_role_tags_cleanup(struct discord_permissions_role_tags*)</tt>
 *   - <tt>discord_permissions_role_tags_list_free(struct discord_permissions_role_tags**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_permissions_role_tags_from_json(char *rbuf, size_t len, struct discord_permissions_role_tags**)</tt>
 *   - <tt>discord_permissions_role_tags_list_from_json(char *rbuf, size_t len, struct discord_permissions_role_tags***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_permissions_role_tags_to_json(char *wbuf, size_t len, struct discord_permissions_role_tags *p)</tt>
 *   - <tt>discord_permissions_role_tags_list_to_json(char *wbuf, size_t len, struct discord_permissions_role_tags**)</tt>
 */
struct discord_permissions_role_tags {
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t bot_id;

  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t integration_id;

  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  int premium_subscriber;

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
extern void discord_permissions_role_tags_cleanup_v(void *p);
extern void discord_permissions_role_tags_cleanup(struct discord_permissions_role_tags *p);
extern void discord_permissions_role_tags_init_v(void *p);
extern void discord_permissions_role_tags_init(struct discord_permissions_role_tags *p);
extern void discord_permissions_role_tags_from_json_v(char *json, size_t len, void *pp);
extern void discord_permissions_role_tags_from_json(char *json, size_t len, struct discord_permissions_role_tags **pp);
extern size_t discord_permissions_role_tags_to_json_v(char *json, size_t len, void *p);
extern size_t discord_permissions_role_tags_to_json(char *json, size_t len, struct discord_permissions_role_tags *p);
extern size_t discord_permissions_role_tags_to_query_v(char *json, size_t len, void *p);
extern size_t discord_permissions_role_tags_to_query(char *json, size_t len, struct discord_permissions_role_tags *p);
extern void discord_permissions_role_tags_list_free_v(void **p);
extern void discord_permissions_role_tags_list_free(struct discord_permissions_role_tags **p);
extern void discord_permissions_role_tags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_permissions_role_tags_list_from_json(char *str, size_t len, struct discord_permissions_role_tags ***p);
extern size_t discord_permissions_role_tags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_permissions_role_tags_list_to_json(char *str, size_t len, struct discord_permissions_role_tags **p);
