#include "github-v3.h"
#include "settings.h"

using namespace github::v3::user_agent;

void load(void * ptr, char * str, size_t len) {
  json_scanf(str, len, "[object][sha]%?s", ptr);
}

void load_file_sha(void * ptr, char * str, size_t len) {
  json_scanf(str, len, "[sha]%?s", ptr);
}

int commit (char * username, char * token,
            char * repo_name, char * branch_name,
            char * filename, char * content)
{
  data data = {0};
  curl_global_init(CURL_GLOBAL_ALL);
  init (&data, username, token);
  struct api_resbody_s  body = { 0, 0 };

  //1. get the head of the master branch
  char * last_sha = NULL;
  run(&data, &last_sha, load, NULL,
      GET, "/repos/%s/%s/git/refs/heads/master",  username, repo_name);

  //2. create a new branch from last commit
  body.size = json_asprintf(&body.str,
                            "{ |ref|: |refs/heads/%s|, |sha|:|%s| }",
                            branch_name, last_sha);

  fprintf(stderr, "%.*s\n", body.size, body.str);
  run(&data, NULL, NULL, &body, POST, "/repos/%s/%s/git/refs", username, repo_name);

  //3. get sha of file be replaced
  char * file_sha = NULL;
  run(&data, &file_sha, load_file_sha, NULL,
      GET, "/repos/%s/%s/contents/%s", username, repo_name, filename);

  //4. update a file
  body.size = json_asprintf(&body.str,
                            "{"
                                    "|message|:|update file|,"
                                    "|content|:|%s|,"
                                    "|branch|:|%s|,"
                                    "|sha|:|%s|"
                            "}",
                            content, branch_name, file_sha);

  fprintf(stderr, "%.*s\n", body.size, body.str);
  run(&data, NULL, NULL, &body,
      PUT, "/repos/%s/%s/contents/%s", username, repo_name, filename);


  // 5. create a pull request
  body.size = json_asprintf(&body.str,
                            "{"
                               "|title|:|%s|,"
                               "|body|:|please pull this in|,"
                               "|head|:|%s|,"
                               "|base|:|master|"
                            "}",
                            branch_name, branch_name);

  run(&data, NULL, NULL, &body,
      POST, "/repos/%s/%s/pulls", username, repo_name);
  curl_global_cleanup();
  return 0;
}

int main (int argc, char ** argv)
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct bot_settings settings;
  bot_settings_init (&settings, config_file);

  commit(settings.github.username, settings.github.token,
         "test_repo", "test_2", "test.c", "LypuZXcgY29kZSovCg==");
  return 0;
}
