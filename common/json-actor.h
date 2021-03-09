#ifndef JSON_ACTOR_H
#define JSON_ACTOR_H
#include <stdarg.h>

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
#endif // __cplusplus

struct json_raw_value {
  //struct sized_buffer buffer;
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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //JSON_ACTOR_H
