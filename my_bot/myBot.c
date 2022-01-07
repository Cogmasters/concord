#include <string.h> // strncmp()
#include <stdio.h>
#include <orca/discord.h>

void on_message(struct discord *client, const struct discord_message *msg)
{
  if (msg->author->bot) return; // Verify if the author, if it is, stops here.
  if (0 == strcmp(msg->content, "!ping")) {
    char ping[64];
    
    snprintf(ping, sizeof(ping), "Pong, `%d`ms", discord_get_ping(client)); // Setting value for char "ping";
    
    struct discord_create_message_params params = { .content = ping };
      
    discord_async_next(client, NULL); // Next request will be async.
    discord_create_message(client, msg->channel_id, &params, NULL); // Sending message.
  }
  if (0 == strncmp("!say ", msg->content, 5)) {
    char *content = msg->content + 5;
    
    struct discord_create_message_params params = { .content = content };
      
    discord_async_next(client, NULL); // Next request will be async.
    discord_create_message(client, msg->channel_id, &params, NULL); // Sending message.
  }
}

void on_ready(struct discord* client)
{
  const struct discord_user *bot = discord_get_self(client);

  log_info("Logged in as %s!", bot->username);
}

int main(void)
{
  struct discord *client = discord_config_init("config.json");

  discord_set_on_ready(client, &on_ready);
  discord_set_on_message_create(client, &on_message);
  discord_run(client);

  discord_cleanup(client);

  return 0;
}
