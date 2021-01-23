#include "github-v3.hpp"

namespace github {
namespace v3 {
namespace git_database {

namespace create_a_blob {

static void
load_resp (void * p, char * str, size_t len)
{
  struct response * rep = (struct response *)p;
  json_scanf(str, len, "[url]%?s [sha]%?s", &rep->url, &rep->sha);
  return;
}

bool run (user_agent::data * ua, struct params * d, struct response * resp)
{
  char * post_field [2] = { 0 };
  post_field[0] = d->content;
  struct resp_handle handle = { .cb = load_resp, .obj = resp};
  user_agent::run(ua,
                  &handle,
                  NULL,
                  POST,
                  "/repos/%s/%s/git/blobs",
                  d->owner,
                  d->repo);
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
  struct resp_handle handle = { .cb = load_resp, .obj = resp };
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

namespace create_a_commit {


} // create_a_commit

}}}
