/*****************************************************************************
 * Emoji Datatypes
 * **************************************************************************/

PUB_STRUCT(discord_emoji)
  DESC("emoji ID")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("emoji name")
    FIELD_PTR(name, char, *)
  DESC("roles allowed to use this emoji")
  COND_WRITE(this->roles != NULL)
    FIELD_STRUCT_PTR(roles, discord_roles, *)
  COND_END
  DESC("user that created this emoji")
  COND_WRITE(this->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
  DESC("whether this emoji must be wrapped in colons")
    FIELD(require_colons, bool, false)
  DESC("whether this emoji is managed")
    FIELD(managed, bool, false)
  DESC("whether this emoji is animated")
    FIELD(animated, bool, false)
  DESC("whether this emoji can be used, may be false due to loss of Server"
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
  DESC("name of the emoji")
    FIELD_PTR(name, char, *)
  /* TODO: implement base64 encoding */
#if 0
  DESC("the 128x128 emoji image")
    FIELD_PTR(image, char, *)
#endif
  DESC("roles allowed to use this emoji")
  COND_WRITE(this->roles != NULL)
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_modify_guild_emoji)
  DESC("name of the emoji")
    FIELD_PTR(name, char, *)
  /* TODO: implement base64 encoding */
#if 0
  DESC("the 128x128 emoji image")
    FIELD_PTR(image, char, *)
#endif
  DESC("roles allowed to use this emoji")
  COND_WRITE(this->roles != NULL)
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  COND_END
STRUCT_END
