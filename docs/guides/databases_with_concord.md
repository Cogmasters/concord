# Using Databases with Concord

When developing a Discord bot, you often need to persist data across bot restarts. Databases provide a reliable way to store and retrieve information that won't be lost when your bot shuts down or crashes.

This guide covers two popular database options for Concord bots:
- **SQLite3**: A lightweight, file-based database ideal for simple bots or development
- **PostgreSQL**: A robust, client-server database system better for production applications

## Choosing the Right Database

| Feature | SQLite3 | PostgreSQL |
|---------|---------|------------|
| **Setup Complexity** | Low (single file) | Higher (server installation) |
| **Scalability** | Limited (suitable for small-to-medium bots) | High (can handle large applications) |
| **Concurrency** | Limited (single-writer, multiple-reader) | Excellent (true concurrent access) |
| **Performance** | Good for most small bots | Better for high-load applications |
| **Administration** | Minimal | Requires more maintenance |
| **Use Case** | Personal bots, development | Production bots, multi-server bots |

## PostgreSQL

PostgreSQL is a powerful, enterprise-grade database system with robust features for scaling, concurrency, and data integrity.

### Installation

Before using PostgreSQL, you'll need to:

1. Install PostgreSQL on your server or use a hosted solution
2. Install the PostgreSQL client library:

```bash
# Debian/Ubuntu
sudo apt-get install libpq-dev

# Fedora/RHEL
sudo dnf install postgresql-devel

# macOS
brew install postgresql
```

When compiling your bot, link against libpq:

```bash
gcc bot.c -o bot -ldiscord -lcurl -lpq
```

### Opening a Database Connection

Creating a connection to PostgreSQL requires providing authentication credentials:

```c
#include <libpq-fe.h> // PostgreSQL library
#include <concord/discord.h>
#include <concord/logmod.h>

// Connect to the database
PGconn *conn = PQconnectdb("host=localhost port=5432 dbname=mybot user=postgres password=secretpassword");

// Check connection status
if (PQstatus(conn) != CONNECTION_OK) {
    logmod_log(FATAL, NULL, "Connection to database failed: %s", PQerrorMessage(conn));
    PQfinish(conn);
    return;
}

logmod_log(INFO, NULL, "Successfully connected to PostgreSQL database");

// Use the connection for database operations...

// Always close the connection when done
PQfinish(conn);
```

For better security, consider storing credentials in environment variables or a config file rather than hardcoding them.

### Creating a Table

Tables define the structure of your data. Here's how to create one:

```c
// Create a table for storing user data
PGresult *res = PQexec(conn, 
    "CREATE TABLE IF NOT EXISTS users("
    "user_id BIGINT PRIMARY KEY,"  // Discord IDs are 64-bit integers
    "guild_id BIGINT NOT NULL,"
    "points INTEGER DEFAULT 0,"
    "last_seen TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
    ")");

if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    logmod_log(ERROR, NULL, "Failed to create table: %s", PQerrorMessage(conn));
    PQclear(res);
    // Continue execution - table creation might fail if table already exists
} else {
    logmod_log(INFO, NULL, "Table created or already exists");
}

// Always clean up the result object
PQclear(res);
```

### Using Prepared Statements

Prepared statements are safer and more efficient than building SQL strings directly:

```c
// Prepare a statement for inserting user data
res = PQprepare(conn, "insert_user",
    "INSERT INTO users(user_id, guild_id, points) VALUES($1, $2, $3) "
    "ON CONFLICT(user_id) DO UPDATE SET points = users.points + $3",
    3, NULL);

if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    logmod_log(ERROR, NULL, "Failed to prepare statement: %s", PQerrorMessage(conn));
    PQclear(res);
    return;
}
PQclear(res);

// Execute the prepared statement with parameters
const char *paramValues[3];
char user_id_str[32], guild_id_str[32], points_str[32];

snprintf(user_id_str, sizeof(user_id_str), "%"PRIu64, msg->author->id);
snprintf(guild_id_str, sizeof(guild_id_str), "%"PRIu64, msg->guild_id);
snprintf(points_str, sizeof(points_str), "%d", 10); // Add 10 points

paramValues[0] = user_id_str;
paramValues[1] = guild_id_str;
paramValues[2] = points_str;

res = PQexecPrepared(conn, "insert_user", 3, paramValues, NULL, NULL, 0);

if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    logmod_log(ERROR, NULL, "Failed to execute statement: %s", PQerrorMessage(conn));
} else {
    logmod_log(INFO, NULL, "Successfully updated user points");
}

PQclear(res);
```

### Reading Data

To retrieve data from PostgreSQL:

```c
// Query user points
char user_id_str[32];
snprintf(user_id_str, sizeof(user_id_str), "%"PRIu64, msg->author->id);

const char *paramValues[1] = {user_id_str};

res = PQexecParams(conn,
    "SELECT points, last_seen FROM users WHERE user_id = $1",
    1, NULL, paramValues, NULL, NULL, 0);

if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    logmod_log(ERROR, NULL, "Query failed: %s", PQerrorMessage(conn));
    PQclear(res);
    return;
}

// Check if we got any results
if (PQntuples(res) > 0) {
    int points = atoi(PQgetvalue(res, 0, 0));
    const char *last_seen = PQgetvalue(res, 0, 1);
    
    char response[256];
    snprintf(response, sizeof(response), 
             "You have %d points. Last seen: %s", points, last_seen);
             
    struct discord_create_message params = { .content = response };
    discord_create_message(client, msg->channel_id, &params, NULL);
} else {
    // No data found
    struct discord_create_message params = { .content = "No data found for your user." };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

PQclear(res);
```

### PostgreSQL Best Practices

1. **Use connection pooling** for busy bots
2. **Use prepared statements** to prevent SQL injection
3. **Implement transactions** for operations that modify multiple tables
4. **Handle connection failures gracefully** with reconnection logic
5. **Include proper indexes** on frequently queried columns

## SQLite3

SQLite3 is a lightweight, file-based database that's perfect for simpler bots or development environments.

### Installation

Install the SQLite3 development library:

```bash
# Debian/Ubuntu
sudo apt-get install libsqlite3-dev

# Fedora/RHEL
sudo dnf install sqlite-devel

# macOS
brew install sqlite3
```

When compiling, link against SQLite3:

```bash
gcc bot.c -o bot -ldiscord -lcurl -lsqlite3
```

### Opening a Database Connection

SQLite3 stores your entire database in a single file:

```c
#include <sqlite3.h>
#include <concord/discord.h>
#include <concord/logmod.h>

sqlite3 *db;
int rc = sqlite3_open("bot_data.db", &db);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "Failed to open database: %s", sqlite3_errmsg(db));
    sqlite3_close(db);  // Always close even on error
    return;
}

// Use the database...

// Close when done
sqlite3_close(db);
```

### Creating a Table

Create tables to define your data structure:

```c
char *err_msg = NULL;
const char *sql = 
    "CREATE TABLE IF NOT EXISTS users("
    "user_id INTEGER NOT NULL,"    // Discord user ID (64-bit)
    "guild_id INTEGER NOT NULL,"   // Discord guild ID (64-bit)
    "points INTEGER DEFAULT 0,"    // User points
    "last_seen INTEGER,"          // Timestamp
    "PRIMARY KEY(user_id, guild_id)"
    ")";

rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "SQL error: %s", err_msg);
    sqlite3_free(err_msg);
    return;
}
```

### Using Prepared Statements

Prepared statements are safer and more efficient than direct SQL:

```c
// Prepare statement for adding points
sqlite3_stmt *stmt = NULL;
rc = sqlite3_prepare_v2(db,
    "INSERT INTO users(user_id, guild_id, points, last_seen) "
    "VALUES(?, ?, ?, ?) "
    "ON CONFLICT(user_id, guild_id) DO "
    "UPDATE SET points = points + excluded.points, last_seen = excluded.last_seen",
    -1, &stmt, NULL);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "Failed to prepare statement: %s", sqlite3_errmsg(db));
    return;
}

// Bind parameters to the statement
sqlite3_bind_int64(stmt, 1, msg->author->id);     // user_id
sqlite3_bind_int64(stmt, 2, msg->guild_id);       // guild_id
sqlite3_bind_int(stmt, 3, 10);                    // points to add
sqlite3_bind_int64(stmt, 4, time(NULL));          // current timestamp

// Execute statement
rc = sqlite3_step(stmt);
if (rc != SQLITE_DONE) {
    logmod_log(ERROR, NULL, "Failed to execute statement: %s", sqlite3_errmsg(db));
}

// Reset statement for reuse or finalize
sqlite3_finalize(stmt);
```

### Reading Data

Query data from your database:

```c
// Prepare a query
sqlite3_stmt *stmt = NULL;
rc = sqlite3_prepare_v2(db,
    "SELECT points, last_seen FROM users WHERE user_id = ? AND guild_id = ?",
    -1, &stmt, NULL);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "Failed to prepare query: %s", sqlite3_errmsg(db));
    return;
}

// Bind parameters
sqlite3_bind_int64(stmt, 1, msg->author->id);
sqlite3_bind_int64(stmt, 2, msg->guild_id);

// Execute and fetch results
if (sqlite3_step(stmt) == SQLITE_ROW) {
    // Data found - get values from columns
    int points = sqlite3_column_int(stmt, 0);
    int64_t last_seen = sqlite3_column_int64(stmt, 1);
    
    // Format a timestamp
    time_t timestamp = (time_t)last_seen;
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
    
    char response[256];
    snprintf(response, sizeof(response), 
             "You have %d points. Last seen: %s", points, time_str);
             
    struct discord_create_message params = { .content = response };
    discord_create_message(client, msg->channel_id, &params, NULL);
} else {
    // No data found
    struct discord_create_message params = { .content = "No data found for your user." };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

// Always finalize statements
sqlite3_finalize(stmt);
```

### SQLite3 Best Practices

1. **Use transactions** for multiple operations:
   ```c
   sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
   // Multiple operations...
   sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
   ```

2. **Avoid database locks** by keeping transactions short

3. **Use prepared statements** to prevent SQL injection and improve performance

4. **Check error codes** from all SQLite3 functions

5. **Always finalize statements** and close the database when done

6. **Consider WAL mode** for better concurrency:
   ```c
   sqlite3_exec(db, "PRAGMA journal_mode=WAL", NULL, NULL, NULL);
   ```

### Debugging SQLite3 Issues

Use these techniques to troubleshoot database problems:

1. **Enable foreign key constraints**:
   ```c
   sqlite3_exec(db, "PRAGMA foreign_keys = ON", NULL, NULL, NULL);
   ```

2. **Check database integrity**:
   ```c
   sqlite3_exec(db, "PRAGMA integrity_check", NULL, NULL, NULL);
   ```

3. **Trace SQL statements** for debugging:
   ```c
   sqlite3_trace(db, callback_function, user_data);
   ```

## Example Bot Implementation

For a complete working example with SQLite3, see our [SQLite3 with Concord](sqlite3_db_with_concord.md) guide which includes a full bot implementation with points tracking and leaderboards.

## Further Reading

- [SQLite Documentation](https://www.sqlite.org/docs.html)
- [PostgreSQL C API Documentation](https://www.postgresql.org/docs/current/libpq.html)
- [SQL Injection Prevention](https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html)
