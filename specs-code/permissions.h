/* This file is generated from specs/permissions.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions
*/


enum discord_permissions_bitwise_flags {
  ZERO = 0, // No permission bits
  CREATE_INSTANT_INVITE = 1, // Allows creation of instant invites  T, V
  KICK_MEMBERS = 2, // Allows kicking members
  BAN_MEMBERS = 4, // Allows banning members
  ADMINISTRATOR = 8, // Allows all permissions and bypasses channel permission overwrites   
  MANAGE_CHANNELS = 16, // Allows management and editing of channels   T, V
  MANAGE_GUILD = 32, // Allows management and editing of the guild  
  ADD_REACTIONS = 64, // Allows for the addition of reactions to messages    T
  VIEW_AUDIT_LOG = 128, // Allows for viewing of audit logs    
  PRIORITY_SPEAKER = 256, // Allows for using priority speaker in a voice channel    V
  STREAM = 512, // Allows the user to go live  V
  VIEW_CHANNEL = 1024, // Allows guild members to view a channel, which includes reading messages in text channels    T, V
  SEND_MESSAGES = 2048, // Allows for sending messages in a channel    T
  SEND_TTS_MESSAGES = 4096, // Allows for sending of /tts messages T
  MANAGE_MESSAGES = 8192, // Allows for deletion of other users messages T
  EMBED_LINKS = 16384, // Links sent by users with this permission will be auto-embedded  T
  ATTACH_FILES = 32768, // Allows for uploading images and files   T
  READ_MESSAGE_HISTORY = 65536, // Allows for reading of message history   T
  MENTION_EVERYONE = 131072, // Allows for using the @everyone tag to notify all users in a channel, and the @here tag to notify all online users in a channel  T
  USE_EXTERNAL_EMOJIS = 262144, // Allows the usage of custom emojis from other servers    T
  VIEW_GUILD_INSIGHTS = 524288, // Allows for viewing guild insights   
  CONNECT = 1048576, // Allows for joining of a voice channel   V
  SPEAK = 2097152, // Allows for speaking in a voice channel  V
  MUTE_MEMBERS = 4194304, // Allows for muting members in a voice channel    V
  DEAFEN_MEMBERS = 8388608, // Allows for deafening of members in a voice channel  V
  MOVE_MEMBERS = 16777216, // Allows for moving of members between voice channels V
  USE_VAD = 33554432, // Allows for using voice-activity-detection in a voice channel    V
  CHANGE_NICKNAME = 67108864, // Allows for modification of own nickname 
  MANAGE_NICKNAMES = 134217728, // Allows for modification of other users nicknames    
  MANAGE_ROLES = 268435456, // Allows management and editing of roles  T, V
  MANAGE_WEBHOOKS = 536870912, // Allows management and editing of webhooks   T, V
  MANAGE_EMOJIS = 1073741824, // Allows management and editing of emojis
};
