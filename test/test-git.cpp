#include "github-v3-user-agent.hpp"
#include "orka-utils.h"
#include "json-scanf.h"

struct file {
  char * path;
  char * content;
  char * sha;
};
namespace git = github::v3::user_agent;

void load_object_sha(char * str, size_t len, void * ptr) {
  fprintf (stderr, "%.*s\n", (int)len, str);
  json_scanf(str, len, "[object][sha]%?s", ptr);
}

void load_sha(char *str, size_t len, void *ptr) {
  fprintf (stderr, "%.*s\n", (int)len, str);
  json_scanf(str, len, "[sha]%?s", ptr);
}

void log(char * str, size_t len, void * ptr) {
  fprintf (stderr, "%.*s\n", (int)len, str);
}

static struct sized_buffer  body = { 0, 0 };

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
  body.size = json_asprintf(&body.start,
                            "{ |ref|: |refs/heads/%s|, |sha|:|%s| }",
                            branch, last_sha);

  fprintf(stderr, "%.*s\n", (int)body.size, body.start);
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
  body.size = json_asprintf(&body.start,
                            "{"
                                    "|message|:|update file|,"
                                    "|content|:|%s|,"
                                    "|branch|:|%s|,"
                                    "|sha|:|%s|"
                            "}",
                            content, branch, file_sha);

  fprintf(stderr, "%.*s\n", (int)body.size, body.start);
  handle.ok_cb = log;
  handle.ok_obj = NULL;
  git::run(data, &handle, &body,
      HTTP_PUT, "/repos/%s/%s/contents/%s", owner, repo, filename);


  // 5. create a pull request
  body.size = json_asprintf(&body.start,
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

  struct orka_config config;
  orka_config_init (&config, "GIT HTTP", config_file);
  char *username = orka_config_get_field(&config, "github.username");
  char *token = orka_config_get_field(&config, "github.token");

  git::dati data = {0};
  curl_global_init(CURL_GLOBAL_ALL);
  git::init(&data, username, token);
  char * repo = "test_repo";
  commit(&data, username, repo, "test_2", "x/test.c", "LypuZXcgY29kZSovCg==");
  return 0;
}
