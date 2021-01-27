#ifndef GITHUB_V3_API_H
#define GITHUB_V3_API_H
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json-scanf.h"
#include "http-common.h"
#include "github-v3-user-agent.hpp"

/*
 * There is a 1-1 mapping between https://docs.github.com/en/rest/reference
 * and APIs defined here
 */
namespace github {
namespace v3 {
namespace git_database {
// https://docs.github.com/en/rest/reference/git

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
bool run (user_agent::dati * ua,
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
bool run (user_agent::dati * ua,
          struct params * p,
          struct response * resp);
} // get_a_blob

namespace create_a_commit {
}
namespace get_a_commit {

}

inline namespace tree {
struct tree {
  char *path;
  char *mode;
  char *type;
  int size;
  char *sha;
  char *url;
};

struct response {
  char * sha;
  char * url;
  struct tree ** tree;
  bool truncated;
};

namespace create_a_tree {
struct params {
  char *owner;
  char *repo;
  struct tree {
    char * path;
    char * mode;
    char * type;
    char * sha;  // either sha or content
    char * content;
  } ** tree;
  char * base_tree;
};
bool run(user_agent::dati *ua, struct params *p, struct response *resp);
void free_params (struct params *p);
void free_response (struct response * resp);
}

namespace get_a_tree {
struct params {
  char *owner;
  char *repo;
  char *tree_sha;
  char *recursive;
};
struct response {
  char *sha;
  char *url;
  struct tree *tree; // NULL TOKEN terminated
  bool truncated;
};

bool run(user_agent::dati *ua,
         struct params *p,
         struct response *resp);
}
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
extern bool run (user_agent::dati * ua, struct params * p);
}

namespace create_a_tag {

}

namespace get_a_tag {

}

namespace create_a_tree {
#if 0
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
#endif
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
extern bool run(user_agent::dati * ua,
                struct params * p,
                struct response * resp);
}


namespace get_a_tree {
#if 0
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
#endif
} // get_a_tree

} // git_database


namespace repositories {

} // repositories

} // v3
} // github

#endif //GITHUB_V3_API_H
