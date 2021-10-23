..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

===============
Event Reference
===============

.. doxygenfunction:: discord_set_on_command
.. doxygenfunction:: discord_set_on_event_raw
.. doxygenfunction:: discord_set_on_idle
.. doxygenfunction:: discord_set_on_ready
.. doxygenfunction:: discord_set_on_application_command_create
.. doxygenfunction:: discord_set_on_application_command_update
.. doxygenfunction:: discord_set_on_application_command_delete
.. doxygenfunction:: discord_set_on_channel_create
.. doxygenfunction:: discord_set_on_channel_update
.. doxygenfunction:: discord_set_on_channel_delete
.. doxygenfunction:: discord_set_on_channel_pins_update
.. doxygenfunction:: discord_set_on_thread_create
.. doxygenfunction:: discord_set_on_thread_update
.. doxygenfunction:: discord_set_on_thread_delete
.. doxygenfunction:: discord_set_on_guild_role_create
.. doxygenfunction:: discord_set_on_guild_role_update
.. doxygenfunction:: discord_set_on_guild_role_delete
.. doxygenfunction:: discord_set_on_guild_member_update
.. doxygenfunction:: discord_set_on_guild_ban_add
.. doxygenfunction:: discord_set_on_guild_ban_remove
.. doxygenfunction:: discord_set_on_interaction_create
.. doxygenfunction:: discord_set_on_message_create
.. doxygenfunction:: discord_set_on_message_update
.. doxygenfunction:: discord_set_on_message_delete
.. doxygenfunction:: discord_set_on_message_delete_bulk
.. doxygenfunction:: discord_set_on_message_reaction_add
.. doxygenfunction:: discord_set_on_message_reaction_remove
.. doxygenfunction:: discord_set_on_message_reaction_remove_all
.. doxygenfunction:: discord_set_on_message_reaction_remove_emoji
.. doxygenfunction:: discord_set_on_voice_state_update
.. doxygenfunction:: discord_set_on_voice_server_update

Callbacks Signatures
--------------------

.. doxygengroup:: DiscordCallbacksGeneral
   :content-only:
.. doxygengroup:: DiscordCallbacksApplicationCommand
   :content-only:
.. doxygengroup:: DiscordCallbacksChannel
   :content-only:
.. doxygengroup:: DiscordCallbacksGuild
   :content-only:
.. doxygengroup:: DiscordCallbacksInteraction
   :content-only:
.. doxygengroup:: DiscordCallbacksMessage
   :content-only:
.. doxygengroup:: DiscordCallbacksVoice
   :content-only:
