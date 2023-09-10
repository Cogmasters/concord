#include "db.h"

sqlite3* sbclone_DB;

sqlite3* sbclone_connectDB() {
  sqlite3 *db;
  int rc = sqlite3_open("starboard.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return NULL;
  }

  sbclone_DB = db;
  return db;
}

void sbclone_init(sqlite3* db) {
  // Create the `posts` table
  char* create_posts_sql =  "CREATE TABLE IF NOT EXISTS posts ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                              "userid text NOT NULL,"
                              "messageid text NOT NULL,"
                              "isposted boolean"
                            ")";
  sqlite3_exec(db, create_posts_sql, 0, 0, NULL);

  // Create the `channels` table
  char* create_channels_sql = "CREATE TABLE IF NOT EXISTS channels ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                "channelid TEXT NOT NULL,"
                                "guildid TEXT NOT NULL,"
                                "isboardchannel INT NOT NULL"
                              ")";
  sqlite3_exec(db, create_channels_sql, 0, 0, NULL);
}
