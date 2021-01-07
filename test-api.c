#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <libdiscord.h>

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

  discord_user_t *user = discord_user_init(); 
  assert(NULL != user);

  discord_get_client(client, &user);
  printf("Greetings, %s#%s!\n", user->username, user->discriminator);

  discord_user_cleanup(user);

  discord_cleanup(client);
  discord_global_cleanup();
}
