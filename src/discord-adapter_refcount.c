#include <stdio.h>
#include <stdlib.h>

#include "discord.h"
#include "discord-internal.h"

void
discord_refcount_incr(struct discord_adapter *adapter,
                      void *data,
                      void (*cleanup)(void *data))
{
    struct discord_refcount *ref = NULL;

    HASH_FIND_PTR(adapter->refcounts, &data, ref);
    if (NULL == ref) {
        ref = calloc(1, sizeof *ref);
        ref->data = data;
        ref->cleanup = cleanup;

        HASH_ADD_PTR(adapter->refcounts, data, ref);
    }

    ++ref->visits;
}

void
discord_refcount_decr(struct discord_adapter *adapter, void *data)
{
    struct discord_refcount *ref = NULL;

    HASH_FIND_PTR(adapter->refcounts, &data, ref);
    if (ref && --ref->visits <= 0) {
        if (ref->cleanup) ref->cleanup(ref->data);

        HASH_DEL(adapter->refcounts, ref);
        free(ref);
    }
}
