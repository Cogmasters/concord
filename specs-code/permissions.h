/* This file is generated from specs/permissions.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions
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
