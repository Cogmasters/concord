/*****************************************************************************
 * User Datatypes
 * **************************************************************************/

DESC("None")
DIRECTIVE(define DISCORD_USER_NONE 0)
DESC("Discord Employee")
DIRECTIVE(define DISCORD_USER_STAFF 1 << 0)
DESC("Partnered Server Owner")
DIRECTIVE(define DISCORD_USER_PARTNER 1 << 1)
DESC("HypeSquad Events Coordinator")
DIRECTIVE(define DISCORD_USER_HYPESQUAD 1 << 2)
DESC("Bug Hunter Level 1")
DIRECTIVE(define DISCORD_USER_BUG_HUNTER_LEVEL_1 1 << 3)
DESC("House Bravery Member")
DIRECTIVE(define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_1 1 << 6)
DESC("House Brilliance Member")
DIRECTIVE(define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_2 1 << 7)
DESC("House Balance Member")
DIRECTIVE(define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_3 1 << 8)
DESC("Early Nitro Supporter")
DIRECTIVE(define DISCORD_USER_PREMIUM_EARLY_SUPPORTER 1 << 9)
DESC("User is a team")
DIRECTIVE(define DISCORD_USER_TEAM_PSEUDO_USER 1 << 10)
DESC("Bug Hunter Level 2")
DIRECTIVE(define DISCORD_USER_BUG_HUNTER_LEVEL_2 1 << 14)
DESC("Verified Bot")
DIRECTIVE(define DISCORD_USER_VERIFIED_BOT 1 << 16)
DESC("Early Verified Bot Developer")
DIRECTIVE(define DISCORD_USER_VERIFIED_DEVELOPER 1 << 17)
DESC("Discord Certified Moderator")
DIRECTIVE(define DISCORD_USER_CERTIFIED_MODERATOR 1 << 18)
DESC("Bot uses only HTTP interactions and is shownin the online member list")
DIRECTIVE(define DISCORD_USER_BOT_HTTP_INTERACTIONS 1 << 19)

ENUM(discord_premium_types)
    ENUMERATOR(DISCORD_PREMIUM_NONE, = 0)
    ENUMERATOR(DISCORD_PREMIUM_NITRO_CLASSIC, = 1)
    ENUMERATOR_LAST(DISCORD_PREMIUM_NITRO, = 2)
ENUM_END

ENUM(discord_visibility_types)
  DESC("invisible to everyone except the user themselves")
    ENUMERATOR(DISCORD_VISIBILITY_NONE, = 0)
  DESC("visible to everyone")
    ENUMERATOR_LAST(DISCORD_VISIBILITY_EVERYONE, = 1)
ENUM_END

PUB_STRUCT(discord_user)
  DESC("the user's ID")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the user's username, not unique across the platform")
    FIELD_PTR(username, char, *)
  DESC("the user's 4-digit discord tag")
    FIELD_PTR(discriminator, char, *)
  DESC("the user's avatar hash")
    FIELD_PTR(avatar, char, *)
  DESC("whether the user belong to an OAuth2 application")
    FIELD(bot, bool, false)
  DESC("whether the user is an Official Discord System user (part of the"
       "urgent message system)")
    FIELD_CUSTOM(System, system, bool, DECOR_BLANK, INIT_BLANK, CLEANUP_BLANK,
                 JSON_ENCODER_bool, JSON_DECODER_bool, false)
  DESC("whether the user has two factor enabled on their account")
    FIELD(mfa_enabled, bool, false)
  DESC("the user's banner hash")
    FIELD_PTR(banner, char, *)
  DESC("the user's banner color encoded as an integer representation of"
       "hexadecimal color code")
    FIELD(accent_color, int, 0)
  DESC("the user's chosen language option")
    FIELD_PTR(locale, char, *)
  DESC("whether the email on this account has been verified")
    FIELD(verified, bool, false)
  DESC("the user's email")
    FIELD_PTR(email, char, *)
  DESC("the flags on a user's account")
    FIELD_PRINTF(flags, uint64_t, PRIu64, SCNu64)
  DESC("the type of Nitro subscription on a user's account")
    FIELD_ENUM(premium_type, discord_premium_types)
  DESC("the public flags on a user's account")
    FIELD_PRINTF(public_flags, uint64_t, PRIu64, SCNu64)
STRUCT_END

PUB_LIST(discord_users)
    LISTTYPE_STRUCT(discord_user)
LIST_END

STRUCT(discord_connection)
  DESC("ID of the connection account")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the username of the connection account")
    FIELD_PTR(name, char, *)
  DESC("the service of the connection (twitch, youtube)")
    FIELD_PTR(type, char, *)
  DESC("whether the connection is revoked")
    FIELD(revoked, bool, false)
  DESC("an array of partial server integrations")
  COND_WRITE(this->integrations != NULL)
    FIELD_STRUCT_PTR(integrations, discord_server_integrations, *)
  COND_END
  DESC("whether the connection is verified")
    FIELD(verified, bool, false)
  DESC("whether friend sync is enabled for this connection")
    FIELD(friend_sync, bool, false)
  DESC("whether activities related to this connection will be shown in presence"
       "updates")
    FIELD(show_activity, bool, false)
  DESC("visibility of this connection")
    FIELD_ENUM(visibility, discord_visibility_types)
STRUCT_END

/*****************************************************************************
 * User REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_modify_current_user)
  DESC("user's username, if changed may cause the user's discriminator to be"
       "randomized")
  COND_WRITE(this->username != NULL)
    FIELD_PTR(username, char, *)
  COND_END
  DESC("if passed, modified the user's avatar")
  COND_WRITE(this->avatar != NULL)
    FIELD_PTR(avatar, char, *)
  COND_END
STRUCT_END

/* TODO: disable generating JSON encoding function */
STRUCT(discord_get_current_user_guilds)
  DESC("get guilds before this guild ID")
  COND_WRITE(this->before != 0)
    FIELD_PRINTF(before, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("get guilds after this guild ID")
  COND_WRITE(this->after != 0)
    FIELD_PRINTF(after, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("max number of guilds to return (1-200)")
  COND_WRITE(this->limit >= 1 && this->limit <= 200)
    FIELD(limit, int, 200)
  COND_END
STRUCT_END

PUB_STRUCT(discord_create_dm)
  DESC("the recipient to open a DM channel with")
  COND_WRITE(this->recipient_id != 0)
    FIELD_PRINTF(recipient_id, u64snowflake, PRIu64, SCNu64)
  COND_END
STRUCT_END

PUB_STRUCT(discord_create_group_dm)
  DESC("access tokens of users that have grantes your app `gdm.join` scope")
  COND_WRITE(this->access_tokens != NULL)
    FIELD_STRUCT_PTR(access_tokens, snowflakes, *)
  COND_END
  DESC("a dictionary of user IDs to their respective nicknames")
  COND_WRITE(this->nicks != NULL)
    FIELD_STRUCT_PTR(nicks, json_strings, *)
  COND_END
STRUCT_END
