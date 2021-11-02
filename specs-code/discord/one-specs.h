/* This file is generated from specs/discord/application.json, Please don't edit it. */
/**
 * @file specs-code/discord/one-specs.h
 * @see https://discord.com/developers/docs/resources/application
 */


/* defined at specs/discord/application.json:9:22 */
/**
 * @brief Application Structure
 *
 * @see https://discord.com/developers/docs/resources/application#application-object-application-structure
 */
struct discord_application;


/* This file is generated from specs/discord/application_commands.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/application_commands.endpoints-params.json:10:22 */
/**
 * @brief Create Global Application Command
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#create-global-application-command
 */
struct discord_create_global_application_command_params;

/* defined at specs/discord/application_commands.endpoints-params.json:24:23 */
/**
 * @brief Edit Global Application Command
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-global-application-command
 */
struct discord_edit_global_application_command_params;

/* defined at specs/discord/application_commands.endpoints-params.json:37:23 */
/**
 * @brief Create Guild Application Command
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#create-guild-application-command
 */
struct discord_create_guild_application_command_params;

/* defined at specs/discord/application_commands.endpoints-params.json:51:23 */
/**
 * @brief Edit Guild Application Command
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-guild-application-command
 */
struct discord_edit_guild_application_command_params;

/* defined at specs/discord/application_commands.endpoints-params.json:64:23 */
/**
 * @brief Edit Application Command Permissions
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-application-command-permissions
 */
struct discord_edit_application_command_permissions_params;
/* This file is generated from specs/discord/application_commands.json, Please don't edit it. */

/* defined at specs/discord/application_commands.json:9:22 */
/**
 * @brief Application Command Structure
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-structure
 */
struct discord_application_command;



/* defined at specs/discord/application_commands.json:38:22 */
/**
 * @brief Application Command Option Structure
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-structure
 */
struct discord_application_command_option;



/* defined at specs/discord/application_commands.json:72:22 */
/**
 * @brief Application Command Option Choice Structure
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-choice-structure
 */
struct discord_application_command_option_choice;

/* defined at specs/discord/application_commands.json:83:22 */
/**
 * @brief Guild Application Command Permissions Structure
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-guild-application-command-permissions-structure
 */
struct discord_guild_application_command_permissions;

/* defined at specs/discord/application_commands.json:96:22 */
/**
 * @brief Application Command Permissions Structure
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-application-command-permissions-structure
 */
struct discord_application_command_permissions;



/* defined at specs/discord/application_commands.json:119:22 */
/**
 * @brief Application Command Interaction Data Option Structure
 *
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-interaction-data-option-structure
 */
struct discord_application_command_interaction_data_option;
/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/audit_log.endpoints-params.json:7:22 */
/**
 */
struct discord_get_guild_audit_log_params;
/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */

/* defined at specs/discord/audit_log.json:9:22 */
/**
 * @brief Audit Log Structure
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure
 */
struct discord_audit_log;

/* defined at specs/discord/audit_log.json:23:22 */
/**
 * @brief Audit Log Entry Structure
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-entry-structure
 */
struct discord_audit_log_entry;



/* defined at specs/discord/audit_log.json:91:22 */
/**
 * @brief Optional Audit Entry Info Structure
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-optional-audit-entry-info
 */
struct discord_optional_audit_entry_info;

/* defined at specs/discord/audit_log.json:108:22 */
/**
 * @brief Audit Log Change Structure
 *
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-structure
 */
struct discord_audit_log_change;
/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/channel.endpoints-params.json:9:22 */
/**
 * @brief Modify Channel
 *
 */
struct discord_modify_channel_params;

/* defined at specs/discord/channel.endpoints-params.json:33:22 */
/**
 * @brief Create Message
 *
 */
struct discord_create_message_params;

/* defined at specs/discord/channel.endpoints-params.json:50:22 */
/**
 * @brief Get Channel Messages
 *
 */
struct discord_get_channel_messages_params;

/* defined at specs/discord/channel.endpoints-params.json:62:22 */
/**
 * @brief Get Reactions
 *
 */
struct discord_get_reactions_params;

/* defined at specs/discord/channel.endpoints-params.json:72:22 */
/**
 * @brief Edit Channel Permissions
 *
 */
struct discord_edit_channel_permissions_params;

/* defined at specs/discord/channel.endpoints-params.json:83:22 */
/**
 * @brief Edit Message
 *
 */
struct discord_edit_message_params;

/* defined at specs/discord/channel.endpoints-params.json:98:22 */
/**
 * @brief Follow News Channel
 *
 */
struct discord_follow_news_channel_params;

/* defined at specs/discord/channel.endpoints-params.json:107:22 */
/**
 * @brief Create Channel Invite
 *
 */
struct discord_create_channel_invite_params;

/* defined at specs/discord/channel.endpoints-params.json:122:22 */
/**
 * @brief Group DM Add Recipient
 *
 */
struct discord_group_dm_add_recipient_params;

/* defined at specs/discord/channel.endpoints-params.json:132:22 */
/**
 * @brief Start Thread with Message
 *
 */
struct discord_start_thread_with_message_params;

/* defined at specs/discord/channel.endpoints-params.json:142:22 */
/**
 * @brief Start Thread without Message
 *
 */
struct discord_start_thread_without_message_params;

/* defined at specs/discord/channel.endpoints-params.json:153:22 */
/**
 * @brief List Active Threads
 *
 */
struct discord_thread_response_body;
/* This file is generated from specs/discord/channel.json, Please don't edit it. */



/* defined at specs/discord/channel.json:29:22 */
/**
 * @brief Channel Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#channel-object-channel-structure
 */
struct discord_channel;



/* defined at specs/discord/channel.json:80:22 */
/**
 * @brief Message Sticker Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure
 */
struct discord_message_sticker;



/* defined at specs/discord/channel.json:110:22 */
/**
 * @brief Message Reference Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-reference-structure
 */
struct discord_message_reference;

/* defined at specs/discord/channel.json:122:22 */
/**
 * @brief Message Application Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-application-structure
 */
struct discord_message_application;



/* defined at specs/discord/channel.json:147:22 */
/**
 * @brief Message Activity Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure
 */
struct discord_message_activity;



/* defined at specs/discord/channel.json:182:22 */
/**
 * @brief Message Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#message-object
 */
struct discord_message;

/* defined at specs/discord/channel.json:219:22 */
/**
 * @brief Followed Channel Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure
 */
struct discord_followed_channel;

/* defined at specs/discord/channel.json:229:22 */
/**
 * @brief Reaction Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure
 */
struct discord_reaction;

/* defined at specs/discord/channel.json:239:22 */
/**
 * @brief Overwrite Structure
 *
 */
struct discord_overwrite;

/* defined at specs/discord/channel.json:254:22 */
/**
 * @brief Thread Metadata Object
 *
 * @see https://discord.com/developers/docs/resources/channel#thread-metadata-object
 */
struct discord_thread_metadata;

/* defined at specs/discord/channel.json:268:22 */
/**
 * @brief Thread Member Object
 *
 * @see https://discord.com/developers/docs/resources/channel#thread-member-object
 */
struct discord_thread_member;

/* defined at specs/discord/channel.json:280:22 */
/**
 * @brief Attachment Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#attachment-object
 */
struct discord_attachment;

/* defined at specs/discord/channel.json:301:22 */
/**
 * @brief Channel Mention Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure
 */
struct discord_channel_mention;

/* defined at specs/discord/channel.json:313:22 */
/**
 * @brief Allowed Mentions Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure
 */
struct discord_allowed_mentions;

/* defined at specs/discord/channel.json:325:22 */
/**
 * @brief Embed Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-structure
 */
struct discord_embed;

/* defined at specs/discord/channel.json:347:22 */
/**
 * @brief Embed Thumbnail Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure
 */
struct discord_embed_thumbnail;

/* defined at specs/discord/channel.json:359:22 */
/**
 * @brief Embed Video Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure
 */
struct discord_embed_video;

/* defined at specs/discord/channel.json:371:22 */
/**
 * @brief Embed Image Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure
 */
struct discord_embed_image;

/* defined at specs/discord/channel.json:383:22 */
/**
 * @brief Embed Provider Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure
 */
struct discord_embed_provider;

/* defined at specs/discord/channel.json:393:22 */
/**
 * @brief Embed Author Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure
 */
struct discord_embed_author;

/* defined at specs/discord/channel.json:405:22 */
/**
 * @brief Embed Footer Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure
 */
struct discord_embed_footer;

/* defined at specs/discord/channel.json:416:22 */
/**
 * @brief Embed Field Structure
 *
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure
 */
struct discord_embed_field;
/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/emoji.endpoints-params.json:9:22 */
/**
 * @brief Create Guild Emoji
 *
 */
struct discord_create_guild_emoji_params;

/* defined at specs/discord/emoji.endpoints-params.json:20:22 */
/**
 * @brief Modify Guild Emoji
 *
 */
struct discord_modify_guild_emoji_params;
/* This file is generated from specs/discord/emoji.json, Please don't edit it. */

/* defined at specs/discord/emoji.json:9:22 */
/**
 * @brief Emoji Structure
 *
 * @see https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
 */
struct discord_emoji;
/* This file is generated from specs/discord/gateway.json, Please don't edit it. */









/* defined at specs/discord/gateway.json:139:22 */
/**
 * @brief Identify Structure
 *
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-structure
 */
struct discord_identify;

/* defined at specs/discord/gateway.json:156:22 */
/**
 * @brief Gateway Voice State Update Structure
 *
 * @see https://discord.com/developers/docs/topics/gateway#update-voice-state-gateway-voice-state-update-structure
 */
struct discord_voice_state_status;

/* defined at specs/discord/gateway.json:169:22 */
/**
 * @brief Gateway Presence Update Structure
 *
 * @see https://discord.com/developers/docs/topics/gateway#update-presence-gateway-presence-update-structure
 */
struct discord_presence_status;

/* defined at specs/discord/gateway.json:182:22 */
/**
 * @brief Identify Connection Properties
 *
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties
 */
struct discord_identify_connection;

/* defined at specs/discord/gateway.json:193:22 */
/**
 * @brief Activity Structure
 *
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure
 */
struct discord_activity;



/* defined at specs/discord/gateway.json:224:22 */
/**
 * @brief Session Start Limit Structure
 *
 * @see https://discord.com/developers/docs/topics/gateway#session-start-limit-object-session-start-limit-structure
 */
struct discord_session_start_limit;
/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/guild-template.endpoints-params.json:9:22 */
/**
 * @brief Create Guild From Guild Template
 *
 */
struct discord_create_guild_from_guild_template_params;

/* defined at specs/discord/guild-template.endpoints-params.json:19:22 */
/**
 * @brief Create Guild Template
 *
 */
struct discord_create_guild_template_params;

/* defined at specs/discord/guild-template.endpoints-params.json:29:22 */
/**
 * @brief Modify Guild Template
 *
 */
struct discord_modify_guild_template_params;
/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */

/* defined at specs/discord/guild-template.json:9:22 */
/**
 * @brief Guild Template Structure
 *
 * @see https://discord.com/developers/docs/resources/guild-template#guild-template-object-guild-template-structure
 */
struct discord_guild_template;
/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/guild.endpoints-params.json:9:22 */
/**
 * @brief Create Guild
 *
 */
struct discord_create_guild_params;

/* defined at specs/discord/guild.endpoints-params.json:28:22 */
/**
 * @brief Modify Guild
 *
 */
struct discord_modify_guild_params;

/* defined at specs/discord/guild.endpoints-params.json:55:22 */
/**
 * @brief Create Guild Channel
 *
 */
struct discord_create_guild_channel_params;

/* defined at specs/discord/guild.endpoints-params.json:73:22 */
/**
 * @brief Modify Guild Channel Positions
 *
 */
struct discord_modify_guild_channel_positions_params;

/* defined at specs/discord/guild.endpoints-params.json:85:22 */
/**
 * @brief List Guild Members
 *
 */
struct discord_list_guild_members_params;

/* defined at specs/discord/guild.endpoints-params.json:95:22 */
/**
 * @brief Search Guild Members
 *
 */
struct discord_search_guild_members_params;

/* defined at specs/discord/guild.endpoints-params.json:105:22 */
/**
 * @brief Add Guild Member
 *
 */
struct discord_add_guild_member_params;

/* defined at specs/discord/guild.endpoints-params.json:118:22 */
/**
 * @brief Modify Guild Member
 *
 */
struct discord_modify_guild_member_params;

/* defined at specs/discord/guild.endpoints-params.json:131:22 */
/**
 * @brief Modify Current Member
 *
 */
struct discord_modify_current_member_params;

/* defined at specs/discord/guild.endpoints-params.json:140:22 */
/**
 * @brief Modify Current User Nick
 *
 */
struct discord_modify_current_user_nick_params;

/* defined at specs/discord/guild.endpoints-params.json:149:22 */
/**
 * @brief Create Guild Ban
 *
 */
struct discord_create_guild_ban_params;

/* defined at specs/discord/guild.endpoints-params.json:159:22 */
/**
 * @brief Create Guild Role
 *
 */
struct discord_create_guild_role_params;

/* defined at specs/discord/guild.endpoints-params.json:172:22 */
/**
 * @brief Modify Guild Role Positions
 *
 */
struct discord_modify_guild_role_positions_params;

/* defined at specs/discord/guild.endpoints-params.json:182:22 */
/**
 * @brief Modify Guild Role
 *
 */
struct discord_modify_guild_role_params;

/* defined at specs/discord/guild.endpoints-params.json:195:22 */
/**
 * @brief Get Guild Prune Count
 *
 */
struct discord_get_guild_prune_count_params;

/* defined at specs/discord/guild.endpoints-params.json:205:22 */
/**
 * @brief Begin Guild Prune
 *
 */
struct discord_begin_guild_prune_params;
/* This file is generated from specs/discord/guild.json, Please don't edit it. */

/* defined at specs/discord/guild.json:9:22 */
/**
 * @brief Guild Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
 */
struct discord_guild;















/* defined at specs/discord/guild.json:150:23 */
/**
 * @brief Unavailable Guild Object
 *
 * @see https://discord.com/developers/docs/resources/guild#unavailable-guild-object
 */
struct discord_unavailable_guild;

/* defined at specs/discord/guild.json:160:23 */
/**
 * @brief Guild Preview Object
 *
 * @see https://discord.com/developers/docs/resources/guild#guild-preview-object
 */
struct discord_guild_preview;

/* defined at specs/discord/guild.json:178:23 */
/**
 * @brief Guild Widget Object
 *
 * @see https://discord.com/developers/docs/resources/guild#guild-widget-object
 */
struct discord_guild_widget;

/* defined at specs/discord/guild.json:188:22 */
/**
 * @brief Guild Member Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#guild-member-object
 */
struct discord_guild_member;

/* defined at specs/discord/guild.json:205:22 */
/**
 * @brief Integration Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
 */
struct discord_integration;



/* defined at specs/discord/guild.json:239:22 */
/**
 * @brief Integration Account Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#integration-account-object-integration-account-structure
 */
struct discord_integration_account;

/* defined at specs/discord/guild.json:249:22 */
/**
 * @brief Integration Application Object
 *
 * @see https://discord.com/developers/docs/resources/guild#integration-application-object-integration-application-structure
 */
struct discord_integration_application;

/* defined at specs/discord/guild.json:262:22 */
/**
 * @brief Ban Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#ban-object
 */
struct discord_ban;

/* defined at specs/discord/guild.json:272:22 */
/**
 * @brief Welcome Screen Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-structure
 */
struct discord_welcome_screen;

/* defined at specs/discord/guild.json:283:22 */
/**
 * @brief Welcome Screen Channel Structure
 *
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure
 */
struct discord_welcome_screen_channel;
/* This file is generated from specs/discord/interaction.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/interaction.endpoints-params.json:9:22 */
/**
 * @brief Edit Original Interaction Response
 *
 */
struct discord_edit_original_interaction_response_params;

/* defined at specs/discord/interaction.endpoints-params.json:23:22 */
/**
 * @brief Create Followup Message
 *
 */
struct discord_create_followup_message_params;

/* defined at specs/discord/interaction.endpoints-params.json:44:22 */
/**
 * @brief Edit Followup Message
 *
 */
struct discord_edit_followup_message_params;
/* This file is generated from specs/discord/interaction.json, Please don't edit it. */

/* defined at specs/discord/interaction.json:9:22 */
/**
 * @brief Interaction Structure
 *
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-interaction-structure
 */
struct discord_interaction;



/* defined at specs/discord/interaction.json:40:22 */
/**
 * @brief Interaction Data Structure
 *
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-data-structure
 */
struct discord_interaction_data;

/* defined at specs/discord/interaction.json:57:22 */
/**
 * @brief Resolved Data Structure
 *
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-resolved-data-structure
 */
struct discord_resolved_data;

/* defined at specs/discord/interaction.json:71:22 */
/**
 * @brief Message Interaction Structure
 *
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#message-interaction-object-message-interaction-structure
 */
struct discord_message_interaction;

/* defined at specs/discord/interaction.json:84:22 */
/**
 * @brief Interaction Response Structure
 *
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-response-structure
 */
struct discord_interaction_response;



/* defined at specs/discord/interaction.json:109:22 */
/**
 * @brief Interaction Callback Data Structure
 *
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-structure
 */
struct discord_interaction_callback_data;


/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/invite.endpoints-params.json:9:22 */
/**
 * @brief Get Invite
 *
 */
struct discord_get_invite_params;
/* This file is generated from specs/discord/invite.json, Please don't edit it. */



/* defined at specs/discord/invite.json:19:22 */
/**
 * @brief Invite Structure
 *
 * @see https://discord.com/developers/docs/resources/invite#invite-object-invite-structure
 */
struct discord_invite;

/* defined at specs/discord/invite.json:36:22 */
/**
 * @brief Invite Metadata Structure
 *
 * @see https://discord.com/developers/docs/resources/invite#invite-metadata-object
 */
struct discord_invite_metadata;
/* This file is generated from specs/discord/message_components.json, Please don't edit it. */

/* defined at specs/discord/message_components.json:9:22 */
/**
 * @brief Component Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#component-object-component-structure
 */
struct discord_component;



/* defined at specs/discord/message_components.json:41:22 */
/**
 * @brief Button Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#button-object-button-structure
 */
struct discord_button;



/* defined at specs/discord/message_components.json:70:22 */
/**
 * @brief Select Menu Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-menu-structure
 */
struct discord_select_menu;

/* defined at specs/discord/message_components.json:85:22 */
/**
 * @brief Select Option Structure
 *
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-option-structure
 */
struct discord_select_option;
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */



/* defined at specs/discord/permissions.json:50:22 */
/**
 * @brief Role Structure
 *
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-structure
 */
struct discord_role;

/* defined at specs/discord/permissions.json:68:22 */
/**
 * @brief Role Tags Structure
 *
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-tags-structure
 */
struct discord_role_tags;
/* This file is generated from specs/discord/stage-instance.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/stage-instance.endpoints-params.json:8:22 */
/**
 * @brief Create Stage Instance
 *
 */
struct discord_create_stage_instance_params;

/* defined at specs/discord/stage-instance.endpoints-params.json:19:22 */
/**
 * @brief Modify Stage Instance
 *
 */
struct discord_modify_stage_instance_params;
/* This file is generated from specs/discord/stage-instance.json, Please don't edit it. */



/* defined at specs/discord/stage-instance.json:17:22 */
/**
 * @brief Stage Instance Structure
 *
 */
struct discord_stage_instance;
/* This file is generated from specs/discord/sticker.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/sticker.endpoints-params.json:8:22 */
/**
 * @brief List Nitro Sticker Packs
 *
 */
struct discord_list_nitro_sticker_packs_response;

/* defined at specs/discord/sticker.endpoints-params.json:17:22 */
/**
 * @brief Create Guild Sticker
 *
 */
struct discord_create_guild_sticker_params;

/* defined at specs/discord/sticker.endpoints-params.json:29:22 */
/**
 * @brief Modify Guild Sticker
 *
 */
struct discord_modify_guild_sticker_params;
/* This file is generated from specs/discord/sticker.json, Please don't edit it. */





/* defined at specs/discord/sticker.json:28:22 */
/**
 * @brief Sticker Structure
 *
 */
struct discord_sticker;

/* defined at specs/discord/sticker.json:47:22 */
/**
 * @brief Sticker Item Structure
 *
 */
struct discord_sticker_item;

/* defined at specs/discord/sticker.json:57:22 */
/**
 * @brief Sticker Pack Structure
 *
 */
struct discord_sticker_pack;
/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/user.endpoints-params.json:9:22 */
/**
 * @brief Modify Current User
 *
 */
struct discord_modify_current_user_params;

/* defined at specs/discord/user.endpoints-params.json:19:22 */
/**
 * @brief Create DM
 *
 */
struct discord_create_dm_params;

/* defined at specs/discord/user.endpoints-params.json:28:22 */
/**
 * @brief Create Group DM
 *
 */
struct discord_create_group_dm_params;
/* This file is generated from specs/discord/user.json, Please don't edit it. */





/* defined at specs/discord/user.json:41:28 */
/**
 * @brief User Structure
 *
 */
struct discord_user;



/* defined at specs/discord/user.json:74:28 */
/**
 * @brief Connection Structure
 *
 * @see https://discord.com/developers/docs/resources/user#connection-object-connection-structure
 */
struct discord_connection;
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */






/* This file is generated from specs/discord/voice.json, Please don't edit it. */

/* defined at specs/discord/voice.json:10:22 */
/**
 * @brief Voice State Structure
 *
 * @see https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure
 */
struct discord_voice_state;

/* defined at specs/discord/voice.json:31:22 */
/**
 * @brief Voice Region Structure
 *
 * @see https://discord.com/developers/docs/resources/voice#voice-region-object-voice-region-structure
 */
struct discord_voice_region;
/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/webhook.endpoints-params.json:9:22 */
/**
 * @brief Create Webhook
 *
 */
struct discord_create_webhook_params;

/* defined at specs/discord/webhook.endpoints-params.json:19:22 */
/**
 * @brief Modify Webhook
 *
 */
struct discord_modify_webhook_params;

/* defined at specs/discord/webhook.endpoints-params.json:30:22 */
/**
 * @brief Modify Webhook with Token
 *
 */
struct discord_modify_webhook_with_token_params;

/* defined at specs/discord/webhook.endpoints-params.json:40:22 */
/**
 * @brief Execute Webhook
 *
 */
struct discord_execute_webhook_params;

/* defined at specs/discord/webhook.endpoints-params.json:59:22 */
/**
 * @brief Edit Webhook Message
 *
 */
struct discord_edit_webhook_message_params;
/* This file is generated from specs/discord/webhook.json, Please don't edit it. */

/* defined at specs/discord/webhook.json:9:22 */
/**
 * @brief Webhook Structure
 *
 * @see https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
 */
struct discord_webhook;


/* This file is generated from specs/discord/application.json, Please don't edit it. */


/* Application Flags */
/* defined at specs/discord/application.json:28:5 */
/**
 * @see https://discord.com/developers/docs/resources/application#application-object-application-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_application_flags_print(enum discord_application_flags code)`
 *   * :code:`enum discord_application_flags discord_application_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_application_flags {
  DISCORD_APPLICATION_GATEWAY_PRESENCE = 4096, /**< 1 << 12 */
  DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED = 8192, /**< 1 << 13 */
  DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS = 16384, /**< 1 << 14 */
  DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED = 32768, /**< 1 << 15 */
  DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT = 65536, /**< 1 << 16 */
  DISCORD_APPLICATION_EMBEDDED = 131072, /**< 1 << 17 */
};
extern char* discord_application_flags_print(enum discord_application_flags);
extern enum discord_application_flags discord_application_flags_eval(char*);
extern void discord_application_flags_list_free_v(void **p);
extern void discord_application_flags_list_free(enum discord_application_flags **p);
extern void discord_application_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_flags_list_from_json(char *str, size_t len, enum discord_application_flags ***p);
extern size_t discord_application_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_flags_list_to_json(char *str, size_t len, enum discord_application_flags **p);
/* This file is generated from specs/discord/application_commands.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/application_commands.json, Please don't edit it. */


/* Application Command Types */
/* defined at specs/discord/application_commands.json:22:5 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_application_command_types_print(enum discord_application_command_types code)`
 *   * :code:`enum discord_application_command_types discord_application_command_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_application_command_types {
  DISCORD_APPLICATION_COMMAND_CHAT_INPUT = 1, /**< Slash commands; a text-based command that shows up when a user types / */
  DISCORD_APPLICATION_COMMAND_USER = 2, /**< A UI-based command that shows up when you right click or tap on a user */
  DISCORD_APPLICATION_COMMAND_MESSAGE = 3, /**< A UI-based command that shows up when you right lick or tap on a message */
};
extern char* discord_application_command_types_print(enum discord_application_command_types);
extern enum discord_application_command_types discord_application_command_types_eval(char*);
extern void discord_application_command_types_list_free_v(void **p);
extern void discord_application_command_types_list_free(enum discord_application_command_types **p);
extern void discord_application_command_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_types_list_from_json(char *str, size_t len, enum discord_application_command_types ***p);
extern size_t discord_application_command_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_types_list_to_json(char *str, size_t len, enum discord_application_command_types **p);


/* Application Command Option Type */
/* defined at specs/discord/application_commands.json:49:5 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-type
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_application_command_option_types_print(enum discord_application_command_option_types code)`
 *   * :code:`enum discord_application_command_option_types discord_application_command_option_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_application_command_option_types {
  DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND = 1,
  DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND_GROUP = 2,
  DISCORD_APPLICATION_COMMAND_OPTION_STRING = 3,
  DISCORD_APPLICATION_COMMAND_OPTION_INTEGER = 4, /**< Any integer between -2^53 and 2^53 */
  DISCORD_APPLICATION_COMMAND_OPTION_BOOLEAN = 5,
  DISCORD_APPLICATION_COMMAND_OPTION_USER = 6,
  DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL = 7, /**< Includes all channel types + categories */
  DISCORD_APPLICATION_COMMAND_OPTION_ROLE = 8,
  DISCORD_APPLICATION_COMMAND_OPTION_MENTIONABLE = 9, /**< Includes users and roles */
  DISCORD_APPLICATION_COMMAND_OPTION_NUMBER = 10, /**< Any double between -2^53 and 2^53 */
};
extern char* discord_application_command_option_types_print(enum discord_application_command_option_types);
extern enum discord_application_command_option_types discord_application_command_option_types_eval(char*);
extern void discord_application_command_option_types_list_free_v(void **p);
extern void discord_application_command_option_types_list_free(enum discord_application_command_option_types **p);
extern void discord_application_command_option_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_option_types_list_from_json(char *str, size_t len, enum discord_application_command_option_types ***p);
extern size_t discord_application_command_option_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_option_types_list_to_json(char *str, size_t len, enum discord_application_command_option_types **p);


/* Application Command Permission Type */
/* defined at specs/discord/application_commands.json:104:5 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-application-command-permission-type
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_application_command_permission_types_print(enum discord_application_command_permission_types code)`
 *   * :code:`enum discord_application_command_permission_types discord_application_command_permission_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_application_command_permission_types {
  DISCORD_APPLICATION_COMMAND_PERMISSION_ROLE = 1,
  DISCORD_APPLICATION_COMMAND_PERMISSION_USER = 2,
};
extern char* discord_application_command_permission_types_print(enum discord_application_command_permission_types);
extern enum discord_application_command_permission_types discord_application_command_permission_types_eval(char*);
extern void discord_application_command_permission_types_list_free_v(void **p);
extern void discord_application_command_permission_types_list_free(enum discord_application_command_permission_types **p);
extern void discord_application_command_permission_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_permission_types_list_from_json(char *str, size_t len, enum discord_application_command_permission_types ***p);
extern size_t discord_application_command_permission_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_permission_types_list_to_json(char *str, size_t len, enum discord_application_command_permission_types **p);
/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */


/* Audit Log Events */
/* defined at specs/discord/audit_log.json:35:5 */
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-events
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_audit_log_events_print(enum discord_audit_log_events code)`
 *   * :code:`enum discord_audit_log_events discord_audit_log_events_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_audit_log_events {
  DISCORD_AUDIT_LOG_GUILD_UPDATE = 1,
  DISCORD_AUDIT_LOG_CHANNEL_CREATE = 10,
  DISCORD_AUDIT_LOG_CHANNEL_UPDATE = 11,
  DISCORD_AUDIT_LOG_CHANNEL_DELETE = 12,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_CREATE = 13,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_UPDATE = 14,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_DELETE = 15,
  DISCORD_AUDIT_LOG_MEMBER_KICK = 20,
  DISCORD_AUDIT_LOG_MEMBER_PRUNE = 21,
  DISCORD_AUDIT_LOG_MEMBER_BAN_ADD = 22,
  DISCORD_AUDIT_LOG_MEMBER_BAN_REMOVE = 23,
  DISCORD_AUDIT_LOG_MEMBER_UPDATE = 24,
  DISCORD_AUDIT_LOG_MEMBER_ROLE_UPDATE = 25,
  DISCORD_AUDIT_LOG_MEMBER_MOVE = 26,
  DISCORD_AUDIT_LOG_MEMBER_DISCONNECT = 27,
  DISCORD_AUDIT_LOG_BOT_ADD = 28,
  DISCORD_AUDIT_LOG_ROLE_CREATE = 30,
  DISCORD_AUDIT_LOG_ROLE_UPDATE = 31,
  DISCORD_AUDIT_LOG_ROLE_DELETE = 32,
  DISCORD_AUDIT_LOG_INVITE_CREATE = 40,
  DISCORD_AUDIT_LOG_INVITE_DELETE = 42,
  DISCORD_AUDIT_LOG_WEBHOOK_CREATE = 50,
  DISCORD_AUDIT_LOG_WEBHOOK_UPDATE = 51,
  DISCORD_AUDIT_LOG_WEBHOOK_DELETE = 52,
  DISCORD_AUDIT_LOG_EMOJI_CREATE = 60,
  DISCORD_AUDIT_LOG_EMOJI_UPDATE = 61,
  DISCORD_AUDIT_LOG_EMOJI_DELETE = 62,
  DISCORD_AUDIT_LOG_MESSAGE_DELETE = 72,
  DISCORD_AUDIT_LOG_MESSAGE_BULK_DELETE = 73,
  DISCORD_AUDIT_LOG_MESSAGE_PIN = 74,
  DISCORD_AUDIT_LOG_MESSAGE_UNPIN = 75,
  DISCORD_AUDIT_LOG_INTEGRATION_CREATE = 80,
  DISCORD_AUDIT_LOG_INTEGRATION_UPDATE = 81,
  DISCORD_AUDIT_LOG_INTEGRATION_DELETE = 82,
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_CREATE = 83,
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_UPDATE = 84,
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_DELETE = 85,
  DISCORD_AUDIT_LOG_STICKER_CREATE = 90,
  DISCORD_AUDIT_LOG_STICKER_UPDATE = 91,
  DISCORD_AUDIT_LOG_STICKER_DELETE = 92,
  DISCORD_AUDIT_LOG_THREAD_CREATE = 110,
  DISCORD_AUDIT_LOG_THREAD_UPDATE = 111,
  DISCORD_AUDIT_LOG_THREAD_DELETE = 112,
};
extern char* discord_audit_log_events_print(enum discord_audit_log_events);
extern enum discord_audit_log_events discord_audit_log_events_eval(char*);
extern void discord_audit_log_events_list_free_v(void **p);
extern void discord_audit_log_events_list_free(enum discord_audit_log_events **p);
extern void discord_audit_log_events_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_events_list_from_json(char *str, size_t len, enum discord_audit_log_events ***p);
extern size_t discord_audit_log_events_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_events_list_to_json(char *str, size_t len, enum discord_audit_log_events **p);
/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/channel.json, Please don't edit it. */


/* Channel Types */
/* defined at specs/discord/channel.json:6:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#channel-object-channel-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_channel_types_print(enum discord_channel_types code)`
 *   * :code:`enum discord_channel_types discord_channel_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_channel_types {
  DISCORD_CHANNEL_GUILD_TEXT = 0,
  DISCORD_CHANNEL_DM = 1,
  DISCORD_CHANNEL_GUILD_VOICE = 2,
  DISCORD_CHANNEL_GROUP_DM = 3,
  DISCORD_CHANNEL_GUILD_CATEGORY = 4,
  DISCORD_CHANNEL_GUILD_NEWS = 5,
  DISCORD_CHANNEL_GUILD_STORE = 6,
  DISCORD_CHANNEL_GUILD_NEWS_THREAD = 10,
  DISCORD_CHANNEL_GUILD_PUBLIC_THREAD = 11,
  DISCORD_CHANNEL_GUILD_PRIVATE_THREAD = 12,
  DISCORD_CHANNEL_GUILD_STAGE_VOICE = 13,
};
extern char* discord_channel_types_print(enum discord_channel_types);
extern enum discord_channel_types discord_channel_types_eval(char*);
extern void discord_channel_types_list_free_v(void **p);
extern void discord_channel_types_list_free(enum discord_channel_types **p);
extern void discord_channel_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_types_list_from_json(char *str, size_t len, enum discord_channel_types ***p);
extern size_t discord_channel_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_types_list_to_json(char *str, size_t len, enum discord_channel_types **p);


/* Message Sticker Format Types */
/* defined at specs/discord/channel.json:64:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-sticker-format-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_message_sticker_format_types_print(enum discord_message_sticker_format_types code)`
 *   * :code:`enum discord_message_sticker_format_types discord_message_sticker_format_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_message_sticker_format_types {
  DISCORD_MESSAGE_STICKER_PNG = 1,
  DISCORD_MESSAGE_STICKER_APNG = 2,
  DISCORD_MESSAGE_STICKER_LOTTIE = 3,
};
extern char* discord_message_sticker_format_types_print(enum discord_message_sticker_format_types);
extern enum discord_message_sticker_format_types discord_message_sticker_format_types_eval(char*);
extern void discord_message_sticker_format_types_list_free_v(void **p);
extern void discord_message_sticker_format_types_list_free(enum discord_message_sticker_format_types **p);
extern void discord_message_sticker_format_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_sticker_format_types_list_from_json(char *str, size_t len, enum discord_message_sticker_format_types ***p);
extern size_t discord_message_sticker_format_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_sticker_format_types_list_to_json(char *str, size_t len, enum discord_message_sticker_format_types **p);


/* Message Flags */
/* defined at specs/discord/channel.json:93:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_message_flags_print(enum discord_message_flags code)`
 *   * :code:`enum discord_message_flags discord_message_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_message_flags {
  DISCORD_MESSAGE_CROSSPOSTED = 1, /**< 1<<0 */
  DISCORD_MESSAGE_IS_CROSSPOST = 2, /**< 1<<1 */
  DISCORD_MESSAGE_SUPRESS_EMBEDS = 4, /**< 1<<2 */
  DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED = 8, /**< 1<<3 */
  DISCORD_MESSAGE_URGENT = 16, /**< 1<<4 */
};
extern char* discord_message_flags_print(enum discord_message_flags);
extern enum discord_message_flags discord_message_flags_eval(char*);
extern void discord_message_flags_list_free_v(void **p);
extern void discord_message_flags_list_free(enum discord_message_flags **p);
extern void discord_message_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_flags_list_from_json(char *str, size_t len, enum discord_message_flags ***p);
extern size_t discord_message_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_flags_list_to_json(char *str, size_t len, enum discord_message_flags **p);


/* Message Activity Types */
/* defined at specs/discord/channel.json:131:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-activity-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_message_activity_types_print(enum discord_message_activity_types code)`
 *   * :code:`enum discord_message_activity_types discord_message_activity_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_message_activity_types {
  DISCORD_MESSAGE_ACTIVITY_JOIN = 1,
  DISCORD_MESSAGE_ACTIVITY_SPECTATE = 2,
  DISCORD_MESSAGE_ACTIVITY_LISTEN = 3,
  DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST = 5,
};
extern char* discord_message_activity_types_print(enum discord_message_activity_types);
extern enum discord_message_activity_types discord_message_activity_types_eval(char*);
extern void discord_message_activity_types_list_free_v(void **p);
extern void discord_message_activity_types_list_free(enum discord_message_activity_types **p);
extern void discord_message_activity_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_activity_types_list_from_json(char *str, size_t len, enum discord_message_activity_types ***p);
extern size_t discord_message_activity_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_activity_types_list_to_json(char *str, size_t len, enum discord_message_activity_types **p);


/* Message Types */
/* defined at specs/discord/channel.json:154:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_message_types_print(enum discord_message_types code)`
 *   * :code:`enum discord_message_types discord_message_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_message_types {
  DISCORD_MESSAGE_DEFAULT = 0,
  DISCORD_MESSAGE_RECIPIENT_ADD = 1,
  DISCORD_MESSAGE_RECIPIENT_REMOVE = 2,
  DISCORD_MESSAGE_CALL = 3,
  DISCORD_MESSAGE_CHANNEL_NAME_CHANGE = 4,
  DISCORD_MESSAGE_CHANNEL_ICON_CHANGE = 5,
  DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE = 6,
  DISCORD_MESSAGE_GUILD_MEMBER_JOIN = 7,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION = 8,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
  DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD = 12,
  DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED = 14,
  DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED = 15,
  DISCORD_MESSAGE_REPLY = 19,
  DISCORD_MESSAGE_APPLICATION_COMMAND = 20,
};
extern char* discord_message_types_print(enum discord_message_types);
extern enum discord_message_types discord_message_types_eval(char*);
extern void discord_message_types_list_free_v(void **p);
extern void discord_message_types_list_free(enum discord_message_types **p);
extern void discord_message_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_types_list_from_json(char *str, size_t len, enum discord_message_types ***p);
extern size_t discord_message_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_types_list_to_json(char *str, size_t len, enum discord_message_types **p);
/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/emoji.json, Please don't edit it. */
/* This file is generated from specs/discord/gateway.json, Please don't edit it. */


/* Gateway Close Event Codes */
/* defined at specs/discord/gateway.json:6:5 */
/**
 * @see https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-close-event-codes
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_close_opcodes_print(enum discord_gateway_close_opcodes code)`
 *   * :code:`enum discord_gateway_close_opcodes discord_gateway_close_opcodes_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_close_opcodes {
  DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR = 4000,
  DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE = 4001,
  DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR = 4002,
  DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED = 4003,
  DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE = 4007,
  DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED = 4008,
  DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT = 4009,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD = 4010,
  DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED = 4011,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION = 4012,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS = 4013,
  DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS = 4014,
};
extern char* discord_gateway_close_opcodes_print(enum discord_gateway_close_opcodes);
extern enum discord_gateway_close_opcodes discord_gateway_close_opcodes_eval(char*);
extern void discord_gateway_close_opcodes_list_free_v(void **p);
extern void discord_gateway_close_opcodes_list_free(enum discord_gateway_close_opcodes **p);
extern void discord_gateway_close_opcodes_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_close_opcodes_list_from_json(char *str, size_t len, enum discord_gateway_close_opcodes ***p);
extern size_t discord_gateway_close_opcodes_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_close_opcodes_list_to_json(char *str, size_t len, enum discord_gateway_close_opcodes **p);


/* Gateway Intents */
/* defined at specs/discord/gateway.json:29:5 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#gateway-intents
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_intents_print(enum discord_gateway_intents code)`
 *   * :code:`enum discord_gateway_intents discord_gateway_intents_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_intents {
  DISCORD_GATEWAY_GUILDS = 1, /**< 1 << 0 */
  DISCORD_GATEWAY_GUILD_MEMBERS = 2, /**< 1 << 1 */
  DISCORD_GATEWAY_GUILD_BANS = 4, /**< 1 << 2 */
  DISCORD_GATEWAY_GUILD_EMOJIS = 8, /**< 1 << 3 */
  DISCORD_GATEWAY_GUILD_INTEGRATIONS = 16, /**< 1 << 4 */
  DISCORD_GATEWAY_GUILD_WEBHOOKS = 32, /**< 1 << 5 */
  DISCORD_GATEWAY_GUILD_INVITES = 64, /**< 1 << 6 */
  DISCORD_GATEWAY_GUILD_VOICE_STATES = 128, /**< 1 << 7 */
  DISCORD_GATEWAY_GUILD_PRESENCES = 256, /**< 1 << 8 */
  DISCORD_GATEWAY_GUILD_MESSAGES = 512, /**< 1 << 9 */
  DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS = 1024, /**< 1 << 10 */
  DISCORD_GATEWAY_GUILD_MESSAGE_TYPING = 2048, /**< 1 << 11 */
  DISCORD_GATEWAY_DIRECT_MESSAGES = 4096, /**< 1 << 12 */
  DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS = 8192, /**< 1 << 13 */
  DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING = 16384, /**< 1 << 14 */
};
extern char* discord_gateway_intents_print(enum discord_gateway_intents);
extern enum discord_gateway_intents discord_gateway_intents_eval(char*);
extern void discord_gateway_intents_list_free_v(void **p);
extern void discord_gateway_intents_list_free(enum discord_gateway_intents **p);
extern void discord_gateway_intents_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_intents_list_from_json(char *str, size_t len, enum discord_gateway_intents ***p);
extern size_t discord_gateway_intents_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_intents_list_to_json(char *str, size_t len, enum discord_gateway_intents **p);


/* Gateway Opcodes */
/* defined at specs/discord/gateway.json:53:5 */
/**
 * @see https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_opcodes_print(enum discord_gateway_opcodes code)`
 *   * :code:`enum discord_gateway_opcodes discord_gateway_opcodes_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_opcodes {
  DISCORD_GATEWAY_DISPATCH = 0,
  DISCORD_GATEWAY_HEARTBEAT = 1,
  DISCORD_GATEWAY_IDENTIFY = 2,
  DISCORD_GATEWAY_PRESENCE_UPDATE = 3,
  DISCORD_GATEWAY_VOICE_STATE_UPDATE = 4,
  DISCORD_GATEWAY_RESUME = 6,
  DISCORD_GATEWAY_RECONNECT = 7,
  DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS = 8,
  DISCORD_GATEWAY_INVALID_SESSION = 9,
  DISCORD_GATEWAY_HELLO = 10,
  DISCORD_GATEWAY_HEARTBEAT_ACK = 11,
};
extern char* discord_gateway_opcodes_print(enum discord_gateway_opcodes);
extern enum discord_gateway_opcodes discord_gateway_opcodes_eval(char*);
extern void discord_gateway_opcodes_list_free_v(void **p);
extern void discord_gateway_opcodes_list_free(enum discord_gateway_opcodes **p);
extern void discord_gateway_opcodes_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_opcodes_list_from_json(char *str, size_t len, enum discord_gateway_opcodes ***p);
extern size_t discord_gateway_opcodes_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_opcodes_list_to_json(char *str, size_t len, enum discord_gateway_opcodes **p);


/* Gateway Events */
/* defined at specs/discord/gateway.json:73:5 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#commands-and-events-gateway-events
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_gateway_events_print(enum discord_gateway_events code)`
 *   * :code:`enum discord_gateway_events discord_gateway_events_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_gateway_events {
  DISCORD_GATEWAY_EVENTS_NONE = 0,
  DISCORD_GATEWAY_EVENTS_READY = 1,
  DISCORD_GATEWAY_EVENTS_RESUMED = 2,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_CREATE = 3,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_UPDATE = 4,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_DELETE = 5,
  DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE = 6,
  DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE = 7,
  DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE = 8,
  DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE = 9,
  DISCORD_GATEWAY_EVENTS_THREAD_CREATE = 10,
  DISCORD_GATEWAY_EVENTS_THREAD_UPDATE = 11,
  DISCORD_GATEWAY_EVENTS_THREAD_DELETE = 12,
  DISCORD_GATEWAY_EVENTS_THREAD_LIST_SYNC = 13,
  DISCORD_GATEWAY_EVENTS_THREAD_MEMBER_UPDATE = 14,
  DISCORD_GATEWAY_EVENTS_THREAD_MEMBERS_UPDATE = 15,
  DISCORD_GATEWAY_EVENTS_GUILD_CREATE = 16,
  DISCORD_GATEWAY_EVENTS_GUILD_UPDATE = 17,
  DISCORD_GATEWAY_EVENTS_GUILD_DELETE = 18,
  DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD = 19,
  DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE = 20,
  DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE = 21,
  DISCORD_GATEWAY_EVENTS_GUILD_STICKERS_UPDATE = 22,
  DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE = 23,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD = 24,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE = 25,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE = 26,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBERS_CHUNK = 27,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE = 28,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE = 29,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE = 30,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_CREATE = 31,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_UPDATE = 32,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_DELETE = 33,
  DISCORD_GATEWAY_EVENTS_INTERACTION_CREATE = 34,
  DISCORD_GATEWAY_EVENTS_INVITE_CREATE = 35,
  DISCORD_GATEWAY_EVENTS_INVITE_DELETE = 36,
  DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE = 37,
  DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE = 38,
  DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE = 39,
  DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK = 40,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD = 41,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE = 42,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL = 43,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI = 44,
  DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE = 45,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_CREATE = 46,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_DELETE = 47,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_UPDATE = 48,
  DISCORD_GATEWAY_EVENTS_TYPING_START = 49,
  DISCORD_GATEWAY_EVENTS_USER_UPDATE = 50,
  DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE = 51,
  DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE = 52,
  DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE = 53,
};
extern char* discord_gateway_events_print(enum discord_gateway_events);
extern enum discord_gateway_events discord_gateway_events_eval(char*);
extern void discord_gateway_events_list_free_v(void **p);
extern void discord_gateway_events_list_free(enum discord_gateway_events **p);
extern void discord_gateway_events_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_events_list_from_json(char *str, size_t len, enum discord_gateway_events ***p);
extern size_t discord_gateway_events_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_events_list_to_json(char *str, size_t len, enum discord_gateway_events **p);


/* Activity Types */
/* defined at specs/discord/gateway.json:206:5 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_activity_types_print(enum discord_activity_types code)`
 *   * :code:`enum discord_activity_types discord_activity_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_activity_types {
  DISCORD_ACTIVITY_GAME = 0,
  DISCORD_ACTIVITY_STREAMING = 1,
  DISCORD_ACTIVITY_LISTENING = 2,
  DISCORD_ACTIVITY_CUSTOM = 4,
  DISCORD_ACTIVITY_COMPETING = 5,
};
extern char* discord_activity_types_print(enum discord_activity_types);
extern enum discord_activity_types discord_activity_types_eval(char*);
extern void discord_activity_types_list_free_v(void **p);
extern void discord_activity_types_list_free(enum discord_activity_types **p);
extern void discord_activity_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_activity_types_list_from_json(char *str, size_t len, enum discord_activity_types ***p);
extern size_t discord_activity_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_activity_types_list_to_json(char *str, size_t len, enum discord_activity_types **p);
/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */
/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/guild.json, Please don't edit it. */


/* Default Message Notification Level */
/* defined at specs/discord/guild.json:64:5 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-default-message-notification-level
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_default_message_notification_level_print(enum discord_default_message_notification_level code)`
 *   * :code:`enum discord_default_message_notification_level discord_default_message_notification_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_default_message_notification_level {
  DISCORD_ALL_MESSAGES = 0,
  DISCORD_ONLY_MENTIONS = 1,
};
extern char* discord_default_message_notification_level_print(enum discord_default_message_notification_level);
extern enum discord_default_message_notification_level discord_default_message_notification_level_eval(char*);
extern void discord_default_message_notification_level_list_free_v(void **p);
extern void discord_default_message_notification_level_list_free(enum discord_default_message_notification_level **p);
extern void discord_default_message_notification_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_default_message_notification_level_list_from_json(char *str, size_t len, enum discord_default_message_notification_level ***p);
extern size_t discord_default_message_notification_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_default_message_notification_level_list_to_json(char *str, size_t len, enum discord_default_message_notification_level **p);


/* Explicit Content Filter Level */
/* defined at specs/discord/guild.json:73:5 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-explicit-content-filter-level
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_explicit_content_filter_level_print(enum discord_explicit_content_filter_level code)`
 *   * :code:`enum discord_explicit_content_filter_level discord_explicit_content_filter_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_explicit_content_filter_level {
  DISCORD_DISABLED = 0,
  DISCORD_MEMBERS_WITHOUT_ROLES = 1,
  DISCORD_ALL_MEMBERS = 2,
};
extern char* discord_explicit_content_filter_level_print(enum discord_explicit_content_filter_level);
extern enum discord_explicit_content_filter_level discord_explicit_content_filter_level_eval(char*);
extern void discord_explicit_content_filter_level_list_free_v(void **p);
extern void discord_explicit_content_filter_level_list_free(enum discord_explicit_content_filter_level **p);
extern void discord_explicit_content_filter_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_explicit_content_filter_level_list_from_json(char *str, size_t len, enum discord_explicit_content_filter_level ***p);
extern size_t discord_explicit_content_filter_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_explicit_content_filter_level_list_to_json(char *str, size_t len, enum discord_explicit_content_filter_level **p);


/* MFA Level */
/* defined at specs/discord/guild.json:83:5 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-mfa-level
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_mfa_level_print(enum discord_mfa_level code)`
 *   * :code:`enum discord_mfa_level discord_mfa_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_mfa_level {
  DISCORD_DISCORD_MFA_NONE = 0,
  DISCORD_ELEVATED = 1,
};
extern char* discord_mfa_level_print(enum discord_mfa_level);
extern enum discord_mfa_level discord_mfa_level_eval(char*);
extern void discord_mfa_level_list_free_v(void **p);
extern void discord_mfa_level_list_free(enum discord_mfa_level **p);
extern void discord_mfa_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_mfa_level_list_from_json(char *str, size_t len, enum discord_mfa_level ***p);
extern size_t discord_mfa_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_mfa_level_list_to_json(char *str, size_t len, enum discord_mfa_level **p);


/* Verification Level */
/* defined at specs/discord/guild.json:92:5 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-verification-level
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_verification_level_print(enum discord_verification_level code)`
 *   * :code:`enum discord_verification_level discord_verification_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_verification_level {
  DISCORD_DISCORD_VL_NONE = 0,
  DISCORD_LOW = 1,
  DISCORD_MEDIUM = 2,
  DISCORD_HIGH = 3,
  DISCORD_VERY_HIGH = 4,
};
extern char* discord_verification_level_print(enum discord_verification_level);
extern enum discord_verification_level discord_verification_level_eval(char*);
extern void discord_verification_level_list_free_v(void **p);
extern void discord_verification_level_list_free(enum discord_verification_level **p);
extern void discord_verification_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_verification_level_list_from_json(char *str, size_t len, enum discord_verification_level ***p);
extern size_t discord_verification_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_verification_level_list_to_json(char *str, size_t len, enum discord_verification_level **p);


/* Premium Tier */
/* defined at specs/discord/guild.json:104:5 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-premium-tier
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_premium_tier_print(enum discord_premium_tier code)`
 *   * :code:`enum discord_premium_tier discord_premium_tier_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_premium_tier {
  DISCORD_DISCORD_PREMIUM_NONE = 0,
  DISCORD_TIER_1 = 1,
  DISCORD_TIER_2 = 2,
  DISCORD_TIER_3 = 3,
};
extern char* discord_premium_tier_print(enum discord_premium_tier);
extern enum discord_premium_tier discord_premium_tier_eval(char*);
extern void discord_premium_tier_list_free_v(void **p);
extern void discord_premium_tier_list_free(enum discord_premium_tier **p);
extern void discord_premium_tier_list_from_json_v(char *str, size_t len, void *p);
extern void discord_premium_tier_list_from_json(char *str, size_t len, enum discord_premium_tier ***p);
extern size_t discord_premium_tier_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_premium_tier_list_to_json(char *str, size_t len, enum discord_premium_tier **p);


/* System Channel Flags */
/* defined at specs/discord/guild.json:115:5 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-system-channel-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_system_channel_flags_print(enum discord_system_channel_flags code)`
 *   * :code:`enum discord_system_channel_flags discord_system_channel_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_system_channel_flags {
  DISCORD_SUPRESS_JOIN_NOTIFICATIONS = 1, /**< 1<<0 */
  DISCORD_SUPRESS_PREMIUM_SUBSCRIPTIONS = 2, /**< 1<<1 */
};
extern char* discord_system_channel_flags_print(enum discord_system_channel_flags);
extern enum discord_system_channel_flags discord_system_channel_flags_eval(char*);
extern void discord_system_channel_flags_list_free_v(void **p);
extern void discord_system_channel_flags_list_free(enum discord_system_channel_flags **p);
extern void discord_system_channel_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_system_channel_flags_list_from_json(char *str, size_t len, enum discord_system_channel_flags ***p);
extern size_t discord_system_channel_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_system_channel_flags_list_to_json(char *str, size_t len, enum discord_system_channel_flags **p);


/* Guild Features */
/* defined at specs/discord/guild.json:124:5 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-guild-features
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_features_print(enum discord_guild_features code)`
 *   * :code:`enum discord_guild_features discord_guild_features_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_features {
  DISCORD_GUILD_INVITE_SPLASH = 0,
  DISCORD_GUILD_VIP_REGIONS = 1,
  DISCORD_GUILD_VANITY_URL = 2,
  DISCORD_GUILD_VERIFIED = 3,
  DISCORD_GUILD_PARTNERED = 4,
  DISCORD_GUILD_COMMUNITY = 5,
  DISCORD_GUILD_COMMERCE = 6,
  DISCORD_GUILD_NEWS = 7,
  DISCORD_GUILD_DISCOVERABLE = 8,
  DISCORD_GUILD_FEATURABLE = 9,
  DISCORD_GUILD_ANIMATED_ICON = 10,
  DISCORD_GUILD_BANNER = 11,
  DISCORD_GUILD_WELCOME_SCREEN_ENABLED = 12,
  DISCORD_GUILD_MEMBER_VERIFICATION_GATE_ENABLED = 13,
  DISCORD_GUILD_PREVIEW_ENABLED = 14,
};
extern char* discord_guild_features_print(enum discord_guild_features);
extern enum discord_guild_features discord_guild_features_eval(char*);
extern void discord_guild_features_list_free_v(void **p);
extern void discord_guild_features_list_free(enum discord_guild_features **p);
extern void discord_guild_features_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_features_list_from_json(char *str, size_t len, enum discord_guild_features ***p);
extern size_t discord_guild_features_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_features_list_to_json(char *str, size_t len, enum discord_guild_features **p);


/* Integration Expire Behaviors */
/* defined at specs/discord/guild.json:225:5 */
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-object-integration-expire-behaviors
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_integration_expire_behaviors_print(enum discord_integration_expire_behaviors code)`
 *   * :code:`enum discord_integration_expire_behaviors discord_integration_expire_behaviors_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_integration_expire_behaviors {
  DISCORD_INTEGRATION_REMOVE_ROLE = 0,
  DISCORD_INTEGRATION_KICK = 1,
};
extern char* discord_integration_expire_behaviors_print(enum discord_integration_expire_behaviors);
extern enum discord_integration_expire_behaviors discord_integration_expire_behaviors_eval(char*);
extern void discord_integration_expire_behaviors_list_free_v(void **p);
extern void discord_integration_expire_behaviors_list_free(enum discord_integration_expire_behaviors **p);
extern void discord_integration_expire_behaviors_list_from_json_v(char *str, size_t len, void *p);
extern void discord_integration_expire_behaviors_list_from_json(char *str, size_t len, enum discord_integration_expire_behaviors ***p);
extern size_t discord_integration_expire_behaviors_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_integration_expire_behaviors_list_to_json(char *str, size_t len, enum discord_integration_expire_behaviors **p);
/* This file is generated from specs/discord/interaction.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/interaction.json, Please don't edit it. */


/* Interaction Type */
/* defined at specs/discord/interaction.json:24:5 */
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-type
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_interaction_types_print(enum discord_interaction_types code)`
 *   * :code:`enum discord_interaction_types discord_interaction_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_interaction_types {
  DISCORD_INTERACTION_PING = 1,
  DISCORD_INTERACTION_APPLICATION_COMMAND = 2,
  DISCORD_INTERACTION_MESSAGE_COMPONENT = 3,
};
extern char* discord_interaction_types_print(enum discord_interaction_types);
extern enum discord_interaction_types discord_interaction_types_eval(char*);
extern void discord_interaction_types_list_free_v(void **p);
extern void discord_interaction_types_list_free(enum discord_interaction_types **p);
extern void discord_interaction_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_types_list_from_json(char *str, size_t len, enum discord_interaction_types ***p);
extern size_t discord_interaction_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_types_list_to_json(char *str, size_t len, enum discord_interaction_types **p);


/* Interaction Callback Type */
/* defined at specs/discord/interaction.json:91:5 */
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-type
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_interaction_callback_types_print(enum discord_interaction_callback_types code)`
 *   * :code:`enum discord_interaction_callback_types discord_interaction_callback_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_interaction_callback_types {
  DISCORD_INTERACTION_CALLBACK_PONG = 1, /**< ACK a Ping */
  DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE = 4, /**< respond to a interaction with a message */
  DISCORD_INTERACTION_CALLBACK_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE = 5, /**< ACK an interaction and edit a response later, the user sees a loading state */
  DISCORD_INTERACTION_CALLBACK_DEFERRED_UPDATE_MESSAGE = 6, /**< for components, ACK an interaction and edit the original message later; the user does not see a loading state */
  DISCORD_INTERACTION_CALLBACK_UPDATE_MESSAGE = 7, /**< for components, edit the message the component was attached to */
};
extern char* discord_interaction_callback_types_print(enum discord_interaction_callback_types);
extern enum discord_interaction_callback_types discord_interaction_callback_types_eval(char*);
extern void discord_interaction_callback_types_list_free_v(void **p);
extern void discord_interaction_callback_types_list_free(enum discord_interaction_callback_types **p);
extern void discord_interaction_callback_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_callback_types_list_from_json(char *str, size_t len, enum discord_interaction_callback_types ***p);
extern size_t discord_interaction_callback_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_callback_types_list_to_json(char *str, size_t len, enum discord_interaction_callback_types **p);


/* Interaction Callback Data Flags */
/* defined at specs/discord/interaction.json:121:5 */
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_interaction_callback_data_flags_print(enum discord_interaction_callback_data_flags code)`
 *   * :code:`enum discord_interaction_callback_data_flags discord_interaction_callback_data_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_interaction_callback_data_flags {
  DISCORD_INTERACTION_CALLBACK_DATA_EPHEMERAL = 64, /**< only the user receiving the message can see it */
};
extern char* discord_interaction_callback_data_flags_print(enum discord_interaction_callback_data_flags);
extern enum discord_interaction_callback_data_flags discord_interaction_callback_data_flags_eval(char*);
extern void discord_interaction_callback_data_flags_list_free_v(void **p);
extern void discord_interaction_callback_data_flags_list_free(enum discord_interaction_callback_data_flags **p);
extern void discord_interaction_callback_data_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_callback_data_flags_list_from_json(char *str, size_t len, enum discord_interaction_callback_data_flags ***p);
extern size_t discord_interaction_callback_data_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_callback_data_flags_list_to_json(char *str, size_t len, enum discord_interaction_callback_data_flags **p);
/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/invite.json, Please don't edit it. */


/* Target User Types */
/* defined at specs/discord/invite.json:6:5 */
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-object-target-user-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_invite_target_user_types_print(enum discord_invite_target_user_types code)`
 *   * :code:`enum discord_invite_target_user_types discord_invite_target_user_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_invite_target_user_types {
  DISCORD_INVITE_STREAM = 1,
};
extern char* discord_invite_target_user_types_print(enum discord_invite_target_user_types);
extern enum discord_invite_target_user_types discord_invite_target_user_types_eval(char*);
extern void discord_invite_target_user_types_list_free_v(void **p);
extern void discord_invite_target_user_types_list_free(enum discord_invite_target_user_types **p);
extern void discord_invite_target_user_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_target_user_types_list_from_json(char *str, size_t len, enum discord_invite_target_user_types ***p);
extern size_t discord_invite_target_user_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_target_user_types_list_to_json(char *str, size_t len, enum discord_invite_target_user_types **p);
/* This file is generated from specs/discord/message_components.json, Please don't edit it. */


/* Component Types */
/* defined at specs/discord/message_components.json:26:5 */
/**
 * @see https://discord.com/developers/docs/interactions/message-components#component-object-component-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_component_types_print(enum discord_component_types code)`
 *   * :code:`enum discord_component_types discord_component_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_component_types {
  DISCORD_COMPONENT_ACTION_ROW = 1,
  DISCORD_COMPONENT_BUTTON = 2,
  DISCORD_COMPONENT_SELECT_MENU = 3,
};
extern char* discord_component_types_print(enum discord_component_types);
extern enum discord_component_types discord_component_types_eval(char*);
extern void discord_component_types_list_free_v(void **p);
extern void discord_component_types_list_free(enum discord_component_types **p);
extern void discord_component_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_component_types_list_from_json(char *str, size_t len, enum discord_component_types ***p);
extern size_t discord_component_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_component_types_list_to_json(char *str, size_t len, enum discord_component_types **p);


/* Button Styles */
/* defined at specs/discord/message_components.json:53:5 */
/**
 * @see https://discord.com/developers/docs/interactions/message-components#button-object-button-styles
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_button_styles_print(enum discord_button_styles code)`
 *   * :code:`enum discord_button_styles discord_button_styles_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_button_styles {
  DISCORD_BUTTON_PRIMARY = 1, /**< blurple, requires custom_id */
  DISCORD_BUTTON_SECONDARY = 2, /**< grey, requires custom_id */
  DISCORD_BUTTON_SUCCESS = 3, /**< green, requires custom_id */
  DISCORD_BUTTON_DANGER = 4, /**< red, requires custom_id */
  DISCORD_BUTTON_LINK = 5, /**< grey, requires url */
};
extern char* discord_button_styles_print(enum discord_button_styles);
extern enum discord_button_styles discord_button_styles_eval(char*);
extern void discord_button_styles_list_free_v(void **p);
extern void discord_button_styles_list_free(enum discord_button_styles **p);
extern void discord_button_styles_list_from_json_v(char *str, size_t len, void *p);
extern void discord_button_styles_list_from_json(char *str, size_t len, enum discord_button_styles ***p);
extern size_t discord_button_styles_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_button_styles_list_to_json(char *str, size_t len, enum discord_button_styles **p);
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */


/* Bitwise Permission Flags */
/* defined at specs/discord/permissions.json:6:5 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_bitwise_permission_flags_print(enum discord_bitwise_permission_flags code)`
 *   * :code:`enum discord_bitwise_permission_flags discord_bitwise_permission_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_bitwise_permission_flags {
  DISCORD_BITWISE_PERMISSION_ZERO = 0, /**< No permission bits */
  DISCORD_BITWISE_PERMISSION_CREATE_INSTANT_INVITE = 1, /**< Allows creation of instant invites  T, V */
  DISCORD_BITWISE_PERMISSION_KICK_MEMBERS = 2, /**< Allows kicking members */
  DISCORD_BITWISE_PERMISSION_BAN_MEMBERS = 4, /**< Allows banning members */
  DISCORD_BITWISE_PERMISSION_ADMINISTRATOR = 8, /**< Allows all permissions and bypasses channel permission overwrites    */
  DISCORD_BITWISE_PERMISSION_MANAGE_CHANNELS = 16, /**< Allows management and editing of channels   T, V */
  DISCORD_BITWISE_PERMISSION_MANAGE_GUILD = 32, /**< Allows management and editing of the guild   */
  DISCORD_BITWISE_PERMISSION_ADD_REACTIONS = 64, /**< Allows for the addition of reactions to messages    T */
  DISCORD_BITWISE_PERMISSION_VIEW_AUDIT_LOG = 128, /**< Allows for viewing of audit logs     */
  DISCORD_BITWISE_PERMISSION_PRIORITY_SPEAKER = 256, /**< Allows for using priority speaker in a voice channel    V */
  DISCORD_BITWISE_PERMISSION_STREAM = 512, /**< Allows the user to go live  V */
  DISCORD_BITWISE_PERMISSION_VIEW_CHANNEL = 1024, /**< Allows guild members to view a channel, which includes reading messages in text channels    T, V */
  DISCORD_BITWISE_PERMISSION_SEND_MESSAGES = 2048, /**< Allows for sending messages in a channel    T */
  DISCORD_BITWISE_PERMISSION_SEND_TTS_MESSAGES = 4096, /**< Allows for sending of /tts messages T */
  DISCORD_BITWISE_PERMISSION_MANAGE_MESSAGES = 8192, /**< Allows for deletion of other users messages T */
  DISCORD_BITWISE_PERMISSION_EMBED_LINKS = 16384, /**< Links sent by users with this permission will be auto-embedded  T */
  DISCORD_BITWISE_PERMISSION_ATTACH_FILES = 32768, /**< Allows for uploading images and files   T */
  DISCORD_BITWISE_PERMISSION_READ_MESSAGE_HISTORY = 65536, /**< Allows for reading of message history   T */
  DISCORD_BITWISE_PERMISSION_MENTION_EVERYONE = 131072, /**< Allows for using the @everyone tag to notify all users in a channel, and the @here tag to notify all online users in a channel  T */
  DISCORD_BITWISE_PERMISSION_USE_EXTERNAL_EMOJIS = 262144, /**< Allows the usage of custom emojis from other servers    T */
  DISCORD_BITWISE_PERMISSION_VIEW_GUILD_INSIGHTS = 524288, /**< Allows for viewing guild insights    */
  DISCORD_BITWISE_PERMISSION_CONNECT = 1048576, /**< Allows for joining of a voice channel   V */
  DISCORD_BITWISE_PERMISSION_SPEAK = 2097152, /**< Allows for speaking in a voice channel  V */
  DISCORD_BITWISE_PERMISSION_MUTE_MEMBERS = 4194304, /**< Allows for muting members in a voice channel    V */
  DISCORD_BITWISE_PERMISSION_DEAFEN_MEMBERS = 8388608, /**< Allows for deafening of members in a voice channel  V */
  DISCORD_BITWISE_PERMISSION_MOVE_MEMBERS = 16777216, /**< Allows for moving of members between voice channels V */
  DISCORD_BITWISE_PERMISSION_USE_VAD = 33554432, /**< Allows for using voice-activity-detection in a voice channel    V */
  DISCORD_BITWISE_PERMISSION_CHANGE_NICKNAME = 67108864, /**< Allows for modification of own nickname  */
  DISCORD_BITWISE_PERMISSION_MANAGE_NICKNAMES = 134217728, /**< Allows for modification of other users nicknames     */
  DISCORD_BITWISE_PERMISSION_MANAGE_ROLES = 268435456, /**< Allows management and editing of roles  T, V */
  DISCORD_BITWISE_PERMISSION_MANAGE_WEBHOOKS = 536870912, /**< Allows management and editing of webhooks   T, V */
  DISCORD_BITWISE_PERMISSION_MANAGE_EMOJIS = 1073741824, /**< Allows management and editing of emojis */
};
extern char* discord_bitwise_permission_flags_print(enum discord_bitwise_permission_flags);
extern enum discord_bitwise_permission_flags discord_bitwise_permission_flags_eval(char*);
extern void discord_bitwise_permission_flags_list_free_v(void **p);
extern void discord_bitwise_permission_flags_list_free(enum discord_bitwise_permission_flags **p);
extern void discord_bitwise_permission_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_bitwise_permission_flags_list_from_json(char *str, size_t len, enum discord_bitwise_permission_flags ***p);
extern size_t discord_bitwise_permission_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_bitwise_permission_flags_list_to_json(char *str, size_t len, enum discord_bitwise_permission_flags **p);
/* This file is generated from specs/discord/stage-instance.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/stage-instance.json, Please don't edit it. */


/* Privacy Level */
/* defined at specs/discord/stage-instance.json:5:5 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_stage_instance_privacy_level_print(enum discord_stage_instance_privacy_level code)`
 *   * :code:`enum discord_stage_instance_privacy_level discord_stage_instance_privacy_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_stage_instance_privacy_level {
  DISCORD_STAGE_INSTANCE_PUBLIC = 1, /**< The Stage instance is visible publicly, such as on Stage Discovery. */
  DISCORD_STAGE_INSTANCE_GUILD_ONLY = 2, /**< The Stage instance is visible to only guild members. */
};
extern char* discord_stage_instance_privacy_level_print(enum discord_stage_instance_privacy_level);
extern enum discord_stage_instance_privacy_level discord_stage_instance_privacy_level_eval(char*);
extern void discord_stage_instance_privacy_level_list_free_v(void **p);
extern void discord_stage_instance_privacy_level_list_free(enum discord_stage_instance_privacy_level **p);
extern void discord_stage_instance_privacy_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_stage_instance_privacy_level_list_from_json(char *str, size_t len, enum discord_stage_instance_privacy_level ***p);
extern size_t discord_stage_instance_privacy_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_stage_instance_privacy_level_list_to_json(char *str, size_t len, enum discord_stage_instance_privacy_level **p);
/* This file is generated from specs/discord/sticker.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/sticker.json, Please don't edit it. */


/* Sticker Types */
/* defined at specs/discord/sticker.json:5:5 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_sticker_types_print(enum discord_sticker_types code)`
 *   * :code:`enum discord_sticker_types discord_sticker_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_sticker_types {
  DISCORD_STICKER_STANDARD = 1, /**< an official sticker in a pack, part of Nitro or in a removed purchasable pack */
  DISCORD_STICKER_GUILD = 2, /**< a sticker uploaded to a Boosted guild for the guild's members */
};
extern char* discord_sticker_types_print(enum discord_sticker_types);
extern enum discord_sticker_types discord_sticker_types_eval(char*);
extern void discord_sticker_types_list_free_v(void **p);
extern void discord_sticker_types_list_free(enum discord_sticker_types **p);
extern void discord_sticker_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_types_list_from_json(char *str, size_t len, enum discord_sticker_types ***p);
extern size_t discord_sticker_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_types_list_to_json(char *str, size_t len, enum discord_sticker_types **p);


/* Sticker Format Types */
/* defined at specs/discord/sticker.json:15:5 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_sticker_format_types_print(enum discord_sticker_format_types code)`
 *   * :code:`enum discord_sticker_format_types discord_sticker_format_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_sticker_format_types {
  DISCORD_STICKER_PNG = 1,
  DISCORD_STICKER_APNG = 2,
  DISCORD_STICKER_LOTTIE = 3,
};
extern char* discord_sticker_format_types_print(enum discord_sticker_format_types);
extern enum discord_sticker_format_types discord_sticker_format_types_eval(char*);
extern void discord_sticker_format_types_list_free_v(void **p);
extern void discord_sticker_format_types_list_free(enum discord_sticker_format_types **p);
extern void discord_sticker_format_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_format_types_list_from_json(char *str, size_t len, enum discord_sticker_format_types ***p);
extern size_t discord_sticker_format_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_format_types_list_to_json(char *str, size_t len, enum discord_sticker_format_types **p);
/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/user.json, Please don't edit it. */


/* User Flags */
/* defined at specs/discord/user.json:6:7 */
/**
 * @see https://discord.com/developers/docs/resources/user#user-object-user-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_user_flags_print(enum discord_user_flags code)`
 *   * :code:`enum discord_user_flags discord_user_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_user_flags {
  DISCORD_USER_DISCORD_EMPLOYEE = 1, /**< 1 << 0 */
  DISCORD_USER_PARTNERED_SERVER_OWNER = 2, /**< 1 << 2 */
  DISCORD_USER_HYPESQUAD_EVENTS = 4, /**< 1 << 3 */
  DISCORD_USER_BUG_HUNTER_LEVEL_1 = 8, /**< 1 << 4 */
  DISCORD_USER_HOUSE_BRAVERY = 32, /**< 1 << 6 */
  DISCORD_USER_HOUSE_BRILLIANCE = 64, /**< 1 << 7 */
  DISCORD_USER_HOUSE_BALANCE = 128, /**< 1 << 8 */
  DISCORD_USER_EARLY_SUPPORTER = 256, /**< 1 << 9 */
  DISCORD_USER_TEAM_USER = 512, /**< 1 << 10 */
  DISCORD_USER_SYSTEM = 4096, /**< 1 << 12 */
  DISCORD_USER_BUG_HUNTER_LEVEL_2 = 16384, /**< 1 << 14 */
  DISCORD_USER_VERIFIED_BOT = 65536, /**< 1 << 16 */
  DISCORD_USER_EARLY_VERIFIED_BOT_DEVELOPER = 131072, /**< 1 << 17 */
};
extern char* discord_user_flags_print(enum discord_user_flags);
extern enum discord_user_flags discord_user_flags_eval(char*);
extern void discord_user_flags_list_free_v(void **p);
extern void discord_user_flags_list_free(enum discord_user_flags **p);
extern void discord_user_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_user_flags_list_from_json(char *str, size_t len, enum discord_user_flags ***p);
extern size_t discord_user_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_user_flags_list_to_json(char *str, size_t len, enum discord_user_flags **p);


/* Premium Types */
/* defined at specs/discord/user.json:28:7 */
/**
 * @see https://discord.com/developers/docs/resources/user#user-object-premium-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_user_premium_types_print(enum discord_user_premium_types code)`
 *   * :code:`enum discord_user_premium_types discord_user_premium_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_user_premium_types {
  DISCORD_USER_NITRO_CLASSIC = 0,
  DISCORD_USER_NITRO = 1,
};
extern char* discord_user_premium_types_print(enum discord_user_premium_types);
extern enum discord_user_premium_types discord_user_premium_types_eval(char*);
extern void discord_user_premium_types_list_free_v(void **p);
extern void discord_user_premium_types_list_free(enum discord_user_premium_types **p);
extern void discord_user_premium_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_user_premium_types_list_from_json(char *str, size_t len, enum discord_user_premium_types ***p);
extern size_t discord_user_premium_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_user_premium_types_list_to_json(char *str, size_t len, enum discord_user_premium_types **p);


/* Visbility Types */
/* defined at specs/discord/user.json:60:7 */
/**
 * @see https://discord.com/developers/docs/resources/user#connection-object-visibility-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_visibility_types_print(enum discord_visibility_types code)`
 *   * :code:`enum discord_visibility_types discord_visibility_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_visibility_types {
  DISCORD_VISIBILITY_NONE = 0,
  DISCORD_VISIBILITY_EVERYONE = 1,
};
extern char* discord_visibility_types_print(enum discord_visibility_types);
extern enum discord_visibility_types discord_visibility_types_eval(char*);
extern void discord_visibility_types_list_free_v(void **p);
extern void discord_visibility_types_list_free(enum discord_visibility_types **p);
extern void discord_visibility_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_visibility_types_list_from_json(char *str, size_t len, enum discord_visibility_types ***p);
extern size_t discord_visibility_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_visibility_types_list_to_json(char *str, size_t len, enum discord_visibility_types **p);
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */


/* Voice Close Event Codes */
/* defined at specs/discord/voice-connections.json:6:5 */
/**
 * @see https://discord.com/developers/docs/topics/opcodes-and-status-codes#voice-voice-close-event-codes
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_voice_close_event_codes_print(enum discord_voice_close_event_codes code)`
 *   * :code:`enum discord_voice_close_event_codes discord_voice_close_event_codes_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_voice_close_event_codes {
  DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_OPCODE = 4001,
  DISCORD_VOICE_CLOSE_EVENT_DECODE_ERROR = 4002,
  DISCORD_VOICE_CLOSE_EVENT_NOT_AUTHENTICATED = 4003,
  DISCORD_VOICE_CLOSE_EVENT_AUTHENTICATION_FAILED = 4004,
  DISCORD_VOICE_CLOSE_EVENT_ALREADY_AUTHENTICATED = 4005,
  DISCORD_VOICE_CLOSE_EVENT_INVALID_SESSION = 4006,
  DISCORD_VOICE_CLOSE_EVENT_SESSION_TIMED_OUT = 4009,
  DISCORD_VOICE_CLOSE_EVENT_SERVER_NOT_FOUND = 4011,
  DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_PROTOCOL = 4012,
  DISCORD_VOICE_CLOSE_EVENT_DISCONNECTED = 4014,
  DISCORD_VOICE_CLOSE_EVENT_SERVER_CRASH = 4015,
  DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_ENCRYPTION_MODE = 4016,
};
extern char* discord_voice_close_event_codes_print(enum discord_voice_close_event_codes);
extern enum discord_voice_close_event_codes discord_voice_close_event_codes_eval(char*);
extern void discord_voice_close_event_codes_list_free_v(void **p);
extern void discord_voice_close_event_codes_list_free(enum discord_voice_close_event_codes **p);
extern void discord_voice_close_event_codes_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_close_event_codes_list_from_json(char *str, size_t len, enum discord_voice_close_event_codes ***p);
extern size_t discord_voice_close_event_codes_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_close_event_codes_list_to_json(char *str, size_t len, enum discord_voice_close_event_codes **p);


/* Voice Opcodes */
/* defined at specs/discord/voice-connections.json:27:5 */
/**
 * @see https://discord.com/developers/docs/topics/opcodes-and-status-codes#voice-voice-opcodes
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_voice_opcodes_print(enum discord_voice_opcodes code)`
 *   * :code:`enum discord_voice_opcodes discord_voice_opcodes_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_voice_opcodes {
  DISCORD_VOICE_IDENTIFY = 0,
  DISCORD_VOICE_SELECT_PROTOCOL = 1,
  DISCORD_VOICE_READY = 2,
  DISCORD_VOICE_HEARTBEAT = 3,
  DISCORD_VOICE_SESSION_DESCRIPTION = 4,
  DISCORD_VOICE_SPEAKING = 5,
  DISCORD_VOICE_HEARTBEAT_ACK = 6,
  DISCORD_VOICE_RESUME = 7,
  DISCORD_VOICE_HELLO = 8,
  DISCORD_VOICE_RESUMED = 9,
  DISCORD_VOICE_CLIENT_DISCONNECT = 13,
  DISCORD_VOICE_CODEC = 14,
};
extern char* discord_voice_opcodes_print(enum discord_voice_opcodes);
extern enum discord_voice_opcodes discord_voice_opcodes_eval(char*);
extern void discord_voice_opcodes_list_free_v(void **p);
extern void discord_voice_opcodes_list_free(enum discord_voice_opcodes **p);
extern void discord_voice_opcodes_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_opcodes_list_from_json(char *str, size_t len, enum discord_voice_opcodes ***p);
extern size_t discord_voice_opcodes_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_opcodes_list_to_json(char *str, size_t len, enum discord_voice_opcodes **p);


/* Voice Speaking Flags */
/* defined at specs/discord/voice-connections.json:48:5 */
/**
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_voice_speaking_flags_print(enum discord_voice_speaking_flags code)`
 *   * :code:`enum discord_voice_speaking_flags discord_voice_speaking_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_voice_speaking_flags {
  DISCORD_VOICE_MICROPHONE = 1, /**< 1 << 0 */
  DISCORD_VOICE_SOUNDSHARE = 2, /**< 1 << 1 */
  DISCORD_VOICE_PRIORITY = 4, /**< 1 << 2 */
};
extern char* discord_voice_speaking_flags_print(enum discord_voice_speaking_flags);
extern enum discord_voice_speaking_flags discord_voice_speaking_flags_eval(char*);
extern void discord_voice_speaking_flags_list_free_v(void **p);
extern void discord_voice_speaking_flags_list_free(enum discord_voice_speaking_flags **p);
extern void discord_voice_speaking_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_speaking_flags_list_from_json(char *str, size_t len, enum discord_voice_speaking_flags ***p);
extern size_t discord_voice_speaking_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_speaking_flags_list_to_json(char *str, size_t len, enum discord_voice_speaking_flags **p);
/* This file is generated from specs/discord/voice.json, Please don't edit it. */
/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/discord/webhook.json, Please don't edit it. */


/* Webhook Types */
/* defined at specs/discord/webhook.json:26:5 */
/**
 * @see https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_webhook_types_print(enum discord_webhook_types code)`
 *   * :code:`enum discord_webhook_types discord_webhook_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_webhook_types {
  DISCORD_WEBHOOK_INCOMING = 1, /**< Incoming Webhooks can post messages to channels with a generated token */
  DISCORD_WEBHOOK_CHANNEL_FOLLOWER = 2, /**< Channel Follower Webhooks are internal webhooks used with Channel Following to post new messages int channels */
  DISCORD_WEBHOOK_APPLICATION = 3, /**< Application webhooks are webhooks used with interactions */
};
extern char* discord_webhook_types_print(enum discord_webhook_types);
extern enum discord_webhook_types discord_webhook_types_eval(char*);
extern void discord_webhook_types_list_free_v(void **p);
extern void discord_webhook_types_list_free(enum discord_webhook_types **p);
extern void discord_webhook_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_webhook_types_list_from_json(char *str, size_t len, enum discord_webhook_types ***p);
extern size_t discord_webhook_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_webhook_types_list_to_json(char *str, size_t len, enum discord_webhook_types **p);
/* This file is generated from specs/discord/application.json, Please don't edit it. */

/* Application Structure */
/* defined at specs/discord/application.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/application#application-object-application-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_init(struct discord_application *)`
 *   * Cleanup:

 *     * :code:`void discord_application_cleanup(struct discord_application *)`
 *     * :code:`void discord_application_list_free(struct discord_application **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_from_json(char *rbuf, size_t len, struct discord_application **)`
 *     * :code:`void discord_application_list_from_json(char *rbuf, size_t len, struct discord_application ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_to_json(char *wbuf, size_t len, struct discord_application *)`
 *     * :code:`void discord_application_list_to_json(char *wbuf, size_t len, struct discord_application **)`
 * @endverbatim
 */
struct discord_application {
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */
  u64_snowflake_t id; /**< the id of the app */

  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */
  char *name; /**< the name of the app */

  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */
  char *icon; /**< the icon hash of the app */

  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */
  char *description; /**< the description of the app */

  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */
  ja_str **rpc_origins; /**< an array of rpc origin urls, if rpc is enabled */

  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */
  bool bot_public; /**< when false only app owner can join the app's bot to guilds */

  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */
  bool bot_require_code_grant; /**< when true the app's bot will only join upon completion of the full oauth2 code grant flow */

  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */
  char *term_of_service_url; /**< the url of the app's terms of service */

  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */
  char *privacy_policy_url; /**< the url of the app's privacy policy */

  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */
  /* @todo team if the application belongs to a team, this will be a list of the members of that team; */

  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */
  u64_snowflake_t guild_id; /**< if this application is a game sold on Discord, this field will be the guild on which it has been linked */

  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */
  u64_snowflake_t primary_sku_id; /**< if this application is a game sold on Discord, this field will be the id of the "Game SKU" that is created, if exists */

  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */
  char *slug; /**< if this application is a game sold on Discord, this field will be the URL slug that links to the store page */

  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */
  enum discord_application_flags flags; /**< the application's public flags */

};


/* This file is generated from specs/discord/application_commands.endpoints-params.json, Please don't edit it. */

/* Create Global Application Command */
/* defined at specs/discord/application_commands.endpoints-params.json:10:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#create-global-application-command
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_global_application_command_params_init(struct discord_create_global_application_command_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_global_application_command_params_cleanup(struct discord_create_global_application_command_params *)`
 *     * :code:`void discord_create_global_application_command_params_list_free(struct discord_create_global_application_command_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_global_application_command_params_from_json(char *rbuf, size_t len, struct discord_create_global_application_command_params **)`
 *     * :code:`void discord_create_global_application_command_params_list_from_json(char *rbuf, size_t len, struct discord_create_global_application_command_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_global_application_command_params_to_json(char *wbuf, size_t len, struct discord_create_global_application_command_params *)`
 *     * :code:`void discord_create_global_application_command_params_list_to_json(char *wbuf, size_t len, struct discord_create_global_application_command_params **)`
 * @endverbatim
 */
struct discord_create_global_application_command_params {
  /* specs/discord/application_commands.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
  char *name; /**< 1-32 lowercase character name */

  /* specs/discord/application_commands.endpoints-params.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
  char *description; /**< 1-100 character description */

  /* specs/discord/application_commands.endpoints-params.json:15:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  struct discord_application_command_option **options; /**< the parameters for the command */

  /* specs/discord/application_commands.endpoints-params.json:16:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  bool default_permission; /**< whether the command is enabled by default when the app is added to a guild */

  /* specs/discord/application_commands.endpoints-params.json:17:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
  enum discord_application_command_types type;

};

/* Edit Global Application Command */
/* defined at specs/discord/application_commands.endpoints-params.json:24:23 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-global-application-command
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_global_application_command_params_init(struct discord_edit_global_application_command_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_global_application_command_params_cleanup(struct discord_edit_global_application_command_params *)`
 *     * :code:`void discord_edit_global_application_command_params_list_free(struct discord_edit_global_application_command_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_global_application_command_params_from_json(char *rbuf, size_t len, struct discord_edit_global_application_command_params **)`
 *     * :code:`void discord_edit_global_application_command_params_list_from_json(char *rbuf, size_t len, struct discord_edit_global_application_command_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_global_application_command_params_to_json(char *wbuf, size_t len, struct discord_edit_global_application_command_params *)`
 *     * :code:`void discord_edit_global_application_command_params_list_to_json(char *wbuf, size_t len, struct discord_edit_global_application_command_params **)`
 * @endverbatim
 */
struct discord_edit_global_application_command_params {
  /* specs/discord/application_commands.endpoints-params.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
  char *name; /**< 1-32 lowercase character name */

  /* specs/discord/application_commands.endpoints-params.json:28:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
  char *description; /**< 1-100 character description */

  /* specs/discord/application_commands.endpoints-params.json:29:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  struct discord_application_command_option **options; /**< the parameters for the command */

  /* specs/discord/application_commands.endpoints-params.json:30:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  bool default_permission; /**< whether the command is enabled by default when the app is added to a guild */

};

/* Create Guild Application Command */
/* defined at specs/discord/application_commands.endpoints-params.json:37:23 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#create-guild-application-command
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_application_command_params_init(struct discord_create_guild_application_command_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_application_command_params_cleanup(struct discord_create_guild_application_command_params *)`
 *     * :code:`void discord_create_guild_application_command_params_list_free(struct discord_create_guild_application_command_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_application_command_params_from_json(char *rbuf, size_t len, struct discord_create_guild_application_command_params **)`
 *     * :code:`void discord_create_guild_application_command_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_application_command_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_application_command_params_to_json(char *wbuf, size_t len, struct discord_create_guild_application_command_params *)`
 *     * :code:`void discord_create_guild_application_command_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_application_command_params **)`
 * @endverbatim
 */
struct discord_create_guild_application_command_params {
  /* specs/discord/application_commands.endpoints-params.json:40:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
  char *name; /**< 1-32 lowercase character name */

  /* specs/discord/application_commands.endpoints-params.json:41:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
  char *description; /**< 1-100 character description */

  /* specs/discord/application_commands.endpoints-params.json:42:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  struct discord_application_command_option **options; /**< the parameters for the command */

  /* specs/discord/application_commands.endpoints-params.json:43:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  bool default_permission; /**< whether the command is enabled by default when the app is added to a guild */

  /* specs/discord/application_commands.endpoints-params.json:44:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
  enum discord_application_command_types type;

};

/* Edit Guild Application Command */
/* defined at specs/discord/application_commands.endpoints-params.json:51:23 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-guild-application-command
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_guild_application_command_params_init(struct discord_edit_guild_application_command_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_guild_application_command_params_cleanup(struct discord_edit_guild_application_command_params *)`
 *     * :code:`void discord_edit_guild_application_command_params_list_free(struct discord_edit_guild_application_command_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_guild_application_command_params_from_json(char *rbuf, size_t len, struct discord_edit_guild_application_command_params **)`
 *     * :code:`void discord_edit_guild_application_command_params_list_from_json(char *rbuf, size_t len, struct discord_edit_guild_application_command_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_guild_application_command_params_to_json(char *wbuf, size_t len, struct discord_edit_guild_application_command_params *)`
 *     * :code:`void discord_edit_guild_application_command_params_list_to_json(char *wbuf, size_t len, struct discord_edit_guild_application_command_params **)`
 * @endverbatim
 */
struct discord_edit_guild_application_command_params {
  /* specs/discord/application_commands.endpoints-params.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
  char *name; /**< 1-32 lowercase character name */

  /* specs/discord/application_commands.endpoints-params.json:55:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
  char *description; /**< 1-100 character description */

  /* specs/discord/application_commands.endpoints-params.json:56:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  struct discord_application_command_option **options; /**< the parameters for the command */

  /* specs/discord/application_commands.endpoints-params.json:57:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  bool default_permission; /**< whether the command is enabled by default when the app is added to a guild */

};

/* Edit Application Command Permissions */
/* defined at specs/discord/application_commands.endpoints-params.json:64:23 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-application-command-permissions
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_application_command_permissions_params_init(struct discord_edit_application_command_permissions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_application_command_permissions_params_cleanup(struct discord_edit_application_command_permissions_params *)`
 *     * :code:`void discord_edit_application_command_permissions_params_list_free(struct discord_edit_application_command_permissions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_application_command_permissions_params_from_json(char *rbuf, size_t len, struct discord_edit_application_command_permissions_params **)`
 *     * :code:`void discord_edit_application_command_permissions_params_list_from_json(char *rbuf, size_t len, struct discord_edit_application_command_permissions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_application_command_permissions_params_to_json(char *wbuf, size_t len, struct discord_edit_application_command_permissions_params *)`
 *     * :code:`void discord_edit_application_command_permissions_params_list_to_json(char *wbuf, size_t len, struct discord_edit_application_command_permissions_params **)`
 * @endverbatim
 */
struct discord_edit_application_command_permissions_params {
  /* specs/discord/application_commands.endpoints-params.json:67:20
     '{ "name": "permissions", "type":{"base": "struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  struct discord_application_command_permissions **permissions; /**< the permissions for the command in the guild */

};
/* This file is generated from specs/discord/application_commands.json, Please don't edit it. */

/* Application Command Structure */
/* defined at specs/discord/application_commands.json:9:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_init(struct discord_application_command *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_cleanup(struct discord_application_command *)`
 *     * :code:`void discord_application_command_list_free(struct discord_application_command **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_from_json(char *rbuf, size_t len, struct discord_application_command **)`
 *     * :code:`void discord_application_command_list_from_json(char *rbuf, size_t len, struct discord_application_command ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_to_json(char *wbuf, size_t len, struct discord_application_command *)`
 *     * :code:`void discord_application_command_list_to_json(char *wbuf, size_t len, struct discord_application_command **)`
 * @endverbatim
 */
struct discord_application_command {
  /* specs/discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  u64_snowflake_t id; /**< unique id of the command */

  /* specs/discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
  enum discord_application_command_types type; /**< the type of the command, defaults 1 if not set */

  /* specs/discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  u64_snowflake_t application_id; /**< unique id of the parent application */

  /* specs/discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
  u64_snowflake_t guild_id; /**< guild id of the command, if not global */

  /* specs/discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 character name"}' */
  char name[32+1]; /**< 1-32 character name */

  /* specs/discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
  char description[100+1]; /**< 1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands */

  /* specs/discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  struct discord_application_command_option **options; /**< the parameters for the command */

  /* specs/discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  bool default_permission; /**< whether the command is enabled by default when the app is added to a guild */

};



/* Application Command Option Structure */
/* defined at specs/discord/application_commands.json:38:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_option_init(struct discord_application_command_option *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_option_cleanup(struct discord_application_command_option *)`
 *     * :code:`void discord_application_command_option_list_free(struct discord_application_command_option **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_option_from_json(char *rbuf, size_t len, struct discord_application_command_option **)`
 *     * :code:`void discord_application_command_option_list_from_json(char *rbuf, size_t len, struct discord_application_command_option ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_option_to_json(char *wbuf, size_t len, struct discord_application_command_option *)`
 *     * :code:`void discord_application_command_option_list_to_json(char *wbuf, size_t len, struct discord_application_command_option **)`
 * @endverbatim
 */
struct discord_application_command_option {
  /* specs/discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  enum discord_application_command_option_types type; /**< value of application command option type */

  /* specs/discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  char name[32+1]; /**< 1-32 lowercase character */

  /* specs/discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  char description[100+1]; /**< 1-100 character description */

  /* specs/discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
  bool required; /**< if the parameter is required or optional -- default false */

  /* specs/discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  struct discord_application_command_option_choice **choices; /**< choices for string and int types for the user to pick from */

  /* specs/discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  struct discord_application_command_option **options; /**< if the option is a subcommand or subcommand group type, this nested options will be the parameters */

};



/* Application Command Option Choice Structure */
/* defined at specs/discord/application_commands.json:72:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-choice-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_option_choice_init(struct discord_application_command_option_choice *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_option_choice_cleanup(struct discord_application_command_option_choice *)`
 *     * :code:`void discord_application_command_option_choice_list_free(struct discord_application_command_option_choice **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_option_choice_from_json(char *rbuf, size_t len, struct discord_application_command_option_choice **)`
 *     * :code:`void discord_application_command_option_choice_list_from_json(char *rbuf, size_t len, struct discord_application_command_option_choice ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_option_choice_to_json(char *wbuf, size_t len, struct discord_application_command_option_choice *)`
 *     * :code:`void discord_application_command_option_choice_list_to_json(char *wbuf, size_t len, struct discord_application_command_option_choice **)`
 * @endverbatim
 */
struct discord_application_command_option_choice {
  /* specs/discord/application_commands.json:75:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
  char name[100+1]; /**< 1-100 character choice name */

  /* specs/discord/application_commands.json:76:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
  json_char_t* value; /**< value of choice, up to 100 characters if string */

};

/* Guild Application Command Permissions Structure */
/* defined at specs/discord/application_commands.json:83:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-guild-application-command-permissions-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_application_command_permissions_cleanup(struct discord_guild_application_command_permissions *)`
 *     * :code:`void discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_application_command_permissions_from_json(char *rbuf, size_t len, struct discord_guild_application_command_permissions **)`
 *     * :code:`void discord_guild_application_command_permissions_list_from_json(char *rbuf, size_t len, struct discord_guild_application_command_permissions ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_application_command_permissions_to_json(char *wbuf, size_t len, struct discord_guild_application_command_permissions *)`
 *     * :code:`void discord_guild_application_command_permissions_list_to_json(char *wbuf, size_t len, struct discord_guild_application_command_permissions **)`
 * @endverbatim
 */
struct discord_guild_application_command_permissions {
  /* specs/discord/application_commands.json:86:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  u64_snowflake_t id; /**< the id of the command */

  /* specs/discord/application_commands.json:87:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  u64_snowflake_t application_id; /**< the id of the parent application the command belongs to */

  /* specs/discord/application_commands.json:88:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  u64_snowflake_t guild_id; /**< the id of the guild */

  /* specs/discord/application_commands.json:89:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  struct discord_application_command_permissions **permissions; /**< the permissions for the command in the guild */

};

/* Application Command Permissions Structure */
/* defined at specs/discord/application_commands.json:96:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-application-command-permissions-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_permissions_init(struct discord_application_command_permissions *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_permissions_cleanup(struct discord_application_command_permissions *)`
 *     * :code:`void discord_application_command_permissions_list_free(struct discord_application_command_permissions **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_permissions_from_json(char *rbuf, size_t len, struct discord_application_command_permissions **)`
 *     * :code:`void discord_application_command_permissions_list_from_json(char *rbuf, size_t len, struct discord_application_command_permissions ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_permissions_to_json(char *wbuf, size_t len, struct discord_application_command_permissions *)`
 *     * :code:`void discord_application_command_permissions_list_to_json(char *wbuf, size_t len, struct discord_application_command_permissions **)`
 * @endverbatim
 */
struct discord_application_command_permissions {
  /* specs/discord/application_commands.json:99:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  u64_snowflake_t id; /**< the id of the command */

  /* specs/discord/application_commands.json:100:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  enum discord_application_command_permission_types type; /**< role or user */

  /* specs/discord/application_commands.json:101:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  bool permission; /**< true to allow, false, to disallow */

};



/* Application Command Interaction Data Option Structure */
/* defined at specs/discord/application_commands.json:119:22 */
/**
 * @see https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-interaction-data-option-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *)`
 *   * Cleanup:

 *     * :code:`void discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option *)`
 *     * :code:`void discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_command_interaction_data_option_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_option **)`
 *     * :code:`void discord_application_command_interaction_data_option_list_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_option ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_command_interaction_data_option_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_option *)`
 *     * :code:`void discord_application_command_interaction_data_option_list_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_option **)`
 * @endverbatim
 */
struct discord_application_command_interaction_data_option {
  /* specs/discord/application_commands.json:122:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  char *name; /**< the name of the parameter */

  /* specs/discord/application_commands.json:123:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  enum discord_application_command_option_types type; /**< value of application command option type */

  /* specs/discord/application_commands.json:124:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
  json_char_t* value; /**< the value of the pair */

  /* specs/discord/application_commands.json:125:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_option **options; /**< present if this option is a group or subcommand */

};
/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */

/* defined at specs/discord/audit_log.endpoints-params.json:7:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_guild_audit_log_params_init(struct discord_get_guild_audit_log_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_guild_audit_log_params_cleanup(struct discord_get_guild_audit_log_params *)`
 *     * :code:`void discord_get_guild_audit_log_params_list_free(struct discord_get_guild_audit_log_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_guild_audit_log_params_from_json(char *rbuf, size_t len, struct discord_get_guild_audit_log_params **)`
 *     * :code:`void discord_get_guild_audit_log_params_list_from_json(char *rbuf, size_t len, struct discord_get_guild_audit_log_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_guild_audit_log_params_to_json(char *wbuf, size_t len, struct discord_get_guild_audit_log_params *)`
 *     * :code:`void discord_get_guild_audit_log_params_list_to_json(char *wbuf, size_t len, struct discord_get_guild_audit_log_params **)`
 * @endverbatim
 */
struct discord_get_guild_audit_log_params {
  /* specs/discord/audit_log.endpoints-params.json:10:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"filter the log for actions made by a user", "inject_if_not":0 }' */
  u64_snowflake_t user_id; /**< filter the log for actions made by a user */

  /* specs/discord/audit_log.endpoints-params.json:11:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "comment":"the type of audit log event", "inject_if_not":0 }' */
  enum discord_audit_log_events action_type; /**< the type of audit log event */

  /* specs/discord/audit_log.endpoints-params.json:12:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"filter the log before a certain entry id", "inject_if_not":0 }' */
  u64_snowflake_t before; /**< filter the log before a certain entry id */

  /* specs/discord/audit_log.endpoints-params.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "default_value":50, "comment":"how many entries are returned (default 50, minimum 1, maximum 100)", "inject_if_not":0 }' */
  int limit; /**< how many entries are returned (default 50, minimum 1, maximum 100) */

};
/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */

/* Audit Log Structure */
/* defined at specs/discord/audit_log.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_audit_log_init(struct discord_audit_log *)`
 *   * Cleanup:

 *     * :code:`void discord_audit_log_cleanup(struct discord_audit_log *)`
 *     * :code:`void discord_audit_log_list_free(struct discord_audit_log **)`
 *   * JSON Decoder:

 *     * :code:`void discord_audit_log_from_json(char *rbuf, size_t len, struct discord_audit_log **)`
 *     * :code:`void discord_audit_log_list_from_json(char *rbuf, size_t len, struct discord_audit_log ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_audit_log_to_json(char *wbuf, size_t len, struct discord_audit_log *)`
 *     * :code:`void discord_audit_log_list_to_json(char *wbuf, size_t len, struct discord_audit_log **)`
 * @endverbatim
 */
struct discord_audit_log {
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
  struct discord_webhook **webhooks; /**< list of webhooks found in the audit log */

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
  struct discord_user **users; /**< list of users found in the audit log */

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
  struct discord_audit_log_entry **audit_log_entries; /**< list of audit log entries */

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
  struct discord_integration **integrations; /**< list of partial integration objects */

  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
  struct discord_channel **threads; /**< list of threads found in the audit log */

};

/* Audit Log Entry Structure */
/* defined at specs/discord/audit_log.json:23:22 */
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-entry-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_audit_log_entry_init(struct discord_audit_log_entry *)`
 *   * Cleanup:

 *     * :code:`void discord_audit_log_entry_cleanup(struct discord_audit_log_entry *)`
 *     * :code:`void discord_audit_log_entry_list_free(struct discord_audit_log_entry **)`
 *   * JSON Decoder:

 *     * :code:`void discord_audit_log_entry_from_json(char *rbuf, size_t len, struct discord_audit_log_entry **)`
 *     * :code:`void discord_audit_log_entry_list_from_json(char *rbuf, size_t len, struct discord_audit_log_entry ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_audit_log_entry_to_json(char *wbuf, size_t len, struct discord_audit_log_entry *)`
 *     * :code:`void discord_audit_log_entry_list_to_json(char *wbuf, size_t len, struct discord_audit_log_entry **)`
 * @endverbatim
 */
struct discord_audit_log_entry {
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
  char *target_id; /**< id of the affected entity (webhook,user,role,etc.) */

  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
  struct discord_audit_log_change **changes; /**< changes made to the target_id */

  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
  u64_snowflake_t user_id; /**< the user who made the changes */

  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
  u64_snowflake_t id; /**< id of the entry */

  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
  int action_type; /**< type of action that occured */

  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
  struct discord_optional_audit_entry_info **options; /**< additional info for certain action types */

  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */
  char *reason; /**< the reason for the change */

};



/* Optional Audit Entry Info Structure */
/* defined at specs/discord/audit_log.json:91:22 */
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-optional-audit-entry-info
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_optional_audit_entry_info_init(struct discord_optional_audit_entry_info *)`
 *   * Cleanup:

 *     * :code:`void discord_optional_audit_entry_info_cleanup(struct discord_optional_audit_entry_info *)`
 *     * :code:`void discord_optional_audit_entry_info_list_free(struct discord_optional_audit_entry_info **)`
 *   * JSON Decoder:

 *     * :code:`void discord_optional_audit_entry_info_from_json(char *rbuf, size_t len, struct discord_optional_audit_entry_info **)`
 *     * :code:`void discord_optional_audit_entry_info_list_from_json(char *rbuf, size_t len, struct discord_optional_audit_entry_info ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_optional_audit_entry_info_to_json(char *wbuf, size_t len, struct discord_optional_audit_entry_info *)`
 *     * :code:`void discord_optional_audit_entry_info_list_to_json(char *wbuf, size_t len, struct discord_optional_audit_entry_info **)`
 * @endverbatim
 */
struct discord_optional_audit_entry_info {
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
  char *delete_member_days; /**< number of days after which inactive members were kicked */

  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
  char *members_removed; /**< number of members removed by the prune */

  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
  u64_snowflake_t channel_id; /**< channel in which the entities were targeted */

  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
  u64_snowflake_t message_id; /**< id of the message that was targeted */

  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
  char *count; /**< number of entities that were targeted */

  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
  u64_snowflake_t id; /**< id of the ovewritten entity */

  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
  char *type; /**< type of overwritten entity - '0' for role or '1' for member */

  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
  char *role_name; /**< name of the role if type is '0' (not present if type is '1') */

};

/* Audit Log Change Structure */
/* defined at specs/discord/audit_log.json:108:22 */
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_audit_log_change_init(struct discord_audit_log_change *)`
 *   * Cleanup:

 *     * :code:`void discord_audit_log_change_cleanup(struct discord_audit_log_change *)`
 *     * :code:`void discord_audit_log_change_list_free(struct discord_audit_log_change **)`
 *   * JSON Decoder:

 *     * :code:`void discord_audit_log_change_from_json(char *rbuf, size_t len, struct discord_audit_log_change **)`
 *     * :code:`void discord_audit_log_change_list_from_json(char *rbuf, size_t len, struct discord_audit_log_change ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_audit_log_change_to_json(char *wbuf, size_t len, struct discord_audit_log_change *)`
 *     * :code:`void discord_audit_log_change_list_to_json(char *wbuf, size_t len, struct discord_audit_log_change **)`
 * @endverbatim
 */
struct discord_audit_log_change {
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */
  json_char_t* new_value; /**< new value of the key */

  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */
  json_char_t* old_value; /**< old value of the key */

  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
  char *key; /**< name of audit log change key */

};
/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */

/* Modify Channel */
/* defined at specs/discord/channel.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_channel_params_init(struct discord_modify_channel_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *)`
 *     * :code:`void discord_modify_channel_params_list_free(struct discord_modify_channel_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_channel_params_from_json(char *rbuf, size_t len, struct discord_modify_channel_params **)`
 *     * :code:`void discord_modify_channel_params_list_from_json(char *rbuf, size_t len, struct discord_modify_channel_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_channel_params_to_json(char *wbuf, size_t len, struct discord_modify_channel_params *)`
 *     * :code:`void discord_modify_channel_params_list_to_json(char *wbuf, size_t len, struct discord_modify_channel_params **)`
 * @endverbatim
 */
struct discord_modify_channel_params {
  /* specs/discord/channel.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *icon;

  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int position;

  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *topic;

  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool nsfw;

  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int rate_limit_per_user;

  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int bitrate;

  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int user_limit;

  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  struct discord_overwrite **permission_overwrites;

  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *rtc_region;

  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int video_quality_mode;

  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool archived;

  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool locked;

};

/* Create Message */
/* defined at specs/discord/channel.endpoints-params.json:33:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_message_params_init(struct discord_create_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_message_params_cleanup(struct discord_create_message_params *)`
 *     * :code:`void discord_create_message_params_list_free(struct discord_create_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_message_params_from_json(char *rbuf, size_t len, struct discord_create_message_params **)`
 *     * :code:`void discord_create_message_params_list_from_json(char *rbuf, size_t len, struct discord_create_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_message_params_to_json(char *wbuf, size_t len, struct discord_create_message_params *)`
 *     * :code:`void discord_create_message_params_list_to_json(char *wbuf, size_t len, struct discord_create_message_params **)`
 * @endverbatim
 */
struct discord_create_message_params {
  /* specs/discord/channel.endpoints-params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* specs/discord/channel.endpoints-params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  bool tts; /**< true if this is a TTS message */

  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< embedded rich content (up to 6000 characters) */

  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  struct discord_embed *embed; /**< embedded rich content, deprecated in favor of embeds */

  /* specs/discord/channel.endpoints-params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/channel.endpoints-params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
  struct discord_message_reference *message_reference; /**< include to make your message a reply */

  /* specs/discord/channel.endpoints-params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

  /* specs/discord/channel.endpoints-params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
  ja_u64 **sticker_ids; /**< ids of up to 3 stickers in the server to send in the message */

  /* specs/discord/channel.endpoints-params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attachment objects with filename and description */

};

/* Get Channel Messages */
/* defined at specs/discord/channel.endpoints-params.json:50:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_channel_messages_params_init(struct discord_get_channel_messages_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_channel_messages_params_cleanup(struct discord_get_channel_messages_params *)`
 *     * :code:`void discord_get_channel_messages_params_list_free(struct discord_get_channel_messages_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_channel_messages_params_from_json(char *rbuf, size_t len, struct discord_get_channel_messages_params **)`
 *     * :code:`void discord_get_channel_messages_params_list_from_json(char *rbuf, size_t len, struct discord_get_channel_messages_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_channel_messages_params_to_json(char *wbuf, size_t len, struct discord_get_channel_messages_params *)`
 *     * :code:`void discord_get_channel_messages_params_list_to_json(char *wbuf, size_t len, struct discord_get_channel_messages_params **)`
 * @endverbatim
 */
struct discord_get_channel_messages_params {
  /* specs/discord/channel.endpoints-params.json:53:20
     '{ "name": "around", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages around this message ID", "inject_if_not":0 }' */
  u64_snowflake_t around; /**< get messages around this message ID */

  /* specs/discord/channel.endpoints-params.json:54:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages before this message ID", "inject_if_not":0 }' */
  u64_snowflake_t before; /**< get messages before this message ID */

  /* specs/discord/channel.endpoints-params.json:55:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages after this message ID", "inject_if_not":0 }' */
  u64_snowflake_t after; /**< get messages after this message ID */

  /* specs/discord/channel.endpoints-params.json:56:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query", "default_value":50, "comment":"max number of messages to return (1-100)", "inject_if_not":0 }' */
  int limit; /**< max number of messages to return (1-100) */

};

/* Get Reactions */
/* defined at specs/discord/channel.endpoints-params.json:62:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_reactions_params_init(struct discord_get_reactions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *)`
 *     * :code:`void discord_get_reactions_params_list_free(struct discord_get_reactions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_reactions_params_from_json(char *rbuf, size_t len, struct discord_get_reactions_params **)`
 *     * :code:`void discord_get_reactions_params_list_from_json(char *rbuf, size_t len, struct discord_get_reactions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_reactions_params_to_json(char *wbuf, size_t len, struct discord_get_reactions_params *)`
 *     * :code:`void discord_get_reactions_params_list_to_json(char *wbuf, size_t len, struct discord_get_reactions_params **)`
 * @endverbatim
 */
struct discord_get_reactions_params {
  /* specs/discord/channel.endpoints-params.json:65:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  u64_snowflake_t after;

  /* specs/discord/channel.endpoints-params.json:66:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  int limit;

};

/* Edit Channel Permissions */
/* defined at specs/discord/channel.endpoints-params.json:72:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *)`
 *     * :code:`void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_channel_permissions_params_from_json(char *rbuf, size_t len, struct discord_edit_channel_permissions_params **)`
 *     * :code:`void discord_edit_channel_permissions_params_list_from_json(char *rbuf, size_t len, struct discord_edit_channel_permissions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_channel_permissions_params_to_json(char *wbuf, size_t len, struct discord_edit_channel_permissions_params *)`
 *     * :code:`void discord_edit_channel_permissions_params_list_to_json(char *wbuf, size_t len, struct discord_edit_channel_permissions_params **)`
 * @endverbatim
 */
struct discord_edit_channel_permissions_params {
  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags"}, "comment":"permission bit set" }' */
  enum discord_bitwise_permission_flags allow; /**< permission bit set */

  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags"}, "comment":"permission bit set" }' */
  enum discord_bitwise_permission_flags deny; /**< permission bit set */

  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

};

/* Edit Message */
/* defined at specs/discord/channel.endpoints-params.json:83:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_message_params_init(struct discord_edit_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_message_params_cleanup(struct discord_edit_message_params *)`
 *     * :code:`void discord_edit_message_params_list_free(struct discord_edit_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_message_params_from_json(char *rbuf, size_t len, struct discord_edit_message_params **)`
 *     * :code:`void discord_edit_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_message_params_to_json(char *wbuf, size_t len, struct discord_edit_message_params *)`
 *     * :code:`void discord_edit_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_message_params **)`
 * @endverbatim
 */
struct discord_edit_message_params {
  /* specs/discord/channel.endpoints-params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< embedded rich content (up to 6000 characters) */

  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  struct discord_embed *embed; /**< embedded rich content, deprecated in favor of embeds */

  /* specs/discord/channel.endpoints-params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
  enum discord_message_flags flags; /**< edit the flags of a message */

  /* specs/discord/channel.endpoints-params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/channel.endpoints-params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/channel.endpoints-params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};

/* Follow News Channel */
/* defined at specs/discord/channel.endpoints-params.json:98:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *)`
 *   * Cleanup:

 *     * :code:`void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *)`
 *     * :code:`void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_follow_news_channel_params_from_json(char *rbuf, size_t len, struct discord_follow_news_channel_params **)`
 *     * :code:`void discord_follow_news_channel_params_list_from_json(char *rbuf, size_t len, struct discord_follow_news_channel_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_follow_news_channel_params_to_json(char *wbuf, size_t len, struct discord_follow_news_channel_params *)`
 *     * :code:`void discord_follow_news_channel_params_list_to_json(char *wbuf, size_t len, struct discord_follow_news_channel_params **)`
 * @endverbatim
 */
struct discord_follow_news_channel_params {
  /* specs/discord/channel.endpoints-params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t webhook_channel_id;

};

/* Create Channel Invite */
/* defined at specs/discord/channel.endpoints-params.json:107:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *)`
 *     * :code:`void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_channel_invite_params_from_json(char *rbuf, size_t len, struct discord_create_channel_invite_params **)`
 *     * :code:`void discord_create_channel_invite_params_list_from_json(char *rbuf, size_t len, struct discord_create_channel_invite_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_channel_invite_params_to_json(char *wbuf, size_t len, struct discord_create_channel_invite_params *)`
 *     * :code:`void discord_create_channel_invite_params_list_to_json(char *wbuf, size_t len, struct discord_create_channel_invite_params **)`
 * @endverbatim
 */
struct discord_create_channel_invite_params {
  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  int max_age;

  /* specs/discord/channel.endpoints-params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  int max_uses;

  /* specs/discord/channel.endpoints-params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  bool temporary;

  /* specs/discord/channel.endpoints-params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  bool unique;

  /* specs/discord/channel.endpoints-params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  int target_type;

  /* specs/discord/channel.endpoints-params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_user_id;

  /* specs/discord/channel.endpoints-params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_application_id;

};

/* Group DM Add Recipient */
/* defined at specs/discord/channel.endpoints-params.json:122:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *)`
 *   * Cleanup:

 *     * :code:`void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *)`
 *     * :code:`void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_group_dm_add_recipient_params_from_json(char *rbuf, size_t len, struct discord_group_dm_add_recipient_params **)`
 *     * :code:`void discord_group_dm_add_recipient_params_list_from_json(char *rbuf, size_t len, struct discord_group_dm_add_recipient_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_group_dm_add_recipient_params_to_json(char *wbuf, size_t len, struct discord_group_dm_add_recipient_params *)`
 *     * :code:`void discord_group_dm_add_recipient_params_list_to_json(char *wbuf, size_t len, struct discord_group_dm_add_recipient_params **)`
 * @endverbatim
 */
struct discord_group_dm_add_recipient_params {
  /* specs/discord/channel.endpoints-params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  char *access_token;

  /* specs/discord/channel.endpoints-params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

};

/* Start Thread with Message */
/* defined at specs/discord/channel.endpoints-params.json:132:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params *)`
 *     * :code:`void discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_start_thread_with_message_params_from_json(char *rbuf, size_t len, struct discord_start_thread_with_message_params **)`
 *     * :code:`void discord_start_thread_with_message_params_list_from_json(char *rbuf, size_t len, struct discord_start_thread_with_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_start_thread_with_message_params_to_json(char *wbuf, size_t len, struct discord_start_thread_with_message_params *)`
 *     * :code:`void discord_start_thread_with_message_params_list_to_json(char *wbuf, size_t len, struct discord_start_thread_with_message_params **)`
 * @endverbatim
 */
struct discord_start_thread_with_message_params {
  /* specs/discord/channel.endpoints-params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

};

/* Start Thread without Message */
/* defined at specs/discord/channel.endpoints-params.json:142:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *)`
 *     * :code:`void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_start_thread_without_message_params_from_json(char *rbuf, size_t len, struct discord_start_thread_without_message_params **)`
 *     * :code:`void discord_start_thread_without_message_params_list_from_json(char *rbuf, size_t len, struct discord_start_thread_without_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_start_thread_without_message_params_to_json(char *wbuf, size_t len, struct discord_start_thread_without_message_params *)`
 *     * :code:`void discord_start_thread_without_message_params_list_to_json(char *wbuf, size_t len, struct discord_start_thread_without_message_params **)`
 * @endverbatim
 */
struct discord_start_thread_without_message_params {
  /* specs/discord/channel.endpoints-params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* specs/discord/channel.endpoints-params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  enum discord_channel_types type;

};

/* List Active Threads */
/* defined at specs/discord/channel.endpoints-params.json:153:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_thread_response_body_init(struct discord_thread_response_body *)`
 *   * Cleanup:

 *     * :code:`void discord_thread_response_body_cleanup(struct discord_thread_response_body *)`
 *     * :code:`void discord_thread_response_body_list_free(struct discord_thread_response_body **)`
 *   * JSON Decoder:

 *     * :code:`void discord_thread_response_body_from_json(char *rbuf, size_t len, struct discord_thread_response_body **)`
 *     * :code:`void discord_thread_response_body_list_from_json(char *rbuf, size_t len, struct discord_thread_response_body ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_thread_response_body_to_json(char *wbuf, size_t len, struct discord_thread_response_body *)`
 *     * :code:`void discord_thread_response_body_list_to_json(char *wbuf, size_t len, struct discord_thread_response_body **)`
 * @endverbatim
 */
struct discord_thread_response_body {
  /* specs/discord/channel.endpoints-params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  struct discord_channel **threads;

  /* specs/discord/channel.endpoints-params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  struct discord_thread_member **members;

  /* specs/discord/channel.endpoints-params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  bool has_more;

};
/* This file is generated from specs/discord/channel.json, Please don't edit it. */



/* Channel Structure */
/* defined at specs/discord/channel.json:29:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#channel-object-channel-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_channel_init(struct discord_channel *)`
 *   * Cleanup:

 *     * :code:`void discord_channel_cleanup(struct discord_channel *)`
 *     * :code:`void discord_channel_list_free(struct discord_channel **)`
 *   * JSON Decoder:

 *     * :code:`void discord_channel_from_json(char *rbuf, size_t len, struct discord_channel **)`
 *     * :code:`void discord_channel_list_from_json(char *rbuf, size_t len, struct discord_channel ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_channel_to_json(char *wbuf, size_t len, struct discord_channel *)`
 *     * :code:`void discord_channel_list_to_json(char *wbuf, size_t len, struct discord_channel **)`
 * @endverbatim
 */
struct discord_channel {
  /* specs/discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
  enum discord_channel_types type;

  /* specs/discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
  int position;

  /* specs/discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
  struct discord_overwrite **permission_overwrites;

  /* specs/discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */
  char *topic;

  /* specs/discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
  bool nsfw;

  /* specs/discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t last_message_id;

  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
  int bitrate;

  /* specs/discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
  int user_limit;

  /* specs/discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
  int rate_limit_per_user;

  /* specs/discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
  struct discord_user **recipients;

  /* specs/discord/channel.json:51:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "name":"icon",
         "option":true, "inject_if_not":""}' */
  char icon[ORCA_LIMITS_SHA256];

  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t owner_id;

  /* specs/discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t application_id;

  /* specs/discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
  u64_unix_ms_t last_pin_timestamp;

  /* specs/discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
  struct discord_message **messages;

};



/* Message Sticker Structure */
/* defined at specs/discord/channel.json:80:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_sticker_init(struct discord_message_sticker *)`
 *   * Cleanup:

 *     * :code:`void discord_message_sticker_cleanup(struct discord_message_sticker *)`
 *     * :code:`void discord_message_sticker_list_free(struct discord_message_sticker **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_sticker_from_json(char *rbuf, size_t len, struct discord_message_sticker **)`
 *     * :code:`void discord_message_sticker_list_from_json(char *rbuf, size_t len, struct discord_message_sticker ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_sticker_to_json(char *wbuf, size_t len, struct discord_message_sticker *)`
 *     * :code:`void discord_message_sticker_list_to_json(char *wbuf, size_t len, struct discord_message_sticker **)`
 * @endverbatim
 */
struct discord_message_sticker {
  /* specs/discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t pack_id;

  /* specs/discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  char *description;

  /* specs/discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
  char *tags;

  /* specs/discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */
  char asset[ORCA_LIMITS_SHA256];

  /* specs/discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "option":true, "inject_if_not":""}' */
  char preview_asset[ORCA_LIMITS_SHA256];

  /* specs/discord/channel.json:90:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
  enum discord_message_sticker_format_types type;

};



/* Message Reference Structure */
/* defined at specs/discord/channel.json:110:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-reference-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_reference_init(struct discord_message_reference *)`
 *   * Cleanup:

 *     * :code:`void discord_message_reference_cleanup(struct discord_message_reference *)`
 *     * :code:`void discord_message_reference_list_free(struct discord_message_reference **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_reference_from_json(char *rbuf, size_t len, struct discord_message_reference **)`
 *     * :code:`void discord_message_reference_list_from_json(char *rbuf, size_t len, struct discord_message_reference ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_reference_to_json(char *wbuf, size_t len, struct discord_message_reference *)`
 *     * :code:`void discord_message_reference_list_to_json(char *wbuf, size_t len, struct discord_message_reference **)`
 * @endverbatim
 */
struct discord_message_reference {
  /* specs/discord/channel.json:112:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t message_id;

  /* specs/discord/channel.json:113:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:114:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:115:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  bool fail_if_not_exists;

};

/* Message Application Structure */
/* defined at specs/discord/channel.json:122:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-application-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_application_init(struct discord_message_application *)`
 *   * Cleanup:

 *     * :code:`void discord_message_application_cleanup(struct discord_message_application *)`
 *     * :code:`void discord_message_application_list_free(struct discord_message_application **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_application_from_json(char *rbuf, size_t len, struct discord_message_application **)`
 *     * :code:`void discord_message_application_list_from_json(char *rbuf, size_t len, struct discord_message_application ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_application_to_json(char *wbuf, size_t len, struct discord_message_application *)`
 *     * :code:`void discord_message_application_list_to_json(char *wbuf, size_t len, struct discord_message_application **)`
 * @endverbatim
 */
struct discord_message_application {
  /* specs/discord/channel.json:124:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:125:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *cover_image;

  /* specs/discord/channel.json:126:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  char *description;

  /* specs/discord/channel.json:127:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *icon;

  /* specs/discord/channel.json:128:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  char *name;

};



/* Message Activity Structure */
/* defined at specs/discord/channel.json:147:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_activity_init(struct discord_message_activity *)`
 *   * Cleanup:

 *     * :code:`void discord_message_activity_cleanup(struct discord_message_activity *)`
 *     * :code:`void discord_message_activity_list_free(struct discord_message_activity **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_activity_from_json(char *rbuf, size_t len, struct discord_message_activity **)`
 *     * :code:`void discord_message_activity_list_from_json(char *rbuf, size_t len, struct discord_message_activity ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_activity_to_json(char *wbuf, size_t len, struct discord_message_activity *)`
 *     * :code:`void discord_message_activity_list_to_json(char *wbuf, size_t len, struct discord_message_activity **)`
 * @endverbatim
 */
struct discord_message_activity {
  /* specs/discord/channel.json:149:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
  enum discord_message_activity_types type;

  /* specs/discord/channel.json:150:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
  char *party_id;

};



/* Message Structure */
/* defined at specs/discord/channel.json:182:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_init(struct discord_message *)`
 *   * Cleanup:

 *     * :code:`void discord_message_cleanup(struct discord_message *)`
 *     * :code:`void discord_message_list_free(struct discord_message **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_from_json(char *rbuf, size_t len, struct discord_message **)`
 *     * :code:`void discord_message_list_from_json(char *rbuf, size_t len, struct discord_message ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_to_json(char *wbuf, size_t len, struct discord_message *)`
 *     * :code:`void discord_message_list_to_json(char *wbuf, size_t len, struct discord_message **)`
 * @endverbatim
 */
struct discord_message {
  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:186:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:187:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
  struct discord_user *author;

  /* specs/discord/channel.json:188:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
  struct discord_guild_member *member; /**< partial guild member object */

  /* specs/discord/channel.json:189:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
  char *content;

  /* specs/discord/channel.json:190:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.json:191:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
  u64_unix_ms_t edited_timestamp;

  /* specs/discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
  bool tts;

  /* specs/discord/channel.json:193:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
  bool mention_everyone;

  /* specs/discord/channel.json:194:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
  struct discord_user **mentions; /**< array of user objects, with an additional partial member field */

  /* specs/discord/channel.json:195:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
  ja_u64 **mention_roles; /**< array of role object ids */

  /* specs/discord/channel.json:196:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
  struct discord_channel_mention **mention_channels;

  /* specs/discord/channel.json:197:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */
  struct discord_attachment **attachments;

  /* specs/discord/channel.json:198:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
  struct discord_embed **embeds;

  /* specs/discord/channel.json:199:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
  struct discord_reaction **reactions;

  /* specs/discord/channel.json:200:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
  char *nonce; /**< integer or string */

  /* specs/discord/channel.json:201:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
  bool pinned;

  /* specs/discord/channel.json:202:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
  u64_snowflake_t webhook_id;

  /* specs/discord/channel.json:203:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
  enum discord_message_types type;

  /* specs/discord/channel.json:204:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
  struct discord_message_activity *activity;

  /* specs/discord/channel.json:205:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
  struct discord_message_application **application;

  /* specs/discord/channel.json:206:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
  struct discord_message_reference *message_reference;

  /* specs/discord/channel.json:207:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
  enum discord_message_flags flags;

  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
  struct discord_message *referenced_message; /**< this will cause recursive allocation if allocating as the parent */

  /* specs/discord/channel.json:209:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
  struct discord_message_interaction *interaction; /**< the message associated with the message_reference */

  /* specs/discord/channel.json:210:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
  struct discord_channel *thread; /**< the channel that was started from this message, includes thread member obejct */

  /* specs/discord/channel.json:211:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
  struct discord_component **components; /**< sent if the message contains components like buttons, actions rows, or other interactive components */

  /* specs/discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
  struct discord_message_sticker **sticker_items; /**< sent if the message contains stickets */

  /* specs/discord/channel.json:213:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
  struct discord_message_sticker **stickers; /**< [DEPRECATED] array of sticker objects */

};

/* Followed Channel Structure */
/* defined at specs/discord/channel.json:219:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_followed_channel_init(struct discord_followed_channel *)`
 *   * Cleanup:

 *     * :code:`void discord_followed_channel_cleanup(struct discord_followed_channel *)`
 *     * :code:`void discord_followed_channel_list_free(struct discord_followed_channel **)`
 *   * JSON Decoder:

 *     * :code:`void discord_followed_channel_from_json(char *rbuf, size_t len, struct discord_followed_channel **)`
 *     * :code:`void discord_followed_channel_list_from_json(char *rbuf, size_t len, struct discord_followed_channel ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_followed_channel_to_json(char *wbuf, size_t len, struct discord_followed_channel *)`
 *     * :code:`void discord_followed_channel_list_to_json(char *wbuf, size_t len, struct discord_followed_channel **)`
 * @endverbatim
 */
struct discord_followed_channel {
  /* specs/discord/channel.json:222:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:223:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t webhook_id;

};

/* Reaction Structure */
/* defined at specs/discord/channel.json:229:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_reaction_init(struct discord_reaction *)`
 *   * Cleanup:

 *     * :code:`void discord_reaction_cleanup(struct discord_reaction *)`
 *     * :code:`void discord_reaction_list_free(struct discord_reaction **)`
 *   * JSON Decoder:

 *     * :code:`void discord_reaction_from_json(char *rbuf, size_t len, struct discord_reaction **)`
 *     * :code:`void discord_reaction_list_from_json(char *rbuf, size_t len, struct discord_reaction ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_reaction_to_json(char *wbuf, size_t len, struct discord_reaction *)`
 *     * :code:`void discord_reaction_list_to_json(char *wbuf, size_t len, struct discord_reaction **)`
 * @endverbatim
 */
struct discord_reaction {
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */
  int count;

  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
  bool me;

  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
  struct discord_emoji *emoji; /**< partial emoji object */

};

/* Overwrite Structure */
/* defined at specs/discord/channel.json:239:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_overwrite_init(struct discord_overwrite *)`
 *   * Cleanup:

 *     * :code:`void discord_overwrite_cleanup(struct discord_overwrite *)`
 *     * :code:`void discord_overwrite_list_free(struct discord_overwrite **)`
 *   * JSON Decoder:

 *     * :code:`void discord_overwrite_from_json(char *rbuf, size_t len, struct discord_overwrite **)`
 *     * :code:`void discord_overwrite_list_from_json(char *rbuf, size_t len, struct discord_overwrite ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_overwrite_to_json(char *wbuf, size_t len, struct discord_overwrite *)`
 *     * :code:`void discord_overwrite_list_to_json(char *wbuf, size_t len, struct discord_overwrite **)`
 * @endverbatim
 */
struct discord_overwrite {
  /* specs/discord/channel.json:242:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:243:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/channel.json:244:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags"}, 
          "comment":"permission bit set"}' */
  enum discord_bitwise_permission_flags allow; /**< permission bit set */

  /* specs/discord/channel.json:246:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags"}, 
          "comment":"permission bit set"}' */
  enum discord_bitwise_permission_flags deny; /**< permission bit set */

};

/* Thread Metadata Object */
/* defined at specs/discord/channel.json:254:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#thread-metadata-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_thread_metadata_init(struct discord_thread_metadata *)`
 *   * Cleanup:

 *     * :code:`void discord_thread_metadata_cleanup(struct discord_thread_metadata *)`
 *     * :code:`void discord_thread_metadata_list_free(struct discord_thread_metadata **)`
 *   * JSON Decoder:

 *     * :code:`void discord_thread_metadata_from_json(char *rbuf, size_t len, struct discord_thread_metadata **)`
 *     * :code:`void discord_thread_metadata_list_from_json(char *rbuf, size_t len, struct discord_thread_metadata ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_thread_metadata_to_json(char *wbuf, size_t len, struct discord_thread_metadata *)`
 *     * :code:`void discord_thread_metadata_list_to_json(char *wbuf, size_t len, struct discord_thread_metadata **)`
 * @endverbatim
 */
struct discord_thread_metadata {
  /* specs/discord/channel.json:257:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
  bool archived;

  /* specs/discord/channel.json:258:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t archiver_id;

  /* specs/discord/channel.json:259:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
  int auto_archive_duration;

  /* specs/discord/channel.json:260:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t archive_timestamp;

  /* specs/discord/channel.json:261:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
  bool locked;

};

/* Thread Member Object */
/* defined at specs/discord/channel.json:268:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#thread-member-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_thread_member_init(struct discord_thread_member *)`
 *   * Cleanup:

 *     * :code:`void discord_thread_member_cleanup(struct discord_thread_member *)`
 *     * :code:`void discord_thread_member_list_free(struct discord_thread_member **)`
 *   * JSON Decoder:

 *     * :code:`void discord_thread_member_from_json(char *rbuf, size_t len, struct discord_thread_member **)`
 *     * :code:`void discord_thread_member_list_from_json(char *rbuf, size_t len, struct discord_thread_member ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_thread_member_to_json(char *wbuf, size_t len, struct discord_thread_member *)`
 *     * :code:`void discord_thread_member_list_to_json(char *wbuf, size_t len, struct discord_thread_member **)`
 * @endverbatim
 */
struct discord_thread_member {
  /* specs/discord/channel.json:271:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:272:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t user_id;

  /* specs/discord/channel.json:273:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t join_timestamp;

  /* specs/discord/channel.json:274:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
  int flags;

};

/* Attachment Structure */
/* defined at specs/discord/channel.json:280:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#attachment-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_attachment_init(struct discord_attachment *)`
 *   * Cleanup:

 *     * :code:`void discord_attachment_cleanup(struct discord_attachment *)`
 *     * :code:`void discord_attachment_list_free(struct discord_attachment **)`
 *   * JSON Decoder:

 *     * :code:`void discord_attachment_from_json(char *rbuf, size_t len, struct discord_attachment **)`
 *     * :code:`void discord_attachment_list_from_json(char *rbuf, size_t len, struct discord_attachment ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_attachment_to_json(char *wbuf, size_t len, struct discord_attachment *)`
 *     * :code:`void discord_attachment_list_to_json(char *wbuf, size_t len, struct discord_attachment **)`
 * @endverbatim
 */
struct discord_attachment {
  /* specs/discord/channel.json:283:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "loc":"multipart", "comment":"the file contents", "inject_if_not":null }' */
  char *content; /**< the file contents */

  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */
  int id; /**< attachment id */

  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */
  char *filename; /**< name of file attached */

  /* specs/discord/channel.json:287:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */
  char *description; /**< description for the file */

  /* specs/discord/channel.json:288:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */
  char *content_type; /**< the attachment's media type */

  /* specs/discord/channel.json:289:20
     '{ "name": "size", "type":{ "base":"int" }, "inject_if_not":0, "comment":"size of file in bytes"}' */
  int size; /**< size of file in bytes */

  /* specs/discord/channel.json:290:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */
  char *url; /**< source url of file */

  /* specs/discord/channel.json:291:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */
  char *proxy_url; /**< a proxied url of file */

  /* specs/discord/channel.json:292:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */
  int height; /**< height of file (if image) */

  /* specs/discord/channel.json:293:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */
  int width; /**< width of file (if image) */

  /* specs/discord/channel.json:294:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */
  bool ephemeral; /**< whether this attachment is ephemeral */

};

/* Channel Mention Structure */
/* defined at specs/discord/channel.json:301:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_channel_mention_init(struct discord_channel_mention *)`
 *   * Cleanup:

 *     * :code:`void discord_channel_mention_cleanup(struct discord_channel_mention *)`
 *     * :code:`void discord_channel_mention_list_free(struct discord_channel_mention **)`
 *   * JSON Decoder:

 *     * :code:`void discord_channel_mention_from_json(char *rbuf, size_t len, struct discord_channel_mention **)`
 *     * :code:`void discord_channel_mention_list_from_json(char *rbuf, size_t len, struct discord_channel_mention ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_channel_mention_to_json(char *wbuf, size_t len, struct discord_channel_mention *)`
 *     * :code:`void discord_channel_mention_list_to_json(char *wbuf, size_t len, struct discord_channel_mention **)`
 * @endverbatim
 */
struct discord_channel_mention {
  /* specs/discord/channel.json:304:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:305:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:306:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
  enum discord_channel_types type;

  /* specs/discord/channel.json:307:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

};

/* Allowed Mentions Structure */
/* defined at specs/discord/channel.json:313:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_allowed_mentions_init(struct discord_allowed_mentions *)`
 *   * Cleanup:

 *     * :code:`void discord_allowed_mentions_cleanup(struct discord_allowed_mentions *)`
 *     * :code:`void discord_allowed_mentions_list_free(struct discord_allowed_mentions **)`
 *   * JSON Decoder:

 *     * :code:`void discord_allowed_mentions_from_json(char *rbuf, size_t len, struct discord_allowed_mentions **)`
 *     * :code:`void discord_allowed_mentions_list_from_json(char *rbuf, size_t len, struct discord_allowed_mentions ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_allowed_mentions_to_json(char *wbuf, size_t len, struct discord_allowed_mentions *)`
 *     * :code:`void discord_allowed_mentions_list_to_json(char *wbuf, size_t len, struct discord_allowed_mentions **)`
 * @endverbatim
 */
struct discord_allowed_mentions {
  /* specs/discord/channel.json:316:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
  ja_str **parse;

  /* specs/discord/channel.json:317:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  ja_u64 **roles; /**< list of snowflakes */

  /* specs/discord/channel.json:318:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  ja_u64 **users; /**< list of snowflakes */

  /* specs/discord/channel.json:319:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
  bool replied_user;

};

/* Embed Structure */
/* defined at specs/discord/channel.json:325:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_init(struct discord_embed *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_cleanup(struct discord_embed *)`
 *     * :code:`void discord_embed_list_free(struct discord_embed **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_from_json(char *rbuf, size_t len, struct discord_embed **)`
 *     * :code:`void discord_embed_list_from_json(char *rbuf, size_t len, struct discord_embed ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_to_json(char *wbuf, size_t len, struct discord_embed *)`
 *     * :code:`void discord_embed_list_to_json(char *wbuf, size_t len, struct discord_embed **)`
 * @endverbatim
 */
struct discord_embed {
  /* specs/discord/channel.json:328:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  char *title;

  /* specs/discord/channel.json:329:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":""}' */
  char type[32];

  /* specs/discord/channel.json:330:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *description;

  /* specs/discord/channel.json:331:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:332:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.json:333:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
  int color;

  /* specs/discord/channel.json:334:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
  struct discord_embed_footer *footer;

  /* specs/discord/channel.json:335:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_image *image;

  /* specs/discord/channel.json:336:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_thumbnail *thumbnail;

  /* specs/discord/channel.json:337:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_video *video;

  /* specs/discord/channel.json:338:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_provider *provider;

  /* specs/discord/channel.json:339:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_author *author;

  /* specs/discord/channel.json:340:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
  struct discord_embed_field **fields;

};

/* Embed Thumbnail Structure */
/* defined at specs/discord/channel.json:347:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_thumbnail_init(struct discord_embed_thumbnail *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *)`
 *     * :code:`void discord_embed_thumbnail_list_free(struct discord_embed_thumbnail **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_thumbnail_from_json(char *rbuf, size_t len, struct discord_embed_thumbnail **)`
 *     * :code:`void discord_embed_thumbnail_list_from_json(char *rbuf, size_t len, struct discord_embed_thumbnail ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_thumbnail_to_json(char *wbuf, size_t len, struct discord_embed_thumbnail *)`
 *     * :code:`void discord_embed_thumbnail_list_to_json(char *wbuf, size_t len, struct discord_embed_thumbnail **)`
 * @endverbatim
 */
struct discord_embed_thumbnail {
  /* specs/discord/channel.json:349:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:350:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:351:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:352:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

};

/* Embed Video Structure */
/* defined at specs/discord/channel.json:359:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_video_init(struct discord_embed_video *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_video_cleanup(struct discord_embed_video *)`
 *     * :code:`void discord_embed_video_list_free(struct discord_embed_video **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_video_from_json(char *rbuf, size_t len, struct discord_embed_video **)`
 *     * :code:`void discord_embed_video_list_from_json(char *rbuf, size_t len, struct discord_embed_video ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_video_to_json(char *wbuf, size_t len, struct discord_embed_video *)`
 *     * :code:`void discord_embed_video_list_to_json(char *wbuf, size_t len, struct discord_embed_video **)`
 * @endverbatim
 */
struct discord_embed_video {
  /* specs/discord/channel.json:361:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:362:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:363:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:364:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

};

/* Embed Image Structure */
/* defined at specs/discord/channel.json:371:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_image_init(struct discord_embed_image *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_image_cleanup(struct discord_embed_image *)`
 *     * :code:`void discord_embed_image_list_free(struct discord_embed_image **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_image_from_json(char *rbuf, size_t len, struct discord_embed_image **)`
 *     * :code:`void discord_embed_image_list_from_json(char *rbuf, size_t len, struct discord_embed_image ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_image_to_json(char *wbuf, size_t len, struct discord_embed_image *)`
 *     * :code:`void discord_embed_image_list_to_json(char *wbuf, size_t len, struct discord_embed_image **)`
 * @endverbatim
 */
struct discord_embed_image {
  /* specs/discord/channel.json:373:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:374:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:375:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:376:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

};

/* Embed Provider Structure */
/* defined at specs/discord/channel.json:383:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_provider_init(struct discord_embed_provider *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_provider_cleanup(struct discord_embed_provider *)`
 *     * :code:`void discord_embed_provider_list_free(struct discord_embed_provider **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_provider_from_json(char *rbuf, size_t len, struct discord_embed_provider **)`
 *     * :code:`void discord_embed_provider_list_from_json(char *rbuf, size_t len, struct discord_embed_provider ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_provider_to_json(char *wbuf, size_t len, struct discord_embed_provider *)`
 *     * :code:`void discord_embed_provider_list_to_json(char *wbuf, size_t len, struct discord_embed_provider **)`
 * @endverbatim
 */
struct discord_embed_provider {
  /* specs/discord/channel.json:385:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:386:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *url;

};

/* Embed Author Structure */
/* defined at specs/discord/channel.json:393:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_author_init(struct discord_embed_author *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_author_cleanup(struct discord_embed_author *)`
 *     * :code:`void discord_embed_author_list_free(struct discord_embed_author **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_author_from_json(char *rbuf, size_t len, struct discord_embed_author **)`
 *     * :code:`void discord_embed_author_list_from_json(char *rbuf, size_t len, struct discord_embed_author ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_author_to_json(char *wbuf, size_t len, struct discord_embed_author *)`
 *     * :code:`void discord_embed_author_list_to_json(char *wbuf, size_t len, struct discord_embed_author **)`
 * @endverbatim
 */
struct discord_embed_author {
  /* specs/discord/channel.json:395:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:396:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:397:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *icon_url;

  /* specs/discord/channel.json:398:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_icon_url;

};

/* Embed Footer Structure */
/* defined at specs/discord/channel.json:405:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_footer_init(struct discord_embed_footer *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_footer_cleanup(struct discord_embed_footer *)`
 *     * :code:`void discord_embed_footer_list_free(struct discord_embed_footer **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_footer_from_json(char *rbuf, size_t len, struct discord_embed_footer **)`
 *     * :code:`void discord_embed_footer_list_from_json(char *rbuf, size_t len, struct discord_embed_footer ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_footer_to_json(char *wbuf, size_t len, struct discord_embed_footer *)`
 *     * :code:`void discord_embed_footer_list_to_json(char *wbuf, size_t len, struct discord_embed_footer **)`
 * @endverbatim
 */
struct discord_embed_footer {
  /* specs/discord/channel.json:407:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *text;

  /* specs/discord/channel.json:408:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  char *icon_url;

  /* specs/discord/channel.json:409:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *proxy_icon_url;

};

/* Embed Field Structure */
/* defined at specs/discord/channel.json:416:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_field_init(struct discord_embed_field *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_field_cleanup(struct discord_embed_field *)`
 *     * :code:`void discord_embed_field_list_free(struct discord_embed_field **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_field_from_json(char *rbuf, size_t len, struct discord_embed_field **)`
 *     * :code:`void discord_embed_field_list_from_json(char *rbuf, size_t len, struct discord_embed_field ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_field_to_json(char *wbuf, size_t len, struct discord_embed_field *)`
 *     * :code:`void discord_embed_field_list_to_json(char *wbuf, size_t len, struct discord_embed_field **)`
 * @endverbatim
 */
struct discord_embed_field {
  /* specs/discord/channel.json:418:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:419:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *value;

  /* specs/discord/channel.json:420:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
  bool Inline;

};
/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */

/* Create Guild Emoji */
/* defined at specs/discord/emoji.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_emoji_params_init(struct discord_create_guild_emoji_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_emoji_params_cleanup(struct discord_create_guild_emoji_params *)`
 *     * :code:`void discord_create_guild_emoji_params_list_free(struct discord_create_guild_emoji_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_emoji_params_from_json(char *rbuf, size_t len, struct discord_create_guild_emoji_params **)`
 *     * :code:`void discord_create_guild_emoji_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_emoji_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_emoji_params_to_json(char *wbuf, size_t len, struct discord_create_guild_emoji_params *)`
 *     * :code:`void discord_create_guild_emoji_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_emoji_params **)`
 * @endverbatim
 */
struct discord_create_guild_emoji_params {
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
  char *image; /**< Base64 Encoded Image Data */

  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  ja_u64 **roles; /**< roles for which this emoji will be whitelisted */

};

/* Modify Guild Emoji */
/* defined at specs/discord/emoji.endpoints-params.json:20:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_emoji_params_init(struct discord_modify_guild_emoji_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_emoji_params_cleanup(struct discord_modify_guild_emoji_params *)`
 *     * :code:`void discord_modify_guild_emoji_params_list_free(struct discord_modify_guild_emoji_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_emoji_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_emoji_params **)`
 *     * :code:`void discord_modify_guild_emoji_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_emoji_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_emoji_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_emoji_params *)`
 *     * :code:`void discord_modify_guild_emoji_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_emoji_params **)`
 * @endverbatim
 */
struct discord_modify_guild_emoji_params {
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  ja_u64 **roles; /**< roles for which this emoji will be whitelisted */

};
/* This file is generated from specs/discord/emoji.json, Please don't edit it. */

/* Emoji Structure */
/* defined at specs/discord/emoji.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_emoji_init(struct discord_emoji *)`
 *   * Cleanup:

 *     * :code:`void discord_emoji_cleanup(struct discord_emoji *)`
 *     * :code:`void discord_emoji_list_free(struct discord_emoji **)`
 *   * JSON Decoder:

 *     * :code:`void discord_emoji_from_json(char *rbuf, size_t len, struct discord_emoji **)`
 *     * :code:`void discord_emoji_list_from_json(char *rbuf, size_t len, struct discord_emoji ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_emoji_to_json(char *wbuf, size_t len, struct discord_emoji *)`
 *     * :code:`void discord_emoji_list_to_json(char *wbuf, size_t len, struct discord_emoji **)`
 * @endverbatim
 */
struct discord_emoji {
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */
  u64_snowflake_t id; /**< emoji id */

  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */
  char *name; /**< emoji name */

  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */
  struct discord_role **roles; /**< roles allowed to use this emoji */

  /* specs/discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */
  struct discord_user *user; /**< user that created this emoji */

  /* specs/discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */
  bool require_colons; /**< whether this emoji must be wrapped in colons */

  /* specs/discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */
  bool managed; /**< whether this emoji is managed */

  /* specs/discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */
  bool animated; /**< whether this emoji is animated */

  /* specs/discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */
  bool available;

};
/* This file is generated from specs/discord/gateway.json, Please don't edit it. */









/* Identify Structure */
/* defined at specs/discord/gateway.json:139:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_identify_init(struct discord_identify *)`
 *   * Cleanup:

 *     * :code:`void discord_identify_cleanup(struct discord_identify *)`
 *     * :code:`void discord_identify_list_free(struct discord_identify **)`
 *   * JSON Decoder:

 *     * :code:`void discord_identify_from_json(char *rbuf, size_t len, struct discord_identify **)`
 *     * :code:`void discord_identify_list_from_json(char *rbuf, size_t len, struct discord_identify ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_identify_to_json(char *wbuf, size_t len, struct discord_identify *)`
 *     * :code:`void discord_identify_list_to_json(char *wbuf, size_t len, struct discord_identify **)`
 * @endverbatim
 */
struct discord_identify {
  /* specs/discord/gateway.json:142:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
  char *token;

  /* specs/discord/gateway.json:143:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */
  struct discord_identify_connection *properties;

  /* specs/discord/gateway.json:144:19
     '{ "name":"compress","type":{"base":"bool"}}' */
  bool compress;

  /* specs/discord/gateway.json:145:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
  int large_threshold;

  /* specs/discord/gateway.json:146:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
  bool guild_subscriptions;

  /* specs/discord/gateway.json:147:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  /* @todo shard (null); */

  /* specs/discord/gateway.json:148:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */
  struct discord_presence_status *presence;

  /* specs/discord/gateway.json:149:19
     '{ "name":"intents","type":{"base":"int"}}' */
  int intents;

};

/* Gateway Voice State Update Structure */
/* defined at specs/discord/gateway.json:156:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#update-voice-state-gateway-voice-state-update-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_voice_state_status_init(struct discord_voice_state_status *)`
 *   * Cleanup:

 *     * :code:`void discord_voice_state_status_cleanup(struct discord_voice_state_status *)`
 *     * :code:`void discord_voice_state_status_list_free(struct discord_voice_state_status **)`
 *   * JSON Decoder:

 *     * :code:`void discord_voice_state_status_from_json(char *rbuf, size_t len, struct discord_voice_state_status **)`
 *     * :code:`void discord_voice_state_status_list_from_json(char *rbuf, size_t len, struct discord_voice_state_status ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_voice_state_status_to_json(char *wbuf, size_t len, struct discord_voice_state_status *)`
 *     * :code:`void discord_voice_state_status_list_to_json(char *wbuf, size_t len, struct discord_voice_state_status **)`
 * @endverbatim
 */
struct discord_voice_state_status {
  /* specs/discord/gateway.json:159:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */
  u64_snowflake_t guild_id; /**< id of the guild */

  /* specs/discord/gateway.json:160:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */
  u64_snowflake_t channel_id; /**< id of the voice channel client wants to join (null if disconnecting) */

  /* specs/discord/gateway.json:161:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */
  bool self_mute; /**< is the client muted */

  /* specs/discord/gateway.json:162:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */
  bool self_deaf; /**< is the client deafened */

};

/* Gateway Presence Update Structure */
/* defined at specs/discord/gateway.json:169:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#update-presence-gateway-presence-update-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_presence_status_init(struct discord_presence_status *)`
 *   * Cleanup:

 *     * :code:`void discord_presence_status_cleanup(struct discord_presence_status *)`
 *     * :code:`void discord_presence_status_list_free(struct discord_presence_status **)`
 *   * JSON Decoder:

 *     * :code:`void discord_presence_status_from_json(char *rbuf, size_t len, struct discord_presence_status **)`
 *     * :code:`void discord_presence_status_list_from_json(char *rbuf, size_t len, struct discord_presence_status ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_presence_status_to_json(char *wbuf, size_t len, struct discord_presence_status *)`
 *     * :code:`void discord_presence_status_list_to_json(char *wbuf, size_t len, struct discord_presence_status **)`
 * @endverbatim
 */
struct discord_presence_status {
  /* specs/discord/gateway.json:172:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */
  u64_unix_ms_t since; /**< unix time (in milliseconds) of when the client went idle, or null if the client is not idle */

  /* specs/discord/gateway.json:173:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */
  struct discord_activity **activities; /**< the user's activities */

  /* specs/discord/gateway.json:174:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}, "comment":"the user's new status", "inject_if_not":"" }' */
  char status[16]; /**< the user's new status */

  /* specs/discord/gateway.json:175:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */
  bool afk; /**< whether or not the client is afk */

};

/* Identify Connection Properties */
/* defined at specs/discord/gateway.json:182:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_identify_connection_init(struct discord_identify_connection *)`
 *   * Cleanup:

 *     * :code:`void discord_identify_connection_cleanup(struct discord_identify_connection *)`
 *     * :code:`void discord_identify_connection_list_free(struct discord_identify_connection **)`
 *   * JSON Decoder:

 *     * :code:`void discord_identify_connection_from_json(char *rbuf, size_t len, struct discord_identify_connection **)`
 *     * :code:`void discord_identify_connection_list_from_json(char *rbuf, size_t len, struct discord_identify_connection ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_identify_connection_to_json(char *wbuf, size_t len, struct discord_identify_connection *)`
 *     * :code:`void discord_identify_connection_list_to_json(char *wbuf, size_t len, struct discord_identify_connection **)`
 * @endverbatim
 */
struct discord_identify_connection {
  /* specs/discord/gateway.json:185:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */
  char *os; /**< your operating system */

  /* specs/discord/gateway.json:186:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
  char *browser; /**< your library name */

  /* specs/discord/gateway.json:187:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
  char *device; /**< your library name */

};

/* Activity Structure */
/* defined at specs/discord/gateway.json:193:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_activity_init(struct discord_activity *)`
 *   * Cleanup:

 *     * :code:`void discord_activity_cleanup(struct discord_activity *)`
 *     * :code:`void discord_activity_list_free(struct discord_activity **)`
 *   * JSON Decoder:

 *     * :code:`void discord_activity_from_json(char *rbuf, size_t len, struct discord_activity **)`
 *     * :code:`void discord_activity_list_from_json(char *rbuf, size_t len, struct discord_activity ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_activity_to_json(char *wbuf, size_t len, struct discord_activity *)`
 *     * :code:`void discord_activity_list_to_json(char *wbuf, size_t len, struct discord_activity **)`
 * @endverbatim
 */
struct discord_activity {
  /* specs/discord/gateway.json:196:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}' */
  char name[512];

  /* specs/discord/gateway.json:197:19
     '{ "name":"type","type":{"base":"int"}}' */
  int type;

  /* specs/discord/gateway.json:198:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */
  char *url;

  /* specs/discord/gateway.json:199:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */
  u64_unix_ms_t created_at;

  /* specs/discord/gateway.json:200:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t application_id;

  /* specs/discord/gateway.json:201:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *details;

  /* specs/discord/gateway.json:202:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *state;

  /* specs/discord/gateway.json:203:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  bool instance;

};



/* Session Start Limit Structure */
/* defined at specs/discord/gateway.json:224:22 */
/**
 * @see https://discord.com/developers/docs/topics/gateway#session-start-limit-object-session-start-limit-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_session_start_limit_init(struct discord_session_start_limit *)`
 *   * Cleanup:

 *     * :code:`void discord_session_start_limit_cleanup(struct discord_session_start_limit *)`
 *     * :code:`void discord_session_start_limit_list_free(struct discord_session_start_limit **)`
 *   * JSON Decoder:

 *     * :code:`void discord_session_start_limit_from_json(char *rbuf, size_t len, struct discord_session_start_limit **)`
 *     * :code:`void discord_session_start_limit_list_from_json(char *rbuf, size_t len, struct discord_session_start_limit ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_session_start_limit_to_json(char *wbuf, size_t len, struct discord_session_start_limit *)`
 *     * :code:`void discord_session_start_limit_list_to_json(char *wbuf, size_t len, struct discord_session_start_limit **)`
 * @endverbatim
 */
struct discord_session_start_limit {
  /* specs/discord/gateway.json:227:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */
  int total; /**< the total number of session starts the current user is allowed */

  /* specs/discord/gateway.json:228:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */
  int remaining; /**< the remaining number of session starts the current user is allowed */

  /* specs/discord/gateway.json:229:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */
  int reset_after; /**< the number of milliseconds after which the limit resets */

  /* specs/discord/gateway.json:230:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */
  int max_concurrency; /**< the number of identify requests allowed per 5 seconds */

};
/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */

/* Create Guild From Guild Template */
/* defined at specs/discord/guild-template.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_from_guild_template_params_init(struct discord_create_guild_from_guild_template_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_from_guild_template_params_cleanup(struct discord_create_guild_from_guild_template_params *)`
 *     * :code:`void discord_create_guild_from_guild_template_params_list_free(struct discord_create_guild_from_guild_template_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_from_guild_template_params_from_json(char *rbuf, size_t len, struct discord_create_guild_from_guild_template_params **)`
 *     * :code:`void discord_create_guild_from_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_from_guild_template_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_from_guild_template_params_to_json(char *wbuf, size_t len, struct discord_create_guild_from_guild_template_params *)`
 *     * :code:`void discord_create_guild_from_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_from_guild_template_params **)`
 * @endverbatim
 */
struct discord_create_guild_from_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  char *name; /**< name of the guild */

  /* specs/discord/guild-template.endpoints-params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */
  char *icon; /**< base64 128x128 image for the guild icon */

};

/* Create Guild Template */
/* defined at specs/discord/guild-template.endpoints-params.json:19:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_template_params_init(struct discord_create_guild_template_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_template_params_cleanup(struct discord_create_guild_template_params *)`
 *     * :code:`void discord_create_guild_template_params_list_free(struct discord_create_guild_template_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_template_params_from_json(char *rbuf, size_t len, struct discord_create_guild_template_params **)`
 *     * :code:`void discord_create_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_template_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_template_params_to_json(char *wbuf, size_t len, struct discord_create_guild_template_params *)`
 *     * :code:`void discord_create_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_template_params **)`
 * @endverbatim
 */
struct discord_create_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  char *name; /**< name of the guild */

  /* specs/discord/guild-template.endpoints-params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
  char *description; /**< description for the template (0-120) chars */

};

/* Modify Guild Template */
/* defined at specs/discord/guild-template.endpoints-params.json:29:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_template_params_init(struct discord_modify_guild_template_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params *)`
 *     * :code:`void discord_modify_guild_template_params_list_free(struct discord_modify_guild_template_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_template_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_template_params **)`
 *     * :code:`void discord_modify_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_template_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_template_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_template_params *)`
 *     * :code:`void discord_modify_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_template_params **)`
 * @endverbatim
 */
struct discord_modify_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */
  char *name; /**< name of the guild */

  /* specs/discord/guild-template.endpoints-params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
  char *description; /**< description for the template (0-120) chars */

};
/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */

/* Guild Template Structure */
/* defined at specs/discord/guild-template.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild-template#guild-template-object-guild-template-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_template_init(struct discord_guild_template *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_template_cleanup(struct discord_guild_template *)`
 *     * :code:`void discord_guild_template_list_free(struct discord_guild_template **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_template_from_json(char *rbuf, size_t len, struct discord_guild_template **)`
 *     * :code:`void discord_guild_template_list_from_json(char *rbuf, size_t len, struct discord_guild_template ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_template_to_json(char *wbuf, size_t len, struct discord_guild_template *)`
 *     * :code:`void discord_guild_template_list_to_json(char *wbuf, size_t len, struct discord_guild_template **)`
 * @endverbatim
 */
struct discord_guild_template {
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
  char *code;

  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  char *description;

  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
  int usage_count;

  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t creator_id;

  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  struct discord_user *creator;

  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t created_at;

  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t updated_at;

  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t source_guild_id;

  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
  struct discord_guild *serialized_source_guild;

  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
  json_char_t* is_dirty;

};
/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */

/* Create Guild */
/* defined at specs/discord/guild.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_params_init(struct discord_create_guild_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_params_cleanup(struct discord_create_guild_params *)`
 *     * :code:`void discord_create_guild_params_list_free(struct discord_create_guild_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_params_from_json(char *rbuf, size_t len, struct discord_create_guild_params **)`
 *     * :code:`void discord_create_guild_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_params_to_json(char *wbuf, size_t len, struct discord_create_guild_params *)`
 *     * :code:`void discord_create_guild_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_params **)`
 * @endverbatim
 */
struct discord_create_guild_params {
  /* specs/discord/guild.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  char *name; /**< name of the guild (2-100) characters */

  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  char *region; /**< voice region id */

  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  char *icon; /**< base64 128x1128 image for the guild icon */

  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  int verification_level; /**< verification level */

  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  int default_message_notifications; /**< default message notification level */

  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  int explicit_content_filter; /**< explicit content filter level */

  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */
  struct discord_role **roles; /**< new guild roles */

  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
  struct discord_channel **channels; /**< array of partial channel objects */

  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  u64_snowflake_t afk_channel_id; /**< id for afk channel */

  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  int afk_timeout; /**< afk timeout in seconds */

  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  u64_snowflake_t system_channel_id; /**< the id of the channel where guild notices such as welcome messages and boost events are posted */

};

/* Modify Guild */
/* defined at specs/discord/guild.endpoints-params.json:28:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_params_init(struct discord_modify_guild_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *)`
 *     * :code:`void discord_modify_guild_params_list_free(struct discord_modify_guild_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_params **)`
 *     * :code:`void discord_modify_guild_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_params *)`
 *     * :code:`void discord_modify_guild_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_params **)`
 * @endverbatim
 */
struct discord_modify_guild_params {
  /* specs/discord/guild.endpoints-params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  char *name; /**< name of the guild (2-100) characters */

  /* specs/discord/guild.endpoints-params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  char *region; /**< voice region id */

  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  int verification_level; /**< verification level */

  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  int default_message_notifications; /**< default message notification level */

  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  int explicit_content_filter; /**< explicit content filter level */

  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  u64_snowflake_t afk_channel_id; /**< id for afk channel */

  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  int afk_timeout; /**< afk timeout in seconds */

  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  char *icon; /**< base64 128x1128 image for the guild icon */

  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
  u64_snowflake_t owner_id; /**< user id to transfer guild ownership to (must be owner) */

  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
  char *splash; /**< base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature */

  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
  char *discovery_splash; /**< base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature) */

  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
  char *banner; /**< cannot unescape an ill-formed-string 	base64 16:9 png/jpeg image for the guild banner (wh */

  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  u64_snowflake_t system_channel_id; /**< cannot unescape an ill-formed-string 	the id of the channel where guild notices such as welcome */

  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
  enum discord_system_channel_flags system_channel_flags; /**< system channel flags */

  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
  u64_snowflake_t rules_channel_id; /**< the id of the channel where Community guilds display rules and/or guidelines */

  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
  u64_snowflake_t public_updates_channel_id; /**< the id of the channel where admins and moderators of Community guilds receive notices from Discord */

  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
  char *preferred_locale; /**< the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to "en-US" */

  /* specs/discord/guild.endpoints-params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */
  ja_str **features; /**< array of guild feature strings */

  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
  char *description; /**< the description for the guild, if the guild is discoverable */

};

/* Create Guild Channel */
/* defined at specs/discord/guild.endpoints-params.json:55:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *)`
 *     * :code:`void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_channel_params_from_json(char *rbuf, size_t len, struct discord_create_guild_channel_params **)`
 *     * :code:`void discord_create_guild_channel_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_channel_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_channel_params_to_json(char *wbuf, size_t len, struct discord_create_guild_channel_params *)`
 *     * :code:`void discord_create_guild_channel_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_channel_params **)`
 * @endverbatim
 */
struct discord_create_guild_channel_params {
  /* specs/discord/guild.endpoints-params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.endpoints-params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/guild.endpoints-params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
  char *topic;

  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
  int bitrate;

  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
  int user_limit;

  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
  int rate_limit_per_user;

  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */
  int position;

  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
  struct discord_overwrite **permission_overwrites;

  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  u64_snowflake_t parent_id;

  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
  bool nsfw;

};

/* Modify Guild Channel Positions */
/* defined at specs/discord/guild.endpoints-params.json:73:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *)`
 *     * :code:`void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_channel_positions_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_channel_positions_params **)`
 *     * :code:`void discord_modify_guild_channel_positions_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_channel_positions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_channel_positions_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_channel_positions_params *)`
 *     * :code:`void discord_modify_guild_channel_positions_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_channel_positions_params **)`
 * @endverbatim
 */
struct discord_modify_guild_channel_positions_params {
  /* specs/discord/guild.endpoints-params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
  u64_snowflake_t id; /**< channel id */

  /* specs/discord/guild.endpoints-params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
  int position; /**< sorting position of the channel */

  /* specs/discord/guild.endpoints-params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
  bool lock_permissions; /**< syncs the permission overwrites with the new parent, if moving to a new category */

  /* specs/discord/guild.endpoints-params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
  u64_snowflake_t parent_id; /**< the new parent ID for the channel that is moved */

};

/* List Guild Members */
/* defined at specs/discord/guild.endpoints-params.json:85:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_list_guild_members_params_init(struct discord_list_guild_members_params *)`
 *   * Cleanup:

 *     * :code:`void discord_list_guild_members_params_cleanup(struct discord_list_guild_members_params *)`
 *     * :code:`void discord_list_guild_members_params_list_free(struct discord_list_guild_members_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_list_guild_members_params_from_json(char *rbuf, size_t len, struct discord_list_guild_members_params **)`
 *     * :code:`void discord_list_guild_members_params_list_from_json(char *rbuf, size_t len, struct discord_list_guild_members_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_list_guild_members_params_to_json(char *wbuf, size_t len, struct discord_list_guild_members_params *)`
 *     * :code:`void discord_list_guild_members_params_list_to_json(char *wbuf, size_t len, struct discord_list_guild_members_params **)`
 * @endverbatim
 */
struct discord_list_guild_members_params {
  /* specs/discord/guild.endpoints-params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */
  int limit; /**< max numbers of members to return (1-1000) */

  /* specs/discord/guild.endpoints-params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */
  u64_snowflake_t after; /**< the highest user id in the previous page */

};

/* Search Guild Members */
/* defined at specs/discord/guild.endpoints-params.json:95:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_search_guild_members_params_init(struct discord_search_guild_members_params *)`
 *   * Cleanup:

 *     * :code:`void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *)`
 *     * :code:`void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_search_guild_members_params_from_json(char *rbuf, size_t len, struct discord_search_guild_members_params **)`
 *     * :code:`void discord_search_guild_members_params_list_from_json(char *rbuf, size_t len, struct discord_search_guild_members_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_search_guild_members_params_to_json(char *wbuf, size_t len, struct discord_search_guild_members_params *)`
 *     * :code:`void discord_search_guild_members_params_list_to_json(char *wbuf, size_t len, struct discord_search_guild_members_params **)`
 * @endverbatim
 */
struct discord_search_guild_members_params {
  /* specs/discord/guild.endpoints-params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
  char *query; /**< Query string to match username(s) and nickname(s) against. */

  /* specs/discord/guild.endpoints-params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
  int limit; /**< max number of members to return (1-1000) */

};

/* Add Guild Member */
/* defined at specs/discord/guild.endpoints-params.json:105:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_add_guild_member_params_init(struct discord_add_guild_member_params *)`
 *   * Cleanup:

 *     * :code:`void discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params *)`
 *     * :code:`void discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_add_guild_member_params_from_json(char *rbuf, size_t len, struct discord_add_guild_member_params **)`
 *     * :code:`void discord_add_guild_member_params_list_from_json(char *rbuf, size_t len, struct discord_add_guild_member_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_add_guild_member_params_to_json(char *wbuf, size_t len, struct discord_add_guild_member_params *)`
 *     * :code:`void discord_add_guild_member_params_list_to_json(char *wbuf, size_t len, struct discord_add_guild_member_params **)`
 * @endverbatim
 */
struct discord_add_guild_member_params {
  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *access_token;

  /* specs/discord/guild.endpoints-params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *nick;

  /* specs/discord/guild.endpoints-params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **roles;

  /* specs/discord/guild.endpoints-params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mute;

  /* specs/discord/guild.endpoints-params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool deaf;

};

/* Modify Guild Member */
/* defined at specs/discord/guild.endpoints-params.json:118:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *)`
 *     * :code:`void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_member_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_member_params **)`
 *     * :code:`void discord_modify_guild_member_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_member_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_member_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_member_params *)`
 *     * :code:`void discord_modify_guild_member_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_member_params **)`
 * @endverbatim
 */
struct discord_modify_guild_member_params {
  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **roles;

  /* specs/discord/guild.endpoints-params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mute;

  /* specs/discord/guild.endpoints-params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool deaf;

  /* specs/discord/guild.endpoints-params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  u64_snowflake_t channel_id;

};

/* Modify Current Member */
/* defined at specs/discord/guild.endpoints-params.json:131:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_current_member_params_init(struct discord_modify_current_member_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_current_member_params_cleanup(struct discord_modify_current_member_params *)`
 *     * :code:`void discord_modify_current_member_params_list_free(struct discord_modify_current_member_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_current_member_params_from_json(char *rbuf, size_t len, struct discord_modify_current_member_params **)`
 *     * :code:`void discord_modify_current_member_params_list_from_json(char *rbuf, size_t len, struct discord_modify_current_member_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_current_member_params_to_json(char *wbuf, size_t len, struct discord_modify_current_member_params *)`
 *     * :code:`void discord_modify_current_member_params_list_to_json(char *wbuf, size_t len, struct discord_modify_current_member_params **)`
 * @endverbatim
 */
struct discord_modify_current_member_params {
  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

};

/* Modify Current User Nick */
/* defined at specs/discord/guild.endpoints-params.json:140:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_current_user_nick_params_init(struct discord_modify_current_user_nick_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_current_user_nick_params_cleanup(struct discord_modify_current_user_nick_params *)`
 *     * :code:`void discord_modify_current_user_nick_params_list_free(struct discord_modify_current_user_nick_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_current_user_nick_params_from_json(char *rbuf, size_t len, struct discord_modify_current_user_nick_params **)`
 *     * :code:`void discord_modify_current_user_nick_params_list_from_json(char *rbuf, size_t len, struct discord_modify_current_user_nick_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_current_user_nick_params_to_json(char *wbuf, size_t len, struct discord_modify_current_user_nick_params *)`
 *     * :code:`void discord_modify_current_user_nick_params_list_to_json(char *wbuf, size_t len, struct discord_modify_current_user_nick_params **)`
 * @endverbatim
 */
struct discord_modify_current_user_nick_params {
  /* specs/discord/guild.endpoints-params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

};

/* Create Guild Ban */
/* defined at specs/discord/guild.endpoints-params.json:149:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_ban_params_init(struct discord_create_guild_ban_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_ban_params_cleanup(struct discord_create_guild_ban_params *)`
 *     * :code:`void discord_create_guild_ban_params_list_free(struct discord_create_guild_ban_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_ban_params_from_json(char *rbuf, size_t len, struct discord_create_guild_ban_params **)`
 *     * :code:`void discord_create_guild_ban_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_ban_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_ban_params_to_json(char *wbuf, size_t len, struct discord_create_guild_ban_params *)`
 *     * :code:`void discord_create_guild_ban_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_ban_params **)`
 * @endverbatim
 */
struct discord_create_guild_ban_params {
  /* specs/discord/guild.endpoints-params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */
  int delete_message_days; /**< number of days to delete messages for(0-7) */

  /* specs/discord/guild.endpoints-params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */
  char *reason; /**< reason for the ban (deprecated) */

};

/* Create Guild Role */
/* defined at specs/discord/guild.endpoints-params.json:159:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_role_params_init(struct discord_create_guild_role_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *)`
 *     * :code:`void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_role_params_from_json(char *rbuf, size_t len, struct discord_create_guild_role_params **)`
 *     * :code:`void discord_create_guild_role_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_role_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_role_params_to_json(char *wbuf, size_t len, struct discord_create_guild_role_params *)`
 *     * :code:`void discord_create_guild_role_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_role_params **)`
 * @endverbatim
 */
struct discord_create_guild_role_params {
  /* specs/discord/guild.endpoints-params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.endpoints-params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags" }, "inject_if_not":0}' */
  enum discord_bitwise_permission_flags permissions;

  /* specs/discord/guild.endpoints-params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
  int color;

  /* specs/discord/guild.endpoints-params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool hoist;

  /* specs/discord/guild.endpoints-params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mentionable;

};

/* Modify Guild Role Positions */
/* defined at specs/discord/guild.endpoints-params.json:172:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *)`
 *     * :code:`void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_role_positions_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_positions_params **)`
 *     * :code:`void discord_modify_guild_role_positions_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_positions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_role_positions_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_positions_params *)`
 *     * :code:`void discord_modify_guild_role_positions_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_positions_params **)`
 * @endverbatim
 */
struct discord_modify_guild_role_positions_params {
  /* specs/discord/guild.endpoints-params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
  u64_snowflake_t id; /**< role */

  /* specs/discord/guild.endpoints-params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
  int position; /**< sorting position of the role */

};

/* Modify Guild Role */
/* defined at specs/discord/guild.endpoints-params.json:182:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *)`
 *     * :code:`void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_role_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_params **)`
 *     * :code:`void discord_modify_guild_role_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_role_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_params *)`
 *     * :code:`void discord_modify_guild_role_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_params **)`
 * @endverbatim
 */
struct discord_modify_guild_role_params {
  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
  char *name; /**< name of the role */

  /* specs/discord/guild.endpoints-params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
  enum discord_bitwise_permission_flags permissions; /**< bitwise value of the enabled/disabled permissions */

  /* specs/discord/guild.endpoints-params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
  int color; /**< RGB color value */

  /* specs/discord/guild.endpoints-params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
  bool hoist; /**< whether the role should be displayed separately in the sidebar */

  /* specs/discord/guild.endpoints-params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
  bool mentionable; /**< whether the role should be mentionable */

};

/* Get Guild Prune Count */
/* defined at specs/discord/guild.endpoints-params.json:195:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_guild_prune_count_params_cleanup(struct discord_get_guild_prune_count_params *)`
 *     * :code:`void discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_guild_prune_count_params_from_json(char *rbuf, size_t len, struct discord_get_guild_prune_count_params **)`
 *     * :code:`void discord_get_guild_prune_count_params_list_from_json(char *rbuf, size_t len, struct discord_get_guild_prune_count_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_guild_prune_count_params_to_json(char *wbuf, size_t len, struct discord_get_guild_prune_count_params *)`
 *     * :code:`void discord_get_guild_prune_count_params_list_to_json(char *wbuf, size_t len, struct discord_get_guild_prune_count_params **)`
 * @endverbatim
 */
struct discord_get_guild_prune_count_params {
  /* specs/discord/guild.endpoints-params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  int days;

  /* specs/discord/guild.endpoints-params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **include_roles;

};

/* Begin Guild Prune */
/* defined at specs/discord/guild.endpoints-params.json:205:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params *)`
 *   * Cleanup:

 *     * :code:`void discord_begin_guild_prune_params_cleanup(struct discord_begin_guild_prune_params *)`
 *     * :code:`void discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_begin_guild_prune_params_from_json(char *rbuf, size_t len, struct discord_begin_guild_prune_params **)`
 *     * :code:`void discord_begin_guild_prune_params_list_from_json(char *rbuf, size_t len, struct discord_begin_guild_prune_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_begin_guild_prune_params_to_json(char *wbuf, size_t len, struct discord_begin_guild_prune_params *)`
 *     * :code:`void discord_begin_guild_prune_params_list_to_json(char *wbuf, size_t len, struct discord_begin_guild_prune_params **)`
 * @endverbatim
 */
struct discord_begin_guild_prune_params {
  /* specs/discord/guild.endpoints-params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  int days;

  /* specs/discord/guild.endpoints-params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool compute_prune_count;

  /* specs/discord/guild.endpoints-params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **include_roles;

  /* specs/discord/guild.endpoints-params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *reason;

};
/* This file is generated from specs/discord/guild.json, Please don't edit it. */

/* Guild Structure */
/* defined at specs/discord/guild.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_init(struct discord_guild *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_cleanup(struct discord_guild *)`
 *     * :code:`void discord_guild_list_free(struct discord_guild **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_from_json(char *rbuf, size_t len, struct discord_guild **)`
 *     * :code:`void discord_guild_list_from_json(char *rbuf, size_t len, struct discord_guild ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_to_json(char *wbuf, size_t len, struct discord_guild *)`
 *     * :code:`void discord_guild_list_to_json(char *wbuf, size_t len, struct discord_guild **)`
 * @endverbatim
 */
struct discord_guild {
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:13:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name"}' */
  char *name;

  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */
  char *icon;

  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */
  char *icon_hash;

  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */
  char *splash;

  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */
  char *discovery_splash;

  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */
  bool owner;

  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */
  u64_snowflake_t owner_id;

  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */
  int permissions;

  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */
  char region[ORCA_LIMITS_REGION];

  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */
  u64_snowflake_t afk_channel_id;

  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */
  int afk_timeout;

  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */
  bool widget_enabled;

  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */
  u64_snowflake_t widget_channel_id;

  /* specs/discord/guild.json:26:88
     '{"type":{"base":"int", "int_alias":"enum discord_verification_level"}, "name":"verification_level"}' */
  enum discord_verification_level verification_level;

  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */
  enum discord_default_message_notification_level default_message_notifications;

  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */
  enum discord_explicit_content_filter_level explicit_content_filter;

  /* specs/discord/guild.json:31:70
     '{"type":{"base":"struct discord_role", "dec":"ntl"}, "name":"roles", "comment":"array of role objects", "inject_if_not":null }' */
  struct discord_role **roles; /**< array of role objects */

  /* specs/discord/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */
  struct discord_emoji **emojis;

  /* specs/discord/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "comment":"array of guild feature strings", "inject_if_not":null }' */
  ja_str **features; /**< array of guild feature strings */

  /* specs/discord/guild.json:34:79
     '{"type":{"base":"int", "int_alias":"enum discord_mfa_level"}, "name":"mfa_level"}' */
  enum discord_mfa_level mfa_level;

  /* specs/discord/guild.json:35:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */
  u64_snowflake_t application_id;

  /* specs/discord/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */
  u64_snowflake_t system_channel_id;

  /* specs/discord/guild.json:37:90
     '{"type":{"base":"int", "int_alias":"enum discord_system_channel_flags"}, "name":"system_channel_flags"}' */
  enum discord_system_channel_flags system_channel_flags;

  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */
  u64_snowflake_t rules_channel_id;

  /* specs/discord/guild.json:39:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */
  u64_unix_ms_t joined_at;

  /* specs/discord/guild.json:40:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */
  bool large;

  /* specs/discord/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */
  bool unavailable;

  /* specs/discord/guild.json:42:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */
  int member_count;

  /* specs/discord/guild.json:43:77
     '{"type":{"base":"struct discord_voice_state", "dec":"ntl"}, "name":"voice_states", "comment":"array of partial voice state objects", "inject_if_not":null }' */
  struct discord_voice_state **voice_states; /**< array of partial voice state objects */

  /* specs/discord/guild.json:44:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */
  struct discord_guild_member **members;

  /* specs/discord/guild.json:45:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */
  struct discord_channel **channels; /**< array of channel objects */

  /* specs/discord/guild.json:47:81
     '{"type":{"base":"struct discord_presence_status", "dec":"ntl"}, "name":"presences", "option":true, "comment":"array of partial presence update objects", "inject_if_not":null }' */
  struct discord_presence_status **presences; /**< array of partial presence update objects */

  /* specs/discord/guild.json:48:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */
  int max_presences;

  /* specs/discord/guild.json:49:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */
  int max_members;

  /* specs/discord/guild.json:50:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */
  char *vanity_url;

  /* specs/discord/guild.json:51:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */
  char *description;

  /* specs/discord/guild.json:52:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */
  char *banner;

  /* specs/discord/guild.json:53:82
     '{"type":{"base":"int", "int_alias":"enum discord_premium_tier"}, "name":"premium_tier"}' */
  enum discord_premium_tier premium_tier;

  /* specs/discord/guild.json:54:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */
  int premium_subscription_count;

  /* specs/discord/guild.json:55:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */
  char preferred_locale[ORCA_LIMITS_LOCALE];

  /* specs/discord/guild.json:57:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */
  u64_snowflake_t public_updates_channel_id;

  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */
  int max_video_channel_users;

  /* specs/discord/guild.json:59:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */
  int approximate_member_count;

  /* specs/discord/guild.json:60:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */
  int approximate_presence_count;

  /* specs/discord/guild.json:61:78
     '{"type":{"base":"struct discord_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
  struct discord_welcome_screen *welcome_screen;

};















/* Unavailable Guild Object */
/* defined at specs/discord/guild.json:150:23 */
/**
 * @see https://discord.com/developers/docs/resources/guild#unavailable-guild-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_unavailable_guild_init(struct discord_unavailable_guild *)`
 *   * Cleanup:

 *     * :code:`void discord_unavailable_guild_cleanup(struct discord_unavailable_guild *)`
 *     * :code:`void discord_unavailable_guild_list_free(struct discord_unavailable_guild **)`
 *   * JSON Decoder:

 *     * :code:`void discord_unavailable_guild_from_json(char *rbuf, size_t len, struct discord_unavailable_guild **)`
 *     * :code:`void discord_unavailable_guild_list_from_json(char *rbuf, size_t len, struct discord_unavailable_guild ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_unavailable_guild_to_json(char *wbuf, size_t len, struct discord_unavailable_guild *)`
 *     * :code:`void discord_unavailable_guild_list_to_json(char *wbuf, size_t len, struct discord_unavailable_guild **)`
 * @endverbatim
 */
struct discord_unavailable_guild {
  /* specs/discord/guild.json:152:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:153:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */
  bool unavailable;

};

/* Guild Preview Object */
/* defined at specs/discord/guild.json:160:23 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-preview-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_preview_init(struct discord_guild_preview *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_preview_cleanup(struct discord_guild_preview *)`
 *     * :code:`void discord_guild_preview_list_free(struct discord_guild_preview **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_preview_from_json(char *rbuf, size_t len, struct discord_guild_preview **)`
 *     * :code:`void discord_guild_preview_list_from_json(char *rbuf, size_t len, struct discord_guild_preview ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_preview_to_json(char *wbuf, size_t len, struct discord_guild_preview *)`
 *     * :code:`void discord_guild_preview_list_to_json(char *wbuf, size_t len, struct discord_guild_preview **)`
 * @endverbatim
 */
struct discord_guild_preview {
  /* specs/discord/guild.json:162:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:163:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/guild.json:164:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  char *icon;

  /* specs/discord/guild.json:165:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  char *splash;

  /* specs/discord/guild.json:166:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  char *discovery_splash;

  /* specs/discord/guild.json:167:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */
  struct discord_emoji **emojis;

  /* specs/discord/guild.json:168:18
     '{"name":"features", "type":{"base":"ja_str", "dec":"ntl"}}' */
  ja_str **features;

  /* specs/discord/guild.json:169:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */
  int approximate_member_count;

  /* specs/discord/guild.json:170:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */
  int approximate_presence_count;

  /* specs/discord/guild.json:171:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  char *description;

};

/* Guild Widget Object */
/* defined at specs/discord/guild.json:178:23 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-widget-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_widget_init(struct discord_guild_widget *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_widget_cleanup(struct discord_guild_widget *)`
 *     * :code:`void discord_guild_widget_list_free(struct discord_guild_widget **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_widget_from_json(char *rbuf, size_t len, struct discord_guild_widget **)`
 *     * :code:`void discord_guild_widget_list_from_json(char *rbuf, size_t len, struct discord_guild_widget ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_widget_to_json(char *wbuf, size_t len, struct discord_guild_widget *)`
 *     * :code:`void discord_guild_widget_list_to_json(char *wbuf, size_t len, struct discord_guild_widget **)`
 * @endverbatim
 */
struct discord_guild_widget {
  /* specs/discord/guild.json:180:18
     '{"name":"enabled", "type":{"base":"bool"}}' */
  bool enabled;

  /* specs/discord/guild.json:181:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */
  u64_snowflake_t channel_id;

};

/* Guild Member Structure */
/* defined at specs/discord/guild.json:188:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-member-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_member_init(struct discord_guild_member *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_member_cleanup(struct discord_guild_member *)`
 *     * :code:`void discord_guild_member_list_free(struct discord_guild_member **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_member_from_json(char *rbuf, size_t len, struct discord_guild_member **)`
 *     * :code:`void discord_guild_member_list_from_json(char *rbuf, size_t len, struct discord_guild_member ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_member_to_json(char *wbuf, size_t len, struct discord_guild_member *)`
 *     * :code:`void discord_guild_member_list_to_json(char *wbuf, size_t len, struct discord_guild_member **)`
 * @endverbatim
 */
struct discord_guild_member {
  /* specs/discord/guild.json:191:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  struct discord_user *user;

  /* specs/discord/guild.json:192:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}, "option":true}' */
  char *nick;

  /* specs/discord/guild.json:193:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */
  ja_u64 **roles; /**< array of role object ids */

  /* specs/discord/guild.json:194:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t joined_at;

  /* specs/discord/guild.json:195:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t premium_since;

  /* specs/discord/guild.json:196:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  bool deaf;

  /* specs/discord/guild.json:197:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  bool mute;

  /* specs/discord/guild.json:198:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */
  bool pending;

  /* specs/discord/guild.json:199:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */
  char *permissions;

};

/* Integration Structure */
/* defined at specs/discord/guild.json:205:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_integration_init(struct discord_integration *)`
 *   * Cleanup:

 *     * :code:`void discord_integration_cleanup(struct discord_integration *)`
 *     * :code:`void discord_integration_list_free(struct discord_integration **)`
 *   * JSON Decoder:

 *     * :code:`void discord_integration_from_json(char *rbuf, size_t len, struct discord_integration **)`
 *     * :code:`void discord_integration_list_from_json(char *rbuf, size_t len, struct discord_integration ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_integration_to_json(char *wbuf, size_t len, struct discord_integration *)`
 *     * :code:`void discord_integration_list_to_json(char *wbuf, size_t len, struct discord_integration **)`
 * @endverbatim
 */
struct discord_integration {
  /* specs/discord/guild.json:208:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:209:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/guild.json:210:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  char *type;

  /* specs/discord/guild.json:211:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */
  bool enabled;

  /* specs/discord/guild.json:212:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */
  bool syncing;

  /* specs/discord/guild.json:213:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t role_id;

  /* specs/discord/guild.json:214:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */
  bool enable_emotions;

  /* specs/discord/guild.json:215:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_integration_expire_behaviors"}}' */
  enum discord_integration_expire_behaviors expire_behavior;

  /* specs/discord/guild.json:216:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */
  int expire_grace_period;

  /* specs/discord/guild.json:217:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
  struct discord_user *user;

  /* specs/discord/guild.json:218:20
     '{ "name": "account", "type":{ "base":"struct discord_integration_account", "dec":"*"}}' */
  struct discord_integration_account *account;

  /* specs/discord/guild.json:219:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  u64_unix_ms_t synced_at;

  /* specs/discord/guild.json:220:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */
  int subscriber_count;

  /* specs/discord/guild.json:221:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  bool revoked;

  /* specs/discord/guild.json:222:20
     '{ "name": "application", "type":{ "base":"struct discord_integration_application", "dec":"*" }}' */
  struct discord_integration_application *application;

};



/* Integration Account Structure */
/* defined at specs/discord/guild.json:239:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-account-object-integration-account-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_integration_account_init(struct discord_integration_account *)`
 *   * Cleanup:

 *     * :code:`void discord_integration_account_cleanup(struct discord_integration_account *)`
 *     * :code:`void discord_integration_account_list_free(struct discord_integration_account **)`
 *   * JSON Decoder:

 *     * :code:`void discord_integration_account_from_json(char *rbuf, size_t len, struct discord_integration_account **)`
 *     * :code:`void discord_integration_account_list_from_json(char *rbuf, size_t len, struct discord_integration_account ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_integration_account_to_json(char *wbuf, size_t len, struct discord_integration_account *)`
 *     * :code:`void discord_integration_account_list_to_json(char *wbuf, size_t len, struct discord_integration_account **)`
 * @endverbatim
 */
struct discord_integration_account {
  /* specs/discord/guild.json:241:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:242:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

};

/* Integration Application Object */
/* defined at specs/discord/guild.json:249:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-application-object-integration-application-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_integration_application_init(struct discord_integration_application *)`
 *   * Cleanup:

 *     * :code:`void discord_integration_application_cleanup(struct discord_integration_application *)`
 *     * :code:`void discord_integration_application_list_free(struct discord_integration_application **)`
 *   * JSON Decoder:

 *     * :code:`void discord_integration_application_from_json(char *rbuf, size_t len, struct discord_integration_application **)`
 *     * :code:`void discord_integration_application_list_from_json(char *rbuf, size_t len, struct discord_integration_application ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_integration_application_to_json(char *wbuf, size_t len, struct discord_integration_application *)`
 *     * :code:`void discord_integration_application_list_to_json(char *wbuf, size_t len, struct discord_integration_application **)`
 * @endverbatim
 */
struct discord_integration_application {
  /* specs/discord/guild.json:251:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:252:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.json:253:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  char icon[ORCA_LIMITS_SHA256];

  /* specs/discord/guild.json:254:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */
  char *description;

  /* specs/discord/guild.json:255:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */
  char *summary;

  /* specs/discord/guild.json:256:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  struct discord_user *bot;

};

/* Ban Structure */
/* defined at specs/discord/guild.json:262:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild#ban-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_ban_init(struct discord_ban *)`
 *   * Cleanup:

 *     * :code:`void discord_ban_cleanup(struct discord_ban *)`
 *     * :code:`void discord_ban_list_free(struct discord_ban **)`
 *   * JSON Decoder:

 *     * :code:`void discord_ban_from_json(char *rbuf, size_t len, struct discord_ban **)`
 *     * :code:`void discord_ban_list_from_json(char *rbuf, size_t len, struct discord_ban ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_ban_to_json(char *wbuf, size_t len, struct discord_ban *)`
 *     * :code:`void discord_ban_list_to_json(char *wbuf, size_t len, struct discord_ban **)`
 * @endverbatim
 */
struct discord_ban {
  /* specs/discord/guild.json:265:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }}' */
  char *reason;

  /* specs/discord/guild.json:266:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  struct discord_user *user; /**< partial user object */

};

/* Welcome Screen Structure */
/* defined at specs/discord/guild.json:272:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_welcome_screen_init(struct discord_welcome_screen *)`
 *   * Cleanup:

 *     * :code:`void discord_welcome_screen_cleanup(struct discord_welcome_screen *)`
 *     * :code:`void discord_welcome_screen_list_free(struct discord_welcome_screen **)`
 *   * JSON Decoder:

 *     * :code:`void discord_welcome_screen_from_json(char *rbuf, size_t len, struct discord_welcome_screen **)`
 *     * :code:`void discord_welcome_screen_list_from_json(char *rbuf, size_t len, struct discord_welcome_screen ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_welcome_screen_to_json(char *wbuf, size_t len, struct discord_welcome_screen *)`
 *     * :code:`void discord_welcome_screen_list_to_json(char *wbuf, size_t len, struct discord_welcome_screen **)`
 * @endverbatim
 */
struct discord_welcome_screen {
  /* specs/discord/guild.json:275:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *description;

  /* specs/discord/guild.json:276:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_welcome_screen_channel", "dec":"ntl" }, "inject_if_not":null }' */
  struct discord_welcome_screen_channel **welcome_channels;

};

/* Welcome Screen Channel Structure */
/* defined at specs/discord/guild.json:283:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_welcome_screen_channel_init(struct discord_welcome_screen_channel *)`
 *   * Cleanup:

 *     * :code:`void discord_welcome_screen_channel_cleanup(struct discord_welcome_screen_channel *)`
 *     * :code:`void discord_welcome_screen_channel_list_free(struct discord_welcome_screen_channel **)`
 *   * JSON Decoder:

 *     * :code:`void discord_welcome_screen_channel_from_json(char *rbuf, size_t len, struct discord_welcome_screen_channel **)`
 *     * :code:`void discord_welcome_screen_channel_list_from_json(char *rbuf, size_t len, struct discord_welcome_screen_channel ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_welcome_screen_channel_to_json(char *wbuf, size_t len, struct discord_welcome_screen_channel *)`
 *     * :code:`void discord_welcome_screen_channel_list_to_json(char *wbuf, size_t len, struct discord_welcome_screen_channel **)`
 * @endverbatim
 */
struct discord_welcome_screen_channel {
  /* specs/discord/guild.json:286:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t channel_id;

  /* specs/discord/guild.json:287:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  char *description;

  /* specs/discord/guild.json:288:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t emoji_id;

  /* specs/discord/guild.json:289:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */
  char *emoji_name;

};
/* This file is generated from specs/discord/interaction.endpoints-params.json, Please don't edit it. */

/* Edit Original Interaction Response */
/* defined at specs/discord/interaction.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_original_interaction_response_params_init(struct discord_edit_original_interaction_response_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_original_interaction_response_params_cleanup(struct discord_edit_original_interaction_response_params *)`
 *     * :code:`void discord_edit_original_interaction_response_params_list_free(struct discord_edit_original_interaction_response_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_original_interaction_response_params_from_json(char *rbuf, size_t len, struct discord_edit_original_interaction_response_params **)`
 *     * :code:`void discord_edit_original_interaction_response_params_list_from_json(char *rbuf, size_t len, struct discord_edit_original_interaction_response_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_original_interaction_response_params_to_json(char *wbuf, size_t len, struct discord_edit_original_interaction_response_params *)`
 *     * :code:`void discord_edit_original_interaction_response_params_list_to_json(char *wbuf, size_t len, struct discord_edit_original_interaction_response_params **)`
 * @endverbatim
 */
struct discord_edit_original_interaction_response_params {
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  char *content; /**< name of the webhook(1-2000) chars */

  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< array of up to 10 embeds objects */

  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  char *payload_json; /**< JSON encoded body of non-file params (multipart/form-data only) */

  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};

/* Create Followup Message */
/* defined at specs/discord/interaction.endpoints-params.json:23:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_followup_message_params_init(struct discord_create_followup_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_followup_message_params_cleanup(struct discord_create_followup_message_params *)`
 *     * :code:`void discord_create_followup_message_params_list_free(struct discord_create_followup_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_followup_message_params_from_json(char *rbuf, size_t len, struct discord_create_followup_message_params **)`
 *     * :code:`void discord_create_followup_message_params_list_from_json(char *rbuf, size_t len, struct discord_create_followup_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_followup_message_params_to_json(char *wbuf, size_t len, struct discord_create_followup_message_params *)`
 *     * :code:`void discord_create_followup_message_params_list_to_json(char *wbuf, size_t len, struct discord_create_followup_message_params **)`
 * @endverbatim
 */
struct discord_create_followup_message_params {
  /* specs/discord/interaction.endpoints-params.json:27:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)", "default_value":true }' */
  bool wait; /**< cannot unescape an ill-formed-string 	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that i */

  /* specs/discord/interaction.endpoints-params.json:28:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  u64_snowflake_t thread_id; /**< Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived */

  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  char *username; /**< override the default username of the webhook */

  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  char *avatar_url; /**< override the default avatar of the webhook */

  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  bool tts; /**< true if this is a TTS message */

  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  struct discord_embed *embeds; /**< embedded rich content */

  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
  char *payload_json; /**< JSON encoded body of non-file params */

  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  struct discord_component **components; /**< the components to include with the message */

  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
  int flags; /**< can be set to 64 to send a ephemeral message */

};

/* Edit Followup Message */
/* defined at specs/discord/interaction.endpoints-params.json:44:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_followup_message_params_init(struct discord_edit_followup_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_followup_message_params_cleanup(struct discord_edit_followup_message_params *)`
 *     * :code:`void discord_edit_followup_message_params_list_free(struct discord_edit_followup_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_followup_message_params_from_json(char *rbuf, size_t len, struct discord_edit_followup_message_params **)`
 *     * :code:`void discord_edit_followup_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_followup_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_followup_message_params_to_json(char *wbuf, size_t len, struct discord_edit_followup_message_params *)`
 *     * :code:`void discord_edit_followup_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_followup_message_params **)`
 * @endverbatim
 */
struct discord_edit_followup_message_params {
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  char *content; /**< name of the webhook(1-2000) chars */

  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< array of up to 10 embeds objects */

  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  char *payload_json; /**< JSON encoded body of non-file params (multipart/form-data only) */

  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};
/* This file is generated from specs/discord/interaction.json, Please don't edit it. */

/* Interaction Structure */
/* defined at specs/discord/interaction.json:9:22 */
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-interaction-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_interaction_init(struct discord_interaction *)`
 *   * Cleanup:

 *     * :code:`void discord_interaction_cleanup(struct discord_interaction *)`
 *     * :code:`void discord_interaction_list_free(struct discord_interaction **)`
 *   * JSON Decoder:

 *     * :code:`void discord_interaction_from_json(char *rbuf, size_t len, struct discord_interaction **)`
 *     * :code:`void discord_interaction_list_from_json(char *rbuf, size_t len, struct discord_interaction ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_interaction_to_json(char *wbuf, size_t len, struct discord_interaction *)`
 *     * :code:`void discord_interaction_list_to_json(char *wbuf, size_t len, struct discord_interaction **)`
 * @endverbatim
 */
struct discord_interaction {
  /* specs/discord/interaction.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  u64_snowflake_t id; /**< id of the interaction */

  /* specs/discord/interaction.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
  u64_snowflake_t application_id; /**< id of the application this iteraction is for */

  /* specs/discord/interaction.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
  enum discord_interaction_types type; /**< the request type of the interaction */

  /* specs/discord/interaction.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  struct discord_interaction_data *data; /**< the command data payload */

  /* specs/discord/interaction.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
  u64_snowflake_t guild_id; /**< the guild it was sent from */

  /* specs/discord/interaction.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
  u64_snowflake_t channel_id; /**< the channel it was sent from */

  /* specs/discord/interaction.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  struct discord_guild_member *member; /**< guild member data for the invoking user, including permissions */

  /* specs/discord/interaction.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  struct discord_user *user; /**< user object for the invoking user, if invoked in a DM */

  /* specs/discord/interaction.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
  char *token; /**< a continuation token for responding to the interaction */

  /* specs/discord/interaction.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */
  struct discord_message *message; /**< for components, the message they were attached to */

};



/* Interaction Data Structure */
/* defined at specs/discord/interaction.json:40:22 */
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-data-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_interaction_data_init(struct discord_interaction_data *)`
 *   * Cleanup:

 *     * :code:`void discord_interaction_data_cleanup(struct discord_interaction_data *)`
 *     * :code:`void discord_interaction_data_list_free(struct discord_interaction_data **)`
 *   * JSON Decoder:

 *     * :code:`void discord_interaction_data_from_json(char *rbuf, size_t len, struct discord_interaction_data **)`
 *     * :code:`void discord_interaction_data_list_from_json(char *rbuf, size_t len, struct discord_interaction_data ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_interaction_data_to_json(char *wbuf, size_t len, struct discord_interaction_data *)`
 *     * :code:`void discord_interaction_data_list_to_json(char *wbuf, size_t len, struct discord_interaction_data **)`
 * @endverbatim
 */
struct discord_interaction_data {
  /* specs/discord/interaction.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
  u64_snowflake_t id; /**< the ID of the invoked command */

  /* specs/discord/interaction.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
  char *name; /**< the name of the invoked command */

  /* specs/discord/interaction.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */
  enum discord_application_command_types type; /**< the type of the invoked command */

  /* specs/discord/interaction.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  struct discord_resolved_data *resolved; /**< converted users + roles + channels */

  /* specs/discord/interaction.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_option **options; /**< the parameters for the command, max 25 */

  /* specs/discord/interaction.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */
  char *custom_id; /**< the custom id of the component */

  /* specs/discord/interaction.json:49:18
     '{"name":"values", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */
  ja_str **values; /**< the values the user selected */

  /* specs/discord/interaction.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */
  u64_snowflake_t target_id; /**< id of a user or message targetted by a user or message command */

};

/* Resolved Data Structure */
/* defined at specs/discord/interaction.json:57:22 */
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-resolved-data-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_resolved_data_init(struct discord_resolved_data *)`
 *   * Cleanup:

 *     * :code:`void discord_resolved_data_cleanup(struct discord_resolved_data *)`
 *     * :code:`void discord_resolved_data_list_free(struct discord_resolved_data **)`
 *   * JSON Decoder:

 *     * :code:`void discord_resolved_data_from_json(char *rbuf, size_t len, struct discord_resolved_data **)`
 *     * :code:`void discord_resolved_data_list_from_json(char *rbuf, size_t len, struct discord_resolved_data ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_resolved_data_to_json(char *wbuf, size_t len, struct discord_resolved_data *)`
 *     * :code:`void discord_resolved_data_list_to_json(char *wbuf, size_t len, struct discord_resolved_data **)`
 * @endverbatim
 */
struct discord_resolved_data {
  /* specs/discord/interaction.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
  ja_str **users; /**< the ids and User objects */

  /* specs/discord/interaction.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
  ja_str **members; /**< the ids and partial Member objects */

  /* specs/discord/interaction.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
  ja_str **roles; /**< the ids and Role objects */

  /* specs/discord/interaction.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
  ja_str **channels; /**< the ids and partial Channel objects */

  /* specs/discord/interaction.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */
  ja_str **messages; /**< the ids and partial Message objects */

};

/* Message Interaction Structure */
/* defined at specs/discord/interaction.json:71:22 */
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#message-interaction-object-message-interaction-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_interaction_init(struct discord_message_interaction *)`
 *   * Cleanup:

 *     * :code:`void discord_message_interaction_cleanup(struct discord_message_interaction *)`
 *     * :code:`void discord_message_interaction_list_free(struct discord_message_interaction **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_interaction_from_json(char *rbuf, size_t len, struct discord_message_interaction **)`
 *     * :code:`void discord_message_interaction_list_from_json(char *rbuf, size_t len, struct discord_message_interaction ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_interaction_to_json(char *wbuf, size_t len, struct discord_message_interaction *)`
 *     * :code:`void discord_message_interaction_list_to_json(char *wbuf, size_t len, struct discord_message_interaction **)`
 * @endverbatim
 */
struct discord_message_interaction {
  /* specs/discord/interaction.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  u64_snowflake_t id; /**< id of the interaction */

  /* specs/discord/interaction.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
  enum discord_interaction_types type; /**< the request type of the interaction */

  /* specs/discord/interaction.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
  char *name; /**< the name of the application command */

  /* specs/discord/interaction.json:77:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
  struct discord_user *user; /**< the user who invoked the interaction */

};

/* Interaction Response Structure */
/* defined at specs/discord/interaction.json:84:22 */
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-response-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_interaction_response_init(struct discord_interaction_response *)`
 *   * Cleanup:

 *     * :code:`void discord_interaction_response_cleanup(struct discord_interaction_response *)`
 *     * :code:`void discord_interaction_response_list_free(struct discord_interaction_response **)`
 *   * JSON Decoder:

 *     * :code:`void discord_interaction_response_from_json(char *rbuf, size_t len, struct discord_interaction_response **)`
 *     * :code:`void discord_interaction_response_list_from_json(char *rbuf, size_t len, struct discord_interaction_response ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_interaction_response_to_json(char *wbuf, size_t len, struct discord_interaction_response *)`
 *     * :code:`void discord_interaction_response_list_to_json(char *wbuf, size_t len, struct discord_interaction_response **)`
 * @endverbatim
 */
struct discord_interaction_response {
  /* specs/discord/interaction.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
  enum discord_interaction_callback_types type; /**< the type of response */

  /* specs/discord/interaction.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  struct discord_interaction_callback_data *data; /**< an optional response message */

};



/* Interaction Callback Data Structure */
/* defined at specs/discord/interaction.json:109:22 */
/**
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_interaction_callback_data_init(struct discord_interaction_callback_data *)`
 *   * Cleanup:

 *     * :code:`void discord_interaction_callback_data_cleanup(struct discord_interaction_callback_data *)`
 *     * :code:`void discord_interaction_callback_data_list_free(struct discord_interaction_callback_data **)`
 *   * JSON Decoder:

 *     * :code:`void discord_interaction_callback_data_from_json(char *rbuf, size_t len, struct discord_interaction_callback_data **)`
 *     * :code:`void discord_interaction_callback_data_list_from_json(char *rbuf, size_t len, struct discord_interaction_callback_data ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_interaction_callback_data_to_json(char *wbuf, size_t len, struct discord_interaction_callback_data *)`
 *     * :code:`void discord_interaction_callback_data_list_to_json(char *wbuf, size_t len, struct discord_interaction_callback_data **)`
 * @endverbatim
 */
struct discord_interaction_callback_data {
  /* specs/discord/interaction.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
  bool tts; /**< is the response TTS */

  /* specs/discord/interaction.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
  char *content; /**< message content */

  /* specs/discord/interaction.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
  struct discord_embed **embeds; /**< support up to 10 embeds */

  /* specs/discord/interaction.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null}' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions object */

  /* specs/discord/interaction.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
  enum discord_interaction_callback_data_flags flags; /**< interaction application command callback data flags */

  /* specs/discord/interaction.json:117:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
  struct discord_component **components; /**< message components */

  /* specs/discord/interaction.json:118:19
     '{"name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null}' */
  struct discord_attachment **attachments; /**< attachment objects with filename and description */

};


/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */

/* Get Invite */
/* defined at specs/discord/invite.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_invite_params_init(struct discord_get_invite_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_invite_params_cleanup(struct discord_get_invite_params *)`
 *     * :code:`void discord_get_invite_params_list_free(struct discord_get_invite_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_invite_params_from_json(char *rbuf, size_t len, struct discord_get_invite_params **)`
 *     * :code:`void discord_get_invite_params_list_from_json(char *rbuf, size_t len, struct discord_get_invite_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_invite_params_to_json(char *wbuf, size_t len, struct discord_get_invite_params *)`
 *     * :code:`void discord_get_invite_params_list_to_json(char *wbuf, size_t len, struct discord_get_invite_params **)`
 * @endverbatim
 */
struct discord_get_invite_params {
  /* specs/discord/invite.endpoints-params.json:12:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */
  bool with_counts; /**< whether the invite should contain approximate member counts */

  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */
  bool with_expiration; /**< whether the invite should contain the expiration date */

};
/* This file is generated from specs/discord/invite.json, Please don't edit it. */



/* Invite Structure */
/* defined at specs/discord/invite.json:19:22 */
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-object-invite-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_invite_init(struct discord_invite *)`
 *   * Cleanup:

 *     * :code:`void discord_invite_cleanup(struct discord_invite *)`
 *     * :code:`void discord_invite_list_free(struct discord_invite **)`
 *   * JSON Decoder:

 *     * :code:`void discord_invite_from_json(char *rbuf, size_t len, struct discord_invite **)`
 *     * :code:`void discord_invite_list_from_json(char *rbuf, size_t len, struct discord_invite ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_invite_to_json(char *wbuf, size_t len, struct discord_invite *)`
 *     * :code:`void discord_invite_list_to_json(char *wbuf, size_t len, struct discord_invite **)`
 * @endverbatim
 */
struct discord_invite {
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */
  char *code;

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  struct discord_guild *guild; /**< partial guild object */

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  struct discord_channel *channel; /**< partial channel object */

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  struct discord_user *inviter;

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  struct discord_user *target_user; /**< partial user object */

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
  enum discord_invite_target_user_types target_user_type;

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
  int approximate_presence_count;

  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
  int approximate_member_count;

};

/* Invite Metadata Structure */
/* defined at specs/discord/invite.json:36:22 */
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-metadata-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_invite_metadata_init(struct discord_invite_metadata *)`
 *   * Cleanup:

 *     * :code:`void discord_invite_metadata_cleanup(struct discord_invite_metadata *)`
 *     * :code:`void discord_invite_metadata_list_free(struct discord_invite_metadata **)`
 *   * JSON Decoder:

 *     * :code:`void discord_invite_metadata_from_json(char *rbuf, size_t len, struct discord_invite_metadata **)`
 *     * :code:`void discord_invite_metadata_list_from_json(char *rbuf, size_t len, struct discord_invite_metadata ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_invite_metadata_to_json(char *wbuf, size_t len, struct discord_invite_metadata *)`
 *     * :code:`void discord_invite_metadata_list_to_json(char *wbuf, size_t len, struct discord_invite_metadata **)`
 * @endverbatim
 */
struct discord_invite_metadata {
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
  int user;

  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  int max_uses;

  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  int max_age;

  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
  int temporary;

  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  u64_unix_ms_t created_at;

};
/* This file is generated from specs/discord/message_components.json, Please don't edit it. */

/* Component Structure */
/* defined at specs/discord/message_components.json:9:22 */
/**
 * @see https://discord.com/developers/docs/interactions/message-components#component-object-component-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_component_init(struct discord_component *)`
 *   * Cleanup:

 *     * :code:`void discord_component_cleanup(struct discord_component *)`
 *     * :code:`void discord_component_list_free(struct discord_component **)`
 *   * JSON Decoder:

 *     * :code:`void discord_component_from_json(char *rbuf, size_t len, struct discord_component **)`
 *     * :code:`void discord_component_list_from_json(char *rbuf, size_t len, struct discord_component ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_component_to_json(char *wbuf, size_t len, struct discord_component *)`
 *     * :code:`void discord_component_list_to_json(char *wbuf, size_t len, struct discord_component **)`
 * @endverbatim
 */
struct discord_component {
  /* specs/discord/message_components.json:12:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment":"component type"}' */
  enum discord_component_types type; /**< component type */

  /* specs/discord/message_components.json:13:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "inject_if_not":"", "comment":"a developer-defined identifier for the component, max 100 characters"}' */
  char custom_id[100+1]; /**< a developer-defined identifier for the component, max 100 characters */

  /* specs/discord/message_components.json:14:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"whether the component is disabled, default false"}' */
  bool disabled; /**< whether the component is disabled, default false */

  /* specs/discord/message_components.json:15:18
     '{"name":"style", "type":{"base":"int", "int_alias":"enum discord_button_styles"}, "option":true, "inject_if_not":0, "comment":"one of button styles"}' */
  enum discord_button_styles style; /**< one of button styles */

  /* specs/discord/message_components.json:16:18
     '{"name":"label", "type":{"base":"char", "dec":"[80+1]"}, "option":true, "comment":"text that appears on the button, max 80 characters", "inject_if_not":""}' */
  char label[80+1]; /**< text that appears on the button, max 80 characters */

  /* specs/discord/message_components.json:17:18
     '{"name":"emoji", "type":{"base":"struct discord_emoji", "dec":"*"}, "option":true, "comment":"name, id and animated", "inject_if_not":null}' */
  struct discord_emoji *emoji; /**< name, id and animated */

  /* specs/discord/message_components.json:18:18
     '{"name":"url", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a url for link-style buttons", "inject_if_not":null}' */
  char *url; /**< a url for link-style buttons */

  /* specs/discord/message_components.json:19:18
     '{"name":"options", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the choices in the select, max 25", "inject_if_not":null}' */
  struct discord_select_option **options; /**< the choices in the select, max 25 */

  /* specs/discord/message_components.json:20:18
     '{"name":"placeholder", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"custom placeholder text if nothing is selected, max 100 characters", "inject_if_not":""}' */
  char placeholder[100+1]; /**< custom placeholder text if nothing is selected, max 100 characters */

  /* specs/discord/message_components.json:21:18
     '{"name":"min_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the minimum number of items that must be chosen; default 1, min 0, max 25"}' */
  int min_values; /**< the minimum number of items that must be chosen; default 1, min 0, max 25 */

  /* specs/discord/message_components.json:22:18
     '{"name":"max_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the maximum number of items that must be chosen; default 1, min 0, max 25"}' */
  int max_values; /**< the maximum number of items that must be chosen; default 1, min 0, max 25 */

  /* specs/discord/message_components.json:23:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"a list of child components", "inject_if_not":null}' */
  struct discord_component **components; /**< a list of child components */

};



/* Button Structure */
/* defined at specs/discord/message_components.json:41:22 */
/**
 * @see https://discord.com/developers/docs/interactions/message-components#button-object-button-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_button_init(struct discord_button *)`
 *   * Cleanup:

 *     * :code:`void discord_button_cleanup(struct discord_button *)`
 *     * :code:`void discord_button_list_free(struct discord_button **)`
 *   * JSON Decoder:

 *     * :code:`void discord_button_from_json(char *rbuf, size_t len, struct discord_button **)`
 *     * :code:`void discord_button_list_from_json(char *rbuf, size_t len, struct discord_button ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_button_to_json(char *wbuf, size_t len, struct discord_button *)`
 *     * :code:`void discord_button_list_to_json(char *wbuf, size_t len, struct discord_button **)`
 * @endverbatim
 */
struct discord_button {
  /* specs/discord/message_components.json:44:18
     '{"name":"type", "type": {"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment": "2 for a button"}' */
  enum discord_component_types type; /**< 2 for a button */

  /* specs/discord/message_components.json:45:18
     '{"name":"style", "type": {"base":"int", "int_alias":"enum discord_button_styles"}, "inject_if_not":0, "comment": "one of button styles"}' */
  enum discord_button_styles style; /**< one of button styles */

  /* specs/discord/message_components.json:46:18
     '{"name":"label", "type":{"base":"char", "dec":"[80+1]"}, "option":true, "comment":"text that appears on the button, max 80 characters", "inject_if_not":""}' */
  char label[80+1]; /**< text that appears on the button, max 80 characters */

  /* specs/discord/message_components.json:47:18
     '{"name":"emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "option":true, "comment":"name, id and animated", "inject_if_not":null}' */
  struct discord_emoji *emoji; /**< name, id and animated */

  /* specs/discord/message_components.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"a developer-defined identifier for the component, max 100 characters", "inject_if_not":""}' */
  char custom_id[100+1]; /**< a developer-defined identifier for the component, max 100 characters */

  /* specs/discord/message_components.json:49:18
     '{"name":"url", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a url for link-style buttons", "inject_if_not":null}' */
  char *url; /**< a url for link-style buttons */

  /* specs/discord/message_components.json:50:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"whether the component is disabled, default false"}' */
  bool disabled; /**< whether the component is disabled, default false */

};



/* Select Menu Structure */
/* defined at specs/discord/message_components.json:70:22 */
/**
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-menu-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_select_menu_init(struct discord_select_menu *)`
 *   * Cleanup:

 *     * :code:`void discord_select_menu_cleanup(struct discord_select_menu *)`
 *     * :code:`void discord_select_menu_list_free(struct discord_select_menu **)`
 *   * JSON Decoder:

 *     * :code:`void discord_select_menu_from_json(char *rbuf, size_t len, struct discord_select_menu **)`
 *     * :code:`void discord_select_menu_list_from_json(char *rbuf, size_t len, struct discord_select_menu ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_select_menu_to_json(char *wbuf, size_t len, struct discord_select_menu *)`
 *     * :code:`void discord_select_menu_list_to_json(char *wbuf, size_t len, struct discord_select_menu **)`
 * @endverbatim
 */
struct discord_select_menu {
  /* specs/discord/message_components.json:73:18
     '{"name":"type", "type": {"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment": "3 for a select menu"}' */
  enum discord_component_types type; /**< 3 for a select menu */

  /* specs/discord/message_components.json:74:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters", "inject_if_not":""}' */
  char custom_id[100+1]; /**< a developer-defined identifier for the component, max 100 characters */

  /* specs/discord/message_components.json:75:18
     '{"name":"options", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "comment":"the choices in the select, max 25"}' */
  struct discord_select_option **options; /**< the choices in the select, max 25 */

  /* specs/discord/message_components.json:76:18
     '{"name":"placeholder", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"custom placeholder text if nothing is selected, max 100 characters", "inject_if_not":""}' */
  char placeholder[100+1]; /**< custom placeholder text if nothing is selected, max 100 characters */

  /* specs/discord/message_components.json:77:18
     '{"name":"min_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the minimum number of items that must be chosen; default 1, min 0, max 25"}' */
  int min_values; /**< the minimum number of items that must be chosen; default 1, min 0, max 25 */

  /* specs/discord/message_components.json:78:18
     '{"name":"max_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the maximum number of items that must be chosen; default 1, min 0, max 25"}' */
  int max_values; /**< the maximum number of items that must be chosen; default 1, min 0, max 25 */

  /* specs/discord/message_components.json:79:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"disable the select, default false"}' */
  bool disabled; /**< disable the select, default false */

};

/* Select Option Structure */
/* defined at specs/discord/message_components.json:85:22 */
/**
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-option-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_select_option_init(struct discord_select_option *)`
 *   * Cleanup:

 *     * :code:`void discord_select_option_cleanup(struct discord_select_option *)`
 *     * :code:`void discord_select_option_list_free(struct discord_select_option **)`
 *   * JSON Decoder:

 *     * :code:`void discord_select_option_from_json(char *rbuf, size_t len, struct discord_select_option **)`
 *     * :code:`void discord_select_option_list_from_json(char *rbuf, size_t len, struct discord_select_option ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_select_option_to_json(char *wbuf, size_t len, struct discord_select_option *)`
 *     * :code:`void discord_select_option_list_to_json(char *wbuf, size_t len, struct discord_select_option **)`
 * @endverbatim
 */
struct discord_select_option {
  /* specs/discord/message_components.json:88:18
     '{"name":"label", "type":{"base":"char", "dec":"[25+1]"}, "inject_if_not":"", "comment":"the user-facing name of the option, max 25 characters"}' */
  char label[25+1]; /**< the user-facing name of the option, max 25 characters */

  /* specs/discord/message_components.json:89:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "inject_if_not":"", "comment":"the dev define value of the option, max 100 characters"}' */
  char value[100+1]; /**< the dev define value of the option, max 100 characters */

  /* specs/discord/message_components.json:90:18
     '{"name":"description", "type":{"base":"char", "dec":"[50+1]"}, "inject_if_not":"", "option":true, "comment":"a additional description of the option, max 50 characters"}' */
  char description[50+1]; /**< a additional description of the option, max 50 characters */

  /* specs/discord/message_components.json:91:18
     '{"name":"emoji", "type":{"base":"struct discord_emoji", "dec":"*"}, "inject_if_not":null, "option":true, "comment":"name, id and animated"}' */
  struct discord_emoji *emoji; /**< name, id and animated */

  /* specs/discord/message_components.json:92:18
     '{"name":"Default", "json_key":"default", "type":{"base":"bool"}, "option":true, "comment":"will render this option as selected by default"}' */
  bool Default; /**< will render this option as selected by default */

};
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */



/* Role Structure */
/* defined at specs/discord/permissions.json:50:22 */
/**
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_role_init(struct discord_role *)`
 *   * Cleanup:

 *     * :code:`void discord_role_cleanup(struct discord_role *)`
 *     * :code:`void discord_role_list_free(struct discord_role **)`
 *   * JSON Decoder:

 *     * :code:`void discord_role_from_json(char *rbuf, size_t len, struct discord_role **)`
 *     * :code:`void discord_role_list_from_json(char *rbuf, size_t len, struct discord_role ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_role_to_json(char *wbuf, size_t len, struct discord_role *)`
 *     * :code:`void discord_role_list_to_json(char *wbuf, size_t len, struct discord_role **)`
 * @endverbatim
 */
struct discord_role {
  /* specs/discord/permissions.json:53:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/permissions.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/permissions.json:55:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  int color;

  /* specs/discord/permissions.json:56:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  bool hoist;

  /* specs/discord/permissions.json:57:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  int position;

  /* specs/discord/permissions.json:58:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  char *permissions;

  /* specs/discord/permissions.json:59:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  bool managed;

  /* specs/discord/permissions.json:60:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  bool mentionable;

  /* specs/discord/permissions.json:61:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
  struct discord_role_tags *tags;

};

/* Role Tags Structure */
/* defined at specs/discord/permissions.json:68:22 */
/**
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-tags-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_role_tags_init(struct discord_role_tags *)`
 *   * Cleanup:

 *     * :code:`void discord_role_tags_cleanup(struct discord_role_tags *)`
 *     * :code:`void discord_role_tags_list_free(struct discord_role_tags **)`
 *   * JSON Decoder:

 *     * :code:`void discord_role_tags_from_json(char *rbuf, size_t len, struct discord_role_tags **)`
 *     * :code:`void discord_role_tags_list_from_json(char *rbuf, size_t len, struct discord_role_tags ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_role_tags_to_json(char *wbuf, size_t len, struct discord_role_tags *)`
 *     * :code:`void discord_role_tags_list_to_json(char *wbuf, size_t len, struct discord_role_tags **)`
 * @endverbatim
 */
struct discord_role_tags {
  /* specs/discord/permissions.json:71:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t bot_id;

  /* specs/discord/permissions.json:72:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t integration_id;

  /* specs/discord/permissions.json:73:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  int premium_subscriber;

};
/* This file is generated from specs/discord/stage-instance.endpoints-params.json, Please don't edit it. */

/* Create Stage Instance */
/* defined at specs/discord/stage-instance.endpoints-params.json:8:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_stage_instance_params_init(struct discord_create_stage_instance_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_stage_instance_params_cleanup(struct discord_create_stage_instance_params *)`
 *     * :code:`void discord_create_stage_instance_params_list_free(struct discord_create_stage_instance_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_stage_instance_params_from_json(char *rbuf, size_t len, struct discord_create_stage_instance_params **)`
 *     * :code:`void discord_create_stage_instance_params_list_from_json(char *rbuf, size_t len, struct discord_create_stage_instance_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_stage_instance_params_to_json(char *wbuf, size_t len, struct discord_create_stage_instance_params *)`
 *     * :code:`void discord_create_stage_instance_params_list_to_json(char *wbuf, size_t len, struct discord_create_stage_instance_params **)`
 * @endverbatim
 */
struct discord_create_stage_instance_params {
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */
  u64_snowflake_t channel_id; /**< The id of the Stage channel */

  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  char *topic; /**< The topic of the Stage instance (1-120 characters) */

  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
  enum discord_stage_instance_privacy_level privacy_level;

};

/* Modify Stage Instance */
/* defined at specs/discord/stage-instance.endpoints-params.json:19:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_stage_instance_params_init(struct discord_modify_stage_instance_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_stage_instance_params_cleanup(struct discord_modify_stage_instance_params *)`
 *     * :code:`void discord_modify_stage_instance_params_list_free(struct discord_modify_stage_instance_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_stage_instance_params_from_json(char *rbuf, size_t len, struct discord_modify_stage_instance_params **)`
 *     * :code:`void discord_modify_stage_instance_params_list_from_json(char *rbuf, size_t len, struct discord_modify_stage_instance_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_stage_instance_params_to_json(char *wbuf, size_t len, struct discord_modify_stage_instance_params *)`
 *     * :code:`void discord_modify_stage_instance_params_list_to_json(char *wbuf, size_t len, struct discord_modify_stage_instance_params **)`
 * @endverbatim
 */
struct discord_modify_stage_instance_params {
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  char *topic; /**< The topic of the Stage instance (1-120 characters) */

  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
  enum discord_stage_instance_privacy_level privacy_level;

};
/* This file is generated from specs/discord/stage-instance.json, Please don't edit it. */



/* Stage Instance Structure */
/* defined at specs/discord/stage-instance.json:17:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_stage_instance_init(struct discord_stage_instance *)`
 *   * Cleanup:

 *     * :code:`void discord_stage_instance_cleanup(struct discord_stage_instance *)`
 *     * :code:`void discord_stage_instance_list_free(struct discord_stage_instance **)`
 *   * JSON Decoder:

 *     * :code:`void discord_stage_instance_from_json(char *rbuf, size_t len, struct discord_stage_instance **)`
 *     * :code:`void discord_stage_instance_list_from_json(char *rbuf, size_t len, struct discord_stage_instance ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_stage_instance_to_json(char *wbuf, size_t len, struct discord_stage_instance *)`
 *     * :code:`void discord_stage_instance_list_to_json(char *wbuf, size_t len, struct discord_stage_instance **)`
 * @endverbatim
 */
struct discord_stage_instance {
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */
  u64_snowflake_t id; /**< The id of this Stage instance */

  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */
  u64_snowflake_t guild_id; /**< The guild id of the associated Stage channel */

  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */
  u64_snowflake_t channel_id; /**< The id of the associated Stage channel */

  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  char *topic; /**< The topic of the Stage instance (1-120 characters) */

  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */
  enum discord_stage_instance_privacy_level privacy_level; /**< The privacy level of the Stage instance */

  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */
  bool discoverable_disabled;

};
/* This file is generated from specs/discord/sticker.endpoints-params.json, Please don't edit it. */

/* List Nitro Sticker Packs */
/* defined at specs/discord/sticker.endpoints-params.json:8:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_list_nitro_sticker_packs_response_init(struct discord_list_nitro_sticker_packs_response *)`
 *   * Cleanup:

 *     * :code:`void discord_list_nitro_sticker_packs_response_cleanup(struct discord_list_nitro_sticker_packs_response *)`
 *     * :code:`void discord_list_nitro_sticker_packs_response_list_free(struct discord_list_nitro_sticker_packs_response **)`
 *   * JSON Decoder:

 *     * :code:`void discord_list_nitro_sticker_packs_response_from_json(char *rbuf, size_t len, struct discord_list_nitro_sticker_packs_response **)`
 *     * :code:`void discord_list_nitro_sticker_packs_response_list_from_json(char *rbuf, size_t len, struct discord_list_nitro_sticker_packs_response ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_list_nitro_sticker_packs_response_to_json(char *wbuf, size_t len, struct discord_list_nitro_sticker_packs_response *)`
 *     * :code:`void discord_list_nitro_sticker_packs_response_list_to_json(char *wbuf, size_t len, struct discord_list_nitro_sticker_packs_response **)`
 * @endverbatim
 */
struct discord_list_nitro_sticker_packs_response {
  /* specs/discord/sticker.endpoints-params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */
  struct discord_sticker_pack **sticker_packs; /**< array of sticker pack objects */

};

/* Create Guild Sticker */
/* defined at specs/discord/sticker.endpoints-params.json:17:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_sticker_params_init(struct discord_create_guild_sticker_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_sticker_params_cleanup(struct discord_create_guild_sticker_params *)`
 *     * :code:`void discord_create_guild_sticker_params_list_free(struct discord_create_guild_sticker_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_sticker_params_from_json(char *rbuf, size_t len, struct discord_create_guild_sticker_params **)`
 *     * :code:`void discord_create_guild_sticker_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_sticker_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_sticker_params_to_json(char *wbuf, size_t len, struct discord_create_guild_sticker_params *)`
 *     * :code:`void discord_create_guild_sticker_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_sticker_params **)`
 * @endverbatim
 */
struct discord_create_guild_sticker_params {
  /* specs/discord/sticker.endpoints-params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
  char *name; /**< name of the sticker (2-30 characters) */

  /* specs/discord/sticker.endpoints-params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
  char *description; /**< description of the sticker (empty or 2-100 characters) */

  /* specs/discord/sticker.endpoints-params.json:22:18
     '{"name":"file", "type":{ "base":"struct discord_attachment", "dec":"*" }, "loc":"multipart", "comment":"the sticker file to upload, must be a PNG, APNG, or Lottie JSON file, max 500 KB"}' */
  struct discord_attachment *file; /**< the sticker file to upload, must be a PNG, APNG, or Lottie JSON file, max 500 KB */

  /* specs/discord/sticker.endpoints-params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  char *tags; /**< autocomplete/suggestion tags for the sticker (max 200 characters) */

};

/* Modify Guild Sticker */
/* defined at specs/discord/sticker.endpoints-params.json:29:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_sticker_params_init(struct discord_modify_guild_sticker_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_sticker_params_cleanup(struct discord_modify_guild_sticker_params *)`
 *     * :code:`void discord_modify_guild_sticker_params_list_free(struct discord_modify_guild_sticker_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_sticker_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_sticker_params **)`
 *     * :code:`void discord_modify_guild_sticker_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_sticker_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_sticker_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_sticker_params *)`
 *     * :code:`void discord_modify_guild_sticker_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_sticker_params **)`
 * @endverbatim
 */
struct discord_modify_guild_sticker_params {
  /* specs/discord/sticker.endpoints-params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
  char *name; /**< name of the sticker (2-30 characters) */

  /* specs/discord/sticker.endpoints-params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
  char *description; /**< description of the sticker (empty or 2-100 characters) */

  /* specs/discord/sticker.endpoints-params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  char *tags; /**< autocomplete/suggestion tags for the sticker (max 200 characters) */

};
/* This file is generated from specs/discord/sticker.json, Please don't edit it. */





/* Sticker Structure */
/* defined at specs/discord/sticker.json:28:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_sticker_init(struct discord_sticker *)`
 *   * Cleanup:

 *     * :code:`void discord_sticker_cleanup(struct discord_sticker *)`
 *     * :code:`void discord_sticker_list_free(struct discord_sticker **)`
 *   * JSON Decoder:

 *     * :code:`void discord_sticker_from_json(char *rbuf, size_t len, struct discord_sticker **)`
 *     * :code:`void discord_sticker_list_from_json(char *rbuf, size_t len, struct discord_sticker ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_sticker_to_json(char *wbuf, size_t len, struct discord_sticker *)`
 *     * :code:`void discord_sticker_list_to_json(char *wbuf, size_t len, struct discord_sticker **)`
 * @endverbatim
 */
struct discord_sticker {
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  u64_snowflake_t id; /**< id of the sticker */

  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
  u64_snowflake_t pack_id; /**< for standard stickers, id of the pack the sticker is from */

  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  char *name; /**< name of the sticker */

  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
  char *description; /**< description of the sticker */

  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  char *tags; /**< autocomplete/suggestion tags for the sticker (max 200 characters) */

  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
  char *asset; /**< Deprecated previously the sticker asset hash, now an empty string */

  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
  enum discord_sticker_types type; /**< type of sticker */

  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  enum discord_sticker_format_types format_type; /**< type of sticker format */

  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
  bool available; /**< whether this guild sticker can be used, may be false due to loss of Server Boosts */

  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
  u64_snowflake_t guild_id; /**< id of the guild that owns this sticker */

  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
  struct discord_user *user; /**< the user that uploaded the guild sticker */

  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
  int sort_value; /**< the standard sticker's sort order within its pack */

};

/* Sticker Item Structure */
/* defined at specs/discord/sticker.json:47:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_sticker_item_init(struct discord_sticker_item *)`
 *   * Cleanup:

 *     * :code:`void discord_sticker_item_cleanup(struct discord_sticker_item *)`
 *     * :code:`void discord_sticker_item_list_free(struct discord_sticker_item **)`
 *   * JSON Decoder:

 *     * :code:`void discord_sticker_item_from_json(char *rbuf, size_t len, struct discord_sticker_item **)`
 *     * :code:`void discord_sticker_item_list_from_json(char *rbuf, size_t len, struct discord_sticker_item ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_sticker_item_to_json(char *wbuf, size_t len, struct discord_sticker_item *)`
 *     * :code:`void discord_sticker_item_list_to_json(char *wbuf, size_t len, struct discord_sticker_item **)`
 * @endverbatim
 */
struct discord_sticker_item {
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  u64_snowflake_t id; /**< id of the sticker */

  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  char *name; /**< name of the sticker */

  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  enum discord_sticker_format_types format_type; /**< type of sticker format */

};

/* Sticker Pack Structure */
/* defined at specs/discord/sticker.json:57:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_sticker_pack_init(struct discord_sticker_pack *)`
 *   * Cleanup:

 *     * :code:`void discord_sticker_pack_cleanup(struct discord_sticker_pack *)`
 *     * :code:`void discord_sticker_pack_list_free(struct discord_sticker_pack **)`
 *   * JSON Decoder:

 *     * :code:`void discord_sticker_pack_from_json(char *rbuf, size_t len, struct discord_sticker_pack **)`
 *     * :code:`void discord_sticker_pack_list_from_json(char *rbuf, size_t len, struct discord_sticker_pack ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_sticker_pack_to_json(char *wbuf, size_t len, struct discord_sticker_pack *)`
 *     * :code:`void discord_sticker_pack_list_to_json(char *wbuf, size_t len, struct discord_sticker_pack **)`
 * @endverbatim
 */
struct discord_sticker_pack {
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
  u64_snowflake_t id; /**< id of the sticker pack */

  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
  struct discord_sticker **stickers; /**< the stickers in the pack */

  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
  char *name; /**< name of the sticker pack */

  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
  u64_snowflake_t sku_id; /**< id of the pack's SKU */

  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
  u64_snowflake_t cover_sticker_id; /**< id of a sticker in the pack which is shown as the pack's icon */

  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
  char *description; /**< description of the sticker pack */

  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
  u64_snowflake_t banner_asset_id; /**< id of the sticker pack's banner image */

};
/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */

/* Modify Current User */
/* defined at specs/discord/user.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_current_user_params_init(struct discord_modify_current_user_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_current_user_params_cleanup(struct discord_modify_current_user_params *)`
 *     * :code:`void discord_modify_current_user_params_list_free(struct discord_modify_current_user_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_current_user_params_from_json(char *rbuf, size_t len, struct discord_modify_current_user_params **)`
 *     * :code:`void discord_modify_current_user_params_list_from_json(char *rbuf, size_t len, struct discord_modify_current_user_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_current_user_params_to_json(char *wbuf, size_t len, struct discord_modify_current_user_params *)`
 *     * :code:`void discord_modify_current_user_params_list_to_json(char *wbuf, size_t len, struct discord_modify_current_user_params **)`
 * @endverbatim
 */
struct discord_modify_current_user_params {
  /* specs/discord/user.endpoints-params.json:12:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
  char *username;

  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
  char *avatar; /**< base64 encoded image data */

};

/* Create DM */
/* defined at specs/discord/user.endpoints-params.json:19:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_dm_params_init(struct discord_create_dm_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_dm_params_cleanup(struct discord_create_dm_params *)`
 *     * :code:`void discord_create_dm_params_list_free(struct discord_create_dm_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_dm_params_from_json(char *rbuf, size_t len, struct discord_create_dm_params **)`
 *     * :code:`void discord_create_dm_params_list_from_json(char *rbuf, size_t len, struct discord_create_dm_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_dm_params_to_json(char *wbuf, size_t len, struct discord_create_dm_params *)`
 *     * :code:`void discord_create_dm_params_list_to_json(char *wbuf, size_t len, struct discord_create_dm_params **)`
 * @endverbatim
 */
struct discord_create_dm_params {
  /* specs/discord/user.endpoints-params.json:22:20
     '{ "name": "recipient_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the recipient to open a DM channel with", "inject_if_not":0 }' */
  u64_snowflake_t recipient_id; /**< the recipient to open a DM channel with */

};

/* Create Group DM */
/* defined at specs/discord/user.endpoints-params.json:28:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_group_dm_params_init(struct discord_create_group_dm_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_group_dm_params_cleanup(struct discord_create_group_dm_params *)`
 *     * :code:`void discord_create_group_dm_params_list_free(struct discord_create_group_dm_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_group_dm_params_from_json(char *rbuf, size_t len, struct discord_create_group_dm_params **)`
 *     * :code:`void discord_create_group_dm_params_list_from_json(char *rbuf, size_t len, struct discord_create_group_dm_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_group_dm_params_to_json(char *wbuf, size_t len, struct discord_create_group_dm_params *)`
 *     * :code:`void discord_create_group_dm_params_list_to_json(char *wbuf, size_t len, struct discord_create_group_dm_params **)`
 * @endverbatim
 */
struct discord_create_group_dm_params {
  /* specs/discord/user.endpoints-params.json:31:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
  ja_str **access_tokens; /**< access tokens of users that have granted your app the gdm.join scope */

  /* specs/discord/user.endpoints-params.json:33:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"a dictionary of user ids to their respective nicknames"}' */
  ja_u64 **nicks; /**< a dictionary of user ids to their respective nicknames */

};
/* This file is generated from specs/discord/user.json, Please don't edit it. */





/* User Structure */
/* defined at specs/discord/user.json:41:28 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_user_init(struct discord_user *)`
 *   * Cleanup:

 *     * :code:`void discord_user_cleanup(struct discord_user *)`
 *     * :code:`void discord_user_list_free(struct discord_user **)`
 *   * JSON Decoder:

 *     * :code:`void discord_user_from_json(char *rbuf, size_t len, struct discord_user **)`
 *     * :code:`void discord_user_list_from_json(char *rbuf, size_t len, struct discord_user ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_user_to_json(char *wbuf, size_t len, struct discord_user *)`
 *     * :code:`void discord_user_list_to_json(char *wbuf, size_t len, struct discord_user **)`
 * @endverbatim
 */
struct discord_user {
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t id;

  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
  char *username;

  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
  char *discriminator;

  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  char avatar[ORCA_LIMITS_SHA256];

  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
  bool bot;

  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
  bool System;

  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
  bool mfa_enabled;

  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */
  char locale[ORCA_LIMITS_LOCALE];

  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  bool verified;

  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */
  char email[ORCA_LIMITS_EMAIL];

  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  enum discord_user_flags flags;

  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  char banner[ORCA_LIMITS_SHA256];

  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
  enum discord_user_premium_types premium_type;

  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  enum discord_user_flags public_flags;

};



/* Connection Structure */
/* defined at specs/discord/user.json:74:28 */
/**
 * @see https://discord.com/developers/docs/resources/user#connection-object-connection-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_connection_init(struct discord_connection *)`
 *   * Cleanup:

 *     * :code:`void discord_connection_cleanup(struct discord_connection *)`
 *     * :code:`void discord_connection_list_free(struct discord_connection **)`
 *   * JSON Decoder:

 *     * :code:`void discord_connection_from_json(char *rbuf, size_t len, struct discord_connection **)`
 *     * :code:`void discord_connection_list_from_json(char *rbuf, size_t len, struct discord_connection ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_connection_to_json(char *wbuf, size_t len, struct discord_connection *)`
 *     * :code:`void discord_connection_list_to_json(char *wbuf, size_t len, struct discord_connection **)`
 * @endverbatim
 */
struct discord_connection {
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  char *id;

  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  char *type;

  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  bool revoked;

  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
  struct discord_integration **integrations;

  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  bool verified;

  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
  bool friend_sync;

  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
  bool show_activity;

  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
  enum discord_visibility_types visibility;

};
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */






/* This file is generated from specs/discord/voice.json, Please don't edit it. */

/* Voice State Structure */
/* defined at specs/discord/voice.json:10:22 */
/**
 * @see https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_voice_state_init(struct discord_voice_state *)`
 *   * Cleanup:

 *     * :code:`void discord_voice_state_cleanup(struct discord_voice_state *)`
 *     * :code:`void discord_voice_state_list_free(struct discord_voice_state **)`
 *   * JSON Decoder:

 *     * :code:`void discord_voice_state_from_json(char *rbuf, size_t len, struct discord_voice_state **)`
 *     * :code:`void discord_voice_state_list_from_json(char *rbuf, size_t len, struct discord_voice_state ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_voice_state_to_json(char *wbuf, size_t len, struct discord_voice_state *)`
 *     * :code:`void discord_voice_state_list_to_json(char *wbuf, size_t len, struct discord_voice_state **)`
 * @endverbatim
 */
struct discord_voice_state {
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t guild_id;

  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t channel_id;

  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t user_id;

  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
  struct discord_guild_member *member;

  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
  char *session_id;

  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  bool deaf;

  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  bool mute;

  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
  bool self_deaf;

  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
  bool self_mute;

  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
  bool self_stream;

  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
  bool self_video;

  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
  bool supress;

};

/* Voice Region Structure */
/* defined at specs/discord/voice.json:31:22 */
/**
 * @see https://discord.com/developers/docs/resources/voice#voice-region-object-voice-region-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_voice_region_init(struct discord_voice_region *)`
 *   * Cleanup:

 *     * :code:`void discord_voice_region_cleanup(struct discord_voice_region *)`
 *     * :code:`void discord_voice_region_list_free(struct discord_voice_region **)`
 *   * JSON Decoder:

 *     * :code:`void discord_voice_region_from_json(char *rbuf, size_t len, struct discord_voice_region **)`
 *     * :code:`void discord_voice_region_list_from_json(char *rbuf, size_t len, struct discord_voice_region ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_voice_region_to_json(char *wbuf, size_t len, struct discord_voice_region *)`
 *     * :code:`void discord_voice_region_list_to_json(char *wbuf, size_t len, struct discord_voice_region **)`
 * @endverbatim
 */
struct discord_voice_region {
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  char *id;

  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
  bool vip;

  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
  bool optimal;

  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
  bool deprecated;

  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
  bool custom;

};
/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */

/* Create Webhook */
/* defined at specs/discord/webhook.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_webhook_params_init(struct discord_create_webhook_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *)`
 *     * :code:`void discord_create_webhook_params_list_free(struct discord_create_webhook_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_webhook_params_from_json(char *rbuf, size_t len, struct discord_create_webhook_params **)`
 *     * :code:`void discord_create_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_create_webhook_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_webhook_params_to_json(char *wbuf, size_t len, struct discord_create_webhook_params *)`
 *     * :code:`void discord_create_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_create_webhook_params **)`
 * @endverbatim
 */
struct discord_create_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  char *name; /**< name of the webhook(1-80) chars */

  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; /**< base64 image for the default webhook avatar */

};

/* Modify Webhook */
/* defined at specs/discord/webhook.endpoints-params.json:19:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_webhook_params_init(struct discord_modify_webhook_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *)`
 *     * :code:`void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_webhook_params_from_json(char *rbuf, size_t len, struct discord_modify_webhook_params **)`
 *     * :code:`void discord_modify_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_modify_webhook_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_webhook_params_to_json(char *wbuf, size_t len, struct discord_modify_webhook_params *)`
 *     * :code:`void discord_modify_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_modify_webhook_params **)`
 * @endverbatim
 */
struct discord_modify_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
  char *name; /**< name of the webhook(1-80) chars */

  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; /**< base64 image for the default webhook avatar */

  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */
  u64_snowflake_t channel_id; /**< the new channel id this webhook should be moved to */

};

/* Modify Webhook with Token */
/* defined at specs/discord/webhook.endpoints-params.json:30:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_webhook_with_token_params_init(struct discord_modify_webhook_with_token_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_webhook_with_token_params_cleanup(struct discord_modify_webhook_with_token_params *)`
 *     * :code:`void discord_modify_webhook_with_token_params_list_free(struct discord_modify_webhook_with_token_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_webhook_with_token_params_from_json(char *rbuf, size_t len, struct discord_modify_webhook_with_token_params **)`
 *     * :code:`void discord_modify_webhook_with_token_params_list_from_json(char *rbuf, size_t len, struct discord_modify_webhook_with_token_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_webhook_with_token_params_to_json(char *wbuf, size_t len, struct discord_modify_webhook_with_token_params *)`
 *     * :code:`void discord_modify_webhook_with_token_params_list_to_json(char *wbuf, size_t len, struct discord_modify_webhook_with_token_params **)`
 * @endverbatim
 */
struct discord_modify_webhook_with_token_params {
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
  char *name; /**< name of the webhook(1-80) chars */

  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; /**< base64 image for the default webhook avatar */

};

/* Execute Webhook */
/* defined at specs/discord/webhook.endpoints-params.json:40:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_execute_webhook_params_init(struct discord_execute_webhook_params *)`
 *   * Cleanup:

 *     * :code:`void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *)`
 *     * :code:`void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_execute_webhook_params_from_json(char *rbuf, size_t len, struct discord_execute_webhook_params **)`
 *     * :code:`void discord_execute_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_execute_webhook_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_execute_webhook_params_to_json(char *wbuf, size_t len, struct discord_execute_webhook_params *)`
 *     * :code:`void discord_execute_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_execute_webhook_params **)`
 * @endverbatim
 */
struct discord_execute_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:44:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)" }' */
  bool wait; /**< cannot unescape an ill-formed-string 	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that i */

  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  u64_snowflake_t thread_id; /**< Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived */

  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  char *username; /**< override the default username of the webhook */

  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  char *avatar_url; /**< override the default avatar of the webhook */

  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  bool tts; /**< true if this is a TTS message */

  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  struct discord_embed *embeds; /**< embedded rich content */

  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  struct discord_component **components; /**< the components to include with the message */

  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

};

/* Edit Webhook Message */
/* defined at specs/discord/webhook.endpoints-params.json:59:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *)`
 *     * :code:`void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_webhook_message_params_from_json(char *rbuf, size_t len, struct discord_edit_webhook_message_params **)`
 *     * :code:`void discord_edit_webhook_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_webhook_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_webhook_message_params_to_json(char *wbuf, size_t len, struct discord_edit_webhook_message_params *)`
 *     * :code:`void discord_edit_webhook_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_webhook_message_params **)`
 * @endverbatim
 */
struct discord_edit_webhook_message_params {
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  char *content; /**< name of the webhook(1-2000) chars */

  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< array of up to 10 embeds objects */

  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};
/* This file is generated from specs/discord/webhook.json, Please don't edit it. */

/* Webhook Structure */
/* defined at specs/discord/webhook.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_webhook_init(struct discord_webhook *)`
 *   * Cleanup:

 *     * :code:`void discord_webhook_cleanup(struct discord_webhook *)`
 *     * :code:`void discord_webhook_list_free(struct discord_webhook **)`
 *   * JSON Decoder:

 *     * :code:`void discord_webhook_from_json(char *rbuf, size_t len, struct discord_webhook **)`
 *     * :code:`void discord_webhook_list_from_json(char *rbuf, size_t len, struct discord_webhook ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_webhook_to_json(char *wbuf, size_t len, struct discord_webhook *)`
 *     * :code:`void discord_webhook_list_to_json(char *wbuf, size_t len, struct discord_webhook **)`
 * @endverbatim
 */
struct discord_webhook {
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */
  u64_snowflake_t id; /**< the id of the webhook */

  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */
  enum discord_webhook_types type; /**< the type of the webhook */

  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */
  u64_snowflake_t guild_id; /**< the guild id this webhook is for, if any */

  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */
  u64_snowflake_t channel_id; /**< the channel id this webhook is for, if any */

  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */
  struct discord_user *user; /**< the user this webhook was created by (not returned when getting a webhook with its token */

  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */
  char *name;

  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */
  char *avatar; /**< the default user avatar has of the webhook */

  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */
  char *token; /**< the secure token of the webhook (returned for Incoming Webhooks) */

  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */
  u64_snowflake_t application_id; /**< the bot/OAuth2 application that created this webhook */

  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */
  struct discord_guild *source_guild; /**< the guild of the channel that this webhook is following (returned for Channel Follower Webhook) */

  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */
  struct discord_channel *source_channel; /**< the channel that this webhook is following (returned for Channel Follower Webhooks) */

  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */
  char *url; /**< the url used for executing the webhook (returned by the webhooks OAuth2 flow) */

};


/* This file is generated from specs/discord/application.json, Please don't edit it. */

extern void discord_application_cleanup_v(void *p);
extern void discord_application_cleanup(struct discord_application *p);
extern void discord_application_init_v(void *p);
extern void discord_application_init(struct discord_application *p);
extern void discord_application_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_from_json(char *json, size_t len, struct discord_application **pp);
extern size_t discord_application_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_to_json(char *json, size_t len, struct discord_application *p);
extern void discord_application_list_free_v(void **p);
extern void discord_application_list_free(struct discord_application **p);
extern void discord_application_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_list_from_json(char *str, size_t len, struct discord_application ***p);
extern size_t discord_application_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_list_to_json(char *str, size_t len, struct discord_application **p);


/* This file is generated from specs/discord/application_commands.endpoints-params.json, Please don't edit it. */

extern void discord_create_global_application_command_params_cleanup_v(void *p);
extern void discord_create_global_application_command_params_cleanup(struct discord_create_global_application_command_params *p);
extern void discord_create_global_application_command_params_init_v(void *p);
extern void discord_create_global_application_command_params_init(struct discord_create_global_application_command_params *p);
extern void discord_create_global_application_command_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_global_application_command_params_from_json(char *json, size_t len, struct discord_create_global_application_command_params **pp);
extern size_t discord_create_global_application_command_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_global_application_command_params_to_json(char *json, size_t len, struct discord_create_global_application_command_params *p);
extern void discord_create_global_application_command_params_list_free_v(void **p);
extern void discord_create_global_application_command_params_list_free(struct discord_create_global_application_command_params **p);
extern void discord_create_global_application_command_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_global_application_command_params_list_from_json(char *str, size_t len, struct discord_create_global_application_command_params ***p);
extern size_t discord_create_global_application_command_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_global_application_command_params_list_to_json(char *str, size_t len, struct discord_create_global_application_command_params **p);

extern void discord_edit_global_application_command_params_cleanup_v(void *p);
extern void discord_edit_global_application_command_params_cleanup(struct discord_edit_global_application_command_params *p);
extern void discord_edit_global_application_command_params_init_v(void *p);
extern void discord_edit_global_application_command_params_init(struct discord_edit_global_application_command_params *p);
extern void discord_edit_global_application_command_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_global_application_command_params_from_json(char *json, size_t len, struct discord_edit_global_application_command_params **pp);
extern size_t discord_edit_global_application_command_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_global_application_command_params_to_json(char *json, size_t len, struct discord_edit_global_application_command_params *p);
extern void discord_edit_global_application_command_params_list_free_v(void **p);
extern void discord_edit_global_application_command_params_list_free(struct discord_edit_global_application_command_params **p);
extern void discord_edit_global_application_command_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_global_application_command_params_list_from_json(char *str, size_t len, struct discord_edit_global_application_command_params ***p);
extern size_t discord_edit_global_application_command_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_global_application_command_params_list_to_json(char *str, size_t len, struct discord_edit_global_application_command_params **p);

extern void discord_create_guild_application_command_params_cleanup_v(void *p);
extern void discord_create_guild_application_command_params_cleanup(struct discord_create_guild_application_command_params *p);
extern void discord_create_guild_application_command_params_init_v(void *p);
extern void discord_create_guild_application_command_params_init(struct discord_create_guild_application_command_params *p);
extern void discord_create_guild_application_command_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_application_command_params_from_json(char *json, size_t len, struct discord_create_guild_application_command_params **pp);
extern size_t discord_create_guild_application_command_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_application_command_params_to_json(char *json, size_t len, struct discord_create_guild_application_command_params *p);
extern void discord_create_guild_application_command_params_list_free_v(void **p);
extern void discord_create_guild_application_command_params_list_free(struct discord_create_guild_application_command_params **p);
extern void discord_create_guild_application_command_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_application_command_params_list_from_json(char *str, size_t len, struct discord_create_guild_application_command_params ***p);
extern size_t discord_create_guild_application_command_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_application_command_params_list_to_json(char *str, size_t len, struct discord_create_guild_application_command_params **p);

extern void discord_edit_guild_application_command_params_cleanup_v(void *p);
extern void discord_edit_guild_application_command_params_cleanup(struct discord_edit_guild_application_command_params *p);
extern void discord_edit_guild_application_command_params_init_v(void *p);
extern void discord_edit_guild_application_command_params_init(struct discord_edit_guild_application_command_params *p);
extern void discord_edit_guild_application_command_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_guild_application_command_params_from_json(char *json, size_t len, struct discord_edit_guild_application_command_params **pp);
extern size_t discord_edit_guild_application_command_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_guild_application_command_params_to_json(char *json, size_t len, struct discord_edit_guild_application_command_params *p);
extern void discord_edit_guild_application_command_params_list_free_v(void **p);
extern void discord_edit_guild_application_command_params_list_free(struct discord_edit_guild_application_command_params **p);
extern void discord_edit_guild_application_command_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_guild_application_command_params_list_from_json(char *str, size_t len, struct discord_edit_guild_application_command_params ***p);
extern size_t discord_edit_guild_application_command_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_guild_application_command_params_list_to_json(char *str, size_t len, struct discord_edit_guild_application_command_params **p);

extern void discord_edit_application_command_permissions_params_cleanup_v(void *p);
extern void discord_edit_application_command_permissions_params_cleanup(struct discord_edit_application_command_permissions_params *p);
extern void discord_edit_application_command_permissions_params_init_v(void *p);
extern void discord_edit_application_command_permissions_params_init(struct discord_edit_application_command_permissions_params *p);
extern void discord_edit_application_command_permissions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_application_command_permissions_params_from_json(char *json, size_t len, struct discord_edit_application_command_permissions_params **pp);
extern size_t discord_edit_application_command_permissions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_application_command_permissions_params_to_json(char *json, size_t len, struct discord_edit_application_command_permissions_params *p);
extern void discord_edit_application_command_permissions_params_list_free_v(void **p);
extern void discord_edit_application_command_permissions_params_list_free(struct discord_edit_application_command_permissions_params **p);
extern void discord_edit_application_command_permissions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_application_command_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_application_command_permissions_params ***p);
extern size_t discord_edit_application_command_permissions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_application_command_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_application_command_permissions_params **p);
/* This file is generated from specs/discord/application_commands.json, Please don't edit it. */

extern void discord_application_command_cleanup_v(void *p);
extern void discord_application_command_cleanup(struct discord_application_command *p);
extern void discord_application_command_init_v(void *p);
extern void discord_application_command_init(struct discord_application_command *p);
extern void discord_application_command_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_from_json(char *json, size_t len, struct discord_application_command **pp);
extern size_t discord_application_command_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_to_json(char *json, size_t len, struct discord_application_command *p);
extern void discord_application_command_list_free_v(void **p);
extern void discord_application_command_list_free(struct discord_application_command **p);
extern void discord_application_command_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_list_from_json(char *str, size_t len, struct discord_application_command ***p);
extern size_t discord_application_command_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_list_to_json(char *str, size_t len, struct discord_application_command **p);



extern void discord_application_command_option_cleanup_v(void *p);
extern void discord_application_command_option_cleanup(struct discord_application_command_option *p);
extern void discord_application_command_option_init_v(void *p);
extern void discord_application_command_option_init(struct discord_application_command_option *p);
extern void discord_application_command_option_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_option_from_json(char *json, size_t len, struct discord_application_command_option **pp);
extern size_t discord_application_command_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_to_json(char *json, size_t len, struct discord_application_command_option *p);
extern void discord_application_command_option_list_free_v(void **p);
extern void discord_application_command_option_list_free(struct discord_application_command_option **p);
extern void discord_application_command_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_option_list_from_json(char *str, size_t len, struct discord_application_command_option ***p);
extern size_t discord_application_command_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_option_list_to_json(char *str, size_t len, struct discord_application_command_option **p);



extern void discord_application_command_option_choice_cleanup_v(void *p);
extern void discord_application_command_option_choice_cleanup(struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_init_v(void *p);
extern void discord_application_command_option_choice_init(struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_option_choice_from_json(char *json, size_t len, struct discord_application_command_option_choice **pp);
extern size_t discord_application_command_option_choice_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_choice_to_json(char *json, size_t len, struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_list_free_v(void **p);
extern void discord_application_command_option_choice_list_free(struct discord_application_command_option_choice **p);
extern void discord_application_command_option_choice_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_option_choice_list_from_json(char *str, size_t len, struct discord_application_command_option_choice ***p);
extern size_t discord_application_command_option_choice_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_option_choice_list_to_json(char *str, size_t len, struct discord_application_command_option_choice **p);

extern void discord_guild_application_command_permissions_cleanup_v(void *p);
extern void discord_guild_application_command_permissions_cleanup(struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_init_v(void *p);
extern void discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_application_command_permissions_from_json(char *json, size_t len, struct discord_guild_application_command_permissions **pp);
extern size_t discord_guild_application_command_permissions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_to_json(char *json, size_t len, struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_list_free_v(void **p);
extern void discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions **p);
extern void discord_guild_application_command_permissions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_application_command_permissions_list_from_json(char *str, size_t len, struct discord_guild_application_command_permissions ***p);
extern size_t discord_guild_application_command_permissions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_list_to_json(char *str, size_t len, struct discord_guild_application_command_permissions **p);

extern void discord_application_command_permissions_cleanup_v(void *p);
extern void discord_application_command_permissions_cleanup(struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_init_v(void *p);
extern void discord_application_command_permissions_init(struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_permissions_from_json(char *json, size_t len, struct discord_application_command_permissions **pp);
extern size_t discord_application_command_permissions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_permissions_to_json(char *json, size_t len, struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_list_free_v(void **p);
extern void discord_application_command_permissions_list_free(struct discord_application_command_permissions **p);
extern void discord_application_command_permissions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_permissions_list_from_json(char *str, size_t len, struct discord_application_command_permissions ***p);
extern size_t discord_application_command_permissions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_permissions_list_to_json(char *str, size_t len, struct discord_application_command_permissions **p);



extern void discord_application_command_interaction_data_option_cleanup_v(void *p);
extern void discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_init_v(void *p);
extern void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_interaction_data_option_from_json(char *json, size_t len, struct discord_application_command_interaction_data_option **pp);
extern size_t discord_application_command_interaction_data_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_to_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_list_free_v(void **p);
extern void discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option **p);
extern void discord_application_command_interaction_data_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_interaction_data_option_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_option ***p);
extern size_t discord_application_command_interaction_data_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_option **p);
/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */

extern void discord_get_guild_audit_log_params_cleanup_v(void *p);
extern void discord_get_guild_audit_log_params_cleanup(struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_init_v(void *p);
extern void discord_get_guild_audit_log_params_init(struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_guild_audit_log_params_from_json(char *json, size_t len, struct discord_get_guild_audit_log_params **pp);
extern size_t discord_get_guild_audit_log_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_audit_log_params_to_json(char *json, size_t len, struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_list_free_v(void **p);
extern void discord_get_guild_audit_log_params_list_free(struct discord_get_guild_audit_log_params **p);
extern void discord_get_guild_audit_log_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_guild_audit_log_params_list_from_json(char *str, size_t len, struct discord_get_guild_audit_log_params ***p);
extern size_t discord_get_guild_audit_log_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_guild_audit_log_params_list_to_json(char *str, size_t len, struct discord_get_guild_audit_log_params **p);
/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */

extern void discord_audit_log_cleanup_v(void *p);
extern void discord_audit_log_cleanup(struct discord_audit_log *p);
extern void discord_audit_log_init_v(void *p);
extern void discord_audit_log_init(struct discord_audit_log *p);
extern void discord_audit_log_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_from_json(char *json, size_t len, struct discord_audit_log **pp);
extern size_t discord_audit_log_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_to_json(char *json, size_t len, struct discord_audit_log *p);
extern void discord_audit_log_list_free_v(void **p);
extern void discord_audit_log_list_free(struct discord_audit_log **p);
extern void discord_audit_log_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_list_from_json(char *str, size_t len, struct discord_audit_log ***p);
extern size_t discord_audit_log_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_list_to_json(char *str, size_t len, struct discord_audit_log **p);

extern void discord_audit_log_entry_cleanup_v(void *p);
extern void discord_audit_log_entry_cleanup(struct discord_audit_log_entry *p);
extern void discord_audit_log_entry_init_v(void *p);
extern void discord_audit_log_entry_init(struct discord_audit_log_entry *p);
extern void discord_audit_log_entry_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_entry_from_json(char *json, size_t len, struct discord_audit_log_entry **pp);
extern size_t discord_audit_log_entry_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_to_json(char *json, size_t len, struct discord_audit_log_entry *p);
extern void discord_audit_log_entry_list_free_v(void **p);
extern void discord_audit_log_entry_list_free(struct discord_audit_log_entry **p);
extern void discord_audit_log_entry_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_entry_list_from_json(char *str, size_t len, struct discord_audit_log_entry ***p);
extern size_t discord_audit_log_entry_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_entry_list_to_json(char *str, size_t len, struct discord_audit_log_entry **p);



extern void discord_optional_audit_entry_info_cleanup_v(void *p);
extern void discord_optional_audit_entry_info_cleanup(struct discord_optional_audit_entry_info *p);
extern void discord_optional_audit_entry_info_init_v(void *p);
extern void discord_optional_audit_entry_info_init(struct discord_optional_audit_entry_info *p);
extern void discord_optional_audit_entry_info_from_json_v(char *json, size_t len, void *pp);
extern void discord_optional_audit_entry_info_from_json(char *json, size_t len, struct discord_optional_audit_entry_info **pp);
extern size_t discord_optional_audit_entry_info_to_json_v(char *json, size_t len, void *p);
extern size_t discord_optional_audit_entry_info_to_json(char *json, size_t len, struct discord_optional_audit_entry_info *p);
extern void discord_optional_audit_entry_info_list_free_v(void **p);
extern void discord_optional_audit_entry_info_list_free(struct discord_optional_audit_entry_info **p);
extern void discord_optional_audit_entry_info_list_from_json_v(char *str, size_t len, void *p);
extern void discord_optional_audit_entry_info_list_from_json(char *str, size_t len, struct discord_optional_audit_entry_info ***p);
extern size_t discord_optional_audit_entry_info_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_optional_audit_entry_info_list_to_json(char *str, size_t len, struct discord_optional_audit_entry_info **p);

extern void discord_audit_log_change_cleanup_v(void *p);
extern void discord_audit_log_change_cleanup(struct discord_audit_log_change *p);
extern void discord_audit_log_change_init_v(void *p);
extern void discord_audit_log_change_init(struct discord_audit_log_change *p);
extern void discord_audit_log_change_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_change_from_json(char *json, size_t len, struct discord_audit_log_change **pp);
extern size_t discord_audit_log_change_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_to_json(char *json, size_t len, struct discord_audit_log_change *p);
extern void discord_audit_log_change_list_free_v(void **p);
extern void discord_audit_log_change_list_free(struct discord_audit_log_change **p);
extern void discord_audit_log_change_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_list_from_json(char *str, size_t len, struct discord_audit_log_change ***p);
extern size_t discord_audit_log_change_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_list_to_json(char *str, size_t len, struct discord_audit_log_change **p);
/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */

extern void discord_modify_channel_params_cleanup_v(void *p);
extern void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_init_v(void *p);
extern void discord_modify_channel_params_init(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params **pp);
extern size_t discord_modify_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_channel_params_to_json(char *json, size_t len, struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_list_free_v(void **p);
extern void discord_modify_channel_params_list_free(struct discord_modify_channel_params **p);
extern void discord_modify_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_channel_params_list_from_json(char *str, size_t len, struct discord_modify_channel_params ***p);
extern size_t discord_modify_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_channel_params_list_to_json(char *str, size_t len, struct discord_modify_channel_params **p);

extern void discord_create_message_params_cleanup_v(void *p);
extern void discord_create_message_params_cleanup(struct discord_create_message_params *p);
extern void discord_create_message_params_init_v(void *p);
extern void discord_create_message_params_init(struct discord_create_message_params *p);
extern void discord_create_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_message_params_from_json(char *json, size_t len, struct discord_create_message_params **pp);
extern size_t discord_create_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_message_params_to_json(char *json, size_t len, struct discord_create_message_params *p);
extern void discord_create_message_params_list_free_v(void **p);
extern void discord_create_message_params_list_free(struct discord_create_message_params **p);
extern void discord_create_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_message_params_list_from_json(char *str, size_t len, struct discord_create_message_params ***p);
extern size_t discord_create_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_message_params_list_to_json(char *str, size_t len, struct discord_create_message_params **p);

extern void discord_get_channel_messages_params_cleanup_v(void *p);
extern void discord_get_channel_messages_params_cleanup(struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_init_v(void *p);
extern void discord_get_channel_messages_params_init(struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_channel_messages_params_from_json(char *json, size_t len, struct discord_get_channel_messages_params **pp);
extern size_t discord_get_channel_messages_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_channel_messages_params_to_json(char *json, size_t len, struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_list_free_v(void **p);
extern void discord_get_channel_messages_params_list_free(struct discord_get_channel_messages_params **p);
extern void discord_get_channel_messages_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_channel_messages_params_list_from_json(char *str, size_t len, struct discord_get_channel_messages_params ***p);
extern size_t discord_get_channel_messages_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_channel_messages_params_list_to_json(char *str, size_t len, struct discord_get_channel_messages_params **p);

extern void discord_get_reactions_params_cleanup_v(void *p);
extern void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_init_v(void *p);
extern void discord_get_reactions_params_init(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_reactions_params_from_json(char *json, size_t len, struct discord_get_reactions_params **pp);
extern size_t discord_get_reactions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_reactions_params_to_json(char *json, size_t len, struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_list_free_v(void **p);
extern void discord_get_reactions_params_list_free(struct discord_get_reactions_params **p);
extern void discord_get_reactions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_reactions_params_list_from_json(char *str, size_t len, struct discord_get_reactions_params ***p);
extern size_t discord_get_reactions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_reactions_params_list_to_json(char *str, size_t len, struct discord_get_reactions_params **p);

extern void discord_edit_channel_permissions_params_cleanup_v(void *p);
extern void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_init_v(void *p);
extern void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params **pp);
extern size_t discord_edit_channel_permissions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_list_free_v(void **p);
extern void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **p);
extern void discord_edit_channel_permissions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_channel_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_channel_permissions_params ***p);
extern size_t discord_edit_channel_permissions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_channel_permissions_params **p);

extern void discord_edit_message_params_cleanup_v(void *p);
extern void discord_edit_message_params_cleanup(struct discord_edit_message_params *p);
extern void discord_edit_message_params_init_v(void *p);
extern void discord_edit_message_params_init(struct discord_edit_message_params *p);
extern void discord_edit_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_message_params_from_json(char *json, size_t len, struct discord_edit_message_params **pp);
extern size_t discord_edit_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_message_params_to_json(char *json, size_t len, struct discord_edit_message_params *p);
extern void discord_edit_message_params_list_free_v(void **p);
extern void discord_edit_message_params_list_free(struct discord_edit_message_params **p);
extern void discord_edit_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_message_params_list_from_json(char *str, size_t len, struct discord_edit_message_params ***p);
extern size_t discord_edit_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_message_params_list_to_json(char *str, size_t len, struct discord_edit_message_params **p);

extern void discord_follow_news_channel_params_cleanup_v(void *p);
extern void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_init_v(void *p);
extern void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params **pp);
extern size_t discord_follow_news_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_follow_news_channel_params_to_json(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_list_free_v(void **p);
extern void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **p);
extern void discord_follow_news_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_follow_news_channel_params_list_from_json(char *str, size_t len, struct discord_follow_news_channel_params ***p);
extern size_t discord_follow_news_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_follow_news_channel_params_list_to_json(char *str, size_t len, struct discord_follow_news_channel_params **p);

extern void discord_create_channel_invite_params_cleanup_v(void *p);
extern void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_init_v(void *p);
extern void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params **pp);
extern size_t discord_create_channel_invite_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_list_free_v(void **p);
extern void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **p);
extern void discord_create_channel_invite_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_channel_invite_params_list_from_json(char *str, size_t len, struct discord_create_channel_invite_params ***p);
extern size_t discord_create_channel_invite_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_channel_invite_params_list_to_json(char *str, size_t len, struct discord_create_channel_invite_params **p);

extern void discord_group_dm_add_recipient_params_cleanup_v(void *p);
extern void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_init_v(void *p);
extern void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params **pp);
extern size_t discord_group_dm_add_recipient_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_list_free_v(void **p);
extern void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p);
extern void discord_group_dm_add_recipient_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p);
extern size_t discord_group_dm_add_recipient_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p);

extern void discord_start_thread_with_message_params_cleanup_v(void *p);
extern void discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_init_v(void *p);
extern void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_start_thread_with_message_params_from_json(char *json, size_t len, struct discord_start_thread_with_message_params **pp);
extern size_t discord_start_thread_with_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_to_json(char *json, size_t len, struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_list_free_v(void **p);
extern void discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params **p);
extern void discord_start_thread_with_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_with_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_with_message_params ***p);
extern size_t discord_start_thread_with_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_with_message_params **p);

extern void discord_start_thread_without_message_params_cleanup_v(void *p);
extern void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_init_v(void *p);
extern void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params **pp);
extern size_t discord_start_thread_without_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_list_free_v(void **p);
extern void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **p);
extern void discord_start_thread_without_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_without_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_without_message_params ***p);
extern size_t discord_start_thread_without_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_without_message_params **p);

extern void discord_thread_response_body_cleanup_v(void *p);
extern void discord_thread_response_body_cleanup(struct discord_thread_response_body *p);
extern void discord_thread_response_body_init_v(void *p);
extern void discord_thread_response_body_init(struct discord_thread_response_body *p);
extern void discord_thread_response_body_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body **pp);
extern size_t discord_thread_response_body_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p);
extern void discord_thread_response_body_list_free_v(void **p);
extern void discord_thread_response_body_list_free(struct discord_thread_response_body **p);
extern void discord_thread_response_body_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p);
extern size_t discord_thread_response_body_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p);
/* This file is generated from specs/discord/channel.json, Please don't edit it. */



extern void discord_channel_cleanup_v(void *p);
extern void discord_channel_cleanup(struct discord_channel *p);
extern void discord_channel_init_v(void *p);
extern void discord_channel_init(struct discord_channel *p);
extern void discord_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_from_json(char *json, size_t len, struct discord_channel **pp);
extern size_t discord_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_to_json(char *json, size_t len, struct discord_channel *p);
extern void discord_channel_list_free_v(void **p);
extern void discord_channel_list_free(struct discord_channel **p);
extern void discord_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_list_from_json(char *str, size_t len, struct discord_channel ***p);
extern size_t discord_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_list_to_json(char *str, size_t len, struct discord_channel **p);



extern void discord_message_sticker_cleanup_v(void *p);
extern void discord_message_sticker_cleanup(struct discord_message_sticker *p);
extern void discord_message_sticker_init_v(void *p);
extern void discord_message_sticker_init(struct discord_message_sticker *p);
extern void discord_message_sticker_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_sticker_from_json(char *json, size_t len, struct discord_message_sticker **pp);
extern size_t discord_message_sticker_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_sticker_to_json(char *json, size_t len, struct discord_message_sticker *p);
extern void discord_message_sticker_list_free_v(void **p);
extern void discord_message_sticker_list_free(struct discord_message_sticker **p);
extern void discord_message_sticker_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_sticker_list_from_json(char *str, size_t len, struct discord_message_sticker ***p);
extern size_t discord_message_sticker_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_sticker_list_to_json(char *str, size_t len, struct discord_message_sticker **p);



extern void discord_message_reference_cleanup_v(void *p);
extern void discord_message_reference_cleanup(struct discord_message_reference *p);
extern void discord_message_reference_init_v(void *p);
extern void discord_message_reference_init(struct discord_message_reference *p);
extern void discord_message_reference_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_reference_from_json(char *json, size_t len, struct discord_message_reference **pp);
extern size_t discord_message_reference_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_reference_to_json(char *json, size_t len, struct discord_message_reference *p);
extern void discord_message_reference_list_free_v(void **p);
extern void discord_message_reference_list_free(struct discord_message_reference **p);
extern void discord_message_reference_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_reference_list_from_json(char *str, size_t len, struct discord_message_reference ***p);
extern size_t discord_message_reference_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_reference_list_to_json(char *str, size_t len, struct discord_message_reference **p);

extern void discord_message_application_cleanup_v(void *p);
extern void discord_message_application_cleanup(struct discord_message_application *p);
extern void discord_message_application_init_v(void *p);
extern void discord_message_application_init(struct discord_message_application *p);
extern void discord_message_application_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_application_from_json(char *json, size_t len, struct discord_message_application **pp);
extern size_t discord_message_application_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_application_to_json(char *json, size_t len, struct discord_message_application *p);
extern void discord_message_application_list_free_v(void **p);
extern void discord_message_application_list_free(struct discord_message_application **p);
extern void discord_message_application_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_application_list_from_json(char *str, size_t len, struct discord_message_application ***p);
extern size_t discord_message_application_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_application_list_to_json(char *str, size_t len, struct discord_message_application **p);



extern void discord_message_activity_cleanup_v(void *p);
extern void discord_message_activity_cleanup(struct discord_message_activity *p);
extern void discord_message_activity_init_v(void *p);
extern void discord_message_activity_init(struct discord_message_activity *p);
extern void discord_message_activity_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_activity_from_json(char *json, size_t len, struct discord_message_activity **pp);
extern size_t discord_message_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_activity_to_json(char *json, size_t len, struct discord_message_activity *p);
extern void discord_message_activity_list_free_v(void **p);
extern void discord_message_activity_list_free(struct discord_message_activity **p);
extern void discord_message_activity_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_activity_list_from_json(char *str, size_t len, struct discord_message_activity ***p);
extern size_t discord_message_activity_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_activity_list_to_json(char *str, size_t len, struct discord_message_activity **p);



extern void discord_message_cleanup_v(void *p);
extern void discord_message_cleanup(struct discord_message *p);
extern void discord_message_init_v(void *p);
extern void discord_message_init(struct discord_message *p);
extern void discord_message_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_from_json(char *json, size_t len, struct discord_message **pp);
extern size_t discord_message_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_to_json(char *json, size_t len, struct discord_message *p);
extern void discord_message_list_free_v(void **p);
extern void discord_message_list_free(struct discord_message **p);
extern void discord_message_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_list_from_json(char *str, size_t len, struct discord_message ***p);
extern size_t discord_message_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_list_to_json(char *str, size_t len, struct discord_message **p);

extern void discord_followed_channel_cleanup_v(void *p);
extern void discord_followed_channel_cleanup(struct discord_followed_channel *p);
extern void discord_followed_channel_init_v(void *p);
extern void discord_followed_channel_init(struct discord_followed_channel *p);
extern void discord_followed_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_followed_channel_from_json(char *json, size_t len, struct discord_followed_channel **pp);
extern size_t discord_followed_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_followed_channel_to_json(char *json, size_t len, struct discord_followed_channel *p);
extern void discord_followed_channel_list_free_v(void **p);
extern void discord_followed_channel_list_free(struct discord_followed_channel **p);
extern void discord_followed_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_followed_channel_list_from_json(char *str, size_t len, struct discord_followed_channel ***p);
extern size_t discord_followed_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_followed_channel_list_to_json(char *str, size_t len, struct discord_followed_channel **p);

extern void discord_reaction_cleanup_v(void *p);
extern void discord_reaction_cleanup(struct discord_reaction *p);
extern void discord_reaction_init_v(void *p);
extern void discord_reaction_init(struct discord_reaction *p);
extern void discord_reaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_reaction_from_json(char *json, size_t len, struct discord_reaction **pp);
extern size_t discord_reaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_reaction_to_json(char *json, size_t len, struct discord_reaction *p);
extern void discord_reaction_list_free_v(void **p);
extern void discord_reaction_list_free(struct discord_reaction **p);
extern void discord_reaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_reaction_list_from_json(char *str, size_t len, struct discord_reaction ***p);
extern size_t discord_reaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_reaction_list_to_json(char *str, size_t len, struct discord_reaction **p);

extern void discord_overwrite_cleanup_v(void *p);
extern void discord_overwrite_cleanup(struct discord_overwrite *p);
extern void discord_overwrite_init_v(void *p);
extern void discord_overwrite_init(struct discord_overwrite *p);
extern void discord_overwrite_from_json_v(char *json, size_t len, void *pp);
extern void discord_overwrite_from_json(char *json, size_t len, struct discord_overwrite **pp);
extern size_t discord_overwrite_to_json_v(char *json, size_t len, void *p);
extern size_t discord_overwrite_to_json(char *json, size_t len, struct discord_overwrite *p);
extern void discord_overwrite_list_free_v(void **p);
extern void discord_overwrite_list_free(struct discord_overwrite **p);
extern void discord_overwrite_list_from_json_v(char *str, size_t len, void *p);
extern void discord_overwrite_list_from_json(char *str, size_t len, struct discord_overwrite ***p);
extern size_t discord_overwrite_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_overwrite_list_to_json(char *str, size_t len, struct discord_overwrite **p);

extern void discord_thread_metadata_cleanup_v(void *p);
extern void discord_thread_metadata_cleanup(struct discord_thread_metadata *p);
extern void discord_thread_metadata_init_v(void *p);
extern void discord_thread_metadata_init(struct discord_thread_metadata *p);
extern void discord_thread_metadata_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_metadata_from_json(char *json, size_t len, struct discord_thread_metadata **pp);
extern size_t discord_thread_metadata_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_metadata_to_json(char *json, size_t len, struct discord_thread_metadata *p);
extern void discord_thread_metadata_list_free_v(void **p);
extern void discord_thread_metadata_list_free(struct discord_thread_metadata **p);
extern void discord_thread_metadata_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_metadata_list_from_json(char *str, size_t len, struct discord_thread_metadata ***p);
extern size_t discord_thread_metadata_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_metadata_list_to_json(char *str, size_t len, struct discord_thread_metadata **p);

extern void discord_thread_member_cleanup_v(void *p);
extern void discord_thread_member_cleanup(struct discord_thread_member *p);
extern void discord_thread_member_init_v(void *p);
extern void discord_thread_member_init(struct discord_thread_member *p);
extern void discord_thread_member_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_member_from_json(char *json, size_t len, struct discord_thread_member **pp);
extern size_t discord_thread_member_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_member_to_json(char *json, size_t len, struct discord_thread_member *p);
extern void discord_thread_member_list_free_v(void **p);
extern void discord_thread_member_list_free(struct discord_thread_member **p);
extern void discord_thread_member_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_member_list_from_json(char *str, size_t len, struct discord_thread_member ***p);
extern size_t discord_thread_member_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_member_list_to_json(char *str, size_t len, struct discord_thread_member **p);

extern void discord_attachment_cleanup_v(void *p);
extern void discord_attachment_cleanup(struct discord_attachment *p);
extern void discord_attachment_init_v(void *p);
extern void discord_attachment_init(struct discord_attachment *p);
extern void discord_attachment_from_json_v(char *json, size_t len, void *pp);
extern void discord_attachment_from_json(char *json, size_t len, struct discord_attachment **pp);
extern size_t discord_attachment_to_json_v(char *json, size_t len, void *p);
extern size_t discord_attachment_to_json(char *json, size_t len, struct discord_attachment *p);
extern void discord_attachment_list_free_v(void **p);
extern void discord_attachment_list_free(struct discord_attachment **p);
extern void discord_attachment_list_from_json_v(char *str, size_t len, void *p);
extern void discord_attachment_list_from_json(char *str, size_t len, struct discord_attachment ***p);
extern size_t discord_attachment_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_attachment_list_to_json(char *str, size_t len, struct discord_attachment **p);

extern void discord_channel_mention_cleanup_v(void *p);
extern void discord_channel_mention_cleanup(struct discord_channel_mention *p);
extern void discord_channel_mention_init_v(void *p);
extern void discord_channel_mention_init(struct discord_channel_mention *p);
extern void discord_channel_mention_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_mention_from_json(char *json, size_t len, struct discord_channel_mention **pp);
extern size_t discord_channel_mention_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_mention_to_json(char *json, size_t len, struct discord_channel_mention *p);
extern void discord_channel_mention_list_free_v(void **p);
extern void discord_channel_mention_list_free(struct discord_channel_mention **p);
extern void discord_channel_mention_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_mention_list_from_json(char *str, size_t len, struct discord_channel_mention ***p);
extern size_t discord_channel_mention_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_mention_list_to_json(char *str, size_t len, struct discord_channel_mention **p);

extern void discord_allowed_mentions_cleanup_v(void *p);
extern void discord_allowed_mentions_cleanup(struct discord_allowed_mentions *p);
extern void discord_allowed_mentions_init_v(void *p);
extern void discord_allowed_mentions_init(struct discord_allowed_mentions *p);
extern void discord_allowed_mentions_from_json_v(char *json, size_t len, void *pp);
extern void discord_allowed_mentions_from_json(char *json, size_t len, struct discord_allowed_mentions **pp);
extern size_t discord_allowed_mentions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_allowed_mentions_to_json(char *json, size_t len, struct discord_allowed_mentions *p);
extern void discord_allowed_mentions_list_free_v(void **p);
extern void discord_allowed_mentions_list_free(struct discord_allowed_mentions **p);
extern void discord_allowed_mentions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_allowed_mentions_list_from_json(char *str, size_t len, struct discord_allowed_mentions ***p);
extern size_t discord_allowed_mentions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_allowed_mentions_list_to_json(char *str, size_t len, struct discord_allowed_mentions **p);

extern void discord_embed_cleanup_v(void *p);
extern void discord_embed_cleanup(struct discord_embed *p);
extern void discord_embed_init_v(void *p);
extern void discord_embed_init(struct discord_embed *p);
extern void discord_embed_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_from_json(char *json, size_t len, struct discord_embed **pp);
extern size_t discord_embed_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_to_json(char *json, size_t len, struct discord_embed *p);
extern void discord_embed_list_free_v(void **p);
extern void discord_embed_list_free(struct discord_embed **p);
extern void discord_embed_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_list_from_json(char *str, size_t len, struct discord_embed ***p);
extern size_t discord_embed_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_list_to_json(char *str, size_t len, struct discord_embed **p);

extern void discord_embed_thumbnail_cleanup_v(void *p);
extern void discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_init_v(void *p);
extern void discord_embed_thumbnail_init(struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_thumbnail_from_json(char *json, size_t len, struct discord_embed_thumbnail **pp);
extern size_t discord_embed_thumbnail_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_thumbnail_to_json(char *json, size_t len, struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_list_free_v(void **p);
extern void discord_embed_thumbnail_list_free(struct discord_embed_thumbnail **p);
extern void discord_embed_thumbnail_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_thumbnail_list_from_json(char *str, size_t len, struct discord_embed_thumbnail ***p);
extern size_t discord_embed_thumbnail_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_thumbnail_list_to_json(char *str, size_t len, struct discord_embed_thumbnail **p);

extern void discord_embed_video_cleanup_v(void *p);
extern void discord_embed_video_cleanup(struct discord_embed_video *p);
extern void discord_embed_video_init_v(void *p);
extern void discord_embed_video_init(struct discord_embed_video *p);
extern void discord_embed_video_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_video_from_json(char *json, size_t len, struct discord_embed_video **pp);
extern size_t discord_embed_video_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_video_to_json(char *json, size_t len, struct discord_embed_video *p);
extern void discord_embed_video_list_free_v(void **p);
extern void discord_embed_video_list_free(struct discord_embed_video **p);
extern void discord_embed_video_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_video_list_from_json(char *str, size_t len, struct discord_embed_video ***p);
extern size_t discord_embed_video_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_video_list_to_json(char *str, size_t len, struct discord_embed_video **p);

extern void discord_embed_image_cleanup_v(void *p);
extern void discord_embed_image_cleanup(struct discord_embed_image *p);
extern void discord_embed_image_init_v(void *p);
extern void discord_embed_image_init(struct discord_embed_image *p);
extern void discord_embed_image_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_image_from_json(char *json, size_t len, struct discord_embed_image **pp);
extern size_t discord_embed_image_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_image_to_json(char *json, size_t len, struct discord_embed_image *p);
extern void discord_embed_image_list_free_v(void **p);
extern void discord_embed_image_list_free(struct discord_embed_image **p);
extern void discord_embed_image_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_image_list_from_json(char *str, size_t len, struct discord_embed_image ***p);
extern size_t discord_embed_image_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_image_list_to_json(char *str, size_t len, struct discord_embed_image **p);

extern void discord_embed_provider_cleanup_v(void *p);
extern void discord_embed_provider_cleanup(struct discord_embed_provider *p);
extern void discord_embed_provider_init_v(void *p);
extern void discord_embed_provider_init(struct discord_embed_provider *p);
extern void discord_embed_provider_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_provider_from_json(char *json, size_t len, struct discord_embed_provider **pp);
extern size_t discord_embed_provider_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_provider_to_json(char *json, size_t len, struct discord_embed_provider *p);
extern void discord_embed_provider_list_free_v(void **p);
extern void discord_embed_provider_list_free(struct discord_embed_provider **p);
extern void discord_embed_provider_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_provider_list_from_json(char *str, size_t len, struct discord_embed_provider ***p);
extern size_t discord_embed_provider_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_provider_list_to_json(char *str, size_t len, struct discord_embed_provider **p);

extern void discord_embed_author_cleanup_v(void *p);
extern void discord_embed_author_cleanup(struct discord_embed_author *p);
extern void discord_embed_author_init_v(void *p);
extern void discord_embed_author_init(struct discord_embed_author *p);
extern void discord_embed_author_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_author_from_json(char *json, size_t len, struct discord_embed_author **pp);
extern size_t discord_embed_author_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_author_to_json(char *json, size_t len, struct discord_embed_author *p);
extern void discord_embed_author_list_free_v(void **p);
extern void discord_embed_author_list_free(struct discord_embed_author **p);
extern void discord_embed_author_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_author_list_from_json(char *str, size_t len, struct discord_embed_author ***p);
extern size_t discord_embed_author_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_author_list_to_json(char *str, size_t len, struct discord_embed_author **p);

extern void discord_embed_footer_cleanup_v(void *p);
extern void discord_embed_footer_cleanup(struct discord_embed_footer *p);
extern void discord_embed_footer_init_v(void *p);
extern void discord_embed_footer_init(struct discord_embed_footer *p);
extern void discord_embed_footer_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_footer_from_json(char *json, size_t len, struct discord_embed_footer **pp);
extern size_t discord_embed_footer_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_footer_to_json(char *json, size_t len, struct discord_embed_footer *p);
extern void discord_embed_footer_list_free_v(void **p);
extern void discord_embed_footer_list_free(struct discord_embed_footer **p);
extern void discord_embed_footer_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_footer_list_from_json(char *str, size_t len, struct discord_embed_footer ***p);
extern size_t discord_embed_footer_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_footer_list_to_json(char *str, size_t len, struct discord_embed_footer **p);

extern void discord_embed_field_cleanup_v(void *p);
extern void discord_embed_field_cleanup(struct discord_embed_field *p);
extern void discord_embed_field_init_v(void *p);
extern void discord_embed_field_init(struct discord_embed_field *p);
extern void discord_embed_field_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_field_from_json(char *json, size_t len, struct discord_embed_field **pp);
extern size_t discord_embed_field_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_field_to_json(char *json, size_t len, struct discord_embed_field *p);
extern void discord_embed_field_list_free_v(void **p);
extern void discord_embed_field_list_free(struct discord_embed_field **p);
extern void discord_embed_field_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_field_list_from_json(char *str, size_t len, struct discord_embed_field ***p);
extern size_t discord_embed_field_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_field_list_to_json(char *str, size_t len, struct discord_embed_field **p);
/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */

extern void discord_create_guild_emoji_params_cleanup_v(void *p);
extern void discord_create_guild_emoji_params_cleanup(struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_init_v(void *p);
extern void discord_create_guild_emoji_params_init(struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_emoji_params_from_json(char *json, size_t len, struct discord_create_guild_emoji_params **pp);
extern size_t discord_create_guild_emoji_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_emoji_params_to_json(char *json, size_t len, struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_list_free_v(void **p);
extern void discord_create_guild_emoji_params_list_free(struct discord_create_guild_emoji_params **p);
extern void discord_create_guild_emoji_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_emoji_params_list_from_json(char *str, size_t len, struct discord_create_guild_emoji_params ***p);
extern size_t discord_create_guild_emoji_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_emoji_params_list_to_json(char *str, size_t len, struct discord_create_guild_emoji_params **p);

extern void discord_modify_guild_emoji_params_cleanup_v(void *p);
extern void discord_modify_guild_emoji_params_cleanup(struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_init_v(void *p);
extern void discord_modify_guild_emoji_params_init(struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_emoji_params_from_json(char *json, size_t len, struct discord_modify_guild_emoji_params **pp);
extern size_t discord_modify_guild_emoji_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_emoji_params_to_json(char *json, size_t len, struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_list_free_v(void **p);
extern void discord_modify_guild_emoji_params_list_free(struct discord_modify_guild_emoji_params **p);
extern void discord_modify_guild_emoji_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_emoji_params_list_from_json(char *str, size_t len, struct discord_modify_guild_emoji_params ***p);
extern size_t discord_modify_guild_emoji_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_emoji_params_list_to_json(char *str, size_t len, struct discord_modify_guild_emoji_params **p);
/* This file is generated from specs/discord/emoji.json, Please don't edit it. */

extern void discord_emoji_cleanup_v(void *p);
extern void discord_emoji_cleanup(struct discord_emoji *p);
extern void discord_emoji_init_v(void *p);
extern void discord_emoji_init(struct discord_emoji *p);
extern void discord_emoji_from_json_v(char *json, size_t len, void *pp);
extern void discord_emoji_from_json(char *json, size_t len, struct discord_emoji **pp);
extern size_t discord_emoji_to_json_v(char *json, size_t len, void *p);
extern size_t discord_emoji_to_json(char *json, size_t len, struct discord_emoji *p);
extern void discord_emoji_list_free_v(void **p);
extern void discord_emoji_list_free(struct discord_emoji **p);
extern void discord_emoji_list_from_json_v(char *str, size_t len, void *p);
extern void discord_emoji_list_from_json(char *str, size_t len, struct discord_emoji ***p);
extern size_t discord_emoji_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_emoji_list_to_json(char *str, size_t len, struct discord_emoji **p);
/* This file is generated from specs/discord/gateway.json, Please don't edit it. */









extern void discord_identify_cleanup_v(void *p);
extern void discord_identify_cleanup(struct discord_identify *p);
extern void discord_identify_init_v(void *p);
extern void discord_identify_init(struct discord_identify *p);
extern void discord_identify_from_json_v(char *json, size_t len, void *pp);
extern void discord_identify_from_json(char *json, size_t len, struct discord_identify **pp);
extern size_t discord_identify_to_json_v(char *json, size_t len, void *p);
extern size_t discord_identify_to_json(char *json, size_t len, struct discord_identify *p);
extern void discord_identify_list_free_v(void **p);
extern void discord_identify_list_free(struct discord_identify **p);
extern void discord_identify_list_from_json_v(char *str, size_t len, void *p);
extern void discord_identify_list_from_json(char *str, size_t len, struct discord_identify ***p);
extern size_t discord_identify_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_identify_list_to_json(char *str, size_t len, struct discord_identify **p);

extern void discord_voice_state_status_cleanup_v(void *p);
extern void discord_voice_state_status_cleanup(struct discord_voice_state_status *p);
extern void discord_voice_state_status_init_v(void *p);
extern void discord_voice_state_status_init(struct discord_voice_state_status *p);
extern void discord_voice_state_status_from_json_v(char *json, size_t len, void *pp);
extern void discord_voice_state_status_from_json(char *json, size_t len, struct discord_voice_state_status **pp);
extern size_t discord_voice_state_status_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_state_status_to_json(char *json, size_t len, struct discord_voice_state_status *p);
extern void discord_voice_state_status_list_free_v(void **p);
extern void discord_voice_state_status_list_free(struct discord_voice_state_status **p);
extern void discord_voice_state_status_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_state_status_list_from_json(char *str, size_t len, struct discord_voice_state_status ***p);
extern size_t discord_voice_state_status_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_state_status_list_to_json(char *str, size_t len, struct discord_voice_state_status **p);

extern void discord_presence_status_cleanup_v(void *p);
extern void discord_presence_status_cleanup(struct discord_presence_status *p);
extern void discord_presence_status_init_v(void *p);
extern void discord_presence_status_init(struct discord_presence_status *p);
extern void discord_presence_status_from_json_v(char *json, size_t len, void *pp);
extern void discord_presence_status_from_json(char *json, size_t len, struct discord_presence_status **pp);
extern size_t discord_presence_status_to_json_v(char *json, size_t len, void *p);
extern size_t discord_presence_status_to_json(char *json, size_t len, struct discord_presence_status *p);
extern void discord_presence_status_list_free_v(void **p);
extern void discord_presence_status_list_free(struct discord_presence_status **p);
extern void discord_presence_status_list_from_json_v(char *str, size_t len, void *p);
extern void discord_presence_status_list_from_json(char *str, size_t len, struct discord_presence_status ***p);
extern size_t discord_presence_status_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_presence_status_list_to_json(char *str, size_t len, struct discord_presence_status **p);

extern void discord_identify_connection_cleanup_v(void *p);
extern void discord_identify_connection_cleanup(struct discord_identify_connection *p);
extern void discord_identify_connection_init_v(void *p);
extern void discord_identify_connection_init(struct discord_identify_connection *p);
extern void discord_identify_connection_from_json_v(char *json, size_t len, void *pp);
extern void discord_identify_connection_from_json(char *json, size_t len, struct discord_identify_connection **pp);
extern size_t discord_identify_connection_to_json_v(char *json, size_t len, void *p);
extern size_t discord_identify_connection_to_json(char *json, size_t len, struct discord_identify_connection *p);
extern void discord_identify_connection_list_free_v(void **p);
extern void discord_identify_connection_list_free(struct discord_identify_connection **p);
extern void discord_identify_connection_list_from_json_v(char *str, size_t len, void *p);
extern void discord_identify_connection_list_from_json(char *str, size_t len, struct discord_identify_connection ***p);
extern size_t discord_identify_connection_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_identify_connection_list_to_json(char *str, size_t len, struct discord_identify_connection **p);

extern void discord_activity_cleanup_v(void *p);
extern void discord_activity_cleanup(struct discord_activity *p);
extern void discord_activity_init_v(void *p);
extern void discord_activity_init(struct discord_activity *p);
extern void discord_activity_from_json_v(char *json, size_t len, void *pp);
extern void discord_activity_from_json(char *json, size_t len, struct discord_activity **pp);
extern size_t discord_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_activity_to_json(char *json, size_t len, struct discord_activity *p);
extern void discord_activity_list_free_v(void **p);
extern void discord_activity_list_free(struct discord_activity **p);
extern void discord_activity_list_from_json_v(char *str, size_t len, void *p);
extern void discord_activity_list_from_json(char *str, size_t len, struct discord_activity ***p);
extern size_t discord_activity_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_activity_list_to_json(char *str, size_t len, struct discord_activity **p);



extern void discord_session_start_limit_cleanup_v(void *p);
extern void discord_session_start_limit_cleanup(struct discord_session_start_limit *p);
extern void discord_session_start_limit_init_v(void *p);
extern void discord_session_start_limit_init(struct discord_session_start_limit *p);
extern void discord_session_start_limit_from_json_v(char *json, size_t len, void *pp);
extern void discord_session_start_limit_from_json(char *json, size_t len, struct discord_session_start_limit **pp);
extern size_t discord_session_start_limit_to_json_v(char *json, size_t len, void *p);
extern size_t discord_session_start_limit_to_json(char *json, size_t len, struct discord_session_start_limit *p);
extern void discord_session_start_limit_list_free_v(void **p);
extern void discord_session_start_limit_list_free(struct discord_session_start_limit **p);
extern void discord_session_start_limit_list_from_json_v(char *str, size_t len, void *p);
extern void discord_session_start_limit_list_from_json(char *str, size_t len, struct discord_session_start_limit ***p);
extern size_t discord_session_start_limit_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_session_start_limit_list_to_json(char *str, size_t len, struct discord_session_start_limit **p);
/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */

extern void discord_create_guild_from_guild_template_params_cleanup_v(void *p);
extern void discord_create_guild_from_guild_template_params_cleanup(struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_init_v(void *p);
extern void discord_create_guild_from_guild_template_params_init(struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_from_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params **pp);
extern size_t discord_create_guild_from_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_list_free_v(void **p);
extern void discord_create_guild_from_guild_template_params_list_free(struct discord_create_guild_from_guild_template_params **p);
extern void discord_create_guild_from_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_from_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_from_guild_template_params ***p);
extern size_t discord_create_guild_from_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_from_guild_template_params **p);

extern void discord_create_guild_template_params_cleanup_v(void *p);
extern void discord_create_guild_template_params_cleanup(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_init_v(void *p);
extern void discord_create_guild_template_params_init(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_template_params **pp);
extern size_t discord_create_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_list_free_v(void **p);
extern void discord_create_guild_template_params_list_free(struct discord_create_guild_template_params **p);
extern void discord_create_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_template_params ***p);
extern size_t discord_create_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_template_params **p);

extern void discord_modify_guild_template_params_cleanup_v(void *p);
extern void discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_init_v(void *p);
extern void discord_modify_guild_template_params_init(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_template_params_from_json(char *json, size_t len, struct discord_modify_guild_template_params **pp);
extern size_t discord_modify_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_template_params_to_json(char *json, size_t len, struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_list_free_v(void **p);
extern void discord_modify_guild_template_params_list_free(struct discord_modify_guild_template_params **p);
extern void discord_modify_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_template_params_list_from_json(char *str, size_t len, struct discord_modify_guild_template_params ***p);
extern size_t discord_modify_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_template_params_list_to_json(char *str, size_t len, struct discord_modify_guild_template_params **p);
/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */

extern void discord_guild_template_cleanup_v(void *p);
extern void discord_guild_template_cleanup(struct discord_guild_template *p);
extern void discord_guild_template_init_v(void *p);
extern void discord_guild_template_init(struct discord_guild_template *p);
extern void discord_guild_template_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_template_from_json(char *json, size_t len, struct discord_guild_template **pp);
extern size_t discord_guild_template_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_template_to_json(char *json, size_t len, struct discord_guild_template *p);
extern void discord_guild_template_list_free_v(void **p);
extern void discord_guild_template_list_free(struct discord_guild_template **p);
extern void discord_guild_template_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_template_list_from_json(char *str, size_t len, struct discord_guild_template ***p);
extern size_t discord_guild_template_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_template_list_to_json(char *str, size_t len, struct discord_guild_template **p);
/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */

extern void discord_create_guild_params_cleanup_v(void *p);
extern void discord_create_guild_params_cleanup(struct discord_create_guild_params *p);
extern void discord_create_guild_params_init_v(void *p);
extern void discord_create_guild_params_init(struct discord_create_guild_params *p);
extern void discord_create_guild_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_params_from_json(char *json, size_t len, struct discord_create_guild_params **pp);
extern size_t discord_create_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_params_to_json(char *json, size_t len, struct discord_create_guild_params *p);
extern void discord_create_guild_params_list_free_v(void **p);
extern void discord_create_guild_params_list_free(struct discord_create_guild_params **p);
extern void discord_create_guild_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_params_list_from_json(char *str, size_t len, struct discord_create_guild_params ***p);
extern size_t discord_create_guild_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_params_list_to_json(char *str, size_t len, struct discord_create_guild_params **p);

extern void discord_modify_guild_params_cleanup_v(void *p);
extern void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_init_v(void *p);
extern void discord_modify_guild_params_init(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_params_from_json(char *json, size_t len, struct discord_modify_guild_params **pp);
extern size_t discord_modify_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_params_to_json(char *json, size_t len, struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_list_free_v(void **p);
extern void discord_modify_guild_params_list_free(struct discord_modify_guild_params **p);
extern void discord_modify_guild_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_params_list_from_json(char *str, size_t len, struct discord_modify_guild_params ***p);
extern size_t discord_modify_guild_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_params_list_to_json(char *str, size_t len, struct discord_modify_guild_params **p);

extern void discord_create_guild_channel_params_cleanup_v(void *p);
extern void discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_init_v(void *p);
extern void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_channel_params_from_json(char *json, size_t len, struct discord_create_guild_channel_params **pp);
extern size_t discord_create_guild_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_channel_params_to_json(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_list_free_v(void **p);
extern void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **p);
extern void discord_create_guild_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_channel_params_list_from_json(char *str, size_t len, struct discord_create_guild_channel_params ***p);
extern size_t discord_create_guild_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_channel_params_list_to_json(char *str, size_t len, struct discord_create_guild_channel_params **p);

extern void discord_modify_guild_channel_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_init_v(void *p);
extern void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_channel_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params **pp);
extern size_t discord_modify_guild_channel_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_list_free_v(void **p);
extern void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **p);
extern void discord_modify_guild_channel_positions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_channel_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params ***p);
extern size_t discord_modify_guild_channel_positions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params **p);

extern void discord_list_guild_members_params_cleanup_v(void *p);
extern void discord_list_guild_members_params_cleanup(struct discord_list_guild_members_params *p);
extern void discord_list_guild_members_params_init_v(void *p);
extern void discord_list_guild_members_params_init(struct discord_list_guild_members_params *p);
extern void discord_list_guild_members_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_list_guild_members_params_from_json(char *json, size_t len, struct discord_list_guild_members_params **pp);
extern size_t discord_list_guild_members_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_list_guild_members_params_to_json(char *json, size_t len, struct discord_list_guild_members_params *p);
extern void discord_list_guild_members_params_list_free_v(void **p);
extern void discord_list_guild_members_params_list_free(struct discord_list_guild_members_params **p);
extern void discord_list_guild_members_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_list_guild_members_params_list_from_json(char *str, size_t len, struct discord_list_guild_members_params ***p);
extern size_t discord_list_guild_members_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_list_guild_members_params_list_to_json(char *str, size_t len, struct discord_list_guild_members_params **p);

extern void discord_search_guild_members_params_cleanup_v(void *p);
extern void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_init_v(void *p);
extern void discord_search_guild_members_params_init(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_search_guild_members_params_from_json(char *json, size_t len, struct discord_search_guild_members_params **pp);
extern size_t discord_search_guild_members_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_search_guild_members_params_to_json(char *json, size_t len, struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_list_free_v(void **p);
extern void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **p);
extern void discord_search_guild_members_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_search_guild_members_params_list_from_json(char *str, size_t len, struct discord_search_guild_members_params ***p);
extern size_t discord_search_guild_members_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_search_guild_members_params_list_to_json(char *str, size_t len, struct discord_search_guild_members_params **p);

extern void discord_add_guild_member_params_cleanup_v(void *p);
extern void discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_init_v(void *p);
extern void discord_add_guild_member_params_init(struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_add_guild_member_params_from_json(char *json, size_t len, struct discord_add_guild_member_params **pp);
extern size_t discord_add_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_add_guild_member_params_to_json(char *json, size_t len, struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_list_free_v(void **p);
extern void discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **p);
extern void discord_add_guild_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_add_guild_member_params_list_from_json(char *str, size_t len, struct discord_add_guild_member_params ***p);
extern size_t discord_add_guild_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_add_guild_member_params_list_to_json(char *str, size_t len, struct discord_add_guild_member_params **p);

extern void discord_modify_guild_member_params_cleanup_v(void *p);
extern void discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_init_v(void *p);
extern void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_member_params_from_json(char *json, size_t len, struct discord_modify_guild_member_params **pp);
extern size_t discord_modify_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_member_params_to_json(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_list_free_v(void **p);
extern void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **p);
extern void discord_modify_guild_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_member_params_list_from_json(char *str, size_t len, struct discord_modify_guild_member_params ***p);
extern size_t discord_modify_guild_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_member_params_list_to_json(char *str, size_t len, struct discord_modify_guild_member_params **p);

extern void discord_modify_current_member_params_cleanup_v(void *p);
extern void discord_modify_current_member_params_cleanup(struct discord_modify_current_member_params *p);
extern void discord_modify_current_member_params_init_v(void *p);
extern void discord_modify_current_member_params_init(struct discord_modify_current_member_params *p);
extern void discord_modify_current_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_current_member_params_from_json(char *json, size_t len, struct discord_modify_current_member_params **pp);
extern size_t discord_modify_current_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_member_params_to_json(char *json, size_t len, struct discord_modify_current_member_params *p);
extern void discord_modify_current_member_params_list_free_v(void **p);
extern void discord_modify_current_member_params_list_free(struct discord_modify_current_member_params **p);
extern void discord_modify_current_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_current_member_params_list_from_json(char *str, size_t len, struct discord_modify_current_member_params ***p);
extern size_t discord_modify_current_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_current_member_params_list_to_json(char *str, size_t len, struct discord_modify_current_member_params **p);

extern void discord_modify_current_user_nick_params_cleanup_v(void *p);
extern void discord_modify_current_user_nick_params_cleanup(struct discord_modify_current_user_nick_params *p);
extern void discord_modify_current_user_nick_params_init_v(void *p);
extern void discord_modify_current_user_nick_params_init(struct discord_modify_current_user_nick_params *p);
extern void discord_modify_current_user_nick_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_current_user_nick_params_from_json(char *json, size_t len, struct discord_modify_current_user_nick_params **pp);
extern size_t discord_modify_current_user_nick_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_user_nick_params_to_json(char *json, size_t len, struct discord_modify_current_user_nick_params *p);
extern void discord_modify_current_user_nick_params_list_free_v(void **p);
extern void discord_modify_current_user_nick_params_list_free(struct discord_modify_current_user_nick_params **p);
extern void discord_modify_current_user_nick_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_current_user_nick_params_list_from_json(char *str, size_t len, struct discord_modify_current_user_nick_params ***p);
extern size_t discord_modify_current_user_nick_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_current_user_nick_params_list_to_json(char *str, size_t len, struct discord_modify_current_user_nick_params **p);

extern void discord_create_guild_ban_params_cleanup_v(void *p);
extern void discord_create_guild_ban_params_cleanup(struct discord_create_guild_ban_params *p);
extern void discord_create_guild_ban_params_init_v(void *p);
extern void discord_create_guild_ban_params_init(struct discord_create_guild_ban_params *p);
extern void discord_create_guild_ban_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_ban_params_from_json(char *json, size_t len, struct discord_create_guild_ban_params **pp);
extern size_t discord_create_guild_ban_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_ban_params_to_json(char *json, size_t len, struct discord_create_guild_ban_params *p);
extern void discord_create_guild_ban_params_list_free_v(void **p);
extern void discord_create_guild_ban_params_list_free(struct discord_create_guild_ban_params **p);
extern void discord_create_guild_ban_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_ban_params_list_from_json(char *str, size_t len, struct discord_create_guild_ban_params ***p);
extern size_t discord_create_guild_ban_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_ban_params_list_to_json(char *str, size_t len, struct discord_create_guild_ban_params **p);

extern void discord_create_guild_role_params_cleanup_v(void *p);
extern void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_init_v(void *p);
extern void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params **pp);
extern size_t discord_create_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_role_params_to_json(char *json, size_t len, struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_list_free_v(void **p);
extern void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **p);
extern void discord_create_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_role_params_list_from_json(char *str, size_t len, struct discord_create_guild_role_params ***p);
extern size_t discord_create_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_role_params_list_to_json(char *str, size_t len, struct discord_create_guild_role_params **p);

extern void discord_modify_guild_role_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_init_v(void *p);
extern void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_role_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_role_positions_params **pp);
extern size_t discord_modify_guild_role_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_list_free_v(void **p);
extern void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **p);
extern void discord_modify_guild_role_positions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_role_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_positions_params ***p);
extern size_t discord_modify_guild_role_positions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_positions_params **p);

extern void discord_modify_guild_role_params_cleanup_v(void *p);
extern void discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_init_v(void *p);
extern void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_role_params_from_json(char *json, size_t len, struct discord_modify_guild_role_params **pp);
extern size_t discord_modify_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_params_to_json(char *json, size_t len, struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_list_free_v(void **p);
extern void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **p);
extern void discord_modify_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_role_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_params ***p);
extern size_t discord_modify_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_role_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_params **p);

extern void discord_get_guild_prune_count_params_cleanup_v(void *p);
extern void discord_get_guild_prune_count_params_cleanup(struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_init_v(void *p);
extern void discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_guild_prune_count_params_from_json(char *json, size_t len, struct discord_get_guild_prune_count_params **pp);
extern size_t discord_get_guild_prune_count_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_to_json(char *json, size_t len, struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_list_free_v(void **p);
extern void discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params **p);
extern void discord_get_guild_prune_count_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_guild_prune_count_params_list_from_json(char *str, size_t len, struct discord_get_guild_prune_count_params ***p);
extern size_t discord_get_guild_prune_count_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_list_to_json(char *str, size_t len, struct discord_get_guild_prune_count_params **p);

extern void discord_begin_guild_prune_params_cleanup_v(void *p);
extern void discord_begin_guild_prune_params_cleanup(struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_init_v(void *p);
extern void discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_begin_guild_prune_params_from_json(char *json, size_t len, struct discord_begin_guild_prune_params **pp);
extern size_t discord_begin_guild_prune_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_to_json(char *json, size_t len, struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_list_free_v(void **p);
extern void discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **p);
extern void discord_begin_guild_prune_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_begin_guild_prune_params_list_from_json(char *str, size_t len, struct discord_begin_guild_prune_params ***p);
extern size_t discord_begin_guild_prune_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_list_to_json(char *str, size_t len, struct discord_begin_guild_prune_params **p);
/* This file is generated from specs/discord/guild.json, Please don't edit it. */

extern void discord_guild_cleanup_v(void *p);
extern void discord_guild_cleanup(struct discord_guild *p);
extern void discord_guild_init_v(void *p);
extern void discord_guild_init(struct discord_guild *p);
extern void discord_guild_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_from_json(char *json, size_t len, struct discord_guild **pp);
extern size_t discord_guild_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_to_json(char *json, size_t len, struct discord_guild *p);
extern void discord_guild_list_free_v(void **p);
extern void discord_guild_list_free(struct discord_guild **p);
extern void discord_guild_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_list_from_json(char *str, size_t len, struct discord_guild ***p);
extern size_t discord_guild_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_list_to_json(char *str, size_t len, struct discord_guild **p);















extern void discord_unavailable_guild_cleanup_v(void *p);
extern void discord_unavailable_guild_cleanup(struct discord_unavailable_guild *p);
extern void discord_unavailable_guild_init_v(void *p);
extern void discord_unavailable_guild_init(struct discord_unavailable_guild *p);
extern void discord_unavailable_guild_from_json_v(char *json, size_t len, void *pp);
extern void discord_unavailable_guild_from_json(char *json, size_t len, struct discord_unavailable_guild **pp);
extern size_t discord_unavailable_guild_to_json_v(char *json, size_t len, void *p);
extern size_t discord_unavailable_guild_to_json(char *json, size_t len, struct discord_unavailable_guild *p);
extern void discord_unavailable_guild_list_free_v(void **p);
extern void discord_unavailable_guild_list_free(struct discord_unavailable_guild **p);
extern void discord_unavailable_guild_list_from_json_v(char *str, size_t len, void *p);
extern void discord_unavailable_guild_list_from_json(char *str, size_t len, struct discord_unavailable_guild ***p);
extern size_t discord_unavailable_guild_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_unavailable_guild_list_to_json(char *str, size_t len, struct discord_unavailable_guild **p);

extern void discord_guild_preview_cleanup_v(void *p);
extern void discord_guild_preview_cleanup(struct discord_guild_preview *p);
extern void discord_guild_preview_init_v(void *p);
extern void discord_guild_preview_init(struct discord_guild_preview *p);
extern void discord_guild_preview_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_preview_from_json(char *json, size_t len, struct discord_guild_preview **pp);
extern size_t discord_guild_preview_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_preview_to_json(char *json, size_t len, struct discord_guild_preview *p);
extern void discord_guild_preview_list_free_v(void **p);
extern void discord_guild_preview_list_free(struct discord_guild_preview **p);
extern void discord_guild_preview_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_preview_list_from_json(char *str, size_t len, struct discord_guild_preview ***p);
extern size_t discord_guild_preview_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_preview_list_to_json(char *str, size_t len, struct discord_guild_preview **p);

extern void discord_guild_widget_cleanup_v(void *p);
extern void discord_guild_widget_cleanup(struct discord_guild_widget *p);
extern void discord_guild_widget_init_v(void *p);
extern void discord_guild_widget_init(struct discord_guild_widget *p);
extern void discord_guild_widget_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_widget_from_json(char *json, size_t len, struct discord_guild_widget **pp);
extern size_t discord_guild_widget_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_widget_to_json(char *json, size_t len, struct discord_guild_widget *p);
extern void discord_guild_widget_list_free_v(void **p);
extern void discord_guild_widget_list_free(struct discord_guild_widget **p);
extern void discord_guild_widget_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_widget_list_from_json(char *str, size_t len, struct discord_guild_widget ***p);
extern size_t discord_guild_widget_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_widget_list_to_json(char *str, size_t len, struct discord_guild_widget **p);

extern void discord_guild_member_cleanup_v(void *p);
extern void discord_guild_member_cleanup(struct discord_guild_member *p);
extern void discord_guild_member_init_v(void *p);
extern void discord_guild_member_init(struct discord_guild_member *p);
extern void discord_guild_member_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_member_from_json(char *json, size_t len, struct discord_guild_member **pp);
extern size_t discord_guild_member_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_member_to_json(char *json, size_t len, struct discord_guild_member *p);
extern void discord_guild_member_list_free_v(void **p);
extern void discord_guild_member_list_free(struct discord_guild_member **p);
extern void discord_guild_member_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_member_list_from_json(char *str, size_t len, struct discord_guild_member ***p);
extern size_t discord_guild_member_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_member_list_to_json(char *str, size_t len, struct discord_guild_member **p);

extern void discord_integration_cleanup_v(void *p);
extern void discord_integration_cleanup(struct discord_integration *p);
extern void discord_integration_init_v(void *p);
extern void discord_integration_init(struct discord_integration *p);
extern void discord_integration_from_json_v(char *json, size_t len, void *pp);
extern void discord_integration_from_json(char *json, size_t len, struct discord_integration **pp);
extern size_t discord_integration_to_json_v(char *json, size_t len, void *p);
extern size_t discord_integration_to_json(char *json, size_t len, struct discord_integration *p);
extern void discord_integration_list_free_v(void **p);
extern void discord_integration_list_free(struct discord_integration **p);
extern void discord_integration_list_from_json_v(char *str, size_t len, void *p);
extern void discord_integration_list_from_json(char *str, size_t len, struct discord_integration ***p);
extern size_t discord_integration_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_integration_list_to_json(char *str, size_t len, struct discord_integration **p);



extern void discord_integration_account_cleanup_v(void *p);
extern void discord_integration_account_cleanup(struct discord_integration_account *p);
extern void discord_integration_account_init_v(void *p);
extern void discord_integration_account_init(struct discord_integration_account *p);
extern void discord_integration_account_from_json_v(char *json, size_t len, void *pp);
extern void discord_integration_account_from_json(char *json, size_t len, struct discord_integration_account **pp);
extern size_t discord_integration_account_to_json_v(char *json, size_t len, void *p);
extern size_t discord_integration_account_to_json(char *json, size_t len, struct discord_integration_account *p);
extern void discord_integration_account_list_free_v(void **p);
extern void discord_integration_account_list_free(struct discord_integration_account **p);
extern void discord_integration_account_list_from_json_v(char *str, size_t len, void *p);
extern void discord_integration_account_list_from_json(char *str, size_t len, struct discord_integration_account ***p);
extern size_t discord_integration_account_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_integration_account_list_to_json(char *str, size_t len, struct discord_integration_account **p);

extern void discord_integration_application_cleanup_v(void *p);
extern void discord_integration_application_cleanup(struct discord_integration_application *p);
extern void discord_integration_application_init_v(void *p);
extern void discord_integration_application_init(struct discord_integration_application *p);
extern void discord_integration_application_from_json_v(char *json, size_t len, void *pp);
extern void discord_integration_application_from_json(char *json, size_t len, struct discord_integration_application **pp);
extern size_t discord_integration_application_to_json_v(char *json, size_t len, void *p);
extern size_t discord_integration_application_to_json(char *json, size_t len, struct discord_integration_application *p);
extern void discord_integration_application_list_free_v(void **p);
extern void discord_integration_application_list_free(struct discord_integration_application **p);
extern void discord_integration_application_list_from_json_v(char *str, size_t len, void *p);
extern void discord_integration_application_list_from_json(char *str, size_t len, struct discord_integration_application ***p);
extern size_t discord_integration_application_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_integration_application_list_to_json(char *str, size_t len, struct discord_integration_application **p);

extern void discord_ban_cleanup_v(void *p);
extern void discord_ban_cleanup(struct discord_ban *p);
extern void discord_ban_init_v(void *p);
extern void discord_ban_init(struct discord_ban *p);
extern void discord_ban_from_json_v(char *json, size_t len, void *pp);
extern void discord_ban_from_json(char *json, size_t len, struct discord_ban **pp);
extern size_t discord_ban_to_json_v(char *json, size_t len, void *p);
extern size_t discord_ban_to_json(char *json, size_t len, struct discord_ban *p);
extern void discord_ban_list_free_v(void **p);
extern void discord_ban_list_free(struct discord_ban **p);
extern void discord_ban_list_from_json_v(char *str, size_t len, void *p);
extern void discord_ban_list_from_json(char *str, size_t len, struct discord_ban ***p);
extern size_t discord_ban_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_ban_list_to_json(char *str, size_t len, struct discord_ban **p);

extern void discord_welcome_screen_cleanup_v(void *p);
extern void discord_welcome_screen_cleanup(struct discord_welcome_screen *p);
extern void discord_welcome_screen_init_v(void *p);
extern void discord_welcome_screen_init(struct discord_welcome_screen *p);
extern void discord_welcome_screen_from_json_v(char *json, size_t len, void *pp);
extern void discord_welcome_screen_from_json(char *json, size_t len, struct discord_welcome_screen **pp);
extern size_t discord_welcome_screen_to_json_v(char *json, size_t len, void *p);
extern size_t discord_welcome_screen_to_json(char *json, size_t len, struct discord_welcome_screen *p);
extern void discord_welcome_screen_list_free_v(void **p);
extern void discord_welcome_screen_list_free(struct discord_welcome_screen **p);
extern void discord_welcome_screen_list_from_json_v(char *str, size_t len, void *p);
extern void discord_welcome_screen_list_from_json(char *str, size_t len, struct discord_welcome_screen ***p);
extern size_t discord_welcome_screen_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_welcome_screen_list_to_json(char *str, size_t len, struct discord_welcome_screen **p);

extern void discord_welcome_screen_channel_cleanup_v(void *p);
extern void discord_welcome_screen_channel_cleanup(struct discord_welcome_screen_channel *p);
extern void discord_welcome_screen_channel_init_v(void *p);
extern void discord_welcome_screen_channel_init(struct discord_welcome_screen_channel *p);
extern void discord_welcome_screen_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_welcome_screen_channel_from_json(char *json, size_t len, struct discord_welcome_screen_channel **pp);
extern size_t discord_welcome_screen_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_welcome_screen_channel_to_json(char *json, size_t len, struct discord_welcome_screen_channel *p);
extern void discord_welcome_screen_channel_list_free_v(void **p);
extern void discord_welcome_screen_channel_list_free(struct discord_welcome_screen_channel **p);
extern void discord_welcome_screen_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_welcome_screen_channel_list_from_json(char *str, size_t len, struct discord_welcome_screen_channel ***p);
extern size_t discord_welcome_screen_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_welcome_screen_channel_list_to_json(char *str, size_t len, struct discord_welcome_screen_channel **p);
/* This file is generated from specs/discord/interaction.endpoints-params.json, Please don't edit it. */

extern void discord_edit_original_interaction_response_params_cleanup_v(void *p);
extern void discord_edit_original_interaction_response_params_cleanup(struct discord_edit_original_interaction_response_params *p);
extern void discord_edit_original_interaction_response_params_init_v(void *p);
extern void discord_edit_original_interaction_response_params_init(struct discord_edit_original_interaction_response_params *p);
extern void discord_edit_original_interaction_response_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_original_interaction_response_params_from_json(char *json, size_t len, struct discord_edit_original_interaction_response_params **pp);
extern size_t discord_edit_original_interaction_response_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_original_interaction_response_params_to_json(char *json, size_t len, struct discord_edit_original_interaction_response_params *p);
extern void discord_edit_original_interaction_response_params_list_free_v(void **p);
extern void discord_edit_original_interaction_response_params_list_free(struct discord_edit_original_interaction_response_params **p);
extern void discord_edit_original_interaction_response_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_original_interaction_response_params_list_from_json(char *str, size_t len, struct discord_edit_original_interaction_response_params ***p);
extern size_t discord_edit_original_interaction_response_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_original_interaction_response_params_list_to_json(char *str, size_t len, struct discord_edit_original_interaction_response_params **p);

extern void discord_create_followup_message_params_cleanup_v(void *p);
extern void discord_create_followup_message_params_cleanup(struct discord_create_followup_message_params *p);
extern void discord_create_followup_message_params_init_v(void *p);
extern void discord_create_followup_message_params_init(struct discord_create_followup_message_params *p);
extern void discord_create_followup_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_followup_message_params_from_json(char *json, size_t len, struct discord_create_followup_message_params **pp);
extern size_t discord_create_followup_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_followup_message_params_to_json(char *json, size_t len, struct discord_create_followup_message_params *p);
extern void discord_create_followup_message_params_list_free_v(void **p);
extern void discord_create_followup_message_params_list_free(struct discord_create_followup_message_params **p);
extern void discord_create_followup_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_followup_message_params_list_from_json(char *str, size_t len, struct discord_create_followup_message_params ***p);
extern size_t discord_create_followup_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_followup_message_params_list_to_json(char *str, size_t len, struct discord_create_followup_message_params **p);

extern void discord_edit_followup_message_params_cleanup_v(void *p);
extern void discord_edit_followup_message_params_cleanup(struct discord_edit_followup_message_params *p);
extern void discord_edit_followup_message_params_init_v(void *p);
extern void discord_edit_followup_message_params_init(struct discord_edit_followup_message_params *p);
extern void discord_edit_followup_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_followup_message_params_from_json(char *json, size_t len, struct discord_edit_followup_message_params **pp);
extern size_t discord_edit_followup_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_followup_message_params_to_json(char *json, size_t len, struct discord_edit_followup_message_params *p);
extern void discord_edit_followup_message_params_list_free_v(void **p);
extern void discord_edit_followup_message_params_list_free(struct discord_edit_followup_message_params **p);
extern void discord_edit_followup_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_followup_message_params_list_from_json(char *str, size_t len, struct discord_edit_followup_message_params ***p);
extern size_t discord_edit_followup_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_followup_message_params_list_to_json(char *str, size_t len, struct discord_edit_followup_message_params **p);
/* This file is generated from specs/discord/interaction.json, Please don't edit it. */

extern void discord_interaction_cleanup_v(void *p);
extern void discord_interaction_cleanup(struct discord_interaction *p);
extern void discord_interaction_init_v(void *p);
extern void discord_interaction_init(struct discord_interaction *p);
extern void discord_interaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_from_json(char *json, size_t len, struct discord_interaction **pp);
extern size_t discord_interaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_to_json(char *json, size_t len, struct discord_interaction *p);
extern void discord_interaction_list_free_v(void **p);
extern void discord_interaction_list_free(struct discord_interaction **p);
extern void discord_interaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_list_from_json(char *str, size_t len, struct discord_interaction ***p);
extern size_t discord_interaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_list_to_json(char *str, size_t len, struct discord_interaction **p);



extern void discord_interaction_data_cleanup_v(void *p);
extern void discord_interaction_data_cleanup(struct discord_interaction_data *p);
extern void discord_interaction_data_init_v(void *p);
extern void discord_interaction_data_init(struct discord_interaction_data *p);
extern void discord_interaction_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_data_from_json(char *json, size_t len, struct discord_interaction_data **pp);
extern size_t discord_interaction_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_data_to_json(char *json, size_t len, struct discord_interaction_data *p);
extern void discord_interaction_data_list_free_v(void **p);
extern void discord_interaction_data_list_free(struct discord_interaction_data **p);
extern void discord_interaction_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_data_list_from_json(char *str, size_t len, struct discord_interaction_data ***p);
extern size_t discord_interaction_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_data_list_to_json(char *str, size_t len, struct discord_interaction_data **p);

extern void discord_resolved_data_cleanup_v(void *p);
extern void discord_resolved_data_cleanup(struct discord_resolved_data *p);
extern void discord_resolved_data_init_v(void *p);
extern void discord_resolved_data_init(struct discord_resolved_data *p);
extern void discord_resolved_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_resolved_data_from_json(char *json, size_t len, struct discord_resolved_data **pp);
extern size_t discord_resolved_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_resolved_data_to_json(char *json, size_t len, struct discord_resolved_data *p);
extern void discord_resolved_data_list_free_v(void **p);
extern void discord_resolved_data_list_free(struct discord_resolved_data **p);
extern void discord_resolved_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_resolved_data_list_from_json(char *str, size_t len, struct discord_resolved_data ***p);
extern size_t discord_resolved_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_resolved_data_list_to_json(char *str, size_t len, struct discord_resolved_data **p);

extern void discord_message_interaction_cleanup_v(void *p);
extern void discord_message_interaction_cleanup(struct discord_message_interaction *p);
extern void discord_message_interaction_init_v(void *p);
extern void discord_message_interaction_init(struct discord_message_interaction *p);
extern void discord_message_interaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_interaction_from_json(char *json, size_t len, struct discord_message_interaction **pp);
extern size_t discord_message_interaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_interaction_to_json(char *json, size_t len, struct discord_message_interaction *p);
extern void discord_message_interaction_list_free_v(void **p);
extern void discord_message_interaction_list_free(struct discord_message_interaction **p);
extern void discord_message_interaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_interaction_list_from_json(char *str, size_t len, struct discord_message_interaction ***p);
extern size_t discord_message_interaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_interaction_list_to_json(char *str, size_t len, struct discord_message_interaction **p);

extern void discord_interaction_response_cleanup_v(void *p);
extern void discord_interaction_response_cleanup(struct discord_interaction_response *p);
extern void discord_interaction_response_init_v(void *p);
extern void discord_interaction_response_init(struct discord_interaction_response *p);
extern void discord_interaction_response_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_response_from_json(char *json, size_t len, struct discord_interaction_response **pp);
extern size_t discord_interaction_response_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_response_to_json(char *json, size_t len, struct discord_interaction_response *p);
extern void discord_interaction_response_list_free_v(void **p);
extern void discord_interaction_response_list_free(struct discord_interaction_response **p);
extern void discord_interaction_response_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_response_list_from_json(char *str, size_t len, struct discord_interaction_response ***p);
extern size_t discord_interaction_response_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_response_list_to_json(char *str, size_t len, struct discord_interaction_response **p);



extern void discord_interaction_callback_data_cleanup_v(void *p);
extern void discord_interaction_callback_data_cleanup(struct discord_interaction_callback_data *p);
extern void discord_interaction_callback_data_init_v(void *p);
extern void discord_interaction_callback_data_init(struct discord_interaction_callback_data *p);
extern void discord_interaction_callback_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_callback_data_from_json(char *json, size_t len, struct discord_interaction_callback_data **pp);
extern size_t discord_interaction_callback_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_callback_data_to_json(char *json, size_t len, struct discord_interaction_callback_data *p);
extern void discord_interaction_callback_data_list_free_v(void **p);
extern void discord_interaction_callback_data_list_free(struct discord_interaction_callback_data **p);
extern void discord_interaction_callback_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_callback_data_list_from_json(char *str, size_t len, struct discord_interaction_callback_data ***p);
extern size_t discord_interaction_callback_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_callback_data_list_to_json(char *str, size_t len, struct discord_interaction_callback_data **p);


/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */

extern void discord_get_invite_params_cleanup_v(void *p);
extern void discord_get_invite_params_cleanup(struct discord_get_invite_params *p);
extern void discord_get_invite_params_init_v(void *p);
extern void discord_get_invite_params_init(struct discord_get_invite_params *p);
extern void discord_get_invite_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_invite_params_from_json(char *json, size_t len, struct discord_get_invite_params **pp);
extern size_t discord_get_invite_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_invite_params_to_json(char *json, size_t len, struct discord_get_invite_params *p);
extern void discord_get_invite_params_list_free_v(void **p);
extern void discord_get_invite_params_list_free(struct discord_get_invite_params **p);
extern void discord_get_invite_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_invite_params_list_from_json(char *str, size_t len, struct discord_get_invite_params ***p);
extern size_t discord_get_invite_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_invite_params_list_to_json(char *str, size_t len, struct discord_get_invite_params **p);
/* This file is generated from specs/discord/invite.json, Please don't edit it. */



extern void discord_invite_cleanup_v(void *p);
extern void discord_invite_cleanup(struct discord_invite *p);
extern void discord_invite_init_v(void *p);
extern void discord_invite_init(struct discord_invite *p);
extern void discord_invite_from_json_v(char *json, size_t len, void *pp);
extern void discord_invite_from_json(char *json, size_t len, struct discord_invite **pp);
extern size_t discord_invite_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_to_json(char *json, size_t len, struct discord_invite *p);
extern void discord_invite_list_free_v(void **p);
extern void discord_invite_list_free(struct discord_invite **p);
extern void discord_invite_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_list_from_json(char *str, size_t len, struct discord_invite ***p);
extern size_t discord_invite_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_list_to_json(char *str, size_t len, struct discord_invite **p);

extern void discord_invite_metadata_cleanup_v(void *p);
extern void discord_invite_metadata_cleanup(struct discord_invite_metadata *p);
extern void discord_invite_metadata_init_v(void *p);
extern void discord_invite_metadata_init(struct discord_invite_metadata *p);
extern void discord_invite_metadata_from_json_v(char *json, size_t len, void *pp);
extern void discord_invite_metadata_from_json(char *json, size_t len, struct discord_invite_metadata **pp);
extern size_t discord_invite_metadata_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_metadata_to_json(char *json, size_t len, struct discord_invite_metadata *p);
extern void discord_invite_metadata_list_free_v(void **p);
extern void discord_invite_metadata_list_free(struct discord_invite_metadata **p);
extern void discord_invite_metadata_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_metadata_list_from_json(char *str, size_t len, struct discord_invite_metadata ***p);
extern size_t discord_invite_metadata_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_metadata_list_to_json(char *str, size_t len, struct discord_invite_metadata **p);
/* This file is generated from specs/discord/message_components.json, Please don't edit it. */

extern void discord_component_cleanup_v(void *p);
extern void discord_component_cleanup(struct discord_component *p);
extern void discord_component_init_v(void *p);
extern void discord_component_init(struct discord_component *p);
extern void discord_component_from_json_v(char *json, size_t len, void *pp);
extern void discord_component_from_json(char *json, size_t len, struct discord_component **pp);
extern size_t discord_component_to_json_v(char *json, size_t len, void *p);
extern size_t discord_component_to_json(char *json, size_t len, struct discord_component *p);
extern void discord_component_list_free_v(void **p);
extern void discord_component_list_free(struct discord_component **p);
extern void discord_component_list_from_json_v(char *str, size_t len, void *p);
extern void discord_component_list_from_json(char *str, size_t len, struct discord_component ***p);
extern size_t discord_component_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_component_list_to_json(char *str, size_t len, struct discord_component **p);



extern void discord_button_cleanup_v(void *p);
extern void discord_button_cleanup(struct discord_button *p);
extern void discord_button_init_v(void *p);
extern void discord_button_init(struct discord_button *p);
extern void discord_button_from_json_v(char *json, size_t len, void *pp);
extern void discord_button_from_json(char *json, size_t len, struct discord_button **pp);
extern size_t discord_button_to_json_v(char *json, size_t len, void *p);
extern size_t discord_button_to_json(char *json, size_t len, struct discord_button *p);
extern void discord_button_list_free_v(void **p);
extern void discord_button_list_free(struct discord_button **p);
extern void discord_button_list_from_json_v(char *str, size_t len, void *p);
extern void discord_button_list_from_json(char *str, size_t len, struct discord_button ***p);
extern size_t discord_button_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_button_list_to_json(char *str, size_t len, struct discord_button **p);



extern void discord_select_menu_cleanup_v(void *p);
extern void discord_select_menu_cleanup(struct discord_select_menu *p);
extern void discord_select_menu_init_v(void *p);
extern void discord_select_menu_init(struct discord_select_menu *p);
extern void discord_select_menu_from_json_v(char *json, size_t len, void *pp);
extern void discord_select_menu_from_json(char *json, size_t len, struct discord_select_menu **pp);
extern size_t discord_select_menu_to_json_v(char *json, size_t len, void *p);
extern size_t discord_select_menu_to_json(char *json, size_t len, struct discord_select_menu *p);
extern void discord_select_menu_list_free_v(void **p);
extern void discord_select_menu_list_free(struct discord_select_menu **p);
extern void discord_select_menu_list_from_json_v(char *str, size_t len, void *p);
extern void discord_select_menu_list_from_json(char *str, size_t len, struct discord_select_menu ***p);
extern size_t discord_select_menu_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_select_menu_list_to_json(char *str, size_t len, struct discord_select_menu **p);

extern void discord_select_option_cleanup_v(void *p);
extern void discord_select_option_cleanup(struct discord_select_option *p);
extern void discord_select_option_init_v(void *p);
extern void discord_select_option_init(struct discord_select_option *p);
extern void discord_select_option_from_json_v(char *json, size_t len, void *pp);
extern void discord_select_option_from_json(char *json, size_t len, struct discord_select_option **pp);
extern size_t discord_select_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_select_option_to_json(char *json, size_t len, struct discord_select_option *p);
extern void discord_select_option_list_free_v(void **p);
extern void discord_select_option_list_free(struct discord_select_option **p);
extern void discord_select_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_select_option_list_from_json(char *str, size_t len, struct discord_select_option ***p);
extern size_t discord_select_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_select_option_list_to_json(char *str, size_t len, struct discord_select_option **p);
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */



extern void discord_role_cleanup_v(void *p);
extern void discord_role_cleanup(struct discord_role *p);
extern void discord_role_init_v(void *p);
extern void discord_role_init(struct discord_role *p);
extern void discord_role_from_json_v(char *json, size_t len, void *pp);
extern void discord_role_from_json(char *json, size_t len, struct discord_role **pp);
extern size_t discord_role_to_json_v(char *json, size_t len, void *p);
extern size_t discord_role_to_json(char *json, size_t len, struct discord_role *p);
extern void discord_role_list_free_v(void **p);
extern void discord_role_list_free(struct discord_role **p);
extern void discord_role_list_from_json_v(char *str, size_t len, void *p);
extern void discord_role_list_from_json(char *str, size_t len, struct discord_role ***p);
extern size_t discord_role_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_role_list_to_json(char *str, size_t len, struct discord_role **p);

extern void discord_role_tags_cleanup_v(void *p);
extern void discord_role_tags_cleanup(struct discord_role_tags *p);
extern void discord_role_tags_init_v(void *p);
extern void discord_role_tags_init(struct discord_role_tags *p);
extern void discord_role_tags_from_json_v(char *json, size_t len, void *pp);
extern void discord_role_tags_from_json(char *json, size_t len, struct discord_role_tags **pp);
extern size_t discord_role_tags_to_json_v(char *json, size_t len, void *p);
extern size_t discord_role_tags_to_json(char *json, size_t len, struct discord_role_tags *p);
extern void discord_role_tags_list_free_v(void **p);
extern void discord_role_tags_list_free(struct discord_role_tags **p);
extern void discord_role_tags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_role_tags_list_from_json(char *str, size_t len, struct discord_role_tags ***p);
extern size_t discord_role_tags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_role_tags_list_to_json(char *str, size_t len, struct discord_role_tags **p);
/* This file is generated from specs/discord/stage-instance.endpoints-params.json, Please don't edit it. */

extern void discord_create_stage_instance_params_cleanup_v(void *p);
extern void discord_create_stage_instance_params_cleanup(struct discord_create_stage_instance_params *p);
extern void discord_create_stage_instance_params_init_v(void *p);
extern void discord_create_stage_instance_params_init(struct discord_create_stage_instance_params *p);
extern void discord_create_stage_instance_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_stage_instance_params_from_json(char *json, size_t len, struct discord_create_stage_instance_params **pp);
extern size_t discord_create_stage_instance_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_stage_instance_params_to_json(char *json, size_t len, struct discord_create_stage_instance_params *p);
extern void discord_create_stage_instance_params_list_free_v(void **p);
extern void discord_create_stage_instance_params_list_free(struct discord_create_stage_instance_params **p);
extern void discord_create_stage_instance_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_stage_instance_params_list_from_json(char *str, size_t len, struct discord_create_stage_instance_params ***p);
extern size_t discord_create_stage_instance_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_stage_instance_params_list_to_json(char *str, size_t len, struct discord_create_stage_instance_params **p);

extern void discord_modify_stage_instance_params_cleanup_v(void *p);
extern void discord_modify_stage_instance_params_cleanup(struct discord_modify_stage_instance_params *p);
extern void discord_modify_stage_instance_params_init_v(void *p);
extern void discord_modify_stage_instance_params_init(struct discord_modify_stage_instance_params *p);
extern void discord_modify_stage_instance_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_stage_instance_params_from_json(char *json, size_t len, struct discord_modify_stage_instance_params **pp);
extern size_t discord_modify_stage_instance_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_stage_instance_params_to_json(char *json, size_t len, struct discord_modify_stage_instance_params *p);
extern void discord_modify_stage_instance_params_list_free_v(void **p);
extern void discord_modify_stage_instance_params_list_free(struct discord_modify_stage_instance_params **p);
extern void discord_modify_stage_instance_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_stage_instance_params_list_from_json(char *str, size_t len, struct discord_modify_stage_instance_params ***p);
extern size_t discord_modify_stage_instance_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_stage_instance_params_list_to_json(char *str, size_t len, struct discord_modify_stage_instance_params **p);
/* This file is generated from specs/discord/stage-instance.json, Please don't edit it. */



extern void discord_stage_instance_cleanup_v(void *p);
extern void discord_stage_instance_cleanup(struct discord_stage_instance *p);
extern void discord_stage_instance_init_v(void *p);
extern void discord_stage_instance_init(struct discord_stage_instance *p);
extern void discord_stage_instance_from_json_v(char *json, size_t len, void *pp);
extern void discord_stage_instance_from_json(char *json, size_t len, struct discord_stage_instance **pp);
extern size_t discord_stage_instance_to_json_v(char *json, size_t len, void *p);
extern size_t discord_stage_instance_to_json(char *json, size_t len, struct discord_stage_instance *p);
extern void discord_stage_instance_list_free_v(void **p);
extern void discord_stage_instance_list_free(struct discord_stage_instance **p);
extern void discord_stage_instance_list_from_json_v(char *str, size_t len, void *p);
extern void discord_stage_instance_list_from_json(char *str, size_t len, struct discord_stage_instance ***p);
extern size_t discord_stage_instance_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_stage_instance_list_to_json(char *str, size_t len, struct discord_stage_instance **p);
/* This file is generated from specs/discord/sticker.endpoints-params.json, Please don't edit it. */

extern void discord_list_nitro_sticker_packs_response_cleanup_v(void *p);
extern void discord_list_nitro_sticker_packs_response_cleanup(struct discord_list_nitro_sticker_packs_response *p);
extern void discord_list_nitro_sticker_packs_response_init_v(void *p);
extern void discord_list_nitro_sticker_packs_response_init(struct discord_list_nitro_sticker_packs_response *p);
extern void discord_list_nitro_sticker_packs_response_from_json_v(char *json, size_t len, void *pp);
extern void discord_list_nitro_sticker_packs_response_from_json(char *json, size_t len, struct discord_list_nitro_sticker_packs_response **pp);
extern size_t discord_list_nitro_sticker_packs_response_to_json_v(char *json, size_t len, void *p);
extern size_t discord_list_nitro_sticker_packs_response_to_json(char *json, size_t len, struct discord_list_nitro_sticker_packs_response *p);
extern void discord_list_nitro_sticker_packs_response_list_free_v(void **p);
extern void discord_list_nitro_sticker_packs_response_list_free(struct discord_list_nitro_sticker_packs_response **p);
extern void discord_list_nitro_sticker_packs_response_list_from_json_v(char *str, size_t len, void *p);
extern void discord_list_nitro_sticker_packs_response_list_from_json(char *str, size_t len, struct discord_list_nitro_sticker_packs_response ***p);
extern size_t discord_list_nitro_sticker_packs_response_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_list_nitro_sticker_packs_response_list_to_json(char *str, size_t len, struct discord_list_nitro_sticker_packs_response **p);

extern void discord_create_guild_sticker_params_cleanup_v(void *p);
extern void discord_create_guild_sticker_params_cleanup(struct discord_create_guild_sticker_params *p);
extern void discord_create_guild_sticker_params_init_v(void *p);
extern void discord_create_guild_sticker_params_init(struct discord_create_guild_sticker_params *p);
extern void discord_create_guild_sticker_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_sticker_params_from_json(char *json, size_t len, struct discord_create_guild_sticker_params **pp);
extern size_t discord_create_guild_sticker_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_sticker_params_to_json(char *json, size_t len, struct discord_create_guild_sticker_params *p);
extern void discord_create_guild_sticker_params_list_free_v(void **p);
extern void discord_create_guild_sticker_params_list_free(struct discord_create_guild_sticker_params **p);
extern void discord_create_guild_sticker_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_sticker_params_list_from_json(char *str, size_t len, struct discord_create_guild_sticker_params ***p);
extern size_t discord_create_guild_sticker_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_sticker_params_list_to_json(char *str, size_t len, struct discord_create_guild_sticker_params **p);

extern void discord_modify_guild_sticker_params_cleanup_v(void *p);
extern void discord_modify_guild_sticker_params_cleanup(struct discord_modify_guild_sticker_params *p);
extern void discord_modify_guild_sticker_params_init_v(void *p);
extern void discord_modify_guild_sticker_params_init(struct discord_modify_guild_sticker_params *p);
extern void discord_modify_guild_sticker_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_sticker_params_from_json(char *json, size_t len, struct discord_modify_guild_sticker_params **pp);
extern size_t discord_modify_guild_sticker_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_sticker_params_to_json(char *json, size_t len, struct discord_modify_guild_sticker_params *p);
extern void discord_modify_guild_sticker_params_list_free_v(void **p);
extern void discord_modify_guild_sticker_params_list_free(struct discord_modify_guild_sticker_params **p);
extern void discord_modify_guild_sticker_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_sticker_params_list_from_json(char *str, size_t len, struct discord_modify_guild_sticker_params ***p);
extern size_t discord_modify_guild_sticker_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_sticker_params_list_to_json(char *str, size_t len, struct discord_modify_guild_sticker_params **p);
/* This file is generated from specs/discord/sticker.json, Please don't edit it. */





extern void discord_sticker_cleanup_v(void *p);
extern void discord_sticker_cleanup(struct discord_sticker *p);
extern void discord_sticker_init_v(void *p);
extern void discord_sticker_init(struct discord_sticker *p);
extern void discord_sticker_from_json_v(char *json, size_t len, void *pp);
extern void discord_sticker_from_json(char *json, size_t len, struct discord_sticker **pp);
extern size_t discord_sticker_to_json_v(char *json, size_t len, void *p);
extern size_t discord_sticker_to_json(char *json, size_t len, struct discord_sticker *p);
extern void discord_sticker_list_free_v(void **p);
extern void discord_sticker_list_free(struct discord_sticker **p);
extern void discord_sticker_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_list_from_json(char *str, size_t len, struct discord_sticker ***p);
extern size_t discord_sticker_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_list_to_json(char *str, size_t len, struct discord_sticker **p);

extern void discord_sticker_item_cleanup_v(void *p);
extern void discord_sticker_item_cleanup(struct discord_sticker_item *p);
extern void discord_sticker_item_init_v(void *p);
extern void discord_sticker_item_init(struct discord_sticker_item *p);
extern void discord_sticker_item_from_json_v(char *json, size_t len, void *pp);
extern void discord_sticker_item_from_json(char *json, size_t len, struct discord_sticker_item **pp);
extern size_t discord_sticker_item_to_json_v(char *json, size_t len, void *p);
extern size_t discord_sticker_item_to_json(char *json, size_t len, struct discord_sticker_item *p);
extern void discord_sticker_item_list_free_v(void **p);
extern void discord_sticker_item_list_free(struct discord_sticker_item **p);
extern void discord_sticker_item_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_item_list_from_json(char *str, size_t len, struct discord_sticker_item ***p);
extern size_t discord_sticker_item_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_item_list_to_json(char *str, size_t len, struct discord_sticker_item **p);

extern void discord_sticker_pack_cleanup_v(void *p);
extern void discord_sticker_pack_cleanup(struct discord_sticker_pack *p);
extern void discord_sticker_pack_init_v(void *p);
extern void discord_sticker_pack_init(struct discord_sticker_pack *p);
extern void discord_sticker_pack_from_json_v(char *json, size_t len, void *pp);
extern void discord_sticker_pack_from_json(char *json, size_t len, struct discord_sticker_pack **pp);
extern size_t discord_sticker_pack_to_json_v(char *json, size_t len, void *p);
extern size_t discord_sticker_pack_to_json(char *json, size_t len, struct discord_sticker_pack *p);
extern void discord_sticker_pack_list_free_v(void **p);
extern void discord_sticker_pack_list_free(struct discord_sticker_pack **p);
extern void discord_sticker_pack_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_pack_list_from_json(char *str, size_t len, struct discord_sticker_pack ***p);
extern size_t discord_sticker_pack_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_pack_list_to_json(char *str, size_t len, struct discord_sticker_pack **p);
/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */

extern void discord_modify_current_user_params_cleanup_v(void *p);
extern void discord_modify_current_user_params_cleanup(struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_init_v(void *p);
extern void discord_modify_current_user_params_init(struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_current_user_params_from_json(char *json, size_t len, struct discord_modify_current_user_params **pp);
extern size_t discord_modify_current_user_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_user_params_to_json(char *json, size_t len, struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_list_free_v(void **p);
extern void discord_modify_current_user_params_list_free(struct discord_modify_current_user_params **p);
extern void discord_modify_current_user_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_current_user_params_list_from_json(char *str, size_t len, struct discord_modify_current_user_params ***p);
extern size_t discord_modify_current_user_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_current_user_params_list_to_json(char *str, size_t len, struct discord_modify_current_user_params **p);

extern void discord_create_dm_params_cleanup_v(void *p);
extern void discord_create_dm_params_cleanup(struct discord_create_dm_params *p);
extern void discord_create_dm_params_init_v(void *p);
extern void discord_create_dm_params_init(struct discord_create_dm_params *p);
extern void discord_create_dm_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_dm_params_from_json(char *json, size_t len, struct discord_create_dm_params **pp);
extern size_t discord_create_dm_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_dm_params_to_json(char *json, size_t len, struct discord_create_dm_params *p);
extern void discord_create_dm_params_list_free_v(void **p);
extern void discord_create_dm_params_list_free(struct discord_create_dm_params **p);
extern void discord_create_dm_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_dm_params_list_from_json(char *str, size_t len, struct discord_create_dm_params ***p);
extern size_t discord_create_dm_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_dm_params_list_to_json(char *str, size_t len, struct discord_create_dm_params **p);

extern void discord_create_group_dm_params_cleanup_v(void *p);
extern void discord_create_group_dm_params_cleanup(struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_init_v(void *p);
extern void discord_create_group_dm_params_init(struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_group_dm_params_from_json(char *json, size_t len, struct discord_create_group_dm_params **pp);
extern size_t discord_create_group_dm_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_group_dm_params_to_json(char *json, size_t len, struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_list_free_v(void **p);
extern void discord_create_group_dm_params_list_free(struct discord_create_group_dm_params **p);
extern void discord_create_group_dm_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_group_dm_params_list_from_json(char *str, size_t len, struct discord_create_group_dm_params ***p);
extern size_t discord_create_group_dm_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_group_dm_params_list_to_json(char *str, size_t len, struct discord_create_group_dm_params **p);
/* This file is generated from specs/discord/user.json, Please don't edit it. */





extern void discord_user_cleanup_v(void *p);
extern void discord_user_cleanup(struct discord_user *p);
extern void discord_user_init_v(void *p);
extern void discord_user_init(struct discord_user *p);
extern void discord_user_from_json_v(char *json, size_t len, void *pp);
extern void discord_user_from_json(char *json, size_t len, struct discord_user **pp);
extern size_t discord_user_to_json_v(char *json, size_t len, void *p);
extern size_t discord_user_to_json(char *json, size_t len, struct discord_user *p);
extern void discord_user_list_free_v(void **p);
extern void discord_user_list_free(struct discord_user **p);
extern void discord_user_list_from_json_v(char *str, size_t len, void *p);
extern void discord_user_list_from_json(char *str, size_t len, struct discord_user ***p);
extern size_t discord_user_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_user_list_to_json(char *str, size_t len, struct discord_user **p);



extern void discord_connection_cleanup_v(void *p);
extern void discord_connection_cleanup(struct discord_connection *p);
extern void discord_connection_init_v(void *p);
extern void discord_connection_init(struct discord_connection *p);
extern void discord_connection_from_json_v(char *json, size_t len, void *pp);
extern void discord_connection_from_json(char *json, size_t len, struct discord_connection **pp);
extern size_t discord_connection_to_json_v(char *json, size_t len, void *p);
extern size_t discord_connection_to_json(char *json, size_t len, struct discord_connection *p);
extern void discord_connection_list_free_v(void **p);
extern void discord_connection_list_free(struct discord_connection **p);
extern void discord_connection_list_from_json_v(char *str, size_t len, void *p);
extern void discord_connection_list_from_json(char *str, size_t len, struct discord_connection ***p);
extern size_t discord_connection_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_connection_list_to_json(char *str, size_t len, struct discord_connection **p);
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */






/* This file is generated from specs/discord/voice.json, Please don't edit it. */

extern void discord_voice_state_cleanup_v(void *p);
extern void discord_voice_state_cleanup(struct discord_voice_state *p);
extern void discord_voice_state_init_v(void *p);
extern void discord_voice_state_init(struct discord_voice_state *p);
extern void discord_voice_state_from_json_v(char *json, size_t len, void *pp);
extern void discord_voice_state_from_json(char *json, size_t len, struct discord_voice_state **pp);
extern size_t discord_voice_state_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_state_to_json(char *json, size_t len, struct discord_voice_state *p);
extern void discord_voice_state_list_free_v(void **p);
extern void discord_voice_state_list_free(struct discord_voice_state **p);
extern void discord_voice_state_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_state_list_from_json(char *str, size_t len, struct discord_voice_state ***p);
extern size_t discord_voice_state_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_state_list_to_json(char *str, size_t len, struct discord_voice_state **p);

extern void discord_voice_region_cleanup_v(void *p);
extern void discord_voice_region_cleanup(struct discord_voice_region *p);
extern void discord_voice_region_init_v(void *p);
extern void discord_voice_region_init(struct discord_voice_region *p);
extern void discord_voice_region_from_json_v(char *json, size_t len, void *pp);
extern void discord_voice_region_from_json(char *json, size_t len, struct discord_voice_region **pp);
extern size_t discord_voice_region_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_region_to_json(char *json, size_t len, struct discord_voice_region *p);
extern void discord_voice_region_list_free_v(void **p);
extern void discord_voice_region_list_free(struct discord_voice_region **p);
extern void discord_voice_region_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_region_list_from_json(char *str, size_t len, struct discord_voice_region ***p);
extern size_t discord_voice_region_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_region_list_to_json(char *str, size_t len, struct discord_voice_region **p);
/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */

extern void discord_create_webhook_params_cleanup_v(void *p);
extern void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_init_v(void *p);
extern void discord_create_webhook_params_init(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_webhook_params_from_json(char *json, size_t len, struct discord_create_webhook_params **pp);
extern size_t discord_create_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_webhook_params_to_json(char *json, size_t len, struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_list_free_v(void **p);
extern void discord_create_webhook_params_list_free(struct discord_create_webhook_params **p);
extern void discord_create_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_webhook_params_list_from_json(char *str, size_t len, struct discord_create_webhook_params ***p);
extern size_t discord_create_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_webhook_params_list_to_json(char *str, size_t len, struct discord_create_webhook_params **p);

extern void discord_modify_webhook_params_cleanup_v(void *p);
extern void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_init_v(void *p);
extern void discord_modify_webhook_params_init(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_webhook_params_from_json(char *json, size_t len, struct discord_modify_webhook_params **pp);
extern size_t discord_modify_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_webhook_params_to_json(char *json, size_t len, struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_list_free_v(void **p);
extern void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **p);
extern void discord_modify_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_webhook_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_params ***p);
extern size_t discord_modify_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_webhook_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_params **p);

extern void discord_modify_webhook_with_token_params_cleanup_v(void *p);
extern void discord_modify_webhook_with_token_params_cleanup(struct discord_modify_webhook_with_token_params *p);
extern void discord_modify_webhook_with_token_params_init_v(void *p);
extern void discord_modify_webhook_with_token_params_init(struct discord_modify_webhook_with_token_params *p);
extern void discord_modify_webhook_with_token_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_webhook_with_token_params_from_json(char *json, size_t len, struct discord_modify_webhook_with_token_params **pp);
extern size_t discord_modify_webhook_with_token_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_webhook_with_token_params_to_json(char *json, size_t len, struct discord_modify_webhook_with_token_params *p);
extern void discord_modify_webhook_with_token_params_list_free_v(void **p);
extern void discord_modify_webhook_with_token_params_list_free(struct discord_modify_webhook_with_token_params **p);
extern void discord_modify_webhook_with_token_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_webhook_with_token_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_with_token_params ***p);
extern size_t discord_modify_webhook_with_token_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_webhook_with_token_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_with_token_params **p);

extern void discord_execute_webhook_params_cleanup_v(void *p);
extern void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_init_v(void *p);
extern void discord_execute_webhook_params_init(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_execute_webhook_params_from_json(char *json, size_t len, struct discord_execute_webhook_params **pp);
extern size_t discord_execute_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_execute_webhook_params_to_json(char *json, size_t len, struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_list_free_v(void **p);
extern void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **p);
extern void discord_execute_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_execute_webhook_params_list_from_json(char *str, size_t len, struct discord_execute_webhook_params ***p);
extern size_t discord_execute_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_execute_webhook_params_list_to_json(char *str, size_t len, struct discord_execute_webhook_params **p);

extern void discord_edit_webhook_message_params_cleanup_v(void *p);
extern void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_init_v(void *p);
extern void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_edit_webhook_message_params **pp);
extern size_t discord_edit_webhook_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_to_json(char *json, size_t len, struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_list_free_v(void **p);
extern void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **p);
extern void discord_edit_webhook_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_webhook_message_params_list_from_json(char *str, size_t len, struct discord_edit_webhook_message_params ***p);
extern size_t discord_edit_webhook_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_list_to_json(char *str, size_t len, struct discord_edit_webhook_message_params **p);
/* This file is generated from specs/discord/webhook.json, Please don't edit it. */

extern void discord_webhook_cleanup_v(void *p);
extern void discord_webhook_cleanup(struct discord_webhook *p);
extern void discord_webhook_init_v(void *p);
extern void discord_webhook_init(struct discord_webhook *p);
extern void discord_webhook_from_json_v(char *json, size_t len, void *pp);
extern void discord_webhook_from_json(char *json, size_t len, struct discord_webhook **pp);
extern size_t discord_webhook_to_json_v(char *json, size_t len, void *p);
extern size_t discord_webhook_to_json(char *json, size_t len, struct discord_webhook *p);
extern void discord_webhook_list_free_v(void **p);
extern void discord_webhook_list_free(struct discord_webhook **p);
extern void discord_webhook_list_from_json_v(char *str, size_t len, void *p);
extern void discord_webhook_list_from_json(char *str, size_t len, struct discord_webhook ***p);
extern size_t discord_webhook_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_webhook_list_to_json(char *str, size_t len, struct discord_webhook **p);


