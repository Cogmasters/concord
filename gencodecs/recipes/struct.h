#define BLANK
#define INIT_BLANK(_var, _type)

#define CLEANUP_BLANK(_var, _type)
#define CLEANUP_STRUCT_PTR(_var, _type)                                       \
    if (_var) {                                                               \
        _type##_cleanup(_var);                                                \
        free(_var);                                                           \
    }
#define CLEANUP_PTR(_var, _type)                                              \
    if (_var) free(_var)

#ifdef GENCODECS_STRUCT
#ifdef GENCODECS_HEADER

#define GENCODECS_STRUCT_BEGIN(_type) struct _type;
#define GENCODECS_LIST_BEGIN(_type)   struct _type;

#define GENCODECS_DESC(_description)
#include "gencodecs-gen.H"

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    struct _type {
#define GENCODECS_FIELD(_type, _name, _default_value)                         \
        _type _name;
#define GENCODECS_FIELD_STRUCT_PTR(_type, _decor, _name)                      \
        struct _type _decor _name;
#define GENCODECS_FIELD_PTR(_type, _decor, _name)                             \
        _type _decor _name;
#define GENCODECS_FIELD_CUSTOM(_type, _decor, _name, _init, _cleanup,         \
                               _encoder, _decoder, _key, _default_value)      \
        _type _decor _name;
#define GENCODECS_FIELD_PRINTF(_type, _scanf_type, _printf_type, _name)       \
        _type _name;
#define GENCODECS_FIELD_ENUM(_type, _name)                                    \
        enum _type _name;
#define GENCODECS_STRUCT_END                                                  \
    };

#define GENCODECS_LIST_BEGIN(_type)                                           \
    struct _type {                                                            \
        int size;
#define GENCODECS_LISTTYPE_PRIMITIVE(_type)                                   \
        _type *array;
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        struct _type *array;
#define GENCODECS_LISTTYPE_PTR(_type)                                         \
        _type **array;
#define GENCODECS_LIST_END                                                    \
        int realsize;                                                         \
    };

#define GENCODECS_ENUM_BEGIN(_name)                                           \
    enum _name {
#define GENCODECS_ENUMERATOR(_enumerator, _value)                             \
        _enumerator _value,
#define GENCODECS_ENUMERATOR_LAST(_enumerator, _value)                        \
        _enumerator _value
#define GENCODECS_ENUM_END                                                    \
    };

#undef GENCODECS_DESC
#include "gencodecs-gen.H"

#ifdef GENCODECS_STRUCT_INIT

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    void _type##_init(struct _type *this);                                    \
    void _type##_cleanup(struct _type *this);
#define GENCODECS_LIST_BEGIN(_type)                                           \
    void _type##_cleanup(struct _type *this);

#include "gencodecs-gen.H"

#endif /* GENCODECSS_STRUCT_INIT */

#else

#ifdef GENCODECS_STRUCT_INIT

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    void _type##_init(struct _type *this)                                     \
    {
#define GENCODECS_FIELD_CUSTOM(_type, _decor, _name, _init, _cleanup,         \
                               _encoder, _decoder, _key, _default_value)      \
        this->_name = _default_value;
#define GENCODECS_FIELD_PRINTF(_type, _scanf_type, _printf_type, _name)       \
        this->_name = (_type)0;
#define GENCODECS_STRUCT_END                                                  \
    }

#include "gencodecs-gen.H"

#define GENCODECS_STRUCT_BEGIN(_type)                                         \
    void _type##_cleanup(struct _type *this)                                  \
    {
#define GENCODECS_FIELD(_type, _name, _default_value)                         \
        (void)this->_name;
#define GENCODECS_FIELD_CUSTOM(_type, _decor, _name, _init, _cleanup,         \
                               _encoder, _decoder, _key, _default_value)      \
        _cleanup(this->_name, _type);
#define GENCODECS_STRUCT_END                                                  \
    }

#define GENCODECS_LIST_BEGIN(_type)                                           \
    void _type##_cleanup(struct _type *this)                                  \
    {
#define GENCODECS_LISTTYPE_PRIMITIVE(_type)                                   \
        __carray_free(this, _type, NULL, NULL);
#define GENCODECS_LISTTYPE_STRUCT(_type)                                      \
        __carray_free(this, struct _type, NULL,                               \
                      _type##_cleanup(&__CARRAY_OPERAND_A));
#define GENCODECS_LISTTYPE_PTR(_type)                                         \
        __carray_free(this, _type, NULL, free(&__CARRAY_OPERAND_A));
#define GENCODECS_LIST_END                                                    \
    }

#include "gencodecs-gen.H"

#endif /* GENCODECS_STRUCT_INIT */
#endif /* GENCODECS_HEADER */
#endif /* GENCODECS_STRUCT */
