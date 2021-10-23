..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

======
Client
======

.. doxygenstruct:: discord
.. doxygenenum:: discord_event_scheduler

Functions
---------

Initialization / Cleanup
~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: discord_global_init
.. doxygenfunction:: discord_global_cleanup
.. doxygenfunction:: discord_init
.. doxygenfunction:: discord_config_init
.. doxygenfunction:: discord_clone
.. doxygenfunction:: discord_cleanup

Connecting
~~~~~~~~~~

.. doxygenfunction:: discord_run
.. doxygenfunction:: discord_shutdown
.. doxygenfunction:: discord_reconnect

Error Handling
~~~~~~~~~~~~~~

.. doxygenfunction:: discord_strerror

Behaviour
~~~~~~~~~

.. doxygenfunction:: discord_add_intents
.. doxygenfunction:: discord_remove_intents
.. doxygenfunction:: discord_set_prefix
.. doxygenfunction:: discord_set_event_scheduler

Utils
~~~~~

.. doxygenfunction:: discord_set_data
.. doxygenfunction:: discord_get_data
.. doxygenfunction:: discord_set_presence
.. doxygenfunction:: discord_get_ping
