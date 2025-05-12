#define INIT_BLANK(_var, _type)
#define CLEANUP_BLANK(_var, _type)

#define CLEANUP_STRUCT_PTR(_var, _type)                                       \
    if (_var) {                                                               \
        _type##_cleanup(_var);                                                \
        discord_free(_var);                                                   \
    }
#define CLEANUP_PTR(_var, _type)                                              \
    if (_var) discord_free(_var)

#ifdef GENCODECS_DATA
#ifdef GENCODECS_HEADER

#define GENCODECS_STRUCT(_type)                                               \
    struct _type {
#define GENCODECS_FIELD(_name, _type, _default_value)                         \
        _type _name;
#define GENCODECS_FIELD_STRUCT_PTR(_name, _type, _decor)                      \
        struct _type _decor _name;
#define GENCODECS_FIELD_PTR(_name, _type, _decor)                             \
        _type _decor _name;
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        _type _decor _name;
#define GENCODECS_FIELD_PRINTF(_name, _type, printf_type, _scanf_type)        \
        _type _name;
#define GENCODECS_FIELD_ENUM(_name, _type)                                    \
        enum _type _name;
#define GENCODECS_STRUCT_END                                                  \
    };

#define GENCODECS_ENUM(_name)                                                 \
    enum _name {
#define GENCODECS_ENUMERATOR(_enumerator, _value)                             \
        _enumerator _value,
#define GENCODECS_ENUMERATOR_LAST(_enumerator, _value)                        \
        _enumerator _value
#define GENCODECS_ENUM_END                                                    \
    };

#define GENCODECS_PUB_STRUCT(_type) GENCODECS_STRUCT(_type)

#undef GENCODECS_PP
#undef GENCODECS_PP_DEFINE
#include "gencodecs-gen.PRE.h"
#define GENCODECS_PP(_description)
#define GENCODECS_PP_DEFINE(_description)

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_DATA */

#ifdef GENCODECS_INIT
#ifdef GENCODECS_HEADER

#define GENCODECS_PUB_STRUCT(_type)                                           \
    void _type##_init(struct _type *self);                                    \
    void _type##_cleanup(struct _type *self);

#include "gencodecs-gen.PRE.h"

#elif defined(GENCODECS_FORWARD)

#define GENCODECS_STRUCT(_type)                                               \
    static void _type##_init(struct _type *self);                             \
    static void _type##_cleanup(struct _type *self);

#include "gencodecs-gen.PRE.h"

#else

#define GENCODECS_PUB_STRUCT(_type)                                           \
    void _type##_init(struct _type *self)                                     \
    {
#define GENCODECS_STRUCT(_type)                                               \
    static GENCODECS_PUB_STRUCT(_type)
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        self->_name = _default_value;
#define GENCODECS_FIELD_PRINTF(_name, _type, printf_type, _scanf_type)        \
        self->_name = (_type)0;
#define GENCODECS_STRUCT_END                                                  \
    }

#include "gencodecs-gen.PRE.h"

#define GENCODECS_PUB_STRUCT(_type)                                           \
    void _type##_cleanup(struct _type *self)                                  \
    {
#define GENCODECS_STRUCT(_type)                                               \
    static GENCODECS_PUB_STRUCT(_type)
#define GENCODECS_FIELD(_name, _type, _default_value)                         \
        (void)self->_name;
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        _cleanup(self->_name, _type);
#define GENCODECS_STRUCT_END                                                  \
    }

#include "gencodecs-gen.PRE.h"

#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_INIT */
