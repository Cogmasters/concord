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
#define REFCOUNTER_TABLE_HASH(_key, _hash) ((intptr_t)(_key))
#define REFCOUNTER_TABLE_FREE_VALUE(_value)                                   \
    _discord_refvalue_cleanup(&_value, client)
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
    void (*cleanup)(struct discord *client, void *data);
    /**
     * `data` references count
     * @note if `-1` then `data` has been claimed with
     *      discord_refcounter_claim() and will be cleaned up once
     *      discord_refcount_unclaim() is called
     */
    int visits;
    /** whether `data` cleanup should also be followed by a free() */
    bool should_free;
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
_discord_refvalue_cleanup(struct _discord_refvalue *value,
                          struct discord *client)
{
    if (value->cleanup) value->cleanup(client, value->data);
    if (value->should_free) free(value->data);
}

static struct _discord_refvalue *
_discord_refvalue_find(struct discord_refcounter *rc, void *data)
{
    struct _discord_ref *ref = NULL;

    ref = chash_lookup_bucket(rc, (intptr_t)data, ref, REFCOUNTER_TABLE);

    return &ref->value;
}

static struct _discord_refvalue *
_discord_refvalue_init(struct discord_refcounter *rc,
                       void *data,
                       void (*cleanup)(struct discord *client, void *data),
                       bool should_free)
{
    struct discord *client = CLIENT(rc, refcounter);
    struct _discord_refvalue value = {
        .data = data,
        .cleanup = cleanup,
        .visits = 0,
        .should_free = should_free,
    };

    chash_assign(rc, (intptr_t)data, value, REFCOUNTER_TABLE);

    return _discord_refvalue_find(rc, data);
}

static bool
_discord_refvalue_contains(struct discord_refcounter *rc, void *data)
{
    bool ret = chash_contains(rc, (intptr_t)data, ret, REFCOUNTER_TABLE);
    return ret;
}

static void
_discord_refvalue_delete(struct discord_refcounter *rc, void *data)
{
    struct discord *client = CLIENT(rc, refcounter);
    chash_delete(rc, (intptr_t)data, REFCOUNTER_TABLE);
}

void
discord_refcounter_init(struct discord_refcounter *rc, struct logconf *conf)
{
    __chash_init(rc, REFCOUNTER_TABLE);

    logconf_branch(&rc->conf, conf, "DISCORD_REFCOUNT");
}

void
discord_refcounter_cleanup(struct discord_refcounter *rc)
{
    struct discord *client = CLIENT(rc, refcounter);
    __chash_free(rc, REFCOUNTER_TABLE);
}

bool
discord_refcounter_claim(struct discord_refcounter *rc, void *data)
{
    if (_discord_refvalue_contains(rc, data)) {
        struct _discord_refvalue *value = _discord_refvalue_find(rc, data);

        value->visits = -1;
        return true;
    }
    return false;
}

bool
discord_refcounter_unclaim(struct discord_refcounter *rc, void *data)
{
    if (_discord_refvalue_contains(rc, data)) {
        struct _discord_refvalue *value = _discord_refvalue_find(rc, data);

        if (value->visits == -1) {
            _discord_refvalue_delete(rc, data);
            return true;
        }
    }
    return false;
}

bool
discord_refcounter_incr(struct discord_refcounter *rc,
                        void *data,
                        void (*cleanup)(struct discord *client, void *data),
                        bool should_free)
{
    struct _discord_refvalue *value;

    if (_discord_refvalue_contains(rc, data))
        value = _discord_refvalue_find(rc, data);
    else
        value = _discord_refvalue_init(rc, data, cleanup, should_free);

    if (value->visits != -1) {
        ++value->visits;
        return true;
    }
    return false;
}

bool
discord_refcounter_decr(struct discord_refcounter *rc, void *data)
{
    struct _discord_refvalue *value = NULL;

    if (_discord_refvalue_contains(rc, data))
        value = _discord_refvalue_find(rc, data);

    if (value && value->visits != -1) {
        if (0 == --value->visits) {
            _discord_refvalue_delete(rc, data);
        }
        return true;
    }
    return false;
}
