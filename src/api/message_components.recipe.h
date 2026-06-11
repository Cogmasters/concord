PUBLIC(enum, discord_component_types, 16, (
        (DISCORD_COMPONENT_ACTION_ROW, =, 1),
        (DISCORD_COMPONENT_BUTTON, =, 2),
        (DISCORD_COMPONENT_SELECT_MENU, =, 3),
        (DISCORD_COMPONENT_TEXT_INPUT, =, 4),
        (DISCORD_COMPONENT_USER_SELECT, =, 5),
        (DISCORD_COMPONENT_ROLE_SELECT, =, 6),
        (DISCORD_COMPONENT_MENTION_SELECT, =, 7),
        (DISCORD_COMPONENT_CHANNEL_SELECT, =, 8),
        (DISCORD_COMPONENT_SECTION, =, 9),
        (DISCORD_COMPONENT_TEXT_DISPLAY, =, 10),
        (DISCORD_COMPONENT_THUMBNAIL, =, 11),
        (DISCORD_COMPONENT_MEDIA_GALLERY, =, 12),
        (DISCORD_COMPONENT_FILE, =, 13),
        (DISCORD_COMPONENT_SEPARATOR, =, 14),
        (DISCORD_COMPONENT_CONTENT_INVENTORY_ENTRY, =, 16),
        (DISCORD_COMPONENT_CONTAINER, =, 17)
    )
)

PUBLIC(enum, discord_component_styles, 7, (
        (DISCORD_BUTTON_PRIMARY, =, 1),
        (DISCORD_BUTTON_SECONDARY, =, 2),
        (DISCORD_BUTTON_SUCCESS, =, 3),
        (DISCORD_BUTTON_DANGER, =, 4),
        (DISCORD_BUTTON_LINK, =, 5),
        (DISCORD_TEXT_SHORT, =, 1),
        (DISCORD_TEXT_PARAGRAPH, =, 2)
    )
)

PUBLIC(enum, discord_component_spacing, 2, (
        (DISCORD_COMPONENT_SPACING_SMALL, =, 1),
        (DISCORD_COMPONENT_SPACING_LARGE, =, 2)
    )
)

PUBLIC(struct, discord_component, 17, (
        (_, _, u64snowflake, _, id, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_component_types, _, type, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, custom_id, _, _, 0ul),
        (_, _, u64snowflake, _, sku_id, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_component_styles, _, style, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, label, _, _, 0ul),
        (_, struct, discord_emoji, *, emoji, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, url, _, _, 0ul),
        (_, struct, discord_select_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, placeholder, _, _, 0ul),
        (_, _, int, _, min_values, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, max_values, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_components, *, components, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, min_length, _, _, 0ul),
        (_, _, int, _, max_length, _, _, 0ul),
        (_, _, bool, _, required, _, _, 0ul),
        (_, _, char, *, value, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_components, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_component, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_select_option, 5, (
        (_, _, char, *, label, _, _, 0ul),
        (_, _, char, *, value, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, discord_emoji, *, emoji, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, Default, default, _, 0ul)
    )
)

PUBLIC(struct, discord_select_options, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_select_option, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_component_media, 1, (
        (_, _, char, *, url, _, _, 0ul)
    )
)

PRIVATE(struct, discord_component_item, 3, (
        (_, struct, discord_component_media, *, media, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, description, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, spoiler, _, _, 0ul)
    )
)

PUBLIC(struct, discord_component_items, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_component_item, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)
