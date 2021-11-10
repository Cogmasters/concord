..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - cee-utils/logconf.h

=========================
Modular Logging Reference
=========================

An add-on to the popular `log.c <https://github.com/rxi/log.c>`__
logging library. Its goal is to promote modularity over the existing
functionalities. All functions from ``log.c`` are included and expect 
them to behave as the original. The following outlines the modular logging
functionalities.

Datatypes
---------

.. doxygenstruct:: logconf
.. doxygenstruct:: loginfo
.. doxygendefine:: LOGCONF_ID_LEN
.. doxygendefine:: LOGCONF_PATH_MAX

Logging
-------

.. doxygendefine:: logconf_trace
.. doxygendefine:: logconf_debug
.. doxygendefine:: logconf_info
.. doxygendefine:: logconf_warn
.. doxygendefine:: logconf_error
.. doxygendefine:: logconf_fatal
.. doxygendefine:: logconf_log

HTTP Logging
------------

.. doxygenfunction:: logconf_http

Configuring Via a Config File
-----------------------------

.. doxygenfunction:: logconf_setup

Configuring Manually
--------------------

.. doxygenfunction:: logconf_set_quiet
.. doxygenfunction:: logconf_set_level
.. doxygenfunction:: logconf_add_fp
.. doxygenfunction:: logconf_add_callback
.. doxygenfunction:: logconf_set_lock

Branch a Logging Module
-----------------------

.. doxygenfunction:: logconf_branch

Cleanup
-------

.. doxygenfunction:: logconf_cleanup

Utils
-----

.. doxygenfunction:: logconf_get_field

log.c Borrowed Datatypes
------------------------

.. doxygengroup:: Log_C_Datatypes
