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
github_create_gist(struct github *client,
                   struct github_gist_create_params *params,
                   struct github_gist *gist)
{
  log_info("===create-gist===");

  if (!params->description) {
    log_error("Missing 'description'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->title) {
    log_error("Missing 'title'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->contents) {
    log_error("Missing 'contents'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  char fmt[2048];

  /* Create the format string for the payload
   * TODO:
   * Allocate buffer big enough, then free it after the request is made
   * */
  snprintf(fmt, sizeof(fmt),
           "(public): \"%s\", (description): \"%s\", (files): { (%s): { "
           "(content): \"%s\" }}",
           params->public, params->description, params->title,
           params->contents);

  size_t ret = json_inject(payload, sizeof(payload), fmt);

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &github_gist_from_json_v,
                              .ok_obj = &gist },
    &(struct sized_buffer){ payload, ret }, HTTP_POST, "/gists");
}

ORCAcode
github_get_gist(struct github *client, char *id, struct github_gist *gist)
{
  log_info("===get-a-gist===");

  if (!id) {
    log_error("Missing 'id'");
    return ORCA_MISSING_PARAMETER;
  }

  if (!gist) {
    log_error("Missing 'gist'");
    return ORCA_MISSING_PARAMETER;
  }

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &github_gist_from_json_v,
                              .ok_obj = &gist },
    NULL, HTTP_GET, "/gists/%s", id);
}

ORCAcode
github_gist_is_starred(struct github *client, char *id)
{
  log_info("===gist-is-starred===");

  if (!id) {
    log_error("Missing 'id'");
    return ORCA_MISSING_PARAMETER;
  }

  return github_adapter_run(&client->adapter, NULL, NULL, HTTP_GET,
                            "/gists/%s/star", id);
}
