/*****************************************************************************
 * Entitlement Datatypes
 * **************************************************************************/

/** Discord polls
 * @see https://discord.com/developers/docs/monetization/entitlements */

#if GENCODECS_RECIPE == DATA
ENUM(discord_entitlement_types)
  /** entitlement was purchased by user */
    ENUMERATOR(DISCORD_ENTITLEMENT_PURCHASE, = 1)
  /** entitlement for Discord Nitro subscription */
    ENUMERATOR(DISCORD_ENTITLEMENT_PREMIUM_SUBSCRIPTION, = 2)
  /** entitlement was gifted by developer */
    ENUMERATOR(DISCORD_ENTITLEMENT_DEVELOPER_GIFT, = 3)
  /** entitlement was purchased by a dev in application test mode */
    ENUMERATOR(DISCORD_ENTITLEMENT_TEST_MODE_PURCHASE, = 4)
  /** entitlement was granted when the SKU was free */
    ENUMERATOR(DISCORD_ENTITLEMENT_FREE_PURCHASE, = 5)
  /** entitlement was gifted by another user */
    ENUMERATOR(DISCORD_ENTITLEMENT_USER_GIFT, = 6)
  /** entitlement was claimed by user for free as a Nitro Subscriber */
    ENUMERATOR(DISCORD_ENTITLEMENT_PREMIUM_PURCHASE, = 7)
  /** entitlement was purchased as an app subscription */
    ENUMERATOR_LAST(DISCORD_ENTITLEMENT_APPLICATION_SUBSCRIPTION, = 8)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_entitlement_tenant_fulfillment_status_response)
    ENUMERATOR(DISCORD_ENTITLEMENT_FULFILLMENT_UNKNOWN, = 0)
    ENUMERATOR(DISCORD_ENTITLEMENT_FULFILLMENT_NOT_NEEDED, = 1)
    ENUMERATOR(DISCORD_ENTITLEMENT_FULFILLMENT_NEEDED, = 2)
    ENUMERATOR(DISCORD_ENTITLEMENT_FULFILLED, = 3)
    ENUMERATOR(DISCORD_ENTITLEMENT_FULFILLMENT_FAILED, = 4)
    ENUMERATOR(DISCORD_ENTITLEMENT_UNFULFILLMENT_NEEDED, = 5)
    ENUMERATOR_LAST(DISCORD_ENTITLEMENT_UNFULFILLED, = 6)
ENUM_END
#endif

/** @CCORD_pub_struct{discord_entitlement} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_entitlement)
  /** ID of the entitlement */
  FIELD_SNOWFLAKE(id)
  /** ID of the SKU */
  FIELD_SNOWFLAKE(sku_id)
  /** ID of the parent application */
  FIELD_SNOWFLAKE(application_id)
  /** ID of the user that is granted access
       to the entitlement's sku */
  COND_WRITE(self->user_id != 0)
    FIELD_SNOWFLAKE(user_id)
  COND_END
  /** the type of entitlement */
  FIELD_ENUM(type, discord_entitlement_types)
  /** if the entitlement was deleted */
  FIELD(deleted, bool, false)
  /** start date at which the entitlement is valid (old name: start_date) */
  COND_WRITE(self->start_date != 0)
    FIELD_TIMESTAMP(start_date)
  COND_END
  /** new standardized field: starts_at */
  COND_WRITE(self->starts_at != 0)
    FIELD_TIMESTAMP(starts_at)
  COND_END
  /** date at which the entitlement is no longer valid (old name: end_date) */
  COND_WRITE(self->end_date != 0)
    FIELD_TIMESTAMP(end_date)
  COND_END
  /** new standardized field: ends_at */
  COND_WRITE(self->ends_at != 0)
    FIELD_TIMESTAMP(ends_at)
  COND_END
  /** when the entitlement was fulfilled */
  COND_WRITE(self->fulfilled_at != 0)
    FIELD_TIMESTAMP(fulfilled_at)
  COND_END
  /** tenant level fulfillment status */
    FIELD_ENUM(fulfillment_status, discord_entitlement_tenant_fulfillment_status_response)
  /** ID of the user who gifted this entitlement */
  COND_WRITE(self->gifter_user_id != 0)
    FIELD_SNOWFLAKE(gifter_user_id)
  COND_END
  /** ID of the parent entitlement (if any) */
  COND_WRITE(self->parent_id != 0)
    FIELD_SNOWFLAKE(parent_id)
  COND_END
  /** ID of the guild that is granted access to the entitlement's sku */
  COND_WRITE(self->guild_id != 0)
    FIELD_SNOWFLAKE(guild_id)
  COND_END
  /** for consumable items, whether or not the entitlement has been consumed */
  FIELD(consumed, bool, false)
STRUCT_END
#endif


/** @CCORD_pub_list{discord_entitlements} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_entitlements)
  LISTTYPE_STRUCT(discord_entitlement)
LIST_END

#endif
