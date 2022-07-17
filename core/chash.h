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

/* Modified by Lucas Müller (muller.lucas@hotmail.com), 16 May 2022 
 * - add __chash_init() and __chash_free() as a non-malloc option */

#ifndef CWARE_LIBCHASH_H
#define CWARE_LIBCHASH_H

#define CWARE_LIBCHASH_VERSION  "x.0.0"

/* How big heap-allocated hashtables are by default */
#ifndef CHASH_INITIAL_SIZE
#define CHASH_INITIAL_SIZE 10
#elif CHASH_INITIAL_SIZE <= 0 
        "chash_init: default length must be greater than 0"
#endif

/* Calculates the next size of the hashtable. */
#ifndef CHASH_RESIZE
#define CHASH_RESIZE(size) \
    ((size) * 1.3)
#endif

/* The threshold that, when passed, will cause a resize */
#ifndef CHASH_LOAD_THRESHOLD
#define CHASH_LOAD_THRESHOLD 0.8
#endif

/* The type that is used for counters; useful for aligning hashtable
 * length and capacity fields so type casting warnings do not appear */
#ifndef CHASH_COUNTER_TYPE
#define CHASH_COUNTER_TYPE  int
#endif

/* The name of the key field */
#ifndef CHASH_KEY_FIELD
#define CHASH_KEY_FIELD key
#endif

/* The name of the value field */
#ifndef CHASH_VALUE_FIELD
#define CHASH_VALUE_FIELD value
#endif

/* The name of the state field */
#ifndef CHASH_STATE_FIELD
#define CHASH_STATE_FIELD state
#endif

/* The name of the buckets field */
#ifndef CHASH_BUCKETS_FIELD
#define CHASH_BUCKETS_FIELD buckets
#endif

/* The name of the length field */
#ifndef CHASH_LENGTH_FIELD
#define CHASH_LENGTH_FIELD length
#endif

/* The name of the capacity field */
#ifndef CHASH_CAPACITY_FIELD
#define CHASH_CAPACITY_FIELD capacity
#endif

/* State enums */
#define CHASH_UNFILLED  0
#define CHASH_FILLED    1
#define CHASH_TOMBSTONE 2

/* Built-ins */

#define chash_string_hash(key, hash)                                          \
    5031;                                                                     \
    do {                                                                      \
        int __CHASH_HINDEX = 0;                                               \
                                                                              \
        for(__CHASH_HINDEX = 0; (key)[__CHASH_HINDEX] != '\0';                \
                                                          __CHASH_HINDEX++) { \
            (hash) = (((hash) << 1) + (hash)) + (key)[__CHASH_HINDEX];        \
        }                                                                     \
    } while(0)

#define chash_string_compare(cmp_a, cmp_b) \
    (strcmp((cmp_a), (cmp_b)) == 0)

#define chash_default_init(bucket, _key, _value) \
    (bucket).CHASH_KEY_FIELD = (_key);           \
    (bucket).CHASH_VALUE_FIELD = _value




















/* utility macros */

#define __chash_abs(x) \
    ((x) < 0 ? (x) * - 1 : (x))

#define __chash_hash(mod, _key, namespace)                   \
    __CHASH_HASH = namespace ## _HASH((_key), __CHASH_HASH); \
    __CHASH_HASH = __CHASH_HASH % (mod);                     \
    __CHASH_HASH = __chash_abs(__CHASH_HASH);

#define __chash_probe(hashtable, _key, namespace)                             \
  while(__CHASH_INDEX < (hashtable)->CHASH_CAPACITY_FIELD) {                  \
    if((hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_STATE_FIELD ==    \
                                                      CHASH_UNFILLED)         \
      break;                                                                  \
                                                                              \
    if((namespace ## _COMPARE((_key),                                         \
     (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_KEY_FIELD)) == 1) { \
                                                                              \
      __CHASH_INDEX = -1;                                                     \
      break;                                                                  \
    }                                                                         \
                                                                              \
    __CHASH_HASH = (__CHASH_HASH + 1) % (hashtable)->CHASH_CAPACITY_FIELD;    \
    __CHASH_INDEX++;                                                          \
  }                                                                           \

#define __chash_probe_to_unfilled(mod, _key, buffer, namespace)              \
  while(1) {                                                                 \
    if(buffer[__CHASH_HASH].CHASH_STATE_FIELD != CHASH_FILLED)               \
      break;                                                                 \
                                                                             \
    if((namespace ## _COMPARE((_key), buffer[__CHASH_HASH].CHASH_KEY_FIELD)) \
                                                                      == 1)  \
      break;                                                                 \
                                                                             \
    __CHASH_HASH = (__CHASH_HASH + 1) % mod;                                 \
  }                                                                          \

#define __chash_resize(hashtable, namespace)                                  \
do {                                                                          \
  CHASH_COUNTER_TYPE __CHASH_INDEX = 0;                                       \
  namespace ## _BUCKET *__CHASH_BUCKETS = NULL;                               \
  CHASH_COUNTER_TYPE __CHASH_NEXT_SIZE = (CHASH_COUNTER_TYPE)                 \
                          CHASH_RESIZE((hashtable)->CHASH_CAPACITY_FIELD);    \
                                                                              \
  if((namespace ## _HEAP) == 0) {                                             \
    if((hashtable)->CHASH_LENGTH_FIELD !=                                     \
                                       (hashtable)->CHASH_CAPACITY_FIELD) {   \
        break;                                                                \
    }                                                                         \
                                                                              \
    fprintf(stderr, "__chash_resize: hashtable is full. could not resize"     \
                    " (%s:%i)\n", __FILE__, __LINE__);                        \
    abort();                                                                  \
  }                                                                           \
                                                                              \
  if((double) (hashtable)->CHASH_LENGTH_FIELD /                               \
     (double) (hashtable)->CHASH_CAPACITY_FIELD  < CHASH_LOAD_THRESHOLD)      \
    break;                                                                    \
                                                                              \
  __CHASH_BUCKETS = malloc((size_t) (__CHASH_NEXT_SIZE                        \
                           * ((CHASH_COUNTER_TYPE)                            \
                               sizeof(namespace ## _BUCKET))));               \
  memset(__CHASH_BUCKETS, 0, ((size_t) (__CHASH_NEXT_SIZE                     \
                           * ((CHASH_COUNTER_TYPE)                            \
                           sizeof(namespace ## _BUCKET)))));                  \
                                                                              \
  for(__CHASH_INDEX = 0; __CHASH_INDEX < (hashtable)->CHASH_CAPACITY_FIELD;   \
                                                         __CHASH_INDEX++) {   \
    namespace ## _BUCKET __CHASH_NEW_KEY_BUCKET;                              \
    memset(&__CHASH_NEW_KEY_BUCKET, 0, sizeof(namespace ## _BUCKET));         \
    namespace ## _INIT(__CHASH_NEW_KEY_BUCKET,                                \
        (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_INDEX].CHASH_KEY_FIELD,      \
        (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_INDEX].CHASH_VALUE_FIELD);   \
                                                                              \
    if((hashtable)->CHASH_BUCKETS_FIELD[__CHASH_INDEX].CHASH_STATE_FIELD      \
                                                             != CHASH_FILLED) \
      continue;                                                               \
                                                                              \
    __chash_hash(__CHASH_NEXT_SIZE, __CHASH_NEW_KEY_BUCKET.CHASH_KEY_FIELD,   \
                 namespace);                                                  \
    __chash_probe_to_unfilled(__CHASH_NEXT_SIZE,                              \
           (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_INDEX].CHASH_KEY_FIELD,   \
           __CHASH_BUCKETS, namespace)                                        \
                                                                              \
    __CHASH_BUCKETS[__CHASH_HASH] = __CHASH_NEW_KEY_BUCKET;                   \
    __CHASH_BUCKETS[__CHASH_HASH].CHASH_STATE_FIELD = CHASH_FILLED;           \
    __CHASH_HASH = 0;                                                         \
  }                                                                           \
                                                                              \
  free((hashtable)->CHASH_BUCKETS_FIELD);                                     \
  (hashtable)->CHASH_BUCKETS_FIELD = __CHASH_BUCKETS;                         \
  (hashtable)->CHASH_CAPACITY_FIELD = __CHASH_NEXT_SIZE;                      \
  __CHASH_HASH = 0;                                                           \
} while(0)

#define __chash_assert_nonnull(func, ptr)                            \
do {                                                                 \
    if((ptr) == NULL) {                                              \
        fprintf(stderr, #func ": " #ptr " cannot be null (%s:%i)\n", \
                __FILE__, __LINE__);                                 \
        abort();                                                     \
    }                                                                \
} while(0)
















/* operations */
#define __chash_init(hashtable, namespace)                            \
    (hashtable)->CHASH_LENGTH_FIELD = 0;                              \
    (hashtable)->CHASH_CAPACITY_FIELD = CHASH_INITIAL_SIZE;           \
    (hashtable)->CHASH_BUCKETS_FIELD = malloc(CHASH_INITIAL_SIZE      \
                      * sizeof(*((hashtable)->CHASH_BUCKETS_FIELD))); \
    memset((hashtable)->CHASH_BUCKETS_FIELD, 0,                       \
    sizeof(*((hashtable)->CHASH_BUCKETS_FIELD)) * CHASH_INITIAL_SIZE)

#define chash_init(hashtable, namespace)                              \
    NULL;                                                             \
                                                                      \
    (hashtable) = malloc(sizeof((*(hashtable))));                     \
    __chash_init(hashtable, namespace)

#define chash_init_stack(hashtable, buffer, _length, namespace)               \
    (*(hashtable));                                                           \
                                                                              \
    if((_length) <= 0) {                                                      \
        fprintf(stderr, "chash_init_stack: hashtable cannot have a maximum "  \
                        "length of 0 or less (%s:%i)\n", __FILE__, __LINE__); \
        abort();                                                              \
    }                                                                         \
                                                                              \
    __chash_assert_nonnull(chash_init_stack, buffer);                         \
                                                                              \
    (hashtable)->CHASH_LENGTH_FIELD = 0;                                      \
    (hashtable)->CHASH_CAPACITY_FIELD = _length;                              \
    (hashtable)->CHASH_BUCKETS_FIELD  = buffer 

#define chash_assign(hashtable, _key, _value, namespace)                     \
do {                                                                         \
  long __CHASH_HASH = 0;                                                     \
  namespace ## _BUCKET __CHASH_KEY_BUCKET;                                   \
  memset(&__CHASH_KEY_BUCKET, 0, sizeof(namespace ## _BUCKET));              \
  namespace ## _INIT(__CHASH_KEY_BUCKET, _key, _value);                      \
                                                                             \
  __chash_assert_nonnull(chash_assign, hashtable);                           \
  __chash_assert_nonnull(chash_assign, (hashtable)->CHASH_BUCKETS_FIELD);    \
  __chash_resize(hashtable, namespace);                                      \
  __chash_hash((hashtable)->CHASH_CAPACITY_FIELD, _key, namespace);          \
  __chash_probe_to_unfilled((hashtable)->CHASH_CAPACITY_FIELD,               \
                (_key), (hashtable)->CHASH_BUCKETS_FIELD, namespace)         \
                                                                             \
  if((hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_STATE_FIELD ==     \
                                                             CHASH_FILLED) { \
     namespace ## _FREE_VALUE(                                               \
          (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_VALUE_FIELD); \
  } else {                                                                   \
     (hashtable)->CHASH_LENGTH_FIELD++;                                      \
  }                                                                          \
                                                                             \
  (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH] = __CHASH_KEY_BUCKET;       \
  (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_STATE_FIELD =         \
                                                               CHASH_FILLED; \
} while(0)

#define chash_lookup(hashtable, _key, storage, namespace)                     \
storage;                                                                      \
                                                                              \
do {                                                                          \
  int __CHASH_INDEX = 0;                                                      \
  long __CHASH_HASH = 0;                                                      \
  namespace ## _BUCKET __CHASH_KEY_BUCKET;                                    \
  memset(&__CHASH_KEY_BUCKET, 0, sizeof(namespace ## _BUCKET));               \
  namespace ## _INIT(__CHASH_KEY_BUCKET, _key,                                \
                     __CHASH_KEY_BUCKET.CHASH_VALUE_FIELD);                   \
                                                                              \
  (void) __CHASH_KEY_BUCKET;                                                  \
                                                                              \
  __chash_assert_nonnull(chash_lookup, hashtable);                            \
  __chash_assert_nonnull(chash_lookup, (hashtable)->CHASH_BUCKETS_FIELD);     \
  __chash_hash((hashtable)->CHASH_CAPACITY_FIELD, _key, namespace);           \
  __chash_probe(hashtable, _key, namespace)                                   \
                                                                              \
  if(((hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_STATE_FIELD !=     \
              CHASH_FILLED) || __CHASH_INDEX != -1) {                         \
    fprintf(stderr, "chash_lookup: failed to find key in hashtable (%s:%i)"   \
                    "\n", __FILE__, __LINE__);                                \
    abort();                                                                  \
  }                                                                           \
                                                                              \
  storage = (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_VALUE_FIELD; \
} while(0)

#define chash_delete(hashtable, _key, namespace)                             \
do {                                                                         \
  int __CHASH_INDEX = 0;                                                     \
  long __CHASH_HASH = 0;                                                     \
                                                                             \
  __chash_assert_nonnull(chash_delete, hashtable);                           \
  __chash_assert_nonnull(chash_delete, (hashtable)->CHASH_BUCKETS_FIELD);    \
  __chash_hash((hashtable)->CHASH_CAPACITY_FIELD, _key, namespace);          \
  __chash_probe(hashtable, _key, namespace)                                  \
                                                                             \
  if(((hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_STATE_FIELD !=    \
                                    CHASH_FILLED) || __CHASH_INDEX != -1) {  \
    fprintf(stderr, "chash_delete: failed to find key in hashtable (%s:%i)"  \
                    "\n", __FILE__, __LINE__);                               \
    abort();                                                                 \
  }                                                                          \
                                                                             \
  namespace ## _FREE_KEY((hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH]      \
                         .CHASH_KEY_FIELD);                                  \
  namespace ## _FREE_VALUE(                                                  \
          (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_VALUE_FIELD); \
  (hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_STATE_FIELD =         \
                                                        CHASH_TOMBSTONE;     \
  (hashtable)->CHASH_LENGTH_FIELD--;                                         \
} while(0)

#define chash_contains(hashtable, _key, storage, namespace)                 \
1;                                                                          \
                                                                            \
do {                                                                        \
  int __CHASH_INDEX = 0;                                                    \
  long __CHASH_HASH = 0;                                                    \
                                                                            \
  __chash_assert_nonnull(chash_contents, hashtable);                        \
  __chash_assert_nonnull(chash_contents, (hashtable)->CHASH_BUCKETS_FIELD); \
  __chash_hash((hashtable)->CHASH_CAPACITY_FIELD, _key, namespace);         \
  __chash_probe(hashtable, _key, namespace)                                 \
                                                                            \
  if(((hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_STATE_FIELD !=   \
                                    CHASH_FILLED) || __CHASH_INDEX != -1) { \
    storage = 0;                                                            \
  }                                                                         \
} while(0)

#define chash_lookup_bucket(hashtable, _key, storage, namespace)           \
storage;                                                                   \
                                                                           \
do {                                                                       \
  CHASH_COUNTER_TYPE __CHASH_INDEX = 0;                                    \
  long __CHASH_HASH = 0;                                                   \
  namespace ## _BUCKET __CHASH_KEY_BUCKET;                                 \
  memset(&__CHASH_KEY_BUCKET, 0, sizeof(namespace ## _BUCKET));            \
  namespace ## _INIT(__CHASH_KEY_BUCKET, _key,                             \
                                  __CHASH_KEY_BUCKET.CHASH_VALUE_FIELD);   \
                                                                           \
  (void) __CHASH_KEY_BUCKET;                                               \
                                                                           \
  __chash_assert_nonnull(chash_lookup_bucket, hashtable);                  \
  __chash_assert_nonnull(chash_lookup_bucket,                              \
                                  (hashtable)->CHASH_BUCKETS_FIELD);       \
  __chash_hash((hashtable)->CHASH_CAPACITY_FIELD, _key, namespace);        \
  __chash_probe(hashtable, _key, namespace)                                \
                                                                           \
  if(((hashtable)->CHASH_BUCKETS_FIELD[__CHASH_HASH].CHASH_STATE_FIELD !=  \
                                   CHASH_FILLED) || __CHASH_INDEX != -1) { \
    fprintf(stderr, "chash_lookup_bucket: failed to find key in hashtable" \
                    "(%s:%i) \n", __FILE__, __LINE__);                     \
    abort();                                                               \
  }                                                                        \
                                                                           \
  storage = ((hashtable)->CHASH_BUCKETS_FIELD + __CHASH_HASH);             \
} while(0)

#define __chash_free(hashtable, namespace)                                  \
do {                                                                        \
  __chash_assert_nonnull(__chash_free, hashtable);                          \
  __chash_assert_nonnull(__chash_free, (hashtable)->CHASH_BUCKETS_FIELD);   \
  (hashtable)->CHASH_CAPACITY_FIELD--;                                      \
                                                                            \
  while((hashtable)->CHASH_CAPACITY_FIELD != -1) {                          \
    if((hashtable)->CHASH_BUCKETS_FIELD[(hashtable)->CHASH_CAPACITY_FIELD]  \
                                      .CHASH_STATE_FIELD != CHASH_FILLED) { \
      (hashtable)->CHASH_CAPACITY_FIELD--;                                  \
      continue;                                                             \
    }                                                                       \
                                                                            \
    namespace ##_FREE_KEY(                                                  \
      (hashtable)->CHASH_BUCKETS_FIELD[(hashtable)->CHASH_CAPACITY_FIELD]   \
            .CHASH_KEY_FIELD);                                              \
    namespace ##_FREE_VALUE(                                                \
      (hashtable)->CHASH_BUCKETS_FIELD[(hashtable)->CHASH_CAPACITY_FIELD]   \
            .CHASH_VALUE_FIELD);                                            \
    (hashtable)->CHASH_CAPACITY_FIELD--;                                    \
    (hashtable)->CHASH_LENGTH_FIELD--;                                      \
  }                                                                         \
                                                                            \
  if((namespace ## _HEAP) == 1) {                                           \
    free((hashtable)->CHASH_BUCKETS_FIELD);                                 \
  }                                                                         \
} while(0)

#define chash_free(hashtable, namespace)                                    \
do {                                                                        \
  __chash_assert_nonnull(chash_free, hashtable);                            \
  __chash_assert_nonnull(chash_free, (hashtable)->CHASH_BUCKETS_FIELD);     \
  (hashtable)->CHASH_CAPACITY_FIELD--;                                      \
                                                                            \
  while((hashtable)->CHASH_CAPACITY_FIELD != -1) {                          \
    if((hashtable)->CHASH_BUCKETS_FIELD[(hashtable)->CHASH_CAPACITY_FIELD]  \
                                      .CHASH_STATE_FIELD != CHASH_FILLED) { \
      (hashtable)->CHASH_CAPACITY_FIELD--;                                  \
      continue;                                                             \
    }                                                                       \
                                                                            \
    namespace ##_FREE_KEY(                                                  \
      (hashtable)->CHASH_BUCKETS_FIELD[(hashtable)->CHASH_CAPACITY_FIELD]   \
            .CHASH_KEY_FIELD);                                              \
    namespace ##_FREE_VALUE(                                                \
      (hashtable)->CHASH_BUCKETS_FIELD[(hashtable)->CHASH_CAPACITY_FIELD]   \
            .CHASH_VALUE_FIELD);                                            \
    (hashtable)->CHASH_CAPACITY_FIELD--;                                    \
    (hashtable)->CHASH_LENGTH_FIELD--;                                      \
  }                                                                         \
                                                                            \
  if((namespace ## _HEAP) == 1) {                                           \
    free((hashtable)->CHASH_BUCKETS_FIELD);                                 \
    free((hashtable));                                                      \
  }                                                                         \
} while(0)

#define chash_is_full(hashtable, namespace) \
    (((hashtable)->CHASH_LENGTH_FIELD) == ((hashtable)->CHASH_CAPACITY_FIELD))









/* Iterator logic */
#define chash_iter(hashtable, index, _key, _value)                           \
	for((index) = 0, (_key) = (hashtable)->CHASH_BUCKETS_FIELD[index].       \
                                                        CHASH_KEY_FIELD,     \
       (_value) = (hashtable)->CHASH_BUCKETS_FIELD[index].CHASH_VALUE_FIELD; \
       (index) < (hashtable)->CHASH_CAPACITY_FIELD;                          \
       (index) = ((index) < (hashtable)->CHASH_CAPACITY_FIELD)               \
                          ? ((index) + 1) : index,                           \
       (_key) = (hashtable)->CHASH_BUCKETS_FIELD[index].CHASH_KEY_FIELD,     \
       (_value) = (hashtable)->CHASH_BUCKETS_FIELD[index].CHASH_VALUE_FIELD, \
       (index) = (hashtable)->CHASH_CAPACITY_FIELD)

#define chash_skip(hashtable, index)                                        \
    if((hashtable)->CHASH_BUCKETS_FIELD[index].                             \
                                         CHASH_STATE_FIELD != CHASH_FILLED) \
        continue;

#endif
