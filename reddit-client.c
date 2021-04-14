#include <string.h>

#include "reddit.h"
#include "reddit-internal.h"

struct reddit* 
reddit_config_init(const char config_file[])
{
  struct reddit *new_client = calloc(1, sizeof *new_client);
  new_client->adapter.p_client = new_client;
  reddit_adapter_config_init(&new_client->adapter, config_file);
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
  struct sized_buffer username = ua_config_get_field(client->adapter.ua, "reddit.username");
  struct sized_buffer password = ua_config_get_field(client->adapter.ua, "reddit.password");

  char query[512];
  int ret = query_inject(query, sizeof(query),
              "(grant_type):s"
              "(username):.*s"
              "(password):.*s", 
              "password",
              (int)username.size, username.start,
              (int)password.size, password.start);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");

  reddit_adapter_run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_POST, "/access_token%s", query);
}
