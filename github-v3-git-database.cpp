#include "github-v3.hpp"
#include "ntl.h"

namespace github {
namespace v3 {
namespace git_database {

namespace create_a_blob {

static void
log_resp (void * p, char * str, size_t len)
{
  fprintf(stderr, "%.*s", len, str);
}

static void
load_resp (void * p, char * str, size_t len)
{
  struct response * rep = (struct response *)p;
  json_scanf(str, len, "[url]%?s [sha]%?s", &rep->url, &rep->sha);
  return;
}


bool run (user_agent::data * ua, struct params * d, struct response * resp)
{
  struct resp_handle handle = {
          .ok_cb = load_resp, .ok_obj = resp,
          .err_cb = log_resp, .err_obj = NULL
  };
  struct api_resbody_s body;
  body.size = json_asprintf(&body.str, "{|content|:|%s|, |encoding|:|utf-8| }",
                            d->content);
  user_agent::run(ua,
                  &handle,
                  &body,
                  POST,
                  "/repos/%s/%s/git/blobs",
                  d->owner,
                  d->repo);
  free(body.str);
}

} // create_a_blob

namespace get_a_blob {

static void
load_resp (void * p, char * str, size_t len)
{
  struct response * rep = (struct response *)p;
  json_scanf(str, len,
             "[content]%?s"
             "[encoding]%?s"
             "[url]%?s"
             "[sha]%?s"
             "[size]%d"
             "[node_id]%?s"
             "",
             &rep->content,
             &rep->encoding,
             &rep->url,
             &rep->sha,
             &rep->size,
             &rep->node_id);
  return;
}
bool run (user_agent::data * ua, struct params * p, struct response * resp) {
  struct resp_handle handle = { .ok_cb = load_resp, .ok_obj = resp };
  user_agent::run(ua,
                  &handle,
                  NULL,
                  GET,
                  "/repos/%s/%s/git/blobs/%s",
                  p->owner,
                  p->repo,
                  p->file_sha);
}

} // get_a_blob

inline namespace tree {

static void token_to_tree (void * from, void * to)
{
  struct json_token * from_t = (struct json_token *) from;
  struct tree * to_t = (struct tree *) to;
  json_scanf(from_t->start, from_t->length,
             "[path]%?s"
             "[mode]%?s"
             "[type]%?s"
             "[size]%d"
             "[sha]%?s"
             "[url]%?s",
             &to_t->path,
             &to_t->mode,
             &to_t->type,
             &to_t->size,
             &to_t->sha,
             &to_t->url);
}

static void
load_resp(void * p, char * str, size_t len) {
  struct response * resp = (struct response *)p;
  struct json_token ** token_ptrs = NULL;;
  json_scanf(str, len,
             "[sha]%?s"
             "[url]%?s"
             "[tree]%A"
             "[truncated]%b",
             &resp->sha,
             &resp->url,
             &token_ptrs,
             &resp->truncated);

  resp->tree = (struct tree **)
    ntl_fmap((void **)token_ptrs, sizeof(struct tree), token_to_tree);
}

namespace create_a_tree {
static int
print_tree (char * str, size_t size, void *p, bool is_last) {
  struct params::tree * t = (struct params::tree *)p;
  int ret =
    json_snprintf(str, size,
                  "{"
                  "|path|:|%s|, |mode|:|%s|, |type|:|%s|, |sha|:|%s|"
                  "}",
                  t->path, t->mode, t->type, t->sha);
  return ret;
}

static int
tree_to_json (char * str, size_t size, struct params::tree ** tree) {
  return ntl_sn2str(str, size, (void **) tree, print_tree);
}

static void
params_to_body (char ** buf, struct params * p) {
  json_asprintf(buf, "");
}

bool run(user_agent::data *ua, struct params *p, struct response *resp) {
  struct resp_handle handle = {.ok_cb = load_resp, .ok_obj = resp};
  struct api_resbody_s body;

  /*
  user_agent::run(ua,
                  &handle,
                  NULL,
                  POST,
                  "/repos/%s/%s/git/trees",
                  p->owner,
                  p->repo,
                  p->file_sha);
                  */
}
}
}

namespace create_a_commit {


} // create_a_commit

namespace get_a_tree {

}

}}}
