/*****************************************************************************
 * Message Components Datatypes
 * **************************************************************************/

ENUM(discord_component_types)
  DESC("a container for the other components")
    ENUMERATOR(DISCORD_COMPONENT_ACTION_ROW, = 1)
  DESC("a button object")
    ENUMERATOR(DISCORD_COMPONENT_BUTTON, = 2)
  DESC("a select menu for picking from choices")
    ENUMERATOR(DISCORD_COMPONENT_SELECT_MENU, = 3)
  DESC("a text input object")
    ENUMERATOR_LAST(DISCORD_COMPONENT_TEXT_INPUT, = 4)
ENUM_END

ENUM(discord_component_styles)
  /* button styles */
  DESC("blurple")
    ENUMERATOR(DISCORD_BUTTON_PRIMARY, = 1)
  DESC("grey")
    ENUMERATOR(DISCORD_BUTTON_SECONDARY, = 2)
  DESC("green")
    ENUMERATOR(DISCORD_BUTTON_SUCCESS, = 3)
  DESC("red")
    ENUMERATOR(DISCORD_BUTTON_DANGER, = 4)
  DESC("grey, navigates to a URL")
    ENUMERATOR(DISCORD_BUTTON_LINK, = 5)
  /* text styles */
  DESC("a single-line input")
    ENUMERATOR(DISCORD_TEXT_SHORT, = 1)
  DESC("a multi-line input")
    ENUMERATOR_LAST(DISCORD_TEXT_PARAGRAPH, = 2)
ENUM_END

PUB_STRUCT(discord_component)
  DESC("component type")
  COND_WRITE(this->type != 0)
    FIELD_ENUM(type, discord_component_types)
  COND_END
  DESC("whether the component is disabled, default `false`")
    FIELD(disabled, bool, false)
  DESC("one of button or text styles")
  COND_WRITE(this->style != 0)
    FIELD_ENUM(style, discord_component_styles)
  COND_END
  DESC("text that appears on the button, max 80 characters")
    FIELD_PTR(label, char, *)
  DESC("`name`, `id`, and `animated`")
  COND_WRITE(this->emoji != NULL)
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
  COND_END
  DESC("a url for link-style buttons")
    FIELD_PTR(url, char, *)
  DESC("the choices in the select, max 25")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_select_options, *)
  COND_END
  DESC("custom placeholder text if nothing is selected, max 100 characters")
    FIELD_PTR(placeholder, char, *)
  DESC("the minimum number of items that must be chosen: default 1, min 0,"
       "max 25")
  COND_WRITE(this->min_values >= 0 && this->max_values <= 25)
    FIELD(min_values, int, 1)
  COND_END
  DESC("the maximum number of items that must be chosen: default 1, max 25")
  COND_WRITE(this->max_values <= 25)
    FIELD(max_values, int, 1)
  COND_END
  DESC("a list of child components")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  DESC("the minimum input length for a text input")
    FIELD(min_length, int, 0)
  DESC("the maximum input length for a text input")
    FIELD(max_length, int, 0)
  DESC("whether this componentis required to be filled")
    FIELD(required, bool, false)
  DESC("a pre-filled value for this component")
    FIELD_PTR(value, char, *)
STRUCT_END

PUB_LIST(discord_components)
    LISTTYPE_STRUCT(discord_component)
LIST_END

STRUCT(discord_select_option)
  DESC("the user-facing name of the option, max 100 characters")
    FIELD_PTR(label, char, *)
  DESC("the dev-define value of the option, max 100 characters")
    FIELD_PTR(value, char, *)
  DESC("an additional description of the option, max 100 characters")
    FIELD_PTR(description, char, *)
  DESC("`id`, `name`, and `animated`")
  COND_WRITE(this->emoji != NULL)
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
  COND_END
  DESC("will render this option as selected by default")
    FIELD_CUSTOM(Default, "default", bool, DECOR_BLANK, INIT_BLANK,
                 CLEANUP_BLANK, JSON_ENCODER_bool, JSON_DECODER_bool, false)
STRUCT_END

PUB_LIST(discord_select_options)
    LISTTYPE_STRUCT(discord_select_option)
LIST_END
