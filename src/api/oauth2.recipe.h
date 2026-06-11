PUBLIC(struct, discord_auth_response, 4, (
        (_, struct, discord_application, *, application, _, _, 0ul),
        (_, struct, strings, *, scopes, _, _, 0ul),
        (_, _, u64unix_ms, _, expires, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, 0ul)
    )
)
