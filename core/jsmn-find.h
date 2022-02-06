#ifndef JSMN_FIND_H
#define JSMN_FIND_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef JSMN_H
#error "jsmn-find.h should be included after jsmn.h"
#endif

#include "uthash.h"

/** @brief store key/value jsmn tokens in a hashtable */
typedef struct jsmnfind {
    /** the key of the pair (null if root) */
    jsmntok_t *key;
    /** the value of the pair (null if unexistent) */
    jsmntok_t *val;
    /** the positional index of the pair */
    int idx;
    /** this structure fields */
    struct jsmnfind *child;
    /** make this structure fields hashable */
    UT_hash_handle hh;
} jsmnfind;

/**
 * @brief Initialize a @ref jsmnfind root
 *
 * @return a @ref jsmnfind root that should be cleanup up with
 *      jsmnfind_cleanup()
 */
JSMN_API jsmnfind *jsmnfind_init(void);

/**
 * @brief Cleanup a @ref jsmnfind handle
 *
 * @param root the @ref jsmnfind root initialized with jsmnfind_init()
 */
JSMN_API void jsmnfind_cleanup(jsmnfind *root);

/**
 * @brief Populate the @ref jsmnfind root with jsmn tokens
 *
 * @param root the @ref jsmnfind structure initialized with jsmnfind_init()
 * @param json the raw JSON string
 * @param size the raw JSON length
 * @return a negative number for error, or the number of tokens found
 */
JSMN_API int jsmnfind_start(jsmnfind *root, const char json[], size_t size);

/**
 * @brief Find a value `jsmntok_t` by its key
 *
 * @param root the @ref jsmnfind structure initialized with jsmnfind_init()
 * @param key the key too be matched
 * @param size size of the key too be matched
 * @return the key/value pair matched to `key`
 */
JSMN_API jsmnfind *jsmnfind_find(jsmnfind *root, const char key[], size_t size);

/**
 * @brief Find a value `jsmntok_t` by its key path
 *
 * @param root the @ref jsmnfind structure initialized with jsmnfind_init()
 * @param path an array of key path strings, from least to highest depth
 * @param depth the depth level of the last `path` key
 * @return the key/value pair matched to `path`
 */
JSMN_API jsmnfind *jsmnfind_find_path(jsmnfind *root,
                                      char *const path[],
                                      int depth);

#ifndef JSMN_HEADER
#include <stdio.h>
#include <stdlib.h>

struct _jsmnroot {
    /**
     * the root jsmnfind
     * @note `root` must be the first element so that `struct _jsmnroot` can be
     *      safely cast to `struct jsmnfind` */
    jsmnfind root;
    /** tokens storage cap */
    size_t real_ntoks;
    /** amount of tokens currently stored */
    size_t ntoks;
};

static jsmnfind *
_jsmnfind_init(void)
{
    return calloc(1, sizeof(jsmnfind));
}

jsmnfind *
jsmnfind_init(void)
{
    struct _jsmnroot *r = calloc(1, sizeof *r);
    if (!r) return NULL;

    r->real_ntoks = 128;
    r->root.val = malloc(r->real_ntoks * sizeof *r->root.val);
    if (!r->root.val) {
        free(r);
        return NULL;
    }
    return &r->root;
}

static void
_jsmnfind_cleanup(jsmnfind *head)
{
    if (!head) return;

    if (JSMN_OBJECT == head->val->type || JSMN_ARRAY == head->val->type) {
        jsmnfind *iter, *tmp;

        HASH_ITER(hh, head->child, iter, tmp)
        {
            HASH_DEL(head->child, iter);
            _jsmnfind_cleanup(iter);
            free(iter);
        }
    }
}

void
jsmnfind_cleanup(jsmnfind *root)
{
    _jsmnfind_cleanup(root);
    free(root->val);
    free(root);
}

static int
_jsmnfind_get_pairs(const char js[],
                    jsmntok_t *tok,
                    size_t ntoks,
                    jsmnfind *head)
{
    int offset = 0;

    if (!ntoks) return 0;

    switch (tok->type) {
    case JSMN_OBJECT: {
        jsmnfind *curr;
        int ret;
        int i;

        for (i = 0; i < tok->size; ++i) {
            curr = _jsmnfind_init();
            curr->idx = i;
            curr->key = tok + 1 + offset;

            ret = _jsmnfind_get_pairs(js, curr->key, ntoks - offset, curr);
            if (ret < 0) return ret;

            offset += ret;

            if (curr->key->size > 0) {
                curr->val = tok + 1 + offset;

                ret = _jsmnfind_get_pairs(js, curr->val, ntoks - offset, curr);
                if (ret < 0) return ret;

                offset += ret;
            }

            HASH_ADD_KEYPTR(hh, head->child, js + curr->key->start,
                            curr->key->end - curr->key->start, curr);
        }
    } break;
    case JSMN_ARRAY: {
        jsmnfind *curr;
        int ret;
        int i;

        for (i = 0; i < tok->size; ++i) {
            curr = _jsmnfind_init();
            curr->idx = i;
            curr->val = tok + 1 + offset;

            ret = _jsmnfind_get_pairs(js, curr->val, ntoks - offset, curr);
            if (ret < 0) return ret;

            offset += ret;

            HASH_ADD_INT(head->child, idx, curr);
        }
    } break;
    case JSMN_STRING:
    case JSMN_PRIMITIVE:
        break;
    case JSMN_UNDEFINED:
    default:
        fprintf(stderr, "Unexpected key: %.*s\n", tok->end - tok->start,
                js + tok->start);
        return -1;
    }
    return offset + 1;
}

int
jsmnfind_start(jsmnfind *root, const char js[], size_t size)
{
    struct _jsmnroot *r = (struct _jsmnroot *)root;
    jsmn_parser parser;
    int ret;

    /* Prepare parser */
    jsmn_init(&parser);
    while (1) {
        ret = jsmn_parse(&parser, js, size, root->val, r->real_ntoks);

        if (ret >= 0) {
            r->ntoks = parser.toknext;
            ret = _jsmnfind_get_pairs(js, root->val, r->ntoks, root);
            break;
        }
        else {
            if (ret != JSMN_ERROR_NOMEM) {
                break;
            }
            else {
                size_t new_ntoks = r->real_ntoks * 2;
                void *tmp;

                tmp = realloc(root->val, new_ntoks * sizeof *root->val);
                if (!tmp) return JSMN_ERROR_NOMEM;

                r->real_ntoks = new_ntoks;
                root->val = tmp;
            }
        }
    }
    return ret;
}

jsmnfind *
jsmnfind_find(jsmnfind *head, const char key[], size_t size)
{
    jsmnfind *found = NULL;

    if (!key || !head) return NULL;

    if (JSMN_OBJECT == head->val->type) {
        HASH_FIND(hh, head->child, key, size, found);
    }
    else if (JSMN_ARRAY == head->val->type) {
        char *endptr;
        int idx = (int)strtol(key, &endptr, 10);

        if (endptr == key) return NULL;

        HASH_FIND_INT(head->child, &idx, found);
    }
    return found;
}

jsmnfind *
jsmnfind_find_path(jsmnfind *head, char *const path[], int depth)
{
    jsmnfind *iter = head, *found = NULL;
    int i;

    for (i = 0; i < depth; ++i) {
        if (!iter) continue;
        found = jsmnfind_find(iter, path[i], strlen(path[i]));
        if (!found) break;
        iter = found;
    }
    return found;
}
#endif /* JSMN_HEADER */

#ifdef __cplusplus
}
#endif

#endif /* JSMN_FIND_H */
