/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/topics/permissions
*/


enum discord_permissions_bitwise_flags discord_permissions_bitwise_flags_from_string(char *s){
  if(strcasecmp("ZERO", s) == 0) return DISCORD_PERMISSIONS_ZERO;
  if(strcasecmp("CREATE_INSTANT_INVITE", s) == 0) return DISCORD_PERMISSIONS_CREATE_INSTANT_INVITE;
  if(strcasecmp("KICK_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_KICK_MEMBERS;
  if(strcasecmp("BAN_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_BAN_MEMBERS;
  if(strcasecmp("ADMINISTRATOR", s) == 0) return DISCORD_PERMISSIONS_ADMINISTRATOR;
  if(strcasecmp("MANAGE_CHANNELS", s) == 0) return DISCORD_PERMISSIONS_MANAGE_CHANNELS;
  if(strcasecmp("MANAGE_GUILD", s) == 0) return DISCORD_PERMISSIONS_MANAGE_GUILD;
  if(strcasecmp("ADD_REACTIONS", s) == 0) return DISCORD_PERMISSIONS_ADD_REACTIONS;
  if(strcasecmp("VIEW_AUDIT_LOG", s) == 0) return DISCORD_PERMISSIONS_VIEW_AUDIT_LOG;
  if(strcasecmp("PRIORITY_SPEAKER", s) == 0) return DISCORD_PERMISSIONS_PRIORITY_SPEAKER;
  if(strcasecmp("STREAM", s) == 0) return DISCORD_PERMISSIONS_STREAM;
  if(strcasecmp("VIEW_CHANNEL", s) == 0) return DISCORD_PERMISSIONS_VIEW_CHANNEL;
  if(strcasecmp("SEND_MESSAGES", s) == 0) return DISCORD_PERMISSIONS_SEND_MESSAGES;
  if(strcasecmp("SEND_TTS_MESSAGES", s) == 0) return DISCORD_PERMISSIONS_SEND_TTS_MESSAGES;
  if(strcasecmp("MANAGE_MESSAGES", s) == 0) return DISCORD_PERMISSIONS_MANAGE_MESSAGES;
  if(strcasecmp("EMBED_LINKS", s) == 0) return DISCORD_PERMISSIONS_EMBED_LINKS;
  if(strcasecmp("ATTACH_FILES", s) == 0) return DISCORD_PERMISSIONS_ATTACH_FILES;
  if(strcasecmp("READ_MESSAGE_HISTORY", s) == 0) return DISCORD_PERMISSIONS_READ_MESSAGE_HISTORY;
  if(strcasecmp("MENTION_EVERYONE", s) == 0) return DISCORD_PERMISSIONS_MENTION_EVERYONE;
  if(strcasecmp("USE_EXTERNAL_EMOJIS", s) == 0) return DISCORD_PERMISSIONS_USE_EXTERNAL_EMOJIS;
  if(strcasecmp("VIEW_GUILD_INSIGHTS", s) == 0) return DISCORD_PERMISSIONS_VIEW_GUILD_INSIGHTS;
  if(strcasecmp("CONNECT", s) == 0) return DISCORD_PERMISSIONS_CONNECT;
  if(strcasecmp("SPEAK", s) == 0) return DISCORD_PERMISSIONS_SPEAK;
  if(strcasecmp("MUTE_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_MUTE_MEMBERS;
  if(strcasecmp("DEAFEN_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_DEAFEN_MEMBERS;
  if(strcasecmp("MOVE_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_MOVE_MEMBERS;
  if(strcasecmp("USE_VAD", s) == 0) return DISCORD_PERMISSIONS_USE_VAD;
  if(strcasecmp("CHANGE_NICKNAME", s) == 0) return DISCORD_PERMISSIONS_CHANGE_NICKNAME;
  if(strcasecmp("MANAGE_NICKNAMES", s) == 0) return DISCORD_PERMISSIONS_MANAGE_NICKNAMES;
  if(strcasecmp("MANAGE_ROLES", s) == 0) return DISCORD_PERMISSIONS_MANAGE_ROLES;
  if(strcasecmp("MANAGE_WEBHOOKS", s) == 0) return DISCORD_PERMISSIONS_MANAGE_WEBHOOKS;
  if(strcasecmp("MANAGE_EMOJIS", s) == 0) return DISCORD_PERMISSIONS_MANAGE_EMOJIS;
  abort();
}
char* discord_permissions_bitwise_flags_to_string(enum discord_permissions_bitwise_flags v){
  if (v == DISCORD_PERMISSIONS_ZERO) return "ZERO";
  if (v == DISCORD_PERMISSIONS_CREATE_INSTANT_INVITE) return "CREATE_INSTANT_INVITE";
  if (v == DISCORD_PERMISSIONS_KICK_MEMBERS) return "KICK_MEMBERS";
  if (v == DISCORD_PERMISSIONS_BAN_MEMBERS) return "BAN_MEMBERS";
  if (v == DISCORD_PERMISSIONS_ADMINISTRATOR) return "ADMINISTRATOR";
  if (v == DISCORD_PERMISSIONS_MANAGE_CHANNELS) return "MANAGE_CHANNELS";
  if (v == DISCORD_PERMISSIONS_MANAGE_GUILD) return "MANAGE_GUILD";
  if (v == DISCORD_PERMISSIONS_ADD_REACTIONS) return "ADD_REACTIONS";
  if (v == DISCORD_PERMISSIONS_VIEW_AUDIT_LOG) return "VIEW_AUDIT_LOG";
  if (v == DISCORD_PERMISSIONS_PRIORITY_SPEAKER) return "PRIORITY_SPEAKER";
  if (v == DISCORD_PERMISSIONS_STREAM) return "STREAM";
  if (v == DISCORD_PERMISSIONS_VIEW_CHANNEL) return "VIEW_CHANNEL";
  if (v == DISCORD_PERMISSIONS_SEND_MESSAGES) return "SEND_MESSAGES";
  if (v == DISCORD_PERMISSIONS_SEND_TTS_MESSAGES) return "SEND_TTS_MESSAGES";
  if (v == DISCORD_PERMISSIONS_MANAGE_MESSAGES) return "MANAGE_MESSAGES";
  if (v == DISCORD_PERMISSIONS_EMBED_LINKS) return "EMBED_LINKS";
  if (v == DISCORD_PERMISSIONS_ATTACH_FILES) return "ATTACH_FILES";
  if (v == DISCORD_PERMISSIONS_READ_MESSAGE_HISTORY) return "READ_MESSAGE_HISTORY";
  if (v == DISCORD_PERMISSIONS_MENTION_EVERYONE) return "MENTION_EVERYONE";
  if (v == DISCORD_PERMISSIONS_USE_EXTERNAL_EMOJIS) return "USE_EXTERNAL_EMOJIS";
  if (v == DISCORD_PERMISSIONS_VIEW_GUILD_INSIGHTS) return "VIEW_GUILD_INSIGHTS";
  if (v == DISCORD_PERMISSIONS_CONNECT) return "CONNECT";
  if (v == DISCORD_PERMISSIONS_SPEAK) return "SPEAK";
  if (v == DISCORD_PERMISSIONS_MUTE_MEMBERS) return "MUTE_MEMBERS";
  if (v == DISCORD_PERMISSIONS_DEAFEN_MEMBERS) return "DEAFEN_MEMBERS";
  if (v == DISCORD_PERMISSIONS_MOVE_MEMBERS) return "MOVE_MEMBERS";
  if (v == DISCORD_PERMISSIONS_USE_VAD) return "USE_VAD";
  if (v == DISCORD_PERMISSIONS_CHANGE_NICKNAME) return "CHANGE_NICKNAME";
  if (v == DISCORD_PERMISSIONS_MANAGE_NICKNAMES) return "MANAGE_NICKNAMES";
  if (v == DISCORD_PERMISSIONS_MANAGE_ROLES) return "MANAGE_ROLES";
  if (v == DISCORD_PERMISSIONS_MANAGE_WEBHOOKS) return "MANAGE_WEBHOOKS";
  if (v == DISCORD_PERMISSIONS_MANAGE_EMOJIS) return "MANAGE_EMOJIS";

  return (void*)0;
}
bool discord_permissions_bitwise_flags_has(enum discord_permissions_bitwise_flags v, char *s) {
  enum discord_permissions_bitwise_flags v1 = discord_permissions_bitwise_flags_from_string(s);
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  return false;
}
