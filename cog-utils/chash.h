#ifndef CWARE_LIBCHASH_H
#define CWARE_LIBCHASH_H

#define CWARE_LIBCHASH_VERSION  "1.0.5"

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
    (bucket).key = (_key);                       \
    (bucket).value = _value




















/* utility macros */

#define __chash_abs(x) \
    ((x) < 0 ? (x) * - 1 : (x))

#define __chash_hash(mod, _key, namespace)                   \
    __CHASH_HASH = namespace ## _HASH((_key), __CHASH_HASH); \
    __CHASH_HASH = __CHASH_HASH % (mod);                     \
    __CHASH_HASH = __chash_abs(__CHASH_HASH);

#define __chash_probe(hashtable, _key, namespace)                             \
  while(__CHASH_INDEX < (hashtable)->capacity) {                              \
    if((hashtable)->buckets[__CHASH_HASH].state == CHASH_UNFILLED)            \
      break;                                                                  \
                                                                              \
    if((namespace ## _COMPARE((_key),                                         \
                             (hashtable)->buckets[__CHASH_HASH].key)) == 1) { \
      __CHASH_INDEX = -1;                                                     \
      break;                                                                  \
    }                                                                         \
                                                                              \
    __CHASH_HASH = (__CHASH_HASH + 1) % (hashtable)->capacity;                \
    __CHASH_INDEX++;                                                          \
  }                                                                           \

#define __chash_probe_to_unfilled(mod, _key, buffer, namespace)         \
  while(1) {                                                            \
    if(buffer[__CHASH_HASH].state != CHASH_FILLED)                      \
      break;                                                            \
                                                                        \
    if((namespace ## _COMPARE((_key), buffer[__CHASH_HASH].key)) == 1)  \
      break;                                                            \
                                                                        \
    __CHASH_HASH = (__CHASH_HASH + 1) % mod;                            \
  }                                                                     \

#define __chash_resize(hashtable, namespace)                                \
do {                                                                        \
  CHASH_COUNTER_TYPE __CHASH_INDEX = 0;                                     \
  namespace ## _BUCKET *__CHASH_BUCKETS = NULL;                             \
  CHASH_COUNTER_TYPE __CHASH_NEXT_SIZE = (CHASH_COUNTER_TYPE)               \
                          CHASH_RESIZE((hashtable)->capacity);              \
                                                                            \
  if((namespace ## _HEAP) == 0) {                                           \
    if((hashtable)->length != (hashtable)->capacity) {                      \
        break;                                                              \
    }                                                                       \
                                                                            \
    fprintf(stderr, "__chash_resize: hashtable is full. could not resize"   \
                    " (%s:%i)\n", __FILE__, __LINE__);                      \
    abort();                                                                \
  }                                                                         \
                                                                            \
  if((double) (hashtable)->length /                                         \
     (double) (hashtable)->capacity < CHASH_LOAD_THRESHOLD)                 \
    break;                                                                  \
                                                                            \
  __CHASH_BUCKETS = malloc(__CHASH_NEXT_SIZE                                \
                           * ((CHASH_COUNTER_TYPE)                          \
                               sizeof(namespace ## _BUCKET)));              \
  memset(__CHASH_BUCKETS, 0, __CHASH_NEXT_SIZE                              \
                           * ((CHASH_COUNTER_TYPE)                          \
                           sizeof(namespace ## _BUCKET)));                  \
                                                                            \
  for(__CHASH_INDEX = 0; __CHASH_INDEX < (hashtable)->capacity;             \
                                                         __CHASH_INDEX++) { \
    namespace ## _BUCKET __CHASH_NEW_KEY_BUCKET;                            \
    namespace ## _INIT(__CHASH_NEW_KEY_BUCKET,                              \
                      (hashtable)->buckets[__CHASH_INDEX].key,              \
                      (hashtable)->buckets[__CHASH_INDEX].value);           \
                                                                            \
    if((hashtable)->buckets[__CHASH_INDEX].state != CHASH_FILLED)           \
      continue;                                                             \
                                                                            \
    __chash_hash(__CHASH_NEXT_SIZE, __CHASH_NEW_KEY_BUCKET.key, namespace); \
    __chash_probe_to_unfilled(__CHASH_NEXT_SIZE,                            \
                              (hashtable)->buckets[__CHASH_INDEX].key,      \
                              __CHASH_BUCKETS, namespace)                   \
                                                                            \
    __CHASH_BUCKETS[__CHASH_HASH] = __CHASH_NEW_KEY_BUCKET;                 \
    __CHASH_BUCKETS[__CHASH_HASH].state = CHASH_FILLED;                     \
    __CHASH_HASH = 0;                                                       \
  }                                                                         \
                                                                            \
  free((hashtable)->buckets);                                               \
  (hashtable)->buckets = __CHASH_BUCKETS;                                   \
  (hashtable)->capacity = __CHASH_NEXT_SIZE;                                \
  __CHASH_HASH = 0;                                                         \
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
#define chash_init(hashtable, namespace)                              \
    NULL;                                                             \
                                                                      \
    (hashtable) = malloc(sizeof((*(hashtable))));                     \
    (hashtable)->length = 0;                                          \
    (hashtable)->capacity = CHASH_INITIAL_SIZE;                       \
    (hashtable)->buckets = malloc(CHASH_INITIAL_SIZE                  \
                                  * sizeof(*((hashtable)->buckets))); \
    memset((hashtable)->buckets, 0,                                   \
                sizeof(*((hashtable)->buckets)) * CHASH_INITIAL_SIZE)

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
    (hashtable)->length = 0;                                                  \
    (hashtable)->capacity = _length;                                          \
    (hashtable)->buckets = buffer 

#define chash_assign(hashtable, _key, _value, namespace)                 \
do {                                                                     \
  long __CHASH_HASH = 0;                                                 \
  namespace ## _BUCKET __CHASH_KEY_BUCKET;                               \
  namespace ## _INIT(__CHASH_KEY_BUCKET, _key, _value);                  \
                                                                         \
  __chash_assert_nonnull(chash_assign, hashtable);                       \
  __chash_assert_nonnull(chash_assign, (hashtable)->buckets);            \
  __chash_resize(hashtable, namespace);                                  \
  __chash_hash((hashtable)->capacity, _key, namespace);                  \
  __chash_probe_to_unfilled((hashtable)->capacity,                       \
                            (_key), (hashtable)->buckets, namespace)     \
                                                                         \
  if((hashtable)->buckets[__CHASH_HASH].state == CHASH_FILLED) {         \
     namespace ## _FREE_VALUE((hashtable)->buckets[__CHASH_HASH].value); \
  } else {                                                               \
     (hashtable)->length++;                                              \
  }                                                                      \
                                                                         \
  (hashtable)->buckets[__CHASH_HASH] = __CHASH_KEY_BUCKET;               \
  (hashtable)->buckets[__CHASH_HASH].state = CHASH_FILLED;               \
} while(0)

#define chash_lookup(hashtable, _key, storage, namespace)                   \
storage;                                                                    \
                                                                            \
do {                                                                        \
  int __CHASH_INDEX = 0;                                                    \
  long __CHASH_HASH = 0;                                                    \
  namespace ## _BUCKET __CHASH_KEY_BUCKET;                                  \
  namespace ## _INIT(__CHASH_KEY_BUCKET, _key, __CHASH_KEY_BUCKET.value);   \
                                                                            \
  (void) __CHASH_KEY_BUCKET;                                                \
                                                                            \
  __chash_assert_nonnull(chash_lookup, hashtable);                          \
  __chash_assert_nonnull(chash_lookup, (hashtable)->buckets);               \
  __chash_hash((hashtable)->capacity, _key, namespace);                     \
  __chash_probe(hashtable, _key, namespace)                                 \
                                                                            \
  if(((hashtable)->buckets[__CHASH_HASH].state != CHASH_FILLED) ||          \
                                                    __CHASH_INDEX != -1) {  \
    fprintf(stderr, "chash_lookup: failed to find key in hashtable (%s:%i)" \
                    "\n", __FILE__, __LINE__);                              \
    abort();                                                                \
  }                                                                         \
                                                                            \
  storage = (hashtable)->buckets[__CHASH_HASH].value;                       \
} while(0)

#define chash_delete(hashtable, _key, namespace)                            \
do {                                                                        \
  int __CHASH_INDEX = 0;                                                    \
  long __CHASH_HASH = 0;                                                    \
                                                                            \
  __chash_assert_nonnull(chash_delete, hashtable);                          \
  __chash_assert_nonnull(chash_delete, (hashtable)->buckets);               \
  __chash_hash((hashtable)->capacity, _key, namespace);                     \
  __chash_probe(hashtable, _key, namespace)                                 \
                                                                            \
  if(((hashtable)->buckets[__CHASH_HASH].state != CHASH_FILLED) ||          \
                                                  __CHASH_INDEX != -1) {    \
    fprintf(stderr, "chash_delete: failed to find key in hashtable (%s:%i)" \
                    "\n", __FILE__, __LINE__);                              \
    abort();                                                                \
  }                                                                         \
                                                                            \
  namespace ## _FREE_KEY((hashtable)->buckets[__CHASH_HASH].key);           \
  namespace ## _FREE_VALUE((hashtable)->buckets[__CHASH_HASH].value);       \
  (hashtable)->buckets[__CHASH_HASH].state = CHASH_TOMBSTONE;               \
  (hashtable)->length--;                                                    \
} while(0)

#define chash_contains(hashtable, _key, storage, namespace)              \
1;                                                                       \
                                                                         \
do {                                                                     \
  int __CHASH_INDEX = 0;                                                 \
  long __CHASH_HASH = 0;                                                 \
                                                                         \
  __chash_assert_nonnull(chash_contents, hashtable);                     \
  __chash_assert_nonnull(chash_contents, (hashtable)->buckets);          \
  __chash_hash((hashtable)->capacity, _key, namespace);                  \
  __chash_probe(hashtable, _key, namespace)                              \
                                                                         \
  if(((hashtable)->buckets[__CHASH_HASH].state != CHASH_FILLED)          \
                                               || __CHASH_INDEX != -1) { \
    storage = 0;                                                         \
  }                                                                      \
} while(0)

#define chash_lookup_bucket(hashtable, _key, storage, namespace)           \
storage;                                                                   \
                                                                           \
do {                                                                       \
  CHASH_COUNTER_TYPE __CHASH_INDEX = 0;                                    \
  long __CHASH_HASH = 0;                                                   \
  namespace ## _BUCKET __CHASH_KEY_BUCKET;                                 \
  namespace ## _INIT(__CHASH_KEY_BUCKET, _key, __CHASH_KEY_BUCKET.value);  \
                                                                           \
  (void) __CHASH_KEY_BUCKET;                                               \
                                                                           \
  __chash_assert_nonnull(chash_lookup_bucket, hashtable);                  \
  __chash_assert_nonnull(chash_lookup_bucket, (hashtable)->buckets);       \
  __chash_hash((hashtable)->capacity, _key, namespace);                    \
  __chash_probe(hashtable, _key, namespace)                                \
                                                                           \
  if(((hashtable)->buckets[__CHASH_HASH].state != CHASH_FILLED) ||         \
                                                    __CHASH_INDEX != -1) { \
    fprintf(stderr, "chash_lookup_bucket: failed to find key in hashtable" \
                    "(%s:%i) \n", __FILE__, __LINE__);                     \
    abort();                                                               \
  }                                                                        \
                                                                           \
  storage = ((hashtable)->buckets + __CHASH_HASH);                         \
} while(0)

#define chash_free(hashtable, namespace)                                    \
do {                                                                        \
  __chash_assert_nonnull(chash_free, hashtable);                            \
  __chash_assert_nonnull(chash_free, (hashtable)->buckets);                 \
  (hashtable)->capacity--;                                                  \
                                                                            \
  while((hashtable)->capacity != -1) {                                      \
    if((hashtable)->buckets[(hashtable)->capacity].state != CHASH_FILLED) { \
      (hashtable)->capacity--;                                              \
      continue;                                                             \
    }                                                                       \
                                                                            \
    namespace ##_FREE_KEY(                                                  \
                    (hashtable)->buckets[(hashtable)->capacity].key);       \
    namespace ##_FREE_VALUE(                                                \
                    (hashtable)->buckets[(hashtable)->capacity].value);     \
    (hashtable)->capacity--;                                                \
    (hashtable)->length--;                                                  \
  }                                                                         \
                                                                            \
  if((namespace ## _HEAP) == 1) {                                           \
    free((hashtable)->buckets);                                             \
    free((hashtable));                                                      \
  }                                                                         \
} while(0);

#define chash_is_full(hashtable, namespace) \
    (((hashtable)->length) == ((hashtable)->capacity))









/* Iterator logic */
#define chash_iter(hashtable, index, _key, _value)                 \
	for((index) = 0, (_key) = (hashtable)->buckets[index].key,     \
                     (_value) = (hashtable)->buckets[index].value; \
                     (index) < (hashtable)->capacity;              \
                     (index) = ((index) < (hashtable)->capacity)   \
                                        ? ((index) + 1) : index,   \
                     (_key) = (hashtable)->buckets[index].key,     \
                     (_value) = (hashtable)->buckets[index].value, \
                     (index) = (hashtable)->capacity)

#define chash_skip(hashtable, index)                      \
    if((hashtable)->buckets[index].state != CHASH_FILLED) \
        continue;

#endif
