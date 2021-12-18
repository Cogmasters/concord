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

#include "js_user-agent.h"

/* @todo shouldn't be a dependency */
extern const char *g_config_file;

int debug_stack = 0;

static const char *stacktrace_js =
  "Error.prototype.toString = function() {\n"
  "var s = this.name;\n"
  "if ('message' in this) s += ': ' + this.message;\n"
  "if ('stackTrace' in this) s += this.stackTrace;\n"
  "return s;\n"
  "};\n";

static void
enable_debug_track(js_State *J)
{
  debug_stack = 1;
}

static void
jsua_logger(js_State *J)
{
  js_getglobal(J, "Object");
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, "logger", NULL, NULL);
  {
    js_newcfunction(J, enable_debug_track, "logger.prototype.enable", 0);
    js_defproperty(J, -2, "enable", JS_READONLY | JS_DONTCONF | JS_DONTENUM);
  }
  js_defglobal(J, "logger", JS_READONLY | JS_DONTCONF | JS_DONTENUM);
}

void
jsua_log(char *fmt, ...)
{
  static FILE *logger = NULL;
  va_list ap;

  if (!logger) {
    char buf[512], file[1024];

    cee_gen_readlink(buf, sizeof(buf));
    cee_gen_dirname(buf);
    snprintf(file, sizeof(file), "%s/jso.log", buf);
    logger = fopen(file, "a");
  }

  va_start(ap, fmt);

  vfprintf(logger, fmt, ap);
  fflush(logger);

  va_end(ap);
}

static void
jsua_print(js_State *J)
{
  int top = js_gettop(J);
  int i;

  for (i = 1; i < top; ++i) {
    const char *s = js_tostring(J, i);

    if (i > 1) putchar(' ');
    fputs(s, stdout);
  }
  putchar('\n');
  js_pushundefined(J);
}

static void
jsua_cleanup(js_State *J, void *p_ua)
{
  jsua_log("jsua_cleanup is called\n");
  if (p_ua) ua_cleanup((struct user_agent *)p_ua);
}

static void
new_UserAgent(js_State *J)
{
  static struct logconf conf = { 0 };
  static _Bool first_run = 0;
  struct ua_attr attr = { 0 };
  struct user_agent *ua;

  if (!first_run) {
    FILE *fp = fopen(g_config_file, "rb");
    logconf_setup(&conf, "JS_UserAgent", fp);
    fclose(fp);
    first_run = 1;
  }

  attr.conf = &conf;
  ua = ua_init(&attr);

  if (js_isstring(J, 1)) {
    char *tmp = (char *)js_tostring(J, 1);
    char *url = NULL;

    if ('<' == *tmp) /* remove enclosing '< >' from string */
      asprintf(&url, "%.*s", (int)(strlen(tmp + 1) - 1), tmp + 1);
    else
      asprintf(&url, "%s", tmp);

    ua_set_url(ua, url);
    free(url);
  }

  js_currentfunction(J);
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, "UserAgent", ua, &jsua_cleanup);
}

static void
UserAgent_prototype_run(js_State *J)
{
  struct user_agent *ua = js_touserdata(J, 0, "UserAgent");
  struct ua_info info = { 0 };

  jsua_easy_run(J, ua, &info);

  js_newobject(J);
  {
    struct sized_buffer body = ua_info_get_body(&info);

    js_pushnumber(J, (double)info.httpcode);
    js_setproperty(J, -2, "httpCode");

    js_pushstring(J, body.start);
    js_setproperty(J, -2, "responseBody");
  }
  ua_info_cleanup(&info);
}

static void
UserAgent_prototype_string(js_State *J)
{
  struct user_agent *ua = js_touserdata(J, 0, "UserAgent");
  struct sized_buffer body, new_body = { 0 };
  struct ua_info info = { 0 };

  jsua_easy_run(J, ua, &info);

  body = ua_info_get_body(&info);

  jsua_log("original response >>>:%.*s\n", (int)body.size, body.start);
  json_string_unescape(&new_body.start, &new_body.size, body.start, body.size);
  jsua_log("unescaped response >>>:%.*s\n", (int)new_body.size,
           new_body.start);
  js_pushstring(J, new_body.start); /* this will make a new copy */

  ua_info_cleanup(&info);
}
#if 0
static void
UserAgent_prototype_addHeader(js_State *J)
{
  struct ua_conn *conn;

  if (!js_isstring(J, 1))
    js_typeerror(J, "Expected 'first' argument to be a 'string'");
  if (!js_isstring(J, 2))
    js_typeerror(J, "Expected 'second' argument to be a 'string'");

  conn = js_touserdata(J, 0, "Conn");
  ua_conn_add_header(ua, js_tostring(J, 1), js_tostring(J, 2));
  js_pushundefined(J);
}
#endif
static void
UserAgent_prototype_setUrl(js_State *J)
{
  struct user_agent *ua;

  if (!js_isstring(J, 1)) {
    js_typeerror(J, "Expected 'first' argument to be a 'string'");
  }

  ua = js_touserdata(J, 0, "UserAgent");
  ua_set_url(ua, js_tostring(J, 1));
  js_pushundefined(J);
}

static void
jsua_ua_init(js_State *J)
{
  js_getglobal(J, "Object");
  /* UserAgent.prototype.[[Prototype]] = Object.prototype */
  js_getproperty(J, -1, "prototype");
  /* UserAgent.prototype.[[UserData]] = null */
  js_newuserdata(J, "UserAgent", NULL, NULL);
  {
    /* UserAgent.prototype.run = function() { ... } */
    js_newcfunction(J, &UserAgent_prototype_run, "UserAgent.prototype.run", 1);
    js_defproperty(J, -2, "run", JS_DONTENUM);

    /* UserAgent.prototype.string = function() { ... } */
    js_newcfunction(J, &UserAgent_prototype_string,
                    "UserAgent.prototype.string", 1);
    js_defproperty(J, -2, "string", JS_DONTENUM);
#if 0
    /* UserAgent.prototype.addHeader = function() { ... } */
    js_newcfunction(J, &UserAgent_prototype_addHeader,
                    "UserAgent.prototype.addHeader", 2);
    js_defproperty(J, -2, "addHeader", JS_DONTENUM);
#endif
    /* UserAgent.prototype.setUrl = function() { ... } */
    js_newcfunction(J, &UserAgent_prototype_setUrl,
                    "UserAgent.prototype.setUrl", 2);
    js_defproperty(J, -2, "setUrl", JS_DONTENUM);
  }
  js_newcconstructor(J, &new_UserAgent, &new_UserAgent, "UserAgent", 1);
  js_defglobal(J, "UserAgent", JS_DONTENUM);
}

void
jsua_init(js_State *J)
{
  jsua_logger(J);

  /* declare common functions */
  js_newcfunction(J, jsua_print, "print", 1);
  js_setglobal(J, "print");

  /* declare UserAgent Object */
  jsua_ua_init(J);

  /* declare common Error prototypes */
  js_dostring(J, stacktrace_js);

  /* declare from common files */
#ifdef JSUA_IMPORT
  js_dofile(J, JSUA_IMPORT);
#endif
}

ORCAcode
jsua_easy_run(js_State *J, struct user_agent *ua, struct ua_info *p_info)
{
  struct sized_buffer body = { 0 };
  struct ua_conn_attr attr = { 0 };

  if (!js_isstring(J, 1))
    js_typeerror(J, "Expected 'first' argument to be a 'string'");
  if (!js_isstring(J, 2))
    js_typeerror(J, "Expected 'second' argument to be a 'string'");

  attr.method = http_method_eval((char *)js_tostring(J, 1));
  attr.endpoint = (char *)js_tostring(J, 2);

  if (js_isobject(J, 3) || js_isstring(J, 3)) {
    body.start = (char *)js_tostring(J, 3);
    body.size = strlen(body.start);
  }
  attr.body = &body;

  /* @todo map Error codes to JS Error objects */
  return ua_easy_run(ua, p_info, NULL, &attr);
}
