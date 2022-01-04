#ifndef NTL_H
#define NTL_H
#include <stddef.h> /* for size_t */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * A Null Terminated List (ntl) implementation
 *
 * A null terminated list of n elements of type struct E is defined as
 *
 * struct ntl {
 *    void * indices[n+1];  // indices[n] = NULL
 *    struct E e[n];  // sizeof (struct E)
 * };
 *
 * the list can be allocated as
 * p = ntl_calloc(n, size);
 *
 *       /-indices[n+1]\   /--------- e[n]-----------\
 * p -> [ | | | | | | |0][e_0]...............[e_(n-1)]
 *       |                 ^
 *       |                 |
 *       +-------->--------+
 *
 * p points to the begin of the memory block which overlaps with indices.
 *
 * p[0] points to e_0
 * p[1] points to e_1
 * ...
 * p[n-1] points to e_(n-1)
 * p[n] points to NULL
 *
 *
 * if p is NULL, it is treated as an empty NTL by all ntl functions.
 *
 * The use of ntl is very simple
 *
 *  for (size_t i = 0; p && p[i]; i++)
 *    // do something here for each element
 *
 * A ntl pointed by p is empty if p is NULL or p[0] == NULL
 *
 */

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
 * @brief Null-terminated list helper type
 */
typedef void **ntl_t;

/**
 * @brief Identification macro for null-terminated lists
 *
 * A macro meant to facillitate the identification of null-terminated lists.
 */
#define NTL_T(t) t **

/**
 * @brief Null-terminated list initialization callback
 *
 * Callback function that will be called for each element of the NTL
 *        during initialization
 */
typedef void (*ntl_init_cb)(void *);

/**
 * @brief Initialize a null-terminated list and each of its elements
 *
 * Initialize a NTL and fill n `nelems` of size `elem_size` with zeroes, and
 * call `init` for each element.
 * @param nelems the amount of elements for the NTL
 * @param elem_size the size of each NTL element
 * @param init the callback function to be called for each element initialized
 * @return the null-terminated list
 * @note if `init` is NULL, it is the same as ntl_calloc
 */
ntl_t ntl_calloc_init(size_t nelems, size_t elem_size, ntl_init_cb init_cb);

/**
 * @brief Initialize a null-terminated list
 *
 * Initialize a NTL and fill n `nelems` of size `elem_size` with zeroes
 * @param nelems the amount of elements for the NTL
 * @param elem_size the size of each NTL element
 * @return the null-terminated list
 */
ntl_t ntl_calloc(size_t nelems, size_t elem_size);

/**
 * @brief Initialize a null-terminated list and each of its elements
 *
 * @param nelems the amount of elements of the NTL
 * @param elem_size the size of each NTL element
 * @param init the callback function to be called for each element initialized
 * @return the null-terminated list
 * @note if `init` is NULL, it is the same as ntl_calloc
 * @warning use ntl_calloc_init() unless there's a good reason to use this
 */
ntl_t ntl_malloc_init(size_t nelems, size_t elem_size, ntl_init_cb init_cb);

/**
 * @brief Initialize a null-terminated list
 *
 * @param nelems the amount of elements of the NTL
 * @param elem_size the size of each NTL element
 * @return the null-terminated list
 * @warning use ntl_calloc() unless there's a good reason to use this
 */
ntl_t ntl_malloc(size_t nelems, size_t elem_size);

/**
 * @brief Changes the size of the null-terminated list
 *
 * Changes the size of the NTL memory block pointed by `p` to `nelems *
 * elem_size` bytes, call `init` for each element.
 * @param p the NTL to be resized
 * @param nelems the amount of elements of the NTL
 * @param elem_size the size of each NTL element
 * @param init the callback function to be called for each element initialized
 * @return the null-terminated list
 */
ntl_t ntl_realloc_init(ntl_t p,
                       size_t nelems,
                       size_t elem_size,
                       ntl_init_cb init);

/**
 * @brief Duplicate a null-terminated list
 *
 * @param p pointer to the source NTL
 * @param elem_size the size of each NTL element
 * @return the NTL duplicate
 */
ntl_t ntl_dup(ntl_t p, size_t elem_size);

/**
 * @brief Null-terminated list cleanup callback
 *
 * Callback function that will be called for each element of the NTL
 *        during cleanup
 */
typedef void (*ntl_free_cb)(void *);

/**
 * @brief Cleanup a null-terminated list
 *
 * Call `cleanup` callback for each element of the NTL, and then
 *        `free()` the NTL `p` pointer.
 * @param p the NTL to be free'd
 * @param cleanup the cleanup callback to be called for each element
 */
void ntl_free(ntl_t p, ntl_free_cb cleanup);

/**
 * @brief Return the null-terminated list length
 *
 * Analogous to `strlen()`, will iterate over the NTL until a NULL is found. If
 * `p` is NULL, it will return 0.
 * @param p the NTL pointer
 * @return the NTL length
 */
size_t ntl_length(ntl_t p);

/**
 * @brief Return the null-terminated list length under a threshold
 *
 * Behaves like ntl_length() but will stop at a threshold `max`
 * @param p the NTL pointer
 * @param max the threshold length that the function will stop at
 * @return the NTL length
 */
size_t ntl_length_max(ntl_t p, size_t max);

/**
 * @brief Call a user-defined callback for each NTL element
 *
 * @param cxt an optional user-arbitrary data to be passed along the callbacks
 * @param p the NTL pointer
 * @param f the user-defined callback
 */
void ntl_apply(void *cxt, ntl_t p, void (*f)(void *cxt, void *elem_p));

/**
 * @brief Callback function for creating and mapping a NTL to another
 */
typedef void (*ntl_elem_map)(void *cxt, void *from_elem, void *to_elem);

/**
 * @brief Behaves similarly to Haskell list's fmap
 *
 * @param cxt an optional user-arbitrary data to be passed along the callbacks
 * @param in_list the input NTL
 * @param out_elem_size the size of each output element
 * @param map the callback function to map each `in_list` element to the
 * `returned` NTL element
 * @return the new NTL
 */
ntl_t ntl_fmap(void *cxt,
               ntl_t in_list,
               size_t out_elem_size,
               ntl_elem_map map);

/**
 * @deprecated use ntl_append2() instead
 */
ntl_t ntl_append(ntl_t p, size_t elem_size, void *added_elem);

/**
 * @brief Append a element to the null-terminated list
 *
 * Append a element to the NTL, this is not efficient
 * for many appends.
 * @param p the NTL pointer
 * @param elem_size the size of each NTL element
 * @param added_elem the element to be appended
 * @note Its the caller's responsibility to make sure `added_elem` has the
 * same type and size as the NTL.
 */
void ntl_append2(ntl_t *p, size_t elem_size, void *added_elem);

/**
 * @brief The callback function to serialize a null-terminate into a buffer
 */
typedef size_t (*ntl_elem_serializer)(char *buf, size_t size, void *p);

/**
 * @brief Structure to assisti null-terminated list serialization
 */
struct ntl_serializer {
  /**
   * optional string delimiters
   */
  struct ntl_str_delimiter *delimiter;
  /**
   * the callback for serializing and appending each NTL element to `buf`
   * `elem_to_buf(NULL,0,p)` calculates the size needed to serializer p
   * `elem_to_buf(buf,n,p)` serialize p to a buffer
   * `elem_to_buf` should return a negative value for any errors
   */
  /*
   */
  ntl_elem_serializer elem_to_buf;
  /** the NTL to be serialized */
  ntl_t ntl_provider;
};

/**
 * @brief Configure serialized NTL string delimiters
 */
struct ntl_str_delimiter {
  /** defaults to '[' */
  char start_delimiter;
  /** defaults to ',' */
  char *element_delimiter;
  /** defaults to "" (blank) */
  char *last_element_delimiter;
  /** defaults to ']' */
  char end_delimiter;
  /** defaults to "null" */
  char *null_ntl;
};

/**
 * @deprecated use ntl_to_buf2() instead
 * @brief Behaves similarly to snprintf(), serialize a NTL `p` to string
 *
 * `ntl_to_buf(NULL,0,...)` return the number of bytes (excluding \0) needed to
 *       serialize p
 * `ntl_to_buf(buf,n,...)` serialize p to buf and return the number of
 *       bytes written excluding \0
 * @param buf the buffer to store the serialized NTL
 * @param buf_size the buffer size
 * @param p the NTL
 * @param d string delimiters for the resulting serialized string (defaults to
 * JSON array delimiters)
 * @param serialize the element serializer callback
 * @return the amount written to `buf` in bytes
 */
size_t ntl_to_buf(char *buf,
                  size_t buf_size,
                  ntl_t p,
                  struct ntl_str_delimiter *d,
                  ntl_elem_serializer serialize);

/**
 * @deprecated use ntl_to_abuf2() instead
 * @brief Analogous ntl_to_buf(), but will create a buffer thats large enough
 * to hold the output (including the null byte '\0')
 *
 * @param buf_p the buffer to be created (expects a `char*` address)
 * @param p the NTL
 * @param d string delimiters for the resulting serialized string (defaults to
 * JSON array delimiters)
 * @param serialize the element serializer callback
 * @return the amount written to `buf_p` in bytes
 * @note `buf_p` should be free'd accordingly after done being used
 */
size_t ntl_to_abuf(char **buf_p,
                   ntl_t p,
                   struct ntl_str_delimiter *d,
                   ntl_elem_serializer serialize);

/**
 * @brief Behaves similarly to snprintf(), serialize a NTL `p` to string
 *
 * `ntl_to_buf(NULL,0,...)` return the number of bytes (excluding \0) needed to
 *       serialize p
 * `ntl_to_buf(buf,n,...)` serialize p to buf and return the number of
 *       bytes written excluding \0
 * @param buf the buffer to store the serialized NTL
 * @param size the buffer size
 * @param serializer the serializer config structure
 * @return the amount written to `buf` in bytes
 */
size_t ntl_to_buf2(char *buf, size_t size, struct ntl_serializer *serializer);

/**
 * @brief Analogous ntl_to_buf(), but will create a buffer thats large enough
 * to hold the output (including the null byte '\0')
 *
 * @param buf_p the buffer to be created (expects a `char*` address)
 * @param serializer the serializer config structure
 * @return the amount written to `buf_p` in bytes
 * @note `buf_p` should be free'd accordingly after done being used
 */
size_t ntl_to_abuf2(char **buf_p, struct ntl_serializer *serializer);

/**
 * @brief Structure to assist de-serialization into a null-terminated list
 */
struct ntl_deserializer {
  /**
   * mandatory callback that partition a string to n smaller tokens,
   * each representing a NTL element
   */
  int (*partition_as_sized_bufs)(char *,
                                 size_t,
                                 NTL_T(struct sized_buffer) * p);
  /**
   * the size of each NTL element
   */
  size_t elem_size;
  /**
   * NTL elements initialization callback (ignored if NULL)
   */
  void (*init_elem)(void *);
  /**
   * callback that matches each token created at `partition_as_sized_bufs`
   *        to a NTL element
   */
  void (*elem_from_buf)(char *buf, size_t size, void *recipient);
  /**
   * a NTL pointer that should receive the resulting NTL
   */
  ntl_t *ntl_recipient_p;
};

/**
 * @deprecated use ntl_from_buf2() instead
 * @brief De-serialize buffer into a null-terminated list
 *
 * @param buf the buffer containing the data to be de-serialized into the NTL
 * @param size the buffer size
 * @param deserializer the de-serializer config structure
 * @return the amount of elements in the new NTL
 */
size_t ntl_from_buf(char *buf,
                    size_t size,
                    struct ntl_deserializer *deserializer);

/**
 * @brief De-serialize buffer into a null-terminated list
 *
 * @param buf the buffer containing the data to be de-serialized into the NTL
 * @param size the buffer size
 * @param deserializer the de-serializer config structure
 * @return the amount of elements in the new NTL
 * @note this will pass each one of the NTL's elements by its address at the
 * callback
 */
size_t ntl_from_buf2(char *buf,
                     size_t size,
                     struct ntl_deserializer *deserializer);

/**
 * @brief Check if an element is part of a null-terminated list by its address
 *
 * @param p the NTL
 * @param elem the element to be checked against `p`
 * @return `1` if `elem` is a member of the NTL, `0` otherwise
 */
int ntl_is_a_member(ntl_t p, void *elem);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NTL_H */
