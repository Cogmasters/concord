#include <string.h>

#include "reddit.h"
#include "reddit-common.h"

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
