#ifndef JSON_SCANF
#define JSON_SCANF

struct json_token {
  char *start;
  size_t length;
};

#ifdef __cplusplus
extern "C" {
#endif

extern int json_scanf(char *buffer, size_t buf_size, char *format, ...);
extern int json_asprintf(char ** buf, char * format, ...);
extern int json_snprintf(char *str, size_t size, char * format, ...);

#ifdef __cplusplus
}
#endif
#endif //JSON_SCANF
