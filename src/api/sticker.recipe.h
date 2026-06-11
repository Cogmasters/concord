PUBLIC(enum, discord_sticker_types, 2, (
        (DISCORD_STICKER_STANDARD, =, 1),
        (DISCORD_STICKER_GUILD, =, 2)
    )
)

PUBLIC(enum, discord_sticker_format_types, 3, (
        (DISCORD_STICKER_FORMAT_PNG, =, 1),
        (DISCORD_STICKER_FORMAT_APNG, =, 2),
        (DISCORD_STICKER_FORMAT_LOTTIE, =, 3)
    )
)

PUBLIC(struct, discord_sticker, 11, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, pack_id, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, char, *, tags, _, _, 0ul),
        (_, enum, discord_sticker_types, _, type, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_sticker_format_types, _, format_type, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, available, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_user, *, user, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, sort_value, _, _, 0ul)
    )
)

PUBLIC(struct, discord_stickers, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_sticker, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_sticker_item, 3, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, enum, discord_sticker_format_types, _, format_type, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_sticker_items, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_sticker_item, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_sticker_pack, 7, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, struct, discord_stickers, *, stickers, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, u64snowflake, _, sku_id, _, _, 0ul),
        (_, _, u64snowflake, _, cover_sticker_id, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, u64snowflake, _, banner_asset_id, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_sticker_packs, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_sticker_pack, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_list_nitro_sticker_packs, 1, (
        (_, struct, discord_sticker_packs, *, sticker_packs, _, _, 0ul)
    )
)

PRIVATE(struct, discord_create_guild_sticker, 5, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, char, *, tags, _, _, 0ul),
        (_, struct, discord_attachment, *, file, _, _, 0ul)
    )
)

PUBLIC(struct, discord_modify_guild_sticker, 4, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, char, *, tags, _, _, 0ul)
    )
)

PRIVATE(struct, discord_delete_guild_sticker, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)
