#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp() */
#include <pthread.h>
#include <assert.h>

#include "discord.h"

struct user_cxt {
    u64_snowflake_t channel_id;
    unsigned long long counter;
};

void
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Succesfully connected to Discord as %s#%s!", bot->username,
             bot->discriminator);
}

void
disconnect(struct discord *client, struct discord_ret *ret)
{
    discord_shutdown(client);
}

void
reconnect(struct discord *client, struct discord_ret *ret)
{
    discord_reconnect(client, true);
}

void
on_disconnect(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct discord_attr attr = { .done = &disconnect, .high_p = true };
    struct discord_create_message_params params = { .content =
                                                        "Disconnecting ..." };

    discord_create_message(client, msg->channel_id, &params, &attr);
}

void
on_reconnect(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct discord_attr attr = { .done = &reconnect, .high_p = true };
    struct discord_create_message_params params = { .content =
                                                        "Reconnecting ..." };

    discord_create_message(client, msg->channel_id, &params, &attr);
}

void
on_single(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct discord_create_message_params params = { .content = "Hello" };

    discord_create_message(client, msg->channel_id, &params, NULL);
}

void
send_batch(struct discord *client, struct discord_ret *ret)
{
    const struct discord_message *msg = ret->ret;

    struct discord_attr attr = { .done = &send_batch };
    struct discord_create_message_params params = { 0 };
    char text[32];

    params.content = text;
    for (int i = 0; i < 128; ++i) {
        snprintf(text, sizeof(text), "%d", i);

        discord_create_message(client, msg->channel_id, &params, &attr);
    }

    params.content = "CHECKPOINT";

    discord_create_message(client, msg->channel_id, &params, &attr);
}

void
on_spam(struct discord *client, const struct discord_message *msg)
{
    struct discord_ret ret = { .ret = (void *)msg };

    send_batch(client, &ret);
}

void
send_msg(struct discord *client, struct discord_ret *ret)
{
    const struct discord_message *msg = ret->ret;
    char text[32];

    struct discord_create_message_params params = { .content = text };
    struct discord_attr attr = { .done = &send_msg };
    struct user_cxt *cxt = discord_get_data(client);

    snprintf(text, sizeof(text), "%llu", cxt->counter);

    discord_create_message(client, msg->channel_id, &params, &attr);

    ++cxt->counter;
}

void
on_spam_ordered(struct discord *client, const struct discord_message *msg)
{
    struct discord_ret ret = { .ret = (void *)msg };

    send_msg(client, &ret);
}

void
send_err(struct discord *client, struct discord_err *err)
{
    u64_snowflake_t channel_id = *(u64_snowflake_t *)err->data;

    struct discord_create_message_params params = {
        .content = (char *)discord_strerror(err->code, client)
    };
    discord_create_message(client, channel_id, &params, NULL);
}

void
on_force_error(struct discord *client, const struct discord_message *msg)
{
    u64_snowflake_t *channel_id = malloc(sizeof(u64_snowflake_t));
    struct discord_attr attr = { .fail = &send_err,
                                 .data = channel_id,
                                 .fail_cleanup = &free,
                                 .done_cleanup = &free };

    memcpy(channel_id, &msg->channel_id, sizeof(u64_snowflake_t));

    discord_delete_channel(client, 123, &attr);
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
