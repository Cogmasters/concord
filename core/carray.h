/* Copyright 2022 Cogmasters */
/*
 * C-Ware License
 * 
 * Copyright (c) 2022, C-Ware
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Redistributions of modified source code must append a copyright notice in
 *    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
 *    copyright notice, and the standalone license file if one exists.
 *
 * A 'redistribution' can be constituted as any version of the original source
 * code material that is intended to comprise some other derivative work of
 * this code. A fork created for the purpose of contributing to any version of
 * the source does not constitute a truly 'derivative work' and does not require
 * listing.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Modified by Lucas Müller <lucas@muller.codes>, 19 Sept 2022 
 * - __carray_init() should initialize its `size` value
 *
 * Modified by Lucas Müller <lucas@muller.codes>, 15 Feb 2022 
 * - CARRAY_RESIZE() has a fallback value (+1)
 *
 * Modified by Lucas Müller <lucas@muller.codes>, 06 Feb 2022 
 * - __carray_init() accept initial length
 *
 * Modified by Lucas Müller <lucas@muller.codes>, 02 Feb 2022 
 * - remove free(carray) at __carrray_free()
 *
 * Modified by Lucas Müller <lucas@muller.codes>, 01 Feb 2022 
 * - change CARRAY_INITIAL_SIZE from 5 to 4
 * - change CARRAY_RESIZE to doubling arrays to reduce realloc calls
 * - remove calloc() from __carray_init(), expect user to allocate it
 * - remove pseudo-return from __carray_init()
 *
 * Modified by Lucas Müller <lucas@muller.codes>, 27 Jan 2022 
 * - rename contents -> array 
 * - rename logical_size -> size
 * - rename physical_size -> realsize
 */

#ifndef CWARE_ARRAY_H
#define CWARE_ARRAY_H

#ifndef CARRAY_INITIAL_SIZE
#define CARRAY_INITIAL_SIZE 4
#endif

#ifndef CARRAY_RESIZE
#define CARRAY_RESIZE(current_size) \
    1 + current_size * 2
#endif

/* carray_init */
#ifndef CARRAY_STACKFUL
#define __carray_init(carray, length, _type, _compare, _free) \
do {                                                          \
    (carray)->realsize = length;                              \
    (carray)->size = 0;                                       \
    (carray)->array = calloc(length, sizeof(_type));          \
} while (0)

#define carray_init(carray, settings) \
    __carray_init(carray, CARRAY_INITIAL_SIZE, settings)
#else
#define carray_init(carray, length, block) \
do {                                       \
    carray.realsize = length;              \
    carray.size = 0;                       \
    carray.array = block;                  \
} while (0)
#endif

/* carray_insert */
#ifndef CARRAY_STACKFUL
#define __carray_insert_handle_full(carray, index, value)                                                  \
    (carray)->realsize = CARRAY_RESIZE((carray)->realsize);                                                \
    (carray)->array = realloc((carray)->array, sizeof(*(carray)->array) * (size_t) (carray)->realsize)
#else
#define __carray_insert_handle_full(carray, index, value)                                                                                \
    fprintf(stderr, "carray_insert: attempt to insert value '%s' into full array '%s'. (%s:%i)\n", #value, #carray, __FILE__, __LINE__); \
    exit(EXIT_FAILURE)
#endif

#define carray_insert(carray, index, value)                                                                                                          \
    if((carray)->size == (carray)->realsize) {                                                                                                       \
        __carray_insert_handle_full(carray, index, value);                                                                                           \
    }                                                                                                                                                \
                                                                                                                                                     \
    if(index < 0 || index > (carray)->size) {                                                                                                        \
        fprintf(stderr, "carray_insert: attempt to insert at index %i, out of bounds of array '%s'. (%s:%i)\n", index, #carray, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                                                                                                          \
    }                                                                                                                                                \
                                                                                                                                                     \
    memmove((carray)->array + index + 1, (carray)->array + index, sizeof(*(carray)->array) * (size_t) ((carray)->size - index));                  \
    (carray)->array[index] = value;                                                                                                               \
    (carray)->size++

/* carray_pop */
#define carray_pop(carray, index, location)                                                                                                       \
    location;                                                                                                                                     \
                                                                                                                                                  \
    if(index < 0 || index >= (carray)->size) {                                                                                                    \
        fprintf(stderr, "carray_pop: attempt to pop index %i, out of bounds of array '%s'. (%s:%i)\n", index, #carray, __FILE__, __LINE__);       \
        exit(EXIT_FAILURE);                                                                                                                       \
    }                                                                                                                                             \
                                                                                                                                                  \
    (carray)->size--;                                                                                                                             \
    (location) = (carray)->array[(index)];                                                                                                        \
    memmove((carray)->array + index, (carray)->array + index + 1, sizeof(*(carray)->array) * (size_t) ((carray)->size - index))

/* carray_remove */
#define __carray_remove(carray, value, _type, _compare, _free)                                                                                    \
do {                                                                                                                                              \
    int __CARRAY_ITER_INDEX = 0;                                                                                                                  \
                                                                                                                                                  \
    for(__CARRAY_ITER_INDEX = 0; __CARRAY_ITER_INDEX < (carray)->size; __CARRAY_ITER_INDEX++) {                                                   \
        _type __CARRAY_OPERAND_A = (carray)->array[__CARRAY_ITER_INDEX];                                                                          \
        _type __CARRAY_OPERAND_B = value;                                                                                                         \
                                                                                                                                                  \
        if((_compare) == 0)                                                                                                                       \
            continue;                                                                                                                             \
                                                                                                                                                  \
        _free;                                                                                                                                    \
        (carray)->size--;                                                                                                                         \
        memmove((carray)->array + __CARRAY_ITER_INDEX,                                                                                            \
                (carray)->array + __CARRAY_ITER_INDEX + 1,                                                                                        \
                sizeof(*(carray)->array) * (size_t) ((carray)->size - __CARRAY_ITER_INDEX));                                                      \
                                                                                                                                                  \
        __CARRAY_ITER_INDEX = -1;                                                                                                                 \
        break;                                                                                                                                    \
    }                                                                                                                                             \
                                                                                                                                                  \
    if(__CARRAY_ITER_INDEX != -1) {                                                                                                               \
        fprintf(stderr, "carray_remove: attempt to remove value '%s' that is not in array '%s'. (%s:%i)\n", #value, #carray, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                                                                                                       \
    }                                                                                                                                             \
} while(0)

#define carray_remove(carray, value, settings) \
    __carray_remove(carray, value, settings)

/* carray_find */
#define __carray_find(carray, value, location, _type, _compare, _free)                              \
    -1;                                                                                             \
                                                                                                    \
    do {                                                                                            \
        int __CARRAY_ITER_INDEX = 0;                                                                \
        location = -1;                                                                              \
                                                                                                    \
        for(__CARRAY_ITER_INDEX = 0; __CARRAY_ITER_INDEX < (carray)->size; __CARRAY_ITER_INDEX++) { \
            _type __CARRAY_OPERAND_A = (carray)->array[__CARRAY_ITER_INDEX];                        \
            _type __CARRAY_OPERAND_B = value;                                                       \
                                                                                                    \
            if((_compare) == 0)                                                                     \
                continue;                                                                           \
                                                                                                    \
            location = __CARRAY_ITER_INDEX;                                                         \
                                                                                                    \
            break;                                                                                  \
        }                                                                                           \
    } while(0)

#define carray_find(carray, value, location, settings) \
    __carray_find(carray, value, location, settings)

#ifndef CARRAY_STACKFUL
#define __carray_free_array(carray) free((carray)->array);         
#else
#define __carray_free_array(carray)
#endif

/* carray_free */
#define __carray_free(carray, _type, _compare, _free)                                           \
do {                                                                                            \
    int __CARRAY_ITER_INDEX = 0;                                                                \
                                                                                                \
    for(__CARRAY_ITER_INDEX = 0; __CARRAY_ITER_INDEX < (carray)->size; __CARRAY_ITER_INDEX++) { \
        _type __CARRAY_OPERAND_A = (carray)->array[__CARRAY_ITER_INDEX];                        \
        (void) __CARRAY_OPERAND_A;                                                              \
                                                                                                \
        _free;                                                                                  \
    }                                                                                           \
                                                                                                \
    __carray_free_array(carray);                                                                \
} while(0)

#define carray_free(carray, settings) \
    __carray_free(carray, settings)

/* carray_append */
#ifndef CARRAY_STACKFUL
#define __carray_append_handle_full(carray, value)                                                     \
    (carray)->realsize = CARRAY_RESIZE((carray)->realsize);                                            \
    (carray)->array = realloc((carray)->array, sizeof(*(carray)->array) * (size_t) (carray)->realsize)
#else
#define __carray_append_handle_full(carray, value)                                                                                       \
    fprintf(stderr, "carray_append: attempt to append value '%s' into full array '%s'. (%s:%i)\n", #value, #carray, __FILE__, __LINE__); \
    exit(EXIT_FAILURE)
#endif

#define carray_append(carray, value)                \
    if((carray)->size == (carray)->realsize) {      \
        __carray_append_handle_full(carray, value); \
    }                                               \
                                                    \
    (carray)->array[(carray)->size] = value;        \
    (carray)->size++;

#endif
