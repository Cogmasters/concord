#include <signal.h>
#include <curl/curl.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include <error.h>
#include "discord-worker.h"
#include "mem.h"
#include "concord-once.h"

static pthread_mutex_t shutdown_lock = PTHREAD_MUTEX_INITIALIZER;

/* if set to 1 then client(s) will be disconnected */
int ccord_should_shutdown = 0;

static int once;

void
ccord_shutdown_async(void)
{
    pthread_mutex_lock(&shutdown_lock);
    ccord_should_shutdown = 1;
    pthread_mutex_unlock(&shutdown_lock);
}

int
ccord_shutting_down(void)
{
    int retval;
    pthread_mutex_lock(&shutdown_lock);
    retval = ccord_should_shutdown;
    pthread_mutex_unlock(&shutdown_lock);
    return retval;
}

#ifdef CCORD_SIGINTCATCH
/* shutdown gracefully on SIGINT received */
static void
_ccord_sigint_handler(int signum)
{
    (void)signum;
    fputs("\nSIGINT: Disconnecting running concord client(s) ...\n", stderr);
    pthread_mutex_lock(&shutdown_lock);
    ccord_should_shutdown = 1;
    pthread_mutex_unlock(&shutdown_lock);
}
#endif /* CCORD_SIGINTCATCH */

/* system memory functions */


CCORDcode
ccord_global_init_memory(malloc_fn_t malloc_fn,
                         calloc_fn_t calloc_fn,
                         realloc_fn_t realloc_fn,
                         free_fn_t free_fn,
                         strdup_fn_t strdup_fn)
{
    if (once) {
        return CCORD_GLOBAL_INIT;
    }
    else {
#ifdef CCORD_SIGINTCATCH
        signal(SIGINT, &_ccord_sigint_handler);
#endif

        mem_init(malloc_fn, calloc_fn, realloc_fn, free_fn, strdup_fn);

        const CURLcode res =
            curl_global_init_mem(CURL_GLOBAL_DEFAULT, malloc_fn, free_fn,
                                 realloc_fn, strdup_fn, calloc_fn);

        if (0 != res) {
            fputs("Couldn't start libcurl's globals\n", stderr);
            return CCORD_GLOBAL_INIT;
        }
        if (discord_worker_global_init()) {
            fputs("Attempt duplicate global initialization\n", stderr);
            return CCORD_GLOBAL_INIT;
        }
        once = 1;
    }
    return CCORD_OK;
}

static void *
malloc_fn_system(size_t length)
{
    void *const ptr = malloc(length);
    if (!ptr) {
        fprintf(stderr, "Out of memory when allocating %zu bytes, aborting",
                length);
        abort();
    }
    return ptr;
}

static void *
calloc_fn_system(size_t nmemb, size_t length)
{
    void *const ptr = calloc(nmemb, length);
    if (!ptr) {
        fprintf(
            stderr,
            "Out of memory when allocating %zu items of size %zu, aborting",
            nmemb, length);
        abort();
    }
    return ptr;
}

static void *
realloc_fn_system(void *old_ptr, size_t length)
{
    void *const ptr = realloc(old_ptr, length);
    if (!ptr) {
        fprintf(stderr,
                "Out of memory when reallocating %" PRIxPTR
                " to %zu bytes, aborting",
                (uintptr_t)old_ptr, length);
        abort();
    }
    return ptr;
}

static void
free_fn_system(void *ptr)
{
    if (!ptr) return;
    free(ptr);
}

static char *
strdup_fn_system(const char *str)
{
    char *const ptr = strdup(str);
    if (!ptr) {
        fprintf(stderr,
                "Out of memory when duplicating string %" PRIxPTR
                " of length %zu",
                (uintptr_t)str, strlen(str));
        abort();
    }
    return ptr;
}

CCORDcode
ccord_global_init(void)
{
    return ccord_global_init_memory(malloc_fn_system, &calloc_fn_system,
                                    &realloc_fn_system, &free_fn_system,
                                    &strdup_fn_system);
}

void
ccord_global_cleanup()
{
    curl_global_cleanup();
    discord_worker_global_cleanup();
    once = 0;
    pthread_mutex_lock(&shutdown_lock);
    ccord_should_shutdown = 0;
    pthread_mutex_unlock(&shutdown_lock);
}
