/* This file is generated from slack/chat.params.json, Please don't edit it. */
/**
 * @file specs-code/slack/one-specs.h
 * @see https://api.slack.com/methods?filter=chat
 */


/* defined at slack/chat.params.json:9:22 */
/**
 * @brief Post Message
 *
 */
struct slack_chat_post_message_params;
/* This file is generated from slack/users.params.json, Please don't edit it. */

/* defined at slack/users.params.json:9:22 */
/**
 * @brief Users Info
 *
 */
struct slack_users_info_params;
/* This file is generated from slack/chat.params.json, Please don't edit it. */
/* This file is generated from slack/users.params.json, Please don't edit it. */
/* This file is generated from slack/chat.params.json, Please don't edit it. */

/* Post Message */
/* defined at slack/chat.params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void slack_chat_post_message_params_init(struct slack_chat_post_message_params *)`
 *   * Cleanup:

 *     * :code:`void slack_chat_post_message_params_cleanup(struct slack_chat_post_message_params *)`
 *     * :code:`void slack_chat_post_message_params_list_free(struct slack_chat_post_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void slack_chat_post_message_params_from_json(char *rbuf, size_t len, struct slack_chat_post_message_params *)`
 *     * :code:`void slack_chat_post_message_params_list_from_json(char *rbuf, size_t len, struct slack_chat_post_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void slack_chat_post_message_params_to_json(char *wbuf, size_t len, struct slack_chat_post_message_params *)`
 *     * :code:`void slack_chat_post_message_params_list_to_json(char *wbuf, size_t len, struct slack_chat_post_message_params **)`
 * @endverbatim
 */
struct slack_chat_post_message_params {
  /* slack/chat.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
  char *token; /**< Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter. */

  /* slack/chat.params.json:13:20
     '{ "name": "channel", "type":{ "base":"char", "dec":"*" }, "comment":"Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details.", "inject_if_not":null }' */
  char *channel; /**< Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details. */

  /* slack/chat.params.json:14:20
     '{ "name": "attachments", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured attachments, presented as a URL-encoded string.", "inject_if_not":null }' */
  char *attachments; /**< A JSON-based array of structured attachments, presented as a URL-encoded string. */

  /* slack/chat.params.json:15:20
     '{ "name": "blocks", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured blocks, presented as a URL-encoded string.", "inject_if_not":null }' */
  char *blocks; /**< A JSON-based array of structured blocks, presented as a URL-encoded string. */

  /* slack/chat.params.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.", "inject_if_not":null }' */
  char *text; /**< The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications. */

  /* slack/chat.params.json:17:20
     '{ "name": "as_user", "type":{ "base":"bool" }, "comment":"Pass true to post the message as the authed user, instead of as a bot. Defaults to false.", "inject_if_not":false }' */
  bool as_user; /**< Pass true to post the message as the authed user, instead of as a bot. Defaults to false. */

  /* slack/chat.params.json:18:20
     '{ "name": "icon_emoji", "type":{ "base":"char", "dec":"*" }, "comment":"Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  char *icon_emoji; /**< Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored. */

  /* slack/chat.params.json:19:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "comment":"URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  char *icon_url; /**< URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored. */

  /* slack/chat.params.json:20:20
     '{ "name": "link_names", "type":{ "base":"bool" }, "comment":"Find and link channel names and usernames.", "inject_if_not":false }' */
  bool link_names; /**< Find and link channel names and usernames. */

  /* slack/chat.params.json:21:20
     '{ "name": "mrkdwn", "type":{ "base":"bool" }, "default_value":true, "comment":"Disable Slack markup parsing by setting to false. Enabled by default.", "inject_if_not":true }' */
  bool mrkdwn; /**< Disable Slack markup parsing by setting to false. Enabled by default. */

  /* slack/chat.params.json:22:20
     '{ "name": "parse", "type":{ "base":"char", "dec":"*" }, "comment":"Change how messages are treated. Defaults to none", "inject_if_not":null }' */
  char *parse; /**< Change how messages are treated. Defaults to none */

  /* slack/chat.params.json:23:20
     '{ "name": "reply_broadcast", "type":{ "base":"bool" }, "comment":"Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false.", "inject_if_not":false }' */
  bool reply_broadcast; /**< Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false. */

  /* slack/chat.params.json:24:20
     '{ "name": "thread_ts", "type":{ "base":"char", "dec":"*" }, "comment":"Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead.", "inject_if_not":null }' */
  char *thread_ts; /**< Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead. */

  /* slack/chat.params.json:25:20
     '{ "name": "unfurl_links", "type":{ "base":"bool" }, "comment":"Pass true to enable unfurling of primarily text-based content.", "inject_if_not":false }' */
  bool unfurl_links; /**< Pass true to enable unfurling of primarily text-based content. */

  /* slack/chat.params.json:26:20
     '{ "name": "unfurl_media", "type":{ "base":"bool" }, "default_value":true, "comment":"Pass false to disable unfurling of media content.", "inject_if_not":true }' */
  bool unfurl_media; /**< Pass false to disable unfurling of media content. */

  /* slack/chat.params.json:27:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  char *username; /**< Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored. */

};
/* This file is generated from slack/users.params.json, Please don't edit it. */

/* Users Info */
/* defined at slack/users.params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void slack_users_info_params_init(struct slack_users_info_params *)`
 *   * Cleanup:

 *     * :code:`void slack_users_info_params_cleanup(struct slack_users_info_params *)`
 *     * :code:`void slack_users_info_params_list_free(struct slack_users_info_params **)`
 *   * JSON Decoder:

 *     * :code:`void slack_users_info_params_from_json(char *rbuf, size_t len, struct slack_users_info_params *)`
 *     * :code:`void slack_users_info_params_list_from_json(char *rbuf, size_t len, struct slack_users_info_params ***)`
 *   * JSON Encoder:

 *     * :code:`void slack_users_info_params_to_json(char *wbuf, size_t len, struct slack_users_info_params *)`
 *     * :code:`void slack_users_info_params_list_to_json(char *wbuf, size_t len, struct slack_users_info_params **)`
 * @endverbatim
 */
struct slack_users_info_params {
  /* slack/users.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
  char *token; /**< Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter. */

  /* slack/users.params.json:13:20
     '{ "name": "user", "type":{ "base":"char", "dec":"*" }, "comment":"User to get info onUser to get info on", "inject_if_not":null }' */
  char *user; /**< User to get info onUser to get info on */

  /* slack/users.params.json:14:20
     '{ "name": "include_locale", "type":{ "base":"bool" }, "comment":"Set this to true to receive the locale for this user. Defaults to false", "inject_if_not":false }' */
  bool include_locale; /**< Set this to true to receive the locale for this user. Defaults to false */

};
/* This file is generated from slack/chat.params.json, Please don't edit it. */

extern void slack_chat_post_message_params_cleanup_v(void *p);
extern void slack_chat_post_message_params_cleanup(struct slack_chat_post_message_params *p);
extern void slack_chat_post_message_params_init_v(void *p);
extern void slack_chat_post_message_params_init(struct slack_chat_post_message_params *p);
extern void slack_chat_post_message_params_from_json_v(char *json, size_t len, void *p);
extern void slack_chat_post_message_params_from_json_p(char *json, size_t len, struct slack_chat_post_message_params **pp);
extern void slack_chat_post_message_params_from_json(char *json, size_t len, struct slack_chat_post_message_params *p);
extern size_t slack_chat_post_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t slack_chat_post_message_params_to_json(char *json, size_t len, struct slack_chat_post_message_params *p);
extern void slack_chat_post_message_params_list_free_v(void **p);
extern void slack_chat_post_message_params_list_free(struct slack_chat_post_message_params **p);
extern void slack_chat_post_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void slack_chat_post_message_params_list_from_json(char *str, size_t len, struct slack_chat_post_message_params ***p);
extern size_t slack_chat_post_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t slack_chat_post_message_params_list_to_json(char *str, size_t len, struct slack_chat_post_message_params **p);
/* This file is generated from slack/users.params.json, Please don't edit it. */

extern void slack_users_info_params_cleanup_v(void *p);
extern void slack_users_info_params_cleanup(struct slack_users_info_params *p);
extern void slack_users_info_params_init_v(void *p);
extern void slack_users_info_params_init(struct slack_users_info_params *p);
extern void slack_users_info_params_from_json_v(char *json, size_t len, void *p);
extern void slack_users_info_params_from_json_p(char *json, size_t len, struct slack_users_info_params **pp);
extern void slack_users_info_params_from_json(char *json, size_t len, struct slack_users_info_params *p);
extern size_t slack_users_info_params_to_json_v(char *json, size_t len, void *p);
extern size_t slack_users_info_params_to_json(char *json, size_t len, struct slack_users_info_params *p);
extern void slack_users_info_params_list_free_v(void **p);
extern void slack_users_info_params_list_free(struct slack_users_info_params **p);
extern void slack_users_info_params_list_from_json_v(char *str, size_t len, void *p);
extern void slack_users_info_params_list_from_json(char *str, size_t len, struct slack_users_info_params ***p);
extern size_t slack_users_info_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t slack_users_info_params_list_to_json(char *str, size_t len, struct slack_users_info_params **p);
