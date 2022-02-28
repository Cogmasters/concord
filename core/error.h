/** @file error.h */

#ifndef CONCORD_ERROR_H
#define CONCORD_ERROR_H

/** @defgroup ConcordError
 *  @brief Concord error handling
 *  @{ */

/** the error code datatype */
typedef int CCORDcode;
/** request was a success */
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

/** @} ConcordError */

#endif /* CONCORD_ERROR_H */
