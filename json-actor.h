#ifndef JSON_ACTOR_H
#define JSON_ACTOR_H
#include <stdarg.h>

/*
 *
 * json actor (injector or extractor) specification grammar
 *
 * <apath> := (key) | (key) <apath>
 *
 * <value> := true | false | null | <int> | <float> | <string-literal>
 *            | <composite-value> | <actor>
 *
 * <actor> := d | ld | lld | f | lf | b | <size-specifier>s
 *            | F | F_nullable | T | L
 *
 * <apath-value> := <apath> : <value>
 *
 * <composite-value> :=  { <apath-value>* } <existence>?
 *                   | [ <value> ]  <existence>?
 *
 * <existence> := <size-specifier>@
 *
 * <size-specifier> := <integer> | .* | ? | epsilon
 *
 * examples:
 *
 * json_extractor(pos, size, "{ (key) : d, (key) : .*s }", &i)
 *
 * int ** list;
 * json_extractor(pos, size, "[ d ]", &list)*
 *
 *
 * json_injector(pos, size, "{  (key) : d, (key) : /abc/ }", i);
 *
 *
 */

extern int
json_injector_alloc (
  char ** buf_p,
  size_t * size_p,
  char * injection_spec, ...);

extern int json_injector (
  char * pos,
  size_t size,
  char * injection_spec,
  ...);

extern int
json_injector_va_list(
  char * pos,
  size_t size,
  char * injection_spec,
  va_list ap);

#endif //JSON_ACTOR_H
