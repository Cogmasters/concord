#include <signal.h>
#include <curl/curl.h>

#include "error.h"
#include "work.h"

/* if set to 1 then client(s) will be disconnected */
int ccord_has_sigint = 0;

static int once;

/* shutdown gracefully on SIGINT received */
static void
sigint_handler(int signum)
{
  (void)signum;
  fputs("\nSIGINT: Disconnecting running concord client(s) ...\n", stderr);
  ccord_has_sigint = 1;
}

CCORDcode
ccord_global_init()
{
    if (once) {
        return CCORD_GLOBAL_INIT;
    }
    else {
#ifdef SIGINTCATCH
        __sighandler_t prev = signal(SIGINT, &sigint_handler);
        if (prev != SIG_DFL && prev != sigint_handler)
            signal(SIGINT, prev);
#endif
        if (0 != curl_global_init(CURL_GLOBAL_DEFAULT)) {
            fputs("Couldn't start libcurl's globals\n", stderr);
            return CCORD_GLOBAL_INIT;
        }
        if (work_global_init()) {
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
    work_global_cleanup();
    once = 0;
}
