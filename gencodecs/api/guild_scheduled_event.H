/*****************************************************************************
 * Guild Scheduled Event Datatypes
 * **************************************************************************/

ENUM(discord_guild_scheduled_event_privacy_level)
  DESC("the scheduled event is only accessible to guild members")
    ENUMERATOR_LAST(DISCORD_GUILD_SCHEDULED_EVENT_GUILD_ONLY, = 2)
ENUM_END

ENUM(discord_guild_scheduled_event_entity_types)
    ENUMERATOR(DISCORD_GUILD_SCHEDULED_EVENT_ENTITY_STAGE_INSTANCE, = 1)
    ENUMERATOR(DISCORD_GUILD_SCHEDULED_EVENT_ENTITY_VOICE, = 2)
    ENUMERATOR_LAST(DISCORD_GUILD_SCHEDULED_EVENT_ENTITY_EXTERNAL, = 3)
ENUM_END

ENUM(discord_guild_scheduled_event_status)
    ENUMERATOR(DISCORD_GUILD_SCHEDULED_EVENT_SCHEDULED, = 1)
    ENUMERATOR(DISCORD_GUILD_SCHEDULED_EVENT_ACTIVE, = 2)
    ENUMERATOR(DISCORD_GUILD_SCHEDULED_EVENT_COMPLETED, = 3)
    ENUMERATOR_LAST(DISCORD_GUILD_SCHEDULED_EVENT_CANCELED, = 4)
ENUM_END

PUB_STRUCT(discord_guild_scheduled_event)
  DESC("the ID of the scheduled event")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the guild ID which the scheduled event belongs to")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("the channel ID in which the scheduled event will be hosted, or `NULL`"
       "if `entity_type` is @ref DISCORD_SCHEDULED_ENTITY_EXTERNAL")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the ID of the user that created the scheduled event")
    FIELD_PRINTF(creator_id, u64snowflake, PRIu64, SCNu64)
  DESC("the name of the scheduled event (1-100 characters)")
    FIELD_PTR(name, char, *)
  DESC("the description of the scheduled event (1-1000 characters)")
    FIELD_PTR(description, char, *)
  /* TODO: iso8601 conversion */
#if 0
  DESC("the time the scheduled event will start")
    FIELD_PRINTF(scheduled_start_time, u64snowflake, PRIu64, SCNu64)
  DESC("the time the scheduled event will end, required if `entity_type` is"
       "@ref DISCORD_SCHEDULED_ENTITY_EXTERNAL")
    FIELD_PRINTF(scheduled_end_time, u64snowflake, PRIu64, SCNu64)
#endif
  DESC("the privacy level of the scheduled event")
  COND_WRITE(this->privacy_level != 0)
    FIELD_ENUM(privacy_level, discord_guild_scheduled_event_privacy_level)
  COND_END
  DESC("the status of the scheduled event")
  COND_WRITE(this->status != 0)
    FIELD_ENUM(status, discord_guild_scheduled_event_status)
  COND_END
  DESC("the type of scheduled event")
  COND_WRITE(this->entity_type != 0)
    FIELD_ENUM(entity_type, discord_guild_scheduled_event_entity_types)
  COND_END
  DESC("the ID of an entity associated with a guild scheduled event")
    FIELD_PRINTF(entity_id, u64snowflake, PRIu64, SCNu64)
  DESC("additional metadata for the guild scheduled event")
  COND_WRITE(this->entity_metadata != NULL)
    FIELD_STRUCT_PTR(entity_metadata, discord_guild_scheduled_event_entity_metadata, *)
  COND_END
  DESC("the user that created the scheduled event")
  COND_WRITE(this->creator != NULL)
    FIELD_STRUCT_PTR(creator, discord_user, *)
  COND_END
  DESC("the number of users subscribed to the scheduled event")
    FIELD(user_count, int, 0)
  DESC("the cover image hashof the scheduled event")
    FIELD_PTR(image, char, *)
STRUCT_END

PUB_LIST(discord_guild_scheduled_events)
    LISTTYPE_STRUCT(discord_guild_scheduled_event)
LIST_END

STRUCT(discord_guild_scheduled_event_entity_metadata)
  DESC("location of the event (1-100 characters)")
  COND_WRITE(this->location != NULL)
    FIELD_PTR(location, char, *)
  COND_END
STRUCT_END

STRUCT(discord_guild_scheduled_event_user)
  DESC("the scheduled event ID which the user subscribed to")
    FIELD_PRINTF(guild_scheduled_event_id, u64snowflake, PRIu64, SCNu64)
  DESC("user which subscribed to an event")
  COND_WRITE(this->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
  DESC("guild member data for this user for the guild which this event belongs"
       "to, if any")
  COND_WRITE(this->member != NULL)
    FIELD_STRUCT_PTR(member, discord_guild_member, *)
  COND_END
STRUCT_END

/*****************************************************************************
 * Guild Scheduled Event REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_list_scheduled_events_for_guild)
  DESC("include number of users subscribed to each event")
    FIELD(with_user_count, bool, false)
STRUCT_END

PUB_STRUCT(discord_create_guild_scheduled_event)
  DESC("the channel ID of the scheduled event")
  COND_WRITE(this->channel_id != 0)
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("the entity metadata of the scheduled event")
  COND_WRITE(this->entity_metadata != NULL)
    FIELD_STRUCT_PTR(entity_metadata, discord_guild_scheduled_event_entity_metadata, *)
  COND_END
  DESC("the name of the scheduled event")
    FIELD_PTR(name, char, *)
  /* TODO: iso8601 conversion */
#if 0
  DESC("the time the scheduled event will start")
  COND_WRITE(this->scheduled_start_time != 0)
    FIELD_PRINTF(scheduled_start_time, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("the time the scheduled event will end")
  COND_WRITE(this->scheduled_end_time != 0)
    FIELD_PRINTF(scheduled_end_time, u64snowflake, PRIu64, SCNu64)
  COND_END
#endif
  DESC("the description of the scheduled event")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
  DESC("the entity type of the scheduled event")
  COND_WRITE(this->entity_type != 0)
    FIELD_ENUM(entity_type, discord_guild_scheduled_event_entity_types)
  COND_END
  DESC("the cover image of the scheduled event")
  COND_WRITE(this->image != NULL)
    FIELD_PTR(image, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_get_guild_scheduled_event)
  DESC("include number of users subscribed to each event")
    FIELD(with_user_count, bool, false)
STRUCT_END

PUB_STRUCT(discord_modify_guild_scheduled_event)
  DESC("the channel ID of the scheduled event")
  COND_WRITE(this->channel_id != 0)
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("the entity metadata of the scheduled event")
  COND_WRITE(this->entity_metadata != NULL)
    FIELD_STRUCT_PTR(entity_metadata, discord_guild_scheduled_event_entity_metadata, *)
  COND_END
  DESC("the name of the scheduled event")
    FIELD_PTR(name, char, *)
  /* TODO: iso8601 conversion */
#if 0
  DESC("the time the scheduled event will start")
  COND_WRITE(this->scheduled_start_time != 0)
    FIELD_PRINTF(scheduled_start_time, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("the time the scheduled event will end")
  COND_WRITE(this->scheduled_end_time != 0)
    FIELD_PRINTF(scheduled_end_time, u64snowflake, PRIu64, SCNu64)
  COND_END
#endif
  DESC("the description of the scheduled event")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
  DESC("the entity type of the scheduled event")
  COND_WRITE(this->entity_type != 0)
    FIELD_ENUM(entity_type, discord_guild_scheduled_event_entity_types)
  COND_END
  DESC("the status of the scheduled event")
  COND_WRITE(this->status != 0)
    FIELD_ENUM(status, discord_guild_scheduled_event_status)
  COND_END
  DESC("the cover image of the scheduled event")
  COND_WRITE(this->image != NULL)
    FIELD_PTR(image, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_get_guild_scheduled_event_users)
  DESC("number of users to return (up to maximum of 100)")
    FIELD(limit, int, 0)
  DESC("include guild member data if exists")
    FIELD(with_member, bool, false)
  DESC("consider only users before given user ID")
  COND_WRITE(this->before != 0)
    FIELD_PRINTF(before, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("consider only users after given user ID")
  COND_WRITE(this->after != 0)
    FIELD_PRINTF(after, u64snowflake, PRIu64, SCNu64)
  COND_END
STRUCT_END
