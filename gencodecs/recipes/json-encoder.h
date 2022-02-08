#define JSON_ENCODER_int(b, buf, size, _var, _type)                           \
    if (0 > jsonb_number(b, buf, size, _var)) return 0
#define JSON_ENCODER_PTR_char(b, buf, size, _var, _type)                      \
    if (0 > jsonb_string(b, buf, size, _var, strlen(_var))) return 0
#define JSON_ENCODER_bool(b, buf, size, _var, _type)                          \
    if (0 > jsonb_bool(b, buf, size, _var)) return 0
#define JSON_ENCODER_STRUCT_PTR(b, buf, size, _var, _type)                    \
    if (!_##_type##_to_json(b, buf, size, _var)) return 0;

#ifdef GENCODECS_STRUCT_JSON_ENCODER
#ifdef GENCODECS_HEADER

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    size_t _type##_to_json(char buf[], size_t size, const struct _type *this);
#define GENCODECS_LIST_BEGIN(_type) GENCODECS_STRUCT_BEGIN(_type)
#include "gencodecs-gen.H"

#else

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    static size_t _##_type##_to_json(jsonb *b, char buf[], size_t size,       \
                                     const struct _type *this);
#define GENCODECS_LIST_BEGIN(_type) GENCODECS_STRUCT_BEGIN(_type)
#include "gencodecs-gen.H"

#define GENCODECS_COND_WRITE(_condition)                                      \
    if (_condition) {
#define GENCODECS_COND_END                                                    \
    }

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    static size_t _##_type##_to_json(jsonb *b, char buf[], size_t size,       \
                                     const struct _type *this)                \
    {                                                                         \
        if (0 > jsonb_object(b, buf, size)) return 0;                         \
        if (this != NULL) {
#define GENCODECS_FIELD_CUSTOM(_type, _decor, _name, _init, _cleanup,         \
                               _encoder, _decoder, _key, _default_value)      \
        if (0 > jsonb_key(b, buf, size, #_key, sizeof(#_key) - 1)) return 0;  \
        _encoder(b, buf, size, this->_name, _type);
#define GENCODECS_FIELD_PRINTF(_type, _scanf_type, _printf_type, _name)       \
        if (0 > jsonb_key(b, buf, size, #_name, sizeof(#_name) - 1))          \
            return 0;                                                         \
        else {                                                                \
            char tok[64];                                                     \
            int toklen;                                                       \
            toklen = sprintf(tok, "%" _printf_type, this->_name);             \
            if (0 > jsonb_string(b, buf, size, tok, toklen)) return 0;        \
        }
#define GENCODECS_STRUCT_END                                                  \
        }                                                                     \
        if (0 > jsonb_object_pop(b, buf, size)) return 0;                     \
        return b->pos;                                                        \
    }

#define GENCODECS_LIST_BEGIN(_type)                                           \
    static size_t _##_type##_to_json(jsonb *b, char buf[], size_t size,       \
                                     const struct _type *this)                \
    {                                                                         \
        if (0 > jsonb_array(b, buf, size)) return 0;                          \
        if (this != NULL) {                                                   \
            int i;
#define GENCODECS_LISTTYPE_PRIMITIVE(_type)                                   \
        for (i = 0; i < this->size; ++i) {                                    \
            JSON_ENCODER_##_type(b, buf, size, this->array[i], _type);        \
        }
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        for (i = 0; i < this->size; ++i)                                      \
            if (!_##_type##_to_json(b, buf, size, &this->array[i])) return 0;
#define GENCODECS_LISTTYPE_PTR(_type)                                         \
        for (i = 0; i < this->size; ++i) {                                    \
            JSON_ENCODER_PTR_##_type(b, buf, size, this->array[i], _type);    \
        }
#define GENCODECS_LIST_END                                                    \
        }                                                                     \
        if (0 > jsonb_array_pop(b, buf, size)) return 0;                      \
        return b->pos;                                                        \
    }

#include "gencodecs-gen.H"

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    size_t _type##_to_json(char buf[], size_t size, const struct _type *this) \
    {                                                                         \
        jsonb b;                                                              \
        jsonb_init(&b);                                                       \
        return _##_type##_to_json(&b, buf, size, this);                       \
    }
#define GENCODECS_LIST_BEGIN(_type)                                           \
    size_t _type##_to_json(char buf[], size_t size, const struct _type *this) \
    {                                                                         \
        jsonb b;                                                              \
        jsonb_init(&b);                                                       \
        return _##_type##_to_json(&b, buf, size, this);                       \
    }

#include "gencodecs-gen.H"

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_STRUCT_JSON_ENCODER */
