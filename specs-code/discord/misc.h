/* This file is generated from specs/discord/misc.json, Please don't edit it. */
/**
 * @file specs-code/discord/misc.h
 * @see (null)
 */


/* Custom File Structure */
/* defined at specs/discord/misc.json:7:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_file_init(struct discord_file *)`
 *   * Cleanup:

 *     * :code:`void discord_file_cleanup(struct discord_file *)`
 *     * :code:`void discord_file_list_free(struct discord_file **)`
 *   * JSON Decoder:

 *     * :code:`void discord_file_from_json(char *rbuf, size_t len, struct discord_file **)`
 *     * :code:`void discord_file_list_from_json(char *rbuf, size_t len, struct discord_file ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_file_to_json(char *wbuf, size_t len, struct discord_file *)`
 *     * :code:`void discord_file_list_to_json(char *wbuf, size_t len, struct discord_file **)`
 * @endverbatim
 */
struct discord_file {
  /* specs/discord/misc.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"the name of the file being sent", "inject_if_not":null }' */
  char *name; /**< the name of the file being sent */

  /* specs/discord/misc.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the contents of the file being sent", "inject_if_not":null }' */
  char *content; /**< the contents of the file being sent */

  /* specs/discord/misc.json:13:20
     '{ "name": "size", "type":{ "base":"int", "int_alias":"size_t" }, "comment":"the size of the file in bytes", "inject_if_not":0 }' */
  size_t size; /**< the size of the file in bytes */

};
extern void discord_file_cleanup_v(void *p);
extern void discord_file_cleanup(struct discord_file *p);
extern void discord_file_init_v(void *p);
extern void discord_file_init(struct discord_file *p);
extern void discord_file_list_free_v(void **p);
extern void discord_file_list_free(struct discord_file **p);
