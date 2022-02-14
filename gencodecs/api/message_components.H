/*****************************************************************************
 * Message Components Datatypes
 * **************************************************************************/

ENUM(discord_component_types)
  PP("a container for the other components")
    ENUMERATOR(DISCORD_COMPONENT_ACTION_ROW, = 1)
  PP("a button object")
    ENUMERATOR(DISCORD_COMPONENT_BUTTON, = 2)
  PP("a select menu for picking from choices")
    ENUMERATOR(DISCORD_COMPONENT_SELECT_MENU, = 3)
  PP("a text input object")
    ENUMERATOR_LAST(DISCORD_COMPONENT_TEXT_INPUT, = 4)
ENUM_END

ENUM(discord_component_styles)
  /* button styles */
  PP("blurple")
    ENUMERATOR(DISCORD_BUTTON_PRIMARY, = 1)
  PP("grey")
    ENUMERATOR(DISCORD_BUTTON_SECONDARY, = 2)
  PP("green")
    ENUMERATOR(DISCORD_BUTTON_SUCCESS, = 3)
  PP("red")
    ENUMERATOR(DISCORD_BUTTON_DANGER, = 4)
  PP("grey, navigates to a URL")
    ENUMERATOR(DISCORD_BUTTON_LINK, = 5)
  /* text styles */
  PP("a single-line input")
    ENUMERATOR(DISCORD_TEXT_SHORT, = 1)
  PP("a multi-line input")
    ENUMERATOR_LAST(DISCORD_TEXT_PARAGRAPH, = 2)
ENUM_END

PUB_STRUCT(discord_component)
  PP("component type")
  COND_WRITE(this->type != 0)
    FIELD_ENUM(type, discord_component_types)
  COND_END
  PP("whether the component is disabled, default `false`")
    FIELD(disabled, bool, false)
  PP("one of button or text styles")
  COND_WRITE(this->style != 0)
    FIELD_ENUM(style, discord_component_styles)
  COND_END
  PP("text that appears on the button, max 80 characters")
    FIELD_PTR(label, char, *)
  PP("`name`, `id`, and `animated`")
  COND_WRITE(this->emoji != NULL)
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
  COND_END
  PP("a url for link-style buttons")
    FIELD_PTR(url, char, *)
  PP("the choices in the select, max 25")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_select_options, *)
  COND_END
  PP("custom placeholder text if nothing is selected, max 100 characters")
    FIELD_PTR(placeholder, char, *)
  PP("the minimum number of items that must be chosen: default 1, min 0,"
       "max 25")
  COND_WRITE(this->min_values >= 0 && this->max_values <= 25)
    FIELD(min_values, int, 1)
  COND_END
  PP("the maximum number of items that must be chosen: default 1, max 25")
  COND_WRITE(this->max_values <= 25)
    FIELD(max_values, int, 1)
  COND_END
  PP("a list of child components")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  PP("the minimum input length for a text input")
    FIELD(min_length, int, 0)
  PP("the maximum input length for a text input")
    FIELD(max_length, int, 0)
  PP("whether this componentis required to be filled")
    FIELD(required, bool, false)
  PP("a pre-filled value for this component")
    FIELD_PTR(value, char, *)
STRUCT_END

PUB_LIST(discord_components)
    LISTTYPE_STRUCT(discord_component)
LIST_END

STRUCT(discord_select_option)
  PP("the user-facing name of the option, max 100 characters")
    FIELD_PTR(label, char, *)
  PP("the dev-define value of the option, max 100 characters")
    FIELD_PTR(value, char, *)
  PP("an additional description of the option, max 100 characters")
    FIELD_PTR(description, char, *)
  PP("`id`, `name`, and `animated`")
  COND_WRITE(this->emoji != NULL)
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
  COND_END
  PP("will render this option as selected by default")
    FIELD_CUSTOM(Default, "default", bool, DECOR_BLANK, INIT_BLANK,
                 CLEANUP_BLANK, JSON_ENCODER_bool, JSON_DECODER_bool, false)
STRUCT_END

PUB_LIST(discord_select_options)
    LISTTYPE_STRUCT(discord_select_option)
LIST_END
