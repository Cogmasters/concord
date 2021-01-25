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

  user::self::get(client, self);
  printf("Greetings, %s#%s!\n", self->username, self->discriminator);

  guild::data *guilds = NULL;
  user::self::get_guilds(client, &guilds);

  for (size_t i=0; guilds + i; ++i) {
    D_PRINT("%s", guilds[i].id);
  }

  //guild::list_cleanup(&guilds);

  user::cleanup(self);

  //cleanup(client);

  global_cleanup();
}
