// MIT License
// Copyright (c) 2022 Anotra
// https://github.com/Anotra/anomap

#include <stdlib.h>
#include <string.h>

#include "anomap.h"

#define ANOMAP_ALLOWED_OPTIONS ( anomap_reverse_order              \
                               | anomap_direct_access              \
                               | anomap_preserve_order             \
                               )

struct anomap {
  int (*cmp)(const void *, const void *);
  anomap_options options;
  bool free_on_cleanup;
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
  if (!key_size || !cmp || (options & ~ANOMAP_ALLOWED_OPTIONS))
    return false;
  memset(map, 0, sizeof *map);
  map->free_on_cleanup = false;
  map->options = options;
  map->cmp = cmp;
  map->keys.size = key_size;
  map->vals.size = val_size;
  return true;
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
  const bool free_on_cleanup = map->free_on_cleanup;
  memset(map, 0, sizeof *map);
  if (free_on_cleanup)
    free(map);
}

void
anomap_set_on_item_changed(
  struct anomap *map, anomap_on_item_changed *on_changed, void *data)
{
  map->on_changed.cb = on_changed;
  map->on_changed.data = data;
}

size_t
anomap_length(struct anomap *map) {
  return map->map.len;
}

static inline void
_anomap_on_empty(struct anomap *map) {
  if (map->map.len) return;
  if (map->options & anomap_preserve_order)
    map->order.tail = map->order.arr[0].next = map->order.arr[0].prev = 0;
  map->map.highest = 0;
}

void
anomap_clear(struct anomap *map) {
  if (0 == map->map.len)
    return;

  for (size_t i = 0; i < map->map.len; i++) {
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
  }
  map->map.len = 0;
  _anomap_on_empty(map);
}

bool
anomap_contains(struct anomap *map, void *key) {
  size_t position;
  return anomap_index_of(map, key, &position);
}

bool
anomap_index_of(struct anomap *map, void *key, size_t *position) {
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
anomap_at_index(struct anomap *map, size_t index, void *key, void *val) {
  if (index >= map->map.len) return false;
  const size_t key_size = map->keys.size, val_size = map->vals.size;
  const unsigned pos = map->map.arr[index];
  if (key) memcpy(key, map->keys.arr + key_size * pos, key_size);
  if (val) memcpy(val, map->vals.arr + val_size * pos, val_size);
  return true;
}

const void *
anomap_direct_key_at_index(struct anomap *map, size_t index) {
  if (!(map->options & anomap_direct_access))
    return NULL;
  if (index >= map->map.len)
    return NULL;
  return map->keys.arr + map->keys.size * map->map.arr[index];
}

void *
anomap_direct_val_at_index(struct anomap *map, size_t index) {
  if (!(map->options & anomap_direct_access))
    return NULL;
  if (index >= map->map.len)
    return NULL;
  if (!map->vals.size)
    return NULL;
  return map->vals.arr + map->vals.size * map->map.arr[index];
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
  const size_t key_size = map->keys.size, val_size = map->vals.size;
  anomap_operation result = 0;
  size_t mpos = 0;
  if (!anomap_index_of(map, key, &mpos)) {
    if (!(operation & anomap_insert))
      return 0;
    if (!_anomap_ensure_capacity(map, map->map.len + 1))
      return 0;
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
    return result;
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
  return result;
}

size_t
anomap_copy_range(struct anomap *map, size_t from_index, size_t to_index,
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
anomap_delete_range(struct anomap *map, size_t from_index, size_t to_index,
                    void *keys, void *vals)
{
  size_t count = anomap_copy_range(map, from_index, to_index, keys, vals);
  if (!count) return 0;
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
  return count;
}

void
anomap_foreach(struct anomap *map, anomap_foreach_cb *cb, void *data) {
  const size_t key_size = map->keys.size, val_size = map->vals.size;
  if (0 == map->map.len)
    return;
  if (map->options & anomap_preserve_order) {
    const unsigned tail = map->order.tail;
    unsigned pos = map->order.arr[tail].next;
    switch (val_size ? 1 : 0) {
      while (tail != pos) {
        pos = map->order.arr[pos].next;
        case 1:
        cb(map, data, map->keys.arr + key_size * pos,
                      map->vals.arr + val_size * pos);
      } break;

      while (tail != pos) {
        pos = map->order.arr[pos].next;
        case 0:
        cb(map, data, map->keys.arr + key_size * pos, NULL);
      } break;
    }
  } else {
    if (val_size) {
      for (size_t i=0; i<map->map.len; i++)
        cb(map, data, map->keys.arr + key_size * map->map.arr[i],
                      map->vals.arr + val_size * map->map.arr[i]);
    } else {
      for (size_t i=0; i<map->map.len; i++)
        cb(map, data, map->keys.arr + key_size * map->map.arr[i], NULL);
    }
  } 
}

bool
anomap_advance(struct anomap *map, size_t *index, anomap_position *position) {
  unsigned pos;
  if (0 == map->map.len)
    return false;
  if (map->options & anomap_preserve_order) {
    switch (*position) {
      case anomap_head:
        pos = map->order.arr[map->order.tail].next;
        anomap_index_of(map, map->keys.arr + map->keys.size * pos, index);
        *position = anomap_next;
        return true;
      case anomap_tail:
        pos = map->order.tail;
        anomap_index_of(map, map->keys.arr + map->keys.size * pos, index);
        *position = anomap_prev;
        return true;
      case anomap_next:
        pos = map->map.arr[*index];
        if (pos == map->order.tail)
          return false;
        pos = map->order.arr[pos].next;
        anomap_index_of(map, map->keys.arr + map->keys.size * pos, index);
        return true;
      case anomap_prev:
        pos = map->map.arr[*index];
        if (pos == map->order.arr[map->order.tail].next)
          return false;
        pos = map->order.arr[pos].prev;
        anomap_index_of(map, map->keys.arr + map->keys.size * pos, index);
        return true;
    }
  } else {
    switch (*position) {
      case anomap_head:
        *index = 0;
        *position = anomap_next;
        return true;
      case anomap_tail:
        *index = map->map.len - 1;
        *position = anomap_prev;
        return true;
      case anomap_next:
        if (*index >= map->map.len - 1)
          return false;
        (*index)++;
        return true;
      case anomap_prev:
        if (0 == *index)
          return false;
        (*index)--;
        return true;
    }
  }
  return false;
}

int
anomap_cmp_str(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}
