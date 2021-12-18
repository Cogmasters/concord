#ifndef CEE_UTILS_H
#define CEE_UTILS_H

#include <stdint.h>

#include "debug.h"
#include "ntl.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Compare equality between two strings
 *
 * 1 if strings are equal, 0 otherwise
 * @param str1 first string
 * @param str2 second string
 */
#define STREQ(str1, str2) (0 == strcmp(str1, str2))
/**
 * @brief Compare equality between two strings up to n characters
 *
 * 1 if strings are equal, 0 otherwise
 * @param str1 first string
 * @param str2 second string
 * @param n length of characters to compare
 */
#define STRNEQ(str1, str2, n) (0 == strncmp(str1, str2, n))
/**
 * @brief Check if string pointer is an empty string
 *
 * @param str the string pointer to be checked
 */
#define IS_EMPTY_STRING(str) (!(str) || !*(str))
/**
 * @brief Return enumerator token as a string if there's a switch match
 *
 * @param opcode the enumerator to be checked against
 * @return opcode as a string if there's a match
 */
#define CASE_RETURN_STR(opcode)                                               \
  case opcode:                                                                \
    return #opcode
/**
 * @brief Return enum value if string matches enum token
 *
 * @param enum enumerator token to be compared against `str`
 * @param str a string to be compared against the `enum` token
 * @return enum opcode if there's a match
 */
#define STREQ_RETURN_ENUM(enum, str)                                          \
  if (STREQ(#enum, str)) return enum

/**
 * @brief Load file contents into a string
 *
 * @param fp the file to be read
 * @param len optional pointer to store the amount of bytes read
 * @return the file contents
 */
char *cee_load_whole_file_fp(FILE *fp, size_t *len);
/**
 * @brief Load file contents into a string
 *
 * Wrapper over cee_load_whole_file_fp(), get the file by its
 *        relative-path.
 * @param filename the name of the file to be read
 * @param len optional pointer to store the amount of bytes read
 * @return the file contents
 */
char *cee_load_whole_file(const char filename[], size_t *len);

/**
 * @brief Fill a structure from a JSON file
 *
 * @param filename the name of the JSON file to be read
 * @param p_data a pointer to the structure to be filled
 * @param from_json_cb the callback that will receive the JSON data
 *        and then fill the structure
 * @return 1 on success, 0 on failure
 */
int cee_dati_from_fjson(char filename[],
                        void *p_data,
                        void(from_json_cb)(char *str,
                                           size_t len,
                                           void *p_data));

/**
 * @brief Create a copy of JSON string to a `struct sized_buffer`
 *
 * @param str the JSON string
 * @param len the JSON string length
 * @param buf the sized buffer
 */
void cee_sized_buffer_from_json(char *str,
                                size_t len,
                                struct sized_buffer *buf);

/**
 * @brief Convert a iso8601 string to a unix timestamp (milliseconds)
 *
 * Can be matched to the json_extract() and json_inject() %F specifier
 * @param timestamp the iso8601 string timestamp
 * @param len the string length
 * @param p_value pointer to the `uint64_t` variable to receive the converted
 * timestamp
 * @return 1 on success, 0 on failure
 */
int cee_iso8601_to_unix_ms(char *timestamp, size_t len, uint64_t *p_value);

/**
 * @brief Convert a unix timestamp (milliseconds) to a iso8601 string
 *
 * @param str the buffer to receive the converted timestamp
 * @param len the size of the buffer
 * @param p_value the unix timestamp to be converted to iso8601
 * @return the amount of characters (in bytes) written to the buffer
 */
int cee_unix_ms_to_iso8601(char *str, size_t len, uint64_t *p_value);

/**
 * @brief Convert a numerical string to `uint64_t`
 *
 * @param str the numerical string
 * @param len the string length
 * @param p_value pointer to the `uint64_t` variable to receive the converted
 * value
 * @return 1 on success, 0 on failure
 */
int cee_strtou64(char *str, size_t len, uint64_t *p_value);

/**
 * @brief Convert `uint64_t` to a numerical string
 *
 * @param str the buffer to store the numerical string
 * @param len the size of the buffer
 * @param p_value the `unsigned long long` value
 * @return the amount of characters (in bytes) written to the buffer
 */
int cee_u64tostr(char *str, size_t len, uint64_t *p_value);

/**
 * @brief Copies at most `len` bytes of `src` to `*p_dest`.
 *
 * Analogous to `strndup()`
 * @param src the buffer to be copied
 * @param len the maximum amount of characters to be copied
 * @p_dest a pointer to the new `src` copy
 * @return 1 on success, 0 on failure
 */
int cee_strndup(char *src, size_t len, char **p_dest);

/**
 * @brief Sleep for milliseconds amount
 *
 * @param tms milliseconds amount to sleep for
 * @return 0 on success, -1 on error with an `errno` set to indicate the error
 */
int cee_sleep_ms(const long tms);

/**
 * @brief Get the current timestamp in milliseconds
 *
 * @return the timestamp on success, 0 on failure
 */
uint64_t cee_timestamp_ms(void);

/**
 * @brief Get the preferred date and time representation for the current locale
 *
 * @param p_str the string buffer to be filled
 * @param len the string buffer size
 * @return a pointer to `p_str`
 */
char *cee_timestamp_str(char *p_str, int len);

/**
 * @brief Check if arbitrary string length is exceeded
 *
 * @param str the string to be checked
 * @param threshold_len maximum length for success
 * @return the string length on success, -1 on `NULL` string, and 0 if string
 * length is greater than threshold
 */
ssize_t cee_str_bounds_check(const char *str, const size_t threshold_len);

/**
 * @brief Concatenate an array of strings to a buffer
 *
 * @param strings the array of strings
 * @param nmemb amount of elements in the array
 * @param delim arbitrary delimiter for separating strings
 * @param wordlen maximum length supported for each string
 * @param maxlen maximum length supported for resulting buffer
 * @return the buffer of concatenated strings
 */
char *cee_join_strings(char **strings,
                       const size_t nmemb,
                       const char delim[],
                       const size_t wordlen,
                       const size_t maxlen);

void cee_gen_readlink(char *linkbuf, size_t linkbuf_size);

void cee_gen_dirname(char *linkbuf);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*CEE_UTILS_H */
