#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <locale.h>
#include <limits.h>
#include <errno.h>
#include <inttypes.h> /* SCNu64 */

#include "discord.h"

u64_snowflake_t g_sudo_id;

void
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Shell-Bot succesfully connected to Discord as %s#%s!",
             bot->username, bot->discriminator);
}

void
on_cd(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->id != g_sudo_id) return;

    chdir(*msg->content ? msg->content : ".");

    char path[PATH_MAX];
    struct discord_create_message_params params = {
        .content = getcwd(path, sizeof(path)),
    };

    discord_async_next(client, NULL);
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void
on_less_like(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->id != g_sudo_id) return;

    struct discord_create_message_params params = { 0 };
    char buf[512];

    if (!msg->content) {
        params.content = "No file specified";
    }
    else {
        snprintf(buf, sizeof(buf), "attachment://%s", msg->content);

        params.embeds = (struct discord_embed *[]){
            &(struct discord_embed){ .title = msg->content },
            NULL // end of array
        };

        params.attachments = (struct discord_attachment *[]){
            &(struct discord_attachment){ .filename = msg->content },
            NULL // end of array
        };
    }

    discord_async_next(client, NULL);
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void
on_fallback(struct discord *client, const struct discord_message *msg)
{
    const size_t MAX_FSIZE = 5e6; // 5 mb

    if (msg->author->id != g_sudo_id) return;

    FILE *fp = popen(msg->content, "r");
    if (NULL == fp) {
        printf("Failed to run command");
        return;
    }

    char *path = calloc(1, MAX_FSIZE);
    char *pathtmp = calloc(1, MAX_FSIZE);

    while (NULL != fgets(path, MAX_FSIZE, fp)) {
        strncat(pathtmp, path, MAX_FSIZE - 1);
    }

    const size_t fsize = strlen(pathtmp);
    struct discord_create_message_params params = { 0 };

    if (fsize <= DISCORD_MAX_MESSAGE_LEN) {
        params.content = pathtmp;
    }
    else {
        params.attachments = (struct discord_attachment *[]){
            &(struct discord_attachment){
                .content = pathtmp,
                .size = fsize,
            },
            NULL // end of array
        };
    }

    discord_async_next(client, NULL);
    discord_create_message(client, msg->channel_id, &params, NULL);

    pclose(fp);
    free(path);
    free(pathtmp);
}

int
main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    ccord_global_init();
    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Couldn't initialize client");

    discord_set_prefix(client, "$");
    discord_set_on_command(client, NULL, &on_fallback);
    discord_set_on_command(client, "cd", &on_cd);
    discord_set_on_commands(client, &on_less_like, "less", "cat", "hexdump",
                            NULL);

    printf("\n\nThis bot allows navigating its host machine like"
           " a shell terminal.\n\n"
           "DISCLAIMER: This bot is potentially dangerous if not"
           " used with care.\nOnly give admin privileges to yourself"
           " or someone trustworthy.\n\n\n");

    do {
        printf("User ID to have sudo privileges\n");
        fscanf(stdin, "%" SCNu64, &g_sudo_id);
    } while (!g_sudo_id || errno == ERANGE);

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
