// MIT License
// Copyright (c) 2022 Anotra
// https://github.com/Anotra/anomap

#include <stdlib.h>
#include <string.h>

#include "anomap.h"

struct anomap {
  int (*cmp)(const void *, const void *);
  struct {
    unsigned *arr;
    size_t len, cap;
    size_t highest;
  } map;
  struct {
    char *arr;
    size_t len, cap, size;
  } keys;
  struct {
    char *arr;
    size_t len, cap, size;
  } vals;
};

struct anomap *
anomap_create(size_t key_size, size_t val_size,
              int (*cmp)(const void *, const void *)) {
  struct anomap *map = calloc(1, sizeof *map);
  if (map) {
    map->cmp = cmp;
    map->keys.size = key_size;
    map->vals.size = val_size;
    return map;
  }
  return NULL;
}

void
anomap_destroy(struct anomap *map) {
  free(map->keys.arr);
  free(map->vals.arr);
  free(map->map.arr);
  memset(map, 0, sizeof *map);
  free(map);
}

size_t
anomap_length(struct anomap *map) {
  return map->map.len;
}

static bool
_anomap_find(struct anomap *map, void *key, size_t *position) {
  size_t lo = 0, mid, hi = map->map.len;
  while (lo < hi) {
    mid = (lo + hi) / 2;
    int r = map->cmp(key, map->keys.arr + map->keys.size * map->map.arr[mid]);
    if (r == 0) return *position = mid, true;
    if (r > 0) lo = mid + 1;
    else hi = mid;
  }
  return *position = lo, false;
}

bool
anomap_index_of(struct anomap *map, size_t *index, void *key) {
  size_t mpos = 0;
  if (!_anomap_find(map, key, &mpos))
    return false;
  return *index = mpos, true;
}

bool
anomap_at_index(struct anomap *map, size_t index, void *key, void *val) {
  if (index >= map->map.len) return false;
  if (key) memcpy(key, map->keys.arr + map->keys.size * map->map.arr[index],
                  map->keys.size);
  if (val) memcpy(val, map->vals.arr + map->vals.size * map->map.arr[index],
                  map->vals.size);
  return true;
}

static bool
_anomap_ensure_capacity(struct anomap *map, size_t capacity) {
  if (capacity > ~(unsigned)0) return false;
  if (capacity <= map->map.cap) return true;
  size_t cap = map->map.cap ? map->map.cap << 1 : 8;
  while (cap < capacity) cap <<= 1;
  if (map->keys.cap < cap) {
    void *tmp = realloc(map->keys.arr, map->keys.size * cap);
    if (!tmp) return false;
    map->keys.arr = tmp;
    map->keys.cap = cap;
  }
  if (map->vals.size && map->vals.cap < cap) {
    void *tmp = realloc(map->vals.arr, map->vals.size * cap);
    if (!tmp) return false;
    map->vals.arr = tmp;
    map->vals.cap = cap;
  }
  if (map->map.cap < cap) {
    unsigned *tmp = realloc(map->map.arr, sizeof *map->map.arr * cap);
    if (!tmp) return false;
    map->map.arr = tmp;
    map->map.cap = cap;
  }
  return true;
}

enum anomap_operation
anomap_do(struct anomap *map, enum anomap_operation operation,
          void *key, void *val)
{
  enum anomap_operation result = 0;
  size_t mpos = 0;
  if (!_anomap_find(map, key, &mpos)) {
    if (~operation & anomap_insert)
      return 0;
    if (!_anomap_ensure_capacity(map, map->map.len + 1))
      return 0;
    unsigned pos = map->map.highest == map->map.len ?
                  map->map.highest++ : map->map.arr[map->map.len];
    memcpy(map->keys.arr + map->keys.size * pos, key, map->keys.size);
    if (map->vals.size) {
      if (val)
        memcpy(map->vals.arr + map->vals.size * pos, val, map->vals.size);
      else
        memset(map->vals.arr + map->vals.size * pos, 0, map->vals.size);
    }
    if (mpos <= map->map.len)
      memmove(map->map.arr + mpos + 1, map->map.arr + mpos,
              sizeof *map->map.arr * (map->map.len - mpos));
    map->map.arr[mpos] = pos;
    map->map.len++;
    result |= anomap_insert;
    return result;
  }
  unsigned pos = map->map.arr[mpos];
  if (operation & anomap_update) {
    result |= anomap_update;
    if (operation & anomap_getval) {
      result |= anomap_getval;
      char tmp[0x1000];
      char *a = map->vals.arr + map->vals.size * pos;
      char *b = val;
      size_t amount_left = map->vals.size;
      for (size_t i = 0; amount_left; i += sizeof tmp) {
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
      if (map->vals.size) {
        if (val)
          memcpy(map->vals.arr + map->vals.size * pos, val, map->vals.size);
        else
          memset(map->vals.arr + map->vals.size * pos, 0, map->vals.size);
      }
    }
  } else if (operation & anomap_getval) {
    result |= anomap_getval;
    memcpy(val, map->vals.arr + map->vals.size * pos, map->vals.size);
  }

  if (operation & anomap_delete) {
    result |= anomap_delete;
    if (mpos < --map->map.len)
      memmove(map->map.arr + mpos, map->map.arr + mpos + 1,
              sizeof *map->map.arr * (map->map.len - mpos));
    map->map.arr[map->map.len] = pos;
  }
  return result;
}
