/*****************************************************************************
 * Invite Datatypes
 * **************************************************************************/

ENUM(discord_invite_target_types)
    ENUMERATOR(DISCORD_INVITE_TARGET_STREAM, = 1)
    ENUMERATOR_LAST(DISCORD_INVITE_TARGET_EMBEDDED_APPLICATION, = 2)
ENUM_END

PUB_STRUCT(discord_invite)
  PP("the invite code (unique ID)")
    FIELD_PTR(code, char, *)
  PP("the guild this invite is for")
  COND_WRITE(this->guild != NULL)
    FIELD_STRUCT_PTR(guild, discord_guild, *)
  COND_END
  PP("the channel this invite is for")
    FIELD_STRUCT_PTR(channel, discord_channel, *)
  PP("the user who created the invite")
  COND_WRITE(this->inviter != NULL)
    FIELD_STRUCT_PTR(inviter, discord_user, *)
  COND_END
  PP("the type of target for this voice channel invite")
  COND_WRITE(this->target_type != 0)
    FIELD_ENUM(target_type, discord_invite_target_types)
  COND_END
  PP("the user whose stream to display for this voice channel stream invite")
  COND_WRITE(this->target_user != NULL)
    FIELD_STRUCT_PTR(target_user, discord_user, *)
  COND_END
  PP("the embedded application to open for this voice channel embedded"
       "application invite")
  COND_WRITE(this->target_application != NULL)
    FIELD_STRUCT_PTR(target_application, discord_application, *)
  COND_END
  PP("approximate count of online members")
    FIELD(approximate_presence_count, int, 0)
  PP("approximate count of total members")
    FIELD(approximate_member_count, int, 0)
  /* TODO: nullable */
  PP("the expiration date of this invite")
  COND_WRITE(this->expires_at != 0)
    FIELD_TIMESTAMP(expires_at)
  COND_END
  PP("stage instance data if there is a public stage instance in the stage"
       "channel this invite is for")
  COND_WRITE(this->stage_instance != NULL)
    FIELD_STRUCT_PTR(stage_instance, discord_invite_stage_instance, *)
  COND_END
  PP("guild scheduled event data, only included if `guild_scheduled_event_id`"
       "contains a valid guild scheduled event ID")
  COND_WRITE(this->guild_scheduled_event != NULL)
    FIELD_STRUCT_PTR(guild_scheduled_event, discord_guild_scheduled_event, *)
  COND_END
STRUCT_END

PUB_LIST(discord_invites)
    LISTTYPE_STRUCT(discord_invite)
LIST_END

STRUCT(discord_invite_metadata)
  PP("number of times this invite has been used")
    FIELD(uses, int, 0)
  PP("max number of times this invite can been used")
    FIELD(max_uses, int, 0)
  PP("duration (in seconds) after which the invite expires")
    FIELD(max_age, int, 0)
  PP("whether this invite only grants temporary membership")
    FIELD(temporary, bool, false)
  PP("when this invite was created")
  COND_WRITE(this->created_at != 0)
    FIELD_TIMESTAMP(created_at)
  COND_END
STRUCT_END

STRUCT(discord_invite_stage_instance)
  PP("the members speaking in the Stage")
  COND_WRITE(this->members != NULL)
    FIELD_STRUCT_PTR(members, discord_guild_members, *)
  COND_END
  PP("the number of users in the Stage")
    FIELD(participant_count, int, 0)
  PP("the number of users speaking in the Stage")
    FIELD(speaker_count, int, 0)
  PP("the topic of the Stage instance (1-120 characters)")
    FIELD_PTR(topic, char, *)
STRUCT_END

/*****************************************************************************
 * Invite REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_get_invite)
  PP("whether the invite should contain approximate member counts")
    FIELD(with_counts, bool, false)
  PP("whether the invite should contain the expiration date")
    FIELD(with_expiration, bool, false)
  PP("the guild scheduled event to include with the invite")
  COND_WRITE(this->guild_scheduled_event_id != 0)
    FIELD_SNOWFLAKE(guild_scheduled_event_id)
  COND_END
STRUCT_END
