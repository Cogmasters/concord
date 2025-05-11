#ifndef OA_HASH_H
#define OA_HASH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef OA_HASH_STATIC
#define OA_HASH_API static
#else
#define OA_HASH_API extern
#endif /* OA_HASH_STATIC */

#include <stddef.h>

/** @brief Hash table entry state */
enum oa_hash_entry_state {
    OA_HASH_ENTRY_EMPTY = 0, /**< empty entry */
    OA_HASH_ENTRY_OCCUPIED, /**< occupied entry */
    OA_HASH_ENTRY_DELETED /**< deleted entry */
};

/** @brief Entry holding key-value pair in hash table */
struct oa_hash_entry {
    enum oa_hash_entry_state state; /**< entry state */
    struct {
        const char *buf; /**< key buffer */
        size_t length; /**< key length */
    } key;
    void *value; /**< value pointer */
};

#define __OA_HASH_ATTRS_const                                                 \
    const size_t length; /**< amount of entries */                            \
    const size_t capacity; /**< total buckets capacity */                     \
    const struct oa_hash_entry *buckets /**< entries array */
#define __OA_HASH_ATTRS_mut                                                   \
    size_t length; /**< amount of entries */                                  \
    size_t capacity; /**< total buckets capacity */                           \
    struct oa_hash_entry *buckets /**< entries array */
/** @brief can be used to cast to struct oa_hash */
#define OA_HASH_ATTRS(_qualifier) __OA_HASH_ATTRS_##_qualifier

/** @brief Open addressing hash table */
struct oa_hash {
    OA_HASH_ATTRS(mut);
};

/**
 * @brief Initialize hash table with given buckets array
 *
 * @param[out] ht the hash table to be initialized
 * @param[out] buckets pre-allocated array of entries
 * @param[in] capacity amount of buckets
 */
OA_HASH_API void oa_hash_init(struct oa_hash *ht,
                              struct oa_hash_entry buckets[],
                              const size_t capacity);

/**
 * @brief Clean up hash table entries and struct
 *
 * @param[out] ht the hash table to be cleaned
 */
OA_HASH_API void oa_hash_cleanup(struct oa_hash *ht);

/**
 * @brief Retrieve entry by key
 *
 * @param[in] ht the hash table
 * @param[in] key the key to search for
 * @param[in] len the key length
 * @return entry if found, NULL otherwise
 */
OA_HASH_API const struct oa_hash_entry *oa_hash_get_entry(
    const struct oa_hash *ht, const char key[], const size_t len);

/**
 * @brief Retrieve value by key (wrapper around oa_hash_get_entry)
 *
 * @param[in] ht the hash table
 * @param[in] key the key to search for
 * @param[in] len the key length
 * @return value if found, NULL otherwise
 */
OA_HASH_API void *oa_hash_get(const struct oa_hash *ht,
                              const char key[],
                              const size_t len);

/**
 * @brief Insert or update entry
 *
 * @param[in,out] ht the hash table
 * @param[in] key the key to insert/update
 * @param[in] len the key length
 * @param[in] value the value to be assigned
 * @return entry if successful, or NULL if no space left, in which case
 *      oa_hash_rehash() should be called
 */
OA_HASH_API const struct oa_hash_entry *oa_hash_set_entry(struct oa_hash *ht,
                                                          const char key[],
                                                          const size_t len,
                                                          void *value);

/**
 * @brief Insert or update entry (wrapper around oa_hash_set_entry)
 *
 * @param[in,out] ht the hash table
 * @param[in] key the key to insert/update
 * @param[in] len the key length
 * @param[in] value the value to be assigned
 * @return value if successful, or NULL if no space left, in which case
 *     oa_hash_rehash() should be called
 */
OA_HASH_API void *oa_hash_set(struct oa_hash *ht,
                              const char key[],
                              const size_t len,
                              void *value);

/**
 * @brief Remove entry by key
 *
 * @param[in,out] ht the hash table
 * @param[in] key the key to be removed
 * @param[in] len the key length
 * @return 1 if found and removed, 0 otherwise
 */
OA_HASH_API int oa_hash_remove(struct oa_hash *ht,
                               const char key[],
                               const size_t len);

/**
 * @brief Rehash table to new buckets array
 *
 * @param[in,out] ht the hash table
 * @param[in,out] new_buckets the new buckets array
 * @param[in] new_capacity the new buckets capacity
 * @return pointer to old (now unused) bucket if successful, or NULL otherwise
 */
OA_HASH_API struct oa_hash_entry *oa_hash_rehash(
    struct oa_hash *ht,
    struct oa_hash_entry new_buckets[],
    const size_t new_capacity);

#ifndef OA_HASH_HEADER

#include <string.h>
#include <stdint.h>

OA_HASH_API void
oa_hash_init(struct oa_hash *ht,
             struct oa_hash_entry buckets[],
             const size_t capacity)
{
    memset(buckets, 0, sizeof(struct oa_hash_entry) * capacity);
    ht->buckets = buckets;
    ht->length = 0;
    ht->capacity = capacity;
}

OA_HASH_API void
oa_hash_cleanup(struct oa_hash *ht)
{
    if (!ht) return;

    ht->length = 0;
    ht->capacity = 0;
    ht->buckets = NULL;
}

static size_t
_oa_hash_genhash(const char key[], size_t len, const size_t capacity)
{
    const unsigned char *str = (const unsigned char *)key;
    unsigned long hash = 5381; /* DJB2 initial value */

    if (!key || !capacity) return 0;

    while (len--) {
        hash = ((hash & 0x7fffffff) << 5) + hash + *str++;
    }
    return hash % capacity;
}

OA_HASH_API const struct oa_hash_entry *
oa_hash_get_entry(const struct oa_hash *ht, const char key[], const size_t len)
{
    const size_t start_slot = _oa_hash_genhash(key, len, ht->capacity);
    size_t slot = start_slot;

    if (!len || !ht->capacity) return NULL;

    do {
        struct oa_hash_entry *entry = &ht->buckets[slot];

        if (entry->state == OA_HASH_ENTRY_EMPTY) {
            return NULL;
        }

        if (entry->state == OA_HASH_ENTRY_OCCUPIED && len == entry->key.length
            && 0 == memcmp(entry->key.buf, key, len))
        {
            return entry;
        }

        slot = (slot + 1) % ht->capacity;
    } while (slot != start_slot);

    return NULL;
}

OA_HASH_API void *
oa_hash_get(const struct oa_hash *ht, const char key[], const size_t len)
{
    const struct oa_hash_entry *entry = oa_hash_get_entry(ht, key, len);
    return entry ? entry->value : NULL;
}

OA_HASH_API const struct oa_hash_entry *
oa_hash_set_entry(struct oa_hash *ht,
                  const char key[],
                  const size_t len,
                  void *value)
{
    const size_t start_slot = _oa_hash_genhash(key, len, ht->capacity);
    size_t slot = start_slot;
    size_t first_deleted = SIZE_MAX;

    if (!len || !ht->capacity) return NULL;

    do {
        struct oa_hash_entry *entry = &ht->buckets[slot];

        if (entry->state != OA_HASH_ENTRY_OCCUPIED) {
            if (first_deleted == SIZE_MAX
                && entry->state == OA_HASH_ENTRY_DELETED)
            {
                first_deleted = slot;
            }
            if (entry->state == OA_HASH_ENTRY_EMPTY) {
                slot = (first_deleted != SIZE_MAX) ? first_deleted : slot;
                entry = &ht->buckets[slot];
                entry->key.buf = (char *)key;
                entry->key.length = len;
                entry->value = value;
                entry->state = OA_HASH_ENTRY_OCCUPIED;
                ht->length++;
                return entry;
            }
        }

        if (entry->state == OA_HASH_ENTRY_OCCUPIED && len == entry->key.length
            && 0 == memcmp(entry->key.buf, key, len))
        {
            entry->value = value;
            return entry;
        }

        slot = (slot + 1) % ht->capacity;
    } while (slot != start_slot);

    return NULL;
}

OA_HASH_API void *
oa_hash_set(struct oa_hash *ht,
            const char key[],
            const size_t len,
            void *value)
{
    const struct oa_hash_entry *entry = oa_hash_set_entry(ht, key, len, value);
    return entry ? entry->value : NULL;
}

OA_HASH_API int
oa_hash_remove(struct oa_hash *ht, const char key[], const size_t len)
{
    const size_t start_slot = _oa_hash_genhash(key, len, ht->capacity);
    size_t slot = start_slot;

    if (!len || !ht->capacity) return 0;

    do {
        struct oa_hash_entry *entry = &ht->buckets[slot];

        if (entry->state == OA_HASH_ENTRY_EMPTY) {
            return 0;
        }

        if (entry->state == OA_HASH_ENTRY_OCCUPIED && len == entry->key.length
            && 0 == memcmp(entry->key.buf, key, len))
        {
            entry->state = OA_HASH_ENTRY_DELETED;
            ht->length--;
            return 1;
        }

        slot = (slot + 1) % ht->capacity;
    } while (slot != start_slot);

    return 0;
}

OA_HASH_API struct oa_hash_entry *
oa_hash_rehash(struct oa_hash *ht,
               struct oa_hash_entry new_buckets[],
               const size_t new_capacity)
{
    struct oa_hash_entry *old_buckets = ht->buckets;
    const size_t old_capacity = ht->capacity;
    const size_t old_length = ht->length;
    size_t i;

    if (!new_buckets || new_capacity <= old_capacity) return 0;

    memset(new_buckets, 0, sizeof(struct oa_hash_entry) * new_capacity);

    /* temporarily switch to new buckets */
    ht->buckets = new_buckets;
    ht->capacity = new_capacity;
    ht->length = 0;

    for (i = 0; i < old_capacity; ++i) {
        if (old_buckets[i].state == OA_HASH_ENTRY_OCCUPIED
            && !oa_hash_set_entry(ht, old_buckets[i].key.buf,
                                  old_buckets[i].key.length,
                                  old_buckets[i].value))
        {
            /* restore original state on failure */
            ht->buckets = old_buckets;
            ht->capacity = old_capacity;
            ht->length = old_length;
            return NULL;
        }
    }
    return old_buckets;
}

#endif /* OA_HASH_HEADER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OA_HASH_H */
