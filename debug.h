#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef __stensal__
#define ABORT()    { char * p = 0; * p = 0; }
#else
#define ABORT()    abort()
#endif


#define D_OUT stderr
#define D_FMT_PREFIX "[%s:%d] %s()\n\t"
#define D_FMT_ARGS __FILE__, __LINE__, __func__

#define __ERROR(fmt, ...) fprintf(D_OUT, D_FMT_PREFIX "ERROR:\t"fmt"\n%s", D_FMT_ARGS, __VA_ARGS__)
#define ERROR(...) \
        do { \
            __ERROR(__VA_ARGS__, ""); \
            ABORT(); \
        } while (0)

/* minimalistic error message */
#define ERROR_MIN(err_macro) ERROR("%d %s", err_macro, #err_macro)
/* assert with diagnose string */
#define ASSERT_S(expr, msg) \
        do { \
            if (!(expr)){ \
                ERROR("Assert Failed:\t%s\n\tExpected:\t%s", msg, #expr); \
            } \
        } while(0)


#if DEBUG_MODE == 1 /* DEBUG MODE ACTIVE */

/* @param msg string to be printed in debug mode */
#       define D_PUTS(msg) fprintf(D_OUT, D_FMT_PREFIX "%s\n", D_FMT_ARGS, msg)
#       define D_NOTOP_PUTS(msg) fprintf(D_OUT, "\t%s\n", msg)
/* @param fmt like printf
   @param ... arguments to be parsed into fmt */
#       define __D_PRINT(fmt, ...) fprintf(D_OUT, D_FMT_PREFIX fmt"\n%s", D_FMT_ARGS, __VA_ARGS__)
#       define D_PRINT(...) __D_PRINT(__VA_ARGS__, "")
#       define __D_NOTOP_PRINT(fmt, ...) fprintf(D_OUT, "\t"fmt"\n%s", __VA_ARGS__)
#       define D_NOTOP_PRINT(...) __D_NOTOP_PRINT(__VA_ARGS__, "")
#       define D_ERROR(...) ERROR(__VA_ARGS__)
#       define D_ASSERT_S(expr, msg) ASSERT_S(expr, msg)
#       define D_ONLY(arg) (arg)

#else /* DEBUG MODE INNACTIVE */

#       define D_PUTS(msg) 
#       define D_NOTOP_PUTS(msg) 
#       define D_PRINT(...)
#       define D_NOTOP_PRINT(...)
#       define D_ERROR(...)
#       define D_ASSERT_S(expr, msg)
#       define D_ONLY(arg)
#endif

#endif
