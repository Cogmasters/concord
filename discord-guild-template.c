#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_get_guild_template(
  struct discord *client,
  char *code,
  struct discord_guild_template *p_template)
{
  if (!code) {
    log_error("Missing 'code'");
    return ORCA_MISSING_PARAMETER;
  }

  if (!p_template) {
    log_error("Missing 'p_template'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
          &client->adapter,
          &(struct ua_resp_handle){
            .ok_cb = discord_guild_template_from_json_v,
            .ok_obj = &p_template
          },
          NULL,
          HTTP_GET,
          "/guilds/templates/%s",
          code);
}
