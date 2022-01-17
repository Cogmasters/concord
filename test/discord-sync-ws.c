#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp() */
#include <pthread.h>
#include <assert.h>

#include "discord.h"
#include "json-actor.h" /* json_extract() */

#define THREADPOOL_SIZE "4"
#define PREFIX          "!"

pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
bool g_keep_spamming = true;
unsigned g_thread_count;

void
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Succesfully connected to Discord as %s#%s!", bot->username,
             bot->discriminator);
}

void
on_disconnect(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    discord_create_message(client, msg->channel_id,
                           &(struct discord_create_message){
                               .content = "Disconnecting ...",
                           },
                           &(struct discord_ret_message){
                               .sync = DISCORD_SYNC_FLAG,
                           });

    discord_shutdown(client);
}

void
on_reconnect(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    discord_create_message(client, msg->channel_id,
                           &(struct discord_create_message){
                               .content = "Reconnecting ...",
                           },
                           &(struct discord_ret_message){
                               .sync = DISCORD_SYNC_FLAG,
                           });

    discord_reconnect(client, true);
}

void
on_spam(struct discord *client, const struct discord_message *msg)
{
    const unsigned threadpool_size = strtol(THREADPOOL_SIZE, NULL, 10);

    if (msg->author->bot) return;

    // prevent blocking all threads
    pthread_mutex_lock(&g_lock);
    if (g_thread_count >= threadpool_size - 1) {
        discord_create_message(client, msg->channel_id,
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
        discord_create_message(client, msg->channel_id,
                               &(struct discord_create_message){
                                   .content = number,
                               },
                               &(struct discord_ret_message){
                                   .sync = DISCORD_SYNC_FLAG,
                               });
    }
}

void
on_spam_block(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    discord_create_message(client, msg->channel_id,
                           &(struct discord_create_message){
                               .content = "No 1",
                           },
                           &(struct discord_ret_message){
                               .sync = DISCORD_SYNC_FLAG,
                           });
}

void
on_spam_block_continue(struct discord *client,
                       const struct discord_message *msg)
{
    const struct discord_user *bot = discord_get_self(client);
    char text[32];
    int number;

    if (msg->author->id != bot->id) return;

    sscanf(msg->content, "No %d", &number);
    snprintf(text, sizeof(text), "No %d", 1 + number);

    discord_create_message(client, msg->channel_id,
                           &(struct discord_create_message){
                               .content = text,
                           },
                           &(struct discord_ret_message){
                               .sync = DISCORD_SYNC_FLAG,
                           });
}

void
on_stop(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    pthread_mutex_lock(&g_lock);
    g_keep_spamming = false;
    g_thread_count = 0;
    pthread_mutex_unlock(&g_lock);
}

void
on_force_error(struct discord *client, const struct discord_message *msg)
{
    const u64_snowflake_t FAUX_CHANNEL_ID = 123ULL;
    CCORDcode code;

    if (msg->author->bot) return;

    code = discord_delete_channel(client, FAUX_CHANNEL_ID,
                                  &(struct discord_ret_channel){
                                      .sync = DISCORD_SYNC_FLAG,
                                  });
    assert(code != CCORD_OK);

    discord_create_message(
        client, msg->channel_id,
        &(struct discord_create_message){
            .content = (char *)discord_strerror(code, client),
        },
        &(struct discord_ret_message){
            .sync = DISCORD_SYNC_FLAG,
        });
}

void
on_ping(struct discord *client, const struct discord_message *msg)
{
    char text[256];

    if (msg->author->bot) return;

    sprintf(text, "Ping: %d", discord_get_ping(client));

    discord_create_message(client, msg->channel_id,
                           &(struct discord_create_message){
                               .content = text,
                           },
                           &(struct discord_ret_message){
                               .sync = DISCORD_SYNC_FLAG,
                           });
}

enum discord_event_scheduler
scheduler(struct discord *client,
          struct sized_buffer *data,
          enum discord_gateway_events event)
{
    if (event == DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE) {
        char cmd[1024] = "";

        json_extract(data->start, data->size, "(content):.*s", sizeof(cmd),
                     cmd);

        if (0 == strcmp(PREFIX "ping", cmd)
            || 0 == strcmp(PREFIX "spam-block", cmd)) {
            return DISCORD_EVENT_MAIN_THREAD;
        }
        else if (0 == strncmp("No", cmd, 2)) {
            struct discord_message msg = { 0 };

            discord_message_from_json(data->start, data->size, &msg);
            on_spam_block_continue(client, &msg);
            discord_message_cleanup(&msg);

            return DISCORD_EVENT_IGNORE;
        }
    }

    return DISCORD_EVENT_WORKER_THREAD;
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

    /* trigger event callbacks in a multi-threaded fashion */
    discord_set_event_scheduler(client, &scheduler);

    discord_set_on_ready(client, &on_ready);

    discord_set_prefix(client, PREFIX);
    discord_set_on_command(client, "disconnect", &on_disconnect);
    discord_set_on_command(client, "reconnect", &on_reconnect);
    discord_set_on_command(client, "spam", &on_spam);
    discord_set_on_command(client, "spam-block", &on_spam_block);
    discord_set_on_command(client, "stop", &on_stop);
    discord_set_on_command(client, "force_error", &on_force_error);
    discord_set_on_command(client, "ping", &on_ping);

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
