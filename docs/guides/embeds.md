# Embeds

Discord's embeds stand for **embedded content messages** that can be **used to present data with special formatting** (such as **hyperlinks**) **and structure**, and **allows a higher message's length limit** as an added benefit.

## Concord & embeds

**There are multiple ways of sending an embed with Concord**, but in this guide, we'll be focusing on the "static approach".

See the example below explaining all the fields of the structures:

```c
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
                .icon_url = "https://raw.githubusercontent.com/Cogmasters/concord/master/docs/static/concord-small.png",
            },
        .image =
            &(struct discord_embed_image){
                .url = "https://raw.githubusercontent.com/Cogmasters/concord/master/docs/static/social-preview.png",
            }
    },
};

struct discord_create_message params = {
    .content = "Cogmaster - Concord",
    .embeds =
        &(struct discord_embeds){
            .size = sizeof(embeds) / sizeof *embeds,
            .array = embeds,
        },
};
discord_create_message(client, msg->channel_id, &params, NULL);
```

As you can see we are creating a structure with an array of embeds, which contain the information we want the bot to send.

*Keep in mind that this is a simple example, click [here](https://discord.com/developers/docs/resources/channel#embed-object) for a more thorough explanation of each embed field*

![Embed example](screenshots/embeds/embeds_example.png "Embed example")

[Embed structure](https://discord.com/developers/docs/resources/channel#embed-object):

* title: The title of the embed, the top part of the embed.
* description: The description/content of the embed, supports up to 4096 characters.
* url: A URL that if someone clicks on the title of the embed, will redirect to it (NOTE: Title is required for the URL to work).
* color: A color for the embed's left border, represented by a decimal number, HEX number (e.g., 0x3498DB), etc.
* timestamp: A `uint64_t` value with the current time, this value can be retrieved with [`discord_timestamp()`](https://cogmasters.github.io/concord/group__DiscordClient.html#ga15a8fe1a6d3f30c18c6985b3afae11f5).

[Embed author structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure):

* name: Author name, up to 256 characters.
* url: URL that the author name will redirect to when clicked.
* icon_url: URL of the author icon image.

```c
.author =
    &(struct discord_embed_author){
        .name = "Concord Bot",
        .url = "https://github.com/Cogmasters/concord",
        .icon_url = "https://raw.githubusercontent.com/Cogmasters/concord/master/docs/static/concord-small.png",
    },
```

[Embed footer structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure):

* text: Footer text, up to 2048 characters.
* icon_url: URL of an image to display in the footer.

[Embed image structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure):

* url: Source URL of the image.

[Embed thumbnail structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure):

* url: Source URL of the thumbnail image.
* height: Height of the thumbnail (optional).
* width: Width of the thumbnail (optional).

```c
.thumbnail =
    &(struct discord_embed_thumbnail){
        .url = "https://raw.githubusercontent.com/Cogmasters/concord/master/docs/static/concord-small.png",
    },
```

[Embed field structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure):

* name: Field name/title, up to 256 characters.
* value: Field content, up to 1024 characters.
* inline: Whether the field should be displayed inline (horizontally).

```c
.fields =
    &(struct discord_embed_fields){
        .size = 2,
        .array = (struct discord_embed_field[]) {
            {
                .name = "Field 1",
                .value = "This is a regular field",
                .is_inline = false
            },
            {
                .name = "Field 2",
                .value = "This is an inline field",
                .is_inline = true
            },
        }
    },
```

After creating the embed structure, now we will make the last structure so we can pass all the information needed to send a message.

The [`discord_create_message()`](https://cogmasters.github.io/concord/structdiscord__create__message.html) request expects its `params` to include the `embed` structure that will be sent over to the channel.

## Example bot

The following example outlines the recommended `static approach` way for sending an embed. For alternatives, you may take a look at this [example](examples/embed.c)

The only command from this bot is the `.sendembed` that only sends a basic embed.

```c
#include <stdio.h>

#include <concord/discord.h>
#include <concord/logmod.h>

void on_ready(struct discord *client, const struct discord_ready *bot) {
    (void) client;
    logmod_log(INFO, NULL, "Logged in as %s!", bot->user->username);
}

void on_sendembed(struct discord *client, const struct discord_message *msg) {
    struct discord_embed embeds[] = {
        {
            .title = "Hi, this is the title",
            .description = "Interesting, a description!",
            .url = "https://github.com/Cogmasters/concord",
            .color = 0x3498DB,
            .timestamp = discord_timestamp(client),
            .footer =
                &(struct discord_embed_footer){
                    .text = "Footer text, fancy!",
                    .icon_url = "https://raw.githubusercontent.com/Cogmasters/concord/master/docs/static/concord-small.png",
                },
            .image =
                &(struct discord_embed_image){
                    .url = "https://raw.githubusercontent.com/Cogmasters/concord/master/docs/static/social-preview.png",
                },
            .author =
                &(struct discord_embed_author){
                    .name = "Concord Bot",
                    .url = "https://github.com/Cogmasters/concord",
                    .icon_url = "https://raw.githubusercontent.com/Cogmasters/concord/master/docs/static/concord-small.png",
                },
            .thumbnail =
                &(struct discord_embed_thumbnail){
                    .url = "https://raw.githubusercontent.com/Cogmasters/concord/master/docs/static/concord-small.png",
                },
            .fields =
                &(struct discord_embed_fields){
                    .size = 2,
                    .array = (struct discord_embed_field[]) {
                        {
                            .name = "Field 1",
                            .value = "This is a regular field",
                            .is_inline = false
                        },
                        {
                            .name = "Field 2",
                            .value = "This is an inline field",
                            .is_inline = true
                        },
                    }
                },
        },
    };

    struct discord_create_message params = {
        .content = "Just the content of the embed.",
        .embeds =
            &(struct discord_embeds){
                .size = sizeof(embeds) / sizeof *embeds,
                .array = embeds,
            },
    };

    discord_create_message(client, msg->channel_id, &params, NULL);
}

int main(void) {
    struct discord *client = discord_from_json("config.json");

    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);

    discord_set_on_ready(client, &on_ready);
    discord_set_on_command(client, ".sendembed", &on_sendembed);

    discord_run(client);
}
```
