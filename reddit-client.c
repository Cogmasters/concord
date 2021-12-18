#define _GNU_SOURCE
#include <string.h>
#include <errno.h>

#include "reddit.h"
#include "reddit-internal.h"

static void
_reddit_init(struct reddit *new_client)
{
  reddit_adapter_init(&new_client->adapter, &new_client->conf);
}

struct reddit *
reddit_init(const char username[],
            const char password[],
            const char client_id[],
            const char client_secret[])
{
  struct reddit *new_client;

  new_client = calloc(1, sizeof *new_client);
  logconf_setup(&new_client->conf, "REDDIT", NULL);

  /* TODO: fix memory leak */
  new_client->username.size =
    asprintf(&new_client->username.start, "%s", username);
  new_client->password.size =
    asprintf(&new_client->password.start, "%s", password);
  new_client->client_id.size =
    asprintf(&new_client->client_id.start, "%s", client_id);
  new_client->client_secret.size =
    asprintf(&new_client->client_secret.start, "%s", client_secret);

  _reddit_init(new_client);

  return new_client;
}

struct reddit *
reddit_config_init(const char config_file[])
{
  struct reddit *new_client = calloc(1, sizeof *new_client);
  FILE *fp;

  fp = fopen(config_file, "rb");
  VASSERT_S(fp != NULL, "Couldn't open '%s': %s", config_file,
            strerror(errno));

  new_client = calloc(1, sizeof *new_client);
  logconf_setup(&new_client->conf, "REDDIT", fp);
  fclose(fp);

  new_client->username =
    logconf_get_field(&new_client->conf, "reddit.username");
  new_client->password =
    logconf_get_field(&new_client->conf, "reddit.password");
  new_client->client_id =
    logconf_get_field(&new_client->conf, "reddit.client_id");
  new_client->client_secret =
    logconf_get_field(&new_client->conf, "reddit.client_secret");

  _reddit_init(new_client);

  return new_client;
}

void
reddit_cleanup(struct reddit *client)
{
  logconf_cleanup(&client->conf);
  reddit_adapter_cleanup(&client->adapter);
  free(client);
}
