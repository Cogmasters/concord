/** @file error.h */

#ifndef CONCORD_ERROR_H
#define CONCORD_ERROR_H

/** @defgroup ConcordError Error handling
 *  @brief Concord error codes and meaning
 *  @{ */

/* XXX: As new values are added, discord_strerror() should be updated
 *      accordingly! */
typedef enum CCORDcode {
    /** most likely a bug in the library, please report it */
    CCORD_INTERNAL_ERROR = -200,
    /** couldn't encode format */
    CCORD_BAD_ENCODE = -101,
    /** couldn't decode format */
    CCORD_BAD_DECODE = -100,
    /** out of memory, something really bad happened! */
    CCORD_OUT_OF_MEMORY = -60,
    /** check strerror() for more information */
    CCORD_ERRNO = -50,
    /** curl has been compiled without the --enable-websockets flag */
    CCORD_CURL_WEBSOCKETS_MISSING = -14,
    /** curl need to be updated to 8.7.1 or greater */
    CCORD_CURL_OUTDATED_VERSION = -13,
    /** failure when creating request's payload */
    CCORD_MALFORMED_PAYLOAD = -12,
    /** couldn't enqueue worker thread (queue is full) */
    CCORD_FULL_WORKER = -11,
    /** couldn't perform action because resource is unavailable */
    CCORD_RESOURCE_UNAVAILABLE = -10,
    /** @deprecated use @ref CCORD_RESOURCE_UNAVAILABLE instead */
    CCORD_UNAVAILABLE = CCORD_RESOURCE_UNAVAILABLE,
    /** couldn't cleanup resource automatically due to being claimed */
    CCORD_RESOURCE_OWNERSHIP = -9,
    /** @deprecated use @ref CCORD_RESOURCE_OWNERSHIP instead */
    CCORD_OWNERSHIP = CCORD_RESOURCE_OWNERSHIP,
    /** attempt to initialize globals more than once */
    CCORD_GLOBAL_INIT = -8,
    /** curl's multi handle internal error */
    CCORD_CURLM_INTERNAL = -7,
    /** curl's easy handle internal error */
    CCORD_CURLE_INTERNAL = -6,
    /** internal failure when encoding or decoding JSON */
    CCORD_BAD_JSON = -5,
    /** bad value for parameter */
    CCORD_BAD_PARAMETER = -4,
    /** received a non-standard http code */
    CCORD_UNUSUAL_HTTP_CODE = -3,
    /** no response came through from curl */
    CCORD_CURL_NO_RESPONSE = -2,
    /** request wasn't succesful */
    CCORD_HTTP_CODE = -1,
    /** action was a success */
    CCORD_OK = 0,
    /**
     * action is pending (ex: request has been enqueued and will be performed
     *      later)
     */
    CCORD_PENDING,
    /** received a JSON error message */
    CCORD_DISCORD_JSON_CODE = 100,
    /** bad authentication token */
    CCORD_DISCORD_BAD_AUTH,
    /** being ratelimited */
    CCORD_DISCORD_RATELIMIT,
    /** couldn't establish connection to Discord */
    CCORD_DISCORD_CONNECTION,
} CCORDcode;

/** @} ConcordError */

#endif /* CONCORD_ERROR_H */
