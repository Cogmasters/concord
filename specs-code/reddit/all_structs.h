/* This file is generated from specs/reddit/links_n_comments.json, Please don't edit it. */
/**
 * @file specs-code/reddit/all_structs.h
 * @author cee-studio
 * @date 21 Jun 2021
 * @brief Specs generated file
 * @see 
 */


/**
 * @brief Comment
 *
 * @see https://www.reddit.com/dev/api/#POST_api_comment
 * @note defined at specs/reddit/links_n_comments.json:10:22
 */
struct reddit_comment_params {
  /* specs/reddit/links_n_comments.json:13:20
     '{ "name": "api_type", "type":{ "base":"char", "dec":"*" }, "comment":"the string json" }' */
  char *api_type; // the string json

  /* specs/reddit/links_n_comments.json:14:20
     '{ "name": "return_rtjson", "type":{ "base":"bool" }, "comment":"boolean value" }' */
  bool return_rtjson; // boolean value

  /* specs/reddit/links_n_comments.json:15:20
     '{ "name": "richtext_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON data" }' */
  char *richtext_json; // JSON data

  /* specs/reddit/links_n_comments.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"raw markdown text" }' */
  char *text; // raw markdown text

  /* specs/reddit/links_n_comments.json:17:20
     '{ "name": "thing_id", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of parent thing" }' */
  char *thing_id; // fullname of parent thing

  /* specs/reddit/links_n_comments.json:18:20
     '{ "name": "uh", "type":{ "base":"char", "dec":"*" }, "comment":"a modhash" }' */
  char *uh; // a modhash

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/reddit/oauth2.json, Please don't edit it. */
/**
 * @file specs-code/reddit/all_structs.h
 * @author cee-studio
 * @date 21 Jun 2021
 * @brief Specs generated file
 * @see https://github.com/reddit-archive/reddit/wiki/OAuth2-Quick-Start-Example
 */


/**
 * @brief Access Token
 *
 * @note defined at specs/reddit/oauth2.json:9:22
 */
struct reddit_access_token_params {
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
  char *grant_type; // 'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps

  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
  char *username; // username for script app

  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
  char *password; // password for script app

  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
  char *code; // the code retrieved by the webapp

  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
  char *redirect_uri; // redirect uri for webapp

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/reddit/search.json, Please don't edit it. */
/**
 * @file specs-code/reddit/all_structs.h
 * @author cee-studio
 * @date 21 Jun 2021
 * @brief Specs generated file
 * @see 
 */


/**
 * @brief Search
 *
 * @see https://www.reddit.com/dev/api/#GET_search
 * @note defined at specs/reddit/search.json:10:22
 */
struct reddit_search_params {
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  char *after; // fullname of a thing

  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  char *before; // fullname of a thing

  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
  char *category; // a string no longer than 5 character

  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
  int count; // a positive integer (default: 0)

  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  bool include_facets; // boolean value

  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
  int limit; // the maximum number of items desired (default: 25, maximum: 100)

  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
  char *q; // a string no longer than 512 characters

  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  bool restrict_sr; // boolean value

  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
  char *show; // (optional)the string all

  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
  char *sort; // one of(relevance, hot, top, new, comments)

  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
  char *sr_detail; // expand subreddits

  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
  char *t; // one of(hour, day, week, month, year, all)

  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
  char *type; // (optional) comma-delimited list of result types (sr, link, user)

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[13];
    void *record_defined[13];
    void *record_null[13];
  } __M; // metadata
/// @endcond
};
