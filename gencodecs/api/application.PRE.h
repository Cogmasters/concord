/*****************************************************************************
 * Application Datatypes
 * **************************************************************************/

/** @defgroup DiscordApplicationFlags Application flags
 * @ingroup DiscordConstants
 *  @{ */

#if GENCODECS_RECIPE == DATA
ENUM(discord_application_integration_type)
  /** app is installable to servers */
    ENUMERATOR(DISCORD_APPLICATIONS_GUILD_INSTALL, = 0)
  /** app is installable to users */
    ENUMERATOR_LAST(DISCORD_APPLICATIONS_USER_INSTALL, = 1)
ENUM_END
#endif

/** @CCORD_pub_list{discord_application_integration_types} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_application_integration_types)
    LISTTYPE_ENUM(discord_application_integration_type)
LIST_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_application_event_webhook_status)
  /** webhook events are disabled by developer */
    ENUMERATOR(DISCORD_APPLICATIONS_WEBHOOK_DISABLED, = 1)
  /** webhook events are enabled by developer */
    ENUMERATOR(DISCORD_APPLICATIONS_WEBHOOK_ENABLED, = 2)
  /** webhook events are disabled by Discord, usually due to inactivity */
    ENUMERATOR_LAST(DISCORD_APPLICATIONS_WEBHOOK_DISABLED_BY_DISCORD, = 3)
ENUM_END
#endif

/** indicates if an app uses the Auto Moderation API */
PP_DEFINE(DISCORD_APPLICATION_APPLICATION_AUTO_MODERATION_RULE_CREATE_BADGE 1 << 6)
/**	intent required for bots in 100 or more servers to
      receive presence_update events */
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_PRESENCE 1 << 12)
/** intent required for bots in under 100 servers to receive
      presence_update events */
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED 1 << 13)
/** intent required for bots in 100 or more servers to receive
      member-related events like guild_member_add */
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS 1 << 14)
/** intent required for bots in under 100 servers to receive
      member-related events like guild_member_add */
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED 1 << 15)
/** indicates unusual growth of an app that prevents verification */
PP_DEFINE(DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT 1 << 16)
/** indicates if an app is embedded within the Discord client */
PP_DEFINE(DISCORD_APPLICATION_EMBEDDED 1 << 17)
/** intent required for bots in 100 or more servers to receive message content */
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT 1 << 18)
/** intent required for bots in under 100 servers to receive message content */
PP_DEFINE(DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT_LIMITED 1 << 19)
/** indicates if an app has registered global application commands */
PP_DEFINE(DISCORD_APPLICATION_APPLICATION_COMMAND_BADGE 1 << 23)

/** @} DiscordApplicationFlags */

/** @CCORD_pub_struct{discord_application_install_params} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_application_install_params)
  /** the scopes to add the application to the server with */
    FIELD_STRUCT_PTR(scopes, strings, *)
  /** the permissions to request for the bot role */
    FIELD_BITMASK(permissions)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_application} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_application)
  /** the ID of the app */
    FIELD_SNOWFLAKE(id)
  /** the name of the app */
    FIELD_PTR(name, char, *)
  /** the icon hash of the app */
    FIELD_PTR(icon, char, *)
  /** the description of the app */
    FIELD_PTR(description, char, *)
  /** an array of rpc origin urls, if rpc is enabled */
  COND_WRITE(self->rpc_origins != NULL)
    FIELD_STRUCT_PTR(rpc_origins, strings, *)
  COND_END
  /** when false only app owner can join the app's bot to guilds */
    FIELD(bot_public, bool, false)
  /** when true the app's bot will only join upon completion of the full
       oauth2 code grant flow */
    FIELD(bot_require_code_grant, bool, false)
  /** partial user object for the bot user associated with the app */
  COND_WRITE(self->bot != NULL)
    FIELD_STRUCT_PTR(bot, discord_user, *)
  COND_END
  /** the url of the app's terms of service */
    FIELD_PTR(terms_of_service_url, char, *)
  /** the url of the app's privacy policy */
    FIELD_PTR(privacy_policy_url, char, *)
  /** partial user object containing info on the owner of the application */
  COND_WRITE(self->owner != NULL)
    FIELD_STRUCT_PTR(owner, discord_user, *)
  COND_END
  /** the hex encoded key for verification in interactions and the GameSDK's
       GetTicket */
    FIELD_PTR(verify_key, char, *)
  /** if the application belongs to a team, this will be a list of the
       members of that team */
  COND_WRITE(self->team != NULL)
    FIELD_STRUCT_PTR(team, discord_team, *)
  COND_END
  /** if this application is a game sold on Discord, this field will be the
       guild to which it has been linked */
    FIELD_SNOWFLAKE(guild_id)
  /** Partial object of the associated guild */
  COND_WRITE(self->guild != NULL)
    FIELD_STRUCT_PTR(guild, discord_guild, *)
  COND_END
  /** if this application is a game sold on Discord, this field will be the
       ID of the \"Game SKU\" that is created, if exists */
    FIELD_SNOWFLAKE(primary_sku_id)
  /** if this application is a game sold on Discord, this field will be the
       URL slug that links to the store page */
    FIELD_PTR(slug, char, *)
  /** the application's default rich presence invite cover image hash */
    FIELD_PTR(cover_image, char, *)
  /** the application's public flags @see DiscordApplicationFlags */
    FIELD_BITMASK(flags)
  /** the approximate count of guilds the app has been added to */
    FIELD(applicatimate_guild_count, size_t, 0)
  /** the approximate count of users that have installed the app */
    FIELD(approximate_user_install_count, size_t, 0)
  /** array of redirect URIs for the app */
  COND_WRITE(self->redirect_uris != NULL)
    FIELD_STRUCT_PTR(redirect_uris, strings, *)
  COND_END
  /** the interactions endpoint URL for the app */
    FIELD_PTR(interactions_endpoint_url, char, *)
  /** the role connection verification URL for the app */
    FIELD_PTR(role_connections_verification_url, char, *)
  /** the event webhooks URL for the app to receive webhook events */
    FIELD_PTR(event_webhooks_url, char, *)
  /** if webhook events are enabled for the app. */
    FIELD_ENUM(event_webhooks_status, discord_application_event_webhook_status)
  /** the list of Webhook event types the app subscribes to */
  COND_WRITE(self->event_webhooks_types != NULL)
    FIELD_STRUCT_PTR(event_webhooks_types, strings, *)
  COND_END
  /** the list of tags describing the content and functionality of the
       app. Max of 5 tags. */
  COND_WRITE(self->tags != NULL)
    FIELD_STRUCT_PTR(tags, strings, *)
  COND_END
  /** the settings for the app's default in-app authorization link, if enabled */
  COND_WRITE(self->install_params != NULL)
    FIELD_STRUCT_PTR(install_params, discord_application_install_params, *)
  COND_END
  /* TODO: integration_types_config */
  /** default custom authorization URL for the app, if enabled */
    FIELD_PTR(custom_install_url, char, *)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_install_params} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_install_params)
  /** the scopes to add the application to the server with */
    FIELD_STRUCT_PTR(scopes, strings, *)
  /** the permissions to request for the bot role */
    FIELD_BITMASK(permissions)
STRUCT_END
#endif
