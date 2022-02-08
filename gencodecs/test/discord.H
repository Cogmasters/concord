ENUM_BEGIN(discord_channel_types)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_TEXT, = 0)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_DM, BLANK)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_VOICE, BLANK)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GROUP_DM, BLANK)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_CATEGORY, BLANK)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_NEWS, BLANK)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_STORE, BLANK)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_NEWS_THREAD, = 11)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_PUBLIC_THREAD, BLANK)
    ENUMERATOR(DISCORD_CHANNEL_TYPE_GUILD_PRIVATE_THREAD, BLANK)
    ENUMERATOR_LAST(DISCORD_CHANNEL_TYPE_GUILD_STAGE_VOICE, BLANK)
ENUM_END

STRUCT_BEGIN(discord_overwrite)
  COND_WRITE(this->id != 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, id)
  COND_END
    FIELD(int, type, 0)
    FIELD_PRINTF(uint64_t, SCNu64, PRIu64, allow)
    FIELD_PRINTF(uint64_t, SCNu64, PRIu64, deny)
STRUCT_END

LIST_BEGIN(discord_overwrites)
    LISTTYPE_STRUCT(discord_overwrite)
LIST_END

STRUCT_BEGIN(discord_channel)
  COND_WRITE(this->id != 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, id)
  COND_END
    FIELD_ENUM(discord_channel_types, type)
  COND_WRITE(this->guild_id != 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, guild_id)
  COND_END
    FIELD(int, position, 0)
  COND_WRITE(this->permission_overwrites != NULL)
    FIELD_STRUCT_PTR(discord_overwrites, *, permission_overwrites)
  COND_END
  COND_WRITE(this->name != NULL)
    FIELD_PTR(char, *, name)
  COND_END
  COND_WRITE(this->topic != NULL)
    FIELD_PTR(char, *, topic)
  COND_END
    FIELD(bool, nsfw, false)
  COND_WRITE(this->last_message_id != 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, last_message_id)
  COND_END
  COND_WRITE(this->bitrate != 0)
    FIELD(int, bitrate, 0)
  COND_END
  COND_WRITE(this->user_limit != 0)
    FIELD(int, user_limit, 0)
  COND_END
  COND_WRITE(this->rate_limit_per_user != 0)
    FIELD(int, rate_limit_per_user, 0)
  COND_END
  COND_WRITE(this->recipients != NULL)
    FIELD_STRUCT_PTR(discord_users, *, recipients)
  COND_END
  COND_WRITE(this->icon != NULL)
    FIELD_PTR(char, *, icon)
  COND_END
  COND_WRITE(this->owner_id != 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, owner_id)
  COND_END
  COND_WRITE(this->application_id != 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, application_id)
  COND_END
  COND_WRITE(this->parent_id != 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, parent_id)
  COND_END
#if 0
  COND_WRITE(this->last_pin_timestamp != 0)
    FIELD_PRINTF(u64unix_ms, last_pin_timestamp)
  COND_END
    FIELD_STRUCT_PTR(discord_messages, *, messages)
#endif
STRUCT_END

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
    ENUMERATOR_LAST(DISCORD_EARLY_VERIFIED_BOT_DEVELOPER, = 1 << 12)
ENUM_END

ENUM_BEGIN(discord_premium_types)
    ENUMERATOR(DISCORD_NITRO_CLASSIC, = 0)
    ENUMERATOR_LAST(DISCORD_NITRO, BLANK)
ENUM_END

STRUCT_BEGIN(discord_user)
  COND_WRITE(this->id != 0)
    FIELD_PRINTF(u64snowflake, SCNu64, PRIu64, id)
  COND_END
  COND_WRITE(this->username != NULL)
    FIELD_PTR(char, *, username)
  COND_END
  COND_WRITE(this->discriminator != NULL)
    FIELD_PTR(char, *, discriminator)
  COND_END
  COND_WRITE(this->avatar != NULL)
    FIELD_PTR(char, *, avatar)
  COND_END
    FIELD(bool, bot, false)
    FIELD_CUSTOM(bool, DECOR_BLANK, System, INIT_BLANK, CLEANUP_BLANK, 
                 JSON_ENCODER_bool, JSON_DECODER_bool, system, false)
    FIELD(bool, mfa_enabled, false)
  COND_WRITE(this->locale != NULL)
    FIELD_PTR(char, *, locale)
  COND_END
    FIELD(bool, verified, false)
  COND_WRITE(this->email != NULL)
    FIELD_PTR(char, *, email)
  COND_END
    FIELD_ENUM(discord_user_flags, flags)
  COND_WRITE(this->banner != NULL)
    FIELD_PTR(char, *, banner)
  COND_END
    FIELD_ENUM(discord_premium_types, premium_type)
    FIELD_ENUM(discord_user_flags, public_flags)
STRUCT_END

LIST_BEGIN(discord_users)
    LISTTYPE_STRUCT(discord_user)
LIST_END
