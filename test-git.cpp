#include "github-v3-ua.hpp"
#include "settings.h"
#include "ntl.h"


using namespace github::v3;

struct file {
  char * path;
  char * content;
  char * sha;
};

void load(char * str, size_t len, void * ptr) {
  fprintf (stderr, "%.*s\n", len, str);
  json_scanf(str, len, "[object][sha]%?s", ptr);
}

void load_file_sha(char * str, size_t len, void * ptr) {
  fprintf (stderr, "%.*s\n", len, str);
  json_scanf(str, len, "[sha]%?s", ptr);
}

void log(char * str, size_t len, void * ptr) {
  fprintf (stderr, "%.*s\n", len, str);
}

struct api_resbody_s  body = { 0, 0 };

struct resp_handle handle = {
  .ok_cb = NULL, .ok_obj = NULL,
  .err_cb = log, .err_obj = NULL
};

int commit (user_agent::data *data, char * username, char * repo_name,
            char * branch_name, char * filename, char * content) {
  //1. get the head of the master branch
  char * last_sha = NULL;
  handle.ok_cb = load;
  handle.ok_obj = &last_sha;
  user_agent::run(data, &handle, NULL,
      GET, "/repos/%s/%s/git/refs/heads/master",  username, repo_name);

  //2. create a new branch from last commit
  body.size = json_asprintf(&body.str,
                            "{ |ref|: |refs/heads/%s|, |sha|:|%s| }",
                            branch_name, last_sha);

  fprintf(stderr, "%.*s\n", body.size, body.str);
  handle.ok_cb = log;
  handle.ok_obj = NULL;
  user_agent::run(data, &handle, &body,
                  POST, "/repos/%s/%s/git/refs", username, repo_name);

  //3. get sha of file be replaced
  char * file_sha = NULL;
  handle.ok_cb = load_file_sha;
  handle.ok_obj = &file_sha;
  user_agent::run(data, &handle, NULL,
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
  user_agent::run(data, &handle, &body,
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
  user_agent::run(data, &handle, &body,
                  POST, "/repos/%s/%s/pulls", username, repo_name);
  curl_global_cleanup();
  return 0;
}

char * get_last_commit (user_agent::data * data,
                        char * username, char * repo_name) {
  char * sha = NULL;
  handle.ok_cb = load;
  handle.ok_obj = &sha;
  user_agent::run(data, &handle, NULL,
                  GET, "/repos/%s/%s/git/refs/heads/master",  username, repo_name);
  return sha;
}

char * get_tree_sha(user_agent::data * data,
                    char * owner, char * repo, char * commit_sha) {

  fprintf(stderr, "===get-tree-sha==\n");
  char * sha = NULL;
  handle.ok_cb = load_file_sha;
  handle.ok_obj = &sha;
  user_agent::run(data, &handle, NULL,
                  GET, "/repos/%s/%s/git/trees/%s", owner, repo, commit_sha);

  fprintf(stderr, "tree-sha:%s\n", sha);
  return sha;
}

void create_blobs (user_agent::data * data, char * owner, char * repo,
                   struct file ** files) {
  int i;
  char * file_sha = NULL;
  handle.ok_cb = load_file_sha;
  handle.ok_obj = &file_sha;

  for (i = 0; files[i]; i++) {
    fprintf(stderr, "===creating blob for %s===\n", files[i]->path);
    body.size = json_asprintf(&body.str,
                              "{ |content|:|%s|, |encoding|:|utf-8| }",
                              files[i]->content);
    user_agent::run(data, &handle, &body,
                    POST, "/repos/%s/%s/git/blobs", owner, repo);
    fprintf(stderr, "file-sha %s\n", file_sha);
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
                  "|sha|:|%s|"
                "}", f->path, f->sha);
}

static int
nodes_to_json (char * str, size_t size, void *p)
{
  return ntl_sn2str(str, size, (void **)p, NULL, to_tree_node);
}

static char *
create_tree (user_agent::data * data,
             char * owner, char * repo,
             char * tree_sha,
             struct file ** files)
{
  fprintf(stderr, "==create-tree==\n");
  body.size = json_asprintf(&body.str,
                            "{"
                            "|tree|:%F,"
                            "|base_tree|:|%s|"
                            "}", nodes_to_json, files, tree_sha);
  char * new_tree_sha = NULL;
  handle.ok_cb = load_file_sha;
  handle.ok_obj = &new_tree_sha;
  fprintf(stderr, "%s\n", body.str);
  user_agent::run(data, &handle, &body,
                  POST, "/repos/%s/%s/git/trees", owner, repo);
  free(body.str);
  fprintf(stderr, "new-tree-sha:%s\n", new_tree_sha);
  return new_tree_sha;
}

static char *
create_a_commit (user_agent::data * data,
                 char * owner, char * repo,
                 char * tree_sha,
                 char * last_cmmit_sha, char * message)
{
  fprintf(stderr, "===create-a-commit===\n");
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
  fprintf(stderr, "commit-sha:%s\n", new_commit_sha);
  return new_commit_sha;
}

static void
update_a_commit (user_agent::data * data,
                 char * owner, char * repo, char * commit_sha)
{
  fprintf(stderr, "===update-a-commit===\n");
  handle.ok_cb = log;
  body.size = json_asprintf(&body.str, "{|sha|:|%s|}", commit_sha);
  fprintf(stderr, "%s\n", body.str);
  user_agent::run(data, &handle, &body,
                  PATCH, "/repos/%s/%s/git/refs/heads/master", owner, repo);
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

  user_agent::data data = {0};
  curl_global_init(CURL_GLOBAL_ALL);
  user_agent::init (&data, settings.github.username, settings.github.token);
  char * repo = "test_repo";

  if (0)
    commit(&data, settings.github.username,
           repo, "test_2", "x/test.c", "LypuZXcgY29kZSovCg==");
  else {
    struct file files [] = {
      {.path = "test/f.c", .content = "the contentxx of f.c"},
      {.path = "test/g.c", .content = "the contentxx of g.c"}
    };
    struct file * fptrs [] = { &files[0], &files[1], NULL};

    char * head_commit_sha =
      get_last_commit(&data, settings.github.username, repo);
    char * tree_sha = get_tree_sha(&data, settings.github.username, repo,
                                   head_commit_sha);

    create_blobs(&data, settings.github.username, repo, fptrs);
    char * new_tree_sha =
      create_tree(&data, settings.github.username, repo, tree_sha, fptrs);
    char * new_commit_sha =
      create_a_commit(&data, settings.github.username, repo, new_tree_sha,
                      head_commit_sha, "committed thru github API");
    update_a_commit(&data, settings.github.username, repo, new_commit_sha);
  }
  return 0;
}
