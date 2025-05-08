# Using SQLite3 with Concord

## Introduction

When building Discord bots, you often need to persist data across bot restarts. This is where databases come in handy. SQLite3 is an excellent choice for Discord bots because:

- **Self-contained**: The entire database is stored in a single file
- **Zero configuration**: No separate server process to install or manage
- **Cross-platform**: Works on all major operating systems
- **Reliability**: ACID-compliant with excellent crash recovery
- **Performance**: Fast for most operations typical in Discord bots
- **Lightweight**: Small memory and disk footprint

This guide will walk you through integrating SQLite3 with your Concord bot, covering everything from basic setup to a complete working example.

## Prerequisites

Before starting, ensure you have the SQLite3 development library installed on your system:

```bash
# Debian/Ubuntu
sudo apt-get install libsqlite3-dev

# Fedora/RHEL
sudo dnf install sqlite-devel

# macOS (Homebrew)
brew install sqlite3
```

When compiling your bot, you'll need to link against the SQLite3 library:

```bash
gcc mybot.c -o mybot -ldiscord -lcurl -lsqlite3
```

## Database Operations

### Opening a Database Connection

The first step when working with SQLite3 is to open a connection to your database file. If the file doesn't exist, SQLite will create it automatically.

```c
#include <sqlite3.h>  // Include the SQLite3 header

// Open a database connection
sqlite3 *db;
int rc = sqlite3_open("bot_data.db", &db);

if (rc != SQLITE_OK) {
    // Handle opening error
    logmod_log(ERROR, NULL, "SQLite error: %s", sqlite3_errmsg(db));
    
    // Always close the database handle, even on error
    sqlite3_close(db);
    return;
}

// Use the database connection...

// Close the database when done
sqlite3_close(db);
```

> **Important**: Always close your database connection with `sqlite3_close()` when you're done using it, regardless of whether an error occurred during opening. Failing to do so will leak resources.

### Creating a Table

Before storing data, you need to create a table. Each table has a schema defining the columns and their data types.

```c
// Error message holder
char *err_msg = NULL;

// Format the SQL query (using sqlite3_mprintf for proper escaping)
char *query = sqlite3_mprintf(
    "CREATE TABLE IF NOT EXISTS users("
    "user_id INTEGER PRIMARY KEY," // Discord user ID
    "guild_id INTEGER NOT NULL,"   // Discord guild ID
    "points INTEGER DEFAULT 0,"    // Example user data
    "last_active INTEGER"          // Timestamp
    ");"
);

// Execute the query
rc = sqlite3_exec(db, query, NULL, NULL, &err_msg);

// Free the query string (important to avoid memory leaks)
sqlite3_free(query);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "SQLite error: %s", err_msg);
    sqlite3_free(err_msg);  // Free the error message
    sqlite3_close(db);
    return;
}
```

#### SQLite Data Types

SQLite3 supports these basic data types:
- `INTEGER`: Whole numbers (use this for Discord IDs)
- `REAL`: Floating-point numbers
- `TEXT`: String data
- `BLOB`: Binary data
- `NULL`: Null values

Discord IDs should be stored as `INTEGER` since they're 64-bit numbers.

### Inserting Data

To store data in your table:

```c
// Insert a new user or update if already exists
char *query = sqlite3_mprintf(
    "INSERT OR REPLACE INTO users(user_id, guild_id, last_active) "
    "VALUES(%"PRIu64", %"PRIu64", %lld);",
    msg->author->id,          // Discord user ID
    msg->guild_id,            // Discord guild ID
    (long long)time(NULL)     // Current timestamp
);

rc = sqlite3_exec(db, query, NULL, NULL, &err_msg);
sqlite3_free(query);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "Insert failed: %s", err_msg);
    sqlite3_free(err_msg);
    return;
}
```

The `%"PRIu64"` format specifier is used for 64-bit unsigned integers like Discord IDs. It's defined in `<inttypes.h>`, which you should include.

### Querying Data

Querying data is slightly more complex because you need to prepare a statement and fetch results:

```c
// Prepare a statement
sqlite3_stmt *stmt = NULL;
char *query = sqlite3_mprintf(
    "SELECT points, last_active FROM users WHERE user_id = %"PRIu64" AND guild_id = %"PRIu64";",
    target_user_id, guild_id
);

rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
sqlite3_free(query);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "Failed to prepare query: %s", sqlite3_errmsg(db));
    return;
}

// Execute the query and fetch results
if (sqlite3_step(stmt) == SQLITE_ROW) {
    // Data found - access columns (0-indexed)
    int points = sqlite3_column_int(stmt, 0);
    long long last_active = sqlite3_column_int64(stmt, 1);
    
    // Use the retrieved data
    char response[256];
    snprintf(response, sizeof(response), 
             "User has %d points, last active: %lld", 
             points, last_active);
             
    struct discord_create_message params = { .content = response };
    discord_create_message(client, msg->channel_id, &params, NULL);
} else {
    // No data found
    struct discord_create_message params = { .content = "No data found for this user." };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

// Always finalize your statements
sqlite3_finalize(stmt);
```

#### Accessing Different Column Types

SQLite3 provides different functions to retrieve column values based on their type:

- `sqlite3_column_int(stmt, col)` - For 32-bit integers
- `sqlite3_column_int64(stmt, col)` - For 64-bit integers (use for Discord IDs)
- `sqlite3_column_double(stmt, col)` - For floating-point numbers
- `sqlite3_column_text(stmt, col)` - For text (returns `unsigned char*`)
- `sqlite3_column_blob(stmt, col)` - For binary data

### Updating Data

Updating existing records uses similar syntax to inserting:

```c
char *query = sqlite3_mprintf(
    "UPDATE users SET points = points + 1 WHERE user_id = %"PRIu64" AND guild_id = %"PRIu64";",
    user_id, guild_id
);

rc = sqlite3_exec(db, query, NULL, NULL, &err_msg);
sqlite3_free(query);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "Update failed: %s", err_msg);
    sqlite3_free(err_msg);
}
```

### Deleting Data

To remove records from your database:

```c
char *query = sqlite3_mprintf(
    "DELETE FROM users WHERE user_id = %"PRIu64" AND guild_id = %"PRIu64";",
    user_id, guild_id
);

rc = sqlite3_exec(db, query, NULL, NULL, &err_msg);
sqlite3_free(query);

if (rc != SQLITE_OK) {
    logmod_log(ERROR, NULL, "Delete failed: %s", err_msg);
    sqlite3_free(err_msg);
}
```

## Best Practices

### 1. Use Prepared Statements

For queries that are executed frequently, use prepared statements instead of `sqlite3_exec()`. They're more efficient and provide better protection against SQL injection:

```c
// Prepare once
sqlite3_stmt *stmt = NULL;
rc = sqlite3_prepare_v2(db, 
    "INSERT INTO users(user_id, guild_id, points) VALUES(?, ?, ?);",
    -1, &stmt, NULL);

// Execute many times with different values
sqlite3_bind_int64(stmt, 1, user_id);     // Bind first parameter
sqlite3_bind_int64(stmt, 2, guild_id);    // Bind second parameter
sqlite3_bind_int(stmt, 3, 100);           // Bind third parameter

rc = sqlite3_step(stmt);                  // Execute
sqlite3_reset(stmt);                      // Reset for next execution

// Finalize when done
sqlite3_finalize(stmt);
```

### 2. Use Transactions for Multiple Operations

When performing multiple database operations, wrap them in a transaction for better performance:

```c
// Begin transaction
sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

// Perform multiple operations...

// Commit transaction (or ROLLBACK if errors occurred)
sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
```

### 3. Handle Concurrency

SQLite can handle concurrent reads, but writers block all other operations. For bots handling many guilds, consider:

- Using separate database files per guild
- Implementing a connection pool
- Using a more robust database system like PostgreSQL for high-traffic bots

### 4. Error Handling and Recovery

Always check return codes and implement proper error handling:

```c
if (rc != SQLITE_OK) {
    // Log detailed error information
    logmod_log(ERROR, NULL, 
        "SQLite error (%d): %s - %s", 
        rc, sqlite3_errstr(rc), sqlite3_errmsg(db));
    
    // Take appropriate recovery action
    if (rc == SQLITE_BUSY || rc == SQLITE_LOCKED) {
        // Database is locked, wait and retry
        sleep(1);
        // retry operation...
    }
}
```

## Complete Example Bot

This example bot demonstrates a simple points system using SQLite3:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#include <concord/discord.h>
#include <concord/logmod.h>
#include <sqlite3.h>

// Initialize database and create tables if needed
sqlite3* init_database() {
    sqlite3 *db;
    int rc = sqlite3_open("bot_data.db", &db);
    
    if (rc != SQLITE_OK) {
        logmod_log(ERROR, NULL, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    
    char *err_msg = NULL;
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "  user_id INTEGER NOT NULL,"
        "  guild_id INTEGER NOT NULL,"
        "  points INTEGER DEFAULT 0,"
        "  last_active INTEGER,"
        "  PRIMARY KEY (user_id, guild_id)"
        ");";
        
    rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        logmod_log(ERROR, NULL, "SQL error: %s", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return NULL;
    }
    
    return db;
}

// Global database connection
sqlite3 *db = NULL;

void on_ready(struct discord *client, const struct discord_ready *event) {
    logmod_log(INFO, NULL, "Logged in as %s!", event->user->username);
}

// Add points to a user
void on_points_add(struct discord *client, const struct discord_message *msg) {
    if (!msg->guild_id) return; // Ignore DMs
    
    // Parse target user from message
    if (!msg->mentions || !msg->mentions->size) {
        struct discord_create_message params = { .content = "Please mention a user to add points to." };
        discord_create_message(client, msg->channel_id, &params, NULL);
        return;
    }
    
    u64snowflake target_id = msg->mentions->array[0]->id;
    int points_to_add = 1; // Default 1 point
    
    // Parse command for custom points amount
    char *args = strstr(msg->content, " ");
    if (args) {
        char *end_of_mention = strstr(args + 1, ">");
        if (end_of_mention && *(end_of_mention + 1)) {
            int parsed = atoi(end_of_mention + 1);
            if (parsed > 0) points_to_add = parsed;
        }
    }
    
    char *query = sqlite3_mprintf(
        "INSERT INTO users(user_id, guild_id, points, last_active) "
        "VALUES(%"PRIu64", %"PRIu64", %d, %lld) "
        "ON CONFLICT(user_id, guild_id) DO "
        "UPDATE SET points = points + %d, last_active = %lld;",
        target_id, msg->guild_id, points_to_add, (long long)time(NULL),
        points_to_add, (long long)time(NULL)
    );
    
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, query, NULL, NULL, &err_msg);
    sqlite3_free(query);
    
    if (rc != SQLITE_OK) {
        logmod_log(ERROR, NULL, "Failed to add points: %s", err_msg);
        sqlite3_free(err_msg);
        
        struct discord_create_message params = { .content = "Failed to add points. Database error." };
        discord_create_message(client, msg->channel_id, &params, NULL);
        return;
    }
    
    char response[256];
    snprintf(response, sizeof(response), "<@%"PRIu64"> received %d points!", target_id, points_to_add);
    
    struct discord_create_message params = { .content = response };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

// Check points for a user
void on_points_check(struct discord *client, const struct discord_message *msg) {
    if (!msg->guild_id) return; // Ignore DMs
    
    u64snowflake target_id = msg->author->id; // Default to message author
    
    // Check if a user was mentioned
    if (msg->mentions && msg->mentions->size) {
        target_id = msg->mentions->array[0]->id;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *query = sqlite3_mprintf(
        "SELECT points, last_active FROM users "
        "WHERE user_id = %"PRIu64" AND guild_id = %"PRIu64";",
        target_id, msg->guild_id
    );
    
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_free(query);
    
    if (rc != SQLITE_OK) {
        logmod_log(ERROR, NULL, "Failed to prepare query: %s", sqlite3_errmsg(db));
        
        struct discord_create_message params = { .content = "Database error occurred." };
        discord_create_message(client, msg->channel_id, &params, NULL);
        return;
    }
    
    char response[256];
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int points = sqlite3_column_int(stmt, 0);
        long long last_active = sqlite3_column_int64(stmt, 1);
        
        time_t active_time = (time_t)last_active;
        char time_str[64];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&active_time));
        
        snprintf(response, sizeof(response), 
                 "<@%"PRIu64"> has %d points. Last active: %s", 
                 target_id, points, time_str);
    } else {
        snprintf(response, sizeof(response), 
                 "<@%"PRIu64"> has no points yet.", target_id);
    }
    
    sqlite3_finalize(stmt);
    
    struct discord_create_message params = { .content = response };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

// Show top 5 users by points
void on_points_leaderboard(struct discord *client, const struct discord_message *msg) {
    if (!msg->guild_id) return; // Ignore DMs
    
    sqlite3_stmt *stmt = NULL;
    char *query = sqlite3_mprintf(
        "SELECT user_id, points FROM users "
        "WHERE guild_id = %"PRIu64" "
        "ORDER BY points DESC LIMIT 5;",
        msg->guild_id
    );
    
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_free(query);
    
    if (rc != SQLITE_OK) {
        logmod_log(ERROR, NULL, "Failed to prepare leaderboard query: %s", sqlite3_errmsg(db));
        return;
    }
    
    struct discord_embed embed = {
        .title = "Points Leaderboard",
        .color = 0x3498DB,
        .timestamp = discord_timestamp(client)
    };
    
    char description[512] = "Top 5 users by points:\n\n";
    int position = 1;
    int has_entries = 0;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        has_entries = 1;
        u64snowflake user_id = sqlite3_column_int64(stmt, 0);
        int points = sqlite3_column_int(stmt, 1);
        
        char line[128];
        snprintf(line, sizeof(line), "%d. <@%"PRIu64"> - %d points\n", 
                 position++, user_id, points);
        
        strcat(description, line);
    }
    
    sqlite3_finalize(stmt);
    
    if (!has_entries) {
        strcpy(description, "No points have been awarded yet.");
    }
    
    embed.description = description;
    
    struct discord_create_message params = {
        .embeds = &(struct discord_embeds){
            .size = 1,
            .array = &embed
        }
    };
    
    discord_create_message(client, msg->channel_id, &params, NULL);
}

int main(void) {
    // Initialize database
    db = init_database();
    if (!db) {
        logmod_log(FATAL, NULL, "Failed to initialize database. Exiting.");
        return 1;
    }
    
    // Initialize Discord bot
    struct discord *client = discord_from_json("config.json");
    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
    
    // Set up event handlers
    discord_set_on_ready(client, &on_ready);
    discord_set_on_command(client, ".points add", &on_points_add);
    discord_set_on_command(client, ".points check", &on_points_check);
    discord_set_on_command(client, ".points top", &on_points_leaderboard);
    
    // Run the bot
    discord_run(client);
    
    // Clean up
    sqlite3_close(db);
    return 0;
}
```

## Troubleshooting

### Common SQLite Errors

| Error | Description | Solution |
|-------|-------------|----------|
| `SQLITE_BUSY` | Database file is locked | Use transactions, implement retry logic |
| `SQLITE_CONSTRAINT` | Constraint violation (e.g., unique key) | Use `INSERT OR REPLACE` or proper error handling |
| `SQLITE_NOMEM` | Out of memory | Check system resources, optimize queries |
| `SQLITE_READONLY` | Database is read-only | Check file permissions |
| `SQLITE_IOERR` | Disk I/O error | Check disk space and health |

### Database Corruption

If your database becomes corrupted (rare with proper usage):

1. Always maintain backups
2. Use `PRAGMA integrity_check;` to verify database integrity
3. Use SQLite's recovery tools like `.recover` in the SQLite CLI

## Further Reading

- [SQLite Official Documentation](https://www.sqlite.org/docs.html)
- [SQLite C Interface](https://www.sqlite.org/c3ref/intro.html)
- [SQLite Query Language](https://www.sqlite.org/lang.html)

## Conclusion

SQLite3 is an excellent choice for Discord bots due to its simplicity, reliability, and zero-configuration nature. By following this guide, you should now be able to effectively store and retrieve persistent data in your Concord bot.

Remember these key points:
- Always check return codes and handle errors
- Free allocated resources (statements, error messages, query strings)
- Use transactions for multiple operations
- Consider database design carefully to match your bot's needs
