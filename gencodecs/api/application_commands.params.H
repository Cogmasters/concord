STRUCT_BEGIN(discord_create_global_application_command)
  DESC("1-32 lowercase character name")
    FIELD_PTR(char, *, name)

  DESC("1-100 character description")
  COND_WRITE(options != NULL)
    FIELD_STRUCT_PTR(discord_application_command_options, *, options)
  COND_END

  DESC("whether the command is enabled by default when the app is added to a"
       "guild")
    FIELD(bool, default_permission, true)

  COND_WRITE(type != 0)
    FIELD_ENUM(discord_application_command_types, type)
  COND_END
STRUCT_END
