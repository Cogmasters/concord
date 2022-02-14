#define BLANK
#define INIT_BLANK(_var, _type)

#define CLEANUP_BLANK(_var, _type)
#define CLEANUP_STRUCT_PTR(_var, _type)                                       \
    if (_var) {                                                               \
        _##_type##_cleanup(_var);                                             \
        free(_var);                                                           \
    }
#define CLEANUP_PTR(_var, _type)                                              \
    if (_var) free(_var)

#ifdef GENCODECS_DATA
#ifdef GENCODECS_HEADER

#define GENCODECS_STRUCT(_type) struct _type;
#define GENCODECS_LIST(_type)   struct _type;

#define GENCODECS_PUB_STRUCT(_type) GENCODECS_STRUCT(_type)
#define GENCODECS_PUB_LIST(_type) GENCODECS_LIST(_type)

#include "gencodecs-gen.H"

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
#define GENCODECS_FIELD_PRINTF(_name, _type, _scanf_type, _printf_type)       \
        _type _name;
#define GENCODECS_FIELD_ENUM(_name, _type)                                    \
        enum _type _name;
#define GENCODECS_STRUCT_END                                                  \
    };

#define GENCODECS_LIST(_type)                                                 \
    struct _type {                                                            \
        int size;
#define GENCODECS_LISTTYPE(_type)                                             \
        _type *array;
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        struct _type *array;
#define GENCODECS_LISTTYPE_PTR(_type, _decor)                                         \
        _type * _decor array;
#define GENCODECS_LIST_END                                                    \
        int realsize;                                                         \
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
#define GENCODECS_PUB_LIST(_type) GENCODECS_LIST(_type)

#undef GENCODECS_PP
#undef GENCODECS_PP_DEFINE
#include "gencodecs-gen.H"
#define GENCODECS_PP(_description)
#define GENCODECS_PP_DEFINE(_description)

#ifdef GENCODECS_INIT

#define GENCODECS_PUB_STRUCT(_type)                                           \
    void _type##_init(struct _type *this);                                    \
    void _type##_cleanup(struct _type *this);
#define GENCODECS_PUB_LIST(_type)                                             \
    void _type##_cleanup(struct _type *this);

#include "gencodecs-gen.H"

#endif /* GENCODECS_INIT */

#elif defined(GENCODECS_FORWARD)

#ifdef GENCODECS_INIT

#define GENCODECS_STRUCT(_type)                                               \
    static void _##_type##_init(struct _type *this);                          \
    static void _##_type##_cleanup(struct _type *this);
#define GENCODECS_LIST(_type)                                                 \
    static void _##_type##_cleanup(struct _type *this);
#define GENCODECS_PUB_STRUCT(_type) GENCODECS_STRUCT(_type)
#define GENCODECS_PUB_LIST(_type) GENCODECS_LIST(_type)

#include "gencodecs-gen.H"

#endif /* GENCODECS_INIT */

#else

#ifdef GENCODECS_INIT

#define GENCODECS_STRUCT(_type)                                               \
    static void _##_type##_init(struct _type *this)                           \
    {
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        this->_name = _default_value;
#define GENCODECS_FIELD_PRINTF(_name, _type, _scanf_type, _printf_type)       \
        this->_name = (_type)0;
#define GENCODECS_STRUCT_END                                                  \
    }

#define GENCODECS_PUB_STRUCT(_type) GENCODECS_STRUCT(_type)

#include "gencodecs-gen.H"

#define GENCODECS_STRUCT(_type)                                               \
    static void _##_type##_cleanup(struct _type *this)                        \
    {
#define GENCODECS_FIELD(_name, _type, _default_value)                         \
        (void)this->_name;
#define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,   \
                               _encoder, _decoder, _default_value)            \
        _cleanup(this->_name, _type);
#define GENCODECS_STRUCT_END                                                  \
    }

#define GENCODECS_LIST(_type)                                                 \
    static void _##_type##_cleanup(struct _type *this)                        \
    {
#define GENCODECS_LISTTYPE(_type)                                             \
        if (this) __carray_free(this, _type, NULL, NULL);
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        if (this)                                                                 \
            __carray_free(this, struct _type, NULL,                               \
                          _##_type##_cleanup(&__CARRAY_OPERAND_A));
#define GENCODECS_LISTTYPE_PTR(_type, _decor)                                         \
        if (this) __carray_free(this, _type _decor, NULL, NULL);
#define GENCODECS_LIST_END                                                    \
    }

#define GENCODECS_PUB_STRUCT(_type) GENCODECS_STRUCT(_type)
#define GENCODECS_PUB_LIST(_type) GENCODECS_LIST(_type)

#include "gencodecs-gen.H"

#define GENCODECS_PUB_STRUCT(_type)                                           \
    void _type##_init(struct _type *this)                                     \
    {                                                                         \
        _##_type##_init(this);                                                \
    }                                                                         \
    void _type##_cleanup(struct _type *this)                                  \
    {                                                                         \
        _##_type##_cleanup(this);                                             \
    }

#define GENCODECS_PUB_LIST(_type)                                             \
    void _type##_cleanup(struct _type *this)                                  \
    {                                                                         \
        _##_type##_cleanup(this);                                             \
    }

#include "gencodecs-gen.H"

#endif /* GENCODECS_INIT */
#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_DATA */
