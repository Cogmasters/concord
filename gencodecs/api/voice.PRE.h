/*****************************************************************************
 * Voice Datatypes
 * **************************************************************************/

/** @CCORD_pub_struct{discord_voice_state} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_voice_state)
  /** the guild ID this voice state is for */
    FIELD_SNOWFLAKE(guild_id)
  /** the channel ID this user is connected to */
    FIELD_SNOWFLAKE(channel_id)
  /** the user ID this voice state is for */
    FIELD_SNOWFLAKE(user_id)
  /** the guild member this voice state is for */
    FIELD_STRUCT_PTR(member, discord_guild_member, *)
  /** the session ID for this voice state */
    FIELD_PTR(session_id, char, *)
  /** whether this user is deafened by the server */
    FIELD(deaf, bool, false)
  /** whether this user is muted by the server */
    FIELD(mute, bool, false)
  /** whether this user is locally deafened */
    FIELD(self_deaf, bool, false)
  /** whether this user is locally muted */
    FIELD(self_mute, bool, false)
  /** whether this user is streaming using \"Go Live\" */
    FIELD(self_stream, bool, false)
  /** whether this user is muted by the current user */
    FIELD(self_video, bool, false)
  /** whether this user is muted by the current user */
    FIELD(suppress, bool, false)
  /* TODO: nullable */
  /** the time at which the user requested to speak */
  COND_WRITE(self->request_to_speak_timestamp)
    FIELD_TIMESTAMP(request_to_speak_timestamp)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_list{discord_voice_states} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_voice_states)
    LISTTYPE_STRUCT(discord_voice_state)
LIST_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_voice_region)
  /** unique ID for the region */
    FIELD_PTR(id, char, *)
  /** name of the region */
    FIELD_PTR(name, char, *)
  /** true for a single server that is closest to the current user's client */
    FIELD(optimal, bool, false)
  /** whether this is a deprecated voice region (avoid switching to these) */
    FIELD(deprecated, bool, false)
  /** whether this is a custom voice region (used for events/etc) */
    FIELD(custom, bool, false)
STRUCT_END
#endif

/** @CCORD_pub_list{discord_voice_regions} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_voice_regions)
    LISTTYPE_STRUCT(discord_voice_region)
LIST_END
#endif
