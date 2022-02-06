ENUM_BEGIN(discord_channel_types)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_TEXT, = 0)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_DM, )
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_VOICE, )
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GROUP_DM, )
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_CATEGORY, )
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_NEWS, )
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_STORE, )
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_NEWS_THREAD, = 11)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_PUBLIC_THREAD, )
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_PRIVATE_THREAD, )
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_STAGE_VOICE, )
ENUM_END(discord_channel_types)

STRUCT_BEGIN(discord_overwrite)
  IF(id, !=, 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, id)
  ENDIF
    FIELD(int, type, 0)
    FIELD_PRINTF(uint64_t, SCNu64, PRIu64, allow)
    FIELD_PRINTF(uint64_t, SCNu64, PRIu64, deny)
STRUCT_END(discord_overwrite)

LIST_BEGIN(discord_overwrites)
    LISTTYPE_STRUCT(discord_overwrite)
LIST_END(discord_overwrites)

STRUCT_BEGIN(discord_channel)
  IF(id, !=, 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, id)
  ENDIF
    FIELD_ENUM(discord_channel_types, type)
  IF(guild_id, !=, 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, guild_id)
  ENDIF
    FIELD(int, position, 0)
  IF(permission_overwrites, !=, NULL)
    FIELD_STRUCT_PTR(discord_overwrites, *, permission_overwrites)
  ENDIF
  IF(name, !=, NULL)
    FIELD_PTR(char, *, name)
  ENDIF
  IF(topic, !=, NULL)
    FIELD_PTR(char, *, topic)
  ENDIF
    FIELD(bool, nsfw, false)
  IF(last_message_id, !=, 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, last_message_id)
  ENDIF
  IF(bitrate, !=, 0)
    FIELD(int, bitrate, 0)
  ENDIF
  IF(user_limit, !=, 0)
    FIELD(int, user_limit, 0)
  ENDIF
  IF(rate_limit_per_user, !=, 0)
    FIELD(int, rate_limit_per_user, 0)
  ENDIF
  IF(recipients, !=, NULL)
    FIELD_STRUCT_PTR(discord_users, *, recipients)
  ENDIF
  IF(icon, !=, NULL)
    FIELD_PTR(char, *, icon)
  ENDIF
  IF(owner_id, !=, 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, owner_id)
  ENDIF
  IF(application_id, !=, 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, application_id)
  ENDIF
  IF(parent_id, !=, 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, parent_id)
  ENDIF
#if 0
  IF(last_pin_timestamp, !=, 0)
    FIELD_PRINTF(u64unix_ms, last_pin_timestamp)
    FIELD_STRUCT_PTR(discord_messages, *, messages)
#endif
STRUCT_END(discord_channel)

ENUM_BEGIN(discord_user_flags)
    ENUMERATOR(DISCORD_DISCORD_EMPLOYEE, = 1 << 0)
    ENUMERATOR(DISCORD_PARTNERED_SERVER_OWNER, = 1 << 1)
    ENUMERATOR(DISCORD_HYPESQUAD_EVENTS, = 1 << 2)
    ENUMERATOR(DISCORD_BUG_HUNTER_LEVEL_1, = 1 << 3)
    ENUMERATOR(DISCORD_HOUSE_BRAVERY, = 1 << 4)
    ENUMERATOR(DISCORD_HOUSE_BRILLIANCE, = 1 << 5)
    ENUMERATOR(DISCORD_HOUSE_BALANCE, = 1 << 6)
    ENUMERATOR(DISCORD_EARLY_SUPPORTER, = 1 << 7)
    ENUMERATOR(DISCORD_TEAM_USER, = 1 << 8)
    ENUMERATOR(DISCORD_SYSTEM, = 1 << 9)
    ENUMERATOR(DISCORD_BUG_HUNTER_LEVEL_2, = 1 << 10)
    ENUMERATOR(DISCORD_VERIFIED_BOT, = 1 << 11)
    ENUMERATOR(DISCORD_EARLY_VERIFIED_BOT_DEVELOPER, = 1 << 12)
ENUM_END(discord_user_flags)

ENUM_BEGIN(discord_premium_types)
    ENUMERATOR(DISCORD_NITRO_CLASSIC, = 0)
    ENUMERATOR(DISCORD_NITRO, )
ENUM_END(discord_premium_types)

STRUCT_BEGIN(discord_user)
  IF(id, !=, 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, id)
  ENDIF
  IF(username, !=, NULL)
    FIELD_PTR(char, *, username)
  ENDIF
  IF(discriminator, !=, NULL)
    FIELD_PTR(char, *, discriminator)
  ENDIF
  IF(avatar, !=, NULL)
    FIELD_PTR(char, *, avatar)
  ENDIF
    FIELD(bool, bot, false)
    FIELD_CUSTOM(bool, DECOR_BLANK, System, INIT_BLANK, CLEANUP_BLANK, 
                 JSON_ENCODER_bool, JSON_DECODER_bool, system, false)
    FIELD(bool, mfa_enabled, false)
  IF(locale, !=, NULL)
    FIELD_PTR(char, *, locale)
  ENDIF
    FIELD(bool, verified, false)
  IF(email, !=, NULL)
    FIELD_PTR(char, *, email)
  ENDIF
    FIELD_ENUM(discord_user_flags, flags)
  IF(banner, !=, NULL)
    FIELD_PTR(char, *, banner)
  ENDIF
    FIELD_ENUM(discord_premium_types, premium_type)
    FIELD_ENUM(discord_user_flags, public_flags)
STRUCT_END(discord_user)

LIST_BEGIN(discord_users)
    LISTTYPE_STRUCT(discord_user)
LIST_END(discord_users)
