#ifndef GITHUB_V3_H
#define GITHUB_V3_H
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json-common.h"
#include "json-scanf.h"
#include "http-common.h"


typedef void (load_obj_cb)(void *p_obj, char *str, size_t len);

namespace github {
namespace v3 {
namespace user_agent {

struct data {
  struct curl_slist *req_header; //the request header sent to the api
  struct api_resbody_s body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header
  CURL *ehandle; //the curl's easy handle used to perform requests
  struct _settings_s settings;
};

extern void init(struct data *api,
                 char username[],
                 char token[]);

extern void run(struct data *api,
                void *p_object,
                load_obj_cb *load_cb,
                struct api_resbody_s * body,
                enum http_method http_method,
                char endpoint[],
                ...);

} // user_agent
} // v3
} // github

namespace github {
namespace v3 {
namespace git_database {

struct author {
  char * date;
  char * name;
  char * email;
};


namespace create_a_blob {

struct params {
  char * owner;
  char * repo;
  char * content;
  char * encoding;
};
struct response {
  char * url;
  char * sha;
};
extern bool run (user_agent::data * ua,
                 struct params * p,
                 struct response * resp);

} // create_a_blob

namespace get_a_blob {

struct params {
  char * owner;
  char * repo;
  char * file_sha;
};
struct response {
  char * content;
  char * encoding;
  char * url;
  char * sha;
  int size;
  char * node_id;
};
extern bool run (user_agent::data * ua,
                 struct params * p,
                 struct response * resp);
} // get_a_blob

namespace create_a_commit {
}
namespace get_a_commit {

}

namespace list_matching_references {

struct params {
  char * owner;
  char * repo;
  char * ref;
  int per_page;
  int page;
};
struct response {
  struct {
    char * ref;
      char * node_id;
      char * url;
      struct {
        char * type;
        char * sha;
        char * url;
      } object;
  } * ref;
};

}

namespace get_a_reference {

struct params {
  char * owner;
  char * repo;
  char * ref;
};
struct response {
  char * ref;
  char * node_id;
  char * url;
  struct {
    char * type;
    char * sha;
    char * url;
  } object;
};

}

namespace create_a_reference {
struct params {
  char * owner;
  char * repo;
  char * ref;
  char * sha;
  char * key;
};
struct response {
  char * ref;
  char * node_id;
  char * url;
  struct {
    char * type;
    char * sha;
    char * url;
  } object;
};
}

namespace upate_a_reference {
struct params {
  char * owner;
  char * repo;
  char * ref;
  char * sha;
  bool force;
};
struct response {
  char * ref;
  char * node_id;
  char * url;
  struct {
    char * type;
    char * sha;
    char * url;
  } object;
};
}

namespace delete_a_reference {
struct params {
  char * owner;
  char * repo;
  char * ref;
};
extern bool run (user_agent::data * ua, struct params * p);
}

namespace create_a_tag {

}

namespace get_a_tag {

}

namespace create_a_tree {
struct params {
  char * owner;
  char * repo;
  struct {
    char * path;
    char * mode;
    char * type;
    char * sha;
    char * content;
  } * tree; // a null terminated array
};
struct response {
  char * sha;
  char * url;
  struct {
    char * path;
    char * mode;
    char * type;
    int size;
    char * sha;
    char * url;
  } * tree;
  bool truncated;
};
extern bool run(user_agent::data * ua,
                struct params * p,
                struct response * resp);
}


namespace get_a_tree {
  struct params {
    char * owner;
    char * repo;
    char * tree_sha;
    char * recursive;
  };
  struct response {
    char * sha;
    char * url;
    struct {
      char * path;
      char * mode;
      char * type;
      int size;
      char * sha;
      char * url;
    } * tree;
    bool truncated;
  };
} // get_a_tree

}
}
}

#endif //GITHUB_V3_H
