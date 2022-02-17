#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <concord/discord.h>

void on_ready(struct discord *client)
{
  const struct discord_user *bot = discord_get_self(client);

  log_info("8ball-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void eight_ball(struct discord *client, const struct discord_message *msg) {

	if(msg->author->bot) return;

	srand(time(0));//generate seed for randomizer

	char *phrases[20] = { //List of 8ball phrases/responses
		":green_circle:It is certain.",
		":green_circle:It is decidedly so.",
		":green_circle:Without a doubt.",
		":green_circle:Yes definitely.",
		":green_circle:You may rely on it.",
		":green_circle:As I see it, yes.",
		":green_circle:Most likely.",
		":green_circle:Outlook good.",
		":green_circle:Yes.",
		":green_circle:Signs Point to Yes.",
		":yellow_circle:Reply hazy, try again.",
		":yellow_circle:Ask again later.",
		":yellow_circle:Better not tell you now.",
		":yellow_circle:Cannot predict now.",
		":yellow_circle:Concentrate and ask again.",
		":red_circle:Don't count on it.",
		":red_circle:My reply is no.",
		":red_circle:My sources say no.",
		":red_circle:Outlook not so good.",
		":red_circle: Very doubtful."
		};

	int32_t answer = rand() % 20; //random number from 0 - 20

	struct discord_embed embed = { // simple embed message
		.title = ":8ball:8-Ball",
		.description = phrases[answer]
	};

	
	struct discord_create_message_params params = { .embed = &embed};
	discord_create_message(client, msg->channel_id, &params, NULL);

}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  ccord_global_init();
  struct discord *client = discord_config_init(config_file);

  discord_set_on_ready(client, &on_ready);

  discord_set_on_command(client, "8ball", &eight_ball);

  printf("\n\nThis is a bot to demonstrate an easy to make 8ball response to a question.\n"
	"1. type '8ball (question)' in chat\n"
	"\nTYPE ANY KEY TO START BOT\n");

  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);
  ccord_global_cleanup();

}
