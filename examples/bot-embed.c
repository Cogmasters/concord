#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"

char JSON_STRING[] =
  "{\n"
  "  \"title\": \"Orca\",\n"
  "  \"description\": \"Multi-REST Api library\",\n"
  "  \"url\": \"https://github.com/cee-studio/orca\",\n"
  "  \"color\": 3447003,\n"
  "  \"footer\": {\n"
  "    \"text\": \"github.com/cee-studio/orca\",\n"
  "    \"icon_url\": "
  "\"https://raw.githubusercontent.com/cee-studio/orca-docs/master/docs/"
  "source/images/icon.svg\"\n"
  "  },\n"
  "  \"image\": {\n"
  "    \"url\": "
  "\"https://github.com/cee-studio/orca-docs/blob/master/docs/source/images/"
  "social-preview.png?raw=true\"\n"
  "  },\n"
  "  \"author\": {\n"
  "    \"name\": \"cee-studio\",\n"
  "    \"url\": \"https://github.com/cee-studio\",\n"
  "    \"icon_url\": \"https://cee.dev/static/images/cee.png\"\n"
  "  },\n"
  "  \"fields\": [\n"
  "    {\n"
  "      \"name\":\"Want to learn more?\", \n"
  "      \"value\":\"Read our "
  "[documentation](https://cee-studio.github.io/orca/"
  "discord_api.html#c.discord_embed)!\"\n"
  "    },\n"
  "    {\n"
  "      \"name\":\"Need help troubleshooting?\", \n"
  "      \"value\":\"Debug with [Saiph-C](https://www.cee.studio/)\"\n"
  "    },\n"
  "    {\n"
  "      \"name\":\"Looking for support?\", \n"
  "      \"value\":\"Join our server [here](https://discord.gg/nBUqrWf)!\"\n"
  "    }\n"
  "  ]\n"
  "}";

void on_ready(struct discord *client)
{
  const struct discord_user *bot = discord_get_self(client);

  log_info("Embed-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_dynamic(struct discord *client, const struct discord_message *msg)
{
  if (msg->author->bot) return;

  /* load a embed from the json string */
  struct discord_embed embed;
  discord_embed_from_json(JSON_STRING, sizeof(JSON_STRING), &embed);
  embed.timestamp = discord_timestamp(client); // get current timestamp

  struct discord_create_message_params params = {
    .content = "This is an embed",
    .embed = &embed,
  };
  discord_create_message(client, msg->channel_id, &params, NULL);

  /* must cleanup 'embed' afterwards */
  discord_embed_cleanup(&embed);
}

void on_static(struct discord *client, const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_embed embed = {
    .title = "Orca",
    .description = "Multi-REST Api library",
    .url = "https://github.com/cee-studio/orca",
    .color = 3447003,
    .footer =
      &(struct discord_embed_footer){
        .text = "github.com/cee-studio/orca",
        .icon_url = "https://raw.githubusercontent.com/cee-studio/orca-docs/"
                    "master/docs/source/images/icon.svg",
      },
    .image =
      &(struct discord_embed_image){
        .url = "https://github.com/cee-studio/orca-docs/blob/master/docs/"
               "source/images/social-preview.png?raw=true",
      },
    .author =
      &(struct discord_embed_author){
        .name = "cee-studio",
        .url = "https://github.com/cee-studio",
        .icon_url = "https://cee.dev/static/images/cee.png",
      },
    .fields =
      (struct discord_embed_field *[]){
        &(struct discord_embed_field){
          .name = "Want to learn more?",
          .value = "Read our "
                   "[documentation](https://cee-studio.github.io/orca/apis/"
                   "discord.html#c.discord_embed)!",
        },
        &(struct discord_embed_field){
          .name = "Looking for support?",
          .value = "Join our server [here](https://discord.gg/x4hhGQYu)!",
        },
        NULL // END OF ARRAY
      }
  };

  struct discord_create_message_params params = { .embed = &embed };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_builder(struct discord *client, const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_embed embed = { .color = 3447003 };

  discord_embed_set_title(&embed, "Orca");
  discord_embed_set_description(&embed, "Multi-REST Api library");
  discord_embed_set_url(&embed, "https://github.com/cee-studio/orca");

  discord_embed_set_footer(&embed, "github.com/cee-studio/orca",
                           "https://raw.githubusercontent.com/cee-studio/"
                           "orca-docs/master/docs/source/images/icon.svg",
                           NULL);
  discord_embed_set_image(
    &embed,
    "https://github.com/cee-studio/orca-docs/blob/master/docs/source/images/"
    "social-preview.png?raw=true",
    NULL, 0, 0);
  discord_embed_set_author(&embed, "cee-studio",
                           "https://github.com/cee-studio",
                           "https://cee.dev/static/images/cee.png", NULL);
  discord_embed_add_field(&embed, "Want to learn more?",
                          "Read our "
                          "[documentation](https://cee-studio.github.io/orca/"
                          "apis/discord.html#c.discord_embed)!",
                          false);
  discord_embed_add_field(
    &embed, "Looking for support?",
    "Join our server [here](https://discord.gg/x4hhGQYu)!", false);

  struct discord_create_message_params params = { .embed = &embed };
  discord_create_message(client, msg->channel_id, &params, NULL);

  /* must cleanup 'embed' afterwards */
  discord_embed_cleanup(&embed);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  orca_global_init();
  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_ready(client, &on_ready);

  discord_set_prefix(client, "!");
  discord_set_on_command(client, "dynamic", &on_dynamic);
  discord_set_on_command(client, "static", &on_static);
  discord_set_on_command(client, "builder", &on_builder);

  printf(
    "\n\nThis bot demonstrates how to embeds"
    " with three different methods.\n"
    "1 - Dynamic-approach (type !dynamic): Load the embed from "
    "a JSON string.\n"
    "2 - Static-approach (type !static): A  clean  initialization approach "
    "using the combination of designated initialization and compound "
    "literals.\n"
    "3 - Builder-approach (type !builder): A dynamic and flexible "
    "approach that relies on embed builder functions.\n"
    "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);
  orca_global_cleanup();
}
