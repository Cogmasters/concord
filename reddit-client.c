#include <string.h>

#include "reddit.h"
#include "reddit-internal.h"

static void
_reddit_init(struct reddit *new_client)
{
  new_client->adapter.p_client = new_client;
  reddit_adapter_init(&new_client->adapter, &new_client->config);
}


struct reddit*
reddit_init(
  const char username[],
  const char password[],
  const char client_id[],
  const char client_secret[])
{
  struct reddit *new_client = calloc(1, sizeof *new_client);

  logconf_setup(&new_client->config, NULL);

  *new_client = (struct reddit){
    .username = {
      .start = (char*)username,
      .size = cee_str_bounds_check(username, 128)
    },
    .password = {
      .start = (char*)password,
      .size = cee_str_bounds_check(password, 128)
    },
    .client_id = {
      .start = (char*)client_id,
      .size = cee_str_bounds_check(client_id, 128)
    },
    .client_secret = {
      .start = (char*)client_secret,
      .size = cee_str_bounds_check(client_secret, 128)
    }
  };

  _reddit_init(new_client);

  return new_client;
}

struct reddit* 
reddit_config_init(const char config_file[])
{
  struct reddit *new_client = calloc(1, sizeof *new_client);

  logconf_setup(&new_client->config, config_file);

  new_client->username = logconf_get_field(&new_client->config, "reddit.username");
  new_client->password = logconf_get_field(&new_client->config, "reddit.password");
  new_client->client_id = logconf_get_field(&new_client->config, "reddit.client_id");
  new_client->client_secret = logconf_get_field(&new_client->config, "reddit.client_secret");

  _reddit_init(new_client);

  return new_client;
}

void 
reddit_cleanup(struct reddit *client)
{
  logconf_cleanup(&client->config);
  reddit_adapter_cleanup(&client->adapter);
  free(client);
}
