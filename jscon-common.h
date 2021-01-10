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

/*
 * jscon-common.c
 */

char* Jscon_decode_string(char **p_buffer);
void Jscon_decode_static_string(char **p_buffer, const long len, const long offset, char set_str[]);
double Jscon_decode_double(char **p_buffer);
bool Jscon_decode_boolean(char **p_buffer);
void Jscon_decode_null(char **p_buffer);
size_t strscpy(char *dest, const char *src, size_t n);


#endif
