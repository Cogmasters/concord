#define JSON_ENCODER_int(b, buf, size, _var, _type)                           \
    if (0 > (code = jsonb_number(b, buf, size, _var))) return code
#define JSON_ENCODER_PTR_char(b, buf, size, _var, _type)                      \
    if (0 > (code = jsonb_string(b, buf, size, _var,                          \
                                 _var ? strlen(_var) : 0)))                   \
        return code
#define JSON_ENCODER_bool(b, buf, size, _var, _type)                          \
    if (0 > (code = jsonb_bool(b, buf, size, _var))) return code
#define JSON_ENCODER_STRUCT_PTR(b, buf, size, _var, _type)                    \
    if (0 > (code = _type##_to_jsonb(b, buf, size, _var))) return code

#ifdef GENCODECS_JSON_ENCODER
#ifdef GENCODECS_HEADER

#define GENCODECS_PUB_STRUCT(_type)                                           \
    jsonbcode _type##_to_jsonb(jsonb *b, char buf[], size_t size,             \
                              const struct _type *this);                      \
    size_t _type##_to_json(char buf[], size_t size, const struct _type *this);
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.pre.h"

#elif defined(GENCODECS_FORWARD)

#define GENCODECS_STRUCT(_type)                                               \
    static jsonbcode _type##_to_jsonb(jsonb *b, char buf[], size_t size,      \
                                         const struct _type *this);
#define GENCODECS_LIST(_type) GENCODECS_STRUCT(_type)

#include "gencodecs-gen.pre.h"

#else

#define GENCODECS_COND_WRITE(_condition)                                      \
    if (_condition) {
#define GENCODECS_COND_END                                                    \
    }

#define GENCODECS_PUB_STRUCT(_type)                                           \
    jsonbcode _type##_to_jsonb(jsonb *b, char buf[], size_t size,             \
                                         const struct _type *this)            \
    {                                                                         \
        jsonbcode code;                                                       \
        if (0 > (code = jsonb_object(b, buf, size))) return code;             \
        if (this != NULL) {
#define GENCODECS_STRUCT(_type)                                               \
    static GENCODECS_PUB_STRUCT(_type)
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        if (0 > (code = jsonb_key(b, buf, size, _key, sizeof(_key) - 1)))     \
            return code;                                                      \
        _encoder(b, buf, size, this->_name, _type);
#define GENCODECS_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)       \
        if (0 > (code = jsonb_key(b, buf, size, #_name, sizeof(#_name) - 1))) \
            return code;                                                      \
        else {                                                                \
            char tok[64];                                                     \
            int toklen;                                                       \
            toklen = sprintf(tok, _printf_type, this->_name);                 \
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))          \
                return code;                                                  \
        }
#define GENCODECS_STRUCT_END                                                  \
        }                                                                     \
        if (0 > (code = jsonb_object_pop(b, buf, size))) return code;         \
        return code;                                                          \
    }

#define GENCODECS_PUB_LIST(_type)                                             \
    jsonbcode _type##_to_jsonb(jsonb *b, char buf[], size_t size,             \
                                         const struct _type *this)            \
    {                                                                         \
        jsonbcode code;                                                       \
        if (0 > (code = jsonb_array(b, buf, size))) return code;              \
        if (this != NULL) {                                                   \
            int i;
#define GENCODECS_LIST(_type)                                                 \
    static GENCODECS_PUB_LIST(_type)
#define GENCODECS_LISTTYPE(_type)                                             \
        for (i = 0; i < this->size; ++i) {                                    \
            JSON_ENCODER_##_type(b, buf, size, this->array[i], _type);        \
        }
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        for (i = 0; i < this->size; ++i)                                      \
            if (0 > (code = _type##_to_jsonb(b, buf, size,                    \
                                                &this->array[i])))            \
                return code;
#define GENCODECS_LISTTYPE_PTR(_type, _decor)                                 \
        for (i = 0; i < this->size; ++i) {                                    \
            JSON_ENCODER_PTR_##_type(b, buf, size, this->array[i], _type);    \
        }
#define GENCODECS_LIST_END                                                    \
        }                                                                     \
        if (0 > (code = jsonb_array_pop(b, buf, size))) return code;          \
        return code;                                                          \
    }

#include "gencodecs-gen.pre.h"

#define GENCODECS_PUB_STRUCT(_type)                                           \
    size_t _type##_to_json(char buf[], size_t size,                           \
                              const struct _type *this)                       \
    {                                                                         \
        jsonb b;                                                              \
        jsonbcode code;                                                       \
        jsonb_init(&b);                                                       \
        code = _type##_to_jsonb(&b, buf, size, this);                         \
        return code < 0 ? 0 : b.pos;                                          \
    }
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)


#include "gencodecs-gen.pre.h"

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_JSON_ENCODER */
