/**
 * @file discord-templates.h
 * @author Cogmasters
 * @brief File containing datatypes generated via macro templates
 */

#ifndef DISCORD_TEMPLATES_H
#define DISCORD_TEMPLATES_H

#define DISCORD_T_DONE(type)                                                  \
    typedef void (*discord_done_##type)(struct discord * client, void *data,  \
                                        const struct discord_##type *ret)

#define DISCORD_T_DONE_LIST(type)                                             \
    typedef void (*discord_done_##type##s)(struct discord * client,           \
                                           void *data,                        \
                                           const struct discord_##type **ret)

#define DISCORD_T_ATTR_FIELDS                                                 \
    discord_fail fail;                                                        \
    void *data;                                                               \
    void (*done_cleanup)(void *data);                                         \
    void (*fail_cleanup)(void *data);                                         \
    bool *high_p

#define DISCORD_T_ATTR(type)                                                  \
    struct discord_attr_##type {                                              \
        discord_done_##type done;                                             \
        DISCORD_T_ATTR_FIELDS;                                                \
    }

#define DISCORD_T_ATTR_LIST(type)                                             \
    struct discord_attr_##type##s {                                           \
        discord_done_##type##s done;                                          \
        DISCORD_T_ATTR_FIELDS;                                                \
    }

#define DISCORD_T_RETURN(type)                                                \
    DISCORD_T_DONE(type);                                                     \
    DISCORD_T_ATTR(type)

#define DISCORD_T_RETURN_LIST(type)                                           \
    DISCORD_T_DONE_LIST(type);                                                \
    DISCORD_T_ATTR_LIST(type)

/** @brief Triggers on a successful request */
typedef void (*discord_done)(struct discord *client, void *data);

/** @brief Triggers on a successful request */
typedef void (*discord_done_generic)(struct discord *client,
                                     void *data,
                                     const void *ret);

/** @brief Triggers on a failed request */
typedef void (*discord_fail)(struct discord *client,
                             CCORDcode code,
                             void *data);
struct discord_attr {
    discord_done done;
    DISCORD_T_ATTR_FIELDS;
};

struct discord_attr_generic {
    discord_done_generic done;
    DISCORD_T_ATTR_FIELDS;
};

DISCORD_T_RETURN(application_command);
DISCORD_T_RETURN_LIST(application_command);
DISCORD_T_RETURN(application_command_permissions);
DISCORD_T_RETURN_LIST(application_command_permissions);
DISCORD_T_RETURN_LIST(guild_application_command_permissions);
DISCORD_T_RETURN(interaction_response);

DISCORD_T_RETURN(audit_log);

DISCORD_T_RETURN(channel);
DISCORD_T_RETURN_LIST(channel);
DISCORD_T_RETURN(message);
DISCORD_T_RETURN_LIST(message);

DISCORD_T_RETURN(user);
DISCORD_T_RETURN_LIST(user);

DISCORD_T_RETURN(invite);
DISCORD_T_RETURN_LIST(invite);

DISCORD_T_RETURN_LIST(thread_member);
DISCORD_T_RETURN(thread_response_body);

DISCORD_T_RETURN(emoji);
DISCORD_T_RETURN_LIST(emoji);

DISCORD_T_RETURN(guild);
DISCORD_T_RETURN_LIST(guild);
DISCORD_T_RETURN(guild_preview);
DISCORD_T_RETURN(guild_member);
DISCORD_T_RETURN_LIST(guild_member);
DISCORD_T_RETURN(ban);
DISCORD_T_RETURN_LIST(ban);
DISCORD_T_RETURN(role);
DISCORD_T_RETURN_LIST(role);
DISCORD_T_RETURN(welcome_screen);

DISCORD_T_RETURN(guild_template);

DISCORD_T_RETURN_LIST(connection);
DISCORD_T_RETURN_LIST(voice_region);

DISCORD_T_RETURN(webhook);
DISCORD_T_RETURN_LIST(webhook);

#undef DISCORD_T_DONE
#undef DISCORD_T_DONE_LIST
#undef DISCORD_T_ATTR_FIELDS
#undef DISCORD_T_ATTR
#undef DISCORD_T_ATTR_LIST
#undef DISCORD_T_RETURN
#undef DISCORD_T_RETURN_LIST

#endif /* DISCORD_TEMPLATES_H */
