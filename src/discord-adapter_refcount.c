#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

#include "chash.h"

/* chash heap-mode (auto-increase hashtable buckets) */
#define INTPTR_TABLE_HEAP   1
#define INTPTR_TABLE_BUCKET struct _intptr_bucket
#define INTPTR_TABLE_FREE_KEY(_key)
#define INTPTR_TABLE_HASH(_key, _hash)       ((intptr_t)(_key))
#define INTPTR_TABLE_FREE_VALUE(_value)      _discord_refcount_cleanup(&_value)
#define INTPTR_TABLE_COMPARE(_cmp_a, _cmp_b) (_cmp_a == _cmp_b)
#define INTPTR_TABLE_INIT(bucket, _key, _value)                               \
    memset(&bucket, 0, sizeof(bucket));                                       \
    chash_default_init(bucket, _key, _value)

struct _discord_refcount {
    /** user arbitrary data to be retrieved at `done` or `fail` callbacks */
    void *data;
    /**
     * cleanup for when `data` is no longer needed
     * @note this only has to be assigned once, it is automatically called once
     *      `data` is no longer referenced by any callback */
    void (*cleanup)(void *data);
    /** `data` references count */
    int visits;
};

struct _intptr_bucket {
    /** key is the user data's address */
    intptr_t key;
    /** holds the user data and information for automatic cleanup */
    struct _discord_refcount value;
    /** the route state in the hashtable (see chash.h 'State enums') */
    int state;
};

static void
_discord_refcount_cleanup(struct _discord_refcount *ref)
{
    if (ref->cleanup) ref->cleanup(ref->data);
}

static struct _discord_refcount *
_discord_refcount_find(struct discord_refcounter *rc, intptr_t key)
{
    struct _intptr_bucket *bucket = NULL;

    bucket = chash_lookup_bucket(rc, key, bucket, INTPTR_TABLE);

    return &bucket->value;
}

static struct _discord_refcount *
_discord_refcount_init(struct discord_refcounter *rc,
                       intptr_t key,
                       void *data,
                       void (*cleanup)(void *data))
{
    struct _discord_refcount ref;

    ref.data = data;
    ref.cleanup = cleanup;
    ref.visits = 0;
    chash_assign(rc, key, ref, INTPTR_TABLE);

    return _discord_refcount_find(rc, key);
}

struct discord_refcounter *
discord_refcounter_init(struct logconf *conf)
{
    struct discord_refcounter *rc = chash_init(rc, INTPTR_TABLE);

    logconf_branch(&rc->conf, conf, "DISCORD_REFCOUNT");

    return rc;
}

void
discord_refcounter_cleanup(struct discord_refcounter *rc)
{
    chash_free(rc, INTPTR_TABLE);
}

void
discord_refcounter_incr(struct discord_refcounter *rc,
                        void *data,
                        void (*cleanup)(void *data))
{
    struct _discord_refcount *ref = NULL;
    intptr_t key = (intptr_t)data;
    int ret;

    ret = chash_contains(rc, key, ret, INTPTR_TABLE);
    if (ret)
        ref = _discord_refcount_find(rc, key);
    else
        ref = _discord_refcount_init(rc, key, data, cleanup);
    ++ref->visits;
}

void
discord_refcounter_decr(struct discord_refcounter *rc, void *data)
{
    struct _discord_refcount *ref = NULL;
    intptr_t key = (intptr_t)data;
    int ret;

    ret = chash_contains(rc, key, ret, INTPTR_TABLE);
    if (ret) {
        ref = _discord_refcount_find(rc, key);
        if (0 == --ref->visits) {
            chash_delete(rc, key, INTPTR_TABLE);
        }
    }
}
