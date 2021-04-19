#include <stdio.h>
#include <stdlib.h>

#include "reddit.h"


int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct reddit *client = reddit_config_init(config_file);

  reddit_access_token(client); 

  struct reddit_search_params params = {
    .limit = 100,
    .q = "C Discord library",
  };

  struct sized_buffer json_resp={0};
  reddit_search(client, &params, "all", &json_resp);

  FILE *f_out = fopen("reddit-search.json", "w+");
  fwrite(json_resp.start, 1, json_resp.size, f_out);
  fclose(f_out);

  reddit_cleanup(client);
}
