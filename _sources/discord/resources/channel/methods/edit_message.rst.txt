..
  Most of our documentation is generated from our source code comments,
    please head to github.com/Cogmasters/concord if you want to contribute!

  The following files contains the documentation used to generate this page: 
  - discord.h (for public datatypes)
  - discord-internal.h (for private datatypes)
  - specs/discord/ (for generated datatypes)

============
Edit Message
============

.. doxygenfunction:: discord_edit_message
.. doxygenstruct:: discord_edit_message_params

Example
-------

.. code:: c

   struct discord_message ret;
   
   discord_create_message(client, 
                          msg->channel_id,
                          &(struct discord_create_message_params){ 
                            .content = "Hello there?" 
                          },
                          &ret);
   
   discord_edit_message(client,
                        msg->channel_id,
                        ret.id,
                        &(struct discord_edit_message_params){
                          .content = "Such a fast response!"
                        },
                        NULL);
  
   discord_message_cleanup(&ret); 
