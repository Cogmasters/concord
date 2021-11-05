#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cee-utils.h"
#include "cee-utils/ntl.h"
#include "json-actor.h"

#include "github.h"
#include "github-internal.h"

ORCAcode
github_create_fork(struct github *client, char *owner, char *repo)
{
  log_info("===create-fork===");

  if (!owner) {
    log_error("Missing 'owner'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!repo) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = NULL, .ok_obj = NULL }, NULL, HTTP_POST,
    "/repos/%s/%s/forks", owner, repo);
}
