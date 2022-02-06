#define JSON_ENCODER_int(b, buf, size, _var, _type)                           \
    if (jsonb_number(b, buf, size, _var) < 0) return 0
#define JSON_ENCODER_PTR_char(b, buf, size, _var, _type)                      \
    if (jsonb_string(b, buf, size, _var, strlen(_var)) < 0) return 0
#define JSON_ENCODER_bool(b, buf, size, _var, _type)                          \
    if (jsonb_bool(b, buf, size, _var) < 0) return 0
#define JSON_ENCODER_STRUCT_PTR(b, buf, size, _var, _type)                    \
    if (!_##_type##_to_json(b, buf, size, _var)) return 0;

#ifdef GENCODECS_STRUCT_JSON_ENCODER
#ifdef GENCODECS_FORWARD

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    static size_t _##_type##_to_json(jsonb *b, char buf[], size_t size,       \
                                     const struct _type *p);
#define GENCODECS_STRUCT_END(_type)                                           \
    size_t _type##_to_json(char buf[], size_t size, const struct _type *p);

#define GENCODECS_LIST_BEGIN(_type)                                           \
    static size_t _##_type##_to_json(jsonb *b, char buf[], size_t size,       \
                                     const struct _type *p);
#define GENCODECS_LIST_END(_type)                                             \
    size_t _type##_to_json(char buf[], size_t size, const struct _type *p);

#include "gencodecs-gen.h"

#endif /* GENCODECS_FORWARD */

#define GENCODECS_IF(_name, _op, _value)                                      \
    if (p->_name _op _value) {
#define GENCODECS_ENDIF }

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    static size_t _##_type##_to_json(jsonb *b, char buf[], size_t size,       \
                                     const struct _type *p)                   \
    {                                                                         \
        if (jsonb_object(b, buf, size) < 0) return 0;                         \
        if (p != NULL) {
#define GENCODECS_FIELD_CUSTOM(_type, _decor, _name, _init, _cleanup,         \
                               _encoder, _decoder, _key, _default_value)      \
        if (jsonb_key(b, buf, size, #_key, sizeof(#_key) - 1) < 0) return 0;  \
        _encoder(b, buf, size, p->_name, _type);
#define GENCODECS_FIELD_PRINTF(_type, _scanf_type, _printf_type, _name)       \
        if (jsonb_key(b, buf, size, #_name, sizeof(#_name) - 1) < 0)          \
            return 0;                                                         \
        else {                                                                \
            char tok[64];                                                     \
            int toklen;                                                       \
            toklen = sprintf(tok, "%" _printf_type, p->_name);                \
            if (jsonb_string(b, buf, size, tok, toklen) < 0) return 0;        \
        }
#define GENCODECS_STRUCT_END(_type)                                           \
        }                                                                     \
        if (jsonb_object_pop(b, buf, size) < 0) return 0;                     \
        return b->pos;                                                        \
    }                                                                         \
                                                                              \
    size_t _type##_to_json(char buf[], size_t size, const struct _type *p)    \
    {                                                                         \
        jsonb b;                                                              \
        jsonb_init(&b);                                                       \
        return _##_type##_to_json(&b, buf, size, p);                          \
    }

#define GENCODECS_LIST_BEGIN(_type)                                           \
    static size_t _##_type##_to_json(jsonb *b, char buf[], size_t size,       \
                                     const struct _type *p)                   \
    {                                                                         \
        if (jsonb_array(b, buf, size) < 0) return 0;                          \
        if (p != NULL) {                                                      \
            int i;
#define GENCODECS_LISTTYPE_PRIMITIVE(_type)                                   \
        for (i = 0; i < p->size; ++i) {                                       \
            JSON_ENCODER_##_type(b, buf, size, p->array[i], _type);           \
        }
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        for (i = 0; i < p->size; ++i)                                         \
            if (!_##_type##_to_json(b, buf, size, &p->array[i])) return 0;
#define GENCODECS_LISTTYPE_PTR(_type)                                         \
        for (i = 0; i < p->size; ++i) {                                       \
            JSON_ENCODER_PTR_##_type(b, buf, size, p->array[i], _type);       \
        }
#define GENCODECS_LIST_END(_type)                                             \
        }                                                                     \
        if (jsonb_array_pop(b, buf, size) < 0) return 0;                      \
        return b->pos;                                                        \
    }                                                                         \
                                                                              \
    size_t _type##_to_json(char buf[], size_t size, const struct _type *p)    \
    {                                                                         \
        jsonb b;                                                              \
        jsonb_init(&b);                                                       \
        return _##_type##_to_json(&b, buf, size, p);                          \
    }

#include "gencodecs-gen.h"

#undef GENCODECS_STRUCT_JSON_ENCODER
#endif /* GENCODECS_STRUCT_JSON_ENCODER */
