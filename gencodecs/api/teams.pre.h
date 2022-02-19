/*****************************************************************************
 * Teams Datatypes
 * **************************************************************************/

ENUM(discord_membership_state)
    ENUMERATOR(DISCORD_MEMBERSHIP_INVITED, = 1)
    ENUMERATOR_LAST(DISCORD_MEMBERSHIP_ACCEPTED, = 2)
ENUM_END

PUB_STRUCT(discord_team)
  PP("a hash image of the team's icon")
    FIELD_PTR(icon, char, *)
  PP("the unique ID of the team")
    FIELD_SNOWFLAKE(id)
  PP("the members of the team")
  COND_WRITE(this->members != NULL)
    FIELD_STRUCT_PTR(members, discord_team_members, *)
  COND_END
  PP("the name of the team")
    FIELD_PTR(name, char, *)
  PP("the user ID of the current team owner")
    FIELD_SNOWFLAKE(owner_user_id)
STRUCT_END

STRUCT(discord_team_member)
  PP("the user's membership state on the team")
    FIELD_ENUM(membership_state, discord_membership_state)
  PP("will always be \"[\"*\"]\"")
  COND_WRITE(this->permissions != NULL)
    FIELD_STRUCT_PTR(permissions, strings, *)
  COND_END
  PP("the ID of the parent team of which they are a member")
    FIELD_SNOWFLAKE(team_id)
  PP("the avatar, discriminator, id,and username of the user")
  COND_WRITE(this->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
STRUCT_END

LIST(discord_team_members)
    LISTTYPE_STRUCT(discord_team_member)
LIST_END
