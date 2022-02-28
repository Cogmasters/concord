#include <stdint.h>
#include <curl/curl.h>

#include "common.h"
#include "work.h"
#include "log.h"

static _Bool once;

const char *
ccord_strerror(CCORDcode code)
{
    switch (code) {
    case CCORD_OK:
        return "Success: The request was a success";
    case CCORD_HTTP_CODE:
        return "Failure: The request was a failure";
    case CCORD_UNUSUAL_HTTP_CODE:
        return "Failure: The request was a failure";
    case CCORD_BAD_PARAMETER:
        return "Failure: Bad value for parameter";
    case CCORD_BAD_JSON:
        return "Failure: Internal failure when encoding or decoding JSON";
    case CCORD_CURLE_INTERNAL:
    case CCORD_CURLM_INTERNAL:
        return "Failure: Libcurl's internal error";
    default:
        return "Unknown: Code received doesn't match any description";
    }
}

CCORDcode
ccord_global_init()
{
    if (once) return CCORD_GLOBAL_INIT;

    if (0 != curl_global_init(CURL_GLOBAL_DEFAULT)) {
        log_warn("Couldn't start libcurl's globals");
        return CCORD_GLOBAL_INIT;
    }
    if (work_global_init()) {
        log_warn("Attempt duplicate global initialization");
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

CCORDcode
ccord_return_error(const char error[], CCORDcode code)
{
    log_info("(%d) %s", code, error);
    return code;
}
