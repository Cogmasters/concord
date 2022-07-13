#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#include "discord.h"

struct discord_data {
    CURLM *multi;
};

struct easy_request {
    CURL *easy;
    char url[4096];
    struct {
        char *arr;
        size_t len;
    } buf;
    u64snowflake channel_id;
};

static size_t
write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    struct easy_request *easy_request = userdata;
    size_t current_len = easy_request->buf.len;
    size_t len = current_len + nmemb;
    void *tmp = realloc(easy_request->buf.arr, len + 1);
    if (!tmp) return 0;
    easy_request->buf.arr = tmp;
    easy_request->buf.len = len;
    easy_request->buf.arr[easy_request->buf.len] = 0;
    memcpy(easy_request->buf.arr + current_len, ptr, nmemb);
    return nmemb;
}

static void
on_url_cmd(struct discord *client, const struct discord_message *message)
{
    struct discord_data *discord_data = discord_get_data(client);
    struct easy_request *easy_request = calloc(1, sizeof *easy_request);
    easy_request->channel_id = message->channel_id;
    strcpy(easy_request->url, message->content);
    easy_request->easy = curl_easy_init();
    curl_easy_setopt(easy_request->easy, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(easy_request->easy, CURLOPT_URL, easy_request->url);
    curl_easy_setopt(easy_request->easy, CURLOPT_WRITEDATA, easy_request);
    curl_easy_setopt(easy_request->easy, CURLOPT_WRITEFUNCTION,
                     write_callback);
    curl_easy_setopt(easy_request->easy, CURLOPT_PRIVATE, easy_request);
    curl_multi_add_handle(discord_data->multi, easy_request->easy);
    io_poller_curlm_enable_perform(discord_get_io_poller(client),
                                   discord_data->multi);
}

static int
curl_callback(struct io_poller *io, CURLM *multi, void *user_data)
{
    struct discord *client = user_data;
    int running, msgs;
    curl_multi_socket_all(multi, &running);

    for (CURLMsg *msg; (msg = curl_multi_info_read(multi, &msgs));) {
        if (CURLMSG_DONE == msg->msg) {
            struct easy_request *easy_request;
            curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE,
                              &easy_request);
            if (easy_request->buf.len > 1024) easy_request->buf.arr[1024] = 0;
            discord_create_message(
                client, easy_request->channel_id,
                &(struct discord_create_message){
                    .content = easy_request->buf.arr,
                },
                &(struct discord_ret_message){ .sync = DISCORD_SYNC_FLAG });
            curl_multi_remove_handle(multi, msg->easy_handle);
            curl_easy_cleanup(easy_request->easy);
            free(easy_request->buf.arr);
            free(easy_request);
        }
    }
    return 0; // always return 0
}

int
main(int argc, const char *argv[])
{
    ccord_global_init();
    struct discord_data discord_data = { 0 };
    struct discord *client =
        discord_config_init(argc > 1 ? argv[1] : "../config.json");
    discord_set_data(client, &discord_data);
    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
    discord_set_prefix(client, "!");
    discord_set_on_command(client, "url", on_url_cmd);
    struct io_poller *io = discord_get_io_poller(client);
    discord_data.multi = curl_multi_init();
    io_poller_curlm_add(io, discord_data.multi, curl_callback, client);
    discord_run(client);

    io_poller_curlm_del(io, discord_data.multi);
    curl_multi_cleanup(discord_data.multi);
    discord_cleanup(client);
    ccord_global_cleanup();
}
