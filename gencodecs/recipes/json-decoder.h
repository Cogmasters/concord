#define GENCODECS_JSON_DECODER_int(_f, _js, _var, _type)                      \
    if (_f->v->type == JSMN_PRIMITIVE)                                        \
    _var = (int)strtol(_js + _f->v->start, NULL, 10)
#define GENCODECS_JSON_DECODER_bool(_f, _js, _var, _type)                     \
    if (_f->v->type == JSMN_PRIMITIVE) _var = ('t' == _js[_f->v->start])
#define GENCODECS_JSON_DECODER_PTR_char(_f, _js, _var, _type)                 \
    if (_f->v->type == JSMN_STRING) {                                         \
        long _ret;                                                            \
        if (!(_var = discord_calloc(1, _f->v->end - _f->v->start + 1)))       \
            return JSMN_ERROR_NOMEM;                                          \
        if (0 > (_ret = jsmnf_unescape(_var, _f->v->end - _f->v->start,       \
                                       _js + _f->v->start,                    \
                                       _f->v->end - _f->v->start)))           \
            return discord_free(_var), _ret;                                  \
        ret += _ret;                                                          \
    }
#define GENCODECS_JSON_DECODER_STRUCT_PTR(_f, _js, _var, _type)               \
    if (_f->v->type == JSMN_OBJECT) {                                         \
        long _ret;                                                            \
        if (!(_var = discord_calloc(1, sizeof *_var)))                        \
            return JSMN_ERROR_NOMEM;                                          \
        if ((_ret = _type##_from_jsmnf(_f, _js, _var)) < 0) return _ret;      \
        ret += sizeof *_var + _ret;                                           \
    }                                                                         \
    else if (_f->v->type == JSMN_ARRAY) {                                     \
        long _ret;                                                            \
        if (!(_var = discord_calloc(_f->length, sizeof *_var)))               \
            return JSMN_ERROR_NOMEM;                                          \
        if ((_ret = _type##_from_jsmnf(_f, _js, _var)) < 0) return _ret;      \
        ret += sizeof *_var + _ret;                                           \
    }

#ifdef GENCODECS_JSON_DECODER
#ifdef GENCODECS_HEADER

#define GENCODECS_PUB_STRUCT(_type)                                           \
    long _type##_from_jsmnf(const jsmnf_pair *root, const char *js,           \
                            struct _type *self);                              \
    long _type##_from_json(const char buf[], size_t size, struct _type *self);

#include "gencodecs-gen.PRE.h"

#elif defined(GENCODECS_FORWARD)

#define GENCODECS_STRUCT(_type)                                               \
    static long _type##_from_jsmnf(const jsmnf_pair *root, const char *js,    \
                                   struct _type *self);

#include "gencodecs-gen.PRE.h"

#else

#define GENCODECS_PUB_STRUCT(_type)                                           \
    long _type##_from_jsmnf(const jsmnf_pair *root, const char *js,           \
                            struct _type *self)                               \
    {                                                                         \
        const long length = root->v->type == JSMN_ARRAY ? root->length : 1;   \
        const jsmnf_pair *start =                                             \
            root->v->type == JSMN_ARRAY ? root->fields : root;                \
        long ret = 0;                                                         \
        for (long i = 0; i < length; ++i) {                                   \
            const jsmnf_pair *f;
#define GENCODECS_STRUCT(_type) static GENCODECS_PUB_STRUCT(_type)
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
    if ((f = jsmnf_find(start, _key, sizeof(_key) - 1))) {                    \
        _decoder(f, js, self->_name, _type);                                  \
    }
#define GENCODECS_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)       \
    if ((f = jsmnf_find(start, #_name, sizeof(#_name) - 1))) {                \
        sscanf(js + f->v->start, _scanf_type, &self->_name);                  \
    }
#define GENCODECS_STRUCT_END                                                  \
    }                                                                         \
    return ret;                                                               \
    }

#include "gencodecs-gen.PRE.h"

#define GENCODECS_PUB_STRUCT(_type)                                           \
    long _type##_from_json(const char buf[], size_t size, struct _type *self) \
    {                                                                         \
        long retval = 0;                                                      \
        size_t table_len = 0;                                                 \
        jsmnf_loader loader;                                                  \
        jsmnf_table *table = NULL;                                            \
        jsmnf_init(&loader);                                                  \
        if (jsmnf_load_auto(&loader, buf, size, &table, &table_len) > 0) {    \
            retval = _type##_from_jsmnf(loader.root, buf, self);              \
            free(table);                                                      \
        }                                                                     \
        return retval > 0 ? retval : JSMN_ERROR_INVAL;                        \
    }

#include "gencodecs-gen.PRE.h"

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_JSON_DECODER */
