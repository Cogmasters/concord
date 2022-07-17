/*****************************************************************************
 * Stage Instance Datatypes
 * **************************************************************************/

ENUM(discord_privacy_level)
  /** the stage instance is visible publicly @deprecated deprecated value */
    ENUMERATOR(DISCORD_PRIVACY_PUBLIC, = 1)
  /** the stage instance is visible to only guild members */
    ENUMERATOR_LAST(DISCORD_PRIVACY_GUILD_ONLY, = 2)
ENUM_END

/** @CCORD_pub_struct{discord_stage_instance} */
PUB_STRUCT(discord_stage_instance)
  /** the ID of this stage instance */
    FIELD_SNOWFLAKE(id)
  /** the guild ID of the associated stage channel */
    FIELD_SNOWFLAKE(guild_id)
  /** the ID of the associated stage channel */
    FIELD_SNOWFLAKE(channel_id)
  /** the topic of the Stage instance (1-120 characters) */
    FIELD_PTR(topic, char, *)
  /** the privacy level of the stage instance */
  COND_WRITE(self->privacy_level != 0)
    FIELD_ENUM(privacy_level, discord_privacy_level)
  COND_END
  /** whether or not stage discovery is disabled @deprecated deprecated field */
    FIELD(discoverable_disabled, bool, false)
STRUCT_END

LIST(discord_stage_instances)
    LISTTYPE_STRUCT(discord_stage_instance)
LIST_END

/*****************************************************************************
 * Stage Instance REST parameters
 * **************************************************************************/

/** @CCORD_pub_struct{discord_create_stage_instance} */
PUB_STRUCT(discord_create_stage_instance)
  /** the ID of the stage channel */
    FIELD_SNOWFLAKE(channel_id)
  /** the topic of the Stage instance (1-120 characters) */
    FIELD_PTR(topic, char, *)
  /** the privacy level of the stage instance */
  COND_WRITE(self->privacy_level != 0)
    FIELD_ENUM(privacy_level, discord_privacy_level)
  COND_END
STRUCT_END

/** @CCORD_pub_struct{discord_modify_stage_instance} */
PUB_STRUCT(discord_modify_stage_instance)
  /** the topic of the Stage instance (1-120 characters) */
    FIELD_PTR(topic, char, *)
  /** the privacy level of the stage instance */
  COND_WRITE(self->privacy_level != 0)
    FIELD_ENUM(privacy_level, discord_privacy_level)
  COND_END
STRUCT_END
