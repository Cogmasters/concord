#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef uint64_t u64_unix_ms_t; ///< unix time in ms

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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TYPES_H
