/**
 * @file types.h
 */

#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** @defgroup OrcaTypes
 *  @brief Commonly used datatypes with various APIs
 *  @{ */
typedef uint64_t u64_unix_ms_t;   ///< unix time in ms
typedef uint64_t u64_snowflake_t; ///< snowflake datatype
typedef char json_char_t; ///< raw json string
/** @} OrcaTypes */

/** @defgroup OrcaCodes
 *  @brief Error code returned by Orca REST functions
 *  @todo add origins links
 *  @{ */
typedef int ORCAcode;             ///< the error code datatype
#define ORCA_OK                 0 ///< request was a success
#define ORCA_HTTP_CODE         -1 ///< request wasn't succesful (2xx)
#define ORCA_NO_RESPONSE       -2 ///< failure connecting to API's url
#define ORCA_UNUSUAL_HTTP_CODE -3 ///< received a non-standard http code
#define ORCA_MISSING_PARAMETER -4 ///< missing a mandatory function parameter
#define ORCA_BAD_PARAMETER     -5 ///< unexpected value for parameter
#define ORCA_BAD_JSON          -6 ///< internal failure when encoding or decoding JSON
/** @} OrcaCodes */

/** @defgroup OrcaDiscordCodes
 *  @see discord_strerror()
 *  @{ */
#define ORCA_DISCORD_JSON_CODE  1 ///< Received a JSON error message
#define ORCA_DISCORD_BAD_AUTH   2 ///< Bad authentication token
#define ORCA_DISCORD_RATELIMIT  3 ///< Being ratelimited
#define ORCA_DISCORD_CONNECTION 4 ///< Couldn't establish connection to Discord
/** @} OrcaDiscordCodes */

/* Github error codes */
#define ORCA_GITHUB_JSON        1
#define ORCA_GITHUB_BAD_AUTH    2
#define ORCA_GITHUB_NOT_STARRED 404


/** @defgroup OrcaLimits
 *  @brief Limits discovered across the web
 *  @todo add reference links
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
const char* orca_strerror(ORCAcode code);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TYPES_H
