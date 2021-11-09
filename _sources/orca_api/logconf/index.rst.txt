..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - cee-utils/logconf.h

=============================
Modularized Logging Reference
=============================

Datatypes
---------

.. doxygendefine:: LOGCONF_ID_LEN
.. doxygendefine:: LOGCONF_PATH_MAX
.. doxygenstruct:: logconf
.. doxygenstruct:: loginfo

Initialize
----------

.. doxygenfunction:: logconf_setup
.. doxygenfunction:: logconf_branch
.. doxygenfunction:: logconf_cleanup

Logging
-------

.. doxygenfunction:: logconf_http
.. doxygendefine:: logconf_log
.. doxygendefine:: logconf_trace
.. doxygendefine:: logconf_debug
.. doxygendefine:: logconf_info
.. doxygendefine:: logconf_warn
.. doxygendefine:: logconf_error
.. doxygendefine:: logconf_fatal

Utils
-----

.. doxygenfunction:: logconf_get_field
