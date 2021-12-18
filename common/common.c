#include <stdint.h>
#include <curl/curl.h>

#include "common.h"
#include "work.h"
#include "log.h"

static _Bool once;

const char *
orca_strerror(ORCAcode code)
{
  switch (code) {
  case ORCA_OK:
    return "Success: The request was a success";
  case ORCA_HTTP_CODE:
    return "Failure: The request was a failure";
  case ORCA_UNUSUAL_HTTP_CODE:
    return "Failure: The request was a failure";
  case ORCA_BAD_PARAMETER:
    return "Failure: Bad value for parameter";
  case ORCA_BAD_JSON:
    return "Failure: Internal failure when encoding or decoding JSON";
  case ORCA_CURLE_INTERNAL:
  case ORCA_CURLM_INTERNAL:
    return "Failure: Libcurl's internal error";
  default:
    return "Unknown: Code received doesn't match any description";
  }
}

ORCAcode
orca_global_init()
{
  if (once) return ORCA_GLOBAL_INIT;

  if (0 != curl_global_init(CURL_GLOBAL_DEFAULT)) {
    log_warn("Couldn't start libcurl's globals");
    return ORCA_GLOBAL_INIT;
  }
  if (work_global_init()) {
    log_warn("Attempt duplicate global initialization");
    return ORCA_GLOBAL_INIT;
  }

  once = 1;

  return ORCA_OK;
}

void
orca_global_cleanup()
{
  curl_global_cleanup();
  work_global_cleanup();
  once = 0;
}
