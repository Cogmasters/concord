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

#ifndef JSCON_PUBLIC_H_
#define JSCON_PUBLIC_H_

#include <stddef.h>
#include <stdbool.h>


/* All of the possible jscon datatypes */
enum jscon_type {
    /* DATATYPE FLAGS */
    JSCON_UNDEFINED        = 0,
    JSCON_NULL             = 1 << 0,
    JSCON_BOOLEAN          = 1 << 1,
    JSCON_INTEGER          = 1 << 2,
    JSCON_DOUBLE           = 1 << 3,
    JSCON_STRING           = 1 << 4,
    JSCON_OBJECT           = 1 << 5,
    JSCON_ARRAY            = 1 << 6,
    /* SUPERSET FLAGS */
    JSCON_NUMBER           = JSCON_INTEGER | JSCON_DOUBLE,
    JSCON_ANY              = JSCON_NULL | JSCON_BOOLEAN | JSCON_NUMBER \
                             | JSCON_STRING | JSCON_OBJECT | JSCON_ARRAY,
};


/* forwarding, definition at jscon-common.h */
typedef struct jscon_item_s jscon_item_t;
/* jscon_parser() callback */
typedef jscon_item_t* (jscon_cb)(jscon_item_t*);


/* JSCON INIT */
jscon_item_t *jscon_object(const char *key);
jscon_item_t *jscon_array(const char *key);
jscon_item_t *jscon_null(const char *key);
jscon_item_t *jscon_boolean(const char *key, bool boolean);
jscon_item_t *jscon_integer(const char *key, long long i_number);
jscon_item_t *jscon_double(const char *key, double number);
jscon_item_t *jscon_number(const char *key, double d_number);
jscon_item_t *jscon_string(const char *key, char *string);

/* JSCON DESTRUCTORS
 * clean up jscon item and global allocated keys */
void jscon_destroy(jscon_item_t *item);

/* JSCON DECODING
 * parse buffer and returns a jscon item */
jscon_item_t* jscon_parse(char *buffer);
jscon_cb* jscon_parse_cb(jscon_cb *new_cb);
/* only parse json values from given parameters */
void jscon_scanf(char *buffer, char *format, ...);
 
/* JSCON ENCODING */
char* jscon_stringify(jscon_item_t *root, enum jscon_type type);

/* JSCON UTILITIES */
size_t jscon_size(const jscon_item_t* item);
jscon_item_t* jscon_append(jscon_item_t *item, jscon_item_t *new_branch);
jscon_item_t* jscon_dettach(jscon_item_t *item);
void jscon_delete(jscon_item_t *item, const char *key);
jscon_item_t* jscon_iter_composite_r(jscon_item_t *item, jscon_item_t **p_current_item);
jscon_item_t* jscon_iter_next(jscon_item_t* item);
jscon_item_t* jscon_clone(jscon_item_t *item);
char* jscon_typeof(const jscon_item_t* item);
char* jscon_strdup(const jscon_item_t* item);
char* jscon_strcpy(char *dest, const jscon_item_t* item);
int jscon_typecmp(const jscon_item_t* item, const enum jscon_type type);
int jscon_keycmp(const jscon_item_t* item, const char *key);
int jscon_doublecmp(const jscon_item_t* item, const double d_number);
int jscon_intcmp(const jscon_item_t* item, const long long i_number);

/* JSCON GETTERS */
jscon_item_t* jscon_get_root(jscon_item_t* item);
jscon_item_t* jscon_get_branch(jscon_item_t* item, const char *key);
jscon_item_t* jscon_get_sibling(const jscon_item_t* item, const size_t relative_index);
jscon_item_t* jscon_get_parent(const jscon_item_t* item);
jscon_item_t* jscon_get_byindex(const jscon_item_t* item, const size_t index);
long jscon_get_index(const jscon_item_t* item, const char *key);
enum jscon_type jscon_get_type(const jscon_item_t* item);
char* jscon_get_key(const jscon_item_t* item);
bool jscon_get_boolean(const jscon_item_t* item);
char* jscon_get_string(const jscon_item_t* item);
double jscon_get_double(const jscon_item_t* item);
long long jscon_get_integer(const jscon_item_t* item);

/* JSCON SETTERS */
bool jscon_set_boolean(jscon_item_t* item, bool boolean);
char* jscon_set_string(jscon_item_t* item, char *string);
double jscon_set_double(jscon_item_t* item, double d_number);
long long jscon_set_integer(jscon_item_t* item, long long i_number);

#endif
