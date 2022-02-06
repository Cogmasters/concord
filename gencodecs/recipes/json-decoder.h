#ifdef GENCODECS_STRUCT_JSON_DECODER
#ifdef GENCODECS_FORWARD

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    static size_t _##_type##_from_json(jsmnfind *root, const char buf[],      \
                                       struct _type *p);
#define GENCODECS_STRUCT_END(_type)                                           \
    size_t _type##_from_json(const char buf[], size_t size, struct _type *p);

#define GENCODECS_LIST_BEGIN(_type)                                           \
    static size_t _##_type##_from_json(jsmnfind *root, const char buf[],      \
                                       struct _type *p);
#define GENCODECS_LIST_END(_type)                                             \
    size_t _type##_from_json(const char buf[], size_t size, struct _type *p);

#include "gencodecs-gen.h"

#endif /* GENCODECS_FORWARD */

#define JSON_DECODER_int(f, buf, _var, _type)                                 \
    if (f && f->val->type == JSMN_PRIMITIVE)                                  \
    _var = (int)strtol(buf + f->val->start, NULL, 10)
#define JSON_DECODER_bool(f, buf, _var, _type)                                \
    if (f && f->val->type == JSMN_PRIMITIVE) _var = ('t' == buf[f->val->start])
#define JSON_DECODER_PTR_char(f, buf, _var, _type)                            \
    if (f && f->val->type == JSMN_STRING)                                     \
    _var = strndup(buf + f->val->start, f->val->end - f->val->start)
#define JSON_DECODER_STRUCT_PTR(f, buf, _var, _type)                          \
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {   \
        _var = calloc(1, sizeof *_var);                                       \
        ret += _##_type##_from_json(f, buf, _var);                            \
    }

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    static size_t _##_type##_from_json(jsmnfind *root, const char buf[],      \
                                       struct _type *p)                       \
    {                                                                         \
        jsmnfind *f;                                                          \
        size_t ret = 0;
#define GENCODECS_FIELD_CUSTOM(_type, _decor, _name, _init, _cleanup,         \
                               _encoder, _decoder, _key)                      \
    f = jsmnfind_find(root, #_key, sizeof(#_key) - 1);                        \
    _decoder(f, buf, p->_name, _type);
#define GENCODECS_FIELD_PRINTF(_type, _scanf_type, _printf_type, _name)       \
    f = jsmnfind_find(root, #_name, sizeof(#_name) - 1);                      \
    if (f && f->val->type == JSMN_STRING)                                     \
        sscanf(buf + f->val->start, "%" _scanf_type, &p->_name);
#define GENCODECS_STRUCT_END(_type)                                           \
    return ret;                                                               \
    }                                                                         \
                                                                              \
    size_t _type##_from_json(const char buf[], size_t size, struct _type *p)  \
    {                                                                         \
        jsmnfind *root = jsmnfind_init();                                     \
        int ret = jsmnfind_start(root, buf, size);                            \
        if (ret >= 0) ret = _##_type##_from_json(root, buf, p);               \
        jsmnfind_cleanup(root);                                               \
        return ret;                                                           \
    }

#define GENCODECS_LIST_BEGIN(_type)                                           \
    static size_t _##_type##_from_json(jsmnfind *root, const char buf[],      \
                                       struct _type *p)                       \
    {                                                                         \
        jsmnfind *f, *tmp;                                                    \
        size_t ret = 0;
#define GENCODECS_LISTTYPE_PRIMITIVE(_type)                                   \
    __carray_init(p, _type, , );                                              \
    HASH_ITER(hh, root->child, f, tmp)                                        \
    {                                                                         \
        _type o;                                                              \
        JSON_DECODER_##_type(f, buf, o, _type);                               \
        carray_insert(p, f->idx, o);                                          \
    }
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
    __carray_init(p, struct _type, , );                                       \
    HASH_ITER(hh, root->child, f, tmp)                                        \
    {                                                                         \
        struct _type o = { 0 };                                               \
        ret += _##_type##_from_json(f, buf, &o);                              \
        carray_insert(p, f->idx, o);                                          \
    }
#define GENCODECS_LISTTYPE_PTR(_type)                                         \
    __carray_init(p, _type *, , );                                            \
    HASH_ITER(hh, root->child, f, tmp)                                        \
    {                                                                         \
        _type *o;                                                             \
        JSON_DECODER_PTR_##_type(f, buf, o, _type);                           \
        carray_insert(p, f->idx, o);                                          \
    }
#define GENCODECS_LIST_END(_type)                                             \
    return ret;                                                               \
    }                                                                         \
                                                                              \
    size_t _type##_from_json(const char buf[], size_t size, struct _type *p)  \
    {                                                                         \
        jsmnfind *root = jsmnfind_init();                                     \
        size_t ret = 0;                                                       \
        if (jsmnfind_start(root, buf, size) > 0)                              \
            ret = _##_type##_from_json(root, buf, p);                         \
        jsmnfind_cleanup(root);                                               \
        return ret;                                                           \
    }

#include "gencodecs-gen.h"

#undef GENCODECS_STRUCT_JSON_DECODER
#endif /* GENCODECS_STRUCT_JSON_DECODER */
