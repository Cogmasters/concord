..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

======
Models
======

Application
-----------

.. doxygenfile:: specs-code/discord/application.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Audit Log
---------

.. doxygenfile:: specs-code/discord/audit_log.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

Get Guild Audit Log
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildAuditLog
   :content-only:

Channel
-------

.. doxygenfile:: specs-code/discord/channel.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Utils
~~~~~

.. doxygengroup:: DiscordMiscChannel
   :content-only:

Embed
~~~~~

.. doxygengroup:: DiscordMiscEmbed
   :content-only:

Methods
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
-----

.. doxygenfile:: specs-code/discord/emoji.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

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
-----

.. doxygenfile:: specs-code/discord/guild.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Utils
~~~~~

.. doxygengroup:: DiscordMiscGuild
   :content-only:

Methods
~~~~~~~

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

List Guild Members
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListGuildMembers

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


Guild Template
--------------

.. doxygenfile:: specs-code/discord/guild-template.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Invite
------

.. doxygenfile:: specs-code/discord/invite.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

Get Invite
^^^^^^^^^^

.. doxygengroup:: DiscordGetInvite

Delete Invite
^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteInvite

Stage Instance
--------------

.. doxygenfile:: specs-code/discord/stage-instance.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Sticker
-------

.. doxygenfile:: specs-code/discord/sticker.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

User
----

.. doxygenfile:: specs-code/discord/user.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

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
-----

.. doxygenfile:: specs-code/discord/voice.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

List Voice Regions
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListVoiceRegions

Webhook
-------

.. doxygenfile:: specs-code/discord/webhook.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

Create Webhook
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateWebhook

Get Channel Webhooks
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannelWebhooks

Get Guild Webhooks
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildWebhooks

Get Webhook
^^^^^^^^^^^

.. doxygengroup:: DiscordGetWebhook

Get Webhook with Token
^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetWebhookWithToken

Modify Webhook
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyWebhook

Modify Webhook with Token
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyWebhookWithToken

Delete Webhook
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteWebhook

Delete Webhook with Token
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteWebhookWithToken

Execute Webhook
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordExecuteWebhook

Get Webhook Message
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetWebhookMessage

Edit Webhook Message
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditWebhookMessage

Delete Webhook Message
^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteWebhookMessage

Gateway
-------

.. doxygenfile:: specs-code/discord/gateway.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Utils
~~~~~

.. doxygengroup:: DiscordMiscGateway
   :content-only:

Methods
~~~~~~~

Get Gateway
^^^^^^^^^^^

.. doxygengroup:: DiscordGetGateway

Get Gateway Bot
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGatewayBot

Permissions
-----------

.. doxygenfile:: specs-code/discord/permissions.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Custom
------

.. doxygenfile:: specs-code/discord/misc.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib
