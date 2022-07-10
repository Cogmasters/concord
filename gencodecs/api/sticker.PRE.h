/*****************************************************************************
 * Sticker Datatypes
 * **************************************************************************/

ENUM(discord_sticker_types)
  /** an official sticker in a pack, part of Nitro or in a removed
       purchasable pack */
    ENUMERATOR(DISCORD_STICKER_STANDARD, = 1)
  /** a sticker uploaded to a Boosted guild for the guild's members */
    ENUMERATOR_LAST(DISCORD_STICKER_GUILD, = 2)
ENUM_END

ENUM(discord_sticker_format_types)
    ENUMERATOR(DISCORD_STICKER_FORMAT_PNG, = 1)
    ENUMERATOR(DISCORD_STICKER_FORMAT_APNG, = 2)
    ENUMERATOR_LAST(DISCORD_STICKER_FORMAT_LOTTIE, = 3)
ENUM_END

/** @CCORD_pub_struct{discord_sticker} */
PUB_STRUCT(discord_sticker)
  /** ID of the sticker */
    FIELD_SNOWFLAKE(id)
  /** for standard stickers, ID of the pack the sticker is from */
  COND_WRITE(self->pack_id != 0)
    FIELD_SNOWFLAKE(pack_id)
  COND_END
  /** name of the sticker */
    FIELD_PTR(name, char, *)
  /** description of the sticker */
    FIELD_PTR(description, char, *)
  /** autocomplete/suggestion tags for the sticker (max 200 characters) */
    FIELD_PTR(tags, char, *)
  /** type of sticker */
  COND_WRITE(self->type != 0)
    FIELD_ENUM(type, discord_sticker_types)
  COND_END
  /** type of sticker format */
  COND_WRITE(self->format_type != 0)
    FIELD_ENUM(format_type, discord_sticker_format_types)
  COND_END
  /** whether this guild sticker can be used, may be false due to loss of
       Server Boosts */
    FIELD(available, bool, false)
  /** ID of the guild that owns this sticker */
  COND_WRITE(self->guild_id != 0)
    FIELD_SNOWFLAKE(guild_id)
  COND_END
  /** the user that uploaded the guild sticker */
  COND_WRITE(self->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
  /** the standard sticker's sort order within its pack */
    FIELD(sort_value, int, 0)
STRUCT_END

LIST(discord_stickers)
    LISTTYPE_STRUCT(discord_sticker)
LIST_END

STRUCT(discord_sticker_item)
  /** ID of the sticker */
    FIELD_SNOWFLAKE(id)
  /** name of the sticker */
    FIELD_PTR(name, char, *)
  /** type of sticker format */
  COND_WRITE(self->format_type != 0)
    FIELD_ENUM(format_type, discord_sticker_format_types)
  COND_END
STRUCT_END

LIST(discord_sticker_items)
    LISTTYPE_STRUCT(discord_sticker_item)
LIST_END

STRUCT(discord_sticker_pack)
  /** ID of the sticker */
    FIELD_SNOWFLAKE(id)
  /** the stickers in the pack */
  COND_WRITE(self->stickers != NULL)
    FIELD_STRUCT_PTR(stickers, discord_stickers, *)
  COND_END
  /** name of the sticker pack */
    FIELD_PTR(name, char, *)
  /** ID of the pack's SKU */
    FIELD_SNOWFLAKE(sku_id)
  /** ID of a sticker in the pack which is shown as the pack's icon */
  COND_WRITE(self->cover_sticker_id != 0)
    FIELD_SNOWFLAKE(cover_sticker_id)
  COND_END
  /** description of the sticker pack */
    FIELD_PTR(description, char, *)
  /** ID of the sticker pack's banner image */
  COND_WRITE(self->banner_asset_id != 0)
    FIELD_SNOWFLAKE(banner_asset_id)
  COND_END
STRUCT_END

/*****************************************************************************
 * Sticker REST parameters
 * **************************************************************************/

#if defined(GENCODECS_ON_STRUCT)
STRUCT(discord_create_guild_sticker)
  /** name of the sticker (2-30 characters) */
    FIELD_PTR(name, char, *)
  /** description of the sticker (empty or 2-100 characters) */
    FIELD_PTR(description, char, *)
  /** autocomplete/suggestion tags for the sticker (max 200 characters) */
    FIELD_PTR(tags, char, *)
  /** the sticker file to upload, must be a PNG, APNG, or Lottie JSON file
       max 500 KB */
    FIELD_STRUCT_PTR(file, discord_attachment, *)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_guild_sticker} */
PUB_STRUCT(discord_modify_guild_sticker)
  /** name of the sticker (2-30 characters) */
    FIELD_PTR(name, char, *)
  /** description of the sticker (empty or 2-100 characters) */
    FIELD_PTR(description, char, *)
  /** autocomplete/suggestion tags for the sticker (max 200 characters) */
    FIELD_PTR(tags, char, *)
STRUCT_END
