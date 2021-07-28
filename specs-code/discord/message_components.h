/* This file is generated from specs/discord/message_components.json, Please don't edit it. */
/**
 * @file specs-code/discord/message_components.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/interactions/message-components#message-components
 */


/**
 * @brief Component Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#component-object-component-structure
 * @note defined at specs/discord/message_components.json:9:22
 */
struct discord_component {
  /* specs/discord/message_components.json:12:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment":"component type"}' */
  enum discord_component_types type; ///< component type

  /* specs/discord/message_components.json:13:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "inject_if_not":"", "comment":"a developer-defined identifier for the component, max 100 characters"}' */
  char custom_id[100+1]; ///< a developer-defined identifier for the component, max 100 characters

  /* specs/discord/message_components.json:14:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"whether the component is disabled, default false"}' */
  bool disabled; ///< whether the component is disabled, default false

  /* specs/discord/message_components.json:15:18
     '{"name":"style", "type":{"base":"int", "int_alias":"enum discord_button_styles"}, "option":true, "inject_if_not":0, "comment":"one of button styles"}' */
  enum discord_button_styles style; ///< one of button styles

  /* specs/discord/message_components.json:16:18
     '{"name":"label", "type":{"base":"char", "dec":"[80+1]"}, "option":true, "comment":"text that appears on the button, max 80 characters", "inject_if_not":""}' */
  char label[80+1]; ///< text that appears on the button, max 80 characters

  /* specs/discord/message_components.json:17:18
     '{"name":"emoji", "type":{"base":"struct discord_emoji", "dec":"*"}, "option":true, "comment":"name, id and animated", "inject_if_not":null}' */
  struct discord_emoji *emoji; ///< name, id and animated

  /* specs/discord/message_components.json:18:18
     '{"name":"url", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a url for link-style buttons", "inject_if_not":null}' */
  char *url; ///< a url for link-style buttons

  /* specs/discord/message_components.json:19:18
     '{"name":"options", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the choices in the select, max 25", "inject_if_not":null}' */
  struct discord_select_option **options; ///< the choices in the select, max 25

  /* specs/discord/message_components.json:20:18
     '{"name":"placeholder", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"custom placeholder text if nothing is selected, max 100 characters", "inject_if_not":""}' */
  char placeholder[100+1]; ///< custom placeholder text if nothing is selected, max 100 characters

  /* specs/discord/message_components.json:21:18
     '{"name":"min_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the minimum number of items that must be chosen; default 1, min 0, max 25"}' */
  int min_values; ///< the minimum number of items that must be chosen; default 1, min 0, max 25

  /* specs/discord/message_components.json:22:18
     '{"name":"max_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the maximum number of items that must be chosen; default 1, min 0, max 25"}' */
  int max_values; ///< the maximum number of items that must be chosen; default 1, min 0, max 25

  /* specs/discord/message_components.json:23:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"a list of child components", "inject_if_not":null}' */
  struct discord_component **components; ///< a list of child components

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[12];
    void *record_defined[12];
    void *record_null[12];
  } __M; // metadata
/// @endcond
};
extern void discord_component_cleanup_v(void *p);
extern void discord_component_cleanup(struct discord_component *p);
extern void discord_component_init_v(void *p);
extern void discord_component_init(struct discord_component *p);
extern struct discord_component * discord_component_alloc();
extern void discord_component_free_v(void *p);
extern void discord_component_free(struct discord_component *p);
extern void discord_component_from_json_v(char *json, size_t len, void *pp);
extern void discord_component_from_json(char *json, size_t len, struct discord_component **pp);
extern size_t discord_component_to_json_v(char *json, size_t len, void *p);
extern size_t discord_component_to_json(char *json, size_t len, struct discord_component *p);
extern size_t discord_component_to_query_v(char *json, size_t len, void *p);
extern size_t discord_component_to_query(char *json, size_t len, struct discord_component *p);
extern void discord_component_list_free_v(void **p);
extern void discord_component_list_free(struct discord_component **p);
extern void discord_component_list_from_json_v(char *str, size_t len, void *p);
extern void discord_component_list_from_json(char *str, size_t len, struct discord_component ***p);
extern size_t discord_component_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_component_list_to_json(char *str, size_t len, struct discord_component **p);


enum discord_component_types {
  DISCORD_COMPONENT_ACTION_ROW = 1,
  DISCORD_COMPONENT_BUTTON = 2,
  DISCORD_COMPONENT_SELECT_MENU = 3,
};
extern char* discord_component_types_to_string(enum discord_component_types);
extern enum discord_component_types discord_component_types_from_string(char*);
extern bool discord_component_types_has(enum discord_component_types, char*);

/**
 * @brief Button Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#button-object-button-structure
 * @note defined at specs/discord/message_components.json:41:22
 */
struct discord_button {
  /* specs/discord/message_components.json:44:18
     '{"name":"type", "type": {"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment": "2 for a button"}' */
  enum discord_component_types type; ///< 2 for a button

  /* specs/discord/message_components.json:45:18
     '{"name":"style", "type": {"base":"int", "int_alias":"enum discord_button_styles"}, "inject_if_not":0, "comment": "one of button styles"}' */
  enum discord_button_styles style; ///< one of button styles

  /* specs/discord/message_components.json:46:18
     '{"name":"label", "type":{"base":"char", "dec":"[80+1]"}, "option":true, "comment":"text that appears on the button, max 80 characters", "inject_if_not":""}' */
  char label[80+1]; ///< text that appears on the button, max 80 characters

  /* specs/discord/message_components.json:47:18
     '{"name":"emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "option":true, "comment":"name, id and animated", "inject_if_not":null}' */
  struct discord_emoji *emoji; ///< name, id and animated

  /* specs/discord/message_components.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"a developer-defined identifier for the component, max 100 characters", "inject_if_not":""}' */
  char custom_id[100+1]; ///< a developer-defined identifier for the component, max 100 characters

  /* specs/discord/message_components.json:49:18
     '{"name":"url", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a url for link-style buttons", "inject_if_not":null}' */
  char *url; ///< a url for link-style buttons

  /* specs/discord/message_components.json:50:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"whether the component is disabled, default false"}' */
  bool disabled; ///< whether the component is disabled, default false

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};
extern void discord_button_cleanup_v(void *p);
extern void discord_button_cleanup(struct discord_button *p);
extern void discord_button_init_v(void *p);
extern void discord_button_init(struct discord_button *p);
extern struct discord_button * discord_button_alloc();
extern void discord_button_free_v(void *p);
extern void discord_button_free(struct discord_button *p);
extern void discord_button_from_json_v(char *json, size_t len, void *pp);
extern void discord_button_from_json(char *json, size_t len, struct discord_button **pp);
extern size_t discord_button_to_json_v(char *json, size_t len, void *p);
extern size_t discord_button_to_json(char *json, size_t len, struct discord_button *p);
extern size_t discord_button_to_query_v(char *json, size_t len, void *p);
extern size_t discord_button_to_query(char *json, size_t len, struct discord_button *p);
extern void discord_button_list_free_v(void **p);
extern void discord_button_list_free(struct discord_button **p);
extern void discord_button_list_from_json_v(char *str, size_t len, void *p);
extern void discord_button_list_from_json(char *str, size_t len, struct discord_button ***p);
extern size_t discord_button_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_button_list_to_json(char *str, size_t len, struct discord_button **p);


enum discord_button_styles {
  DISCORD_BUTTON_PRIMARY = 1, // blurple, requires custom_id
  DISCORD_BUTTON_SECONDARY = 2, // grey, requires custom_id
  DISCORD_BUTTON_SUCCESS = 3, // green, requires custom_id
  DISCORD_BUTTON_DANGER = 4, // red, requires custom_id
  DISCORD_BUTTON_LINK = 5, // grey, requires url
};
extern char* discord_button_styles_to_string(enum discord_button_styles);
extern enum discord_button_styles discord_button_styles_from_string(char*);
extern bool discord_button_styles_has(enum discord_button_styles, char*);

/**
 * @brief Select Menu Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-menu-structure
 * @note defined at specs/discord/message_components.json:70:22
 */
struct discord_select_menu {
  /* specs/discord/message_components.json:73:18
     '{"name":"type", "type": {"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment": "3 for a select menu"}' */
  enum discord_component_types type; ///< 3 for a select menu

  /* specs/discord/message_components.json:74:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters", "inject_if_not":""}' */
  char custom_id[100+1]; ///< a developer-defined identifier for the component, max 100 characters

  /* specs/discord/message_components.json:75:18
     '{"name":"options", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "comment":"the choices in the select, max 25"}' */
  struct discord_select_option **options; ///< the choices in the select, max 25

  /* specs/discord/message_components.json:76:18
     '{"name":"placeholder", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"custom placeholder text if nothing is selected, max 100 characters", "inject_if_not":""}' */
  char placeholder[100+1]; ///< custom placeholder text if nothing is selected, max 100 characters

  /* specs/discord/message_components.json:77:18
     '{"name":"min_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the minimum number of items that must be chosen; default 1, min 0, max 25"}' */
  int min_values; ///< the minimum number of items that must be chosen; default 1, min 0, max 25

  /* specs/discord/message_components.json:78:18
     '{"name":"max_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the maximum number of items that must be chosen; default 1, min 0, max 25"}' */
  int max_values; ///< the maximum number of items that must be chosen; default 1, min 0, max 25

  /* specs/discord/message_components.json:79:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"disable the select, default false"}' */
  bool disabled; ///< disable the select, default false

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};
extern void discord_select_menu_cleanup_v(void *p);
extern void discord_select_menu_cleanup(struct discord_select_menu *p);
extern void discord_select_menu_init_v(void *p);
extern void discord_select_menu_init(struct discord_select_menu *p);
extern struct discord_select_menu * discord_select_menu_alloc();
extern void discord_select_menu_free_v(void *p);
extern void discord_select_menu_free(struct discord_select_menu *p);
extern void discord_select_menu_from_json_v(char *json, size_t len, void *pp);
extern void discord_select_menu_from_json(char *json, size_t len, struct discord_select_menu **pp);
extern size_t discord_select_menu_to_json_v(char *json, size_t len, void *p);
extern size_t discord_select_menu_to_json(char *json, size_t len, struct discord_select_menu *p);
extern size_t discord_select_menu_to_query_v(char *json, size_t len, void *p);
extern size_t discord_select_menu_to_query(char *json, size_t len, struct discord_select_menu *p);
extern void discord_select_menu_list_free_v(void **p);
extern void discord_select_menu_list_free(struct discord_select_menu **p);
extern void discord_select_menu_list_from_json_v(char *str, size_t len, void *p);
extern void discord_select_menu_list_from_json(char *str, size_t len, struct discord_select_menu ***p);
extern size_t discord_select_menu_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_select_menu_list_to_json(char *str, size_t len, struct discord_select_menu **p);

/**
 * @brief Select Option Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-option-structure
 * @note defined at specs/discord/message_components.json:85:22
 */
struct discord_select_option {
  /* specs/discord/message_components.json:88:18
     '{"name":"label", "type":{"base":"char", "dec":"[25+1]"}, "inject_if_not":"", "comment":"the user-facing name of the option, max 25 characters"}' */
  char label[25+1]; ///< the user-facing name of the option, max 25 characters

  /* specs/discord/message_components.json:89:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "inject_if_not":"", "comment":"the dev define value of the option, max 100 characters"}' */
  char value[100+1]; ///< the dev define value of the option, max 100 characters

  /* specs/discord/message_components.json:90:18
     '{"name":"description", "type":{"base":"char", "dec":"[50+1]"}, "inject_if_not":"", "option":true, "comment":"a additional description of the option, max 50 characters"}' */
  char description[50+1]; ///< a additional description of the option, max 50 characters

  /* specs/discord/message_components.json:91:18
     '{"name":"emoji", "type":{"base":"struct discord_emoji", "dec":"*"}, "inject_if_not":null, "option":true, "comment":"name, id and animated"}' */
  struct discord_emoji *emoji; ///< name, id and animated

  /* specs/discord/message_components.json:92:18
     '{"name":"Default", "json_key":"default", "type":{"base":"bool"}, "option":true, "comment":"will render this option as selected by default"}' */
  bool Default; ///< will render this option as selected by default

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
extern void discord_select_option_cleanup_v(void *p);
extern void discord_select_option_cleanup(struct discord_select_option *p);
extern void discord_select_option_init_v(void *p);
extern void discord_select_option_init(struct discord_select_option *p);
extern struct discord_select_option * discord_select_option_alloc();
extern void discord_select_option_free_v(void *p);
extern void discord_select_option_free(struct discord_select_option *p);
extern void discord_select_option_from_json_v(char *json, size_t len, void *pp);
extern void discord_select_option_from_json(char *json, size_t len, struct discord_select_option **pp);
extern size_t discord_select_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_select_option_to_json(char *json, size_t len, struct discord_select_option *p);
extern size_t discord_select_option_to_query_v(char *json, size_t len, void *p);
extern size_t discord_select_option_to_query(char *json, size_t len, struct discord_select_option *p);
extern void discord_select_option_list_free_v(void **p);
extern void discord_select_option_list_free(struct discord_select_option **p);
extern void discord_select_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_select_option_list_from_json(char *str, size_t len, struct discord_select_option ***p);
extern size_t discord_select_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_select_option_list_to_json(char *str, size_t len, struct discord_select_option **p);
