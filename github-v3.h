#ifndef GITHUB_V3_H
#define GITHUB_V3_H

typedef void (load_obj_cb)(void *p_obj, char *str, size_t len);

namespace github { namespace v3 { namespace user_agent {
  struct data;
  extern void run(
          struct data *api,
          void *p_object,
          load_obj_cb *load_cb,
          char postfields[],
          enum http_method http_method,
          char endpoint[],
          ...);
}}}

namespace github { namespace v3 { namespace git_database {


  namespace create_a_blob {
    struct payload {
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
                     struct payload * p,
                     struct response * resp);
  }

  namespace get_a_blob {
    struct payload {
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
                     struct payload * p,
                     struct response * resp);
  }

  namespace create_a_commit {

  }
  namespace get_a_commit {

  }

  namespace list_matching_references {

  }
  namespace get_a_reference {

  }
  namespace create_a_reference {

  }
  namespace upate_a_reference {

  }
  namespace delete_a_reference {

  }

  namespace create_a_tag {

  }
  namespace get_a_tag {

  }

  namespace create_a_tree {

  }
  namespace get_a_tree {

  }

}}}

#endif //GITHUB_V3_H
