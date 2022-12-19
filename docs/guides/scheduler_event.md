# The scheduler event

The scheduler is one way to get the raw JSON from Discord's WebSocket payloads. This feature gives the developer fine-grain control over how an event behaves such that events can be ignored or spawn a worker thread. Additionally, the JSON key can be manually parsed to achieve the best performance.

## How to use it

To usage of the scheduler is easy, take a look at the example below of printing the raw JSON from Discord of the MESSAGE_CREATE event and making Concord ignore the event:

```c
enum discord_event_scheduler scheduler(struct discord *client, const char data[], size_t length, enum discord_gateway_events event) {
    /* The "event" parameter is the parameter allows you to distinguish the events, and the data one is the JSON Discord sent. */
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        log_debug("Received event JSON: %s", data);
        /* Returning the "event ignore" enum, that says to Concord to ignore the event. */
        return DISCORD_EVENT_IGNORE;
    }
    /* Here we are "saying" to Concord to handle the rest of the received events. */
    return DISCORD_EVENT_MAIN_THREAD;
    /* The "length" parameter can be used to parse the JSON, you can use jsmnf, from müller, in case you want to parse separated fields, or you can use discord_xxx_from_json() functions, in case you want to parse the whole JSON. */
}
enum discord_event_scheduler scheduler(struct discord *client, const char data[], size_t length, enum discord_gateway_events event) {
    /* The "event" parameter is the parameter allows you to distinguish the events, and the data one is the JSON Discord sent. */
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        log_debug("Received event JSON: %s", data);
        /* Returning the "event ignore" enum, that says to Concord to ignore the event. */
        return DISCORD_EVENT_IGNORE;
    }
    /* Here we are "saying" to Concord to handle the rest of the received events. */
    return DISCORD_EVENT_MAIN_THREAD;
    /* The "length" parameter can be used to parse the JSON, you can use jsmnf, from müller, in case you want to parse separated fields, or you can use discord_xxx_from_json() functions, in case you want to parse the whole JSON. */
}

...

int main() {
    ...
    /* Be sure to include the callback */
    discord_set_event_scheduler(client, &scheduler);
    ...
}
```

And this is it, but don't forget to add `discord_set_event_scheduler(client, scheduler);` to your code, otherwise, Concord will not use the scheduler.

## How to parse the JSON (discord_xxx_from_json)

Scheduler also allows the use of `discord_xxx_from_json()` to convert the JSON into a struct where you can then produce the logic you need. Here, `xxx` implies a family of functions. In this case, the `xxx` in `discord_xxx_from_json` can be replaced with events like `message_create`.

Here is an example of using the Scheduler to ignore the `MESSAGE_CREATE` event and print out its JSON:

```c
enum discord_event_scheduler scheduler(struct discord *client, const char data[], size_t length, enum discord_gateway_events event) {
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        struct discord_message self;
        /* Parse the JSON and store the it in the "self" struct. */
        discord_message_from_json(data, length, &self);
        log_debug("Message content: %s", self.content);
        /* Free the struct. */
        discord_message_cleanup(&self);
        return DISCORD_EVENT_IGNORE;
    }
    return DISCORD_EVENT_MAIN_THREAD;
}
```

Mhm, that's easy! Now, if you want to parse a single JSON key, you should see the next section.

## How to parse the JSON (jsmnf)

This method trades simplicity for speed, but the returned structure does not have to be freed.

Note that the `jsmn-find` library, the one we are going to use, it's the same which Concord uses for parsing.

For example, a developer could parse message content from `message_create` with the following:

```c
enum discord_event_scheduler scheduler(struct discord *client, const char data[], size_t length, enum discord_gateway_events event) {
    if (event == DISCORD_EV_MESSAGE_CREATE) {
        jsmn_parser parser;
        jsmntok_t tokens[1024];

        /* Set base variables to the parser struct. */
        jsmn_init(&parser);
        /* Parses the JSON and store the tokens. */
        int r = jsmn_parse(&parser, data, length, tokens, sizeof(tokens));

        /* Check if the parsing was successful. */
        if (r < 0) {
            log_error("Failed to parse JSON.");
            return DISCORD_EVENT_IGNORE;
        }

        jsmnf_loader loader;
        jsmnf_pair pairs[1024];

        /* Set base variables of the loader struct. */
        jsmnf_init(&loader);
        /* Load jsmn-find with the tokens and the pairs. */
        r = jsmnf_load(&loader, data, tokens, parser.toknext, pairs, sizeof(pairs) / sizeof(*pairs));

        if (r < 0) {
            log_error("Failed to load jsmn-find.");
            return DISCORD_EVENT_IGNORE;
        }

        jsmnf_pair *content = jsmnf_find(pairs, data, "content", strlen("content"));
        if (!content) {
            log_error("Failed to find the \"content\" key.");
            return DISCORD_EVENT_IGNORE;
        }

        /* The maximum length of a content in Discord is 2000, so we will be used it */
        char contentStr[2000 + 1];
        snprintf(contentStr, sizeof(contentStr), "%.*s", (int)content->v.len, data + content->v.pos);

        log_debug("Message content: %s", contentStr);
        return DISCORD_EVENT_IGNORE;
    }
    return DISCORD_EVENT_MAIN_THREAD;
}
```

This will only parse the `content` key allowing you to build more features and systems.