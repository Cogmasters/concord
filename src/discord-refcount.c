#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

#define CHASH_BUCKETS_FIELD refs
#include "chash.h"

/* chash heap-mode (auto-increase hashtable) */
#define REFCOUNTER_TABLE_HEAP   1
#define REFCOUNTER_TABLE_BUCKET struct _discord_ref
#define REFCOUNTER_TABLE_FREE_KEY(_key)
#define REFCOUNTER_TABLE_HASH(_key, _hash)       ((intptr_t)(_key))
#define REFCOUNTER_TABLE_FREE_VALUE(_value)      _discord_refvalue_cleanup(&_value)
#define REFCOUNTER_TABLE_COMPARE(_cmp_a, _cmp_b) (_cmp_a == _cmp_b)
#define REFCOUNTER_TABLE_INIT(ref, _key, _value)                              \
    memset(&ref, 0, sizeof(ref));                                             \
    chash_default_init(ref, _key, _value)

struct _discord_refvalue {
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

struct _discord_ref {
    /** key is the user data's address */
    intptr_t key;
    /** holds the user data and information for automatic cleanup */
    struct _discord_refvalue value;
    /** the route state in the hashtable (see chash.h 'State enums') */
    int state;
};

static void
_discord_refvalue_cleanup(struct _discord_refvalue *value)
{
    if (value->cleanup) value->cleanup(value->data);
}

static struct _discord_refvalue *
_discord_refvalue_find(struct discord_refcounter *rc, intptr_t key)
{
    struct _discord_ref *ref = NULL;

    ref = chash_lookup_bucket(rc, key, ref, REFCOUNTER_TABLE);

    return &ref->value;
}

static struct _discord_refvalue *
_discord_refvalue_init(struct discord_refcounter *rc,
                       intptr_t key,
                       void *data,
                       void (*cleanup)(void *data))
{
    struct _discord_refvalue value;

    value.data = data;
    value.cleanup = cleanup;
    value.visits = 0;
    chash_assign(rc, key, value, REFCOUNTER_TABLE);

    return _discord_refvalue_find(rc, key);
}

struct discord_refcounter *
discord_refcounter_init(struct logconf *conf)
{
    struct discord_refcounter *rc = chash_init(rc, REFCOUNTER_TABLE);

    logconf_branch(&rc->conf, conf, "DISCORD_REFCOUNT");

    return rc;
}

void
discord_refcounter_cleanup(struct discord_refcounter *rc)
{
    chash_free(rc, REFCOUNTER_TABLE);
}

void
discord_refcounter_incr(struct discord_refcounter *rc,
                        void *data,
                        void (*cleanup)(void *data))
{
    struct _discord_refvalue *value = NULL;
    intptr_t key = (intptr_t)data;
    int ret;

    ret = chash_contains(rc, key, ret, REFCOUNTER_TABLE);
    if (ret)
        value = _discord_refvalue_find(rc, key);
    else
        value = _discord_refvalue_init(rc, key, data, cleanup);
    ++value->visits;
}

void
discord_refcounter_decr(struct discord_refcounter *rc, void *data)
{
    struct _discord_refvalue *value = NULL;
    intptr_t key = (intptr_t)data;
    int ret;

    ret = chash_contains(rc, key, ret, REFCOUNTER_TABLE);
    if (ret) {
        value = _discord_refvalue_find(rc, key);
        if (0 == --value->visits) {
            chash_delete(rc, key, REFCOUNTER_TABLE);
        }
    }
}
