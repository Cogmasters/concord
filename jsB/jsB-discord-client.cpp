#include <stdlib.h>
#include <string.h>

#ifndef JMP_BUF
#define JMP_BUF  struct __jmp_buf_tag *
#endif

#include "mujs.h"
#include "discord-common.h"
#define TAG "DiscordCurl"

using namespace discord;

static user_agent::dati* ator(const char *config)
{
  user_agent::dati *ua = (user_agent::dati *)calloc(1, sizeof(user_agent::dati));
  user_agent::init(ua, NULL, config);
  return ua;
}

static void dtor(js_State *J, void *p)
{
  user_agent::dati *req = (user_agent::dati *)p;
  user_agent::cleanup(req);
  free(req);
}

static void new_ua(js_State * J)
{
  user_agent::dati *req = NULL;
  if (js_isundefined(J, 1)) {
    // default configuration
    req = ator("bot-config");
  }
  else {
    // custom configuration
    const char *config = js_tostring(J, 1);
    req = ator(config);
  }
  js_currentfunction(J);
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, TAG, req, dtor);
}

static void copy_resp(char *start, size_t size, void *p)
{
  char *buf = (char *)malloc(size + 1);
  char **buf_p = (char **)p;

  memcpy(buf, start, size);
  buf[size] = 0;
  *buf_p = buf;
}

static enum http_method check_method(char *s) {
  if (strcmp(s, "GET") == 0) {
    return HTTP_GET;
  }
  else if (strcmp(s, "POST") == 0) {
    return HTTP_POST;
  }
  else if (strcmp(s, "PATCH") == 0) {
    return HTTP_PATCH;
  }
  else if (strcmp(s, "DELETE") == 0) {
    return HTTP_DELETE;
  }
  else if (strcmp(s, "PUT") == 0) {
    return HTTP_PUT;
  }
  else {
    fprintf(stderr, "Unknown HTTP method %s\n", s);
    exit(1);
  }
}

static char* do_url(js_State *J, int *nparam_p)
{
  user_agent::dati *req = (user_agent::dati *)js_touserdata(J, 0, TAG);
  char *url, *m, *b = "";

  enum http_method method;
  if (js_isstring(J, 1)) {
    m = (char *)js_tostring(J, 1);
    method = check_method (m);
  }
  else {
    fprintf(stderr, TAG ".do_url expect a METHOD string\n");
    //js_error(J, "HttpGet.do expect a url parameter");
    exit(1);
  }
  if (js_isstring(J, 2)) {
    url = (char *)js_tostring(J, 2);
  }
  else {
    fprintf(stderr, TAG ".do_url expect a url string\n");
    //js_error(J, "HttpGet.do expect a url parameter");
    exit(1);
  }
  int n = js_gettop(J);
  *nparam_p = n;

  if (n == 3) { // has body
    if (js_isobject(J, 3)) {
      b = (char *)js_tostring(J, 3);
    }
  }

  char *buf = NULL;
  struct resp_handle  resp_handle =
    { .ok_cb = copy_resp, .ok_obj = &buf };

  struct sized_buffer req_body =
    { .start = b, .size = strlen(b) };


  user_agent::run(req, &resp_handle, &req_body, method, url);
  return buf;
}

static void prototype_json(js_State *J) {
  int nparam = 0;
  char *response = do_url(J, &nparam);
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
  free(response);
}

static void prototype_string(js_State *J)
{
  int nparam = 0;
  char *response = do_url(J, &nparam);
  js_pushstring(J, response); // this will make a new copy
  free(response);
}

void jsB_init_UA(js_State *J)
{
  js_getglobal(J, "Object");
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, TAG, ator("bot-config"), dtor);
  {
    js_newcfunction(J, prototype_json, TAG ".prototype.json", 1);
    js_defproperty(J, -2, "json", JS_DONTENUM);
    js_newcfunction(J, prototype_string, TAG ".prototype.string", 1);
    js_defproperty(J, -2, "string", JS_DONTENUM);
  }
  js_newcconstructor(J, new_ua, new_ua, TAG, 1);
  js_defglobal(J, TAG, JS_DONTENUM);
}