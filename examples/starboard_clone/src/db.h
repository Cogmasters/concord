#include <sqlite3.h>
#include <stdio.h>

extern sqlite3* sbclone_DB;

sqlite3* sbclone_connectDB();
void sbclone_init(sqlite3* db);
