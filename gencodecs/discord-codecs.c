#include "discord-codecs.h"
#include <stdio.h>
#include <stdlib.h>
#include "carray.h"
static char *
_gc_strndup(const char *src, size_t len)
{
    char *dest = malloc(len + 1);
    memcpy(dest, src, len);
    dest[len] = '\0';
    return dest;
}

static void discord_role_tag_init(struct discord_role_tag *this);
static void discord_role_tag_cleanup(struct discord_role_tag *this);

static void discord_audit_log_entry_init(struct discord_audit_log_entry *this);
static void discord_audit_log_entry_cleanup(
    struct discord_audit_log_entry *this);

static void discord_audit_log_entries_cleanup(
    struct discord_audit_log_entries *this);

static void discord_optional_audit_entry_info_init(
    struct discord_optional_audit_entry_info *this);
static void discord_optional_audit_entry_info_cleanup(
    struct discord_optional_audit_entry_info *this);

static void discord_optional_audit_entry_infos_cleanup(
    struct discord_optional_audit_entry_infos *this);

static void discord_audit_log_change_init(
    struct discord_audit_log_change *this);
static void discord_audit_log_change_cleanup(
    struct discord_audit_log_change *this);

static void discord_audit_log_changes_cleanup(
    struct discord_audit_log_changes *this);

static void discord_get_guild_audit_log_init(
    struct discord_get_guild_audit_log *this);
static void discord_get_guild_audit_log_cleanup(
    struct discord_get_guild_audit_log *this);

static void discord_invite_metadata_init(struct discord_invite_metadata *this);
static void discord_invite_metadata_cleanup(
    struct discord_invite_metadata *this);

static void discord_invite_stage_instance_init(
    struct discord_invite_stage_instance *this);
static void discord_invite_stage_instance_cleanup(
    struct discord_invite_stage_instance *this);

static void discord_message_activity_init(
    struct discord_message_activity *this);
static void discord_message_activity_cleanup(
    struct discord_message_activity *this);

static void discord_message_reference_init(
    struct discord_message_reference *this);
static void discord_message_reference_cleanup(
    struct discord_message_reference *this);

static void discord_reaction_init(struct discord_reaction *this);
static void discord_reaction_cleanup(struct discord_reaction *this);

static void discord_reactions_cleanup(struct discord_reactions *this);

static void discord_overwrite_init(struct discord_overwrite *this);
static void discord_overwrite_cleanup(struct discord_overwrite *this);

static void discord_overwrites_cleanup(struct discord_overwrites *this);

static void discord_thread_metadata_init(struct discord_thread_metadata *this);
static void discord_thread_metadata_cleanup(
    struct discord_thread_metadata *this);

static void discord_thread_member_init(struct discord_thread_member *this);
static void discord_thread_member_cleanup(struct discord_thread_member *this);

static void discord_attachment_init(struct discord_attachment *this);
static void discord_attachment_cleanup(struct discord_attachment *this);

static void discord_channel_mention_init(struct discord_channel_mention *this);
static void discord_channel_mention_cleanup(
    struct discord_channel_mention *this);

static void discord_allowed_mention_init(struct discord_allowed_mention *this);
static void discord_allowed_mention_cleanup(
    struct discord_allowed_mention *this);

static void discord_guild_widget_setting_init(
    struct discord_guild_widget_setting *this);
static void discord_guild_widget_setting_cleanup(
    struct discord_guild_widget_setting *this);

static void discord_get_guild_widget_init(
    struct discord_get_guild_widget *this);
static void discord_get_guild_widget_cleanup(
    struct discord_get_guild_widget *this);

static void discord_integration_init(struct discord_integration *this);
static void discord_integration_cleanup(struct discord_integration *this);

static void discord_integrations_cleanup(struct discord_integrations *this);

static void discord_integration_account_init(
    struct discord_integration_account *this);
static void discord_integration_account_cleanup(
    struct discord_integration_account *this);

static void discord_integration_application_init(
    struct discord_integration_application *this);
static void discord_integration_application_cleanup(
    struct discord_integration_application *this);

static void discord_welcome_screen_channel_init(
    struct discord_welcome_screen_channel *this);
static void discord_welcome_screen_channel_cleanup(
    struct discord_welcome_screen_channel *this);

static void discord_welcome_screen_channels_cleanup(
    struct discord_welcome_screen_channels *this);

static void discord_modify_guild_channel_position_init(
    struct discord_modify_guild_channel_position *this);
static void discord_modify_guild_channel_position_cleanup(
    struct discord_modify_guild_channel_position *this);

static void discord_list_guild_members_init(
    struct discord_list_guild_members *this);
static void discord_list_guild_members_cleanup(
    struct discord_list_guild_members *this);

static void discord_search_guild_members_init(
    struct discord_search_guild_members *this);
static void discord_search_guild_members_cleanup(
    struct discord_search_guild_members *this);

static void discord_modify_guild_role_position_init(
    struct discord_modify_guild_role_position *this);
static void discord_modify_guild_role_position_cleanup(
    struct discord_modify_guild_role_position *this);

static void discord_get_guild_prune_count_init(
    struct discord_get_guild_prune_count *this);
static void discord_get_guild_prune_count_cleanup(
    struct discord_get_guild_prune_count *this);

static void discord_get_guild_widget_image_init(
    struct discord_get_guild_widget_image *this);
static void discord_get_guild_widget_image_cleanup(
    struct discord_get_guild_widget_image *this);

static void discord_guild_scheduled_event_entity_metadata_init(
    struct discord_guild_scheduled_event_entity_metadata *this);
static void discord_guild_scheduled_event_entity_metadata_cleanup(
    struct discord_guild_scheduled_event_entity_metadata *this);

static void discord_guild_scheduled_event_user_init(
    struct discord_guild_scheduled_event_user *this);
static void discord_guild_scheduled_event_user_cleanup(
    struct discord_guild_scheduled_event_user *this);

static void discord_stage_instances_cleanup(
    struct discord_stage_instances *this);

static void discord_stickers_cleanup(struct discord_stickers *this);

static void discord_sticker_item_init(struct discord_sticker_item *this);
static void discord_sticker_item_cleanup(struct discord_sticker_item *this);

static void discord_sticker_items_cleanup(struct discord_sticker_items *this);

static void discord_sticker_pack_init(struct discord_sticker_pack *this);
static void discord_sticker_pack_cleanup(struct discord_sticker_pack *this);

static void discord_create_guild_sticker_init(
    struct discord_create_guild_sticker *this);
static void discord_create_guild_sticker_cleanup(
    struct discord_create_guild_sticker *this);

static void discord_connection_init(struct discord_connection *this);
static void discord_connection_cleanup(struct discord_connection *this);

static void discord_get_current_user_guilds_init(
    struct discord_get_current_user_guilds *this);
static void discord_get_current_user_guilds_cleanup(
    struct discord_get_current_user_guilds *this);

static void discord_voice_region_init(struct discord_voice_region *this);
static void discord_voice_region_cleanup(struct discord_voice_region *this);

static void discord_get_webhook_message_init(
    struct discord_get_webhook_message *this);
static void discord_get_webhook_message_cleanup(
    struct discord_get_webhook_message *this);

static void discord_delete_webhook_message_init(
    struct discord_delete_webhook_message *this);
static void discord_delete_webhook_message_cleanup(
    struct discord_delete_webhook_message *this);

static void discord_identify_connection_init(
    struct discord_identify_connection *this);
static void discord_identify_connection_cleanup(
    struct discord_identify_connection *this);

static void discord_presence_updates_cleanup(
    struct discord_presence_updates *this);

static void discord_activity_init(struct discord_activity *this);
static void discord_activity_cleanup(struct discord_activity *this);

static void discord_activities_cleanup(struct discord_activities *this);

static void discord_activity_timestamps_init(
    struct discord_activity_timestamps *this);
static void discord_activity_timestamps_cleanup(
    struct discord_activity_timestamps *this);

static void discord_activity_emoji_init(struct discord_activity_emoji *this);
static void discord_activity_emoji_cleanup(
    struct discord_activity_emoji *this);

static void discord_activity_party_init(struct discord_activity_party *this);
static void discord_activity_party_cleanup(
    struct discord_activity_party *this);

static void discord_activity_assets_init(struct discord_activity_assets *this);
static void discord_activity_assets_cleanup(
    struct discord_activity_assets *this);

static void discord_activity_secrets_init(
    struct discord_activity_secrets *this);
static void discord_activity_secrets_cleanup(
    struct discord_activity_secrets *this);

static void discord_activity_button_init(struct discord_activity_button *this);
static void discord_activity_button_cleanup(
    struct discord_activity_button *this);

static void discord_activity_buttons_cleanup(
    struct discord_activity_buttons *this);

static void discord_team_member_init(struct discord_team_member *this);
static void discord_team_member_cleanup(struct discord_team_member *this);

static void discord_team_members_cleanup(struct discord_team_members *this);

static void discord_application_command_option_init(
    struct discord_application_command_option *this);
static void discord_application_command_option_cleanup(
    struct discord_application_command_option *this);

static void discord_application_command_options_cleanup(
    struct discord_application_command_options *this);

static void discord_application_command_option_choice_init(
    struct discord_application_command_option_choice *this);
static void discord_application_command_option_choice_cleanup(
    struct discord_application_command_option_choice *this);

static void discord_application_command_option_choices_cleanup(
    struct discord_application_command_option_choices *this);

static void discord_application_command_interaction_data_option_init(
    struct discord_application_command_interaction_data_option *this);
static void discord_application_command_interaction_data_option_cleanup(
    struct discord_application_command_interaction_data_option *this);

static void discord_application_command_interaction_data_options_cleanup(
    struct discord_application_command_interaction_data_options *this);

static void discord_guild_application_command_permission_init(
    struct discord_guild_application_command_permission *this);
static void discord_guild_application_command_permission_cleanup(
    struct discord_guild_application_command_permission *this);

static void discord_select_option_init(struct discord_select_option *this);
static void discord_select_option_cleanup(struct discord_select_option *this);

static void discord_interaction_data_init(
    struct discord_interaction_data *this);
static void discord_interaction_data_cleanup(
    struct discord_interaction_data *this);

static void discord_resolved_data_init(struct discord_resolved_data *this);
static void discord_resolved_data_cleanup(struct discord_resolved_data *this);

static void discord_message_interaction_init(
    struct discord_message_interaction *this);
static void discord_message_interaction_cleanup(
    struct discord_message_interaction *this);

static void discord_interaction_callback_data_init(
    struct discord_interaction_callback_data *this);
static void discord_interaction_callback_data_cleanup(
    struct discord_interaction_callback_data *this);

static size_t discord_role_tag_from_jsmnf(jsmnf *root,
                                          const char buf[],
                                          struct discord_role_tag *this);

static size_t discord_audit_log_entry_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_audit_log_entry *this);

static size_t discord_audit_log_entries_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_audit_log_entries *this);

static size_t discord_optional_audit_entry_info_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_optional_audit_entry_info *this);

static size_t discord_optional_audit_entry_infos_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_optional_audit_entry_infos *this);

static size_t discord_audit_log_change_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_audit_log_change *this);

static size_t discord_audit_log_changes_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_audit_log_changes *this);

static size_t discord_get_guild_audit_log_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_guild_audit_log *this);

static size_t discord_invite_metadata_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_invite_metadata *this);

static size_t discord_invite_stage_instance_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_invite_stage_instance *this);

static size_t discord_message_activity_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_message_activity *this);

static size_t discord_message_reference_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_message_reference *this);

static size_t discord_reaction_from_jsmnf(jsmnf *root,
                                          const char buf[],
                                          struct discord_reaction *this);

static size_t discord_reactions_from_jsmnf(jsmnf *root,
                                           const char buf[],
                                           struct discord_reactions *this);

static size_t discord_overwrite_from_jsmnf(jsmnf *root,
                                           const char buf[],
                                           struct discord_overwrite *this);

static size_t discord_overwrites_from_jsmnf(jsmnf *root,
                                            const char buf[],
                                            struct discord_overwrites *this);

static size_t discord_thread_metadata_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_thread_metadata *this);

static size_t discord_thread_member_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_thread_member *this);

static size_t discord_attachment_from_jsmnf(jsmnf *root,
                                            const char buf[],
                                            struct discord_attachment *this);

static size_t discord_channel_mention_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_channel_mention *this);

static size_t discord_allowed_mention_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_allowed_mention *this);

static size_t discord_guild_widget_setting_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_guild_widget_setting *this);

static size_t discord_get_guild_widget_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_guild_widget *this);

static size_t discord_integration_from_jsmnf(jsmnf *root,
                                             const char buf[],
                                             struct discord_integration *this);

static size_t discord_integrations_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_integrations *this);

static size_t discord_integration_account_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_integration_account *this);

static size_t discord_integration_application_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_integration_application *this);

static size_t discord_welcome_screen_channel_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_welcome_screen_channel *this);

static size_t discord_welcome_screen_channels_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_welcome_screen_channels *this);

static size_t discord_modify_guild_channel_position_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_guild_channel_position *this);

static size_t discord_list_guild_members_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_list_guild_members *this);

static size_t discord_search_guild_members_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_search_guild_members *this);

static size_t discord_modify_guild_role_position_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_guild_role_position *this);

static size_t discord_get_guild_prune_count_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_guild_prune_count *this);

static size_t discord_get_guild_widget_image_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_get_guild_widget_image *this);

static size_t discord_guild_scheduled_event_entity_metadata_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_guild_scheduled_event_entity_metadata *this);

static size_t discord_guild_scheduled_event_user_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_guild_scheduled_event_user *this);

static size_t discord_stage_instances_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_stage_instances *this);

static size_t discord_stickers_from_jsmnf(jsmnf *root,
                                          const char buf[],
                                          struct discord_stickers *this);

static size_t discord_sticker_item_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_sticker_item *this);

static size_t discord_sticker_items_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_sticker_items *this);

static size_t discord_sticker_pack_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_sticker_pack *this);

static size_t discord_create_guild_sticker_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_guild_sticker *this);

static size_t discord_connection_from_jsmnf(jsmnf *root,
                                            const char buf[],
                                            struct discord_connection *this);

static size_t discord_get_current_user_guilds_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_get_current_user_guilds *this);

static size_t discord_voice_region_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_voice_region *this);

static size_t discord_get_webhook_message_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_webhook_message *this);

static size_t discord_delete_webhook_message_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_delete_webhook_message *this);

static size_t discord_identify_connection_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_identify_connection *this);

static size_t discord_presence_updates_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_presence_updates *this);

static size_t discord_activity_from_jsmnf(jsmnf *root,
                                          const char buf[],
                                          struct discord_activity *this);

static size_t discord_activities_from_jsmnf(jsmnf *root,
                                            const char buf[],
                                            struct discord_activities *this);

static size_t discord_activity_timestamps_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_activity_timestamps *this);

static size_t discord_activity_emoji_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_activity_emoji *this);

static size_t discord_activity_party_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_activity_party *this);

static size_t discord_activity_assets_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_activity_assets *this);

static size_t discord_activity_secrets_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_activity_secrets *this);

static size_t discord_activity_button_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_activity_button *this);

static size_t discord_activity_buttons_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_activity_buttons *this);

static size_t discord_team_member_from_jsmnf(jsmnf *root,
                                             const char buf[],
                                             struct discord_team_member *this);

static size_t discord_team_members_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_team_members *this);

static size_t discord_application_command_option_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_option *this);

static size_t discord_application_command_options_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_options *this);

static size_t discord_application_command_option_choice_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_option_choice *this);

static size_t discord_application_command_option_choices_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_option_choices *this);

static size_t discord_application_command_interaction_data_option_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_interaction_data_option *this);

static size_t discord_application_command_interaction_data_options_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_interaction_data_options *this);

static size_t discord_guild_application_command_permission_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_guild_application_command_permission *this);

static size_t discord_select_option_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_select_option *this);

static size_t discord_interaction_data_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_interaction_data *this);

static size_t discord_resolved_data_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_resolved_data *this);

static size_t discord_message_interaction_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_message_interaction *this);

static size_t discord_interaction_callback_data_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_interaction_callback_data *this);

static jsonbcode discord_role_tag_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_role_tag *this);

static jsonbcode discord_audit_log_entry_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_audit_log_entry *this);

static jsonbcode discord_audit_log_entries_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_audit_log_entries *this);

static jsonbcode discord_optional_audit_entry_info_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_optional_audit_entry_info *this);

static jsonbcode discord_optional_audit_entry_infos_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_optional_audit_entry_infos *this);

static jsonbcode discord_audit_log_change_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_audit_log_change *this);

static jsonbcode discord_audit_log_changes_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_audit_log_changes *this);

static jsonbcode discord_get_guild_audit_log_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_audit_log *this);

static jsonbcode discord_invite_metadata_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_invite_metadata *this);

static jsonbcode discord_invite_stage_instance_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_invite_stage_instance *this);

static jsonbcode discord_message_activity_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_message_activity *this);

static jsonbcode discord_message_reference_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_message_reference *this);

static jsonbcode discord_reaction_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_reaction *this);

static jsonbcode discord_reactions_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_reactions *this);

static jsonbcode discord_overwrite_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_overwrite *this);

static jsonbcode discord_overwrites_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_overwrites *this);

static jsonbcode discord_thread_metadata_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_thread_metadata *this);

static jsonbcode discord_thread_member_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_thread_member *this);

static jsonbcode discord_attachment_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_attachment *this);

static jsonbcode discord_channel_mention_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_channel_mention *this);

static jsonbcode discord_allowed_mention_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_allowed_mention *this);

static jsonbcode discord_guild_widget_setting_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_widget_setting *this);

static jsonbcode discord_get_guild_widget_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_widget *this);

static jsonbcode discord_integration_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_integration *this);

static jsonbcode discord_integrations_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_integrations *this);

static jsonbcode discord_integration_account_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_integration_account *this);

static jsonbcode discord_integration_application_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_integration_application *this);

static jsonbcode discord_welcome_screen_channel_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_welcome_screen_channel *this);

static jsonbcode discord_welcome_screen_channels_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_welcome_screen_channels *this);

static jsonbcode discord_modify_guild_channel_position_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_channel_position *this);

static jsonbcode discord_list_guild_members_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_list_guild_members *this);

static jsonbcode discord_search_guild_members_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_search_guild_members *this);

static jsonbcode discord_modify_guild_role_position_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_role_position *this);

static jsonbcode discord_get_guild_prune_count_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_prune_count *this);

static jsonbcode discord_get_guild_widget_image_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_widget_image *this);

static jsonbcode discord_guild_scheduled_event_entity_metadata_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_scheduled_event_entity_metadata *this);

static jsonbcode discord_guild_scheduled_event_user_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_scheduled_event_user *this);

static jsonbcode discord_stage_instances_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_stage_instances *this);

static jsonbcode discord_stickers_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_stickers *this);

static jsonbcode discord_sticker_item_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_sticker_item *this);

static jsonbcode discord_sticker_items_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_sticker_items *this);

static jsonbcode discord_sticker_pack_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_sticker_pack *this);

static jsonbcode discord_create_guild_sticker_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_sticker *this);

static jsonbcode discord_connection_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_connection *this);

static jsonbcode discord_get_current_user_guilds_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_current_user_guilds *this);

static jsonbcode discord_voice_region_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_voice_region *this);

static jsonbcode discord_get_webhook_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_webhook_message *this);

static jsonbcode discord_delete_webhook_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_delete_webhook_message *this);

static jsonbcode discord_identify_connection_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_identify_connection *this);

static jsonbcode discord_presence_updates_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_presence_updates *this);

static jsonbcode discord_activity_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_activity *this);

static jsonbcode discord_activities_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_activities *this);

static jsonbcode discord_activity_timestamps_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_activity_timestamps *this);

static jsonbcode discord_activity_emoji_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_activity_emoji *this);

static jsonbcode discord_activity_party_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_activity_party *this);

static jsonbcode discord_activity_assets_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_activity_assets *this);

static jsonbcode discord_activity_secrets_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_activity_secrets *this);

static jsonbcode discord_activity_button_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_activity_button *this);

static jsonbcode discord_activity_buttons_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_activity_buttons *this);

static jsonbcode discord_team_member_to_jsonb(
    jsonb *b, char buf[], size_t size, const struct discord_team_member *this);

static jsonbcode discord_team_members_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_team_members *this);

static jsonbcode discord_application_command_option_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_option *this);

static jsonbcode discord_application_command_options_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_options *this);

static jsonbcode discord_application_command_option_choice_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_option_choice *this);

static jsonbcode discord_application_command_option_choices_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_option_choices *this);

static jsonbcode discord_application_command_interaction_data_option_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_interaction_data_option *this);

static jsonbcode discord_application_command_interaction_data_options_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_interaction_data_options *this);

static jsonbcode discord_guild_application_command_permission_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_application_command_permission *this);

static jsonbcode discord_select_option_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_select_option *this);

static jsonbcode discord_interaction_data_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_interaction_data *this);

static jsonbcode discord_resolved_data_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_resolved_data *this);

static jsonbcode discord_message_interaction_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_message_interaction *this);

static jsonbcode discord_interaction_callback_data_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_interaction_callback_data *this);

#include <stdio.h>
#include <stdlib.h>
#include "carray.h"

void
discord_role_init(struct discord_role *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->color = 0;

    this->hoist = false;

    this->icon = NULL;

    this->unicode_emoji = NULL;

    this->position = 0;

    this->permissions = NULL;

    this->managed = false;

    this->mentionable = false;

    this->tags = NULL;
}

static void
discord_role_tag_init(struct discord_role_tag *this)
{

    this->bot_id = (u64snowflake)0;

    this->integration_id = (u64snowflake)0;

    this->premium_subscribe = false;
}

void
discord_application_init(struct discord_application *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->icon = NULL;

    this->description = NULL;

    this->rpc_origins = NULL;

    this->bot_public = false;

    this->bot_require_code_grant = false;

    this->terms_of_service_url = NULL;

    this->privacy_policy_url = NULL;

    this->owner = NULL;

    this->summary = NULL;

    this->verify_key = NULL;

    this->team = NULL;

    this->guild_id = (u64snowflake)0;

    this->primary_sku_id = (u64snowflake)0;

    this->slug = NULL;

    this->cover_image = NULL;

    this->flags = (u64snowflake)0;
}

void
discord_audit_log_init(struct discord_audit_log *this)
{

    this->audit_log_entries = NULL;

    this->guild_scheduled_events = NULL;

    this->integrations = NULL;

    this->threads = NULL;

    this->users = NULL;

    this->webhooks = NULL;
}
static void
discord_audit_log_entry_init(struct discord_audit_log_entry *this)
{

    this->target_id = (u64snowflake)0;

    this->changes = NULL;

    this->user_id = (u64snowflake)0;

    this->id = (u64snowflake)0;

    this->action_type = 0;

    this->options = NULL;

    this->reason = NULL;
}

static void
discord_optional_audit_entry_info_init(
    struct discord_optional_audit_entry_info *this)
{

    this->channel_id = (u64snowflake)0;

    this->count = NULL;

    this->delete_member_days = NULL;

    this->id = (u64snowflake)0;

    this->members_removed = NULL;

    this->message_id = (u64snowflake)0;

    this->role_name = NULL;

    this->type = NULL;
}

static void
discord_audit_log_change_init(struct discord_audit_log_change *this)
{

    this->new_value = NULL;

    this->old_value = NULL;

    this->key = NULL;
}

static void
discord_get_guild_audit_log_init(struct discord_get_guild_audit_log *this)
{

    this->user_id = (u64snowflake)0;

    this->action_type = 0;

    this->before = (u64snowflake)0;

    this->limit = 50;
}

void
discord_invite_init(struct discord_invite *this)
{

    this->code = NULL;

    this->guild = NULL;

    this->channel = NULL;

    this->inviter = NULL;

    this->target_type = 0;

    this->target_user = NULL;

    this->target_application = NULL;

    this->approximate_presence_count = 0;

    this->approximate_member_count = 0;

    this->expires_at = (u64unix_ms)0;

    this->stage_instance = NULL;

    this->guild_scheduled_event = NULL;
}

static void
discord_invite_metadata_init(struct discord_invite_metadata *this)
{

    this->uses = 0;

    this->max_uses = 0;

    this->max_age = 0;

    this->temporary = false;

    this->created_at = (u64unix_ms)0;
}
static void
discord_invite_stage_instance_init(struct discord_invite_stage_instance *this)
{

    this->members = NULL;

    this->participant_count = 0;

    this->speaker_count = 0;

    this->topic = NULL;
}
void
discord_get_invite_init(struct discord_get_invite *this)
{

    this->with_counts = false;

    this->with_expiration = false;

    this->guild_scheduled_event_id = (u64snowflake)0;
}

void
discord_channel_init(struct discord_channel *this)
{

    this->id = (u64snowflake)0;

    this->type = 0;

    this->guild_id = (u64snowflake)0;

    this->position = 0;

    this->permission_overwrites = NULL;

    this->name = NULL;

    this->topic = NULL;

    this->nsfw = false;

    this->last_message_id = (u64snowflake)0;

    this->bitrate = 0;

    this->user_limit = 0;

    this->rate_limit_per_user = 0;

    this->recipients = NULL;

    this->icon = NULL;

    this->owner_id = (u64snowflake)0;

    this->application_id = (u64snowflake)0;

    this->parent_id = (u64snowflake)0;

    this->last_pin_timestamp = (u64unix_ms)0;

    this->rtc_region = NULL;

    this->voice_quality_mode = 0;

    this->message_count = 0;

    this->member_count = 0;

    this->thread_metadata = NULL;

    this->member = NULL;

    this->default_auto_archive_duration = 0;

    this->permissions = NULL;
}

void
discord_message_init(struct discord_message *this)
{

    this->id = (u64snowflake)0;

    this->channel_id = (u64snowflake)0;

    this->guild_id = (u64snowflake)0;

    this->author = NULL;

    this->member = NULL;

    this->content = NULL;

    this->timestamp = (u64unix_ms)0;

    this->edited_timestamp = (u64unix_ms)0;

    this->tts = false;

    this->mention_everyone = false;

    this->mentions = NULL;

    this->mention_roles = NULL;

    this->mention_channels = NULL;

    this->attachments = NULL;

    this->embeds = NULL;

    this->reactions = NULL;

    this->nonce = NULL;

    this->pinned = false;

    this->webhook_id = (u64snowflake)0;

    this->type = 0;

    this->activity = NULL;

    this->application = NULL;

    this->application_id = (u64snowflake)0;

    this->message_reference = NULL;

    this->flags = 0;

    this->referenced_message = NULL;

    this->interaction = NULL;

    this->thread = NULL;

    this->components = NULL;

    this->sticker_items = NULL;
}

static void
discord_message_activity_init(struct discord_message_activity *this)
{

    this->type = 0;

    this->party_id = NULL;
}
static void
discord_message_reference_init(struct discord_message_reference *this)
{

    this->message_id = (u64snowflake)0;

    this->channel_id = (u64snowflake)0;

    this->guild_id = (u64snowflake)0;

    this->fail_if_not_exists = true;
}
void
discord_followed_channel_init(struct discord_followed_channel *this)
{

    this->channel_id = (u64snowflake)0;

    this->webhook_id = (u64snowflake)0;
}
static void
discord_reaction_init(struct discord_reaction *this)
{

    this->count = 0;

    this->me = false;

    this->emoji = NULL;
}

static void
discord_overwrite_init(struct discord_overwrite *this)
{

    this->id = (u64snowflake)0;

    this->type = 0;

    this->allow = (u64snowflake)0;

    this->deny = (u64snowflake)0;
}

static void
discord_thread_metadata_init(struct discord_thread_metadata *this)
{

    this->archived = false;

    this->auto_archive_duration = 0;

    this->archive_timestamp = (u64unix_ms)0;

    this->locked = false;

    this->invitable = false;

    this->create_timestamp = (u64unix_ms)0;
}
static void
discord_thread_member_init(struct discord_thread_member *this)
{

    this->id = (u64snowflake)0;

    this->user_id = (u64snowflake)0;

    this->join_timestamp = (u64unix_ms)0;

    this->flags = 0;
}

static void
discord_attachment_init(struct discord_attachment *this)
{

    this->content = NULL;

    this->id = (u64snowflake)0;

    this->filename = NULL;

    this->description = NULL;

    this->content_type = NULL;

    this->size = 0;

    this->url = NULL;

    this->proxy_url = NULL;

    this->height = 0;

    this->width = 0;

    this->ephemeral = false;
}

void
discord_embed_init(struct discord_embed *this)
{

    this->title = NULL;

    this->type = NULL;

    this->description = NULL;

    this->url = NULL;

    this->timestamp = (u64unix_ms)0;

    this->color = 0;

    this->footer = NULL;

    this->image = NULL;

    this->thumbnail = NULL;

    this->video = NULL;

    this->provider = NULL;

    this->author = NULL;

    this->fields = NULL;
}

void
discord_embed_thumbnail_init(struct discord_embed_thumbnail *this)
{

    this->url = NULL;

    this->proxy_url = NULL;

    this->height = 0;

    this->width = 0;
}
void
discord_embed_video_init(struct discord_embed_video *this)
{

    this->url = NULL;

    this->proxy_url = NULL;

    this->height = 0;

    this->width = 0;
}
void
discord_embed_image_init(struct discord_embed_image *this)
{

    this->url = NULL;

    this->proxy_url = NULL;

    this->height = 0;

    this->width = 0;
}
void
discord_embed_provider_init(struct discord_embed_provider *this)
{

    this->name = NULL;

    this->url = NULL;
}
void
discord_embed_author_init(struct discord_embed_author *this)
{

    this->name = NULL;

    this->url = NULL;

    this->icon_url = NULL;

    this->proxy_icon_url = NULL;
}
void
discord_embed_footer_init(struct discord_embed_footer *this)
{

    this->text = NULL;

    this->icon_url = NULL;

    this->proxy_icon_url = NULL;
}
void
discord_embed_field_init(struct discord_embed_field *this)
{

    this->name = NULL;

    this->value = NULL;

    this->Inline = false;
}

static void
discord_channel_mention_init(struct discord_channel_mention *this)
{

    this->id = (u64snowflake)0;

    this->guild_id = (u64snowflake)0;

    this->type = 0;

    this->name = NULL;
}
static void
discord_allowed_mention_init(struct discord_allowed_mention *this)
{

    this->parse = NULL;

    this->roles = NULL;

    this->users = NULL;

    this->replied_user = false;
}
void
discord_thread_response_body_init(struct discord_thread_response_body *this)
{

    this->threads = NULL;

    this->members = NULL;

    this->has_more = false;
}
void
discord_modify_channel_init(struct discord_modify_channel *this)
{

    this->name = NULL;

    this->type = 0;

    this->position = 0;

    this->topic = NULL;

    this->nsfw = false;

    this->rate_limit_per_user = 0;

    this->user_limit = 0;

    this->permission_overwrites = NULL;

    this->parent_id = (u64snowflake)0;

    this->rtc_region = NULL;

    this->video_quality_mode = 0;

    this->default_auto_archive_duration = 0;

    this->archived = false;

    this->auto_archive_duration = 0;

    this->locked = false;

    this->invitable = false;
}
void
discord_get_channel_messages_init(struct discord_get_channel_messages *this)
{

    this->around = (u64snowflake)0;

    this->before = (u64snowflake)0;

    this->after = (u64snowflake)0;

    this->limit = 50;
}
void
discord_create_message_init(struct discord_create_message *this)
{

    this->content = NULL;

    this->tts = false;

    this->embeds = NULL;

    this->allowed_mentions = NULL;

    this->message_reference = NULL;

    this->components = NULL;

    this->sticker_ids = NULL;

    this->attachments = NULL;

    this->flags = 0;
}
void
discord_get_reactions_init(struct discord_get_reactions *this)
{

    this->after = (u64snowflake)0;

    this->limit = 0;
}
void
discord_edit_message_init(struct discord_edit_message *this)
{

    this->content = NULL;

    this->embeds = NULL;

    this->flags = 0;

    this->allowed_mentions = NULL;

    this->components = NULL;

    this->attachments = NULL;
}
void
discord_bulk_delete_messages_init(struct discord_bulk_delete_messages *this)
{

    this->messages = NULL;
}
void
discord_edit_channel_permissions_init(
    struct discord_edit_channel_permissions *this)
{

    this->allow = (u64bitmask)0;

    this->deny = (u64bitmask)0;

    this->type = 0;
}
void
discord_create_channel_invite_init(struct discord_create_channel_invite *this)
{

    this->max_age = 86400;

    this->max_uses = 0;

    this->temporary = false;

    this->unique = false;

    this->target_type = 0;

    this->target_user_id = (u64snowflake)0;

    this->target_application_id = (u64snowflake)0;
}
void
discord_follow_news_channel_init(struct discord_follow_news_channel *this)
{

    this->webhook_channel_id = (u64snowflake)0;
}
void
discord_group_dm_add_recipient_init(
    struct discord_group_dm_add_recipient *this)
{

    this->access_token = NULL;

    this->nick = NULL;
}
void
discord_start_thread_with_message_init(
    struct discord_start_thread_with_message *this)
{

    this->name = NULL;

    this->auto_archive_duration = 0;

    this->rate_limit_per_user = 0;
}
void
discord_start_thread_without_message_init(
    struct discord_start_thread_without_message *this)
{

    this->name = NULL;

    this->auto_archive_duration = 0;

    this->type = 0;

    this->invitable = false;

    this->rate_limit_per_user = 0;
}
void
discord_list_active_threads_init(struct discord_list_active_threads *this)
{

    this->threads = NULL;

    this->members = NULL;

    this->has_more = false;
}
void
discord_emoji_init(struct discord_emoji *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->roles = NULL;

    this->user = NULL;

    this->require_colons = false;

    this->managed = false;

    this->animated = false;

    this->available = false;
}

void
discord_create_guild_emoji_init(struct discord_create_guild_emoji *this)
{

    this->name = NULL;

    this->image = NULL;

    this->roles = NULL;
}
void
discord_modify_guild_emoji_init(struct discord_modify_guild_emoji *this)
{

    this->name = NULL;

    this->image = NULL;

    this->roles = NULL;
}

void
discord_guild_init(struct discord_guild *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->icon = NULL;

    this->icon_hash = NULL;

    this->splash = NULL;

    this->discovery_splash = NULL;

    this->owner = false;

    this->owner_id = (u64snowflake)0;

    this->permissions = NULL;

    this->afk_channel_id = (u64snowflake)0;

    this->afk_timeout = 0;

    this->widget_enabled = false;

    this->widget_channel_id = (u64snowflake)0;

    this->verification_level = 0;

    this->default_message_notifications = 0;

    this->explicit_content_filter = 0;

    this->roles = NULL;

    this->emojis = NULL;

    this->features = NULL;

    this->mfa_level = 0;

    this->application_id = (u64snowflake)0;

    this->system_channel_id = (u64snowflake)0;

    this->system_channel_flags = 0;

    this->rules_channel_id = (u64snowflake)0;

    this->joined_at = (u64unix_ms)0;

    this->large = false;

    this->unavailable = false;

    this->member_count = 0;

    this->voice_states = NULL;

    this->members = NULL;

    this->channels = NULL;

    this->threads = NULL;

    this->presences = NULL;

    this->max_presences = 0;

    this->max_members = 0;

    this->vanity_url_code = NULL;

    this->description = NULL;

    this->banner = NULL;

    this->premium_tier = 0;

    this->premium_subscription_count = 0;

    this->preferred_locale = NULL;

    this->public_updates_channel_id = (u64snowflake)0;

    this->max_video_channel_users = 0;

    this->approximate_member_count = 0;

    this->approximate_presence_count = 0;

    this->welcome_screen = NULL;

    this->nsfw_level = 0;

    this->stage_instances = NULL;

    this->stickers = NULL;

    this->guild_scheduled_events = NULL;

    this->premium_progress_bar_enabled = false;
}

void
discord_guild_preview_init(struct discord_guild_preview *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->icon = NULL;

    this->splash = NULL;

    this->discovery_splash = NULL;

    this->emojis = NULL;

    this->features = NULL;

    this->approximate_member_count = 0;

    this->approximate_presence_count = 0;

    this->description = NULL;

    this->stickers = NULL;
}
static void
discord_guild_widget_setting_init(struct discord_guild_widget_setting *this)
{

    this->enabled = false;

    this->channel_id = (u64snowflake)0;
}
static void
discord_get_guild_widget_init(struct discord_get_guild_widget *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->instant_invite = NULL;

    this->channels = NULL;

    this->members = NULL;

    this->presence_count = 0;
}
void
discord_guild_member_init(struct discord_guild_member *this)
{

    this->user = NULL;

    this->nick = NULL;

    this->avatar = NULL;

    this->roles = NULL;

    this->joined_at = (u64unix_ms)0;

    this->premium_since = (u64unix_ms)0;

    this->deaf = false;

    this->muted = false;

    this->pending = false;

    this->permissions = NULL;

    this->communication_disabled_until = (u64unix_ms)0;
}

static void
discord_integration_init(struct discord_integration *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->type = NULL;

    this->enabled = false;

    this->syncing = false;

    this->role_id = (u64snowflake)0;

    this->enable_emoticons = false;

    this->expire_behavior = 0;

    this->expire_grace_period = 0;

    this->user = NULL;

    this->account = NULL;

    this->synced_at = (u64unix_ms)0;

    this->subscriber_count = 0;

    this->revoked = false;

    this->application = NULL;
}

static void
discord_integration_account_init(struct discord_integration_account *this)
{

    this->id = NULL;

    this->name = NULL;
}
static void
discord_integration_application_init(
    struct discord_integration_application *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->icon = NULL;

    this->description = NULL;

    this->summary = NULL;

    this->bot = NULL;
}
void
discord_ban_init(struct discord_ban *this)
{

    this->reason = NULL;

    this->user = NULL;
}

void
discord_welcome_screen_init(struct discord_welcome_screen *this)
{

    this->description = NULL;

    this->welcome_channels = NULL;
}
static void
discord_welcome_screen_channel_init(
    struct discord_welcome_screen_channel *this)
{

    this->channel_id = (u64snowflake)0;

    this->description = NULL;

    this->emoji_id = (u64snowflake)0;

    this->emoji_name = NULL;
}

void
discord_create_guild_init(struct discord_create_guild *this)
{

    this->name = NULL;

    this->region = NULL;

    this->icon = NULL;

    this->verification_level = 0;

    this->default_message_notifications = 0;

    this->explicit_content_filter = 0;

    this->roles = NULL;

    this->channels = NULL;

    this->afk_channel_id = (u64snowflake)0;

    this->afk_timeout = 0;

    this->system_channel_id = (u64snowflake)0;

    this->system_channel_flags = 0;
}
void
discord_modify_guild_init(struct discord_modify_guild *this)
{

    this->name = NULL;

    this->verification_level = 0;

    this->default_message_notifications = 0;

    this->explicit_content_filter = 0;

    this->afk_channel_id = (u64snowflake)0;

    this->afk_timeout = 0;

    this->icon = NULL;

    this->owner_id = (u64snowflake)0;

    this->splash = NULL;

    this->discovery_splash = NULL;

    this->banner = NULL;

    this->system_channel_id = (u64snowflake)0;

    this->system_channel_flags = 0;

    this->rules_channel_id = (u64snowflake)0;

    this->public_updates_channel_id = (u64snowflake)0;

    this->preferred_locale = NULL;

    this->features = NULL;

    this->description = NULL;

    this->premium_progress_bar_enabled = false;
}
void
discord_create_guild_channel_init(struct discord_create_guild_channel *this)
{

    this->name = NULL;

    this->type = 0;

    this->topic = NULL;

    this->bitrate = 0;

    this->user_limit = 0;

    this->rate_limit_per_user = 0;

    this->position = 0;

    this->permission_overwrites = NULL;

    this->parent_id = (u64snowflake)0;

    this->nsfw = false;
}
static void
discord_modify_guild_channel_position_init(
    struct discord_modify_guild_channel_position *this)
{

    this->id = (u64snowflake)0;

    this->position = 0;

    this->lock_category = false;

    this->parent_id = (u64snowflake)0;
}

void
discord_list_active_guild_threads_init(
    struct discord_list_active_guild_threads *this)
{

    this->threads = NULL;

    this->members = NULL;
}
static void
discord_list_guild_members_init(struct discord_list_guild_members *this)
{

    this->limit = 0;

    this->after = (u64snowflake)0;
}
static void
discord_search_guild_members_init(struct discord_search_guild_members *this)
{

    this->query = NULL;

    this->limit = 0;
}
void
discord_add_guild_member_init(struct discord_add_guild_member *this)
{

    this->access_token = NULL;

    this->nick = NULL;

    this->roles = NULL;

    this->mute = false;

    this->deaf = false;
}
void
discord_modify_guild_member_init(struct discord_modify_guild_member *this)
{

    this->nick = NULL;

    this->roles = NULL;

    this->mute = false;

    this->deaf = false;

    this->channel_id = (u64snowflake)0;

    this->communication_disabled_until = (u64unix_ms)0;
}
void
discord_modify_current_member_init(struct discord_modify_current_member *this)
{

    this->nick = NULL;
}
void
discord_modify_current_user_nick_init(
    struct discord_modify_current_user_nick *this)
{

    this->nick = NULL;
}
void
discord_create_guild_ban_init(struct discord_create_guild_ban *this)
{

    this->delete_message_days = 0;

    this->reason = NULL;
}
void
discord_create_guild_role_init(struct discord_create_guild_role *this)
{

    this->name = NULL;

    this->permissions = (u64snowflake)0;

    this->color = 0;

    this->hoist = false;

    this->icon = NULL;

    this->unicode_emoji = NULL;

    this->mentionable = false;
}
static void
discord_modify_guild_role_position_init(
    struct discord_modify_guild_role_position *this)
{

    this->id = (u64snowflake)0;

    this->position = 0;
}

void
discord_modify_guild_role_init(struct discord_modify_guild_role *this)
{

    this->name = NULL;

    this->permissions = (u64snowflake)0;

    this->color = 0;

    this->hoist = false;

    this->icon = NULL;

    this->unicode_emoji = NULL;

    this->mentionable = false;
}
static void
discord_get_guild_prune_count_init(struct discord_get_guild_prune_count *this)
{

    this->count = 7;

    this->include_roles = NULL;
}
void
discord_begin_guild_prune_init(struct discord_begin_guild_prune *this)
{

    this->days = 7;

    this->compute_prune_count = true;

    this->include_roles = NULL;

    this->reason = NULL;
}
static void
discord_get_guild_widget_image_init(
    struct discord_get_guild_widget_image *this)
{

    this->style = NULL;
}
void
discord_modify_guild_welcome_screen_init(
    struct discord_modify_guild_welcome_screen *this)
{

    this->enabled = false;

    this->welcome_channels = NULL;

    this->description = NULL;
}
void
discord_modify_current_user_voice_state_init(
    struct discord_modify_current_user_voice_state *this)
{

    this->channel_id = (u64snowflake)0;

    this->suppress = false;

    this->request_to_speak_timestamp = (u64unix_ms)0;
}
void
discord_modify_user_voice_state_init(
    struct discord_modify_user_voice_state *this)
{

    this->channel_id = (u64snowflake)0;

    this->suppress = false;
}

void
discord_guild_scheduled_event_init(struct discord_guild_scheduled_event *this)
{

    this->id = (u64snowflake)0;

    this->guild_id = (u64snowflake)0;

    this->channel_id = (u64snowflake)0;

    this->creator_id = (u64snowflake)0;

    this->name = NULL;

    this->description = NULL;

    this->scheduled_start_time = (u64unix_ms)0;

    this->scheduled_end_time = (u64unix_ms)0;

    this->privacy_level = 0;

    this->status = 0;

    this->entity_type = 0;

    this->entity_id = (u64snowflake)0;

    this->entity_metadata = NULL;

    this->creator = NULL;

    this->user_count = 0;

    this->image = NULL;
}

static void
discord_guild_scheduled_event_entity_metadata_init(
    struct discord_guild_scheduled_event_entity_metadata *this)
{

    this->location = NULL;
}
static void
discord_guild_scheduled_event_user_init(
    struct discord_guild_scheduled_event_user *this)
{

    this->guild_scheduled_event_id = (u64snowflake)0;

    this->user = NULL;

    this->member = NULL;
}
void
discord_list_scheduled_events_for_guild_init(
    struct discord_list_scheduled_events_for_guild *this)
{

    this->with_user_count = false;
}
void
discord_create_guild_scheduled_event_init(
    struct discord_create_guild_scheduled_event *this)
{

    this->channel_id = (u64snowflake)0;

    this->entity_metadata = NULL;

    this->name = NULL;

    this->scheduled_start_time = (u64unix_ms)0;

    this->scheduled_end_time = (u64unix_ms)0;

    this->description = NULL;

    this->entity_type = 0;

    this->image = NULL;
}
void
discord_get_guild_scheduled_event_init(
    struct discord_get_guild_scheduled_event *this)
{

    this->with_user_count = false;
}
void
discord_modify_guild_scheduled_event_init(
    struct discord_modify_guild_scheduled_event *this)
{

    this->channel_id = (u64snowflake)0;

    this->entity_metadata = NULL;

    this->name = NULL;

    this->scheduled_start_time = (u64unix_ms)0;

    this->scheduled_end_time = (u64unix_ms)0;

    this->description = NULL;

    this->entity_type = 0;

    this->status = 0;

    this->image = NULL;
}
void
discord_get_guild_scheduled_event_users_init(
    struct discord_get_guild_scheduled_event_users *this)
{

    this->limit = 0;

    this->with_member = false;

    this->before = (u64snowflake)0;

    this->after = (u64snowflake)0;
}
void
discord_guild_template_init(struct discord_guild_template *this)
{

    this->code = NULL;

    this->name = NULL;

    this->description = NULL;

    this->usage_count = 0;

    this->creator_id = (u64snowflake)0;

    this->creator = NULL;

    this->created_at = (u64unix_ms)0;

    this->updated_at = (u64unix_ms)0;

    this->source_guild_id = (u64snowflake)0;

    this->serialized_source_guild = NULL;

    this->is_dirty = false;
}
void
discord_create_guild_from_guild_template_init(
    struct discord_create_guild_from_guild_template *this)
{

    this->name = NULL;

    this->icon = NULL;
}
void
discord_create_guild_template_init(struct discord_create_guild_template *this)
{

    this->name = NULL;

    this->description = NULL;
}
void
discord_modify_guild_template_init(struct discord_modify_guild_template *this)
{

    this->name = NULL;

    this->description = NULL;
}

void
discord_stage_instance_init(struct discord_stage_instance *this)
{

    this->id = (u64snowflake)0;

    this->guild_id = (u64snowflake)0;

    this->channel_id = (u64snowflake)0;

    this->topic = NULL;

    this->privacy_level = 0;

    this->discoverable_disabled = false;
}

void
discord_create_stage_instance_init(struct discord_create_stage_instance *this)
{

    this->channel_id = (u64snowflake)0;

    this->topic = NULL;

    this->privacy_level = 0;
}
void
discord_modify_stage_instance_init(struct discord_modify_stage_instance *this)
{

    this->topic = NULL;

    this->privacy_level = 0;
}

void
discord_sticker_init(struct discord_sticker *this)
{

    this->id = (u64snowflake)0;

    this->pack_id = (u64snowflake)0;

    this->name = NULL;

    this->description = NULL;

    this->tags = NULL;

    this->type = 0;

    this->format_type = 0;

    this->available = false;

    this->guild_id = (u64snowflake)0;

    this->user = NULL;

    this->sort_value = 0;
}

static void
discord_sticker_item_init(struct discord_sticker_item *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->format_type = 0;
}

static void
discord_sticker_pack_init(struct discord_sticker_pack *this)
{

    this->id = (u64snowflake)0;

    this->stickers = NULL;

    this->name = NULL;

    this->sku_id = (u64snowflake)0;

    this->cover_sticker_id = (u64snowflake)0;

    this->description = NULL;

    this->banner_asset_id = (u64snowflake)0;
}
static void
discord_create_guild_sticker_init(struct discord_create_guild_sticker *this)
{

    this->name = NULL;

    this->description = NULL;

    this->tags = NULL;

    this->file = NULL;
}
void
discord_modify_guild_sticker_init(struct discord_modify_guild_sticker *this)
{

    this->name = NULL;

    this->description = NULL;

    this->tags = NULL;
}

void
discord_user_init(struct discord_user *this)
{

    this->id = (u64snowflake)0;

    this->username = NULL;

    this->discriminator = NULL;

    this->avatar = NULL;

    this->bot = false;

    this->System = false;

    this->mfa_enabled = false;

    this->banner = NULL;

    this->accent_color = 0;

    this->locale = NULL;

    this->verified = false;

    this->email = NULL;

    this->flags = (u64snowflake)0;

    this->premium_type = 0;

    this->public_flags = (u64snowflake)0;
}

static void
discord_connection_init(struct discord_connection *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->type = NULL;

    this->revoked = false;

    this->integrations = NULL;

    this->verified = false;

    this->friend_sync = false;

    this->show_activity = false;

    this->visibility = 0;
}

void
discord_modify_current_user_init(struct discord_modify_current_user *this)
{

    this->username = NULL;

    this->avatar = NULL;
}
static void
discord_get_current_user_guilds_init(
    struct discord_get_current_user_guilds *this)
{

    this->before = (u64snowflake)0;

    this->after = (u64snowflake)0;

    this->limit = 200;
}
void
discord_create_dm_init(struct discord_create_dm *this)
{

    this->recipient_id = (u64snowflake)0;
}
void
discord_create_group_dm_init(struct discord_create_group_dm *this)
{

    this->access_tokens = NULL;

    this->nicks = NULL;
}
void
discord_voice_state_init(struct discord_voice_state *this)
{

    this->guild_id = (u64snowflake)0;

    this->channel_id = (u64snowflake)0;

    this->user_id = (u64snowflake)0;

    this->member = NULL;

    this->session_id = NULL;

    this->deaf = false;

    this->mute = false;

    this->self_deaf = false;

    this->self_mute = false;

    this->self_stream = false;

    this->self_video = false;

    this->suppress = false;

    this->request_to_speak_timestamp = (u64unix_ms)0;
}

static void
discord_voice_region_init(struct discord_voice_region *this)
{

    this->id = NULL;

    this->name = NULL;

    this->optimal = false;

    this->deprecated = false;

    this->custom = false;
}

void
discord_webhook_init(struct discord_webhook *this)
{

    this->id = (u64snowflake)0;

    this->type = 0;

    this->guild_id = (u64snowflake)0;

    this->channel_id = (u64snowflake)0;

    this->user = NULL;

    this->name = NULL;

    this->token = NULL;

    this->application_id = (u64snowflake)0;

    this->source_channel = NULL;

    this->url = NULL;
}

void
discord_create_webhook_init(struct discord_create_webhook *this)
{

    this->name = NULL;

    this->avatar = NULL;
}
void
discord_modify_webhook_init(struct discord_modify_webhook *this)
{

    this->name = NULL;

    this->avatar = NULL;

    this->channel_id = (u64snowflake)0;
}
void
discord_modify_webhook_with_token_init(
    struct discord_modify_webhook_with_token *this)
{

    this->name = NULL;

    this->avatar = NULL;
}
void
discord_execute_webhook_init(struct discord_execute_webhook *this)
{

    this->wait = false;

    this->thread_id = (u64snowflake)0;

    this->content = NULL;

    this->username = NULL;

    this->avatar_url = NULL;

    this->tts = false;

    this->embeds = NULL;

    this->allowed_mentions = NULL;

    this->components = NULL;

    this->attachments = NULL;

    this->flags = (u64snowflake)0;
}
static void
discord_get_webhook_message_init(struct discord_get_webhook_message *this)
{

    this->thread_id = (u64snowflake)0;
}
void
discord_edit_webhook_message_init(struct discord_edit_webhook_message *this)
{

    this->thread_id = (u64snowflake)0;

    this->content = NULL;

    this->embeds = NULL;

    this->allowed_mentions = NULL;

    this->components = NULL;

    this->attachments = NULL;
}
static void
discord_delete_webhook_message_init(
    struct discord_delete_webhook_message *this)
{

    this->thread_id = (u64snowflake)0;
}

void
discord_identify_init(struct discord_identify *this)
{

    this->token = NULL;

    this->properties = NULL;

    this->compress = false;

    this->large_threshold = 50;

    this->presence = NULL;

    this->intents = 0;
}
static void
discord_identify_connection_init(struct discord_identify_connection *this)
{

    this->os = NULL;

    this->browser = NULL;

    this->device = NULL;
}
void
discord_voice_state_status_init(struct discord_voice_state_status *this)
{

    this->guild_id = (u64snowflake)0;

    this->channel_id = (u64snowflake)0;

    this->self_mute = false;

    this->self_deaf = false;
}
void
discord_presence_update_init(struct discord_presence_update *this)
{

    this->since = (u64unix_ms)0;

    this->activities = NULL;

    this->status = NULL;

    this->afk = false;
}

static void
discord_activity_init(struct discord_activity *this)
{

    this->name = NULL;

    this->type = 0;

    this->url = NULL;

    this->created_at = (u64unix_ms)0;

    this->timestamps = NULL;

    this->application_id = (u64snowflake)0;

    this->details = NULL;

    this->state = NULL;

    this->emoji = NULL;

    this->party = NULL;

    this->assets = NULL;

    this->secrets = NULL;

    this->instance = false;

    this->flags = (u64snowflake)0;

    this->buttons = NULL;
}

static void
discord_activity_timestamps_init(struct discord_activity_timestamps *this)
{

    this->start = (u64unix_ms)0;

    this->end = (u64unix_ms)0;
}
static void
discord_activity_emoji_init(struct discord_activity_emoji *this)
{

    this->name = NULL;

    this->id = (u64snowflake)0;

    this->animated = false;
}
static void
discord_activity_party_init(struct discord_activity_party *this)
{

    this->id = NULL;

    this->size = NULL;
}
static void
discord_activity_assets_init(struct discord_activity_assets *this)
{

    this->large_image = NULL;

    this->large_text = NULL;

    this->small_image = NULL;

    this->small_text = NULL;
}
static void
discord_activity_secrets_init(struct discord_activity_secrets *this)
{

    this->join = NULL;

    this->spectate = NULL;

    this->match = NULL;
}
static void
discord_activity_button_init(struct discord_activity_button *this)
{

    this->label = NULL;

    this->url = NULL;
}

void
discord_session_start_limit_init(struct discord_session_start_limit *this)
{

    this->total = 0;

    this->remaining = 0;

    this->reset_after = 0;

    this->max_concurrency = 0;
}

void
discord_team_init(struct discord_team *this)
{

    this->icon = NULL;

    this->id = (u64snowflake)0;

    this->members = NULL;

    this->name = NULL;

    this->owner_user_id = (u64snowflake)0;
}
static void
discord_team_member_init(struct discord_team_member *this)
{

    this->membership_state = 0;

    this->permissions = NULL;

    this->team_id = (u64snowflake)0;

    this->user = NULL;
}

void
discord_application_command_init(struct discord_application_command *this)
{

    this->id = (u64snowflake)0;

    this->type = 0;

    this->application_id = (u64snowflake)0;

    this->guild_id = (u64snowflake)0;

    this->name = NULL;

    this->description = NULL;

    this->options = NULL;

    this->default_permission = true;

    this->version = (u64snowflake)0;
}

static void
discord_application_command_option_init(
    struct discord_application_command_option *this)
{

    this->type = 0;

    this->name = NULL;

    this->description = NULL;

    this->required = false;

    this->choices = NULL;

    this->options = NULL;

    this->channel_types = NULL;

    this->min_value = NULL;

    this->max_value = NULL;

    this->autocomplete = false;
}

static void
discord_application_command_option_choice_init(
    struct discord_application_command_option_choice *this)
{

    this->name = NULL;

    this->value = NULL;
}

static void
discord_application_command_interaction_data_option_init(
    struct discord_application_command_interaction_data_option *this)
{

    this->name = NULL;

    this->type = 0;

    this->value = NULL;

    this->options = NULL;

    this->focused = false;
}

static void
discord_guild_application_command_permission_init(
    struct discord_guild_application_command_permission *this)
{

    this->id = (u64snowflake)0;

    this->application_id = (u64snowflake)0;

    this->guild_id = (u64snowflake)0;

    this->permissions = NULL;
}

void
discord_application_command_permission_init(
    struct discord_application_command_permission *this)
{

    this->id = (u64snowflake)0;

    this->type = 0;

    this->permission = false;
}

void
discord_create_global_application_command_init(
    struct discord_create_global_application_command *this)
{

    this->name = NULL;

    this->description = NULL;

    this->options = NULL;

    this->default_permission = true;

    this->type = 0;
}
void
discord_edit_global_application_command_init(
    struct discord_edit_global_application_command *this)
{

    this->name = NULL;

    this->description = NULL;

    this->options = NULL;

    this->default_permission = true;
}
void
discord_create_guild_application_command_init(
    struct discord_create_guild_application_command *this)
{

    this->name = NULL;

    this->description = NULL;

    this->options = NULL;

    this->default_permission = true;

    this->type = 0;
}
void
discord_edit_guild_application_command_init(
    struct discord_edit_guild_application_command *this)
{

    this->name = NULL;

    this->description = NULL;

    this->options = NULL;

    this->default_permission = true;
}
void
discord_edit_application_command_permissions_init(
    struct discord_edit_application_command_permissions *this)
{

    this->permissions = NULL;
}

void
discord_component_init(struct discord_component *this)
{

    this->type = 0;

    this->custom_id = NULL;

    this->disabled = false;

    this->style = 0;

    this->label = NULL;

    this->emoji = NULL;

    this->url = NULL;

    this->options = NULL;

    this->placeholder = NULL;

    this->min_values = 1;

    this->max_values = 1;

    this->components = NULL;

    this->min_length = 0;

    this->max_length = 0;

    this->required = false;

    this->value = NULL;
}

static void
discord_select_option_init(struct discord_select_option *this)
{

    this->label = NULL;

    this->value = NULL;

    this->description = NULL;

    this->emoji = NULL;

    this->Default = false;
}

void
discord_interaction_init(struct discord_interaction *this)
{

    this->id = (u64snowflake)0;

    this->application_id = (u64snowflake)0;

    this->type = 0;

    this->data = NULL;

    this->guild_id = (u64snowflake)0;

    this->channel_id = (u64snowflake)0;

    this->member = NULL;

    this->user = NULL;

    this->token = NULL;

    this->version = 1;

    this->message = NULL;

    this->locale = NULL;

    this->guild_locale = NULL;
}
static void
discord_interaction_data_init(struct discord_interaction_data *this)
{

    this->id = (u64snowflake)0;

    this->name = NULL;

    this->type = 0;

    this->resolved = NULL;

    this->options = NULL;

    this->custom_id = NULL;

    this->component_type = 0;

    this->values = NULL;

    this->target_id = (u64snowflake)0;

    this->components = NULL;
}
static void
discord_resolved_data_init(struct discord_resolved_data *this)
{

    this->users = NULL;

    this->members = NULL;

    this->roles = NULL;

    this->channels = NULL;

    this->messages = NULL;

    this->attachments = NULL;
}
static void
discord_message_interaction_init(struct discord_message_interaction *this)
{

    this->id = (u64snowflake)0;

    this->type = 0;

    this->name = NULL;

    this->user = NULL;

    this->member = NULL;
}
void
discord_interaction_response_init(struct discord_interaction_response *this)
{

    this->type = 0;

    this->data = NULL;
}
static void
discord_interaction_callback_data_init(
    struct discord_interaction_callback_data *this)
{

    this->components = NULL;

    this->tts = false;

    this->content = NULL;

    this->embeds = NULL;

    this->flags = 0;

    this->attachments = NULL;

    this->choices = NULL;

    this->custom_id = NULL;

    this->title = NULL;
}
void
discord_edit_original_interaction_response_init(
    struct discord_edit_original_interaction_response *this)
{

    this->thread_id = (u64snowflake)0;

    this->content = NULL;

    this->embeds = NULL;

    this->allowed_mentions = NULL;

    this->components = NULL;

    this->attachments = NULL;
}
void
discord_create_followup_message_init(
    struct discord_create_followup_message *this)
{

    this->wait = true;

    this->thread_id = (u64snowflake)0;

    this->avatar_url = NULL;

    this->tts = false;

    this->embeds = NULL;

    this->allowed_mentions = NULL;

    this->components = NULL;

    this->attachments = NULL;

    this->flags = (u64snowflake)0;
}
void
discord_edit_followup_message_init(struct discord_edit_followup_message *this)
{

    this->thread_id = (u64snowflake)0;

    this->content = NULL;

    this->embeds = NULL;

    this->allowed_mentions = NULL;

    this->components = NULL;

    this->attachments = NULL;
}
void
strings_cleanup(struct strings *this)
{
    __carray_free(this, char *, NULL, NULL);
}
void
json_values_cleanup(struct json_values *this)
{
    __carray_free(this, json_char *, NULL, NULL);
}
void
snowflakes_cleanup(struct snowflakes *this)
{
    __carray_free(this, u64snowflake, NULL, NULL);
}
void
integers_cleanup(struct integers *this)
{
    __carray_free(this, int, NULL, NULL);
}

void
discord_role_cleanup(struct discord_role *this)
{

    if (this->name) free(this->name);

    (void)this->color;

    (void)this->hoist;

    if (this->icon) free(this->icon);

    if (this->unicode_emoji) free(this->unicode_emoji);

    (void)this->position;

    if (this->permissions) free(this->permissions);

    (void)this->managed;

    (void)this->mentionable;

    if (this->tags) {
        discord_role_tag_cleanup(this->tags);
        free(this->tags);
    };
}
void
discord_roles_cleanup(struct discord_roles *this)
{
    __carray_free(this, struct discord_role, NULL,
                  discord_role_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_role_tag_cleanup(struct discord_role_tag *this)
{

    (void)this->premium_subscribe;
}

void
discord_application_cleanup(struct discord_application *this)
{

    if (this->name) free(this->name);

    if (this->icon) free(this->icon);

    if (this->description) free(this->description);

    if (this->rpc_origins) {
        strings_cleanup(this->rpc_origins);
        free(this->rpc_origins);
    };

    (void)this->bot_public;

    (void)this->bot_require_code_grant;

    if (this->terms_of_service_url) free(this->terms_of_service_url);

    if (this->privacy_policy_url) free(this->privacy_policy_url);

    if (this->owner) {
        discord_user_cleanup(this->owner);
        free(this->owner);
    };

    if (this->summary) free(this->summary);

    if (this->verify_key) free(this->verify_key);

    if (this->team) {
        discord_team_cleanup(this->team);
        free(this->team);
    };

    if (this->slug) free(this->slug);

    if (this->cover_image) free(this->cover_image);
}

void
discord_audit_log_cleanup(struct discord_audit_log *this)
{

    if (this->audit_log_entries) {
        discord_audit_log_entries_cleanup(this->audit_log_entries);
        free(this->audit_log_entries);
    };

    if (this->guild_scheduled_events) {
        discord_guild_scheduled_events_cleanup(this->guild_scheduled_events);
        free(this->guild_scheduled_events);
    };

    if (this->integrations) {
        discord_integrations_cleanup(this->integrations);
        free(this->integrations);
    };

    if (this->threads) {
        discord_channels_cleanup(this->threads);
        free(this->threads);
    };

    if (this->users) {
        discord_users_cleanup(this->users);
        free(this->users);
    };

    if (this->webhooks) {
        discord_webhooks_cleanup(this->webhooks);
        free(this->webhooks);
    };
}
static void
discord_audit_log_entry_cleanup(struct discord_audit_log_entry *this)
{

    if (this->changes) {
        discord_audit_log_changes_cleanup(this->changes);
        free(this->changes);
    };

    (void)this->action_type;

    if (this->options) {
        discord_optional_audit_entry_infos_cleanup(this->options);
        free(this->options);
    };

    if (this->reason) free(this->reason);
}
static void
discord_audit_log_entries_cleanup(struct discord_audit_log_entries *this)
{
    __carray_free(this, struct discord_audit_log_entry, NULL,
                  discord_audit_log_entry_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_optional_audit_entry_info_cleanup(
    struct discord_optional_audit_entry_info *this)
{

    if (this->count) free(this->count);

    if (this->delete_member_days) free(this->delete_member_days);

    if (this->members_removed) free(this->members_removed);

    if (this->role_name) free(this->role_name);

    if (this->type) free(this->type);
}
static void
discord_optional_audit_entry_infos_cleanup(
    struct discord_optional_audit_entry_infos *this)
{
    __carray_free(
        this, struct discord_optional_audit_entry_info, NULL,
        discord_optional_audit_entry_info_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_audit_log_change_cleanup(struct discord_audit_log_change *this)
{

    if (this->new_value) free(this->new_value);

    if (this->old_value) free(this->old_value);

    if (this->key) free(this->key);
}
static void
discord_audit_log_changes_cleanup(struct discord_audit_log_changes *this)
{
    __carray_free(this, struct discord_audit_log_change, NULL,
                  discord_audit_log_change_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_get_guild_audit_log_cleanup(struct discord_get_guild_audit_log *this)
{

    (void)this->action_type;

    (void)this->limit;
}

void
discord_invite_cleanup(struct discord_invite *this)
{

    if (this->code) free(this->code);

    if (this->guild) {
        discord_guild_cleanup(this->guild);
        free(this->guild);
    };

    if (this->channel) {
        discord_channel_cleanup(this->channel);
        free(this->channel);
    };

    if (this->inviter) {
        discord_user_cleanup(this->inviter);
        free(this->inviter);
    };

    (void)this->target_type;

    if (this->target_user) {
        discord_user_cleanup(this->target_user);
        free(this->target_user);
    };

    if (this->target_application) {
        discord_application_cleanup(this->target_application);
        free(this->target_application);
    };

    (void)this->approximate_presence_count;

    (void)this->approximate_member_count;

    ;

    if (this->stage_instance) {
        discord_invite_stage_instance_cleanup(this->stage_instance);
        free(this->stage_instance);
    };

    if (this->guild_scheduled_event) {
        discord_guild_scheduled_event_cleanup(this->guild_scheduled_event);
        free(this->guild_scheduled_event);
    };
}
void
discord_invites_cleanup(struct discord_invites *this)
{
    __carray_free(this, struct discord_invite, NULL,
                  discord_invite_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_invite_metadata_cleanup(struct discord_invite_metadata *this)
{

    (void)this->uses;

    (void)this->max_uses;

    (void)this->max_age;

    (void)this->temporary;

    ;
}
static void
discord_invite_stage_instance_cleanup(
    struct discord_invite_stage_instance *this)
{

    if (this->members) {
        discord_guild_members_cleanup(this->members);
        free(this->members);
    };

    (void)this->participant_count;

    (void)this->speaker_count;

    if (this->topic) free(this->topic);
}
void
discord_get_invite_cleanup(struct discord_get_invite *this)
{

    (void)this->with_counts;

    (void)this->with_expiration;
}

void
discord_channel_cleanup(struct discord_channel *this)
{

    (void)this->type;

    (void)this->position;

    if (this->permission_overwrites) {
        discord_overwrites_cleanup(this->permission_overwrites);
        free(this->permission_overwrites);
    };

    if (this->name) free(this->name);

    if (this->topic) free(this->topic);

    (void)this->nsfw;

    (void)this->bitrate;

    (void)this->user_limit;

    (void)this->rate_limit_per_user;

    if (this->recipients) {
        discord_users_cleanup(this->recipients);
        free(this->recipients);
    };

    if (this->icon) free(this->icon);

    ;

    if (this->rtc_region) free(this->rtc_region);

    (void)this->voice_quality_mode;

    (void)this->message_count;

    (void)this->member_count;

    if (this->thread_metadata) {
        discord_thread_metadata_cleanup(this->thread_metadata);
        free(this->thread_metadata);
    };

    if (this->member) {
        discord_thread_member_cleanup(this->member);
        free(this->member);
    };

    (void)this->default_auto_archive_duration;

    if (this->permissions) free(this->permissions);
}
void
discord_channels_cleanup(struct discord_channels *this)
{
    __carray_free(this, struct discord_channel, NULL,
                  discord_channel_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_message_cleanup(struct discord_message *this)
{

    if (this->author) {
        discord_user_cleanup(this->author);
        free(this->author);
    };

    if (this->member) {
        discord_guild_member_cleanup(this->member);
        free(this->member);
    };

    if (this->content) free(this->content);

    ;

    ;

    (void)this->tts;

    (void)this->mention_everyone;

    if (this->mentions) {
        discord_users_cleanup(this->mentions);
        free(this->mentions);
    };

    if (this->mention_roles) {
        discord_roles_cleanup(this->mention_roles);
        free(this->mention_roles);
    };

    if (this->mention_channels) {
        discord_channels_cleanup(this->mention_channels);
        free(this->mention_channels);
    };

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    if (this->reactions) {
        discord_reactions_cleanup(this->reactions);
        free(this->reactions);
    };

    if (this->nonce) free(this->nonce);

    (void)this->pinned;

    (void)this->type;

    if (this->activity) {
        discord_message_activity_cleanup(this->activity);
        free(this->activity);
    };

    if (this->application) {
        discord_application_cleanup(this->application);
        free(this->application);
    };

    if (this->message_reference) {
        discord_message_reference_cleanup(this->message_reference);
        free(this->message_reference);
    };

    (void)this->flags;

    if (this->referenced_message) {
        discord_message_cleanup(this->referenced_message);
        free(this->referenced_message);
    };

    if (this->interaction) {
        discord_message_interaction_cleanup(this->interaction);
        free(this->interaction);
    };

    if (this->thread) {
        discord_channel_cleanup(this->thread);
        free(this->thread);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    if (this->sticker_items) {
        discord_sticker_items_cleanup(this->sticker_items);
        free(this->sticker_items);
    };
}
void
discord_messages_cleanup(struct discord_messages *this)
{
    __carray_free(this, struct discord_message, NULL,
                  discord_message_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_message_activity_cleanup(struct discord_message_activity *this)
{

    (void)this->type;

    if (this->party_id) free(this->party_id);
}
static void
discord_message_reference_cleanup(struct discord_message_reference *this)
{

    (void)this->fail_if_not_exists;
}
void
discord_followed_channel_cleanup(struct discord_followed_channel *this)
{
}
static void
discord_reaction_cleanup(struct discord_reaction *this)
{

    (void)this->count;

    (void)this->me;

    if (this->emoji) {
        discord_emoji_cleanup(this->emoji);
        free(this->emoji);
    };
}
static void
discord_reactions_cleanup(struct discord_reactions *this)
{
    __carray_free(this, struct discord_reaction, NULL,
                  discord_reaction_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_overwrite_cleanup(struct discord_overwrite *this)
{

    (void)this->type;
}
static void
discord_overwrites_cleanup(struct discord_overwrites *this)
{
    __carray_free(this, struct discord_overwrite, NULL,
                  discord_overwrite_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_thread_metadata_cleanup(struct discord_thread_metadata *this)
{

    (void)this->archived;

    (void)this->auto_archive_duration;

    ;

    (void)this->locked;

    (void)this->invitable;

    ;
}
static void
discord_thread_member_cleanup(struct discord_thread_member *this)
{

    ;

    (void)this->flags;
}
void
discord_thread_members_cleanup(struct discord_thread_members *this)
{
    __carray_free(this, struct discord_thread_member, NULL,
                  discord_thread_member_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_attachment_cleanup(struct discord_attachment *this)
{

    if (this->content) free(this->content);

    if (this->filename) free(this->filename);

    if (this->description) free(this->description);

    if (this->content_type) free(this->content_type);

    (void)this->size;

    if (this->url) free(this->url);

    if (this->proxy_url) free(this->proxy_url);

    (void)this->height;

    (void)this->width;

    (void)this->ephemeral;
}
void
discord_attachments_cleanup(struct discord_attachments *this)
{
    __carray_free(this, struct discord_attachment, NULL,
                  discord_attachment_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_embed_cleanup(struct discord_embed *this)
{

    if (this->title) free(this->title);

    if (this->type) free(this->type);

    if (this->description) free(this->description);

    if (this->url) free(this->url);

    ;

    (void)this->color;

    if (this->footer) {
        discord_embed_footer_cleanup(this->footer);
        free(this->footer);
    };

    if (this->image) {
        discord_embed_image_cleanup(this->image);
        free(this->image);
    };

    if (this->thumbnail) {
        discord_embed_thumbnail_cleanup(this->thumbnail);
        free(this->thumbnail);
    };

    if (this->video) {
        discord_embed_video_cleanup(this->video);
        free(this->video);
    };

    if (this->provider) {
        discord_embed_provider_cleanup(this->provider);
        free(this->provider);
    };

    if (this->author) {
        discord_embed_author_cleanup(this->author);
        free(this->author);
    };

    if (this->fields) {
        discord_embed_fields_cleanup(this->fields);
        free(this->fields);
    };
}
void
discord_embeds_cleanup(struct discord_embeds *this)
{
    __carray_free(this, struct discord_embed, NULL,
                  discord_embed_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *this)
{

    if (this->url) free(this->url);

    if (this->proxy_url) free(this->proxy_url);

    (void)this->height;

    (void)this->width;
}
void
discord_embed_video_cleanup(struct discord_embed_video *this)
{

    if (this->url) free(this->url);

    if (this->proxy_url) free(this->proxy_url);

    (void)this->height;

    (void)this->width;
}
void
discord_embed_image_cleanup(struct discord_embed_image *this)
{

    if (this->url) free(this->url);

    if (this->proxy_url) free(this->proxy_url);

    (void)this->height;

    (void)this->width;
}
void
discord_embed_provider_cleanup(struct discord_embed_provider *this)
{

    if (this->name) free(this->name);

    if (this->url) free(this->url);
}
void
discord_embed_author_cleanup(struct discord_embed_author *this)
{

    if (this->name) free(this->name);

    if (this->url) free(this->url);

    if (this->icon_url) free(this->icon_url);

    if (this->proxy_icon_url) free(this->proxy_icon_url);
}
void
discord_embed_footer_cleanup(struct discord_embed_footer *this)
{

    if (this->text) free(this->text);

    if (this->icon_url) free(this->icon_url);

    if (this->proxy_icon_url) free(this->proxy_icon_url);
}
void
discord_embed_field_cleanup(struct discord_embed_field *this)
{

    if (this->name) free(this->name);

    if (this->value) free(this->value);

    ;
}
void
discord_embed_fields_cleanup(struct discord_embed_fields *this)
{
    __carray_free(this, struct discord_embed_field, NULL,
                  discord_embed_field_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_channel_mention_cleanup(struct discord_channel_mention *this)
{

    (void)this->type;

    if (this->name) free(this->name);
}
static void
discord_allowed_mention_cleanup(struct discord_allowed_mention *this)
{

    if (this->parse) {
        strings_cleanup(this->parse);
        free(this->parse);
    };

    if (this->roles) {
        snowflakes_cleanup(this->roles);
        free(this->roles);
    };

    if (this->users) {
        snowflakes_cleanup(this->users);
        free(this->users);
    };

    (void)this->replied_user;
}
void
discord_thread_response_body_cleanup(struct discord_thread_response_body *this)
{

    if (this->threads) {
        discord_channels_cleanup(this->threads);
        free(this->threads);
    };

    if (this->members) {
        discord_thread_members_cleanup(this->members);
        free(this->members);
    };

    (void)this->has_more;
}
void
discord_modify_channel_cleanup(struct discord_modify_channel *this)
{

    if (this->name) free(this->name);

    (void)this->type;

    (void)this->position;

    if (this->topic) free(this->topic);

    (void)this->nsfw;

    (void)this->rate_limit_per_user;

    (void)this->user_limit;

    if (this->permission_overwrites) {
        discord_overwrites_cleanup(this->permission_overwrites);
        free(this->permission_overwrites);
    };

    if (this->rtc_region) free(this->rtc_region);

    (void)this->video_quality_mode;

    (void)this->default_auto_archive_duration;

    (void)this->archived;

    (void)this->auto_archive_duration;

    (void)this->locked;

    (void)this->invitable;
}
void
discord_get_channel_messages_cleanup(struct discord_get_channel_messages *this)
{

    (void)this->limit;
}
void
discord_create_message_cleanup(struct discord_create_message *this)
{

    if (this->content) free(this->content);

    (void)this->tts;

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    if (this->allowed_mentions) {
        discord_allowed_mention_cleanup(this->allowed_mentions);
        free(this->allowed_mentions);
    };

    if (this->message_reference) {
        discord_message_reference_cleanup(this->message_reference);
        free(this->message_reference);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    if (this->sticker_ids) {
        snowflakes_cleanup(this->sticker_ids);
        free(this->sticker_ids);
    };

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };

    (void)this->flags;
}
void
discord_get_reactions_cleanup(struct discord_get_reactions *this)
{

    (void)this->limit;
}
void
discord_edit_message_cleanup(struct discord_edit_message *this)
{

    if (this->content) free(this->content);

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    (void)this->flags;

    if (this->allowed_mentions) {
        discord_allowed_mention_cleanup(this->allowed_mentions);
        free(this->allowed_mentions);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };
}
void
discord_bulk_delete_messages_cleanup(struct discord_bulk_delete_messages *this)
{

    if (this->messages) {
        snowflakes_cleanup(this->messages);
        free(this->messages);
    };
}
void
discord_edit_channel_permissions_cleanup(
    struct discord_edit_channel_permissions *this)
{

    (void)this->type;
}
void
discord_create_channel_invite_cleanup(
    struct discord_create_channel_invite *this)
{

    (void)this->max_age;

    (void)this->max_uses;

    (void)this->temporary;

    (void)this->unique;

    (void)this->target_type;
}
void
discord_follow_news_channel_cleanup(struct discord_follow_news_channel *this)
{
}
void
discord_group_dm_add_recipient_cleanup(
    struct discord_group_dm_add_recipient *this)
{

    if (this->access_token) free(this->access_token);

    if (this->nick) free(this->nick);
}
void
discord_start_thread_with_message_cleanup(
    struct discord_start_thread_with_message *this)
{

    if (this->name) free(this->name);

    (void)this->auto_archive_duration;

    (void)this->rate_limit_per_user;
}
void
discord_start_thread_without_message_cleanup(
    struct discord_start_thread_without_message *this)
{

    if (this->name) free(this->name);

    (void)this->auto_archive_duration;

    (void)this->type;

    (void)this->invitable;

    (void)this->rate_limit_per_user;
}
void
discord_list_active_threads_cleanup(struct discord_list_active_threads *this)
{

    if (this->threads) {
        discord_channels_cleanup(this->threads);
        free(this->threads);
    };

    if (this->members) {
        discord_thread_members_cleanup(this->members);
        free(this->members);
    };

    (void)this->has_more;
}
void
discord_emoji_cleanup(struct discord_emoji *this)
{

    if (this->name) free(this->name);

    if (this->roles) {
        discord_roles_cleanup(this->roles);
        free(this->roles);
    };

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };

    (void)this->require_colons;

    (void)this->managed;

    (void)this->animated;

    (void)this->available;
}
void
discord_emojis_cleanup(struct discord_emojis *this)
{
    __carray_free(this, struct discord_emoji, NULL,
                  discord_emoji_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_create_guild_emoji_cleanup(struct discord_create_guild_emoji *this)
{

    if (this->name) free(this->name);

    if (this->image) free(this->image);

    if (this->roles) {
        snowflakes_cleanup(this->roles);
        free(this->roles);
    };
}
void
discord_modify_guild_emoji_cleanup(struct discord_modify_guild_emoji *this)
{

    if (this->name) free(this->name);

    if (this->image) free(this->image);

    if (this->roles) {
        snowflakes_cleanup(this->roles);
        free(this->roles);
    };
}

void
discord_guild_cleanup(struct discord_guild *this)
{

    if (this->name) free(this->name);

    if (this->icon) free(this->icon);

    if (this->icon_hash) free(this->icon_hash);

    if (this->splash) free(this->splash);

    if (this->discovery_splash) free(this->discovery_splash);

    (void)this->owner;

    if (this->permissions) free(this->permissions);

    (void)this->afk_timeout;

    (void)this->widget_enabled;

    (void)this->verification_level;

    (void)this->default_message_notifications;

    (void)this->explicit_content_filter;

    if (this->roles) {
        discord_roles_cleanup(this->roles);
        free(this->roles);
    };

    if (this->emojis) {
        discord_emojis_cleanup(this->emojis);
        free(this->emojis);
    };

    if (this->features) {
        strings_cleanup(this->features);
        free(this->features);
    };

    (void)this->mfa_level;

    (void)this->system_channel_flags;

    ;

    (void)this->large;

    (void)this->unavailable;

    (void)this->member_count;

    if (this->voice_states) {
        discord_voice_states_cleanup(this->voice_states);
        free(this->voice_states);
    };

    if (this->members) {
        discord_guild_members_cleanup(this->members);
        free(this->members);
    };

    if (this->channels) {
        discord_channels_cleanup(this->channels);
        free(this->channels);
    };

    if (this->threads) {
        discord_channels_cleanup(this->threads);
        free(this->threads);
    };

    if (this->presences) {
        discord_presence_updates_cleanup(this->presences);
        free(this->presences);
    };

    (void)this->max_presences;

    (void)this->max_members;

    if (this->vanity_url_code) free(this->vanity_url_code);

    if (this->description) free(this->description);

    if (this->banner) free(this->banner);

    (void)this->premium_tier;

    (void)this->premium_subscription_count;

    if (this->preferred_locale) free(this->preferred_locale);

    (void)this->max_video_channel_users;

    (void)this->approximate_member_count;

    (void)this->approximate_presence_count;

    if (this->welcome_screen) {
        discord_welcome_screen_cleanup(this->welcome_screen);
        free(this->welcome_screen);
    };

    (void)this->nsfw_level;

    if (this->stage_instances) {
        discord_stage_instances_cleanup(this->stage_instances);
        free(this->stage_instances);
    };

    if (this->stickers) {
        discord_stickers_cleanup(this->stickers);
        free(this->stickers);
    };

    if (this->guild_scheduled_events) {
        discord_guild_scheduled_events_cleanup(this->guild_scheduled_events);
        free(this->guild_scheduled_events);
    };

    (void)this->premium_progress_bar_enabled;
}
void
discord_guilds_cleanup(struct discord_guilds *this)
{
    __carray_free(this, struct discord_guild, NULL,
                  discord_guild_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_guild_preview_cleanup(struct discord_guild_preview *this)
{

    if (this->name) free(this->name);

    if (this->icon) free(this->icon);

    if (this->splash) free(this->splash);

    if (this->discovery_splash) free(this->discovery_splash);

    if (this->emojis) {
        discord_emojis_cleanup(this->emojis);
        free(this->emojis);
    };

    if (this->features) {
        strings_cleanup(this->features);
        free(this->features);
    };

    (void)this->approximate_member_count;

    (void)this->approximate_presence_count;

    if (this->description) free(this->description);

    if (this->stickers) {
        discord_stickers_cleanup(this->stickers);
        free(this->stickers);
    };
}
static void
discord_guild_widget_setting_cleanup(struct discord_guild_widget_setting *this)
{

    (void)this->enabled;
}
static void
discord_get_guild_widget_cleanup(struct discord_get_guild_widget *this)
{

    if (this->name) free(this->name);

    if (this->instant_invite) free(this->instant_invite);

    if (this->channels) {
        discord_channels_cleanup(this->channels);
        free(this->channels);
    };

    if (this->members) {
        discord_users_cleanup(this->members);
        free(this->members);
    };

    (void)this->presence_count;
}
void
discord_guild_member_cleanup(struct discord_guild_member *this)
{

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };

    if (this->nick) free(this->nick);

    if (this->avatar) free(this->avatar);

    if (this->roles) {
        snowflakes_cleanup(this->roles);
        free(this->roles);
    };

    ;

    ;

    (void)this->deaf;

    (void)this->muted;

    (void)this->pending;

    if (this->permissions) free(this->permissions);

    ;
}
void
discord_guild_members_cleanup(struct discord_guild_members *this)
{
    __carray_free(this, struct discord_guild_member, NULL,
                  discord_guild_member_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_integration_cleanup(struct discord_integration *this)
{

    if (this->name) free(this->name);

    if (this->type) free(this->type);

    (void)this->enabled;

    (void)this->syncing;

    (void)this->enable_emoticons;

    (void)this->expire_behavior;

    (void)this->expire_grace_period;

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };

    if (this->account) {
        discord_integration_account_cleanup(this->account);
        free(this->account);
    };

    ;

    (void)this->subscriber_count;

    (void)this->revoked;

    if (this->application) {
        discord_integration_application_cleanup(this->application);
        free(this->application);
    };
}
static void
discord_integrations_cleanup(struct discord_integrations *this)
{
    __carray_free(this, struct discord_integration, NULL,
                  discord_integration_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_integration_account_cleanup(struct discord_integration_account *this)
{

    if (this->id) free(this->id);

    if (this->name) free(this->name);
}
static void
discord_integration_application_cleanup(
    struct discord_integration_application *this)
{

    if (this->name) free(this->name);

    if (this->icon) free(this->icon);

    if (this->description) free(this->description);

    if (this->summary) free(this->summary);

    if (this->bot) {
        discord_user_cleanup(this->bot);
        free(this->bot);
    };
}
void
discord_ban_cleanup(struct discord_ban *this)
{

    if (this->reason) free(this->reason);

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };
}
void
discord_bans_cleanup(struct discord_bans *this)
{
    __carray_free(this, struct discord_ban, NULL,
                  discord_ban_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_welcome_screen_cleanup(struct discord_welcome_screen *this)
{

    if (this->description) free(this->description);

    if (this->welcome_channels) {
        discord_welcome_screen_channels_cleanup(this->welcome_channels);
        free(this->welcome_channels);
    };
}
static void
discord_welcome_screen_channel_cleanup(
    struct discord_welcome_screen_channel *this)
{

    if (this->description) free(this->description);

    if (this->emoji_name) free(this->emoji_name);
}
static void
discord_welcome_screen_channels_cleanup(
    struct discord_welcome_screen_channels *this)
{
    __carray_free(this, struct discord_welcome_screen_channel, NULL,
                  discord_welcome_screen_channel_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_create_guild_cleanup(struct discord_create_guild *this)
{

    if (this->name) free(this->name);

    if (this->region) free(this->region);

    if (this->icon) free(this->icon);

    (void)this->verification_level;

    (void)this->default_message_notifications;

    (void)this->explicit_content_filter;

    if (this->roles) {
        discord_roles_cleanup(this->roles);
        free(this->roles);
    };

    if (this->channels) {
        discord_channels_cleanup(this->channels);
        free(this->channels);
    };

    (void)this->afk_timeout;

    (void)this->system_channel_flags;
}
void
discord_modify_guild_cleanup(struct discord_modify_guild *this)
{

    if (this->name) free(this->name);

    (void)this->verification_level;

    (void)this->default_message_notifications;

    (void)this->explicit_content_filter;

    (void)this->afk_timeout;

    if (this->icon) free(this->icon);

    if (this->splash) free(this->splash);

    if (this->discovery_splash) free(this->discovery_splash);

    if (this->banner) free(this->banner);

    (void)this->system_channel_flags;

    if (this->preferred_locale) free(this->preferred_locale);

    if (this->features) {
        strings_cleanup(this->features);
        free(this->features);
    };

    if (this->description) free(this->description);

    (void)this->premium_progress_bar_enabled;
}
void
discord_create_guild_channel_cleanup(struct discord_create_guild_channel *this)
{

    if (this->name) free(this->name);

    (void)this->type;

    if (this->topic) free(this->topic);

    (void)this->bitrate;

    (void)this->user_limit;

    (void)this->rate_limit_per_user;

    (void)this->position;

    if (this->permission_overwrites) {
        discord_overwrites_cleanup(this->permission_overwrites);
        free(this->permission_overwrites);
    };

    (void)this->nsfw;
}
static void
discord_modify_guild_channel_position_cleanup(
    struct discord_modify_guild_channel_position *this)
{

    (void)this->position;

    (void)this->lock_category;
}
void
discord_modify_guild_channel_positions_cleanup(
    struct discord_modify_guild_channel_positions *this)
{
    __carray_free(
        this, struct discord_modify_guild_channel_position, NULL,
        discord_modify_guild_channel_position_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_list_active_guild_threads_cleanup(
    struct discord_list_active_guild_threads *this)
{

    if (this->threads) {
        discord_channels_cleanup(this->threads);
        free(this->threads);
    };

    if (this->members) {
        discord_thread_members_cleanup(this->members);
        free(this->members);
    };
}
static void
discord_list_guild_members_cleanup(struct discord_list_guild_members *this)
{

    (void)this->limit;
}
static void
discord_search_guild_members_cleanup(struct discord_search_guild_members *this)
{

    if (this->query) free(this->query);

    (void)this->limit;
}
void
discord_add_guild_member_cleanup(struct discord_add_guild_member *this)
{

    if (this->access_token) free(this->access_token);

    if (this->nick) free(this->nick);

    if (this->roles) {
        snowflakes_cleanup(this->roles);
        free(this->roles);
    };

    (void)this->mute;

    (void)this->deaf;
}
void
discord_modify_guild_member_cleanup(struct discord_modify_guild_member *this)
{

    if (this->nick) free(this->nick);

    if (this->roles) {
        snowflakes_cleanup(this->roles);
        free(this->roles);
    };

    (void)this->mute;

    (void)this->deaf;

    ;
}
void
discord_modify_current_member_cleanup(
    struct discord_modify_current_member *this)
{

    if (this->nick) free(this->nick);
}
void
discord_modify_current_user_nick_cleanup(
    struct discord_modify_current_user_nick *this)
{

    if (this->nick) free(this->nick);
}
void
discord_create_guild_ban_cleanup(struct discord_create_guild_ban *this)
{

    (void)this->delete_message_days;

    if (this->reason) free(this->reason);
}
void
discord_create_guild_role_cleanup(struct discord_create_guild_role *this)
{

    if (this->name) free(this->name);

    (void)this->color;

    (void)this->hoist;

    if (this->icon) free(this->icon);

    if (this->unicode_emoji) free(this->unicode_emoji);

    (void)this->mentionable;
}
static void
discord_modify_guild_role_position_cleanup(
    struct discord_modify_guild_role_position *this)
{

    (void)this->position;
}
void
discord_modify_guild_role_positions_cleanup(
    struct discord_modify_guild_role_positions *this)
{
    __carray_free(
        this, struct discord_modify_guild_role_position, NULL,
        discord_modify_guild_role_position_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_modify_guild_role_cleanup(struct discord_modify_guild_role *this)
{

    if (this->name) free(this->name);

    (void)this->color;

    (void)this->hoist;

    if (this->icon) free(this->icon);

    if (this->unicode_emoji) free(this->unicode_emoji);

    (void)this->mentionable;
}
static void
discord_get_guild_prune_count_cleanup(
    struct discord_get_guild_prune_count *this)
{

    (void)this->count;

    if (this->include_roles) {
        snowflakes_cleanup(this->include_roles);
        free(this->include_roles);
    };
}
void
discord_begin_guild_prune_cleanup(struct discord_begin_guild_prune *this)
{

    (void)this->days;

    (void)this->compute_prune_count;

    if (this->include_roles) {
        snowflakes_cleanup(this->include_roles);
        free(this->include_roles);
    };

    if (this->reason) free(this->reason);
}
static void
discord_get_guild_widget_image_cleanup(
    struct discord_get_guild_widget_image *this)
{

    if (this->style) free(this->style);
}
void
discord_modify_guild_welcome_screen_cleanup(
    struct discord_modify_guild_welcome_screen *this)
{

    (void)this->enabled;

    if (this->welcome_channels) {
        discord_welcome_screen_channels_cleanup(this->welcome_channels);
        free(this->welcome_channels);
    };

    if (this->description) free(this->description);
}
void
discord_modify_current_user_voice_state_cleanup(
    struct discord_modify_current_user_voice_state *this)
{

    (void)this->suppress;

    ;
}
void
discord_modify_user_voice_state_cleanup(
    struct discord_modify_user_voice_state *this)
{

    (void)this->suppress;
}

void
discord_guild_scheduled_event_cleanup(
    struct discord_guild_scheduled_event *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    ;

    ;

    (void)this->privacy_level;

    (void)this->status;

    (void)this->entity_type;

    if (this->entity_metadata) {
        discord_guild_scheduled_event_entity_metadata_cleanup(
            this->entity_metadata);
        free(this->entity_metadata);
    };

    if (this->creator) {
        discord_user_cleanup(this->creator);
        free(this->creator);
    };

    (void)this->user_count;

    if (this->image) free(this->image);
}
void
discord_guild_scheduled_events_cleanup(
    struct discord_guild_scheduled_events *this)
{
    __carray_free(this, struct discord_guild_scheduled_event, NULL,
                  discord_guild_scheduled_event_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_guild_scheduled_event_entity_metadata_cleanup(
    struct discord_guild_scheduled_event_entity_metadata *this)
{

    if (this->location) free(this->location);
}
static void
discord_guild_scheduled_event_user_cleanup(
    struct discord_guild_scheduled_event_user *this)
{

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };

    if (this->member) {
        discord_guild_member_cleanup(this->member);
        free(this->member);
    };
}
void
discord_list_scheduled_events_for_guild_cleanup(
    struct discord_list_scheduled_events_for_guild *this)
{

    (void)this->with_user_count;
}
void
discord_create_guild_scheduled_event_cleanup(
    struct discord_create_guild_scheduled_event *this)
{

    if (this->entity_metadata) {
        discord_guild_scheduled_event_entity_metadata_cleanup(
            this->entity_metadata);
        free(this->entity_metadata);
    };

    if (this->name) free(this->name);

    ;

    ;

    if (this->description) free(this->description);

    (void)this->entity_type;

    if (this->image) free(this->image);
}
void
discord_get_guild_scheduled_event_cleanup(
    struct discord_get_guild_scheduled_event *this)
{

    (void)this->with_user_count;
}
void
discord_modify_guild_scheduled_event_cleanup(
    struct discord_modify_guild_scheduled_event *this)
{

    if (this->entity_metadata) {
        discord_guild_scheduled_event_entity_metadata_cleanup(
            this->entity_metadata);
        free(this->entity_metadata);
    };

    if (this->name) free(this->name);

    ;

    ;

    if (this->description) free(this->description);

    (void)this->entity_type;

    (void)this->status;

    if (this->image) free(this->image);
}
void
discord_get_guild_scheduled_event_users_cleanup(
    struct discord_get_guild_scheduled_event_users *this)
{

    (void)this->limit;

    (void)this->with_member;
}
void
discord_guild_template_cleanup(struct discord_guild_template *this)
{

    if (this->code) free(this->code);

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    (void)this->usage_count;

    if (this->creator) {
        discord_user_cleanup(this->creator);
        free(this->creator);
    };

    ;

    ;

    if (this->serialized_source_guild) {
        discord_guild_cleanup(this->serialized_source_guild);
        free(this->serialized_source_guild);
    };

    (void)this->is_dirty;
}
void
discord_create_guild_from_guild_template_cleanup(
    struct discord_create_guild_from_guild_template *this)
{

    if (this->name) free(this->name);

    if (this->icon) free(this->icon);
}
void
discord_create_guild_template_cleanup(
    struct discord_create_guild_template *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);
}
void
discord_modify_guild_template_cleanup(
    struct discord_modify_guild_template *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);
}

void
discord_stage_instance_cleanup(struct discord_stage_instance *this)
{

    if (this->topic) free(this->topic);

    (void)this->privacy_level;

    (void)this->discoverable_disabled;
}
static void
discord_stage_instances_cleanup(struct discord_stage_instances *this)
{
    __carray_free(this, struct discord_stage_instance, NULL,
                  discord_stage_instance_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_create_stage_instance_cleanup(
    struct discord_create_stage_instance *this)
{

    if (this->topic) free(this->topic);

    (void)this->privacy_level;
}
void
discord_modify_stage_instance_cleanup(
    struct discord_modify_stage_instance *this)
{

    if (this->topic) free(this->topic);

    (void)this->privacy_level;
}

void
discord_sticker_cleanup(struct discord_sticker *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    if (this->tags) free(this->tags);

    (void)this->type;

    (void)this->format_type;

    (void)this->available;

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };

    (void)this->sort_value;
}
static void
discord_stickers_cleanup(struct discord_stickers *this)
{
    __carray_free(this, struct discord_sticker, NULL,
                  discord_sticker_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_sticker_item_cleanup(struct discord_sticker_item *this)
{

    if (this->name) free(this->name);

    (void)this->format_type;
}
static void
discord_sticker_items_cleanup(struct discord_sticker_items *this)
{
    __carray_free(this, struct discord_sticker_item, NULL,
                  discord_sticker_item_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_sticker_pack_cleanup(struct discord_sticker_pack *this)
{

    if (this->stickers) {
        discord_stickers_cleanup(this->stickers);
        free(this->stickers);
    };

    if (this->name) free(this->name);

    if (this->description) free(this->description);
}
static void
discord_create_guild_sticker_cleanup(struct discord_create_guild_sticker *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    if (this->tags) free(this->tags);

    if (this->file) {
        discord_attachment_cleanup(this->file);
        free(this->file);
    };
}
void
discord_modify_guild_sticker_cleanup(struct discord_modify_guild_sticker *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    if (this->tags) free(this->tags);
}

void
discord_user_cleanup(struct discord_user *this)
{

    if (this->username) free(this->username);

    if (this->discriminator) free(this->discriminator);

    if (this->avatar) free(this->avatar);

    (void)this->bot;

    ;

    (void)this->mfa_enabled;

    if (this->banner) free(this->banner);

    (void)this->accent_color;

    if (this->locale) free(this->locale);

    (void)this->verified;

    if (this->email) free(this->email);

    (void)this->premium_type;
}
void
discord_users_cleanup(struct discord_users *this)
{
    __carray_free(this, struct discord_user, NULL,
                  discord_user_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_connection_cleanup(struct discord_connection *this)
{

    if (this->name) free(this->name);

    if (this->type) free(this->type);

    (void)this->revoked;

    if (this->integrations) {
        discord_integrations_cleanup(this->integrations);
        free(this->integrations);
    };

    (void)this->verified;

    (void)this->friend_sync;

    (void)this->show_activity;

    (void)this->visibility;
}
void
discord_connections_cleanup(struct discord_connections *this)
{
    __carray_free(this, struct discord_connection, NULL,
                  discord_connection_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_modify_current_user_cleanup(struct discord_modify_current_user *this)
{

    if (this->username) free(this->username);

    if (this->avatar) free(this->avatar);
}
static void
discord_get_current_user_guilds_cleanup(
    struct discord_get_current_user_guilds *this)
{

    (void)this->limit;
}
void
discord_create_dm_cleanup(struct discord_create_dm *this)
{
}
void
discord_create_group_dm_cleanup(struct discord_create_group_dm *this)
{

    if (this->access_tokens) {
        snowflakes_cleanup(this->access_tokens);
        free(this->access_tokens);
    };

    if (this->nicks) {
        strings_cleanup(this->nicks);
        free(this->nicks);
    };
}
void
discord_voice_state_cleanup(struct discord_voice_state *this)
{

    if (this->member) {
        discord_guild_member_cleanup(this->member);
        free(this->member);
    };

    if (this->session_id) free(this->session_id);

    (void)this->deaf;

    (void)this->mute;

    (void)this->self_deaf;

    (void)this->self_mute;

    (void)this->self_stream;

    (void)this->self_video;

    (void)this->suppress;

    ;
}
void
discord_voice_states_cleanup(struct discord_voice_states *this)
{
    __carray_free(this, struct discord_voice_state, NULL,
                  discord_voice_state_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_voice_region_cleanup(struct discord_voice_region *this)
{

    if (this->id) free(this->id);

    if (this->name) free(this->name);

    (void)this->optimal;

    (void)this->deprecated;

    (void)this->custom;
}
void
discord_voice_regions_cleanup(struct discord_voice_regions *this)
{
    __carray_free(this, struct discord_voice_region, NULL,
                  discord_voice_region_cleanup(&__CARRAY_OPERAND_A));
}

void
discord_webhook_cleanup(struct discord_webhook *this)
{

    (void)this->type;

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };

    if (this->name) free(this->name);

    if (this->token) free(this->token);

    if (this->source_channel) {
        discord_channel_cleanup(this->source_channel);
        free(this->source_channel);
    };

    if (this->url) free(this->url);
}
void
discord_webhooks_cleanup(struct discord_webhooks *this)
{
    __carray_free(this, struct discord_webhook, NULL,
                  discord_webhook_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_create_webhook_cleanup(struct discord_create_webhook *this)
{

    if (this->name) free(this->name);

    if (this->avatar) free(this->avatar);
}
void
discord_modify_webhook_cleanup(struct discord_modify_webhook *this)
{

    if (this->name) free(this->name);

    if (this->avatar) free(this->avatar);
}
void
discord_modify_webhook_with_token_cleanup(
    struct discord_modify_webhook_with_token *this)
{

    if (this->name) free(this->name);

    if (this->avatar) free(this->avatar);
}
void
discord_execute_webhook_cleanup(struct discord_execute_webhook *this)
{

    (void)this->wait;

    if (this->content) free(this->content);

    if (this->username) free(this->username);

    if (this->avatar_url) free(this->avatar_url);

    (void)this->tts;

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    if (this->allowed_mentions) {
        discord_allowed_mention_cleanup(this->allowed_mentions);
        free(this->allowed_mentions);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };
}
static void
discord_get_webhook_message_cleanup(struct discord_get_webhook_message *this)
{
}
void
discord_edit_webhook_message_cleanup(struct discord_edit_webhook_message *this)
{

    if (this->content) free(this->content);

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    if (this->allowed_mentions) {
        discord_allowed_mention_cleanup(this->allowed_mentions);
        free(this->allowed_mentions);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };
}
static void
discord_delete_webhook_message_cleanup(
    struct discord_delete_webhook_message *this)
{
}

void
discord_identify_cleanup(struct discord_identify *this)
{

    if (this->token) free(this->token);

    if (this->properties) {
        discord_identify_connection_cleanup(this->properties);
        free(this->properties);
    };

    (void)this->compress;

    (void)this->large_threshold;

    if (this->presence) {
        discord_presence_update_cleanup(this->presence);
        free(this->presence);
    };

    (void)this->intents;
}
static void
discord_identify_connection_cleanup(struct discord_identify_connection *this)
{

    if (this->os) free(this->os);

    if (this->browser) free(this->browser);

    if (this->device) free(this->device);
}
void
discord_voice_state_status_cleanup(struct discord_voice_state_status *this)
{

    (void)this->self_mute;

    (void)this->self_deaf;
}
void
discord_presence_update_cleanup(struct discord_presence_update *this)
{

    ;

    if (this->activities) {
        discord_activities_cleanup(this->activities);
        free(this->activities);
    };

    if (this->status) free(this->status);

    (void)this->afk;
}
static void
discord_presence_updates_cleanup(struct discord_presence_updates *this)
{
    __carray_free(this, struct discord_presence_update, NULL,
                  discord_presence_update_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_activity_cleanup(struct discord_activity *this)
{

    if (this->name) free(this->name);

    (void)this->type;

    if (this->url) free(this->url);

    ;

    if (this->timestamps) {
        discord_activity_timestamps_cleanup(this->timestamps);
        free(this->timestamps);
    };

    if (this->details) free(this->details);

    if (this->state) free(this->state);

    if (this->emoji) {
        discord_activity_emoji_cleanup(this->emoji);
        free(this->emoji);
    };

    if (this->party) {
        discord_activity_party_cleanup(this->party);
        free(this->party);
    };

    if (this->assets) {
        discord_activity_assets_cleanup(this->assets);
        free(this->assets);
    };

    if (this->secrets) {
        discord_activity_secrets_cleanup(this->secrets);
        free(this->secrets);
    };

    (void)this->instance;

    if (this->buttons) {
        discord_activity_buttons_cleanup(this->buttons);
        free(this->buttons);
    };
}
static void
discord_activities_cleanup(struct discord_activities *this)
{
    __carray_free(this, struct discord_activity, NULL,
                  discord_activity_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_activity_timestamps_cleanup(struct discord_activity_timestamps *this)
{

    ;

    ;
}
static void
discord_activity_emoji_cleanup(struct discord_activity_emoji *this)
{

    if (this->name) free(this->name);

    (void)this->animated;
}
static void
discord_activity_party_cleanup(struct discord_activity_party *this)
{

    if (this->id) free(this->id);

    if (this->size) {
        integers_cleanup(this->size);
        free(this->size);
    };
}
static void
discord_activity_assets_cleanup(struct discord_activity_assets *this)
{

    if (this->large_image) free(this->large_image);

    if (this->large_text) free(this->large_text);

    if (this->small_image) free(this->small_image);

    if (this->small_text) free(this->small_text);
}
static void
discord_activity_secrets_cleanup(struct discord_activity_secrets *this)
{

    if (this->join) free(this->join);

    if (this->spectate) free(this->spectate);

    if (this->match) free(this->match);
}
static void
discord_activity_button_cleanup(struct discord_activity_button *this)
{

    if (this->label) free(this->label);

    if (this->url) free(this->url);
}
static void
discord_activity_buttons_cleanup(struct discord_activity_buttons *this)
{
    __carray_free(this, struct discord_activity_button, NULL,
                  discord_activity_button_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_session_start_limit_cleanup(struct discord_session_start_limit *this)
{

    (void)this->total;

    (void)this->remaining;

    (void)this->reset_after;

    (void)this->max_concurrency;
}

void
discord_team_cleanup(struct discord_team *this)
{

    if (this->icon) free(this->icon);

    if (this->members) {
        discord_team_members_cleanup(this->members);
        free(this->members);
    };

    if (this->name) free(this->name);
}
static void
discord_team_member_cleanup(struct discord_team_member *this)
{

    (void)this->membership_state;

    if (this->permissions) {
        strings_cleanup(this->permissions);
        free(this->permissions);
    };

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };
}
static void
discord_team_members_cleanup(struct discord_team_members *this)
{
    __carray_free(this, struct discord_team_member, NULL,
                  discord_team_member_cleanup(&__CARRAY_OPERAND_A));
}

void
discord_application_command_cleanup(struct discord_application_command *this)
{

    (void)this->type;

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    if (this->options) {
        discord_application_command_options_cleanup(this->options);
        free(this->options);
    };

    (void)this->default_permission;
}
void
discord_application_commands_cleanup(struct discord_application_commands *this)
{
    __carray_free(this, struct discord_application_command, NULL,
                  discord_application_command_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_application_command_option_cleanup(
    struct discord_application_command_option *this)
{

    (void)this->type;

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    (void)this->required;

    if (this->choices) {
        discord_application_command_option_choices_cleanup(this->choices);
        free(this->choices);
    };

    if (this->options) {
        discord_application_command_options_cleanup(this->options);
        free(this->options);
    };

    if (this->channel_types) {
        integers_cleanup(this->channel_types);
        free(this->channel_types);
    };

    if (this->min_value) free(this->min_value);

    if (this->max_value) free(this->max_value);

    (void)this->autocomplete;
}
static void
discord_application_command_options_cleanup(
    struct discord_application_command_options *this)
{
    __carray_free(
        this, struct discord_application_command_option, NULL,
        discord_application_command_option_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_application_command_option_choice_cleanup(
    struct discord_application_command_option_choice *this)
{

    if (this->name) free(this->name);

    if (this->value) free(this->value);
}
static void
discord_application_command_option_choices_cleanup(
    struct discord_application_command_option_choices *this)
{
    __carray_free(this, struct discord_application_command_option_choice, NULL,
                  discord_application_command_option_choice_cleanup(
                      &__CARRAY_OPERAND_A));
}
static void
discord_application_command_interaction_data_option_cleanup(
    struct discord_application_command_interaction_data_option *this)
{

    if (this->name) free(this->name);

    (void)this->type;

    if (this->value) free(this->value);

    if (this->options) {
        discord_application_command_interaction_data_options_cleanup(
            this->options);
        free(this->options);
    };

    (void)this->focused;
}
static void
discord_application_command_interaction_data_options_cleanup(
    struct discord_application_command_interaction_data_options *this)
{
    __carray_free(
        this, struct discord_application_command_interaction_data_option, NULL,
        discord_application_command_interaction_data_option_cleanup(
            &__CARRAY_OPERAND_A));
}
static void
discord_guild_application_command_permission_cleanup(
    struct discord_guild_application_command_permission *this)
{

    if (this->permissions) {
        discord_application_command_permissions_cleanup(this->permissions);
        free(this->permissions);
    };
}
void
discord_guild_application_command_permissions_cleanup(
    struct discord_guild_application_command_permissions *this)
{
    __carray_free(this, struct discord_guild_application_command_permission,
                  NULL,
                  discord_guild_application_command_permission_cleanup(
                      &__CARRAY_OPERAND_A));
}
void
discord_application_command_permission_cleanup(
    struct discord_application_command_permission *this)
{

    (void)this->type;

    (void)this->permission;
}
void
discord_application_command_permissions_cleanup(
    struct discord_application_command_permissions *this)
{
    __carray_free(
        this, struct discord_application_command_permission, NULL,
        discord_application_command_permission_cleanup(&__CARRAY_OPERAND_A));
}
void
discord_create_global_application_command_cleanup(
    struct discord_create_global_application_command *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    if (this->options) {
        discord_application_command_options_cleanup(this->options);
        free(this->options);
    };

    (void)this->default_permission;

    (void)this->type;
}
void
discord_edit_global_application_command_cleanup(
    struct discord_edit_global_application_command *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    if (this->options) {
        discord_application_command_options_cleanup(this->options);
        free(this->options);
    };

    (void)this->default_permission;
}
void
discord_create_guild_application_command_cleanup(
    struct discord_create_guild_application_command *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    if (this->options) {
        discord_application_command_options_cleanup(this->options);
        free(this->options);
    };

    (void)this->default_permission;

    (void)this->type;
}
void
discord_edit_guild_application_command_cleanup(
    struct discord_edit_guild_application_command *this)
{

    if (this->name) free(this->name);

    if (this->description) free(this->description);

    if (this->options) {
        discord_application_command_options_cleanup(this->options);
        free(this->options);
    };

    (void)this->default_permission;
}
void
discord_edit_application_command_permissions_cleanup(
    struct discord_edit_application_command_permissions *this)
{

    if (this->permissions) {
        discord_application_command_permissions_cleanup(this->permissions);
        free(this->permissions);
    };
}

void
discord_component_cleanup(struct discord_component *this)
{

    (void)this->type;

    if (this->custom_id) free(this->custom_id);

    (void)this->disabled;

    (void)this->style;

    if (this->label) free(this->label);

    if (this->emoji) {
        discord_emoji_cleanup(this->emoji);
        free(this->emoji);
    };

    if (this->url) free(this->url);

    if (this->options) {
        discord_select_options_cleanup(this->options);
        free(this->options);
    };

    if (this->placeholder) free(this->placeholder);

    (void)this->min_values;

    (void)this->max_values;

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    (void)this->min_length;

    (void)this->max_length;

    (void)this->required;

    if (this->value) free(this->value);
}
void
discord_components_cleanup(struct discord_components *this)
{
    __carray_free(this, struct discord_component, NULL,
                  discord_component_cleanup(&__CARRAY_OPERAND_A));
}
static void
discord_select_option_cleanup(struct discord_select_option *this)
{

    if (this->label) free(this->label);

    if (this->value) free(this->value);

    if (this->description) free(this->description);

    if (this->emoji) {
        discord_emoji_cleanup(this->emoji);
        free(this->emoji);
    };

    ;
}
void
discord_select_options_cleanup(struct discord_select_options *this)
{
    __carray_free(this, struct discord_select_option, NULL,
                  discord_select_option_cleanup(&__CARRAY_OPERAND_A));
}

void
discord_interaction_cleanup(struct discord_interaction *this)
{

    (void)this->type;

    if (this->data) {
        discord_interaction_data_cleanup(this->data);
        free(this->data);
    };

    if (this->member) {
        discord_guild_member_cleanup(this->member);
        free(this->member);
    };

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };

    if (this->token) free(this->token);

    (void)this->version;

    if (this->message) {
        discord_message_cleanup(this->message);
        free(this->message);
    };

    if (this->locale) free(this->locale);

    if (this->guild_locale) free(this->guild_locale);
}
static void
discord_interaction_data_cleanup(struct discord_interaction_data *this)
{

    if (this->name) free(this->name);

    (void)this->type;

    if (this->resolved) {
        discord_resolved_data_cleanup(this->resolved);
        free(this->resolved);
    };

    if (this->options) {
        discord_application_command_interaction_data_options_cleanup(
            this->options);
        free(this->options);
    };

    if (this->custom_id) free(this->custom_id);

    (void)this->component_type;

    if (this->values) {
        strings_cleanup(this->values);
        free(this->values);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };
}
static void
discord_resolved_data_cleanup(struct discord_resolved_data *this)
{

    if (this->users) {
        snowflakes_cleanup(this->users);
        free(this->users);
    };

    if (this->members) {
        snowflakes_cleanup(this->members);
        free(this->members);
    };

    if (this->roles) {
        snowflakes_cleanup(this->roles);
        free(this->roles);
    };

    if (this->channels) {
        snowflakes_cleanup(this->channels);
        free(this->channels);
    };

    if (this->messages) {
        snowflakes_cleanup(this->messages);
        free(this->messages);
    };

    if (this->attachments) {
        snowflakes_cleanup(this->attachments);
        free(this->attachments);
    };
}
static void
discord_message_interaction_cleanup(struct discord_message_interaction *this)
{

    (void)this->type;

    if (this->name) free(this->name);

    if (this->user) {
        discord_user_cleanup(this->user);
        free(this->user);
    };

    if (this->member) {
        discord_guild_member_cleanup(this->member);
        free(this->member);
    };
}
void
discord_interaction_response_cleanup(struct discord_interaction_response *this)
{

    (void)this->type;

    if (this->data) {
        discord_interaction_callback_data_cleanup(this->data);
        free(this->data);
    };
}
static void
discord_interaction_callback_data_cleanup(
    struct discord_interaction_callback_data *this)
{

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    (void)this->tts;

    if (this->content) free(this->content);

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    (void)this->flags;

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };

    if (this->choices) {
        discord_application_command_option_choices_cleanup(this->choices);
        free(this->choices);
    };

    if (this->custom_id) free(this->custom_id);

    if (this->title) free(this->title);
}
void
discord_edit_original_interaction_response_cleanup(
    struct discord_edit_original_interaction_response *this)
{

    if (this->content) free(this->content);

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    if (this->allowed_mentions) {
        discord_allowed_mention_cleanup(this->allowed_mentions);
        free(this->allowed_mentions);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };
}
void
discord_create_followup_message_cleanup(
    struct discord_create_followup_message *this)
{

    (void)this->wait;

    if (this->avatar_url) free(this->avatar_url);

    (void)this->tts;

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    if (this->allowed_mentions) {
        discord_allowed_mention_cleanup(this->allowed_mentions);
        free(this->allowed_mentions);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };
}
void
discord_edit_followup_message_cleanup(
    struct discord_edit_followup_message *this)
{

    if (this->content) free(this->content);

    if (this->embeds) {
        discord_embeds_cleanup(this->embeds);
        free(this->embeds);
    };

    if (this->allowed_mentions) {
        discord_allowed_mention_cleanup(this->allowed_mentions);
        free(this->allowed_mentions);
    };

    if (this->components) {
        discord_components_cleanup(this->components);
        free(this->components);
    };

    if (this->attachments) {
        discord_attachments_cleanup(this->attachments);
        free(this->attachments);
    };
}
size_t
strings_from_jsmnf(jsmnf *root, const char buf[], struct strings *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, char *, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        char *o;
        if (f && f->val->type == JSMN_STRING)
            ret += jsmnf_unescape(&o, buf + f->val->start,
                                  f->val->end - f->val->start);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
json_values_from_jsmnf(jsmnf *root, const char buf[], struct json_values *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, json_char *, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        json_char *o;
        if (f) {
            o = _gc_strndup(buf + f->val->start, f->val->end - f->val->start);
            ret += f->val->end - f->val->start;
        };
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
snowflakes_from_jsmnf(jsmnf *root, const char buf[], struct snowflakes *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, u64snowflake, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        u64snowflake o;
        if (f) sscanf(buf + f->val->start, "%" SCNu64, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
integers_from_jsmnf(jsmnf *root, const char buf[], struct integers *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, int, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        int o;
        if (f && f->val->type == JSMN_PRIMITIVE)
            o = (int)strtol(buf + f->val->start, NULL, 10);
        carray_insert(this, f->idx, o);
    }
    return ret;
}

size_t
discord_role_from_jsmnf(jsmnf *root,
                        const char buf[],
                        struct discord_role *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "color", sizeof("color") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->color = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "hoist", sizeof("hoist") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->hoist = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "unicode_emoji", sizeof("unicode_emoji") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->unicode_emoji, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "position", sizeof("position") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->position = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->permissions, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "managed", sizeof("managed") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->managed = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "mentionable", sizeof("mentionable") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mentionable = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "tags", sizeof("tags") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->tags = calloc(1, sizeof *this->tags);
        ret += sizeof *this->tags
               + discord_role_tag_from_jsmnf(f, buf, this->tags);
    };

    return ret;
}
size_t
discord_roles_from_jsmnf(jsmnf *root,
                         const char buf[],
                         struct discord_roles *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_role, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_role o = { 0 };
        ret += discord_role_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_role_tag_from_jsmnf(jsmnf *root,
                            const char buf[],
                            struct discord_role_tag *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "bot_id", sizeof("bot_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->bot_id);

    f = jsmnf_find(root, "integration_id", sizeof("integration_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->integration_id);

    f = jsmnf_find(root, "premium_subscribe", sizeof("premium_subscribe") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->premium_subscribe = ('t' == buf[f->val->start]);
    return ret;
}

size_t
discord_application_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_application *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "rpc_origins", sizeof("rpc_origins") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->rpc_origins = calloc(1, sizeof *this->rpc_origins);
        ret += sizeof *this->rpc_origins
               + strings_from_jsmnf(f, buf, this->rpc_origins);
    };

    f = jsmnf_find(root, "bot_public", sizeof("bot_public") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->bot_public = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "bot_require_code_grant",
                   sizeof("bot_require_code_grant") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->bot_require_code_grant = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "terms_of_service_url",
                   sizeof("terms_of_service_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->terms_of_service_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "privacy_policy_url",
                   sizeof("privacy_policy_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->privacy_policy_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "owner", sizeof("owner") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->owner = calloc(1, sizeof *this->owner);
        ret +=
            sizeof *this->owner + discord_user_from_jsmnf(f, buf, this->owner);
    };

    f = jsmnf_find(root, "summary", sizeof("summary") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->summary, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "verify_key", sizeof("verify_key") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->verify_key, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "team", sizeof("team") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->team = calloc(1, sizeof *this->team);
        ret +=
            sizeof *this->team + discord_team_from_jsmnf(f, buf, this->team);
    };

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "primary_sku_id", sizeof("primary_sku_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->primary_sku_id);

    f = jsmnf_find(root, "slug", sizeof("slug") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->slug, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "cover_image", sizeof("cover_image") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->cover_image, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->flags);
    return ret;
}

size_t
discord_audit_log_from_jsmnf(jsmnf *root,
                             const char buf[],
                             struct discord_audit_log *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "audit_log_entries", sizeof("audit_log_entries") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->audit_log_entries = calloc(1, sizeof *this->audit_log_entries);
        ret += sizeof *this->audit_log_entries
               + discord_audit_log_entries_from_jsmnf(f, buf,
                                                      this->audit_log_entries);
    };

    f = jsmnf_find(root, "guild_scheduled_events",
                   sizeof("guild_scheduled_events") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->guild_scheduled_events =
            calloc(1, sizeof *this->guild_scheduled_events);
        ret += sizeof *this->guild_scheduled_events
               + discord_guild_scheduled_events_from_jsmnf(
                   f, buf, this->guild_scheduled_events);
    };

    f = jsmnf_find(root, "integrations", sizeof("integrations") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->integrations = calloc(1, sizeof *this->integrations);
        ret += sizeof *this->integrations
               + discord_integrations_from_jsmnf(f, buf, this->integrations);
    };

    f = jsmnf_find(root, "threads", sizeof("threads") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->threads = calloc(1, sizeof *this->threads);
        ret += sizeof *this->threads
               + discord_channels_from_jsmnf(f, buf, this->threads);
    };

    f = jsmnf_find(root, "users", sizeof("users") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->users = calloc(1, sizeof *this->users);
        ret += sizeof *this->users
               + discord_users_from_jsmnf(f, buf, this->users);
    };

    f = jsmnf_find(root, "webhooks", sizeof("webhooks") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->webhooks = calloc(1, sizeof *this->webhooks);
        ret += sizeof *this->webhooks
               + discord_webhooks_from_jsmnf(f, buf, this->webhooks);
    };

    return ret;
}
static size_t
discord_audit_log_entry_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_audit_log_entry *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "target_id", sizeof("target_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->target_id);

    f = jsmnf_find(root, "changes", sizeof("changes") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->changes = calloc(1, sizeof *this->changes);
        ret += sizeof *this->changes
               + discord_audit_log_changes_from_jsmnf(f, buf, this->changes);
    };

    f = jsmnf_find(root, "user_id", sizeof("user_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->user_id);

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "action_type", sizeof("action_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->action_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret += sizeof *this->options
               + discord_optional_audit_entry_infos_from_jsmnf(f, buf,
                                                               this->options);
    };

    f = jsmnf_find(root, "reason", sizeof("reason") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->reason, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_audit_log_entries_from_jsmnf(jsmnf *root,
                                     const char buf[],
                                     struct discord_audit_log_entries *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_audit_log_entry, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_audit_log_entry o = { 0 };
        ret += discord_audit_log_entry_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_optional_audit_entry_info_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_optional_audit_entry_info *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "count", sizeof("count") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->count, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "delete_member_days",
                   sizeof("delete_member_days") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->delete_member_days, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "members_removed", sizeof("members_removed") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->members_removed, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "message_id", sizeof("message_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->message_id);

    f = jsmnf_find(root, "role_name", sizeof("role_name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->role_name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->type, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_optional_audit_entry_infos_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_optional_audit_entry_infos *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_optional_audit_entry_info, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_optional_audit_entry_info o = { 0 };
        ret += discord_optional_audit_entry_info_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_audit_log_change_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_audit_log_change *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "new_value", sizeof("new_value") - 1);
    if (f) {
        this->new_value =
            _gc_strndup(buf + f->val->start, f->val->end - f->val->start);
        ret += f->val->end - f->val->start;
    };

    f = jsmnf_find(root, "old_value", sizeof("old_value") - 1);
    if (f) {
        this->old_value =
            _gc_strndup(buf + f->val->start, f->val->end - f->val->start);
        ret += f->val->end - f->val->start;
    };

    f = jsmnf_find(root, "key", sizeof("key") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->key, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_audit_log_changes_from_jsmnf(jsmnf *root,
                                     const char buf[],
                                     struct discord_audit_log_changes *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_audit_log_change, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_audit_log_change o = { 0 };
        ret += discord_audit_log_change_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_get_guild_audit_log_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_guild_audit_log *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "user_id", sizeof("user_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->user_id);

    f = jsmnf_find(root, "action_type", sizeof("action_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->action_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "before", sizeof("before") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->before);

    f = jsmnf_find(root, "limit", sizeof("limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->limit = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}

size_t
discord_invite_from_jsmnf(jsmnf *root,
                          const char buf[],
                          struct discord_invite *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "code", sizeof("code") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->code, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "guild", sizeof("guild") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->guild = calloc(1, sizeof *this->guild);
        ret += sizeof *this->guild
               + discord_guild_from_jsmnf(f, buf, this->guild);
    };

    f = jsmnf_find(root, "channel", sizeof("channel") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->channel = calloc(1, sizeof *this->channel);
        ret += sizeof *this->channel
               + discord_channel_from_jsmnf(f, buf, this->channel);
    };

    f = jsmnf_find(root, "inviter", sizeof("inviter") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->inviter = calloc(1, sizeof *this->inviter);
        ret += sizeof *this->inviter
               + discord_user_from_jsmnf(f, buf, this->inviter);
    };

    f = jsmnf_find(root, "target_type", sizeof("target_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->target_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "target_user", sizeof("target_user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->target_user = calloc(1, sizeof *this->target_user);
        ret += sizeof *this->target_user
               + discord_user_from_jsmnf(f, buf, this->target_user);
    };

    f = jsmnf_find(root, "target_application",
                   sizeof("target_application") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->target_application = calloc(1, sizeof *this->target_application);
        ret +=
            sizeof *this->target_application
            + discord_application_from_jsmnf(f, buf, this->target_application);
    };

    f = jsmnf_find(root, "approximate_presence_count",
                   sizeof("approximate_presence_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->approximate_presence_count =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "approximate_member_count",
                   sizeof("approximate_member_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->approximate_member_count =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "expires_at", sizeof("expires_at") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->expires_at);

    f = jsmnf_find(root, "stage_instance", sizeof("stage_instance") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->stage_instance = calloc(1, sizeof *this->stage_instance);
        ret += sizeof *this->stage_instance
               + discord_invite_stage_instance_from_jsmnf(
                   f, buf, this->stage_instance);
    };

    f = jsmnf_find(root, "guild_scheduled_event",
                   sizeof("guild_scheduled_event") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->guild_scheduled_event =
            calloc(1, sizeof *this->guild_scheduled_event);
        ret += sizeof *this->guild_scheduled_event
               + discord_guild_scheduled_event_from_jsmnf(
                   f, buf, this->guild_scheduled_event);
    };

    return ret;
}
size_t
discord_invites_from_jsmnf(jsmnf *root,
                           const char buf[],
                           struct discord_invites *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_invite, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_invite o = { 0 };
        ret += discord_invite_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_invite_metadata_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_invite_metadata *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "uses", sizeof("uses") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->uses = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "max_uses", sizeof("max_uses") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_uses = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "max_age", sizeof("max_age") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_age = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "temporary", sizeof("temporary") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->temporary = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "created_at", sizeof("created_at") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->created_at);

    return ret;
}
static size_t
discord_invite_stage_instance_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_invite_stage_instance *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "members", sizeof("members") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->members = calloc(1, sizeof *this->members);
        ret += sizeof *this->members
               + discord_guild_members_from_jsmnf(f, buf, this->members);
    };

    f = jsmnf_find(root, "participant_count", sizeof("participant_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->participant_count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "speaker_count", sizeof("speaker_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->speaker_count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "topic", sizeof("topic") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->topic, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
size_t
discord_get_invite_from_jsmnf(jsmnf *root,
                              const char buf[],
                              struct discord_get_invite *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "with_counts", sizeof("with_counts") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->with_counts = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "with_expiration", sizeof("with_expiration") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->with_expiration = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "guild_scheduled_event_id",
                   sizeof("guild_scheduled_event_id") - 1);
    if (f)
        sscanf(buf + f->val->start, "%" SCNu64,
               &this->guild_scheduled_event_id);

    return ret;
}

size_t
discord_channel_from_jsmnf(jsmnf *root,
                           const char buf[],
                           struct discord_channel *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "position", sizeof("position") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->position = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "permission_overwrites",
                   sizeof("permission_overwrites") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->permission_overwrites =
            calloc(1, sizeof *this->permission_overwrites);
        ret += sizeof *this->permission_overwrites
               + discord_overwrites_from_jsmnf(f, buf,
                                               this->permission_overwrites);
    };

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "topic", sizeof("topic") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->topic, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "nsfw", sizeof("nsfw") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->nsfw = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "last_message_id", sizeof("last_message_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->last_message_id);

    f = jsmnf_find(root, "bitrate", sizeof("bitrate") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->bitrate = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "user_limit", sizeof("user_limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->user_limit = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "rate_limit_per_user",
                   sizeof("rate_limit_per_user") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->rate_limit_per_user = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "recipients", sizeof("recipients") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->recipients = calloc(1, sizeof *this->recipients);
        ret += sizeof *this->recipients
               + discord_users_from_jsmnf(f, buf, this->recipients);
    };

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "owner_id", sizeof("owner_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->owner_id);

    f = jsmnf_find(root, "application_id", sizeof("application_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->application_id);

    f = jsmnf_find(root, "parent_id", sizeof("parent_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->parent_id);

    f = jsmnf_find(root, "last_pin_timestamp",
                   sizeof("last_pin_timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->last_pin_timestamp);

    f = jsmnf_find(root, "rtc_region", sizeof("rtc_region") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->rtc_region, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "voice_quality_mode",
                   sizeof("voice_quality_mode") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->voice_quality_mode = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "message_count", sizeof("message_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->message_count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "member_count", sizeof("member_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->member_count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "thread_metadata", sizeof("thread_metadata") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->thread_metadata = calloc(1, sizeof *this->thread_metadata);
        ret += sizeof *this->thread_metadata
               + discord_thread_metadata_from_jsmnf(f, buf,
                                                    this->thread_metadata);
    };

    f = jsmnf_find(root, "member", sizeof("member") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->member = calloc(1, sizeof *this->member);
        ret += sizeof *this->member
               + discord_thread_member_from_jsmnf(f, buf, this->member);
    };

    f = jsmnf_find(root, "default_auto_archive_duration",
                   sizeof("default_auto_archive_duration") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_auto_archive_duration =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->permissions, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
size_t
discord_channels_from_jsmnf(jsmnf *root,
                            const char buf[],
                            struct discord_channels *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_channel, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_channel o = { 0 };
        ret += discord_channel_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_message_from_jsmnf(jsmnf *root,
                           const char buf[],
                           struct discord_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "author", sizeof("author") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->author = calloc(1, sizeof *this->author);
        ret += sizeof *this->author
               + discord_user_from_jsmnf(f, buf, this->author);
    };

    f = jsmnf_find(root, "member", sizeof("member") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->member = calloc(1, sizeof *this->member);
        ret += sizeof *this->member
               + discord_guild_member_from_jsmnf(f, buf, this->member);
    };

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "timestamp", sizeof("timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->timestamp);

    f = jsmnf_find(root, "edited_timestamp", sizeof("edited_timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->edited_timestamp);

    f = jsmnf_find(root, "tts", sizeof("tts") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->tts = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "mention_everyone", sizeof("mention_everyone") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mention_everyone = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "mentions", sizeof("mentions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->mentions = calloc(1, sizeof *this->mentions);
        ret += sizeof *this->mentions
               + discord_users_from_jsmnf(f, buf, this->mentions);
    };

    f = jsmnf_find(root, "mention_roles", sizeof("mention_roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->mention_roles = calloc(1, sizeof *this->mention_roles);
        ret += sizeof *this->mention_roles
               + discord_roles_from_jsmnf(f, buf, this->mention_roles);
    };

    f = jsmnf_find(root, "mention_channels", sizeof("mention_channels") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->mention_channels = calloc(1, sizeof *this->mention_channels);
        ret += sizeof *this->mention_channels
               + discord_channels_from_jsmnf(f, buf, this->mention_channels);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "reactions", sizeof("reactions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->reactions = calloc(1, sizeof *this->reactions);
        ret += sizeof *this->reactions
               + discord_reactions_from_jsmnf(f, buf, this->reactions);
    };

    f = jsmnf_find(root, "nonce", sizeof("nonce") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->nonce, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "pinned", sizeof("pinned") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->pinned = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "webhook_id", sizeof("webhook_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->webhook_id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "activity", sizeof("activity") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->activity = calloc(1, sizeof *this->activity);
        ret += sizeof *this->activity
               + discord_message_activity_from_jsmnf(f, buf, this->activity);
    };

    f = jsmnf_find(root, "application", sizeof("application") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->application = calloc(1, sizeof *this->application);
        ret += sizeof *this->application
               + discord_application_from_jsmnf(f, buf, this->application);
    };

    f = jsmnf_find(root, "application_id", sizeof("application_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->application_id);

    f = jsmnf_find(root, "message_reference", sizeof("message_reference") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->message_reference = calloc(1, sizeof *this->message_reference);
        ret += sizeof *this->message_reference
               + discord_message_reference_from_jsmnf(f, buf,
                                                      this->message_reference);
    };

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->flags = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "referenced_message",
                   sizeof("referenced_message") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->referenced_message = calloc(1, sizeof *this->referenced_message);
        ret += sizeof *this->referenced_message
               + discord_message_from_jsmnf(f, buf, this->referenced_message);
    };

    f = jsmnf_find(root, "interaction", sizeof("interaction") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->interaction = calloc(1, sizeof *this->interaction);
        ret += sizeof *this->interaction
               + discord_message_interaction_from_jsmnf(f, buf,
                                                        this->interaction);
    };

    f = jsmnf_find(root, "thread", sizeof("thread") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->thread = calloc(1, sizeof *this->thread);
        ret += sizeof *this->thread
               + discord_channel_from_jsmnf(f, buf, this->thread);
    };

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "sticker_items", sizeof("sticker_items") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->sticker_items = calloc(1, sizeof *this->sticker_items);
        ret += sizeof *this->sticker_items
               + discord_sticker_items_from_jsmnf(f, buf, this->sticker_items);
    };
    return ret;
}
size_t
discord_messages_from_jsmnf(jsmnf *root,
                            const char buf[],
                            struct discord_messages *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_message, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_message o = { 0 };
        ret += discord_message_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_message_activity_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_message_activity *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "party_id", sizeof("party_id") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->party_id, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_message_reference_from_jsmnf(jsmnf *root,
                                     const char buf[],
                                     struct discord_message_reference *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "message_id", sizeof("message_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->message_id);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "fail_if_not_exists",
                   sizeof("fail_if_not_exists") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->fail_if_not_exists = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_followed_channel_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_followed_channel *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "webhook_id", sizeof("webhook_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->webhook_id);
    return ret;
}
static size_t
discord_reaction_from_jsmnf(jsmnf *root,
                            const char buf[],
                            struct discord_reaction *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "count", sizeof("count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "me", sizeof("me") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->me = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "emoji", sizeof("emoji") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->emoji = calloc(1, sizeof *this->emoji);
        ret += sizeof *this->emoji
               + discord_emoji_from_jsmnf(f, buf, this->emoji);
    };
    return ret;
}
static size_t
discord_reactions_from_jsmnf(jsmnf *root,
                             const char buf[],
                             struct discord_reactions *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_reaction, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_reaction o = { 0 };
        ret += discord_reaction_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_overwrite_from_jsmnf(jsmnf *root,
                             const char buf[],
                             struct discord_overwrite *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "allow", sizeof("allow") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->allow);

    f = jsmnf_find(root, "deny", sizeof("deny") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->deny);
    return ret;
}
static size_t
discord_overwrites_from_jsmnf(jsmnf *root,
                              const char buf[],
                              struct discord_overwrites *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_overwrite, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_overwrite o = { 0 };
        ret += discord_overwrite_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_thread_metadata_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_thread_metadata *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "archived", sizeof("archived") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->archived = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "auto_archive_duration",
                   sizeof("auto_archive_duration") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->auto_archive_duration =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "archive_timestamp", sizeof("archive_timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->archive_timestamp);

    f = jsmnf_find(root, "locked", sizeof("locked") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->locked = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "invitable", sizeof("invitable") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->invitable = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "create_timestamp", sizeof("create_timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->create_timestamp);
    return ret;
}
static size_t
discord_thread_member_from_jsmnf(jsmnf *root,
                                 const char buf[],
                                 struct discord_thread_member *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "user_id", sizeof("user_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->user_id);

    f = jsmnf_find(root, "join_timestamp", sizeof("join_timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->join_timestamp);

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->flags = (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}
size_t
discord_thread_members_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_thread_members *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_thread_member, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_thread_member o = { 0 };
        ret += discord_thread_member_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_attachment_from_jsmnf(jsmnf *root,
                              const char buf[],
                              struct discord_attachment *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "filename", sizeof("filename") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->filename, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "content_type", sizeof("content_type") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content_type, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "size", sizeof("size") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->size = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "proxy_url", sizeof("proxy_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->proxy_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "height", sizeof("height") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->height = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "width", sizeof("width") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->width = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "ephemeral", sizeof("ephemeral") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->ephemeral = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_attachments_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_attachments *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_attachment, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_attachment o = { 0 };
        ret += discord_attachment_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_embed_from_jsmnf(jsmnf *root,
                         const char buf[],
                         struct discord_embed *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "title", sizeof("title") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->title, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->type, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "timestamp", sizeof("timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->timestamp);

    f = jsmnf_find(root, "color", sizeof("color") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->color = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "footer", sizeof("footer") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->footer = calloc(1, sizeof *this->footer);
        ret += sizeof *this->footer
               + discord_embed_footer_from_jsmnf(f, buf, this->footer);
    };

    f = jsmnf_find(root, "image", sizeof("image") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->image = calloc(1, sizeof *this->image);
        ret += sizeof *this->image
               + discord_embed_image_from_jsmnf(f, buf, this->image);
    };

    f = jsmnf_find(root, "thumbnail", sizeof("thumbnail") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->thumbnail = calloc(1, sizeof *this->thumbnail);
        ret += sizeof *this->thumbnail
               + discord_embed_thumbnail_from_jsmnf(f, buf, this->thumbnail);
    };

    f = jsmnf_find(root, "video", sizeof("video") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->video = calloc(1, sizeof *this->video);
        ret += sizeof *this->video
               + discord_embed_video_from_jsmnf(f, buf, this->video);
    };

    f = jsmnf_find(root, "provider", sizeof("provider") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->provider = calloc(1, sizeof *this->provider);
        ret += sizeof *this->provider
               + discord_embed_provider_from_jsmnf(f, buf, this->provider);
    };

    f = jsmnf_find(root, "author", sizeof("author") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->author = calloc(1, sizeof *this->author);
        ret += sizeof *this->author
               + discord_embed_author_from_jsmnf(f, buf, this->author);
    };

    f = jsmnf_find(root, "fields", sizeof("fields") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->fields = calloc(1, sizeof *this->fields);
        ret += sizeof *this->fields
               + discord_embed_fields_from_jsmnf(f, buf, this->fields);
    };

    return ret;
}
size_t
discord_embeds_from_jsmnf(jsmnf *root,
                          const char buf[],
                          struct discord_embeds *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_embed, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_embed o = { 0 };
        ret += discord_embed_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_embed_thumbnail_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_embed_thumbnail *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "proxy_url", sizeof("proxy_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->proxy_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "height", sizeof("height") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->height = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "width", sizeof("width") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->width = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_embed_video_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_embed_video *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "proxy_url", sizeof("proxy_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->proxy_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "height", sizeof("height") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->height = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "width", sizeof("width") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->width = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_embed_image_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_embed_image *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "proxy_url", sizeof("proxy_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->proxy_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "height", sizeof("height") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->height = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "width", sizeof("width") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->width = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_embed_provider_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_embed_provider *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_embed_author_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_embed_author *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon_url", sizeof("icon_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "proxy_icon_url", sizeof("proxy_icon_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->proxy_icon_url, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_embed_footer_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_embed_footer *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "text", sizeof("text") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->text, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon_url", sizeof("icon_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "proxy_icon_url", sizeof("proxy_icon_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->proxy_icon_url, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_embed_field_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_embed_field *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "value", sizeof("value") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->value, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "inline", sizeof("inline") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->Inline = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_embed_fields_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_embed_fields *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_embed_field, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_embed_field o = { 0 };
        ret += discord_embed_field_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_channel_mention_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_channel_mention *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_allowed_mention_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_allowed_mention *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "parse", sizeof("parse") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->parse = calloc(1, sizeof *this->parse);
        ret += sizeof *this->parse + strings_from_jsmnf(f, buf, this->parse);
    };

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret +=
            sizeof *this->roles + snowflakes_from_jsmnf(f, buf, this->roles);
    };

    f = jsmnf_find(root, "users", sizeof("users") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->users = calloc(1, sizeof *this->users);
        ret +=
            sizeof *this->users + snowflakes_from_jsmnf(f, buf, this->users);
    };

    f = jsmnf_find(root, "replied_user", sizeof("replied_user") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->replied_user = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_thread_response_body_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_thread_response_body *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "threads", sizeof("threads") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->threads = calloc(1, sizeof *this->threads);
        ret += sizeof *this->threads
               + discord_channels_from_jsmnf(f, buf, this->threads);
    };

    f = jsmnf_find(root, "members", sizeof("members") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->members = calloc(1, sizeof *this->members);
        ret += sizeof *this->members
               + discord_thread_members_from_jsmnf(f, buf, this->members);
    };

    f = jsmnf_find(root, "has_more", sizeof("has_more") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->has_more = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_modify_channel_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_modify_channel *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "position", sizeof("position") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->position = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "topic", sizeof("topic") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->topic, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "nsfw", sizeof("nsfw") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->nsfw = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "rate_limit_per_user",
                   sizeof("rate_limit_per_user") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->rate_limit_per_user = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "user_limit", sizeof("user_limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->user_limit = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "permission_overwrites",
                   sizeof("permission_overwrites") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->permission_overwrites =
            calloc(1, sizeof *this->permission_overwrites);
        ret += sizeof *this->permission_overwrites
               + discord_overwrites_from_jsmnf(f, buf,
                                               this->permission_overwrites);
    };

    f = jsmnf_find(root, "parent_id", sizeof("parent_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->parent_id);

    f = jsmnf_find(root, "rtc_region", sizeof("rtc_region") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->rtc_region, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "video_quality_mode",
                   sizeof("video_quality_mode") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->video_quality_mode = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "default_auto_archive_duration",
                   sizeof("default_auto_archive_duration") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_auto_archive_duration =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "archived", sizeof("archived") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->archived = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "auto_archive_duration",
                   sizeof("auto_archive_duration") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->auto_archive_duration =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "locked", sizeof("locked") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->locked = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "invitable", sizeof("invitable") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->invitable = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_get_channel_messages_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_channel_messages *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "around", sizeof("around") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->around);

    f = jsmnf_find(root, "before", sizeof("before") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->before);

    f = jsmnf_find(root, "after", sizeof("after") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->after);

    f = jsmnf_find(root, "limit", sizeof("limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->limit = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_create_message_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_create_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "tts", sizeof("tts") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->tts = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "allowed_mentions", sizeof("allowed_mentions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->allowed_mentions = calloc(1, sizeof *this->allowed_mentions);
        ret += sizeof *this->allowed_mentions
               + discord_allowed_mention_from_jsmnf(f, buf,
                                                    this->allowed_mentions);
    };

    f = jsmnf_find(root, "message_reference", sizeof("message_reference") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->message_reference = calloc(1, sizeof *this->message_reference);
        ret += sizeof *this->message_reference
               + discord_message_reference_from_jsmnf(f, buf,
                                                      this->message_reference);
    };

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "sticker_ids", sizeof("sticker_ids") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->sticker_ids = calloc(1, sizeof *this->sticker_ids);
        ret += sizeof *this->sticker_ids
               + snowflakes_from_jsmnf(f, buf, this->sticker_ids);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->flags = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_get_reactions_from_jsmnf(jsmnf *root,
                                 const char buf[],
                                 struct discord_get_reactions *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "after", sizeof("after") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->after);

    f = jsmnf_find(root, "limit", sizeof("limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->limit = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_edit_message_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_edit_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->flags = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "allowed_mentions", sizeof("allowed_mentions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->allowed_mentions = calloc(1, sizeof *this->allowed_mentions);
        ret += sizeof *this->allowed_mentions
               + discord_allowed_mention_from_jsmnf(f, buf,
                                                    this->allowed_mentions);
    };

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    return ret;
}
size_t
discord_bulk_delete_messages_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_bulk_delete_messages *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "messages", sizeof("messages") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->messages = calloc(1, sizeof *this->messages);
        ret += sizeof *this->messages
               + snowflakes_from_jsmnf(f, buf, this->messages);
    };
    return ret;
}
size_t
discord_edit_channel_permissions_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_edit_channel_permissions *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "allow", sizeof("allow") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->allow);

    f = jsmnf_find(root, "deny", sizeof("deny") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->deny);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}
size_t
discord_create_channel_invite_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_channel_invite *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "max_age", sizeof("max_age") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_age = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "max_uses", sizeof("max_uses") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_uses = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "temporary", sizeof("temporary") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->temporary = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "unique", sizeof("unique") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->unique = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "target_type", sizeof("target_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->target_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "target_user_id", sizeof("target_user_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->target_user_id);

    f = jsmnf_find(root, "target_application_id",
                   sizeof("target_application_id") - 1);
    if (f)
        sscanf(buf + f->val->start, "%" SCNu64, &this->target_application_id);

    return ret;
}
size_t
discord_follow_news_channel_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_follow_news_channel *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "webhook_channel_id",
                   sizeof("webhook_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->webhook_channel_id);

    return ret;
}
size_t
discord_group_dm_add_recipient_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_group_dm_add_recipient *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "access_token", sizeof("access_token") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->access_token, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "nick", sizeof("nick") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->nick, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
size_t
discord_start_thread_with_message_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_start_thread_with_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "auto_archive_duration",
                   sizeof("auto_archive_duration") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->auto_archive_duration =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "rate_limit_per_user",
                   sizeof("rate_limit_per_user") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->rate_limit_per_user = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_start_thread_without_message_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_start_thread_without_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "auto_archive_duration",
                   sizeof("auto_archive_duration") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->auto_archive_duration =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "invitable", sizeof("invitable") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->invitable = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "rate_limit_per_user",
                   sizeof("rate_limit_per_user") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->rate_limit_per_user = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_list_active_threads_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_list_active_threads *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "threads", sizeof("threads") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->threads = calloc(1, sizeof *this->threads);
        ret += sizeof *this->threads
               + discord_channels_from_jsmnf(f, buf, this->threads);
    };

    f = jsmnf_find(root, "members", sizeof("members") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->members = calloc(1, sizeof *this->members);
        ret += sizeof *this->members
               + discord_thread_members_from_jsmnf(f, buf, this->members);
    };

    f = jsmnf_find(root, "has_more", sizeof("has_more") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->has_more = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_emoji_from_jsmnf(jsmnf *root,
                         const char buf[],
                         struct discord_emoji *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret += sizeof *this->roles
               + discord_roles_from_jsmnf(f, buf, this->roles);
    };

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    f = jsmnf_find(root, "require_colons", sizeof("require_colons") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->require_colons = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "managed", sizeof("managed") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->managed = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "animated", sizeof("animated") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->animated = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "available", sizeof("available") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->available = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_emojis_from_jsmnf(jsmnf *root,
                          const char buf[],
                          struct discord_emojis *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_emoji, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_emoji o = { 0 };
        ret += discord_emoji_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_create_guild_emoji_from_jsmnf(jsmnf *root,
                                      const char buf[],
                                      struct discord_create_guild_emoji *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "image", sizeof("image") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->image, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret +=
            sizeof *this->roles + snowflakes_from_jsmnf(f, buf, this->roles);
    };

    return ret;
}
size_t
discord_modify_guild_emoji_from_jsmnf(jsmnf *root,
                                      const char buf[],
                                      struct discord_modify_guild_emoji *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "image", sizeof("image") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->image, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret +=
            sizeof *this->roles + snowflakes_from_jsmnf(f, buf, this->roles);
    };

    return ret;
}

size_t
discord_guild_from_jsmnf(jsmnf *root,
                         const char buf[],
                         struct discord_guild *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon_hash", sizeof("icon_hash") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon_hash, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "splash", sizeof("splash") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->splash, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "discovery_splash", sizeof("discovery_splash") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->discovery_splash, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "owner", sizeof("owner") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->owner = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "owner_id", sizeof("owner_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->owner_id);

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->permissions, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "afk_channel_id", sizeof("afk_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->afk_channel_id);

    f = jsmnf_find(root, "afk_timeout", sizeof("afk_timeout") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->afk_timeout = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "widget_enabled", sizeof("widget_enabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->widget_enabled = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "widget_channel_id", sizeof("widget_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->widget_channel_id);

    f = jsmnf_find(root, "verification_level",
                   sizeof("verification_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->verification_level = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "default_message_notifications",
                   sizeof("default_message_notifications") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_message_notifications =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "explicit_content_filter",
                   sizeof("explicit_content_filter") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->explicit_content_filter =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret += sizeof *this->roles
               + discord_roles_from_jsmnf(f, buf, this->roles);
    };

    f = jsmnf_find(root, "emojis", sizeof("emojis") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->emojis = calloc(1, sizeof *this->emojis);
        ret += sizeof *this->emojis
               + discord_emojis_from_jsmnf(f, buf, this->emojis);
    };

    f = jsmnf_find(root, "features", sizeof("features") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->features = calloc(1, sizeof *this->features);
        ret += sizeof *this->features
               + strings_from_jsmnf(f, buf, this->features);
    };

    f = jsmnf_find(root, "mfa_level", sizeof("mfa_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mfa_level = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "application_id", sizeof("application_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->application_id);

    f = jsmnf_find(root, "system_channel_id", sizeof("system_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->system_channel_id);

    f = jsmnf_find(root, "system_channel_flags",
                   sizeof("system_channel_flags") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->system_channel_flags =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "rules_channel_id", sizeof("rules_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->rules_channel_id);

    f = jsmnf_find(root, "joined_at", sizeof("joined_at") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->joined_at);

    f = jsmnf_find(root, "large", sizeof("large") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->large = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "unavailable", sizeof("unavailable") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->unavailable = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "member_count", sizeof("member_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->member_count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "voice_states", sizeof("voice_states") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->voice_states = calloc(1, sizeof *this->voice_states);
        ret += sizeof *this->voice_states
               + discord_voice_states_from_jsmnf(f, buf, this->voice_states);
    };

    f = jsmnf_find(root, "members", sizeof("members") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->members = calloc(1, sizeof *this->members);
        ret += sizeof *this->members
               + discord_guild_members_from_jsmnf(f, buf, this->members);
    };

    f = jsmnf_find(root, "channels", sizeof("channels") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->channels = calloc(1, sizeof *this->channels);
        ret += sizeof *this->channels
               + discord_channels_from_jsmnf(f, buf, this->channels);
    };

    f = jsmnf_find(root, "threads", sizeof("threads") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->threads = calloc(1, sizeof *this->threads);
        ret += sizeof *this->threads
               + discord_channels_from_jsmnf(f, buf, this->threads);
    };

    f = jsmnf_find(root, "presences", sizeof("presences") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->presences = calloc(1, sizeof *this->presences);
        ret += sizeof *this->presences
               + discord_presence_updates_from_jsmnf(f, buf, this->presences);
    };

    f = jsmnf_find(root, "max_presences", sizeof("max_presences") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_presences = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "max_members", sizeof("max_members") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_members = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "vanity_url_code", sizeof("vanity_url_code") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->vanity_url_code, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "banner", sizeof("banner") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->banner, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "premium_tier", sizeof("premium_tier") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->premium_tier = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "premium_subscription_count",
                   sizeof("premium_subscription_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->premium_subscription_count =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "preferred_locale", sizeof("preferred_locale") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->preferred_locale, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "public_updates_channel_id",
                   sizeof("public_updates_channel_id") - 1);
    if (f)
        sscanf(buf + f->val->start, "%" SCNu64,
               &this->public_updates_channel_id);

    f = jsmnf_find(root, "max_video_channel_users",
                   sizeof("max_video_channel_users") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_video_channel_users =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "approximate_member_count",
                   sizeof("approximate_member_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->approximate_member_count =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "approximate_presence_count",
                   sizeof("approximate_presence_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->approximate_presence_count =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "welcome_screen", sizeof("welcome_screen") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->welcome_screen = calloc(1, sizeof *this->welcome_screen);
        ret +=
            sizeof *this->welcome_screen
            + discord_welcome_screen_from_jsmnf(f, buf, this->welcome_screen);
    };

    f = jsmnf_find(root, "nsfw_level", sizeof("nsfw_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->nsfw_level = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "stage_instances", sizeof("stage_instances") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->stage_instances = calloc(1, sizeof *this->stage_instances);
        ret += sizeof *this->stage_instances
               + discord_stage_instances_from_jsmnf(f, buf,
                                                    this->stage_instances);
    };

    f = jsmnf_find(root, "stickers", sizeof("stickers") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->stickers = calloc(1, sizeof *this->stickers);
        ret += sizeof *this->stickers
               + discord_stickers_from_jsmnf(f, buf, this->stickers);
    };

    f = jsmnf_find(root, "guild_scheduled_events",
                   sizeof("guild_scheduled_events") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->guild_scheduled_events =
            calloc(1, sizeof *this->guild_scheduled_events);
        ret += sizeof *this->guild_scheduled_events
               + discord_guild_scheduled_events_from_jsmnf(
                   f, buf, this->guild_scheduled_events);
    };

    f = jsmnf_find(root, "premium_progress_bar_enabled",
                   sizeof("premium_progress_bar_enabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->premium_progress_bar_enabled = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_guilds_from_jsmnf(jsmnf *root,
                          const char buf[],
                          struct discord_guilds *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_guild, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_guild o = { 0 };
        ret += discord_guild_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_guild_preview_from_jsmnf(jsmnf *root,
                                 const char buf[],
                                 struct discord_guild_preview *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "splash", sizeof("splash") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->splash, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "discovery_splash", sizeof("discovery_splash") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->discovery_splash, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "emojis", sizeof("emojis") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->emojis = calloc(1, sizeof *this->emojis);
        ret += sizeof *this->emojis
               + discord_emojis_from_jsmnf(f, buf, this->emojis);
    };

    f = jsmnf_find(root, "features", sizeof("features") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->features = calloc(1, sizeof *this->features);
        ret += sizeof *this->features
               + strings_from_jsmnf(f, buf, this->features);
    };

    f = jsmnf_find(root, "approximate_member_count",
                   sizeof("approximate_member_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->approximate_member_count =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "approximate_presence_count",
                   sizeof("approximate_presence_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->approximate_presence_count =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "stickers", sizeof("stickers") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->stickers = calloc(1, sizeof *this->stickers);
        ret += sizeof *this->stickers
               + discord_stickers_from_jsmnf(f, buf, this->stickers);
    };
    return ret;
}
static size_t
discord_guild_widget_setting_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_guild_widget_setting *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "enabled", sizeof("enabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->enabled = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);
    return ret;
}
static size_t
discord_get_guild_widget_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_get_guild_widget *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "instant_invite", sizeof("instant_invite") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->instant_invite, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "channels", sizeof("channels") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->channels = calloc(1, sizeof *this->channels);
        ret += sizeof *this->channels
               + discord_channels_from_jsmnf(f, buf, this->channels);
    };

    f = jsmnf_find(root, "members", sizeof("members") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->members = calloc(1, sizeof *this->members);
        ret += sizeof *this->members
               + discord_users_from_jsmnf(f, buf, this->members);
    };

    f = jsmnf_find(root, "presence_count", sizeof("presence_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->presence_count = (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}
size_t
discord_guild_member_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_guild_member *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    f = jsmnf_find(root, "nick", sizeof("nick") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->nick, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "avatar", sizeof("avatar") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->avatar, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret +=
            sizeof *this->roles + snowflakes_from_jsmnf(f, buf, this->roles);
    };

    f = jsmnf_find(root, "joined_at", sizeof("joined_at") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->joined_at);

    f = jsmnf_find(root, "premium_since", sizeof("premium_since") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->premium_since);

    f = jsmnf_find(root, "deaf", sizeof("deaf") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->deaf = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "muted", sizeof("muted") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->muted = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "pending", sizeof("pending") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->pending = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->permissions, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "communication_disabled_until",
                   sizeof("communication_disabled_until") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->communication_disabled_until);
    return ret;
}
size_t
discord_guild_members_from_jsmnf(jsmnf *root,
                                 const char buf[],
                                 struct discord_guild_members *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_guild_member, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_guild_member o = { 0 };
        ret += discord_guild_member_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_integration_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_integration *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->type, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "enabled", sizeof("enabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->enabled = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "syncing", sizeof("syncing") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->syncing = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "role_id", sizeof("role_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->role_id);

    f = jsmnf_find(root, "enable_emoticons", sizeof("enable_emoticons") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->enable_emoticons = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "expire_behavior", sizeof("expire_behavior") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->expire_behavior = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "expire_grace_period",
                   sizeof("expire_grace_period") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->expire_grace_period = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    f = jsmnf_find(root, "account", sizeof("account") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->account = calloc(1, sizeof *this->account);
        ret += sizeof *this->account
               + discord_integration_account_from_jsmnf(f, buf, this->account);
    };

    f = jsmnf_find(root, "synced_at", sizeof("synced_at") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->synced_at);

    f = jsmnf_find(root, "subscriber_count", sizeof("subscriber_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->subscriber_count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "revoked", sizeof("revoked") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->revoked = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "application", sizeof("application") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->application = calloc(1, sizeof *this->application);
        ret += sizeof *this->application
               + discord_integration_application_from_jsmnf(f, buf,
                                                            this->application);
    };
    return ret;
}
static size_t
discord_integrations_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_integrations *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_integration, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_integration o = { 0 };
        ret += discord_integration_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_integration_account_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_integration_account *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->id, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_integration_application_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_integration_application *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "summary", sizeof("summary") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->summary, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "bot", sizeof("bot") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->bot = calloc(1, sizeof *this->bot);
        ret += sizeof *this->bot + discord_user_from_jsmnf(f, buf, this->bot);
    };

    return ret;
}
size_t
discord_ban_from_jsmnf(jsmnf *root, const char buf[], struct discord_ban *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "reason", sizeof("reason") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->reason, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };
    return ret;
}
size_t
discord_bans_from_jsmnf(jsmnf *root,
                        const char buf[],
                        struct discord_bans *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_ban, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_ban o = { 0 };
        ret += discord_ban_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_welcome_screen_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_welcome_screen *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "welcome_channels", sizeof("welcome_channels") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->welcome_channels = calloc(1, sizeof *this->welcome_channels);
        ret += sizeof *this->welcome_channels
               + discord_welcome_screen_channels_from_jsmnf(
                   f, buf, this->welcome_channels);
    };

    return ret;
}
static size_t
discord_welcome_screen_channel_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_welcome_screen_channel *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "emoji_id", sizeof("emoji_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->emoji_id);

    f = jsmnf_find(root, "emoji_name", sizeof("emoji_name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->emoji_name, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_welcome_screen_channels_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_welcome_screen_channels *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_welcome_screen_channel, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_welcome_screen_channel o = { 0 };
        ret += discord_welcome_screen_channel_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_create_guild_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_create_guild *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "region", sizeof("region") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->region, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "verification_level",
                   sizeof("verification_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->verification_level = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "default_message_notifications",
                   sizeof("default_message_notifications") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_message_notifications =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "explicit_content_filter",
                   sizeof("explicit_content_filter") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->explicit_content_filter =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret += sizeof *this->roles
               + discord_roles_from_jsmnf(f, buf, this->roles);
    };

    f = jsmnf_find(root, "channels", sizeof("channels") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->channels = calloc(1, sizeof *this->channels);
        ret += sizeof *this->channels
               + discord_channels_from_jsmnf(f, buf, this->channels);
    };

    f = jsmnf_find(root, "afk_channel_id", sizeof("afk_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->afk_channel_id);

    f = jsmnf_find(root, "afk_timeout", sizeof("afk_timeout") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->afk_timeout = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "system_channel_id", sizeof("system_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->system_channel_id);

    f = jsmnf_find(root, "system_channel_flags",
                   sizeof("system_channel_flags") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->system_channel_flags =
            (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}
size_t
discord_modify_guild_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_modify_guild *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "verification_level",
                   sizeof("verification_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->verification_level = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "default_message_notifications",
                   sizeof("default_message_notifications") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_message_notifications =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "explicit_content_filter",
                   sizeof("explicit_content_filter") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->explicit_content_filter =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "afk_channel_id", sizeof("afk_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->afk_channel_id);

    f = jsmnf_find(root, "afk_timeout", sizeof("afk_timeout") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->afk_timeout = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "owner_id", sizeof("owner_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->owner_id);

    f = jsmnf_find(root, "splash", sizeof("splash") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->splash, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "discovery_splash", sizeof("discovery_splash") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->discovery_splash, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "banner", sizeof("banner") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->banner, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "system_channel_id", sizeof("system_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->system_channel_id);

    f = jsmnf_find(root, "system_channel_flags",
                   sizeof("system_channel_flags") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->system_channel_flags =
            (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "rules_channel_id", sizeof("rules_channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->rules_channel_id);

    f = jsmnf_find(root, "public_updates_channel_id",
                   sizeof("public_updates_channel_id") - 1);
    if (f)
        sscanf(buf + f->val->start, "%" SCNu64,
               &this->public_updates_channel_id);

    f = jsmnf_find(root, "preferred_locale", sizeof("preferred_locale") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->preferred_locale, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "features", sizeof("features") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->features = calloc(1, sizeof *this->features);
        ret += sizeof *this->features
               + strings_from_jsmnf(f, buf, this->features);
    };

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "premium_progress_bar_enabled",
                   sizeof("premium_progress_bar_enabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->premium_progress_bar_enabled = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_create_guild_channel_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_guild_channel *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "topic", sizeof("topic") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->topic, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "bitrate", sizeof("bitrate") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->bitrate = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "user_limit", sizeof("user_limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->user_limit = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "rate_limit_per_user",
                   sizeof("rate_limit_per_user") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->rate_limit_per_user = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "position", sizeof("position") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->position = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "permission_overwrites",
                   sizeof("permission_overwrites") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->permission_overwrites =
            calloc(1, sizeof *this->permission_overwrites);
        ret += sizeof *this->permission_overwrites
               + discord_overwrites_from_jsmnf(f, buf,
                                               this->permission_overwrites);
    };

    f = jsmnf_find(root, "parent_id", sizeof("parent_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->parent_id);

    f = jsmnf_find(root, "nsfw", sizeof("nsfw") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->nsfw = ('t' == buf[f->val->start]);
    return ret;
}
static size_t
discord_modify_guild_channel_position_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_guild_channel_position *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "position", sizeof("position") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->position = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "lock_category", sizeof("lock_category") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->lock_category = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "parent_id", sizeof("parent_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->parent_id);

    return ret;
}
size_t
discord_modify_guild_channel_positions_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_guild_channel_positions *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_modify_guild_channel_position,
                  , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_modify_guild_channel_position o = { 0 };
        ret += discord_modify_guild_channel_position_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_list_active_guild_threads_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_list_active_guild_threads *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "threads", sizeof("threads") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->threads = calloc(1, sizeof *this->threads);
        ret += sizeof *this->threads
               + discord_channels_from_jsmnf(f, buf, this->threads);
    };

    f = jsmnf_find(root, "members", sizeof("members") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->members = calloc(1, sizeof *this->members);
        ret += sizeof *this->members
               + discord_thread_members_from_jsmnf(f, buf, this->members);
    };
    return ret;
}
static size_t
discord_list_guild_members_from_jsmnf(jsmnf *root,
                                      const char buf[],
                                      struct discord_list_guild_members *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "limit", sizeof("limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->limit = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "after", sizeof("after") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->after);
    return ret;
}
static size_t
discord_search_guild_members_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_search_guild_members *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "query", sizeof("query") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->query, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "limit", sizeof("limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->limit = (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}
size_t
discord_add_guild_member_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_add_guild_member *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "access_token", sizeof("access_token") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->access_token, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "nick", sizeof("nick") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->nick, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret +=
            sizeof *this->roles + snowflakes_from_jsmnf(f, buf, this->roles);
    };

    f = jsmnf_find(root, "mute", sizeof("mute") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mute = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "deaf", sizeof("deaf") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->deaf = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_modify_guild_member_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_guild_member *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "nick", sizeof("nick") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->nick, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret +=
            sizeof *this->roles + snowflakes_from_jsmnf(f, buf, this->roles);
    };

    f = jsmnf_find(root, "mute", sizeof("mute") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mute = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "deaf", sizeof("deaf") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->deaf = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "communication_disabled_until",
                   sizeof("communication_disabled_until") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->communication_disabled_until);

    return ret;
}
size_t
discord_modify_current_member_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_current_member *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "nick", sizeof("nick") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->nick, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_modify_current_user_nick_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_current_user_nick *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "nick", sizeof("nick") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->nick, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_create_guild_ban_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_create_guild_ban *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "delete_message_days",
                   sizeof("delete_message_days") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->delete_message_days = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "reason", sizeof("reason") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->reason, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_create_guild_role_from_jsmnf(jsmnf *root,
                                     const char buf[],
                                     struct discord_create_guild_role *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->permissions);

    f = jsmnf_find(root, "color", sizeof("color") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->color = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "hoist", sizeof("hoist") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->hoist = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "unicode_emoji", sizeof("unicode_emoji") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->unicode_emoji, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "mentionable", sizeof("mentionable") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mentionable = ('t' == buf[f->val->start]);
    return ret;
}
static size_t
discord_modify_guild_role_position_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_guild_role_position *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "position", sizeof("position") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->position = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_modify_guild_role_positions_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_guild_role_positions *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_modify_guild_role_position, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_modify_guild_role_position o = { 0 };
        ret += discord_modify_guild_role_position_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_modify_guild_role_from_jsmnf(jsmnf *root,
                                     const char buf[],
                                     struct discord_modify_guild_role *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->permissions);

    f = jsmnf_find(root, "color", sizeof("color") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->color = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "hoist", sizeof("hoist") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->hoist = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "unicode_emoji", sizeof("unicode_emoji") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->unicode_emoji, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "mentionable", sizeof("mentionable") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mentionable = ('t' == buf[f->val->start]);
    return ret;
}
static size_t
discord_get_guild_prune_count_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_guild_prune_count *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "count", sizeof("count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "include_roles", sizeof("include_roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->include_roles = calloc(1, sizeof *this->include_roles);
        ret += sizeof *this->include_roles
               + snowflakes_from_jsmnf(f, buf, this->include_roles);
    };
    return ret;
}
size_t
discord_begin_guild_prune_from_jsmnf(jsmnf *root,
                                     const char buf[],
                                     struct discord_begin_guild_prune *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "days", sizeof("days") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->days = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "compute_prune_count",
                   sizeof("compute_prune_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->compute_prune_count = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "include_roles", sizeof("include_roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->include_roles = calloc(1, sizeof *this->include_roles);
        ret += sizeof *this->include_roles
               + snowflakes_from_jsmnf(f, buf, this->include_roles);
    };

    f = jsmnf_find(root, "reason", sizeof("reason") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->reason, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
static size_t
discord_get_guild_widget_image_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_guild_widget_image *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "style", sizeof("style") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->style, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_modify_guild_welcome_screen_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_guild_welcome_screen *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "enabled", sizeof("enabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->enabled = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "welcome_channels", sizeof("welcome_channels") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->welcome_channels = calloc(1, sizeof *this->welcome_channels);
        ret += sizeof *this->welcome_channels
               + discord_welcome_screen_channels_from_jsmnf(
                   f, buf, this->welcome_channels);
    };

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_modify_current_user_voice_state_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_current_user_voice_state *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "suppress", sizeof("suppress") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->suppress = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "request_to_speak_timestamp",
                   sizeof("request_to_speak_timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->request_to_speak_timestamp);

    return ret;
}
size_t
discord_modify_user_voice_state_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_user_voice_state *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "suppress", sizeof("suppress") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->suppress = ('t' == buf[f->val->start]);
    return ret;
}

size_t
discord_guild_scheduled_event_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_guild_scheduled_event *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "creator_id", sizeof("creator_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->creator_id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "scheduled_start_time",
                   sizeof("scheduled_start_time") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->scheduled_start_time);

    f = jsmnf_find(root, "scheduled_end_time",
                   sizeof("scheduled_end_time") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->scheduled_end_time);

    f = jsmnf_find(root, "privacy_level", sizeof("privacy_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->privacy_level = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "status", sizeof("status") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->status = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "entity_type", sizeof("entity_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->entity_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "entity_id", sizeof("entity_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->entity_id);

    f = jsmnf_find(root, "entity_metadata", sizeof("entity_metadata") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->entity_metadata = calloc(1, sizeof *this->entity_metadata);
        ret += sizeof *this->entity_metadata
               + discord_guild_scheduled_event_entity_metadata_from_jsmnf(
                   f, buf, this->entity_metadata);
    };

    f = jsmnf_find(root, "creator", sizeof("creator") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->creator = calloc(1, sizeof *this->creator);
        ret += sizeof *this->creator
               + discord_user_from_jsmnf(f, buf, this->creator);
    };

    f = jsmnf_find(root, "user_count", sizeof("user_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->user_count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "image", sizeof("image") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->image, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
size_t
discord_guild_scheduled_events_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_guild_scheduled_events *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_guild_scheduled_event, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_guild_scheduled_event o = { 0 };
        ret += discord_guild_scheduled_event_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_guild_scheduled_event_entity_metadata_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_guild_scheduled_event_entity_metadata *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "location", sizeof("location") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->location, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
static size_t
discord_guild_scheduled_event_user_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_guild_scheduled_event_user *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "guild_scheduled_event_id",
                   sizeof("guild_scheduled_event_id") - 1);
    if (f)
        sscanf(buf + f->val->start, "%" SCNu64,
               &this->guild_scheduled_event_id);

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    f = jsmnf_find(root, "member", sizeof("member") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->member = calloc(1, sizeof *this->member);
        ret += sizeof *this->member
               + discord_guild_member_from_jsmnf(f, buf, this->member);
    };

    return ret;
}
size_t
discord_list_scheduled_events_for_guild_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_list_scheduled_events_for_guild *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "with_user_count", sizeof("with_user_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->with_user_count = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_create_guild_scheduled_event_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_create_guild_scheduled_event *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "entity_metadata", sizeof("entity_metadata") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->entity_metadata = calloc(1, sizeof *this->entity_metadata);
        ret += sizeof *this->entity_metadata
               + discord_guild_scheduled_event_entity_metadata_from_jsmnf(
                   f, buf, this->entity_metadata);
    };

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "scheduled_start_time",
                   sizeof("scheduled_start_time") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->scheduled_start_time);

    f = jsmnf_find(root, "scheduled_end_time",
                   sizeof("scheduled_end_time") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->scheduled_end_time);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "entity_type", sizeof("entity_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->entity_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "image", sizeof("image") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->image, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_get_guild_scheduled_event_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_get_guild_scheduled_event *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "with_user_count", sizeof("with_user_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->with_user_count = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_modify_guild_scheduled_event_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_guild_scheduled_event *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "entity_metadata", sizeof("entity_metadata") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->entity_metadata = calloc(1, sizeof *this->entity_metadata);
        ret += sizeof *this->entity_metadata
               + discord_guild_scheduled_event_entity_metadata_from_jsmnf(
                   f, buf, this->entity_metadata);
    };

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "scheduled_start_time",
                   sizeof("scheduled_start_time") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->scheduled_start_time);

    f = jsmnf_find(root, "scheduled_end_time",
                   sizeof("scheduled_end_time") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->scheduled_end_time);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "entity_type", sizeof("entity_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->entity_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "status", sizeof("status") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->status = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "image", sizeof("image") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->image, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_get_guild_scheduled_event_users_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_get_guild_scheduled_event_users *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "limit", sizeof("limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->limit = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "with_member", sizeof("with_member") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->with_member = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "before", sizeof("before") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->before);

    f = jsmnf_find(root, "after", sizeof("after") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->after);

    return ret;
}
size_t
discord_guild_template_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_guild_template *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "code", sizeof("code") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->code, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "usage_count", sizeof("usage_count") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->usage_count = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "creator_id", sizeof("creator_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->creator_id);

    f = jsmnf_find(root, "creator", sizeof("creator") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->creator = calloc(1, sizeof *this->creator);
        ret += sizeof *this->creator
               + discord_user_from_jsmnf(f, buf, this->creator);
    };

    f = jsmnf_find(root, "created_at", sizeof("created_at") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->created_at);

    f = jsmnf_find(root, "updated_at", sizeof("updated_at") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->updated_at);

    f = jsmnf_find(root, "source_guild_id", sizeof("source_guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->source_guild_id);

    f = jsmnf_find(root, "serialized_source_guild",
                   sizeof("serialized_source_guild") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->serialized_source_guild =
            calloc(1, sizeof *this->serialized_source_guild);
        ret +=
            sizeof *this->serialized_source_guild
            + discord_guild_from_jsmnf(f, buf, this->serialized_source_guild);
    };

    f = jsmnf_find(root, "is_dirty", sizeof("is_dirty") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->is_dirty = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_create_guild_from_guild_template_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_create_guild_from_guild_template *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_create_guild_template_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_guild_template *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_modify_guild_template_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_guild_template *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}

size_t
discord_stage_instance_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_stage_instance *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "topic", sizeof("topic") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->topic, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "privacy_level", sizeof("privacy_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->privacy_level = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "discoverable_disabled",
                   sizeof("discoverable_disabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->discoverable_disabled = ('t' == buf[f->val->start]);
    return ret;
}
static size_t
discord_stage_instances_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_stage_instances *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_stage_instance, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_stage_instance o = { 0 };
        ret += discord_stage_instance_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_create_stage_instance_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_stage_instance *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "topic", sizeof("topic") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->topic, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "privacy_level", sizeof("privacy_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->privacy_level = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_modify_stage_instance_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_stage_instance *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "topic", sizeof("topic") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->topic, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "privacy_level", sizeof("privacy_level") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->privacy_level = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}

size_t
discord_sticker_from_jsmnf(jsmnf *root,
                           const char buf[],
                           struct discord_sticker *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "pack_id", sizeof("pack_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->pack_id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "tags", sizeof("tags") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->tags, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "format_type", sizeof("format_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->format_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "available", sizeof("available") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->available = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    f = jsmnf_find(root, "sort_value", sizeof("sort_value") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->sort_value = (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}
static size_t
discord_stickers_from_jsmnf(jsmnf *root,
                            const char buf[],
                            struct discord_stickers *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_sticker, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_sticker o = { 0 };
        ret += discord_sticker_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_sticker_item_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_sticker_item *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "format_type", sizeof("format_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->format_type = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
static size_t
discord_sticker_items_from_jsmnf(jsmnf *root,
                                 const char buf[],
                                 struct discord_sticker_items *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_sticker_item, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_sticker_item o = { 0 };
        ret += discord_sticker_item_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_sticker_pack_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_sticker_pack *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "stickers", sizeof("stickers") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->stickers = calloc(1, sizeof *this->stickers);
        ret += sizeof *this->stickers
               + discord_stickers_from_jsmnf(f, buf, this->stickers);
    };

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "sku_id", sizeof("sku_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->sku_id);

    f = jsmnf_find(root, "cover_sticker_id", sizeof("cover_sticker_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->cover_sticker_id);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "banner_asset_id", sizeof("banner_asset_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->banner_asset_id);

    return ret;
}
static size_t
discord_create_guild_sticker_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_guild_sticker *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "tags", sizeof("tags") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->tags, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "file", sizeof("file") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->file = calloc(1, sizeof *this->file);
        ret += sizeof *this->file
               + discord_attachment_from_jsmnf(f, buf, this->file);
    };
    return ret;
}
size_t
discord_modify_guild_sticker_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_guild_sticker *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "tags", sizeof("tags") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->tags, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}

size_t
discord_user_from_jsmnf(jsmnf *root,
                        const char buf[],
                        struct discord_user *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "username", sizeof("username") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->username, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "discriminator", sizeof("discriminator") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->discriminator, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "avatar", sizeof("avatar") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->avatar, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "bot", sizeof("bot") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->bot = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "system", sizeof("system") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->System = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "mfa_enabled", sizeof("mfa_enabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mfa_enabled = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "banner", sizeof("banner") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->banner, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "accent_color", sizeof("accent_color") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->accent_color = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "locale", sizeof("locale") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->locale, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "verified", sizeof("verified") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->verified = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "email", sizeof("email") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->email, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->flags);

    f = jsmnf_find(root, "premium_type", sizeof("premium_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->premium_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "public_flags", sizeof("public_flags") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->public_flags);
    return ret;
}
size_t
discord_users_from_jsmnf(jsmnf *root,
                         const char buf[],
                         struct discord_users *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_user, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_user o = { 0 };
        ret += discord_user_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_connection_from_jsmnf(jsmnf *root,
                              const char buf[],
                              struct discord_connection *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->type, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "revoked", sizeof("revoked") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->revoked = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "integrations", sizeof("integrations") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->integrations = calloc(1, sizeof *this->integrations);
        ret += sizeof *this->integrations
               + discord_integrations_from_jsmnf(f, buf, this->integrations);
    };

    f = jsmnf_find(root, "verified", sizeof("verified") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->verified = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "friend_sync", sizeof("friend_sync") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->friend_sync = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "show_activity", sizeof("show_activity") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->show_activity = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "visibility", sizeof("visibility") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->visibility = (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}
size_t
discord_connections_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_connections *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_connection, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_connection o = { 0 };
        ret += discord_connection_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_modify_current_user_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_current_user *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "username", sizeof("username") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->username, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "avatar", sizeof("avatar") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->avatar, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
static size_t
discord_get_current_user_guilds_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_get_current_user_guilds *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "before", sizeof("before") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->before);

    f = jsmnf_find(root, "after", sizeof("after") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->after);

    f = jsmnf_find(root, "limit", sizeof("limit") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->limit = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_create_dm_from_jsmnf(jsmnf *root,
                             const char buf[],
                             struct discord_create_dm *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "recipient_id", sizeof("recipient_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->recipient_id);

    return ret;
}
size_t
discord_create_group_dm_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_create_group_dm *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "access_tokens", sizeof("access_tokens") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->access_tokens = calloc(1, sizeof *this->access_tokens);
        ret += sizeof *this->access_tokens
               + snowflakes_from_jsmnf(f, buf, this->access_tokens);
    };

    f = jsmnf_find(root, "nicks", sizeof("nicks") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->nicks = calloc(1, sizeof *this->nicks);
        ret += sizeof *this->nicks + strings_from_jsmnf(f, buf, this->nicks);
    };

    return ret;
}
size_t
discord_voice_state_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_voice_state *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "user_id", sizeof("user_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->user_id);

    f = jsmnf_find(root, "member", sizeof("member") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->member = calloc(1, sizeof *this->member);
        ret += sizeof *this->member
               + discord_guild_member_from_jsmnf(f, buf, this->member);
    };

    f = jsmnf_find(root, "session_id", sizeof("session_id") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->session_id, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "deaf", sizeof("deaf") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->deaf = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "mute", sizeof("mute") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->mute = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "self_deaf", sizeof("self_deaf") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->self_deaf = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "self_mute", sizeof("self_mute") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->self_mute = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "self_stream", sizeof("self_stream") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->self_stream = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "self_video", sizeof("self_video") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->self_video = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "suppress", sizeof("suppress") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->suppress = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "request_to_speak_timestamp",
                   sizeof("request_to_speak_timestamp") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start,
                               &this->request_to_speak_timestamp);

    return ret;
}
size_t
discord_voice_states_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_voice_states *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_voice_state, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_voice_state o = { 0 };
        ret += discord_voice_state_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_voice_region_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_voice_region *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->id, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "optimal", sizeof("optimal") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->optimal = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "deprecated", sizeof("deprecated") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->deprecated = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "custom", sizeof("custom") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->custom = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_voice_regions_from_jsmnf(jsmnf *root,
                                 const char buf[],
                                 struct discord_voice_regions *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_voice_region, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_voice_region o = { 0 };
        ret += discord_voice_region_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}

size_t
discord_webhook_from_jsmnf(jsmnf *root,
                           const char buf[],
                           struct discord_webhook *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "token", sizeof("token") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->token, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "application_id", sizeof("application_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->application_id);

    f = jsmnf_find(root, "source_channel", sizeof("source_channel") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->source_channel = calloc(1, sizeof *this->source_channel);
        ret += sizeof *this->source_channel
               + discord_channel_from_jsmnf(f, buf, this->source_channel);
    };

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
size_t
discord_webhooks_from_jsmnf(jsmnf *root,
                            const char buf[],
                            struct discord_webhooks *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_webhook, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_webhook o = { 0 };
        ret += discord_webhook_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_create_webhook_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_create_webhook *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "avatar", sizeof("avatar") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->avatar, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_modify_webhook_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_modify_webhook *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "avatar", sizeof("avatar") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->avatar, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);
    return ret;
}
size_t
discord_modify_webhook_with_token_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_modify_webhook_with_token *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "avatar", sizeof("avatar") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->avatar, buf + f->val->start,
                              f->val->end - f->val->start);

    return ret;
}
size_t
discord_execute_webhook_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_execute_webhook *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "wait", sizeof("wait") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->wait = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "thread_id", sizeof("thread_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->thread_id);

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "username", sizeof("username") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->username, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "avatar_url", sizeof("avatar_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->avatar_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "tts", sizeof("tts") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->tts = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "allowed_mentions", sizeof("allowed_mentions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->allowed_mentions = calloc(1, sizeof *this->allowed_mentions);
        ret += sizeof *this->allowed_mentions
               + discord_allowed_mention_from_jsmnf(f, buf,
                                                    this->allowed_mentions);
    };

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->flags);

    return ret;
}
static size_t
discord_get_webhook_message_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_webhook_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "thread_id", sizeof("thread_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->thread_id);

    return ret;
}
size_t
discord_edit_webhook_message_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_edit_webhook_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "thread_id", sizeof("thread_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->thread_id);

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "allowed_mentions", sizeof("allowed_mentions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->allowed_mentions = calloc(1, sizeof *this->allowed_mentions);
        ret += sizeof *this->allowed_mentions
               + discord_allowed_mention_from_jsmnf(f, buf,
                                                    this->allowed_mentions);
    };

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    return ret;
}
static size_t
discord_delete_webhook_message_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_delete_webhook_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "thread_id", sizeof("thread_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->thread_id);

    return ret;
}

size_t
discord_identify_from_jsmnf(jsmnf *root,
                            const char buf[],
                            struct discord_identify *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "token", sizeof("token") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->token, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "properties", sizeof("properties") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->properties = calloc(1, sizeof *this->properties);
        ret +=
            sizeof *this->properties
            + discord_identify_connection_from_jsmnf(f, buf, this->properties);
    };

    f = jsmnf_find(root, "compress", sizeof("compress") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->compress = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "large_threshold", sizeof("large_threshold") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->large_threshold = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "presence", sizeof("presence") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->presence = calloc(1, sizeof *this->presence);
        ret += sizeof *this->presence
               + discord_presence_update_from_jsmnf(f, buf, this->presence);
    };

    f = jsmnf_find(root, "intents", sizeof("intents") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->intents = (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}
static size_t
discord_identify_connection_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_identify_connection *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "$os", sizeof("$os") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->os, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "$browser", sizeof("$browser") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->browser, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "$device", sizeof("$device") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->device, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
size_t
discord_voice_state_status_from_jsmnf(jsmnf *root,
                                      const char buf[],
                                      struct discord_voice_state_status *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "self_mute", sizeof("self_mute") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->self_mute = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "self_deaf", sizeof("self_deaf") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->self_deaf = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_presence_update_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_presence_update *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "since", sizeof("since") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->since);

    f = jsmnf_find(root, "activities", sizeof("activities") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->activities = calloc(1, sizeof *this->activities);
        ret += sizeof *this->activities
               + discord_activities_from_jsmnf(f, buf, this->activities);
    };

    f = jsmnf_find(root, "status", sizeof("status") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->status, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "afk", sizeof("afk") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->afk = ('t' == buf[f->val->start]);
    return ret;
}
static size_t
discord_presence_updates_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_presence_updates *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_presence_update, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_presence_update o = { 0 };
        ret += discord_presence_update_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_activity_from_jsmnf(jsmnf *root,
                            const char buf[],
                            struct discord_activity *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "created_at", sizeof("created_at") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->created_at);

    f = jsmnf_find(root, "timestamps", sizeof("timestamps") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->timestamps = calloc(1, sizeof *this->timestamps);
        ret +=
            sizeof *this->timestamps
            + discord_activity_timestamps_from_jsmnf(f, buf, this->timestamps);
    };

    f = jsmnf_find(root, "application_id", sizeof("application_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->application_id);

    f = jsmnf_find(root, "details", sizeof("details") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->details, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "state", sizeof("state") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->state, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "emoji", sizeof("emoji") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->emoji = calloc(1, sizeof *this->emoji);
        ret += sizeof *this->emoji
               + discord_activity_emoji_from_jsmnf(f, buf, this->emoji);
    };

    f = jsmnf_find(root, "party", sizeof("party") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->party = calloc(1, sizeof *this->party);
        ret += sizeof *this->party
               + discord_activity_party_from_jsmnf(f, buf, this->party);
    };

    f = jsmnf_find(root, "assets", sizeof("assets") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->assets = calloc(1, sizeof *this->assets);
        ret += sizeof *this->assets
               + discord_activity_assets_from_jsmnf(f, buf, this->assets);
    };

    f = jsmnf_find(root, "secrets", sizeof("secrets") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->secrets = calloc(1, sizeof *this->secrets);
        ret += sizeof *this->secrets
               + discord_activity_secrets_from_jsmnf(f, buf, this->secrets);
    };

    f = jsmnf_find(root, "instance", sizeof("instance") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->instance = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->flags);

    f = jsmnf_find(root, "buttons", sizeof("buttons") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->buttons = calloc(1, sizeof *this->buttons);
        ret += sizeof *this->buttons
               + discord_activity_buttons_from_jsmnf(f, buf, this->buttons);
    };
    return ret;
}
static size_t
discord_activities_from_jsmnf(jsmnf *root,
                              const char buf[],
                              struct discord_activities *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_activity, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_activity o = { 0 };
        ret += discord_activity_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_activity_timestamps_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_activity_timestamps *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "start", sizeof("start") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->start);

    f = jsmnf_find(root, "end", sizeof("end") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        cog_iso8601_to_unix_ms(buf + f->val->start,
                               f->val->end - f->val->start, &this->end);
    return ret;
}
static size_t
discord_activity_emoji_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_activity_emoji *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "animated", sizeof("animated") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->animated = ('t' == buf[f->val->start]);
    return ret;
}
static size_t
discord_activity_party_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_activity_party *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->id, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "size", sizeof("size") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->size = calloc(1, sizeof *this->size);
        ret += sizeof *this->size + integers_from_jsmnf(f, buf, this->size);
    };
    return ret;
}
static size_t
discord_activity_assets_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_activity_assets *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "large_image", sizeof("large_image") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->large_image, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "large_text", sizeof("large_text") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->large_text, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "small_image", sizeof("small_image") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->small_image, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "small_text", sizeof("small_text") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->small_text, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_activity_secrets_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_activity_secrets *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "join", sizeof("join") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->join, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "spectate", sizeof("spectate") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->spectate, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "match", sizeof("match") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->match, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_activity_button_from_jsmnf(jsmnf *root,
                                   const char buf[],
                                   struct discord_activity_button *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "label", sizeof("label") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->label, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_activity_buttons_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_activity_buttons *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_activity_button, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_activity_button o = { 0 };
        ret += discord_activity_button_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_session_start_limit_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_session_start_limit *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "total", sizeof("total") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->total = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "remaining", sizeof("remaining") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->remaining = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "reset_after", sizeof("reset_after") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->reset_after = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "max_concurrency", sizeof("max_concurrency") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_concurrency = (int)strtol(buf + f->val->start, NULL, 10);
    return ret;
}

size_t
discord_team_from_jsmnf(jsmnf *root,
                        const char buf[],
                        struct discord_team *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "icon", sizeof("icon") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->icon, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "members", sizeof("members") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->members = calloc(1, sizeof *this->members);
        ret += sizeof *this->members
               + discord_team_members_from_jsmnf(f, buf, this->members);
    };

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "owner_user_id", sizeof("owner_user_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->owner_user_id);
    return ret;
}
static size_t
discord_team_member_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_team_member *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "membership_state", sizeof("membership_state") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->membership_state = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->permissions = calloc(1, sizeof *this->permissions);
        ret += sizeof *this->permissions
               + strings_from_jsmnf(f, buf, this->permissions);
    };

    f = jsmnf_find(root, "team_id", sizeof("team_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->team_id);

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    return ret;
}
static size_t
discord_team_members_from_jsmnf(jsmnf *root,
                                const char buf[],
                                struct discord_team_members *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_team_member, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_team_member o = { 0 };
        ret += discord_team_member_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}

size_t
discord_application_command_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_application_command *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "application_id", sizeof("application_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->application_id);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret += sizeof *this->options
               + discord_application_command_options_from_jsmnf(f, buf,
                                                                this->options);
    };

    f = jsmnf_find(root, "default_permission",
                   sizeof("default_permission") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_permission = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "version", sizeof("version") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->version);
    return ret;
}
size_t
discord_application_commands_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_application_commands *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_application_command, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_application_command o = { 0 };
        ret += discord_application_command_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_application_command_option_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_option *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "required", sizeof("required") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->required = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "choices", sizeof("choices") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->choices = calloc(1, sizeof *this->choices);
        ret += sizeof *this->choices
               + discord_application_command_option_choices_from_jsmnf(
                   f, buf, this->choices);
    };

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret += sizeof *this->options
               + discord_application_command_options_from_jsmnf(f, buf,
                                                                this->options);
    };

    f = jsmnf_find(root, "channel_types", sizeof("channel_types") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->channel_types = calloc(1, sizeof *this->channel_types);
        ret += sizeof *this->channel_types
               + integers_from_jsmnf(f, buf, this->channel_types);
    };

    f = jsmnf_find(root, "min_value", sizeof("min_value") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->min_value, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "max_value", sizeof("max_value") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->max_value, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "autocomplete", sizeof("autocomplete") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->autocomplete = ('t' == buf[f->val->start]);

    return ret;
}
static size_t
discord_application_command_options_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_options *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_application_command_option, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_application_command_option o = { 0 };
        ret += discord_application_command_option_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_application_command_option_choice_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_option_choice *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "value", sizeof("value") - 1);
    if (f) {
        this->value =
            _gc_strndup(buf + f->val->start, f->val->end - f->val->start);
        ret += f->val->end - f->val->start;
    };
    return ret;
}
static size_t
discord_application_command_option_choices_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_option_choices *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems,
                  struct discord_application_command_option_choice, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_application_command_option_choice o = { 0 };
        ret +=
            discord_application_command_option_choice_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_application_command_interaction_data_option_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_interaction_data_option *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "value", sizeof("value") - 1);
    if (f) {
        this->value =
            _gc_strndup(buf + f->val->start, f->val->end - f->val->start);
        ret += f->val->end - f->val->start;
    };

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret +=
            sizeof *this->options
            + discord_application_command_interaction_data_options_from_jsmnf(
                f, buf, this->options);
    };

    f = jsmnf_find(root, "focused", sizeof("focused") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->focused = ('t' == buf[f->val->start]);
    return ret;
}
static size_t
discord_application_command_interaction_data_options_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_interaction_data_options *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems,
                  struct discord_application_command_interaction_data_option,
                  , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_application_command_interaction_data_option o = { 0 };
        ret += discord_application_command_interaction_data_option_from_jsmnf(
            f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_guild_application_command_permission_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_guild_application_command_permission *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "application_id", sizeof("application_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->application_id);

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->permissions = calloc(1, sizeof *this->permissions);
        ret += sizeof *this->permissions
               + discord_application_command_permissions_from_jsmnf(
                   f, buf, this->permissions);
    };
    return ret;
}
size_t
discord_guild_application_command_permissions_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_guild_application_command_permissions *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems,
                  struct discord_guild_application_command_permission, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_guild_application_command_permission o = { 0 };
        ret += discord_guild_application_command_permission_from_jsmnf(f, buf,
                                                                       &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_application_command_permission_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_permission *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "permission", sizeof("permission") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->permission = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_application_command_permissions_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_application_command_permissions *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_application_command_permission,
                  , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_application_command_permission o = { 0 };
        ret += discord_application_command_permission_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
size_t
discord_create_global_application_command_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_create_global_application_command *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret += sizeof *this->options
               + discord_application_command_options_from_jsmnf(f, buf,
                                                                this->options);
    };

    f = jsmnf_find(root, "default_permission",
                   sizeof("default_permission") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_permission = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_edit_global_application_command_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_edit_global_application_command *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret += sizeof *this->options
               + discord_application_command_options_from_jsmnf(f, buf,
                                                                this->options);
    };

    f = jsmnf_find(root, "default_permission",
                   sizeof("default_permission") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_permission = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_create_guild_application_command_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_create_guild_application_command *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret += sizeof *this->options
               + discord_application_command_options_from_jsmnf(f, buf,
                                                                this->options);
    };

    f = jsmnf_find(root, "default_permission",
                   sizeof("default_permission") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_permission = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    return ret;
}
size_t
discord_edit_guild_application_command_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_edit_guild_application_command *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret += sizeof *this->options
               + discord_application_command_options_from_jsmnf(f, buf,
                                                                this->options);
    };

    f = jsmnf_find(root, "default_permission",
                   sizeof("default_permission") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->default_permission = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_edit_application_command_permissions_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_edit_application_command_permissions *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "permissions", sizeof("permissions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->permissions = calloc(1, sizeof *this->permissions);
        ret += sizeof *this->permissions
               + discord_application_command_permissions_from_jsmnf(
                   f, buf, this->permissions);
    };

    return ret;
}

size_t
discord_component_from_jsmnf(jsmnf *root,
                             const char buf[],
                             struct discord_component *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "custom_id", sizeof("custom_id") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->custom_id, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "disabled", sizeof("disabled") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->disabled = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "style", sizeof("style") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->style = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "label", sizeof("label") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->label, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "emoji", sizeof("emoji") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->emoji = calloc(1, sizeof *this->emoji);
        ret += sizeof *this->emoji
               + discord_emoji_from_jsmnf(f, buf, this->emoji);
    };

    f = jsmnf_find(root, "url", sizeof("url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret += sizeof *this->options
               + discord_select_options_from_jsmnf(f, buf, this->options);
    };

    f = jsmnf_find(root, "placeholder", sizeof("placeholder") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->placeholder, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "min_values", sizeof("min_values") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->min_values = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "max_values", sizeof("max_values") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_values = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "min_length", sizeof("min_length") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->min_length = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "max_length", sizeof("max_length") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->max_length = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "required", sizeof("required") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->required = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "value", sizeof("value") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->value, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
size_t
discord_components_from_jsmnf(jsmnf *root,
                              const char buf[],
                              struct discord_components *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_component, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_component o = { 0 };
        ret += discord_component_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}
static size_t
discord_select_option_from_jsmnf(jsmnf *root,
                                 const char buf[],
                                 struct discord_select_option *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "label", sizeof("label") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->label, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "value", sizeof("value") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->value, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "description", sizeof("description") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->description, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "emoji", sizeof("emoji") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->emoji = calloc(1, sizeof *this->emoji);
        ret += sizeof *this->emoji
               + discord_emoji_from_jsmnf(f, buf, this->emoji);
    };

    f = jsmnf_find(root, "default", sizeof("default") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->Default = ('t' == buf[f->val->start]);
    return ret;
}
size_t
discord_select_options_from_jsmnf(jsmnf *root,
                                  const char buf[],
                                  struct discord_select_options *this)
{
    jsmnf *f, *tmp;
    size_t ret, nelems = HASH_COUNT(root->child);
    if (!nelems) return 0;
    ret = sizeof *this * nelems;
    __carray_init(this, nelems, struct discord_select_option, , );
    HASH_ITER(hh, root->child, f, tmp)
    {
        struct discord_select_option o = { 0 };
        ret += discord_select_option_from_jsmnf(f, buf, &o);
        carray_insert(this, f->idx, o);
    }
    return ret;
}

size_t
discord_interaction_from_jsmnf(jsmnf *root,
                               const char buf[],
                               struct discord_interaction *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "application_id", sizeof("application_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->application_id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "data", sizeof("data") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->data = calloc(1, sizeof *this->data);
        ret += sizeof *this->data
               + discord_interaction_data_from_jsmnf(f, buf, this->data);
    };

    f = jsmnf_find(root, "guild_id", sizeof("guild_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->guild_id);

    f = jsmnf_find(root, "channel_id", sizeof("channel_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->channel_id);

    f = jsmnf_find(root, "member", sizeof("member") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->member = calloc(1, sizeof *this->member);
        ret += sizeof *this->member
               + discord_guild_member_from_jsmnf(f, buf, this->member);
    };

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    f = jsmnf_find(root, "token", sizeof("token") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->token, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "version", sizeof("version") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->version = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "message", sizeof("message") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->message = calloc(1, sizeof *this->message);
        ret += sizeof *this->message
               + discord_message_from_jsmnf(f, buf, this->message);
    };

    f = jsmnf_find(root, "locale", sizeof("locale") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->locale, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "guild_locale", sizeof("guild_locale") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->guild_locale, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
static size_t
discord_interaction_data_from_jsmnf(jsmnf *root,
                                    const char buf[],
                                    struct discord_interaction_data *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "resolved", sizeof("resolved") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->resolved = calloc(1, sizeof *this->resolved);
        ret += sizeof *this->resolved
               + discord_resolved_data_from_jsmnf(f, buf, this->resolved);
    };

    f = jsmnf_find(root, "options", sizeof("options") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->options = calloc(1, sizeof *this->options);
        ret +=
            sizeof *this->options
            + discord_application_command_interaction_data_options_from_jsmnf(
                f, buf, this->options);
    };

    f = jsmnf_find(root, "custom_id", sizeof("custom_id") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->custom_id, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "component_type", sizeof("component_type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->component_type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "values", sizeof("values") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->values = calloc(1, sizeof *this->values);
        ret += sizeof *this->values + strings_from_jsmnf(f, buf, this->values);
    };

    f = jsmnf_find(root, "target_id", sizeof("target_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->target_id);

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };
    return ret;
}
static size_t
discord_resolved_data_from_jsmnf(jsmnf *root,
                                 const char buf[],
                                 struct discord_resolved_data *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "users", sizeof("users") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->users = calloc(1, sizeof *this->users);
        ret +=
            sizeof *this->users + snowflakes_from_jsmnf(f, buf, this->users);
    };

    f = jsmnf_find(root, "members", sizeof("members") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->members = calloc(1, sizeof *this->members);
        ret += sizeof *this->members
               + snowflakes_from_jsmnf(f, buf, this->members);
    };

    f = jsmnf_find(root, "roles", sizeof("roles") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->roles = calloc(1, sizeof *this->roles);
        ret +=
            sizeof *this->roles + snowflakes_from_jsmnf(f, buf, this->roles);
    };

    f = jsmnf_find(root, "channels", sizeof("channels") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->channels = calloc(1, sizeof *this->channels);
        ret += sizeof *this->channels
               + snowflakes_from_jsmnf(f, buf, this->channels);
    };

    f = jsmnf_find(root, "messages", sizeof("messages") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->messages = calloc(1, sizeof *this->messages);
        ret += sizeof *this->messages
               + snowflakes_from_jsmnf(f, buf, this->messages);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + snowflakes_from_jsmnf(f, buf, this->attachments);
    };
    return ret;
}
static size_t
discord_message_interaction_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_message_interaction *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "id", sizeof("id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->id);

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "name", sizeof("name") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->name, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "user", sizeof("user") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->user = calloc(1, sizeof *this->user);
        ret +=
            sizeof *this->user + discord_user_from_jsmnf(f, buf, this->user);
    };

    f = jsmnf_find(root, "member", sizeof("member") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->member = calloc(1, sizeof *this->member);
        ret += sizeof *this->member
               + discord_guild_member_from_jsmnf(f, buf, this->member);
    };
    return ret;
}
size_t
discord_interaction_response_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_interaction_response *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "type", sizeof("type") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->type = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "data", sizeof("data") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->data = calloc(1, sizeof *this->data);
        ret +=
            sizeof *this->data
            + discord_interaction_callback_data_from_jsmnf(f, buf, this->data);
    };

    return ret;
}
static size_t
discord_interaction_callback_data_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_interaction_callback_data *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "tts", sizeof("tts") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->tts = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->flags = (int)strtol(buf + f->val->start, NULL, 10);

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    f = jsmnf_find(root, "choices", sizeof("choices") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->choices = calloc(1, sizeof *this->choices);
        ret += sizeof *this->choices
               + discord_application_command_option_choices_from_jsmnf(
                   f, buf, this->choices);
    };

    f = jsmnf_find(root, "custom_id", sizeof("custom_id") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->custom_id, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "title", sizeof("title") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->title, buf + f->val->start,
                              f->val->end - f->val->start);
    return ret;
}
size_t
discord_edit_original_interaction_response_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_edit_original_interaction_response *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "thread_id", sizeof("thread_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->thread_id);

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "allowed_mentions", sizeof("allowed_mentions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->allowed_mentions = calloc(1, sizeof *this->allowed_mentions);
        ret += sizeof *this->allowed_mentions
               + discord_allowed_mention_from_jsmnf(f, buf,
                                                    this->allowed_mentions);
    };

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    return ret;
}
size_t
discord_create_followup_message_from_jsmnf(
    jsmnf *root,
    const char buf[],
    struct discord_create_followup_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "wait", sizeof("wait") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->wait = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "thread_id", sizeof("thread_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->thread_id);

    f = jsmnf_find(root, "avatar_url", sizeof("avatar_url") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->avatar_url, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "tts", sizeof("tts") - 1);
    if (f && f->val->type == JSMN_PRIMITIVE)
        this->tts = ('t' == buf[f->val->start]);

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "allowed_mentions", sizeof("allowed_mentions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->allowed_mentions = calloc(1, sizeof *this->allowed_mentions);
        ret += sizeof *this->allowed_mentions
               + discord_allowed_mention_from_jsmnf(f, buf,
                                                    this->allowed_mentions);
    };

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    f = jsmnf_find(root, "flags", sizeof("flags") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->flags);

    return ret;
}
size_t
discord_edit_followup_message_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_edit_followup_message *this)
{
    jsmnf *f;
    size_t ret = 0;

    f = jsmnf_find(root, "thread_id", sizeof("thread_id") - 1);
    if (f) sscanf(buf + f->val->start, "%" SCNu64, &this->thread_id);

    f = jsmnf_find(root, "content", sizeof("content") - 1);
    if (f && f->val->type == JSMN_STRING)
        ret += jsmnf_unescape(&this->content, buf + f->val->start,
                              f->val->end - f->val->start);

    f = jsmnf_find(root, "embeds", sizeof("embeds") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->embeds = calloc(1, sizeof *this->embeds);
        ret += sizeof *this->embeds
               + discord_embeds_from_jsmnf(f, buf, this->embeds);
    };

    f = jsmnf_find(root, "allowed_mentions", sizeof("allowed_mentions") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->allowed_mentions = calloc(1, sizeof *this->allowed_mentions);
        ret += sizeof *this->allowed_mentions
               + discord_allowed_mention_from_jsmnf(f, buf,
                                                    this->allowed_mentions);
    };

    f = jsmnf_find(root, "components", sizeof("components") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->components = calloc(1, sizeof *this->components);
        ret += sizeof *this->components
               + discord_components_from_jsmnf(f, buf, this->components);
    };

    f = jsmnf_find(root, "attachments", sizeof("attachments") - 1);
    if (f && (f->val->type == JSMN_OBJECT || f->val->type == JSMN_ARRAY)) {
        this->attachments = calloc(1, sizeof *this->attachments);
        ret += sizeof *this->attachments
               + discord_attachments_from_jsmnf(f, buf, this->attachments);
    };

    return ret;
}
size_t
strings_from_json(const char buf[], size_t size, struct strings *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = strings_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
json_values_from_json(const char buf[], size_t size, struct json_values *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = json_values_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
snowflakes_from_json(const char buf[], size_t size, struct snowflakes *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = snowflakes_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
integers_from_json(const char buf[], size_t size, struct integers *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = integers_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_role_from_json(const char buf[],
                       size_t size,
                       struct discord_role *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_role_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_roles_from_json(const char buf[],
                        size_t size,
                        struct discord_roles *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_roles_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_application_from_json(const char buf[],
                              size_t size,
                              struct discord_application *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_application_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_audit_log_from_json(const char buf[],
                            size_t size,
                            struct discord_audit_log *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_audit_log_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_invite_from_json(const char buf[],
                         size_t size,
                         struct discord_invite *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_invite_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_invites_from_json(const char buf[],
                          size_t size,
                          struct discord_invites *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_invites_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_get_invite_from_json(const char buf[],
                             size_t size,
                             struct discord_get_invite *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_get_invite_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_channel_from_json(const char buf[],
                          size_t size,
                          struct discord_channel *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_channel_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_channels_from_json(const char buf[],
                           size_t size,
                           struct discord_channels *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_channels_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_message_from_json(const char buf[],
                          size_t size,
                          struct discord_message *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_message_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_messages_from_json(const char buf[],
                           size_t size,
                           struct discord_messages *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_messages_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_followed_channel_from_json(const char buf[],
                                   size_t size,
                                   struct discord_followed_channel *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_followed_channel_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_thread_members_from_json(const char buf[],
                                 size_t size,
                                 struct discord_thread_members *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_thread_members_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_attachments_from_json(const char buf[],
                              size_t size,
                              struct discord_attachments *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_attachments_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_from_json(const char buf[],
                        size_t size,
                        struct discord_embed *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embeds_from_json(const char buf[],
                         size_t size,
                         struct discord_embeds *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embeds_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_thumbnail_from_json(const char buf[],
                                  size_t size,
                                  struct discord_embed_thumbnail *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_thumbnail_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_video_from_json(const char buf[],
                              size_t size,
                              struct discord_embed_video *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_video_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_image_from_json(const char buf[],
                              size_t size,
                              struct discord_embed_image *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_image_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_provider_from_json(const char buf[],
                                 size_t size,
                                 struct discord_embed_provider *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_provider_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_author_from_json(const char buf[],
                               size_t size,
                               struct discord_embed_author *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_author_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_footer_from_json(const char buf[],
                               size_t size,
                               struct discord_embed_footer *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_footer_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_field_from_json(const char buf[],
                              size_t size,
                              struct discord_embed_field *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_field_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_embed_fields_from_json(const char buf[],
                               size_t size,
                               struct discord_embed_fields *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_embed_fields_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_thread_response_body_from_json(
    const char buf[], size_t size, struct discord_thread_response_body *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_thread_response_body_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_channel_from_json(const char buf[],
                                 size_t size,
                                 struct discord_modify_channel *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_modify_channel_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_get_channel_messages_from_json(
    const char buf[], size_t size, struct discord_get_channel_messages *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_get_channel_messages_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_message_from_json(const char buf[],
                                 size_t size,
                                 struct discord_create_message *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_create_message_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_get_reactions_from_json(const char buf[],
                                size_t size,
                                struct discord_get_reactions *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_get_reactions_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_edit_message_from_json(const char buf[],
                               size_t size,
                               struct discord_edit_message *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_edit_message_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_bulk_delete_messages_from_json(
    const char buf[], size_t size, struct discord_bulk_delete_messages *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_bulk_delete_messages_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_edit_channel_permissions_from_json(
    const char buf[],
    size_t size,
    struct discord_edit_channel_permissions *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_edit_channel_permissions_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_channel_invite_from_json(
    const char buf[], size_t size, struct discord_create_channel_invite *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_channel_invite_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_follow_news_channel_from_json(const char buf[],
                                      size_t size,
                                      struct discord_follow_news_channel *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_follow_news_channel_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_group_dm_add_recipient_from_json(
    const char buf[], size_t size, struct discord_group_dm_add_recipient *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_group_dm_add_recipient_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_start_thread_with_message_from_json(
    const char buf[],
    size_t size,
    struct discord_start_thread_with_message *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_start_thread_with_message_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_start_thread_without_message_from_json(
    const char buf[],
    size_t size,
    struct discord_start_thread_without_message *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_start_thread_without_message_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_list_active_threads_from_json(const char buf[],
                                      size_t size,
                                      struct discord_list_active_threads *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_list_active_threads_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_emoji_from_json(const char buf[],
                        size_t size,
                        struct discord_emoji *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_emoji_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_emojis_from_json(const char buf[],
                         size_t size,
                         struct discord_emojis *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_emojis_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_emoji_from_json(const char buf[],
                                     size_t size,
                                     struct discord_create_guild_emoji *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_create_guild_emoji_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_emoji_from_json(const char buf[],
                                     size_t size,
                                     struct discord_modify_guild_emoji *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_modify_guild_emoji_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guild_from_json(const char buf[],
                        size_t size,
                        struct discord_guild *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_guild_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guilds_from_json(const char buf[],
                         size_t size,
                         struct discord_guilds *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_guilds_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guild_preview_from_json(const char buf[],
                                size_t size,
                                struct discord_guild_preview *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_guild_preview_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guild_member_from_json(const char buf[],
                               size_t size,
                               struct discord_guild_member *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_guild_member_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guild_members_from_json(const char buf[],
                                size_t size,
                                struct discord_guild_members *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_guild_members_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_ban_from_json(const char buf[], size_t size, struct discord_ban *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_ban_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_bans_from_json(const char buf[],
                       size_t size,
                       struct discord_bans *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_bans_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_welcome_screen_from_json(const char buf[],
                                 size_t size,
                                 struct discord_welcome_screen *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_welcome_screen_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_from_json(const char buf[],
                               size_t size,
                               struct discord_create_guild *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_create_guild_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_from_json(const char buf[],
                               size_t size,
                               struct discord_modify_guild *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_modify_guild_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_channel_from_json(
    const char buf[], size_t size, struct discord_create_guild_channel *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_guild_channel_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_channel_positions_from_json(
    const char buf[],
    size_t size,
    struct discord_modify_guild_channel_positions *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret =
            discord_modify_guild_channel_positions_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_list_active_guild_threads_from_json(
    const char buf[],
    size_t size,
    struct discord_list_active_guild_threads *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_list_active_guild_threads_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_add_guild_member_from_json(const char buf[],
                                   size_t size,
                                   struct discord_add_guild_member *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_add_guild_member_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_member_from_json(const char buf[],
                                      size_t size,
                                      struct discord_modify_guild_member *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_guild_member_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_current_member_from_json(
    const char buf[], size_t size, struct discord_modify_current_member *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_current_member_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_current_user_nick_from_json(
    const char buf[],
    size_t size,
    struct discord_modify_current_user_nick *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_current_user_nick_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_ban_from_json(const char buf[],
                                   size_t size,
                                   struct discord_create_guild_ban *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_create_guild_ban_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_role_from_json(const char buf[],
                                    size_t size,
                                    struct discord_create_guild_role *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_create_guild_role_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_role_positions_from_json(
    const char buf[],
    size_t size,
    struct discord_modify_guild_role_positions *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_guild_role_positions_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_role_from_json(const char buf[],
                                    size_t size,
                                    struct discord_modify_guild_role *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_modify_guild_role_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_begin_guild_prune_from_json(const char buf[],
                                    size_t size,
                                    struct discord_begin_guild_prune *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_begin_guild_prune_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_welcome_screen_from_json(
    const char buf[],
    size_t size,
    struct discord_modify_guild_welcome_screen *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_guild_welcome_screen_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_current_user_voice_state_from_json(
    const char buf[],
    size_t size,
    struct discord_modify_current_user_voice_state *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_current_user_voice_state_from_jsmnf(root, buf,
                                                                 this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_user_voice_state_from_json(
    const char buf[],
    size_t size,
    struct discord_modify_user_voice_state *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_user_voice_state_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guild_scheduled_event_from_json(
    const char buf[], size_t size, struct discord_guild_scheduled_event *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_guild_scheduled_event_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guild_scheduled_events_from_json(
    const char buf[], size_t size, struct discord_guild_scheduled_events *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_guild_scheduled_events_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_list_scheduled_events_for_guild_from_json(
    const char buf[],
    size_t size,
    struct discord_list_scheduled_events_for_guild *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_list_scheduled_events_for_guild_from_jsmnf(root, buf,
                                                                 this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_scheduled_event_from_json(
    const char buf[],
    size_t size,
    struct discord_create_guild_scheduled_event *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_guild_scheduled_event_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_get_guild_scheduled_event_from_json(
    const char buf[],
    size_t size,
    struct discord_get_guild_scheduled_event *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_get_guild_scheduled_event_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_scheduled_event_from_json(
    const char buf[],
    size_t size,
    struct discord_modify_guild_scheduled_event *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_guild_scheduled_event_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_get_guild_scheduled_event_users_from_json(
    const char buf[],
    size_t size,
    struct discord_get_guild_scheduled_event_users *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_get_guild_scheduled_event_users_from_jsmnf(root, buf,
                                                                 this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guild_template_from_json(const char buf[],
                                 size_t size,
                                 struct discord_guild_template *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_guild_template_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_from_guild_template_from_json(
    const char buf[],
    size_t size,
    struct discord_create_guild_from_guild_template *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_guild_from_guild_template_from_jsmnf(root, buf,
                                                                  this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_template_from_json(
    const char buf[], size_t size, struct discord_create_guild_template *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_guild_template_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_template_from_json(
    const char buf[], size_t size, struct discord_modify_guild_template *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_guild_template_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_stage_instance_from_json(const char buf[],
                                 size_t size,
                                 struct discord_stage_instance *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_stage_instance_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_stage_instance_from_json(
    const char buf[], size_t size, struct discord_create_stage_instance *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_stage_instance_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_stage_instance_from_json(
    const char buf[], size_t size, struct discord_modify_stage_instance *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_stage_instance_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_sticker_from_json(const char buf[],
                          size_t size,
                          struct discord_sticker *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_sticker_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_guild_sticker_from_json(
    const char buf[], size_t size, struct discord_modify_guild_sticker *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_guild_sticker_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_user_from_json(const char buf[],
                       size_t size,
                       struct discord_user *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_user_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_users_from_json(const char buf[],
                        size_t size,
                        struct discord_users *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_users_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_connections_from_json(const char buf[],
                              size_t size,
                              struct discord_connections *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_connections_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_current_user_from_json(const char buf[],
                                      size_t size,
                                      struct discord_modify_current_user *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_current_user_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_dm_from_json(const char buf[],
                            size_t size,
                            struct discord_create_dm *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_create_dm_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_group_dm_from_json(const char buf[],
                                  size_t size,
                                  struct discord_create_group_dm *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_create_group_dm_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_voice_state_from_json(const char buf[],
                              size_t size,
                              struct discord_voice_state *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_voice_state_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_voice_states_from_json(const char buf[],
                               size_t size,
                               struct discord_voice_states *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_voice_states_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_voice_regions_from_json(const char buf[],
                                size_t size,
                                struct discord_voice_regions *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_voice_regions_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_webhook_from_json(const char buf[],
                          size_t size,
                          struct discord_webhook *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_webhook_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_webhooks_from_json(const char buf[],
                           size_t size,
                           struct discord_webhooks *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_webhooks_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_webhook_from_json(const char buf[],
                                 size_t size,
                                 struct discord_create_webhook *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_create_webhook_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_webhook_from_json(const char buf[],
                                 size_t size,
                                 struct discord_modify_webhook *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_modify_webhook_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_modify_webhook_with_token_from_json(
    const char buf[],
    size_t size,
    struct discord_modify_webhook_with_token *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_modify_webhook_with_token_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_execute_webhook_from_json(const char buf[],
                                  size_t size,
                                  struct discord_execute_webhook *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_execute_webhook_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_edit_webhook_message_from_json(
    const char buf[], size_t size, struct discord_edit_webhook_message *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_edit_webhook_message_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_identify_from_json(const char buf[],
                           size_t size,
                           struct discord_identify *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_identify_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_voice_state_status_from_json(const char buf[],
                                     size_t size,
                                     struct discord_voice_state_status *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_voice_state_status_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_presence_update_from_json(const char buf[],
                                  size_t size,
                                  struct discord_presence_update *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_presence_update_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_session_start_limit_from_json(const char buf[],
                                      size_t size,
                                      struct discord_session_start_limit *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_session_start_limit_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_team_from_json(const char buf[],
                       size_t size,
                       struct discord_team *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_team_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_application_command_from_json(const char buf[],
                                      size_t size,
                                      struct discord_application_command *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_application_command_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_application_commands_from_json(
    const char buf[], size_t size, struct discord_application_commands *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_application_commands_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_guild_application_command_permissions_from_json(
    const char buf[],
    size_t size,
    struct discord_guild_application_command_permissions *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_guild_application_command_permissions_from_jsmnf(
            root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_application_command_permission_from_json(
    const char buf[],
    size_t size,
    struct discord_application_command_permission *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret =
            discord_application_command_permission_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_application_command_permissions_from_json(
    const char buf[],
    size_t size,
    struct discord_application_command_permissions *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_application_command_permissions_from_jsmnf(root, buf,
                                                                 this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_global_application_command_from_json(
    const char buf[],
    size_t size,
    struct discord_create_global_application_command *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_global_application_command_from_jsmnf(root, buf,
                                                                   this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_edit_global_application_command_from_json(
    const char buf[],
    size_t size,
    struct discord_edit_global_application_command *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_edit_global_application_command_from_jsmnf(root, buf,
                                                                 this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_guild_application_command_from_json(
    const char buf[],
    size_t size,
    struct discord_create_guild_application_command *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_guild_application_command_from_jsmnf(root, buf,
                                                                  this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_edit_guild_application_command_from_json(
    const char buf[],
    size_t size,
    struct discord_edit_guild_application_command *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret =
            discord_edit_guild_application_command_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_edit_application_command_permissions_from_json(
    const char buf[],
    size_t size,
    struct discord_edit_application_command_permissions *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_edit_application_command_permissions_from_jsmnf(
            root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_component_from_json(const char buf[],
                            size_t size,
                            struct discord_component *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_component_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_components_from_json(const char buf[],
                             size_t size,
                             struct discord_components *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_components_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_select_options_from_json(const char buf[],
                                 size_t size,
                                 struct discord_select_options *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_select_options_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_interaction_from_json(const char buf[],
                              size_t size,
                              struct discord_interaction *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0) ret = discord_interaction_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_interaction_response_from_json(
    const char buf[], size_t size, struct discord_interaction_response *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_interaction_response_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_edit_original_interaction_response_from_json(
    const char buf[],
    size_t size,
    struct discord_edit_original_interaction_response *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_edit_original_interaction_response_from_jsmnf(root, buf,
                                                                    this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_create_followup_message_from_json(
    const char buf[],
    size_t size,
    struct discord_create_followup_message *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_create_followup_message_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

size_t
discord_edit_followup_message_from_json(
    const char buf[], size_t size, struct discord_edit_followup_message *this)
{
    jsmnf *root = jsmnf_init();
    int ret = jsmnf_start(root, buf, size);
    if (ret >= 0)
        ret = discord_edit_followup_message_from_jsmnf(root, buf, this);
    jsmnf_cleanup(root);
    return ret;
}

jsonbcode
strings_to_jsonb(jsonb *b, char buf[], size_t size, const struct strings *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i) {
            if (0 > (code = jsonb_string(
                         b, buf, size, this->array[i],
                         this->array[i] ? strlen(this->array[i]) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
json_values_to_jsonb(jsonb *b,
                     char buf[],
                     size_t size,
                     const struct json_values *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i) {
            if (0 > (code = jsonb_token(b, buf, size, this->array[i],
                                        strlen(this->array[i]))))
                return code;
        }
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
snowflakes_to_jsonb(jsonb *b,
                    char buf[],
                    size_t size,
                    const struct snowflakes *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i) {
            {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "%" PRIu64, this->array[i]);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
integers_to_jsonb(jsonb *b,
                  char buf[],
                  size_t size,
                  const struct integers *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i) {
            if (0 > (code = jsonb_number(b, buf, size, this->array[i])))
                return code;
        }
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_role_to_jsonb(jsonb *b,
                      char buf[],
                      size_t size,
                      const struct discord_role *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "color", sizeof("color") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->color))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "hoist", sizeof("hoist") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->hoist))) return code;

        if (this->icon != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                         this->icon ? strlen(this->icon) : 0)))
                return code;
        }

        if (this->unicode_emoji != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "unicode_emoji",
                                      sizeof("unicode_emoji") - 1)))
                return code;
            if (0
                > (code = jsonb_string(
                       b, buf, size, this->unicode_emoji,
                       this->unicode_emoji ? strlen(this->unicode_emoji) : 0)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "position",
                                  sizeof("position") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->position)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                  sizeof("permissions") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->permissions,
                     this->permissions ? strlen(this->permissions) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "managed",
                                  sizeof("managed") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->managed))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "mentionable",
                                  sizeof("mentionable") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->mentionable)))
            return code;

        if (this->tags != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "tags", sizeof("tags") - 1)))
                return code;
            if (0
                > (code = discord_role_tag_to_jsonb(b, buf, size, this->tags)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_roles_to_jsonb(jsonb *b,
                       char buf[],
                       size_t size,
                       const struct discord_roles *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code =
                         discord_role_to_jsonb(b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_role_tag_to_jsonb(jsonb *b,
                          char buf[],
                          size_t size,
                          const struct discord_role_tag *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->bot_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "bot_id",
                                      sizeof("bot_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->bot_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->integration_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "integration_id",
                                      sizeof("integration_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->integration_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "premium_subscribe",
                                  sizeof("premium_subscribe") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->premium_subscribe)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_application_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_application *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->rpc_origins != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "rpc_origins",
                                      sizeof("rpc_origins") - 1)))
                return code;
            if (0 > (code = strings_to_jsonb(b, buf, size, this->rpc_origins)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "bot_public",
                                  sizeof("bot_public") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->bot_public)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "bot_require_code_grant",
                                  sizeof("bot_require_code_grant") - 1)))
            return code;
        if (0
            > (code = jsonb_bool(b, buf, size, this->bot_require_code_grant)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "terms_of_service_url",
                                  sizeof("terms_of_service_url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->terms_of_service_url,
                                     this->terms_of_service_url
                                         ? strlen(this->terms_of_service_url)
                                         : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "privacy_policy_url",
                                  sizeof("privacy_policy_url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->privacy_policy_url,
                                     this->privacy_policy_url
                                         ? strlen(this->privacy_policy_url)
                                         : 0)))
            return code;

        if (this->owner != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "owner",
                                      sizeof("owner") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size, this->owner)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "summary",
                                  sizeof("summary") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->summary,
                                   this->summary ? strlen(this->summary) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "verify_key",
                                  sizeof("verify_key") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->verify_key,
                     this->verify_key ? strlen(this->verify_key) : 0)))
            return code;

        if (this->team != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "team", sizeof("team") - 1)))
                return code;
            if (0 > (code = discord_team_to_jsonb(b, buf, size, this->team)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "primary_sku_id",
                                  sizeof("primary_sku_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->primary_sku_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "slug", sizeof("slug") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->slug,
                                     this->slug ? strlen(this->slug) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "cover_image",
                                  sizeof("cover_image") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->cover_image,
                     this->cover_image ? strlen(this->cover_image) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "flags", sizeof("flags") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->flags);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_audit_log_to_jsonb(jsonb *b,
                           char buf[],
                           size_t size,
                           const struct discord_audit_log *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->audit_log_entries != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "audit_log_entries",
                                      sizeof("audit_log_entries") - 1)))
                return code;
            if (0 > (code = discord_audit_log_entries_to_jsonb(
                         b, buf, size, this->audit_log_entries)))
                return code;
        }

        if (this->guild_scheduled_events != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "guild_scheduled_events",
                                      sizeof("guild_scheduled_events") - 1)))
                return code;
            if (0 > (code = discord_guild_scheduled_events_to_jsonb(
                         b, buf, size, this->guild_scheduled_events)))
                return code;
        }

        if (this->integrations != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "integrations",
                                      sizeof("integrations") - 1)))
                return code;
            if (0 > (code = discord_integrations_to_jsonb(b, buf, size,
                                                          this->integrations)))
                return code;
        }

        if (this->threads != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "threads",
                                      sizeof("threads") - 1)))
                return code;
            if (0 > (code = discord_channels_to_jsonb(b, buf, size,
                                                      this->threads)))
                return code;
        }

        if (this->users != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "users",
                                      sizeof("users") - 1)))
                return code;
            if (0 > (code = discord_users_to_jsonb(b, buf, size, this->users)))
                return code;
        }

        if (this->webhooks != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "webhooks",
                                      sizeof("webhooks") - 1)))
                return code;
            if (0 > (code = discord_webhooks_to_jsonb(b, buf, size,
                                                      this->webhooks)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_audit_log_entry_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_audit_log_entry *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "target_id",
                                  sizeof("target_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->target_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->changes != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "changes",
                                      sizeof("changes") - 1)))
                return code;
            if (0 > (code = discord_audit_log_changes_to_jsonb(b, buf, size,
                                                               this->changes)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "user_id",
                                  sizeof("user_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->user_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->action_type != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "action_type",
                                      sizeof("action_type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->action_type)))
                return code;
        }

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0 > (code = discord_optional_audit_entry_infos_to_jsonb(
                         b, buf, size, this->options)))
                return code;
        }

        if (0
            > (code = jsonb_key(b, buf, size, "reason", sizeof("reason") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->reason,
                                     this->reason ? strlen(this->reason) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_audit_log_entries_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_audit_log_entries *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_audit_log_entry_to_jsonb(b, buf, size,
                                                             &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_optional_audit_entry_info_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_optional_audit_entry_info *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "count", sizeof("count") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->count,
                                     this->count ? strlen(this->count) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "delete_member_days",
                                  sizeof("delete_member_days") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->delete_member_days,
                                     this->delete_member_days
                                         ? strlen(this->delete_member_days)
                                         : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "members_removed",
                                  sizeof("members_removed") - 1)))
            return code;
        if (0
            > (code = jsonb_string(
                   b, buf, size, this->members_removed,
                   this->members_removed ? strlen(this->members_removed) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "message_id",
                                  sizeof("message_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->message_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "role_name",
                                  sizeof("role_name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->role_name,
                                     this->role_name ? strlen(this->role_name)
                                                     : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->type,
                                     this->type ? strlen(this->type) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_optional_audit_entry_infos_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_optional_audit_entry_infos *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_optional_audit_entry_info_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_audit_log_change_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_audit_log_change *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "new_value",
                                  sizeof("new_value") - 1)))
            return code;
        if (0 > (code = jsonb_token(b, buf, size, this->new_value,
                                    strlen(this->new_value))))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "old_value",
                                  sizeof("old_value") - 1)))
            return code;
        if (0 > (code = jsonb_token(b, buf, size, this->old_value,
                                    strlen(this->old_value))))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "key", sizeof("key") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->key,
                                     this->key ? strlen(this->key) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_audit_log_changes_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_audit_log_changes *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_audit_log_change_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_get_guild_audit_log_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_audit_log *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "user_id",
                                  sizeof("user_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->user_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "action_type",
                                  sizeof("action_type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->action_type)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "before", sizeof("before") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->before);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->limit >= 1 && this->limit <= 100) {
            if (0 > (code = jsonb_key(b, buf, size, "limit",
                                      sizeof("limit") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->limit)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_invite_to_jsonb(jsonb *b,
                        char buf[],
                        size_t size,
                        const struct discord_invite *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "code", sizeof("code") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->code,
                                     this->code ? strlen(this->code) : 0)))
            return code;

        if (this->guild != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "guild",
                                      sizeof("guild") - 1)))
                return code;
            if (0 > (code = discord_guild_to_jsonb(b, buf, size, this->guild)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel",
                                  sizeof("channel") - 1)))
            return code;
        if (0 > (code = discord_channel_to_jsonb(b, buf, size, this->channel)))
            return code;

        if (this->inviter != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "inviter",
                                      sizeof("inviter") - 1)))
                return code;
            if (0
                > (code = discord_user_to_jsonb(b, buf, size, this->inviter)))
                return code;
        }

        if (this->target_type != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "target_type",
                                      sizeof("target_type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->target_type)))
                return code;
        }

        if (this->target_user != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "target_user",
                                      sizeof("target_user") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size,
                                                  this->target_user)))
                return code;
        }

        if (this->target_application != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "target_application",
                                      sizeof("target_application") - 1)))
                return code;
            if (0 > (code = discord_application_to_jsonb(
                         b, buf, size, this->target_application)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "approximate_presence_count",
                                  sizeof("approximate_presence_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->approximate_presence_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "approximate_member_count",
                                  sizeof("approximate_member_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->approximate_member_count)))
            return code;

        if (this->expires_at != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "expires_at",
                                      sizeof("expires_at") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen =
                    cog_unix_ms_to_iso8601(tok, sizeof(tok), this->expires_at);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (this->stage_instance != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "stage_instance",
                                      sizeof("stage_instance") - 1)))
                return code;
            if (0 > (code = discord_invite_stage_instance_to_jsonb(
                         b, buf, size, this->stage_instance)))
                return code;
        }

        if (this->guild_scheduled_event != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "guild_scheduled_event",
                                      sizeof("guild_scheduled_event") - 1)))
                return code;
            if (0 > (code = discord_guild_scheduled_event_to_jsonb(
                         b, buf, size, this->guild_scheduled_event)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_invites_to_jsonb(jsonb *b,
                         char buf[],
                         size_t size,
                         const struct discord_invites *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_invite_to_jsonb(b, buf, size,
                                                    &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_invite_metadata_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_invite_metadata *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "uses", sizeof("uses") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->uses))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "max_uses",
                                  sizeof("max_uses") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->max_uses)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "max_age",
                                  sizeof("max_age") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->max_age)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "temporary",
                                  sizeof("temporary") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->temporary)))
            return code;

        if (this->created_at != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "created_at",
                                      sizeof("created_at") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen =
                    cog_unix_ms_to_iso8601(tok, sizeof(tok), this->created_at);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_invite_stage_instance_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_invite_stage_instance *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->members != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "members",
                                      sizeof("members") - 1)))
                return code;
            if (0 > (code = discord_guild_members_to_jsonb(b, buf, size,
                                                           this->members)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "participant_count",
                                  sizeof("participant_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->participant_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "speaker_count",
                                  sizeof("speaker_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->speaker_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "topic", sizeof("topic") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->topic,
                                     this->topic ? strlen(this->topic) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_get_invite_to_jsonb(jsonb *b,
                            char buf[],
                            size_t size,
                            const struct discord_get_invite *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "with_counts",
                                  sizeof("with_counts") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->with_counts)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "with_expiration",
                                  sizeof("with_expiration") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->with_expiration)))
            return code;

        if (this->guild_scheduled_event_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "guild_scheduled_event_id",
                                      sizeof("guild_scheduled_event_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"",
                                 this->guild_scheduled_event_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_channel_to_jsonb(jsonb *b,
                         char buf[],
                         size_t size,
                         const struct discord_channel *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (this->guild_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                      sizeof("guild_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "position",
                                  sizeof("position") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->position)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "permission_overwrites",
                                  sizeof("permission_overwrites") - 1)))
            return code;
        if (0 > (code = discord_overwrites_to_jsonb(
                     b, buf, size, this->permission_overwrites)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "topic", sizeof("topic") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->topic,
                                     this->topic ? strlen(this->topic) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "nsfw", sizeof("nsfw") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->nsfw))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "last_message_id",
                                  sizeof("last_message_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->last_message_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "bitrate",
                                  sizeof("bitrate") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->bitrate)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "user_limit",
                                  sizeof("user_limit") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->user_limit)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "rate_limit_per_user",
                                  sizeof("rate_limit_per_user") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->rate_limit_per_user)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "recipients",
                                  sizeof("recipients") - 1)))
            return code;
        if (0
            > (code = discord_users_to_jsonb(b, buf, size, this->recipients)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "owner_id",
                                  sizeof("owner_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->owner_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "application_id",
                                  sizeof("application_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->application_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "parent_id",
                                  sizeof("parent_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->parent_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "last_pin_timestamp",
                                  sizeof("last_pin_timestamp") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                            this->last_pin_timestamp);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "rtc_region",
                                  sizeof("rtc_region") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->rtc_region,
                     this->rtc_region ? strlen(this->rtc_region) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "voice_quality_mode",
                                  sizeof("voice_quality_mode") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->voice_quality_mode)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "message_count",
                                  sizeof("message_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->message_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "member_count",
                                  sizeof("member_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->member_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "thread_metadata",
                                  sizeof("thread_metadata") - 1)))
            return code;
        if (0 > (code = discord_thread_metadata_to_jsonb(
                     b, buf, size, this->thread_metadata)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "member", sizeof("member") - 1)))
            return code;
        if (0 > (code = discord_thread_member_to_jsonb(b, buf, size,
                                                       this->member)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "default_auto_archive_duration",
                                sizeof("default_auto_archive_duration") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->default_auto_archive_duration)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                  sizeof("permissions") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->permissions,
                     this->permissions ? strlen(this->permissions) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_channels_to_jsonb(jsonb *b,
                          char buf[],
                          size_t size,
                          const struct discord_channels *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_channel_to_jsonb(b, buf, size,
                                                     &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_message_to_jsonb(jsonb *b,
                         char buf[],
                         size_t size,
                         const struct discord_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0
            > (code = jsonb_key(b, buf, size, "author", sizeof("author") - 1)))
            return code;
        if (0 > (code = discord_user_to_jsonb(b, buf, size, this->author)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "member", sizeof("member") - 1)))
            return code;
        if (0 > (code = discord_guild_member_to_jsonb(b, buf, size,
                                                      this->member)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "content",
                                  sizeof("content") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->content,
                                   this->content ? strlen(this->content) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "timestamp",
                                  sizeof("timestamp") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), this->timestamp);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (this->edited_timestamp != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "edited_timestamp",
                                      sizeof("edited_timestamp") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                                this->edited_timestamp);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (0 > (code = jsonb_key(b, buf, size, "tts", sizeof("tts") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->tts))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "mention_everyone",
                                  sizeof("mention_everyone") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->mention_everyone)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "mentions",
                                  sizeof("mentions") - 1)))
            return code;
        if (0 > (code = discord_users_to_jsonb(b, buf, size, this->mentions)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "mention_roles",
                                  sizeof("mention_roles") - 1)))
            return code;
        if (0 > (code = discord_roles_to_jsonb(b, buf, size,
                                               this->mention_roles)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "mention_channels",
                                  sizeof("mention_channels") - 1)))
            return code;
        if (0 > (code = discord_channels_to_jsonb(b, buf, size,
                                                  this->mention_channels)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                  sizeof("attachments") - 1)))
            return code;
        if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                     this->attachments)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "embeds", sizeof("embeds") - 1)))
            return code;
        if (0 > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "reactions",
                                  sizeof("reactions") - 1)))
            return code;
        if (0 > (code = discord_reactions_to_jsonb(b, buf, size,
                                                   this->reactions)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "nonce", sizeof("nonce") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->nonce,
                                     this->nonce ? strlen(this->nonce) : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "pinned", sizeof("pinned") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->pinned))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "webhook_id",
                                  sizeof("webhook_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->webhook_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "activity",
                                  sizeof("activity") - 1)))
            return code;
        if (0 > (code = discord_message_activity_to_jsonb(b, buf, size,
                                                          this->activity)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "application",
                                  sizeof("application") - 1)))
            return code;
        if (0 > (code = discord_application_to_jsonb(b, buf, size,
                                                     this->application)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "application_id",
                                  sizeof("application_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->application_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "message_reference",
                                  sizeof("message_reference") - 1)))
            return code;
        if (0 > (code = discord_message_reference_to_jsonb(
                     b, buf, size, this->message_reference)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "flags", sizeof("flags") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->flags))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "referenced_message",
                                  sizeof("referenced_message") - 1)))
            return code;
        if (0 > (code = discord_message_to_jsonb(b, buf, size,
                                                 this->referenced_message)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "interaction",
                                  sizeof("interaction") - 1)))
            return code;
        if (0 > (code = discord_message_interaction_to_jsonb(
                     b, buf, size, this->interaction)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "thread", sizeof("thread") - 1)))
            return code;
        if (0 > (code = discord_channel_to_jsonb(b, buf, size, this->thread)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "components",
                                  sizeof("components") - 1)))
            return code;
        if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                    this->components)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "sticker_items",
                                  sizeof("sticker_items") - 1)))
            return code;
        if (0 > (code = discord_sticker_items_to_jsonb(b, buf, size,
                                                       this->sticker_items)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_messages_to_jsonb(jsonb *b,
                          char buf[],
                          size_t size,
                          const struct discord_messages *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_message_to_jsonb(b, buf, size,
                                                     &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_message_activity_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_message_activity *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "party_id",
                                  sizeof("party_id") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->party_id,
                                     this->party_id ? strlen(this->party_id)
                                                    : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_message_reference_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_message_reference *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "message_id",
                                  sizeof("message_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->message_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "fail_if_not_exists",
                                  sizeof("fail_if_not_exists") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->fail_if_not_exists)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_followed_channel_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_followed_channel *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "webhook_id",
                                  sizeof("webhook_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->webhook_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_reaction_to_jsonb(jsonb *b,
                          char buf[],
                          size_t size,
                          const struct discord_reaction *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "count", sizeof("count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->count))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "me", sizeof("me") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->me))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "emoji", sizeof("emoji") - 1)))
            return code;
        if (0 > (code = discord_emoji_to_jsonb(b, buf, size, this->emoji)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_reactions_to_jsonb(jsonb *b,
                           char buf[],
                           size_t size,
                           const struct discord_reactions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_reaction_to_jsonb(b, buf, size,
                                                      &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_overwrite_to_jsonb(jsonb *b,
                           char buf[],
                           size_t size,
                           const struct discord_overwrite *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "allow", sizeof("allow") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->allow);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "deny", sizeof("deny") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->deny);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_overwrites_to_jsonb(jsonb *b,
                            char buf[],
                            size_t size,
                            const struct discord_overwrites *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_overwrite_to_jsonb(b, buf, size,
                                                       &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_thread_metadata_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_thread_metadata *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "archived",
                                  sizeof("archived") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->archived))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "auto_archive_duration",
                                  sizeof("auto_archive_duration") - 1)))
            return code;
        if (0
            > (code = jsonb_number(b, buf, size, this->auto_archive_duration)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "archive_timestamp",
                                  sizeof("archive_timestamp") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                            this->archive_timestamp);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0
            > (code = jsonb_key(b, buf, size, "locked", sizeof("locked") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->locked))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "invitable",
                                  sizeof("invitable") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->invitable)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "create_timestamp",
                                  sizeof("create_timestamp") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                            this->create_timestamp);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_thread_member_to_jsonb(jsonb *b,
                               char buf[],
                               size_t size,
                               const struct discord_thread_member *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "user_id",
                                  sizeof("user_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->user_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "join_timestamp",
                                  sizeof("join_timestamp") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen =
                cog_unix_ms_to_iso8601(tok, sizeof(tok), this->join_timestamp);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "flags", sizeof("flags") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->flags))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_thread_members_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_thread_members *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_thread_member_to_jsonb(b, buf, size,
                                                           &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_attachment_to_jsonb(jsonb *b,
                            char buf[],
                            size_t size,
                            const struct discord_attachment *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "content",
                                  sizeof("content") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->content,
                                   this->content ? strlen(this->content) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->filename != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "filename",
                                      sizeof("filename") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->filename,
                         this->filename ? strlen(this->filename) : 0)))
                return code;
        }

        if (this->description != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "description",
                                      sizeof("description") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->description,
                         this->description ? strlen(this->description) : 0)))
                return code;
        }

        if (this->content_type != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "content_type",
                                      sizeof("content_type") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->content_type,
                         this->content_type ? strlen(this->content_type) : 0)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "size", sizeof("size") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->size))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->url,
                                     this->url ? strlen(this->url) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "proxy_url",
                                  sizeof("proxy_url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->proxy_url,
                                     this->proxy_url ? strlen(this->proxy_url)
                                                     : 0)))
            return code;

        if (this->height != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "height",
                                      sizeof("height") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->height)))
                return code;
        }

        if (this->width != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "width",
                                      sizeof("width") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->width)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "ephemeral",
                                  sizeof("ephemeral") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->ephemeral)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_attachments_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_attachments *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_attachment_to_jsonb(b, buf, size,
                                                        &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_to_jsonb(jsonb *b,
                       char buf[],
                       size_t size,
                       const struct discord_embed *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "title", sizeof("title") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->title,
                                     this->title ? strlen(this->title) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->type,
                                     this->type ? strlen(this->type) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->url,
                                     this->url ? strlen(this->url) : 0)))
            return code;

        if (this->timestamp != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "timestamp",
                                      sizeof("timestamp") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen =
                    cog_unix_ms_to_iso8601(tok, sizeof(tok), this->timestamp);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (this->color != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "color",
                                      sizeof("color") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->color)))
                return code;
        }

        if (this->footer != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "footer",
                                      sizeof("footer") - 1)))
                return code;
            if (0 > (code = discord_embed_footer_to_jsonb(b, buf, size,
                                                          this->footer)))
                return code;
        }

        if (this->image != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "image",
                                      sizeof("image") - 1)))
                return code;
            if (0 > (code = discord_embed_image_to_jsonb(b, buf, size,
                                                         this->image)))
                return code;
        }

        if (this->thumbnail != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "thumbnail",
                                      sizeof("thumbnail") - 1)))
                return code;
            if (0 > (code = discord_embed_thumbnail_to_jsonb(b, buf, size,
                                                             this->thumbnail)))
                return code;
        }

        if (this->video != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "video",
                                      sizeof("video") - 1)))
                return code;
            if (0 > (code = discord_embed_video_to_jsonb(b, buf, size,
                                                         this->video)))
                return code;
        }
        if (this->provider != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "provider",
                                      sizeof("provider") - 1)))
                return code;
            if (0 > (code = discord_embed_provider_to_jsonb(b, buf, size,
                                                            this->provider)))
                return code;
        }
        if (this->author != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "author",
                                      sizeof("author") - 1)))
                return code;
            if (0 > (code = discord_embed_author_to_jsonb(b, buf, size,
                                                          this->author)))
                return code;
        }
        if (this->fields != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "fields",
                                      sizeof("fields") - 1)))
                return code;
            if (0 > (code = discord_embed_fields_to_jsonb(b, buf, size,
                                                          this->fields)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embeds_to_jsonb(jsonb *b,
                        char buf[],
                        size_t size,
                        const struct discord_embeds *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_embed_to_jsonb(b, buf, size,
                                                   &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_thumbnail_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_embed_thumbnail *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->url,
                                     this->url ? strlen(this->url) : 0)))
            return code;

        if (this->proxy_url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "proxy_url",
                                      sizeof("proxy_url") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->proxy_url,
                         this->proxy_url ? strlen(this->proxy_url) : 0)))
                return code;
        }

        if (this->height != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "height",
                                      sizeof("height") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->height)))
                return code;
        }

        if (this->width != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "width",
                                      sizeof("width") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->width)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_video_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_embed_video *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->url,
                                         this->url ? strlen(this->url) : 0)))
                return code;
        }

        if (this->proxy_url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "proxy_url",
                                      sizeof("proxy_url") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->proxy_url,
                         this->proxy_url ? strlen(this->proxy_url) : 0)))
                return code;
        }

        if (this->height != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "height",
                                      sizeof("height") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->height)))
                return code;
        }

        if (this->width != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "width",
                                      sizeof("width") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->width)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_image_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_embed_image *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->url,
                                     this->url ? strlen(this->url) : 0)))
            return code;

        if (this->proxy_url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "proxy_url",
                                      sizeof("proxy_url") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->proxy_url,
                         this->proxy_url ? strlen(this->proxy_url) : 0)))
                return code;
        }

        if (this->height != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "height",
                                      sizeof("height") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->height)))
                return code;
        }

        if (this->width != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "width",
                                      sizeof("width") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->width)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_provider_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_embed_provider *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->name != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->name,
                                         this->name ? strlen(this->name) : 0)))
                return code;
        }

        if (this->url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->url,
                                         this->url ? strlen(this->url) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_author_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_embed_author *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->url,
                                         this->url ? strlen(this->url) : 0)))
                return code;
        }

        if (this->icon_url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "icon_url",
                                      sizeof("icon_url") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->icon_url,
                         this->icon_url ? strlen(this->icon_url) : 0)))
                return code;
        }

        if (this->proxy_icon_url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "proxy_icon_url",
                                      sizeof("proxy_icon_url") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->proxy_icon_url,
                                         this->proxy_icon_url
                                             ? strlen(this->proxy_icon_url)
                                             : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_footer_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_embed_footer *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "text", sizeof("text") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->text,
                                     this->text ? strlen(this->text) : 0)))
            return code;

        if (this->icon_url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "icon_url",
                                      sizeof("icon_url") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->icon_url,
                         this->icon_url ? strlen(this->icon_url) : 0)))
                return code;
        }

        if (this->proxy_icon_url != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "proxy_icon_url",
                                      sizeof("proxy_icon_url") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->proxy_icon_url,
                                         this->proxy_icon_url
                                             ? strlen(this->proxy_icon_url)
                                             : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_field_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_embed_field *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "value", sizeof("value") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->value,
                                     this->value ? strlen(this->value) : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "inline", sizeof("inline") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->Inline))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_embed_fields_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_embed_fields *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_embed_field_to_jsonb(b, buf, size,
                                                         &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_channel_mention_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_channel_mention *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_allowed_mention_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_allowed_mention *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "parse", sizeof("parse") - 1)))
            return code;
        if (0 > (code = strings_to_jsonb(b, buf, size, this->parse)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "roles", sizeof("roles") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->roles)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "users", sizeof("users") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->users)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "replied_user",
                                  sizeof("replied_user") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->replied_user)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_thread_response_body_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_thread_response_body *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "threads",
                                  sizeof("threads") - 1)))
            return code;
        if (0
            > (code = discord_channels_to_jsonb(b, buf, size, this->threads)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "members",
                                  sizeof("members") - 1)))
            return code;
        if (0 > (code = discord_thread_members_to_jsonb(b, buf, size,
                                                        this->members)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "has_more",
                                  sizeof("has_more") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->has_more))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_channel_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_modify_channel *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (this->position != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "position",
                                      sizeof("position") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->position)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "topic", sizeof("topic") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->topic,
                                     this->topic ? strlen(this->topic) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "nsfw", sizeof("nsfw") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->nsfw))) return code;

        if (this->rate_limit_per_user != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "rate_limit_per_user",
                                      sizeof("rate_limit_per_user") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->rate_limit_per_user)))
                return code;
        }

        if (this->user_limit != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "user_limit",
                                      sizeof("user_limit") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->user_limit)))
                return code;
        }

        if (this->permission_overwrites != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "permission_overwrites",
                                      sizeof("permission_overwrites") - 1)))
                return code;
            if (0 > (code = discord_overwrites_to_jsonb(
                         b, buf, size, this->permission_overwrites)))
                return code;
        }

        if (this->parent_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "parent_id",
                                      sizeof("parent_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->parent_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "rtc_region",
                                  sizeof("rtc_region") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->rtc_region,
                     this->rtc_region ? strlen(this->rtc_region) : 0)))
            return code;

        if (this->video_quality_mode != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "video_quality_mode",
                                      sizeof("video_quality_mode") - 1)))
                return code;
            if (0 > (code =
                         jsonb_number(b, buf, size, this->video_quality_mode)))
                return code;
        }

        if (this->default_auto_archive_duration != 0) {
            if (0 > (code = jsonb_key(
                         b, buf, size, "default_auto_archive_duration",
                         sizeof("default_auto_archive_duration") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->default_auto_archive_duration)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "archived",
                                  sizeof("archived") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->archived))) return code;

        if (this->auto_archive_duration != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "auto_archive_duration",
                                      sizeof("auto_archive_duration") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->auto_archive_duration)))
                return code;
        }

        if (0
            > (code = jsonb_key(b, buf, size, "locked", sizeof("locked") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->locked))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "invitable",
                                  sizeof("invitable") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->invitable)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_get_channel_messages_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_channel_messages *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->around != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "around",
                                      sizeof("around") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->around);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->before != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "before",
                                      sizeof("before") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->before);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->after != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "after",
                                      sizeof("after") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->after);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->limit != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "limit",
                                      sizeof("limit") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->limit)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_message_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_create_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "content",
                                  sizeof("content") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->content,
                                   this->content ? strlen(this->content) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "tts", sizeof("tts") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->tts))) return code;

        if (0
            > (code = jsonb_key(b, buf, size, "embeds", sizeof("embeds") - 1)))
            return code;
        if (0 > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
            return code;

        if (this->allowed_mentions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "allowed_mentions",
                                      sizeof("allowed_mentions") - 1)))
                return code;
            if (0 > (code = discord_allowed_mention_to_jsonb(
                         b, buf, size, this->allowed_mentions)))
                return code;
        }

        if (this->message_reference != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "message_reference",
                                      sizeof("message_reference") - 1)))
                return code;
            if (0 > (code = discord_message_reference_to_jsonb(
                         b, buf, size, this->message_reference)))
                return code;
        }

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (this->sticker_ids != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "sticker_ids",
                                      sizeof("sticker_ids") - 1)))
                return code;
            if (0 > (code =
                         snowflakes_to_jsonb(b, buf, size, this->sticker_ids)))
                return code;
        }

        if (this->attachments != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                      sizeof("attachments") - 1)))
                return code;
            if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                         this->attachments)))
                return code;
        }

        if (this->flags != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "flags",
                                      sizeof("flags") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->flags)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_get_reactions_to_jsonb(jsonb *b,
                               char buf[],
                               size_t size,
                               const struct discord_get_reactions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->after != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "after",
                                      sizeof("after") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->after);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->limit != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "limit",
                                      sizeof("limit") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->limit)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_edit_message_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_edit_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "content",
                                  sizeof("content") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->content,
                                   this->content ? strlen(this->content) : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "embeds", sizeof("embeds") - 1)))
            return code;
        if (0 > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
            return code;

        if (this->flags != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "flags",
                                      sizeof("flags") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->flags)))
                return code;
        }

        if (this->allowed_mentions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "allowed_mentions",
                                      sizeof("allowed_mentions") - 1)))
                return code;
            if (0 > (code = discord_allowed_mention_to_jsonb(
                         b, buf, size, this->allowed_mentions)))
                return code;
        }

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (this->attachments != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                      sizeof("attachments") - 1)))
                return code;
            if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                         this->attachments)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_bulk_delete_messages_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_bulk_delete_messages *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "messages",
                                  sizeof("messages") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->messages)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_edit_channel_permissions_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_edit_channel_permissions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->allow != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "allow",
                                      sizeof("allow") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "%" PRIu64, this->allow);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->deny != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "deny", sizeof("deny") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "%" PRIu64, this->deny);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_channel_invite_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_channel_invite *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->max_age != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "max_age",
                                      sizeof("max_age") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->max_age)))
                return code;
        }

        if (this->max_uses != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "max_uses",
                                      sizeof("max_uses") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->max_uses)))
                return code;
        }

        if (this->temporary != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "temporary",
                                      sizeof("temporary") - 1)))
                return code;
            if (0 > (code = jsonb_bool(b, buf, size, this->temporary)))
                return code;
        }

        if (this->unique != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "unique",
                                      sizeof("unique") - 1)))
                return code;
            if (0 > (code = jsonb_bool(b, buf, size, this->unique)))
                return code;
        }

        if (this->target_type != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "target_type",
                                      sizeof("target_type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->target_type)))
                return code;
        }

        if (this->target_user_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "target_user_id",
                                      sizeof("target_user_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->target_user_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->target_application_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "target_application_id",
                                      sizeof("target_application_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"",
                                 this->target_application_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_follow_news_channel_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_follow_news_channel *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->webhook_channel_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "webhook_channel_id",
                                      sizeof("webhook_channel_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen =
                    sprintf(tok, "\"%" PRIu64 "\"", this->webhook_channel_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_group_dm_add_recipient_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_group_dm_add_recipient *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "access_token",
                                  sizeof("access_token") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->access_token,
                     this->access_token ? strlen(this->access_token) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "nick", sizeof("nick") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->nick,
                                     this->nick ? strlen(this->nick) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_start_thread_with_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_start_thread_with_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->auto_archive_duration != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "auto_archive_duration",
                                      sizeof("auto_archive_duration") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->auto_archive_duration)))
                return code;
        }

        if (this->rate_limit_per_user >= 0
            && this->rate_limit_per_user <= 21600) {
            if (0 > (code = jsonb_key(b, buf, size, "rate_limit_per_user",
                                      sizeof("rate_limit_per_user") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->rate_limit_per_user)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_start_thread_without_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_start_thread_without_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->auto_archive_duration != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "auto_archive_duration",
                                      sizeof("auto_archive_duration") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->auto_archive_duration)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "invitable",
                                  sizeof("invitable") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->invitable)))
            return code;

        if (this->rate_limit_per_user >= 0
            && this->rate_limit_per_user <= 21600) {
            if (0 > (code = jsonb_key(b, buf, size, "rate_limit_per_user",
                                      sizeof("rate_limit_per_user") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->rate_limit_per_user)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_list_active_threads_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_list_active_threads *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->threads != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "threads",
                                      sizeof("threads") - 1)))
                return code;
            if (0 > (code = discord_channels_to_jsonb(b, buf, size,
                                                      this->threads)))
                return code;
        }

        if (this->members != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "members",
                                      sizeof("members") - 1)))
                return code;
            if (0 > (code = discord_thread_members_to_jsonb(b, buf, size,
                                                            this->members)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "has_more",
                                  sizeof("has_more") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->has_more))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_emoji_to_jsonb(jsonb *b,
                       char buf[],
                       size_t size,
                       const struct discord_emoji *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->roles != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "roles",
                                      sizeof("roles") - 1)))
                return code;
            if (0 > (code = discord_roles_to_jsonb(b, buf, size, this->roles)))
                return code;
        }

        if (this->user != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "require_colons",
                                  sizeof("require_colons") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->require_colons)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "managed",
                                  sizeof("managed") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->managed))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "animated",
                                  sizeof("animated") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->animated))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "available",
                                  sizeof("available") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->available)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_emojis_to_jsonb(jsonb *b,
                        char buf[],
                        size_t size,
                        const struct discord_emojis *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_emoji_to_jsonb(b, buf, size,
                                                   &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_emoji_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_emoji *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "image", sizeof("image") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->image,
                                     this->image ? strlen(this->image) : 0)))
            return code;

        if (this->roles != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "roles",
                                      sizeof("roles") - 1)))
                return code;
            if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->roles)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_emoji_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_emoji *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "image", sizeof("image") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->image,
                                     this->image ? strlen(this->image) : 0)))
            return code;

        if (this->roles != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "roles",
                                      sizeof("roles") - 1)))
                return code;
            if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->roles)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_guild_to_jsonb(jsonb *b,
                       char buf[],
                       size_t size,
                       const struct discord_guild *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (this->icon_hash != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "icon_hash",
                                      sizeof("icon_hash") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->icon_hash,
                         this->icon_hash ? strlen(this->icon_hash) : 0)))
                return code;
        }

        if (0
            > (code = jsonb_key(b, buf, size, "splash", sizeof("splash") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->splash,
                                     this->splash ? strlen(this->splash) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "discovery_splash",
                                  sizeof("discovery_splash") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->discovery_splash,
                                     this->discovery_splash
                                         ? strlen(this->discovery_splash)
                                         : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "owner", sizeof("owner") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->owner))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "owner_id",
                                  sizeof("owner_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->owner_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->permissions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                      sizeof("permissions") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->permissions,
                         this->permissions ? strlen(this->permissions) : 0)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "afk_channel_id",
                                  sizeof("afk_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->afk_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "afk_timeout",
                                  sizeof("afk_timeout") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->afk_timeout)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "widget_enabled",
                                  sizeof("widget_enabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->widget_enabled)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "widget_channel_id",
                                  sizeof("widget_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->widget_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "verification_level",
                                  sizeof("verification_level") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->verification_level)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "default_message_notifications",
                                sizeof("default_message_notifications") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->default_message_notifications)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "explicit_content_filter",
                                  sizeof("explicit_content_filter") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->explicit_content_filter)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "roles", sizeof("roles") - 1)))
            return code;
        if (0 > (code = discord_roles_to_jsonb(b, buf, size, this->roles)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "emojis", sizeof("emojis") - 1)))
            return code;
        if (0 > (code = discord_emojis_to_jsonb(b, buf, size, this->emojis)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "features",
                                  sizeof("features") - 1)))
            return code;
        if (0 > (code = strings_to_jsonb(b, buf, size, this->features)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "mfa_level",
                                  sizeof("mfa_level") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->mfa_level)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "application_id",
                                  sizeof("application_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->application_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "system_channel_id",
                                  sizeof("system_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->system_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "system_channel_flags",
                                  sizeof("system_channel_flags") - 1)))
            return code;
        if (0
            > (code = jsonb_number(b, buf, size, this->system_channel_flags)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "rules_channel_id",
                                  sizeof("rules_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->rules_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->joined_at != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "joined_at",
                                      sizeof("joined_at") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen =
                    cog_unix_ms_to_iso8601(tok, sizeof(tok), this->joined_at);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (0 > (code = jsonb_key(b, buf, size, "large", sizeof("large") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->large))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "unavailable",
                                  sizeof("unavailable") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->unavailable)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "member_count",
                                  sizeof("member_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->member_count)))
            return code;

        if (this->voice_states != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "voice_states",
                                      sizeof("voice_states") - 1)))
                return code;
            if (0 > (code = discord_voice_states_to_jsonb(b, buf, size,
                                                          this->voice_states)))
                return code;
        }

        if (this->members != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "members",
                                      sizeof("members") - 1)))
                return code;
            if (0 > (code = discord_guild_members_to_jsonb(b, buf, size,
                                                           this->members)))
                return code;
        }

        if (this->channels != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "channels",
                                      sizeof("channels") - 1)))
                return code;
            if (0 > (code = discord_channels_to_jsonb(b, buf, size,
                                                      this->channels)))
                return code;
        }

        if (this->threads != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "threads",
                                      sizeof("threads") - 1)))
                return code;
            if (0 > (code = discord_channels_to_jsonb(b, buf, size,
                                                      this->threads)))
                return code;
        }

        if (this->presences != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "presences",
                                      sizeof("presences") - 1)))
                return code;
            if (0 > (code = discord_presence_updates_to_jsonb(
                         b, buf, size, this->presences)))
                return code;
        }

        if (this->max_presences != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "max_presences",
                                      sizeof("max_presences") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->max_presences)))
                return code;
        }

        if (this->max_members != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "max_members",
                                      sizeof("max_members") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->max_members)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "vanity_url_code",
                                  sizeof("vanity_url_code") - 1)))
            return code;
        if (0
            > (code = jsonb_string(
                   b, buf, size, this->vanity_url_code,
                   this->vanity_url_code ? strlen(this->vanity_url_code) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "banner", sizeof("banner") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->banner,
                                     this->banner ? strlen(this->banner) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "premium_tier",
                                  sizeof("premium_tier") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->premium_tier)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "premium_subscription_count",
                                  sizeof("premium_subscription_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->premium_subscription_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "preferred_locale",
                                  sizeof("preferred_locale") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->preferred_locale,
                                     this->preferred_locale
                                         ? strlen(this->preferred_locale)
                                         : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "public_updates_channel_id",
                                  sizeof("public_updates_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"",
                             this->public_updates_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->max_video_channel_users != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "max_video_channel_users",
                                      sizeof("max_video_channel_users") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->max_video_channel_users)))
                return code;
        }

        if (this->approximate_member_count != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "approximate_member_count",
                                      sizeof("approximate_member_count") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->approximate_member_count)))
                return code;
        }

        if (this->approximate_presence_count != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "approximate_presence_count",
                                    sizeof("approximate_presence_count") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->approximate_presence_count)))
                return code;
        }

        if (this->welcome_screen != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "welcome_screen",
                                      sizeof("welcome_screen") - 1)))
                return code;
            if (0 > (code = discord_welcome_screen_to_jsonb(
                         b, buf, size, this->welcome_screen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "nsfw_level",
                                  sizeof("nsfw_level") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->nsfw_level)))
            return code;

        if (this->stage_instances != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "stage_instances",
                                      sizeof("stage_instances") - 1)))
                return code;
            if (0 > (code = discord_stage_instances_to_jsonb(
                         b, buf, size, this->stage_instances)))
                return code;
        }

        if (this->stickers != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "stickers",
                                      sizeof("stickers") - 1)))
                return code;
            if (0 > (code = discord_stickers_to_jsonb(b, buf, size,
                                                      this->stickers)))
                return code;
        }

        if (this->guild_scheduled_events != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "guild_scheduled_events",
                                      sizeof("guild_scheduled_events") - 1)))
                return code;
            if (0 > (code = discord_guild_scheduled_events_to_jsonb(
                         b, buf, size, this->guild_scheduled_events)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "premium_progress_bar_enabled",
                                  sizeof("premium_progress_bar_enabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size,
                                   this->premium_progress_bar_enabled)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_guilds_to_jsonb(jsonb *b,
                        char buf[],
                        size_t size,
                        const struct discord_guilds *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_guild_to_jsonb(b, buf, size,
                                                   &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_guild_preview_to_jsonb(jsonb *b,
                               char buf[],
                               size_t size,
                               const struct discord_guild_preview *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "splash", sizeof("splash") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->splash,
                                     this->splash ? strlen(this->splash) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "discovery_splash",
                                  sizeof("discovery_splash") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->discovery_splash,
                                     this->discovery_splash
                                         ? strlen(this->discovery_splash)
                                         : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "emojis", sizeof("emojis") - 1)))
            return code;
        if (0 > (code = discord_emojis_to_jsonb(b, buf, size, this->emojis)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "features",
                                  sizeof("features") - 1)))
            return code;
        if (0 > (code = strings_to_jsonb(b, buf, size, this->features)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "approximate_member_count",
                                  sizeof("approximate_member_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->approximate_member_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "approximate_presence_count",
                                  sizeof("approximate_presence_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->approximate_presence_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "stickers",
                                  sizeof("stickers") - 1)))
            return code;
        if (0
            > (code = discord_stickers_to_jsonb(b, buf, size, this->stickers)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_guild_widget_setting_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_widget_setting *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "enabled",
                                  sizeof("enabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->enabled))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_get_guild_widget_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_get_guild_widget *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "instant_invite",
                                  sizeof("instant_invite") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->instant_invite,
                     this->instant_invite ? strlen(this->instant_invite) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "channels",
                                  sizeof("channels") - 1)))
            return code;
        if (0
            > (code = discord_channels_to_jsonb(b, buf, size, this->channels)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "members",
                                  sizeof("members") - 1)))
            return code;
        if (0 > (code = discord_users_to_jsonb(b, buf, size, this->members)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "presence_count",
                                  sizeof("presence_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->presence_count)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_guild_member_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_guild_member *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->user != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
                return code;
        }

        if (this->nick != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "nick", sizeof("nick") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->nick,
                                         this->nick ? strlen(this->nick) : 0)))
                return code;
        }

        if (this->avatar != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "avatar",
                                      sizeof("avatar") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->avatar,
                                         this->avatar ? strlen(this->avatar)
                                                      : 0)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "roles", sizeof("roles") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->roles)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "joined_at",
                                  sizeof("joined_at") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), this->joined_at);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (this->premium_since != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "premium_since",
                                      sizeof("premium_since") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                                this->premium_since);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (0 > (code = jsonb_key(b, buf, size, "deaf", sizeof("deaf") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->deaf))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "muted", sizeof("muted") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->muted))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "pending",
                                  sizeof("pending") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->pending))) return code;

        if (this->permissions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                      sizeof("permissions") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->permissions,
                         this->permissions ? strlen(this->permissions) : 0)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "communication_disabled_until",
                                  sizeof("communication_disabled_until") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(
                tok, sizeof(tok), this->communication_disabled_until);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_guild_members_to_jsonb(jsonb *b,
                               char buf[],
                               size_t size,
                               const struct discord_guild_members *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_guild_member_to_jsonb(b, buf, size,
                                                          &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_integration_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_integration *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->type,
                                     this->type ? strlen(this->type) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "enabled",
                                  sizeof("enabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->enabled))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "syncing",
                                  sizeof("syncing") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->syncing))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "role_id",
                                  sizeof("role_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->role_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "enable_emoticons",
                                  sizeof("enable_emoticons") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->enable_emoticons)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "expire_behavior",
                                  sizeof("expire_behavior") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->expire_behavior)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "expire_grace_period",
                                  sizeof("expire_grace_period") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->expire_grace_period)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
            return code;
        if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "account",
                                  sizeof("account") - 1)))
            return code;
        if (0 > (code = discord_integration_account_to_jsonb(b, buf, size,
                                                             this->account)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "synced_at",
                                  sizeof("synced_at") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), this->synced_at);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "subscriber_count",
                                  sizeof("subscriber_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->subscriber_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "revoked",
                                  sizeof("revoked") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->revoked))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "application",
                                  sizeof("application") - 1)))
            return code;
        if (0 > (code = discord_integration_application_to_jsonb(
                     b, buf, size, this->application)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_integrations_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_integrations *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_integration_to_jsonb(b, buf, size,
                                                         &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_integration_account_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_integration_account *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->id,
                                     this->id ? strlen(this->id) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_integration_application_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_integration_application *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "summary",
                                  sizeof("summary") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->summary,
                                   this->summary ? strlen(this->summary) : 0)))
            return code;

        if (this->bot != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "bot", sizeof("bot") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size, this->bot)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_ban_to_jsonb(jsonb *b,
                     char buf[],
                     size_t size,
                     const struct discord_ban *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0
            > (code = jsonb_key(b, buf, size, "reason", sizeof("reason") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->reason,
                                     this->reason ? strlen(this->reason) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
            return code;
        if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_bans_to_jsonb(jsonb *b,
                      char buf[],
                      size_t size,
                      const struct discord_bans *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0
                > (code = discord_ban_to_jsonb(b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_welcome_screen_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_welcome_screen *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->welcome_channels != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "welcome_channels",
                                      sizeof("welcome_channels") - 1)))
                return code;
            if (0 > (code = discord_welcome_screen_channels_to_jsonb(
                         b, buf, size, this->welcome_channels)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_welcome_screen_channel_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_welcome_screen_channel *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "emoji_id",
                                  sizeof("emoji_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->emoji_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "emoji_name",
                                  sizeof("emoji_name") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->emoji_name,
                     this->emoji_name ? strlen(this->emoji_name) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_welcome_screen_channels_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_welcome_screen_channels *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_welcome_screen_channel_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_create_guild *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->region != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "region",
                                      sizeof("region") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->region,
                                         this->region ? strlen(this->region)
                                                      : 0)))
                return code;
        }

        if (this->icon != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                         this->icon ? strlen(this->icon) : 0)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "verification_level",
                                  sizeof("verification_level") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->verification_level)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "default_message_notifications",
                                sizeof("default_message_notifications") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->default_message_notifications)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "explicit_content_filter",
                                  sizeof("explicit_content_filter") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->explicit_content_filter)))
            return code;

        if (this->roles != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "roles",
                                      sizeof("roles") - 1)))
                return code;
            if (0 > (code = discord_roles_to_jsonb(b, buf, size, this->roles)))
                return code;
        }

        if (this->channels != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "channels",
                                      sizeof("channels") - 1)))
                return code;
            if (0 > (code = discord_channels_to_jsonb(b, buf, size,
                                                      this->channels)))
                return code;
        }

        if (this->afk_channel_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "afk_channel_id",
                                      sizeof("afk_channel_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->afk_channel_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "afk_timeout",
                                  sizeof("afk_timeout") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->afk_timeout)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "system_channel_id",
                                  sizeof("system_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->system_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "system_channel_flags",
                                  sizeof("system_channel_flags") - 1)))
            return code;
        if (0
            > (code = jsonb_number(b, buf, size, this->system_channel_flags)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_modify_guild *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "verification_level",
                                  sizeof("verification_level") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->verification_level)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "default_message_notifications",
                                sizeof("default_message_notifications") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->default_message_notifications)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "explicit_content_filter",
                                  sizeof("explicit_content_filter") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size,
                                     this->explicit_content_filter)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "afk_channel_id",
                                  sizeof("afk_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->afk_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "afk_timeout",
                                  sizeof("afk_timeout") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->afk_timeout)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "owner_id",
                                  sizeof("owner_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->owner_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0
            > (code = jsonb_key(b, buf, size, "splash", sizeof("splash") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->splash,
                                     this->splash ? strlen(this->splash) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "discovery_splash",
                                  sizeof("discovery_splash") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->discovery_splash,
                                     this->discovery_splash
                                         ? strlen(this->discovery_splash)
                                         : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "banner", sizeof("banner") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->banner,
                                     this->banner ? strlen(this->banner) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "system_channel_id",
                                  sizeof("system_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->system_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "system_channel_flags",
                                  sizeof("system_channel_flags") - 1)))
            return code;
        if (0
            > (code = jsonb_number(b, buf, size, this->system_channel_flags)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "rules_channel_id",
                                  sizeof("rules_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->rules_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "public_updates_channel_id",
                                  sizeof("public_updates_channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"",
                             this->public_updates_channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "preferred_locale",
                                  sizeof("preferred_locale") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->preferred_locale,
                                     this->preferred_locale
                                         ? strlen(this->preferred_locale)
                                         : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "features",
                                  sizeof("features") - 1)))
            return code;
        if (0 > (code = strings_to_jsonb(b, buf, size, this->features)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "premium_progress_bar_enabled",
                                  sizeof("premium_progress_bar_enabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size,
                                   this->premium_progress_bar_enabled)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_channel_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_channel *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "topic", sizeof("topic") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->topic,
                                     this->topic ? strlen(this->topic) : 0)))
            return code;

        if (this->bitrate != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "bitrate",
                                      sizeof("bitrate") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->bitrate)))
                return code;
        }

        if (this->user_limit != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "user_limit",
                                      sizeof("user_limit") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->user_limit)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "rate_limit_per_user",
                                  sizeof("rate_limit_per_user") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->rate_limit_per_user)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "position",
                                  sizeof("position") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->position)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "permission_overwrites",
                                  sizeof("permission_overwrites") - 1)))
            return code;
        if (0 > (code = discord_overwrites_to_jsonb(
                     b, buf, size, this->permission_overwrites)))
            return code;

        if (this->parent_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "parent_id",
                                      sizeof("parent_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->parent_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "nsfw", sizeof("nsfw") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->nsfw))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_modify_guild_channel_position_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_channel_position *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->position != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "position",
                                      sizeof("position") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->position)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "lock_category",
                                  sizeof("lock_category") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->lock_category)))
            return code;

        if (this->parent_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "parent_id",
                                      sizeof("parent_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->parent_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_channel_positions_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_channel_positions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_modify_guild_channel_position_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_list_active_guild_threads_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_list_active_guild_threads *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "threads",
                                  sizeof("threads") - 1)))
            return code;
        if (0
            > (code = discord_channels_to_jsonb(b, buf, size, this->threads)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "members",
                                  sizeof("members") - 1)))
            return code;
        if (0 > (code = discord_thread_members_to_jsonb(b, buf, size,
                                                        this->members)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_list_guild_members_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_list_guild_members *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "limit", sizeof("limit") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->limit))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "after", sizeof("after") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->after);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_search_guild_members_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_search_guild_members *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "query", sizeof("query") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->query,
                                     this->query ? strlen(this->query) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "limit", sizeof("limit") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->limit))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_add_guild_member_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_add_guild_member *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "access_token",
                                  sizeof("access_token") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->access_token,
                     this->access_token ? strlen(this->access_token) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "nick", sizeof("nick") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->nick,
                                     this->nick ? strlen(this->nick) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "roles", sizeof("roles") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->roles)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "mute", sizeof("mute") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->mute))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "deaf", sizeof("deaf") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->deaf))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_member_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_member *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "nick", sizeof("nick") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->nick,
                                     this->nick ? strlen(this->nick) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "roles", sizeof("roles") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->roles)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "mute", sizeof("mute") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->mute))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "deaf", sizeof("deaf") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->deaf))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->communication_disabled_until != 0) {
            if (0 > (code = jsonb_key(
                         b, buf, size, "communication_disabled_until",
                         sizeof("communication_disabled_until") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(
                    tok, sizeof(tok), this->communication_disabled_until);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_current_member_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_current_member *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->nick != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "nick", sizeof("nick") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->nick,
                                         this->nick ? strlen(this->nick) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_current_user_nick_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_current_user_nick *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->nick != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "nick", sizeof("nick") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->nick,
                                         this->nick ? strlen(this->nick) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_ban_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_create_guild_ban *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->delete_message_days >= 0 && this->delete_message_days <= 7) {
            if (0 > (code = jsonb_key(b, buf, size, "delete_message_days",
                                      sizeof("delete_message_days") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size,
                                         this->delete_message_days)))
                return code;
        }

        if (this->reason != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "reason",
                                      sizeof("reason") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->reason,
                                         this->reason ? strlen(this->reason)
                                                      : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_role_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_role *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                  sizeof("permissions") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->permissions);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "color", sizeof("color") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->color))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "hoist", sizeof("hoist") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->hoist))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "unicode_emoji",
                                  sizeof("unicode_emoji") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->unicode_emoji,
                     this->unicode_emoji ? strlen(this->unicode_emoji) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "mentionable",
                                  sizeof("mentionable") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->mentionable)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_modify_guild_role_position_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_role_position *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->position != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "position",
                                      sizeof("position") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->position)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_role_positions_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_role_positions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_modify_guild_role_position_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_role_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_role *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                  sizeof("permissions") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->permissions);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "color", sizeof("color") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->color))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "hoist", sizeof("hoist") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->hoist))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "unicode_emoji",
                                  sizeof("unicode_emoji") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->unicode_emoji,
                     this->unicode_emoji ? strlen(this->unicode_emoji) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "mentionable",
                                  sizeof("mentionable") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->mentionable)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_get_guild_prune_count_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_prune_count *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->count != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "count",
                                      sizeof("count") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->count)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "include_roles",
                                  sizeof("include_roles") - 1)))
            return code;
        if (0
            > (code = snowflakes_to_jsonb(b, buf, size, this->include_roles)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_begin_guild_prune_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_begin_guild_prune *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->days != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "days", sizeof("days") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->days)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "compute_prune_count",
                                  sizeof("compute_prune_count") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->compute_prune_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "include_roles",
                                  sizeof("include_roles") - 1)))
            return code;
        if (0
            > (code = snowflakes_to_jsonb(b, buf, size, this->include_roles)))
            return code;

        if (this->reason != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "reason",
                                      sizeof("reason") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->reason,
                                         this->reason ? strlen(this->reason)
                                                      : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_get_guild_widget_image_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_widget_image *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->style != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "style",
                                      sizeof("style") - 1)))
                return code;
            if (0
                > (code = jsonb_string(b, buf, size, this->style,
                                       this->style ? strlen(this->style) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_welcome_screen_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_welcome_screen *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "enabled",
                                  sizeof("enabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->enabled))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "welcome_channels",
                                  sizeof("welcome_channels") - 1)))
            return code;
        if (0 > (code = discord_welcome_screen_channels_to_jsonb(
                     b, buf, size, this->welcome_channels)))
            return code;

        if (this->description != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "description",
                                      sizeof("description") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->description,
                         this->description ? strlen(this->description) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_current_user_voice_state_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_current_user_voice_state *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "suppress",
                                  sizeof("suppress") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->suppress))) return code;

        if (this->request_to_speak_timestamp != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "request_to_speak_timestamp",
                                    sizeof("request_to_speak_timestamp") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(
                    tok, sizeof(tok), this->request_to_speak_timestamp);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_user_voice_state_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_user_voice_state *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "suppress",
                                  sizeof("suppress") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->suppress))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_guild_scheduled_event_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_scheduled_event *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "creator_id",
                                  sizeof("creator_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->creator_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "scheduled_start_time",
                                  sizeof("scheduled_start_time") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                            this->scheduled_start_time);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "scheduled_end_time",
                                  sizeof("scheduled_end_time") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                            this->scheduled_end_time);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (this->privacy_level != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "privacy_level",
                                      sizeof("privacy_level") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->privacy_level)))
                return code;
        }

        if (this->status != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "status",
                                      sizeof("status") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->status)))
                return code;
        }

        if (this->entity_type != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "entity_type",
                                      sizeof("entity_type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->entity_type)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "entity_id",
                                  sizeof("entity_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->entity_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->entity_metadata != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "entity_metadata",
                                      sizeof("entity_metadata") - 1)))
                return code;
            if (0
                > (code =
                       discord_guild_scheduled_event_entity_metadata_to_jsonb(
                           b, buf, size, this->entity_metadata)))
                return code;
        }

        if (this->creator != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "creator",
                                      sizeof("creator") - 1)))
                return code;
            if (0
                > (code = discord_user_to_jsonb(b, buf, size, this->creator)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "user_count",
                                  sizeof("user_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->user_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "image", sizeof("image") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->image,
                                     this->image ? strlen(this->image) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_guild_scheduled_events_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_scheduled_events *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_guild_scheduled_event_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_guild_scheduled_event_entity_metadata_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_scheduled_event_entity_metadata *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->location != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "location",
                                      sizeof("location") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->location,
                         this->location ? strlen(this->location) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_guild_scheduled_event_user_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_scheduled_event_user *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "guild_scheduled_event_id",
                                  sizeof("guild_scheduled_event_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"",
                             this->guild_scheduled_event_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->user != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
                return code;
        }

        if (this->member != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "member",
                                      sizeof("member") - 1)))
                return code;
            if (0 > (code = discord_guild_member_to_jsonb(b, buf, size,
                                                          this->member)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_list_scheduled_events_for_guild_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_list_scheduled_events_for_guild *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "with_user_count",
                                  sizeof("with_user_count") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->with_user_count)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_scheduled_event_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_scheduled_event *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->channel_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                      sizeof("channel_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->entity_metadata != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "entity_metadata",
                                      sizeof("entity_metadata") - 1)))
                return code;
            if (0
                > (code =
                       discord_guild_scheduled_event_entity_metadata_to_jsonb(
                           b, buf, size, this->entity_metadata)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->scheduled_start_time != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "scheduled_start_time",
                                      sizeof("scheduled_start_time") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                                this->scheduled_start_time);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (this->scheduled_end_time != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "scheduled_end_time",
                                      sizeof("scheduled_end_time") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                                this->scheduled_end_time);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (this->description != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "description",
                                      sizeof("description") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->description,
                         this->description ? strlen(this->description) : 0)))
                return code;
        }

        if (this->entity_type != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "entity_type",
                                      sizeof("entity_type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->entity_type)))
                return code;
        }

        if (this->image != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "image",
                                      sizeof("image") - 1)))
                return code;
            if (0
                > (code = jsonb_string(b, buf, size, this->image,
                                       this->image ? strlen(this->image) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_get_guild_scheduled_event_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_scheduled_event *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "with_user_count",
                                  sizeof("with_user_count") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->with_user_count)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_scheduled_event_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_scheduled_event *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->channel_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                      sizeof("channel_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->entity_metadata != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "entity_metadata",
                                      sizeof("entity_metadata") - 1)))
                return code;
            if (0
                > (code =
                       discord_guild_scheduled_event_entity_metadata_to_jsonb(
                           b, buf, size, this->entity_metadata)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->scheduled_start_time != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "scheduled_start_time",
                                      sizeof("scheduled_start_time") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                                this->scheduled_start_time);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (this->scheduled_end_time != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "scheduled_end_time",
                                      sizeof("scheduled_end_time") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok),
                                                this->scheduled_end_time);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }

        if (this->description != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "description",
                                      sizeof("description") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->description,
                         this->description ? strlen(this->description) : 0)))
                return code;
        }

        if (this->entity_type != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "entity_type",
                                      sizeof("entity_type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->entity_type)))
                return code;
        }

        if (this->status != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "status",
                                      sizeof("status") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->status)))
                return code;
        }

        if (this->image != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "image",
                                      sizeof("image") - 1)))
                return code;
            if (0
                > (code = jsonb_string(b, buf, size, this->image,
                                       this->image ? strlen(this->image) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_get_guild_scheduled_event_users_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_guild_scheduled_event_users *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "limit", sizeof("limit") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->limit))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "with_member",
                                  sizeof("with_member") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->with_member)))
            return code;

        if (this->before != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "before",
                                      sizeof("before") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->before);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->after != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "after",
                                      sizeof("after") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->after);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_guild_template_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_guild_template *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "code", sizeof("code") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->code,
                                     this->code ? strlen(this->code) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "usage_count",
                                  sizeof("usage_count") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->usage_count)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "creator_id",
                                  sizeof("creator_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->creator_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "creator",
                                  sizeof("creator") - 1)))
            return code;
        if (0 > (code = discord_user_to_jsonb(b, buf, size, this->creator)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "created_at",
                                  sizeof("created_at") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen =
                cog_unix_ms_to_iso8601(tok, sizeof(tok), this->created_at);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "updated_at",
                                  sizeof("updated_at") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen =
                cog_unix_ms_to_iso8601(tok, sizeof(tok), this->updated_at);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "source_guild_id",
                                  sizeof("source_guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->source_guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "serialized_source_guild",
                                  sizeof("serialized_source_guild") - 1)))
            return code;
        if (0 > (code = discord_guild_to_jsonb(b, buf, size,
                                               this->serialized_source_guild)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "is_dirty",
                                  sizeof("is_dirty") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->is_dirty))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_from_guild_template_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_from_guild_template *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->icon != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                         this->icon ? strlen(this->icon) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_template_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_template *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->description != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "description",
                                      sizeof("description") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->description,
                         this->description ? strlen(this->description) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_template_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_template *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->name != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->name,
                                         this->name ? strlen(this->name) : 0)))
                return code;
        }

        if (this->description != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "description",
                                      sizeof("description") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->description,
                         this->description ? strlen(this->description) : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_stage_instance_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_stage_instance *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "topic", sizeof("topic") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->topic,
                                     this->topic ? strlen(this->topic) : 0)))
            return code;

        if (this->privacy_level != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "privacy_level",
                                      sizeof("privacy_level") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->privacy_level)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "discoverable_disabled",
                                  sizeof("discoverable_disabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->discoverable_disabled)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_stage_instances_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_stage_instances *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_stage_instance_to_jsonb(b, buf, size,
                                                            &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_stage_instance_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_stage_instance *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "topic", sizeof("topic") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->topic,
                                     this->topic ? strlen(this->topic) : 0)))
            return code;

        if (this->privacy_level != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "privacy_level",
                                      sizeof("privacy_level") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->privacy_level)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_stage_instance_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_stage_instance *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "topic", sizeof("topic") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->topic,
                                     this->topic ? strlen(this->topic) : 0)))
            return code;

        if (this->privacy_level != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "privacy_level",
                                      sizeof("privacy_level") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->privacy_level)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_sticker_to_jsonb(jsonb *b,
                         char buf[],
                         size_t size,
                         const struct discord_sticker *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->pack_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "pack_id",
                                      sizeof("pack_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->pack_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "tags", sizeof("tags") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->tags,
                                     this->tags ? strlen(this->tags) : 0)))
            return code;

        if (this->type != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->type)))
                return code;
        }

        if (this->format_type != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "format_type",
                                      sizeof("format_type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->format_type)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "available",
                                  sizeof("available") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->available)))
            return code;

        if (this->guild_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                      sizeof("guild_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->user != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "sort_value",
                                  sizeof("sort_value") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->sort_value)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_stickers_to_jsonb(jsonb *b,
                          char buf[],
                          size_t size,
                          const struct discord_stickers *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_sticker_to_jsonb(b, buf, size,
                                                     &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_sticker_item_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_sticker_item *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->format_type != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "format_type",
                                      sizeof("format_type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->format_type)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_sticker_items_to_jsonb(jsonb *b,
                               char buf[],
                               size_t size,
                               const struct discord_sticker_items *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_sticker_item_to_jsonb(b, buf, size,
                                                          &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_sticker_pack_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_sticker_pack *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->stickers != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "stickers",
                                      sizeof("stickers") - 1)))
                return code;
            if (0 > (code = discord_stickers_to_jsonb(b, buf, size,
                                                      this->stickers)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "sku_id", sizeof("sku_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->sku_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->cover_sticker_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "cover_sticker_id",
                                      sizeof("cover_sticker_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen =
                    sprintf(tok, "\"%" PRIu64 "\"", this->cover_sticker_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->banner_asset_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "banner_asset_id",
                                      sizeof("banner_asset_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen =
                    sprintf(tok, "\"%" PRIu64 "\"", this->banner_asset_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_create_guild_sticker_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_sticker *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "tags", sizeof("tags") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->tags,
                                     this->tags ? strlen(this->tags) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "file", sizeof("file") - 1)))
            return code;
        if (0 > (code = discord_attachment_to_jsonb(b, buf, size, this->file)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_guild_sticker_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_guild_sticker *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "tags", sizeof("tags") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->tags,
                                     this->tags ? strlen(this->tags) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_user_to_jsonb(jsonb *b,
                      char buf[],
                      size_t size,
                      const struct discord_user *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "username",
                                  sizeof("username") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->username,
                                     this->username ? strlen(this->username)
                                                    : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "discriminator",
                                  sizeof("discriminator") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->discriminator,
                     this->discriminator ? strlen(this->discriminator) : 0)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "avatar", sizeof("avatar") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->avatar,
                                     this->avatar ? strlen(this->avatar) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "bot", sizeof("bot") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->bot))) return code;

        if (0
            > (code = jsonb_key(b, buf, size, "system", sizeof("system") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->System))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "mfa_enabled",
                                  sizeof("mfa_enabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->mfa_enabled)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "banner", sizeof("banner") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->banner,
                                     this->banner ? strlen(this->banner) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "accent_color",
                                  sizeof("accent_color") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->accent_color)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "locale", sizeof("locale") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->locale,
                                     this->locale ? strlen(this->locale) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "verified",
                                  sizeof("verified") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->verified))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "email", sizeof("email") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->email,
                                     this->email ? strlen(this->email) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "flags", sizeof("flags") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->flags);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "premium_type",
                                  sizeof("premium_type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->premium_type)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "public_flags",
                                  sizeof("public_flags") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->public_flags);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_users_to_jsonb(jsonb *b,
                       char buf[],
                       size_t size,
                       const struct discord_users *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code =
                         discord_user_to_jsonb(b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_connection_to_jsonb(jsonb *b,
                            char buf[],
                            size_t size,
                            const struct discord_connection *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->type,
                                     this->type ? strlen(this->type) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "revoked",
                                  sizeof("revoked") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->revoked))) return code;

        if (this->integrations != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "integrations",
                                      sizeof("integrations") - 1)))
                return code;
            if (0 > (code = discord_integrations_to_jsonb(b, buf, size,
                                                          this->integrations)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "verified",
                                  sizeof("verified") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->verified))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "friend_sync",
                                  sizeof("friend_sync") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->friend_sync)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "show_activity",
                                  sizeof("show_activity") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->show_activity)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "visibility",
                                  sizeof("visibility") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->visibility)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_connections_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_connections *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_connection_to_jsonb(b, buf, size,
                                                        &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_current_user_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_current_user *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->username != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "username",
                                      sizeof("username") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->username,
                         this->username ? strlen(this->username) : 0)))
                return code;
        }

        if (this->avatar != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "avatar",
                                      sizeof("avatar") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->avatar,
                                         this->avatar ? strlen(this->avatar)
                                                      : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_get_current_user_guilds_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_current_user_guilds *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->before != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "before",
                                      sizeof("before") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->before);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->after != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "after",
                                      sizeof("after") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->after);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (this->limit >= 1 && this->limit <= 200) {
            if (0 > (code = jsonb_key(b, buf, size, "limit",
                                      sizeof("limit") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->limit)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_dm_to_jsonb(jsonb *b,
                           char buf[],
                           size_t size,
                           const struct discord_create_dm *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->recipient_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "recipient_id",
                                      sizeof("recipient_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->recipient_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_group_dm_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_create_group_dm *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->access_tokens != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "access_tokens",
                                      sizeof("access_tokens") - 1)))
                return code;
            if (0 > (code = snowflakes_to_jsonb(b, buf, size,
                                                this->access_tokens)))
                return code;
        }

        if (this->nicks != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "nicks",
                                      sizeof("nicks") - 1)))
                return code;
            if (0 > (code = strings_to_jsonb(b, buf, size, this->nicks)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_voice_state_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_voice_state *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "user_id",
                                  sizeof("user_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->user_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0
            > (code = jsonb_key(b, buf, size, "member", sizeof("member") - 1)))
            return code;
        if (0 > (code = discord_guild_member_to_jsonb(b, buf, size,
                                                      this->member)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "session_id",
                                  sizeof("session_id") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->session_id,
                     this->session_id ? strlen(this->session_id) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "deaf", sizeof("deaf") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->deaf))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "mute", sizeof("mute") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->mute))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "self_deaf",
                                  sizeof("self_deaf") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->self_deaf)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "self_mute",
                                  sizeof("self_mute") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->self_mute)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "self_stream",
                                  sizeof("self_stream") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->self_stream)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "self_video",
                                  sizeof("self_video") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->self_video)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "suppress",
                                  sizeof("suppress") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->suppress))) return code;

        if (this->request_to_speak_timestamp) {
            if (0
                > (code = jsonb_key(b, buf, size, "request_to_speak_timestamp",
                                    sizeof("request_to_speak_timestamp") - 1)))
                return code;
            {
                char tok[64];
                int toklen;
                toklen = cog_unix_ms_to_iso8601(
                    tok, sizeof(tok), this->request_to_speak_timestamp);
                if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                    return code;
            };
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_voice_states_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_voice_states *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_voice_state_to_jsonb(b, buf, size,
                                                         &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_voice_region_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_voice_region *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->id,
                                     this->id ? strlen(this->id) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "optimal",
                                  sizeof("optimal") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->optimal))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "deprecated",
                                  sizeof("deprecated") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->deprecated)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "custom", sizeof("custom") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->custom))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_voice_regions_to_jsonb(jsonb *b,
                               char buf[],
                               size_t size,
                               const struct discord_voice_regions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_voice_region_to_jsonb(b, buf, size,
                                                          &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_webhook_to_jsonb(jsonb *b,
                         char buf[],
                         size_t size,
                         const struct discord_webhook *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->type != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->type)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->user != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "token", sizeof("token") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->token,
                                     this->token ? strlen(this->token) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "application_id",
                                  sizeof("application_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->application_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->source_channel != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "source_channel",
                                      sizeof("source_channel") - 1)))
                return code;
            if (0 > (code = discord_channel_to_jsonb(b, buf, size,
                                                     this->source_channel)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->url,
                                     this->url ? strlen(this->url) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_webhooks_to_jsonb(jsonb *b,
                          char buf[],
                          size_t size,
                          const struct discord_webhooks *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_webhook_to_jsonb(b, buf, size,
                                                     &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_webhook_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_create_webhook *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->avatar != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "avatar",
                                      sizeof("avatar") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->avatar,
                                         this->avatar ? strlen(this->avatar)
                                                      : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_webhook_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_modify_webhook *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->avatar != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "avatar",
                                      sizeof("avatar") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->avatar,
                                         this->avatar ? strlen(this->avatar)
                                                      : 0)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_modify_webhook_with_token_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_modify_webhook_with_token *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->avatar != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "avatar",
                                      sizeof("avatar") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->avatar,
                                         this->avatar ? strlen(this->avatar)
                                                      : 0)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_execute_webhook_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_execute_webhook *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "wait", sizeof("wait") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->wait))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "thread_id",
                                  sizeof("thread_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->thread_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "content",
                                  sizeof("content") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->content,
                                   this->content ? strlen(this->content) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "username",
                                  sizeof("username") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->username,
                                     this->username ? strlen(this->username)
                                                    : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "avatar_url",
                                  sizeof("avatar_url") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->avatar_url,
                     this->avatar_url ? strlen(this->avatar_url) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "tts", sizeof("tts") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->tts))) return code;

        if (this->embeds != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "embeds",
                                      sizeof("embeds") - 1)))
                return code;
            if (0
                > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
                return code;
        }

        if (this->allowed_mentions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "allowed_mentions",
                                      sizeof("allowed_mentions") - 1)))
                return code;
            if (0 > (code = discord_allowed_mention_to_jsonb(
                         b, buf, size, this->allowed_mentions)))
                return code;
        }

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (this->attachments != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                      sizeof("attachments") - 1)))
                return code;
            if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                         this->attachments)))
                return code;
        }

        if (this->flags != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "flags",
                                      sizeof("flags") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->flags);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_get_webhook_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_get_webhook_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->thread_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "thread_id",
                                      sizeof("thread_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->thread_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_edit_webhook_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_edit_webhook_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "thread_id",
                                  sizeof("thread_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->thread_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "content",
                                  sizeof("content") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->content,
                                   this->content ? strlen(this->content) : 0)))
            return code;

        if (this->embeds != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "embeds",
                                      sizeof("embeds") - 1)))
                return code;
            if (0
                > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
                return code;
        }

        if (this->allowed_mentions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "allowed_mentions",
                                      sizeof("allowed_mentions") - 1)))
                return code;
            if (0 > (code = discord_allowed_mention_to_jsonb(
                         b, buf, size, this->allowed_mentions)))
                return code;
        }

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (this->attachments != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                      sizeof("attachments") - 1)))
                return code;
            if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                         this->attachments)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_delete_webhook_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_delete_webhook_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->thread_id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "thread_id",
                                      sizeof("thread_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->thread_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_identify_to_jsonb(jsonb *b,
                          char buf[],
                          size_t size,
                          const struct discord_identify *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "token", sizeof("token") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->token,
                                     this->token ? strlen(this->token) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "properties",
                                  sizeof("properties") - 1)))
            return code;
        if (0 > (code = discord_identify_connection_to_jsonb(
                     b, buf, size, this->properties)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "compress",
                                  sizeof("compress") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->compress))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "large_threshold",
                                  sizeof("large_threshold") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->large_threshold)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "presence",
                                  sizeof("presence") - 1)))
            return code;
        if (0 > (code = discord_presence_update_to_jsonb(b, buf, size,
                                                         this->presence)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "intents",
                                  sizeof("intents") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->intents)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_identify_connection_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_identify_connection *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "$os", sizeof("$os") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->os,
                                     this->os ? strlen(this->os) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "$browser",
                                  sizeof("$browser") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->browser,
                                   this->browser ? strlen(this->browser) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "$device",
                                  sizeof("$device") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->device,
                                     this->device ? strlen(this->device) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_voice_state_status_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_voice_state_status *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "self_mute",
                                  sizeof("self_mute") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->self_mute)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "self_deaf",
                                  sizeof("self_deaf") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->self_deaf)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_presence_update_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_presence_update *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "since", sizeof("since") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), this->since);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "activities",
                                  sizeof("activities") - 1)))
            return code;
        if (0 > (code = discord_activities_to_jsonb(b, buf, size,
                                                    this->activities)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "status", sizeof("status") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->status,
                                     this->status ? strlen(this->status) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "afk", sizeof("afk") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->afk))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_presence_updates_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_presence_updates *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_presence_update_to_jsonb(b, buf, size,
                                                             &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activity_to_jsonb(jsonb *b,
                          char buf[],
                          size_t size,
                          const struct discord_activity *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->url,
                                     this->url ? strlen(this->url) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "created_at",
                                  sizeof("created_at") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen =
                cog_unix_ms_to_iso8601(tok, sizeof(tok), this->created_at);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "timestamps",
                                  sizeof("timestamps") - 1)))
            return code;
        if (0 > (code = discord_activity_timestamps_to_jsonb(
                     b, buf, size, this->timestamps)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "application_id",
                                  sizeof("application_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->application_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "details",
                                  sizeof("details") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->details,
                                   this->details ? strlen(this->details) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "state", sizeof("state") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->state,
                                     this->state ? strlen(this->state) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "emoji", sizeof("emoji") - 1)))
            return code;
        if (0 > (code = discord_activity_emoji_to_jsonb(b, buf, size,
                                                        this->emoji)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "party", sizeof("party") - 1)))
            return code;
        if (0 > (code = discord_activity_party_to_jsonb(b, buf, size,
                                                        this->party)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "assets", sizeof("assets") - 1)))
            return code;
        if (0 > (code = discord_activity_assets_to_jsonb(b, buf, size,
                                                         this->assets)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "secrets",
                                  sizeof("secrets") - 1)))
            return code;
        if (0 > (code = discord_activity_secrets_to_jsonb(b, buf, size,
                                                          this->secrets)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "instance",
                                  sizeof("instance") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->instance))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "flags", sizeof("flags") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->flags);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "buttons",
                                  sizeof("buttons") - 1)))
            return code;
        if (0 > (code = discord_activity_buttons_to_jsonb(b, buf, size,
                                                          this->buttons)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activities_to_jsonb(jsonb *b,
                            char buf[],
                            size_t size,
                            const struct discord_activities *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_activity_to_jsonb(b, buf, size,
                                                      &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activity_timestamps_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_activity_timestamps *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "start", sizeof("start") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), this->start);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };

        if (0 > (code = jsonb_key(b, buf, size, "end", sizeof("end") - 1)))
            return code;
        {
            char tok[64];
            int toklen;
            toklen = cog_unix_ms_to_iso8601(tok, sizeof(tok), this->end);
            if (0 > (code = jsonb_string(b, buf, size, tok, toklen)))
                return code;
        };
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activity_emoji_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_activity_emoji *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (this->id != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "animated",
                                  sizeof("animated") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->animated))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activity_party_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_activity_party *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->id,
                                     this->id ? strlen(this->id) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "size", sizeof("size") - 1)))
            return code;
        if (0 > (code = integers_to_jsonb(b, buf, size, this->size)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activity_assets_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_activity_assets *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "large_image",
                                  sizeof("large_image") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->large_image,
                     this->large_image ? strlen(this->large_image) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "large_text",
                                  sizeof("large_text") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->large_text,
                     this->large_text ? strlen(this->large_text) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "small_image",
                                  sizeof("small_image") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->small_image,
                     this->small_image ? strlen(this->small_image) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "small_text",
                                  sizeof("small_text") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->small_text,
                     this->small_text ? strlen(this->small_text) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activity_secrets_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_activity_secrets *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "join", sizeof("join") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->join,
                                     this->join ? strlen(this->join) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "spectate",
                                  sizeof("spectate") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->spectate,
                                     this->spectate ? strlen(this->spectate)
                                                    : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "match", sizeof("match") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->match,
                                     this->match ? strlen(this->match) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activity_button_to_jsonb(jsonb *b,
                                 char buf[],
                                 size_t size,
                                 const struct discord_activity_button *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "label", sizeof("label") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->label,
                                     this->label ? strlen(this->label) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->url,
                                     this->url ? strlen(this->url) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_activity_buttons_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_activity_buttons *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_activity_button_to_jsonb(b, buf, size,
                                                             &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_session_start_limit_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_session_start_limit *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "total", sizeof("total") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->total))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "remaining",
                                  sizeof("remaining") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->remaining)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "reset_after",
                                  sizeof("reset_after") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->reset_after)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "max_concurrency",
                                  sizeof("max_concurrency") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->max_concurrency)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_team_to_jsonb(jsonb *b,
                      char buf[],
                      size_t size,
                      const struct discord_team *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "icon", sizeof("icon") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->icon,
                                     this->icon ? strlen(this->icon) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->members != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "members",
                                      sizeof("members") - 1)))
                return code;
            if (0 > (code = discord_team_members_to_jsonb(b, buf, size,
                                                          this->members)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "owner_user_id",
                                  sizeof("owner_user_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->owner_user_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_team_member_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_team_member *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "membership_state",
                                  sizeof("membership_state") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->membership_state)))
            return code;

        if (this->permissions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                      sizeof("permissions") - 1)))
                return code;
            if (0 > (code = strings_to_jsonb(b, buf, size, this->permissions)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "team_id",
                                  sizeof("team_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->team_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->user != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
                return code;
            if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_team_members_to_jsonb(jsonb *b,
                              char buf[],
                              size_t size,
                              const struct discord_team_members *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_team_member_to_jsonb(b, buf, size,
                                                         &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_application_command_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (this->type != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->type)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "application_id",
                                  sizeof("application_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->application_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
        if (this->guild_id != 0) {

            if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                      sizeof("guild_id") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0 > (code = discord_application_command_options_to_jsonb(
                         b, buf, size, this->options)))
                return code;
        }

        if (this->default_permission != true) {
            if (0 > (code = jsonb_key(b, buf, size, "default_permission",
                                      sizeof("default_permission") - 1)))
                return code;
            if (0
                > (code = jsonb_bool(b, buf, size, this->default_permission)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "version",
                                  sizeof("version") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->version);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_application_commands_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_commands *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_application_command_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_application_command_option_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_option *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->required != false) {
            if (0 > (code = jsonb_key(b, buf, size, "required",
                                      sizeof("required") - 1)))
                return code;
            if (0 > (code = jsonb_bool(b, buf, size, this->required)))
                return code;
        }

        if (this->choices != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "choices",
                                      sizeof("choices") - 1)))
                return code;
            if (0
                > (code = discord_application_command_option_choices_to_jsonb(
                       b, buf, size, this->choices)))
                return code;
        }

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0 > (code = discord_application_command_options_to_jsonb(
                         b, buf, size, this->options)))
                return code;
        }

        if (this->channel_types != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "channel_types",
                                      sizeof("channel_types") - 1)))
                return code;
            if (0 > (code =
                         integers_to_jsonb(b, buf, size, this->channel_types)))
                return code;
        }

        if (this->min_value != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "min_value",
                                      sizeof("min_value") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->min_value,
                         this->min_value ? strlen(this->min_value) : 0)))
                return code;
        }

        if (this->max_value != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "max_value",
                                      sizeof("max_value") - 1)))
                return code;
            if (0 > (code = jsonb_string(
                         b, buf, size, this->max_value,
                         this->max_value ? strlen(this->max_value) : 0)))
                return code;
        }

        if (this->choices == NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "autocomplete",
                                      sizeof("autocomplete") - 1)))
                return code;
            if (0 > (code = jsonb_bool(b, buf, size, this->autocomplete)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_application_command_options_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_options *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_application_command_option_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_application_command_option_choice_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_option_choice *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "value", sizeof("value") - 1)))
            return code;
        if (0 > (code = jsonb_token(b, buf, size, this->value,
                                    strlen(this->value))))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_application_command_option_choices_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_option_choices *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_application_command_option_choice_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_application_command_interaction_data_option_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_interaction_data_option *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (this->value != NULL && *this->value != '\0') {
            if (0 > (code = jsonb_key(b, buf, size, "value",
                                      sizeof("value") - 1)))
                return code;
            if (0 > (code = jsonb_token(b, buf, size, this->value,
                                        strlen(this->value))))
                return code;
        }

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0
                > (code =
                       discord_application_command_interaction_data_options_to_jsonb(
                           b, buf, size, this->options)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "focused",
                                  sizeof("focused") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->focused))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_application_command_interaction_data_options_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_interaction_data_options *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0
                > (code =
                       discord_application_command_interaction_data_option_to_jsonb(
                           b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_guild_application_command_permission_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_application_command_permission *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "application_id",
                                  sizeof("application_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->application_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                  sizeof("permissions") - 1)))
            return code;
        if (0 > (code = discord_application_command_permissions_to_jsonb(
                     b, buf, size, this->permissions)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_guild_application_command_permissions_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_guild_application_command_permissions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code =
                         discord_guild_application_command_permission_to_jsonb(
                             b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_application_command_permission_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_permission *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "permission",
                                  sizeof("permission") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->permission)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_application_command_permissions_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_application_command_permissions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_application_command_permission_to_jsonb(
                         b, buf, size, &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_global_application_command_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_global_application_command *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0 > (code = discord_application_command_options_to_jsonb(
                         b, buf, size, this->options)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "default_permission",
                                  sizeof("default_permission") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->default_permission)))
            return code;

        if (this->type != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->type)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_edit_global_application_command_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_edit_global_application_command *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0 > (code = discord_application_command_options_to_jsonb(
                         b, buf, size, this->options)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "default_permission",
                                  sizeof("default_permission") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->default_permission)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_guild_application_command_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_guild_application_command *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0 > (code = discord_application_command_options_to_jsonb(
                         b, buf, size, this->options)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "default_permission",
                                  sizeof("default_permission") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->default_permission)))
            return code;

        if (this->type != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->type)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_edit_guild_application_command_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_edit_guild_application_command *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0 > (code = discord_application_command_options_to_jsonb(
                         b, buf, size, this->options)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "default_permission",
                                  sizeof("default_permission") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->default_permission)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_edit_application_command_permissions_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_edit_application_command_permissions *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->permissions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "permissions",
                                      sizeof("permissions") - 1)))
                return code;
            if (0 > (code = discord_application_command_permissions_to_jsonb(
                         b, buf, size, this->permissions)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_component_to_jsonb(jsonb *b,
                           char buf[],
                           size_t size,
                           const struct discord_component *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->type != 0) {
            if (0
                > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->type)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "custom_id",
                                  sizeof("custom_id") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->custom_id,
                                     this->custom_id ? strlen(this->custom_id)
                                                     : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "disabled",
                                  sizeof("disabled") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->disabled))) return code;

        if (this->style != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "style",
                                      sizeof("style") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->style)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "label", sizeof("label") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->label,
                                     this->label ? strlen(this->label) : 0)))
            return code;

        if (this->emoji != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "emoji",
                                      sizeof("emoji") - 1)))
                return code;
            if (0 > (code = discord_emoji_to_jsonb(b, buf, size, this->emoji)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "url", sizeof("url") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->url,
                                     this->url ? strlen(this->url) : 0)))
            return code;

        if (this->options != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "options",
                                      sizeof("options") - 1)))
                return code;
            if (0 > (code = discord_select_options_to_jsonb(b, buf, size,
                                                            this->options)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "placeholder",
                                  sizeof("placeholder") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->placeholder,
                     this->placeholder ? strlen(this->placeholder) : 0)))
            return code;

        if (this->min_values >= 0 && this->max_values <= 25) {
            if (0 > (code = jsonb_key(b, buf, size, "min_values",
                                      sizeof("min_values") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->min_values)))
                return code;
        }

        if (this->max_values <= 25) {
            if (0 > (code = jsonb_key(b, buf, size, "max_values",
                                      sizeof("max_values") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->max_values)))
                return code;
        }

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "min_length",
                                  sizeof("min_length") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->min_length)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "max_length",
                                  sizeof("max_length") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->max_length)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "required",
                                  sizeof("required") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->required))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "value", sizeof("value") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->value,
                                     this->value ? strlen(this->value) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_components_to_jsonb(jsonb *b,
                            char buf[],
                            size_t size,
                            const struct discord_components *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_component_to_jsonb(b, buf, size,
                                                       &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_select_option_to_jsonb(jsonb *b,
                               char buf[],
                               size_t size,
                               const struct discord_select_option *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "label", sizeof("label") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->label,
                                     this->label ? strlen(this->label) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "value", sizeof("value") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->value,
                                     this->value ? strlen(this->value) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "description",
                                  sizeof("description") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->description,
                     this->description ? strlen(this->description) : 0)))
            return code;

        if (this->emoji != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "emoji",
                                      sizeof("emoji") - 1)))
                return code;
            if (0 > (code = discord_emoji_to_jsonb(b, buf, size, this->emoji)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "default",
                                  sizeof("default") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->Default))) return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_select_options_to_jsonb(jsonb *b,
                                char buf[],
                                size_t size,
                                const struct discord_select_options *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_array(b, buf, size))) return code;
    if (this != NULL) {
        int i;
        for (i = 0; i < this->size; ++i)
            if (0 > (code = discord_select_option_to_jsonb(b, buf, size,
                                                           &this->array[i])))
                return code;
    }
    if (0 > (code = jsonb_array_pop(b, buf, size))) return code;
    return code;
}

jsonbcode
discord_interaction_to_jsonb(jsonb *b,
                             char buf[],
                             size_t size,
                             const struct discord_interaction *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "application_id",
                                  sizeof("application_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->application_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "data", sizeof("data") - 1)))
            return code;
        if (0 > (code = discord_interaction_data_to_jsonb(b, buf, size,
                                                          this->data)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "guild_id",
                                  sizeof("guild_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->guild_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "channel_id",
                                  sizeof("channel_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->channel_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0
            > (code = jsonb_key(b, buf, size, "member", sizeof("member") - 1)))
            return code;
        if (0 > (code = discord_guild_member_to_jsonb(b, buf, size,
                                                      this->member)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
            return code;
        if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "token", sizeof("token") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->token,
                                     this->token ? strlen(this->token) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "version",
                                  sizeof("version") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->version)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "message",
                                  sizeof("message") - 1)))
            return code;
        if (0 > (code = discord_message_to_jsonb(b, buf, size, this->message)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "locale", sizeof("locale") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->locale,
                                     this->locale ? strlen(this->locale) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "guild_locale",
                                  sizeof("guild_locale") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->guild_locale,
                     this->guild_locale ? strlen(this->guild_locale) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_interaction_data_to_jsonb(jsonb *b,
                                  char buf[],
                                  size_t size,
                                  const struct discord_interaction_data *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "resolved",
                                  sizeof("resolved") - 1)))
            return code;
        if (0 > (code = discord_resolved_data_to_jsonb(b, buf, size,
                                                       this->resolved)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "options",
                                  sizeof("options") - 1)))
            return code;
        if (0
            > (code =
                   discord_application_command_interaction_data_options_to_jsonb(
                       b, buf, size, this->options)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "custom_id",
                                  sizeof("custom_id") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->custom_id,
                                     this->custom_id ? strlen(this->custom_id)
                                                     : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "component_type",
                                  sizeof("component_type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->component_type)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "values", sizeof("values") - 1)))
            return code;
        if (0 > (code = strings_to_jsonb(b, buf, size, this->values)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "target_id",
                                  sizeof("target_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->target_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "components",
                                  sizeof("components") - 1)))
            return code;
        if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                    this->components)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_resolved_data_to_jsonb(jsonb *b,
                               char buf[],
                               size_t size,
                               const struct discord_resolved_data *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "users", sizeof("users") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->users)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "members",
                                  sizeof("members") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->members)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "roles", sizeof("roles") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->roles)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "channels",
                                  sizeof("channels") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->channels)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "messages",
                                  sizeof("messages") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->messages)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                  sizeof("attachments") - 1)))
            return code;
        if (0 > (code = snowflakes_to_jsonb(b, buf, size, this->attachments)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_message_interaction_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_message_interaction *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "id", sizeof("id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "name", sizeof("name") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->name,
                                     this->name ? strlen(this->name) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "user", sizeof("user") - 1)))
            return code;
        if (0 > (code = discord_user_to_jsonb(b, buf, size, this->user)))
            return code;

        if (0
            > (code = jsonb_key(b, buf, size, "member", sizeof("member") - 1)))
            return code;
        if (0 > (code = discord_guild_member_to_jsonb(b, buf, size,
                                                      this->member)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_interaction_response_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_interaction_response *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "type", sizeof("type") - 1)))
            return code;
        if (0 > (code = jsonb_number(b, buf, size, this->type))) return code;

        if (this->data != NULL) {
            if (0
                > (code = jsonb_key(b, buf, size, "data", sizeof("data") - 1)))
                return code;
            if (0 > (code = discord_interaction_callback_data_to_jsonb(
                         b, buf, size, this->data)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
static jsonbcode
discord_interaction_callback_data_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_interaction_callback_data *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (this->tts != false) {
            if (0 > (code = jsonb_key(b, buf, size, "tts", sizeof("tts") - 1)))
                return code;
            if (0 > (code = jsonb_bool(b, buf, size, this->tts))) return code;
        }

        if (this->content != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "content",
                                      sizeof("content") - 1)))
                return code;
            if (0 > (code = jsonb_string(b, buf, size, this->content,
                                         this->content ? strlen(this->content)
                                                       : 0)))
                return code;
        }

        if (this->embeds != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "embeds",
                                      sizeof("embeds") - 1)))
                return code;
            if (0
                > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
                return code;
        }

        if (this->flags != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "flags",
                                      sizeof("flags") - 1)))
                return code;
            if (0 > (code = jsonb_number(b, buf, size, this->flags)))
                return code;
        }

        if (this->attachments != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                      sizeof("attachments") - 1)))
                return code;
            if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                         this->attachments)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "choices",
                                  sizeof("choices") - 1)))
            return code;
        if (0 > (code = discord_application_command_option_choices_to_jsonb(
                     b, buf, size, this->choices)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "custom_id",
                                  sizeof("custom_id") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->custom_id,
                                     this->custom_id ? strlen(this->custom_id)
                                                     : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "title", sizeof("title") - 1)))
            return code;
        if (0 > (code = jsonb_string(b, buf, size, this->title,
                                     this->title ? strlen(this->title) : 0)))
            return code;
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_edit_original_interaction_response_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_edit_original_interaction_response *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "thread_id",
                                  sizeof("thread_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->thread_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "content",
                                  sizeof("content") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->content,
                                   this->content ? strlen(this->content) : 0)))
            return code;

        if (this->embeds != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "embeds",
                                      sizeof("embeds") - 1)))
                return code;
            if (0
                > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
                return code;
        }

        if (this->allowed_mentions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "allowed_mentions",
                                      sizeof("allowed_mentions") - 1)))
                return code;
            if (0 > (code = discord_allowed_mention_to_jsonb(
                         b, buf, size, this->allowed_mentions)))
                return code;
        }

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (this->attachments != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                      sizeof("attachments") - 1)))
                return code;
            if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                         this->attachments)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_create_followup_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_create_followup_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "wait", sizeof("wait") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->wait))) return code;

        if (0 > (code = jsonb_key(b, buf, size, "thread_id",
                                  sizeof("thread_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->thread_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "avatar_url",
                                  sizeof("avatar_url") - 1)))
            return code;
        if (0 > (code = jsonb_string(
                     b, buf, size, this->avatar_url,
                     this->avatar_url ? strlen(this->avatar_url) : 0)))
            return code;

        if (0 > (code = jsonb_key(b, buf, size, "tts", sizeof("tts") - 1)))
            return code;
        if (0 > (code = jsonb_bool(b, buf, size, this->tts))) return code;

        if (this->embeds != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "embeds",
                                      sizeof("embeds") - 1)))
                return code;
            if (0
                > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
                return code;
        }

        if (this->allowed_mentions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "allowed_mentions",
                                      sizeof("allowed_mentions") - 1)))
                return code;
            if (0 > (code = discord_allowed_mention_to_jsonb(
                         b, buf, size, this->allowed_mentions)))
                return code;
        }

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (this->attachments != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                      sizeof("attachments") - 1)))
                return code;
            if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                         this->attachments)))
                return code;
        }

        if (this->flags != 0) {
            if (0 > (code = jsonb_key(b, buf, size, "flags",
                                      sizeof("flags") - 1)))
                return code;
            else {
                char tok[64];
                int toklen;
                toklen = sprintf(tok, "\"%" PRIu64 "\"", this->flags);
                if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                    return code;
            }
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
jsonbcode
discord_edit_followup_message_to_jsonb(
    jsonb *b,
    char buf[],
    size_t size,
    const struct discord_edit_followup_message *this)
{
    jsonbcode code;
    if (0 > (code = jsonb_object(b, buf, size))) return code;
    if (this != NULL) {

        if (0 > (code = jsonb_key(b, buf, size, "thread_id",
                                  sizeof("thread_id") - 1)))
            return code;
        else {
            char tok[64];
            int toklen;
            toklen = sprintf(tok, "\"%" PRIu64 "\"", this->thread_id);
            if (0 > (code = jsonb_token(b, buf, size, tok, toklen)))
                return code;
        }

        if (0 > (code = jsonb_key(b, buf, size, "content",
                                  sizeof("content") - 1)))
            return code;
        if (0
            > (code = jsonb_string(b, buf, size, this->content,
                                   this->content ? strlen(this->content) : 0)))
            return code;

        if (this->embeds != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "embeds",
                                      sizeof("embeds") - 1)))
                return code;
            if (0
                > (code = discord_embeds_to_jsonb(b, buf, size, this->embeds)))
                return code;
        }

        if (this->allowed_mentions != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "allowed_mentions",
                                      sizeof("allowed_mentions") - 1)))
                return code;
            if (0 > (code = discord_allowed_mention_to_jsonb(
                         b, buf, size, this->allowed_mentions)))
                return code;
        }

        if (this->components != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "components",
                                      sizeof("components") - 1)))
                return code;
            if (0 > (code = discord_components_to_jsonb(b, buf, size,
                                                        this->components)))
                return code;
        }

        if (this->attachments != NULL) {
            if (0 > (code = jsonb_key(b, buf, size, "attachments",
                                      sizeof("attachments") - 1)))
                return code;
            if (0 > (code = discord_attachments_to_jsonb(b, buf, size,
                                                         this->attachments)))
                return code;
        }
    }
    if (0 > (code = jsonb_object_pop(b, buf, size))) return code;
    return code;
}
size_t
strings_to_json(char buf[], size_t size, const struct strings *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = strings_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
json_values_to_json(char buf[], size_t size, const struct json_values *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = json_values_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
snowflakes_to_json(char buf[], size_t size, const struct snowflakes *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = snowflakes_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
integers_to_json(char buf[], size_t size, const struct integers *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = integers_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_role_to_json(char buf[], size_t size, const struct discord_role *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_role_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_roles_to_json(char buf[],
                      size_t size,
                      const struct discord_roles *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_roles_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_application_to_json(char buf[],
                            size_t size,
                            const struct discord_application *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_application_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_audit_log_to_json(char buf[],
                          size_t size,
                          const struct discord_audit_log *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_audit_log_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_invite_to_json(char buf[],
                       size_t size,
                       const struct discord_invite *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_invite_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_invites_to_json(char buf[],
                        size_t size,
                        const struct discord_invites *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_invites_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_get_invite_to_json(char buf[],
                           size_t size,
                           const struct discord_get_invite *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_get_invite_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_channel_to_json(char buf[],
                        size_t size,
                        const struct discord_channel *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_channel_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_channels_to_json(char buf[],
                         size_t size,
                         const struct discord_channels *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_channels_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_message_to_json(char buf[],
                        size_t size,
                        const struct discord_message *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_message_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_messages_to_json(char buf[],
                         size_t size,
                         const struct discord_messages *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_messages_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_followed_channel_to_json(char buf[],
                                 size_t size,
                                 const struct discord_followed_channel *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_followed_channel_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_thread_members_to_json(char buf[],
                               size_t size,
                               const struct discord_thread_members *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_thread_members_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_attachments_to_json(char buf[],
                            size_t size,
                            const struct discord_attachments *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_attachments_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_to_json(char buf[],
                      size_t size,
                      const struct discord_embed *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embeds_to_json(char buf[],
                       size_t size,
                       const struct discord_embeds *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embeds_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_thumbnail_to_json(char buf[],
                                size_t size,
                                const struct discord_embed_thumbnail *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_thumbnail_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_video_to_json(char buf[],
                            size_t size,
                            const struct discord_embed_video *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_video_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_image_to_json(char buf[],
                            size_t size,
                            const struct discord_embed_image *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_image_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_provider_to_json(char buf[],
                               size_t size,
                               const struct discord_embed_provider *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_provider_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_author_to_json(char buf[],
                             size_t size,
                             const struct discord_embed_author *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_author_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_footer_to_json(char buf[],
                             size_t size,
                             const struct discord_embed_footer *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_footer_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_field_to_json(char buf[],
                            size_t size,
                            const struct discord_embed_field *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_field_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_embed_fields_to_json(char buf[],
                             size_t size,
                             const struct discord_embed_fields *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_embed_fields_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_thread_response_body_to_json(
    char buf[], size_t size, const struct discord_thread_response_body *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_thread_response_body_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_channel_to_json(char buf[],
                               size_t size,
                               const struct discord_modify_channel *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_channel_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_get_channel_messages_to_json(
    char buf[], size_t size, const struct discord_get_channel_messages *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_get_channel_messages_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_message_to_json(char buf[],
                               size_t size,
                               const struct discord_create_message *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_message_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_get_reactions_to_json(char buf[],
                              size_t size,
                              const struct discord_get_reactions *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_get_reactions_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_edit_message_to_json(char buf[],
                             size_t size,
                             const struct discord_edit_message *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_edit_message_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_bulk_delete_messages_to_json(
    char buf[], size_t size, const struct discord_bulk_delete_messages *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_bulk_delete_messages_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_edit_channel_permissions_to_json(
    char buf[],
    size_t size,
    const struct discord_edit_channel_permissions *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_edit_channel_permissions_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_channel_invite_to_json(
    char buf[], size_t size, const struct discord_create_channel_invite *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_channel_invite_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_follow_news_channel_to_json(
    char buf[], size_t size, const struct discord_follow_news_channel *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_follow_news_channel_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_group_dm_add_recipient_to_json(
    char buf[], size_t size, const struct discord_group_dm_add_recipient *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_group_dm_add_recipient_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_start_thread_with_message_to_json(
    char buf[],
    size_t size,
    const struct discord_start_thread_with_message *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_start_thread_with_message_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_start_thread_without_message_to_json(
    char buf[],
    size_t size,
    const struct discord_start_thread_without_message *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_start_thread_without_message_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_list_active_threads_to_json(
    char buf[], size_t size, const struct discord_list_active_threads *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_list_active_threads_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_emoji_to_json(char buf[],
                      size_t size,
                      const struct discord_emoji *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_emoji_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_emojis_to_json(char buf[],
                       size_t size,
                       const struct discord_emojis *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_emojis_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_emoji_to_json(
    char buf[], size_t size, const struct discord_create_guild_emoji *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_guild_emoji_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_emoji_to_json(
    char buf[], size_t size, const struct discord_modify_guild_emoji *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_emoji_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guild_to_json(char buf[],
                      size_t size,
                      const struct discord_guild *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guild_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guilds_to_json(char buf[],
                       size_t size,
                       const struct discord_guilds *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guilds_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guild_preview_to_json(char buf[],
                              size_t size,
                              const struct discord_guild_preview *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guild_preview_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guild_member_to_json(char buf[],
                             size_t size,
                             const struct discord_guild_member *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guild_member_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guild_members_to_json(char buf[],
                              size_t size,
                              const struct discord_guild_members *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guild_members_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_ban_to_json(char buf[], size_t size, const struct discord_ban *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_ban_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_bans_to_json(char buf[], size_t size, const struct discord_bans *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_bans_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_welcome_screen_to_json(char buf[],
                               size_t size,
                               const struct discord_welcome_screen *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_welcome_screen_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_to_json(char buf[],
                             size_t size,
                             const struct discord_create_guild *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_guild_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_to_json(char buf[],
                             size_t size,
                             const struct discord_modify_guild *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_channel_to_json(
    char buf[], size_t size, const struct discord_create_guild_channel *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_guild_channel_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_channel_positions_to_json(
    char buf[],
    size_t size,
    const struct discord_modify_guild_channel_positions *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_modify_guild_channel_positions_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_list_active_guild_threads_to_json(
    char buf[],
    size_t size,
    const struct discord_list_active_guild_threads *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_list_active_guild_threads_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_add_guild_member_to_json(char buf[],
                                 size_t size,
                                 const struct discord_add_guild_member *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_add_guild_member_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_member_to_json(
    char buf[], size_t size, const struct discord_modify_guild_member *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_member_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_current_member_to_json(
    char buf[], size_t size, const struct discord_modify_current_member *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_current_member_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_current_user_nick_to_json(
    char buf[],
    size_t size,
    const struct discord_modify_current_user_nick *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_current_user_nick_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_ban_to_json(char buf[],
                                 size_t size,
                                 const struct discord_create_guild_ban *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_guild_ban_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_role_to_json(char buf[],
                                  size_t size,
                                  const struct discord_create_guild_role *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_guild_role_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_role_positions_to_json(
    char buf[],
    size_t size,
    const struct discord_modify_guild_role_positions *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_role_positions_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_role_to_json(char buf[],
                                  size_t size,
                                  const struct discord_modify_guild_role *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_role_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_begin_guild_prune_to_json(char buf[],
                                  size_t size,
                                  const struct discord_begin_guild_prune *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_begin_guild_prune_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_welcome_screen_to_json(
    char buf[],
    size_t size,
    const struct discord_modify_guild_welcome_screen *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_welcome_screen_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_current_user_voice_state_to_json(
    char buf[],
    size_t size,
    const struct discord_modify_current_user_voice_state *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_modify_current_user_voice_state_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_user_voice_state_to_json(
    char buf[],
    size_t size,
    const struct discord_modify_user_voice_state *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_user_voice_state_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guild_scheduled_event_to_json(
    char buf[], size_t size, const struct discord_guild_scheduled_event *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guild_scheduled_event_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guild_scheduled_events_to_json(
    char buf[], size_t size, const struct discord_guild_scheduled_events *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guild_scheduled_events_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_list_scheduled_events_for_guild_to_json(
    char buf[],
    size_t size,
    const struct discord_list_scheduled_events_for_guild *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_list_scheduled_events_for_guild_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_scheduled_event_to_json(
    char buf[],
    size_t size,
    const struct discord_create_guild_scheduled_event *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_guild_scheduled_event_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_get_guild_scheduled_event_to_json(
    char buf[],
    size_t size,
    const struct discord_get_guild_scheduled_event *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_get_guild_scheduled_event_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_scheduled_event_to_json(
    char buf[],
    size_t size,
    const struct discord_modify_guild_scheduled_event *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_scheduled_event_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_get_guild_scheduled_event_users_to_json(
    char buf[],
    size_t size,
    const struct discord_get_guild_scheduled_event_users *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_get_guild_scheduled_event_users_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guild_template_to_json(char buf[],
                               size_t size,
                               const struct discord_guild_template *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guild_template_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_from_guild_template_to_json(
    char buf[],
    size_t size,
    const struct discord_create_guild_from_guild_template *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_create_guild_from_guild_template_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_template_to_json(
    char buf[], size_t size, const struct discord_create_guild_template *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_guild_template_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_template_to_json(
    char buf[], size_t size, const struct discord_modify_guild_template *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_template_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_stage_instance_to_json(char buf[],
                               size_t size,
                               const struct discord_stage_instance *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_stage_instance_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_stage_instance_to_json(
    char buf[], size_t size, const struct discord_create_stage_instance *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_stage_instance_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_stage_instance_to_json(
    char buf[], size_t size, const struct discord_modify_stage_instance *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_stage_instance_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_sticker_to_json(char buf[],
                        size_t size,
                        const struct discord_sticker *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_sticker_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_guild_sticker_to_json(
    char buf[], size_t size, const struct discord_modify_guild_sticker *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_guild_sticker_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_user_to_json(char buf[], size_t size, const struct discord_user *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_user_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_users_to_json(char buf[],
                      size_t size,
                      const struct discord_users *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_users_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_connections_to_json(char buf[],
                            size_t size,
                            const struct discord_connections *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_connections_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_current_user_to_json(
    char buf[], size_t size, const struct discord_modify_current_user *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_current_user_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_dm_to_json(char buf[],
                          size_t size,
                          const struct discord_create_dm *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_dm_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_group_dm_to_json(char buf[],
                                size_t size,
                                const struct discord_create_group_dm *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_group_dm_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_voice_state_to_json(char buf[],
                            size_t size,
                            const struct discord_voice_state *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_voice_state_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_voice_states_to_json(char buf[],
                             size_t size,
                             const struct discord_voice_states *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_voice_states_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_voice_regions_to_json(char buf[],
                              size_t size,
                              const struct discord_voice_regions *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_voice_regions_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_webhook_to_json(char buf[],
                        size_t size,
                        const struct discord_webhook *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_webhook_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_webhooks_to_json(char buf[],
                         size_t size,
                         const struct discord_webhooks *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_webhooks_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_webhook_to_json(char buf[],
                               size_t size,
                               const struct discord_create_webhook *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_webhook_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_webhook_to_json(char buf[],
                               size_t size,
                               const struct discord_modify_webhook *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_webhook_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_modify_webhook_with_token_to_json(
    char buf[],
    size_t size,
    const struct discord_modify_webhook_with_token *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_modify_webhook_with_token_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_execute_webhook_to_json(char buf[],
                                size_t size,
                                const struct discord_execute_webhook *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_execute_webhook_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_edit_webhook_message_to_json(
    char buf[], size_t size, const struct discord_edit_webhook_message *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_edit_webhook_message_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_identify_to_json(char buf[],
                         size_t size,
                         const struct discord_identify *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_identify_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_voice_state_status_to_json(
    char buf[], size_t size, const struct discord_voice_state_status *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_voice_state_status_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_presence_update_to_json(char buf[],
                                size_t size,
                                const struct discord_presence_update *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_presence_update_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_session_start_limit_to_json(
    char buf[], size_t size, const struct discord_session_start_limit *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_session_start_limit_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_team_to_json(char buf[], size_t size, const struct discord_team *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_team_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_application_command_to_json(
    char buf[], size_t size, const struct discord_application_command *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_application_command_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_application_commands_to_json(
    char buf[], size_t size, const struct discord_application_commands *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_application_commands_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_guild_application_command_permissions_to_json(
    char buf[],
    size_t size,
    const struct discord_guild_application_command_permissions *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_guild_application_command_permissions_to_jsonb(&b, buf,
                                                                  size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_application_command_permission_to_json(
    char buf[],
    size_t size,
    const struct discord_application_command_permission *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_application_command_permission_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_application_command_permissions_to_json(
    char buf[],
    size_t size,
    const struct discord_application_command_permissions *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_application_command_permissions_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_global_application_command_to_json(
    char buf[],
    size_t size,
    const struct discord_create_global_application_command *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_global_application_command_to_jsonb(&b, buf, size,
                                                              this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_edit_global_application_command_to_json(
    char buf[],
    size_t size,
    const struct discord_edit_global_application_command *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_edit_global_application_command_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_guild_application_command_to_json(
    char buf[],
    size_t size,
    const struct discord_create_guild_application_command *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_create_guild_application_command_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_edit_guild_application_command_to_json(
    char buf[],
    size_t size,
    const struct discord_edit_guild_application_command *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code =
        discord_edit_guild_application_command_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_edit_application_command_permissions_to_json(
    char buf[],
    size_t size,
    const struct discord_edit_application_command_permissions *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_edit_application_command_permissions_to_jsonb(&b, buf, size,
                                                                 this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_component_to_json(char buf[],
                          size_t size,
                          const struct discord_component *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_component_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_components_to_json(char buf[],
                           size_t size,
                           const struct discord_components *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_components_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_select_options_to_json(char buf[],
                               size_t size,
                               const struct discord_select_options *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_select_options_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_interaction_to_json(char buf[],
                            size_t size,
                            const struct discord_interaction *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_interaction_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_interaction_response_to_json(
    char buf[], size_t size, const struct discord_interaction_response *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_interaction_response_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_edit_original_interaction_response_to_json(
    char buf[],
    size_t size,
    const struct discord_edit_original_interaction_response *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_edit_original_interaction_response_to_jsonb(&b, buf, size,
                                                               this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_create_followup_message_to_json(
    char buf[],
    size_t size,
    const struct discord_create_followup_message *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_create_followup_message_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}

size_t
discord_edit_followup_message_to_json(
    char buf[], size_t size, const struct discord_edit_followup_message *this)
{
    jsonb b;
    jsonbcode code;
    jsonb_init(&b);
    code = discord_edit_followup_message_to_jsonb(&b, buf, size, this);
    return code < 0 ? 0 : b.pos;
}
