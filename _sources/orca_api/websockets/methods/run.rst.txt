..
  Most of our documentation is generated from our source code comments,
    please head to github.com/cee-studio/orca if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - common/websockets.h

=======
Running
=======

Initializer
-----------

.. doxygenfunction:: ws_init
.. doxygenfunction:: ws_cleanup

Establishing Connection
-----------------------

.. doxygenfunction:: ws_set_url
.. doxygenfunction:: ws_start
.. doxygenfunction:: ws_reqheader_add

Maintain Connection
-------------------

.. doxygenfunction:: ws_perform

Send Control-frames
-------------------

.. doxygenfunction:: ws_send_binary
.. doxygenfunction:: ws_send_text
.. doxygenfunction:: ws_ping
.. doxygenfunction:: ws_pong
.. doxygenfunction:: ws_close
