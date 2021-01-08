#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <libdiscord.h>

void on_ready(struct discord_s *client)
{
  discord_user_t *self = discord_user_init();
  assert(NULL != self);

  discord_get_client_user(client, &self);
  fprintf(stderr, "\n\nSuccesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  discord_user_cleanup(self);
}

int main(void)
{
  FILE *f_bot_token = fopen("bot_token","rb");
  assert(NULL != f_bot_token);

  char bot_token[100];
  fgets(bot_token, 99, f_bot_token);
  fclose(f_bot_token);

  discord_global_init();
  discord_t *client = discord_init(bot_token);
  assert(NULL != client);

  discord_set_on_ready(client, &on_ready);

  discord_run(client);

  discord_cleanup(client);
  discord_global_cleanup();
}

