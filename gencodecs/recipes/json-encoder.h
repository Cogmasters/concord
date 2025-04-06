#define GENCODECS_JSON_ENCODER_int(b, buf, size, _var, _type)                 \
    if (0 > (code = jsonb_number_auto(b, buf, size, _var))) return code
#define GENCODECS_JSON_ENCODER_PTR_char(b, buf, size, _var, _type)            \
    if (0 > (code = jsonb_string_auto(b, buf, size, _var,                     \
                                      _var ? strlen(_var) : 0)))              \
    return code
#define GENCODECS_JSON_ENCODER_bool(b, buf, size, _var, _type)                \
    if (0 > (code = jsonb_bool_auto(b, buf, size, _var))) return code
#define GENCODECS_JSON_ENCODER_STRUCT_PTR(b, buf, size, _var, _type)          \
    if (0 > (code = _type##_to_jsonb(b, buf, size, _var))) return code

#ifdef GENCODECS_JSON_ENCODER
#ifdef GENCODECS_HEADER

#define GENCODECS_PUB_STRUCT(_type)                                           \
    jsonbcode _type##_to_jsonb(jsonb *b, char *buf[], size_t *size,           \
                               const struct _type *self);                     \
    CCORDcode _type##_to_json(char *buf[], size_t *size,                      \
                              const struct _type *self);
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.PRE.h"

#elif defined(GENCODECS_FORWARD)

#define GENCODECS_STRUCT(_type)                                               \
    static jsonbcode _type##_to_jsonb(jsonb *b, char *buf[], size_t *size,    \
                                      const struct _type *self);
#define GENCODECS_LIST(_type) GENCODECS_STRUCT(_type)

#include "gencodecs-gen.PRE.h"

#else

#define GENCODECS_COND_WRITE(_condition)                                      \
    if (_condition) {
#define GENCODECS_COND_END }

#define GENCODECS_PUB_STRUCT(_type)                                           \
    jsonbcode _type##_to_jsonb(jsonb *b, char *buf[], size_t *size,           \
                               const struct _type *self)                      \
    {                                                                         \
        jsonbcode code;                                                       \
        if ((code = jsonb_object_auto(b, buf, size))) return code;            \
        if (self != NULL) {
#define GENCODECS_STRUCT(_type) static GENCODECS_PUB_STRUCT(_type)
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
    if ((code = jsonb_key_auto(b, buf, size, _key, sizeof(_key) - 1)))        \
        return code;                                                          \
    _encoder(b, buf, size, self->_name, _type);
#define GENCODECS_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)       \
    if ((code = jsonb_key_auto(b, buf, size, #_name, sizeof(#_name) - 1)))    \
        return code;                                                          \
    else {                                                                    \
        char tok[64];                                                         \
        int toklen = sprintf(tok, _printf_type, self->_name);                 \
        if ((code = jsonb_token_auto(b, buf, size, tok, toklen)))             \
            return code;                                                      \
    }
#define GENCODECS_STRUCT_END                                                  \
    }                                                                         \
    if ((code = jsonb_object_pop_auto(b, buf, size))) return code;            \
    return code;                                                              \
    }

#define GENCODECS_PUB_LIST(_type)                                             \
    jsonbcode _type##_to_jsonb(jsonb *b, char *buf[], size_t *size,           \
                               const struct _type *self)                      \
    {                                                                         \
        jsonbcode code;                                                       \
        if ((code = jsonb_array_auto(b, buf, size))) return code;             \
        if (self != NULL) {                                                   \
            int i;
#define GENCODECS_LIST(_type) static GENCODECS_PUB_LIST(_type)
#define GENCODECS_LISTTYPE(_type)                                             \
    for (i = 0; i < self->size; ++i)                                          \
        GENCODECS_JSON_ENCODER_##_type(b, buf, size, self->array[i], _type);
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
    for (i = 0; i < self->size; ++i)                                          \
        if ((code = _type##_to_jsonb(b, buf, size, &self->array[i])))         \
            return code;
#define GENCODECS_LISTTYPE_PTR(_type, _decor)                                 \
    for (i = 0; i < self->size; ++i)                                          \
        GENCODECS_JSON_ENCODER_PTR_##_type(b, buf, size, self->array[i],      \
                                           _type);
#define GENCODECS_LIST_END                                                    \
    }                                                                         \
    if ((code = jsonb_array_pop_auto(b, buf, size))) return code;             \
    return code;                                                              \
    }

#include "gencodecs-gen.PRE.h"

#define GENCODECS_PUB_STRUCT(_type)                                           \
    CCORDcode _type##_to_json(char *buf[], size_t *size,                      \
                              const struct _type *self)                       \
    {                                                                         \
        jsonb b;                                                              \
        jsonb_init(&b);                                                       \
        if (_type##_to_jsonb(&b, buf, size, self) != JSONB_END) {             \
            free(*buf);                                                       \
            *buf = NULL;                                                      \
            *size = 0;                                                        \
            return CCORD_MALFORMED_PAYLOAD;                                   \
        }                                                                     \
        *size = b.pos;                                                        \
        return CCORD_OK;                                                      \
    }
#define GENCODECS_PUB_LIST(_type) GENCODECS_PUB_STRUCT(_type)

#include "gencodecs-gen.PRE.h"

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_JSON_ENCODER */
