#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_get_current_bot_application_information(
    struct discord *client, struct discord_ret_application *ret)
{
    struct discord_attributes attr = { 0 };

    DISCORD_ATTR_INIT(attr, discord_application, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/oauth2/applications/@me");
}

CCORDcode
discord_get_current_authorization_information(
    struct discord *client, struct discord_ret_auth_response *ret)
{
    struct discord_attributes attr = { 0 };

    DISCORD_ATTR_INIT(attr, discord_auth_response, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/oauth2/@me");
}
