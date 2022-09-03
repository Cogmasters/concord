
// MIT License
// Copyright (c) 2022 Anotra
// https://github.com/Anotra/priority_queue

#pragma once

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdlib.h>

typedef struct priority_queue priority_queue;
typedef unsigned priority_queue_id;

typedef enum {
  priority_queue_min = 0,
  priority_queue_max = 1,
} priority_queue_flags;

priority_queue *priority_queue_create(
  size_t key_size, size_t val_size,
  int(*cmp)(const void *a, const void *b),
  priority_queue_flags flags);

void priority_queue_destroy(priority_queue *queue);

size_t priority_queue_length(priority_queue *queue);

void priority_queue_set_max_capacity(
  priority_queue *queue,
  size_t capacity);

priority_queue_id priority_queue_push(
  priority_queue *queue,
  void *key, void *val);

priority_queue_id priority_queue_peek(
  priority_queue *queue,
  void *key, void *val);

priority_queue_id priority_queue_pop(
  priority_queue *queue,
  void *key, void *val);

priority_queue_id priority_queue_get(
  priority_queue *queue,
  priority_queue_id id,
  void *key, void *val);

int priority_queue_del(
  priority_queue *queue,
  priority_queue_id id);

int priority_queue_update(priority_queue *queue,
  priority_queue_id id,
  void *key, void *val);

#endif //! PRIORITY_QUEUE_H
