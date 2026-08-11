#include "concord-error.h"

#define CASE_RETURN_STR(event)                                                \
    case event:                                                               \
        return #event
const char *
ccord_code_as_string(CCORDcode code)
{
    switch (code) {
        CASE_RETURN_STR(CCORD_OK);
        CASE_RETURN_STR(CCORD_HTTP_CODE);
        CASE_RETURN_STR(CCORD_CURL_NO_RESPONSE);
        CASE_RETURN_STR(CCORD_UNUSUAL_HTTP_CODE);
        CASE_RETURN_STR(CCORD_BAD_PARAMETER);
        CASE_RETURN_STR(CCORD_BAD_JSON);
        CASE_RETURN_STR(CCORD_CURLE_INTERNAL);
        CASE_RETURN_STR(CCORD_CURLM_INTERNAL);
        CASE_RETURN_STR(CCORD_GLOBAL_INIT);
        CASE_RETURN_STR(CCORD_RESOURCE_OWNERSHIP);
        CASE_RETURN_STR(CCORD_RESOURCE_UNAVAILABLE);
        CASE_RETURN_STR(CCORD_FULL_WORKER);
        CASE_RETURN_STR(CCORD_MALFORMED_PAYLOAD);
        CASE_RETURN_STR(CCORD_CURL_WEBSOCKETS_MISSING);
        CASE_RETURN_STR(CCORD_CURL_OUTDATED_VERSION);
        CASE_RETURN_STR(CCORD_INTERNAL_ERROR);
        CASE_RETURN_STR(CCORD_BAD_ENCODE);
        CASE_RETURN_STR(CCORD_BAD_DECODE);
        CASE_RETURN_STR(CCORD_OUT_OF_MEMORY);
        CASE_RETURN_STR(CCORD_ERRNO);
    default:
        return "Unknown: Code received doesn't match any description";
    }
}
#undef CASE_RETURN_STR

const char *
ccord_strerror(CCORDcode code)
{
    switch (code) {
    case CCORD_OK:
        return "Success: The request was a success";
    case CCORD_HTTP_CODE:
        return "Failure: The request was a failure";
    case CCORD_CURL_NO_RESPONSE:
        return "Failure: No response came through from libcurl";
    case CCORD_UNUSUAL_HTTP_CODE:
        return "Failure: The request was a failure";
    case CCORD_BAD_PARAMETER:
        return "Failure: Bad value for parameter";
    case CCORD_BAD_JSON:
        return "Failure: Internal failure when encoding or decoding JSON";
    case CCORD_CURLE_INTERNAL:
        return "Failure: Libcurl's internal error (CURLE)";
    case CCORD_CURLM_INTERNAL:
        return "Failure: Libcurl's internal error (CURLM)";
    case CCORD_GLOBAL_INIT:
        return "Failure: Attempt to initialize globals more than once";
    case CCORD_RESOURCE_OWNERSHIP:
        return "Failure: Claimed resource can't be cleaned up automatically";
    case CCORD_RESOURCE_UNAVAILABLE:
        return "Failure: Can't perform action on unavailable resource";
    case CCORD_FULL_WORKER:
        return "Failure: Couldn't enqueue worker thread (queue is full)";
    case CCORD_MALFORMED_PAYLOAD:
        return "Failure: Couldn't create request payload";
    case CCORD_CURL_WEBSOCKETS_MISSING:
        return "Failure: Libcurl has been compiled without the "
               "--enable-websockets flag";
    case CCORD_CURL_OUTDATED_VERSION:
        return "Failure: Libcurl need to be updated to 8.7.1 or greater";
    case CCORD_INTERNAL_ERROR:
        return "Failure: Most likely a bug in the library, please report it";
    case CCORD_BAD_ENCODE:
        return "Failure: Couldn't encode format";
    case CCORD_BAD_DECODE:
        return "Failure: Couldn't decode format";
    case CCORD_OUT_OF_MEMORY:
        return "Failure: Out of memory, something really bad happened!";
    case CCORD_ERRNO:
        return "Failure: Check strerror() for more information";
    default:
        return "Unknown: Code received doesn't match any description";
    }
}
