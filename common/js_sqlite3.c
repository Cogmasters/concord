#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cee-utils.h"
#include "json-actor.h"

#include "mujs.h"
#include "jsi.h"

#include "js_sqlite3.h"

#define IS_SKIPPED(c) ((c)==' ' || (c)==';' || ((c)>='\t'&&(c)<='\r'))

struct stmt_cxt {
  sqlite3 *db;
  sqlite3_stmt *stmt;
};

static void
destroy_Database(js_State *J, void *p_db) 
{
  if (p_db) {
    sqlite3_close(*(sqlite3 **)p_db);
    free(p_db);
  }
}

static void 
new_Database(js_State *J)
{
  sqlite3 **db = malloc(sizeof(sqlite3*));
  js_currentfunction(J);
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, "Database", db, &destroy_Database);
}

static void 
Database_prototype_open(js_State *J)
{
  if (!js_isstring(J, 1)) { 
    js_typeerror(J, "Expected 'first' argument to be a 'string'"); 
  }

  sqlite3 **db = js_touserdata(J, 0, "Database");
  const char *dbname = js_tostring(J, 1);
  if (SQLITE_OK != sqlite3_open(dbname, db)) {
    js_error(J, "Couldn't open database '%s': %s", dbname, sqlite3_errmsg(*db)); 
  }
  js_pushundefined(J);
}

static void 
Database_prototype_close(js_State *J)
{
  sqlite3 **db = js_touserdata(J, 0, "Database");
  sqlite3_close(*db);
  *db = NULL;
  js_pushundefined(J);
}

static void 
Database_prototype_exec(js_State *J)
{
  if (!js_isstring(J, 1)) { 
    js_typeerror(J, "Expected 'first' argument to be a 'string'"); 
  }

  sqlite3 **db = js_touserdata(J, 0, "Database");
  sqlite3_stmt *stmt;
  const char *sql = js_tostring(J, 1), *tail;

  while (1) {
    while (IS_SKIPPED(*sql)) ++sql;

    if (SQLITE_OK != sqlite3_prepare_v2(*db, sql, -1, &stmt, &tail)) {
      sqlite3_finalize(stmt);
      js_error(J, "Failed to execute statement: %s", sqlite3_errmsg(*db));
    }

    sql = tail;
    if (!stmt) break;

    while (SQLITE_ROW == sqlite3_step(stmt))
      continue;
    if (SQLITE_OK != sqlite3_finalize(stmt))
      break;
  }

  js_pushundefined(J);
}

static void 
Database_prototype_prepare(js_State *J)
{
  if (!js_isstring(J, 1)) { 
    js_typeerror(J, "Expected 'first' argument to be a 'string'"); 
  }

  sqlite3 **db = js_touserdata(J, 0, "Database");
  const char *sql = js_tostring(J, 1);

  /* var a = new Statement(this) */
  js_getglobal(J, "Statement");
  js_copy(J, 0); // push 'this'
  if (js_pconstruct(J, 1)) { // push Statement to top of stack
    js_referenceerror(J, "Failed to call 'new Statement(this)'");
  }

  struct stmt_cxt *cxt = js_touserdata(J, -1, "Statement");
  if (SQLITE_OK != sqlite3_prepare_v2(*db, sql, -1, &cxt->stmt, NULL)) {
    js_error(J, "Failed to execute statement: %s", sqlite3_errmsg(*db));
  }
}

static void 
jssqlite3_db_init(js_State *J)
{
  js_getglobal(J, "Object"); 
  // Database.prototype.[[Prototype]] = Object.prototype
  js_getproperty(J, -1, "prototype");
  // Database.prototype.[[UserData]] = null
  js_newuserdata(J, "Database", NULL, NULL);
  {
    // Database.prototype.open = function() { ... }
    js_newcfunction(J, &Database_prototype_open, "Database.prototype.open", 1);
    js_defproperty(J, -2, "open", JS_DONTENUM);

    // Database.prototype.close = function() { ... }
    js_newcfunction(J, &Database_prototype_close, "Database.prototype.close", 1);
    js_defproperty(J, -2, "close", JS_DONTENUM);
    
    // Database.prototype.close = function() { ... }
    js_newcfunction(J, &Database_prototype_exec, "Database.prototype.exec", 1);
    js_defproperty(J, -2, "exec", JS_DONTENUM);
    
    // Database.prototype.prepare = function() { ... }
    js_newcfunction(J, &Database_prototype_prepare, "Database.prototype.prepare", 1);
    js_defproperty(J, -2, "prepare", JS_DONTENUM);
  }
  js_newcconstructor(J, &new_Database, &new_Database, "Database", 1);
  js_defglobal(J, "Database", JS_DONTENUM); 
}

static void
destroy_Statement(js_State *J, void *p_cxt) {
  if (p_cxt) free(p_cxt);
}

static void 
new_Statement(js_State *J)
{
  struct stmt_cxt *cxt = malloc(sizeof *cxt);
  sqlite3 **p_db = js_touserdata(J, 1, "Database");
  cxt->db = *p_db;

  js_currentfunction(J);
  js_getproperty(J, -1, "prototype");
  js_newuserdata(J, "Statement", cxt, &destroy_Statement);
}

static int
jssqlite3_bind(js_State *J, int idx, sqlite3_stmt *stmt, int iCol)
{
  switch (js_type(J, idx)) {
  case JS_ISSTRING:
      return sqlite3_bind_text(stmt, iCol, js_tostring(J, idx), -1, SQLITE_STATIC);
  case JS_ISUNDEFINED:
  case JS_ISNULL:
      return sqlite3_bind_null(stmt, iCol);
  case JS_ISBOOLEAN:
      return sqlite3_bind_int(stmt, iCol, js_toint32(J, idx));
  case JS_ISNUMBER:
      return sqlite3_bind_double(stmt, iCol, js_tonumber(J, idx));
  default:
      break;
  }
  return -1;
}

static int
jssqlite3_pushcolumn(js_State *J, int iCol, sqlite3_stmt *stmt)
{
  switch (sqlite3_column_type(stmt, iCol)) {
  case SQLITE_TEXT:
      js_pushstring(J, (const char*)sqlite3_column_text(stmt, iCol));
      break;
  case SQLITE_NULL:
      js_pushnull(J);
      break;
  case SQLITE_INTEGER:
      js_pushnumber(J, (double)sqlite3_column_int(stmt, iCol));
      break;
  case SQLITE_FLOAT:
      js_pushnumber(J, sqlite3_column_double(stmt, iCol));
      break;
  case SQLITE_BLOB: /* @todo */
      js_pushundefined(J);
      break;
  default:
      return -1;
  }
  return SQLITE_OK;
}

static void 
Statement_prototype_run(js_State *J)
{
  if (!js_isstring(J, 1)) { 
    js_typeerror(J, "Expected 'first' argument to be a 'string'"); 
  }

  struct stmt_cxt *cxt = js_touserdata(J, 0, "Statement");
  int nparam = js_gettop(J), 
      expect_nparam = sqlite3_bind_parameter_count(cxt->stmt);
  int status;
  int nrow=0;
  char errbuf[512]="";

  if (nparam-1 != expect_nparam) {
    snprintf(errbuf, sizeof(errbuf), "Expect %d parameters, got %d instead", 
        expect_nparam, nparam-1);
    js_newreferenceerror(J, errbuf);
    goto _end;
  }

  for (int i=1; i < nparam; ++i) {
    status = jssqlite3_bind(J, i, cxt->stmt, i);
    if (SQLITE_OK != status) {
      snprintf(errbuf, sizeof(errbuf), 
          "Failed to bind parameter No#%d of type '%s': %s", 
          i, js_typeof(J, i), sqlite3_errstr(status));
      js_newrangeerror(J, errbuf);
      goto _end;
    }
  }

  while (SQLITE_ROW == (status = sqlite3_step(cxt->stmt))) {
    ++nrow;
  }
  if (SQLITE_DONE != status) {
    snprintf(errbuf, sizeof(errbuf), 
        "Failed to evaluate SQL statement: %s", sqlite3_errstr(status));
    js_newevalerror(J, errbuf);
    goto _end;
  }

  js_newobject(J); // return info object
  {
    js_pushnumber(J, (double)nrow);
    js_setproperty(J, -2, "changes");
  }

_end:
  sqlite3_reset(cxt->stmt);
  sqlite3_clear_bindings(cxt->stmt);
  if (*errbuf) js_throw(J);
}

static void 
Statement_prototype_get(js_State *J)
{
  if (!js_isstring(J, 1)) { 
    js_typeerror(J, "Expected 'first' argument to be a 'string'"); 
  }

  struct stmt_cxt *cxt = js_touserdata(J, 0, "Statement");
  int nparam = js_gettop(J), 
      expect_nparam = sqlite3_bind_parameter_count(cxt->stmt);
  int status;
  int nrow=0;
  char errbuf[512]="";

  if (nparam-1 != expect_nparam) {
    snprintf(errbuf, sizeof(errbuf), "Expect %d parameters, got %d instead", 
        expect_nparam, nparam-1);
    js_newreferenceerror(J, errbuf);
    goto _end;
  }

  for (int i=1; i < nparam; ++i) {
    status = jssqlite3_bind(J, i, cxt->stmt, i);
    if (SQLITE_OK != status) {
      snprintf(errbuf, sizeof(errbuf), 
          "Failed to bind parameter No#%d of type '%s': %s", 
          i, js_typeof(J, i), sqlite3_errstr(status));
      js_newrangeerror(J, errbuf);
      goto _end;
    }
  }

  js_newobject(J); // create object with fetched values
  {
    while (SQLITE_ROW == (status = sqlite3_step(cxt->stmt))) {
      status = jssqlite3_pushcolumn(J, nrow, cxt->stmt);
      if (SQLITE_OK != status) {
        js_pop(J, 2); // pop object and column from stack
        snprintf(errbuf, sizeof(errbuf), 
            "Failed to fetch column '%s': %s", 
            sqlite3_column_name(cxt->stmt, nrow), 
            sqlite3_errstr(status));
        js_newrangeerror(J, errbuf);
        goto _end;
      }
      js_setproperty(J, -2, sqlite3_column_name(cxt->stmt, nrow));
      ++nrow;
    }
  }
  if (SQLITE_DONE != status) {
    js_pop(J, 1); // pop object from stack
    snprintf(errbuf, sizeof(errbuf), 
        "Failed to evaluate SQL statement: %s", sqlite3_errstr(status));
    js_newevalerror(J, errbuf);
    goto _end;
  }

_end:
  sqlite3_reset(cxt->stmt);
  sqlite3_clear_bindings(cxt->stmt);
  if (*errbuf) js_throw(J);
}

static void 
jssqlite3_stmt_init(js_State *J)
{
  js_getglobal(J, "Object"); 
  // Statement.prototype.[[Prototype]] = Object.prototype
  js_getproperty(J, -1, "prototype");
  // Statement.prototype.[[UserData]] = null
  js_newuserdata(J, "Statement", NULL, NULL);
  {
    // Statement.prototype.run = function() { ... }
    // this should receive any amount of args
    js_newcfunction(J, &Statement_prototype_run, "Statement.prototype.run", 0);
    js_defproperty(J, -2, "run", JS_DONTENUM);
    // Statement.prototype.run = function() { ... }
    // this should receive any amount of args
    js_newcfunction(J, &Statement_prototype_get, "Statement.prototype.get", 0);
    js_defproperty(J, -2, "get", JS_DONTENUM);
  }
  js_newcconstructor(J, &new_Statement, &new_Statement, "Statement", 1);
  js_defglobal(J, "Statement", JS_DONTENUM); 
}

void
jssqlite3_init(js_State *J) 
{
  jssqlite3_db_init(J);
  jssqlite3_stmt_init(J);
  D_RUN(js_trap(J, 0));
}
