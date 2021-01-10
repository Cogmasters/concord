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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "json-scanf.h"

#include "jscon-common.h"
#include "debug.h"
#include "jsmn.h"

#define KEY_MAX 256

struct path_specifier {
    enum {
        KEY,
        INDEX,
        ARRAY
    } type;
    union {
        char key[KEY_MAX];
        int index;
    } path;
    struct path_specifier * next;
};

struct extractor_specifier {
    struct path_specifier path_specifier;
    char type_specifier[10];
    size_t size;
    void * recipient; /* it should be a pointer */
    bool applied;
};


static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING
        && (int)strlen(s) == tok->end - tok->start
        && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}

static void match_path (char * buffer,
                        jsmntok_t * t, size_t n_tokens, int start_token,
                        struct extractor_specifier * es,
                        struct path_specifier * p) {
    char * end = 0;
    int i = start_token;
    if (!p) {
        es->applied = true;
        if (STREQ(es->type_specifier, "char*")){
            if (es->size) {
                strncpy((char *) es->recipient, buffer + t[i].start, es->size);
            }
            else {
                strscpy((char *) es->recipient, buffer + t[i].start,
                        t[i].end - t[i].start + 1);
            }
        }
        else if (STREQ(es->type_specifier, "bool*")) {
            if (jsoneq(buffer, &t[i], "true") == 0) {
                *(bool *)es->recipient = true;
            }
            else if (jsoneq(buffer, &t[i], "false") == 0){
                *(bool *)es->recipient = false;
            }
            else {
                goto type_error;
            }
        }
        else if (STREQ(es->type_specifier, "int*")) {
            *(int *)es->recipient = (int)strtol(buffer + t[i].start, &end, 10);
            if (end != buffer + t[i].end) goto type_error;
        }
        else if (STREQ(es->type_specifier, "long*")) {
            *(long *)es->recipient = strtol(buffer + t[i].start, &end, 10);
            if (end != buffer + t[i].end) goto type_error;
        }
        else if (STREQ(es->type_specifier, "long long*")) {
            *(long long *)es->recipient = strtoll(buffer + t[i].start, &end, 10);
            if (end != buffer + t[i].end) goto type_error;
        }
        else if (STREQ(es->type_specifier, "float *")) {
            *(float *)es->recipient = strtof(buffer + t[i].start, &end);
            if (end != buffer + t[i].end) goto type_error;
        }
        else if (STREQ(es->type_specifier, "double *")) {
            *(double *)es->recipient = strtod(buffer + t[i].start, &end);
            if (end != buffer + t[i].end) goto type_error;
        }
        else {
            //strscpy(err_typeis, "float*, double* or jscon_item_t**", sizeof(err_typeis));
            goto type_error;
        }
        return;
    }
    else {
        match_path(buffer, t, n_tokens, i, es, p);
        return;
    }

    type_error:
    ERROR("Expected specifier %s but found: '%.*s' )\n", es->type_specifier, t[i].end - t[i].start, buffer + t[i].start);
    // report errors;
    return;
}

static void apply(char * test_string, jsmntok_t * t, size_t n_tokens,
                  struct extractor_specifier * es) {
    size_t i;
    for (i = 1; i < n_tokens; i++) {
        if (jsoneq(test_string, &t[i], es->path_specifier.path.key) == 0) {
            i++;
            match_path(test_string, t, n_tokens, i, es, es->path_specifier.next);
        }
    }
}


static char* parse_type_specifier(char *specifier, struct extractor_specifier *  p) {
    char * start = specifier, * end;
    long size = strtol(start, &end, 10);

    bool size_is_valid = false;
    if (end != start) {
        size_is_valid = true;
        specifier = end;
    }

    if (strncmp(specifier, "s", 1) == 0 || strncmp(specifier, "S", 1) == 0){
        strcpy(p->type_specifier, "char*");
        if (size_is_valid)
            p->size = size;
        else
            p->size = 0;
        return specifier + 1;
    }
    else if (strncmp(specifier, "d", 1) == 0) {
        p->size = sizeof(int);
        strcpy(p->type_specifier, "int*");
        return specifier + 1;
    }
    else if (strncmp(specifier, "ld", 2) == 0) {
        p->size = sizeof(long);
        strcpy(p->type_specifier, "long*");
        return specifier + 2;
    }
    else if (strncmp(specifier, "lld", 3) == 0) {
        p->size = sizeof(long long);
        strcpy(p->type_specifier, "long long *");
        return specifier + 3;
    }
    else if (strncmp(specifier, "f", 1) == 0) {
        p->size = sizeof(float);
        strcpy(p->type_specifier, "float*");
        return specifier + 1;
    }
    else if (strncmp(specifier, "lf", 2) == 0) {
        p->size = sizeof(double);
        strcpy(p->type_specifier, "double*");
        return specifier + 2;
    }
    else if (strncmp(specifier, "b", 1) == 0){
        p->size = sizeof(bool);
        strcpy(p->type_specifier, "bool*");
        return specifier + 1;
    }
#if 0
    if (STREQ(specifier, "ji")){
        *n_bytes = sizeof(jscon_item_t*);
        return "jscon_item_t**";
    }
#endif
    return 0;
}

/*
 * legit inputs:
 *      abc]
 *      ]
 *      10]
 *
 * illegit inputs:
 *      abc
 *      10
 */
static char * parse_path_specifier (char * format, struct extractor_specifier * p,
                                    struct path_specifier * curr_path) {
    char * start = format;
    bool is_index = true;
    do {
        if (isalpha(*format))
            is_index = false;
        format++;
    } while (*format && *format != ']' && *format != '%');
    size_t len = format - start;

    if (len >= KEY_MAX) { // report key is too long
        return 0;
    }
    else {
        if (len == 0) {
            curr_path->type = ARRAY;
        }
        else if (is_index) { // array indexing
            char * end;
            long l = strtol(start, &end, 10);
            if (end == format) {
                curr_path->path.index = l;
            }
            else {
                // invalid characters in the number strings
            }
        }
        else { // key
            strncpy(curr_path->path.key, start, len);
            curr_path->path.key[len] = 0;
            curr_path->type = KEY;
        }
        format ++; // eat up ']'
        if (*format == '[') {
            format ++;
            struct path_specifier * next_path = malloc(sizeof(*next_path));
            curr_path->next = next_path;
            return parse_path_specifier(format, p, next_path);
        }
        else if (*format == '%'){
            format ++;
            return parse_type_specifier(format, p);
        }
        else {
            return 0;
        }
    }
}

#define SKIP_SPACES(s)   { while (isspace(*s)) ++s; }

static struct extractor_specifier * parse_extractor_specifiers (char * format, size_t n) {
    size_t i = 0;
    struct extractor_specifier * nes = calloc(n, sizeof(*nes));
    SKIP_SPACES(format);
    while (*format) {
        if (*format == '[') {
            format++;
            format = parse_path_specifier(format, nes+i, &nes[i].path_specifier);
        }
        else {
            //error
            free(nes);
            return 0;
        }
        i++;
    }
    return nes;
}

/* count amount of keys and check for formatting errors */
static void format_analyze(char *format, size_t *num_keys) {
    bool opened = false;
    while (*format) { /* run until end of string found */
        // search for open bracket
        while (*format) {
            if ('[' == *format) {
                ++format;
                opened = true;
                break;
            }
            ++format;
        }
        if (!opened && !*format) {
            // report no open bracket;
            return;
        }

        // search for close bracket
        while (*format) {
            if (']' == *format) {
                opened = false;
                if (*++format != '[') {
                    break;
                }
                else {
                    opened = true;
                    ++format;
                    continue;
                }
            }
            ++format;
        }

        if (opened) {
            // report unmatched bracket;
            return;
        }
        /* find % occurrence */
        while (*format) {
            if ('%' == *format){
                do {
                    // skip type specifier
                    ++format;
                } while (*format && *format != '[');
                break;
            }
            ++format;
        }
        (*num_keys) ++;
    }
}

static struct extractor_specifier * format_parse(char *format, size_t * n) {
    format_analyze(format, n);
    struct extractor_specifier * nes = parse_extractor_specifiers(format, *n);
    return nes;
}

/*
 *  format grammar:
 *      ([key1]|[][number])+(%<d|ld\lld|f\lf|b\s\S>)
 *
 *  usage:
 *      json_scanf2(str, "[k1][k2]%d", &i);
 *
 */
int json_scanf2(char *buffer, char *format, ...) {
    va_list ap;
    size_t num_keys = 0;
    struct extractor_specifier * nes;
    nes = format_parse(format, &num_keys);

    va_start(ap, format);
    size_t i = 0;
    for (i = 0; i < num_keys; i++) {
        nes[i].recipient = va_arg(ap, void *);
    }
    va_end(ap);

    jsmn_parser p;
    jsmn_init(&p);

    // calculate how many tokens are needed
    int r = jsmn_parse(&p, buffer, strlen(buffer), NULL, 0);

    printf("need tokens = %d \n", r);
    jsmntok_t *t = malloc(sizeof(jsmntok_t) * r);
    jsmn_init(&p);
    r = jsmn_parse(&p, buffer, strlen(buffer), t, r);

    if (r < 0) {
        printf("Failed to parse JSON: %d\n", r);
        free(t);
        free(nes);
        return 0;
    }

    /* Assume the top-level element is an object */
    if (r < 1 || t[0].type != JSMN_OBJECT) {
        printf("Object expected\n");
        free(t);
        free(nes);
        return 0;
    }

    size_t n = 0;
    for (n = 0; n < num_keys; n++) {
        apply(buffer, t, r, nes+n);
    }
    free(t);
    free(nes);
    return 0;
}
