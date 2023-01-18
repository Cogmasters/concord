# Setting up with env variables

## What is an "env variable"?

Environment variables are dynamically named values that can affect how processes behave when their values are edited. The shell is responsible for defining and managing environment variables. They can store values like paths, names, ints, and anything (except for files). They are widely used in many applications.

## JSON fields vs env variables

Even though JSON is widely used by applications for storing data, it is NOT good for storing sensitive data. **Env variables are much easier to read** than JSON fields, since you can use very straightforward functions like `getenv`, while in **JSON you would require third-party libraries** such [jsmn-find](https://github.com/lcsmuller/jsmn-find) to read stored data.

## Setting an env variable

There are **multiple ways of setting env variables**, but **we don't want all the users in the machine to know the values of the env variables**, so we are going to stick with setting them into a `.sh` file that runs the bot (if using Concord or any type of program).

First, **create a file** with whatever name you want, for example, `foo.sh`. Then, **put in the file the following content** (`myBot` is the file with the binary result of your bot).

Depending on the shell you are using, **the way that you set an env variable will be different**, please choose the example below that matches your OS shell:

**csh**:

```sh
#!/bin/csh
setenv ENV_VARIABLE_NAME "The value of the env variable"
./myBot
```

**bash**:

```sh
#!/bin/bash
export ENV_VARIABLE_NAME="The value of the env variable"
./myBot
```

**korn shell / ksh**:

```sh
#!/bin/ksh
export ENV_VARIABLE_NAME="The value of the env variable"
./myBot
```

**borne shell / POSIX shell**:

```sh
#!/bin/sh
ENV_VARIABLE_NAME="The value of the env variable"; export ENV_VARIABLE_NAME
```

NOTE: **Change the `ENV_VARIABLE_NAME` for whatever env variable name you want to, and also the value of it.**

Done! It is that simple, you can now proceed to read its value.

## Reading env variables


You have set the env variable - now you **will need to get it**. There are two easy ways to **get the env variable value**, take a look and choose the best one for you:

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

Using `${}` (this only applies to [discord_config](https://cogmasters.github.io/concord/group__DiscordClient.html#gacd52a9fc58a1fcb9b4719a5cedd70f5d) and [discord_config_init](https://cogmasters.github.io/concord/group__DiscordClient.html#ga75bbe1d3eb9e6d03953b6313e5543afb)):

```c
#include <stdio.h>

#include <concord/discord.h>
#include <concord/log.h>

#define ENV_VARIABLE_NAME "YOUR_ENV_NAME"

void on_ready(struct discord *client, const struct discord_ready *event) {
    log_trace("Logged in as %s", event->username);
}

int main() {
    struct discord *client = discord_init("${" ENV_VARIABLE_NAME "}");

    discord_set_on_ready(client, &on_ready);

    discord_run(client);
    return 0;
}
```
