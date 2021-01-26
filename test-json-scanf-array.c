#include "json-scanf.h"
#include <stdio.h>
#include <stdlib.h>
#include "jsmn.h"
#include "ntl.h"

#if 0
static char * print_token(jsmntype_t t) {
  switch(t) {
    case JSMN_UNDEFINED: return "undefined";
    case JSMN_OBJECT: return "object";
    case JSMN_ARRAY: return "array";
    case JSMN_STRING: return "string";
    case JSMN_PRIMITIVE: return "primitive";
  }
}
#endif

char test_string [] =
"{\n"
  "|sha|: |9fb037999f264ba9a7fc6274d15fa3ae2ab98312|,\n"
  "|url|: |https://api.github.com/repos/octocat/Hello-World/trees/9fb037999f264ba9a7fc6274d15fa3ae2ab98312|,\n"
  "|tree|: [\n"
  "{"
  "  |path|: |file.rb|,\n"
  "  |mode|: |100644|,\n"
  "  |type|: |blob|,\n"
  "  |size|: 30,\n"
  "  |sha|: |44b4fc6d56897b048c772eb4087f854f46256132|,\n"
  "  |url|: |https://api.github.com/repos/octocat/Hello-World/git/blobs/44b4fc6d56897b048c772eb4087f854f46256132|\n"
  "},\n"
  "{\n"
  "  |path|: |subdir|,\n"
  "  |mode|: |040000|,\n"
  "  |type|: |tree|,\n"
  "  |sha|: |f484d249c660418515fb01c2b9662073663c242e|,\n"
  "  |url|: |https://api.github.com/repos/octocat/Hello-World/git/blobs/f484d249c660418515fb01c2b9662073663c242e|\n"
  "},\n"
  "{\n"
  "  |path|: |exec_file|,\n"
  "  |mode|: |100755|,\n"
  "  |type|: |blob|,\n"
  "  |size|: 75,\n"
  "  |sha|: |45b983be36b73c0788dc9cbcb76cbb80fc7bb057|,\n"
  "  |url|: |https://api.github.com/repos/octocat/Hello-World/git/blobs/45b983be36b73c0788dc9cbcb76cbb80fc7bb057|\n"
  "}\n"
  "],\n"
  "|truncated|: false\n"
"}";

struct tree_node {
  char * path;
  char * mode;
  char * type;
  int size;
  char * sha;
  char * url;
};

void load_tree_node (char * str, size_t len, void * p) {
  struct tree_node * n = (struct tree_node *)p;
  json_scanf(str, len,
             "[path]%?s"
             "[mode]%?s"
             "[type]%?s"
             "[size]%d"
             "[sha]%?s"
             "[url]%?s",
             &n->path,
             &n->mode,
             &n->type,
             &n->size,
             &n->sha,
             &n->url);
}
static int
print_array (char * str, size_t len, void * p)
{
  struct tree_node * n = (struct tree_node *)p;

  return json_snprintf(str, len,
                       "{"
                         "|path|:%S,"
                         "|mode|:%S,"
                         "|type|:%S,"
                         "|size|:%d,"
                         "|sha|:%S,"
                         "|url|:%S"
                         "}",
                  n->path,
                  n->mode,
                  n->type,
                  n->size,
                  n->sha,
                  n->url);
}

static int
print_all (char * str, size_t len, void * p)
{
  struct ntl_str_delimiter d = {
    .element_delimiter = ",\n",
    .last_element_delimiter = ""
  };
  return ntl_sn2str(str, len, (void **)p, &d, print_array);
}

int main () {
  char * json_str = NULL;
  int s = json_asprintf(&json_str, test_string);
  //printf("%s\n", json_str);
  struct json_token array_tok = { .start = NULL, .length = 0 };
  json_scanf(json_str, s, "[tree]%T", &array_tok);
  printf ("json_array_string:\n%.*s\n", array_tok.length, array_tok.start);

  jsmn_parser parser;
  jsmn_init(&parser);
  jsmntok_t * t = NULL;
  int num_tok = jsmn_parse(&parser, array_tok.start, array_tok.length, NULL, 0);
  //printf ("%d\n", num_tok);

  t = malloc(sizeof(jsmntok_t) * num_tok);
  jsmn_init(&parser);
  num_tok = jsmn_parse(&parser, array_tok.start, array_tok.length, t, num_tok+1);

  int i;

  printf ("test []%%L\n");
  struct json_token ** tokens = NULL;
  json_scanf(array_tok.start, array_tok.length, "[]%L", &tokens);
  for (i = 0; tokens[i]; i++) {
    printf ("token [%p, %d]\n", tokens[i]->start, tokens[i]->length);
    printf ("token %.*s\n", tokens[i]->length, tokens[i]->start);
  }
  free(tokens);

  printf ("test [tree]%%L\n");
  tokens = NULL;
  json_scanf(json_str, s, "[tree]%L", &tokens);
  struct tree_node ** nodes = ntl_dup(tokens, sizeof(struct tree_node));
  for (i = 0; tokens[i]; i++) {
    printf ("token [%p, %d]\n", tokens[i]->start, tokens[i]->length);
    printf ("token %.*s\n", tokens[i]->length, tokens[i]->start);
    load_tree_node(tokens[i]->start, tokens[i]->length, nodes[i]);
  }

  int wsize;
  char buf[1024];
  json_snprintf(buf, 1024, "{|a|:%d}", 10);
  fprintf (stderr, "%s\n", buf);

  json_snprintf(buf, 1024, "{|a|:%b}", true);
  fprintf (stderr, "%s\n", buf);

  json_snprintf(buf, 1024, "{|a|:%b}", false);
  fprintf (stderr, "%s\n", buf);

  json_snprintf(buf, 1024, "{|a|:%S}", NULL);
  fprintf (stderr, "%s\n", buf);

  json_snprintf(buf, 1024, "{|a|:%S}", "abc");
  fprintf (stderr, "%s\n", buf);

  json_snprintf(buf, 1024, "{|a|:|%s|}", "abc");
  fprintf (stderr, "%s\n", buf);

  wsize = json_snprintf(NULL, 0, "{|a|:|%s|, |b|:%d, |x|:%F }", "abc",
                        10, print_all, nodes);
  fprintf (stderr, "%d\n", wsize);

  wsize++;
  char * b = malloc(wsize);

  fprintf (stderr, "test json_snprintf\n");
  wsize = json_snprintf(b, wsize, "{|a|:|%s|, |b|:%d, |x|:%F }", "abc",
                        10, print_all, nodes);
  fprintf (stderr, "%d %s\n", wsize, b);

  fprintf(stderr, "test json_asprintf\n");
  wsize = json_asprintf(&b, "{|a|:|%s|, |b|:%d, |x|:%F }", "abc",
                        10, print_all, nodes);
  fprintf (stderr, "%d %s\n", wsize, b);
  return 0;
}


