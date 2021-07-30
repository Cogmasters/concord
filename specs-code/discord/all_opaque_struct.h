/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/audit-log
 */


/**
 * @see https://discord.com/developers/docs/resources/audit-log#get-guild-audit-log
 * @note defined at specs/discord/audit_log.endpoints-params.json:8:22
 */
struct discord_get_guild_audit_log_params;
/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/audit-log
 */


/**
 * @brief Audit Log Structure
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure
 * @note defined at specs/discord/audit_log.json:9:22
 */
struct discord_audit_log;



/**
 * @brief Audit Log Entry Structure
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-entry-structure
 * @note defined at specs/discord/audit_log.json:65:22
 */
struct discord_audit_log_entry;

/**
 * @brief Optional Audit Entry Info Structure
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-optional-audit-entry-info
 * @note defined at specs/discord/audit_log.json:81:22
 */
struct discord_audit_log_entry_optional_info;

/**
 * @brief Audit Log Change Structure
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-structure
 * @note defined at specs/discord/audit_log.json:98:22
 */
struct discord_audit_log_change;

/**
 * @brief Audit Log Change Key
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-key
 * @note defined at specs/discord/audit_log.json:110:22
 */
struct discord_audit_log_change_key;
/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */


/**
 * @brief Modify Channel
 *
 * @see https://discord.com/developers/docs/resources/channel#modify-channel
 * @note defined at specs/discord/channel.endpoints-params.json:10:22
 */
struct discord_modify_channel_params;

/**
 * @brief Get Reactions
 *
 * @see https://discord.com/developers/docs/resources/channel#get-reactions
 * @note defined at specs/discord/channel.endpoints-params.json:35:22
 */
struct discord_get_reactions_params;

/**
 * @brief Edit Channel Permissions
 *
 * @see https://discord.com/developers/docs/resources/channel#edit-channel-permissions
 * @note defined at specs/discord/channel.endpoints-params.json:46:22
 */
struct discord_edit_channel_permissions_params;

/**
 * @brief Follow News Channel
 *
 * @see https://discord.com/developers/docs/resources/channel#follow-news-channel
 * @note defined at specs/discord/channel.endpoints-params.json:58:22
 */
struct discord_follow_news_channel_params;

/**
 * @brief Create Channel Invite
 *
 * @see https://discord.com/developers/docs/resources/channel#create-channel-invite
 * @note defined at specs/discord/channel.endpoints-params.json:68:22
 */
struct discord_create_channel_invite_params;

/**
 * @brief Group DM Add Recipient
 *
 * @see https://discord.com/developers/docs/resources/channel#group-dm-add-recipient
 * @note defined at specs/discord/channel.endpoints-params.json:84:22
 */
struct discord_group_dm_add_recipient_params;

/**
 * @brief Start Thread with Message
 *
 * @see https://discord.com/developers/docs/resources/channel#start-thread-with-message-json-params
 * @note defined at specs/discord/channel.endpoints-params.json:95:22
 */
struct discord_start_thread_with_message_params;

/**
 * @brief Start Thread without Message
 *
 * @see https://discord.com/developers/docs/resources/channel#start-thread-without-message-json-params
 * @note defined at specs/discord/channel.endpoints-params.json:106:22
 */
struct discord_start_thread_without_message_params;

/**
 * @brief List Active Threads
 *
 * @see https://discord.com/developers/docs/resources/channel#list-active-threads-response-body
 * @note defined at specs/discord/channel.endpoints-params.json:118:22
 */
struct discord_thread_response_body;
/* This file is generated from specs/discord/channel.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */




/**
 * @brief Channel Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#channel-object-channel-structure
 * @note defined at specs/discord/channel.json:29:22
 */
struct discord_channel;



/**
 * @brief Message Sticker Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure
 * @note defined at specs/discord/channel.json:82:22
 */
struct discord_message_sticker;



/**
 * @brief Message Reference Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-reference-structure
 * @note defined at specs/discord/channel.json:112:22
 */
struct discord_message_reference;

/**
 * @brief Message Application Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-application-structure
 * @note defined at specs/discord/channel.json:124:22
 */
struct discord_message_application;



/**
 * @brief Message Activity Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure
 * @note defined at specs/discord/channel.json:149:22
 */
struct discord_message_activity;



/**
 * @brief Message Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object
 * @note defined at specs/discord/channel.json:184:22
 */
struct discord_message;

/**
 * @brief Followed Channel Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure
 * @note defined at specs/discord/channel.json:222:22
 */
struct discord_channel_followed_channel;

/**
 * @brief Reaction Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure
 * @note defined at specs/discord/channel.json:233:22
 */
struct discord_channel_reaction;

/**
 * @brief Overwrite Structure
 *
 * @note defined at specs/discord/channel.json:244:22
 */
struct discord_channel_overwrite;

/**
 * @brief Thread Metadata Object
 *
 * @see https://discord.com/developers/docs/resources/channel#thread-metadata-object
 * @note defined at specs/discord/channel.json:259:22
 */
struct discord_thread_metadata;

/**
 * @brief Thread Member Object
 *
 * @see https://discord.com/developers/docs/resources/channel#thread-member-object
 * @note defined at specs/discord/channel.json:273:22
 */
struct discord_thread_member;

/**
 * @brief Attachment Strcture
 *
 * @see https://discord.com/developers/docs/resources/channel#attachment-object
 * @note defined at specs/discord/channel.json:286:22
 */
struct discord_channel_attachment;

/**
 * @brief Channel Mention Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure
 * @note defined at specs/discord/channel.json:302:22
 */
struct discord_channel_mention;

/**
 * @brief Allowed Mentions Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure
 * @note defined at specs/discord/channel.json:315:22
 */
struct discord_channel_allowed_mentions;

/**
 * @brief Embed Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-structure
 * @note defined at specs/discord/channel.json:327:22
 */
struct discord_embed;

/**
 * @brief Embed Thumbnail Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure
 * @note defined at specs/discord/channel.json:349:22
 */
struct discord_embed_thumbnail;

/**
 * @brief Embed Video Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure
 * @note defined at specs/discord/channel.json:361:22
 */
struct discord_embed_video;

/**
 * @brief Embed Image Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure
 * @note defined at specs/discord/channel.json:373:22
 */
struct discord_embed_image;

/**
 * @brief Embed Provider Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure
 * @note defined at specs/discord/channel.json:385:22
 */
struct discord_embed_provider;

/**
 * @brief Embed Author Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure
 * @note defined at specs/discord/channel.json:395:22
 */
struct discord_embed_author;

/**
 * @brief Embed Footer Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure
 * @note defined at specs/discord/channel.json:407:22
 */
struct discord_embed_footer;

/**
 * @brief Embed Field Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure
 * @note defined at specs/discord/channel.json:418:22
 */
struct discord_embed_field;
/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see 
 */


/**
 * @brief Create Guild Emoji
 *
 * @see https://discord.com/developers/docs/resources/emoji#create-guild-emoji
 * @note defined at specs/discord/emoji.endpoints-params.json:10:22
 */
struct discord_create_guild_emoji_params;

/**
 * @brief Modify Guild Emoji
 *
 * @see https://discord.com/developers/docs/resources/emoji#modify-guild-emoji
 * @note defined at specs/discord/emoji.endpoints-params.json:22:22
 */
struct discord_modify_guild_emoji_params;
/* This file is generated from specs/discord/emoji.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/emoji
 */


/**
 * @brief Emoji Structure
 *
 * @see https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
 * @note defined at specs/discord/emoji.json:9:22
 */
struct discord_emoji;
/* This file is generated from specs/discord/gateway.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/gateway
 */










/**
 * @brief Identify Structure
 *
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-structure
 * @note defined at specs/discord/gateway.json:116:22
 */
struct discord_gateway_identify;

/**
 * @brief Gateway Status Update Structure
 *
 * @see https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure
 * @note defined at specs/discord/gateway.json:132:22
 */
struct discord_gateway_status_update;

/**
 * @brief Identify Connection Properties
 *
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties
 * @note defined at specs/discord/gateway.json:147:22
 */
struct discord_gateway_identify_connection;

/**
 * @brief Activity Structure
 *
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure
 * @note defined at specs/discord/gateway.json:158:22
 */
struct discord_gateway_activity;


/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild-template
 */


/**
 * @brief Create Guild From Guild Template
 *
 * @see https://discord.com/developers/docs/resources/guild-template#create-guild-from-guild-template-json-params
 * @note defined at specs/discord/guild-template.endpoints-params.json:10:22
 */
struct discord_create_guild_from_guild_template_params;

/**
 * @brief Create Guild Template
 *
 * @see https://discord.com/developers/docs/resources/guild-template#create-guild-template-json-params
 * @note defined at specs/discord/guild-template.endpoints-params.json:21:22
 */
struct discord_create_guild_template_params;

/**
 * @brief Modify Guild Template
 *
 * @see https://discord.com/developers/docs/resources/guild-template#modify-guild-template-json-params
 * @note defined at specs/discord/guild-template.endpoints-params.json:32:22
 */
struct discord_modify_guild_template_params;
/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild-template
 */


/**
 * @brief Guild Template Structure
 *
 * @see https://discord.com/developers/docs/resources/guild-template#guild-template-object-guild-template-structure
 * @note defined at specs/discord/guild-template.json:9:22
 */
struct discord_guild_template;
/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild
 */


/**
 * @brief Create Guild
 *
 * @see https://discord.com/developers/docs/resources/guild#create-guild
 * @note defined at specs/discord/guild.endpoints-params.json:10:22
 */
struct discord_create_guild_params;

/**
 * @brief Modify Guild
 *
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-json-params
 * @note defined at specs/discord/guild.endpoints-params.json:30:22
 */
struct discord_modify_guild_params;

/**
 * @brief Create Guild Channel
 *
 * @see https://discord.com/developers/docs/resources/guild#create-guild-channel
 * @note defined at specs/discord/guild.endpoints-params.json:58:22
 */
struct discord_create_guild_channel_params;

/**
 * @brief Modify Guild Channel Positions
 *
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-channel-positions-json-params
 * @note defined at specs/discord/guild.endpoints-params.json:77:22
 */
struct discord_modify_guild_channel_positions_params;

/**
 * @brief Search Guild Members
 *
 * @see https://discord.com/developers/docs/resources/guild#search-guild-members-query-string-params
 * @note defined at specs/discord/guild.endpoints-params.json:90:22
 */
struct discord_search_guild_members_params;

/**
 * @brief Add Guild Member
 *
 * @see https://discord.com/developers/docs/resources/guild#add-guild-member-json-params
 * @note defined at specs/discord/guild.endpoints-params.json:101:22
 */
struct discord_add_guild_member_params;

/**
 * @brief Modify Guild Member
 *
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-member
 * @note defined at specs/discord/guild.endpoints-params.json:115:22
 */
struct discord_modify_guild_member_params;

/**
 * @brief Create Guild Role
 *
 * @see https://discord.com/developers/docs/resources/guild#create-guild-role
 * @note defined at specs/discord/guild.endpoints-params.json:129:22
 */
struct discord_create_guild_role_params;

/**
 * @brief Modify Guild Role Positions
 *
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-role-positions-json-params
 * @note defined at specs/discord/guild.endpoints-params.json:143:22
 */
struct discord_modify_guild_role_positions_params;

/**
 * @brief Modify Guild Role
 *
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-role-json-params
 * @note defined at specs/discord/guild.endpoints-params.json:154:22
 */
struct discord_modify_guild_role_params;

/**
 * @brief Get Guild Prune Count
 *
 * @see https://discord.com/developers/docs/resources/guild#get-guild-prune-count-query-string-params
 * @note defined at specs/discord/guild.endpoints-params.json:168:22
 */
struct discord_get_guild_prune_count_params;

/**
 * @brief Begin Guild Prune
 *
 * @see https://discord.com/developers/docs/resources/guild#begin-guild-prune-json-params
 * @note defined at specs/discord/guild.endpoints-params.json:179:22
 */
struct discord_begin_guild_prune_params;
/* This file is generated from specs/discord/guild.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild
 */


/**
 * @brief Guild Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
 * @note defined at specs/discord/guild.json:9:22
 */
struct discord_guild;















/**
 * @brief Unavailable Guild Object
 *
 * @see https://discord.com/developers/docs/resources/guild#unavailable-guild-object
 * @note defined at specs/discord/guild.json:161:23
 */
struct discord_guild_unavailable;

/**
 * @brief Guild Preview Object
 *
 * @see https://discord.com/developers/docs/resources/guild#guild-preview-object
 * @note defined at specs/discord/guild.json:171:23
 */
struct discord_guild_preview;

/**
 * @brief Guild Widget Object
 *
 * @see https://discord.com/developers/docs/resources/guild#guild-widget-object
 * @note defined at specs/discord/guild.json:189:23
 */
struct discord_guild_widget;

/**
 * @brief Guild Member Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#guild-member-object
 * @note defined at specs/discord/guild.json:199:22
 */
struct discord_guild_member;

/**
 * @brief Integration Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
 * @note defined at specs/discord/guild.json:217:22
 */
struct discord_guild_integration;



/**
 * @brief Integration Account Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#integration-account-object-integration-account-structure
 * @note defined at specs/discord/guild.json:251:22
 */
struct discord_guild_integration_account;

/**
 * @brief Integration Application Object
 *
 * @see https://discord.com/developers/docs/resources/guild#integration-application-object-integration-application-structure
 * @note defined at specs/discord/guild.json:261:22
 */
struct discord_guild_integration_application;

/**
 * @brief Ban Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#ban-object
 * @note defined at specs/discord/guild.json:275:22
 */
struct discord_guild_ban;

/**
 * @brief Welcome Screen Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-structure
 * @note defined at specs/discord/guild.json:286:22
 */
struct discord_guild_welcome_screen;

/**
 * @brief Welcome Screen Channel Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure
 * @note defined at specs/discord/guild.json:297:22
 */
struct discord_guild_welcome_screen_channel;
/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/invite
 */


/**
 * @brief Get Invite
 *
 * @see https://discord.com/developers/docs/resources/invite#get-invite-query-string-params
 * @note defined at specs/discord/invite.endpoints-params.json:10:22
 */
struct discord_get_invite_params;
/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/invite
 */




/**
 * @brief Invite Structure
 *
 * @see https://discord.com/developers/docs/resources/invite#invite-object-invite-structure
 * @note defined at specs/discord/invite.json:19:22
 */
struct discord_invite;

/**
 * @brief Invite Metadata Structure
 *
 * @see https://discord.com/developers/docs/resources/invite#invite-metadata-object
 * @note defined at specs/discord/invite.json:36:22
 */
struct discord_invite_metadata;
/* This file is generated from specs/discord/message_components.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/interactions/message-components#message-components
 */


/**
 * @brief Component Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#component-object-component-structure
 * @note defined at specs/discord/message_components.json:9:22
 */
struct discord_component;



/**
 * @brief Button Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#button-object-button-structure
 * @note defined at specs/discord/message_components.json:41:22
 */
struct discord_button;



/**
 * @brief Select Menu Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-menu-structure
 * @note defined at specs/discord/message_components.json:70:22
 */
struct discord_select_menu;

/**
 * @brief Select Option Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-option-structure
 * @note defined at specs/discord/message_components.json:85:22
 */
struct discord_select_option;
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/permissions
 */




/**
 * @brief Role Structure
 *
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-structure
 * @note defined at specs/discord/permissions.json:49:22
 */
struct discord_permissions_role;

/**
 * @brief Role Tags Structure
 *
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-tags-structure
 * @note defined at specs/discord/permissions.json:67:22
 */
struct discord_permissions_role_tags;
/* This file is generated from specs/discord/slash_commands.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/interactions/slash-commands#data-models-and-types
 */


/**
 * @brief Application Command Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-structure
 * @note defined at specs/discord/slash_commands.json:9:22
 */
struct discord_application_command;

/**
 * @brief Application Command Option Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-option-structure
 * @note defined at specs/discord/slash_commands.json:25:22
 */
struct discord_application_command_option;



/**
 * @brief Application Command Option Choice Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-option-choice-structure
 * @note defined at specs/discord/slash_commands.json:58:22
 */
struct discord_application_command_option_choice;

/**
 * @brief Guild Application Command Permissions Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-permissions-object-guild-application-command-permissions-structure
 * @note defined at specs/discord/slash_commands.json:69:22
 */
struct discord_guild_application_command_permissions;

/**
 * @brief Application Command Permissions Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-permissions-object-guild-application-command-permissions-structure
 * @note defined at specs/discord/slash_commands.json:82:22
 */
struct discord_application_command_permissions;



/**
 * @brief Interaction Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-interaction-structure
 * @note defined at specs/discord/slash_commands.json:104:22
 */
struct discord_interaction;



/**
 * @brief Application Command Interaction Data Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-structure
 * @note defined at specs/discord/slash_commands.json:134:22
 */
struct discord_application_command_interaction_data;

/**
 * @brief Application Command Interaction Data Resolved Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-resolved-structure
 * @note defined at specs/discord/slash_commands.json:149:22
 */
struct discord_application_command_interaction_data_resolved;

/**
 * @brief Application Command Interaction Data Option Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-option-structure
 * @note defined at specs/discord/slash_commands.json:162:22
 */
struct discord_application_command_interaction_data_option;

/**
 * @brief Interaction Response Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-response-object-interaction-response-structure
 * @note defined at specs/discord/slash_commands.json:175:22
 */
struct discord_interaction_response;



/**
 * @brief Interaction Application Command Callback Data Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-response-object-interaction-application-command-callback-data-structure
 * @note defined at specs/discord/slash_commands.json:200:22
 */
struct discord_interaction_application_command_callback_data;



/**
 * @brief Message Interaction Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#message-interaction-object-message-interaction-structure
 * @note defined at specs/discord/slash_commands.json:225:22
 */
struct discord_message_interaction;
/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/user
 */


/**
 * @brief Modify Current User
 *
 * @see https://discord.com/developers/docs/resources/user#modify-current-user-json-params
 * @note defined at specs/discord/user.endpoints-params.json:10:22
 */
struct discord_modify_current_user_params;

/**
 * @brief Create Group DM
 *
 * @see https://discord.com/developers/docs/resources/user#create-group-dm-json-params
 * @note defined at specs/discord/user.endpoints-params.json:21:22
 */
struct discord_create_group_dm_params;
/* This file is generated from specs/discord/user.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/user
 */






/**
 * @brief User Structure
 *
 * @note defined at specs/discord/user.json:42:28
 */
struct discord_user;



/**
 * @brief Connection Structure
 *
 * @see https://discord.com/developers/docs/resources/user#connection-object-connection-structure
 * @note defined at specs/discord/user.json:74:28
 */
struct discord_connection;
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/voice-connections
 */







/* This file is generated from specs/discord/voice.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/voice
 */


/**
 * @brief Voice State Structure
 *
 * @see https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure
 * @note defined at specs/discord/voice.json:9:22
 */
struct discord_voice_state;

/**
 * @brief Voice Region Structure
 *
 * @see https://discord.com/developers/docs/resources/voice#voice-region-object-voice-region-structure
 * @note defined at specs/discord/voice.json:29:22
 */
struct discord_voice_region;
/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/webhook
 */


/**
 * @brief Create Webhook
 *
 * @see https://discord.com/developers/docs/resources/webhook#create-webhook
 * @note defined at specs/discord/webhook.endpoints-params.json:10:22
 */
struct discord_create_webhook_params;

/**
 * @brief Modify Webhook
 *
 * @see https://discord.com/developers/docs/resources/webhook#modify-webhook
 * @note defined at specs/discord/webhook.endpoints-params.json:21:22
 */
struct discord_modify_webhook_params;

/**
 * @brief Execute Webhook
 *
 * @see https://discord.com/developers/docs/resources/webhook#execute-webhook
 * @note defined at specs/discord/webhook.endpoints-params.json:33:22
 */
struct discord_execute_webhook_params;

/**
 * @brief Edit Webhook Message
 *
 * @see https://discord.com/developers/docs/resources/webhook#edit-webhook-message
 * @note defined at specs/discord/webhook.endpoints-params.json:78:22
 */
struct discord_edit_webhook_message_params;
/* This file is generated from specs/discord/webhook.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_opaque_struct.h
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/webhook
 */


/**
 * @brief Webhook Structure
 *
 * @see https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
 * @note defined at specs/discord/webhook.json:9:22
 */
struct discord_webhook;


