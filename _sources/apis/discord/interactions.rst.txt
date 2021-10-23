..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

============
Interactions
============

Application Commands
--------------------

.. doxygenfile:: specs-code/discord/application_commands.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

Get Global Application Commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGlobalApplicationCommands
   :content-only:

Create Global Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGlobalApplicationCommand
   :content-only:

Get Global Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGlobalApplicationCommand

Edit Global Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditGlobalApplicationCommand

Delete Global Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteGlobalApplicationCommand

Bulk Overwrite Global Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordBulkOverwriteGlobalApplicationCommand

Get Guild Application Commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildApplicationCommands

Create Guild Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateGuildApplicationCommand

Get Guild Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildApplicationCommand

Edit Guild Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditGuildApplicationCommand

Delete Guild Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteGuildApplicationCommand

Bulk Overwrite Guild Application Command
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordBulkOverwriteGuildApplicationCommand

Get Guild Application Command Permissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetGuildApplicationCommandPermissions

Get Application Command Permissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetApplicationCommandPermissions

Edit Application Command Permissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditApplicationCommandPermissions

Batch Edit Application Command Permissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordBatchEditApplicationCommandPermissions

Interaction
-----------

.. doxygenfile:: specs-code/discord/interaction.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib

Methods
~~~~~~~

Create Interaction Response
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateInteractionResponse

Get Original Interaction Response
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetOriginalInteractionResponse

Edit Original Interaction Response
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditOriginalInteractionResponse

Delete Original Interaction Response
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteOriginalInteractionResponse

Create Followup Message
^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordCreateFollowupMessage

Get Followup Message
^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordGetFollowupMessage

Edit Followup Message
^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordEditFollowupMessage

Delete Followup Message
^^^^^^^^^^^^^^^^^^^^^^^

.. doxygengroup:: DiscordDeleteFollowupMessage

Message Components
------------------

.. doxygenfile:: specs-code/discord/message_components.h
    :sections: detaileddescription briefdescription innerclass enum public-type public-attrib
