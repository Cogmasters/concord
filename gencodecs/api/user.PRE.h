/*****************************************************************************
 * User Datatypes
 * **************************************************************************/

/** @defgroup DiscordAPIUserFlags User flags
 * @brief Flags on a user account
 * @ingroup DiscordAPIUser
 *  @{ */

/** None */
PP_DEFINE(DISCORD_USER_NONE 0)
/** Discord Employee */
PP_DEFINE(DISCORD_USER_STAFF 1 << 0)
/** Partnered Server Owner */
PP_DEFINE(DISCORD_USER_PARTNER 1 << 1)
/** HypeSquad Events Coordinator */
PP_DEFINE(DISCORD_USER_HYPESQUAD 1 << 2)
/** Bug Hunter Level 1 */
PP_DEFINE(DISCORD_USER_BUG_HUNTER_LEVEL_1 1 << 3)
/** House Bravery Member */
PP_DEFINE(DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_1 1 << 6)
/** House Brilliance Member */
PP_DEFINE(DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_2 1 << 7)
/** House Balance Member */
PP_DEFINE(DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_3 1 << 8)
/** Early Nitro Supporter */
PP_DEFINE(DISCORD_USER_PREMIUM_EARLY_SUPPORTER 1 << 9)
/** User is a team */
PP_DEFINE(DISCORD_USER_TEAM_PSEUDO_USER 1 << 10)
/** Bug Hunter Level 2 */
PP_DEFINE(DISCORD_USER_BUG_HUNTER_LEVEL_2 1 << 14)
/** Verified Bot */
PP_DEFINE(DISCORD_USER_VERIFIED_BOT 1 << 16)
/** Early Verified Bot Developer */
PP_DEFINE(DISCORD_USER_VERIFIED_DEVELOPER 1 << 17)
/** Discord Certified Moderator */
PP_DEFINE(DISCORD_USER_CERTIFIED_MODERATOR 1 << 18)
/** Bot uses only HTTP interactions and is shownin the online member list */
PP_DEFINE(DISCORD_USER_BOT_HTTP_INTERACTIONS 1 << 19)

/** @} DiscordAPIUserFlags */

#if GENCODECS_RECIPE == DATA
ENUM(discord_premium_types)
    ENUMERATOR(DISCORD_PREMIUM_NONE, = 0)
    ENUMERATOR(DISCORD_PREMIUM_NITRO_CLASSIC, = 1)
    ENUMERATOR_LAST(DISCORD_PREMIUM_NITRO, = 2)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_visibility_types)
  /** invisible to everyone except the user themselves */
    ENUMERATOR(DISCORD_VISIBILITY_NONE, = 0)
  /** visible to everyone */
    ENUMERATOR_LAST(DISCORD_VISIBILITY_EVERYONE, = 1)
ENUM_END
#endif

/** @CCORD_pub_struct{discord_user} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_user)
  /** the user's ID */
    FIELD_SNOWFLAKE(id)
  /** the user's username, not unique across the platform */
    FIELD_PTR(username, char, *)
  /** the user's 4-digit discord tag */
    FIELD_PTR(discriminator, char, *)
  /** the user's avatar hash */
    FIELD_PTR(avatar, char, *)
  /** whether the user belong to an OAuth2 application */
    FIELD(bot, bool, false)
  /** whether the user is an Official Discord System user (part of the
       urgent message system) */
    FIELD_CUSTOM(System, "system", bool, DECOR_BLANK, INIT_BLANK, CLEANUP_BLANK,
                 GENCODECS_JSON_ENCODER_bool, GENCODECS_JSON_DECODER_bool,
                 false)
  /** whether the user has two factor enabled on their account */
    FIELD(mfa_enabled, bool, false)
  /** the user's banner hash */
    FIELD_PTR(banner, char, *)
  /** the user's banner color encoded as an integer representation of
       hexadecimal color code */
    FIELD(accent_color, int, 0)
  /** the user's chosen language option */
    FIELD_PTR(locale, char, *)
  /** whether the email on this account has been verified */
    FIELD(verified, bool, false)
  /** the user's email */
    FIELD_PTR(email, char, *)
  /** the @ref DiscordAPIUserFlags on a user's account */
    FIELD_BITMASK(flags)
  /** the type of Nitro subscription on a user's account */
    FIELD_ENUM(premium_type, discord_premium_types)
  /** the public @ref DiscordAPIUserFlags on a user's account */
    FIELD_BITMASK(public_flags)
STRUCT_END
#endif

/** @CCORD_pub_list{discord_users} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_users)
    LISTTYPE_STRUCT(discord_user)
LIST_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_connection)
  /** ID of the connection account */
    FIELD_SNOWFLAKE(id)
  /** the username of the connection account */
    FIELD_PTR(name, char, *)
  /** the service of the connection (twitch, youtube) */
    FIELD_PTR(type, char, *)
  /** whether the connection is revoked */
    FIELD(revoked, bool, false)
  /** an array of partial server integrations */
  COND_WRITE(self->integrations != NULL)
    FIELD_STRUCT_PTR(integrations, discord_integrations, *)
  COND_END
  /** whether the connection is verified */
    FIELD(verified, bool, false)
  /** whether friend sync is enabled for this connection */
    FIELD(friend_sync, bool, false)
  /** whether activities related to this connection will be shown in presence
       updates */
    FIELD(show_activity, bool, false)
  /** visibility of this connection */
    FIELD_ENUM(visibility, discord_visibility_types)
STRUCT_END
#endif

/** @CCORD_pub_list{discord_connections} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_connections)
    LISTTYPE_STRUCT(discord_connection)
LIST_END
#endif

/*****************************************************************************
 * User REST parameters
 * **************************************************************************/

/** @CCORD_pub_struct{discord_modify_current_user} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_current_user)
  /** user's username, if changed may cause the user's discriminator to be
       randomized */
  COND_WRITE(self->username != NULL)
    FIELD_PTR(username, char, *)
  COND_END
  /** if passed, modified the user's avatar */
  COND_WRITE(self->avatar != NULL)
    FIELD_PTR(avatar, char, *)
  COND_END
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_get_current_user_guilds)
  /** get guilds before this guild ID */
  COND_WRITE(self->before != 0)
    FIELD_SNOWFLAKE(before)
  COND_END
  /** get guilds after this guild ID */
  COND_WRITE(self->after != 0)
    FIELD_SNOWFLAKE(after)
  COND_END
  /** max number of guilds to return (1-200) */
  COND_WRITE(self->limit >= 1 && self->limit <= 200)
    FIELD(limit, int, 200)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_create_dm} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_create_dm)
  /** the recipient to open a DM channel with */
  COND_WRITE(self->recipient_id != 0)
    FIELD_SNOWFLAKE(recipient_id)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_create_group_dm} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_create_group_dm)
  /** access tokens of users that have grantes your app `gdm.join` scope */
  COND_WRITE(self->access_tokens != NULL)
    FIELD_STRUCT_PTR(access_tokens, snowflakes, *)
  COND_END
  /** a dictionary of user IDs to their respective nicknames */
  COND_WRITE(self->nicks != NULL)
    FIELD_STRUCT_PTR(nicks, strings, *)
  COND_END
STRUCT_END
#endif
