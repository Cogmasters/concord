/*****************************************************************************
 * Guild Template Datatypes
 * **************************************************************************/

PUB_STRUCT(discord_guild_template)
  PP("the template code (unique ID)")
    FIELD_PTR(code, char, *)
  PP("template name")
    FIELD_PTR(name, char, *)
  PP("the description for the template")
    FIELD_PTR(description, char, *)
  PP("number of times this template has been used")
    FIELD(usage_count, int, 0)
  PP("the ID of the user who created the template")
    FIELD_SNOWFLAKE(creator_id)
  PP("the user who created the template")
    FIELD_STRUCT_PTR(creator, discord_user, *)
  PP("when this template was created")
    FIELD_TIMESTAMP(created_at)
  PP("when this template was last synced to the source guild")
    FIELD_TIMESTAMP(updated_at)
  PP("the ID of the guild this template is based on")
    FIELD_SNOWFLAKE(source_guild_id)
  PP("the guild snapshot this template contains")
    FIELD_STRUCT_PTR(serialized_source_guild, discord_guild, *)
  PP("whether the template has unsynced changes")
    FIELD(is_dirty, bool, false)
STRUCT_END

/*****************************************************************************
 * Guild Template REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_create_guild_from_guild_template)
  PP("name of the guild (2-100 characters)")
    FIELD_PTR(name, char, *)
  PP("base64 128x128 image for the guild icon")
  COND_WRITE(this->icon != NULL)
    FIELD_PTR(icon, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_create_guild_template)
  PP("name of the template (1-100 characters)")
    FIELD_PTR(name, char, *)
  PP("description for the template (0-120 characters)")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_modify_guild_template)
  PP("name of the template (1-100 characters)")
  COND_WRITE(this->name != NULL)
    FIELD_PTR(name, char, *)
  COND_END
  PP("description for the template (0-120 characters)")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
STRUCT_END
