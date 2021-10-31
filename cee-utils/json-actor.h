#ifndef JSON_ACTOR_H
#define JSON_ACTOR_H
#include <stdarg.h>
#include "ntl.h"

/*
 *
 * json actor (injector or extractor) specification grammar
 *
 * <injector> := <composite-value> <availability>?
 *               | <access-path-value-list> <availability>?
 *
 * <extractor> := <composite-value> <availability>?
 *                | <access-path-value-list> <availability>?
 *
 * <access-path> := (<key>) | (<key>) <access-path>
 *
 * <value> := true | false | null | <int> | <float> | <string-literal>
 *            | <composite-value> | <action>
 *
 * <action> := d | ld | lld | f | lf | b | <size-specifier>s
 *            | F | F_nullable | T | L
 *
 * <access-path-value> := <access-path> : <value>
 *
 * <access-path-value-list> := <access-path-value>
 *                            | <access-path-value> <access-path-value-list>
 *
 * <composite-value> :=  { <access-path-value-list> } | [ <value> ]
 *
 * <availability> := <size-specifier>@
 *
 * <size-specifier> := <integer> | .* | ? | epsilon
 *
 *
 * <builtin-action> := d | ld | lld | f | lf | b | <size-specifier>s
 *
 *  d:  corresponds to %d, it will inject to json as an int or extract data
 *  from a json value as an int
 *
 *  ld: corresponds to %ld
 *  lld: corresponds to %lld
 *
 *  f: corresponds to %f
 *  lf: corresponds to %lf
 *
 *  b: corresponds to %b
 *
 *  s: corresponds to %s, and it can be decorated with .*  and ?
 *  .*s: corresponds to %.*s
 *
 *  ?s: has not its counter part in printf format string, it tells the
 *     extract function to allocate sufficient memory for
 *     the extraction
 *
 *  T: only works for extractor, it will return the memory section that stores
 *  a json value
 *
 *  L: only works for extractor, it will return the memory sections that store
 *  each value of a json array
 *
 *
 * examples:
 *
 *
 * json_extract(pos, size, "{ (key) : d, (key) : .*s }", &i, &s)
 *
 * sized_buffer ** list;
 * json_extract(pos, size, "[ L ]", &list);
 *
 *
 * json_inject(pos, size, "{  (key) : d, (key) : |abc| }", i);
 *
 *
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct json_raw_value {
  /*struct sized_buffer buffer; */
  int type;
};
/*
 * This function will inject variadic parameters into an json
 * according to the specification `injector`
 *
 *
 * `pos` pointers to the memory address to stop the injected json
 * `size` is the size of the memory block that can be used to store the json
 *
 * `injector` specifies how the variadic parameters should be placed in
 * the injected json.
 *
 * `injector` is defined by the above BNF grammar
 *
 *
 * example:
 * json_inject(pos, size, "(key1) : d, (key2) : |abc|", &i);
 *
 *
 * the result is a json stored at pos
 *
 * { "key1": 10, "key2": "abc" }
 *
 * all variadic parameters of actions should be address
 *
 */
extern size_t json_inject (char * pos, size_t size, char * injector, ...);

/*
 * this function will allocate a sufficient memory block and then call
 * json_inject to inject json to the memory block
 */
extern size_t
json_ainject (char ** buf_p, char * injector, ...);

/*
 *
 */
extern size_t
json_vinject (char * pos, size_t size, char * injector, va_list ap);


extern size_t
json_extract (char * json, size_t size, char * extractor, ...);

extern size_t
json_vextract (char * json, size_t size, char * extractor, va_list ap);

extern char* 
json_string_escape(size_t *new_size, char *str, size_t old_size);
extern int 
json_string_unescape(char **new_str, size_t *new_size, char *str, size_t old_size);


extern size_t
query_inject(char *query, size_t size, char *injector, ...);

extern char* url_encode(char *str);
extern char*url_decode(char *str);

/*
 * the line and column in a text file
 * it will be used to generate more human
 * readable locations.
 */
struct line_and_column {
  int line;
  int column;
};

extern void
addr_to_lnc (char *json, size_t size, char *addr, struct line_and_column *ln);

void json_actor_strong_type(int b);

extern size_t extract_ntl_from_json(char *buf, size_t len, struct ntl_deserializer *ntl_deserializer);
extern size_t extract_ntl_from_json2(char *buf, size_t len, struct ntl_deserializer *ntl_deserializer);

extern int
json_to_sized_buffer_ntl
  (char *json, size_t size, NTL_T(struct sized_buffer) *p);



/* All of the possible json datatypes */
enum json_type {
    /* DATATYPE FLAGS */
    JSON_UNDEFINED        = 0,
    JSON_NULL             = 1 << 0,
    JSON_BOOLEAN          = 1 << 1,
    JSON_NUMBER           = 1 << 2,
    JSON_STRING           = 1 << 3,
    JSON_OBJECT           = 1 << 4,
    JSON_ARRAY            = 1 << 5,
    /* SUPERSET FLAGS */
    JSON_ANY              = JSON_NULL | JSON_BOOLEAN | JSON_NUMBER \
                             | JSON_STRING | JSON_OBJECT | JSON_ARRAY
};

/* forwarding, definition at json-parser.c */
typedef struct json_item_s json_item_t;

/* JSON INIT */
json_item_t *json_object(const char *key);
json_item_t *json_array(const char *key);
json_item_t *json_null(const char *key);
json_item_t *json_boolean(const char *key, _Bool boolean);
json_item_t *json_number(const char *key, long double number);
json_item_t *json_string(const char *key, char *string);

/* JSON DESTRUCTORS
 * clean up json item and global allocated keys */
void json_cleanup(json_item_t *item);


/* JSON DECODING
 * parse buffer and returns a json item */
json_item_t* json_parse(char *buffer, size_t len);
 
/* JSON ENCODING */
struct sized_buffer json_stringify(json_item_t *root, enum json_type type);

/* JSON UTILITIES */
size_t json_size(const json_item_t* item);
json_item_t* json_append(json_item_t *item, json_item_t *new_branch);
json_item_t* json_iter_next(json_item_t* item);
json_item_t* json_clone(json_item_t *item);
char* json_typeof(const json_item_t* item);
char *json_strdup(const json_item_t* item);
int json_typecmp(const json_item_t* item, const enum json_type type);
int json_keycmp(const json_item_t* item, const char *key);
int json_numcmp(const json_item_t* item, const long double number);

/* JSON GETTERS */
json_item_t* json_get_root(json_item_t* item);
json_item_t* json_get_child(json_item_t* item, const char *key);
json_item_t* json_get_sibling(const json_item_t* item, const char *key);
json_item_t* json_get_sibling_byindex(const json_item_t* item, const size_t relative_index);
json_item_t* json_get_parent(const json_item_t* item);
json_item_t* json_get_byindex(const json_item_t* item, const size_t index);
long json_get_index(const json_item_t* item, const char *key);
enum json_type json_get_type(const json_item_t* item);
char* json_get_key(const json_item_t* item);
_Bool json_get_boolean(const json_item_t* item);
char* json_get_string(const json_item_t* item, size_t *len);
long double json_get_number(const json_item_t* item);

/* JSON SETTERS */
json_item_t* json_set_boolean(json_item_t* item, _Bool boolean);
json_item_t* json_set_string(json_item_t* item, char *string);
json_item_t* json_set_number(json_item_t* item, long double number);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*JSON_ACTOR_H */
