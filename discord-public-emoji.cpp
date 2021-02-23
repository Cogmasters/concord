#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace emoji {

void
from_json(char *str, size_t len, void *p_emoji)
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
      &user::from_json, emoji->user,
      &emoji->require_colons,
      &emoji->managed,
      &emoji->animated,
      &emoji->available);

  DS_NOTOP_PUTS("Emoji object loaded with API response");
}

void
list_from_json(char *str, size_t len, void *p_emojis)
{
  struct ntl_deserializer d;
  d.elem_size = sizeof(dati);
  d.init_elem = &init_dati;
  d.elem_from_buf = &from_json;
  d.ntl_recipient_p = (void***)p_emojis;
  orka_str_to_ntl(str, len, &d);
}

void
init_dati(void *p_emoji) 
{
  dati *emoji = (dati*)p_emoji;  
  memset(emoji, 0, sizeof(dati));
  emoji->user = user::alloc_dati();
}

dati*
alloc_dati()
{
  dati *new_emoji = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_emoji);
  return new_emoji;
}

void
cleanup_dati(void *p_emoji) 
{
  dati *emoji = (dati*)p_emoji;  
  user::free_dati(emoji->user);
  DS_NOTOP_PUTS("Emoji object fields cleared"); 
}

void
free_dati(dati *emoji)
{
  cleanup_dati((void*)emoji);
  free(emoji);
}

void
free_list(dati **emojis) {
  ntl_free((void**)emojis, &cleanup_dati);
}

} // namespace emoji
} // namespace discord

