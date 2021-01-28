#include "github-v3.hpp"
#include "settings.h"
#include "ntl.h"

namespace git = github::v3::git_op;

int main (int argc, char ** argv)
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct bot_settings settings;
  bot_settings_init (&settings, config_file);

  git::file ** files = NULL;
  if (argc >= 3) {
    files = (git::file **) ntl_calloc(argc - 2, sizeof(git::file));
    for (int i = 2; files[i-2]; ++i) {
      files[i-2]->path = argv[i];
    }
  }
  else {
    return 0;
  }

  curl_global_init(CURL_GLOBAL_ALL);
  git::dati * data = git::init (settings.github.username,
                                settings.github.token, "repo.config");

  git::create_blobs(data, files);
  char * head_commit_sha = git::get_head_commit(data);
  char * base_tree_sha = git::get_tree_sha(data, head_commit_sha);
  char * tree_sha = git::create_tree(data, base_tree_sha, files);
  char * commit_sha =
    git::create_a_commit(data, tree_sha, head_commit_sha,
                         "committed thru github API");

  char new_branch[256];
  snprintf(new_branch, sizeof(new_branch), "n%ld", time(NULL));
  git::create_a_branch(data, head_commit_sha, new_branch);
  git::update_a_commit(data, new_branch, commit_sha);
  git::create_a_pull_request(data, new_branch);
  return 0;
}
