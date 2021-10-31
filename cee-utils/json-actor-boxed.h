#ifndef JSON_ACTOR_BOXED_H
#define JSON_ACTOR_BOXED_H
#include <stdint.h>
#include <stddef.h>
#include "ntl.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct ja_str
{
  char * value;
} ja_str; /* json-actor's boxed  built-in type */

typedef struct ja_u64
{
  uint64_t value;
} ja_u64; /* json-actor's boxed built-in type */


void ja_str_cleanup_v(void *p);
void ja_str_cleanup(struct ja_str *p);
void ja_str_init_v(void *p);
void ja_str_init(struct ja_str *p);
void ja_str_from_json_v(char *json, size_t len, void *p);
void ja_str_from_json(char *json, size_t len, struct ja_str *p);
size_t ja_str_to_json_v(char *json, size_t len, void *p);
size_t ja_str_to_json(char *json, size_t len, struct ja_str *p);
size_t ja_str_to_query_v(char *json, size_t len, void *p);
size_t ja_str_to_query(char *json, size_t len, struct ja_str *p);
void ja_str_list_free_v(void **p);
void ja_str_list_free(struct ja_str **p);
void ja_str_list_from_json_v(char *str, size_t len, void *p);
void ja_str_list_from_json(char *str, size_t len, struct ja_str ***p);
size_t ja_str_list_to_json_v(char *str, size_t len, void *p);
size_t ja_str_list_to_json(char *str, size_t len, struct ja_str **p);
void ja_str_use_default_inject_settings(struct ja_str *p);

void ja_u64_cleanup_v(void *p);
void ja_u64_cleanup(struct ja_u64 *p);
void ja_u64_init_v(void *p);
void ja_u64_init(struct ja_u64 *p);
void ja_u64_from_json_v(char *json, size_t len, void *p);
void ja_u64_from_json(char *json, size_t len, struct ja_u64 *p);
size_t ja_u64_to_json_v(char *json, size_t len, void *p);
size_t ja_u64_to_json(char *json, size_t len, struct ja_u64 *p);
size_t ja_u64_to_query_v(char *json, size_t len, void *p);
size_t ja_u64_to_query(char *json, size_t len, struct ja_u64 *p);
void ja_u64_list_free_v(void **p);
void ja_u64_list_free(struct ja_u64 **p);
void ja_u64_list_append(NTL_T(ja_u64) *ntl_p, uint64_t *new_p);
void ja_u64_list_from_json_v(char *str, size_t len, void *p);
void ja_u64_list_from_json(char *str, size_t len, struct ja_u64 ***p);
size_t ja_u64_list_to_json_v(char *str, size_t len, void *p);
size_t ja_u64_list_to_json(char *str, size_t len, struct ja_u64 **p);
void ja_u64_use_default_inject_settings(struct ja_u64 *p);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*JSON_ACTOR_BOXED_H */
