Discord API Reference
=====================

The following section outlines the Discord API supported by Orca

Clients
-------

Client
~~~~~~

.. doxygenstruct:: discord

Datatypes
---------

Primitives
~~~~~~~~~~

.. doxygentypedef:: u64_snowflake_t
.. doxygentypedef:: u64_unix_ms_t

Callbacks
~~~~~~~~~

.. doxygentypedef:: event_mode_cb
.. doxygentypedef:: idle_cb
.. doxygentypedef:: event_raw_cb
.. doxygentypedef:: guild_role_cb
.. doxygentypedef:: guild_role_delete_cb
.. doxygentypedef:: guild_member_cb
.. doxygentypedef:: guild_member_remove_cb
.. doxygentypedef:: guild_ban_cb
.. doxygentypedef:: message_cb
.. doxygentypedef:: message_delete_cb
.. doxygentypedef:: message_delete_bulk_cb
.. doxygentypedef:: channel_cb
.. doxygentypedef:: channel_pins_update_cb
.. doxygentypedef:: message_reaction_add_cb
.. doxygentypedef:: message_reaction_remove_cb
.. doxygentypedef:: message_reaction_remove_all_cb
.. doxygentypedef:: message_reaction_remove_emoji_cb
.. doxygentypedef:: voice_state_update_cb
.. doxygentypedef:: voice_server_update_cb

Audit Log
~~~~~~~~~

.. doxygenfile:: specs-code/discord/audit_log.h
    :sections: briefdescription innerclass enum public-type public-attrib

Channel
~~~~~~~

.. doxygenfile:: specs-code/discord/channel.h
    :sections: briefdescription innerclass enum public-type public-attrib

Emoji
~~~~~

.. doxygenfile:: specs-code/discord/emoji.h
    :sections: briefdescription innerclass enum public-type public-attrib

Guild
~~~~~

.. doxygenfile:: specs-code/discord/guild.h
    :sections: briefdescription innerclass enum public-type public-attrib

Guild Template
~~~~~~~~~~~~~~

.. doxygenfile:: specs-code/discord/guild-template.h
    :sections: briefdescription innerclass enum public-type public-attrib

Invite
~~~~~~

.. doxygenfile:: specs-code/discord/invite.h
    :sections: briefdescription innerclass enum public-type public-attrib

User
~~~~

.. doxygenfile:: specs-code/discord/user.h
    :sections: briefdescription innerclass enum public-type public-attrib

Voice
~~~~~

.. doxygenfile:: specs-code/discord/voice.h
    :sections: briefdescription innerclass enum public-type public-attrib

Webhook
~~~~~~~

.. doxygenfile:: specs-code/discord/webhook.h
    :sections: briefdescription innerclass enum public-type public-attrib

Gateway
~~~~~~~

.. doxygenfile:: specs-code/discord/gateway.h
    :sections: briefdescription innerclass enum public-type public-attrib

Macros
------

Snowflake
~~~~~~~~~

.. doxygendefine:: SNOWFLAKE_INCREMENT
.. doxygendefine:: SNOWFLAKE_PROCESS_ID
.. doxygendefine:: SNOWFLAKE_INTERNAL_WORKER_ID
.. doxygendefine:: SNOWFLAKE_TIMESTAMP

Embed Limits
~~~~~~~~~~~~

.. doxygendefine:: EMBED_TITLE_LEN
.. doxygendefine:: EMBED_DESCRIPTION_LEN
.. doxygendefine:: EMBED_MAX_FIELDS
.. doxygendefine:: EMBED_FIELD_NAME_LEN
.. doxygendefine:: EMBED_FIELD_VALUE_LEN
.. doxygendefine:: EMBED_FOOTER_TEXT_LEN
.. doxygendefine:: EMBED_AUTHOR_NAME_LEN

Webhook Limits
~~~~~~~~~~~~~~

.. doxygendefine:: WEBHOOK_NAME_LEN

General Limits
~~~~~~~~~~~~~~

.. doxygendefine:: MAX_NAME_LEN
.. doxygendefine:: MAX_TOPIC_LEN
.. doxygendefine:: MAX_DESCRIPTION_LEN
.. doxygendefine:: MAX_USERNAME_LEN
.. doxygendefine:: MAX_DISCRIMINATOR_LEN
.. doxygendefine:: MAX_SHA256_LEN
.. doxygendefine:: MAX_LOCALE_LEN
.. doxygendefine:: MAX_EMAIL_LEN
.. doxygendefine:: MAX_REGION_LEN
.. doxygendefine:: MAX_REASON_LEN
.. doxygendefine:: MAX_MESSAGE_LEN
.. doxygendefine:: MAX_PAYLOAD_LEN

Functions
---------

Client Functions
~~~~~~~~~~~~~~~~

Initialization / Cleanup
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: discord_global_init
.. doxygenfunction:: discord_global_cleanup
.. doxygenfunction:: discord_init
.. doxygenfunction:: discord_config_init
.. doxygenfunction:: discord_cleanup
.. doxygenfunction:: discord_run

Set Behaviour
^^^^^^^^^^^^^

.. doxygenfunction:: discord_add_intents
.. doxygenfunction:: discord_remove_intents
.. doxygenfunction:: discord_set_prefix
.. doxygenfunction:: discord_set_event_handler

Set Event Callbacks
^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: discord_set_on_command
.. doxygenfunction:: discord_set_on_event_raw
.. doxygenfunction:: discord_set_on_idle
.. doxygenfunction:: discord_set_on_guild_role_create
.. doxygenfunction:: discord_set_on_guild_role_update
.. doxygenfunction:: discord_set_on_guild_role_delete
.. doxygenfunction:: discord_set_on_guild_member_update
.. doxygenfunction:: discord_set_on_guild_ban_add
.. doxygenfunction:: discord_set_on_guild_ban_remove
.. doxygenfunction:: discord_set_on_channel_create
.. doxygenfunction:: discord_set_on_channel_update
.. doxygenfunction:: discord_set_on_channel_delete
.. doxygenfunction:: discord_set_on_channel_pins_update
.. doxygenfunction:: discord_set_on_message_create
.. doxygenfunction:: discord_set_on_message_update
.. doxygenfunction:: discord_set_on_message_delete
.. doxygenfunction:: discord_set_on_message_delete_bulk
.. doxygenfunction:: discord_set_on_message_reaction_add
.. doxygenfunction:: discord_set_on_message_reaction_remove
.. doxygenfunction:: discord_set_on_message_reaction_remove_all
.. doxygenfunction:: discord_set_on_message_reaction_remove_emoji
.. doxygenfunction:: discord_set_on_ready
.. doxygenfunction:: discord_set_on_voice_state_update
.. doxygenfunction:: discord_set_on_voice_server_update

Miscellaneous
^^^^^^^^^^^^^

.. doxygenfunction:: discord_set_data
.. doxygenfunction:: discord_get_data
.. doxygenfunction:: discord_replace_presence
.. doxygenfunction:: discord_set_presence

Audit Log
~~~~~~~~~

.. doxygenfunction:: discord_get_guild_audit_log

Channel
~~~~~~~

.. doxygenfunction:: discord_get_channel
.. doxygenfunction:: discord_modify_channel
.. doxygenfunction:: discord_delete_channel
.. doxygenfunction:: discord_get_channel_messages
.. doxygenfunction:: discord_get_channel_message
.. doxygenfunction:: discord_create_message
.. doxygenfunction:: discord_crosspost_message
.. doxygenfunction:: discord_create_reaction
.. doxygenfunction:: discord_delete_own_reaction
.. doxygenfunction:: discord_delete_user_reaction
.. doxygenfunction:: discord_get_reactions
.. doxygenfunction:: discord_delete_all_reactions
.. doxygenfunction:: discord_delete_all_reactions_for_emoji
.. doxygenfunction:: discord_edit_message
.. doxygenfunction:: discord_delete_message
.. doxygenfunction:: discord_bulk_delete_messages
.. doxygenfunction:: discord_edit_channel_permissions
.. doxygenfunction:: discord_get_channel_invites
.. doxygenfunction:: discord_create_channel_invite
.. doxygenfunction:: discord_delete_channel_permission
.. doxygenfunction:: discord_trigger_typing_indicator
.. doxygenfunction:: discord_follow_news_channel
.. doxygenfunction:: discord_get_pinned_messages
.. doxygenfunction:: discord_pin_message
.. doxygenfunction:: discord_unpin_message
.. doxygenfunction:: discord_group_dm_add_recipient
.. doxygenfunction:: discord_group_dm_remove_recipient
.. doxygenfunction:: discord_start_thread_with_message
.. doxygenfunction:: discord_start_thread_without_message
.. doxygenfunction:: discord_join_thread
.. doxygenfunction:: discord_add_thread_member
.. doxygenfunction:: discord_leave_thread
.. doxygenfunction:: discord_remove_thread_member
.. doxygenfunction:: discord_list_thread_members
.. doxygenfunction:: discord_list_active_threads
.. doxygenfunction:: discord_list_public_archived_threads
.. doxygenfunction:: discord_list_private_archived_threads
.. doxygenfunction:: discord_list_joined_private_archived_threads

Emoji
~~~~~

.. doxygenfunction:: discord_list_guild_emojis
.. doxygenfunction:: discord_get_guild_emoji
.. doxygenfunction:: discord_create_guild_emoji
.. doxygenfunction:: discord_modify_guild_emoji
.. doxygenfunction:: discord_delete_guild_emoji

Guild
~~~~~

.. doxygenfunction:: discord_create_guild
.. doxygenfunction:: discord_get_guild
.. doxygenfunction:: discord_get_guild_preview
.. doxygenfunction:: discord_modify_guild
.. doxygenfunction:: discord_delete_guild
.. doxygenfunction:: discord_get_guild_channels
.. doxygenfunction:: discord_create_guild_channel
.. doxygenfunction:: discord_modify_guild_channel_positions
.. doxygenfunction:: discord_get_guild_member
.. doxygenfunction:: discord_list_guild_members
.. doxygenfunction:: discord_search_guild_members
.. doxygenfunction:: discord_modify_guild_member
.. doxygenfunction:: discord_add_guild_member
.. doxygenfunction:: discord_modify_current_user_nick
.. doxygenfunction:: discord_add_guild_member_role
.. doxygenfunction:: discord_remove_guild_member_role
.. doxygenfunction:: discord_remove_guild_member
.. doxygenfunction:: discord_get_guild_bans
.. doxygenfunction:: discord_get_guild_ban
.. doxygenfunction:: discord_create_guild_ban
.. doxygenfunction:: discord_remove_guild_ban
.. doxygenfunction:: discord_get_guild_roles
.. doxygenfunction:: discord_create_guild_role
.. doxygenfunction:: discord_modify_guild_role_positions
.. doxygenfunction:: discord_modify_guild_role
.. doxygenfunction:: discord_delete_guild_role

Invite
~~~~~~

.. doxygenfunction:: discord_get_invite
.. doxygenfunction:: discord_delete_invite

User
~~~~

.. doxygenfunction:: discord_get_user
.. doxygenfunction:: discord_modify_current_user
.. doxygenfunction:: discord_get_current_user
.. doxygenfunction:: discord_get_current_user_guilds
.. doxygenfunction:: discord_leave_guild
.. doxygenfunction:: discord_create_dm
.. doxygenfunction:: discord_create_group_dm
.. doxygenfunction:: discord_get_user_connections

Voice
~~~~~

.. doxygenfunction:: discord_list_voice_regions

Gateway
~~~~~~~

.. doxygenfunction:: discord_get_gateway
.. doxygenfunction:: discord_get_gateway_bot

Utility
~~~~~~~

Channel
^^^^^^^
.. doxygenfunction:: discord_overwrite_append
.. doxygenfunction:: discord_get_channel_at_pos
.. doxygenfunction:: discord_delete_messages_by_author_id

Guild
^^^^^

.. doxygenfunction:: discord_disconnect_guild_member

Embed
^^^^^

.. doxygenfunction:: discord_embed_set_thumbnail
.. doxygenfunction:: discord_embed_set_image
.. doxygenfunction:: discord_embed_set_video
.. doxygenfunction:: discord_embed_set_footer
.. doxygenfunction:: discord_embed_set_provider
.. doxygenfunction:: discord_embed_set_author
.. doxygenfunction:: discord_embed_add_field
