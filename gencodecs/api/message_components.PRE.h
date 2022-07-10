/*****************************************************************************
 * Message Components Datatypes
 * **************************************************************************/

ENUM(discord_component_types)
  /** a container for the other components */
    ENUMERATOR(DISCORD_COMPONENT_ACTION_ROW, = 1)
  /** a button object */
    ENUMERATOR(DISCORD_COMPONENT_BUTTON, = 2)
  /** a select menu for picking from choices */
    ENUMERATOR(DISCORD_COMPONENT_SELECT_MENU, = 3)
  /** a text input object */
    ENUMERATOR_LAST(DISCORD_COMPONENT_TEXT_INPUT, = 4)
ENUM_END

ENUM(discord_component_styles)
  /* button styles */
  /** blurple */
    ENUMERATOR(DISCORD_BUTTON_PRIMARY, = 1)
  /** grey */
    ENUMERATOR(DISCORD_BUTTON_SECONDARY, = 2)
  /** green */
    ENUMERATOR(DISCORD_BUTTON_SUCCESS, = 3)
  /** red */
    ENUMERATOR(DISCORD_BUTTON_DANGER, = 4)
  /** grey, navigates to a URL */
    ENUMERATOR(DISCORD_BUTTON_LINK, = 5)
  /* text styles */
  /** a single-line input */
    ENUMERATOR(DISCORD_TEXT_SHORT, = 1)
  /** a multi-line input */
    ENUMERATOR_LAST(DISCORD_TEXT_PARAGRAPH, = 2)
ENUM_END

/** @CCORD_pub_struct{discord_component} */
PUB_STRUCT(discord_component)
  /** component type */
  COND_WRITE(self->type != 0)
    FIELD_ENUM(type, discord_component_types)
  COND_END
  /** a developer-defined identifier for the component, max 100 characters */
    FIELD_PTR(custom_id, char, *)
  /** whether the component is disabled, default `false` */
    FIELD(disabled, bool, false)
  /** one of button or text styles */
  COND_WRITE(self->style != 0)
    FIELD_ENUM(style, discord_component_styles)
  COND_END
  /** text that appears on the button, max 80 characters */
    FIELD_PTR(label, char, *)
  /** `name`, `id`, and `animated` */
  COND_WRITE(self->emoji != NULL)
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
  COND_END
  /** a url for link-style buttons */
    FIELD_PTR(url, char, *)
  /** the choices in the select, max 25 */
  COND_WRITE(self->options != NULL)
    FIELD_STRUCT_PTR(options, discord_select_options, *)
  COND_END
  /** custom placeholder text if nothing is selected, max 100 characters */
    FIELD_PTR(placeholder, char, *)
  /** the minimum number of items that must be chosen: default 1, min 0,
       max 25 */
  COND_WRITE(self->min_values >= 0 && self->max_values <= 25)
    FIELD(min_values, int, 1)
  COND_END
  /** the maximum number of items that must be chosen: default 1, max 25 */
  COND_WRITE(self->max_values <= 25)
    FIELD(max_values, int, 1)
  COND_END
  /** a list of child components */
  COND_WRITE(self->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  /** the minimum input length for a text input */
    FIELD(min_length, int, 0)
  /** the maximum input length for a text input */
    FIELD(max_length, int, 0)
  /** whether this componentis required to be filled */
    FIELD(required, bool, false)
  /** a pre-filled value for this component */
    FIELD_PTR(value, char, *)
STRUCT_END

/** @CCORD_pub_list{discord_components} */
PUB_LIST(discord_components)
    LISTTYPE_STRUCT(discord_component)
LIST_END

STRUCT(discord_select_option)
  /** the user-facing name of the option, max 100 characters */
    FIELD_PTR(label, char, *)
  /** the dev-define value of the option, max 100 characters */
    FIELD_PTR(value, char, *)
  /** an additional description of the option, max 100 characters */
    FIELD_PTR(description, char, *)
  /** `id`, `name`, and `animated` */
  COND_WRITE(self->emoji != NULL)
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
  COND_END
  /** will render this option as selected by default */
    FIELD_CUSTOM(Default, "default", bool, DECOR_BLANK, INIT_BLANK,
                 CLEANUP_BLANK, GENCODECS_JSON_ENCODER_bool, 
                 GENCODECS_JSON_DECODER_bool, false)
STRUCT_END

/** @CCORD_pub_list{discord_select_options} */
PUB_LIST(discord_select_options)
    LISTTYPE_STRUCT(discord_select_option)
LIST_END
