/*****************************************************************************
 * Stage Instance Datatypes
 * **************************************************************************/

ENUM(discord_privacy_level)
  DESC("the stage instance is visible publicly @deprecated deprecated value")
    ENUMERATOR(DISCORD_PRIVACY_PUBLIC, = 1)
  DESC("the stage instance is visible to only guild members")
    ENUMERATOR_LAST(DISCORD_PRIVACY_GUILD_ONLY, = 2)
ENUM_END

PUB_STRUCT(discord_stage_instance)
  DESC("the ID of this stage instance")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the guild ID of the associated stage channel")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("the ID of the associated stage channel")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the topic of the Stage instance (1-120 characters)")
    FIELD_PTR(topic, char, *)
  DESC("the privacy level of the stage instance")
  COND_WRITE(this->privacy_level != 0)
    FIELD_ENUM(privacy_level, discord_privacy_level)
  COND_END
  DESC("whether or not stage discovery is disabled @deprecated deprecated field")
    FIELD(discoverable_disabled, bool, false)
STRUCT_END

/*****************************************************************************
 * Stage Instance REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_create_stage_instance)
  DESC("the ID of the stage channel")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the topic of the Stage instance (1-120 characters)")
    FIELD_PTR(topic, char, *)
  DESC("the privacy level of the stage instance")
  COND_WRITE(this->privacy_level != 0)
    FIELD_ENUM(privacy_level, discord_privacy_level)
  COND_END
STRUCT_END

PUB_STRUCT(discord_modify_stage_instance)
  DESC("the topic of the Stage instance (1-120 characters)")
    FIELD_PTR(topic, char, *)
  DESC("the privacy level of the stage instance")
  COND_WRITE(this->privacy_level != 0)
    FIELD_ENUM(privacy_level, discord_privacy_level)
  COND_END
STRUCT_END
