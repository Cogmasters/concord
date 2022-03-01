#include <curl/curl.h>

#include "error.h"
#include "work.h"

static int once;

CCORDcode
ccord_global_init()
{
    if (once) return CCORD_GLOBAL_INIT;

    if (0 != curl_global_init(CURL_GLOBAL_DEFAULT)) {
        fprintf(stderr, "Couldn't start libcurl's globals\n");
        return CCORD_GLOBAL_INIT;
    }
    if (work_global_init()) {
        fprintf(stderr, "Attempt duplicate global initialization\n");
        return CCORD_GLOBAL_INIT;
    }

    once = 1;

    return CCORD_OK;
}

void
ccord_global_cleanup()
{
    curl_global_cleanup();
    work_global_cleanup();
    once = 0;
}
