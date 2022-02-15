/** @file common.h */

#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @defgroup ConcordTypes
 *  @brief Commonly used datatypes across various APIs
 *
 *  @note these datatypes are typedefs of C primitives,
 *          its purpose is to facilitate identification
 *          and "intent of use".
 *  @{ */

/**
 * @brief Unix time in milliseconds
 */
typedef uint64_t u64unix_ms;
/**
 * @brief Snowflake datatype
 *
 * Used in APIs such as Twitter and Discord for their unique IDs
 */
typedef uint64_t u64snowflake;

/**
 * @brief Bitmask primitive
 *
 * Used for fields that may store values of, or perform bitwise operations
 */
typedef uint64_t u64bitmask;

/**
 * @brief Raw JSON string
 *
 * Used for fields that have dynamic or unreliable types. A string made out of
 *        `json_char` should be used to keep a raw JSON, which can then be
 * parsed with the assistance of a JSON library.
 */
typedef char json_char;

/** @} ConcordTypes */

/** @defgroup ConcordCodes
 *  @brief Concord error values
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
/** @} ConcordCodes */

/** @defgroup ConcordLimits
 *  @brief Limits discovered across the web
 *  @{ */
#define CCORD_LIMITS_SHA256 1024 + 1
#define CCORD_LIMITS_LOCALE 16 + 1
#define CCORD_LIMITS_EMAIL  254 + 1
#define CCORD_LIMITS_REGION 16 + 1
/** @} ConcordLimits */

/**
 * @brief Get container `type` from a field `ptr`
 *
 * @param ptr the field contained in `type`
 * @param type the container datatype
 * @param path the path to the field from the container POV
 */
#define CONTAINEROF(ptr, type, path)                                          \
    ((type *)((char *)(ptr)-offsetof(type, path)))

/**
 * @brief log and return `code` if `expect` condition is false
 *
 * @param expect the expected outcome
 * @param client the discord client
 * @param error return CCORDcode error
 * @param reason for return
 */
#define CCORD_EXPECT(client, expect, code, reason)                            \
    do {                                                                      \
        if (!(expect)) {                                                      \
            logconf_error(&(client)->conf, "Expected: " #expect ": " reason); \
            return code;                                                      \
        }                                                                     \
    } while (0)

/**
 * @brief Return a generic meaning for CCORDcode
 *
 * @param code the CCORDcode to be explained
 * @return a string containing the code meaning
 */
const char *ccord_strerror(CCORDcode code);

/**
 * @brief Initialize global shared-resources not API-specific
 *
 * @return CCORD_OK on success, CCORD_GLOBAL_INIT on error
 */
CCORDcode ccord_global_init();

/** @brief Cleanup global shared-resources */
void ccord_global_cleanup();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COMMON_H */
