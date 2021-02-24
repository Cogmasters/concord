#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace emoji {

void
dati_from_json(char *str, size_t len, void *p_emoji)
{
  dati *emoji = (dati*)p_emoji;

  json_scanf(str, len,
      "[id]%F"
      "[name]%s"
      //"[roles]%F" @todo
      "[user]%F"
      "[require_colons]%b"
      "[managed]%b"
      "[animated]%b"
      "[available]%b",
      &orka_strtoull, &emoji->id,
      emoji->name,
      //emoji->roles @todo,
      &user::dati_from_json, emoji->user,
      &emoji->require_colons,
      &emoji->managed,
      &emoji->animated,
      &emoji->available);

  DS_NOTOP_PUTS("Emoji object loaded with API response");
}

void
dati_list_from_json(char *str, size_t len, void *p_emojis)
{
  struct ntl_deserializer d;
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init;
  d.elem_from_buf = &dati_from_json;
  d.ntl_recipient_p = (void***)p_emojis;
  orka_str_to_ntl(str, len, &d);
}

void
dati_init(void *p_emoji) 
{
  dati *emoji = (dati*)p_emoji;  
  memset(emoji, 0, sizeof(dati));
  emoji->user = user::dati_alloc();
}

dati*
dati_alloc()
{
  dati *new_emoji = (dati*)malloc(sizeof(dati));
  dati_init((void*)new_emoji);
  return new_emoji;
}

void
dati_cleanup(void *p_emoji) 
{
  dati *emoji = (dati*)p_emoji;  
  user::dati_free(emoji->user);
  DS_NOTOP_PUTS("Emoji object fields cleared"); 
}

void
dati_free(dati *emoji)
{
  dati_cleanup((void*)emoji);
  free(emoji);
}

void
dati_list_free(dati **emojis) {
  ntl_free((void**)emojis, &dati_cleanup);
}

} // namespace emoji
} // namespace discord

