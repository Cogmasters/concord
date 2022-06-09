#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-worker.h"
#include "cog-utils.h"

static void
_discord_init(struct discord *new_client)
{
    ccord_global_init();
    discord_timers_init(&new_client->timers.internal);
    discord_timers_init(&new_client->timers.user);
    new_client->io_poller = io_poller_create();

    new_client->workers = calloc(1, sizeof *new_client->workers);
    ASSERT_S(!pthread_mutex_init(&new_client->workers->lock, NULL),
             "Couldn't initialize Client's mutex");
    ASSERT_S(!pthread_cond_init(&new_client->workers->cond, NULL),
             "Couldn't initialize Client's cond");

    discord_refcounter_init(&new_client->refcounter, &new_client->conf);
    discord_message_commands_init(&new_client->commands, &new_client->conf);
    discord_rest_init(&new_client->rest, &new_client->conf, new_client->token);
    discord_gateway_init(&new_client->gw, &new_client->conf,
                         new_client->token);
#ifdef CCORD_VOICE
    discord_voice_connections_init(new_client);
#endif

    if (new_client->token) { /* fetch client's user structure */
        CCORDcode code =
            discord_get_current_user(new_client, &(struct discord_ret_user){
                                                     .sync = &new_client->self,
                                                 });
        ASSERT_S(CCORD_OK == code, "Couldn't fetch client's user object");
    }
    new_client->is_original = true;
}

struct discord *
discord_init(const char token[])
{
    struct discord *new_client;

    new_client = calloc(1, sizeof *new_client);
    logconf_setup(&new_client->conf, "DISCORD", NULL);
    /* silence terminal input by default */
    logconf_set_quiet(&new_client->conf, true);

    if (token && *token) cog_strndup(token, strlen(token), &new_client->token);

    _discord_init(new_client);

    return new_client;
}

struct discord *
discord_config_init(const char config_file[])
{
    struct ccord_szbuf_readonly field;
    struct discord *new_client;
    FILE *fp;

    fp = fopen(config_file, "rb");
    VASSERT_S(fp != NULL, "Couldn't open '%s': %s", config_file,
              strerror(errno));

    new_client = calloc(1, sizeof *new_client);
    logconf_setup(&new_client->conf, "DISCORD", fp);

    fclose(fp);

    field = discord_config_get_field(new_client,
                                     (char *[2]){ "discord", "token" }, 2);
    if (field.size && 0 != strncmp("YOUR-BOT-TOKEN", field.start, field.size))
        cog_strndup(field.start, field.size, &new_client->token);

    _discord_init(new_client);

    /* check for default prefix in config file */
    field = discord_config_get_field(
        new_client, (char *[2]){ "discord", "default_prefix" }, 2);
    if (field.size) {
        jsmn_parser parser;
        jsmntok_t tokens[16];

        jsmn_init(&parser);
        if (0 < jsmn_parse(&parser, field.start, field.size, tokens,
                           sizeof(tokens) / sizeof *tokens))
        {
            jsmnf_loader loader;
            jsmnf_pair pairs[16];

            jsmnf_init(&loader);
            if (0 < jsmnf_load(&loader, field.start, tokens, parser.toknext,
                               pairs, sizeof(pairs) / sizeof *pairs))
            {
                bool enable_prefix = false;
                jsmnf_pair *f;

                if ((f = jsmnf_find(pairs, field.start, "enable", 6)))
                    enable_prefix = ('t' == field.start[f->v.pos]);

                if (enable_prefix
                    && (f = jsmnf_find(pairs, field.start, "prefix", 6))) {
                    discord_message_commands_set_prefix(&new_client->commands,
                                                        field.start + f->v.pos,
                                                        f->v.len);
                }
            }
        }
    }

    return new_client;
}

static void
_discord_clone_gateway(struct discord_gateway *clone,
                       const struct discord_gateway *orig)
{
    const size_t n = orig->payload.json.npairs
                     - (size_t)(orig->payload.data - orig->payload.json.pairs);

    clone->payload.data = malloc(n * sizeof *orig->payload.json.pairs);
    memcpy(clone->payload.data, orig->payload.data,
           n * sizeof *orig->payload.json.pairs);

    clone->payload.json.size =
        cog_strndup(orig->payload.json.start, orig->payload.json.size,
                    &clone->payload.json.start);
}

struct discord *
discord_clone(const struct discord *orig)
{
    struct discord *clone = malloc(sizeof(struct discord));

    memcpy(clone, orig, sizeof(struct discord));
    clone->is_original = false;

    _discord_clone_gateway(&clone->gw, &orig->gw);

    return clone;
}

static void
_discord_clone_gateway_cleanup(struct discord_gateway *clone)
{
    free(clone->payload.data);
    free(clone->payload.json.start);
}

static void
_discord_clone_cleanup(struct discord *client)
{
    _discord_clone_gateway_cleanup(&client->gw);
}

void
discord_cleanup(struct discord *client)
{
    if (!client->is_original) {
        _discord_clone_cleanup(client);
    }
    else {
        discord_worker_join(client);
        discord_rest_cleanup(&client->rest);
        discord_gateway_cleanup(&client->gw);
        discord_message_commands_cleanup(&client->commands);
#ifdef CCORD_VOICE
        discord_voice_connections_cleanup(client);
#endif
        discord_user_cleanup(&client->self);
        io_poller_destroy(client->io_poller);
        discord_refcounter_cleanup(&client->refcounter);
        discord_timers_cleanup(client, &client->timers.user);
        discord_timers_cleanup(client, &client->timers.internal);
        logconf_cleanup(&client->conf);
        if (client->token) free(client->token);
        pthread_mutex_destroy(&client->workers->lock);
        pthread_cond_destroy(&client->workers->cond);
        free(client->workers);
    }
    free(client);
}

CCORDcode
discord_return_error(struct discord *client,
                     const char error[],
                     CCORDcode code)
{
    logconf_info(&client->conf, "(%d) %s", code, error);
    return code;
}

static const char *
_ccord_strerror(CCORDcode code)
{
    switch (code) {
    case CCORD_OK:
        return "Success: The request was a success";
    case CCORD_HTTP_CODE:
        return "Failure: The request was a failure";
    case CCORD_UNUSUAL_HTTP_CODE:
        return "Failure: The request was a failure";
    case CCORD_BAD_PARAMETER:
        return "Failure: Bad value for parameter";
    case CCORD_BAD_JSON:
        return "Failure: Internal failure when encoding or decoding JSON";
    case CCORD_CURLE_INTERNAL:
    case CCORD_CURLM_INTERNAL:
        return "Failure: Libcurl's internal error";
    default:
        return "Unknown: Code received doesn't match any description";
    }
}

const char *
discord_strerror(CCORDcode code, struct discord *client)
{
    (void)client;

    switch (code) {
    default:
        return _ccord_strerror(code);
    case CCORD_DISCORD_JSON_CODE:
        return "Discord JSON Error Code: Failed request";
    case CCORD_DISCORD_BAD_AUTH:
        return "Discord Bad Authentication: Bad authentication token";
    case CCORD_DISCORD_RATELIMIT:
        return "Discord Ratelimit: You are being ratelimited";
    case CCORD_DISCORD_CONNECTION:
        return "Discord Connection: Couldn't establish a connection to "
               "discord";
    }
}

void *
discord_set_data(struct discord *client, void *data)
{
    return client->data = data;
}

void *
discord_get_data(struct discord *client)
{
    return client->data;
}

void
discord_add_intents(struct discord *client, uint64_t code)
{
    if (WS_CONNECTED == ws_get_status(client->gw.ws)) {
        logconf_error(&client->conf, "Can't set intents to a running client.");
        return;
    }

    client->gw.id.intents |= code;
}

void
discord_remove_intents(struct discord *client, uint64_t code)
{
    if (WS_CONNECTED == ws_get_status(client->gw.ws)) {
        logconf_error(&client->conf,
                      "Can't remove intents from a running client.");
        return;
    }

    client->gw.id.intents &= ~code;
}

void
discord_set_prefix(struct discord *client, const char prefix[])
{
    if (!prefix || !*prefix) return;

    discord_message_commands_set_prefix(&client->commands, prefix,
                                        strlen(prefix));
}

const struct discord_user *
discord_get_self(struct discord *client)
{
    return &client->self;
}

void
discord_set_on_command(struct discord *client,
                       char command[],
                       discord_ev_message callback)
{
    size_t length = (!command || !*command) ? 0 : strlen(command);

    discord_message_commands_append(&client->commands, command, length,
                                    callback);
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_commands(struct discord *client,
                        char *const commands[],
                        int amount,
                        discord_ev_message callback)
{
    for (int i = 0; i < amount; ++i)
        discord_set_on_command(client, commands[i], callback);
}

void
discord_set_event_scheduler(struct discord *client,
                            discord_ev_scheduler callback)
{
    client->gw.scheduler = callback;
}

void
discord_shutdown(struct discord *client)
{
    if (client->gw.session->status != DISCORD_SESSION_SHUTDOWN)
        discord_gateway_shutdown(&client->gw);
}

void
discord_reconnect(struct discord *client, bool resume)
{
    discord_gateway_reconnect(&client->gw, resume);
}

void
discord_set_on_ready(struct discord *client, discord_ev_ready callback)
{
    client->gw.cbs[DISCORD_EV_READY] = (discord_ev)callback;
}

void
discord_set_on_guild_role_create(struct discord *client,
                                 discord_ev_guild_role_create callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_ROLE_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_role_update(struct discord *client,
                                 discord_ev_guild_role_update callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_ROLE_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_role_delete(struct discord *client,
                                 discord_ev_guild_role_delete callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_ROLE_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_member_add(struct discord *client,
                                discord_ev_guild_member callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_MEMBER_ADD] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_member_update(struct discord *client,
                                   discord_ev_guild_member_update callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_MEMBER_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_member_remove(struct discord *client,
                                   discord_ev_guild_member_remove callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_MEMBER_REMOVE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_ban_add(struct discord *client,
                             discord_ev_guild_ban_add callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_BAN_ADD] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void
discord_set_on_guild_ban_remove(struct discord *client,
                                discord_ev_guild_ban_remove callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_BAN_REMOVE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void
discord_set_on_application_command_create(
    struct discord *client, discord_ev_application_command callback)
{
    client->gw.cbs[DISCORD_EV_APPLICATION_COMMAND_CREATE] =
        (discord_ev)callback;
}

void
discord_set_on_application_command_update(
    struct discord *client, discord_ev_application_command callback)
{
    client->gw.cbs[DISCORD_EV_APPLICATION_COMMAND_UPDATE] =
        (discord_ev)callback;
}

void
discord_set_on_application_command_delete(
    struct discord *client, discord_ev_application_command callback)
{
    client->gw.cbs[DISCORD_EV_APPLICATION_COMMAND_DELETE] =
        (discord_ev)callback;
}

void
discord_set_on_channel_create(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_CHANNEL_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_update(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_CHANNEL_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_delete(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_CHANNEL_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_pins_update(struct discord *client,
                                   discord_ev_channel_pins_update callback)
{
    client->gw.cbs[DISCORD_EV_CHANNEL_PINS_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_create(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_update(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_delete(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_create(struct discord *client, discord_ev_guild callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_update(struct discord *client, discord_ev_guild callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_delete(struct discord *client, discord_ev_guild callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_message_create(struct discord *client,
                              discord_ev_message callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_update(struct discord *client,
                              discord_ev_message callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete(struct discord *client,
                              discord_ev_message_delete callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete_bulk(struct discord *client,
                                   discord_ev_message_delete_bulk callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_DELETE_BULK] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_reaction_add(struct discord *client,
                                    discord_ev_message_reaction_add callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_REACTION_ADD] = (discord_ev)callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove(
    struct discord *client, discord_ev_message_reaction_remove callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_REACTION_REMOVE] = (discord_ev)callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_all(
    struct discord *client, discord_ev_message_reaction_remove_all callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_REACTION_REMOVE_ALL] =
        (discord_ev)callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_emoji(
    struct discord *client, discord_ev_message_reaction_remove_emoji callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_REACTION_REMOVE_EMOJI] =
        (discord_ev)callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_interaction_create(struct discord *client,
                                  discord_ev_interaction callback)
{
    client->gw.cbs[DISCORD_EV_INTERACTION_CREATE] = (discord_ev)callback;
}

void
discord_set_on_voice_state_update(struct discord *client,
                                  discord_ev_voice_state_update callback)
{
    client->gw.cbs[DISCORD_EV_VOICE_STATE_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_on_voice_server_update(struct discord *client,
                                   discord_ev_voice_server_update callback)
{
    client->gw.cbs[DISCORD_EV_VOICE_SERVER_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

/* deprecated, use discord_update_presence() instead */
void
discord_set_presence(struct discord *client,
                     struct discord_presence_update *presence)
{
    discord_gateway_send_presence_update(&client->gw, presence);
}

void
discord_request_guild_members(struct discord *client,
                              struct discord_request_guild_members *request)
{
    discord_gateway_send_request_guild_members(&client->gw, request);
}

void
discord_update_voice_state(struct discord *client,
                           struct discord_update_voice_state *update)
{
    discord_gateway_send_update_voice_state(&client->gw, update);
}

void
discord_update_presence(struct discord *client,
                        struct discord_presence_update *presence)
{
    discord_gateway_send_presence_update(&client->gw, presence);
}

int
discord_get_ping(struct discord *client)
{
    int ping_ms;

    pthread_rwlock_rdlock(&client->gw.timer->rwlock);
    ping_ms = client->gw.timer->ping_ms;
    pthread_rwlock_unlock(&client->gw.timer->rwlock);

    return ping_ms;
}

uint64_t
discord_timestamp(struct discord *client)
{
    (void)client;
    return cog_timestamp_ms();
}
uint64_t
discord_timestamp_us(struct discord *client)
{
    (void)client;
    return cog_timestamp_us();
}

struct logconf *
discord_get_logconf(struct discord *client)
{
    return &client->conf;
}

struct io_poller *
discord_get_io_poller(struct discord *client)
{
    return client->io_poller;
}

struct ccord_szbuf_readonly
discord_config_get_field(struct discord *client,
                         char *const path[],
                         unsigned depth)
{
    struct logconf_field field = logconf_get_field(&client->conf, path, depth);

    return (struct ccord_szbuf_readonly){ field.start, field.size };
}

void
__discord_claim(struct discord *client, const void *param)
{
    ASSERT_S(discord_refcounter_claim(&client->refcounter, (void *)param),
             "Failed attempt to claim non-Concord function parameter");
}

void
discord_unclaim(struct discord *client, const void *param)
{
    ASSERT_S(discord_refcounter_unclaim(&client->refcounter, (void *)param),
             "Failed attempt to unclaim non-Concord function parameter");
}
