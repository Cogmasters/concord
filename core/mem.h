#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <stdbool.h>

#ifdef LOG_DEBUG
#include <stdio.h>
#endif

/**
 * @brief `malloc`-equivalent function pointer type
 *
 * @note This function **must** be thread safe. It **need not** be
 * AS-Safe.
 *
 * Allocates exactly @p length bytes of memory and returns a pointer
 * to it. It **must** return a valid pointer or abort execution. The
 * returned pointer **must** be suitably aligned for any type. If @p
 * length is 0 or exceeds `PTRDIFF_MAX`, the behavior is undefined.
 */
typedef void *(*malloc_fn_t)(size_t length);

/**
 * @brief `calloc`-equivalent function pointer type
 *
 * @note This function **must** be thread safe. It **need not** be
 * AS-Safe.
 *
 * Allocates memory for exactly @p nmemb items of size @p length and
 * returns a pointer to it. The memory consists of all zero bytes. It
 * **must** return a valid pointer or abort execution. The returned
 * pointer **must** be suitably aligned for any type. If @p length or
 * @p nmemb are 0, or the value of `length * nmemb` exceeds
 * `PTRDIFF_MAX`, or the multiplication overflows, the behavior is
 * undefined.
 */
typedef void *(*calloc_fn_t)(size_t nmemb, size_t length);

/**
 * @brief `realloc`-equivalent function pointer type
 *
 * @note This function **must** be thread safe. It **need not** be
 * AS-Safe.
 *
 * Returns a pointer to a new allocation of size @p length for the data
 * in @p old_ptr . It **must** return a valid pointer or abort execution. It
 * **need not** (but **may**) return @p old_ptr. The returned pointer must be
 * suitably aligned for any type. If @p length is 0 or exceeds
 * PTRDIFF_MAX, the behavior is undefined
 *
 */
typedef void *(*realloc_fn_t)(void *old_ptr, size_t length);

/**
 * @brief `free`-equivalent function pointer type
 *
 * @note This function **must** be thread safe. It **need not** be
 * AS-Safe.
 *
 * Releases the memory pointed to by @p ptr. It **must** succeed or abort
 * execution. If @p ptr is a null pointer, it **must** return without any
 * operation being performed.
 */
typedef void (*free_fn_t)(void *ptr);

/**
 * @brief `strdup`-equivalent function pointer type
 *
 * @note This function **must** be thread safe. It **need not** be
 * AS-Safe.
 *
 * Returns a new allocation for the null-terminated string pointed to
 * by @p str. It **must** return a valid pointer or abort execution. The
 * returned pointer **need not** be aligned. If @p str is a null pointer, or
 * the length of @p str exceeds PTRDIFF_MAX, the behavior is undefined.
 *
 */
typedef char *(*strdup_fn_t)(const char *ptr);

struct ccord_memory_fn_vtable {
    malloc_fn_t malloc_fn;
    calloc_fn_t calloc_fn;
    realloc_fn_t realloc_fn;
    free_fn_t free_fn;
    strdup_fn_t strdup_fn;
};

extern struct ccord_memory_fn_vtable ccord_global_memory_fn_vtable;
extern bool ccord_mem_is_initialized;

/** @brief Initialize the memory functions */
void mem_init(malloc_fn_t malloc_fn,
              calloc_fn_t calloc_fn,
              realloc_fn_t realloc_fn,
              free_fn_t free_fn,
              strdup_fn_t strdup_fn);

#ifdef LOG_DEBUG
#define CHECK_INIT                                                            \
    if (!ccord_mem_is_initialized)                                            \
        fprintf(stderr, "memory functions are not initialized, did you "      \
                        "forget to call ccord_global_init?\n");
#else
#define CHECK_INIT
#endif

/** @brief Like malloc. Cannot fail. */
static inline void *
ccord_malloc(size_t length)
{
    CHECK_INIT
    return ccord_global_memory_fn_vtable.malloc_fn(length);
}

/** @brief Like calloc. Cannot fail. */
static inline void *
ccord_calloc(size_t nmemb, size_t length)
{
    CHECK_INIT
    return ccord_global_memory_fn_vtable.calloc_fn(nmemb, length);
}

/** @brief Like realloc. Cannot fail. */
static inline void *
ccord_realloc(void *old_ptr, size_t length)
{
    CHECK_INIT
    return ccord_global_memory_fn_vtable.realloc_fn(old_ptr, length);
}

/** @brief Like free. Cannot fail. */
static inline void
ccord_free(void *ptr)
{
    CHECK_INIT
    ccord_global_memory_fn_vtable.free_fn(ptr);
}

/** @brief Like strdup. Cannot fail. */
static inline char *
ccord_strdup(const char *str)
{
    CHECK_INIT
    return ccord_global_memory_fn_vtable.strdup_fn(str);
}

#undef CHECK_INIT

#endif
