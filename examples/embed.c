#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "log.h"

void
print_usage(void)
{
    printf("\n\nThis bot demonstrates how to embeds"
           " with three different methods.\n"
           "1 - Dynamic-approach (type !dynamic): Load the embed from "
           "a JSON string.\n"
           "2 - Static-approach (type !static): A  clean  initialization "
           "approach "
           "using the combination of designated initialization and compound "
           "literals.\n"
           "3 - Builder-approach (type !builder): A dynamic and flexible "
           "approach that relies on embed builder functions.\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

#define ICON_URL                                                              \
    "https://github.com/Cogmasters/concord/blob/master/docs/static/"          \
    "concord-small.png?raw=true"
#define IMAGE_URL                                                             \
    "https://github.com/Cogmasters/concord/blob/master/docs/static/"          \
    "social-preview.png?raw=true"

char JSON[] = "{\n"
              "  \"title\": \"Concord\",\n"
              "  \"description\": \"Discord API library\",\n"
              "  \"url\": \"https://github.com/Cogmasters/concord\",\n"
              "  \"color\": 3447003,\n"
              "  \"footer\": {\n"
              "    \"text\": \"github.com/Cogmasters/concord\",\n"
              "    \"icon_url\": \"" ICON_URL "\"\n"
              "  },\n"
              "  \"image\": {\n"
              "    \"url\": \"" IMAGE_URL "\"\n"
              "  },\n"
              "  \"author\": {\n"
              "    \"name\": \"Cogmasters\",\n"
              "    \"url\": \"https://github.com/Cogmasters\",\n"
              "  },\n"
              "  \"fields\": [\n"
              "    {\n"
              "      \"name\":\"Want to learn more?\", \n"
              "      \"value\":\"Read our "
              "[documentation](https://cogmasters.github.io/concord/)!\"\n"
              "    },\n"
              "    {\n"
              "      \"name\":\"Looking for support?\", \n"
              "      \"value\":\"Join our server "
              "[here](https://discord.gg/Y7Xa6MA82v)!\"\n"
              "    }\n"
              "  ]\n"
              "}";

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Embed-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
on_dynamic(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    /* load a embed from the json string */
    struct discord_embed embed = { 0 };
    discord_embed_from_json(JSON, sizeof(JSON), &embed);
    embed.timestamp = discord_timestamp(client); // get current timestamp

    struct discord_create_message params = {
        .content = "This is an embed",
        .embeds =
            &(struct discord_embeds){
                .size = 1,
                .array = &embed,
            },
    };
    discord_create_message(client, event->channel_id, &params, NULL);

    /* must cleanup 'embed' afterwards */
    discord_embed_cleanup(&embed);
}

void
on_static(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_embed_field fields[] = {
        {
            .name = "Want to learn more?",
            .value = "Read our "
                     "[documentation](https://cogmasters.github.io/"
                     "concord/)!",
        },
        {
            .name = "Looking for support?",
            .value = "Join our server "
                     "[here](https://discord.gg/x4hhGQYu)!",
        },
    };

    struct discord_embed embeds[] = {
        {
            .title = "Concord",
            .description = "Discord API library",
            .url = "https://github.com/Cogmasters/concord",
            .color = 0x3498DB,
            .timestamp = discord_timestamp(client),
            .footer =
                &(struct discord_embed_footer){
                    .text = "github.com/Cogmasters/concord",
                    .icon_url = ICON_URL,
                },
            .image =
                &(struct discord_embed_image){
                    .url = IMAGE_URL,
                },
            .author =
                &(struct discord_embed_author){
                    .name = "Cogmasters",
                    .url = "https://github.com/Cogmasters",
                },
            .fields =
                &(struct discord_embed_fields){
                    .size = sizeof(fields) / sizeof *fields,
                    .array = fields,
                },
        },
    };

    struct discord_create_message params = {
        .embeds =
            &(struct discord_embeds){
                .size = sizeof(embeds) / sizeof *embeds,
                .array = embeds,
            },
    };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_builder(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_embed embed = {
        .color = 0x3498DB,
        .timestamp = discord_timestamp(client),
    };

    discord_embed_set_title(&embed, "Concord");
    discord_embed_set_description(&embed, "Discord API library");
    discord_embed_set_url(&embed, "https://github.com/Cogmasters/concord");

    discord_embed_set_footer(&embed, "github.com/Cogmasters/concord", ICON_URL,
                             NULL);
    discord_embed_set_image(&embed, IMAGE_URL, NULL, 0, 0);
    discord_embed_set_author(&embed, "Cogmasters",
                             "https://github.com/Cogmasters", NULL, NULL);
    discord_embed_add_field(
        &embed, "Want to learn more?",
        "Read our "
        "[documentation](https://cogmasters.github.io/concord/)!",
        false);
    discord_embed_add_field(
        &embed, "Looking for support?",
        "Join our server [here](https://discord.gg/x4hhGQYu)!", false);

    struct discord_create_message params = {
        .embeds =
            &(struct discord_embeds){
                .size = 1,
                .array = &embed,
            },
    };
    discord_create_message(client, event->channel_id, &params, NULL);

    /* must cleanup 'embed' afterwards */
    discord_embed_cleanup(&embed);
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

    discord_set_on_ready(client, &on_ready);

    discord_set_prefix(client, "!");
    discord_set_on_command(client, "dynamic", &on_dynamic);
    discord_set_on_command(client, "static", &on_static);
    discord_set_on_command(client, "builder", &on_builder);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
