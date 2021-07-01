#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef uint64_t u64_unix_ms_t; ///< unix time in ms
typedef uint64_t u64_snowflake_t; ///< snowflake datatype

/**
 * @todo add more error codes and a strerror()
 */
typedef int ORCAcode;
#define ORCA_OK                  0
#define ORCA_NO_RESPONSE        -1
#define ORCA_UNUSUAL_HTTP_CODE  -2
#define ORCA_MISSING_PARAMETER  -3
#define ORCA_BAD_PARAMETER      -4
#define ORCA_BAD_JSON           -5

/* Size limits discovered from the web */
#define MAX_SHA256_LEN        1024 + 1
#define MAX_LOCALE_LEN        16 + 1
#define MAX_EMAIL_LEN         254 + 1
#define MAX_REGION_LEN        16 + 1

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TYPES_H
