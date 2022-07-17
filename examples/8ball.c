#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "discord.h"
#include "log.h"

void
print_usage(void)
{
    printf("\n\nThis is a bot to demonstrate an easy to make 8ball response "
           "to a question.\n"
           "1. type '8ball (question)' in chat\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("8ball-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
eight_ball(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    /* List of 8ball phrases/responses */
    char *phrases[] = {
        ":green_circle: It is certain.",
        ":green_circle: It is decidedly so.",
        ":green_circle: Without a doubt.",
        ":green_circle: Yes definitely.",
        ":green_circle: You may rely on it.",
        ":green_circle: As I see it, yes.",
        ":green_circle: Most likely.",
        ":green_circle: Outlook good.",
        ":green_circle: Yes.",
        ":green_circle: Signs Point to Yes.",
        ":yellow_circle: Reply hazy, try again.",
        ":yellow_circle: Ask again later.",
        ":yellow_circle: Better not tell you now.",
        ":yellow_circle: Cannot predict now.",
        ":yellow_circle: Concentrate and ask again.",
        ":red_circle: Don't count on it.",
        ":red_circle: My reply is no.",
        ":red_circle: My sources say no.",
        ":red_circle: Outlook not so good.",
        ":red_circle: Very doubtful.",
    };
    /* random index to phrases array */
    int answer = rand() % (sizeof(phrases) / sizeof(*phrases));

    struct discord_embed embeds[] = { {
        .title = ":8ball: 8-Ball",
        .description = phrases[answer],
    } };

    struct discord_create_message params = {
        .embeds =
            &(struct discord_embeds){
                .size = sizeof(embeds) / sizeof *embeds,
                .array = embeds,
            },
    };
    discord_create_message(client, event->channel_id, &params, NULL);
}

int
main(int argc, char *argv[])
{
    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    srand(time(0));

    ccord_global_init();
    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Couldn't initialize client");

    discord_set_on_ready(client, &on_ready);

    discord_set_on_command(client, "8ball", &eight_ball);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
