/*****************************************************************************
 * Teams Datatypes
 * **************************************************************************/

#if GENCODECS_RECIPE == DATA
ENUM(discord_membership_state)
    ENUMERATOR(DISCORD_MEMBERSHIP_INVITED, = 1)
    ENUMERATOR_LAST(DISCORD_MEMBERSHIP_ACCEPTED, = 2)
ENUM_END
#endif

/** @CCORD_pub_struct{discord_team} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_team)
  /** a hash image of the team's icon */
    FIELD_PTR(icon, char, *)
  /** the unique ID of the team */
    FIELD_SNOWFLAKE(id)
  /** the members of the team */
  COND_WRITE(self->members != NULL)
    FIELD_STRUCT_PTR(members, discord_team_members, *)
  COND_END
  /** the name of the team */
    FIELD_PTR(name, char, *)
  /** the user ID of the current team owner */
    FIELD_SNOWFLAKE(owner_user_id)
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_team_member)
  /** the user's membership state on the team */
    FIELD_ENUM(membership_state, discord_membership_state)
  /** will always be \"[\"*\"]\" */
  COND_WRITE(self->permissions != NULL)
    FIELD_STRUCT_PTR(permissions, bitmasks, *)
  COND_END
  /** the ID of the parent team of which they are a member */
    FIELD_SNOWFLAKE(team_id)
  /** the avatar, discriminator, id,and username of the user */
  COND_WRITE(self->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
LIST(discord_team_members)
    LISTTYPE_STRUCT(discord_team_member)
LIST_END
#endif
