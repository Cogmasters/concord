/** @file common.h */

#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @defgroup OrcaTypes
 *  @brief Commonly used datatypes across various APIs
 *
 *  @note these datatypes are typedefs of C primitives,
 *          its purpose is to facilitate identification
 *          and "intent of use".
 *  @{ */

/**
 * @brief Unix time in milliseconds
 */
typedef uint64_t u64_unix_ms_t;
/**
 * @brief Snowflake datatype
 *
 * Used in APIs such as Twitter and Discord for their unique IDs
 */
typedef uint64_t u64_snowflake_t;

/**
 * @brief Bitmask primitive
 *
 * Used for fields that may store be used to store values of, or perform
 *        bitwise operations
 */
typedef uint64_t u64_bitmask_t;

/**
 * @brief Raw JSON string
 *
 * Used for fields that have dynamic or unreliable types. A string made out of
 *        `json_char_t` should be used to keep a raw JSON, which can then be
 * parsed with the assistance of a JSON library.
 */
typedef char json_char_t;

/** @} OrcaTypes */

/** @defgroup OrcaCodes
 *  @brief Orca error values
 *  @{ */
/** the error code datatype */
typedef int ORCAcode;
/** request was a success */
#define ORCA_OK 0
/** request wasn't succesful */
#define ORCA_HTTP_CODE -1
/** no response came through from curl */
#define ORCA_CURL_NO_RESPONSE -2
/** received a non-standard http code */
#define ORCA_UNUSUAL_HTTP_CODE -3
/** bad value for parameter */
#define ORCA_BAD_PARAMETER -4
/** internal failure when encoding or decoding JSON */
#define ORCA_BAD_JSON -5
/** curl's easy handle internal error */
#define ORCA_CURLE_INTERNAL -6
/** curl's multi handle internal error */
#define ORCA_CURLM_INTERNAL -7
/** attempt to initialize globals more than once */
#define ORCA_GLOBAL_INIT -8
/** @} OrcaCodes */

/** @defgroup OrcaLimits
 *  @brief Limits discovered across the web
 *  @{ */
#define ORCA_LIMITS_SHA256 1024 + 1
#define ORCA_LIMITS_LOCALE 16 + 1
#define ORCA_LIMITS_EMAIL  254 + 1
#define ORCA_LIMITS_REGION 16 + 1
/** @} OrcaLimits */

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
 * @param error return ORCAcode error
 * @param ... optional reason
 */
#define ORCA_EXPECT(client, expect, code, ...)                                \
  do {                                                                        \
    if (!(expect)) {                                                          \
      logconf_error(&(client)->conf, "Expected: " #expect ": " __VA_ARGS__);  \
      return code;                                                            \
    }                                                                         \
  } while (0)

/**
 * @brief Return a generic meaning for ORCAcode
 *
 * @param code the ORCAcode to be explained
 * @return a string containing the code meaning
 */
const char *orca_strerror(ORCAcode code);

/**
 * @brief Initialize global shared-resources not API-specific
 *
 * @return ORCA_OK on success, ORCA_GLOBAL_INIT on error
 */
ORCAcode orca_global_init();

/** @brief Cleanup global shared-resources */
void orca_global_cleanup();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COMMON_H */
