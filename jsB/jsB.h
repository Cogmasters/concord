#ifndef JSB_H
#define JSB_H
#ifdef __cplusplus
extern "C" {
#endif

FILE* jsB_log_file();
void jsB_log(char *fmt, ...);
void jsB_init_D(js_State *J);
void jsB_init_SB(js_State *J);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //JSB_H
