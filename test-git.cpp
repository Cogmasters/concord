#include "github-v3-ua.hpp"
#include "settings.h"
#include "ntl.h"


using namespace github::v3;

struct file {
  char * path;
  char * content;
  char * sha;
};

void load(void * ptr, char * str, size_t len) {
  fprintf (stderr, "%.*s\n", len, str);
  json_scanf(str, len, "[object][sha]%?s", ptr);
}

void load_file_sha(void * ptr, char * str, size_t len) {
  fprintf (stderr, "%.*s\n", len, str);
  json_scanf(str, len, "[sha]%?s", ptr);
}

void log(void * ptr, char * str, size_t len) {
  fprintf (stderr, "%.*s\n", len, str);
}

int commit (char * username, char * token,
            char * repo_name, char * branch_name,
            char * filename, char * content)
{
  user_agent::data data = {0};
  curl_global_init(CURL_GLOBAL_ALL);
  user_agent::init (&data, username, token);
  struct api_resbody_s  body = { 0, 0 };
  struct resp_handle handle = {
          .ok_cb = NULL, .ok_obj = NULL,
          .err_cb = log, .err_obj = NULL
  };

  //1. get the head of the master branch
  char * last_sha = NULL;
  handle.ok_cb = load;
  handle.ok_obj = &last_sha;
  user_agent::run(&data, &handle, NULL,
      GET, "/repos/%s/%s/git/refs/heads/master",  username, repo_name);

  //2. create a new branch from last commit
  body.size = json_asprintf(&body.str,
                            "{ |ref|: |refs/heads/%s|, |sha|:|%s| }",
                            branch_name, last_sha);

  fprintf(stderr, "%.*s\n", body.size, body.str);
  handle.ok_cb = log;
  handle.ok_obj = NULL;
  user_agent::run(&data, &handle, &body, POST, "/repos/%s/%s/git/refs",
                  username, repo_name);

  //3. get sha of file be replaced
  char * file_sha = NULL;
  handle.ok_cb = load_file_sha;
  handle.ok_obj = &file_sha;
  user_agent::run(&data, &handle, NULL,
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
  handle.ok_cb = log;
  handle.ok_obj = NULL;
  user_agent::run(&data, &handle, &body,
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

  handle.ok_cb = log;
  handle.ok_obj = NULL;
  user_agent::run(&data, &handle, &body,
                  POST, "/repos/%s/%s/pulls", username, repo_name);
  curl_global_cleanup();
  return 0;
}


void create_blobs (user_agent::data * data, struct file ** files,
                   char * owner, char * repo)
{
  int i;
  struct api_resbody_s body;
  struct resp_handle handle = {
    .ok_cb = NULL, .ok_obj = NULL,
    .err_cb = log, .err_obj = NULL
  };

  char * file_sha = NULL;
  handle.ok_cb = load_file_sha;
  handle.ok_obj = &file_sha;

  for (i = 0; files[i]; i++) {
    body.size = json_asprintf(&body.str,
                              "{ |content|:|%s|, |encoding|:|utf-8| }",
                              files[i]->content);
    user_agent::run(data, &handle, &body,
                    POST, "/repos/%s/%s/git/blobs", owner, repo);
    files[i]->sha = file_sha;
    free(body.str);
  }
}

static int
to_tree_node(char * str, size_t size, void *p)
{
  struct file * f = (struct file *)p;
  return json_snprintf(str, size,
                "{"
                  "|path|:|%s|,"
                  "|mode|:|100644|,"
                  "|type|:|blob|,"
                  "|sha|:|%s|,"
                "}%c",
                f->path,
                f->sha);
}

static int
nodes_to_json (char * str, size_t size, void *p)
{
  struct ntl_str_delimiter d = { ",", "" };
  return ntl_sn2str(str, size, (void **)p, &d, to_tree_node);
}

static char *
create_tree (user_agent::data * data, struct file ** files,
             char * tree_sha, char * owner, char * repo)
{
  struct api_resbody_s body;
  struct resp_handle handle = {
    .ok_cb = NULL, .ok_obj = NULL,
    .err_cb = log, .err_obj = NULL
  };

  body.size = json_asprintf(&body.str,
                            "{"
                            "|tree|:%F,"
                            "|base_tree|:|%s|"
                            "}", nodes_to_json, files, tree_sha);
  char * new_tree_sha = NULL;
  handle.ok_cb = load_file_sha;
  handle.ok_obj = &new_tree_sha;
  user_agent::run(data, &handle, &body,
                  POST, "/repos/%s/%s/git/trees", owner, repo);
  free(body.str);
  return new_tree_sha;
}

static char *
create_a_commit (user_agent::data * data, char * tree_sha,
                 char * last_cmmit_sha, char * message,
                 char * owner, char * repo)
{
  struct api_resbody_s body;
  struct resp_handle handle = {
    .ok_cb = NULL, .ok_obj = NULL,
    .err_cb = log, .err_obj = NULL
  };

  char * new_commit_sha = NULL;
  handle.ok_cb = load_file_sha;
  handle.ok_obj = &new_commit_sha;
  body.size = json_asprintf(&body.str,
                            "{"
                              " |message|:|%s|,"
                              " |tree|:|%s|,"
                              " |parents|: [ |%s| ]"
                            "}",
                            message, tree_sha, last_cmmit_sha);
  user_agent::run(data, &handle, &body,
                  POST, "/repos/%s/%s/git/commits", owner, repo);
  free(body.str);
  return new_commit_sha;
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
