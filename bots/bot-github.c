#include "github.h"

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct github* client = github_config_init(config_file, "../.cee-repo");
  struct github_user user;
  github_user_init(&user);

  github_get_user(client, "LucasMull", &user);

  github_user_cleanup(&user);
}
