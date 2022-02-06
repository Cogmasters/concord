#define DECOR_BLANK

#ifndef GENCODECS_IF
#   define GENCODECS_IF(_name, _op, _value)
#endif
#ifndef GENCODECS_ENDIF
#   define GENCODECS_ENDIF
#endif

#ifndef GENCODECS_STRUCT_BEGIN
#   define GENCODECS_STRUCT_BEGIN(_type)
#endif
#ifndef GENCODECS_FIELD_CUSTOM
#   define GENCODECS_FIELD_CUSTOM(_type, _decor, _name, _init, _cleanup,      \
                               _encoder, _decoder, _key, _default_value)
#endif
#ifndef GENCODECS_FIELD
#   define GENCODECS_FIELD(_type, _name, _default_value)                      \
        GENCODECS_FIELD_CUSTOM(_type, , _name, , CLEANUP_BLANK,               \
                               JSON_ENCODER_##_type, JSON_DECODER_##_type,    \
                               _name, _default_value)
#endif
#ifndef GENCODECS_FIELD_STRUCT_PTR
#   define GENCODECS_FIELD_STRUCT_PTR(_type, _decor, _name)                   \
        GENCODECS_FIELD_CUSTOM(_type, _decor, _name, , CLEANUP_STRUCT_PTR,    \
                           JSON_ENCODER_STRUCT_PTR, JSON_DECODER_STRUCT_PTR,  \
                           _name, NULL)
#endif
#ifndef GENCODECS_FIELD_PTR
#   define GENCODECS_FIELD_PTR(_type, _decor, _name)                          \
        GENCODECS_FIELD_CUSTOM(_type, _decor, _name, , CLEANUP_PTR,           \
                               JSON_ENCODER_PTR_##_type,                      \
                               JSON_DECODER_PTR_##_type, _name, NULL)
#endif
#ifndef GENCODECS_FIELD_PRINTF
#   define GENCODECS_FIELD_PRINTF(_type, _scanf_type, _printf_type, _name)
#endif
#ifndef GENCODECS_FIELD_ENUM
#   define GENCODECS_FIELD_ENUM(_type, _name) GENCODECS_FIELD(int, _name, 0)
#endif
#ifndef GENCODECS_STRUCT_END
#   define GENCODECS_STRUCT_END(_type)
#endif

#ifndef GENCODECS_LIST_BEGIN
#   define GENCODECS_LIST_BEGIN(_type)
#endif
#ifndef GENCODECS_LISTTYPE_PRIMITIVE
#   define GENCODECS_LISTTYPE_PRIMITIVE(_type)
#endif
#ifndef GENCODECS_LISTTYPE_STRUCT
#   define GENCODECS_LISTTYPE_STRUCT(_type)
#endif
#ifndef GENCODECS_LISTTYPE_PTR
#   define GENCODECS_LISTTYPE_PTR(_type)
#endif
#ifndef GENCODECS_LIST_END
#   define GENCODECS_LIST_END(_type)
#endif

#ifndef GENCODECS_ENUM_BEGIN
#   define GENCODECS_ENUM_BEGIN(_name)
#endif
#ifndef GENCODECS_ENUM_END
#   define GENCODECS_ENUM_END(_name)
#endif
#ifndef GENCODECS_ENUMERATOR
#   define GENCODECS_ENUMERATOR(_enumerator, _value)
#endif
#ifndef GENCODECS_ENUMERATOR_END
#   define GENCODECS_ENUMERATOR_END(_name)
#endif

#include GENCODECS_INCLUDE

#undef GENCODECS_IF
#undef GENCODECS_ENDIF

#undef GENCODECS_STRUCT_BEGIN
#undef GENCODECS_FIELD
#undef GENCODECS_FIELD_STRUCT_PTR
#undef GENCODECS_FIELD_PTR
#undef GENCODECS_FIELD_CUSTOM
#undef GENCODECS_FIELD_PRINTF
#undef GENCODECS_FIELD_ENUM
#undef GENCODECS_STRUCT_END

#undef GENCODECS_LIST_BEGIN
#undef GENCODECS_LISTTYPE_PRIMITIVE
#undef GENCODECS_LISTTYPE_STRUCT
#undef GENCODECS_LISTTYPE_PTR
#undef GENCODECS_LIST_END

#undef GENCODECS_ENUM_BEGIN
#undef GENCODECS_ENUM_END
#undef GENCODECS_ENUMERATOR
#undef GENCODECS_ENUMERATOR_END
