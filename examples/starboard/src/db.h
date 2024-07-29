#ifndef STAR_DB_H
#define STAR_DB_H

#include <libpq-fe.h>

extern PGconn* star_db_conn;

void star_db_connect();
void star_db_error_check(PGresult* res, PGconn* conn);
void star_db_drop_all_tables(PGconn* conn);

#endif // STAR_DB_H