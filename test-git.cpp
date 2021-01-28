#include "github-v3-user-agent.hpp"
#include "settings.h"
#include "ntl.h"

struct file {
  char * path;
  char * content;
  char * sha;
};
namespace git = github::v3::user_agent;

void load_object_sha(char * str, size_t len, void * ptr) {
  fprintf (stderr, "%.*s\n", len, str);
  json_scanf(str, len, "[object][sha]%?s", ptr);
}

void load_sha(char *str, size_t len, void *ptr) {
  fprintf (stderr, "%.*s\n", len, str);
  json_scanf(str, len, "[sha]%?s", ptr);
}

void log(char * str, size_t len, void * ptr) {
  fprintf (stderr, "%.*s\n", len, str);
}

static struct api_resbody_s  body = { 0, 0 };

static struct resp_handle handle = {
  .ok_cb = NULL, .ok_obj = NULL,
  .err_cb = log, .err_obj = NULL
};

int commit (git::dati *data, char * owner, char * repo,
            char * branch, char * filename, char * content) {
  //1. get the head of the master branch
  char * last_sha = NULL;
  handle.ok_cb = load_object_sha;
  handle.ok_obj = &last_sha;
  git::run(data, &handle, NULL,
      HTTP_GET, "/repos/%s/%s/git/refs/heads/master",  owner, repo);

  //2. create a new branch from last commit
  body.size = json_asprintf(&body.str,
                            "{ |ref|: |refs/heads/%s|, |sha|:|%s| }",
                            branch, last_sha);

  fprintf(stderr, "%.*s\n", body.size, body.str);
  handle.ok_cb = log;
  handle.ok_obj = NULL;
  git::run(data, &handle, &body,
                  HTTP_POST, "/repos/%s/%s/git/refs", owner, repo);

  //3. get sha of file be replaced
  char * file_sha = NULL;
  handle.ok_cb = load_sha;
  handle.ok_obj = &file_sha;
  git::run(data, &handle, NULL,
      HTTP_GET, "/repos/%s/%s/contents/%s", owner, repo, filename);

  //4. update a file
  body.size = json_asprintf(&body.str,
                            "{"
                                    "|message|:|update file|,"
                                    "|content|:|%s|,"
                                    "|branch|:|%s|,"
                                    "|sha|:|%s|"
                            "}",
                            content, branch, file_sha);

  fprintf(stderr, "%.*s\n", body.size, body.str);
  handle.ok_cb = log;
  handle.ok_obj = NULL;
  git::run(data, &handle, &body,
      HTTP_PUT, "/repos/%s/%s/contents/%s", owner, repo, filename);


  // 5. create a pull request
  body.size = json_asprintf(&body.str,
                            "{"
                               "|title|:|%s|,"
                               "|body|:|please pull this in|,"
                               "|head|:|%s|,"
                               "|base|:|master|"
                            "}",
                            branch, branch);

  handle.ok_cb = log;
  handle.ok_obj = NULL;
  git::run(data, &handle, &body,
                  HTTP_POST, "/repos/%s/%s/pulls", owner, repo);
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

  struct file ** files = NULL;
  if (argc >= 3) {
    files = (struct file **) ntl_calloc(argc - 2, sizeof(struct file));
    for (int i = 2; files[i-2]; ++i) {
      files[i-2]->path = argv[i];
    }
  }
  else {
    return 0;
  }

  git::dati data = {0};
  curl_global_init(CURL_GLOBAL_ALL);
  git::init (&data, settings.github.username, settings.github.token);
  char * repo = "test_repo";
  char * owner = settings.github.username;
  commit(&data, owner, repo, "test_2", "x/test.c", "LypuZXcgY29kZSovCg==");
  return 0;
}
