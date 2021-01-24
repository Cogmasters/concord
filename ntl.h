#ifndef NULL_TERM_LIST_H
#define NULL_TERM_LIST_H
#include <stddef.h> // for size_t
#include <stdbool.h>

/*
 * Null terminated list implementation
 */
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void ** ntl_malloc (size_t nmem,  size_t elem_size);
void ** ntl_dup (void ** p, size_t elem_size);
size_t ntl_length (void **p);

typedef void (ntl_converter)(void * from, void * to);
void ** ntl_fmap(void ** from_list,
                 size_t to_elem_size,
                 ntl_converter * f);

/*
 * sn2str(NULL, 0, p) will calculate the size needed to print *p
 * sn2str(buf, n, p) will print to buffer
 */
typedef int (sn2str)(char * str, size_t size, void *p, bool is_last);
int ntl_sn2str(char *str, size_t size, void **p, sn2str * x);
int ntl_as2str(char **str, void **p, sn2str * x);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //NULL_TERM_LIST_H
