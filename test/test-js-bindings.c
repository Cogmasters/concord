#include <stdio.h>
#include <stdlib.h>

#include "user-agent.h"

#include "mujs.h"
#include "js_user-agent.h"
#include "js_sqlite3.h"

const char *handle=NULL; /* handle to stowed away js function */
const char *g_config_file;

#define DB_NAME  "'test-js-bindings.db'"
#define SQL_EXEC_STMT "'DROP TABLE IF EXISTS cats;"              \
                      "CREATE TABLE cats (name TEXT, age INT);'"
#define SQL_PREPARE_INSERT_STMT "'INSERT INTO cats (name, age) VALUES (?, ?)'"
#define SQL_PREPARE_SELECT_STMT "'SELECT age FROM cats WHERE name = ?'"

void js_request(js_State *J)
{
  struct logconf config={0};
  logconf_setup(&config, NULL);

  struct user_agent *ua = ua_init(&config);
  ua_set_url(ua, "http://www.example.com/");

  if (ORCA_OK == jsua_run(J, ua, NULL)) {
    printf("Request was a success!\n");
  }

  ua_cleanup(ua);
}

int main(void)
{
  log_set_quiet(true);

  js_State *J = js_newstate(NULL, NULL, JS_STRICT);
  jssqlite3_init(J);
  jsua_init(J);

  /* TEST SQLITE3 BINDING */
  js_dostring(J, "var db = new Database();");
  js_dostring(J, "db.open("DB_NAME");");
  js_dostring(J, "db.exec("SQL_EXEC_STMT");");
  js_dostring(J, "var stmt = db.prepare("SQL_PREPARE_INSERT_STMT");");
  js_dostring(J, "stmt.run('Joey', 2);");
  js_dostring(J, "stmt = db.prepare("SQL_PREPARE_SELECT_STMT");");
  js_dostring(J, "var cat = stmt.get('Joey');");
  js_dostring(J, "print(JSON.stringify(cat));");
  js_dostring(J, "db.close();");

  /* TEST USER-AGENT BINDING */
  js_newcfunction(J, &js_request, "request", 2);

  js_copy(J, 1);
  handle = js_ref(J);

  js_getregistry(J, handle);
  js_pushstring(J, "GET");
  js_pushstring(J, "index.html");
  if (js_pcall(J, 2)) {
    fprintf(stderr, "Error\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
