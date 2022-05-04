#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp() */
#include <pthread.h>
#include <assert.h>

#include "discord.h"

struct user_cxt {
    u64snowflake channel_id;
    unsigned long long counter;
};

void
on_ready(struct discord *client, struct discord_ready *event)
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
on_disconnect(struct discord *client, struct discord_message *event)
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
on_reconnect(struct discord *client, struct discord_message *event)
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
on_single(struct discord *client, struct discord_message *event)
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
on_spam(struct discord *client, struct discord_message *event)
{
    send_batch(client, NULL, event);
}

void
send_msg(struct discord *client, void *data, const struct discord_message *msg)
{
    struct user_cxt *cxt = discord_get_data(client);
    char text[32];

    snprintf(text, sizeof(text), "%llu", cxt->counter);

    discord_create_message(client, msg->channel_id,
                           &(struct discord_create_message){
                               .content = text,
                           },
                           &(struct discord_ret_message){
                               .done = &send_msg,
                           });

    ++cxt->counter;
}

void
on_spam_ordered(struct discord *client, struct discord_message *event)
{
    send_msg(client, NULL, event);
}

void
send_err(struct discord *client, CCORDcode code, void *data)
{
    u64snowflake channel_id = *(u64snowflake *)data;

    discord_create_message(
        client, channel_id,
        &(struct discord_create_message){
            .content = (char *)discord_strerror(code, client),
        },
        NULL);
}

void
on_force_error(struct discord *client, struct discord_message *event)
{
    const u64snowflake FAUX_CHANNEL_ID = 123;
    u64snowflake *channel_id = malloc(sizeof(u64snowflake));

    memcpy(channel_id, &event->channel_id, sizeof(u64snowflake));

    discord_delete_channel(client, FAUX_CHANNEL_ID,
                           &(struct discord_ret_channel){
                               .fail = &send_err,
                               .data = channel_id,
                               .cleanup = &free,
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

    struct user_cxt cxt = { 0 };
    discord_set_data(client, &cxt);

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
