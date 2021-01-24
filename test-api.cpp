#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  global_init();

  client *client = fast_init(config_file);
  assert(NULL != client);

  user::data *self = user::init(); 
  assert(NULL != self);

  user::get_self(client, self);
  printf("Greetings, %s#%s!\n", self->username, self->discriminator);

  user::cleanup(self);

  cleanup(client);

  global_cleanup();
}
