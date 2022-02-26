/*****************************************************************************
 * Application Datatypes
 * **************************************************************************/

PP_DEFINE(DISCORD_APPLICATION_GATEWAY_PRESENCE 1 << 12)
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED 1 << 13)
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS 1 << 14)
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED 1 << 15)
PP_DEFINE(DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT 1 << 16)
PP_DEFINE(DISCORD_APPLICATION_EMBEDDED 1 << 17)
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT 1 << 18)
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT_LIMITED 1 << 19)

/** @CCORD_pub_struct{discord_application} */
PUB_STRUCT(discord_application)
  PP("the ID of the app")
    FIELD_SNOWFLAKE(id)
  PP("the name of the app")
    FIELD_PTR(name, char, *)
  PP("the icon hash of the app")
    FIELD_PTR(icon, char, *)
  PP("the description of the app")
    FIELD_PTR(description, char, *)
  PP("an array of rpc origin urls, if rpc is enabled")
  COND_WRITE(this->rpc_origins != NULL)
    FIELD_STRUCT_PTR(rpc_origins, strings, *)
  COND_END
  PP("when false only app owner can join the app's bot to guilds")
    FIELD(bot_public, bool, false)
  PP("when true the app's bot will only join upon completion of the full"
       "oauth2 code grant flow")
    FIELD(bot_require_code_grant, bool, false)
  PP("the url of the app's terms of service")
    FIELD_PTR(terms_of_service_url, char, *)
  PP("the url of the app's privacy policy")
    FIELD_PTR(privacy_policy_url, char, *)
  PP("partial user object containing info on the owner of the application")
  COND_WRITE(this->owner != NULL)
    FIELD_STRUCT_PTR(owner, discord_user, *)
  COND_END
  PP("if this application is a game sold on Discord, this field will be the"
       "summary field for the store page of its primary sku")
    FIELD_PTR(summary, char, *)
  PP("the hex encoded key for verification in interactions and the GameSDK's"
       "GetTicket")
    FIELD_PTR(verify_key, char, *)
  PP("if the application belongs to a team, this will be a list of the"
       "members of that team")
  COND_WRITE(this->team != NULL)
    FIELD_STRUCT_PTR(team, discord_team, *)
  COND_END
  PP("if this application is a game sold on Discord, this field will be the"
       "guild to which it has been linked")
    FIELD_SNOWFLAKE(guild_id)
  PP("if this application is a game sold on Discord, this field will be the"
       "ID of the \"Game SKU\" that is created, if exists")
    FIELD_SNOWFLAKE(primary_sku_id)
  PP("if this application is a game sold on Discord, this field will be the"
       "URL slug that links to the store page")
    FIELD_PTR(slug, char, *)
  PP("the application's default rich presence invite cover image hash")
    FIELD_PTR(cover_image, char, *)
  PP("the application's public flags")
    FIELD_SNOWFLAKE(flags)
STRUCT_END
