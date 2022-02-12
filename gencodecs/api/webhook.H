/*****************************************************************************
 * Webhook Datatypes
 * **************************************************************************/

ENUM(discord_webhook_types)
  DESC("Incoming Webhooks can post messages to channels with a generated token" )
    ENUMERATOR(DISCORD_WEBHOOK_INCOMING, = 1)
  DESC("Channel Follower Webhooks are internal webhooks used with Channel"
       "Following to post new messages into channels")
    ENUMERATOR(DISCORD_WEBHOOK_CHANNEL_FOLLOWER, = 2)
  DESC("Application webhooks are webhooks used with Interactions")
    ENUMERATOR_LAST(DISCORD_WEBHOOK_APPLICATION, = 3)
ENUM_END

PUB_STRUCT(discord_webhook)
  DESC("the ID of the webhook")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the type of the webhook")
  COND_WRITE(this->type != 0)
    FIELD_ENUM(type, discord_webhook_types)
  COND_END
  DESC("the guild ID this webhook is for, if any")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("the channel ID this webhook is for, if any")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the user this webhook was created by (not returned when getting a"
       "webhook with its token)")
  COND_WRITE(this->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
  DESC("the default name of the webhook")
    FIELD_PTR(name, char, *)
  DESC("the secure token of the webhook (returned for Incoming Webhooks)")
    FIELD_PTR(token, char, *)
  DESC("the bot/OAuth2 application that created this webhook")
    FIELD_PRINTF(application_id, u64snowflake, PRIu64, SCNu64)
  DESC("the guild of the channel that this webhook is following (returned for"
       "Channel Follower Webhooks)")
  COND_WRITE(this->source_channel != NULL)
    FIELD_STRUCT_PTR(source_channel, discord_channel, *)
  COND_END
  DESC("the url used for executing the webhook (returned by the webhooks"
       "OAuth2 flow")
    FIELD_PTR(url, char, *)
STRUCT_END

/*****************************************************************************
 * Webhook REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_create_webhook)
  DESC("name of the webhook (1-80 characters)")
    FIELD_PTR(name, char, *)
  /* TODO: base64 conv */
#if 0
  DESC("image for the default webhook avatar")
  COND_WRITE(this->avatar != NULL)
    FIELD_PTR(avatar, char, *)
  COND_END
#endif
STRUCT_END

PUB_STRUCT(discord_modify_webhook)
  DESC("the default name of the webhook")
    FIELD_PTR(name, char, *)
  /* TODO: base64 conv */
#if 0
  DESC("image for the default webhook avatar")
  COND_WRITE(this->avatar != NULL)
    FIELD_PTR(avatar, char, *)
  COND_END
#endif
  DESC("the new channel ID for this webhook should be moved to")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
STRUCT_END

PUB_STRUCT(discord_execute_webhook)
  /* QUERY FIELDS */
  /* TODO: ignored by JSON encoding, is a query parameter */
  DESC("waits for server confirmation of message send before response, and"
       "returns the created message body (defaults to `false`; when `false` a"
       "message that is not saved does not return an error)")
    FIELD(wait, bool, false)
  /* TODO: ignored by JSON encoding, is a query parameter */
  DESC("send a message to the specified thread within a webhook's channel; the"
       "thread will automatically be unarchived")
    FIELD_PRINTF(thread_id, u64snowflake, PRIu64, SCNu64)
  /* JSON FIELDS */
  DESC("override the default avatar of the webhook")
    FIELD_PTR(avatar_url, char, *)
  DESC("true if this is a TTS message")
    FIELD(tts, bool, false)
  DESC("embedded `rich` content")
  COND_WRITE(this->embeds != NULL)
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  COND_END
  DESC("allowed mentions for the message")
  COND_WRITE(this->allowed_mentions != NULL)
    FIELD_STRUCT_PTR(allowed_mentions, discord_allowed_mention, *)
  COND_END
  DESC("the components to include with the message")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  DESC("attachment objects with filename and description")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
  DESC("message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be"
       "set)")
  COND_WRITE(this->flags != 0)
    FIELD_PRINTF(flags, uint64_t, PRIu64, SCNu64)
  COND_END
STRUCT_END

/* TODO: disable JSON encoding functions */
STRUCT(discord_get_webhook_message)
  DESC("ID of the thread the message is in")
  COND_WRITE(this->thread_id != 0)
    FIELD_PRINTF(thread_id, u64snowflake, PRIu64, SCNu64)
  COND_END
STRUCT_END

PUB_STRUCT(discord_execute_webhook)
  /* QUERY FIELDS */
  /* TODO: ignored by JSON encoding, is a query parameter */
  DESC("ID of the thread the message is in")
    FIELD_PRINTF(thread_id, u64snowflake, PRIu64, SCNu64)
  /* JSON FIELDS */
  DESC("the message contents (up to 2000 characters)")
    FIELD_PTR(content, char, *)
  DESC("embedded `rich` content")
  COND_WRITE(this->embeds != NULL)
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  COND_END
  DESC("allowed mentions for the message")
  COND_WRITE(this->allowed_mentions != NULL)
    FIELD_STRUCT_PTR(allowed_mentions, discord_allowed_mention, *)
  COND_END
  DESC("the components to include with the message")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  DESC("attachment objects with filename and description")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
STRUCT_END

/* TODO: disable JSON encoding functions */
STRUCT(discord_delete_webhook_message)
  DESC("ID of the thread the message is in")
  COND_WRITE(this->thread_id != 0)
    FIELD_PRINTF(thread_id, u64snowflake, PRIu64, SCNu64)
  COND_END
STRUCT_END
