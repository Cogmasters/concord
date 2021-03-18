#include "jsB.h"
#include "mujs.h"
#define TAG  "SB"

static SB_ator(char *pos, size_t s)
{
  fprintf(stderr, "%.*s\n", s, pos);
  char *p = malloc(s);
  return p;
}

static void SB_dtor(js_State *J, void *p)
{
  fprintf(stderr, "dtor is called\n");
  free(p);
}

static void new_SB(js_State * J)
{
  char *req = NULL;
  if (js_isundefined(J, 1)) {
    // default configuration
    // error
  }
  else {
    // custom configuration
    const char *config = js_tostring(J, 1);
    req = SB_ator(config);
  }
  js_currentfunction(J);
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, TAG, req, dtor);
}

static void prototype_json(js_State *J) {
  char *response = js_touserdata(J, 0, TAG);
  /*
   * JSON.parse(resp.body)
   */
  js_getglobal(J, "JSON");
  js_getproperty(J, -1, "parse");
  js_pushnull(J); // the 'this' object to use
  js_pushliteral(J, response); // this will not make a copy
  if (js_try(J)) {
    fprintf(stderr, "error: %s\n", js_tostring(J, -1));
    char file[128];
    snprintf(file, 128, "/tmp/%ld", random());
    FILE * f = fopen(file, "+w");
    fwrite(response, strlen(response), 1, f);
    fclose(f);
    fprintf(stderr, "error: %s, json-file %s\n", js_tostring(J, -1), file);
    js_pop(J, nparam+1);
    js_pushundefined(J);
  }
  js_call(J, 1);
  js_endtry(J);
  js_rot2(J);    // swap the returned value to the bottom
  js_pop(J, 1);  // throws away the JSON global.
}

static void prototype_string(js_State *J)
{
  char *response = js_touserdata(J, 0, TAG);
  js_pushstring(J, response); // this will make a new copy
}

static void prototype_unescape(js_State *J)
{
  char *response = js_touserdata(J, 0, TAG);
  char *new_response = NULL;
  size_t new_size = 0;
  fprintf(stderr, "original_response >>> %s\n", response);
  json_string_unescape(&new_response, &new_size, response, strlen(response));
  fprintf(stderr, "unescaped_response >>> %s\n", new_response);
  js_pushstring(J, new_response); // this will make a new copy
}

void jsB_init_SB(js_State *J)
{
  js_getglobal(J, "Object");
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, TAG, NULL, NULL);
  {
    js_newcfunction(J, prototype_json, TAG ".prototype.json", 1);
    js_defproperty(J, -2, "json", JS_DONTENUM);
    js_newcfunction(J, prototype_string, TAG ".prototype.string", 1);
    js_defproperty(J, -2, "string", JS_DONTENUM);
    js_newcfunction(J, prototype_string, TAG ".prototype.unescape", 1);
    js_defproperty(J, -2, "unescape", JS_DONTENUM);
  }
  js_newcconstructor(J, new_TAG, new_TAG, TAG, 1);
  js_defglobal(J, TAG, JS_DONTENUM);
}