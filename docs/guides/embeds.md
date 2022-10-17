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
* description: The description/content of the embed.
* url: A URL that if someone clicks on the title of the embed, will redirect to it (NOTE: Title is required).
* color: A color, that can be represented by a binary number, HEX number, etc.
* timestamp: A `uint64_t` value with the current time, this value can be retrieved with [`discord_timestamp()`](https://cogmasters.github.io/concord/group__DiscordClient.html#ga15a8fe1a6d3f30c18c6985b3afae11f5).

[Embed footer structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure):

* text: A string up to 2048 characters in length.
* icon_url: A valid URL that redirects to an image.

[Embed image structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure):

* url: Same as footer->icon_URL.

After creating the embed structure, now we will make the last structure so we can pass all the information needed to send a message.

The [`discord_create_message()`](https://cogmasters.github.io/concord/structdiscord__create__message.html) request expects its `params` to include the `embed` structure that will be sent over to the channel.

## Example bot

The following example outlines the recommended `static approach` way for sending an embed. For alternatives, you may take a look at this [example](examples/embed.c)

The only command from this bot is the `.sendembed` that only sends a basic embed.

```c
#include <stdio.h>

#include <concord/discord.h>
#include <concord/log.h>

void on_ready(struct discord *client, const struct discord_ready *bot) {
    (void) client;
    log_info("Logged in as %s!", bot->user->username);
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
                }
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
    struct discord *client = discord_config_init("config.json");

    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);

    discord_set_on_ready(client, &on_ready);
    discord_set_on_command(client, ".sendembed", &on_sendembed);

    discord_run(client);
}
```
