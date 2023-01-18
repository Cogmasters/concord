#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-worker.h"
#include "cog-utils.h"

static size_t
_parse_env(char **dest, char *end, const char **src)
{
    const char *p = ++*src;
    if ('{' != *p++) return 0;
    const char *begin = p;
    while (*p != '}')
        if (!*p++) return 0;

    char env_name[0x1000];
    if ((int)sizeof env_name <= snprintf(env_name, sizeof env_name, "%.*s",
                                         (int)(p - begin), begin))
        return 0;
    char *env_str = getenv(env_name);
    if (!env_str) return 0;
    int env_len = (int)strlen(env_str);
    if (end - *dest < env_len) return 0;
    sprintf(*dest, "%s", env_str);
    *dest += env_len;
    *src = p + 1;
    return (size_t)env_len;
}

static bool
_parse_init_string(char *dest, size_t dest_size, const char *src)
{
    while (*src) {
        if (*src == '$') {
            size_t len = _parse_env(&dest, dest + dest_size, &src);
            if (!len) return false;
            dest_size -= len;
        }
        else {
            *dest++ = *src++;
            dest_size--;
        }
        if (!dest_size) return false;
    }
    *dest = 0;
    return true;
}

static void
_discord_init(struct discord *new_client)
{
    ccord_global_init();
    new_client->io_poller = io_poller_create();
    discord_timers_init(&new_client->timers.internal, new_client->io_poller);
    discord_timers_init(&new_client->timers.user, new_client->io_poller);

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
    char parsed_token[4096];
    if (!_parse_init_string(parsed_token, sizeof parsed_token, token))
        return NULL;
    new_client = calloc(1, sizeof *new_client);
    logconf_setup(&new_client->conf, "DISCORD", NULL);
    /* silence terminal input by default */
    logconf_set_quiet(&new_client->conf, true);
    if (token && *token)
        cog_strndup(parsed_token, strlen(parsed_token), &new_client->token);

    _discord_init(new_client);

    return new_client;
}

struct discord *
discord_config_init(const char config_file[])
{
    struct ccord_szbuf_readonly field;
    struct discord *new_client;
    FILE *fp;
    char parsed_config_file[4096];
    if (!_parse_init_string(parsed_config_file, sizeof parsed_config_file,
                            config_file))
        return NULL;
    fp = fopen(parsed_config_file, "rb");
    VASSERT_S(fp != NULL, "Couldn't open '%s': %s", parsed_config_file,
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
        if (client->cache.cleanup) client->cache.cleanup(client);
        discord_refcounter_cleanup(&client->refcounter);
        discord_timers_cleanup(client, &client->timers.user);
        discord_timers_cleanup(client, &client->timers.internal);
        io_poller_destroy(client->io_poller);
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

const struct discord_user *
discord_get_self(struct discord *client)
{
    return &client->self;
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
__discord_claim(struct discord *client, const void *data)
{
    CCORDcode code = discord_refcounter_claim(&client->refcounter, data);
    VASSERT_S(code == CCORD_OK, "Failed attempt to claim resource (code %d)",
              code);
}

void
discord_unclaim(struct discord *client, const void *data)
{
    CCORDcode code =
        discord_refcounter_unclaim(&client->refcounter, (void *)data);
    VASSERT_S(code == CCORD_OK, "Failed attempt to unclaim resource (code %d)",
              code);
}
