/*****************************************************************************
 * Interactions Datatypes
 * **************************************************************************/

ENUM(discord_interaction_types)
    ENUMERATOR(DISCORD_INTERACTION_PING, = 1)
    ENUMERATOR(DISCORD_INTERACTION_APPLICATION_COMMAND, = 2)
    ENUMERATOR(DISCORD_INTERACTION_MESSAGE_COMPONENT, = 3)
    ENUMERATOR(DISCORD_INTERACTION_APPLICATION_COMMAND_AUTOCOMPLETE, = 4)
    ENUMERATOR_LAST(DISCORD_INTERACTION_MODAL_SUBMIT, = 5)
ENUM_END

ENUM(discord_interaction_callback_types)
  DESC("ACK a @ref DISCORD_INTERACTION_PING")
    ENUMERATOR(DISCORD_INTERACTION_PONG, = 1)
  DESC("respond to an interaction with a message")
    ENUMERATOR(DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE, = 4)
  DESC("ACK an interaction and edit a response later, the user sees a loading"
       "state")
    ENUMERATOR(DISCORD_INTERACTION_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE, = 5)
  DESC("for components, ACK an interaction and edit the original message later"
       "the user does not see a loading state")
    ENUMERATOR(DISCORD_INTERACTION_DEFERRED_UPDATE_MESSAGE, = 6)
  DESC("for components, edit the message the component was attached to")
    ENUMERATOR(DISCORD_INTERACTION_UPDATE_MESSAGE, = 7)
  DESC("respond to an autocomplete interaction with suggested choices")
    ENUMERATOR(DISCORD_INTERACTION_APPLICATION_COMMAND_AUTOCOMPLETE_RESULT, = 8)
  DESC("respond to an interaction with a popup modal")
    ENUMERATOR_LAST(DISCORD_INTERACTION_MODAL, = 9)
ENUM_END

PUB_STRUCT(discord_interaction)
  DESC("ID of the interaction")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("ID of the application this interaction is for")
    FIELD_PRINTF(application_id, u64snowflake, PRIu64, SCNu64)
  DESC("the type of the interaction")
    FIELD_ENUM(type, discord_interaction_types)
  DESC("the command data payload")
    FIELD_STRUCT_PTR(data, discord_interaction_data, *)
  DESC("the guild it was sent from")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("the channel it was sent from")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("guild member data for the invoking user, including permissions")
    FIELD_STRUCT_PTR(member, discord_guild_member, *)
  DESC("user object for the invoking user, if invoked in a DM")
    FIELD_STRUCT_PTR(user, discord_user, *)
  DESC("read-only property, always `1`")
    FIELD(version, int, 1)
  DESC("for components, the message they were attached to")
    FIELD_STRUCT_PTR(message, discord_message, *)
  DESC("the selected language of the invoking user")
    FIELD_PTR(locale, char, *)
  DESC("the guild preferred locale, if invoked in a guild")
    FIELD_PTR(guild_locale, char, *)
STRUCT_END

STRUCT(discord_interaction_data)
  DESC("the ID of the invoked command")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the name of the invoked command")
    FIELD_PTR(name, char, *)
  DESC("the type of the invoked command")
    FIELD_ENUM(type, discord_application_command_types)
  DESC("converted users + roles + channels + attachments")
    FIELD_STRUCT_PTR(resolved, discord_resolved_data, *)
  DESC("the params + values from the user")
    FIELD_STRUCT_PTR(options, discord_application_command_interaction_data_options, *)
  DESC("the custom_id of the component")
    FIELD_PTR(custom_id, char, *)
  DESC("the type of the component")
    FIELD_ENUM(component_type, discord_component_types)
#if 0
  DESC("the values the user selected")
    FIELD_STRUCT_PTR(values, json_values, *)
#endif
  DESC("the ID of the user or messaged targetted by a user or message command")
    FIELD_PRINTF(target_id, u64snowflake, PRIu64, SCNu64)
  DESC("the values submitted by the user")
    FIELD_STRUCT_PTR(components, discord_components, *)
STRUCT_END

STRUCT(discord_resolved_data)
  DESC("the IDs and @ref discord_user datatypes")
    FIELD_STRUCT_PTR(users, snowflakes, *)
  DESC("the IDs and partial @ref discord_guild_member datatypes")
    FIELD_STRUCT_PTR(members, snowflakes, *)
  DESC("the IDs and @ref discord_role datatypes")
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  DESC("the IDs and partial @ref discord_channel datatypes")
    FIELD_STRUCT_PTR(channels, snowflakes, *)
  DESC("the IDs and partial @ref discord_message datatypes")
    FIELD_STRUCT_PTR(messages, snowflakes, *)
  DESC("the IDs and partial @ref discord_attachment datatypes")
    FIELD_STRUCT_PTR(attachments, snowflakes, *)
STRUCT_END

STRUCT(discord_message_interaction)
  DESC("ID of the interaction")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the type of interaction")
    FIELD_ENUM(type, discord_interaction_types)
  DESC("the name of the application command")
    FIELD_PTR(name, char, *)
  DESC("the user who invoked the interaction")
    FIELD_STRUCT_PTR(user, discord_user, *)
  DESC("the member who invoked the interaction in the guild")
    FIELD_STRUCT_PTR(member, discord_guild_member, *)
STRUCT_END

PUB_STRUCT(discord_interaction_response)
  DESC("interaction callback type")
    FIELD_ENUM(type, discord_interaction_callback_types)
  DESC("an optional response message")
  COND_WRITE(this->data != NULL)
    FIELD_STRUCT_PTR(data, discord_interaction_callback_data, *)
  COND_END
STRUCT_END

STRUCT(discord_interaction_callback_data)
  DESC("message components")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  /* MESSAGES */
  DESC("is the response TTS")
  COND_WRITE(this->tts != false)
    FIELD(tts, bool, false)
  COND_END
  DESC("message content")
  COND_WRITE(this->content != NULL)
    FIELD_PTR(content, char, *)
  COND_END
  DESC("supports up to 10 embeds")
  COND_WRITE(this->embeds != NULL)
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  COND_END
  DESC("message flags combined as a bitfield (only"
       "@ref DISCORD_MESSAGE_SUPRESS_EMBEDS and @ref DISCORD_MESSAGE_EPHEMERAL"
       "can be set)")
  COND_WRITE(this->flags != 0)
    FIELD_ENUM(flags, discord_message_flags)
  COND_END
  DESC("attachment objects with filename and description")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
  /* AUTOCOMPLETE */
  DESC("autocomplete choices (max of 25 choices)")
    FIELD_STRUCT_PTR(choices, discord_application_command_option_choices, *)
  /* MODAL */
  DESC("a developer defined identifier for the component, max 100 characters")
    FIELD_PTR(custom_id, char, *)
  DESC("the title of the popup modal")
    FIELD_PTR(title, char, *)
STRUCT_END

/*****************************************************************************
 * Interactions REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_edit_original_interaction_response)
  /* QUERY FIELDS */
  /* TODO: ignored by JSON encoding, is a query parameter */
  DESC("id of the thread the message is in")
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
  DESC("attached files to keep and possible descriptions for new files")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_create_followup_message)
  /* QUERY FIELDS */
  /* TODO: ignored by JSON encoding, is a query parameter */
  DESC("waits for server confirmation of message send before response, and"
       "returns the created message body (defaults to `false`; when `false` a"
       "message that is not saved does not return an error)")
    FIELD(wait, bool, true)
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

PUB_STRUCT(discord_edit_followup_message)
  /* QUERY FIELDS */
  /* TODO: ignored by JSON encoding, is a query parameter */
  DESC("id of the thread the message is in")
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
  DESC("attached files to keep and possible descriptions for new files")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
STRUCT_END
