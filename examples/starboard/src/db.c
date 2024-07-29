#include "db.h"
#include <concord/discord.h>
#include <concord/log.h>
#include "bot.h"
#include <postgresql/server/catalog/pg_type_d.h>
#include <stdlib.h>

PGconn* star_db_conn;

// Same as the ones after, but without `PQclear()`
void star_db_error_check(PGresult* res, PGconn* conn) {
  ExecStatusType code = PQresultStatus(res);
  if(code != PGRES_COMMAND_OK && code != PGRES_TUPLES_OK) {
    log_fatal("Failed to perform query: %s", PQerrorMessage(conn));
    PQclear(res);
    PQfinish(conn);
    exit(1);
  }
}

// This just basically checks if the PQexec failed or not
static void star_db_check_table_for_errors(PGresult* res, PGconn* conn) {
  if(PQresultStatus(res) != PGRES_COMMAND_OK) {
    log_fatal("Failed to prepare tables: %s", PQerrorMessage(conn));
    PQclear(res);
    PQfinish(conn);
    exit(1);
  }
  PQclear(res);
}

// The same as before but with prepared statements
static void star_db_check_prepare_for_errors(PGresult* prepared_result, PGconn* conn) {
  if(PQresultStatus(prepared_result) != PGRES_COMMAND_OK) {
    log_fatal("Failed to prepare statement: %s", PQerrorMessage(conn));
    PQclear(prepared_result);
    PQfinish(conn);
    exit(1);
  }
  PQclear(prepared_result);
}

// Was for testing
void star_db_drop_all_tables(PGconn* conn) {
  PQexec(conn, "DROP TABLE channels");
  PQexec(conn, "DROP TABLE posts");
}

static void star_db_init_tables(PGconn* conn) {
  // Initialize the result variable already, so the code looks a bit nicer
  PGresult* res;

  // Create the `posts` table
  res = PQexec(conn, "CREATE TABLE IF NOT EXISTS posts ("
                        "id SERIAL PRIMARY KEY NOT NULL,"
                        "user_id TEXT NOT NULL,"
                        "message_id TEXT NOT NULL,"
                        "is_posted BOOLEAN"
                      ")");
  star_db_check_table_for_errors(res, conn);

  // Create the `channels` table
  res = PQexec(conn, "CREATE TABLE IF NOT EXISTS channels ("
                        "id SERIAL PRIMARY KEY NOT NULL,"
                        "channel_id TEXT NOT NULL,"
                        "guild_id TEXT NOT NULL,"
                        "is_board_channel BOOLEAN NOT NULL"
                      ")");
  star_db_check_table_for_errors(res, conn);
}

static void star_db_init_prepared_statements(PGconn* conn) {
  // Initializing it now, because it looks nicer that way
  PGresult* res;

  res = PQprepare(conn, "get_post_by_message_id",
                  "SELECT * FROM posts WHERE message_id = $1",
                  1, (const Oid[1]){ TEXTOID });
  star_db_check_prepare_for_errors(res, conn);

  // I don't think this was actually used in the code, but I'm going to keep it in, in case something breaks.
  res = PQprepare(conn, "get_channel_by_guild_id",
                  "SELECT * FROM channels WHERE guild_id = $1",
                  1, (const Oid[1]){ TEXTOID });
  star_db_check_prepare_for_errors(res, conn);

  res = PQprepare(conn, "set_as_posted",
                  "UPDATE posts SET is_posted = true WHERE message_id = $1",
                  1, (const Oid[1]){ TEXTOID });
  star_db_check_prepare_for_errors(res, conn);

  res = PQprepare(conn, "get_board_channel",
                  "SELECT * FROM channels WHERE guild_id = $1 AND is_board_channel = true",
                  1, (const Oid[1]){ TEXTOID });
  star_db_check_prepare_for_errors(res, conn);

  res = PQprepare(conn, "create_post",
                  "INSERT INTO posts (user_id, message_id, is_posted) VALUES ($1, $2, false)",
                  2, (const Oid[2]){ TEXTOID, TEXTOID });
  star_db_check_prepare_for_errors(res, conn);

  res = PQprepare(conn, "create_channel",
                  "INSERT INTO channels (channel_id, guild_id, is_board_channel) VALUES ($1, $2, $3)",
                  3, (const Oid[3]){ TEXTOID, TEXTOID, BOOLOID });
  star_db_check_prepare_for_errors(res, conn);

  res = PQprepare(conn, "get_channel_by_id",
                  "SELECT * FROM channels WHERE channel_id = $1",
                  1, (const Oid[1]){ TEXTOID });
  star_db_check_prepare_for_errors(res, conn);

  res = PQprepare(conn, "delete_channel_by_id",
                  "DELETE FROM channels WHERE channel_id = $1",
                  1, (const Oid[1]){ TEXTOID });
  star_db_check_prepare_for_errors(res, conn);
}

void star_db_connect(struct discord* client) {
  // We have to get the url from config.json
  char connection_url[256];
  struct ccord_szbuf_readonly connection_url_field = discord_config_get_field(client, (char*[2]){ "database", "url" }, 2);
  snprintf(connection_url, sizeof(connection_url), "%.*s", (int)connection_url_field.size, connection_url_field.start);

  // Just connect to it  
  PGconn* conn = PQconnectdb(connection_url);

  // Check if the connection was successful
  if(PQstatus(conn) != CONNECTION_OK) {
    log_fatal("Error while connecting to the database: %s", PQerrorMessage(conn));
    
    // Finish it.
    PQfinish(conn);
    exit(1);
  }
  log_info("Connected to the database `%s`", PQdb(conn));
  star_db_init_tables(conn);
  star_db_init_prepared_statements(conn);

  star_db_conn = conn;
}
