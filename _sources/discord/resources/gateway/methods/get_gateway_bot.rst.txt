..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

Get Gateway Bot
===============

.. doxygenfunction:: discord_get_gateway_bot

Example
-------

.. code:: c

   struct sized_buffer ret;

   discord_get_gateway_bot(client, &ret);
   
   printf("JSON length: %zu\n", ret.size);
   printf("%s\n", ret.start);
