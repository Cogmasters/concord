#ifndef ORKA_DEBUG_H
#define ORKA_DEBUG_H

#ifdef __stensal__ // for error tracing purposes
#  define ABORT()    { char * p = 0; * p = 0; }
#else
#  define ABORT()    abort()
#endif

#define D_OUT stderr
#define D_FMT_PREFIX "[%s:%d] %s()\n\t"
#define D_FMT_ARGS __FILE__, __LINE__, __func__


#define PUTS(msg) fprintf(D_OUT, D_FMT_PREFIX "%s\n", D_FMT_ARGS, msg)
#define NOTOP_PUTS(msg) fprintf(D_OUT, "\t%s\n", msg)
#define __PRINT(fmt, ...) fprintf(D_OUT, D_FMT_PREFIX fmt "\n%s", D_FMT_ARGS, __VA_ARGS__)
#define PRINT(...) __PRINT(__VA_ARGS__, "")
#define __NOTOP_PRINT(fmt, ...) fprintf(D_OUT, "\t" fmt "\n%s", __VA_ARGS__)
#define NOTOP_PRINT(...) __NOTOP_PRINT(__VA_ARGS__, "")
#define __ERR(fmt, ...) fprintf(D_OUT, D_FMT_PREFIX "ERROR:\t" fmt "\n%s", D_FMT_ARGS, __VA_ARGS__)
#define ERR(...) \
  do { \
    __ERR(__VA_ARGS__, ""); \
    ABORT(); \
  } while (0)

#define ASSERT_S(expr, msg) \
  do { \
    if (!(expr)){ \
      ERR("Assert Failed:\t%s\n\tExpected:\t%s", msg, #expr); \
    } \
  } while(0)

#if _ORCA_DEBUG /* DEBUG MODE ACTIVE */

/* @param msg string to be printed in debug mode */
#  define D_PUTS(msg) PUTS(msg)
#  define D_NOTOP_PUTS(msg) NOTOP_PUTS(msg)
/* @param fmt like printf
   @param ... arguments to be parsed into fmt */
#  define D_PRINT(...) PRINT(__VA_ARGS__)
#  define D_NOTOP_PRINT(...) NOTOP_PRINT(__VA_ARGS__)
#  define D_ERR(...) ERR(__VA_ARGS__)
#  define D_ASSERT_S(expr, msg) ASSERT_S(expr, msg)
#  define D_ONLY(arg) (arg)

#else /* DEBUG MODE INNACTIVE */

#  define D_PUTS(msg) 
#  define D_NOTOP_PUTS(msg) 
#  define D_PRINT(...)
#  define D_NOTOP_PRINT(...)
#  define D_ERR(...)
#  define D_ASSERT_S(expr, msg)
#  define D_ONLY(arg)

#endif

#endif // ORKA_DEBUG_H
