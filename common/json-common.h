/*
 * Copyright (c) 2020 Lucas Müller
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef JSON_COMMON_H_
#define JSON_COMMON_H_

#define MAX_INTEGER_DIG 20 /* ULLONG_MAX maximum amt of digits possible */

#ifdef __stensal__
#define ABORT()    { char * p = 0; * p = 0; }
#else
#define ABORT()    abort()
#endif


#define D_OUT stderr
#define D_FMT_PREFIX "[%s:%d] %s()\n\t"
#define D_FMT_ARGS __FILE__, __LINE__, __func__

#define __ERR(fmt, ...) fprintf(D_OUT, D_FMT_PREFIX "ERROR:\t" \
                           /* force spaces */ fmt /* force spaces */ \
                          "\n%s", D_FMT_ARGS, __VA_ARGS__)
#define ERR(...) \
        do { \
            __ERR(__VA_ARGS__, ""); \
            ABORT(); \
        } while (0)

/* assert with diagnose string */
#define ASSERT_S(expr, msg) \
        do { \
            if (!(expr)){ \
                ERR("Assert Failed:\t%s\n\tExpected:\t%s", msg, #expr); \
            } \
        } while(0)

#if JSON_SCANF_DEBUG /* DEBUG MODE ACTIVE */

/* @param msg string to be printed in debug mode */
#       define D_PUTS(msg) fprintf(D_OUT, D_FMT_PREFIX "%s\n", D_FMT_ARGS, msg)
#       define D_NOTOP_PUTS(msg) fprintf(D_OUT, "\t%s\n", msg)
/* @param fmt like printf
   @param ... arguments to be parsed into fmt */
#       define __D_PRINT(fmt, ...) fprintf(D_OUT, D_FMT_PREFIX fmt"\n%s", D_FMT_ARGS, __VA_ARGS__)
#       define D_PRINT(...) __D_PRINT(__VA_ARGS__, "")
#       define __D_NOTOP_PRINT(fmt, ...) fprintf(D_OUT, "\t" /* force */fmt /* force */"\n%s", __VA_ARGS__)
#       define D_NOTOP_PRINT(...) __D_NOTOP_PRINT(__VA_ARGS__, "")
#       define D_ERR(...) ERR(__VA_ARGS__)
#       define D_ASSERT_S(expr, msg) ASSERT_S(expr, msg)
#       define D_ONLY(arg) (arg)

#else /* DEBUG MODE INNACTIVE */

#       define D_PUTS(msg) 
#       define D_NOTOP_PUTS(msg) 
#       define D_PRINT(...)
#       define D_NOTOP_PRINT(...)
#       define D_ERR(...)
#       define D_ASSERT_S(expr, msg)
#       define D_ONLY(arg)
#endif

#define STREQ(s,t) (0 == strcmp(s,t))
#define STRNEQ(s,t,n) (0 == strncmp(s,t,n))

typedef enum json_errcode
{
/* JSON EXTERNAL ERRORS */

  JSON_EXT__OUT_MEM              = 0,
  JSON_EXT__INVALID_TOKEN        = 50,
  JSON_EXT__INVALID_STRING,
  JSON_EXT__INVALID_BOOLEAN,
  JSON_EXT__INVALID_NUMBER,
  JSON_EXT__INVALID_COMPOSITE,
  JSON_EXT__NOT_STRING           = 100,
  JSON_EXT__NOT_BOOLEAN,
  JSON_EXT__NOT_NUMBER,
  JSON_EXT__NOT_COMPOSITE,
  JSON_EXT__EMPTY_FIELD          = 200,

/* JSON INTERNAL ERRORS */

  JSON_INT__NOT_FREED        = -1,
  JSON_INT__OVERFLOW         = -50,
} json_errcode;

/* this allocates memory dynamically, should only be used for printing
 *  exception error messages */
char *__json_strerror(json_errcode code, char codetag[], void *where, char entity[]);
#define json_strerror(code, where) __json_strerror(code, #code, where, #where)

#endif //JSON_COMMON_H_
