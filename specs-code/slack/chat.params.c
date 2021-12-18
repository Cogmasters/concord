/* This file is generated from specs/slack/chat.params.json, Please don't edit it. */
/**
 * @file specs-code/slack/chat.params.c
 * @see https://api.slack.com/methods?filter=chat
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "slack.h"

void slack_chat_post_message_params_from_json_p(char *json, size_t len, struct slack_chat_post_message_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  slack_chat_post_message_params_from_json(json, len, *pp);
}
void slack_chat_post_message_params_from_json(char *json, size_t len, struct slack_chat_post_message_params *p)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  slack_chat_post_message_params_init(p);
  r=json_extract(json, len, 
  /* specs/slack/chat.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
                "(token):?s,"
  /* specs/slack/chat.params.json:13:20
     '{ "name": "channel", "type":{ "base":"char", "dec":"*" }, "comment":"Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details.", "inject_if_not":null }' */
                "(channel):?s,"
  /* specs/slack/chat.params.json:14:20
     '{ "name": "attachments", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured attachments, presented as a URL-encoded string.", "inject_if_not":null }' */
                "(attachments):?s,"
  /* specs/slack/chat.params.json:15:20
     '{ "name": "blocks", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured blocks, presented as a URL-encoded string.", "inject_if_not":null }' */
                "(blocks):?s,"
  /* specs/slack/chat.params.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.", "inject_if_not":null }' */
                "(text):?s,"
  /* specs/slack/chat.params.json:17:20
     '{ "name": "as_user", "type":{ "base":"bool" }, "comment":"Pass true to post the message as the authed user, instead of as a bot. Defaults to false.", "inject_if_not":false }' */
                "(as_user):b,"
  /* specs/slack/chat.params.json:18:20
     '{ "name": "icon_emoji", "type":{ "base":"char", "dec":"*" }, "comment":"Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                "(icon_emoji):?s,"
  /* specs/slack/chat.params.json:19:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "comment":"URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                "(icon_url):?s,"
  /* specs/slack/chat.params.json:20:20
     '{ "name": "link_names", "type":{ "base":"bool" }, "comment":"Find and link channel names and usernames.", "inject_if_not":false }' */
                "(link_names):b,"
  /* specs/slack/chat.params.json:21:20
     '{ "name": "mrkdwn", "type":{ "base":"bool" }, "default_value":true, "comment":"Disable Slack markup parsing by setting to false. Enabled by default.", "inject_if_not":true }' */
                "(mrkdwn):b,"
  /* specs/slack/chat.params.json:22:20
     '{ "name": "parse", "type":{ "base":"char", "dec":"*" }, "comment":"Change how messages are treated. Defaults to none", "inject_if_not":null }' */
                "(parse):?s,"
  /* specs/slack/chat.params.json:23:20
     '{ "name": "reply_broadcast", "type":{ "base":"bool" }, "comment":"Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false.", "inject_if_not":false }' */
                "(reply_broadcast):b,"
  /* specs/slack/chat.params.json:24:20
     '{ "name": "thread_ts", "type":{ "base":"char", "dec":"*" }, "comment":"Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead.", "inject_if_not":null }' */
                "(thread_ts):?s,"
  /* specs/slack/chat.params.json:25:20
     '{ "name": "unfurl_links", "type":{ "base":"bool" }, "comment":"Pass true to enable unfurling of primarily text-based content.", "inject_if_not":false }' */
                "(unfurl_links):b,"
  /* specs/slack/chat.params.json:26:20
     '{ "name": "unfurl_media", "type":{ "base":"bool" }, "default_value":true, "comment":"Pass false to disable unfurling of media content.", "inject_if_not":true }' */
                "(unfurl_media):b,"
  /* specs/slack/chat.params.json:27:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                "(username):?s,",
  /* specs/slack/chat.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
                &p->token,
  /* specs/slack/chat.params.json:13:20
     '{ "name": "channel", "type":{ "base":"char", "dec":"*" }, "comment":"Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details.", "inject_if_not":null }' */
                &p->channel,
  /* specs/slack/chat.params.json:14:20
     '{ "name": "attachments", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured attachments, presented as a URL-encoded string.", "inject_if_not":null }' */
                &p->attachments,
  /* specs/slack/chat.params.json:15:20
     '{ "name": "blocks", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured blocks, presented as a URL-encoded string.", "inject_if_not":null }' */
                &p->blocks,
  /* specs/slack/chat.params.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.", "inject_if_not":null }' */
                &p->text,
  /* specs/slack/chat.params.json:17:20
     '{ "name": "as_user", "type":{ "base":"bool" }, "comment":"Pass true to post the message as the authed user, instead of as a bot. Defaults to false.", "inject_if_not":false }' */
                &p->as_user,
  /* specs/slack/chat.params.json:18:20
     '{ "name": "icon_emoji", "type":{ "base":"char", "dec":"*" }, "comment":"Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                &p->icon_emoji,
  /* specs/slack/chat.params.json:19:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "comment":"URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                &p->icon_url,
  /* specs/slack/chat.params.json:20:20
     '{ "name": "link_names", "type":{ "base":"bool" }, "comment":"Find and link channel names and usernames.", "inject_if_not":false }' */
                &p->link_names,
  /* specs/slack/chat.params.json:21:20
     '{ "name": "mrkdwn", "type":{ "base":"bool" }, "default_value":true, "comment":"Disable Slack markup parsing by setting to false. Enabled by default.", "inject_if_not":true }' */
                &p->mrkdwn,
  /* specs/slack/chat.params.json:22:20
     '{ "name": "parse", "type":{ "base":"char", "dec":"*" }, "comment":"Change how messages are treated. Defaults to none", "inject_if_not":null }' */
                &p->parse,
  /* specs/slack/chat.params.json:23:20
     '{ "name": "reply_broadcast", "type":{ "base":"bool" }, "comment":"Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false.", "inject_if_not":false }' */
                &p->reply_broadcast,
  /* specs/slack/chat.params.json:24:20
     '{ "name": "thread_ts", "type":{ "base":"char", "dec":"*" }, "comment":"Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead.", "inject_if_not":null }' */
                &p->thread_ts,
  /* specs/slack/chat.params.json:25:20
     '{ "name": "unfurl_links", "type":{ "base":"bool" }, "comment":"Pass true to enable unfurling of primarily text-based content.", "inject_if_not":false }' */
                &p->unfurl_links,
  /* specs/slack/chat.params.json:26:20
     '{ "name": "unfurl_media", "type":{ "base":"bool" }, "default_value":true, "comment":"Pass false to disable unfurling of media content.", "inject_if_not":true }' */
                &p->unfurl_media,
  /* specs/slack/chat.params.json:27:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                &p->username);
  ret = r;
}

size_t slack_chat_post_message_params_to_json(char *json, size_t len, struct slack_chat_post_message_params *p)
{
  size_t r;
  void *arg_switches[16]={NULL};
  /* specs/slack/chat.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
  if (p->token != NULL)
    arg_switches[0] = p->token;

  /* specs/slack/chat.params.json:13:20
     '{ "name": "channel", "type":{ "base":"char", "dec":"*" }, "comment":"Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details.", "inject_if_not":null }' */
  if (p->channel != NULL)
    arg_switches[1] = p->channel;

  /* specs/slack/chat.params.json:14:20
     '{ "name": "attachments", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured attachments, presented as a URL-encoded string.", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[2] = p->attachments;

  /* specs/slack/chat.params.json:15:20
     '{ "name": "blocks", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured blocks, presented as a URL-encoded string.", "inject_if_not":null }' */
  if (p->blocks != NULL)
    arg_switches[3] = p->blocks;

  /* specs/slack/chat.params.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.", "inject_if_not":null }' */
  if (p->text != NULL)
    arg_switches[4] = p->text;

  /* specs/slack/chat.params.json:17:20
     '{ "name": "as_user", "type":{ "base":"bool" }, "comment":"Pass true to post the message as the authed user, instead of as a bot. Defaults to false.", "inject_if_not":false }' */
  if (p->as_user != false)
    arg_switches[5] = &p->as_user;

  /* specs/slack/chat.params.json:18:20
     '{ "name": "icon_emoji", "type":{ "base":"char", "dec":"*" }, "comment":"Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  if (p->icon_emoji != NULL)
    arg_switches[6] = p->icon_emoji;

  /* specs/slack/chat.params.json:19:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "comment":"URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  if (p->icon_url != NULL)
    arg_switches[7] = p->icon_url;

  /* specs/slack/chat.params.json:20:20
     '{ "name": "link_names", "type":{ "base":"bool" }, "comment":"Find and link channel names and usernames.", "inject_if_not":false }' */
  if (p->link_names != false)
    arg_switches[8] = &p->link_names;

  /* specs/slack/chat.params.json:21:20
     '{ "name": "mrkdwn", "type":{ "base":"bool" }, "default_value":true, "comment":"Disable Slack markup parsing by setting to false. Enabled by default.", "inject_if_not":true }' */
  if (p->mrkdwn != true)
    arg_switches[9] = &p->mrkdwn;

  /* specs/slack/chat.params.json:22:20
     '{ "name": "parse", "type":{ "base":"char", "dec":"*" }, "comment":"Change how messages are treated. Defaults to none", "inject_if_not":null }' */
  if (p->parse != NULL)
    arg_switches[10] = p->parse;

  /* specs/slack/chat.params.json:23:20
     '{ "name": "reply_broadcast", "type":{ "base":"bool" }, "comment":"Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false.", "inject_if_not":false }' */
  if (p->reply_broadcast != false)
    arg_switches[11] = &p->reply_broadcast;

  /* specs/slack/chat.params.json:24:20
     '{ "name": "thread_ts", "type":{ "base":"char", "dec":"*" }, "comment":"Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead.", "inject_if_not":null }' */
  if (p->thread_ts != NULL)
    arg_switches[12] = p->thread_ts;

  /* specs/slack/chat.params.json:25:20
     '{ "name": "unfurl_links", "type":{ "base":"bool" }, "comment":"Pass true to enable unfurling of primarily text-based content.", "inject_if_not":false }' */
  if (p->unfurl_links != false)
    arg_switches[13] = &p->unfurl_links;

  /* specs/slack/chat.params.json:26:20
     '{ "name": "unfurl_media", "type":{ "base":"bool" }, "default_value":true, "comment":"Pass false to disable unfurling of media content.", "inject_if_not":true }' */
  if (p->unfurl_media != true)
    arg_switches[14] = &p->unfurl_media;

  /* specs/slack/chat.params.json:27:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  if (p->username != NULL)
    arg_switches[15] = p->username;

  r=json_inject(json, len, 
  /* specs/slack/chat.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
                "(token):s,"
  /* specs/slack/chat.params.json:13:20
     '{ "name": "channel", "type":{ "base":"char", "dec":"*" }, "comment":"Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details.", "inject_if_not":null }' */
                "(channel):s,"
  /* specs/slack/chat.params.json:14:20
     '{ "name": "attachments", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured attachments, presented as a URL-encoded string.", "inject_if_not":null }' */
                "(attachments):s,"
  /* specs/slack/chat.params.json:15:20
     '{ "name": "blocks", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured blocks, presented as a URL-encoded string.", "inject_if_not":null }' */
                "(blocks):s,"
  /* specs/slack/chat.params.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.", "inject_if_not":null }' */
                "(text):s,"
  /* specs/slack/chat.params.json:17:20
     '{ "name": "as_user", "type":{ "base":"bool" }, "comment":"Pass true to post the message as the authed user, instead of as a bot. Defaults to false.", "inject_if_not":false }' */
                "(as_user):b,"
  /* specs/slack/chat.params.json:18:20
     '{ "name": "icon_emoji", "type":{ "base":"char", "dec":"*" }, "comment":"Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                "(icon_emoji):s,"
  /* specs/slack/chat.params.json:19:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "comment":"URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                "(icon_url):s,"
  /* specs/slack/chat.params.json:20:20
     '{ "name": "link_names", "type":{ "base":"bool" }, "comment":"Find and link channel names and usernames.", "inject_if_not":false }' */
                "(link_names):b,"
  /* specs/slack/chat.params.json:21:20
     '{ "name": "mrkdwn", "type":{ "base":"bool" }, "default_value":true, "comment":"Disable Slack markup parsing by setting to false. Enabled by default.", "inject_if_not":true }' */
                "(mrkdwn):b,"
  /* specs/slack/chat.params.json:22:20
     '{ "name": "parse", "type":{ "base":"char", "dec":"*" }, "comment":"Change how messages are treated. Defaults to none", "inject_if_not":null }' */
                "(parse):s,"
  /* specs/slack/chat.params.json:23:20
     '{ "name": "reply_broadcast", "type":{ "base":"bool" }, "comment":"Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false.", "inject_if_not":false }' */
                "(reply_broadcast):b,"
  /* specs/slack/chat.params.json:24:20
     '{ "name": "thread_ts", "type":{ "base":"char", "dec":"*" }, "comment":"Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead.", "inject_if_not":null }' */
                "(thread_ts):s,"
  /* specs/slack/chat.params.json:25:20
     '{ "name": "unfurl_links", "type":{ "base":"bool" }, "comment":"Pass true to enable unfurling of primarily text-based content.", "inject_if_not":false }' */
                "(unfurl_links):b,"
  /* specs/slack/chat.params.json:26:20
     '{ "name": "unfurl_media", "type":{ "base":"bool" }, "default_value":true, "comment":"Pass false to disable unfurling of media content.", "inject_if_not":true }' */
                "(unfurl_media):b,"
  /* specs/slack/chat.params.json:27:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                "(username):s,"
                "@arg_switches:b",
  /* specs/slack/chat.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
                p->token,
  /* specs/slack/chat.params.json:13:20
     '{ "name": "channel", "type":{ "base":"char", "dec":"*" }, "comment":"Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details.", "inject_if_not":null }' */
                p->channel,
  /* specs/slack/chat.params.json:14:20
     '{ "name": "attachments", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured attachments, presented as a URL-encoded string.", "inject_if_not":null }' */
                p->attachments,
  /* specs/slack/chat.params.json:15:20
     '{ "name": "blocks", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured blocks, presented as a URL-encoded string.", "inject_if_not":null }' */
                p->blocks,
  /* specs/slack/chat.params.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.", "inject_if_not":null }' */
                p->text,
  /* specs/slack/chat.params.json:17:20
     '{ "name": "as_user", "type":{ "base":"bool" }, "comment":"Pass true to post the message as the authed user, instead of as a bot. Defaults to false.", "inject_if_not":false }' */
                &p->as_user,
  /* specs/slack/chat.params.json:18:20
     '{ "name": "icon_emoji", "type":{ "base":"char", "dec":"*" }, "comment":"Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                p->icon_emoji,
  /* specs/slack/chat.params.json:19:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "comment":"URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                p->icon_url,
  /* specs/slack/chat.params.json:20:20
     '{ "name": "link_names", "type":{ "base":"bool" }, "comment":"Find and link channel names and usernames.", "inject_if_not":false }' */
                &p->link_names,
  /* specs/slack/chat.params.json:21:20
     '{ "name": "mrkdwn", "type":{ "base":"bool" }, "default_value":true, "comment":"Disable Slack markup parsing by setting to false. Enabled by default.", "inject_if_not":true }' */
                &p->mrkdwn,
  /* specs/slack/chat.params.json:22:20
     '{ "name": "parse", "type":{ "base":"char", "dec":"*" }, "comment":"Change how messages are treated. Defaults to none", "inject_if_not":null }' */
                p->parse,
  /* specs/slack/chat.params.json:23:20
     '{ "name": "reply_broadcast", "type":{ "base":"bool" }, "comment":"Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false.", "inject_if_not":false }' */
                &p->reply_broadcast,
  /* specs/slack/chat.params.json:24:20
     '{ "name": "thread_ts", "type":{ "base":"char", "dec":"*" }, "comment":"Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead.", "inject_if_not":null }' */
                p->thread_ts,
  /* specs/slack/chat.params.json:25:20
     '{ "name": "unfurl_links", "type":{ "base":"bool" }, "comment":"Pass true to enable unfurling of primarily text-based content.", "inject_if_not":false }' */
                &p->unfurl_links,
  /* specs/slack/chat.params.json:26:20
     '{ "name": "unfurl_media", "type":{ "base":"bool" }, "default_value":true, "comment":"Pass false to disable unfurling of media content.", "inject_if_not":true }' */
                &p->unfurl_media,
  /* specs/slack/chat.params.json:27:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
                p->username,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void slack_chat_post_message_params_cleanup_v(void *p) {
  slack_chat_post_message_params_cleanup((struct slack_chat_post_message_params *)p);
}

void slack_chat_post_message_params_init_v(void *p) {
  slack_chat_post_message_params_init((struct slack_chat_post_message_params *)p);
}

void slack_chat_post_message_params_from_json_v(char *json, size_t len, void *p) {
 slack_chat_post_message_params_from_json(json, len, (struct slack_chat_post_message_params*)p);
}

size_t slack_chat_post_message_params_to_json_v(char *json, size_t len, void *p) {
  return slack_chat_post_message_params_to_json(json, len, (struct slack_chat_post_message_params*)p);
}

void slack_chat_post_message_params_list_free_v(void **p) {
  slack_chat_post_message_params_list_free((struct slack_chat_post_message_params**)p);
}

void slack_chat_post_message_params_list_from_json_v(char *str, size_t len, void *p) {
  slack_chat_post_message_params_list_from_json(str, len, (struct slack_chat_post_message_params ***)p);
}

size_t slack_chat_post_message_params_list_to_json_v(char *str, size_t len, void *p){
  return slack_chat_post_message_params_list_to_json(str, len, (struct slack_chat_post_message_params **)p);
}


void slack_chat_post_message_params_cleanup(struct slack_chat_post_message_params *d) {
  /* specs/slack/chat.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
  if (d->token)
    free(d->token);
  /* specs/slack/chat.params.json:13:20
     '{ "name": "channel", "type":{ "base":"char", "dec":"*" }, "comment":"Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details.", "inject_if_not":null }' */
  if (d->channel)
    free(d->channel);
  /* specs/slack/chat.params.json:14:20
     '{ "name": "attachments", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured attachments, presented as a URL-encoded string.", "inject_if_not":null }' */
  if (d->attachments)
    free(d->attachments);
  /* specs/slack/chat.params.json:15:20
     '{ "name": "blocks", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured blocks, presented as a URL-encoded string.", "inject_if_not":null }' */
  if (d->blocks)
    free(d->blocks);
  /* specs/slack/chat.params.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.", "inject_if_not":null }' */
  if (d->text)
    free(d->text);
  /* specs/slack/chat.params.json:17:20
     '{ "name": "as_user", "type":{ "base":"bool" }, "comment":"Pass true to post the message as the authed user, instead of as a bot. Defaults to false.", "inject_if_not":false }' */
  /* p->as_user is a scalar */
  /* specs/slack/chat.params.json:18:20
     '{ "name": "icon_emoji", "type":{ "base":"char", "dec":"*" }, "comment":"Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  if (d->icon_emoji)
    free(d->icon_emoji);
  /* specs/slack/chat.params.json:19:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "comment":"URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  if (d->icon_url)
    free(d->icon_url);
  /* specs/slack/chat.params.json:20:20
     '{ "name": "link_names", "type":{ "base":"bool" }, "comment":"Find and link channel names and usernames.", "inject_if_not":false }' */
  /* p->link_names is a scalar */
  /* specs/slack/chat.params.json:21:20
     '{ "name": "mrkdwn", "type":{ "base":"bool" }, "default_value":true, "comment":"Disable Slack markup parsing by setting to false. Enabled by default.", "inject_if_not":true }' */
  /* p->mrkdwn is a scalar */
  /* specs/slack/chat.params.json:22:20
     '{ "name": "parse", "type":{ "base":"char", "dec":"*" }, "comment":"Change how messages are treated. Defaults to none", "inject_if_not":null }' */
  if (d->parse)
    free(d->parse);
  /* specs/slack/chat.params.json:23:20
     '{ "name": "reply_broadcast", "type":{ "base":"bool" }, "comment":"Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false.", "inject_if_not":false }' */
  /* p->reply_broadcast is a scalar */
  /* specs/slack/chat.params.json:24:20
     '{ "name": "thread_ts", "type":{ "base":"char", "dec":"*" }, "comment":"Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead.", "inject_if_not":null }' */
  if (d->thread_ts)
    free(d->thread_ts);
  /* specs/slack/chat.params.json:25:20
     '{ "name": "unfurl_links", "type":{ "base":"bool" }, "comment":"Pass true to enable unfurling of primarily text-based content.", "inject_if_not":false }' */
  /* p->unfurl_links is a scalar */
  /* specs/slack/chat.params.json:26:20
     '{ "name": "unfurl_media", "type":{ "base":"bool" }, "default_value":true, "comment":"Pass false to disable unfurling of media content.", "inject_if_not":true }' */
  /* p->unfurl_media is a scalar */
  /* specs/slack/chat.params.json:27:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */
  if (d->username)
    free(d->username);
}

void slack_chat_post_message_params_init(struct slack_chat_post_message_params *p) {
  memset(p, 0, sizeof(struct slack_chat_post_message_params));
  /* specs/slack/chat.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:13:20
     '{ "name": "channel", "type":{ "base":"char", "dec":"*" }, "comment":"Channel, private group, or IM channel to send message to. Can be an encoded ID, or a name. See below for more details.", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:14:20
     '{ "name": "attachments", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured attachments, presented as a URL-encoded string.", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:15:20
     '{ "name": "blocks", "type":{ "base":"char", "dec":"*" }, "comment":"A JSON-based array of structured blocks, presented as a URL-encoded string.", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:17:20
     '{ "name": "as_user", "type":{ "base":"bool" }, "comment":"Pass true to post the message as the authed user, instead of as a bot. Defaults to false.", "inject_if_not":false }' */

  /* specs/slack/chat.params.json:18:20
     '{ "name": "icon_emoji", "type":{ "base":"char", "dec":"*" }, "comment":"Emoji to use as the icon for this message. Overrides icon_url. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:19:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "comment":"URL to an image to use as the icon for this message. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:20:20
     '{ "name": "link_names", "type":{ "base":"bool" }, "comment":"Find and link channel names and usernames.", "inject_if_not":false }' */

  /* specs/slack/chat.params.json:21:20
     '{ "name": "mrkdwn", "type":{ "base":"bool" }, "default_value":true, "comment":"Disable Slack markup parsing by setting to false. Enabled by default.", "inject_if_not":true }' */

  /* specs/slack/chat.params.json:22:20
     '{ "name": "parse", "type":{ "base":"char", "dec":"*" }, "comment":"Change how messages are treated. Defaults to none", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:23:20
     '{ "name": "reply_broadcast", "type":{ "base":"bool" }, "comment":"Used in conjunction with thread_ts and indicates whether reply should be made visible to everyone in the channel or conversation. Defaults to false.", "inject_if_not":false }' */

  /* specs/slack/chat.params.json:24:20
     '{ "name": "thread_ts", "type":{ "base":"char", "dec":"*" }, "comment":"Provide another message's ts value to make this message a reply. Avoid using a reply's ts value; use its parent instead.", "inject_if_not":null }' */

  /* specs/slack/chat.params.json:25:20
     '{ "name": "unfurl_links", "type":{ "base":"bool" }, "comment":"Pass true to enable unfurling of primarily text-based content.", "inject_if_not":false }' */

  /* specs/slack/chat.params.json:26:20
     '{ "name": "unfurl_media", "type":{ "base":"bool" }, "default_value":true, "comment":"Pass false to disable unfurling of media content.", "inject_if_not":true }' */

  /* specs/slack/chat.params.json:27:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"Set your bot's user name. Must be used in conjunction with as_user set to false, otherwise ignored.", "inject_if_not":null }' */

}
void slack_chat_post_message_params_list_free(struct slack_chat_post_message_params **p) {
  ntl_free((void**)p, (vfvp)slack_chat_post_message_params_cleanup);
}

void slack_chat_post_message_params_list_from_json(char *str, size_t len, struct slack_chat_post_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct slack_chat_post_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)slack_chat_post_message_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t slack_chat_post_message_params_list_to_json(char *str, size_t len, struct slack_chat_post_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)slack_chat_post_message_params_to_json);
}

