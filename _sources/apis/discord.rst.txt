..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

Discord API Reference
=====================

The following section outlines the Discord API supported by Orca

Clients
-------

Client
~~~~~~

.. doxygenstruct:: discord
.. doxygenenum:: discord_event_handling_mode

Datatypes
---------

Primitives
~~~~~~~~~~

.. doxygentypedef:: u64_snowflake_t
.. doxygentypedef:: u64_unix_ms_t

Callbacks
~~~~~~~~~

.. doxygengroup:: DiscordCallbacksGeneral
.. doxygengroup:: DiscordCallbacksGuild
.. doxygengroup:: DiscordCallbacksMessage
.. doxygengroup:: DiscordCallbacksChannel
.. doxygengroup:: DiscordCallbacksVoice

Audit Log
~~~~~~~~~

.. doxygenfile:: specs-code/discord/audit_log.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Channel
~~~~~~~

.. doxygenfile:: specs-code/discord/channel.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Emoji
~~~~~

.. doxygenfile:: specs-code/discord/emoji.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Guild
~~~~~

.. doxygenfile:: specs-code/discord/guild.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Guild Template
~~~~~~~~~~~~~~

.. doxygenfile:: specs-code/discord/guild-template.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Invite
~~~~~~

.. doxygenfile:: specs-code/discord/invite.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Message Components
~~~~~~~~~~~~~~~~~~

.. doxygenfile:: specs-code/discord/message_components.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Permissions
~~~~~~~~~~~

.. doxygenfile:: specs-code/discord/permissions.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Slash Commands
~~~~~~~~~~~~~~

.. doxygenfile:: specs-code/discord/slash_commands.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

User
~~~~

.. doxygenfile:: specs-code/discord/user.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Voice
~~~~~

.. doxygenfile:: specs-code/discord/voice.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Webhook
~~~~~~~

.. doxygenfile:: specs-code/discord/webhook.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Gateway
~~~~~~~

.. doxygenfile:: specs-code/discord/gateway.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Macros
------

.. doxygengroup:: DiscordLimitsSnowflake
.. doxygengroup:: DiscordLimitsGeneral
.. doxygengroup:: DiscordLimitsEmbed
.. doxygengroup:: DiscordLimitsWebhook

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

Misc
^^^^

.. doxygenfunction:: discord_set_data
.. doxygenfunction:: discord_get_data
.. doxygenfunction:: discord_replace_presence
.. doxygenfunction:: discord_set_presence

Audit Log
~~~~~~~~~

.. doxygengroup:: DiscordEndpointsAuditLog
    :content-only:

Channel
~~~~~~~

.. doxygengroup:: DiscordEndpointsChannel
    :content-only:

Emoji
~~~~~

.. doxygengroup:: DiscordEndpointsEmoji
    :content-only:

Guild
~~~~~

.. doxygengroup:: DiscordEndpointsGuild
    :content-only:

Invite
~~~~~~

.. doxygengroup:: DiscordEndpointsInvite
    :content-only:

User
~~~~

.. doxygengroup:: DiscordEndpointsUser
    :content-only:

Voice
~~~~~

.. doxygengroup:: DiscordEndpointsVoice
    :content-only:

Gateway
~~~~~~~

.. doxygengroup:: DiscordEndpointsGateway
    :content-only:

Misc
~~~~

Channel
^^^^^^^

.. doxygengroup:: DiscordMiscChannel
    :content-only:

Guild
^^^^^

.. doxygengroup:: DiscordMiscGuild
    :content-only:

Embed
^^^^^

.. doxygengroup:: DiscordMiscEmbed
    :content-only:
