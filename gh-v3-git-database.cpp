#include "json_scanf.h"

namespace github { 
namespace v3 {
namespace git_database {

namespace create_a_blob {

struct data {
    char *accept;
    char *owner;
    char *repo;
    char *content;
    char *encoding;
};
struct response {
    char *url;
    char *sha;
};

static struct response*
load_ret_object(void *p, char *str, size_t len)
{
  struct response *rep = p;
  json_scanf(str, len, "[url]%?s [sha]%?s", &rep->url, &rep->sha);
  return rep;
}

bool 
run(user_agent::data *ua, struct data *d)
{
  struct response *rep = calloc(1, sizeof(*rep));
  char *post_field[2] = { 0 };

  post_field[0] = d->content;
  user_agent::run(ua,
                  rep,
                  load_ret_object,
                  post_field,
                  POST, "/repos/%s/%s/git/blobs", d->owner, d->repo);
}

} // namespace create_a_blob

} // namespace git_database
} // namespace v3
} // namespace github
