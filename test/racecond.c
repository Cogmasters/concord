#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp() */
#include <pthread.h>
#include <assert.h>

#define JSMN_HEADER
#include "jsmn.h"
#include "jsmn-find.h"

#include "discord.h"

#define THREADPOOL_SIZE "4"
#define PREFIX          "!"

pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
bool g_keep_spamming = true;
unsigned g_thread_count;

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
disconnect(struct discord *client,
           struct discord_response *resp,
           const struct discord_message *msg)
{
    (void)resp;
    (void)msg;
    discord_shutdown(client);
}

void
reconnect(struct discord *client,
          struct discord_response *resp,
          const struct discord_message *msg)
{
    (void)resp;
    (void)msg;
    discord_reconnect(client, true);
}

void
on_disconnect(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    discord_create_message(client, event->channel_id,
                           &(struct discord_create_message){
                               .content = "Disconnecting ...",
                           },
                           &(struct discord_ret_message){
                               .done = &disconnect,
                               .high_p = true,
                           });
}

void
on_reconnect(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    discord_create_message(client, event->channel_id,
                           &(struct discord_create_message){
                               .content = "Reconnecting ...",
                           },
                           &(struct discord_ret_message){
                               .done = &reconnect,
                               .high_p = true,
                           });
}

void
on_single(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    discord_create_message(client, event->channel_id,
                           &(struct discord_create_message){
                               .content = "Hello",
                           },
                           NULL);
}

void
on_stop_spam_sync(struct discord *client, const struct discord_message *event)
{
    pthread_mutex_lock(&g_lock);
    g_keep_spamming = false;
    g_thread_count = 0;
    pthread_mutex_unlock(&g_lock);
}

void
on_spam_sync(struct discord *client, const struct discord_message *event)
{
    const unsigned threadpool_size = strtol(THREADPOOL_SIZE, NULL, 10);

    if (event->author->bot) return;

    // prevent blocking all threads
    pthread_mutex_lock(&g_lock);
    if (g_thread_count >= threadpool_size - 1) {
        discord_create_message(client, event->channel_id,
                               &(struct discord_create_message){
                                   .content =
                                       "Too many threads (" THREADPOOL_SIZE
                                       ") will block the threadpool!",
                               },
                               &(struct discord_ret_message){
                                   .sync = DISCORD_SYNC_FLAG,
                               });

        pthread_mutex_unlock(&g_lock);
        return;
    }

    ++g_thread_count;
    g_keep_spamming = true;
    pthread_mutex_unlock(&g_lock);

    char number[256];
    bool keep_alive = true;
    for (int i = 0;; ++i) {
        pthread_mutex_lock(&g_lock);
        keep_alive = g_keep_spamming;
        pthread_mutex_unlock(&g_lock);

        if (!keep_alive) break;

        snprintf(number, sizeof(number), "%d", i);
        discord_create_message(client, event->channel_id,
                               &(struct discord_create_message){
                                   .content = number,
                               },
                               &(struct discord_ret_message){
                                   .sync = DISCORD_SYNC_FLAG,
                               });
    }
}

void
send_batch(struct discord *client,
           struct discord_response *resp,
           const struct discord_message *msg)
{
    (void)resp;
    char text[32];

    for (int i = 0; i < 128; ++i) {
        snprintf(text, sizeof(text), "%d", i);
        discord_create_message(client, msg->channel_id,
                               &(struct discord_create_message){
                                   .content = text,
                               },
                               NULL);
    }

    discord_create_message(client, msg->channel_id,
                           &(struct discord_create_message){
                               .content = "CHECKPOINT",
                           },
                           &(struct discord_ret_message){
                               .done = &send_batch,
                           });
}

void
on_spam_async(struct discord *client, const struct discord_message *event)
{
    send_batch(client, NULL, event);
}

void
fail_delete_channel(struct discord *client, struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;

    discord_create_message(
        client, event->channel_id,
        &(struct discord_create_message){
            .content = (char *)discord_strerror(resp->code, client),
        },
        NULL);
}

void
on_force_error(struct discord *client, const struct discord_message *event)
{
    const u64snowflake FAUX_CHANNEL_ID = 123;

    discord_delete_channel(client, FAUX_CHANNEL_ID,
                           &(struct discord_ret_channel){
                               .fail = &fail_delete_channel,
                               .keep = event,
                           });
}

enum discord_event_scheduler
scheduler(struct discord *client,
          const char data[],
          size_t size,
          enum discord_gateway_events event)
{
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        char cmd[DISCORD_MAX_MESSAGE_LEN] = "";

        jsmntok_t *tokens = NULL;
        unsigned ntokens = 0;
        jsmn_parser parser;

        jsmn_init(&parser);
        if (0 < jsmn_parse_auto(&parser, data, size, &tokens, &ntokens)) {
            jsmnf_pair *pairs = NULL;
            unsigned npairs = 0;
            jsmnf_loader loader;

            jsmnf_init(&loader);
            if (0 < jsmnf_load_auto(&loader, data, tokens, parser.toknext,
                                    &pairs, &npairs))
            {
                jsmnf_pair *f;

                if ((f = jsmnf_find(pairs, data, "content", 7)))
                    snprintf(cmd, sizeof(cmd), "%.*s", (int)f->v.len,
                             data + f->v.pos);
                free(pairs);
            }
            free(tokens);
        }

        if (0 == strcmp(PREFIX "spam_sync", cmd))
            return DISCORD_EVENT_WORKER_THREAD;
    }
    return DISCORD_EVENT_MAIN_THREAD;
}

int
main(int argc, char *argv[])
{
    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    setenv("CCORD_THREADPOOL_SIZE", THREADPOOL_SIZE, 1);
    setenv("CCORD_THREADPOOL_QUEUE_SIZE", "128", 1);

    ccord_global_init();

    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Couldn't initialize client");

    discord_set_event_scheduler(client, &scheduler);

    discord_set_on_ready(client, &on_ready);

    discord_set_prefix(client, PREFIX);
    discord_set_on_command(client, "disconnect", &on_disconnect);
    discord_set_on_command(client, "reconnect", &on_reconnect);
    discord_set_on_command(client, "single", &on_single);
    discord_set_on_command(client, "stop_spam_sync", &on_stop_spam_sync);
    discord_set_on_command(client, "spam_sync", &on_spam_sync);
    discord_set_on_command(client, "spam_async", &on_spam_async);
    discord_set_on_command(client, "force_error", &on_force_error);

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
