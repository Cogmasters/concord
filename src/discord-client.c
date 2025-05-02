#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-worker.h"
#include "cog-utils.h"

static size_t
_discord_envs_parse(char **dest, char *end, const char **src)
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
_discord_envs_expand(char *dest, size_t dest_size, const char *src)
{
    if (!src || !*src) {
        *dest = 0;
        return true;
    }

    while (*src) {
        if (*src == '$') {
            size_t len = _discord_envs_parse(&dest, dest + dest_size, &src);
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
_discord_on_shutdown(struct io_poller *io,
                     enum io_poller_events events,
                     void *data)
{
    (void)io;
    (void)events;
    discord_shutdown(data);
}

static CCORDcode
_discord_init(struct discord *client)
{
    CCORDcode code;

    if ((code = ccord_global_init()) != CCORD_OK) {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize global resources: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return code;
    }
    client->pid = (unsigned)getpid();
    client->is_original = true;
    if (!(client->io_poller = io_poller_create())) {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize IO poller: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return CCORD_INTERNAL_ERROR;
    }
    if ((code =
             discord_timers_init(&client->timers.internal, client->io_poller)))
    {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize internal timers: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return code;
    }
    if ((code = discord_timers_init(&client->timers.user, client->io_poller))
        != CCORD_OK)
    {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize user timers: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return code;
    }
    if (!io_poller_socket_add(client->io_poller,
                              client->shutdown_fd = discord_dup_shutdown_fd(),
                              IO_POLLER_IN, _discord_on_shutdown, client))
    {
        logmod_log(FATAL, client->logger,
                   "Couldn't add shutdown fd to IO poller");
        return CCORD_INTERNAL_ERROR;
    }

    if (!(client->workers = calloc(1, sizeof *client->workers))) {
        logmod_log(FATAL, client->logger,
                   "Couldn't allocate memory for Client's workers");
        return CCORD_OUT_OF_MEMORY;
    }
    if (pthread_mutex_init(&client->workers->lock, NULL)) {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize Client's mutex");
        return CCORD_ERRNO;
    }
    if (pthread_cond_init(&client->workers->cond, NULL)) {
        logmod_log(FATAL, client->logger, "Couldn't initialize Client's cond");
        return CCORD_ERRNO;
    }
    if ((code = discord_refcounter_init(&client->refcounter))) {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize Client's refcounter: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return code;
    }
    if ((code = discord_message_commands_init(&client->commands))) {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize Client's commands: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return code;
    }
    if ((code = discord_rest_init(&client->rest, client->config.token))) {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize REST API: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return code;
    }
    if ((code = discord_gateway_init(&client->gw, client->config.token))) {
        logmod_log(FATAL, client->logger,
                   "Couldn't initialize Gateway API: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return code;
    }

    if (client->config.token) {
        if ((code = discord_get_current_user(client,
                                             &(struct discord_ret_user){
                                                 .sync = &client->self,
                                             }))
            != CCORD_OK)
        {
            logmod_log(ERROR, client->logger,
                       "Couldn't fetch client's user object: %s (code %d)",
                       discord_strerror(code, NULL), code);
            return code;
        }
    }
    return CCORD_OK;
}

struct discord *
discord_init(const char token[])
{
    struct discord *client;
    char parsed_token[0x1000];
    CCORDcode code;

    if (!(client = calloc(1, sizeof *client))) {
        logmod_log(FATAL, NULL, "Couldn't allocate memory for client");
        return NULL;
    }
    if (logmod_init(&client->logmod, "CONCORD", client->table,
                    sizeof(client->table) / sizeof *client->table)
        != LOGMOD_OK)
    {
        logmod_log(FATAL, NULL, "Couldn't initialize logging module");
        return discord_cleanup(client), NULL;
    }
    if (!(client->logger = logmod_get_logger(&client->logmod, "CLIENT"))) {
        logmod_log(FATAL, NULL, "Couldn't create logger for client");
        return discord_cleanup(client), NULL;
    }
    logmod_logger_set_quiet(client->logger, 1); /* silence console default */

    if (!_discord_envs_expand(parsed_token, sizeof parsed_token, token)) {
        logmod_log(FATAL, client->logger, "Couldn't parse token: %s", token);
        return discord_cleanup(client), NULL;
    }

    if (*parsed_token != '\0'
        && !cog_strndup(parsed_token, strlen(parsed_token),
                        &client->config.token))
    {
        logmod_log(FATAL, client->logger, "Couldn't copy token: %s",
                   parsed_token);
        return discord_cleanup(client), NULL;
    }

    if ((code = _discord_init(client)) != CCORD_OK) {
        logmod_log(FATAL, client->logger, "Couldn't initialize client: %s",
                   discord_strerror(code, NULL));
        return discord_cleanup(client), NULL;
    }
    return client;
}

static void
_discord_config_load_disabled_modules(struct discord_config *config)
{
    jsmn_parser parser;
    jsmntok_t tokens[256];

    jsmn_init(&parser);
    if (0 < jsmn_parse(&parser, config->file.start, config->file.size, tokens,
                       sizeof(tokens) / sizeof *tokens))
    {
        jsmnf_loader loader;
        jsmnf_pair pairs[256];

        jsmnf_init(&loader);
        if (0 < jsmnf_load(&loader, config->file.start, tokens, parser.toknext,
                           pairs, sizeof(pairs) / sizeof *pairs))
        {
            const char *file = config->file.start;
            jsmnf_pair *f;

            if ((f = jsmnf_find(pairs, file, "log", 3))) {
                jsmnf_pair *f1;

                if ((f1 = jsmnf_find(f, file, "disable", 7)) && f1->size >= 0)
                {
                    const size_t size = (size_t)f1->size;
                    config->disable.ids = malloc(size * sizeof(char *));
                    for (size_t i = 0; i < size; ++i) {
                        jsmnf_pair *f2 = f1->fields + i;
                        if (f2->type == JSMN_STRING) {
                            const size_t length = f2->v.len + 1;
                            char *id = malloc(length);
                            memcpy(id, file + f2->v.pos, f2->v.len);
                            id[f2->v.len] = '\0';
                            config->disable.ids[i] = id;
                        }
                    }
                    config->disable.size = size;
                }
            }
        }
    }
}

static void _discord_config_cleanup(struct discord_config *config);

static CCORDcode
_discord_config_load(struct discord_config *config, const char config_file[])
{
    struct discord *client = CLIENT(config, config);
    struct ccord_szbuf_readonly field;
    char parsed_config_file[0x1000];

    if (!_discord_envs_expand(parsed_config_file, sizeof parsed_config_file,
                              config_file))
    {
        logmod_log(FATAL, client->logger, "Couldn't parse config file: %s",
                   config_file);
        return CCORD_BAD_DECODE;
    }
    if (!(config->file.start =
              cog_load_whole_file(parsed_config_file, &config->file.size)))
    {
        logmod_log(FATAL, client->logger, "Couldn't load '%s': %s",
                   parsed_config_file, strerror(errno));
        return _discord_config_cleanup(config), CCORD_ERRNO;
    }

    if ((field = discord_config_get_field(client, (char *[1]){ "token" }, 1)),
        0 == strncmp("YOUR-BOT-TOKEN", field.start, field.size))
    {
        logmod_log(FATAL, client->logger, "Bad token at '%s'",
                   parsed_config_file);
        return _discord_config_cleanup(config), CCORD_BAD_DECODE;
    }
    if (field.size && !cog_strndup(field.start, field.size, &config->token)) {
        logmod_log(FATAL, client->logger, "Couldn't copy token: %.*s",
                   (int)field.size, field.start);
        return _discord_config_cleanup(config), CCORD_BAD_DECODE;
    }

    if ((field = discord_config_get_field(client,
                                          (char *[2]){ "log", "level" }, 2)),
        field.size)
    {
        char label[64];
        snprintf(label, sizeof(label), "%.*s", (int)field.size, field.start);
        for (char *it = label; *it; ++it) {
            *it = (char)toupper((int)*it);
        }
        if ((config->level = logmod_logger_get_level(client->logger, label))
            < 0)
        {
            logmod_log(ERROR, client->logger, "Invalid logging level: %s",
                       label);
            config->level = LOGMOD_LEVEL_TRACE;
        }
    }
    if ((field = discord_config_get_field(client,
                                          (char *[2]){ "log", "quiet" }, 2)),
        field.size)
    {
        config->quiet = 't' == field.start[0];
    }
    if ((field = discord_config_get_field(client,
                                          (char *[2]){ "log", "color" }, 2)),
        field.size)
    {
        config->color = 't' == field.start[0];
    }
    if ((field = discord_config_get_field(
             client, (char *[2]){ "log", "overwrite" }, 2)),
        field.size)
    {
        config->overwrite = 't' == field.start[0];
    }
    if ((field = discord_config_get_field(client,
                                          (char *[2]){ "log", "trace" }, 2)),
        field.size)
    {
        char *filename;
        if (!cog_strndup(field.start, field.size, &filename)) {
            logmod_log(FATAL, client->logger, "Couldn't copy trace file");
            return _discord_config_cleanup(config), CCORD_BAD_DECODE;
        }
        if (!(config->trace =
                  fopen(filename, config->overwrite ? "w+" : "a+")))
        {
            logmod_log(FATAL, client->logger, "Couldn't open trace file: %s",
                       filename);
            free(filename);
            return _discord_config_cleanup(config), CCORD_ERRNO;
        }
        free(filename);
    }
    if ((field = discord_config_get_field(client, (char *[2]){ "log", "http" },
                                          2)),
        field.size)
    {
        char *filename;
        if (!cog_strndup(field.start, field.size, &filename)) {
            logmod_log(FATAL, client->logger, "Couldn't copy http log file");
            return _discord_config_cleanup(config), CCORD_BAD_DECODE;
        }
        if (!(config->http = fopen(filename, config->overwrite ? "w+" : "a+")))
        {
            return _discord_config_cleanup(config), CCORD_ERRNO;
        }
        free(filename);
    }
    _discord_config_load_disabled_modules(config);
    for (size_t i = 0; i < config->disable.size; ++i) {
        logmod_toggle_logger(&client->logmod, config->disable.ids[i]);
        logmod_log(INFO, client->logger, "Disabled logging for '%s'",
                   config->disable.ids[i]);
    }
    if (logmod_set_options(&client->logmod,
                           (struct logmod_options){
                               .logfile = client->config.trace,
                               .quiet = client->config.quiet,
                               .color = client->config.color,
                               .hide_context_id = 0,
                               .show_application_id = 1,
                               .level = client->config.level,
                           })
        < 0)
    {
        logmod_log(ERROR, client->logger, "Couldn't set logger options");
    }
    return CCORD_OK;
}

void
_discord_config_cleanup(struct discord_config *config)
{
    if (config->token) {
        free(config->token);
    }
    if (config->trace) {
        fclose(config->trace);
    }
    if (config->http) {
        fclose(config->http);
    }
    if (config->disable.ids) {
        for (size_t i = 0; i < config->disable.size; ++i)
            free(config->disable.ids[i]);
        free(config->disable.ids);
    }
    if (config->file.start) {
        free(config->file.start);
    }
    memset(config, 0, sizeof *config);
}

struct discord *
discord_config_init(const char config_file[])
{
    struct discord *client;
    CCORDcode code;

    if (!(client = calloc(1, sizeof *client))) {
        logmod_log(FATAL, NULL, "Couldn't allocate memory for client");
        return NULL;
    }
    if (logmod_init(&client->logmod, "CONCORD", client->table,
                    sizeof(client->table) / sizeof *client->table)
        != LOGMOD_OK)
    {
        logmod_log(FATAL, NULL, "Couldn't initialize logging module");
        return discord_cleanup(client), NULL;
    }
    if (!(client->logger = logmod_get_logger(&client->logmod, "CLIENT"))) {
        logmod_log(FATAL, NULL, "Couldn't create logger for client");
        return discord_cleanup(client), NULL;
    }
    if (_discord_config_load(&client->config, config_file) != CCORD_OK) {
        logmod_log(FATAL, client->logger, "Couldn't load config file: %s",
                   config_file);
        return discord_cleanup(client), NULL;
    }
    if ((code = _discord_init(client)) != CCORD_OK) {
        logmod_log(FATAL, client->logger, "Couldn't initialize client: %s",
                   discord_strerror(code, NULL));
        return discord_cleanup(client), NULL;
    }
    return client;
}

static CCORDcode
_discord_clone_gateway(struct discord_gateway *clone,
                       const struct discord_gateway *orig)
{
    const size_t n = orig->payload.json.npairs
                     - (size_t)(orig->payload.data - orig->payload.json.pairs);

    if (!(clone->payload.data = malloc(n * sizeof *orig->payload.json.pairs)))
    {
        logmod_log(FATAL, clone->logger,
                   "Couldn't allocate memory for gateway payload");
        return CCORD_ERRNO;
    }
    memcpy(clone->payload.data, orig->payload.data,
           n * sizeof *orig->payload.json.pairs);
    if (!(clone->payload.json.size =
              cog_strndup(orig->payload.json.start, orig->payload.json.size,
                          &clone->payload.json.start)))
    {
        logmod_log(FATAL, clone->logger,
                   "Couldn't copy gateway payload json string");
        return free(clone->payload.data), CCORD_ERRNO;
    }
    return CCORD_OK;
}

struct discord *
discord_clone(const struct discord *orig)
{
    struct discord *clone;

    if (!(clone = malloc(sizeof(struct discord)))) {
        logmod_log(FATAL, orig->logger, "Couldn't allocate memory for client");
        return NULL;
    }
    memcpy(clone, orig, sizeof(struct discord));
    clone->is_original = false;
    if (_discord_clone_gateway(&clone->gw, &orig->gw)) {
        logmod_log(FATAL, clone->logger,
                   "Couldn't clone gateway payload data");
        return free(clone), NULL;
    }
    return clone;
}

static void
_discord_clone_gateway_cleanup(struct discord_gateway *clone)
{
    if (clone->payload.data) free(clone->payload.data);
    if (clone->payload.json.start) free(clone->payload.json.start);
}

void
discord_cleanup(struct discord *client)
{
    if (!client->is_original) {
        _discord_clone_gateway_cleanup(&client->gw);
        free(client);
        return;
    }
    close(client->shutdown_fd);
    if (client->workers) {
        discord_worker_join(client);
        pthread_mutex_destroy(&client->workers->lock);
        pthread_cond_destroy(&client->workers->cond);
        free(client->workers);
    }
    discord_rest_cleanup(&client->rest);
    discord_gateway_cleanup(&client->gw);
    discord_message_commands_cleanup(&client->commands);
    discord_user_cleanup(&client->self);
    if (client->cache.cleanup) client->cache.cleanup(client);
    discord_refcounter_cleanup(&client->refcounter);
    discord_timers_cleanup(client, &client->timers.user);
    discord_timers_cleanup(client, &client->timers.internal);
    logmod_cleanup(&client->logmod);
    _discord_config_cleanup(&client->config);
    if (client->io_poller) {
        io_poller_destroy(client->io_poller);
    }
    ccord_global_cleanup();
}

#define CASE_RETURN_STR(event)                                                \
    case event:                                                               \
        return #event

static const char *
_ccord_code_as_string(CCORDcode code)
{
    switch (code) {
        CASE_RETURN_STR(CCORD_OK);
        CASE_RETURN_STR(CCORD_HTTP_CODE);
        CASE_RETURN_STR(CCORD_CURL_NO_RESPONSE);
        CASE_RETURN_STR(CCORD_UNUSUAL_HTTP_CODE);
        CASE_RETURN_STR(CCORD_BAD_PARAMETER);
        CASE_RETURN_STR(CCORD_BAD_JSON);
        CASE_RETURN_STR(CCORD_CURLE_INTERNAL);
        CASE_RETURN_STR(CCORD_CURLM_INTERNAL);
        CASE_RETURN_STR(CCORD_GLOBAL_INIT);
        CASE_RETURN_STR(CCORD_RESOURCE_OWNERSHIP);
        CASE_RETURN_STR(CCORD_RESOURCE_UNAVAILABLE);
        CASE_RETURN_STR(CCORD_FULL_WORKER);
        CASE_RETURN_STR(CCORD_MALFORMED_PAYLOAD);
        CASE_RETURN_STR(CCORD_CURL_WEBSOCKETS_MISSING);
        CASE_RETURN_STR(CCORD_CURL_OUTDATED_VERSION);
    default:
        return "Unknown: Code received doesn't match any description";
    }
}

const char *
discord_code_as_string(CCORDcode code)
{
    switch (code) {
        CASE_RETURN_STR(CCORD_PENDING);
        CASE_RETURN_STR(CCORD_DISCORD_JSON_CODE);
        CASE_RETURN_STR(CCORD_DISCORD_BAD_AUTH);
        CASE_RETURN_STR(CCORD_DISCORD_RATELIMIT);
        CASE_RETURN_STR(CCORD_DISCORD_CONNECTION);
    default:
        return _ccord_code_as_string(code);
    }
}

#undef CASE_RETURN_STR

static const char *
_ccord_strerror(CCORDcode code)
{
    switch (code) {
    case CCORD_OK:
        return "Success: The request was a success";
    case CCORD_HTTP_CODE:
        return "Failure: The request was a failure";
    case CCORD_CURL_NO_RESPONSE:
        return "Failure: No response came through from libcurl";
    case CCORD_UNUSUAL_HTTP_CODE:
        return "Failure: The request was a failure";
    case CCORD_BAD_PARAMETER:
        return "Failure: Bad value for parameter";
    case CCORD_BAD_JSON:
        return "Failure: Internal failure when encoding or decoding JSON";
    case CCORD_CURLE_INTERNAL:
        return "Failure: Libcurl's internal error (CURLE)";
    case CCORD_CURLM_INTERNAL:
        return "Failure: Libcurl's internal error (CURLM)";
    case CCORD_GLOBAL_INIT:
        return "Failure: Attempt to initialize globals more than once";
    case CCORD_RESOURCE_OWNERSHIP:
        return "Failure: Claimed resource can't be cleaned up automatically";
    case CCORD_RESOURCE_UNAVAILABLE:
        return "Failure: Can't perform action on unavailable resource";
    case CCORD_FULL_WORKER:
        return "Failure: Couldn't enqueue worker thread (queue is full)";
    case CCORD_MALFORMED_PAYLOAD:
        return "Failure: Couldn't create request payload";
    case CCORD_CURL_WEBSOCKETS_MISSING:
        return "Failure: Libcurl has been compiled without the "
               "--enable-websockets flag";
    case CCORD_CURL_OUTDATED_VERSION:
        return "Failure: Libcurl need to be updated to 8.7.1 or greater";
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
    case CCORD_PENDING:
        return "Discord Pending: Request has been added enqueued and will be "
               "performed asynchronously";
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

struct logmod *
discord_get_logmod(struct discord *client)
{
    return &client->logmod;
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
    static const size_t num_tokens = 256;
    const struct ccord_szbuf *file = &client->config.file;
    struct ccord_szbuf field = { 0 };

    if (file->size) {
        jsmn_parser parser;
        jsmntok_t tokens[num_tokens];

        jsmn_init(&parser);
        if (0 < jsmn_parse(&parser, file->start, file->size, tokens,
                           sizeof(tokens) / sizeof *tokens))
        {
            jsmnf_loader loader;
            jsmnf_pair pairs[num_tokens];

            jsmnf_init(&loader);
            if (0 < jsmnf_load(&loader, file->start, tokens, parser.toknext,
                               pairs, sizeof(pairs) / sizeof *pairs))
            {
                jsmnf_pair *f;
                if ((f = jsmnf_find_path(pairs, file->start, path, depth))) {
                    field = (struct ccord_szbuf){ file->start + f->v.pos,
                                                  f->v.len, 1 };
                }
            }
        }
    }
    return (struct ccord_szbuf_readonly){ field.start, field.size };
}

void
__discord_claim(struct discord *client, const void *data)
{
    CCORDcode code = discord_refcounter_claim(&client->refcounter, data);
    if (CCORD_OK != code) {
        logmod_log(ERROR, client->logger,
                   "Failed attempt to claim resource (code %d)", code);
    }
}

void
discord_unclaim(struct discord *client, const void *data)
{
    CCORDcode code =
        discord_refcounter_unclaim(&client->refcounter, (void *)data);
    if (CCORD_OK != code) {
        logmod_log(ERROR, client->logger,
                   "Failed attempt to unclaim resource (code %d)", code);
    }
}
