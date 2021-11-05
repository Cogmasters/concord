/**
 * @file types.h
 */

#ifndef TYPES_H
#define TYPES_H

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
 * @brief Raw JSON string
 *
 * Used for fields that have dynamic or unreliable types. A string made out of
 *        `json_char_t` should be used to keep a raw JSON, which can then be
 * parsed with the assistance of a JSON library.
 */
typedef char json_char_t;
/** @} OrcaTypes */

/** @defgroup OrcaCodes
 *  @brief Error code returned by Orca REST functions
 *  @{ */
/** the error code datatype */
typedef int ORCAcode;
/** request was a success */
#define ORCA_OK 0
/** request wasn't succesful */
#define ORCA_HTTP_CODE -1
/** failure connecting to API's url */
#define ORCA_NO_RESPONSE -2
/** received a non-standard http code */
#define ORCA_UNUSUAL_HTTP_CODE -3
/** missing a mandatory function parameter */
#define ORCA_MISSING_PARAMETER -4
/** unexpected value for parameter */
#define ORCA_BAD_PARAMETER -5
/** internal failure when encoding or decoding JSON */
#define ORCA_BAD_JSON -6
/** curl's easy handle internal error */
#define ORCA_CURLE_INTERNAL -7
/** curl's multi handle internal error */
#define ORCA_CURLM_INTERNAL -8
/** @} OrcaCodes */

/** @defgroup OrcaDiscordCodes
 *  @see discord_strerror()
 *  @{ */
/** Received a JSON error message */
#define ORCA_DISCORD_JSON_CODE 1
/** Bad authentication token */
#define ORCA_DISCORD_BAD_AUTH 2
/** Being ratelimited */
#define ORCA_DISCORD_RATELIMIT 3
/** Couldn't establish connection to Discord */
#define ORCA_DISCORD_CONNECTION 4
/** @} OrcaDiscordCodes */

/* Github error codes */
#define ORCA_GITHUB_JSON        1
#define ORCA_GITHUB_BAD_AUTH    2
#define ORCA_GITHUB_NOT_STARRED 404

/** @defgroup OrcaLimits
 *  @brief Limits discovered across the web
 *  @{ */
#define ORCA_LIMITS_SHA256 1024 + 1
#define ORCA_LIMITS_LOCALE 16 + 1
#define ORCA_LIMITS_EMAIL  254 + 1
#define ORCA_LIMITS_REGION 16 + 1
/** @} OrcaLimits */

/**
 * @brief Return a generic meaning for ORCAcode
 * @param code the ORCAcode to be explained
 * @return a string containing the code meaning
 */
const char *orca_strerror(ORCAcode code);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TYPES_H */
