
// MIT License
// Copyright (c) 2022 Anotra
// https://github.com/Anotra/priority_queue

#include <inttypes.h>
#include <string.h>

#include "priority_queue.h"

#define queue_CMP(result, queue, a, b)         \
  do {                                         \
    result = queue->cmp(a, b);                 \
    if (queue->max_queue) {                    \
      switch (result) {                        \
        case -1: result =  1; break;           \
        case  0: result =  0; break;           \
        case  1: result = -1; break;           \
        default: result = result > 0 ? -1 : 1; \
      }                                        \
    }                                          \
  } while (0)

struct priority_queue {
  struct {
    priority_queue_id *arr;
    size_t cap;
    size_t len;
  } queue;
  struct {
    struct {
      priority_queue_id position;
    } *info;
    struct {
      char *arr;
      size_t size;
    } keys;
    struct {
      char *arr;
      size_t size;
    } vals;
    size_t cap;
    size_t len;
    size_t max;
  } elements;
  int(*cmp)(const void *a, const void *b);
  int max_queue;
  priority_queue_id scan_start;
};

priority_queue *
priority_queue_create(
  size_t key_size, size_t val_size,
  int(*cmp)(const void *a, const void *b),
  priority_queue_flags flags)
{
  priority_queue *queue = calloc(1, sizeof *queue);
  if (queue) {
    if (flags & priority_queue_max)
      queue->max_queue = 1;
    queue->elements.keys.size = key_size;
    queue->elements.vals.size = val_size;
    queue->elements.max = UINT32_MAX - 2;
    queue->cmp = cmp;
    queue->queue.len = 1;
    queue->queue.arr = calloc((queue->queue.cap = 0x400), sizeof *queue->queue.arr);
    if (queue->queue.arr)
      return queue;
    free(queue);
  }
  return NULL;
}


void
priority_queue_destroy(priority_queue *queue) {
  free(queue->queue.arr);
  free(queue->elements.info);
  free(queue->elements.keys.arr);
  free(queue->elements.vals.arr);
  free(queue);
}

size_t
priority_queue_length(priority_queue *queue) {
  return queue->queue.len - 1;
}

void
priority_queue_set_max_capacity(priority_queue *queue, size_t capacity) {
  queue->elements.max = capacity;
}

static void
priority_queue_swap(
  priority_queue *queue,
  priority_queue_id a, priority_queue_id b)
{
  priority_queue_id ai = queue->queue.arr[a];
  priority_queue_id bi = queue->queue.arr[b];
  queue->queue.arr[a] = bi;
  queue->queue.arr[b] = ai;
  queue->elements.info[ai].position = b;
  queue->elements.info[bi].position = a;
}

static void
priority_queue_bubble_down(priority_queue *queue, priority_queue_id pos) {
  const size_t key_size = queue->elements.keys.size;
  while (pos < queue->queue.len) {
    priority_queue_id lchild =  pos << 1;
    priority_queue_id rchild = (pos << 1) + 1;

    if (lchild >= queue->queue.len)
      return;

    priority_queue_id successor = lchild;

    int cmp = -1;
    if (rchild < queue->queue.len) {
      queue_CMP(cmp, queue,
        queue->elements.keys.arr + key_size * queue->queue.arr[lchild],
        queue->elements.keys.arr + key_size * queue->queue.arr[rchild]);
      if (cmp >= 0)
        successor = rchild;
    }
    
    queue_CMP(cmp, queue,
      queue->elements.keys.arr + key_size * queue->queue.arr[pos],
      queue->elements.keys.arr + key_size * queue->queue.arr[successor]);
    if (cmp <= 0)
      return;
    priority_queue_swap(queue, pos, successor);
    pos = successor;
  }
}

static void
priority_queue_bubble_up(priority_queue *queue, priority_queue_id pos) {
  while (pos > 1) {
    priority_queue_id par = pos >> 1;
    priority_queue_id par_index = queue->queue.arr[par];
    priority_queue_id pos_index = queue->queue.arr[pos];

    int cmp;
    queue_CMP(cmp, queue,
      queue->elements.keys.arr + queue->elements.keys.size * par_index,
      queue->elements.keys.arr + queue->elements.keys.size * pos_index);
    if (cmp < 0)
      return;
    priority_queue_swap(queue, par, pos);
    pos = par;
  }
}

priority_queue_id
priority_queue_push(priority_queue *queue, void *key, void *val) {
  if (!key)
    return 0;
  if (priority_queue_length(queue) >= queue->elements.max)
    return 0;

  if (queue->elements.len == queue->elements.cap) {
    size_t cap = queue->elements.cap ? queue->elements.cap << 1 : 0x40;
    if (cap > queue->elements.max)
      cap = queue->elements.max;
    if (cap > queue->elements.max)
      return 0;
    void *tmp;

    tmp = realloc(queue->elements.info, cap * sizeof *queue->elements.info);
    if (!tmp) return 0;
    if (queue->elements.info) {
      memset(tmp + queue->elements.cap * sizeof *queue->elements.info,
             0, (cap - queue->elements.cap) * sizeof *queue->elements.info);
    } else {
      memset(tmp, 0, cap * sizeof *queue->elements.info);
    }
    queue->elements.info = tmp;

    tmp = realloc(queue->elements.keys.arr, queue->elements.keys.size * cap);
    if (!tmp) return 0;
    queue->elements.keys.arr = tmp;
    
    if (queue->elements.vals.size) {
      tmp = realloc(queue->elements.vals.arr, queue->elements.vals.size * cap);
      if (!tmp) return 0;
      queue->elements.vals.arr = tmp;
    }

    queue->elements.cap = cap;
  }

  if (queue->queue.len == queue->queue.cap) {
    size_t cap = queue->queue.cap << 1;
    void *tmp = realloc(queue->queue.arr, cap * sizeof *queue->queue.arr);
    if (!tmp) return 0;
    queue->queue.arr = tmp;
    queue->queue.cap = cap;
  }

  priority_queue_id id = queue->scan_start;
  for (; queue->elements.info[id].position; id++);
  queue->elements.len++;
  queue->scan_start = id + 1;

  memcpy(queue->elements.keys.arr + queue->elements.keys.size * id,
         key, queue->elements.keys.size);

  if (queue->elements.vals.size) {
    if (val) {
      memcpy(queue->elements.vals.arr + queue->elements.vals.size * id,
             val, queue->elements.vals.size);
    } else {
      memset(queue->elements.vals.arr + queue->elements.vals.size * id,
             0, queue->elements.vals.size);
    }
  }
  priority_queue_id pos = queue->queue.len++;
  queue->queue.arr[pos] = id;
  queue->elements.info[id].position = pos;
  priority_queue_bubble_up(queue, pos);

  return id + 1;
}

priority_queue_id
priority_queue_peek(priority_queue *queue, void *key, void *val) {
  if (queue->queue.len == 1)
    return 0;
  priority_queue_id pos = queue->queue.arr[1];
  if (key)
    memcpy(key, queue->elements.keys.arr + queue->elements.keys.size * pos,
           queue->elements.keys.size);
  if (val && queue->elements.vals.size)
    memcpy(val, queue->elements.vals.arr + queue->elements.vals.size * pos,
           queue->elements.vals.size);
  return pos + 1;
}

priority_queue_id
priority_queue_pop(priority_queue *queue, void *key, void *val) {
  priority_queue_id id = priority_queue_peek(queue, key, val);
  if (id) priority_queue_del(queue, id);
  return id;
}


priority_queue_id
priority_queue_get(
  priority_queue *queue,
  priority_queue_id id,
  void *key, void *val) {
  id--;
  if (id >= queue->elements.len || !queue->elements.info[id].position)
    return 0;
  priority_queue_id pos = queue->queue.arr[queue->elements.info[id].position];
  if (key)
    memcpy(key, queue->elements.keys.arr + queue->elements.keys.size * pos,
           queue->elements.keys.size);
  if (val && queue->elements.vals.size)
    memcpy(val, queue->elements.vals.arr + queue->elements.vals.size * pos,
           queue->elements.vals.size);
  return id + 1;
}

int
priority_queue_del(priority_queue *queue, priority_queue_id id) {
  if (queue->queue.len == 1)
    return 0;
  id--;
  if (id >= queue->elements.len || !queue->elements.info[id].position)
    return 0;
  if (queue->scan_start > id)
    queue->scan_start = id;
  priority_queue_id pos = queue->elements.info[id].position;
  priority_queue_swap(queue, pos, --queue->queue.len);
  queue->elements.info[queue->queue.arr[queue->queue.len]].position = 0;
  priority_queue_bubble_up(queue, pos);
  priority_queue_bubble_down(queue, pos);
  return 1;
}

int
priority_queue_update(
  priority_queue *queue, priority_queue_id id,
  void *key, void *val)
{
  if (queue->queue.len == 1)
    return 0;
  id--;
  if (id >= queue->elements.len || !queue->elements.info[id].position)
    return 0;
  memcpy(queue->elements.keys.arr + queue->elements.keys.size * id,
         key, queue->elements.keys.size);

  if (queue->elements.vals.size) {
    if (val) {
      memcpy(queue->elements.vals.arr + queue->elements.vals.size * id,
             val, queue->elements.vals.size);
    } else {
      memset(queue->elements.vals.arr + queue->elements.vals.size * id,
             0, queue->elements.vals.size);
    }
  }
  priority_queue_id pos = queue->elements.info[id].position;
  priority_queue_bubble_up(queue, pos);
  priority_queue_bubble_down(queue, pos);
  return 1;
}
