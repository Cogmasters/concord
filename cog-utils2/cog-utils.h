#ifndef COG_UTILS_H
#define COG_UTILS_H

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Sized buffer
 *
 * A very important data structure that is used
 * pervasively in the conversion between JSON strings and C structs,
 * http request/response body
 */
struct sized_buffer {
  /** the buffer's start */
  char *start;
  /** the buffer's size in bytes */
  size_t size;
};

/**
 * @brief Load file contents into a string
 *
 * @param fp the file to be read
 * @param len optional pointer to store the amount of bytes read
 * @return the file contents
 */
char *cog_load_whole_file_fp(FILE *fp, size_t *len);
/**
 * @brief Load file contents into a string
 *
 * Wrapper over cog_load_whole_file_fp(), get the file by its
 *        relative-path.
 * @param filename the name of the file to be read
 * @param len optional pointer to store the amount of bytes read
 * @return the file contents
 */
char *cog_load_whole_file(const char filename[], size_t *len);

/**
 * @brief Fill a structure from a JSON file
 *
 * @param filename the name of the JSON file to be read
 * @param p_data a pointer to the structure to be filled
 * @param from_json_cb the callback that will receive the JSON data
 *        and then fill the structure
 * @return 1 on success, 0 on failure
 */
int cog_dati_from_fjson(char filename[],
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
void cog_sized_buffer_from_json(char *str,
                                size_t len,
                                struct sized_buffer *buf);

/**
 * @brief Get the difference between UTC and the latest local standard time, in
 *        seconds.
 * @return difference between UTC and local time in seconds
 */
long cog_timezone(void);

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
int cog_iso8601_to_unix_ms(char *timestamp, size_t len, uint64_t *p_value);

/**
 * @brief Convert a unix timestamp (milliseconds) to a iso8601 string
 *
 * @param str the buffer to receive the converted timestamp
 * @param len the size of the buffer
 * @param p_value the unix timestamp to be converted to iso8601
 * @return the amount of characters (in bytes) written to the buffer
 */
int cog_unix_ms_to_iso8601(char *str, size_t len, uint64_t *p_value);

/**
 * @brief Convert a numerical string to `uint64_t`
 *
 * @param str the numerical string
 * @param len the string length
 * @param p_value pointer to the `uint64_t` variable to receive the converted
 * value
 * @return 1 on success, 0 on failure
 */
int cog_strtou64(char *str, size_t len, uint64_t *p_value);

/**
 * @brief Convert `uint64_t` to a numerical string
 *
 * @param str the buffer to store the numerical string
 * @param len the size of the buffer
 * @param p_value the `unsigned long long` value
 * @return the amount of characters (in bytes) written to the buffer
 */
int cog_u64tostr(char *str, size_t len, uint64_t *p_value);

/**
 * @brief Copies at most `len` bytes of `src` to `*p_dest`.
 *
 * Analogous to `strndup()`
 * @param src the buffer to be copied
 * @param len the maximum amount of characters to be copied
 * @param p_dest a pointer to the new `src` copy
 * @return length of copied string on success, 0 on failure
 */
size_t cog_strndup(const char *src, size_t len, char **p_dest);

/**
 * @brief Copies at most `len` bytes of `src` to `*p_dest`.
 *
 * Analogous to `asprintf()`
 * @param strp source to write resulting string to
 * @param fmt printf format string
 * @param ... variadic arguments to be matched to `fmt` specifiers
 * @return length of copied string on success, -1 on failure
 */
size_t cog_asprintf(char **strp, const char fmt[], ...);

/**
 * @brief Sleep for milliseconds amount
 *
 * @param tms milliseconds amount to sleep for
 * @return 0 on success, -1 on error with an `errno` set to indicate the error
 */
int cog_sleep_ms(const long tms);

/**
 * @brief Get the current timestamp in milliseconds
 *
 * @return the timestamp on success, 0 on failure
 */
uint64_t cog_timestamp_ms(void);

/**
 * @brief Check if arbitrary string length is exceeded
 *
 * @param str the string to be checked
 * @param threshold_len maximum length for success
 * @return the string length on success, SIZE_MAX on `NULL` string, and 0 if
 *        string length is greater than threshold
 */
size_t cog_str_bounds_check(const char *str, const size_t threshold_len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COG_UTILS_H */
