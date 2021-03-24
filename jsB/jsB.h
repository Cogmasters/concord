#ifndef JSB_H
#define JSB_H
#include "mujs.h"

FILE* jsB_log_file();
void jsB_log(char *fmt, ...);
void jsB_init_D(js_State *J);
void jsB_init_SB(js_State *J);

void jsB_me_channel(js_State *J,
                    uint64_t guild_id,
                    char *me_name,
                    uint64_t me_id,
                    uint64_t author_id,
                    uint64_t channel_id,
                    uint64_t message_id);

#endif //JSB_H
