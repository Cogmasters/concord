# Using a DB with concord

Sometimes, when you are developing a bot command, you may wish to save some data that will not be erased once the bot restart (aka persistent data). This is where a database comes in - it can save data, and don't worry, it won't be erased if you restart your bot.

In this guide, you will either decide on choosing SQLite3 to start, or postgreSQL, which is the most recommended one for production.

## PostgreSQL

PostgreSQL is a really advanced database, and incredibly fast, but it's hard to use it, at least, compared to easier databases, like SQLite3.

### Opening the DB file

Before executing any type of function on the database, you will first need to connect to it, which luckily is incredibly easy to do.

See an example below, where we are opening the DB file, and checking if it failed to open.

```c
#include <libpq-fe.h> // PostgreSQL library

...

/* Here we connect to the database, and store the connection in the conn struct. */
PGconn *conn = PQconnectdb("host=POSTGRESQL-HOSTNAME port=5432 dbname=POSTGRESQL-DBNAME user=POSTGRESQL-USER-NAME password=POSTGRESQL-PASSWORD");

/* Checking if the connection failed, if it did, it will log the error message, and deallocate the conn struct with PQfinish. */
switch (PQstatus(conn)) {
    case CONNECTION_OK:
    case CONNECTION_MADE:
        /* Successfully connected, you can proceed using database functions. */
        log_trace("[libpq] Successfully connected to the postgres database server.");
        break;
    case CONNECTION_STARTED:
        /* Still connecting, but really soon you will be connected. */
        log_trace("[libpq] Waiting for connection to be made.");
        break;
    case CONNECTION_AWAITING_RESPONSE:
        /* Waiting for a response from the database, probably will respond soon, if properly configured. */
        log_trace("[libpq] Waiting for a response from the server.");
        break;
    case CONNECTION_AUTH_OK:
        /* Authentication was successful, but the backend is still starting up. */
        log_trace("[libpq] Received authentication; waiting for backend start-up to finish.");
        break;
    case CONNECTION_SSL_STARTUP:
        /* Negotiating SSL encryption, since the connected database was using SSL encryption. */
        log_trace("[libpq] Almost connecting; negotiating SSL encryption.");
        break;
    case CONNECTION_SETENV:
        /* Negotiating environment-driven parameter settings, soonly will be connected */
        log_trace("[libpq] Almost connecting; negotiating environment-driven parameter settings.");
        break;
    default:
        /* Ugh, something went wrong while connecting to the database, probably a wrong password, firewall, or something blocking the connection. */
        log_fatal("[libpq] Error when trying to connect to the postgres database server. [%s]\n", PQerrorMessage(conn));
        PQfinish(conn);
}
```

### Creating a table

We got the database connected, so now we can now proceed creating a table, since it's required before saving any data into it.

```c

/* Here we are using PQexec to execute commands. In this example, we are using "CREATE TABLE" command, which creates a table in the database; the IF NOT EXISTS clause will only create the table if it doesn't exist, and the table will have two columns with the value type INT. */
PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS concord_guides(user_id INT, guild_id INT);");

if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    /* Something went wrong while creating the table, so we are going to log the error message of what went wrong. */
    log_fatal("[libpq] Error when trying to create the table. [%s]", PQerrorMessage(conn));
    PQclear(res);
    /* Even not properly being executed, this isn't, at least most of the time, the fault of the connection, so we are not closing it. */
    // PQfinish(conn);
    return;
} else {
    log_debug("[libpq] Successfully created the table.");
}
```

### Saving data into the table

Now that we have a table, we can now proceed saving data into it, which is really easy to do, since it's almost equal to create a table, the only difference is the command we send to the database to be executed.

```c
/* Creating a row in the created table with the user_id and guild_id of the message author as columns. */
PGresult *res = PQexec(conn, "INSERT INTO concord_guides(user_id, guild_id) values(%"PRIu64", %"PRIu64");", msg->author->id, msg->guild_id);

if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    /* Failed to insert the row, maybe the connection was blocked, or something like it. */
    log_fatal("[libpq] Error when inserting a row. [%s]", PQerrorMessage(conn));
    /* Deallocating the res struct made while trying to create the row. */
    PQclear(res);
    return;
} else {
    /* Successfully inserted the row (with the user_id and guild_id structures) into the table. */
    log_debug("[libpq] Successfully inserted a row.");
}
```

And, we're done! We have a row in the table, but now we have to read it.

### Reading data from the table

Reading the data is dead easy, but it's a little bigger than the other functions.

```c
char query[512];
snprintf(query, sizeof(query), "SELECT user_id FROM concord_guides WHERE user_id = %"PRIu64";", message->author->id);

PGresult *res = PQexec(conn, query);

if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    /* Failed to read row, maybe because the database is not connected, or the firewall blocked the PQexec. */
    log_fatal("[libpq] Error when reading row. [%s]", PQerrorMessage(conn));
    /* Deallocating the res struct made while trying to read the row. */
    PQclear(res);
    return;
}

char *userId = PQgetvalue(res, 0, 0);

log_debug("[libpq] Found the user id: %s", userId);
```

## SQLite3

### Opening the DB file

The first step in this guide will be opening the DB file, as it's required for the other SQLite3 functions like reading and writing data.

```c
#include <sqlite3.h> // Including the SQLite3 header so we can use its functions.

...

/* Here we are opening the DB file so other functions (read and save records) can be executed.
And also checking the status code of this function, to see if it failed or not to be executed. */

sqlite3 *db;
int rc = sqlite3_open("db.sqlite", &db);

/* Checking if something failed while opening the DB file. */
if (rc != SQLITE_OK) {
    /* As it saw something went wrong, it is going to log the error message of what went wrong. */
    log_fatal("[SQLITE] Error when opening the DB file. [%s]", sqlite3_errmsg(db));

    /* Since it failed, the resources must be deallocated. We are using the sqlite3_close for that. 
    If something went wrong while trying to close it, the code inside this if will be executed. (NOTE: Yes, even failing to open, you MUST use `sqlite3_close` as said in the SQLite3 docs!) */
      
    if (sqlite3_close(db) != SQLITE_OK) {
        /* Logging a fatal saying that it failed to close the DB. (NOTE: The sqlite3_errmsg function shows the error message of what happened) */
        log_fatal("[SQLITE] Failed to close sqlite DB. [%s]", sqlite3_errmsg(db));

        /* This is not a high-detailed guide, so we are not going to explain how to deal with this case with a lot of details. 
        But you will need to finalize the ongoing statement and execute the sqlite3_close again. */
        abort();
    }
    return;
}
```

> Whether or not an error occurs when it is opened, resources associated with the database connection handle should be released by passing it to sqlite3_close() when it is no longer required.

### Creating a SQLite3 table

Firstly, before trying to save data into the DB file, we need to create a SQL table (the schema for that DB). A DB schema can be summed up as "a description of all of the other tables, indexes, triggers, and views that are contained within the database".

```c
char *msgErr = NULL;

/* Here we are using the function below to set commands, in this case the command is the same as the PostgreSQL, see "Creating a table" of PostgreSQL section for more information. */
char *query = sqlite3_mprintf("CREATE TABLE IF NOT EXISTS concord_guides(user_id INT, guild_id INT);");
/* Executing the command that was set with sqlite3_mprintf, and saving the status code. */
rc = sqlite3_exec(db, query, NULL, NULL, &msgErr);

/* Deallocating the query variable, as it's not needed anymore. */
sqlite3_free(query);

/* Checking if something went wrong while executing the command. */
if (rc != SQLITE_OK) {
    /* Something went wrong, so logging it to the console with the error message. */
    log_fatal("[SQLITE] Something went wrong while creating concord_guides table. [%s]", msgErr);
    /* Closing the database since an error happened. */
    if (sqlite3_close(db) != SQLITE_OK) {
        log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
        abort();
    }
    return;
}
```

Done! If all goes well, then you've created a table called concord_guides.

### Saving records into the created table

Now that we created a table, we need to save records into it, it's the purpose of SQLite3.

For this, it will be pretty similar to the way that we created the table. Follow the example:

```c
/* Set the "INSERT INTO" command, which inserts a row into a table. The inserted row have user_id and guild_id as parameters. */
query = sqlite3_mprintf("INSERT INTO concord_guides(user_id, guild_id) values(%"PRIu64", %"PRIu64");", msg->author->id, msg->guild_id);
/* Executing the setted command. */
rc = sqlite3_exec(db, query, NULL, NULL, &msgErr);

/* Deallocating the query variable. */
sqlite3_free(query);

/* Checking if something went wrong while executing the command. */
if (rc != SQLITE_OK) {
    log_fatal("[SQLITE] Something went wrong while inserting values into concord_guides table. [%s]", msgErr);
    /* Closing the database since an error happened. */
    if (sqlite3_close(db) != SQLITE_OK) {
        log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
        abort();
    }
    return;
}
```

Pretty similar, isn't it? The difference is, the command now is "`INSERT INTO concord_guides(user_id, guild_id) values(%"PRIu64", %"PRIu64");`".

The `concord_guides()` parameters **MUST match the schema for the table** that we wish to insert corresponding `values()` into.

### Reading the saved records

Finally, after saving the records, we will be reading them! This is a little more complicated than creating the table and saving records. See the following example:

```c
sqlite3_stmt *stmt = NULL;

/* Here we are setting the command, using the "SELECT ... FROM ... WHERE" command, which explains itself. */
query = sqlite3_mprintf("SELECT user_id FROM concord_guides WHERE guild_id = %"PRIu64";", msg->guild_id);
/* Prepare the statement and returns the status code. */
rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);

/* Checks if anything went wrong while evaluating or executing the statement. */
if ((rc = sqlite3_step(stmt)) != SQLITE_ERROR) {
    /* Successfully read the record, reading it as a int64. You could use "sqlite3_column_text" to get a UTF-8 value. */
    log_trace("Sucessfully read the record: %lld.", sqlite3_column_int64(stmt, 0));
} else {
    /* Closing the database since an error happened. */
    if (sqlite3_close(db) != SQLITE_OK) {
        log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
        abort();
    }
}

/* Deallocating the statement struct. */
if (sqlite3_finalize(stmt) != SQLITE_OK) {
    log_fatal("[SQLITE] Error while executing function sqlite3_finalize.");
    abort();
}

/* Closing the database. */
sqlite3_close(db);
```

### Deleting records

After creating a table, saving records, and reading them, you may finally wish to delete the records.

Deleting records (AKA data) is as easy (and pretty similar) to creating a table, see the following example:

```c
/* Setting the command, using the "DELETE FROM ... WHERE" command, which deletes a row where some collumn is equal "msg->guild_id". */
query = sqlite3_mprintf("DELETE FROM concord_guides WHERE guild_id = %"PRIu64";", msg->guild_id);
/* Executing the command setted above. */
rc = sqlite3_exec(db, query, NULL, NULL, &msgErr);

/* Deallocating the query variable. */
sqlite3_free(query);

/* Checking if something went wrong while executing the command. */
if (rc != SQLITE_OK) {
    log_fatal("[SYSTEM] Something went wrong while deleting concord_guides table from guild_id. [%s]", msgErr);
    /* Closing the database since an error happened. */
    if (sqlite3_close(db) != SQLITE_OK) {
        log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
        abort();
    }
    return;
}
```

Okay, now the row where the collumn `guild_id` is equal to `msg->guild_id` is deleted.

### Example bot with the code of all processes

The following bot has the single purpose of **summing this entire guide** in a simple program.

Below, you'll find **4 commands**: `.createtable`, `.insertdata`, `.retrievedata`, `.deletedata`.

The `.createtable` should be the first one to be executed, it **creates a table** called `concord_guides` so records can be saved in it.

`.insertdata` **inserts a record into the table created with `.createtable`**. It inserts the ID of the guild and the ID of the message's author.

The command `.retrievedata` **retrieves the user_id saved with `.insertdata`**, using the ID of the guild (guild_id) as a **parameter to search it** and then sends a message in the same channel with the user_id saved.

And finally, the `.deletedata`, which **deletes the record inserted with `.insertdata`** that the guild_id is the same as the ID of the guild that the command is being executed (NOTE: This **doesn't delete the table****, only the record).

```c
#include <string.h>
#include <stdlib.h>

#include <concord/discord.h>
#include <concord/log.h>

#include <sqlite3.h>

void on_ready(struct discord *client, const struct discord_ready *bot) {
    log_info("Logged in as %s!", bot->user->username);
}

void on_createtable(struct discord *client, const struct discord_message *msg) {
    sqlite3 *db;
    int rc = sqlite3_open("db.sqlite", &db);

    if (rc != SQLITE_OK) {
        log_fatal("[SQLITE] Error when opening the db file. [%s]", sqlite3_errmsg(db));
      
        if (sqlite3_close(db) != SQLITE_OK) {
            log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
            abort();
        }
        return;
    }

    char *msgErr = NULL;

    char *query = sqlite3_mprintf("CREATE TABLE IF NOT EXISTS concord_guides(user_id INT, guild_id INT);");
    rc = sqlite3_exec(db, query, NULL, NULL, &msgErr);

    sqlite3_free(query);

    if (rc != SQLITE_OK) {
        log_fatal("[SQLITE] Something went wrong while creating concord_guides table. [%s]", msgErr);
        if (sqlite3_close(db) != SQLITE_OK) {
            log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
            abort();
        }
        return;
    }

    sqlite3_close(db);

    struct discord_create_message params = { .content = "Created the table." };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_insertdata(struct discord *client, const struct discord_message *msg) {
    sqlite3 *db;
    int rc = sqlite3_open("db.sqlite", &db);

    if (rc != SQLITE_OK) {
        log_fatal("[SQLITE] Error when opening the db file. [%s]", sqlite3_errmsg(db));
      
        if (sqlite3_close(db) != SQLITE_OK) {
            log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
            abort();
        }
        return;
    }

    char *msgErr = NULL;

    char * query = sqlite3_mprintf("INSERT INTO concord_guides(user_id, guild_id) values(%"PRIu64", %"PRIu64");", msg->author->id, msg->guild_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &msgErr);

    sqlite3_free(query);

    if (rc != SQLITE_OK) {
        log_fatal("[SQLITE] Something went wrong while inserting values into concord_guides table. [%s]", msgErr);

        if (sqlite3_close(db) != SQLITE_OK) {
            log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
            abort();
        }
    }

    sqlite3_close(db);

    struct discord_create_message params = { .content = "Inserted record." };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_retrievedata(struct discord *client, const struct discord_message *msg) {
    sqlite3 *db;
    int rc = sqlite3_open("db.sqlite", &db);

    if (rc != SQLITE_OK) {
        log_fatal("[SQLITE] Error when opening the db file. [%s]", sqlite3_errmsg(db));
      
        if (sqlite3_close(db) != SQLITE_OK) {
            log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
            abort();
        }
        return;
    }

    sqlite3_stmt *stmt = NULL;

    char *query = sqlite3_mprintf("SELECT user_id FROM concord_guides WHERE guild_id = %"PRIu64";", msg->guild_id);
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);

    if ((rc = sqlite3_step(stmt)) != SQLITE_ERROR) {
        char message[64];
        snprintf(message, sizeof(message), "Sucessfully read the record: %lld.\n", sqlite3_column_int64(stmt, 0));

        struct discord_create_message params = { .content = message };
        discord_create_message(client, msg->channel_id, &params, NULL);
    }

    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        log_fatal("[SQLITE] Error while executing function sqlite3_finalize.");
        abort();
    }

    sqlite3_close(db);
}


void on_deletedata(struct discord *client, const struct discord_message *msg) {
    sqlite3 *db;
    int rc = sqlite3_open("db.sqlite", &db);

    if (rc != SQLITE_OK) {
        log_fatal("[SQLITE] Error when opening the db file. [%s]", sqlite3_errmsg(db));
      
        if (sqlite3_close(db) != SQLITE_OK) {
            log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
            abort();
        }
        return;
    }

    char *msgErr = NULL;

    char *query = sqlite3_mprintf("DELETE FROM concord_guides WHERE guild_id = %"PRIu64";", msg->guild_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &msgErr);

    if (rc != SQLITE_OK) {
        log_fatal("[SYSTEM] Something went wrong while deleting concord_guides table from guild_id. [%s]", msgErr);
        if (sqlite3_close(db) != SQLITE_OK) {
            log_fatal("[SQLITE] Failed to close sqlite db. [%s]", sqlite3_errmsg(db));
            abort();
        }
    }

    sqlite3_close(db);

    struct discord_create_message params = { .content = "Deleted record." };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

int main(void) {
    struct discord *client = discord_config_init("config.json");

    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);

    discord_set_on_ready(client, &on_ready);
    discord_set_on_command(client, ".createtable", &on_createtable);
    discord_set_on_command(client, ".insertdata", &on_insertdata);
    discord_set_on_command(client, ".retrievedata", &on_retrievedata);
    discord_set_on_command(client, ".deletedata", &on_deletedata);

    discord_run(client);
}
```
