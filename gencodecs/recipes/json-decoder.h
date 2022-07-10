#define GENCODECS_JSON_DECODER_int(_f, _js, _var, _type)                      \
    if (_f && _f->type == JSMN_PRIMITIVE)                                     \
        _var = (int)strtol(_js + _f->v.pos, NULL, 10)
#define GENCODECS_JSON_DECODER_bool(_f, _js, _var, _type)                     \
    if (_f && _f->type == JSMN_PRIMITIVE)                                     \
        _var = ('t' == _js[_f->v.pos])
#define GENCODECS_JSON_DECODER_PTR_char(_f, _js, _var, _type)                 \
    if (_f && _f->type == JSMN_STRING) {                                      \
        long _ret;                                                            \
        _var = calloc(1, _f->v.len + 1);                                      \
        if (NULL == _var) return JSMN_ERROR_NOMEM;                            \
        _ret = jsmnf_unescape(_var, _f->v.len, _js + _f->v.pos, _f->v.len);   \
        if (_ret < 0) return _ret;                                            \
        ret += _ret;                                                          \
    }
#define GENCODECS_JSON_DECODER_STRUCT_PTR(_f, _js, _var, _type)               \
    if (_f && (_f->type == JSMN_OBJECT || _f->type == JSMN_ARRAY)) {          \
        long _ret;                                                            \
        _var = calloc(1, sizeof *_var);                                       \
        if (NULL == _var) return JSMN_ERROR_NOMEM;                            \
        _ret = _type##_from_jsmnf(_f, _js, _var);                             \
        if (_ret < 0) return _ret;                                            \
        ret += sizeof *_var + _ret;                                           \
    }

#ifdef GENCODECS_JSON_DECODER
#ifdef GENCODECS_HEADER

#define GENCODECS_PUB_STRUCT(_type)                                           \
    long _type##_from_jsmnf(jsmnf_pair *root, const char *js,                 \
                            struct _type *self);                              \
    size_t _type##_from_json(const char buf[], size_t size,                   \
                             struct _type *self);
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.PRE.h"

#elif defined(GENCODECS_FORWARD)

#define GENCODECS_STRUCT(_type)                                               \
    static long _type##_from_jsmnf(jsmnf_pair *root, const char *js,          \
                                   struct _type *self);
#define GENCODECS_LIST(_type) GENCODECS_STRUCT(_type)

#include "gencodecs-gen.PRE.h"

#else

#define GENCODECS_PUB_STRUCT(_type)                                           \
    long _type##_from_jsmnf(jsmnf_pair *root, const char *js,                 \
                            struct _type *self)                               \
    {                                                                         \
        jsmnf_pair *f;                                                        \
        long ret = 0;
#define GENCODECS_STRUCT(_type)                                               \
    static GENCODECS_PUB_STRUCT(_type)
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        f = jsmnf_find(root, js, _key, sizeof(_key) - 1);                     \
        _decoder(f, js, self->_name, _type);
#define GENCODECS_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)       \
        f = jsmnf_find(root, js, #_name, sizeof(#_name) - 1);                 \
        if (f) sscanf(js + f->v.pos, _scanf_type, &self->_name);
#define GENCODECS_STRUCT_END                                                  \
        return ret;                                                           \
    }

#define GENCODECS_PUB_LIST(_type)                                             \
    long _type##_from_jsmnf(jsmnf_pair *root, const char *js,                 \
                            struct _type *self)                               \
    {                                                                         \
        long ret = sizeof *self * root->size;                                 \
        int i;                                                                \
        if (!ret) return 0;
#define GENCODECS_LIST(_type)                                                 \
    static GENCODECS_PUB_LIST(_type)
#define GENCODECS_LISTTYPE(_type)                                             \
        __carray_init(self, root->size, _type, , );                           \
        for (i = 0; i < root->size; ++i) {                                    \
            jsmnf_pair *f = root->fields + i;                                 \
            _type o;                                                          \
            GENCODECS_JSON_DECODER_##_type(f, js, o, _type);                  \
            carray_insert(self, i, o);                                        \
        }

#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        __carray_init(self, root->size, struct _type, , );                    \
        for (i = 0; i < root->size; ++i) {                                    \
            jsmnf_pair *f = root->fields + i;                                 \
            struct _type o = { 0 };                                           \
            long _ret = _type##_from_jsmnf(f, js, &o);                        \
            if (_ret < 0) return _ret;                                        \
            ret += _ret;                                                      \
            carray_insert(self, i, o);                                        \
        }
#define GENCODECS_LISTTYPE_PTR(_type, _decor)                                 \
        __carray_init(self, root->size, _type _decor, , );                    \
        for (i = 0; i < root->size; ++i) {                                    \
            jsmnf_pair *f = root->fields + i;                                 \
            _type *o;                                                         \
            GENCODECS_JSON_DECODER_PTR_##_type(f, js, o, _type);              \
            carray_insert(self, i, o);                                        \
        }
#define GENCODECS_LIST_END                                                    \
        return ret;                                                           \
    }

#include "gencodecs-gen.PRE.h"

#define GENCODECS_PUB_STRUCT(_type)                                           \
    size_t _type##_from_json(const char buf[], size_t size,                   \
                             struct _type *self)                              \
    {                                                                         \
        size_t nbytes = 0;                                                    \
        jsmn_parser parser;                                                   \
        jsmntok_t *tokens = NULL;                                             \
        unsigned tmp = 0;                                                     \
        jsmn_init(&parser);                                                   \
        if (0 < jsmn_parse_auto(&parser, buf, size, &tokens, &tmp)) {         \
            jsmnf_loader loader;                                              \
            jsmnf_pair *pairs = NULL;                                         \
            tmp = 0;                                                          \
            jsmnf_init(&loader);                                              \
            if (0 < jsmnf_load_auto(&loader, buf, tokens, parser.toknext,     \
                                    &pairs, &tmp)) {                          \
                long ret;                                                     \
                if (0 < (ret = _type##_from_jsmnf(pairs, buf, self)))         \
                    nbytes = ret;                                             \
                free(pairs);                                                  \
            }                                                                 \
            free(tokens);                                                     \
        }                                                                     \
        return nbytes;                                                        \
    }
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.PRE.h"

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_JSON_DECODER */
