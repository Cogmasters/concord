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

#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h> /* for isfinite() */
#include <float.h> /* for DBL_DECIMAL_DIG */
#include <limits.h>
#ifndef DBL_DECIMAL_DIG
#define DBL_DECIMAL_DIG 17
#endif

#include "json-actor.h"
#include "cee-utils.h"

#define MAX_INTEGER_DIG 20 /* ULLONG_MAX maximum amt of digits possible */

#define IN_RANGE(n,lo,hi) (((n) > (lo)) && ((n) < (hi)))

#define DOUBLE_IS_INTEGER(d) \
    ((d) <= LLONG_MIN || (d) >= LLONG_MAX || (d) == (long long)(d))

#define IS_BLANK_CHAR(c) (isspace(c) || iscntrl(c))
#define CONSUME_BLANK_CHARS(str) for( ; IS_BLANK_CHAR(*str) ; ++str)

#define IS_COMPOSITE(item) ((item) && json_typecmp(item, JSON_OBJECT|JSON_ARRAY))
#define IS_EMPTY_COMPOSITE(item) (IS_COMPOSITE(item) && 0 == json_size(item))
#define IS_PRIMITIVE(item) ((item) && !json_typecmp(item, JSON_OBJECT|JSON_ARRAY))
#define IS_PROPERTY(item) (json_typecmp(item->parent, JSON_OBJECT))
#define IS_ELEMENT(item) (json_typecmp(item->parent, JSON_ARRAY))
#define IS_LEAF(item) (IS_PRIMITIVE(item) || IS_EMPTY_COMPOSITE(item))
#define IS_ROOT(item) (NULL == item->parent)


/* JSON COMPOSITE STRUCTURE
 *  if json_item type is of composite type (object or array) it will
 *  include a json_composite_t struct with the following attributes:
 *      branch: for sorting through object's properties/array elements
 *      num_branch: amount of enumerable properties/elements contained
 *      last_accessed_branch: simulate stack trace by storing the last
 *          accessed branch address. this is used for movement 
 *          functions that require state to be preserved between 
 *          calls, while also adhering to tree traversal rules. 
 *          (check public.c json_iter_next() for example)
 *      p_item: reference to the item the composite is part of */
typedef struct json_composite_s {
    struct json_item_s **branch;
    size_t num_branch;
    size_t last_accessed_branch;
    struct json_item_s *p_item;
} json_composite_t;

/* JSON ITEM STRUCTURE
 *  key: item's json key (NULL if root)
 *  parent: object or array that its part of (NULL if root)
 *  type: item's json datatype (check enum json_type_e for flags) 
 *  union {string, d_number, i_number, boolean, comp}:
 *      string,d_number,i_number,boolean: item literal value, denoted 
 *      by its type.  */
struct json_item_s {
    union {
        struct sized_buffer string;
        long double number;
        _Bool boolean;
        json_composite_t *comp;
    };
    enum json_type type;

    char *key;
    struct json_item_s *parent;
};

struct _parse_context {
    char *buffer;
    char *key; /* holds key ptr to be received by item */
};


/* function pointers used while building json items, 
    json_create_value points to functions prefixed by "_json_value_set_"
    json_create_item points to functions prefixed by "json_decode" */
typedef void (json_create_value)(json_item_t *item, struct _parse_context *cxt);
typedef json_item_t* (json_create_item)(json_item_t*, struct _parse_context*, json_create_value*);

static json_item_t*
_json_item_init()
{
    json_item_t *new_item = calloc(1, sizeof *new_item);
    ASSERT_S(NULL != new_item, "Out of memory");

    return new_item;
}

/* create a new branch to current json object item, and return
    the new branch address */
static json_item_t*
_json_branch_init(json_item_t *item)
{
    ++item->comp->num_branch;

    item->comp->branch[item->comp->num_branch-1] = _json_item_init();

    item->comp->branch[item->comp->num_branch-1]->parent = item;

    return item->comp->branch[item->comp->num_branch-1];
}

static void
_json_composite_cleanup(json_item_t *item)
{
    free(item->comp->branch);
    item->comp->branch = NULL;

    free(item->comp);
    item->comp = NULL;
}

static void
_json_preorder_cleanup(json_item_t *item)
{
    switch (item->type){
    case JSON_OBJECT:
    case JSON_ARRAY:
    {
        size_t i;
        for (i=0; i < item->comp->num_branch; ++i){
            _json_preorder_cleanup(item->comp->branch[i]);
        }
        _json_composite_cleanup(item);
        break;
    }
    case JSON_STRING:
        free(item->string.start);
        item->string.start = NULL;
        break;
    default:
        break;
    }

    if (NULL != item->key){
        free(item->key);
        item->key = NULL;
    }

    free(item);
    item = NULL;
}

/* cleanup current item and all of its nested object/arrays */
void
json_cleanup(json_item_t *item){
    _json_preorder_cleanup(json_get_root(item));
}

static json_composite_t*
_json_decode_composite(char **p_buffer, size_t n_branch){
    json_composite_t *new_comp = calloc(1, sizeof *new_comp);
    ASSERT_S(NULL != new_comp, "Out of memory");

    new_comp->branch = malloc((1+n_branch) * sizeof(json_item_t*));
    ASSERT_S(NULL != new_comp->branch, "Out of memory");

    ++*p_buffer; /* skips composite's '{' or '[' delim */

    return new_comp;
}

static char*
_json_decode_string(char **p_buffer, size_t *len)
{
    char *start = *p_buffer;
    ASSERT_S('\"' == *start, "Not a string");

    char *end = ++start;
    while (('\0' != *end) && ('\"' != *end)){
        if ('\\' == *end++){ /* skips escaped characters */
            ++end;
        }
    }
    ASSERT_S('\"' == *end, "Not a string");

    *p_buffer = end + 1;

    *len = end-start;
    char *str = NULL;
    asprintf(&str, "%.*s", (int)*len, start);
    ASSERT_S(NULL != str, "Out of memory");
    return str;
}

static long double
_json_decode_number(char **p_buffer)
{
    char *start = *p_buffer;
    char *end = start;

    /* 1st STEP: check for a minus sign and skip it */
    if ('-' == *end){
        ++end; /* skips minus sign */
    }

    /* 2nd STEP: skips until a non digit char found */
    ASSERT_S(isdigit(*end), "Not a number");
    while (isdigit(*++end))
        continue; /* skips while char is digit */

    /* 3rd STEP: if non-digit char is not a comma then it must be
        an integer*/
    if ('.' == *end){
        while (isdigit(*++end))
            continue;
    }

    /* 4th STEP: if exponent found skips its tokens */
    if (('e' == *end) || ('E' == *end)){
        ++end;
        if (('+' == *end) || ('-' == *end)){ 
            ++end;
        }
        ASSERT_S(isdigit(*end), "Not a number");
        while (isdigit(*++end))
            continue;
    }

    /* 5th STEP: convert string to number and return its value */
    char numstr[MAX_INTEGER_DIG];
    snprintf(numstr, MAX_INTEGER_DIG, "%.*s", (int)(end-start), start);

    *p_buffer = end; /* skips entire length of number */

    DS_PRINT("%.*s, %Ld", (int)(end-start), start, strtod(numstr, NULL));
    return strtod(numstr, NULL);
}

static bool
_json_decode_boolean(char **p_buffer)
{
    if ('t' == **p_buffer){
        *p_buffer += 4; /* skips length of "true" */
        return true;
    }
    *p_buffer += 5; /* skips length of "false" */
    return false;
}

static void
_json_decode_null(char **p_buffer){
    *p_buffer += 4; /* skips length of "null" */
}


/* fetch string type json and return allocated string */
static void
_json_value_set_string(json_item_t *item, struct _parse_context *cxt)
{
    item->type = JSON_STRING;

    size_t size = 0;
    char *str = _json_decode_string(&cxt->buffer, &size);

    char *unstr = NULL; /* unescape string */
    if (!json_string_unescape(&unstr, &item->string.size, str, size)) {
      ERR("(Internal Error) Cannot unescape an ill-formed-string %.*s", (int)size, str);
    }
    item->string.start = unstr;
}

/* fetch number json type by parsing string,
    find out whether its a integer or number and assign*/
static void
_json_value_set_number(json_item_t *item, struct _parse_context *cxt)
{
    item->type = JSON_NUMBER;
    item->number = _json_decode_number(&cxt->buffer);
}

static void
_json_value_set_boolean(json_item_t *item, struct _parse_context *cxt)
{
    item->type = JSON_BOOLEAN;
    item->boolean = _json_decode_boolean(&cxt->buffer);
}

static void
_json_value_set_null(json_item_t *item, struct _parse_context *cxt)
{
    item->type = JSON_NULL;
    _json_decode_null(&cxt->buffer);
}

static size_t
_json_count_property(char *buffer)
{
    /* skips the item and all of its nests, special care is taken for any
        inner string is found, as it might contain a delim character that
        if not treated as a string will incorrectly trigger 
        depth action*/
    size_t depth = 0;
    size_t num_branch = 0;
    do {
        switch (*buffer){
        case ':':
            num_branch += (depth == 1);
            break;
        case '{':
            ++depth;
            break;
        case '}':
            --depth;
            break;
        case '\"':
            /* loops until null terminator or end of string are found */
            do {
            /* skips escaped characters */
                if ('\\' == *buffer++){
                    ++buffer;
                }
            } while ('\0' != *buffer && '\"' != *buffer);
            ASSERT_S('\"' == *buffer, "Not a string");
            break;
        }

        ++buffer; /* skips whatever char */

        if (0 == depth) return num_branch; /* entire item has been skipped, return */

    } while ('\0' != *buffer);

    ERR("Bad formatting");
    abort();
}

static void
_json_value_set_object(json_item_t *item, struct _parse_context *cxt)
{
    item->type = JSON_OBJECT;

    item->comp = _json_decode_composite(&cxt->buffer, _json_count_property(cxt->buffer));
}

static size_t
_json_count_element(char *buffer)
{
    /* skips the item and all of its nests, special care is taken for any
        inner string is found, as it might contain a delim character that
        if not treated as a string will incorrectly trigger 
        depth action*/
    size_t depth = 0;
    size_t num_branch = 0;
    do {
        switch (*buffer){
        case ',':
            num_branch += (depth == 1);
            break;
        case '[':
            ++depth;
            break;
        case ']':
            --depth;
            break;
        case '\"':
        /* loops until null terminator or end of string are found */
            do {
                /* skips escaped characters */
                if ('\\' == *buffer++){
                    ++buffer;
                }
            } while ('\0' != *buffer && '\"' != *buffer);
            ASSERT_S('\"' == *buffer, "Not a string");
            break;
        }

        ++buffer; /* skips whatever char */

        if (0 == depth) return num_branch; /* entire item has been skipped, return */

    } while ('\0' != *buffer);

    ERR("Bad formatting");
    abort();
}

static void
_json_value_set_array(json_item_t *item, struct _parse_context *cxt)
{
    item->type = JSON_ARRAY;

    item->comp = _json_decode_composite(&cxt->buffer, _json_count_element(cxt->buffer));
}

/* create nested composite type (object/array) and return 
      the address. */
static json_item_t*
_json_composite_init(json_item_t *item, struct _parse_context *cxt, json_create_value *value_setter)
{
    item = _json_branch_init(item);
    item->key = cxt->key;
    cxt->key = NULL;

    (*value_setter)(item, cxt);

    return item;
}

/* wrap array or object type json, which means
      all of its branches have been created */
static json_item_t*
_json_wrap_composite(json_item_t *item, struct _parse_context *cxt)
{
    ++cxt->buffer; /* skips '}' or ']' */
    return item->parent;
}

/* create a primitive data type branch. */
static json_item_t*
_json_append_primitive(json_item_t *item, struct _parse_context *cxt, json_create_value *value_setter)
{
    item = _json_branch_init(item);
    item->key = cxt->key;
    cxt->key = NULL;

    (*value_setter)(item, cxt);

    return item->parent;
}

/* this routine is called when setting a branch of a composite type
      (object and array) item. */
static json_item_t*
_json_branch_build(json_item_t *item, struct _parse_context *cxt)
{
    json_create_item *item_setter;
    json_create_value *value_setter;

    switch (*cxt->buffer){
    case '{':/*OBJECT DETECTED*/
        item_setter = &_json_composite_init;
        value_setter = &_json_value_set_object;
        break;
    case '[':/*ARRAY DETECTED*/
        item_setter = &_json_composite_init;
        value_setter = &_json_value_set_array;
        break;
    case '\"':/*STRING DETECTED*/
        item_setter = &_json_append_primitive;
        value_setter = &_json_value_set_string;
        break;
    case 't':/*CHECK FOR*/
    case 'f':/* BOOLEAN */
        if (!STRNEQ(cxt->buffer,"true",4) && !STRNEQ(cxt->buffer,"false",5))
            goto token_error;

        item_setter = &_json_append_primitive;
        value_setter = &_json_value_set_boolean;
        break;
    case 'n':/*CHECK FOR NULL*/
        if (!STRNEQ(cxt->buffer,"null",4))
            goto token_error; 
        
        item_setter = &_json_append_primitive;
        value_setter = &_json_value_set_null;
        break;
    case '-': case '0': case '1': case '2': 
    case '3': case '4': case '5': case '6': 
    case '7': case '8': case '9':
        item_setter = &_json_append_primitive;
        value_setter = &_json_value_set_number;
        break;
    default:
        goto token_error;
    }

    return (*item_setter)(item, cxt, value_setter);


token_error:
    ERR("Invalid '%c' token", *cxt->buffer);
    abort();
}

/* this will be active if the current item is of array type json,
    whatever item is created here will be this array's property.
    if a ']' token is found then the array is wrapped up */
static json_item_t*
_json_array_build(json_item_t *item, struct _parse_context *cxt)
{
    CONSUME_BLANK_CHARS(cxt->buffer);
    switch (*cxt->buffer){
    case ']':/*ARRAY WRAPPER DETECTED*/
        return _json_wrap_composite(item, cxt);
    case ',': /*NEXT ELEMENT TOKEN*/
        ++cxt->buffer; /* skips ',' */
        CONSUME_BLANK_CHARS(cxt->buffer);
    /* fall through */
    default:
     {
        /* creates numerical key for the array element */
        char numkey[MAX_INTEGER_DIG];
        snprintf(numkey, MAX_INTEGER_DIG-1, "%zu", item->comp->num_branch);

        ASSERT_S(NULL == cxt->key, "Memory wasn't free'd");
        cxt->key = strdup(numkey);
        ASSERT_S(NULL != cxt->key, "Out of memory");

        return _json_branch_build(item, cxt);
     }
    }

    /* token error checking done inside _json_branch_build */
}

/* this will be active if the current item is of object type json,
    whatever item is created here will be this object's property.
    if a '}' token is found then the object is wrapped up */
static json_item_t*
_json_object_build(json_item_t *item, struct _parse_context *cxt)
{
    CONSUME_BLANK_CHARS(cxt->buffer);
    switch (*cxt->buffer){
    case '}':/*OBJECT WRAPPER DETECTED*/
        return _json_wrap_composite(item, cxt);
    case ',': /*NEXT PROPERTY TOKEN*/
        ++cxt->buffer; /* skips ',' */
        CONSUME_BLANK_CHARS(cxt->buffer);
    /* fall through */
    case '\"': { /*KEY STRING DETECTED*/
        ASSERT_S(NULL == cxt->key, "Memory wasn't free'd");
        size_t noop=0;
        cxt->key = _json_decode_string(&cxt->buffer, &noop);
        ASSERT_S(':' == *cxt->buffer, "Missing colon after key");
        ++cxt->buffer; /* skips ':' */
        CONSUME_BLANK_CHARS(cxt->buffer);
        return _json_branch_build(item, cxt); }
    default:
        if (!IS_BLANK_CHAR(*cxt->buffer))
            ERR("%s", "Unexpected token");

        CONSUME_BLANK_CHARS(cxt->buffer);
        return item;
    }
}

/* this call will only be used once, at the first iteration,
    it also allows the creation of a json that's not part of an
    array or object. ex: json_item_parse("10") */
static json_item_t*
_json_entity_build(json_item_t *item, struct _parse_context *cxt)
{
    CONSUME_BLANK_CHARS(cxt->buffer);

    switch (*cxt->buffer){
    case '{':/*OBJECT DETECTED*/
        _json_value_set_object(item, cxt);
        break;
    case '[':/*ARRAY DETECTED*/
        _json_value_set_array(item, cxt);
        break;
    case '\"':/*STRING DETECTED*/
        _json_value_set_string(item, cxt);
        break;
    case 't':/*CHECK FOR*/
    case 'f':/* BOOLEAN */
        if (!STRNEQ(cxt->buffer,"true",4) && !STRNEQ(cxt->buffer,"false",5))
            goto token_error;

        _json_value_set_boolean(item, cxt);
        break;
    case 'n':/*CHECK FOR NULL*/
        if (!STRNEQ(cxt->buffer,"null",4))
            goto token_error;

        _json_value_set_null(item, cxt);
        break;
    case '-': case '1': case '2': case '3': 
    case '4': case '5': case '6': case '7': 
    case '8': case '9':
        _json_value_set_number(item, cxt);
        break;
    default:
        goto token_error;

    }

    return item;


token_error:
    ERR("%s", "Unexpected token");
    abort(); 
}

/* parse contents from buffer into a json item object
    and return its root */
json_item_t*
json_parse(char *buffer, size_t len)
{
    json_item_t *root = calloc(1, sizeof *root);
    if (NULL == root) return NULL;

    struct _parse_context cxt = { .buffer = buffer, };
    
    /* build while item and buffer aren't nulled */
    json_item_t *item = root;
    while ((NULL != item) 
        && ((cxt.buffer - buffer) < len)
        && ('\0' != *cxt.buffer))
    {
        switch(item->type){
        case JSON_OBJECT:
            item = _json_object_build(item, &cxt);
            break;
        case JSON_ARRAY:
            item = _json_array_build(item, &cxt);
            break;
        case JSON_UNDEFINED: /* this should be true only at the first iteration */
            item = _json_entity_build(item, &cxt);

            if (IS_PRIMITIVE(item)) return item;

            break;
        default:
            ERR("Unknown type (code: %d)", item->type);
        }
    }

    return root;
}

static json_item_t*
_json_new(const char *key, enum json_type type)
{
    json_item_t *new_item = malloc(sizeof *new_item);
    if (NULL == new_item) return NULL;

    if (NULL != key){
        new_item->key = strdup(key);
        if (NULL == new_item->key){
            free(new_item);
            return NULL;
        }
    } else {
        new_item->key = NULL;
    }

    new_item->parent = NULL;
    new_item->type = type;

    return new_item;
}

json_item_t*
json_null(const char *key){
    return _json_new(key, JSON_NULL);
}

json_item_t*
json_boolean(const char *key, bool boolean)
{
    json_item_t *new_item = _json_new(key, JSON_BOOLEAN);
    if (NULL == new_item) return NULL;

    new_item->boolean = boolean;

    return new_item;
}

json_item_t*
json_number(const char *key, long double number)
{
    json_item_t *new_item = _json_new(key, JSON_NUMBER);
    if (NULL == new_item) return NULL;

    new_item->number = number;

    return new_item;
}

json_item_t*
json_string(const char *key, char *string)
{
    if (NULL == string) return json_null(key);

    json_item_t *new_item = _json_new(key, JSON_STRING);
    if (NULL == new_item) return NULL;

    new_item->string.start = strdup(string);
    new_item->string.size = strlen(string);
    if (NULL == new_item->string.start) goto cleanupA;

    return new_item;

cleanupA:
    free(new_item->key);
    free(new_item);

    return NULL;
}

static json_item_t*
_json_composite(const char *key, enum json_type type)
{
    json_item_t *new_item = _json_new(key, type);
    if (NULL == new_item) return NULL;

    new_item->comp = calloc(1, sizeof *new_item->comp);
    if (NULL == new_item->comp) goto cleanupA;

    new_item->comp->branch = malloc(sizeof(json_item_t*));
    if (NULL == new_item->comp->branch) goto cleanupB;

    return new_item;


cleanupB:
    free(new_item->comp);
cleanupA:
    free(new_item->key);
    free(new_item);

    return NULL;
}

json_item_t*
json_object(const char *key){
    return _json_composite(key, JSON_OBJECT);
}

json_item_t*
json_array(const char *key){
    return _json_composite(key, JSON_ARRAY);
}

/* total branches the item possess, returns 0 if item type is primitive */
size_t
json_size(const json_item_t *item){
    return IS_COMPOSITE(item) ? item->comp->num_branch : 0;
} 

json_item_t*
json_append(json_item_t *item, json_item_t *new_branch)
{
    ASSERT_S(new_branch != item, "Can't perform circular append");

    char *hold_key = NULL; /* hold new_branch->key incase we can't allocate memory for new numerical key */
    switch (item->type){
    case JSON_ARRAY:
     {
        hold_key = new_branch->key; 

        char numkey[MAX_INTEGER_DIG];
        snprintf(numkey, MAX_INTEGER_DIG-1, "%zu", item->comp->num_branch);

        new_branch->key = strdup(numkey);
        if (NULL == new_branch->key) goto cleanupA; /* Out of memory, reattach its old key and return NULL */
     }
    /* fall through */
    case JSON_OBJECT:
        break;
    default:
        ERR("Can't append to\n\t%s", "Not a composite");
    }

    /* realloc parent references to match new size */
    json_item_t **tmp = realloc(item->comp->branch, (1+item->comp->num_branch) * sizeof(json_item_t*));
    if (NULL == tmp) goto cleanupB;

    item->comp->branch = tmp;

    ++item->comp->num_branch;

    item->comp->branch[item->comp->num_branch-1] = new_branch;
    new_branch->parent = item;

    if (hold_key != NULL){
        free(hold_key);
    }

    return new_branch;

cleanupB:
    if (hold_key != NULL)
        free(new_branch->key);
cleanupA:
    new_branch->key = hold_key;

    return NULL;
}

/* return next (not yet accessed) item, by using item->comp->last_accessed_branch as the branch index */
static json_item_t*
_json_push(json_item_t *item)
{
    ASSERT_S(IS_COMPOSITE(item), "Not a composite");
    ASSERT_S(item->comp->last_accessed_branch < item->comp->num_branch, "Integer overflow");

    ++item->comp->last_accessed_branch; /* update last_accessed_branch to next */
    json_item_t *next_item = item->comp->branch[item->comp->last_accessed_branch-1];

    if (IS_COMPOSITE(next_item)){
        /* resets next_item that might have been set from a different run */
        next_item->comp->last_accessed_branch = 0;
    }

    return next_item;
}

static json_item_t*
_json_pop(json_item_t *item)
{
    if (IS_COMPOSITE(item)){
        /* resets object's last_accessed_branch */
        item->comp->last_accessed_branch = 0;
    }

    return item->parent;
}

/* this will simulate tree preorder traversal iteratively, by using 
 *  item->comp->last_accessed_branch like a stack frame. under no circumstance 
 *  should you modify last_accessed_branch value directly */
json_item_t*
json_iter_next(json_item_t *item)
{
    if (NULL == item) return NULL;

    /* resets root's last_accessed_branch in case its set from a different run */
    if (IS_COMPOSITE(item)){
        item->comp->last_accessed_branch = 0;
    }

    if (IS_LEAF(item)){
        /* item is a leaf, fetch parent until found a item with any branch
         *  left to be accessed */
        do {
            /* fetch parent until a item with unacessed branch is found */
            item = _json_pop(item);
            if ((NULL == item) || (0 == item->comp->last_accessed_branch)){
                /* item is unexistent (root's parent) or all of 
                 *  its branches have been accessed */
                return NULL;
            }
        } while (item->comp->num_branch == item->comp->last_accessed_branch);
    }

    return _json_push(item);
}

/* This is not the most effective way to clone a item, but it is
 *  the most reliable, because it automatically accounts for any
 *  new feature that might added in the future. By first stringfying the
 *  (to be cloned) Item and then parsing the resulting string into
 *  a new clone Item, it's guaranteed that it will be a perfect 
 *  clone, with unique fields */
json_item_t*
json_clone(json_item_t *item)
{
    if (NULL == item) return NULL;

    struct sized_buffer tmp = json_stringify(item, JSON_ANY);
    json_item_t *clone = json_parse(tmp.start, tmp.size);
    free(tmp.start);

    if (NULL != item->key){
        clone->key = strdup(item->key);
        if (NULL == clone->key){
            json_cleanup(clone);
            clone = NULL;
        }
    }

    return clone;
}

char*
json_typeof(const json_item_t *item)
{
    if (NULL == item) return "NO ITEM (NULL)";

    switch (item->type){
    CASE_RETURN_STR(JSON_NUMBER);
    CASE_RETURN_STR(JSON_STRING);
    CASE_RETURN_STR(JSON_NULL);
    CASE_RETURN_STR(JSON_BOOLEAN);
    CASE_RETURN_STR(JSON_OBJECT);
    CASE_RETURN_STR(JSON_ARRAY);
    default:
    CASE_RETURN_STR(JSON_UNDEFINED);
    }
}

char*
json_strdup(const json_item_t *item)
{
    struct sized_buffer src = {0};
    src.start = json_get_string(item, &src.size);
    if (NULL == src.start) return NULL;

    char *dest;
    asprintf(&dest, "%.*s", (int)src.size, src.start);
    return dest;
}

int
json_typecmp(const json_item_t *item, const enum json_type type){
    return item->type & type; /* BITMASK AND */
}

int
json_keycmp(const json_item_t *item, const char *key){
    return (NULL != item->key) ? strcmp(item->key, key) : 1;
}

int
json_numcmp(const json_item_t *item, const long double number){
    ASSERT_S(JSON_NUMBER == item->type, "Not a Number");
    return !(item->number == number);
}

json_item_t*
json_get_root(json_item_t *item)
{
    while (!IS_ROOT(item)){
        item = item->parent;
    }

    return item;
}

/* get item branch with given key */
json_item_t*
json_get_child(json_item_t *item, const char *key)
{
    if (!IS_COMPOSITE(item)) {
      log_error("Can't get child from '%s' (item type is %s)", 
          json_get_key(item), json_typeof(item));
      return NULL;
    }
    if (!key) {
      log_error("Missing 'key'");
      return NULL;
    }

    /* search for entry with given key at item's comp,
      and retrieve found or not found(NULL) item */
    json_item_t *ji = item;
    size_t i=0, len;
    while (i < json_size(ji)) 
    {
        len = strlen(ji->comp->branch[i]->key);
        if (STRNEQ(key, ji->comp->branch[i]->key, len)) 
        {
            if ('\0' == key[len]) { /* keys are equal */
                return ji->comp->branch[i];
            }
            if ('.' == key[len]) { /* parent keys are equal */
                ji = ji->comp->branch[i]; /* get child */
                i = 0; /* reset branch counter */
                key += len+1; /* skip to next key */
                continue;
            }
        }
        ++i;
    }
    return NULL;
}

json_item_t*
json_get_sibling(const json_item_t* item, const char *key)
{
    ASSERT_S(!IS_ROOT(item), "Item is root (has no siblings)");
    return json_get_child(item->parent, key);
}

/* get origin item sibling by the relative index, if origin item is of index 3 (from parent's perspective), and relative index is -1, then this function will return item of index 2 (from parent's perspective) */
json_item_t*
json_get_sibling_byindex(const json_item_t* item, const size_t relative_index)
{
    ASSERT_S(!IS_ROOT(item), "Item is root (has no siblings)");

    /* get parent's branch index of the origin item */
    size_t item_index = json_get_index(item->parent, item->key);

    if ((0 <= (int)(item_index + relative_index)) 
        && json_size(item->parent) > (item_index + relative_index)){
        /* relative index given doesn't exceed parent's total branches, and is greater than 0 */
        return json_get_byindex(item->parent, item_index + relative_index);
    }

    return NULL;
}

json_item_t*
json_get_parent(const json_item_t *item){
    return item->parent;
}

json_item_t*
json_get_byindex(const json_item_t *item, const size_t index)
{
    ASSERT_S(IS_COMPOSITE(item), "Not a composite");
    return (index < item->comp->num_branch) ? item->comp->branch[index] : NULL;
}

long
json_get_index(const json_item_t *item, const char *key)
{
    ASSERT_S(IS_COMPOSITE(item), "Not a composite");
    size_t i;
    json_item_t *lookup_item = NULL;
    for (i=0; i < item->comp->num_branch; ++i) {
        if (STREQ(item->comp->branch[i]->key, key)) {
            lookup_item = item->comp->branch[i];
            break;
        }
    }
    if (NULL == lookup_item) return -1;
    /* @todo currently this is O(n), a possible alternative
     *  is adding a new attribute that stores the item's index */
    for (i=0; i < item->comp->num_branch; ++i){
        if (lookup_item == item->comp->branch[i]){
            return i;
        }
    }
    return -1;
}

enum json_type
json_get_type(const json_item_t *item){
    return (NULL != item) ? item->type : JSON_UNDEFINED;
}

char*
json_get_key(const json_item_t *item){
    return (NULL != item) ? item->key : NULL;
}

bool
json_get_boolean(const json_item_t *item)
{
    if (NULL == item || JSON_NULL == item->type) return false;

    ASSERT_S(JSON_BOOLEAN == item->type, "Not a boolean");
    return item->boolean;
}

char*
json_get_string(const json_item_t *item, size_t *len)
{
    if (NULL == item || JSON_NULL == item->type) return NULL;
    ASSERT_S(JSON_STRING == item->type, "Not a string");
    if (len) *len = item->string.size;
    return item->string.start;
}

long double
json_get_number(const json_item_t *item)
{
    if (NULL == item || JSON_NULL == item->type) return 0.0;
    ASSERT_S(JSON_NUMBER == item->type, "Not a Number");
    return item->number;
}

json_item_t*
json_set_boolean(json_item_t *item, bool boolean)
{
    item->boolean = boolean;
    return item;
}

json_item_t*
json_set_string(json_item_t *item, char *string)
{
    if (item->string.start)
      free(item->string.start);
    item->string.start = strdup(string);
    item->string.size = strlen(string);
    return item;
}

json_item_t*
json_set_number(json_item_t *item, long double number) {
    item->number = number;
    return item;
}

/* STRINGIFY IMPLEMENTATION */

struct _stringify_context {
    struct sized_buffer buffer;
    /*a setter method that can be either _json_cxt_analyze or
       _json_cxt_encode*/
    void (*method)(char get_char, struct _stringify_context* cxt);
};

/* every time its called, it adds one position to buffer.size,
      so that it can be used for counting how many position to be expected
      for buffer */ 
static void
_json_cxt_analyze(char get_char, struct _stringify_context *cxt){
    ++cxt->buffer.size;
    (void)get_char;
}

/* fills allocated buffer (with its length calculated by
      _json_cxt_analyze) with string converted json items */
static void
_json_cxt_encode(char get_char, struct _stringify_context *cxt)
{
    cxt->buffer.start[cxt->buffer.size] = get_char;
    ++cxt->buffer.size;
}

/* get string value to perform buffer method calls */
static void
_json_cxt_apply_string(char *string, struct _stringify_context *cxt)
{
    while ('\0' != *string){
        (*cxt->method)(*string,cxt);
        ++string;
    }
}

/* converts number to string and store it in p_str */
static void 
_json_number_tostr(const long double number, char *p_str)
{
    if (DOUBLE_IS_INTEGER(number)){
        /* save time and convert integer to string */
        sprintf(p_str,"%.Lf",number);
        return;
    }

    sprintf(p_str, "%.*Le", DBL_DECIMAL_DIG-1, number);

    if (isfinite(number))
    {
        char *p_last;
        char *tmp;

        if ('0' == p_str[strlen(p_str)-1]){ /* 00 terminating exp */
            p_last = &p_str[strlen(p_str)-1]; /* address of last digit, including exp */
            tmp = p_last;

            while ('0' == *tmp) /* trim trailing zeroes */
                --tmp;

            /* trim exp related characters */
            if ('+' == *tmp || '-' == *tmp)
                --tmp;
            if ('e' == *tmp || 'E' == *tmp)
                --tmp;
        } else { /* get address of last significand digit */
            p_last = (number < 0)
                        ? &p_str[DBL_DECIMAL_DIG+1] /* account for minus sign */
                        : &p_str[DBL_DECIMAL_DIG];
            tmp = p_last;
        }

        while ('0' == *tmp){ /* trim trailing zeroes */
            --tmp;
        }

        memmove(tmp+1, p_last+1, strlen(p_last+1)+1);
    }
}

/* get number converted to string and then perform buffer method calls */
static void
_json_cxt_apply_number(long double number, struct _stringify_context *cxt)
{
    /*             sign + digit + dp +       digits        + e + sign + expo + \0 
         get_strnum[ 1  +  1    + 1  + (DBL_DECIMAL_DIG-1) + 1 +  1   +  5   +  1] */
    char get_strnum[11 + (DBL_DECIMAL_DIG-1)];
    _json_number_tostr(number, get_strnum);
    _json_cxt_apply_string(get_strnum,cxt); /* store value in cxt */
}

/* walk json item, by traversing its branches recursively,
      and perform buffer_method callback on each branch */
static void
_json_stringify_preorder(json_item_t *item, enum json_type type, struct _stringify_context *cxt)
{
    /* 1st STEP: stringify json item only if it match the type
        given as parameter or is a composite type item */
    if (!json_typecmp(item, type) && !IS_COMPOSITE(item))
        return;

    /* 2nd STEP: prints item key only if its a object's property
        (array's numerical keys printing doesn't conform to standard)*/
    if (!IS_ROOT(item) && IS_PROPERTY(item)){
        (*cxt->method)('\"', cxt);
        _json_cxt_apply_string(item->key, cxt);
        (*cxt->method)('\"', cxt);
        (*cxt->method)(':', cxt);
    }
    
    /* 3rd STEP: converts item to its string format and append to buffer */
    switch (item->type){
    case JSON_NULL:
        _json_cxt_apply_string("null", cxt);
        break;
    case JSON_BOOLEAN:
        if (item->boolean){
            _json_cxt_apply_string("true", cxt);
            break;
        }
        _json_cxt_apply_string("false", cxt);
        break;
    case JSON_NUMBER:
        _json_cxt_apply_number(item->number, cxt);
        break;
    case JSON_STRING:
        (*cxt->method)('\"', cxt);
        _json_cxt_apply_string(item->string.start, cxt);
        (*cxt->method)('\"', cxt);
        break;
    case JSON_OBJECT:
        (*cxt->method)('{', cxt);
        break;
    case JSON_ARRAY:
        (*cxt->method)('[', cxt);
        break;
    default:
        ERR("Can't stringify undefined datatype (code: %d)", item->type);
    }

    /* 4th STEP: if item is is a branch's leaf (defined at macros.h),
        the 5th step can be ignored and returned */
    if (IS_LEAF(item)){
        switch(item->type){
        case JSON_OBJECT:
            (*cxt->method)('}', cxt);
            return;
        case JSON_ARRAY:
            (*cxt->method)(']', cxt);
            return;
        default: /* is a primitive, just return */
            return;
        }
    }

    /* 5th STEP: find first item's branch that matches the given type, and 
        calls the write function on it */
    size_t j;
    size_t first_index=0;

    while (first_index < item->comp->num_branch){
        if (json_typecmp(item->comp->branch[first_index], type) || IS_COMPOSITE(item->comp->branch[first_index])){
            _json_stringify_preorder(item->comp->branch[first_index], type, cxt);
            break;
        }
        ++first_index;
    }

    /* 6th STEP: calls the write function on every consecutive branch
        that matches the type criteria, with an added comma before it */
    for (j = first_index+1; j < item->comp->num_branch; ++j){
        /* skips branch that don't fit the criteria */
        if (!json_typecmp(item, type) && !IS_COMPOSITE(item)){
            continue;
        }
        (*cxt->method)(',',cxt);
        _json_stringify_preorder(item->comp->branch[j], type, cxt);
    }

    /* 7th STEP: write the composite's type item wrapper token */
    switch(item->type){
    case JSON_OBJECT:
        (*cxt->method)('}', cxt);
        break;
    case JSON_ARRAY:
        (*cxt->method)(']', cxt);
        break;
    default: /* this shouldn't ever happen, but just in case */
        ERR("Not a composite");
    }
}

/* converts a json item to a json formatted text, and return it */
struct sized_buffer
json_stringify(json_item_t *root, enum json_type type)
{
    ASSERT_S(NULL != root, "Missing 'root'");

    struct _stringify_context cxt = { .method = NULL};

    /* 1st STEP: remove root->key and root->parent temporarily to make
        sure the given item is treated as a root when printing, in the
        case that given item isn't already a root (roots donesn't have
        keys or parents) */
    char *hold_key = root->key;
    json_item_t *hold_parent = root->parent;
    root->key = NULL;
    root->parent = NULL;

    /* 2nd STEP: count how many chars will fill the buffer with
        _json_cxt_analyze, then allocate the buffer to that amount */
    cxt.method = &_json_cxt_analyze;
    _json_stringify_preorder(root, type, &cxt);
    cxt.buffer.start = malloc(cxt.buffer.size += 5);/* +5 for extra safety */
    if (NULL == cxt.buffer.start) return (struct sized_buffer){0};

    /* 3rd STEP: reset buffer.size and proceed with
        _json_cxt_encode to fill allocated buffer */
    cxt.buffer.size = 0;
    cxt.method = &_json_cxt_encode;
    _json_stringify_preorder(root, type, &cxt);
    cxt.buffer.start[cxt.buffer.size] = 0; /* end of buffer token */

    /* 4th STEP: reattach key and parents from step 1 */
    root->key = hold_key;
    root->parent = hold_parent;

    struct sized_buffer ret={0};
    if (!json_string_unescape(&ret.start, &ret.size, cxt.buffer.start, cxt.buffer.size)) {
      ERR("Cannot unescape an ill-formed-string %.*s", (int)ret.size, ret.start);
    }
    return ret;
}
