/*****************************************************************************
 * Sticker Datatypes
 * **************************************************************************/

ENUM(discord_sticker_types)
  PP("an official sticker in a pack, part of Nitro or in a removed"
       "purchasable pack")
    ENUMERATOR(DISCORD_STICKER_STANDARD, = 1)
  PP("a sticker uploaded to a Boosted guild for the guild's members")
    ENUMERATOR_LAST(DISCORD_STICKER_GUILD, = 2)
ENUM_END

ENUM(discord_sticker_format_types)
    ENUMERATOR(DISCORD_STICKER_FORMAT_PNG, = 1)
    ENUMERATOR(DISCORD_STICKER_FORMAT_APNG, = 2)
    ENUMERATOR_LAST(DISCORD_STICKER_FORMAT_LOTTIE, = 3)
ENUM_END

PUB_STRUCT(discord_sticker)
  PP("ID of the sticker")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  PP("for standard stickers, ID of the pack the sticker is from")
  COND_WRITE(this->pack_id != 0)
    FIELD_PRINTF(pack_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  PP("name of the sticker")
    FIELD_PTR(name, char, *)
  PP("description of the sticker")
    FIELD_PTR(description, char, *)
  PP("autocomplete/suggestion tags for the sticker (max 200 characters)")
    FIELD_PTR(tags, char, *)
  PP("type of sticker")
  COND_WRITE(this->type != 0)
    FIELD_ENUM(type, discord_sticker_types)
  COND_END
  PP("type of sticker format")
  COND_WRITE(this->format_type != 0)
    FIELD_ENUM(format_type, discord_sticker_format_types)
  COND_END
  PP("whether this guild sticker can be used, may be false due to loss of"
       "Server Boosts")
    FIELD(available, bool, false)
  PP("ID of the guild that owns this sticker")
  COND_WRITE(this->guild_id != 0)
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  PP("the user that uploaded the guild sticker")
  COND_WRITE(this->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
  PP("the standard sticker's sort order within its pack")
    FIELD(sort_value, int, 0)
STRUCT_END

LIST(discord_stickers)
    LISTTYPE_STRUCT(discord_sticker)
LIST_END

STRUCT(discord_sticker_item)
  PP("ID of the sticker")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  PP("name of the sticker")
    FIELD_PTR(name, char, *)
  PP("type of sticker format")
  COND_WRITE(this->format_type != 0)
    FIELD_ENUM(format_type, discord_sticker_format_types)
  COND_END
STRUCT_END

LIST(discord_sticker_items)
    LISTTYPE_STRUCT(discord_sticker_item)
LIST_END

STRUCT(discord_sticker_pack)
  PP("ID of the sticker")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  PP("the stickers in the pack")
  COND_WRITE(this->stickers != NULL)
    FIELD_STRUCT_PTR(stickers, discord_stickers, *)
  COND_END
  PP("name of the sticker pack")
    FIELD_PTR(name, char, *)
  PP("ID of the pack's SKU")
    FIELD_PRINTF(sku_id, u64snowflake, PRIu64, SCNu64)
  PP("ID of a sticker in the pack which is shown as the pack's icon")
  COND_WRITE(this->cover_sticker_id != 0)
    FIELD_PRINTF(cover_sticker_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  PP("description of the sticker pack")
    FIELD_PTR(description, char, *)
  PP("ID of the sticker pack's banner image")
  COND_WRITE(this->banner_asset_id != 0)
    FIELD_PRINTF(banner_asset_id, u64snowflake, PRIu64, SCNu64)
  COND_END
STRUCT_END

/*****************************************************************************
 * Sticker REST parameters
 * **************************************************************************/

/* TODO: do not generate JSON encoding functions */
STRUCT(discord_create_guild_sticker)
  PP("name of the sticker (2-30 characters)")
    FIELD_PTR(name, char, *)
  PP("description of the sticker (empty or 2-100 characters)")
    FIELD_PTR(description, char, *)
  PP("autocomplete/suggestion tags for the sticker (max 200 characters)")
    FIELD_PTR(tags, char, *)
  PP("the sticker file to upload, must be a PNG, APNG, or Lottie JSON file"
       "max 500 KB")
    FIELD_STRUCT_PTR(file, discord_attachment, *)
STRUCT_END

PUB_STRUCT(discord_modify_guild_sticker)
  PP("name of the sticker (2-30 characters)")
    FIELD_PTR(name, char, *)
  PP("description of the sticker (empty or 2-100 characters)")
    FIELD_PTR(description, char, *)
  PP("autocomplete/suggestion tags for the sticker (max 200 characters)")
    FIELD_PTR(tags, char, *)
STRUCT_END
