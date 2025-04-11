#ifndef QUERIEC_H
#define QUERIEC_H

#define QUERIEC_ADDITIONAL_LETTERS_SIZE 2

#define QUERIEC_ERROR_NOMEM -1
#define QUERIEC_OK 0

#include "attributes.h"

struct queriec {
    int state;
    size_t size;
    size_t offset;
};

void
queriec_init(struct queriec *queriec, size_t size);

int queriec_snprintf_add(struct queriec *queriec, char *query, 
		const char key[], size_t keySize, 
		char buffer[], size_t bufferLen, 
		const char *format, ...) PRINTF_LIKE(7, 8);

int
queriec_add(struct queriec *queriec, char *query, char key[], 
		size_t keySize, char value[], size_t valueSize);

#endif

