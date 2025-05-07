# The Scheduler Event

The scheduler is a powerful feature that gives you direct access to the raw JSON payloads received from Discord's WebSocket. This provides developers with fine-grained control over event handling, allowing you to:

- Ignore specific events
- Process events in the main thread
- Spawn worker threads for handling events asynchronously
- Parse JSON directly for maximum performance

## Understanding the Scheduler

The scheduler is a callback function that gets called for every event received from Discord. It allows you to intercept events before Concord's standard event handlers are invoked, giving you control over how and whether they are processed.

### Return Values

Your scheduler function can return one of these values to control how the event is handled:

- `DISCORD_EVENT_IGNORE` - Completely ignore the event (Concord won't process it)
- `DISCORD_EVENT_MAIN_THREAD` - Process the event in the main thread
- `DISCORD_EVENT_WORKER_THREAD` - Spawn a worker thread to handle the event asynchronously

## How to Use the Scheduler

Implementing a scheduler is straightforward. Here's an example that logs MESSAGE_CREATE events and ignores them:

```c
enum discord_event_scheduler scheduler(struct discord *client,
                                      const char data[],
                                      size_t length,
                                      enum discord_gateway_events event)
{
    /* Check which event we received */
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        /* Log the raw JSON payload for this event */
        logmod_log(DEBUG, NULL, "Received message JSON: %s", data);

        /* Return DISCORD_EVENT_IGNORE to prevent Concord from processing this event */
        return DISCORD_EVENT_IGNORE;
    }

    /* For all other events, let Concord process them normally */
    return DISCORD_EVENT_MAIN_THREAD;
}

int main() {
    // ... initialize client ...

    /* Register the scheduler with Concord */
    discord_set_event_scheduler(client, &scheduler);

    // ... rest of your code ...
}
```

Remember to register your scheduler function with `discord_set_event_scheduler()`. Without this step, Concord won't use your scheduler.

## JSON Parsing Methods

There are two primary ways to parse the JSON payloads in your scheduler:

### 1. Using discord_xxx_from_json()

This method is the most convenient when you need the full structure of an event. Concord provides various functions like `discord_message_from_json()` to convert JSON payloads into C structures.

```c
enum discord_event_scheduler scheduler(struct discord *client,
                                      const char data[],
                                      size_t length,
                                      enum discord_gateway_events event)
{
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        struct discord_message message;

        /* Parse the JSON into a discord_message structure */
        discord_message_from_json(data, length, &message);

        /* Now you can access all message fields directly */
        logmod_log(DEBUG, NULL, "Message content: %s", message.content);
        logmod_log(DEBUG, NULL, "Author: %s#%s",
                   message.author->username,
                   message.author->discriminator);

        /* Important: Clean up the allocated structure when done */
        discord_message_cleanup(&message);

        return DISCORD_EVENT_IGNORE;
    }

    return DISCORD_EVENT_MAIN_THREAD;
}
```

### 2. Using jsmn-find (For Performance)

When you only need specific fields from the JSON payload, using `jsmn-find` is faster and requires less memory since you don't need to parse the entire structure:

```c
enum discord_event_scheduler scheduler(struct discord *client,
                                      const char data[],
                                      size_t length,
                                      enum discord_gateway_events event)
{
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        jsmnf_loader loader;
        jsmnf_table table[0x1000];
        int r;

        /* Initialize jsmn-find loader */
        jsmnf_init(&loader);

        /* Load JSON into lookup table */
        r = jsmnf_load(&loader, data, length, table, sizeof(table) / sizeof *table);
        if (r < 0) {
            logmod_log(ERROR, NULL, "Failed to load jsmn-find lookup table.");
            return DISCORD_EVENT_IGNORE;
        }

        /* Find just the "content" field in the JSON */
        const jsmnf_pair *content = jsmnf_find(loader.root, "content", strlen("content"));
        if (!content) {
            logmod_log(ERROR, NULL, "Failed to find the \"content\" key.");
            return DISCORD_EVENT_IGNORE;
        }

        /* Extract the content string */
        char content_str[1024];
        snprintf(content_str, sizeof(content_str), "%.*s",
                content->v->end - content->v->start,
                data + content->v->start);

        logmod_log(DEBUG, NULL, "Message content: %s", content_str);

        return DISCORD_EVENT_IGNORE;
    }

    return DISCORD_EVENT_MAIN_THREAD;
}
```

## Performance Considerations

- **discord_xxx_from_json()**: Easier to use but requires more memory and processing time since it parses the entire JSON structure.
- **jsmn-find**: More efficient for large payloads when you only need a few specific fields, but requires more manual code.

## Advanced Usage: Worker Threads

For CPU-intensive tasks, you can use worker threads to avoid blocking the main thread:

```c
enum discord_event_scheduler scheduler(struct discord *client,
                                      const char data[],
                                      size_t length,
                                      enum discord_gateway_events event)
{
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        /* Check if this is a message that requires heavy processing */
        jsmnf_loader loader;
        jsmnf_table table[0x100];
        jsmnf_init(&loader);

        if (jsmnf_load(&loader, data, length, table, sizeof(table) / sizeof *table) >= 0) {
            const jsmnf_pair *content = jsmnf_find(loader.root, "content", strlen("content"));

            if (content) {
                char content_str[128];
                snprintf(content_str, sizeof(content_str), "%.*s",
                         content->v->end - content->v->start,
                         data + content->v->start);

                /* If the message needs heavy processing, use a worker thread */
                if (strstr(content_str, "analyze")) {
                    logmod_log(INFO, NULL, "Handling intensive task in worker thread");
                    return DISCORD_EVENT_WORKER_THREAD;
                }
            }
        }
    }

    return DISCORD_EVENT_MAIN_THREAD;
}
```

The scheduler provides a powerful way to customize Concord's event handling to fit your application's specific needs while maintaining high performance.
