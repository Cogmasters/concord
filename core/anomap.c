// MIT License
// Copyright (c) 2022 Anotra
// https://github.com/Anotra/anomap

#include <stdlib.h>
#include <string.h>

#include "anomap.h"

#define NATIVE_LOCK_NONE     0
#define NATIVE_LOCK_PTHREADS 1
#define NATIVE_LOCK_WINDOWS  2

#if !defined ANOMAP_NATIVE_LOCKS
  #if defined __has_include
    #if __has_include(<pthread.h>)
      #define ANOMAP_NATIVE_LOCKS NATIVE_LOCK_PTHREADS
    #endif
  #endif
#endif

struct anomap_lock {
  void *(*create)(void);
  void (*destroy)(void *lock);
  struct {
    bool (*attempt)(void *lock);
    void (*acquire)(void *lock);
    void (*release)(void *lock);
  } r;
  struct {
    bool (*attempt)(void *lock);
    void (*acquire)(void *lock);
    void (*release)(void *lock);
  } w;
};

static void *
_null_lock_create(void) {
  static int dummy = 0;
  return &dummy;
}

static void
_null_lock_destroy(void *lock) {
  (void)lock;
}

static bool
_null_lock_attempt(void *lock) {
  (void)lock;
  return true;
}

static void
_null_lock_acquire(void *lock) {
  (void)lock;
}

static void
_null_lock_release(void *lock) {
  (void)lock;
}

static const struct anomap_lock null_lock = {
  .create = _null_lock_create,
  .destroy = _null_lock_destroy,
  .r = {
    .attempt = _null_lock_attempt,
    .acquire = _null_lock_acquire,
    .release = _null_lock_release,
  },
  .w = {
    .attempt = _null_lock_attempt,
    .acquire = _null_lock_acquire,
    .release = _null_lock_release,
  }
};

static unsigned anomap_has_locks =
#if !defined ANOMAP_NATIVE_LOCKS || ANOMAP_NATIVE_LOCKS == NATIVE_LOCK_NONE
  0;
  static const struct anomap_lock lock_functions = null_lock;
#else
  anomap_use_lock;

  #if ANOMAP_NATIVE_LOCKS == NATIVE_LOCK_PTHREADS
    #ifndef _GNU_SOURCE
      #define _GNU_SOURCE
    #endif
    #include <pthread.h>

    static void *
    _pthread_lock_create(void) {
      pthread_rwlock_t *lock = calloc(1, sizeof *lock);
      if (!lock) return NULL;
      pthread_rwlock_init(lock, NULL);
      return lock;
    }

    static void
    _pthread_lock_destroy(void *lock) {
      pthread_rwlock_destroy(lock);
      free(lock);
    }

    static bool
    _pthread_rd_lock_attempt(void *lock) {
      return 0 == pthread_rwlock_tryrdlock(lock);
    }

    static void
    _pthread_rd_lock(void *lock) {
      pthread_rwlock_rdlock(lock);
    }

    static void
    _pthread_rd_unlock(void *lock) {
      pthread_rwlock_unlock(lock);
    }

    static bool
    _pthread_wr_lock_attempt(void *lock) {
      return 0 == pthread_rwlock_trywrlock(lock);
    }

    static void
    _pthread_wr_lock(void *lock) {
      pthread_rwlock_wrlock(lock);
    }

    static void
    _pthread_wr_unlock(void *lock) {
      pthread_rwlock_unlock(lock);
    }

    static struct anomap_lock lock_functions = {
      .create = _pthread_lock_create,
      .destroy = _pthread_lock_destroy,
      .r = {
        .attempt = _pthread_rd_lock_attempt,
        .acquire = _pthread_rd_lock,
        .release = _pthread_rd_unlock,
      },
      .w = {
        .attempt = _pthread_wr_lock_attempt,
        .acquire = _pthread_wr_lock,
        .release = _pthread_wr_unlock,
      },
    };
  #else
    #error native lock not yet implemented
  #endif
#endif

#define LOCK_W_ATTEMPT map->lock.functions->w.attempt(map->lock.lock)
#define LOCK_W_ACQUIRE map->lock.functions->w.acquire(map->lock.lock)
#define LOCK_W_RELEASE map->lock.functions->w.release(map->lock.lock)
#define LOCK_R_ATTEMPT map->lock.functions->r.attempt(map->lock.lock)
#define LOCK_R_ACQUIRE map->lock.functions->r.acquire(map->lock.lock)
#define LOCK_R_RELEASE map->lock.functions->r.release(map->lock.lock)

#define ANOMAP_ALLOWED_OPTIONS ( anomap_reverse_order              \
                               | anomap_direct_access              \
                               | anomap_preserve_order             \
                               | anomap_has_locks                  \
                               )

struct anomap {
  int (*cmp)(const void *, const void *);
  anomap_options options;
  bool free_on_cleanup;
  struct {
    void *lock;
    const struct anomap_lock *functions;
  } lock;
  struct {
    anomap_on_item_changed *cb;
    void *data;
  } on_changed;
  struct {
    unsigned *arr;
    size_t len : 32, cap : 32;
    size_t highest;
  } map;
  struct {
    char *arr;
    size_t cap : 32, size : 32;
  } keys;
  struct {
    char *arr;
    size_t cap : 32, size : 32;
  } vals;
  struct {
    struct {
      unsigned prev, next;
    } *arr;
    size_t cap : 32;
    unsigned tail;
  } order;
};

static void _anomap_foreach(struct anomap *map, anomap_foreach_cb *cb,
                            void *data, anomap_position start_position);

anomap_options
anomap_supported_options(void) {
  return ANOMAP_ALLOWED_OPTIONS;
}

size_t
anomap_struct_size(void) {
  return sizeof(struct anomap);
}

bool
anomap_init(struct anomap *map,
            size_t key_size, size_t val_size,
            int (*cmp)(const void *, const void *),
            anomap_options options)
{
  if (!map || !key_size || !cmp || (options & ~ANOMAP_ALLOWED_OPTIONS))
    return false;
  memset(map, 0, sizeof *map);
  map->free_on_cleanup = false;
  map->options = options;
  map->cmp = cmp;
  map->keys.size = key_size;
  map->vals.size = val_size;
  map->lock.functions = options & anomap_use_lock
                      ? &lock_functions
                      : &null_lock;
  if ((map->lock.lock = map->lock.functions->create()))
    return true;

  memset(map, 0, sizeof *map);
  return false;
}

struct anomap *
anomap_create(size_t key_size, size_t val_size,
              int (*cmp)(const void *, const void *),
              anomap_options options)
{
  struct anomap *map = calloc(1, sizeof *map);
  if (!map) return NULL;
  if (anomap_init(map, key_size, val_size, cmp, options))
    return map->free_on_cleanup = true, map;
  return free(map), NULL;
}

void
anomap_destroy(struct anomap *map) {
  anomap_clear(map);
  free(map->map.arr);
  free(map->keys.arr);
  free(map->vals.arr);
  free(map->order.arr);
  map->lock.functions->destroy(map->lock.lock);
  const bool free_on_cleanup = map->free_on_cleanup;
  memset(map, 0, sizeof *map);
  if (free_on_cleanup)
    free(map);
}

void
anomap_set_on_item_changed(
  struct anomap *map, anomap_on_item_changed *on_changed, void *data)
{
  LOCK_W_ACQUIRE;
  map->on_changed.cb = on_changed;
  map->on_changed.data = data;
  LOCK_W_RELEASE;
}

size_t
anomap_length(struct anomap *map) {
  LOCK_R_ACQUIRE;
  size_t len = map->map.len;
  LOCK_R_RELEASE;
  return len;
}

static inline void
_anomap_on_empty(struct anomap *map) {
  if (map->map.len) return;
  if (map->options & anomap_preserve_order)
    map->order.tail = map->order.arr[0].next = map->order.arr[0].prev = 0;
  map->map.highest = 0;
}

static void
_anomap_clear_foreach(struct anomap *map, void *data, 
                      const void *key, const void *val)
{
  if (!map->on_changed.cb) return;
  map->on_changed.cb(
    &(struct anomap_item_changed) {
      .map = map,
      .data = map->on_changed.data,
      .op = anomap_delete,
      .key = (void *)key,
      .val.prev = (void *)val,
    });
}

void
anomap_clear(struct anomap *map) {
  LOCK_W_ACQUIRE;
  if (map->map.len) {
    if (map->on_changed.cb) {
      if (map->options & anomap_preserve_order)
        _anomap_foreach(map, _anomap_clear_foreach, NULL, anomap_tail);
      else _anomap_foreach(map, _anomap_clear_foreach, NULL, anomap_head);
    }
    map->map.len = 0;
    _anomap_on_empty(map);
  }
  LOCK_W_RELEASE;
}

bool
anomap_contains(struct anomap *map, void *key) {
  size_t position;
  return anomap_index_of(map, key, &position);
}

static bool
anomap_index_of_no_lock(struct anomap *map, void *key, size_t *position) {
  size_t lo = 0, mid, hi = map->map.len;
  const char *const keys = map->keys.arr;
  const size_t key_size = map->keys.size;
  int result;

  if (0 == map->map.len) goto on_empty;
  result = map->cmp(key, keys + key_size * map->map.arr[map->map.len - 1]);
  if (0 == result) return *position = map->map.len - 1, true;

# define BINARY_SEARCH(cmp_operator)                                          \
  if (result cmp_operator 0)                                                  \
    return *position = map->map.len, false;                                   \
  while (lo < hi) {                                                           \
    mid = lo + (hi - lo) / 2;                                                 \
    result = map->cmp(key, keys + key_size * map->map.arr[mid]);              \
    if (result == 0) return *position = mid, true;                            \
    if (result cmp_operator 0) lo = mid + 1;                                  \
    else hi = mid;                                                            \
  }
  
  if (map->options & anomap_reverse_order) {
    BINARY_SEARCH(<);
  } else {
    BINARY_SEARCH(>);
  }

# undef BINARY_SEARCH

  on_empty:
  return *position = lo, false;
}

bool
anomap_index_of(struct anomap *map, void *key, size_t *position) {
  LOCK_R_ACQUIRE;
  bool found = anomap_index_of_no_lock(map, key, position);
  LOCK_R_RELEASE;
  return found;
}

bool
anomap_at_index(struct anomap *map, size_t index, void *key, void *val) {
  LOCK_R_ACQUIRE;
  if (index >= map->map.len) {
    LOCK_R_RELEASE;
    return false;
  }
  const size_t key_size = map->keys.size, val_size = map->vals.size;
  const unsigned pos = map->map.arr[index];
  if (key) memcpy(key, map->keys.arr + key_size * pos, key_size);
  if (val) memcpy(val, map->vals.arr + val_size * pos, val_size);
  LOCK_R_RELEASE;
  return true;
}

const void *
anomap_direct_key_at_index(struct anomap *map, size_t index) {
  void *result = NULL;
  LOCK_R_ACQUIRE;
  if (!(map->options & anomap_direct_access))
    goto fail;
  if (index >= map->map.len)
    goto fail;

  result = map->keys.arr + map->keys.size * map->map.arr[index];

  fail:
  LOCK_R_RELEASE;
  return result;
}

void *
anomap_direct_val_at_index(struct anomap *map, size_t index) {
  void *result = NULL;
  LOCK_R_ACQUIRE;
  if (!(map->options & anomap_direct_access))
    goto fail;
  if (index >= map->map.len)
    goto fail;
  if (!map->vals.size)
    goto fail;

  result = map->vals.arr + map->vals.size * map->map.arr[index];

  fail:
  LOCK_R_RELEASE;
  return result;
}

static bool
_anomap_ensure_capacity(struct anomap *map, size_t capacity) {
  if (capacity > (size_t)1 << 31) return false;
  if (capacity <= map->map.cap) return true;
  size_t cap = map->map.cap ? map->map.cap << 1 : 8;
  while (cap < capacity) if (0 == (cap <<= 1)) return false;

#define RESIZE_ARRAY(ARRAY, ELEMENT_SIZE, CAPACITY, NEW_CAPACITY)         \
  do {                                                                    \
    if (CAPACITY < NEW_CAPACITY) {                                        \
      void *tmp =     /* use calloc initially to be safe */               \
        0 == CAPACITY ? calloc((NEW_CAPACITY), (ELEMENT_SIZE))            \
                      : realloc(ARRAY, (NEW_CAPACITY) *(ELEMENT_SIZE));   \
      if (!tmp) return false;                                             \
      ARRAY = tmp;                                                        \
      CAPACITY = NEW_CAPACITY;                                            \
    }                                                                     \
  } while (0)

  RESIZE_ARRAY(map->map.arr, sizeof *map->map.arr, map->map.cap, cap);

  RESIZE_ARRAY(map->keys.arr, map->keys.size, map->keys.cap, cap);

  if (map->vals.size)
    RESIZE_ARRAY(map->vals.arr, map->vals.size, map->vals.cap, cap);

  if (map->options & anomap_preserve_order)
    RESIZE_ARRAY(map->order.arr, sizeof *map->order.arr, map->order.cap, cap);

  return true;
}

static void
_unlink_element(struct anomap *map, unsigned pos) {
  if (0 == map->map.len) {
    map->order.tail = map->order.arr[0].next = map->order.arr[0].prev = 0;
  } else {
    const unsigned prev = map->order.arr[pos].prev;
    const unsigned next = map->order.arr[pos].next;
    map->order.arr[next].prev = prev;
    map->order.arr[prev].next = next;
    if (map->order.tail == pos)
      map->order.tail = prev;
  }
}

anomap_operation
anomap_do(struct anomap *map, anomap_operation operation,
          void *key, void *val)
{
  if (operation == anomap_getval)
    LOCK_R_ACQUIRE;
  else LOCK_W_ACQUIRE;
  const size_t key_size = map->keys.size, val_size = map->vals.size;
  anomap_operation result = 0;
  size_t mpos = 0;
  if (!anomap_index_of_no_lock(map, key, &mpos)) {
    if (!(operation & anomap_insert))
      goto finish;
    if (!_anomap_ensure_capacity(map, map->map.len + 1))
      goto finish;
    unsigned pos = map->map.highest == map->map.len
                 ? map->map.highest++
                 : map->map.arr[map->map.len];
    memcpy(map->keys.arr + key_size * pos, key, key_size);
    if (map->vals.size) {
      if (val) memcpy(map->vals.arr + val_size * pos, val, val_size);
      else memset(map->vals.arr + val_size * pos, 0, val_size);
    }
    if (mpos < map->map.len)
      memmove(map->map.arr + mpos + 1, map->map.arr + mpos,
              sizeof *map->map.arr * (map->map.len - mpos));
    map->map.arr[mpos] = pos;
    map->map.len++;
  
    if (map->options & anomap_preserve_order) {
      unsigned tail = map->order.tail;
      unsigned head = map->order.arr[tail].next;
      map->order.arr[map->order.arr[pos].prev = tail].next = pos;
      map->order.arr[map->order.arr[pos].next = head].prev = pos;
      map->order.tail = pos;
    }

    result |= anomap_insert;
    if (map->on_changed.cb)
      map->on_changed.cb(
        &(struct anomap_item_changed) {
          .map = map,
          .data = map->on_changed.data,
          .op = anomap_insert,
          .key = key,
          .val.now = val,
        });
    goto finish;
  }
  unsigned pos = map->map.arr[mpos];
  if (operation & anomap_update) {
    result |= anomap_update;
    void *const val_to_update = map->vals.arr + val_size * pos;
    if (map->on_changed.cb)
      map->on_changed.cb(
        &(struct anomap_item_changed) {
          .map = map,
          .data = map->on_changed.data,
          .op = anomap_update,
          .key = key,
          .val.prev = val_to_update,
          .val.now = val,
        });
    if (operation & anomap_getval) {
      result |= anomap_getval;
      char tmp[0x1000];
      char *a = val_to_update;
      char *b = val;
      for (size_t amount_left = map->vals.size; amount_left;) {
        size_t current_block = amount_left;
        if (current_block > sizeof tmp) current_block = sizeof tmp;
        memcpy(tmp, a, current_block);
        memcpy(a, b, current_block);
        memcpy(b, tmp, current_block);
        amount_left -= current_block;
        a += current_block;
        b += current_block;
      }
    } else {
      if (val_size) {
        if (val) memcpy(val_to_update, val, val_size);
        else memset(val_to_update, 0, val_size);
      }
    }
  } else if (operation & anomap_getval) {
    result |= anomap_getval;
    memcpy(val, map->vals.arr + val_size * pos, val_size);
  }

  if (operation & anomap_delete) {
    result |= anomap_delete;
    void *const deleted_item = map->vals.arr + val_size * pos;
    if (map->on_changed.cb)
      map->on_changed.cb(
        &(struct anomap_item_changed) {
          .map = map,
          .data = map->on_changed.data,
          .op = anomap_delete,
          .key = key,
          .val.prev = deleted_item,
        });
    if (mpos < --map->map.len)
      memmove(map->map.arr + mpos, map->map.arr + mpos + 1,
              sizeof *map->map.arr * (map->map.len - mpos));
    map->map.arr[map->map.len] = pos;
    if (map->options & anomap_preserve_order)
      _unlink_element(map, pos);
    _anomap_on_empty(map);
  }
  finish:
  if (operation == anomap_getval)
    LOCK_R_RELEASE;
  else LOCK_W_RELEASE;
  return result;
}

static size_t
anomap_copy_range_no_lock(struct anomap *map, 
                          size_t from_index, size_t to_index,
                          void *keys, void *vals)
{
  size_t count = 1 + (from_index < to_index ? to_index - from_index :
                                              from_index - to_index);
  if (from_index >= map->map.len || to_index >= map->map.len) return 0;
  if (keys || vals) {
    const size_t key_size = map->keys.size;
    const size_t val_size = map->vals.size;
    const int next = from_index <= to_index ? 1 : -1;
    for (size_t i = 0;; i++, from_index += next) {
      unsigned pos = map->map.arr[from_index];
      if (keys) memcpy(((char *)keys) + key_size * i,
                        map->keys.arr + key_size * pos,
                        key_size);
      if (vals) memcpy(((char *)vals) + val_size * i,
                        map->vals.arr + val_size * pos,
                        val_size);
      if (from_index == to_index) break;
    }
  }
  return count;
}

size_t
anomap_copy_range(struct anomap *map, size_t from_index, size_t to_index,
                  void *keys, void *vals)
{
  LOCK_R_ACQUIRE;
  size_t count = anomap_copy_range_no_lock(map, from_index, to_index,
                                           keys, vals);
  LOCK_R_RELEASE;
  return count;
}

size_t
anomap_delete_range(struct anomap *map, size_t from_index, size_t to_index,
                    void *keys, void *vals)
{
  LOCK_W_ACQUIRE;
  size_t count = anomap_copy_range_no_lock(map, from_index, to_index,
                                           keys, vals);
  if (!count) goto finish;
  const int next = from_index <= to_index ? 1 : -1;
  if (map->options & anomap_preserve_order)
    for (size_t i = from_index;; i += next) {
      _unlink_element(map, map->map.arr[i]);
      if (i == to_index) break;
    }
  for (size_t i = from_index;; i += next) {
    if (!map->on_changed.cb) break;
    unsigned pos = map->map.arr[i];
    map->on_changed.cb(
      &(struct anomap_item_changed) {
        .map = map,
        .data = map->on_changed.data,
        .op = anomap_delete,
        .key = map->keys.arr + map->keys.size * pos,
        .val.prev = map->vals.arr + map->vals.size * pos,
      });
    if (i == to_index) break;
  }
  
  size_t index = to_index < from_index ? to_index : from_index;
  size_t remaining = count;
  while (remaining) {
    unsigned tmp[4096];
    size_t block = remaining > 4096 ? 4096 : remaining;
    size_t copy_size = block * sizeof *map->map.arr;
    memcpy(tmp, map->map.arr + index, copy_size);
    memmove(map->map.arr + index, map->map.arr + index + block,
            (map->map.len - index - block) * sizeof *map->map.arr);
    map->map.len -= block;
    memcpy(map->map.arr + map->map.len, tmp, copy_size);
    remaining -= block;
  }
  _anomap_on_empty(map);
  finish:
  LOCK_W_RELEASE;
  return count;
}

static void
_anomap_foreach(struct anomap *map, anomap_foreach_cb *cb, void *data,
                anomap_position start_position)
{
  const size_t key_size = map->keys.size, val_size = map->vals.size;
  if (0 == map->map.len)
    return;
  if (map->options & anomap_preserve_order) {
    unsigned tail = map->order.tail;
    unsigned head = map->order.arr[tail].next;
    unsigned start = start_position == anomap_head ? head : tail;
    unsigned pos = start;
    switch ((start_position == anomap_tail ? 2 : 0) | (val_size ? 1 : 0)) {
      while (pos != tail) {
        pos = map->order.arr[pos].next;
        case 0 | 0:
        cb(map, data, map->keys.arr + key_size * pos, NULL);
      } break;
      while (pos != tail) {
        pos = map->order.arr[pos].next;
        case 0 | 1:
        cb(map, data, map->keys.arr + key_size * pos,
                      map->vals.arr + val_size * pos);
      } break;
      while (pos != head) {
        pos = map->order.arr[pos].prev;
        case 2 | 0:
        cb(map, data, map->keys.arr + key_size * pos, NULL);
      } break;
      while (pos != head) {
        pos = map->order.arr[pos].prev;
        case 2 | 1:
        cb(map, data, map->keys.arr + key_size * pos,
                      map->vals.arr + val_size * pos);
      } break;
    }
  } else {
    if (start_position == anomap_head) {
      if (val_size) {
        for (size_t i=0; i<map->map.len; i++)
          cb(map, data, map->keys.arr + key_size * map->map.arr[i],
                        map->vals.arr + val_size * map->map.arr[i]);
      } else {
        for (size_t i=0; i<map->map.len; i++)
          cb(map, data, map->keys.arr + key_size * map->map.arr[i], NULL);
      }
    } else {
      if (val_size) {
        for (size_t i = map->map.len; i--;)
          cb(map, data, map->keys.arr + key_size * map->map.arr[i],
                        map->vals.arr + val_size * map->map.arr[i]);
      } else {
        for (size_t i = map->map.len; i--;)
          cb(map, data, map->keys.arr + key_size * map->map.arr[i], NULL);
      }
    }
  } 
}

void
anomap_foreach(struct anomap *map, anomap_foreach_cb *cb, void *data) {
  LOCK_R_ACQUIRE;
  _anomap_foreach(map, cb, data, anomap_head);
  LOCK_R_RELEASE;
}

void
anomap_foreach_reverse(struct anomap *map, anomap_foreach_cb *cb, void *data) {
  LOCK_R_ACQUIRE;
  _anomap_foreach(map, cb, data, anomap_tail);
  LOCK_R_RELEASE;
}


bool
anomap_advance(struct anomap *map, size_t *index, anomap_position *position) {
  unsigned pos;
  LOCK_R_ACQUIRE;
  if (0 == map->map.len)
    goto return_false;
  if (map->options & anomap_preserve_order) {
    switch (*position) {
      case anomap_head:
        pos = map->order.arr[map->order.tail].next;
        anomap_index_of(map, map->keys.arr + map->keys.size * pos, index);
        *position = anomap_next;
        goto return_true;
      case anomap_tail:
        pos = map->order.tail;
        anomap_index_of(map, map->keys.arr + map->keys.size * pos, index);
        *position = anomap_prev;
        goto return_true;
      case anomap_next:
        pos = map->map.arr[*index];
        if (pos == map->order.tail)
          goto return_false;
        pos = map->order.arr[pos].next;
        anomap_index_of(map, map->keys.arr + map->keys.size * pos, index);
        goto return_true;
      case anomap_prev:
        pos = map->map.arr[*index];
        if (pos == map->order.arr[map->order.tail].next)
          goto return_false;
        pos = map->order.arr[pos].prev;
        anomap_index_of(map, map->keys.arr + map->keys.size * pos, index);
        goto return_true;
    }
  } else {
    switch (*position) {
      case anomap_head:
        *index = 0;
        *position = anomap_next;
        goto return_true;
      case anomap_tail:
        *index = map->map.len - 1;
        *position = anomap_prev;
        goto return_true;
      case anomap_next:
        if (*index >= map->map.len - 1)
          goto return_false;
        (*index)++;
        goto return_true;
      case anomap_prev:
        if (0 == *index)
          goto return_false;
        (*index)--;
        goto return_true;
    }
  }
  // false should be first as it's the default return value
  return_false:
  LOCK_R_RELEASE;
  return false;

  return_true:
  LOCK_R_RELEASE;
  return true;
}

int
anomap_cmp_str(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}
