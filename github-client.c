#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "cee-utils.h"
#include "cee-utils/ntl.h"
#include "json-actor.h"

#include "github.h"
#include "github-internal.h"

static void
_github_presets_init(struct github_presets *presets,
                     const struct sized_buffer *username,
                     const struct sized_buffer *token,
                     const char *repo_config)
{

  presets->owner = NULL;
  presets->repo = NULL;
  presets->default_branch = NULL;

  /* Optionally fill in the repo_config. Can be
   * done later with github_fill_repo_config. */
  if (repo_config) {
    size_t len = 0;
    char *json = cee_load_whole_file(repo_config, &len);

    json_extract(json, len, "(owner):?s,(repo):?s,(default_branch):?s",
                 &presets->owner, &presets->repo, &presets->default_branch);

    free(json);
  }

  cee_strndup(username->start, username->size, &presets->username);
  cee_strndup(token->start, token->size, &presets->token);
}

void
github_write_json(char *json, size_t len, void *user_obj)
{
  struct sized_buffer *new_user_obj = user_obj;

  new_user_obj->size = cee_strndup(json, len, &new_user_obj->start);
}

ORCAcode
github_fill_repo_config(struct github *client, char *repo_config)
{
  size_t len = 0;
  char *json;

  ORCA_EXPECT(client, !IS_EMPTY_STRING(repo_config), ORCA_BAD_PARAMETER);

  json = cee_load_whole_file(repo_config, &len);

  json_extract(json, len, "(owner):?s,(repo):?s,(default_branch):?s",
               &client->presets.owner, &client->presets.repo,
               &client->presets.default_branch);

  free(json);

  return ORCA_OK;
}

struct github *
github_init(const char username[],
            const char token[],
            const char repo_config[])
{
  const struct sized_buffer _username = { (char *)username, strlen(username) };
  const struct sized_buffer _token = { (char *)token, strlen(token) };
  struct github *new_client;

  new_client = calloc(1, sizeof *new_client);
  logconf_setup(&new_client->conf, "GITHUB", NULL);

  _github_presets_init(&new_client->presets, &_username, &_token, repo_config);

  github_adapter_init(&new_client->adapter, &new_client->conf,
                      &new_client->presets);

  return new_client;
}

struct github *
github_config_init(const char config_file[], const char repo_config[])
{
  struct sized_buffer username, token;
  struct github *new_client;
  FILE *fp;

  fp = fopen(config_file, "rb");
  VASSERT_S(fp != NULL, "Couldn't open '%s': %s", config_file,
            strerror(errno));

  new_client = calloc(1, sizeof *new_client);
  logconf_setup(&new_client->conf, "GITHUB", fp);

  fclose(fp);

  username = logconf_get_field(&new_client->conf, "github.username");
  token = logconf_get_field(&new_client->conf, "github.token");

  _github_presets_init(&new_client->presets, &username, &token, repo_config);

  github_adapter_init(&new_client->adapter, &new_client->conf,
                      &new_client->presets);

  return new_client;
}
