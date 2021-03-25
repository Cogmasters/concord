/* This file is generated from specs/audit_log.json, Please don't edit it. */
/*
(null)
*/

extern void discord_audit_log_cleanup_v(void *p);
extern void discord_audit_log_cleanup(struct discord_audit_log *p);
extern void discord_audit_log_init_v(void *p);
extern void discord_audit_log_init(struct discord_audit_log *p);
extern struct discord_audit_log * discord_audit_log_alloc();
extern void discord_audit_log_free_v(void *p);
extern void discord_audit_log_free(struct discord_audit_log *p);
extern void discord_audit_log_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_from_json(char *json, size_t len, struct discord_audit_log *p);
extern size_t discord_audit_log_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_to_json(char *json, size_t len, struct discord_audit_log *p);
extern size_t discord_audit_log_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_to_query(char *json, size_t len, struct discord_audit_log *p);
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
extern struct discord_audit_log_entry * discord_audit_log_entry_alloc();
extern void discord_audit_log_entry_free_v(void *p);
extern void discord_audit_log_entry_free(struct discord_audit_log_entry *p);
extern void discord_audit_log_entry_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_entry_from_json(char *json, size_t len, struct discord_audit_log_entry *p);
extern size_t discord_audit_log_entry_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_to_json(char *json, size_t len, struct discord_audit_log_entry *p);
extern size_t discord_audit_log_entry_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_to_query(char *json, size_t len, struct discord_audit_log_entry *p);
extern void discord_audit_log_entry_list_free_v(void **p);
extern void discord_audit_log_entry_list_free(struct discord_audit_log_entry **p);
extern void discord_audit_log_entry_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_entry_list_from_json(char *str, size_t len, struct discord_audit_log_entry ***p);
extern size_t discord_audit_log_entry_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_entry_list_to_json(char *str, size_t len, struct discord_audit_log_entry **p);

extern void discord_audit_log_entry_optional_info_cleanup_v(void *p);
extern void discord_audit_log_entry_optional_info_cleanup(struct discord_audit_log_entry_optional_info *p);
extern void discord_audit_log_entry_optional_info_init_v(void *p);
extern void discord_audit_log_entry_optional_info_init(struct discord_audit_log_entry_optional_info *p);
extern struct discord_audit_log_entry_optional_info * discord_audit_log_entry_optional_info_alloc();
extern void discord_audit_log_entry_optional_info_free_v(void *p);
extern void discord_audit_log_entry_optional_info_free(struct discord_audit_log_entry_optional_info *p);
extern void discord_audit_log_entry_optional_info_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_entry_optional_info_from_json(char *json, size_t len, struct discord_audit_log_entry_optional_info *p);
extern size_t discord_audit_log_entry_optional_info_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_to_json(char *json, size_t len, struct discord_audit_log_entry_optional_info *p);
extern size_t discord_audit_log_entry_optional_info_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_to_query(char *json, size_t len, struct discord_audit_log_entry_optional_info *p);
extern void discord_audit_log_entry_optional_info_list_free_v(void **p);
extern void discord_audit_log_entry_optional_info_list_free(struct discord_audit_log_entry_optional_info **p);
extern void discord_audit_log_entry_optional_info_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_entry_optional_info_list_from_json(char *str, size_t len, struct discord_audit_log_entry_optional_info ***p);
extern size_t discord_audit_log_entry_optional_info_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_list_to_json(char *str, size_t len, struct discord_audit_log_entry_optional_info **p);

extern void discord_audit_log_change_cleanup_v(void *p);
extern void discord_audit_log_change_cleanup(struct discord_audit_log_change *p);
extern void discord_audit_log_change_init_v(void *p);
extern void discord_audit_log_change_init(struct discord_audit_log_change *p);
extern struct discord_audit_log_change * discord_audit_log_change_alloc();
extern void discord_audit_log_change_free_v(void *p);
extern void discord_audit_log_change_free(struct discord_audit_log_change *p);
extern void discord_audit_log_change_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_change_from_json(char *json, size_t len, struct discord_audit_log_change *p);
extern size_t discord_audit_log_change_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_to_json(char *json, size_t len, struct discord_audit_log_change *p);
extern size_t discord_audit_log_change_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_to_query(char *json, size_t len, struct discord_audit_log_change *p);
extern void discord_audit_log_change_list_free_v(void **p);
extern void discord_audit_log_change_list_free(struct discord_audit_log_change **p);
extern void discord_audit_log_change_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_list_from_json(char *str, size_t len, struct discord_audit_log_change ***p);
extern size_t discord_audit_log_change_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_list_to_json(char *str, size_t len, struct discord_audit_log_change **p);

extern void discord_audit_log_change_key_cleanup_v(void *p);
extern void discord_audit_log_change_key_cleanup(struct discord_audit_log_change_key *p);
extern void discord_audit_log_change_key_init_v(void *p);
extern void discord_audit_log_change_key_init(struct discord_audit_log_change_key *p);
extern struct discord_audit_log_change_key * discord_audit_log_change_key_alloc();
extern void discord_audit_log_change_key_free_v(void *p);
extern void discord_audit_log_change_key_free(struct discord_audit_log_change_key *p);
extern void discord_audit_log_change_key_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_change_key_from_json(char *json, size_t len, struct discord_audit_log_change_key *p);
extern size_t discord_audit_log_change_key_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_key_to_json(char *json, size_t len, struct discord_audit_log_change_key *p);
extern size_t discord_audit_log_change_key_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_key_to_query(char *json, size_t len, struct discord_audit_log_change_key *p);
extern void discord_audit_log_change_key_list_free_v(void **p);
extern void discord_audit_log_change_key_list_free(struct discord_audit_log_change_key **p);
extern void discord_audit_log_change_key_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_key_list_from_json(char *str, size_t len, struct discord_audit_log_change_key ***p);
extern size_t discord_audit_log_change_key_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_key_list_to_json(char *str, size_t len, struct discord_audit_log_change_key **p);
/* This file is generated from specs/channel.bulk-delete-messages.json, Please don't edit it. */
/*

*/

extern void discord_bulk_delete_messages_params_cleanup_v(void *p);
extern void discord_bulk_delete_messages_params_cleanup(struct discord_bulk_delete_messages_params *p);
extern void discord_bulk_delete_messages_params_init_v(void *p);
extern void discord_bulk_delete_messages_params_init(struct discord_bulk_delete_messages_params *p);
extern struct discord_bulk_delete_messages_params * discord_bulk_delete_messages_params_alloc();
extern void discord_bulk_delete_messages_params_free_v(void *p);
extern void discord_bulk_delete_messages_params_free(struct discord_bulk_delete_messages_params *p);
extern void discord_bulk_delete_messages_params_from_json_v(char *json, size_t len, void *p);
extern void discord_bulk_delete_messages_params_from_json(char *json, size_t len, struct discord_bulk_delete_messages_params *p);
extern size_t discord_bulk_delete_messages_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_bulk_delete_messages_params_to_json(char *json, size_t len, struct discord_bulk_delete_messages_params *p);
extern size_t discord_bulk_delete_messages_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_bulk_delete_messages_params_to_query(char *json, size_t len, struct discord_bulk_delete_messages_params *p);
extern void discord_bulk_delete_messages_params_list_free_v(void **p);
extern void discord_bulk_delete_messages_params_list_free(struct discord_bulk_delete_messages_params **p);
extern void discord_bulk_delete_messages_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_bulk_delete_messages_params_list_from_json(char *str, size_t len, struct discord_bulk_delete_messages_params ***p);
extern size_t discord_bulk_delete_messages_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_bulk_delete_messages_params_list_to_json(char *str, size_t len, struct discord_bulk_delete_messages_params **p);
/* This file is generated from specs/channel.create-channel-invite.json, Please don't edit it. */
/*

*/

extern void discord_create_channel_invite_params_cleanup_v(void *p);
extern void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_init_v(void *p);
extern void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p);
extern struct discord_create_channel_invite_params * discord_create_channel_invite_params_alloc();
extern void discord_create_channel_invite_params_free_v(void *p);
extern void discord_create_channel_invite_params_free(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern size_t discord_create_channel_invite_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern size_t discord_create_channel_invite_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_query(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_list_free_v(void **p);
extern void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **p);
extern void discord_create_channel_invite_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_channel_invite_params_list_from_json(char *str, size_t len, struct discord_create_channel_invite_params ***p);
extern size_t discord_create_channel_invite_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_channel_invite_params_list_to_json(char *str, size_t len, struct discord_create_channel_invite_params **p);
/* This file is generated from specs/channel.edit-channel-permissions.json, Please don't edit it. */
/*

*/

extern void discord_edit_channel_permissions_params_cleanup_v(void *p);
extern void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_init_v(void *p);
extern void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p);
extern struct discord_edit_channel_permissions_params * discord_edit_channel_permissions_params_alloc();
extern void discord_edit_channel_permissions_params_free_v(void *p);
extern void discord_edit_channel_permissions_params_free(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_from_json_v(char *json, size_t len, void *p);
extern void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern size_t discord_edit_channel_permissions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern size_t discord_edit_channel_permissions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_query(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_list_free_v(void **p);
extern void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **p);
extern void discord_edit_channel_permissions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_channel_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_channel_permissions_params ***p);
extern size_t discord_edit_channel_permissions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_channel_permissions_params **p);
/* This file is generated from specs/channel.follow-news-channel.json, Please don't edit it. */
/*

*/

extern void discord_follow_news_channel_params_cleanup_v(void *p);
extern void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_init_v(void *p);
extern void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p);
extern struct discord_follow_news_channel_params * discord_follow_news_channel_params_alloc();
extern void discord_follow_news_channel_params_free_v(void *p);
extern void discord_follow_news_channel_params_free(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_from_json_v(char *json, size_t len, void *p);
extern void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern size_t discord_follow_news_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_follow_news_channel_params_to_json(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern size_t discord_follow_news_channel_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_follow_news_channel_params_to_query(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_list_free_v(void **p);
extern void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **p);
extern void discord_follow_news_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_follow_news_channel_params_list_from_json(char *str, size_t len, struct discord_follow_news_channel_params ***p);
extern size_t discord_follow_news_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_follow_news_channel_params_list_to_json(char *str, size_t len, struct discord_follow_news_channel_params **p);
/* This file is generated from specs/channel.get-reactions.json, Please don't edit it. */
/*

*/

extern void discord_get_reactions_params_cleanup_v(void *p);
extern void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_init_v(void *p);
extern void discord_get_reactions_params_init(struct discord_get_reactions_params *p);
extern struct discord_get_reactions_params * discord_get_reactions_params_alloc();
extern void discord_get_reactions_params_free_v(void *p);
extern void discord_get_reactions_params_free(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_from_json_v(char *json, size_t len, void *p);
extern void discord_get_reactions_params_from_json(char *json, size_t len, struct discord_get_reactions_params *p);
extern size_t discord_get_reactions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_reactions_params_to_json(char *json, size_t len, struct discord_get_reactions_params *p);
extern size_t discord_get_reactions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_get_reactions_params_to_query(char *json, size_t len, struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_list_free_v(void **p);
extern void discord_get_reactions_params_list_free(struct discord_get_reactions_params **p);
extern void discord_get_reactions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_reactions_params_list_from_json(char *str, size_t len, struct discord_get_reactions_params ***p);
extern size_t discord_get_reactions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_reactions_params_list_to_json(char *str, size_t len, struct discord_get_reactions_params **p);
/* This file is generated from specs/channel.group-dm-add-recipient.json, Please don't edit it. */
/*

*/

extern void discord_group_dm_add_recipient_params_cleanup_v(void *p);
extern void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_init_v(void *p);
extern void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p);
extern struct discord_group_dm_add_recipient_params * discord_group_dm_add_recipient_params_alloc();
extern void discord_group_dm_add_recipient_params_free_v(void *p);
extern void discord_group_dm_add_recipient_params_free(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern size_t discord_group_dm_add_recipient_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern size_t discord_group_dm_add_recipient_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_query(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_list_free_v(void **p);
extern void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p);
extern void discord_group_dm_add_recipient_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p);
extern size_t discord_group_dm_add_recipient_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p);
/* This file is generated from specs/channel.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#channel-object-channel-types
*/

extern void discord_channel_cleanup_v(void *p);
extern void discord_channel_cleanup(struct discord_channel *p);
extern void discord_channel_init_v(void *p);
extern void discord_channel_init(struct discord_channel *p);
extern struct discord_channel * discord_channel_alloc();
extern void discord_channel_free_v(void *p);
extern void discord_channel_free(struct discord_channel *p);
extern void discord_channel_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_from_json(char *json, size_t len, struct discord_channel *p);
extern size_t discord_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_to_json(char *json, size_t len, struct discord_channel *p);
extern size_t discord_channel_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_to_query(char *json, size_t len, struct discord_channel *p);
extern void discord_channel_list_free_v(void **p);
extern void discord_channel_list_free(struct discord_channel **p);
extern void discord_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_list_from_json(char *str, size_t len, struct discord_channel ***p);
extern size_t discord_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_list_to_json(char *str, size_t len, struct discord_channel **p);
/* This file is generated from specs/channel.message.json, Please don't edit it. */
/*

*/

extern void discord_message_sticker_cleanup_v(void *p);
extern void discord_message_sticker_cleanup(struct discord_message_sticker *p);
extern void discord_message_sticker_init_v(void *p);
extern void discord_message_sticker_init(struct discord_message_sticker *p);
extern struct discord_message_sticker * discord_message_sticker_alloc();
extern void discord_message_sticker_free_v(void *p);
extern void discord_message_sticker_free(struct discord_message_sticker *p);
extern void discord_message_sticker_from_json_v(char *json, size_t len, void *p);
extern void discord_message_sticker_from_json(char *json, size_t len, struct discord_message_sticker *p);
extern size_t discord_message_sticker_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_sticker_to_json(char *json, size_t len, struct discord_message_sticker *p);
extern size_t discord_message_sticker_to_query_v(char *json, size_t len, void *p);
extern size_t discord_message_sticker_to_query(char *json, size_t len, struct discord_message_sticker *p);
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
extern struct discord_message_reference * discord_message_reference_alloc();
extern void discord_message_reference_free_v(void *p);
extern void discord_message_reference_free(struct discord_message_reference *p);
extern void discord_message_reference_from_json_v(char *json, size_t len, void *p);
extern void discord_message_reference_from_json(char *json, size_t len, struct discord_message_reference *p);
extern size_t discord_message_reference_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_reference_to_json(char *json, size_t len, struct discord_message_reference *p);
extern size_t discord_message_reference_to_query_v(char *json, size_t len, void *p);
extern size_t discord_message_reference_to_query(char *json, size_t len, struct discord_message_reference *p);
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
extern struct discord_message_application * discord_message_application_alloc();
extern void discord_message_application_free_v(void *p);
extern void discord_message_application_free(struct discord_message_application *p);
extern void discord_message_application_from_json_v(char *json, size_t len, void *p);
extern void discord_message_application_from_json(char *json, size_t len, struct discord_message_application *p);
extern size_t discord_message_application_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_application_to_json(char *json, size_t len, struct discord_message_application *p);
extern size_t discord_message_application_to_query_v(char *json, size_t len, void *p);
extern size_t discord_message_application_to_query(char *json, size_t len, struct discord_message_application *p);
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
extern struct discord_message_activity * discord_message_activity_alloc();
extern void discord_message_activity_free_v(void *p);
extern void discord_message_activity_free(struct discord_message_activity *p);
extern void discord_message_activity_from_json_v(char *json, size_t len, void *p);
extern void discord_message_activity_from_json(char *json, size_t len, struct discord_message_activity *p);
extern size_t discord_message_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_activity_to_json(char *json, size_t len, struct discord_message_activity *p);
extern size_t discord_message_activity_to_query_v(char *json, size_t len, void *p);
extern size_t discord_message_activity_to_query(char *json, size_t len, struct discord_message_activity *p);
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
extern struct discord_message * discord_message_alloc();
extern void discord_message_free_v(void *p);
extern void discord_message_free(struct discord_message *p);
extern void discord_message_from_json_v(char *json, size_t len, void *p);
extern void discord_message_from_json(char *json, size_t len, struct discord_message *p);
extern size_t discord_message_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_to_json(char *json, size_t len, struct discord_message *p);
extern size_t discord_message_to_query_v(char *json, size_t len, void *p);
extern size_t discord_message_to_query(char *json, size_t len, struct discord_message *p);
extern void discord_message_list_free_v(void **p);
extern void discord_message_list_free(struct discord_message **p);
extern void discord_message_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_list_from_json(char *str, size_t len, struct discord_message ***p);
extern size_t discord_message_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_list_to_json(char *str, size_t len, struct discord_message **p);
/* This file is generated from specs/channel.modify-channel.json, Please don't edit it. */
/*

*/

extern void discord_modify_channel_params_cleanup_v(void *p);
extern void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_init_v(void *p);
extern void discord_modify_channel_params_init(struct discord_modify_channel_params *p);
extern struct discord_modify_channel_params * discord_modify_channel_params_alloc();
extern void discord_modify_channel_params_free_v(void *p);
extern void discord_modify_channel_params_free(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params *p);
extern size_t discord_modify_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_channel_params_to_json(char *json, size_t len, struct discord_modify_channel_params *p);
extern size_t discord_modify_channel_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_channel_params_to_query(char *json, size_t len, struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_list_free_v(void **p);
extern void discord_modify_channel_params_list_free(struct discord_modify_channel_params **p);
extern void discord_modify_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_channel_params_list_from_json(char *str, size_t len, struct discord_modify_channel_params ***p);
extern size_t discord_modify_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_channel_params_list_to_json(char *str, size_t len, struct discord_modify_channel_params **p);
/* This file is generated from specs/channel.objects.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/

extern void discord_channel_overwrite_cleanup_v(void *p);
extern void discord_channel_overwrite_cleanup(struct discord_channel_overwrite *p);
extern void discord_channel_overwrite_init_v(void *p);
extern void discord_channel_overwrite_init(struct discord_channel_overwrite *p);
extern struct discord_channel_overwrite * discord_channel_overwrite_alloc();
extern void discord_channel_overwrite_free_v(void *p);
extern void discord_channel_overwrite_free(struct discord_channel_overwrite *p);
extern void discord_channel_overwrite_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_overwrite_from_json(char *json, size_t len, struct discord_channel_overwrite *p);
extern size_t discord_channel_overwrite_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_overwrite_to_json(char *json, size_t len, struct discord_channel_overwrite *p);
extern size_t discord_channel_overwrite_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_overwrite_to_query(char *json, size_t len, struct discord_channel_overwrite *p);
extern void discord_channel_overwrite_list_free_v(void **p);
extern void discord_channel_overwrite_list_free(struct discord_channel_overwrite **p);
extern void discord_channel_overwrite_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_overwrite_list_from_json(char *str, size_t len, struct discord_channel_overwrite ***p);
extern size_t discord_channel_overwrite_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_overwrite_list_to_json(char *str, size_t len, struct discord_channel_overwrite **p);

extern void discord_channel_reaction_cleanup_v(void *p);
extern void discord_channel_reaction_cleanup(struct discord_channel_reaction *p);
extern void discord_channel_reaction_init_v(void *p);
extern void discord_channel_reaction_init(struct discord_channel_reaction *p);
extern struct discord_channel_reaction * discord_channel_reaction_alloc();
extern void discord_channel_reaction_free_v(void *p);
extern void discord_channel_reaction_free(struct discord_channel_reaction *p);
extern void discord_channel_reaction_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_reaction_from_json(char *json, size_t len, struct discord_channel_reaction *p);
extern size_t discord_channel_reaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_reaction_to_json(char *json, size_t len, struct discord_channel_reaction *p);
extern size_t discord_channel_reaction_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_reaction_to_query(char *json, size_t len, struct discord_channel_reaction *p);
extern void discord_channel_reaction_list_free_v(void **p);
extern void discord_channel_reaction_list_free(struct discord_channel_reaction **p);
extern void discord_channel_reaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_reaction_list_from_json(char *str, size_t len, struct discord_channel_reaction ***p);
extern size_t discord_channel_reaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_reaction_list_to_json(char *str, size_t len, struct discord_channel_reaction **p);

extern void discord_channel_followed_channel_cleanup_v(void *p);
extern void discord_channel_followed_channel_cleanup(struct discord_channel_followed_channel *p);
extern void discord_channel_followed_channel_init_v(void *p);
extern void discord_channel_followed_channel_init(struct discord_channel_followed_channel *p);
extern struct discord_channel_followed_channel * discord_channel_followed_channel_alloc();
extern void discord_channel_followed_channel_free_v(void *p);
extern void discord_channel_followed_channel_free(struct discord_channel_followed_channel *p);
extern void discord_channel_followed_channel_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_followed_channel_from_json(char *json, size_t len, struct discord_channel_followed_channel *p);
extern size_t discord_channel_followed_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_followed_channel_to_json(char *json, size_t len, struct discord_channel_followed_channel *p);
extern size_t discord_channel_followed_channel_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_followed_channel_to_query(char *json, size_t len, struct discord_channel_followed_channel *p);
extern void discord_channel_followed_channel_list_free_v(void **p);
extern void discord_channel_followed_channel_list_free(struct discord_channel_followed_channel **p);
extern void discord_channel_followed_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_followed_channel_list_from_json(char *str, size_t len, struct discord_channel_followed_channel ***p);
extern size_t discord_channel_followed_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_followed_channel_list_to_json(char *str, size_t len, struct discord_channel_followed_channel **p);

extern void discord_channel_attachment_cleanup_v(void *p);
extern void discord_channel_attachment_cleanup(struct discord_channel_attachment *p);
extern void discord_channel_attachment_init_v(void *p);
extern void discord_channel_attachment_init(struct discord_channel_attachment *p);
extern struct discord_channel_attachment * discord_channel_attachment_alloc();
extern void discord_channel_attachment_free_v(void *p);
extern void discord_channel_attachment_free(struct discord_channel_attachment *p);
extern void discord_channel_attachment_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_attachment_from_json(char *json, size_t len, struct discord_channel_attachment *p);
extern size_t discord_channel_attachment_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_attachment_to_json(char *json, size_t len, struct discord_channel_attachment *p);
extern size_t discord_channel_attachment_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_attachment_to_query(char *json, size_t len, struct discord_channel_attachment *p);
extern void discord_channel_attachment_list_free_v(void **p);
extern void discord_channel_attachment_list_free(struct discord_channel_attachment **p);
extern void discord_channel_attachment_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_attachment_list_from_json(char *str, size_t len, struct discord_channel_attachment ***p);
extern size_t discord_channel_attachment_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_attachment_list_to_json(char *str, size_t len, struct discord_channel_attachment **p);

extern void discord_channel_mention_cleanup_v(void *p);
extern void discord_channel_mention_cleanup(struct discord_channel_mention *p);
extern void discord_channel_mention_init_v(void *p);
extern void discord_channel_mention_init(struct discord_channel_mention *p);
extern struct discord_channel_mention * discord_channel_mention_alloc();
extern void discord_channel_mention_free_v(void *p);
extern void discord_channel_mention_free(struct discord_channel_mention *p);
extern void discord_channel_mention_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_mention_from_json(char *json, size_t len, struct discord_channel_mention *p);
extern size_t discord_channel_mention_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_mention_to_json(char *json, size_t len, struct discord_channel_mention *p);
extern size_t discord_channel_mention_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_mention_to_query(char *json, size_t len, struct discord_channel_mention *p);
extern void discord_channel_mention_list_free_v(void **p);
extern void discord_channel_mention_list_free(struct discord_channel_mention **p);
extern void discord_channel_mention_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_mention_list_from_json(char *str, size_t len, struct discord_channel_mention ***p);
extern size_t discord_channel_mention_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_mention_list_to_json(char *str, size_t len, struct discord_channel_mention **p);

extern void discord_channel_allowed_mentions_cleanup_v(void *p);
extern void discord_channel_allowed_mentions_cleanup(struct discord_channel_allowed_mentions *p);
extern void discord_channel_allowed_mentions_init_v(void *p);
extern void discord_channel_allowed_mentions_init(struct discord_channel_allowed_mentions *p);
extern struct discord_channel_allowed_mentions * discord_channel_allowed_mentions_alloc();
extern void discord_channel_allowed_mentions_free_v(void *p);
extern void discord_channel_allowed_mentions_free(struct discord_channel_allowed_mentions *p);
extern void discord_channel_allowed_mentions_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_allowed_mentions_from_json(char *json, size_t len, struct discord_channel_allowed_mentions *p);
extern size_t discord_channel_allowed_mentions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_to_json(char *json, size_t len, struct discord_channel_allowed_mentions *p);
extern size_t discord_channel_allowed_mentions_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_to_query(char *json, size_t len, struct discord_channel_allowed_mentions *p);
extern void discord_channel_allowed_mentions_list_free_v(void **p);
extern void discord_channel_allowed_mentions_list_free(struct discord_channel_allowed_mentions **p);
extern void discord_channel_allowed_mentions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_allowed_mentions_list_from_json(char *str, size_t len, struct discord_channel_allowed_mentions ***p);
extern size_t discord_channel_allowed_mentions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_list_to_json(char *str, size_t len, struct discord_channel_allowed_mentions **p);

extern void discord_embed_cleanup_v(void *p);
extern void discord_embed_cleanup(struct discord_embed *p);
extern void discord_embed_init_v(void *p);
extern void discord_embed_init(struct discord_embed *p);
extern struct discord_embed * discord_embed_alloc();
extern void discord_embed_free_v(void *p);
extern void discord_embed_free(struct discord_embed *p);
extern void discord_embed_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_from_json(char *json, size_t len, struct discord_embed *p);
extern size_t discord_embed_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_to_json(char *json, size_t len, struct discord_embed *p);
extern size_t discord_embed_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_to_query(char *json, size_t len, struct discord_embed *p);
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
extern struct discord_embed_thumbnail * discord_embed_thumbnail_alloc();
extern void discord_embed_thumbnail_free_v(void *p);
extern void discord_embed_thumbnail_free(struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_thumbnail_from_json(char *json, size_t len, struct discord_embed_thumbnail *p);
extern size_t discord_embed_thumbnail_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_thumbnail_to_json(char *json, size_t len, struct discord_embed_thumbnail *p);
extern size_t discord_embed_thumbnail_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_thumbnail_to_query(char *json, size_t len, struct discord_embed_thumbnail *p);
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
extern struct discord_embed_video * discord_embed_video_alloc();
extern void discord_embed_video_free_v(void *p);
extern void discord_embed_video_free(struct discord_embed_video *p);
extern void discord_embed_video_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_video_from_json(char *json, size_t len, struct discord_embed_video *p);
extern size_t discord_embed_video_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_video_to_json(char *json, size_t len, struct discord_embed_video *p);
extern size_t discord_embed_video_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_video_to_query(char *json, size_t len, struct discord_embed_video *p);
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
extern struct discord_embed_image * discord_embed_image_alloc();
extern void discord_embed_image_free_v(void *p);
extern void discord_embed_image_free(struct discord_embed_image *p);
extern void discord_embed_image_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_image_from_json(char *json, size_t len, struct discord_embed_image *p);
extern size_t discord_embed_image_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_image_to_json(char *json, size_t len, struct discord_embed_image *p);
extern size_t discord_embed_image_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_image_to_query(char *json, size_t len, struct discord_embed_image *p);
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
extern struct discord_embed_provider * discord_embed_provider_alloc();
extern void discord_embed_provider_free_v(void *p);
extern void discord_embed_provider_free(struct discord_embed_provider *p);
extern void discord_embed_provider_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_provider_from_json(char *json, size_t len, struct discord_embed_provider *p);
extern size_t discord_embed_provider_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_provider_to_json(char *json, size_t len, struct discord_embed_provider *p);
extern size_t discord_embed_provider_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_provider_to_query(char *json, size_t len, struct discord_embed_provider *p);
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
extern struct discord_embed_author * discord_embed_author_alloc();
extern void discord_embed_author_free_v(void *p);
extern void discord_embed_author_free(struct discord_embed_author *p);
extern void discord_embed_author_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_author_from_json(char *json, size_t len, struct discord_embed_author *p);
extern size_t discord_embed_author_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_author_to_json(char *json, size_t len, struct discord_embed_author *p);
extern size_t discord_embed_author_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_author_to_query(char *json, size_t len, struct discord_embed_author *p);
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
extern struct discord_embed_footer * discord_embed_footer_alloc();
extern void discord_embed_footer_free_v(void *p);
extern void discord_embed_footer_free(struct discord_embed_footer *p);
extern void discord_embed_footer_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_footer_from_json(char *json, size_t len, struct discord_embed_footer *p);
extern size_t discord_embed_footer_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_footer_to_json(char *json, size_t len, struct discord_embed_footer *p);
extern size_t discord_embed_footer_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_footer_to_query(char *json, size_t len, struct discord_embed_footer *p);
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
extern struct discord_embed_field * discord_embed_field_alloc();
extern void discord_embed_field_free_v(void *p);
extern void discord_embed_field_free(struct discord_embed_field *p);
extern void discord_embed_field_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_field_from_json(char *json, size_t len, struct discord_embed_field *p);
extern size_t discord_embed_field_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_field_to_json(char *json, size_t len, struct discord_embed_field *p);
extern size_t discord_embed_field_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_field_to_query(char *json, size_t len, struct discord_embed_field *p);
extern void discord_embed_field_list_free_v(void **p);
extern void discord_embed_field_list_free(struct discord_embed_field **p);
extern void discord_embed_field_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_field_list_from_json(char *str, size_t len, struct discord_embed_field ***p);
extern size_t discord_embed_field_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_field_list_to_json(char *str, size_t len, struct discord_embed_field **p);
/* This file is generated from specs/emoji.create-guild-emoji.json, Please don't edit it. */
/*

*/

extern void discord_create_guild_emoji_params_cleanup_v(void *p);
extern void discord_create_guild_emoji_params_cleanup(struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_init_v(void *p);
extern void discord_create_guild_emoji_params_init(struct discord_create_guild_emoji_params *p);
extern struct discord_create_guild_emoji_params * discord_create_guild_emoji_params_alloc();
extern void discord_create_guild_emoji_params_free_v(void *p);
extern void discord_create_guild_emoji_params_free(struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_emoji_params_from_json(char *json, size_t len, struct discord_create_guild_emoji_params *p);
extern size_t discord_create_guild_emoji_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_emoji_params_to_json(char *json, size_t len, struct discord_create_guild_emoji_params *p);
extern size_t discord_create_guild_emoji_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_emoji_params_to_query(char *json, size_t len, struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_list_free_v(void **p);
extern void discord_create_guild_emoji_params_list_free(struct discord_create_guild_emoji_params **p);
extern void discord_create_guild_emoji_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_emoji_params_list_from_json(char *str, size_t len, struct discord_create_guild_emoji_params ***p);
extern size_t discord_create_guild_emoji_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_emoji_params_list_to_json(char *str, size_t len, struct discord_create_guild_emoji_params **p);
/* This file is generated from specs/emoji.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
*/

extern void discord_emoji_cleanup_v(void *p);
extern void discord_emoji_cleanup(struct discord_emoji *p);
extern void discord_emoji_init_v(void *p);
extern void discord_emoji_init(struct discord_emoji *p);
extern struct discord_emoji * discord_emoji_alloc();
extern void discord_emoji_free_v(void *p);
extern void discord_emoji_free(struct discord_emoji *p);
extern void discord_emoji_from_json_v(char *json, size_t len, void *p);
extern void discord_emoji_from_json(char *json, size_t len, struct discord_emoji *p);
extern size_t discord_emoji_to_json_v(char *json, size_t len, void *p);
extern size_t discord_emoji_to_json(char *json, size_t len, struct discord_emoji *p);
extern size_t discord_emoji_to_query_v(char *json, size_t len, void *p);
extern size_t discord_emoji_to_query(char *json, size_t len, struct discord_emoji *p);
extern void discord_emoji_list_free_v(void **p);
extern void discord_emoji_list_free(struct discord_emoji **p);
extern void discord_emoji_list_from_json_v(char *str, size_t len, void *p);
extern void discord_emoji_list_from_json(char *str, size_t len, struct discord_emoji ***p);
extern size_t discord_emoji_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_emoji_list_to_json(char *str, size_t len, struct discord_emoji **p);
/* This file is generated from specs/emoji.modify-guild-emoji.json, Please don't edit it. */
/*

*/

extern void discord_modify_guild_emoji_params_cleanup_v(void *p);
extern void discord_modify_guild_emoji_params_cleanup(struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_init_v(void *p);
extern void discord_modify_guild_emoji_params_init(struct discord_modify_guild_emoji_params *p);
extern struct discord_modify_guild_emoji_params * discord_modify_guild_emoji_params_alloc();
extern void discord_modify_guild_emoji_params_free_v(void *p);
extern void discord_modify_guild_emoji_params_free(struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_guild_emoji_params_from_json(char *json, size_t len, struct discord_modify_guild_emoji_params *p);
extern size_t discord_modify_guild_emoji_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_emoji_params_to_json(char *json, size_t len, struct discord_modify_guild_emoji_params *p);
extern size_t discord_modify_guild_emoji_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_emoji_params_to_query(char *json, size_t len, struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_list_free_v(void **p);
extern void discord_modify_guild_emoji_params_list_free(struct discord_modify_guild_emoji_params **p);
extern void discord_modify_guild_emoji_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_emoji_params_list_from_json(char *str, size_t len, struct discord_modify_guild_emoji_params ***p);
extern size_t discord_modify_guild_emoji_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_emoji_params_list_to_json(char *str, size_t len, struct discord_modify_guild_emoji_params **p);
/* This file is generated from specs/gateway.json, Please don't edit it. */
/*
(null)
*/

extern void discord_gateway_identify_cleanup_v(void *p);
extern void discord_gateway_identify_cleanup(struct discord_gateway_identify *p);
extern void discord_gateway_identify_init_v(void *p);
extern void discord_gateway_identify_init(struct discord_gateway_identify *p);
extern struct discord_gateway_identify * discord_gateway_identify_alloc();
extern void discord_gateway_identify_free_v(void *p);
extern void discord_gateway_identify_free(struct discord_gateway_identify *p);
extern void discord_gateway_identify_from_json_v(char *json, size_t len, void *p);
extern void discord_gateway_identify_from_json(char *json, size_t len, struct discord_gateway_identify *p);
extern size_t discord_gateway_identify_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_to_json(char *json, size_t len, struct discord_gateway_identify *p);
extern size_t discord_gateway_identify_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_to_query(char *json, size_t len, struct discord_gateway_identify *p);
extern void discord_gateway_identify_list_free_v(void **p);
extern void discord_gateway_identify_list_free(struct discord_gateway_identify **p);
extern void discord_gateway_identify_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_identify_list_from_json(char *str, size_t len, struct discord_gateway_identify ***p);
extern size_t discord_gateway_identify_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_identify_list_to_json(char *str, size_t len, struct discord_gateway_identify **p);

extern void discord_gateway_identify_status_update_cleanup_v(void *p);
extern void discord_gateway_identify_status_update_cleanup(struct discord_gateway_identify_status_update *p);
extern void discord_gateway_identify_status_update_init_v(void *p);
extern void discord_gateway_identify_status_update_init(struct discord_gateway_identify_status_update *p);
extern struct discord_gateway_identify_status_update * discord_gateway_identify_status_update_alloc();
extern void discord_gateway_identify_status_update_free_v(void *p);
extern void discord_gateway_identify_status_update_free(struct discord_gateway_identify_status_update *p);
extern void discord_gateway_identify_status_update_from_json_v(char *json, size_t len, void *p);
extern void discord_gateway_identify_status_update_from_json(char *json, size_t len, struct discord_gateway_identify_status_update *p);
extern size_t discord_gateway_identify_status_update_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_to_json(char *json, size_t len, struct discord_gateway_identify_status_update *p);
extern size_t discord_gateway_identify_status_update_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_to_query(char *json, size_t len, struct discord_gateway_identify_status_update *p);
extern void discord_gateway_identify_status_update_list_free_v(void **p);
extern void discord_gateway_identify_status_update_list_free(struct discord_gateway_identify_status_update **p);
extern void discord_gateway_identify_status_update_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_identify_status_update_list_from_json(char *str, size_t len, struct discord_gateway_identify_status_update ***p);
extern size_t discord_gateway_identify_status_update_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_list_to_json(char *str, size_t len, struct discord_gateway_identify_status_update **p);

extern void discord_gateway_identify_connection_cleanup_v(void *p);
extern void discord_gateway_identify_connection_cleanup(struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_init_v(void *p);
extern void discord_gateway_identify_connection_init(struct discord_gateway_identify_connection *p);
extern struct discord_gateway_identify_connection * discord_gateway_identify_connection_alloc();
extern void discord_gateway_identify_connection_free_v(void *p);
extern void discord_gateway_identify_connection_free(struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_from_json_v(char *json, size_t len, void *p);
extern void discord_gateway_identify_connection_from_json(char *json, size_t len, struct discord_gateway_identify_connection *p);
extern size_t discord_gateway_identify_connection_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_connection_to_json(char *json, size_t len, struct discord_gateway_identify_connection *p);
extern size_t discord_gateway_identify_connection_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_connection_to_query(char *json, size_t len, struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_list_free_v(void **p);
extern void discord_gateway_identify_connection_list_free(struct discord_gateway_identify_connection **p);
extern void discord_gateway_identify_connection_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_identify_connection_list_from_json(char *str, size_t len, struct discord_gateway_identify_connection ***p);
extern size_t discord_gateway_identify_connection_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_identify_connection_list_to_json(char *str, size_t len, struct discord_gateway_identify_connection **p);

extern void discord_gateway_identify_status_update_activity_cleanup_v(void *p);
extern void discord_gateway_identify_status_update_activity_cleanup(struct discord_gateway_identify_status_update_activity *p);
extern void discord_gateway_identify_status_update_activity_init_v(void *p);
extern void discord_gateway_identify_status_update_activity_init(struct discord_gateway_identify_status_update_activity *p);
extern struct discord_gateway_identify_status_update_activity * discord_gateway_identify_status_update_activity_alloc();
extern void discord_gateway_identify_status_update_activity_free_v(void *p);
extern void discord_gateway_identify_status_update_activity_free(struct discord_gateway_identify_status_update_activity *p);
extern void discord_gateway_identify_status_update_activity_from_json_v(char *json, size_t len, void *p);
extern void discord_gateway_identify_status_update_activity_from_json(char *json, size_t len, struct discord_gateway_identify_status_update_activity *p);
extern size_t discord_gateway_identify_status_update_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_activity_to_json(char *json, size_t len, struct discord_gateway_identify_status_update_activity *p);
extern size_t discord_gateway_identify_status_update_activity_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_activity_to_query(char *json, size_t len, struct discord_gateway_identify_status_update_activity *p);
extern void discord_gateway_identify_status_update_activity_list_free_v(void **p);
extern void discord_gateway_identify_status_update_activity_list_free(struct discord_gateway_identify_status_update_activity **p);
extern void discord_gateway_identify_status_update_activity_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_identify_status_update_activity_list_from_json(char *str, size_t len, struct discord_gateway_identify_status_update_activity ***p);
extern size_t discord_gateway_identify_status_update_activity_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_identify_status_update_activity_list_to_json(char *str, size_t len, struct discord_gateway_identify_status_update_activity **p);
/* This file is generated from specs/guild.ban.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/

extern void discord_guild_ban_cleanup_v(void *p);
extern void discord_guild_ban_cleanup(struct discord_guild_ban *p);
extern void discord_guild_ban_init_v(void *p);
extern void discord_guild_ban_init(struct discord_guild_ban *p);
extern struct discord_guild_ban * discord_guild_ban_alloc();
extern void discord_guild_ban_free_v(void *p);
extern void discord_guild_ban_free(struct discord_guild_ban *p);
extern void discord_guild_ban_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_ban_from_json(char *json, size_t len, struct discord_guild_ban *p);
extern size_t discord_guild_ban_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_ban_to_json(char *json, size_t len, struct discord_guild_ban *p);
extern size_t discord_guild_ban_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_ban_to_query(char *json, size_t len, struct discord_guild_ban *p);
extern void discord_guild_ban_list_free_v(void **p);
extern void discord_guild_ban_list_free(struct discord_guild_ban **p);
extern void discord_guild_ban_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_ban_list_from_json(char *str, size_t len, struct discord_guild_ban ***p);
extern size_t discord_guild_ban_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_ban_list_to_json(char *str, size_t len, struct discord_guild_ban **p);
/* This file is generated from specs/guild.create-channel.json, Please don't edit it. */
/*

*/

extern void discord_create_guild_channel_params_cleanup_v(void *p);
extern void discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_init_v(void *p);
extern void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *p);
extern struct discord_create_guild_channel_params * discord_create_guild_channel_params_alloc();
extern void discord_create_guild_channel_params_free_v(void *p);
extern void discord_create_guild_channel_params_free(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_channel_params_from_json(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern size_t discord_create_guild_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_channel_params_to_json(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern size_t discord_create_guild_channel_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_channel_params_to_query(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_list_free_v(void **p);
extern void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **p);
extern void discord_create_guild_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_channel_params_list_from_json(char *str, size_t len, struct discord_create_guild_channel_params ***p);
extern size_t discord_create_guild_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_channel_params_list_to_json(char *str, size_t len, struct discord_create_guild_channel_params **p);
/* This file is generated from specs/guild.create-guild.json, Please don't edit it. */
/*

*/

extern void discord_create_guild_params_cleanup_v(void *p);
extern void discord_create_guild_params_cleanup(struct discord_create_guild_params *p);
extern void discord_create_guild_params_init_v(void *p);
extern void discord_create_guild_params_init(struct discord_create_guild_params *p);
extern struct discord_create_guild_params * discord_create_guild_params_alloc();
extern void discord_create_guild_params_free_v(void *p);
extern void discord_create_guild_params_free(struct discord_create_guild_params *p);
extern void discord_create_guild_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_params_from_json(char *json, size_t len, struct discord_create_guild_params *p);
extern size_t discord_create_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_params_to_json(char *json, size_t len, struct discord_create_guild_params *p);
extern size_t discord_create_guild_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_params_to_query(char *json, size_t len, struct discord_create_guild_params *p);
extern void discord_create_guild_params_list_free_v(void **p);
extern void discord_create_guild_params_list_free(struct discord_create_guild_params **p);
extern void discord_create_guild_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_params_list_from_json(char *str, size_t len, struct discord_create_guild_params ***p);
extern size_t discord_create_guild_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_params_list_to_json(char *str, size_t len, struct discord_create_guild_params **p);
/* This file is generated from specs/guild.enum.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/

extern void discord_guild_unavailable_cleanup_v(void *p);
extern void discord_guild_unavailable_cleanup(struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_init_v(void *p);
extern void discord_guild_unavailable_init(struct discord_guild_unavailable *p);
extern struct discord_guild_unavailable * discord_guild_unavailable_alloc();
extern void discord_guild_unavailable_free_v(void *p);
extern void discord_guild_unavailable_free(struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_unavailable_from_json(char *json, size_t len, struct discord_guild_unavailable *p);
extern size_t discord_guild_unavailable_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_unavailable_to_json(char *json, size_t len, struct discord_guild_unavailable *p);
extern size_t discord_guild_unavailable_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_unavailable_to_query(char *json, size_t len, struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_list_free_v(void **p);
extern void discord_guild_unavailable_list_free(struct discord_guild_unavailable **p);
extern void discord_guild_unavailable_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_unavailable_list_from_json(char *str, size_t len, struct discord_guild_unavailable ***p);
extern size_t discord_guild_unavailable_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_unavailable_list_to_json(char *str, size_t len, struct discord_guild_unavailable **p);

extern void discord_guild_preview_cleanup_v(void *p);
extern void discord_guild_preview_cleanup(struct discord_guild_preview *p);
extern void discord_guild_preview_init_v(void *p);
extern void discord_guild_preview_init(struct discord_guild_preview *p);
extern struct discord_guild_preview * discord_guild_preview_alloc();
extern void discord_guild_preview_free_v(void *p);
extern void discord_guild_preview_free(struct discord_guild_preview *p);
extern void discord_guild_preview_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_preview_from_json(char *json, size_t len, struct discord_guild_preview *p);
extern size_t discord_guild_preview_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_preview_to_json(char *json, size_t len, struct discord_guild_preview *p);
extern size_t discord_guild_preview_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_preview_to_query(char *json, size_t len, struct discord_guild_preview *p);
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
extern struct discord_guild_widget * discord_guild_widget_alloc();
extern void discord_guild_widget_free_v(void *p);
extern void discord_guild_widget_free(struct discord_guild_widget *p);
extern void discord_guild_widget_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_widget_from_json(char *json, size_t len, struct discord_guild_widget *p);
extern size_t discord_guild_widget_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_widget_to_json(char *json, size_t len, struct discord_guild_widget *p);
extern size_t discord_guild_widget_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_widget_to_query(char *json, size_t len, struct discord_guild_widget *p);
extern void discord_guild_widget_list_free_v(void **p);
extern void discord_guild_widget_list_free(struct discord_guild_widget **p);
extern void discord_guild_widget_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_widget_list_from_json(char *str, size_t len, struct discord_guild_widget ***p);
extern size_t discord_guild_widget_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_widget_list_to_json(char *str, size_t len, struct discord_guild_widget **p);
/* This file is generated from specs/guild.integration.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/

extern void discord_guild_integration_account_cleanup_v(void *p);
extern void discord_guild_integration_account_cleanup(struct discord_guild_integration_account *p);
extern void discord_guild_integration_account_init_v(void *p);
extern void discord_guild_integration_account_init(struct discord_guild_integration_account *p);
extern struct discord_guild_integration_account * discord_guild_integration_account_alloc();
extern void discord_guild_integration_account_free_v(void *p);
extern void discord_guild_integration_account_free(struct discord_guild_integration_account *p);
extern void discord_guild_integration_account_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_integration_account_from_json(char *json, size_t len, struct discord_guild_integration_account *p);
extern size_t discord_guild_integration_account_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_account_to_json(char *json, size_t len, struct discord_guild_integration_account *p);
extern size_t discord_guild_integration_account_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_account_to_query(char *json, size_t len, struct discord_guild_integration_account *p);
extern void discord_guild_integration_account_list_free_v(void **p);
extern void discord_guild_integration_account_list_free(struct discord_guild_integration_account **p);
extern void discord_guild_integration_account_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_integration_account_list_from_json(char *str, size_t len, struct discord_guild_integration_account ***p);
extern size_t discord_guild_integration_account_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_integration_account_list_to_json(char *str, size_t len, struct discord_guild_integration_account **p);

extern void discord_guild_integration_application_cleanup_v(void *p);
extern void discord_guild_integration_application_cleanup(struct discord_guild_integration_application *p);
extern void discord_guild_integration_application_init_v(void *p);
extern void discord_guild_integration_application_init(struct discord_guild_integration_application *p);
extern struct discord_guild_integration_application * discord_guild_integration_application_alloc();
extern void discord_guild_integration_application_free_v(void *p);
extern void discord_guild_integration_application_free(struct discord_guild_integration_application *p);
extern void discord_guild_integration_application_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_integration_application_from_json(char *json, size_t len, struct discord_guild_integration_application *p);
extern size_t discord_guild_integration_application_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_application_to_json(char *json, size_t len, struct discord_guild_integration_application *p);
extern size_t discord_guild_integration_application_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_application_to_query(char *json, size_t len, struct discord_guild_integration_application *p);
extern void discord_guild_integration_application_list_free_v(void **p);
extern void discord_guild_integration_application_list_free(struct discord_guild_integration_application **p);
extern void discord_guild_integration_application_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_integration_application_list_from_json(char *str, size_t len, struct discord_guild_integration_application ***p);
extern size_t discord_guild_integration_application_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_integration_application_list_to_json(char *str, size_t len, struct discord_guild_integration_application **p);

extern void discord_guild_integration_cleanup_v(void *p);
extern void discord_guild_integration_cleanup(struct discord_guild_integration *p);
extern void discord_guild_integration_init_v(void *p);
extern void discord_guild_integration_init(struct discord_guild_integration *p);
extern struct discord_guild_integration * discord_guild_integration_alloc();
extern void discord_guild_integration_free_v(void *p);
extern void discord_guild_integration_free(struct discord_guild_integration *p);
extern void discord_guild_integration_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_integration_from_json(char *json, size_t len, struct discord_guild_integration *p);
extern size_t discord_guild_integration_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_to_json(char *json, size_t len, struct discord_guild_integration *p);
extern size_t discord_guild_integration_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_to_query(char *json, size_t len, struct discord_guild_integration *p);
extern void discord_guild_integration_list_free_v(void **p);
extern void discord_guild_integration_list_free(struct discord_guild_integration **p);
extern void discord_guild_integration_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_integration_list_from_json(char *str, size_t len, struct discord_guild_integration ***p);
extern size_t discord_guild_integration_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_integration_list_to_json(char *str, size_t len, struct discord_guild_integration **p);
/* This file is generated from specs/guild.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
*/

extern void discord_guild_cleanup_v(void *p);
extern void discord_guild_cleanup(struct discord_guild *p);
extern void discord_guild_init_v(void *p);
extern void discord_guild_init(struct discord_guild *p);
extern struct discord_guild * discord_guild_alloc();
extern void discord_guild_free_v(void *p);
extern void discord_guild_free(struct discord_guild *p);
extern void discord_guild_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_from_json(char *json, size_t len, struct discord_guild *p);
extern size_t discord_guild_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_to_json(char *json, size_t len, struct discord_guild *p);
extern size_t discord_guild_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_to_query(char *json, size_t len, struct discord_guild *p);
extern void discord_guild_list_free_v(void **p);
extern void discord_guild_list_free(struct discord_guild **p);
extern void discord_guild_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_list_from_json(char *str, size_t len, struct discord_guild ***p);
extern size_t discord_guild_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_list_to_json(char *str, size_t len, struct discord_guild **p);
/* This file is generated from specs/guild.member.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-member-object
*/

extern void discord_guild_member_cleanup_v(void *p);
extern void discord_guild_member_cleanup(struct discord_guild_member *p);
extern void discord_guild_member_init_v(void *p);
extern void discord_guild_member_init(struct discord_guild_member *p);
extern struct discord_guild_member * discord_guild_member_alloc();
extern void discord_guild_member_free_v(void *p);
extern void discord_guild_member_free(struct discord_guild_member *p);
extern void discord_guild_member_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_member_from_json(char *json, size_t len, struct discord_guild_member *p);
extern size_t discord_guild_member_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_member_to_json(char *json, size_t len, struct discord_guild_member *p);
extern size_t discord_guild_member_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_member_to_query(char *json, size_t len, struct discord_guild_member *p);
extern void discord_guild_member_list_free_v(void **p);
extern void discord_guild_member_list_free(struct discord_guild_member **p);
extern void discord_guild_member_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_member_list_from_json(char *str, size_t len, struct discord_guild_member ***p);
extern size_t discord_guild_member_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_member_list_to_json(char *str, size_t len, struct discord_guild_member **p);
/* This file is generated from specs/guild.membership_screening.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/

extern void discord_guild_membership_screening_field_cleanup_v(void *p);
extern void discord_guild_membership_screening_field_cleanup(struct discord_guild_membership_screening_field *p);
extern void discord_guild_membership_screening_field_init_v(void *p);
extern void discord_guild_membership_screening_field_init(struct discord_guild_membership_screening_field *p);
extern struct discord_guild_membership_screening_field * discord_guild_membership_screening_field_alloc();
extern void discord_guild_membership_screening_field_free_v(void *p);
extern void discord_guild_membership_screening_field_free(struct discord_guild_membership_screening_field *p);
extern void discord_guild_membership_screening_field_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_membership_screening_field_from_json(char *json, size_t len, struct discord_guild_membership_screening_field *p);
extern size_t discord_guild_membership_screening_field_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_membership_screening_field_to_json(char *json, size_t len, struct discord_guild_membership_screening_field *p);
extern size_t discord_guild_membership_screening_field_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_membership_screening_field_to_query(char *json, size_t len, struct discord_guild_membership_screening_field *p);
extern void discord_guild_membership_screening_field_list_free_v(void **p);
extern void discord_guild_membership_screening_field_list_free(struct discord_guild_membership_screening_field **p);
extern void discord_guild_membership_screening_field_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_membership_screening_field_list_from_json(char *str, size_t len, struct discord_guild_membership_screening_field ***p);
extern size_t discord_guild_membership_screening_field_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_membership_screening_field_list_to_json(char *str, size_t len, struct discord_guild_membership_screening_field **p);

extern void discord_guild_membership_screening_cleanup_v(void *p);
extern void discord_guild_membership_screening_cleanup(struct discord_guild_membership_screening *p);
extern void discord_guild_membership_screening_init_v(void *p);
extern void discord_guild_membership_screening_init(struct discord_guild_membership_screening *p);
extern struct discord_guild_membership_screening * discord_guild_membership_screening_alloc();
extern void discord_guild_membership_screening_free_v(void *p);
extern void discord_guild_membership_screening_free(struct discord_guild_membership_screening *p);
extern void discord_guild_membership_screening_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_membership_screening_from_json(char *json, size_t len, struct discord_guild_membership_screening *p);
extern size_t discord_guild_membership_screening_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_membership_screening_to_json(char *json, size_t len, struct discord_guild_membership_screening *p);
extern size_t discord_guild_membership_screening_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_membership_screening_to_query(char *json, size_t len, struct discord_guild_membership_screening *p);
extern void discord_guild_membership_screening_list_free_v(void **p);
extern void discord_guild_membership_screening_list_free(struct discord_guild_membership_screening **p);
extern void discord_guild_membership_screening_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_membership_screening_list_from_json(char *str, size_t len, struct discord_guild_membership_screening ***p);
extern size_t discord_guild_membership_screening_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_membership_screening_list_to_json(char *str, size_t len, struct discord_guild_membership_screening **p);
/* This file is generated from specs/guild.modify-guild-member.json, Please don't edit it. */
/*

*/

extern void discord_modify_guild_member_params_cleanup_v(void *p);
extern void discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_init_v(void *p);
extern void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *p);
extern struct discord_modify_guild_member_params * discord_modify_guild_member_params_alloc();
extern void discord_modify_guild_member_params_free_v(void *p);
extern void discord_modify_guild_member_params_free(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_guild_member_params_from_json(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern size_t discord_modify_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_member_params_to_json(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern size_t discord_modify_guild_member_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_member_params_to_query(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_list_free_v(void **p);
extern void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **p);
extern void discord_modify_guild_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_member_params_list_from_json(char *str, size_t len, struct discord_modify_guild_member_params ***p);
extern size_t discord_modify_guild_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_member_params_list_to_json(char *str, size_t len, struct discord_modify_guild_member_params **p);
/* This file is generated from specs/guild.role.create.json, Please don't edit it. */
/*

*/

extern void discord_create_guild_role_params_cleanup_v(void *p);
extern void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_init_v(void *p);
extern void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p);
extern struct discord_create_guild_role_params * discord_create_guild_role_params_alloc();
extern void discord_create_guild_role_params_free_v(void *p);
extern void discord_create_guild_role_params_free(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params *p);
extern size_t discord_create_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_role_params_to_json(char *json, size_t len, struct discord_create_guild_role_params *p);
extern size_t discord_create_guild_role_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_role_params_to_query(char *json, size_t len, struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_list_free_v(void **p);
extern void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **p);
extern void discord_create_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_role_params_list_from_json(char *str, size_t len, struct discord_create_guild_role_params ***p);
extern size_t discord_create_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_role_params_list_to_json(char *str, size_t len, struct discord_create_guild_role_params **p);
/* This file is generated from specs/guild.role.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/

extern void discord_guild_role_tags_cleanup_v(void *p);
extern void discord_guild_role_tags_cleanup(struct discord_guild_role_tags *p);
extern void discord_guild_role_tags_init_v(void *p);
extern void discord_guild_role_tags_init(struct discord_guild_role_tags *p);
extern struct discord_guild_role_tags * discord_guild_role_tags_alloc();
extern void discord_guild_role_tags_free_v(void *p);
extern void discord_guild_role_tags_free(struct discord_guild_role_tags *p);
extern void discord_guild_role_tags_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_role_tags_from_json(char *json, size_t len, struct discord_guild_role_tags *p);
extern size_t discord_guild_role_tags_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_role_tags_to_json(char *json, size_t len, struct discord_guild_role_tags *p);
extern size_t discord_guild_role_tags_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_role_tags_to_query(char *json, size_t len, struct discord_guild_role_tags *p);
extern void discord_guild_role_tags_list_free_v(void **p);
extern void discord_guild_role_tags_list_free(struct discord_guild_role_tags **p);
extern void discord_guild_role_tags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_role_tags_list_from_json(char *str, size_t len, struct discord_guild_role_tags ***p);
extern size_t discord_guild_role_tags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_role_tags_list_to_json(char *str, size_t len, struct discord_guild_role_tags **p);

extern void discord_guild_role_cleanup_v(void *p);
extern void discord_guild_role_cleanup(struct discord_guild_role *p);
extern void discord_guild_role_init_v(void *p);
extern void discord_guild_role_init(struct discord_guild_role *p);
extern struct discord_guild_role * discord_guild_role_alloc();
extern void discord_guild_role_free_v(void *p);
extern void discord_guild_role_free(struct discord_guild_role *p);
extern void discord_guild_role_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_role_from_json(char *json, size_t len, struct discord_guild_role *p);
extern size_t discord_guild_role_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_role_to_json(char *json, size_t len, struct discord_guild_role *p);
extern size_t discord_guild_role_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_role_to_query(char *json, size_t len, struct discord_guild_role *p);
extern void discord_guild_role_list_free_v(void **p);
extern void discord_guild_role_list_free(struct discord_guild_role **p);
extern void discord_guild_role_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_role_list_from_json(char *str, size_t len, struct discord_guild_role ***p);
extern size_t discord_guild_role_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_role_list_to_json(char *str, size_t len, struct discord_guild_role **p);
/* This file is generated from specs/guild.welcome_screen.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#welcome-screen-object
*/

extern void discord_guild_welcome_screen_channel_cleanup_v(void *p);
extern void discord_guild_welcome_screen_channel_cleanup(struct discord_guild_welcome_screen_channel *p);
extern void discord_guild_welcome_screen_channel_init_v(void *p);
extern void discord_guild_welcome_screen_channel_init(struct discord_guild_welcome_screen_channel *p);
extern struct discord_guild_welcome_screen_channel * discord_guild_welcome_screen_channel_alloc();
extern void discord_guild_welcome_screen_channel_free_v(void *p);
extern void discord_guild_welcome_screen_channel_free(struct discord_guild_welcome_screen_channel *p);
extern void discord_guild_welcome_screen_channel_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_welcome_screen_channel_from_json(char *json, size_t len, struct discord_guild_welcome_screen_channel *p);
extern size_t discord_guild_welcome_screen_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_channel_to_json(char *json, size_t len, struct discord_guild_welcome_screen_channel *p);
extern size_t discord_guild_welcome_screen_channel_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_channel_to_query(char *json, size_t len, struct discord_guild_welcome_screen_channel *p);
extern void discord_guild_welcome_screen_channel_list_free_v(void **p);
extern void discord_guild_welcome_screen_channel_list_free(struct discord_guild_welcome_screen_channel **p);
extern void discord_guild_welcome_screen_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_welcome_screen_channel_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen_channel ***p);
extern size_t discord_guild_welcome_screen_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_welcome_screen_channel_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen_channel **p);

extern void discord_guild_welcome_screen_cleanup_v(void *p);
extern void discord_guild_welcome_screen_cleanup(struct discord_guild_welcome_screen *p);
extern void discord_guild_welcome_screen_init_v(void *p);
extern void discord_guild_welcome_screen_init(struct discord_guild_welcome_screen *p);
extern struct discord_guild_welcome_screen * discord_guild_welcome_screen_alloc();
extern void discord_guild_welcome_screen_free_v(void *p);
extern void discord_guild_welcome_screen_free(struct discord_guild_welcome_screen *p);
extern void discord_guild_welcome_screen_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_welcome_screen_from_json(char *json, size_t len, struct discord_guild_welcome_screen *p);
extern size_t discord_guild_welcome_screen_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_to_json(char *json, size_t len, struct discord_guild_welcome_screen *p);
extern size_t discord_guild_welcome_screen_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_to_query(char *json, size_t len, struct discord_guild_welcome_screen *p);
extern void discord_guild_welcome_screen_list_free_v(void **p);
extern void discord_guild_welcome_screen_list_free(struct discord_guild_welcome_screen **p);
extern void discord_guild_welcome_screen_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_welcome_screen_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen ***p);
extern size_t discord_guild_welcome_screen_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_welcome_screen_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen **p);
/* This file is generated from specs/invite.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/invite#invite-object
*/

extern void discord_invite_cleanup_v(void *p);
extern void discord_invite_cleanup(struct discord_invite *p);
extern void discord_invite_init_v(void *p);
extern void discord_invite_init(struct discord_invite *p);
extern struct discord_invite * discord_invite_alloc();
extern void discord_invite_free_v(void *p);
extern void discord_invite_free(struct discord_invite *p);
extern void discord_invite_from_json_v(char *json, size_t len, void *p);
extern void discord_invite_from_json(char *json, size_t len, struct discord_invite *p);
extern size_t discord_invite_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_to_json(char *json, size_t len, struct discord_invite *p);
extern size_t discord_invite_to_query_v(char *json, size_t len, void *p);
extern size_t discord_invite_to_query(char *json, size_t len, struct discord_invite *p);
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
extern struct discord_invite_metadata * discord_invite_metadata_alloc();
extern void discord_invite_metadata_free_v(void *p);
extern void discord_invite_metadata_free(struct discord_invite_metadata *p);
extern void discord_invite_metadata_from_json_v(char *json, size_t len, void *p);
extern void discord_invite_metadata_from_json(char *json, size_t len, struct discord_invite_metadata *p);
extern size_t discord_invite_metadata_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_metadata_to_json(char *json, size_t len, struct discord_invite_metadata *p);
extern size_t discord_invite_metadata_to_query_v(char *json, size_t len, void *p);
extern size_t discord_invite_metadata_to_query(char *json, size_t len, struct discord_invite_metadata *p);
extern void discord_invite_metadata_list_free_v(void **p);
extern void discord_invite_metadata_list_free(struct discord_invite_metadata **p);
extern void discord_invite_metadata_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_metadata_list_from_json(char *str, size_t len, struct discord_invite_metadata ***p);
extern size_t discord_invite_metadata_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_metadata_list_to_json(char *str, size_t len, struct discord_invite_metadata **p);
/* This file is generated from specs/permissions.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions
*/
/* This file is generated from specs/template.create-guild-from-template.json, Please don't edit it. */
/*

*/

extern void discord_create_guild_from_template_params_cleanup_v(void *p);
extern void discord_create_guild_from_template_params_cleanup(struct discord_create_guild_from_template_params *p);
extern void discord_create_guild_from_template_params_init_v(void *p);
extern void discord_create_guild_from_template_params_init(struct discord_create_guild_from_template_params *p);
extern struct discord_create_guild_from_template_params * discord_create_guild_from_template_params_alloc();
extern void discord_create_guild_from_template_params_free_v(void *p);
extern void discord_create_guild_from_template_params_free(struct discord_create_guild_from_template_params *p);
extern void discord_create_guild_from_template_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_from_template_params_from_json(char *json, size_t len, struct discord_create_guild_from_template_params *p);
extern size_t discord_create_guild_from_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_from_template_params_to_json(char *json, size_t len, struct discord_create_guild_from_template_params *p);
extern size_t discord_create_guild_from_template_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_from_template_params_to_query(char *json, size_t len, struct discord_create_guild_from_template_params *p);
extern void discord_create_guild_from_template_params_list_free_v(void **p);
extern void discord_create_guild_from_template_params_list_free(struct discord_create_guild_from_template_params **p);
extern void discord_create_guild_from_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_from_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_from_template_params ***p);
extern size_t discord_create_guild_from_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_from_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_from_template_params **p);
/* This file is generated from specs/template.create-guild-template.json, Please don't edit it. */
/*

*/

extern void discord_create_guild_template_params_cleanup_v(void *p);
extern void discord_create_guild_template_params_cleanup(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_init_v(void *p);
extern void discord_create_guild_template_params_init(struct discord_create_guild_template_params *p);
extern struct discord_create_guild_template_params * discord_create_guild_template_params_alloc();
extern void discord_create_guild_template_params_free_v(void *p);
extern void discord_create_guild_template_params_free(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_template_params *p);
extern size_t discord_create_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_template_params *p);
extern size_t discord_create_guild_template_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_template_params_to_query(char *json, size_t len, struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_list_free_v(void **p);
extern void discord_create_guild_template_params_list_free(struct discord_create_guild_template_params **p);
extern void discord_create_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_template_params ***p);
extern size_t discord_create_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_template_params **p);
/* This file is generated from specs/template.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/template#template-object-template-structure
*/

extern void discord_template_cleanup_v(void *p);
extern void discord_template_cleanup(struct discord_template *p);
extern void discord_template_init_v(void *p);
extern void discord_template_init(struct discord_template *p);
extern struct discord_template * discord_template_alloc();
extern void discord_template_free_v(void *p);
extern void discord_template_free(struct discord_template *p);
extern void discord_template_from_json_v(char *json, size_t len, void *p);
extern void discord_template_from_json(char *json, size_t len, struct discord_template *p);
extern size_t discord_template_to_json_v(char *json, size_t len, void *p);
extern size_t discord_template_to_json(char *json, size_t len, struct discord_template *p);
extern size_t discord_template_to_query_v(char *json, size_t len, void *p);
extern size_t discord_template_to_query(char *json, size_t len, struct discord_template *p);
extern void discord_template_list_free_v(void **p);
extern void discord_template_list_free(struct discord_template **p);
extern void discord_template_list_from_json_v(char *str, size_t len, void *p);
extern void discord_template_list_from_json(char *str, size_t len, struct discord_template ***p);
extern size_t discord_template_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_template_list_to_json(char *str, size_t len, struct discord_template **p);
/* This file is generated from specs/template.modify-guild-template.json, Please don't edit it. */
/*

*/

extern void discord_modify_guild_template_params_cleanup_v(void *p);
extern void discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_init_v(void *p);
extern void discord_modify_guild_template_params_init(struct discord_modify_guild_template_params *p);
extern struct discord_modify_guild_template_params * discord_modify_guild_template_params_alloc();
extern void discord_modify_guild_template_params_free_v(void *p);
extern void discord_modify_guild_template_params_free(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_guild_template_params_from_json(char *json, size_t len, struct discord_modify_guild_template_params *p);
extern size_t discord_modify_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_template_params_to_json(char *json, size_t len, struct discord_modify_guild_template_params *p);
extern size_t discord_modify_guild_template_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_template_params_to_query(char *json, size_t len, struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_list_free_v(void **p);
extern void discord_modify_guild_template_params_list_free(struct discord_modify_guild_template_params **p);
extern void discord_modify_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_template_params_list_from_json(char *str, size_t len, struct discord_modify_guild_template_params ***p);
extern size_t discord_modify_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_template_params_list_to_json(char *str, size_t len, struct discord_modify_guild_template_params **p);
/* This file is generated from specs/user.create-group-dm.json, Please don't edit it. */
/*

*/

extern void discord_create_group_dm_params_cleanup_v(void *p);
extern void discord_create_group_dm_params_cleanup(struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_init_v(void *p);
extern void discord_create_group_dm_params_init(struct discord_create_group_dm_params *p);
extern struct discord_create_group_dm_params * discord_create_group_dm_params_alloc();
extern void discord_create_group_dm_params_free_v(void *p);
extern void discord_create_group_dm_params_free(struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_group_dm_params_from_json(char *json, size_t len, struct discord_create_group_dm_params *p);
extern size_t discord_create_group_dm_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_group_dm_params_to_json(char *json, size_t len, struct discord_create_group_dm_params *p);
extern size_t discord_create_group_dm_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_group_dm_params_to_query(char *json, size_t len, struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_list_free_v(void **p);
extern void discord_create_group_dm_params_list_free(struct discord_create_group_dm_params **p);
extern void discord_create_group_dm_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_group_dm_params_list_from_json(char *str, size_t len, struct discord_create_group_dm_params ***p);
extern size_t discord_create_group_dm_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_group_dm_params_list_to_json(char *str, size_t len, struct discord_create_group_dm_params **p);
/* This file is generated from specs/user.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/user#user-object
*/

extern void discord_user_cleanup_v(void *p);
extern void discord_user_cleanup(struct discord_user *p);
extern void discord_user_init_v(void *p);
extern void discord_user_init(struct discord_user *p);
extern struct discord_user * discord_user_alloc();
extern void discord_user_free_v(void *p);
extern void discord_user_free(struct discord_user *p);
extern void discord_user_from_json_v(char *json, size_t len, void *p);
extern void discord_user_from_json(char *json, size_t len, struct discord_user *p);
extern size_t discord_user_to_json_v(char *json, size_t len, void *p);
extern size_t discord_user_to_json(char *json, size_t len, struct discord_user *p);
extern size_t discord_user_to_query_v(char *json, size_t len, void *p);
extern size_t discord_user_to_query(char *json, size_t len, struct discord_user *p);
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
extern struct discord_connection * discord_connection_alloc();
extern void discord_connection_free_v(void *p);
extern void discord_connection_free(struct discord_connection *p);
extern void discord_connection_from_json_v(char *json, size_t len, void *p);
extern void discord_connection_from_json(char *json, size_t len, struct discord_connection *p);
extern size_t discord_connection_to_json_v(char *json, size_t len, void *p);
extern size_t discord_connection_to_json(char *json, size_t len, struct discord_connection *p);
extern size_t discord_connection_to_query_v(char *json, size_t len, void *p);
extern size_t discord_connection_to_query(char *json, size_t len, struct discord_connection *p);
extern void discord_connection_list_free_v(void **p);
extern void discord_connection_list_free(struct discord_connection **p);
extern void discord_connection_list_from_json_v(char *str, size_t len, void *p);
extern void discord_connection_list_from_json(char *str, size_t len, struct discord_connection ***p);
extern size_t discord_connection_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_connection_list_to_json(char *str, size_t len, struct discord_connection **p);
/* This file is generated from specs/user.modify-curent-user.json, Please don't edit it. */
/*

*/

extern void discord_modify_current_user_params_cleanup_v(void *p);
extern void discord_modify_current_user_params_cleanup(struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_init_v(void *p);
extern void discord_modify_current_user_params_init(struct discord_modify_current_user_params *p);
extern struct discord_modify_current_user_params * discord_modify_current_user_params_alloc();
extern void discord_modify_current_user_params_free_v(void *p);
extern void discord_modify_current_user_params_free(struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_current_user_params_from_json(char *json, size_t len, struct discord_modify_current_user_params *p);
extern size_t discord_modify_current_user_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_user_params_to_json(char *json, size_t len, struct discord_modify_current_user_params *p);
extern size_t discord_modify_current_user_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_user_params_to_query(char *json, size_t len, struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_list_free_v(void **p);
extern void discord_modify_current_user_params_list_free(struct discord_modify_current_user_params **p);
extern void discord_modify_current_user_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_current_user_params_list_from_json(char *str, size_t len, struct discord_modify_current_user_params ***p);
extern size_t discord_modify_current_user_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_current_user_params_list_to_json(char *str, size_t len, struct discord_modify_current_user_params **p);
/* This file is generated from specs/voice.json, Please don't edit it. */
/*
(null)
*/

extern void discord_voice_state_cleanup_v(void *p);
extern void discord_voice_state_cleanup(struct discord_voice_state *p);
extern void discord_voice_state_init_v(void *p);
extern void discord_voice_state_init(struct discord_voice_state *p);
extern struct discord_voice_state * discord_voice_state_alloc();
extern void discord_voice_state_free_v(void *p);
extern void discord_voice_state_free(struct discord_voice_state *p);
extern void discord_voice_state_from_json_v(char *json, size_t len, void *p);
extern void discord_voice_state_from_json(char *json, size_t len, struct discord_voice_state *p);
extern size_t discord_voice_state_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_state_to_json(char *json, size_t len, struct discord_voice_state *p);
extern size_t discord_voice_state_to_query_v(char *json, size_t len, void *p);
extern size_t discord_voice_state_to_query(char *json, size_t len, struct discord_voice_state *p);
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
extern struct discord_voice_region * discord_voice_region_alloc();
extern void discord_voice_region_free_v(void *p);
extern void discord_voice_region_free(struct discord_voice_region *p);
extern void discord_voice_region_from_json_v(char *json, size_t len, void *p);
extern void discord_voice_region_from_json(char *json, size_t len, struct discord_voice_region *p);
extern size_t discord_voice_region_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_region_to_json(char *json, size_t len, struct discord_voice_region *p);
extern size_t discord_voice_region_to_query_v(char *json, size_t len, void *p);
extern size_t discord_voice_region_to_query(char *json, size_t len, struct discord_voice_region *p);
extern void discord_voice_region_list_free_v(void **p);
extern void discord_voice_region_list_free(struct discord_voice_region **p);
extern void discord_voice_region_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_region_list_from_json(char *str, size_t len, struct discord_voice_region ***p);
extern size_t discord_voice_region_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_region_list_to_json(char *str, size_t len, struct discord_voice_region **p);
/* This file is generated from specs/webhook.create-webhook.json, Please don't edit it. */
/*

*/

extern void discord_create_webhook_params_cleanup_v(void *p);
extern void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_init_v(void *p);
extern void discord_create_webhook_params_init(struct discord_create_webhook_params *p);
extern struct discord_create_webhook_params * discord_create_webhook_params_alloc();
extern void discord_create_webhook_params_free_v(void *p);
extern void discord_create_webhook_params_free(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_webhook_params_from_json(char *json, size_t len, struct discord_create_webhook_params *p);
extern size_t discord_create_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_webhook_params_to_json(char *json, size_t len, struct discord_create_webhook_params *p);
extern size_t discord_create_webhook_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_webhook_params_to_query(char *json, size_t len, struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_list_free_v(void **p);
extern void discord_create_webhook_params_list_free(struct discord_create_webhook_params **p);
extern void discord_create_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_webhook_params_list_from_json(char *str, size_t len, struct discord_create_webhook_params ***p);
extern size_t discord_create_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_webhook_params_list_to_json(char *str, size_t len, struct discord_create_webhook_params **p);
/* This file is generated from specs/webhook.edit-webhook-message.json, Please don't edit it. */
/*

*/

extern void discord_edit_webhook_message_params_cleanup_v(void *p);
extern void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_init_v(void *p);
extern void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *p);
extern struct discord_edit_webhook_message_params * discord_edit_webhook_message_params_alloc();
extern void discord_edit_webhook_message_params_free_v(void *p);
extern void discord_edit_webhook_message_params_free(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_edit_webhook_message_params *p);
extern size_t discord_edit_webhook_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_to_json(char *json, size_t len, struct discord_edit_webhook_message_params *p);
extern size_t discord_edit_webhook_message_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_to_query(char *json, size_t len, struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_list_free_v(void **p);
extern void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **p);
extern void discord_edit_webhook_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_webhook_message_params_list_from_json(char *str, size_t len, struct discord_edit_webhook_message_params ***p);
extern size_t discord_edit_webhook_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_list_to_json(char *str, size_t len, struct discord_edit_webhook_message_params **p);
/* This file is generated from specs/webhook.execute-webhook.json, Please don't edit it. */
/*

*/

extern void discord_execute_webhook_params_cleanup_v(void *p);
extern void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_init_v(void *p);
extern void discord_execute_webhook_params_init(struct discord_execute_webhook_params *p);
extern struct discord_execute_webhook_params * discord_execute_webhook_params_alloc();
extern void discord_execute_webhook_params_free_v(void *p);
extern void discord_execute_webhook_params_free(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_from_json_v(char *json, size_t len, void *p);
extern void discord_execute_webhook_params_from_json(char *json, size_t len, struct discord_execute_webhook_params *p);
extern size_t discord_execute_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_execute_webhook_params_to_json(char *json, size_t len, struct discord_execute_webhook_params *p);
extern size_t discord_execute_webhook_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_execute_webhook_params_to_query(char *json, size_t len, struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_list_free_v(void **p);
extern void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **p);
extern void discord_execute_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_execute_webhook_params_list_from_json(char *str, size_t len, struct discord_execute_webhook_params ***p);
extern size_t discord_execute_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_execute_webhook_params_list_to_json(char *str, size_t len, struct discord_execute_webhook_params **p);
/* This file is generated from specs/webhook.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
*/

extern void discord_webhook_cleanup_v(void *p);
extern void discord_webhook_cleanup(struct discord_webhook *p);
extern void discord_webhook_init_v(void *p);
extern void discord_webhook_init(struct discord_webhook *p);
extern struct discord_webhook * discord_webhook_alloc();
extern void discord_webhook_free_v(void *p);
extern void discord_webhook_free(struct discord_webhook *p);
extern void discord_webhook_from_json_v(char *json, size_t len, void *p);
extern void discord_webhook_from_json(char *json, size_t len, struct discord_webhook *p);
extern size_t discord_webhook_to_json_v(char *json, size_t len, void *p);
extern size_t discord_webhook_to_json(char *json, size_t len, struct discord_webhook *p);
extern size_t discord_webhook_to_query_v(char *json, size_t len, void *p);
extern size_t discord_webhook_to_query(char *json, size_t len, struct discord_webhook *p);
extern void discord_webhook_list_free_v(void **p);
extern void discord_webhook_list_free(struct discord_webhook **p);
extern void discord_webhook_list_from_json_v(char *str, size_t len, void *p);
extern void discord_webhook_list_from_json(char *str, size_t len, struct discord_webhook ***p);
extern size_t discord_webhook_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_webhook_list_to_json(char *str, size_t len, struct discord_webhook **p);
/* This file is generated from specs/webhook.modify-webhook.json, Please don't edit it. */
/*

*/

extern void discord_modify_webhook_params_cleanup_v(void *p);
extern void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_init_v(void *p);
extern void discord_modify_webhook_params_init(struct discord_modify_webhook_params *p);
extern struct discord_modify_webhook_params * discord_modify_webhook_params_alloc();
extern void discord_modify_webhook_params_free_v(void *p);
extern void discord_modify_webhook_params_free(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_webhook_params_from_json(char *json, size_t len, struct discord_modify_webhook_params *p);
extern size_t discord_modify_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_webhook_params_to_json(char *json, size_t len, struct discord_modify_webhook_params *p);
extern size_t discord_modify_webhook_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_webhook_params_to_query(char *json, size_t len, struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_list_free_v(void **p);
extern void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **p);
extern void discord_modify_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_webhook_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_params ***p);
extern size_t discord_modify_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_webhook_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_params **p);
