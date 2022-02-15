/*****************************************************************************
 * Emoji Datatypes
 * **************************************************************************/

PUB_STRUCT(discord_emoji)
  PP("emoji ID")
    FIELD_SNOWFLAKE(id)
  PP("emoji name")
    FIELD_PTR(name, char, *)
  PP("roles allowed to use this emoji")
  COND_WRITE(this->roles != NULL)
    FIELD_STRUCT_PTR(roles, discord_roles, *)
  COND_END
  PP("user that created this emoji")
  COND_WRITE(this->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
  PP("whether this emoji must be wrapped in colons")
    FIELD(require_colons, bool, false)
  PP("whether this emoji is managed")
    FIELD(managed, bool, false)
  PP("whether this emoji is animated")
    FIELD(animated, bool, false)
  PP("whether this emoji can be used, may be false due to loss of Server"
       "Boosts")
    FIELD(available, bool, false)
STRUCT_END

PUB_LIST(discord_emojis)
    LISTTYPE_STRUCT(discord_emoji)
LIST_END

/*****************************************************************************
 * Emoji REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_create_guild_emoji)
  PP("name of the emoji")
    FIELD_PTR(name, char, *)
  /* TODO: implement base64 encoding */
#if 0
  PP("the 128x128 emoji image")
    FIELD_PTR(image, char, *)
#endif
  PP("roles allowed to use this emoji")
  COND_WRITE(this->roles != NULL)
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_modify_guild_emoji)
  PP("name of the emoji")
    FIELD_PTR(name, char, *)
  /* TODO: implement base64 encoding */
#if 0
  PP("the 128x128 emoji image")
    FIELD_PTR(image, char, *)
#endif
  PP("roles allowed to use this emoji")
  COND_WRITE(this->roles != NULL)
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  COND_END
STRUCT_END
