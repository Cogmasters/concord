/*****************************************************************************
 * Application Datatypes
 * **************************************************************************/

DIRECTIVE(define DISCORD_APPLICATION_GATEWAY_PRESENCE 1 << 12)
DIRECTIVE(define DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED 1 << 13)
DIRECTIVE(define DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS 1 << 14)
DIRECTIVE(define DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED 1 << 15)
DIRECTIVE(define DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT 1 << 16)
DIRECTIVE(define DISCORD_APPLICATION_EMBEDDED 1 << 17)
DIRECTIVE(define DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT 1 << 18)
DIRECTIVE(define DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT_LIMITED 1 << 19)

PUB_STRUCT(discord_application)
  DESC("the ID of the app")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the name of the app")
    FIELD_PTR(name, char, *)
  DESC("the icon hash of the app")
    FIELD_PTR(icon, char, *)
  DESC("the description of the app")
    FIELD_PTR(description, char, *)
  DESC("an array of rpc origin urls, if rpc is enabled")
  COND_WRITE(this->rpc_origins != NULL)
    FIELD_STRUCT_PTR(rpc_origins, json_strings, *)
  COND_END
  DESC("when false only app owner can join the app's bot to guilds")
    FIELD(bot_public, bool, false)
  DESC("when true the app's bot will only join upon completion of the full"
       "oauth2 code grant flow")
    FIELD(bot_require_code_grant, bool, false)
  DESC("the url of the app's terms of service")
    FIELD_PTR(terms_of_service_url, char, *)
  DESC("the url of the app's privacy policy")
    FIELD_PTR(privacy_policy_url, char, *)
  DESC("partial user object containing info on the owner of the application")
  COND_WRITE(this->owner != NULL)
    FIELD_STRUCT_PTR(owner, discord_user, *)
  COND_END
  DESC("if this application is a game sold on Discord, this field will be the"
       "summary field for the store page of its primary sku")
    FIELD_PTR(summary, char, *)
  DESC("the hex encoded key for verification in interactions and the GameSDK's"
       "GetTicket")
    FIELD_PTR(verify_key, char, *)
  DESC("if the application belongs to a team, this will be a list of the"
       "members of that team")
  COND_WRITE(this->team != NULL)
    FIELD_STRUCT_PTR(team, discord_team, *)
  COND_END
  DESC("if this application is a game sold on Discord, this field will be the"
       "guild to which it has been linked")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("if this application is a game sold on Discord, this field will be the"
       "ID of the \"Game SKU\" that is created, if exists")
    FIELD_PRINTF(primary_sku_id, u64snowflake, PRIu64, SCNu64)
  DESC("if this application is a game sold on Discord, this field will be the"
       "URL slug that links to the store page")
    FIELD_PTR(slug, char, *)
  DESC("the application's default rich presence invite cover image hash")
    FIELD_PTR(cover_image, char, *)
  DESC("the application's public flags")
    FIELD_PRINTF(flags, uint64_t, PRIu64, SCNu64)
STRUCT_END
