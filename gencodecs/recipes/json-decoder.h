#define GENCODECS_JSON_DECODER_int(f, buf, _var, _type)                       \
    if (f && f->val->type == JSMN_PRIMITIVE)                                  \
        _var = (int)strtol(buf + f->val->start, NULL, 10)
#define GENCODECS_JSON_DECODER_bool(f, buf, _var, _type)                      \
    if (f && f->val->type == JSMN_PRIMITIVE) _var = ('t' == buf[f->val->start])
#define GENCODECS_JSON_DECODER_PTR_char(f, buf, _var, _type)                  \
    if (f && f->val->type == JSMN_STRING)                                     \
        ret += jsmnf_unescape(&_var, buf + f->val->start,                     \
                              f->val->end - f->val->start)
#define GENCODECS_JSON_DECODER_STRUCT_PTR(f, buf, _var, _type)                \
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {   \
        _var = calloc(1, sizeof *_var);                                       \
        ret += sizeof *_var + _type##_from_jsmnf(f, buf, _var);               \
    }

#ifdef GENCODECS_JSON_DECODER
#ifdef GENCODECS_HEADER

#define GENCODECS_PUB_STRUCT(_type)                                            \
    size_t _type##_from_jsmnf(jsmnf *root, const char buf[],                   \
                              struct _type *this);                             \
    size_t _type##_from_json(const char buf[], size_t size, struct _type *this);
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.pre.h"

#elif defined(GENCODECS_FORWARD)

#define GENCODECS_STRUCT(_type)                                               \
    static size_t _type##_from_jsmnf(jsmnf *root, const char buf[],           \
                                       struct _type *this);
#define GENCODECS_LIST(_type) GENCODECS_STRUCT(_type)

#include "gencodecs-gen.pre.h"

#else

#define GENCODECS_PUB_STRUCT(_type)                                           \
    size_t _type##_from_jsmnf(jsmnf *root, const char buf[],                  \
                                       struct _type *this)                    \
    {                                                                         \
        jsmnf *f;                                                             \
        size_t ret = 0;
#define GENCODECS_STRUCT(_type)                                               \
    static GENCODECS_PUB_STRUCT(_type)
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        f = jsmnf_find(root, _key, sizeof(_key) - 1);                         \
        _decoder(f, buf, this->_name, _type);
#define GENCODECS_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)       \
        f = jsmnf_find(root, #_name, sizeof(#_name) - 1);                     \
        if (f) sscanf(buf + f->val->start, _scanf_type, &this->_name);
#define GENCODECS_STRUCT_END                                                  \
        return ret;                                                           \
    }

#define GENCODECS_PUB_LIST(_type)                                             \
    size_t _type##_from_jsmnf(jsmnf *root, const char buf[],                  \
                                       struct _type *this)                    \
    {                                                                         \
        jsmnf *f, *tmp;                                                       \
        size_t ret, nelems = HASH_COUNT(root->child);                         \
        if (!nelems) return 0;                                                \
        ret = sizeof *this * nelems;
#define GENCODECS_LIST(_type)                                                 \
    static GENCODECS_PUB_LIST(_type)
#define GENCODECS_LISTTYPE(_type)                                             \
        __carray_init(this, nelems, _type, , );                               \
        HASH_ITER(hh, root->child, f, tmp) {                                  \
            _type o;                                                          \
            GENCODECS_JSON_DECODER_##_type(f, buf, o, _type);                 \
            carray_insert(this, f->idx, o);                                   \
        }
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        __carray_init(this, nelems, struct _type, , );                        \
        HASH_ITER(hh, root->child, f, tmp) {                                  \
            struct _type o = { 0 };                                           \
            ret += _type##_from_jsmnf(f, buf, &o);                            \
            carray_insert(this, f->idx, o);                                   \
        }
#define GENCODECS_LISTTYPE_PTR(_type, _decor)                                 \
        __carray_init(this, nelems, _type _decor, , );                        \
        HASH_ITER(hh, root->child, f, tmp) {                                  \
            _type *o;                                                         \
            GENCODECS_JSON_DECODER_PTR_##_type(f, buf, o, _type);             \
            carray_insert(this, f->idx, o);                                   \
        }
#define GENCODECS_LIST_END                                                    \
        return ret;                                                           \
    }

#include "gencodecs-gen.pre.h"

#define GENCODECS_PUB_STRUCT(_type)                                           \
    size_t _type##_from_json(const char buf[], size_t size,                   \
                             struct _type *this)                              \
    {                                                                         \
        jsmnf *root = jsmnf_init();                                           \
        int ret = jsmnf_start(root, buf, size);                               \
        if (ret >= 0) ret = _type##_from_jsmnf(root, buf, this);              \
        jsmnf_cleanup(root);                                                  \
        return ret;                                                           \
    }
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.pre.h"

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_JSON_DECODER */
