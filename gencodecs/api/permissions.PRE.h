/*****************************************************************************
 * Permissions Datatypes
 * **************************************************************************/

/** @defgroup DiscordPermissions Discord permissions
 * @see https://discord.com/developers/docs/topics/permissions#permissions
 * @ingroup DiscordConstants
 *  @{ */

/** Allows creation of instant invites */
PP_DEFINE(DISCORD_PERM_CREATE_INSTANT_INVITE 1 << 0)
/** Allows kicking members */
PP_DEFINE(DISCORD_PERM_KICK_MEMBERS 1 << 1)
/** Allows banning members */
PP_DEFINE(DISCORD_PERM_BAN_MEMBERS 1 << 2)
/** Allows all permissions and bypasses channel permission overwrites */
PP_DEFINE(DISCORD_PERM_ADMINISTRATOR 1 << 3)
/** Allows management and editing of channels */
PP_DEFINE(DISCORD_PERM_MANAGE_CHANNELS 1 << 4)
/** Allows management and editing of the guild */
PP_DEFINE(DISCORD_PERM_MANAGE_GUILD 1 << 5)
/** Allows for the addition of reactions to messages */
PP_DEFINE(DISCORD_PERM_ADD_REACTIONS 1 << 6)
/** Allows for viewing of audit logs */
PP_DEFINE(DISCORD_PERM_VIEW_AUDIT_LOG 1 << 7)
/** Allows for using priority speaker in a voice channel */
PP_DEFINE(DISCORD_PERM_PRIORITY_SPEAKER 1 << 8)
/** Allows the user to go live */
PP_DEFINE(DISCORD_PERM_STREAM 1 << 9)
/** Allows guild members to view a channel, which includes reading messages
     in text channels and joining voice channels */
PP_DEFINE(DISCORD_PERM_VIEW_CHANNEL 1 << 10)
/** Allows for sending messages in a channel (does not allow sending messages
     in threads) */
PP_DEFINE(DISCORD_PERM_SEND_MESSAGES 1 << 11)
/** Allows for sending of `/tts` messages */
PP_DEFINE(DISCORD_PERM_SEND_TTS_MESSAGES 1 << 12)
/** Allows for deletion of other users messages */
PP_DEFINE(DISCORD_PERM_MANAGE_MESSAGES 1 << 13)
/** Links sent by users with this permission will be auto-embedded */
PP_DEFINE(DISCORD_PERM_EMBED_LINKS 1 << 14)
/** Allows for uploading images and files */
PP_DEFINE(DISCORD_PERM_ATTACH_FILES 1 << 15)
/** Allows for reading of message history */
PP_DEFINE(DISCORD_PERM_READ_MESSAGE_HISTORY 1 << 16)
/** Allows for using the `@everyone` tag to notify all users in a channel,
     and the `@here` tag to notify all online users in a channel */
PP_DEFINE(DISCORD_PERM_MENTION_EVERYONE 1 << 17)
/** Allows the usage of custom emojis from other servers */
PP_DEFINE(DISCORD_PERM_USE_EXTERNAL_EMOJIS 1 << 18)
/** Allows for viewing guild insights */
PP_DEFINE(DISCORD_PERM_VIEW_GUILD_INSIGHTS 1 << 19)
/** Allows for joining of a voice channel */
PP_DEFINE(DISCORD_PERM_CONNECT 1 << 20)
/** Allows for speaking in a voice channel */
PP_DEFINE(DISCORD_PERM_SPEAK 1 << 21)
/** Allows for muting members in a voice channel */
PP_DEFINE(DISCORD_PERM_MUTE_MEMBERS 1 << 22)
/** Allows for deafening of members in a voice channel */
PP_DEFINE(DISCORD_PERM_DEAFEN_MEMBERS 1 << 23)
/** Allows for moving of members between voice channels */
PP_DEFINE(DISCORD_PERM_MOVE_MEMBERS 1 << 24)
/** Allows for using voice-activity-detection in a voice channel */
PP_DEFINE(DISCORD_PERM_USE_VAD 1 << 25)
/** Allows for modification of own nickname */
PP_DEFINE(DISCORD_PERM_CHANGE_NICKNAME 1 << 26)
/** Allows for modification of other users nicknames */
PP_DEFINE(DISCORD_PERM_MANAGE_NICKNAMES 1 << 27)
/** Allows management and editing of roles */
PP_DEFINE(DISCORD_PERM_MANAGE_ROLES 1 << 28)
/** Allows management and editing of webhooks */
PP_DEFINE(DISCORD_PERM_MANAGE_WEBHOOKS 1 << 29)
/** Allows management and editing of emojis and stickers */
PP_DEFINE(DISCORD_PERM_MANAGE_EMOJIS_AND_STICKERS 1 << 30)
/** Allows members to use application commands, including slash commands and
     context menu commands */
PP_DEFINE(DISCORD_PERM_USE_APPLICATION_COMMANDS 1 << 31)
/** Allows for requesting to speak in stage channels */
PP_DEFINE(DISCORD_PERM_REQUEST_TO_SPEAK 1 << 32)
/** Allows for creating, editing, and deleting scheduled events */
PP_DEFINE(DISCORD_PERM_MANAGE_EVENTS 1 << 33)
/** Allows for deleting and archiving threads, and viewing all private
     threads */
PP_DEFINE(DISCORD_PERM_MANAGE_THREADS 1 << 34)
/** Allows for creating public and announcement threads */
PP_DEFINE(DISCORD_PERM_CREATE_PUBLIC_THREADS 1 << 35)
/** Allows for creating private threads */
PP_DEFINE(DISCORD_PERM_CREATE_PRIVATE_THREADS 1 << 36)
/** Allows the usage of custom stickers from other servers */
PP_DEFINE(DISCORD_PERM_USE_EXTERNAL_STICKERS 1 << 37)
/** Allows for sending messages in threads */
PP_DEFINE(DISCORD_PERM_SEND_MESSAGES_IN_THREADS 1 << 38)
/** Allows for launching activities (applications with the `EMBEDDED` flag)
     in a voice channel) */
PP_DEFINE(DISCORD_PERM_START_EMBEDDED_ACTIVITIES 1 << 39)
/** Allows for timing out users to prevent them from sending or reacting to
     messages in chat and threads, and from speaking in voice and stage
     channels */
PP_DEFINE(DISCORD_PERM_MODERATE_MEMBERS 1 << 40)

/** @} DiscordPermissions */

/** @CCORD_pub_struct{discord_role} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_role)
  /** role id */
    FIELD_SNOWFLAKE(id)
  /** role name */
    FIELD_PTR(name, char, *)
  /** integer representationof hexadecimal color code */
    FIELD(color, int, 0)
  /** if this role is pinned in the user listing */
    FIELD(hoist, bool, false)
  /** role icon hash */
  COND_WRITE(self->icon != NULL)
    FIELD_PTR(icon, char, *)
  COND_END
  /** role unicode emoji */
  COND_WRITE(self->unicode_emoji != NULL)
    FIELD_PTR(unicode_emoji, char, *)
  COND_END
  /** position of this role */
    FIELD(position, int, 0)
  /** permission bit set */
    FIELD_BITMASK(permissions)
  /** whether this role is managed by an integration */
    FIELD(managed, bool, false)
  /** whether this roleis mentionable */
    FIELD(mentionable, bool, false)
  /** the tags this role has */
  COND_WRITE(self->tags != NULL)
    FIELD_STRUCT_PTR(tags, discord_role_tag, *)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_list{discord_roles} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_roles)
    LISTTYPE_STRUCT(discord_role)
LIST_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_role_tag)
  /** the id of the bot this role belongs to */
  COND_WRITE(self->bot_id != 0)
    FIELD_SNOWFLAKE(bot_id)
  COND_END
  /** the id of the integration this role belongs to */
  COND_WRITE(self->integration_id != 0)
    FIELD_SNOWFLAKE(integration_id)
  COND_END
  /** whether this is the guild's premium subscribe role */
    FIELD(premium_subscribe, bool, false)
STRUCT_END
#endif
