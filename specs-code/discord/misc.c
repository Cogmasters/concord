/* This file is generated from specs/discord/misc.json, Please don't edit it. */
/**
 * @file specs-code/discord/misc.c
 * @see (null)
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"


/* This method is disabled at specs/discord/misc.json:8:30 */


/* This method is disabled at specs/discord/misc.json:8:30 */


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_file_cleanup_v(void *p) {
  discord_file_cleanup((struct discord_file *)p);
}

void discord_file_init_v(void *p) {
  discord_file_init((struct discord_file *)p);
}

void discord_file_list_free_v(void **p) {
  discord_file_list_free((struct discord_file**)p);
}


void discord_file_cleanup(struct discord_file *d) {
  /* specs/discord/misc.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"the name of the file being sent", "inject_if_not":null }' */
  if (d->name)
    free(d->name);
  /* specs/discord/misc.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the contents of the file being sent", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* specs/discord/misc.json:13:20
     '{ "name": "size", "type":{ "base":"int", "int_alias":"size_t" }, "comment":"the size of the file in bytes", "inject_if_not":0 }' */
  /* p->size is a scalar */
}

void discord_file_init(struct discord_file *p) {
  memset(p, 0, sizeof(struct discord_file));
  /* specs/discord/misc.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"the name of the file being sent", "inject_if_not":null }' */

  /* specs/discord/misc.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the contents of the file being sent", "inject_if_not":null }' */

  /* specs/discord/misc.json:13:20
     '{ "name": "size", "type":{ "base":"int", "int_alias":"size_t" }, "comment":"the size of the file in bytes", "inject_if_not":0 }' */

}
void discord_file_list_free(struct discord_file **p) {
  ntl_free((void**)p, (vfvp)discord_file_cleanup);
}


