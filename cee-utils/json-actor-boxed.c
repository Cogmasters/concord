#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "ntl.h"
#include "json-actor-boxed.h"
#include "json-actor.h"

void ja_str_from_json(char * json, size_t len, ja_str * ja)
{
  ja->value = malloc(len + 1);
  memcpy(ja->value, json, len);
  ja->value[len] = 0;
}

void ja_str_cleanup(ja_str *p) {
  if (p->value)
    free(p->value);
}

void ja_str_cleanup_v(void *p) {
  ja_str_cleanup((ja_str *)p);
}

void ja_str_init(ja_str *p) {
  memset(p, 0, sizeof(*p));
}
void ja_str_init_v(void *p) {
  ja_str_init((ja_str *)p);
}

void ja_str_from_json_v(char *json, size_t len, void *p) {
  ja_str_from_json(json, len, (ja_str *)p);
}

size_t ja_str_to_json(char *json, size_t len, ja_str *p) {
  return snprintf(json, len, "\"%s\"", p->value);
}
size_t ja_str_to_json_v(char *json, size_t len, void *p) {
  return ja_str_to_json(json, len, (ja_str *)p);
}

size_t ja_str_to_query(char *json, size_t len, ja_str *p) {
  return snprintf(json, len, "\"%s\"", p->value);
}

size_t ja_str_to_query_v(char *json, size_t len, void *p) {
  return ja_str_to_query(json, len, (ja_str *)p);
}

void ja_str_list_free(ja_str **p) {
  ntl_free((ntl_t)p, &ja_str_cleanup_v);
}

void ja_str_list_free_v(void **p) {
  ja_str_list_free((ja_str **)p);
}

void ja_str_list_from_json(char *str, size_t len, ja_str ***p) {
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(ja_str);
  d.init_elem = ja_str_init_v;
  d.elem_from_buf = ja_str_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

void ja_str_list_from_json_v(char *str, size_t len, void *p) {
  ja_str_list_from_json(str, len, (ja_str ***)p);
}

size_t ja_str_list_to_json(char *str, size_t len, ja_str **p) {
  return ntl_to_buf(str, len, (void **)p, NULL, ja_str_to_json_v);
}

size_t ja_str_list_to_json_v(char *str, size_t len, void *p) {
  return ja_str_list_to_json(str, len, (ja_str **)p);
}

void ja_str_use_default_inject_settings(ja_str *p) {
  return;
}


void ja_u64_from_json(char * json, size_t len, ja_u64 * ja)
{
  ja->value = strtoull(json, NULL, 10);
}

size_t ja_u64_to_json(char * json, size_t len, ja_u64 * ja)
{
  int ret =  snprintf(json, len, "\"%"PRIu64"\"", ja->value);
  return (size_t)ret;
}

size_t ja_u64_to_query(char *json, size_t len, ja_u64 *p) {
  return snprintf(json, len, "\"%"PRIu64"\"", p->value);
}

void ja_u64_init(ja_u64 *p) {
  p->value = 0;
}

void ja_u64_cleanup(ja_u64 *p) {
  return;
}

void ja_u64_cleanup_v(void *p) {
}

void ja_u64_init_v(void *p) {
  ja_u64_init((ja_u64 *)p);
}

void ja_u64_from_json_v(char *json, size_t len, void *p) {
  ja_u64_from_json(json, len, (ja_u64 *)p);
}

size_t ja_u64_to_json_v(char *json, size_t len, void *p) {
  return ja_u64_to_json(json, len, (ja_u64 *)p);
}


size_t ja_u64_to_query_v(char *json, size_t len, void *p) {
  return ja_u64_to_query(json, len, (ja_u64 *)p);
}

void ja_u64_list_free(ja_u64 **p) {
  ntl_free((ntl_t)p, NULL);
}

void ja_u64_list_free_v(void **p) {
  ja_u64_list_free((ja_u64 **)p);
}

void ja_u64_list_from_json(char *str, size_t len, ja_u64 ***p) {
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(ja_u64);
  d.init_elem = ja_u64_init_v;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

void ja_u64_list_append(NTL_T(ja_u64) *ntl_p, uint64_t *u64_p) {
  ntl_append2((ntl_t *)ntl_p, sizeof(ja_u64), u64_p);
}

void ja_u64_list_from_json_v(char *str, size_t len, void *p) {
  ja_u64_list_from_json(str, len, (ja_u64 ***)p);
}

size_t ja_u64_list_to_json(char *str, size_t len, ja_u64 **p) {
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}

size_t ja_u64_list_to_json_v(char *str, size_t len, void *p) {
  return ja_u64_list_to_json(str, len, (ja_u64 **)p);
}

void ja_u64_use_default_inject_settings(ja_u64 *p) {
  return;
}
