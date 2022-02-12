/*****************************************************************************
 * Voice Datatypes
 * **************************************************************************/

PUB_STRUCT(discord_voice_state)
  DESC("the guild ID this voice state is for")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("the channel ID this user is connected to")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the user ID this voice state is for")
    FIELD_PRINTF(user_id, u64snowflake, PRIu64, SCNu64)
  DESC("the guild member this voice state is for")
    FIELD_STRUCT_PTR(member, discord_guild_member, *)
  DESC("the session ID for this voice state")
    FIELD_PTR(session_id, char, *)
  DESC("whether this user is deafened by the server")
    FIELD(deaf, bool, false)
  DESC("whether this user is muted by the server")
    FIELD(mute, bool, false)
  DESC("whether this user is locally deafened")
    FIELD(self_deaf, bool, false)
  DESC("whether this user is locally muted")
    FIELD(self_mute, bool, false)
  DESC("whether this user is streaming using \"Go Live\"")
    FIELD(self_stream, bool, false)
  DESC("whether this user is muted by the current user")
    FIELD(self_video, bool, false)
  DESC("whether this user is muted by the current user")
    FIELD(suppress, bool, false)
  /* TODO: iso8601 support */
  /* TODO: nullable */
#if 0
  DESC("the time at which the user requested to speak")
  COND_WRITE(this->request_to_speak_timestamp)
    FIELD_PRINTF(request_to_speak_timestamp, u64snowflake, PRIu64, SCNu64)
  COND_END
#endif
STRUCT_END

PUB_LIST(discord_voice_states)
    LISTTYPE_STRUCT(discord_voice_state)
LIST_END

STRUCT(discord_voice_region)
  DESC("unique ID for the region")
    FIELD_PTR(id, char, *)
  DESC("name of the region")
    FIELD_PTR(name, char, *)
  DESC("true for a single server that is closest to the current user's client")
    FIELD(optimal, bool, false)
  DESC("whether this is a deprecated voice region (avoid switching to these)")
    FIELD(deprecated, bool, false)
  DESC("whether this is a custom voice region (used for events/etc)")
    FIELD(custom, bool, false)
STRUCT_END

PUB_LIST(discord_voice_regions)
    LISTTYPE_STRUCT(discord_voice_region)
LIST_END
