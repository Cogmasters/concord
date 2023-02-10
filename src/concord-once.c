#include <signal.h>
#include <curl/curl.h>
#include <pthread.h>

#include "error.h"
#include "discord-worker.h"

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

CCORDcode
ccord_global_init()
{
    if (once) {
        return CCORD_GLOBAL_INIT;
    }
    else {
#ifdef CCORD_SIGINTCATCH
        signal(SIGINT, &_ccord_sigint_handler);
#endif
        if (0 != curl_global_init(CURL_GLOBAL_DEFAULT)) {
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
