#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "cee-utils.h" /* cee_timestamp_ms() */

#define JSON_FILE "bot-embed.json"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Embed-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_from_json_init(struct discord *client,
                       const struct discord_user *bot,
                       const struct discord_message *msg)
{
  if (msg->author->bot) return;

  /* load JSON file contents into json_str */
  size_t json_len;
  char *json_str = cee_load_whole_file(JSON_FILE, &json_len);

  /* load a embed from the json string */
  struct discord_embed *embed = NULL;
  discord_embed_from_json(json_str, json_len, &embed);
  embed->timestamp = cee_timestamp_ms(); // get current timestamp

  struct discord_create_message_params params = { .content =
                                                    "This is an embed",
                                                  .embed = embed };
  discord_create_message(client, msg->channel_id, &params, NULL);

  free(json_str);

  discord_embed_cleanup(embed);
  free(embed);
}

void on_designated_init(struct discord *client,
                        const struct discord_user *bot,
                        const struct discord_message *msg)
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
                    "master/docs/source/images/icon.svg" },
    .image =
      &(struct discord_embed_image){
        .url = "https://github.com/cee-studio/orca-docs/blob/master/docs/"
               "source/images/social-preview.png?raw=true" },
    .author =
      &(struct discord_embed_author){
        .name = "cee-studio",
        .url = "https://github.com/cee-studio",
        .icon_url = "https://cee.dev/static/images/cee.png" },
    .fields =
      (struct discord_embed_field *[]){
        &(struct discord_embed_field){
          .name = "Want to learn more?",
          .value = "Read our "
                   "[documentation](https://cee-studio.github.io/orca/apis/"
                   "discord.html#c.discord_embed)!" },
        &(struct discord_embed_field){
          .name = "Looking for support?",
          .value = "Join our server [here](https://discord.gg/x4hhGQYu)!" },
        NULL // END OF ARRAY
      }
  };

  struct discord_create_message_params params = { .embed = &embed };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_builder_init(struct discord *client,
                     const struct discord_user *bot,
                     const struct discord_message *msg)
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

  discord_embed_cleanup(&embed);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  discord_global_init();
  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_ready(client, &on_ready);

  discord_set_prefix(client, "!");
  discord_set_on_command(client, "from_json_init", &on_from_json_init);
  discord_set_on_command(client, "designated_init", &on_designated_init);
  discord_set_on_command(client, "builder_init", &on_builder_init);

  printf("\n\nThis bot demonstrates how to embeds"
         " with three different methods.\n"
         "1 - From JSON init (type !from_json_init): This is the easiest "
         "method by far, you can use it"
         " with a JSON library of your preference.\n"
         "2 - Designated init (type !designated_init): This is a 'clean' "
         "initialization approach"
         " but is not very flexible.\n"
         "3 - Builder init (type !builder_init): This is a very flexible "
         "approach, it relies on utility functions from discord-misc.c.\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);
  discord_global_cleanup();
}
