#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64 */

#include "user-agent.h"
#include "cee-utils.h"
#include "json-actor.h"

#include "mujs.h"
#include "jsi.h"

#include "jso.h"

extern const char* g_config_file;

int debug_stack=0;

static const char *stacktrace_js =
  "Error.prototype.toString = function() {\n"
    "if (this.stackTrace) return this.name + ': ' + this.message + this.stackTrace;\n"
    "return this.name + ': ' + this.message;\n"
    "};\n";

static void 
enable_debug_track(js_State *J) {
  debug_stack = 1;
}

static void 
copy_resp(char *start, size_t size, void *p)
{
  char *buf = (char*)malloc(size+1);
  char **buf_p = (char**)p;

  memcpy(buf, start, size);
  buf[size] = 0;
  *buf_p = buf;
}

/** @todo move to default js bindings */
static void 
console_log(js_State *J) 
{
  js_trap(J, 0);
  printf("%s\n", js_tryrepr(J, 1, "Error"));
  js_pushundefined(J);
  js_trap(J, 0);
}

/** @todo move to default js bindings */
static void
jso_console_log(js_State *J)
{
  js_getglobal(J, "Object");
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, "console", NULL, NULL);
	{
    js_newcfunction(J, console_log,  "console.prototype.log", 1);
    js_defproperty(J, -2, "log", JS_READONLY|JS_DONTCONF|JS_DONTENUM);
  }
  js_defglobal(J, "console", JS_READONLY|JS_DONTCONF|JS_DONTENUM);
}

static void
jso_logger(js_State *J)
{
  js_getglobal(J, "Object");
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, "logger", NULL, NULL);
  {
    js_newcfunction(J, enable_debug_track,  "logger.prototype.enable", 0);
    js_defproperty(J, -2, "enable", JS_READONLY|JS_DONTCONF|JS_DONTENUM);
  }
  js_defglobal(J, "logger", JS_READONLY|JS_DONTCONF|JS_DONTENUM);
}

void 
jso_log(char *fmt, ...)
{
  static FILE *logger = NULL;
  if (!logger) {
    char buf[512], file[1024];
    cee_gen_readlink(buf, sizeof(buf));
    cee_gen_dirname(buf);
    snprintf(file, sizeof(file), "%s/jso.log", buf);
    logger = fopen(file, "a");
  }

  va_list ap;
  va_start(ap, fmt);

  vfprintf(logger, fmt, ap);
  fflush(logger);

  va_end(ap);
}

static void 
jso_print(js_State *J)
{
  int top = js_gettop(J);
  for (int i=1; i < top; ++i) {
    const char *s = js_tostring(J, i);
    if (i > 1) putchar(' ');
    fputs(s, stdout);
  }
  putchar('\n');
  js_pushundefined(J);
}

static void
jso_ua_cleanup(js_State *J, void *p_ua) {
  jso_log("jso_ua_cleanup is called\n");
  if (p_ua) ua_cleanup((struct user_agent*)p_ua);
}

static void 
Orca_constructor(js_State *J)
{
  static struct logconf config={0};
  static _Bool first_run=0;

  if (!first_run) {
    logconf_setup(&config, g_config_file);
    first_run = 1;
  }

  struct user_agent *ua = ua_init(&config);
  if (js_isstring(J, 1)) {
    char *tmp = (char*)js_tostring(J, 1);

    char url[UA_MAX_URL_LEN];
    if ('<' == *tmp) // remove enclosing '< >' from string
      snprintf(url, sizeof(url), "%.*s", (int)(strlen(tmp+1)-1), tmp+1); 
    else
      snprintf(url, sizeof(url), "%s", tmp); 

    ua_set_url(ua, url);
  }

  js_currentfunction(J);
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, "Orca", ua, &jso_ua_cleanup);
}

static void 
Orca_prototype_run(js_State *J) 
{
  int nparam = 0;
  struct user_agent *ua = js_touserdata(J, 0, "Orca");
  struct ua_info info={0};
  jso_ua_run(J, ua, &info, &nparam);

  js_newobject(J);
  {
    js_pushnumber(J, (double)info.httpcode);
    js_setproperty(J, -2, "httpcode");

    js_pushstring(J, info.req_url);
    js_setproperty(J, -2, "reqUrl");

    char aux[64]; // convert timestamp to string
    snprintf(aux, sizeof(aux), "%"PRIu64, info.req_tstamp);
    js_pushstring(J, aux);
    js_setproperty(J, -2, "reqTstamp");

    struct sized_buffer resp_body = ua_info_get_resp_body(&info);
    js_pushstring(J, resp_body.start);
    js_setproperty(J, -2, "respBody");
  }
  ua_info_cleanup(&info);
}

static void 
Orca_prototype_string(js_State *J)
{
  int nparam = 0;
  struct user_agent *ua = js_touserdata(J, 0, "Orca");
  struct ua_info info={0};
  jso_ua_run(J, ua, &info, &nparam);

  struct sized_buffer resp_body = ua_info_get_resp_body(&info);
  struct sized_buffer new_resp_body={0};

  jso_log("original response >>>:%.*s\n", (int)resp_body.size, resp_body.start);
  json_string_unescape(&new_resp_body.start, &new_resp_body.size, resp_body.start, resp_body.size);
  jso_log("unescaped response >>>:%.*s\n", (int)new_resp_body.size, new_resp_body.start);
  js_pushstring(J, new_resp_body.start); // this will make a new copy

  ua_info_cleanup(&info);
}

static void 
Orca_prototype_addHeader(js_State *J)
{
  ASSERT_S(js_isstring(J, 1), "addHeader() field expect string");
  ASSERT_S(js_isstring(J, 2), "addHeader() value expect string");

  struct user_agent *ua = js_touserdata(J, 0, "Orca");
  const char *field = js_tostring(J, 1), *value = js_tostring(J, 2);
  ua_reqheader_add(ua, field, value);
  js_pushundefined(J);
}

static void
Orca_prototype_setUrl(js_State *J)
{
  ASSERT_S(js_isstring(J, 1), "setUrl() baseUrl expect string");

  struct user_agent *ua = js_touserdata(J, 0, "Orca");
  const char *base_url = js_tostring(J, 1);
  ua_set_url(ua, base_url);
  js_pushundefined(J);
}

static void 
Orca_init(js_State *J)
{
  js_getglobal(J, "Object"); 
  // Orca.prototype.[[Prototype]] = Object.prototype
  js_getproperty(J, -1, "prototype");
  // Orca.prototype.[[UserData]] = null
  js_newuserdata(J, "Orca", NULL, NULL);
  {
    // Orca.prototype.run = function() { ... }
    js_newcfunction(J, &Orca_prototype_run, "Orca.prototype.run", 1);
    js_defproperty(J, -2, "run", JS_DONTENUM);

    // Orca.prototype.string = function() { ... }
    js_newcfunction(J, &Orca_prototype_string, "Orca.prototype.string", 1);
    js_defproperty(J, -2, "string", JS_DONTENUM);

    // Orca.prototype.addHeader = function() { ... }
    js_newcfunction(J, &Orca_prototype_addHeader, "Orca.prototype.addHeader", 2);
    js_defproperty(J, -2, "addHeader", JS_DONTENUM);

    // Orca.prototype.setUrl = function() { ... }
    js_newcfunction(J, &Orca_prototype_setUrl, "Orca.prototype.setUrl", 2);
    js_defproperty(J, -2, "setUrl", JS_DONTENUM);
  }
  js_newcconstructor(J, &Orca_constructor, &Orca_constructor, "Orca", 1);
  js_defglobal(J, "Orca", JS_DONTENUM); 
}

void jso_init(js_State *J)
{
  jso_logger(J);

  // declare common functions
  js_newcfunction(J, jso_print, "print", 1);
  js_setglobal(J, "print"); 
#if 0
  jso_console_log(J);
#endif

  // declare Orca Object
  Orca_init(J);

  // declare common Error prototypes
  js_dostring(J, stacktrace_js);

  // declare from common files
  js_dofile(J, "set.js");
  js_dofile(J, "map.js");
  js_dofile(J, "orca.js");
}

ORCAcode jso_ua_run(
  js_State *J, 
  struct user_agent *ua, 
  struct ua_info *p_info,
  int *p_nparam)
{
  int nparam = js_gettop(J);
  *p_nparam = nparam;
  log_debug("n# of parameters: %d", nparam);

  if (!js_isstring(J, 1)) {
    log_fatal("expect a METHOD string");
    exit(1);
  }
  if (!js_isstring(J, 2)) {
    log_fatal("expect a URL string");
    exit(1);
  }

  char *strmethod = (char*)js_tostring(J, 1);
  log_debug("method: %s", strmethod);
  enum http_method method = http_method_eval(strmethod);

  char *endpoint = (char*)js_tostring(J, 2);
  log_debug("endpoint: %s", endpoint);

  struct sized_buffer req_body={0};
  if (4 == nparam) { // has body
    if (js_isobject(J, 3) || js_isstring(J, 3)) {
      req_body.start = (char *)js_tostring(J, 3);
      req_body.size = strlen(req_body.start);
      log_debug("request body: %.*s", (int)req_body.size, req_body.start);
    }
  }

  return ua_run(
          ua, 
          p_info, 
          NULL, 
          &req_body, 
          method, endpoint, "");
}
