#include <string.h>

#include "reddit.h"
#include "reddit-internal.h"

struct reddit* 
reddit_config_init(const char config_file[])
{
  struct reddit *new_client = calloc(1, sizeof *new_client);
  logconf_setup(&new_client->config, config_file);
  new_client->username = logconf_get_field(&new_client->config, "reddit.username");
  new_client->password = logconf_get_field(&new_client->config, "reddit.password");
  new_client->client_id = logconf_get_field(&new_client->config, "reddit.client_id");
  new_client->client_secret = logconf_get_field(&new_client->config, "reddit.client_secret");

  new_client->adapter.p_client = new_client;
  reddit_adapter_init(&new_client->adapter, &new_client->config);

  return new_client;
}

void 
reddit_cleanup(struct reddit *client)
{
  reddit_adapter_cleanup(&client->adapter);
  free(client);
}

void
reddit_access_token(struct reddit *client)
{

  char query[512];
  int ret = query_inject(query, sizeof(query),
              "(grant_type):s"
              "(username):.*s"
              "(password):.*s", 
              "password",
              (int)client->username.size, client->username.start,
              (int)client->password.size, client->password.start);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");

  reddit_adapter_run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_POST, "/access_token%s", query);
}
