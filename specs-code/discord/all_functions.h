/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/audit-log
 */


extern void discord_get_guild_audit_log_params_cleanup_v(void *p);
extern void discord_get_guild_audit_log_params_cleanup(struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_init_v(void *p);
extern void discord_get_guild_audit_log_params_init(struct discord_get_guild_audit_log_params *p);
extern struct discord_get_guild_audit_log_params * discord_get_guild_audit_log_params_alloc();
extern void discord_get_guild_audit_log_params_free_v(void *p);
extern void discord_get_guild_audit_log_params_free(struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_guild_audit_log_params_from_json(char *json, size_t len, struct discord_get_guild_audit_log_params **pp);
extern size_t discord_get_guild_audit_log_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_audit_log_params_to_json(char *json, size_t len, struct discord_get_guild_audit_log_params *p);
extern size_t discord_get_guild_audit_log_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_audit_log_params_to_query(char *json, size_t len, struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_list_free_v(void **p);
extern void discord_get_guild_audit_log_params_list_free(struct discord_get_guild_audit_log_params **p);
extern void discord_get_guild_audit_log_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_guild_audit_log_params_list_from_json(char *str, size_t len, struct discord_get_guild_audit_log_params ***p);
extern size_t discord_get_guild_audit_log_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_guild_audit_log_params_list_to_json(char *str, size_t len, struct discord_get_guild_audit_log_params **p);
/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/audit-log
 */


extern void discord_audit_log_cleanup_v(void *p);
extern void discord_audit_log_cleanup(struct discord_audit_log *p);
extern void discord_audit_log_init_v(void *p);
extern void discord_audit_log_init(struct discord_audit_log *p);
extern struct discord_audit_log * discord_audit_log_alloc();
extern void discord_audit_log_free_v(void *p);
extern void discord_audit_log_free(struct discord_audit_log *p);
extern void discord_audit_log_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_from_json(char *json, size_t len, struct discord_audit_log **pp);
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
extern void discord_audit_log_entry_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_entry_from_json(char *json, size_t len, struct discord_audit_log_entry **pp);
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
extern void discord_audit_log_entry_optional_info_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_entry_optional_info_from_json(char *json, size_t len, struct discord_audit_log_entry_optional_info **pp);
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
extern void discord_audit_log_change_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_change_from_json(char *json, size_t len, struct discord_audit_log_change **pp);
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
extern void discord_audit_log_change_key_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_change_key_from_json(char *json, size_t len, struct discord_audit_log_change_key **pp);
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
/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */


extern void discord_modify_channel_params_cleanup_v(void *p);
extern void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_init_v(void *p);
extern void discord_modify_channel_params_init(struct discord_modify_channel_params *p);
extern struct discord_modify_channel_params * discord_modify_channel_params_alloc();
extern void discord_modify_channel_params_free_v(void *p);
extern void discord_modify_channel_params_free(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params **pp);
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

extern void discord_get_reactions_params_cleanup_v(void *p);
extern void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_init_v(void *p);
extern void discord_get_reactions_params_init(struct discord_get_reactions_params *p);
extern struct discord_get_reactions_params * discord_get_reactions_params_alloc();
extern void discord_get_reactions_params_free_v(void *p);
extern void discord_get_reactions_params_free(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_reactions_params_from_json(char *json, size_t len, struct discord_get_reactions_params **pp);
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

extern void discord_edit_channel_permissions_params_cleanup_v(void *p);
extern void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_init_v(void *p);
extern void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p);
extern struct discord_edit_channel_permissions_params * discord_edit_channel_permissions_params_alloc();
extern void discord_edit_channel_permissions_params_free_v(void *p);
extern void discord_edit_channel_permissions_params_free(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params **pp);
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

extern void discord_follow_news_channel_params_cleanup_v(void *p);
extern void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_init_v(void *p);
extern void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p);
extern struct discord_follow_news_channel_params * discord_follow_news_channel_params_alloc();
extern void discord_follow_news_channel_params_free_v(void *p);
extern void discord_follow_news_channel_params_free(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params **pp);
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

extern void discord_create_channel_invite_params_cleanup_v(void *p);
extern void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_init_v(void *p);
extern void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p);
extern struct discord_create_channel_invite_params * discord_create_channel_invite_params_alloc();
extern void discord_create_channel_invite_params_free_v(void *p);
extern void discord_create_channel_invite_params_free(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params **pp);
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

extern void discord_group_dm_add_recipient_params_cleanup_v(void *p);
extern void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_init_v(void *p);
extern void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p);
extern struct discord_group_dm_add_recipient_params * discord_group_dm_add_recipient_params_alloc();
extern void discord_group_dm_add_recipient_params_free_v(void *p);
extern void discord_group_dm_add_recipient_params_free(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params **pp);
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

extern void discord_start_thread_with_message_params_cleanup_v(void *p);
extern void discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_init_v(void *p);
extern void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *p);
extern struct discord_start_thread_with_message_params * discord_start_thread_with_message_params_alloc();
extern void discord_start_thread_with_message_params_free_v(void *p);
extern void discord_start_thread_with_message_params_free(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_start_thread_with_message_params_from_json(char *json, size_t len, struct discord_start_thread_with_message_params **pp);
extern size_t discord_start_thread_with_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_to_json(char *json, size_t len, struct discord_start_thread_with_message_params *p);
extern size_t discord_start_thread_with_message_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_to_query(char *json, size_t len, struct discord_start_thread_with_message_params *p);
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
extern struct discord_start_thread_without_message_params * discord_start_thread_without_message_params_alloc();
extern void discord_start_thread_without_message_params_free_v(void *p);
extern void discord_start_thread_without_message_params_free(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params **pp);
extern size_t discord_start_thread_without_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern size_t discord_start_thread_without_message_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_query(char *json, size_t len, struct discord_start_thread_without_message_params *p);
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
extern struct discord_thread_response_body * discord_thread_response_body_alloc();
extern void discord_thread_response_body_free_v(void *p);
extern void discord_thread_response_body_free(struct discord_thread_response_body *p);
extern void discord_thread_response_body_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body **pp);
extern size_t discord_thread_response_body_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p);
extern size_t discord_thread_response_body_to_query_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_query(char *json, size_t len, struct discord_thread_response_body *p);
extern void discord_thread_response_body_list_free_v(void **p);
extern void discord_thread_response_body_list_free(struct discord_thread_response_body **p);
extern void discord_thread_response_body_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p);
extern size_t discord_thread_response_body_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p);
/* This file is generated from specs/discord/channel.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */




extern void discord_channel_cleanup_v(void *p);
extern void discord_channel_cleanup(struct discord_channel *p);
extern void discord_channel_init_v(void *p);
extern void discord_channel_init(struct discord_channel *p);
extern struct discord_channel * discord_channel_alloc();
extern void discord_channel_free_v(void *p);
extern void discord_channel_free(struct discord_channel *p);
extern void discord_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_from_json(char *json, size_t len, struct discord_channel **pp);
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



extern void discord_message_sticker_cleanup_v(void *p);
extern void discord_message_sticker_cleanup(struct discord_message_sticker *p);
extern void discord_message_sticker_init_v(void *p);
extern void discord_message_sticker_init(struct discord_message_sticker *p);
extern struct discord_message_sticker * discord_message_sticker_alloc();
extern void discord_message_sticker_free_v(void *p);
extern void discord_message_sticker_free(struct discord_message_sticker *p);
extern void discord_message_sticker_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_sticker_from_json(char *json, size_t len, struct discord_message_sticker **pp);
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
extern void discord_message_reference_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_reference_from_json(char *json, size_t len, struct discord_message_reference **pp);
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
extern void discord_message_application_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_application_from_json(char *json, size_t len, struct discord_message_application **pp);
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
extern void discord_message_activity_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_activity_from_json(char *json, size_t len, struct discord_message_activity **pp);
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
extern void discord_message_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_from_json(char *json, size_t len, struct discord_message **pp);
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

extern void discord_channel_followed_channel_cleanup_v(void *p);
extern void discord_channel_followed_channel_cleanup(struct discord_channel_followed_channel *p);
extern void discord_channel_followed_channel_init_v(void *p);
extern void discord_channel_followed_channel_init(struct discord_channel_followed_channel *p);
extern struct discord_channel_followed_channel * discord_channel_followed_channel_alloc();
extern void discord_channel_followed_channel_free_v(void *p);
extern void discord_channel_followed_channel_free(struct discord_channel_followed_channel *p);
extern void discord_channel_followed_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_followed_channel_from_json(char *json, size_t len, struct discord_channel_followed_channel **pp);
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

extern void discord_channel_reaction_cleanup_v(void *p);
extern void discord_channel_reaction_cleanup(struct discord_channel_reaction *p);
extern void discord_channel_reaction_init_v(void *p);
extern void discord_channel_reaction_init(struct discord_channel_reaction *p);
extern struct discord_channel_reaction * discord_channel_reaction_alloc();
extern void discord_channel_reaction_free_v(void *p);
extern void discord_channel_reaction_free(struct discord_channel_reaction *p);
extern void discord_channel_reaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_reaction_from_json(char *json, size_t len, struct discord_channel_reaction **pp);
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

extern void discord_channel_overwrite_cleanup_v(void *p);
extern void discord_channel_overwrite_cleanup(struct discord_channel_overwrite *p);
extern void discord_channel_overwrite_init_v(void *p);
extern void discord_channel_overwrite_init(struct discord_channel_overwrite *p);
extern struct discord_channel_overwrite * discord_channel_overwrite_alloc();
extern void discord_channel_overwrite_free_v(void *p);
extern void discord_channel_overwrite_free(struct discord_channel_overwrite *p);
extern void discord_channel_overwrite_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_overwrite_from_json(char *json, size_t len, struct discord_channel_overwrite **pp);
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

extern void discord_thread_metadata_cleanup_v(void *p);
extern void discord_thread_metadata_cleanup(struct discord_thread_metadata *p);
extern void discord_thread_metadata_init_v(void *p);
extern void discord_thread_metadata_init(struct discord_thread_metadata *p);
extern struct discord_thread_metadata * discord_thread_metadata_alloc();
extern void discord_thread_metadata_free_v(void *p);
extern void discord_thread_metadata_free(struct discord_thread_metadata *p);
extern void discord_thread_metadata_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_metadata_from_json(char *json, size_t len, struct discord_thread_metadata **pp);
extern size_t discord_thread_metadata_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_metadata_to_json(char *json, size_t len, struct discord_thread_metadata *p);
extern size_t discord_thread_metadata_to_query_v(char *json, size_t len, void *p);
extern size_t discord_thread_metadata_to_query(char *json, size_t len, struct discord_thread_metadata *p);
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
extern struct discord_thread_member * discord_thread_member_alloc();
extern void discord_thread_member_free_v(void *p);
extern void discord_thread_member_free(struct discord_thread_member *p);
extern void discord_thread_member_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_member_from_json(char *json, size_t len, struct discord_thread_member **pp);
extern size_t discord_thread_member_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_member_to_json(char *json, size_t len, struct discord_thread_member *p);
extern size_t discord_thread_member_to_query_v(char *json, size_t len, void *p);
extern size_t discord_thread_member_to_query(char *json, size_t len, struct discord_thread_member *p);
extern void discord_thread_member_list_free_v(void **p);
extern void discord_thread_member_list_free(struct discord_thread_member **p);
extern void discord_thread_member_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_member_list_from_json(char *str, size_t len, struct discord_thread_member ***p);
extern size_t discord_thread_member_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_member_list_to_json(char *str, size_t len, struct discord_thread_member **p);

extern void discord_channel_attachment_cleanup_v(void *p);
extern void discord_channel_attachment_cleanup(struct discord_channel_attachment *p);
extern void discord_channel_attachment_init_v(void *p);
extern void discord_channel_attachment_init(struct discord_channel_attachment *p);
extern struct discord_channel_attachment * discord_channel_attachment_alloc();
extern void discord_channel_attachment_free_v(void *p);
extern void discord_channel_attachment_free(struct discord_channel_attachment *p);
extern void discord_channel_attachment_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_attachment_from_json(char *json, size_t len, struct discord_channel_attachment **pp);
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
extern void discord_channel_mention_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_mention_from_json(char *json, size_t len, struct discord_channel_mention **pp);
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
extern void discord_channel_allowed_mentions_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_allowed_mentions_from_json(char *json, size_t len, struct discord_channel_allowed_mentions **pp);
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
extern void discord_embed_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_from_json(char *json, size_t len, struct discord_embed **pp);
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
extern void discord_embed_thumbnail_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_thumbnail_from_json(char *json, size_t len, struct discord_embed_thumbnail **pp);
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
extern void discord_embed_video_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_video_from_json(char *json, size_t len, struct discord_embed_video **pp);
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
extern void discord_embed_image_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_image_from_json(char *json, size_t len, struct discord_embed_image **pp);
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
extern void discord_embed_provider_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_provider_from_json(char *json, size_t len, struct discord_embed_provider **pp);
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
extern void discord_embed_author_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_author_from_json(char *json, size_t len, struct discord_embed_author **pp);
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
extern void discord_embed_footer_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_footer_from_json(char *json, size_t len, struct discord_embed_footer **pp);
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
extern void discord_embed_field_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_field_from_json(char *json, size_t len, struct discord_embed_field **pp);
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
/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see 
 */


extern void discord_create_guild_emoji_params_cleanup_v(void *p);
extern void discord_create_guild_emoji_params_cleanup(struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_init_v(void *p);
extern void discord_create_guild_emoji_params_init(struct discord_create_guild_emoji_params *p);
extern struct discord_create_guild_emoji_params * discord_create_guild_emoji_params_alloc();
extern void discord_create_guild_emoji_params_free_v(void *p);
extern void discord_create_guild_emoji_params_free(struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_emoji_params_from_json(char *json, size_t len, struct discord_create_guild_emoji_params **pp);
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

extern void discord_modify_guild_emoji_params_cleanup_v(void *p);
extern void discord_modify_guild_emoji_params_cleanup(struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_init_v(void *p);
extern void discord_modify_guild_emoji_params_init(struct discord_modify_guild_emoji_params *p);
extern struct discord_modify_guild_emoji_params * discord_modify_guild_emoji_params_alloc();
extern void discord_modify_guild_emoji_params_free_v(void *p);
extern void discord_modify_guild_emoji_params_free(struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_emoji_params_from_json(char *json, size_t len, struct discord_modify_guild_emoji_params **pp);
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
/* This file is generated from specs/discord/emoji.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/emoji
 */


extern void discord_emoji_cleanup_v(void *p);
extern void discord_emoji_cleanup(struct discord_emoji *p);
extern void discord_emoji_init_v(void *p);
extern void discord_emoji_init(struct discord_emoji *p);
extern struct discord_emoji * discord_emoji_alloc();
extern void discord_emoji_free_v(void *p);
extern void discord_emoji_free(struct discord_emoji *p);
extern void discord_emoji_from_json_v(char *json, size_t len, void *pp);
extern void discord_emoji_from_json(char *json, size_t len, struct discord_emoji **pp);
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
/* This file is generated from specs/discord/gateway.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/gateway
 */










extern void discord_gateway_identify_cleanup_v(void *p);
extern void discord_gateway_identify_cleanup(struct discord_gateway_identify *p);
extern void discord_gateway_identify_init_v(void *p);
extern void discord_gateway_identify_init(struct discord_gateway_identify *p);
extern struct discord_gateway_identify * discord_gateway_identify_alloc();
extern void discord_gateway_identify_free_v(void *p);
extern void discord_gateway_identify_free(struct discord_gateway_identify *p);
extern void discord_gateway_identify_from_json_v(char *json, size_t len, void *pp);
extern void discord_gateway_identify_from_json(char *json, size_t len, struct discord_gateway_identify **pp);
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

extern void discord_gateway_status_update_cleanup_v(void *p);
extern void discord_gateway_status_update_cleanup(struct discord_gateway_status_update *p);
extern void discord_gateway_status_update_init_v(void *p);
extern void discord_gateway_status_update_init(struct discord_gateway_status_update *p);
extern struct discord_gateway_status_update * discord_gateway_status_update_alloc();
extern void discord_gateway_status_update_free_v(void *p);
extern void discord_gateway_status_update_free(struct discord_gateway_status_update *p);
extern void discord_gateway_status_update_from_json_v(char *json, size_t len, void *pp);
extern void discord_gateway_status_update_from_json(char *json, size_t len, struct discord_gateway_status_update **pp);
extern size_t discord_gateway_status_update_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_status_update_to_json(char *json, size_t len, struct discord_gateway_status_update *p);
extern size_t discord_gateway_status_update_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_status_update_to_query(char *json, size_t len, struct discord_gateway_status_update *p);
extern void discord_gateway_status_update_list_free_v(void **p);
extern void discord_gateway_status_update_list_free(struct discord_gateway_status_update **p);
extern void discord_gateway_status_update_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_status_update_list_from_json(char *str, size_t len, struct discord_gateway_status_update ***p);
extern size_t discord_gateway_status_update_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_status_update_list_to_json(char *str, size_t len, struct discord_gateway_status_update **p);

extern void discord_gateway_identify_connection_cleanup_v(void *p);
extern void discord_gateway_identify_connection_cleanup(struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_init_v(void *p);
extern void discord_gateway_identify_connection_init(struct discord_gateway_identify_connection *p);
extern struct discord_gateway_identify_connection * discord_gateway_identify_connection_alloc();
extern void discord_gateway_identify_connection_free_v(void *p);
extern void discord_gateway_identify_connection_free(struct discord_gateway_identify_connection *p);
extern void discord_gateway_identify_connection_from_json_v(char *json, size_t len, void *pp);
extern void discord_gateway_identify_connection_from_json(char *json, size_t len, struct discord_gateway_identify_connection **pp);
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

extern void discord_gateway_activity_cleanup_v(void *p);
extern void discord_gateway_activity_cleanup(struct discord_gateway_activity *p);
extern void discord_gateway_activity_init_v(void *p);
extern void discord_gateway_activity_init(struct discord_gateway_activity *p);
extern struct discord_gateway_activity * discord_gateway_activity_alloc();
extern void discord_gateway_activity_free_v(void *p);
extern void discord_gateway_activity_free(struct discord_gateway_activity *p);
extern void discord_gateway_activity_from_json_v(char *json, size_t len, void *pp);
extern void discord_gateway_activity_from_json(char *json, size_t len, struct discord_gateway_activity **pp);
extern size_t discord_gateway_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_gateway_activity_to_json(char *json, size_t len, struct discord_gateway_activity *p);
extern size_t discord_gateway_activity_to_query_v(char *json, size_t len, void *p);
extern size_t discord_gateway_activity_to_query(char *json, size_t len, struct discord_gateway_activity *p);
extern void discord_gateway_activity_list_free_v(void **p);
extern void discord_gateway_activity_list_free(struct discord_gateway_activity **p);
extern void discord_gateway_activity_list_from_json_v(char *str, size_t len, void *p);
extern void discord_gateway_activity_list_from_json(char *str, size_t len, struct discord_gateway_activity ***p);
extern size_t discord_gateway_activity_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_gateway_activity_list_to_json(char *str, size_t len, struct discord_gateway_activity **p);


/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild-template
 */


extern void discord_create_guild_from_guild_template_params_cleanup_v(void *p);
extern void discord_create_guild_from_guild_template_params_cleanup(struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_init_v(void *p);
extern void discord_create_guild_from_guild_template_params_init(struct discord_create_guild_from_guild_template_params *p);
extern struct discord_create_guild_from_guild_template_params * discord_create_guild_from_guild_template_params_alloc();
extern void discord_create_guild_from_guild_template_params_free_v(void *p);
extern void discord_create_guild_from_guild_template_params_free(struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_from_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params **pp);
extern size_t discord_create_guild_from_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p);
extern size_t discord_create_guild_from_guild_template_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_to_query(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p);
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
extern struct discord_create_guild_template_params * discord_create_guild_template_params_alloc();
extern void discord_create_guild_template_params_free_v(void *p);
extern void discord_create_guild_template_params_free(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_template_params **pp);
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

extern void discord_modify_guild_template_params_cleanup_v(void *p);
extern void discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_init_v(void *p);
extern void discord_modify_guild_template_params_init(struct discord_modify_guild_template_params *p);
extern struct discord_modify_guild_template_params * discord_modify_guild_template_params_alloc();
extern void discord_modify_guild_template_params_free_v(void *p);
extern void discord_modify_guild_template_params_free(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_template_params_from_json(char *json, size_t len, struct discord_modify_guild_template_params **pp);
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
/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild-template
 */


extern void discord_guild_template_cleanup_v(void *p);
extern void discord_guild_template_cleanup(struct discord_guild_template *p);
extern void discord_guild_template_init_v(void *p);
extern void discord_guild_template_init(struct discord_guild_template *p);
extern struct discord_guild_template * discord_guild_template_alloc();
extern void discord_guild_template_free_v(void *p);
extern void discord_guild_template_free(struct discord_guild_template *p);
extern void discord_guild_template_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_template_from_json(char *json, size_t len, struct discord_guild_template **pp);
extern size_t discord_guild_template_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_template_to_json(char *json, size_t len, struct discord_guild_template *p);
extern size_t discord_guild_template_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_template_to_query(char *json, size_t len, struct discord_guild_template *p);
extern void discord_guild_template_list_free_v(void **p);
extern void discord_guild_template_list_free(struct discord_guild_template **p);
extern void discord_guild_template_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_template_list_from_json(char *str, size_t len, struct discord_guild_template ***p);
extern size_t discord_guild_template_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_template_list_to_json(char *str, size_t len, struct discord_guild_template **p);
/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild
 */


extern void discord_create_guild_params_cleanup_v(void *p);
extern void discord_create_guild_params_cleanup(struct discord_create_guild_params *p);
extern void discord_create_guild_params_init_v(void *p);
extern void discord_create_guild_params_init(struct discord_create_guild_params *p);
extern struct discord_create_guild_params * discord_create_guild_params_alloc();
extern void discord_create_guild_params_free_v(void *p);
extern void discord_create_guild_params_free(struct discord_create_guild_params *p);
extern void discord_create_guild_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_params_from_json(char *json, size_t len, struct discord_create_guild_params **pp);
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

extern void discord_modify_guild_params_cleanup_v(void *p);
extern void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_init_v(void *p);
extern void discord_modify_guild_params_init(struct discord_modify_guild_params *p);
extern struct discord_modify_guild_params * discord_modify_guild_params_alloc();
extern void discord_modify_guild_params_free_v(void *p);
extern void discord_modify_guild_params_free(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_params_from_json(char *json, size_t len, struct discord_modify_guild_params **pp);
extern size_t discord_modify_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_params_to_json(char *json, size_t len, struct discord_modify_guild_params *p);
extern size_t discord_modify_guild_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_params_to_query(char *json, size_t len, struct discord_modify_guild_params *p);
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
extern struct discord_create_guild_channel_params * discord_create_guild_channel_params_alloc();
extern void discord_create_guild_channel_params_free_v(void *p);
extern void discord_create_guild_channel_params_free(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_channel_params_from_json(char *json, size_t len, struct discord_create_guild_channel_params **pp);
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

extern void discord_modify_guild_channel_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_init_v(void *p);
extern void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *p);
extern struct discord_modify_guild_channel_positions_params * discord_modify_guild_channel_positions_params_alloc();
extern void discord_modify_guild_channel_positions_params_free_v(void *p);
extern void discord_modify_guild_channel_positions_params_free(struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_channel_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params **pp);
extern size_t discord_modify_guild_channel_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p);
extern size_t discord_modify_guild_channel_positions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_to_query(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_list_free_v(void **p);
extern void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **p);
extern void discord_modify_guild_channel_positions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_channel_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params ***p);
extern size_t discord_modify_guild_channel_positions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params **p);

extern void discord_search_guild_members_params_cleanup_v(void *p);
extern void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_init_v(void *p);
extern void discord_search_guild_members_params_init(struct discord_search_guild_members_params *p);
extern struct discord_search_guild_members_params * discord_search_guild_members_params_alloc();
extern void discord_search_guild_members_params_free_v(void *p);
extern void discord_search_guild_members_params_free(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_search_guild_members_params_from_json(char *json, size_t len, struct discord_search_guild_members_params **pp);
extern size_t discord_search_guild_members_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_search_guild_members_params_to_json(char *json, size_t len, struct discord_search_guild_members_params *p);
extern size_t discord_search_guild_members_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_search_guild_members_params_to_query(char *json, size_t len, struct discord_search_guild_members_params *p);
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
extern struct discord_add_guild_member_params * discord_add_guild_member_params_alloc();
extern void discord_add_guild_member_params_free_v(void *p);
extern void discord_add_guild_member_params_free(struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_add_guild_member_params_from_json(char *json, size_t len, struct discord_add_guild_member_params **pp);
extern size_t discord_add_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_add_guild_member_params_to_json(char *json, size_t len, struct discord_add_guild_member_params *p);
extern size_t discord_add_guild_member_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_add_guild_member_params_to_query(char *json, size_t len, struct discord_add_guild_member_params *p);
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
extern struct discord_modify_guild_member_params * discord_modify_guild_member_params_alloc();
extern void discord_modify_guild_member_params_free_v(void *p);
extern void discord_modify_guild_member_params_free(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_member_params_from_json(char *json, size_t len, struct discord_modify_guild_member_params **pp);
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

extern void discord_create_guild_role_params_cleanup_v(void *p);
extern void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_init_v(void *p);
extern void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p);
extern struct discord_create_guild_role_params * discord_create_guild_role_params_alloc();
extern void discord_create_guild_role_params_free_v(void *p);
extern void discord_create_guild_role_params_free(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params **pp);
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

extern void discord_modify_guild_role_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_init_v(void *p);
extern void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *p);
extern struct discord_modify_guild_role_positions_params * discord_modify_guild_role_positions_params_alloc();
extern void discord_modify_guild_role_positions_params_free_v(void *p);
extern void discord_modify_guild_role_positions_params_free(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_role_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_role_positions_params **pp);
extern size_t discord_modify_guild_role_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
extern size_t discord_modify_guild_role_positions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_to_query(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
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
extern struct discord_modify_guild_role_params * discord_modify_guild_role_params_alloc();
extern void discord_modify_guild_role_params_free_v(void *p);
extern void discord_modify_guild_role_params_free(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_role_params_from_json(char *json, size_t len, struct discord_modify_guild_role_params **pp);
extern size_t discord_modify_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_params_to_json(char *json, size_t len, struct discord_modify_guild_role_params *p);
extern size_t discord_modify_guild_role_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_params_to_query(char *json, size_t len, struct discord_modify_guild_role_params *p);
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
extern struct discord_get_guild_prune_count_params * discord_get_guild_prune_count_params_alloc();
extern void discord_get_guild_prune_count_params_free_v(void *p);
extern void discord_get_guild_prune_count_params_free(struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_guild_prune_count_params_from_json(char *json, size_t len, struct discord_get_guild_prune_count_params **pp);
extern size_t discord_get_guild_prune_count_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_to_json(char *json, size_t len, struct discord_get_guild_prune_count_params *p);
extern size_t discord_get_guild_prune_count_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_to_query(char *json, size_t len, struct discord_get_guild_prune_count_params *p);
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
extern struct discord_begin_guild_prune_params * discord_begin_guild_prune_params_alloc();
extern void discord_begin_guild_prune_params_free_v(void *p);
extern void discord_begin_guild_prune_params_free(struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_begin_guild_prune_params_from_json(char *json, size_t len, struct discord_begin_guild_prune_params **pp);
extern size_t discord_begin_guild_prune_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_to_json(char *json, size_t len, struct discord_begin_guild_prune_params *p);
extern size_t discord_begin_guild_prune_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_to_query(char *json, size_t len, struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_list_free_v(void **p);
extern void discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **p);
extern void discord_begin_guild_prune_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_begin_guild_prune_params_list_from_json(char *str, size_t len, struct discord_begin_guild_prune_params ***p);
extern size_t discord_begin_guild_prune_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_list_to_json(char *str, size_t len, struct discord_begin_guild_prune_params **p);
/* This file is generated from specs/discord/guild.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild
 */


extern void discord_guild_cleanup_v(void *p);
extern void discord_guild_cleanup(struct discord_guild *p);
extern void discord_guild_init_v(void *p);
extern void discord_guild_init(struct discord_guild *p);
extern struct discord_guild * discord_guild_alloc();
extern void discord_guild_free_v(void *p);
extern void discord_guild_free(struct discord_guild *p);
extern void discord_guild_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_from_json(char *json, size_t len, struct discord_guild **pp);
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















extern void discord_guild_unavailable_cleanup_v(void *p);
extern void discord_guild_unavailable_cleanup(struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_init_v(void *p);
extern void discord_guild_unavailable_init(struct discord_guild_unavailable *p);
extern struct discord_guild_unavailable * discord_guild_unavailable_alloc();
extern void discord_guild_unavailable_free_v(void *p);
extern void discord_guild_unavailable_free(struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_unavailable_from_json(char *json, size_t len, struct discord_guild_unavailable **pp);
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
extern void discord_guild_preview_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_preview_from_json(char *json, size_t len, struct discord_guild_preview **pp);
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
extern void discord_guild_widget_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_widget_from_json(char *json, size_t len, struct discord_guild_widget **pp);
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

extern void discord_guild_member_cleanup_v(void *p);
extern void discord_guild_member_cleanup(struct discord_guild_member *p);
extern void discord_guild_member_init_v(void *p);
extern void discord_guild_member_init(struct discord_guild_member *p);
extern struct discord_guild_member * discord_guild_member_alloc();
extern void discord_guild_member_free_v(void *p);
extern void discord_guild_member_free(struct discord_guild_member *p);
extern void discord_guild_member_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_member_from_json(char *json, size_t len, struct discord_guild_member **pp);
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

extern void discord_guild_integration_cleanup_v(void *p);
extern void discord_guild_integration_cleanup(struct discord_guild_integration *p);
extern void discord_guild_integration_init_v(void *p);
extern void discord_guild_integration_init(struct discord_guild_integration *p);
extern struct discord_guild_integration * discord_guild_integration_alloc();
extern void discord_guild_integration_free_v(void *p);
extern void discord_guild_integration_free(struct discord_guild_integration *p);
extern void discord_guild_integration_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_integration_from_json(char *json, size_t len, struct discord_guild_integration **pp);
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



extern void discord_guild_integration_account_cleanup_v(void *p);
extern void discord_guild_integration_account_cleanup(struct discord_guild_integration_account *p);
extern void discord_guild_integration_account_init_v(void *p);
extern void discord_guild_integration_account_init(struct discord_guild_integration_account *p);
extern struct discord_guild_integration_account * discord_guild_integration_account_alloc();
extern void discord_guild_integration_account_free_v(void *p);
extern void discord_guild_integration_account_free(struct discord_guild_integration_account *p);
extern void discord_guild_integration_account_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_integration_account_from_json(char *json, size_t len, struct discord_guild_integration_account **pp);
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
extern void discord_guild_integration_application_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_integration_application_from_json(char *json, size_t len, struct discord_guild_integration_application **pp);
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

extern void discord_guild_ban_cleanup_v(void *p);
extern void discord_guild_ban_cleanup(struct discord_guild_ban *p);
extern void discord_guild_ban_init_v(void *p);
extern void discord_guild_ban_init(struct discord_guild_ban *p);
extern struct discord_guild_ban * discord_guild_ban_alloc();
extern void discord_guild_ban_free_v(void *p);
extern void discord_guild_ban_free(struct discord_guild_ban *p);
extern void discord_guild_ban_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_ban_from_json(char *json, size_t len, struct discord_guild_ban **pp);
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

extern void discord_guild_welcome_screen_cleanup_v(void *p);
extern void discord_guild_welcome_screen_cleanup(struct discord_guild_welcome_screen *p);
extern void discord_guild_welcome_screen_init_v(void *p);
extern void discord_guild_welcome_screen_init(struct discord_guild_welcome_screen *p);
extern struct discord_guild_welcome_screen * discord_guild_welcome_screen_alloc();
extern void discord_guild_welcome_screen_free_v(void *p);
extern void discord_guild_welcome_screen_free(struct discord_guild_welcome_screen *p);
extern void discord_guild_welcome_screen_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_welcome_screen_from_json(char *json, size_t len, struct discord_guild_welcome_screen **pp);
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

extern void discord_guild_welcome_screen_channel_cleanup_v(void *p);
extern void discord_guild_welcome_screen_channel_cleanup(struct discord_guild_welcome_screen_channel *p);
extern void discord_guild_welcome_screen_channel_init_v(void *p);
extern void discord_guild_welcome_screen_channel_init(struct discord_guild_welcome_screen_channel *p);
extern struct discord_guild_welcome_screen_channel * discord_guild_welcome_screen_channel_alloc();
extern void discord_guild_welcome_screen_channel_free_v(void *p);
extern void discord_guild_welcome_screen_channel_free(struct discord_guild_welcome_screen_channel *p);
extern void discord_guild_welcome_screen_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_welcome_screen_channel_from_json(char *json, size_t len, struct discord_guild_welcome_screen_channel **pp);
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
/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/invite
 */


extern void discord_get_invite_params_cleanup_v(void *p);
extern void discord_get_invite_params_cleanup(struct discord_get_invite_params *p);
extern void discord_get_invite_params_init_v(void *p);
extern void discord_get_invite_params_init(struct discord_get_invite_params *p);
extern struct discord_get_invite_params * discord_get_invite_params_alloc();
extern void discord_get_invite_params_free_v(void *p);
extern void discord_get_invite_params_free(struct discord_get_invite_params *p);
extern void discord_get_invite_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_invite_params_from_json(char *json, size_t len, struct discord_get_invite_params **pp);
extern size_t discord_get_invite_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_invite_params_to_json(char *json, size_t len, struct discord_get_invite_params *p);
extern size_t discord_get_invite_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_get_invite_params_to_query(char *json, size_t len, struct discord_get_invite_params *p);
extern void discord_get_invite_params_list_free_v(void **p);
extern void discord_get_invite_params_list_free(struct discord_get_invite_params **p);
extern void discord_get_invite_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_invite_params_list_from_json(char *str, size_t len, struct discord_get_invite_params ***p);
extern size_t discord_get_invite_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_invite_params_list_to_json(char *str, size_t len, struct discord_get_invite_params **p);
/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/invite
 */




extern void discord_invite_cleanup_v(void *p);
extern void discord_invite_cleanup(struct discord_invite *p);
extern void discord_invite_init_v(void *p);
extern void discord_invite_init(struct discord_invite *p);
extern struct discord_invite * discord_invite_alloc();
extern void discord_invite_free_v(void *p);
extern void discord_invite_free(struct discord_invite *p);
extern void discord_invite_from_json_v(char *json, size_t len, void *pp);
extern void discord_invite_from_json(char *json, size_t len, struct discord_invite **pp);
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
extern void discord_invite_metadata_from_json_v(char *json, size_t len, void *pp);
extern void discord_invite_metadata_from_json(char *json, size_t len, struct discord_invite_metadata **pp);
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
/* This file is generated from specs/discord/message_components.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/interactions/message-components#message-components
 */


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
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/permissions
 */




extern void discord_permissions_role_cleanup_v(void *p);
extern void discord_permissions_role_cleanup(struct discord_permissions_role *p);
extern void discord_permissions_role_init_v(void *p);
extern void discord_permissions_role_init(struct discord_permissions_role *p);
extern struct discord_permissions_role * discord_permissions_role_alloc();
extern void discord_permissions_role_free_v(void *p);
extern void discord_permissions_role_free(struct discord_permissions_role *p);
extern void discord_permissions_role_from_json_v(char *json, size_t len, void *pp);
extern void discord_permissions_role_from_json(char *json, size_t len, struct discord_permissions_role **pp);
extern size_t discord_permissions_role_to_json_v(char *json, size_t len, void *p);
extern size_t discord_permissions_role_to_json(char *json, size_t len, struct discord_permissions_role *p);
extern size_t discord_permissions_role_to_query_v(char *json, size_t len, void *p);
extern size_t discord_permissions_role_to_query(char *json, size_t len, struct discord_permissions_role *p);
extern void discord_permissions_role_list_free_v(void **p);
extern void discord_permissions_role_list_free(struct discord_permissions_role **p);
extern void discord_permissions_role_list_from_json_v(char *str, size_t len, void *p);
extern void discord_permissions_role_list_from_json(char *str, size_t len, struct discord_permissions_role ***p);
extern size_t discord_permissions_role_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_permissions_role_list_to_json(char *str, size_t len, struct discord_permissions_role **p);

extern void discord_permissions_role_tags_cleanup_v(void *p);
extern void discord_permissions_role_tags_cleanup(struct discord_permissions_role_tags *p);
extern void discord_permissions_role_tags_init_v(void *p);
extern void discord_permissions_role_tags_init(struct discord_permissions_role_tags *p);
extern struct discord_permissions_role_tags * discord_permissions_role_tags_alloc();
extern void discord_permissions_role_tags_free_v(void *p);
extern void discord_permissions_role_tags_free(struct discord_permissions_role_tags *p);
extern void discord_permissions_role_tags_from_json_v(char *json, size_t len, void *pp);
extern void discord_permissions_role_tags_from_json(char *json, size_t len, struct discord_permissions_role_tags **pp);
extern size_t discord_permissions_role_tags_to_json_v(char *json, size_t len, void *p);
extern size_t discord_permissions_role_tags_to_json(char *json, size_t len, struct discord_permissions_role_tags *p);
extern size_t discord_permissions_role_tags_to_query_v(char *json, size_t len, void *p);
extern size_t discord_permissions_role_tags_to_query(char *json, size_t len, struct discord_permissions_role_tags *p);
extern void discord_permissions_role_tags_list_free_v(void **p);
extern void discord_permissions_role_tags_list_free(struct discord_permissions_role_tags **p);
extern void discord_permissions_role_tags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_permissions_role_tags_list_from_json(char *str, size_t len, struct discord_permissions_role_tags ***p);
extern size_t discord_permissions_role_tags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_permissions_role_tags_list_to_json(char *str, size_t len, struct discord_permissions_role_tags **p);
/* This file is generated from specs/discord/slash_commands.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/interactions/slash-commands#data-models-and-types
 */


extern void discord_application_command_cleanup_v(void *p);
extern void discord_application_command_cleanup(struct discord_application_command *p);
extern void discord_application_command_init_v(void *p);
extern void discord_application_command_init(struct discord_application_command *p);
extern struct discord_application_command * discord_application_command_alloc();
extern void discord_application_command_free_v(void *p);
extern void discord_application_command_free(struct discord_application_command *p);
extern void discord_application_command_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_from_json(char *json, size_t len, struct discord_application_command **pp);
extern size_t discord_application_command_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_to_json(char *json, size_t len, struct discord_application_command *p);
extern size_t discord_application_command_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_to_query(char *json, size_t len, struct discord_application_command *p);
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
extern struct discord_application_command_option * discord_application_command_option_alloc();
extern void discord_application_command_option_free_v(void *p);
extern void discord_application_command_option_free(struct discord_application_command_option *p);
extern void discord_application_command_option_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_option_from_json(char *json, size_t len, struct discord_application_command_option **pp);
extern size_t discord_application_command_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_to_json(char *json, size_t len, struct discord_application_command_option *p);
extern size_t discord_application_command_option_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_to_query(char *json, size_t len, struct discord_application_command_option *p);
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
extern struct discord_application_command_option_choice * discord_application_command_option_choice_alloc();
extern void discord_application_command_option_choice_free_v(void *p);
extern void discord_application_command_option_choice_free(struct discord_application_command_option_choice *p);
extern void discord_application_command_option_choice_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_option_choice_from_json(char *json, size_t len, struct discord_application_command_option_choice **pp);
extern size_t discord_application_command_option_choice_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_choice_to_json(char *json, size_t len, struct discord_application_command_option_choice *p);
extern size_t discord_application_command_option_choice_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_option_choice_to_query(char *json, size_t len, struct discord_application_command_option_choice *p);
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
extern struct discord_guild_application_command_permissions * discord_guild_application_command_permissions_alloc();
extern void discord_guild_application_command_permissions_free_v(void *p);
extern void discord_guild_application_command_permissions_free(struct discord_guild_application_command_permissions *p);
extern void discord_guild_application_command_permissions_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_application_command_permissions_from_json(char *json, size_t len, struct discord_guild_application_command_permissions **pp);
extern size_t discord_guild_application_command_permissions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_to_json(char *json, size_t len, struct discord_guild_application_command_permissions *p);
extern size_t discord_guild_application_command_permissions_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_application_command_permissions_to_query(char *json, size_t len, struct discord_guild_application_command_permissions *p);
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
extern struct discord_application_command_permissions * discord_application_command_permissions_alloc();
extern void discord_application_command_permissions_free_v(void *p);
extern void discord_application_command_permissions_free(struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_permissions_from_json(char *json, size_t len, struct discord_application_command_permissions **pp);
extern size_t discord_application_command_permissions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_permissions_to_json(char *json, size_t len, struct discord_application_command_permissions *p);
extern size_t discord_application_command_permissions_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_permissions_to_query(char *json, size_t len, struct discord_application_command_permissions *p);
extern void discord_application_command_permissions_list_free_v(void **p);
extern void discord_application_command_permissions_list_free(struct discord_application_command_permissions **p);
extern void discord_application_command_permissions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_permissions_list_from_json(char *str, size_t len, struct discord_application_command_permissions ***p);
extern size_t discord_application_command_permissions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_permissions_list_to_json(char *str, size_t len, struct discord_application_command_permissions **p);



extern void discord_interaction_cleanup_v(void *p);
extern void discord_interaction_cleanup(struct discord_interaction *p);
extern void discord_interaction_init_v(void *p);
extern void discord_interaction_init(struct discord_interaction *p);
extern struct discord_interaction * discord_interaction_alloc();
extern void discord_interaction_free_v(void *p);
extern void discord_interaction_free(struct discord_interaction *p);
extern void discord_interaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_from_json(char *json, size_t len, struct discord_interaction **pp);
extern size_t discord_interaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_to_json(char *json, size_t len, struct discord_interaction *p);
extern size_t discord_interaction_to_query_v(char *json, size_t len, void *p);
extern size_t discord_interaction_to_query(char *json, size_t len, struct discord_interaction *p);
extern void discord_interaction_list_free_v(void **p);
extern void discord_interaction_list_free(struct discord_interaction **p);
extern void discord_interaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_list_from_json(char *str, size_t len, struct discord_interaction ***p);
extern size_t discord_interaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_list_to_json(char *str, size_t len, struct discord_interaction **p);



extern void discord_application_command_interaction_data_cleanup_v(void *p);
extern void discord_application_command_interaction_data_cleanup(struct discord_application_command_interaction_data *p);
extern void discord_application_command_interaction_data_init_v(void *p);
extern void discord_application_command_interaction_data_init(struct discord_application_command_interaction_data *p);
extern struct discord_application_command_interaction_data * discord_application_command_interaction_data_alloc();
extern void discord_application_command_interaction_data_free_v(void *p);
extern void discord_application_command_interaction_data_free(struct discord_application_command_interaction_data *p);
extern void discord_application_command_interaction_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_interaction_data_from_json(char *json, size_t len, struct discord_application_command_interaction_data **pp);
extern size_t discord_application_command_interaction_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_to_json(char *json, size_t len, struct discord_application_command_interaction_data *p);
extern size_t discord_application_command_interaction_data_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_to_query(char *json, size_t len, struct discord_application_command_interaction_data *p);
extern void discord_application_command_interaction_data_list_free_v(void **p);
extern void discord_application_command_interaction_data_list_free(struct discord_application_command_interaction_data **p);
extern void discord_application_command_interaction_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_interaction_data_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data ***p);
extern size_t discord_application_command_interaction_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_interaction_data_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data **p);

extern void discord_application_command_interaction_data_resolved_cleanup_v(void *p);
extern void discord_application_command_interaction_data_resolved_cleanup(struct discord_application_command_interaction_data_resolved *p);
extern void discord_application_command_interaction_data_resolved_init_v(void *p);
extern void discord_application_command_interaction_data_resolved_init(struct discord_application_command_interaction_data_resolved *p);
extern struct discord_application_command_interaction_data_resolved * discord_application_command_interaction_data_resolved_alloc();
extern void discord_application_command_interaction_data_resolved_free_v(void *p);
extern void discord_application_command_interaction_data_resolved_free(struct discord_application_command_interaction_data_resolved *p);
extern void discord_application_command_interaction_data_resolved_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_interaction_data_resolved_from_json(char *json, size_t len, struct discord_application_command_interaction_data_resolved **pp);
extern size_t discord_application_command_interaction_data_resolved_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_resolved_to_json(char *json, size_t len, struct discord_application_command_interaction_data_resolved *p);
extern size_t discord_application_command_interaction_data_resolved_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_resolved_to_query(char *json, size_t len, struct discord_application_command_interaction_data_resolved *p);
extern void discord_application_command_interaction_data_resolved_list_free_v(void **p);
extern void discord_application_command_interaction_data_resolved_list_free(struct discord_application_command_interaction_data_resolved **p);
extern void discord_application_command_interaction_data_resolved_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_interaction_data_resolved_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_resolved ***p);
extern size_t discord_application_command_interaction_data_resolved_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_interaction_data_resolved_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_resolved **p);

extern void discord_application_command_interaction_data_option_cleanup_v(void *p);
extern void discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_init_v(void *p);
extern void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *p);
extern struct discord_application_command_interaction_data_option * discord_application_command_interaction_data_option_alloc();
extern void discord_application_command_interaction_data_option_free_v(void *p);
extern void discord_application_command_interaction_data_option_free(struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_command_interaction_data_option_from_json(char *json, size_t len, struct discord_application_command_interaction_data_option **pp);
extern size_t discord_application_command_interaction_data_option_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_to_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p);
extern size_t discord_application_command_interaction_data_option_to_query_v(char *json, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_to_query(char *json, size_t len, struct discord_application_command_interaction_data_option *p);
extern void discord_application_command_interaction_data_option_list_free_v(void **p);
extern void discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option **p);
extern void discord_application_command_interaction_data_option_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_command_interaction_data_option_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_option ***p);
extern size_t discord_application_command_interaction_data_option_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_command_interaction_data_option_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_option **p);

extern void discord_interaction_response_cleanup_v(void *p);
extern void discord_interaction_response_cleanup(struct discord_interaction_response *p);
extern void discord_interaction_response_init_v(void *p);
extern void discord_interaction_response_init(struct discord_interaction_response *p);
extern struct discord_interaction_response * discord_interaction_response_alloc();
extern void discord_interaction_response_free_v(void *p);
extern void discord_interaction_response_free(struct discord_interaction_response *p);
extern void discord_interaction_response_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_response_from_json(char *json, size_t len, struct discord_interaction_response **pp);
extern size_t discord_interaction_response_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_response_to_json(char *json, size_t len, struct discord_interaction_response *p);
extern size_t discord_interaction_response_to_query_v(char *json, size_t len, void *p);
extern size_t discord_interaction_response_to_query(char *json, size_t len, struct discord_interaction_response *p);
extern void discord_interaction_response_list_free_v(void **p);
extern void discord_interaction_response_list_free(struct discord_interaction_response **p);
extern void discord_interaction_response_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_response_list_from_json(char *str, size_t len, struct discord_interaction_response ***p);
extern size_t discord_interaction_response_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_response_list_to_json(char *str, size_t len, struct discord_interaction_response **p);



extern void discord_interaction_application_command_callback_data_cleanup_v(void *p);
extern void discord_interaction_application_command_callback_data_cleanup(struct discord_interaction_application_command_callback_data *p);
extern void discord_interaction_application_command_callback_data_init_v(void *p);
extern void discord_interaction_application_command_callback_data_init(struct discord_interaction_application_command_callback_data *p);
extern struct discord_interaction_application_command_callback_data * discord_interaction_application_command_callback_data_alloc();
extern void discord_interaction_application_command_callback_data_free_v(void *p);
extern void discord_interaction_application_command_callback_data_free(struct discord_interaction_application_command_callback_data *p);
extern void discord_interaction_application_command_callback_data_from_json_v(char *json, size_t len, void *pp);
extern void discord_interaction_application_command_callback_data_from_json(char *json, size_t len, struct discord_interaction_application_command_callback_data **pp);
extern size_t discord_interaction_application_command_callback_data_to_json_v(char *json, size_t len, void *p);
extern size_t discord_interaction_application_command_callback_data_to_json(char *json, size_t len, struct discord_interaction_application_command_callback_data *p);
extern size_t discord_interaction_application_command_callback_data_to_query_v(char *json, size_t len, void *p);
extern size_t discord_interaction_application_command_callback_data_to_query(char *json, size_t len, struct discord_interaction_application_command_callback_data *p);
extern void discord_interaction_application_command_callback_data_list_free_v(void **p);
extern void discord_interaction_application_command_callback_data_list_free(struct discord_interaction_application_command_callback_data **p);
extern void discord_interaction_application_command_callback_data_list_from_json_v(char *str, size_t len, void *p);
extern void discord_interaction_application_command_callback_data_list_from_json(char *str, size_t len, struct discord_interaction_application_command_callback_data ***p);
extern size_t discord_interaction_application_command_callback_data_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_interaction_application_command_callback_data_list_to_json(char *str, size_t len, struct discord_interaction_application_command_callback_data **p);



extern void discord_message_interaction_cleanup_v(void *p);
extern void discord_message_interaction_cleanup(struct discord_message_interaction *p);
extern void discord_message_interaction_init_v(void *p);
extern void discord_message_interaction_init(struct discord_message_interaction *p);
extern struct discord_message_interaction * discord_message_interaction_alloc();
extern void discord_message_interaction_free_v(void *p);
extern void discord_message_interaction_free(struct discord_message_interaction *p);
extern void discord_message_interaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_interaction_from_json(char *json, size_t len, struct discord_message_interaction **pp);
extern size_t discord_message_interaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_interaction_to_json(char *json, size_t len, struct discord_message_interaction *p);
extern size_t discord_message_interaction_to_query_v(char *json, size_t len, void *p);
extern size_t discord_message_interaction_to_query(char *json, size_t len, struct discord_message_interaction *p);
extern void discord_message_interaction_list_free_v(void **p);
extern void discord_message_interaction_list_free(struct discord_message_interaction **p);
extern void discord_message_interaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_interaction_list_from_json(char *str, size_t len, struct discord_message_interaction ***p);
extern size_t discord_message_interaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_interaction_list_to_json(char *str, size_t len, struct discord_message_interaction **p);
/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/user
 */


extern void discord_modify_current_user_params_cleanup_v(void *p);
extern void discord_modify_current_user_params_cleanup(struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_init_v(void *p);
extern void discord_modify_current_user_params_init(struct discord_modify_current_user_params *p);
extern struct discord_modify_current_user_params * discord_modify_current_user_params_alloc();
extern void discord_modify_current_user_params_free_v(void *p);
extern void discord_modify_current_user_params_free(struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_current_user_params_from_json(char *json, size_t len, struct discord_modify_current_user_params **pp);
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

extern void discord_create_group_dm_params_cleanup_v(void *p);
extern void discord_create_group_dm_params_cleanup(struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_init_v(void *p);
extern void discord_create_group_dm_params_init(struct discord_create_group_dm_params *p);
extern struct discord_create_group_dm_params * discord_create_group_dm_params_alloc();
extern void discord_create_group_dm_params_free_v(void *p);
extern void discord_create_group_dm_params_free(struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_group_dm_params_from_json(char *json, size_t len, struct discord_create_group_dm_params **pp);
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
/* This file is generated from specs/discord/user.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/user
 */






extern void discord_user_cleanup_v(void *p);
extern void discord_user_cleanup(struct discord_user *p);
extern void discord_user_init_v(void *p);
extern void discord_user_init(struct discord_user *p);
extern struct discord_user * discord_user_alloc();
extern void discord_user_free_v(void *p);
extern void discord_user_free(struct discord_user *p);
extern void discord_user_from_json_v(char *json, size_t len, void *pp);
extern void discord_user_from_json(char *json, size_t len, struct discord_user **pp);
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
extern void discord_connection_from_json_v(char *json, size_t len, void *pp);
extern void discord_connection_from_json(char *json, size_t len, struct discord_connection **pp);
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
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/voice-connections
 */







/* This file is generated from specs/discord/voice.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/voice
 */


extern void discord_voice_state_cleanup_v(void *p);
extern void discord_voice_state_cleanup(struct discord_voice_state *p);
extern void discord_voice_state_init_v(void *p);
extern void discord_voice_state_init(struct discord_voice_state *p);
extern struct discord_voice_state * discord_voice_state_alloc();
extern void discord_voice_state_free_v(void *p);
extern void discord_voice_state_free(struct discord_voice_state *p);
extern void discord_voice_state_from_json_v(char *json, size_t len, void *pp);
extern void discord_voice_state_from_json(char *json, size_t len, struct discord_voice_state **pp);
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
extern void discord_voice_region_from_json_v(char *json, size_t len, void *pp);
extern void discord_voice_region_from_json(char *json, size_t len, struct discord_voice_region **pp);
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
/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/webhook
 */


extern void discord_create_webhook_params_cleanup_v(void *p);
extern void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_init_v(void *p);
extern void discord_create_webhook_params_init(struct discord_create_webhook_params *p);
extern struct discord_create_webhook_params * discord_create_webhook_params_alloc();
extern void discord_create_webhook_params_free_v(void *p);
extern void discord_create_webhook_params_free(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_webhook_params_from_json(char *json, size_t len, struct discord_create_webhook_params **pp);
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

extern void discord_modify_webhook_params_cleanup_v(void *p);
extern void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_init_v(void *p);
extern void discord_modify_webhook_params_init(struct discord_modify_webhook_params *p);
extern struct discord_modify_webhook_params * discord_modify_webhook_params_alloc();
extern void discord_modify_webhook_params_free_v(void *p);
extern void discord_modify_webhook_params_free(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_webhook_params_from_json(char *json, size_t len, struct discord_modify_webhook_params **pp);
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

extern void discord_execute_webhook_params_cleanup_v(void *p);
extern void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_init_v(void *p);
extern void discord_execute_webhook_params_init(struct discord_execute_webhook_params *p);
extern struct discord_execute_webhook_params * discord_execute_webhook_params_alloc();
extern void discord_execute_webhook_params_free_v(void *p);
extern void discord_execute_webhook_params_free(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_execute_webhook_params_from_json(char *json, size_t len, struct discord_execute_webhook_params **pp);
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

extern void discord_edit_webhook_message_params_cleanup_v(void *p);
extern void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_init_v(void *p);
extern void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *p);
extern struct discord_edit_webhook_message_params * discord_edit_webhook_message_params_alloc();
extern void discord_edit_webhook_message_params_free_v(void *p);
extern void discord_edit_webhook_message_params_free(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_edit_webhook_message_params **pp);
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
/* This file is generated from specs/discord/webhook.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_functions.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/webhook
 */


extern void discord_webhook_cleanup_v(void *p);
extern void discord_webhook_cleanup(struct discord_webhook *p);
extern void discord_webhook_init_v(void *p);
extern void discord_webhook_init(struct discord_webhook *p);
extern struct discord_webhook * discord_webhook_alloc();
extern void discord_webhook_free_v(void *p);
extern void discord_webhook_free(struct discord_webhook *p);
extern void discord_webhook_from_json_v(char *json, size_t len, void *pp);
extern void discord_webhook_from_json(char *json, size_t len, struct discord_webhook **pp);
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


