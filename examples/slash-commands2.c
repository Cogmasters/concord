#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h> /* SCNu64 */

#include "discord.h"
#include "log.h"

u64snowflake g_app_id;

void
print_usage(void)
{
    printf("\n\nThis bot demonstrates how easy it is to create/update/delete "
           "application commands\n"
           "1. Input a valid application id from "
           "https://discord.com/developers/applications\n"
           "2. Type HELP to see commands\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

void
print_help(void)
{
    log_info("\nHelp :\n"
             "\tPrint help : HELP\n"
             "\tList Commands : LIST <?guild_id>\n"
             "\tCreate Command : CREATE <cmd_name>[<cmd_desc>] <?guild_id>\n"
             "\tUpdate Command : UPDATE <cmd_id> <cmd_name>[<cmd_desc>] "
             "<?guild_id>\n"
             "\tDelete Command : DELETE <cmd_id> <?guild_id>\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Slash-Commands-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
fail_interaction_create(struct discord *client, struct discord_response *resp)
{
    log_error("%s", discord_strerror(resp->code, client));
}

void
on_interaction_create(struct discord *client,
                      const struct discord_interaction *event)
{
    log_info("Interaction %" PRIu64 " received", event->id);

    struct discord_interaction_callback_data data = {
        .content = "Hello World!",
        .flags = DISCORD_MESSAGE_EPHEMERAL,
    };
    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
        .data = &data,
    };
    struct discord_ret_interaction_response ret = {
        .fail = &fail_interaction_create
    };

    discord_create_interaction_response(client, event->id, event->token,
                                        &params, &ret);
}

void *
read_input(void *p_client)
{
    struct discord *client = p_client;

    char buf[DISCORD_MAX_MESSAGE_LEN];
    ptrdiff_t bufoffset;
    char cmd_action[9 + 1];
    CCORDcode code;

    pthread_detach(pthread_self());

    while (1) {
        memset(buf, 0, sizeof(buf));

        fgets(buf, sizeof(buf), stdin);
        if (!*buf) continue; // is empty

        memset(cmd_action, 0, sizeof(cmd_action));
        sscanf(buf, "%s", cmd_action);
        bufoffset = strlen(cmd_action) + 1;

        if (!*cmd_action || 0 == strcasecmp(cmd_action, "HELP")) goto _help;

        if (0 == strcasecmp(cmd_action, "LIST")) {
            struct discord_application_commands app_cmds = { 0 };
            u64snowflake guild_id = 0;

            sscanf(buf + bufoffset, "%" SCNu64, &guild_id);

            struct discord_ret_application_commands ret = {
                .sync = &app_cmds,
            };

            if (guild_id)
                code = discord_get_guild_application_commands(client, g_app_id,
                                                              guild_id, &ret);
            else
                code = discord_get_global_application_commands(client,
                                                               g_app_id, &ret);

            if (CCORD_OK == code && app_cmds.size) {
                char list[4096] = ""; // should be large enough ?
                size_t len = 0;

                for (int i = 0; i < app_cmds.size; ++i) {
                    len +=
                        snprintf(list + len, sizeof(list) - len,
                                 "\t%d:\t%s (%" PRIu64 ")\n", i,
                                 app_cmds.array[i].name, app_cmds.array[i].id);
                }

                log_info("\nCommands: \n%.*s", (int)len, list);

                discord_application_commands_cleanup(&app_cmds);
            }
            else {
                log_error("Couldn't list commands");
            }
        }
        else if (0 == strcasecmp(cmd_action, "CREATE")) {
            char cmd_name[32 + 1] = "", cmd_desc[100 + 1] = "";
            struct discord_application_command app_cmd = { 0 };
            u64snowflake guild_id = 0;

            sscanf(buf + bufoffset, "%32[^[][%100[^]]] %" SCNu64, cmd_name,
                   cmd_desc, &guild_id);

            if (!*cmd_name || !*cmd_desc) goto _help;

            struct discord_ret_application_command ret = {
                .sync = &app_cmd,
            };

            if (guild_id) {
                struct discord_create_guild_application_command params = {
                    .name = cmd_name,
                    .description = cmd_desc,
                    .default_permission = true,
                    .type = 1,
                };

                code = discord_create_guild_application_command(
                    client, g_app_id, guild_id, &params, &ret);
            }
            else {
                struct discord_create_global_application_command params = {
                    .name = cmd_name,
                    .description = cmd_desc,
                    .default_permission = true,
                    .type = 1,
                };

                code = discord_create_global_application_command(
                    client, g_app_id, &params, &ret);
            }

            if (CCORD_OK == code && app_cmd.id) {
                log_info("Created command:\t%s (" PRIu64 ")", app_cmd.name,
                         app_cmd.id);
                discord_application_command_cleanup(&app_cmd);
            }
            else {
                log_error("Couldn't create command '%s'", cmd_name);
            }
        }
        else if (0 == strcasecmp(cmd_action, "UPDATE")) {
            char cmd_name[32 + 1] = "", cmd_desc[100 + 1] = "";
            u64snowflake command_id = 0, guild_id = 0;

            sscanf(buf + bufoffset, "%" SCNu64 " %32[^[][%100[^]]] %" SCNu64,
                   &command_id, cmd_name, cmd_desc, &guild_id);

            if (!command_id) goto _help;

            struct discord_application_command app_cmd = { 0 };

            struct discord_ret_application_command ret = {
                .sync = &app_cmd,
            };

            if (guild_id) {
                struct discord_edit_guild_application_command params = {
                    .name = *cmd_name ? cmd_name : NULL,
                    .description = *cmd_desc ? cmd_desc : NULL,
                    .default_permission = true,
                };

                code = discord_edit_guild_application_command(
                    client, g_app_id, guild_id, command_id, &params, &ret);
            }
            else {
                struct discord_edit_global_application_command params = {
                    .name = *cmd_name ? cmd_name : NULL,
                    .description = *cmd_desc ? cmd_desc : NULL,
                    .default_permission = true,
                };

                code = discord_edit_global_application_command(
                    client, g_app_id, command_id, &params, &ret);
            }

            if (CCORD_OK == code && app_cmd.id) {
                log_info("Edited command:\t%s (%" PRIu64 ")", app_cmd.name,
                         app_cmd.id);
                discord_application_command_cleanup(&app_cmd);
            }
            else {
                log_error("Couldn't create command '%s'", cmd_name);
            }
        }
        else if (0 == strcasecmp(cmd_action, "DELETE")) {
            u64snowflake command_id = 0, guild_id = 0;

            sscanf(buf + bufoffset, "%" SCNu64 "%" SCNu64, &command_id,
                   &guild_id);

            if (!command_id) goto _help;

            struct discord_ret ret = { .sync = true };

            if (guild_id) {
                code = discord_delete_guild_application_command(
                    client, g_app_id, guild_id, command_id, &ret);
            }
            else {
                code = discord_delete_global_application_command(
                    client, g_app_id, command_id, &ret);
            }

            if (CCORD_OK == code)
                log_info("Deleted command");
            else
                log_error("Couldn't delete command");
        }
        else {
            goto _help;
        }

        continue;
    _help:
        print_help();
    }

    pthread_exit(NULL);
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
    assert(NULL != client && "Could not initialize client");

    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction_create);

    print_usage();
    fgetc(stdin); // wait for input

    printf("Please provide a valid application id in order to test the Slash "
           "Commands functionality, it can be obtained from: "
           "https://discord.com/developers/applications\n");
    do {
        printf("Application ID:\n");
        fscanf(stdin, "%" SCNu64, &g_app_id);
    } while (!g_app_id || errno == ERANGE);

    pthread_t tid;
    pthread_create(&tid, NULL, &read_input, client);

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
