#define GENCODECS_JSON_DECODER_int(_f, _var, _type)                           \
    if (_f && _f->type == JSMN_PRIMITIVE)                                     \
        _var = (int)strtol(_f->value.contents, NULL, 10)
#define GENCODECS_JSON_DECODER_bool(_f, _var, _type)                          \
    if (_f && _f->type == JSMN_PRIMITIVE)                                     \
        _var = ('t' == *_f->value.contents)
#define GENCODECS_JSON_DECODER_PTR_char(_f, _var, _type)                      \
    if (_f && _f->type == JSMN_STRING) {                                      \
        long _ret;                                                            \
        _var = calloc(1, _f->value.length);                                   \
        if (NULL == _var) return JSMN_ERROR_NOMEM;                            \
        _ret = jsmnf_unescape(_var, _f->value.length, _f->value.contents,     \
                              _f->value.length);                              \
        if (_ret < 0) return _ret;                                            \
        ret += _ret;                                                          \
    }
#define GENCODECS_JSON_DECODER_STRUCT_PTR(_f, _var, _type)                    \
    if (_f && (_f->type == JSMN_OBJECT || _f->type == JSMN_ARRAY)) {          \
        long _ret;                                                            \
        _var = calloc(1, sizeof *_var);                                       \
        if (NULL == _var) return JSMN_ERROR_NOMEM;                            \
        _ret = _type##_from_jsmnf(_f, _var);                                  \
        if (_ret < 0) return _ret;                                            \
        ret += sizeof *_var + _ret;                                           \
    }

#ifdef GENCODECS_JSON_DECODER
#ifdef GENCODECS_HEADER

#define GENCODECS_PUB_STRUCT(_type)                                           \
    long _type##_from_jsmnf(jsmnf_pair *root, struct _type *this);            \
    size_t _type##_from_json(const char buf[], size_t size,                   \
                             struct _type *this);
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.pre.h"

#elif defined(GENCODECS_FORWARD)

#define GENCODECS_STRUCT(_type)                                               \
    static long _type##_from_jsmnf(jsmnf_pair *root, struct _type *this);
#define GENCODECS_LIST(_type) GENCODECS_STRUCT(_type)

#include "gencodecs-gen.pre.h"

#else

#define GENCODECS_PUB_STRUCT(_type)                                           \
    long _type##_from_jsmnf(jsmnf_pair *root, struct _type *this)             \
    {                                                                         \
        jsmnf_pair *f;                                                        \
        long ret = 0;
#define GENCODECS_STRUCT(_type)                                               \
    static GENCODECS_PUB_STRUCT(_type)
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        f = jsmnf_find(root, _key, sizeof(_key) - 1);                         \
        _decoder(f, this->_name, _type);
#define GENCODECS_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)       \
        f = jsmnf_find(root, #_name, sizeof(#_name) - 1);                     \
        if (f) sscanf(f->value.contents, _scanf_type, &this->_name);
#define GENCODECS_STRUCT_END                                                  \
        return ret;                                                           \
    }

#define GENCODECS_PUB_LIST(_type)                                             \
    long _type##_from_jsmnf(jsmnf_pair *root, struct _type *this)             \
    {                                                                         \
        long ret = sizeof *this * root->length;                               \
        int i;                                                                \
        if (!ret) return 0;
#define GENCODECS_LIST(_type)                                                 \
    static GENCODECS_PUB_LIST(_type)
#define GENCODECS_LISTTYPE(_type)                                             \
        __carray_init(this, root->length, _type, , );                         \
        for (i = 0; i < root->length; ++i) {                                  \
            jsmnf_pair *f = root->buckets + i;                                \
            _type o;                                                          \
            GENCODECS_JSON_DECODER_##_type(f, o, _type);                      \
            carray_insert(this, i, o);                                        \
        }

#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        __carray_init(this, root->length, struct _type, , );                  \
        for (i = 0; i < root->length; ++i) {                                  \
            jsmnf_pair *f = root->buckets + i;                                \
            struct _type o = { 0 };                                           \
            long _ret = _type##_from_jsmnf(f, &o);                            \
            if (_ret < 0) return _ret;                                        \
            ret += _ret;                                                      \
            carray_insert(this, i, o);                                        \
        }
#define GENCODECS_LISTTYPE_PTR(_type, _decor)                                 \
        __carray_init(this, root->length, _type _decor, , );                  \
        for (i = 0; i < root->length; ++i) {                                  \
            jsmnf_pair *f = root->buckets + i;                                \
            _type *o;                                                         \
            GENCODECS_JSON_DECODER_PTR_##_type(f, o, _type);                  \
            carray_insert(this, i, o);                                        \
        }
#define GENCODECS_LIST_END                                                    \
        return ret;                                                           \
    }

#include "gencodecs-gen.pre.h"

#define GENCODECS_PUB_STRUCT(_type)                                           \
    size_t _type##_from_json(const char buf[], size_t size,                   \
                             struct _type *this)                              \
    {                                                                         \
        size_t nbytes = 0;                                                    \
        jsmn_parser parser;                                                   \
        jsmntok_t tokens[256];                                                \
        jsmn_init(&parser);                                                   \
        if (0 < jsmn_parse(&parser, buf, size, tokens,                        \
                           sizeof(tokens) / sizeof *tokens)) {                \
            jsmnf_loader loader;                                              \
            jsmnf_pair pairs[256];                                            \
            long ret;                                                         \
            jsmnf_init(&loader);                                              \
            ret = jsmnf_load(&loader, buf, tokens, parser.toknext, pairs,     \
                             sizeof(pairs) / sizeof *pairs);                  \
            if (0 < ret && 0 < (ret = _type##_from_jsmnf(pairs, this)))       \
                nbytes = ret;                                                 \
        }                                                                     \
        return nbytes;                                                        \
    }
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.pre.h"

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_JSON_DECODER */
