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

Callbacks
~~~~~~~~~

General
^^^^^^^

.. doxygengroup:: DiscordCallbacksGeneral

Guild
^^^^^

.. doxygengroup:: DiscordCallbacksGuild

Message
^^^^^^^

.. doxygengroup:: DiscordCallbacksMessage

Channel
^^^^^^^

.. doxygengroup:: DiscordCallbacksChannel

Voice
^^^^^

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

General
~~~~~~~

.. doxygengroup:: DiscordLimitsGeneral

Snowflake
~~~~~~~~~

.. doxygengroup:: DiscordLimitsSnowflake

Embed
~~~~~

.. doxygengroup:: DiscordLimitsEmbed

Webhook
~~~~~~~

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
.. doxygenfunction:: discord_set_on_thread_create
.. doxygenfunction:: discord_set_on_thread_update
.. doxygenfunction:: discord_set_on_thread_delete
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

Get Guild Audit Log
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildAuditLog

Channel
~~~~~~~

Get Channel
^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannel

Modify Channel
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyChannel

Delete Channel
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteChannel

Get Channel Messages
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannelMessages

Get Channel Message
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannelMessage

Create Message
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateMessage

Crosspost Message
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCrosspostMessage

Delete Create Reaction
^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateReaction

Delete Own Reaction
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteOwnReaction

Delete User Reaction
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteUserReaction

Get Reactions
^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetReactions

Delete All Reactions
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteAllReactions

Delete All Reactions For Emoji
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteAllReactionsForEmoji

Edit Message
^^^^^^^^^^^^

.. doxygengroup:: DiscordEditMessage

Delete Message
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteMessage

Bulk Delete Messages
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordBulkDeleteMessages

Edit Channel Permissions
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditChannelPermissions

Get Channel Invites
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannelInvites

Create Channel Invite
^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateChannelInvite

Delete Channel Permission
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteChannelPermission

Trigger Typing Indicator
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordTriggerTypingIndicator

Follow News Channel
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordFollowNewsChannel

Get Pinned Messages
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetPinnedMessages

Pin Message
^^^^^^^^^^^

.. doxygengroup:: DiscordPinMessage

Unpin Message
^^^^^^^^^^^^^

.. doxygengroup:: DiscordUnpinMessage

Group DM Add Recipient
^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGroupDmAddRecipient

Group DM Remove Recipient
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGroupDmRemoveRecipient

Start Thread With Message
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordStartThreadWithMessage

Start Thread Without Message
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordStartThreadWithoutMessage

Join Thread
^^^^^^^^^^^

.. doxygengroup:: DiscordJoinThread

Add Thread Member
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordAddThreadMember

Leave Thread
^^^^^^^^^^^^

.. doxygengroup:: DiscordLeaveThread

Remove Thread Member
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordRemoveThreadMember

List Thread Members
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListThreadMembers

List Active Threads
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListActiveThreads

List Public Archived Threads
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListPublicArchivedThreads

List Private Archived Threads
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListPrivateArchivedThreads

List Joined Private Archived Threads
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListJoinedPrivateArchivedThreads

Emoji
~~~~~

List Guild Emojis
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListGuildEmojis

Get Guild Emoji
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildEmoji

Create Guild Emoji
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildEmoji

Modify Guild Emoji
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildEmoji

Delete Guild Emoji
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteGuildEmoji

Guild
~~~~~

Create Guild
^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuild

Get Guild
^^^^^^^^^

.. doxygengroup:: DiscordGetGuild

Get Guild Preview
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildPreview

Modify Guild
^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuild

Delete Guild
^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteGuild

Get Guild Channels
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildChannels

Create Guild Channel
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildChannel

Modify Guild Channel Positions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildChannelPositions

Get Guild Member
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildMember

Search Guild Members
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordSearchGuildMembers

Modify Guild Member
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildMember

Add Guild Member
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordAddGuildMember

Modify Current User Nick
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyCurrentUserNick

Add Guild Member Role
^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordAddGuildMemberRole

Remove Guild Member Role
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordRemoveGuildMemberRole

Remove Guild Member
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordRemoveGuildMember

Get Guild Bans
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildBans

Get Guild Ban
^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildBan

Create Guild Ban
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildBan

Remove Guild Ban
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordRemoveGuildBan

Get Guild Roles
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildRoles

Create Guild Role
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildRole

Modify Guild Role Positions
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildRolePositions

Modify Guild Role
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildRole

Delete Guild Role
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteGuildRole

Invite
~~~~~~

Get Invite
^^^^^^^^^^

.. doxygengroup:: DiscordGetInvite

Delete Invite
^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteInvite

User
~~~~

Get User
^^^^^^^^

.. doxygengroup:: DiscordGetUser

Modify Current User
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyCurrentUser

Get Current User
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetCurrentUser

Get Current User Guilds
^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetCurrentUserGuilds

Leave Guild
^^^^^^^^^^^

.. doxygengroup:: DiscordLeaveGuild

Create DM
^^^^^^^^^

.. doxygengroup:: DiscordCreateDm

Create Group DM
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGroupDm

Get User Connections
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetUserConnections

Voice
~~~~~

List Voice Regions
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListVoiceRegions

Gateway
~~~~~~~

Get Gateway
^^^^^^^^^^^

.. doxygengroup:: DiscordGetGateway

Get Gateway Bot
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGatewayBot

Misc
~~~~

Channel
^^^^^^^

.. doxygengroup:: DiscordMiscChannel

Guild
^^^^^

.. doxygengroup:: DiscordMiscGuild

Embed
^^^^^

.. doxygengroup:: DiscordMiscEmbed
