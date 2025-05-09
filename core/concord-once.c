#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "concord-error.h"
#include "concord-once.h"
#define LOGMOD_FALLBACK_APPLICATION_ID "CORE"
#define LOGMOD_FALLBACK_CONTEXT_ID     "ONCE"
#define LOGMOD_STATIC
#include "logmod.h"

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

struct ccord_init_cb_node {
    ccord_once_cb callback;
    int flags;
    struct ccord_init_cb_node *next;
};

static struct ccord_init_cb_node *init_cb_list = NULL;

CCORDcode
ccord_once_set_callback(ccord_once_cb callback, long flags)
{
    if (!callback) {
        logmod_log(ERROR, NULL, "Callback function is NULL");
        return CCORD_BAD_PARAMETER;
    }

    struct ccord_init_cb_node *new_node = malloc(sizeof(*new_node));
    if (!new_node) {
        logmod_log(ERROR, NULL, "Memory allocation failed for callback node");
        return CCORD_OUT_OF_MEMORY;
    }

    new_node->callback = callback;
    new_node->flags = flags;
    new_node->next = NULL;

    pthread_mutex_lock(&g_lock);
    /* Add to the end of the list to maintain registration order */
    if (!init_cb_list) {
        init_cb_list = new_node;
    }
    else {
        struct ccord_init_cb_node *current = init_cb_list;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    pthread_mutex_unlock(&g_lock);

    return CCORD_OK;
}

static void _ccord_once_cleanup(void);

CCORDcode
ccord_once(_Bool *const once)
{
    if (!once) {
        logmod_log(ERROR, NULL, "Expected static flag is NULL");
        return CCORD_BAD_PARAMETER;
    }
    if (*once) {
        logmod_log(
            WARN, NULL,
            "ccord_once() with flag %p already initialized, skipping ...",
            (void *)once);
        return CCORD_OK;
    }

    pthread_mutex_lock(&g_lock);
    struct ccord_init_cb_node *current = init_cb_list;
    CCORDcode code;
    while (current) {
        if ((code = current->callback(current->flags)) != CCORD_OK) {
            logmod_log(ERROR, NULL,
                       "User initialization callback failed: %s (code %d)",
                       ccord_strerror(code), code);
            _ccord_once_cleanup();
            goto _skip;
        }
        current = current->next;
    }
    *once = 1;
_skip:
    pthread_mutex_unlock(&g_lock);
    return code;
}

static void
_ccord_once_cleanup(void)
{
    struct ccord_init_cb_node *current = init_cb_list;
    while (current) {
        struct ccord_init_cb_node *next = current->next;
        free(current);
        current = next;
    }
    init_cb_list = NULL;
}

void
ccord_once_cleanup(void)
{
    pthread_mutex_lock(&g_lock);
    _ccord_once_cleanup();
    pthread_mutex_unlock(&g_lock);
}
