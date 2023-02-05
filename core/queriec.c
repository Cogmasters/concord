#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>

#include "queriec.h"

void
queriec_init(struct queriec *queriec, size_t size)
{
    queriec->size = size;
    queriec->state = 0;
    queriec->offset = 0;
}

static void
_queriec_add(struct queriec *queriec, char *query, char *letter, const char key[], size_t key_sz, char value[], size_t value_sz)
{
    size_t i = 0;
        
    query[queriec->offset++] = letter[0];
    while (i < key_sz) {
        query[queriec->offset++] = key[i++];
    }
    --queriec->offset;
    i = 0;

    query[queriec->offset++] = '=';
    while (i < key_sz) {
        query[queriec->offset++] = value[i++];
    }
    --queriec->offset;
}

int queriec_snprintf_add(struct queriec *queriec, char *query, const char key[], size_t keySize, 
                         char buffer[], size_t bufferLen, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    size_t expectedSize = (size_t)vsnprintf(buffer, bufferLen, format, args);
    va_end(args);

    if (queriec->offset + keySize + expectedSize + QUERIEC_ADDITIONAL_LETTERS_SIZE > queriec->size) return QUERIEC_ERROR_NOMEM;

    char *c = NULL;
    switch (queriec->state) {
    case 0:
        c = "?";
        queriec->state = 1;
        break;
    case 1:
        c = "&";
        break;
    default:
       fprintf(stderr, "queriec_snprintf_add: invalid state.\n");

       abort();
    }

    _queriec_add(queriec, query, c, key, keySize, buffer, expectedSize);

    return QUERIEC_OK;
}

int
queriec_add(struct queriec *queriec, char *query, char key[], size_t keySize, char value[], size_t valueSize)
{
    if (queriec->offset + keySize + valueSize + QUERIEC_ADDITIONAL_LETTERS_SIZE > queriec->size) return QUERIEC_ERROR_NOMEM;

    char *c = NULL;
    switch (queriec->state) {
    case 0:
        c = "?";
        queriec->state = 1;
        break;
    case 1:
        c = "&";
        break;
    default:
        fprintf(stderr, "queriec_add: invalid state.\n");

        abort();
    }

    _queriec_add(queriec, query, c, key, keySize, value, valueSize);

    return QUERIEC_OK;
}