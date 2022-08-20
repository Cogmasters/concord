// MIT License
// Copyright (c) 2022 Anotra
// https://github.com/Anotra/anomap

#pragma once

#ifndef ANOMAP_H
#define ANOMAP_H

#include <stddef.h>
#include <stdbool.h>

enum anomap_operation {
  anomap_insert = 1 << 0,
  anomap_update = 1 << 1,
  anomap_upsert = anomap_insert | anomap_update,
  anomap_delete = 1 << 2,
  anomap_getval = 1 << 3,
};

struct anomap;

struct anomap *anomap_create(size_t key_size, size_t val_size,
                             int (*cmp)(const void *, const void *));

void anomap_destroy(struct anomap *map);

size_t anomap_length(struct anomap *map);

bool anomap_index_of(struct anomap *map, size_t *index, void *key);

bool anomap_at_index(struct anomap *map, size_t index, void *key, void *val);

enum anomap_operation anomap_do(struct anomap *map,
                                enum anomap_operation operation,
                                void *key, void *val);

#endif // !ANOMAP_H
