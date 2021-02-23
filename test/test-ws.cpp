#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nSuccesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

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

  setcb(client, READY, &on_ready);

  run(client);

  cleanup(client);

  global_cleanup();
}

