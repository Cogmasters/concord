PUBLIC(struct, discord_voice_state, 13, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, struct, discord_guild_member, *, member, _, _, 0ul),
        (_, _, char, *, session_id, _, _, 0ul),
        (_, _, bool, _, deaf, _, _, 0ul),
        (_, _, bool, _, mute, _, _, 0ul),
        (_, _, bool, _, self_deaf, _, _, 0ul),
        (_, _, bool, _, self_mute, _, _, 0ul),
        (_, _, bool, _, self_stream, _, _, 0ul),
        (_, _, bool, _, self_video, _, _, 0ul),
        (_, _, bool, _, suppress, _, _, 0ul),
        (_, _, u64unix_ms, _, request_to_speak_timestamp, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_voice_states, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_voice_state, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_voice_region, 5, (
        (_, _, char, *, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, bool, _, optimal, _, _, 0ul),
        (_, _, bool, _, deprecated, _, _, 0ul),
        (_, _, bool, _, custom, _, _, 0ul)
    )
)

PUBLIC(struct, discord_voice_regions, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_voice_region, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)
