#include <stdint.h>
#include "types.h"

const char *
orca_strerror(ORCAcode code)
{
  switch (code) {
  case ORCA_OK: return "Success: The request was a success";
  case ORCA_HTTP_CODE: return "Failure: The request was a failure";
  case ORCA_UNUSUAL_HTTP_CODE: return "Failure: The request was a failure";
  case ORCA_MISSING_PARAMETER:
    return "Failure: Missing a mandatory function parameter";
  case ORCA_BAD_PARAMETER: return "Failure: Unexpected value for parameter";
  case ORCA_BAD_JSON:
    return "Failure: Internal failure when encoding or decoding JSON";
  case ORCA_CURLE_INTERNAL:
  case ORCA_CURLM_INTERNAL: return "Failure: Libcurl's internal error";
  default: return "Unknown: Code received doesn't match any description";
  }
}
