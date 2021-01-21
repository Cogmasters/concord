#include "json_scanf.h"
#include "gthb-v3.h"

namespace github { namespace v3 { namespace git_database {

  namespace create_a_blob {
    static struct response *
    load_resp (void * p, char * str, size_t len)
    {
      struct response * rep = p;
      json_scanf(str, len, "[url]%?s [sha]%?s", &rep->url, &rep->sha);
      return rep;
    }

    bool run (user_agent::data * ua, struct params * d, struct response * resp)
    {
      char * post_field [2] = { 0 };
      post_field[0] = d->content;
      user_agent::run(ua,
                      resp,
                      load_resp,
                      post_field,
                      "POST",
                      "/repos/%s/%s/git/blobs",
                      d->owner,
                      d->repo);
    }
  }

  namespace get_a_blob {
    static struct response *
    load_resp (void * p, char * str, size_t len)
    {
      struct response * rep = p;
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
    }
    bool run (user_agent::data * ua, struct params * p, struct response * resp) {
      user_agent::run(ua,
                      resp,
                      load_resp,
                      NULL,
                      "GET",
                      "/repos/%s/%s/git/blobs/%s",
                      p->owner,
                      p->repo,
                      p->file_sha);
    }
  }

            namespace create_a_commit {


            }

}}}
