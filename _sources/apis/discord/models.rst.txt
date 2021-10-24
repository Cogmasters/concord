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
   :content-only:

Modify Channel
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyChannel
   :content-only:

Delete Channel
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteChannel
   :content-only:

Get Channel Messages
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannelMessages
   :content-only:

Get Channel Message
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannelMessage
   :content-only:

Create Message
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateMessage
   :content-only:

Crosspost Message
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCrosspostMessage
   :content-only:

Delete Create Reaction
^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateReaction
   :content-only:

Delete Own Reaction
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteOwnReaction
   :content-only:

Delete User Reaction
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteUserReaction
   :content-only:

Get Reactions
^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetReactions
   :content-only:

Delete All Reactions
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteAllReactions
   :content-only:

Delete All Reactions For Emoji
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteAllReactionsForEmoji
   :content-only:

Edit Message
^^^^^^^^^^^^

.. doxygengroup:: DiscordEditMessage
   :content-only:

Delete Message
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteMessage
   :content-only:

Bulk Delete Messages
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordBulkDeleteMessages
   :content-only:

Edit Channel Permissions
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditChannelPermissions
   :content-only:

Get Channel Invites
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannelInvites
   :content-only:

Create Channel Invite
^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateChannelInvite
   :content-only:

Delete Channel Permission
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteChannelPermission
   :content-only:

Trigger Typing Indicator
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordTriggerTypingIndicator
   :content-only:

Follow News Channel
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordFollowNewsChannel
   :content-only:

Get Pinned Messages
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetPinnedMessages
   :content-only:

Pin Message
^^^^^^^^^^^

.. doxygengroup:: DiscordPinMessage
   :content-only:

Unpin Message
^^^^^^^^^^^^^

.. doxygengroup:: DiscordUnpinMessage
   :content-only:

Group DM Add Recipient
^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGroupDmAddRecipient
   :content-only:

Group DM Remove Recipient
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGroupDmRemoveRecipient
   :content-only:

Start Thread With Message
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordStartThreadWithMessage
   :content-only:

Start Thread Without Message
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordStartThreadWithoutMessage
   :content-only:

Join Thread
^^^^^^^^^^^

.. doxygengroup:: DiscordJoinThread
   :content-only:

Add Thread Member
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordAddThreadMember
   :content-only:

Leave Thread
^^^^^^^^^^^^

.. doxygengroup:: DiscordLeaveThread
   :content-only:

Remove Thread Member
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordRemoveThreadMember
   :content-only:

List Thread Members
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListThreadMembers
   :content-only:

List Active Threads
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListActiveThreads
   :content-only:

List Public Archived Threads
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListPublicArchivedThreads
   :content-only:

List Private Archived Threads
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListPrivateArchivedThreads
   :content-only:

List Joined Private Archived Threads
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListJoinedPrivateArchivedThreads
   :content-only:

Emoji
-----

.. doxygenfile:: specs-code/discord/emoji.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

List Guild Emojis
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListGuildEmojis
   :content-only:

Get Guild Emoji
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildEmoji
   :content-only:

Create Guild Emoji
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildEmoji
   :content-only:

Modify Guild Emoji
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildEmoji
   :content-only:

Delete Guild Emoji
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteGuildEmoji
   :content-only:

Guild
-----

.. doxygenfile:: specs-code/discord/guild.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Utils
~~~~~

.. doxygengroup:: DiscordMiscGuild
   :content-only:
   :content-only:

Methods
~~~~~~~

Create Guild
^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuild
   :content-only:

Get Guild
^^^^^^^^^

.. doxygengroup:: DiscordGetGuild
   :content-only:

Get Guild Preview
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildPreview
   :content-only:

Modify Guild
^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuild
   :content-only:

Delete Guild
^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteGuild
   :content-only:

Get Guild Channels
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildChannels
   :content-only:

Create Guild Channel
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildChannel
   :content-only:

Modify Guild Channel Positions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildChannelPositions
   :content-only:

Get Guild Member
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildMember
   :content-only:

List Guild Members
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListGuildMembers
   :content-only:

Search Guild Members
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordSearchGuildMembers
   :content-only:

Modify Guild Member
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildMember
   :content-only:

Add Guild Member
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordAddGuildMember
   :content-only:

Modify Current User Nick
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyCurrentUserNick
   :content-only:

Add Guild Member Role
^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordAddGuildMemberRole
   :content-only:

Remove Guild Member Role
^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordRemoveGuildMemberRole
   :content-only:

Remove Guild Member
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordRemoveGuildMember
   :content-only:

Get Guild Bans
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildBans
   :content-only:

Get Guild Ban
^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildBan
   :content-only:

Create Guild Ban
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildBan
   :content-only:

Remove Guild Ban
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordRemoveGuildBan
   :content-only:

Get Guild Roles
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildRoles
   :content-only:

Create Guild Role
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildRole
   :content-only:

Modify Guild Role Positions
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildRolePositions
   :content-only:

Modify Guild Role
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyGuildRole
   :content-only:

Delete Guild Role
^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteGuildRole
   :content-only:


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
   :content-only:

Delete Invite
^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteInvite
   :content-only:

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
   :content-only:

Modify Current User
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyCurrentUser
   :content-only:

Get Current User
^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetCurrentUser
   :content-only:

Get Current User Guilds
^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetCurrentUserGuilds
   :content-only:

Leave Guild
^^^^^^^^^^^

.. doxygengroup:: DiscordLeaveGuild
   :content-only:

Create DM
^^^^^^^^^

.. doxygengroup:: DiscordCreateDm
   :content-only:

Create Group DM
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGroupDm
   :content-only:

Get User Connections
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetUserConnections
   :content-only:

Voice
-----

.. doxygenfile:: specs-code/discord/voice.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

List Voice Regions
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordListVoiceRegions
   :content-only:

Webhook
-------

.. doxygenfile:: specs-code/discord/webhook.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

Create Webhook
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateWebhook
   :content-only:

Get Channel Webhooks
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetChannelWebhooks
   :content-only:

Get Guild Webhooks
^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildWebhooks
   :content-only:

Get Webhook
^^^^^^^^^^^

.. doxygengroup:: DiscordGetWebhook
   :content-only:

Get Webhook with Token
^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetWebhookWithToken
   :content-only:

Modify Webhook
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyWebhook
   :content-only:

Modify Webhook with Token
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordModifyWebhookWithToken
   :content-only:

Delete Webhook
^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteWebhook
   :content-only:

Delete Webhook with Token
^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteWebhookWithToken
   :content-only:

Execute Webhook
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordExecuteWebhook
   :content-only:

Get Webhook Message
^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetWebhookMessage
   :content-only:

Edit Webhook Message
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditWebhookMessage
   :content-only:

Delete Webhook Message
^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteWebhookMessage
   :content-only:

Gateway
-------

.. doxygenfile:: specs-code/discord/gateway.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Utils
~~~~~

.. doxygengroup:: DiscordMiscGateway
   :content-only:
   :content-only:

Methods
~~~~~~~

Get Gateway
^^^^^^^^^^^

.. doxygengroup:: DiscordGetGateway
   :content-only:

Get Gateway Bot
^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGatewayBot
   :content-only:

Permissions
-----------

.. doxygenfile:: specs-code/discord/permissions.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Custom
------

.. doxygenfile:: specs-code/discord/misc.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib
