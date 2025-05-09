#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-worker.h"
#include "concord-once.h"
#include "concord-notifier.h"
#include "cog-utils.h"

static int g_shutdown_pipe[2] = { -1, -1 };

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
_discord_check_curl_compatibility(void)
{
    const curl_version_info_data *curl_info =
        curl_version_info(CURLVERSION_NOW);

    // check version 8.7.1 for websockets support
    if (curl_info->version_num < 0x080701) {
        logmod_log(FATAL, NULL,
                   "libcurl version 8.7.1 or higher required (found %s)",
                   curl_info->version);
        return CCORD_CURL_OUTDATED_VERSION;
    }

    _Bool wss_enabled = 0;
    for (const char *const *proto = curl_info->protocols; *proto; ++proto) {
        if (0 == strncmp(*proto, "wss", 3)) wss_enabled = 1;
    }
    if (!wss_enabled) {
        logmod_log(FATAL, NULL,
                   "libcurl must be compiled with websockets support");
        logmod_log(
            FATAL, NULL,
            "Please recompile libcurl with the --enable-websockets flag");
        return CCORD_CURL_WEBSOCKETS_MISSING;
    }
    return CCORD_OK;
}

static void
_discord_notifier_close(void)
{
    ccord_notifier_close(g_shutdown_pipe);
}

#ifdef CCORD_SIGINTCATCH
/* notifier gracefully on SIGINT received */
static void
_discord_sigint_handler(int signum)
{
    (void)signum;
    static const char err_str[] =
        "\nSIGINT: Disconnecting running concord client(s) ...\n";
    write(STDERR_FILENO, err_str, sizeof(err_str) - 1);
    ccord_notifier_notify(g_shutdown_pipe);
}
#endif /* CCORD_SIGINTCATCH */

static CCORDcode
_discord_notifier_open(long flags)
{
    (void)flags;
    CCORDcode code;

#ifdef CCORD_SIGINTCATCH
    signal(SIGINT, &_discord_sigint_handler);
#endif
    if ((code = ccord_notifier_open(g_shutdown_pipe)) != CCORD_OK) {
        logmod_log(ERROR, NULL,
                   "Couldn't open shutdown notifier pipe: %s (code %d)",
                   ccord_strerror(code), code);
    }
    return code;
}

void
discord_shutdown_all(void)
{
    ccord_notifier_notify(g_shutdown_pipe);
}

bool
discord_shutdown_all_ongoing(void)
{
    return ccord_notifier_is_notifying(g_shutdown_pipe);
}

static CCORDcode
_discord_global_init()
{
    static _Bool g_initialized = false;
    CCORDcode code;

    if (g_initialized) {
        logmod_log(WARN, NULL,
                   "Global resources already initialized, skipping");
        return CCORD_OK;
    }

    if ((code = _discord_check_curl_compatibility()) != CCORD_OK) {
        logmod_log(ERROR, NULL,
                   "libcurl compatibility check failed: %s (code %d)",
                   ccord_strerror(code), code);
        return code;
    }
    if ((code = ccord_once_set_callback((ccord_once_cb)&curl_global_init,
                                        CURL_GLOBAL_ALL))
        != CCORD_OK)
    {
        logmod_log(
            FATAL, NULL,
            "Couldn't set curl's global initialization callback: %s (code %d)",
            discord_strerror(code, NULL), code);
        goto fail_curl_init;
    }
    if ((code = ccord_once_set_callback(
             (ccord_once_cb)&discord_worker_global_init, 0))
        != CCORD_OK)
    {
        logmod_log(FATAL, NULL,
                   "Couldn't set worker thread's global initialization "
                   "callback: %s (code %d)",
                   discord_strerror(code, NULL), code);
        goto fail_discord_worker_init;
    }
    if ((code = ccord_once_set_callback((ccord_once_cb)&_discord_notifier_open,
                                        0))
        != CCORD_OK)
    {
        logmod_log(ERROR, NULL,
                   "Couldn't set notifier's global initialization callback: "
                   "%s (code %d)",
                   discord_strerror(code, NULL), code);
    }
    if ((code = ccord_once(&g_initialized)) != CCORD_OK) {
        logmod_log(FATAL, NULL,
                   "Couldn't initialize global resources: %s (code %d)",
                   discord_strerror(code, NULL), code);
        goto fail_ccord_once;
    }
    return CCORD_OK;

fail_ccord_once:
    ccord_once_cleanup();
fail_discord_worker_init:
    discord_worker_global_cleanup();
fail_curl_init:
    curl_global_cleanup();

    return CCORD_GLOBAL_INIT;
}

static CCORDcode
_discord_init(struct discord *client)
{
    CCORDcode code;

    if (logmod_set_options(&client->logmod,
                           (struct logmod_options){
                               .logfile = client->config.log.trace,
                               .quiet = client->config.log.quiet,
                               .color = client->config.log.color,
                               .hide_context_id = 0,
                               .show_application_id = 1,
                               .level = client->config.log.level,
                           })
        < 0)
    {
        logmod_log(ERROR, client->logger, "Couldn't set logger options");
    }
    if ((code = _discord_global_init()) != CCORD_OK) {
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
                              client->shutdown_fd =
                                  ccord_notifier_listen(g_shutdown_pipe),
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

static bool
_discord_token_is_valid(const char *const token, const size_t len)
{
    if (!token || !*token) return false;

    // 1. Check overall length (generally 59-72 characters)
    if (len < 50 || len > 80) return false;
    // 2. Count the dots (should be exactly 2)
    int dot_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (token[i] == '.') dot_count++;
    }
    if (dot_count != 2) return false;
    // 3. Check for three parts and validate their lengths
    const char *first_dot = strchr(token, '.');
    if (!first_dot) return false;
    const char *second_dot = strchr(first_dot + 1, '.');
    if (!second_dot) return false;
    // Calculate lengths of each part
    const ptrdiff_t first_part_len = first_dot - token,
                    second_part_len = second_dot - (first_dot + 1),
                    third_part_len = (ptrdiff_t)len - (second_dot - token) - 1;
    // Validate part lengths
    return (first_part_len >= 20 && first_part_len <= 40
            && second_part_len >= 5 && second_part_len <= 10
            && third_part_len >= 25 && third_part_len <= 40);
}

struct discord *
discord_from_token(const char token[])
{
    struct discord *client;
    char parsed_token[0x1000];
    CCORDcode code;

    if (!(client = calloc(1, sizeof *client))) {
        logmod_log(FATAL, NULL, "Couldn't allocate memory for client");
        return NULL;
    }
    if (!_discord_envs_expand(parsed_token, sizeof parsed_token, token)) {
        logmod_log(FATAL, client->logger, "Couldn't parse token");
        return discord_cleanup(client), NULL;
    }
    if (!_discord_token_is_valid(parsed_token, strlen(parsed_token))) {
        logmod_log(FATAL, client->logger, "Invalid token format");
        return discord_cleanup(client), NULL;
    }
    if (!cog_strndup(parsed_token, strlen(parsed_token),
                     &client->config.token))
    {
        logmod_log(FATAL, client->logger, "Couldn't copy token");
        return discord_cleanup(client), NULL;
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
    if ((code = _discord_init(client)) != CCORD_OK) {
        logmod_log(FATAL, client->logger, "Couldn't initialize client: %s",
                   discord_strerror(code, NULL));
        return discord_cleanup(client), NULL;
    }
    if (logmod_logger_set_quiet(client->logger, 1) != LOGMOD_OK) {
        logmod_log(ERROR, client->logger, "Couldn't silence console output");
    }
    return client;
}

static void
_discord_config_disable_from_json(struct discord_config *config,
                                  const struct ccord_szbuf *file)
{
    jsmnf_table table[0x100];
    jsmnf_loader loader;

    jsmnf_init(&loader);
    if (0 < jsmnf_load(&loader, file->start, file->size, table,
                       sizeof(table) / sizeof *table))
    {
        const jsmnf_pair *f;
        if ((f = jsmnf_find(loader.root, "log", 3))) {
            const jsmnf_pair *f1;
            if ((f1 = jsmnf_find(f, "disable", 7))
                && f1->v->end - f1->v->start >= 0)
            {
                const size_t size = (size_t)f1->v->size;
                config->log.disable.ids = malloc(size * sizeof(char *));
                for (size_t i = 0; i < size; ++i) {
                    const jsmnf_pair *f2 = f1->fields + i;
                    if (f2->v->type == JSMN_STRING) {
                        const size_t length =
                            (size_t)(f2->v->end - f2->v->start);
                        char *id = malloc(length + 1);
                        memcpy(id, file->start + f2->v->start, length);
                        id[length] = '\0';
                        config->log.disable.ids[i] = id;
                    }
                }
                config->log.disable.size = size;
            }
        }
    }
}

static void _discord_config_cleanup(struct discord_config *config);

static CCORDcode
_discord_config_from_json(struct discord_config *config,
                          const char config_file[])
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
    if (!(client->file.start =
              cog_load_whole_file(parsed_config_file, &client->file.size)))
    {
        logmod_log(FATAL, client->logger, "Couldn't load '%s': %s",
                   parsed_config_file, strerror(errno));
        return _discord_config_cleanup(config), CCORD_ERRNO;
    }

    if ((field = discord_config_get_field(client, (char *[1]){ "token" }, 1)),
        !_discord_token_is_valid(field.start, field.size))
    {
        logmod_log(FATAL, client->logger, "Bad token at '%s'",
                   parsed_config_file);
        return _discord_config_cleanup(config), CCORD_BAD_DECODE;
    }
    if (field.size && !cog_strndup(field.start, field.size, &config->token)) {
        logmod_log(FATAL, client->logger, "Couldn't copy token");
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
        if ((config->log.level =
                 logmod_logger_get_level(client->logger, label))
            < 0)
        {
            logmod_log(ERROR, client->logger, "Invalid logging level: %s",
                       label);
            config->log.level = LOGMOD_LEVEL_TRACE;
        }
    }
    if ((field = discord_config_get_field(client,
                                          (char *[2]){ "log", "quiet" }, 2)),
        field.size)
    {
        config->log.quiet = 't' == field.start[0];
    }
    if ((field = discord_config_get_field(client,
                                          (char *[2]){ "log", "color" }, 2)),
        field.size)
    {
        config->log.color = 't' == field.start[0];
    }
    if ((field = discord_config_get_field(
             client, (char *[2]){ "log", "overwrite" }, 2)),
        field.size)
    {
        config->log.overwrite = 't' == field.start[0];
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
        if (!(config->log.trace =
                  fopen(filename, config->log.overwrite ? "w+" : "a+")))
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
        if (!(config->log.http =
                  fopen(filename, config->log.overwrite ? "w+" : "a+")))
        {
            return _discord_config_cleanup(config), CCORD_ERRNO;
        }
        free(filename);
    }
    if ((field =
             discord_config_get_field(client, (char *[2]){ "log", "ws" }, 2)),
        field.size)
    {
        char *filename;
        if (!cog_strndup(field.start, field.size, &filename)) {
            logmod_log(FATAL, client->logger, "Couldn't copy ws log file");
            return _discord_config_cleanup(config), CCORD_BAD_DECODE;
        }
        if (!(config->log.ws =
                  fopen(filename, config->log.overwrite ? "w+" : "a+")))
        {
            return _discord_config_cleanup(config), CCORD_ERRNO;
        }
        free(filename);
    }
    _discord_config_disable_from_json(config, &client->file);
    for (size_t i = 0; i < config->log.disable.size; ++i) {
        logmod_toggle_logger(&client->logmod, config->log.disable.ids[i]);
        logmod_log(INFO, client->logger, "Disabled logging for '%s'",
                   config->log.disable.ids[i]);
    }
    return CCORD_OK;
}

void
_discord_config_cleanup(struct discord_config *config)
{
    if (config->token) {
        free(config->token);
    }
    if (config->log.trace) {
        fclose(config->log.trace);
    }
    if (config->log.http) {
        fclose(config->log.http);
    }
    if (config->log.disable.ids) {
        for (size_t i = 0; i < config->log.disable.size; ++i)
            free(config->log.disable.ids[i]);
        free(config->log.disable.ids);
    }
    memset(config, 0, sizeof *config);
}

struct discord *
discord_from_json(const char config_file[])
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
    if (_discord_config_from_json(&client->config, config_file) != CCORD_OK) {
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

struct discord *
discord_from_config(const struct discord_config *config)
{
    struct discord *client;
    char parsed_token[0x1000];
    CCORDcode code;

    if (!(client = calloc(1, sizeof *client))) {
        logmod_log(FATAL, NULL, "Couldn't allocate memory for client");
        return NULL;
    }
    if (!_discord_envs_expand(parsed_token, sizeof parsed_token,
                              config->token))
    {
        logmod_log(FATAL, client->logger, "Couldn't parse token");
        return discord_cleanup(client), NULL;
    }
    if (!_discord_token_is_valid(parsed_token, strlen(parsed_token))) {
        logmod_log(FATAL, client->logger, "Invalid token format");
        return discord_cleanup(client), NULL;
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
    client->config = *config;
    if ((code = _discord_init(client)) != CCORD_OK) {
        logmod_log(FATAL, client->logger, "Couldn't initialize client: %s",
                   discord_strerror(code, NULL));
        return discord_cleanup(client), NULL;
    }
    return client;
}

static void
_discord_clone_gateway_cleanup(struct discord_gateway *clone)
{
    if (clone->payload.json.table) free(clone->payload.json.table);
    if (clone->payload.data) free((void *)clone->payload.data);
    if (clone->payload.json.start) free(clone->payload.json.start);
    memset(clone, 0, sizeof *clone);
}

static CCORDcode
_discord_clone_gateway(struct discord_gateway *clone,
                       const struct discord_gateway *orig)
{
    const struct discord_gateway_payload *orig_payload = &orig->payload;
    struct discord_gateway_payload *payload = &clone->payload;
    jsmnf_loader loader;
    if (!(payload->json.size =
              cog_strndup(orig_payload->json.start, orig_payload->json.size,
                          &payload->json.start)))
    {
        return _discord_clone_gateway_cleanup(clone), CCORD_ERRNO;
    }
    if (!(payload->json.table =
              calloc(orig_payload->json.ntable, sizeof(*payload->json.table))))
    {
        return _discord_clone_gateway_cleanup(clone), CCORD_ERRNO;
    }
    jsmnf_init(&loader);
    if (jsmnf_load(&loader, payload->json.start, payload->json.size,
                   payload->json.table, payload->json.ntable)
        <= 0)
    {
        return _discord_clone_gateway_cleanup(clone), CCORD_BAD_DECODE;
    }
    if (!(payload->data = jsmnf_find(loader.root, "d", 1))) {
        return _discord_clone_gateway_cleanup(clone), CCORD_BAD_DECODE;
    }
    return CCORD_OK;
}

static void
_discord_clone_cleanup(struct discord *client)
{
    if (client->is_original) {
        logmod_log(ERROR, client->logger,
                   "Attempted to cleanup original client");
        return;
    }
    _discord_clone_gateway_cleanup(&client->gw);
    free(client);
}

struct discord *
discord_clone(const struct discord *orig)
{
    struct discord *clone;
    CCORDcode code;
    if (!(clone = malloc(sizeof(struct discord)))) {
        logmod_log(FATAL, orig->logger, "Couldn't allocate memory for client");
        return NULL;
    }
    memcpy(clone, orig, sizeof(struct discord));
    clone->is_original = false;
    if ((code = _discord_clone_gateway(&clone->gw, &orig->gw)) != CCORD_OK) {
        logmod_log(FATAL, orig->logger, "Couldn't clone gateway: %s (code %d)",
                   discord_strerror(code, NULL), code);
        return _discord_clone_cleanup(clone), NULL;
    }
    return clone;
}

static void
_discord_global_cleanup()
{
    ccord_once_cleanup();
    discord_worker_global_cleanup();
    curl_global_cleanup();
    _discord_notifier_close();
}

void
discord_cleanup(struct discord *client)
{
    if (!client->is_original) {
        _discord_clone_cleanup(client);
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
    if (client->file.start) {
        free(client->file.start);
    }
    _discord_global_cleanup();
    free(client);
}

#define CASE_RETURN_STR(event)                                                \
    case event:                                                               \
        return #event
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
        return ccord_code_as_string(code);
    }
}
#undef CASE_RETURN_STR

const char *
discord_strerror(CCORDcode code, struct discord *client)
{
    (void)client;

    switch (code) {
    default:
        return ccord_strerror(code);
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
    struct ccord_szbuf field = { 0 };

    if (!client->file.size) {
        logmod_log(ERROR, client->logger,
                   "discord_config_get_field() expects a client "
                   "initialized with discord_from_json()");
    }
    else {
        jsmnf_loader loader;
        jsmnf_table table[0x100];

        jsmnf_init(&loader);
        if (0 < jsmnf_load(&loader, client->file.start, client->file.size,
                           table, sizeof(table) / sizeof *table))
        {
            const jsmnf_pair *f;
            if ((f = jsmnf_find_path(loader.root, path, depth))
                && strncmp("null", client->file.start + f->v->start,
                           (size_t)(f->v->end - f->v->start))
                       != 0)
            {
                field =
                    (struct ccord_szbuf){ client->file.start + f->v->start,
                                          (size_t)(f->v->end - f->v->start),
                                          1 };
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
