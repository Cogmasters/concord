/*
 * Copyright (c) 2020 Lucas Müller
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef JSCON_COMMON_H_
#define JSCON_COMMON_H_

#include <limits.h>

/* #include <libjscon.h> (implicit) */
//#include "hashtable.h"


#define DEBUG_MODE 1

#define JSCON_VERSION "0.0"

#define MAX_INTEGER_DIG 20 /* ULLONG_MAX maximum amt of digits possible */

typedef enum jscon_errcode
{
/* JSCON EXTERNAL ERRORS */

    JSCON_EXT__OUT_MEM              = 0,
    JSCON_EXT__INVALID_TOKEN        = 50,
    JSCON_EXT__INVALID_STRING,
    JSCON_EXT__INVALID_BOOLEAN,
    JSCON_EXT__INVALID_NUMBER,
    JSCON_EXT__INVALID_COMPOSITE,
    JSCON_EXT__NOT_STRING           = 100,
    JSCON_EXT__NOT_BOOLEAN,
    JSCON_EXT__NOT_NUMBER,
    JSCON_EXT__NOT_COMPOSITE,
    JSCON_EXT__EMPTY_FIELD          = 200,

/* JSCON INTERNAL ERRORS */

    JSCON_INT__NOT_FREED        = -1,
    JSCON_INT__OVERFLOW         = -50,
} jscon_errcode;

/* this allocates memory dynamically, should only be used for printing
 *  exception error messages */
char *__jscon_strerror(jscon_errcode code, char codetag[], void *where, char entity[]);
#define jscon_strerror(code, where) __jscon_strerror(code, #code, where, #where)

#define STREQ(s,t) (0 == strcmp(s,t))
#define STRNEQ(s,t,n) (0 == strncmp(s,t,n))

#define IN_RANGE(n,lo,hi) (((n) > (lo)) && ((n) < (hi)))

#define DOUBLE_IS_INTEGER(d) \
    ((d) <= LLONG_MIN || (d) >= LLONG_MAX || (d) == (long long)(d))

#define IS_BLANK_CHAR(c) (isspace(c) || iscntrl(c))
#define CONSUME_BLANK_CHARS(str) for( ; IS_BLANK_CHAR(*str) ; ++str)

#define IS_COMPOSITE(item) ((item) && jscon_typecmp(item, JSCON_OBJECT|JSCON_ARRAY))
#define IS_EMPTY_COMPOSITE(item) (IS_COMPOSITE(item) && 0 == jscon_size(item))
#define IS_PRIMITIVE(item) ((item) && !jscon_typecmp(item, JSCON_OBJECT|JSCON_ARRAY))
#define IS_PROPERTY(item) (jscon_typecmp(item->parent, JSCON_OBJECT))
#define IS_ELEMENT(item) (jscon_typecmp(item->parent, JSCON_ARRAY))
#define IS_LEAF(item) (IS_PRIMITIVE(item) || IS_EMPTY_COMPOSITE(item))
#define IS_ROOT(item) (NULL == item->parent)

  
#if 0
/* JSCON COMPOSITE STRUCTURE
 *  if jscon_item type is of composite type (object or array) it will
 *  include a jscon_composite_t struct with the following attributes:
 *      branch: for sorting through object's properties/array elements
 *      num_branch: amount of enumerable properties/elements contained
 *      last_accessed_branch: simulate stack trace by storing the last
 *          accessed branch address. this is used for movement 
 *          functions that require state to be preserved between 
 *          calls, while also adhering to tree traversal rules. 
 *          (check public.c jscon_iter_next() for example)
 *      hashtable: easy reference to its key-value pairs
 *      p_item: reference to the item the composite is part of
 *      next: points to next composite
 *      prev: points to previous composite */
typedef struct jscon_composite_s {
    struct jscon_item_s **branch;
    size_t num_branch;
    size_t last_accessed_branch;

    struct hashtable_s *hashtable;
    struct jscon_item_s *p_item;
    struct jscon_composite_s *next;
    struct jscon_composite_s *prev;
} jscon_composite_t;


void Jscon_composite_link_r(struct jscon_item_s *item, jscon_composite_t **last_accessed_comp);
void Jscon_composite_build(struct jscon_item_s *item);
struct jscon_item_s* Jscon_composite_get(const char *key, struct jscon_item_s *item);
struct jscon_item_s* Jscon_composite_set(const char *key, struct jscon_item_s *item);
void Jscon_composite_remake(jscon_item_t *item);



/* JSCON ITEM STRUCTURE
 *  key: item's jscon key (NULL if root)
 *  parent: object or array that its part of (NULL if root)
 *  type: item's jscon datatype (check enum jscon_type_e for flags) 
 *  union {string, d_number, i_number, boolean, comp}:
 *      string,d_number,i_number,boolean: item literal value, denoted 
 *      by its type.  */
typedef struct jscon_item_s {
    union {
        char *string;
        double d_number;
        long long i_number;
        bool boolean;
        jscon_composite_t *comp;
    };
    enum jscon_type type;

    char *key;
    struct jscon_item_s *parent;
} jscon_item_t;
#endif

/*
 * jscon-common.c
 */
char* Jscon_decode_string(char **p_buffer);
void Jscon_decode_static_string(char **p_buffer, const long len, const long offset, char set_str[]);
double Jscon_decode_double(char **p_buffer);
bool Jscon_decode_boolean(char **p_buffer);
void Jscon_decode_null(char **p_buffer);
//jscon_composite_t* Jscon_decode_composite(char **p_buffer, size_t n_branch);


#endif
