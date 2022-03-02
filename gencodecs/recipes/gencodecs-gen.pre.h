#define DECOR_BLANK

#ifndef GENCODECS_COND_WRITE
#   define GENCODECS_COND_WRITE(_condition)
#endif
#ifndef GENCODECS_COND_END
#   define GENCODECS_COND_END
#endif

#ifndef GENCODECS_PUB_STRUCT
#   define GENCODECS_PUB_STRUCT(_type)
#endif
#ifndef GENCODECS_STRUCT
#   define GENCODECS_STRUCT(_type)
#endif
#ifndef GENCODECS_FIELD_CUSTOM
#   define GENCODECS_FIELD_CUSTOM(_name, _key, _type, _decor, _init, _cleanup,\
                                  _encoder, _decoder, _default_value)
#endif
#ifndef GENCODECS_FIELD
#   define GENCODECS_FIELD(_name, _type, _default_value)                      \
        GENCODECS_FIELD_CUSTOM(_name, #_name, _type, , , CLEANUP_BLANK,       \
                               GENCODECS_JSON_ENCODER_##_type,                \
                               GENCODECS_JSON_DECODER_##_type, _default_value)
#endif
#ifndef GENCODECS_FIELD_STRUCT_PTR
#   define GENCODECS_FIELD_STRUCT_PTR(_name, _type, _decor)                   \
        GENCODECS_FIELD_CUSTOM(_name, #_name, _type, _decor, ,                \
                               CLEANUP_STRUCT_PTR,                            \
                               GENCODECS_JSON_ENCODER_STRUCT_PTR,             \
                               GENCODECS_JSON_DECODER_STRUCT_PTR,  NULL)
#endif
#ifndef GENCODECS_FIELD_PTR
#   define GENCODECS_FIELD_PTR(_name, _type, _decor)                          \
        GENCODECS_FIELD_CUSTOM(_name, #_name, _type, _decor, , CLEANUP_PTR,   \
                               GENCODECS_JSON_ENCODER_PTR_##_type,            \
                               GENCODECS_JSON_DECODER_PTR_##_type, NULL)
#endif
#ifndef GENCODECS_FIELD_PRINTF
#   define GENCODECS_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)
#endif
#ifndef GENCODECS_FIELD_ENUM
#   define GENCODECS_FIELD_ENUM(_name, _type) GENCODECS_FIELD(_name, int, 0)
#endif
#ifndef GENCODECS_STRUCT_END
#   define GENCODECS_STRUCT_END
#endif

#ifndef GENCODECS_PUB_LIST
#   define GENCODECS_PUB_LIST(_type)
#endif
#ifndef GENCODECS_LIST
#   define GENCODECS_LIST(_type)
#endif
#ifndef GENCODECS_LISTTYPE
#   define GENCODECS_LISTTYPE(_type)
#endif
#ifndef GENCODECS_LISTTYPE_STRUCT
#   define GENCODECS_LISTTYPE_STRUCT(_type)
#endif
#ifndef GENCODECS_LISTTYPE_PTR
#   define GENCODECS_LISTTYPE_PTR(_type, _decor)
#endif
#ifndef GENCODECS_LIST_END
#   define GENCODECS_LIST_END
#endif

#ifndef GENCODECS_ENUM
#   define GENCODECS_ENUM(_name)
#endif
#ifndef GENCODECS_ENUM_END
#   define GENCODECS_ENUM_END
#endif
#ifndef GENCODECS_ENUMERATOR
#   define GENCODECS_ENUMERATOR(_enumerator, _value)
#endif
#ifndef GENCODECS_ENUMERATOR_LAST
#   define GENCODECS_ENUMERATOR_LAST(_enumerator, _value)
#endif
#ifndef GENCODECS_ENUMERATOR_END
#   define GENCODECS_ENUMERATOR_END(_name)
#endif

#include GENCODECS_READ

#ifndef GENCODECS_PP
#define GENCODECS_PP(_description)
#endif

#undef GENCODECS_COND_WRITE
#undef GENCODECS_COND_END

#undef GENCODECS_PUB_STRUCT
#undef GENCODECS_STRUCT
#undef GENCODECS_FIELD
#undef GENCODECS_FIELD_STRUCT_PTR
#undef GENCODECS_FIELD_PTR
#undef GENCODECS_FIELD_CUSTOM
#undef GENCODECS_FIELD_PRINTF
#undef GENCODECS_FIELD_ENUM
#undef GENCODECS_STRUCT_END

#undef GENCODECS_PUB_LIST
#undef GENCODECS_LIST
#undef GENCODECS_LISTTYPE
#undef GENCODECS_LISTTYPE_STRUCT
#undef GENCODECS_LISTTYPE_PTR
#undef GENCODECS_LIST_END

#undef GENCODECS_ENUM
#undef GENCODECS_ENUM_END
#undef GENCODECS_ENUMERATOR
#undef GENCODECS_ENUMERATOR_LAST
#undef GENCODECS_ENUMERATOR_END
