#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isgraph() */
#include <errno.h>

#include "discord.h"
#include "discord-internal.h"
#include "cog-utils.h"

static void
_discord_init(struct discord *new_client)
{
    ccord_global_init();
    discord_timers_init(new_client);
    new_client->io_poller = io_poller_create();
    discord_adapter_init(&new_client->adapter, &new_client->conf,
                         &new_client->token);
    discord_gateway_init(&new_client->gw, &new_client->conf,
                         &new_client->token);
#ifdef HAS_DISCORD_VOICE
    discord_voice_connections_init(new_client);
#endif /* HAS_DISCORD_VOICE */

    /* fetch the client user structure */
    if (new_client->token.size) {
        struct discord_ret_user ret = { 0 };
        CCORDcode code;

        ret.sync = &new_client->self;
        code = discord_get_current_user(new_client, &ret);
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

    new_client->token.start = (char *)token;
    new_client->token.size = token ? cog_str_bounds_check(token, 128) : 0;

    _discord_init(new_client);

    return new_client;
}

struct discord *
discord_config_init(const char config_file[])
{
    struct discord *new_client;
    char *path[] = { "discord", "token" };
    FILE *fp;

    fp = fopen(config_file, "rb");
    VASSERT_S(fp != NULL, "Couldn't open '%s': %s", config_file,
              strerror(errno));

    new_client = calloc(1, sizeof *new_client);
    logconf_setup(&new_client->conf, "DISCORD", fp);

    fclose(fp);

    new_client->token = logconf_get_field(&new_client->conf, path,
                                          sizeof(path) / sizeof *path);
    if (!strncmp("YOUR-BOT-TOKEN", new_client->token.start,
                 new_client->token.size))
    {
        memset(&new_client->token, 0, sizeof(new_client->token));
    }

    _discord_init(new_client);

    return new_client;
}

struct discord *
discord_clone(const struct discord *orig_client)
{
    struct discord *clone_client = malloc(sizeof(struct discord));

    memcpy(clone_client, orig_client, sizeof(struct discord));
    clone_client->is_original = false;

    return clone_client;
}

void
discord_cleanup(struct discord *client)
{
    if (client->is_original) {
        discord_timers_cleanup(client);
        logconf_cleanup(&client->conf);
        discord_adapter_cleanup(&client->adapter);
        discord_gateway_cleanup(&client->gw);
        discord_user_cleanup(&client->self);
        io_poller_destroy(client->io_poller);
#ifdef HAS_DISCORD_VOICE
        discord_voice_connections_cleanup(client);
#endif /* HAS_DISCORD_VOICE */
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
discord_set_prefix(struct discord *client, char *prefix)
{
    if (!prefix || !*prefix) return;

    if (client->gw.cmds.prefix.start) free(client->gw.cmds.prefix.start);

    client->gw.cmds.prefix.size =
        cog_strndup(prefix, strlen(prefix), &client->gw.cmds.prefix.start);
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
    const size_t cmd_len = command ? strlen(command) : 0;
    size_t i;

    /* fallback callback if prefix is detected, but command isn't specified */
    if (client->gw.cmds.prefix.size && !cmd_len) {
        client->gw.cmds.fallback.cb = callback;
        return;
    }

    /* if command is already set then modify it */
    for (i = 0; i < client->gw.cmds.amt; i++) {
        if (cmd_len == client->gw.cmds.pool[i].size
            && 0 == strcmp(command, client->gw.cmds.pool[i].start))
        {
            goto _modify;
        }
    }

    if (i == client->gw.cmds.cap) {
        size_t cap = 8;
        void *tmp;

        while (cap <= i)
            cap <<= 1;

        tmp =
            realloc(client->gw.cmds.pool, cap * sizeof(*client->gw.cmds.pool));
        if (!tmp) return;

        client->gw.cmds.pool = tmp;
        client->gw.cmds.cap = cap;
    }

    ++client->gw.cmds.amt;
    client->gw.cmds.pool[i].size =
        cog_strndup(command, cmd_len, &client->gw.cmds.pool[i].start);

_modify:
    client->gw.cmds.pool[i].cb = callback;

    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_commands(struct discord *client,
                        discord_ev_message callback,
                        ...)
{
    char *command = NULL;
    va_list commands;

    va_start(commands, callback);

    command = va_arg(commands, char *);
    while (command != NULL) {
        discord_set_on_command(client, command, callback);
        command = va_arg(commands, char *);
    }

    va_end(commands);
}

void
discord_set_event_scheduler(struct discord *client,
                            discord_ev_scheduler callback)
{
    client->gw.cmds.scheduler = callback;
}


static void
discord_wake_timer_cb(struct discord *client, struct discord_timer *timer) {
    if (~timer->flags & DISCORD_TIMER_CANCELED && client->wakeup_timer.cb)
        client->wakeup_timer.cb(client);
}

void
discord_set_next_wakeup(struct discord *client, int64_t delay)
{
    unsigned id = discord_internal_timer_ctl(client, 
        &(struct discord_timer) {
            .id = client->wakeup_timer.id,
            .cb = discord_wake_timer_cb,
            .delay = delay,
        });
    client->wakeup_timer.id = id;
}

void
discord_set_on_wakeup(struct discord *client, discord_ev_idle callback)
{
    client->wakeup_timer.cb = callback;
    if (client->wakeup_timer.id) {
        discord_internal_timer_ctl(client, 
            &(struct discord_timer) {
                .id = client->wakeup_timer.id,
                .cb = discord_wake_timer_cb,
                .delay = -1,
            });
    }
}

void
discord_set_on_idle(struct discord *client, discord_ev_idle callback)
{
    client->on_idle = callback;
}

void
discord_set_on_cycle(struct discord *client, discord_ev_idle callback)
{
    client->on_cycle = callback;
}

void
discord_set_on_ready(struct discord *client, discord_ev_idle callback)
{
    client->gw.cmds.cbs.on_ready = callback;
}

CCORDcode
discord_run(struct discord *client)
{
    int64_t next_run, now;
    CCORDcode code;

    while (1) {
        if (CCORD_OK != (code = discord_gateway_start(&client->gw))) break;

        next_run = (int64_t)cog_timestamp_ms();
        while (1) {
            int poll_time = 0, poll_result;

            now = (int64_t)cog_timestamp_ms();

            if (!client->on_idle) 
                poll_time = now < next_run ? (int)(next_run - now) : 0;

            struct discord_timers *const timers[] =
                { &client->timers.internal, &client->timers.user };
            for (unsigned i = 0; i < sizeof timers / sizeof *timers; i++) {
                int64_t trigger_us, trigger_ms;
                if (priority_queue_peek(timers[i]->q, &trigger_us, NULL)) {
                    trigger_ms = trigger_us / 1000;
                    if (trigger_ms >= 0) {
                        if (trigger_ms <= now) {
                            poll_time = 0;
                        } else if (trigger_ms - now < poll_time) {
                            poll_time = (int)(trigger_ms - now);
                        }
                    }
                }
            }
            
            poll_result = io_poller_poll(client->io_poller, poll_time);
            if (-1 == poll_result) {
                /* TODO: handle poll error here */
            }
            else if (0 == poll_result) {
                if (ccord_has_sigint != 0) discord_shutdown(client);
                if (client->on_idle) client->on_idle(client);
            }

            if (client->on_cycle) client->on_cycle(client);

            if (CCORD_OK != (code = io_poller_perform(client->io_poller)))
                break;

            for (unsigned i = 0; i < sizeof timers / sizeof *timers; i++)
                discord_timers_run(client, timers[i]);

            if (next_run <= now) {
                if (CCORD_OK != (code = discord_gateway_perform(&client->gw)))
                    break;
                if (CCORD_OK
                    != (code = discord_adapter_perform(&client->adapter)))
                    break;

                /* enforce a min 1 sec delay between runs */
                next_run = now + 1000;
            }
        }

        /* stop all pending requests in case of connection shutdown */
        if (true == discord_gateway_end(&client->gw)) {
            discord_adapter_stop_all(&client->adapter);
            break;
        }
    }

    return code;
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
discord_set_on_guild_role_create(struct discord *client,
                                 discord_ev_guild_role callback)
{
    client->gw.cmds.cbs.on_guild_role_create = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_role_update(struct discord *client,
                                 discord_ev_guild_role callback)
{
    client->gw.cmds.cbs.on_guild_role_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_role_delete(struct discord *client,
                                 discord_ev_guild_role_delete callback)
{
    client->gw.cmds.cbs.on_guild_role_delete = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_member_add(struct discord *client,
                                discord_ev_guild_member callback)
{
    client->gw.cmds.cbs.on_guild_member_add = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_member_update(struct discord *client,
                                   discord_ev_guild_member callback)
{
    client->gw.cmds.cbs.on_guild_member_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_member_remove(struct discord *client,
                                   discord_ev_guild_member_remove callback)
{
    client->gw.cmds.cbs.on_guild_member_remove = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_ban_add(struct discord *client,
                             discord_ev_guild_ban callback)
{
    client->gw.cmds.cbs.on_guild_ban_add = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void
discord_set_on_guild_ban_remove(struct discord *client,
                                discord_ev_guild_ban callback)
{
    client->gw.cmds.cbs.on_guild_ban_remove = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void
discord_set_on_application_command_create(
    struct discord *client, discord_ev_application_command callback)
{
    client->gw.cmds.cbs.on_application_command_create = callback;
}

void
discord_set_on_application_command_update(
    struct discord *client, discord_ev_application_command callback)
{
    client->gw.cmds.cbs.on_application_command_update = callback;
}

void
discord_set_on_application_command_delete(
    struct discord *client, discord_ev_application_command callback)
{
    client->gw.cmds.cbs.on_application_command_delete = callback;
}

void
discord_set_on_channel_create(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cmds.cbs.on_channel_create = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_update(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cmds.cbs.on_channel_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_delete(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cmds.cbs.on_channel_delete = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_pins_update(struct discord *client,
                                   discord_ev_channel_pins_update callback)
{
    client->gw.cmds.cbs.on_channel_pins_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_create(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cmds.cbs.on_thread_create = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_update(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cmds.cbs.on_thread_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_delete(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cmds.cbs.on_thread_delete = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_create(struct discord *client, discord_ev_guild callback)
{
    client->gw.cmds.cbs.on_guild_create = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_update(struct discord *client, discord_ev_guild callback)
{
    client->gw.cmds.cbs.on_guild_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_delete(struct discord *client,
                            discord_ev_guild_delete callback)
{
    client->gw.cmds.cbs.on_guild_delete = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_message_create(struct discord *client,
                              discord_ev_message callback)
{
    client->gw.cmds.cbs.on_message_create = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_update(struct discord *client,
                              discord_ev_message callback)
{
    client->gw.cmds.cbs.on_message_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete(struct discord *client,
                              discord_ev_message_delete callback)
{
    client->gw.cmds.cbs.on_message_delete = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete_bulk(struct discord *client,
                                   discord_ev_message_delete_bulk callback)
{
    client->gw.cmds.cbs.on_message_delete_bulk = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_reaction_add(struct discord *client,
                                    discord_ev_message_reaction_add callback)
{
    client->gw.cmds.cbs.on_message_reaction_add = callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove(
    struct discord *client, discord_ev_message_reaction_remove callback)
{
    client->gw.cmds.cbs.on_message_reaction_remove = callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_all(
    struct discord *client, discord_ev_message_reaction_remove_all callback)
{
    client->gw.cmds.cbs.on_message_reaction_remove_all = callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_emoji(
    struct discord *client, discord_ev_message_reaction_remove_emoji callback)
{
    client->gw.cmds.cbs.on_message_reaction_remove_emoji = callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_interaction_create(struct discord *client,
                                  discord_ev_interaction callback)
{
    client->gw.cmds.cbs.on_interaction_create = callback;
}

void
discord_set_on_voice_state_update(struct discord *client,
                                  discord_ev_voice_state_update callback)
{
    client->gw.cmds.cbs.on_voice_state_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_on_voice_server_update(struct discord *client,
                                   discord_ev_voice_server_update callback)
{
    client->gw.cmds.cbs.on_voice_server_update = callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_presence(struct discord *client,
                     struct discord_presence_update *presence)
{
    memcpy(client->gw.id.presence, presence, sizeof *presence);
    discord_gateway_send_presence_update(&client->gw);
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
