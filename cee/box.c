#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_box_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cee-internal.h"
#endif
#include "cee-header.h"

struct S(header) {
  enum cee_primitive_type type;
  struct cee_sect cs;
  union cee_primitive_value _[1];
};

static void S(del) (void * v) {
  struct S(header) * m = FIND_HEADER(v);
  free(m);
}

static int S(cmp) (void * v1, void * v2) {
  struct S(header) * h1 = FIND_HEADER(v1);
  struct S(header) * h2 = FIND_HEADER(v2);
  if (h1->cs.del == h2->cs.del)
    cee_segfault();
  else
    cee_segfault();
}


static struct S(header) * S(mk_header)(enum cee_primitive_type t) {
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * b = malloc(mem_block_size);
  ZERO_CEE_SECT(&b->cs);
  b->cs.del = S(del);
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->cs.cmp = NULL;
  b->cs.n_product = 0;
  b->type = t;
  b->_[0].u64 = 0;
  return b;
}

static int S(cmp_double)(double v1, double v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_double (double d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_f64);
  b->cs.cmp = S(cmp_double);
  b->_[0].f64 = d;
  return (struct cee_box *)b->_;
}

static int S(cmp_float)(float v1, float v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_float (float d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_f32);
  b->cs.cmp = S(cmp_float);
  b->_[0].f32 = d;
  return (struct cee_box *)b->_;
}

static int S(cmp_u64)(uint64_t v1, uint64_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_u64 (uint64_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_u64);
  b->_[0].u64 = d;
  return (struct cee_box *)b->_;
}

static int S(cmp_u32)(uint32_t v1, uint32_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_u32 (uint32_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_u32);
  b->cs.cmp = S(cmp_u32);
  b->_[0].u32 = d;
  return (struct cee_box *)b->_;
}


static int S(cmp_u16)(uint16_t v1, uint16_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_u16 (uint16_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_u16);
  b->cs.cmp = S(cmp_u16);
  b->_[0].u16 = d;
  return (struct cee_box *)b->_;
}


static int S(cmp_u8)(uint8_t v1, uint8_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_u8 (uint8_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_u8);
  b->cs.cmp = S(cmp_u8);
  b->_[0].u8 = d;
  return (struct cee_box *)b->_;
}


static int S(cmp_i64)(int64_t v1, int64_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_i64 (int64_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_i64);
  b->cs.cmp = S(cmp_i64);
  b->_[0].i64 = d;
  return (struct cee_box *)b->_;
}

static int S(cmp_i32)(int32_t v1, int32_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_i32 (int32_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_i32);
  b->cs.cmp = S(cmp_i32);
  b->_[0].i32 = d;
  return (struct cee_box *)b->_;
}

static int S(cmp_i16)(int16_t v1, int16_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_i16 (int16_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_i16);
  b->cs.cmp = S(cmp_i16);
  b->_[0].i16 = d;
  return (struct cee_box *)b->_;
}

static int S(cmp_i8)(int8_t v1, int8_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else 
    return -1;
}

struct cee_box * cee_box_i8 (int8_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct S(header) * b = S(mk_header)(cee_primitive_i8);
  b->cs.cmp = S(cmp_i8);
  b->_[0].i8 = d;
  return (struct cee_box *)b->_;
}

size_t cee_box_snprintf (char * buf, size_t size, struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  int s;
  switch(h->type)
  {
    case cee_primitive_f64:
      s = snprintf(buf, size, "%lf", h->_[0].f64);
      break;
    case cee_primitive_f32:
      s = snprintf(buf, size, "%f", h->_[0].f32);
      break;
    case cee_primitive_i64:
      s = snprintf(buf, size, "%lld", h->_[0].i64);
      break;
    case cee_primitive_u32:
    case cee_primitive_u16:
    case cee_primitive_u8:
      s = snprintf(buf, size, "%u", h->_[0].u32);
      break;
    case cee_primitive_u64:
      s = snprintf(buf, size, "%llu", h->_[0].u64);
      break;
    case cee_primitive_i32:
    case cee_primitive_i16:
    case cee_primitive_i8:
      s = snprintf(buf, size, "%d", h->_[0].i8);
      break;
    default:
      cee_segfault();
      break;
  }
  if (s > 0)
    return (size_t)s;
  else
    cee_segfault();    
}

double cee_box_as_double (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_f64)
    return h->_[0].f64;
  else
    cee_segfault();
}

float cee_box_as_float (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_f32)
    return h->_[0].f32;
  else
    cee_segfault();
}

uint64_t cee_box_as_u64 (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_u64)
    return h->_[0].u64;
  else
    cee_segfault();
}

uint32_t cee_box_as_u32 (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_u32)
    return h->_[0].u32;
  else
    cee_segfault();
}

uint16_t cee_box_as_u16 (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_u16)
    return h->_[0].u16;
  else
    cee_segfault();
}

uint8_t cee_box_as_u8 (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_u8)
    return h->_[0].u8;
  else
    cee_segfault();
}


int64_t cee_box_as_i64 (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_i64)
    return h->_[0].i64;
  else
    cee_segfault();
}

int32_t cee_box_as_i32 (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_i32)
    return h->_[0].i32;
  else
    cee_segfault();
}

int16_t cee_box_as_i16 (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_i16)
    return h->_[0].i16;
  else
    cee_segfault();
}

int8_t cee_box_as_i8 (struct cee_box * x) {
  struct S(header) * h = FIND_HEADER(x);
  if (h->type == cee_primitive_i8)
    return h->_[0].i8;
  else
    cee_segfault();
}