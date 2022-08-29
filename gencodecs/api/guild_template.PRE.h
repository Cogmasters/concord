/*****************************************************************************
 * Guild Template Datatypes
 * **************************************************************************/

/** @CCORD_pub_struct{discord_guild_template} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_guild_template)
  /** the template code (unique ID) */
    FIELD_PTR(code, char, *)
  /** template name */
    FIELD_PTR(name, char, *)
  /** the description for the template */
    FIELD_PTR(description, char, *)
  /** number of times this template has been used */
    FIELD(usage_count, int, 0)
  /** the ID of the user who created the template */
    FIELD_SNOWFLAKE(creator_id)
  /** the user who created the template */
    FIELD_STRUCT_PTR(creator, discord_user, *)
  /** when this template was created */
    FIELD_TIMESTAMP(created_at)
  /** when this template was last synced to the source guild */
    FIELD_TIMESTAMP(updated_at)
  /** the ID of the guild this template is based on */
    FIELD_SNOWFLAKE(source_guild_id)
  /** the guild snapshot this template contains */
    FIELD_STRUCT_PTR(serialized_source_guild, discord_guild, *)
  /** whether the template has unsynced changes */
    FIELD(is_dirty, bool, false)
STRUCT_END
#endif

/** @CCORD_pub_list{discord_guild_templates} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_guild_templates)
    LISTTYPE_STRUCT(discord_guild_template)
LIST_END
#endif

/*****************************************************************************
 * Guild Template REST parameters
 * **************************************************************************/

/** @CCORD_pub_struct{discord_create_guild_from_guild_template} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_create_guild_from_guild_template)
  /** name of the guild (2-100 characters) */
    FIELD_PTR(name, char, *)
  /** base64 128x128 image for the guild icon */
  COND_WRITE(self->icon != NULL)
    FIELD_PTR(icon, char, *)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_create_guild_template} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_create_guild_template)
  /** name of the template (1-100 characters) */
    FIELD_PTR(name, char, *)
  /** description for the template (0-120 characters) */
  COND_WRITE(self->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_guild_template} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_guild_template)
  /** name of the template (1-100 characters) */
  COND_WRITE(self->name != NULL)
    FIELD_PTR(name, char, *)
  COND_END
  /** description for the template (0-120 characters) */
  COND_WRITE(self->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
STRUCT_END
#endif
