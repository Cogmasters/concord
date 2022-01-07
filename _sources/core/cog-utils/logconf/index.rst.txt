..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - cog-utils/logconf.h

=========================
Modular Logging Reference
=========================

An add-on to the popular `log.c <https://github.com/rxi/log.c>`__
logging library that adds modularity over the existing functionalities.
All functions from ``log.c`` are included and can be expected to behave the same.

The following outlines the modular logging functionalities.

Datatypes
---------

.. doxygenstruct:: logconf

Constants
---------

.. doxygendefine:: LOGCONF_ID_LEN
.. doxygendefine:: LOGCONF_PATH_MAX

Configure logging via a JSON file
---------------------------------

.. doxygenfunction:: logconf_setup

Get file field
^^^^^^^^^^^^^^

.. doxygenfunction:: logconf_get_field

Branch a logging module
-----------------------

.. doxygenfunction:: logconf_branch

Cleanup
-------

.. doxygenfunction:: logconf_cleanup


Logging
-------

.. doxygendefine:: logconf_trace
.. doxygendefine:: logconf_debug
.. doxygendefine:: logconf_info
.. doxygendefine:: logconf_warn
.. doxygendefine:: logconf_error
.. doxygendefine:: logconf_fatal
.. doxygendefine:: logconf_log

HTTP
^^^^

.. doxygenfunction:: logconf_http
.. doxygenstruct:: loginfo

Configuring logging manually
----------------------------

.. doxygenfunction:: logconf_set_quiet
.. doxygenfunction:: logconf_set_level
.. doxygenfunction:: logconf_add_fp
.. doxygenfunction:: logconf_add_callback
.. doxygenfunction:: logconf_set_lock
