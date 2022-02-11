/*****************************************************************************
 * Guild Template Datatypes
 * **************************************************************************/

PUB_STRUCT(discord_guild_template)
  DESC("the template code (unique ID)")
    FIELD_PTR(code, char, *)
  DESC("template name")
    FIELD_PTR(name, char, *)
  DESC("the description for the template")
    FIELD_PTR(description, char, *)
  DESC("number of times this template has been used")
    FIELD(usage_count, int, 0)
  DESC("the ID of the user who created the template")
    FIELD_PRINTF(creator_id, u64snowflake, PRIu64, SCNu64)
  DESC("the user who created the template")
    FIELD_STRUCT_PTR(creator, discord_user, *)
  /* TODO: implement iso8601 conversion */
#if 0
  DESC("when this template was created")
    FIELD_PRINTF(created_at, u64snowflake, PRIu64, SCNu64)
  DESC("when this template was last synced to the source guild")
    FIELD_PRINTF(updated_at, u64snowflake, PRIu64, SCNu64)
#endif
  DESC("the ID of the guild this template is based on")
    FIELD_PRINTF(source_guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("the guild snapshot this template contains")
    FIELD_STRUCT_PTR(serialized_source_guild, discord_guild, *)
  DESC("whether the template has unsynced changes")
    FIELD(is_dirty, bool, false)
STRUCT_END

/*****************************************************************************
 * Guild Template REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_create_guild_from_guild_template)
  DESC("name of the guild (2-100 characters)")
    FIELD_PTR(name, char, *)
  DESC("base64 128x128 image for the guild icon")
  COND_WRITE(this->icon != NULL)
    FIELD_PTR(icon, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_create_guild_template)
  DESC("name of the template (1-100 characters)")
    FIELD_PTR(name, char, *)
  DESC("description for the template (0-120 characters)")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_modify_guild_template)
  DESC("name of the template (1-100 characters)")
  COND_WRITE(this->name != NULL)
    FIELD_PTR(name, char, *)
  COND_END
  DESC("description for the template (0-120 characters)")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
STRUCT_END
