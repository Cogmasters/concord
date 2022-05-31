/** @file error.h */

#ifndef CONCORD_ERROR_H
#define CONCORD_ERROR_H

/** @defgroup ConcordError Error handling
 *  @brief Concord error codes and meaning
 *  @{ */

/** the error code datatype */
typedef int CCORDcode;

/** action was a success */
#define CCORD_OK 0
/** request wasn't succesful */
#define CCORD_HTTP_CODE -1
/** no response came through from curl */
#define CCORD_CURL_NO_RESPONSE -2
/** received a non-standard http code */
#define CCORD_UNUSUAL_HTTP_CODE -3
/** bad value for parameter */
#define CCORD_BAD_PARAMETER -4
/** internal failure when encoding or decoding JSON */
#define CCORD_BAD_JSON -5
/** curl's easy handle internal error */
#define CCORD_CURLE_INTERNAL -6
/** curl's multi handle internal error */
#define CCORD_CURLM_INTERNAL -7
/** attempt to initialize globals more than once */
#define CCORD_GLOBAL_INIT -8
/** couldn't perform action because of resource's ownership issues */
#define CCORD_OWNERSHIP -9
/** couldn't perform action because resource is unavailable */
#define CCORD_UNAVAILABLE -10
/** couldn't enqueue worker thread (queue is full) */
#define CCORD_FULL_WORKER -11

/** @} ConcordError */

#endif /* CONCORD_ERROR_H */
