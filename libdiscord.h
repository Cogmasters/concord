#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

#include "json-actor-boxed.h"
#include "discord-common.h"

typedef uint64_t u64_unix_ms_t;
typedef uint64_t u64_snowflake_t;

/* Size limits encountered in the Docs and searching the web */
#define MAX_NAME_LEN          100 + 1
#define MAX_TOPIC_LEN         1024 + 1
#define MAX_DESCRIPTION_LEN   2048 + 1
#define MAX_USERNAME_LEN      32 + 1
#define MAX_DISCRIMINATOR_LEN 4 + 1
#define MAX_SHA256_LEN        1024 + 1
#define MAX_LOCALE_LEN        16 + 1
#define MAX_EMAIL_LEN         254 + 1
#define MAX_REGION_LEN        16 + 1
#define MAX_REASON_LEN        512 + 1
#define MAX_MESSAGE_LEN       2000 + 1
#define MAX_PAYLOAD_LEN       4096 + 1

/* EMBED LIMITS
https://discord.com/developers/docs/resources/channel#embed-limits */
#define EMBED_TITLE_LEN       256 + 1
#define EMBED_DESCRIPTION_LEN 2048 + 1
#define EMBED_MAX_FIELDS      25
#define EMBED_FIELD_NAME_LEN  256 + 1
#define EMBED_FIELD_VALUE_LEN 1024 + 1
#define EMBED_FOOTER_TEXT_LEN 2048 + 1
#define EMBED_AUTHOR_NAME_LEN 256 + 1

/* WEBHOOK LIMITS
https://discord.com/developers/docs/resources/webhook#create-webhook */
#define WEBHOOK_NAME_LEN 80 + 1

/* SNOWFLAKES
https://discord.com/developers/docs/reference#snowflakes */
#define SNOWFLAKE_INCREMENT           12
#define SNOWFLAKE_PROCESS_ID          17
#define SNOWFLAKE_INTERNAL_WORKER_ID  22
#define SNOWFLAKE_TIMESTAMP           64

/* * * * * * * * * * * * * * * * * * * */
/* * * * STRUCTURES DECLARATIONS * * * */

namespace discord {

enum callback_opt {
  IDLE,
  READY,
  MESSAGE_CREATE,
  MESSAGE_UPDATE,
  MESSAGE_DELETE,
  MESSAGE_DELETE_BULK,
  REACTION_ADD,
  REACTION_REMOVE,
  REACTION_REMOVE_ALL,
  REACTION_REMOVE_EMOJI,
  GUILD_MEMBER_ADD,
  GUILD_MEMBER_UPDATE,
  GUILD_MEMBER_REMOVE
};

/* START OF SHORTCUT ALIASES */

namespace presence = websockets::identify::status_update;

namespace guild {
#include "./specs-code/guild.enum.hh"
}

/* END OF SHORTCUT ALIASES */

/* AUDIT LOG STRUCTURE
https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure */
namespace audit_log {
struct dati {
  webhook::dati **webhooks;
  user::dati **users;
  entry::dati **audit_log_entries;
  guild::integration::dati **integrations;
};

//@todo missing initialization functions

/* AUDIT LOG ENTRY STRUCTURE
https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-entry-structure */
namespace entry {
struct dati {
  char *target_id; //@todo find fixed size limit
  change::dati **changes;
  uint64_t user_id;
  uint64_t id;
  events::code action_type;
  optional_info::dati *options;
  char reason[MAX_REASON_LEN];
};

//@todo missing initialization functions

/* AUDIT LOG EVENTS
https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-events */
namespace events {
enum {
  GUILD_UPDATE             = 1,
  CHANNEL_CREATE           = 10,
  CHANNEL_UPDATE           = 11,
  CHANNEL_DELETE           = 12,
  CHANNEL_OVERWRITE_CREATE = 13,
  CHANNEL_OVERWRITE_UPDATE = 14,
  CHANNEL_OVERWRITE_DELETE = 15,
  MEMBER_KICK              = 20,
  MEMBER_PRUNE             = 21,
  MEMBER_BAN_ADD           = 22,
  MEMBER_BAN_REMOVE        = 23,
  MEMBER_UPDATE            = 24,
  MEMBER_ROLE_UPDATE       = 25,
  MEMBER_MOVE              = 26,
  MEMBER_DISCONNECT        = 27,
  BOT_ADD                  = 28,
  ROLE_CREATE              = 30,
  ROLE_UPDATE              = 31,
  ROLE_DELETE              = 32,
  INVITE_CREATE            = 40,
  INVITE_DELETE            = 42,
  WEBHOOK_CREATE           = 50,
  WEBHOOK_UPDATE           = 51,
  WEBHOOK_DELETE           = 52,
  EMOJI_CREATE             = 60,
  EMOJI_UPDATE             = 61,
  EMOJI_DELETE             = 62,
  MESSAGE_DELETE           = 72,
  MESSAGE_BULK_DELETE      = 73,
  MESSAGE_PIN              = 74,
  MESSAGE_UNPIN            = 75,
  INTEGRATION_CREATE       = 80,
  INTEGRATION_UPDATE       = 81,
  INTEGRATION_DELETE       = 82
};
} // namespace events

/* OPTIONAL AUDIT ENTRY INFO STRUCTURE
https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-optional-audit-entry-info */
namespace optional_info {
#if 1
struct dati {
  char *delete_member_days; //@todo find fixed size limit
  char *members_removed; //@todo find fixed size limit
  uint64_t channel_id;
  uint64_t message_id;
  char *count; //@todo find fixed size limit
  uint64_t id;
  char *type; //@todo find fixed size limit
  char *role; //@todo find fixed size limit
};
#else
#include "./specs-code/entry.optional_info.hh"
#endif
} // namespace optional_entry

} // namespace entry

/* AUDIT LOG CHANGE STRUCTURE
https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-structure */
namespace change {
struct dati {
  void *new_value;
  void *old_value;
  char key[64];
};

//@todo missing initialization functions
/* AUDIT LOG CHANGE KEY
https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-key */
namespace key {
struct dati {
   char name[MAX_NAME_LEN];
   char description[MAX_DESCRIPTION_LEN];
   char hash[MAX_SHA256_LEN];
   char splash_hash[MAX_SHA256_LEN];
   char discovery_splash_hash[MAX_SHA256_LEN];
   uint64_t banner_hash;
   char region[MAX_REGION_LEN];
   char preferred_locale[MAX_LOCALE_LEN];
   uint64_t afk_channel_id;
   int afk_timeout;
   uint64_t rules_channel_id;
   uint64_t public_updates_channel_id;
   int mfa_level;
   int verification_level;
   int explicit_content_filter;
   guild::default_message_notification_level::code default_message_notifications;
   char vanity_url_code[MAX_URL_LEN];
  //@todo missing add
  //@todo missing remove
   int prune_delete_days;
   bool widget_enabled;
   uint64_t widget_channel_id;
   uint64_t system_channel_id;
   int position;
   char topic[MAX_TOPIC_LEN];
   int bitrate;
   channel::overwrite::dati **permission_overwrites;
   bool nsfw;
   uint64_t application_id;
   int ratelimit_per_user;
   char *permission; //@todo find fixed size limit
   int color;
   bool hoist;
   bool mentionable;
   char *allow; //@todo find fixed size limit
   char *deny; //@todo find fixed size limit
   char *code; //@todo find fixed size limit
   uint64_t channel_id;
   uint64_t inviter_id;
   int max_uses;
   int uses;
   int max_age;
   bool temporary;
   bool deaf;
   bool mute;
   char *nick; //@todo find fixed size limit
   char avatar_hash[MAX_SHA256_LEN];
   uint64_t id;
   bool enable_emoticons;
   int expire_behavior;
   int expire_grace_period;
   int user_limit;
};

//@todo missing initialization functions

} // namespace key

} // namespace change

} // namespace audit_log

/* CHANNEL STRUCTURE
https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
namespace channel {
#include "./specs-code/channel.hh"

/* MESSAGE STRUCTURE
https://discord.com/developers/docs/resources/channel#message-object */
namespace message {
#include "./specs-code/channel.message.hh"
} // namespace message

#include "./specs-code/channel.objects.hh"
} // namespace channel

/* EMOJI STRUCTURE
https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure */
namespace emoji {
#include "./specs-code/emoji.hh"
} // namespace emoji


/* GUILD STRUCTURE
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure */
namespace guild {
#include "./specs-code/guild.hh"

/* GUILD MEMBER STRUCTURE
https://discord.com/developers/docs/resources/guild#guild-member-object */
#include "./specs-code/guild.member.hh"

/* INTEGRATION STRUCTURE
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure */
#include "./specs-code/guild.integration.hh"


/* GUILD BAN STRUCTURE
https://discord.com/developers/docs/resources/guild#ban-object */
#include "./specs-code/guild.ban.hh"

/* ROLE STRUCTURE
https://discord.com/developers/docs/topics/permissions#role-object-role-structure */
#include "./specs-code/guild.role.hh"

/* WELCOME SCREEN STRUCTURE
https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-structure */
namespace welcome_screen {
#include "./specs-code/guild.welcome_screen.hh"
} // namespace welcome_screen

/* MEMBERSHIP SCREENING STRUCTURE
https://discord.com/developers/docs/resources/guild#membership-screening-object */
namespace membership_screening {
#include "./specs-code/guild.membership_screening.hh"
} // namespace membership_screening

} // namespace guild

/* INVITE STRUCTURE
https://discord.com/developers/docs/resources/invite#invite-object-invite-structure */
namespace invite {
#include "./specs-code/invite.hh"
} // namespace invite

/* TEMPLATE STRUCTURE
https://discord.com/developers/docs/resources/template#template-object-template-structure */
#include "./specs-code/template.hh"

/* USER STRUCTURE
https://discord.com/developers/docs/resources/user#user-object-user-structure */
namespace user {
#include "./specs-code/user.hh"
} // namespace user

/* VOICE STRUCTURE
https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure */
#include "./specs-code/voice.hh"

/* Webhook Structure
https://discord.com/developers/docs/resources/webhook#webhook-object */
#include "./specs-code/webhook.hh"

} // namespace discord


/* * * * * * * * * * * * * * * * * * */
/* * * * FUNCTION DECLARATIONS * * * */

namespace discord { /* discord-public.c */

void global_init();
void global_cleanup();

client* init(const char token[]);
client* config_init(const char config_file[]);
void cleanup(discord::client *client);

void add_intents(client *client, websockets::intents::code code);
void set_prefix(client *client, char *prefix);
void setcb_command(client *client, char *command, message_cb *user_cb);
void setcb(client *client, enum callback_opt opt, ...);
void run(client *client);

void dump_json(client *client, char file[]);
void dump_curl(client *client, char file[]);
void* set_data(client *client, void *data);
void* get_data(client *client);

user_agent::error get_json_error(client *client);

void replace_presence(client *client, presence::dati *presence);
void set_presence(
  client *client, 
  presence::activity::dati *activity, 
  char status[], 
  bool afk);

namespace channel { /* discord-public-channel.c */

void get(client *client, const uint64_t channel_id, dati *p_channel);
void del(client *client, const uint64_t channel_id, dati *p_channel);
void pin_message(client *client, const uint64_t channel_id, const uint64_t message_id);
void unpin_message(client *client, const uint64_t channel_id, const uint64_t message_id);
void trigger_typing(client *client, const uint64_t channel_id);

namespace message {

/* https://discord.com/developers/docs/resources/channel#get-channel-messages */
namespace get_list { // function wrapper

struct params {
  uint64_t around;
  uint64_t before;
  uint64_t after;
  int limit; // max number of messages (1-100)
};

message::dati** run(client *client, const uint64_t channel_id, params *params);

} // namespace get_list

/* https://discord.com/developers/docs/resources/channel#create-message */
namespace create { // function wrapper

/* default is application/json unless any 
 *  multipart/form-data parameter is set */
struct params {
  // common parameters
  char *content;
  char *nonce;
  bool tts;
  // parameters for application/json
  embed::dati *embed;
  allowed_mentions::dati *allowed_mentions;
  message::reference::dati *message_reference;
  // parameters for multipart/form-data
  struct { // FILE STRUCT @todo better explanation
    char *name; //if only name is set, will search in working directory
    char *content; //the file contents
    size_t size; //the size must accompany the content
  } file;
  char *payload_json;
};

void run(client *client, const uint64_t channel_id, params *params, dati *p_message);

} // namespace create

/* https://discord.com/developers/docs/resources/channel#edit-message */
namespace edit { // function wrapper

struct params {
  char *content;
  embed::dati *embed; //must be initialized
  message::flags::code *flags;
  allowed_mentions::dati *allowed_mentions; //must be initialized
};

void run(client *client, const uint64_t channel_id, const uint64_t message_id, params *params, dati *p_message);

} // namespace edit

void del(client *client, const uint64_t channel_id, const uint64_t message_id);

} // namespace message

namespace reaction {

void create(
  client *client, 
  const uint64_t channel_id, 
  const uint64_t message_id, 
  const uint64_t emoji_id, 
  const char emoji_name[]);

} // namespace reaction

namespace embed {

void change_thumbnail(dati *embed, char url[], char proxy_url[], int height, int width);
void change_image(dati *embed, char url[], char proxy_url[], int height, int width);
void change_video(dati *embed, char url[], char proxy_url[], int height, int width);
void change_footer(dati *embed, char text[], char icon_url[], char proxy_icon_url[]);
void change_provider(dati *embed, char name[], char url[]);
void change_author(dati *embed, char name[], char url[], char icon_url[], char proxy_icon_url[]);
void add_field(dati *embed, char name[], char value[], bool Inline);

} // namespace embed

namespace overwrite {

void append(
  dati ***permission_overwrites, 
  uint64_t id, 
  int type, 
  uint64_t allow, uint64_t deny);

} // namespace overwrite

} // namespace channel

namespace emoji { /* discord-public-emoji.cpp */

dati** get_list(client *client, const uint64_t guild_id);

} // namespace emoji

namespace guild { /* discord-public-guild.cpp */

//size_t dati_to_json(char *, size_t, void *p);

void get(client *client, const uint64_t guild_id, dati *p_guild);
channel::dati** get_channels(client *client, const uint64_t guild_id);

namespace create_channel {
#include "./specs-code/guild.create-channel.hh"

void run(client *client, const uint64_t guild_id, params *params, channel::dati *p_channel);

} // namespace create_channel

namespace member {

namespace get_list {

struct params {
  int limit; // the number of members to return (1-1000)
  uint64_t after; // the highest user id in the previous page
};

dati** run(client *client, const uint64_t guild_id, struct params *params);

} // namespace get_list
void remove(client *client, const uint64_t guild_id, const uint64_t user_id);

namespace modify {
#include "./specs-code/guild.member.modify.hh"

void run(client *client, const uint64_t guild_id, const uint64_t user_id, params *params, member::dati *p_member);

} // namespace modify

} // namespace member

namespace ban {

void get(client *client, const uint64_t guild_id, const uint64_t user_id, dati *p_ban);
dati** get_list(client *client, const uint64_t guild_id);
void create(client *client, const uint64_t guild_id, const uint64_t user_id, int delete_message_days, const char reason[]);
void remove(client *client, const uint64_t guild_id, const uint64_t user_id, const char reason[]);

} // namespace ban

namespace role {

dati** get_list(client *client, const uint64_t guild_id);

namespace create {
#include "./specs-code/guild.role.create.hh"

void run(client *client, const uint64_t guild_id, params *params, role::dati *p_role);

} // namespace create

void del(client *client, const uint64_t guild_id, const uint64_t role_id);

} // namespace role

} // namespace guild

namespace user { /* discord-public-user.cpp */

void get(client *client, const uint64_t user_id, dati *p_user);

namespace me { // current user centered functions

void get(client *client, dati *p_user);
guild::dati** get_guilds(client *client);
void leave_guild(client *client, const u64_snowflake_t guild_id);

} // namespace me

} // namespace user

} // namespace discord

#endif
