/** @file types.h */

#ifndef CONCORD_TYPES_H
#define CONCORD_TYPES_H

#include <stddef.h>
#include <stdint.h>

/** @defgroup ConcordTypes Primitives
 *  @brief Commonly used datatypes
 *
 *  @note these datatypes are typedefs of C primitives,
 *          its purpose is to facilitate identification
 *          and "intent of use".
 *  @{ */

/**
 * @brief Unix time in milliseconds
 *
 * Commonly used for fields that may store timestamps
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

/** @brief Generic sized buffer */
struct ccord_szbuf {
    /** the buffer's start */
    char *start;
    /** the buffer's size in bytes */
    size_t size;
};

/** @brief Read-only generic sized buffer */
struct ccord_szbuf_readonly {
    /** the buffer's start */
    const char *start;
    /** the buffer's size in bytes */
    size_t size;
};

/** @brief Reusable generic sized buffer */
struct ccord_szbuf_reusable {
    /** the buffer's start */
    char *start;
    /** the buffer's relative size in bytes */
    size_t size;
    /** the buffer's real size in bytes */
    size_t realsize;
};

/** @} ConcordTypes */

#endif /* CONCORD_TYPES_H */
