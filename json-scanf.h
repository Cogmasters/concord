#ifndef JSON_SCANF
#define JSON_SCANF

struct json_token {
  char * start;
  size_t length;
};
extern int json_scanf(char *buffer, size_t buf_size, char *format, ...);

#endif //JSON_SCANF
