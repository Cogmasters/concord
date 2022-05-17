#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp() */
#include <pthread.h>
#include <assert.h>

#include "discord.h"

struct global_context {
    u64snowflake channel_id;
    unsigned long long counter;
};

struct local_context {
    struct discord *client;
    const struct discord_message *event;
};

void
local_context_cleanup(struct discord *client, void *data)
{
    struct local_context *cxt = data;

    discord_unclaim(client, cxt->event);
    free(data);
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
disconnect(struct discord *client,
           void *data,
           const struct discord_message *msg)
{
    (void)data;
    (void)msg;
    discord_shutdown(client);
}

void
reconnect(struct discord *client,
          void *data,
          const struct discord_message *msg)
{
    (void)data;
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
send_batch(struct discord *client,
           void *data,
           const struct discord_message *msg)
{
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
on_spam(struct discord *client, const struct discord_message *event)
{
    send_batch(client, NULL, event);
}

void
send_msg(struct discord *client, void *data, const struct discord_message *msg)
{
    struct global_context *g_cxt = discord_get_data(client);
    char text[32];

    snprintf(text, sizeof(text), "%llu", g_cxt->counter);

    discord_create_message(client, msg->channel_id,
                           &(struct discord_create_message){
                               .content = text,
                           },
                           &(struct discord_ret_message){
                               .done = &send_msg,
                           });

    ++g_cxt->counter;
}

void
on_spam_ordered(struct discord *client, const struct discord_message *event)
{
    send_msg(client, NULL, event);
}

void
fail_delete_channel(struct discord *client, CCORDcode code, void *data)
{
    struct local_context *cxt = data;

    discord_create_message(
        client, cxt->event->channel_id,
        &(struct discord_create_message){
            .content = (char *)discord_strerror(code, client),
        },
        NULL);
}

void
on_force_error(struct discord *client, const struct discord_message *event)
{
    const u64snowflake FAUX_CHANNEL_ID = 123;
    struct local_context *cxt = malloc(sizeof *cxt);

    cxt->event = discord_claim(client, event);

    discord_delete_channel(client, FAUX_CHANNEL_ID,
                           &(struct discord_ret_channel){
                               .fail = &fail_delete_channel,
                               .data = cxt,
                               .cleanup = &local_context_cleanup,
                           });
}

int
main(int argc, char *argv[])
{
    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    ccord_global_init();

    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Couldn't initialize client");

    struct global_context g_cxt = { 0 };
    discord_set_data(client, &g_cxt);

    discord_set_on_ready(client, &on_ready);

    discord_set_prefix(client, "!");
    discord_set_on_command(client, "disconnect", &on_disconnect);
    discord_set_on_command(client, "reconnect", &on_reconnect);
    discord_set_on_command(client, "single", &on_single);
    discord_set_on_command(client, "spam", &on_spam);
    discord_set_on_command(client, "spam-ordered", &on_spam_ordered);
    discord_set_on_command(client, "force_error", &on_force_error);

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
