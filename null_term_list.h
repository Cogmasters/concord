#ifndef NULL_TERM_LIST_H
#define NULL_TERM_LIST_H

#include <stddef.h> // for size_t

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern void **null_term_list_malloc(size_t nmem,  size_t elem_size);
extern void **null_term_list_dup(void **p, size_t elem_size);
extern size_t null_term_list_length(void **p);

typedef int (snp)(char * str, size_t size, void *p);
extern int null_term_list_snp(char *str, size_t size, void **p, snp *x);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // NULL_TERM_LIST_H
