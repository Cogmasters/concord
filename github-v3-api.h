#ifndef GITHUB_V3_API_H
#define GITHUB_V3_API_H
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json-common.h"
#include "json-scanf.h"
#include "http-common.h"
#include "github-v3-ua.h"

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

#endif //GITHUB_V3_API_H