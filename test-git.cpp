#include "github-v3.h"

using namespace github::v3::user_agent;

void load(void * ptr, char * str, size_t len) {
  json_scanf(str, len, "[object][sha]%?s", ptr);
}

void load_file_sha(void * ptr, char * str, size_t len) {
  json_scanf(str, len, "[sha]%?s", ptr);
}

int commit (char * username,
            char * token,
            char * branch_name,
            char * filename,
            char * content,
            char * repo_name)
{
  data data = {0};
  init (&data, username, token);

  char * last_sha = NULL;
  run(&data, &last_sha, load, NULL,
      GET, "/repos/%s/%s/git/refs/heads/master",  username, repo_name);

  char * post = NULL;
  asprintf(&post, "{ [ref]: [refs/heads/%s], [sha]:[%s] }",
           branch_name, last_sha);

  run(&data, NULL, NULL, post,
      POST, "/repos/%s/%s/git/refs/", username, repo_name);

  char * file_sha = NULL;
  run(&data, &file_sha, load_file_sha, NULL,
      GET, "/repos/%s/%s/contents/project/%s", username, repo_name, filename);

  char * post_file = NULL;
  asprintf(&post_file,
           "{"
           "\"message\": \"update file\","
           "\"content\": \"%s\","
           "\"branch\": \"%s\","
           "}",
           content, branch_name);

  run(&data, NULL, NULL, post_file,
      PUT, "/repos/%s/%s/contents/project/%s", username, repo_name, filename);

  char * pull = NULL;
  asprintf(&pull,
           "{"
           "\"title\":\"%s\","
           "\"body\":\"please pull this in\","
           "\"head\":\"%s\","
           "\"base\":\"master\""
           "}",
           branch_name, branch_name);

  run(&data, NULL, NULL, pull,
      POST, "/repos/%s/%s/pulls", username, repo_name);
}

int main () {
  return 0;
}