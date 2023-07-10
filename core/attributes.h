#if defined(__MINGW32__) || (defined (__GNUC__) && __GNUC__ > 4 ? true : __GNUC_PATCHLEVEL__ >= 4) || defined(__USE_MINGW_ANSI_STDIO)
#  define PRINTF_LIKE(a, b) __attribute__((format(gnu_printf, a, b)))
#else
#  define PRINTF_LIKE(a, b)
#endif