/*****************************************************************************
 * OAuth2 Datatypes
 * **************************************************************************/

/** @CCORD_pub_struct{discord_auth_response} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_auth_response)
  /** the current application */
    FIELD_STRUCT_PTR(application, discord_application, *)
  /** the scopes the user authorized the application for */
    FIELD_STRUCT_PTR(scopes, strings, *)
  /** when the access token expires */
    FIELD_TIMESTAMP(expires)
  /** the user who has authorized, if the user has authorized with the 
   *    `identify` scope */
    FIELD_STRUCT_PTR(user, discord_user, *)
STRUCT_END
#endif
