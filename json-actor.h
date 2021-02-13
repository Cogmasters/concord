#ifndef JSON_ACTOR_H
#define JSON_ACTOR_H
#include <stdarg.h>

/*
 *
 * json actor (injector or extractor) grammar
 *
 * <injector> := <composite-value>
 *               | <access-path-value-list> <existence>?
 *
 * <extractor> := <composite-value>
 *                | <access-path-value-list> <existence>?
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
 * <composite-value> :=  { <access-path-value-list> } <existence>?
 *                   | [ <value> ]  <existence>?
 *
 * <existence> := <size-specifier>@
 *
 * <size-specifier> := <integer> | .* | ? | epsilon
 *
 *
 * examples:
 *
 * json_extractor(pos, size, "{ (key) : d, (key) : .*s }", &i)
 *
 * sized_buffer ** list;
 * json_extractor(pos, size, "[ L ]", &list);
 *
 *
 * json_injector(pos, size, "{  (key) : d, (key) : |abc| }", i);
 *
 *
 */

extern int
json_inject_alloc (
  char ** buf_p,
  size_t * size_p,
  char * injector, ...);

extern int json_inject (
  char * pos,
  size_t size,
  char * injector,
  ...);

extern int
json_inject_va_list(
  char * pos,
  size_t size,
  char * injector,
  va_list ap);

#endif //JSON_ACTOR_H
