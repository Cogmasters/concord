#include "mem.h"
#include <stdlib.h>
#include <string.h>

struct ccord_memory_fn_vtable ccord_global_memory_fn_vtable;

bool ccord_mem_is_initialized = false;

void
mem_init(malloc_fn_t malloc_fn,
         calloc_fn_t calloc_fn,
         realloc_fn_t realloc_fn,
         free_fn_t free_fn,
         strdup_fn_t strdup_fn)
{
    ccord_mem_is_initialized = true;
    ccord_global_memory_fn_vtable.malloc_fn = malloc_fn;
    ccord_global_memory_fn_vtable.calloc_fn = calloc_fn;
    ccord_global_memory_fn_vtable.realloc_fn = realloc_fn;
    ccord_global_memory_fn_vtable.free_fn = free_fn;
    ccord_global_memory_fn_vtable.strdup_fn = strdup_fn;
}
