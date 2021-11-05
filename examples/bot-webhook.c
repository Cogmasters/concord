#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "discord.h"

static void print_usage(char *prog)
{
  fprintf(stderr, "Usage: %s -i webhook-id -h webhook-token\n", prog);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  char *webhook_token = NULL;
  u64_snowflake_t webhook_id = 0;

  int opt;
  while (-1 != (opt = getopt(argc, argv, "i:t:"))) {
    switch (opt) {
    case 't': webhook_token = strdup(optarg); break;
    case 'i': webhook_id = strtoull(optarg, NULL, 10); break;
    default: print_usage(argv[0]); break;
    }
  }
  if (!webhook_token || !webhook_id) print_usage(argv[0]);

  printf("\n\nThis bot demonstrates how to use webhook endpoints which "
         "require no authentication token\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_global_init();

  struct discord *client = discord_init(NULL);
  assert(NULL != client && "Couldn't initialize client");
  struct discord_webhook webhook;
  discord_webhook_init(&webhook);

  discord_get_webhook_with_token(client, webhook_id, webhook_token, &webhook);
  discord_webhook_cleanup(&webhook);

  discord_execute_webhook(
    client, webhook_id, webhook_token,
    &(struct discord_execute_webhook_params){ .content = "Hello world!" },
    NULL);

  discord_cleanup(client);
  free(webhook_token);

  discord_global_cleanup();

  return EXIT_SUCCESS;
}
