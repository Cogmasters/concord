/** @file error.h */

#ifndef CONCORD_ERROR_H
#define CONCORD_ERROR_H

/** @defgroup ConcordError Error handling
 *  @brief Concord error codes and meaning
 *  @{ */

/** @brief Concord error codes */
typedef int CCORDcode;

/* XXX: As new values are added, ccord_strerror() and ccord_code_as_string()
 *       should be updated accordingly! */
/** @defgroup CoreError Core error codes
 *  @brief These codes are used by the core library and should be used by all
 *      modules
 * @
 *  @{ */

/** most likely a bug in the library, please report it */
#define CCORD_INTERNAL_ERROR -200
/** couldn't encode format */
#define CCORD_BAD_ENCODE -101
/** couldn't decode format */
#define CCORD_BAD_DECODE -100
/** out of memory, something really bad happened! */
#define CCORD_OUT_OF_MEMORY -60
/** check strerror() for more information */
#define CCORD_ERRNO -50
/** curl has been compiled without the --enable-websockets flag */
#define CCORD_CURL_WEBSOCKETS_MISSING -14
/** curl need to be updated to 8.7.1 or greater */
#define CCORD_CURL_OUTDATED_VERSION -13
/** failure when creating request's payload */
#define CCORD_MALFORMED_PAYLOAD -12
/** couldn't enqueue worker thread (queue is full) */
#define CCORD_FULL_WORKER -11
/** couldn't perform action because resource is unavailable */
#define CCORD_RESOURCE_UNAVAILABLE -10
/** couldn't cleanup resource automatically due to being claimed */
#define CCORD_RESOURCE_OWNERSHIP -9
/** attempt to initialize globals more than once */
#define CCORD_GLOBAL_INIT -8
/** curl's multi handle internal error */
#define CCORD_CURLM_INTERNAL -7
/** curl's easy handle internal error */
#define CCORD_CURLE_INTERNAL -6
/** internal failure when encoding or decoding JSON */
#define CCORD_BAD_JSON -5
/** bad value for parameter */
#define CCORD_BAD_PARAMETER -4
/** received a non-standard http code */
#define CCORD_UNUSUAL_HTTP_CODE -3
/** no response came through from curl */
#define CCORD_CURL_NO_RESPONSE -2
/** request wasn't succesful */
#define CCORD_HTTP_CODE -1
/** action was a success */
#define CCORD_OK 0

const char *ccord_code_as_string(CCORDcode code);
const char *ccord_strerror(CCORDcode code);

/** @} CoreError */

/** @} ConcordError */

#endif /* CONCORD_ERROR_H */
