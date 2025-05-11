# Using Environment Variables with Concord

## Introduction

This guide explains how to use environment variables with your Concord bot for safely storing sensitive information such as bot tokens, API keys, and other configuration values. Environment variables provide a more secure alternative to hardcoding sensitive data or storing it in configuration files that might be accidentally committed to version control systems.

## What are Environment Variables?

Environment variables are dynamic named values that can affect how running processes behave on a computer. They are part of the environment in which a process runs and provide a way to:

- Configure application behavior without modifying code
- Store sensitive information securely
- Share configuration across multiple applications
- Override default settings when needed

Environment variables can store various types of data including strings, paths, numbers, and boolean values. They're widely used in development, deployment, and production environments.

## Environment Variables vs. JSON Configuration

While JSON configuration files are commonly used for storing application settings, they have several disadvantages for sensitive data:

| Environment Variables | JSON Configuration Files |
|----------------------|--------------------------|
| Not typically stored in version control | Can be accidentally committed to repositories |
| Access restricted by operating system permissions | Accessible to anyone with file access |
| Simple to read with standard library functions | Require parsing libraries or custom code |
| Easy to change between environments | Need different files for different environments |
| Native support in deployment platforms | Need additional mechanisms for secure storage |

Concord supports both methods, but environment variables are recommended for sensitive information like tokens and API keys.

## Setting Environment Variables

There are multiple ways to set environment variables. For development purposes, we recommend creating a script file that sets the variables and then launches your bot.

### Method 1: Using Shell Scripts

First, create a file (e.g., `run-bot.sh`) with the following content based on your shell:

**Bash (most common):**

```sh
#!/bin/bash
export DISCORD_BOT_TOKEN="your_bot_token_here"
export DATABASE_URL="your_database_connection_string"
./myBot
```

**C Shell (csh/tcsh):**

```sh
#!/bin/csh
setenv DISCORD_BOT_TOKEN "your_bot_token_here"
setenv DATABASE_URL "your_database_connection_string"
./myBot
```

**Korn Shell (ksh):**

```sh
#!/bin/ksh
export DISCORD_BOT_TOKEN="your_bot_token_here"
export DATABASE_URL="your_database_connection_string"
./myBot
```

**POSIX Shell (sh):**

```sh
#!/bin/sh
DISCORD_BOT_TOKEN="your_bot_token_here"
DATABASE_URL="your_database_connection_string"
export DISCORD_BOT_TOKEN DATABASE_URL
./myBot
```

Then make the script executable and run it:

```sh
chmod +x run-bot.sh
./run-bot.sh
```

### Method 2: Setting Variables for the Current Session

You can also set environment variables for your current terminal session:

**Bash/Ksh/Zsh:**
```sh
export DISCORD_BOT_TOKEN="your_bot_token_here"
```

**C Shell:**
```sh
setenv DISCORD_BOT_TOKEN "your_bot_token_here"
```

### Method 3: Using .env Files with External Tools

For more complex projects, you might want to use a `.env` file with a tool like [dotenv](https://github.com/motdotla/dotenv):

## Reading Environment Variables

You have set the environment variable - now you will need to get it. There are two easy ways to get the environment variable value, take a look and choose the best one for you:

Example using the `getenv` function:

```c
#include <stdio.h>
#include <stdlib.h>

#define ENV_VARIABLE_NAME "YOUR_ENV_NAME"

int main() {
    printf("The value of the env variable is: %s\n", getenv(ENV_VARIABLE_NAME));

    return 0;
}
```

Using `${}` (this only applies to [discord_config](https://cogmasters.github.io/concord/group__DiscordClient.html#gacd52a9fc58a1fcb9b4719a5cedd70f5d) and [discord_from_json](https://cogmasters.github.io/concord/group__DiscordClient.html#ga75bbe1d3eb9e6d03953b6313e5543afb)):

```c
#include <stdio.h>

#include <concord/discord.h>
#include <concord/logmod.h>

#define ENV_VARIABLE_NAME "YOUR_ENV_NAME"

void on_ready(struct discord *client, const struct discord_ready *event) {
    logmod_log(TRACE, NULL, "Logged in as %s", event->username);
}

int main() {
    struct discord *client = discord_from_token("${" ENV_VARIABLE_NAME "}");

    discord_set_on_ready(client, &on_ready);

    discord_run(client);
    return 0;
}
```
