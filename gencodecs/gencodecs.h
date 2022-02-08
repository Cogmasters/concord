#ifndef GENCODECS_H
#define GENCODECS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Allow symbols usage without GENCODECS_ prefix */
#ifndef GENCODECS_USE_PREFIX
#   define COND_WRITE GENCODECS_COND_WRITE
#   define COND_END GENCODECS_COND_END

#   define STRUCT_BEGIN GENCODECS_STRUCT_BEGIN
#   define FIELD_CUSTOM GENCODECS_FIELD_CUSTOM
#   define FIELD_PRINTF GENCODECS_FIELD_PRINTF
#   define FIELD GENCODECS_FIELD
#   define FIELD_STRUCT_PTR GENCODECS_FIELD_STRUCT_PTR
#   define FIELD_PTR GENCODECS_FIELD_PTR
#   define FIELD_ENUM GENCODECS_FIELD_ENUM
#   define STRUCT_END GENCODECS_STRUCT_END

#   define LIST_BEGIN GENCODECS_LIST_BEGIN
#   define LISTTYPE_PRIMITIVE GENCODECS_LISTTYPE_PRIMITIVE
#   define LISTTYPE_STRUCT GENCODECS_LISTTYPE_STRUCT
#   define LISTTYPE_PTR GENCODECS_LISTTYPE_PTR
#   define LIST_END GENCODECS_LIST_END

#   define ENUM_BEGIN GENCODECS_ENUM_BEGIN
#   define ENUM_END GENCODECS_ENUM_END
#   define ENUMERATOR GENCODECS_ENUMERATOR
#   define ENUMERATOR_LAST GENCODECS_ENUMERATOR_LAST
#   define ENUMERATOR_END GENCODECS_ENUMERATOR_END
#endif /* GENCODECS_USE_PREFIX */

#ifndef GENCODECS_HEADER
#   ifdef GENCODECS_STRUCT
        GENCODECS_DIRECTIVE(include <stdio.h>)
        GENCODECS_DIRECTIVE(include <stdlib.h>)
#       ifdef GENCODECS_STRUCT_INIT
            GENCODECS_DIRECTIVE(include "carray.h")
#       endif
#       ifdef GENCODECS_STRUCT_JSON_ENCODER
            GENCODECS_DIRECTIVE(define JSONB_HEADER)
            GENCODECS_DIRECTIVE(include "json-build.h")
#       endif
#       ifdef GENCODECS_STRUCT_JSON_DECODER
            GENCODECS_DIRECTIVE(define JSMN_STRICT)
            GENCODECS_DIRECTIVE(define JSMN_HEADER)
            GENCODECS_DIRECTIVE(include "jsmn.h")
            GENCODECS_DIRECTIVE(include "jsmn-find.h")

            static char *
            _gc_strndup(const char *src, size_t len)
            {
                char *dest = malloc(len + 1);
                memcpy(dest, src, len);
                dest[len] = '\0';
                return dest;
            }
#       endif
#   endif
#else
    GENCODECS_DIRECTIVE(include <stddef.h>)
    GENCODECS_DIRECTIVE(include <stdbool.h>)
#endif

#ifdef __cplusplus
}
#endif

#endif /* GENCODECS_H */
