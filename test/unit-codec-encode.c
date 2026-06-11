#include "discord_codecs.h"
#include "test-utils.h"

/* Encode verification for the generated codecs: params types are built
 * in C and their _to_json output asserted by path (key names, presence,
 * values — never whole-buffer string equality); resource types decoded
 * from a B01 fixture are re-encoded and compared path-by-path against
 * the fixture.
 *
 * Round-trip comparison is fixture→encoded on curated path lists only:
 * the encoders emit every struct field (defaults included), so a full
 * document diff cannot hold in either direction.  One-way fields are
 * excluded per type with a comment each. */

static char *
load(const char *name, size_t *len)
{
    char path[512];
    char *buf = NULL;

    snprintf(path, sizeof(path), "fixtures/%s", name);
    if (0 != test_load_fixture(path, &buf, len)) return NULL;
    return buf;
}

/* ── params encode ────────────────────────────────────────────────── */

TEST encode_create_message(void)
{
    struct discord_create_message params = {
        .content = "hello from concord",
        .embeds =
            &(struct discord_embeds){
                .size = 1,
                .array =
                    &(struct discord_embed){
                        .title = "embed title",
                        .description = "embed description",
                        .color = 3447003,
                    },
            },
        .components =
            &(struct discord_components){
                .size = 1,
                .array =
                    &(struct discord_component){
                        .type = DISCORD_COMPONENT_ACTION_ROW,
                        .components =
                            &(struct discord_components){
                                .size = 1,
                                .array =
                                    &(struct discord_component){
                                        .type = DISCORD_COMPONENT_BUTTON,
                                        .style = DISCORD_BUTTON_PRIMARY,
                                        .label = "Click me",
                                        .custom_id = "btn_click",
                                    },
                            },
                    },
            },
        .message_reference =
            &(struct discord_message_reference){
                .message_id = 1000000000000000100ULL,
                .channel_id = 1000000000000000020ULL,
            },
    };
    char *buf = NULL;
    size_t size = 0;
    test_json out;

    ASSERT_EQ(CCORD_OK, discord_create_message_to_json(&buf, &size, &params));
    ASSERT_EQ(0, test_json_load(&out, buf, size));
    ASSERT_JSON_PATH_STR(&out, "content", "hello from concord");
    ASSERT_JSON_PATH_STR(&out, "embeds.0.title", "embed title");
    ASSERT_JSON_PATH_STR(&out, "embeds.0.description", "embed description");
    ASSERT_JSON_PATH_STR(&out, "embeds.0.color", "3447003");
    ASSERT_JSON_PATH_STR(&out, "components.0.type", "1");
    ASSERT_JSON_PATH_STR(&out, "components.0.components.0.custom_id",
                         "btn_click");
    ASSERT_JSON_PATH_STR(&out, "components.0.components.0.label", "Click me");
    ASSERT_JSON_PATH_STR(&out, "message_reference.message_id",
                         "1000000000000000100");
    ASSERT_JSON_ABSENT(&out, "sticker_ids");
    ASSERT_JSON_ABSENT(&out, "attachments");

    test_json_unload(&out);
    free(buf);
    PASS();
}

TEST encode_edit_message(void)
{
    struct discord_edit_message params = {
        .content = "edited content",
        .flags = 4, /* SUPPRESS_EMBEDS */
    };
    char *buf = NULL;
    size_t size = 0;
    test_json out;

    ASSERT_EQ(CCORD_OK, discord_edit_message_to_json(&buf, &size, &params));
    ASSERT_EQ(0, test_json_load(&out, buf, size));
    ASSERT_JSON_PATH_STR(&out, "content", "edited content");
    ASSERT_JSON_PATH_STR(&out, "flags", "4");

    test_json_unload(&out);
    free(buf);
    PASS();
}

TEST encode_interaction_response(void)
{
    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
        .data =
            &(struct discord_interaction_callback_data){
                .content = "pong",
                .tts = false,
            },
    };
    char *buf = NULL;
    size_t size = 0;
    test_json out;

    ASSERT_EQ(CCORD_OK,
              discord_interaction_response_to_json(&buf, &size, &params));
    ASSERT_EQ(0, test_json_load(&out, buf, size));
    ASSERT_JSON_PATH_STR(&out, "type", "4");
    ASSERT_JSON_PATH_STR(&out, "data.content", "pong");

    test_json_unload(&out);
    free(buf);
    PASS();
}

TEST encode_modify_guild(void)
{
    struct discord_modify_guild params = {
        .reason = "audit log reason",
        .name = "Renamed Guild",
        .description = "new description",
        .preferred_locale = "en-US",
    };
    char *buf = NULL;
    size_t size = 0;
    test_json out;

    ASSERT_EQ(CCORD_OK, discord_modify_guild_to_json(&buf, &size, &params));
    ASSERT_EQ(0, test_json_load(&out, buf, size));
    ASSERT_JSON_PATH_STR(&out, "name", "Renamed Guild");
    ASSERT_JSON_PATH_STR(&out, "description", "new description");
    ASSERT_JSON_PATH_STR(&out, "preferred_locale", "en-US");
    /* reason is the X-Audit-Log-Reason header, never the JSON body */
    ASSERT_JSON_ABSENT(&out, "reason");

    test_json_unload(&out);
    free(buf);
    PASS();
}

TEST encode_modify_channel(void)
{
    struct discord_modify_channel params = {
        .reason = "audit log reason",
        .name = "renamed-channel",
        .topic = "new topic",
        .rate_limit_per_user = 5,
        .parent_id = 1000000000000000024ULL,
    };
    char *buf = NULL;
    size_t size = 0;
    test_json out;

    ASSERT_EQ(CCORD_OK, discord_modify_channel_to_json(&buf, &size, &params));
    ASSERT_EQ(0, test_json_load(&out, buf, size));
    ASSERT_JSON_PATH_STR(&out, "name", "renamed-channel");
    ASSERT_JSON_PATH_STR(&out, "topic", "new topic");
    ASSERT_JSON_PATH_STR(&out, "rate_limit_per_user", "5");
    ASSERT_JSON_PATH_STR(&out, "parent_id", "1000000000000000024");
    ASSERT_JSON_ABSENT(&out, "reason");

    test_json_unload(&out);
    free(buf);
    PASS();
}

TEST encode_create_guild_role(void)
{
    struct discord_create_guild_role params = {
        .name = "new-role",
        .permissions = 2048,
        .color = 15844367,
        .hoist = true,
        .mentionable = true,
    };
    char *buf = NULL;
    size_t size = 0;
    test_json out;

    ASSERT_EQ(CCORD_OK,
              discord_create_guild_role_to_json(&buf, &size, &params));
    ASSERT_EQ(0, test_json_load(&out, buf, size));
    ASSERT_JSON_PATH_STR(&out, "name", "new-role");
    ASSERT_JSON_PATH_STR(&out, "permissions", "2048");
    ASSERT_JSON_PATH_STR(&out, "color", "15844367");
    ASSERT_JSON_PATH_STR(&out, "hoist", "true");
    ASSERT_JSON_PATH_STR(&out, "mentionable", "true");

    test_json_unload(&out);
    free(buf);
    PASS();
}

TEST encode_modify_guild_role(void)
{
    struct discord_modify_guild_role params = {
        .reason = "audit log reason",
        .name = "renamed-role",
        .color = 3066993,
    };
    char *buf = NULL;
    size_t size = 0;
    test_json out;

    ASSERT_EQ(CCORD_OK,
              discord_modify_guild_role_to_json(&buf, &size, &params));
    ASSERT_EQ(0, test_json_load(&out, buf, size));
    ASSERT_JSON_PATH_STR(&out, "name", "renamed-role");
    ASSERT_JSON_PATH_STR(&out, "color", "3066993");
    ASSERT_JSON_ABSENT(&out, "reason");

    test_json_unload(&out);
    free(buf);
    PASS();
}

SUITE(params_encode)
{
    RUN_TEST(encode_create_message);
    RUN_TEST(encode_edit_message);
    RUN_TEST(encode_interaction_response);
    RUN_TEST(encode_modify_guild);
    RUN_TEST(encode_modify_channel);
    RUN_TEST(encode_create_guild_role);
    RUN_TEST(encode_modify_guild_role);
}

/* ── round trip ───────────────────────────────────────────────────── */

static greatest_test_res
assert_same_paths(const test_json *fix, const test_json *out,
                  const char *const *paths, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i)
        ASSERT_JSON_SAME(fix, out, paths[i]);
    PASS();
}

#define PATHS_LEN(paths) (sizeof(paths) / sizeof *(paths))

/* Decode FIXTURE into a struct TYPE, re-encode it, and assert every
 * path in PATHS is textually identical in fixture and output. */
#define DEFINE_ROUNDTRIP_TEST(tname, type, prefix, fixture, paths)         \
    TEST tname(void)                                                       \
    {                                                                      \
        size_t len, out_len = 0;                                           \
        char *js = load((fixture), &len), *out_buf = NULL;                 \
        struct type obj;                                                   \
        test_json fix, out;                                                \
                                                                           \
        ASSERT_NEQ(NULL, js);                                              \
        memset(&obj, 0, sizeof(obj));                                      \
        ASSERT_GT(prefix##_from_json(js, len, &obj), 0);                   \
        ASSERT_EQ(CCORD_OK, prefix##_to_json(&out_buf, &out_len, &obj));   \
        ASSERT_EQ(0, test_json_load(&fix, js, len));                       \
        ASSERT_EQ(0, test_json_load(&out, out_buf, out_len));              \
        CHECK_CALL(assert_same_paths(&fix, &out, (paths),                  \
                                     PATHS_LEN(paths)));                   \
        test_json_unload(&out);                                            \
        test_json_unload(&fix);                                            \
        prefix##_cleanup(&obj);                                            \
        free(out_buf);                                                     \
        free(js);                                                          \
        PASS();                                                            \
    }

static const char *const user_rt_paths[] = {
    "id", "username", "discriminator", "avatar", "bot", "system",
    "mfa_enabled", "banner", "accent_color", "locale", "verified", "email",
    "flags", "premium_type", "public_flags",
};
DEFINE_ROUNDTRIP_TEST(roundtrip_user, discord_user, discord_user,
                      "user-basic.json", user_rt_paths)

static const char *const guild_rt_paths[] = {
    "id", "name", "icon", "splash", "owner_id", "afk_timeout",
    "widget_enabled", "verification_level", "default_message_notifications",
    "explicit_content_filter", "roles.1.name", "roles.1.permissions",
    "emojis.0.name", "features.0", "mfa_level", "vanity_url_code",
    "description", "banner", "premium_tier", "premium_subscription_count",
    "preferred_locale", "premium_progress_bar_enabled",
};
/* Excluded from the guild round trip:
 *  - "joined_at": u64unix_ms re-encodes via cog_unix_ms_to_iso8601,
 *    textually different from the docs' microsecond/offset form.
 *  - "discovery_splash", "afk_channel_id", "application_id": null in
 *    the fixture; null-valued scalars re-encode as ""/"0". */
DEFINE_ROUNDTRIP_TEST(roundtrip_guild, discord_guild, discord_guild,
                      "guild-basic.json", guild_rt_paths)

static const char *const member_rt_paths[] = {
    "user.id", "user.username", "user.discriminator", "nick", "roles.0",
    "roles.1", "deaf", "mute", "pending",
};
/* Excluded: "joined_at"/"premium_since" (timestamp form, see guild);
 * "avatar"/"communication_disabled_until" (null in the fixture). */
DEFINE_ROUNDTRIP_TEST(roundtrip_member, discord_guild_member,
                      discord_guild_member, "guild-member-basic.json",
                      member_rt_paths)

static const char *const channel_rt_paths[] = {
    "id", "type", "guild_id", "position", "name", "topic", "nsfw",
    "last_message_id", "rate_limit_per_user", "parent_id",
    "default_auto_archive_duration", "permission_overwrites.0.id",
    "permission_overwrites.0.type", "permission_overwrites.0.allow",
    "permission_overwrites.0.deny",
};
DEFINE_ROUNDTRIP_TEST(roundtrip_channel, discord_channel, discord_channel,
                      "channel-text.json", channel_rt_paths)

static const char *const message_rt_paths[] = {
    "id", "channel_id", "author.id", "author.username", "author.bot",
    "content", "tts", "mention_everyone", "pinned", "type",
    "embeds.0.title", "embeds.0.type", "embeds.0.description",
    "embeds.0.url", "embeds.0.color", "embeds.0.footer.text",
    "embeds.0.image.url", "embeds.0.author.name", "embeds.0.fields.0.name",
    "embeds.0.fields.0.value", "embeds.0.fields.0.inline",
    "embeds.0.fields.1.inline", "embeds.1.title",
};
/* Excluded: "timestamp"/"edited_timestamp"/"embeds.0.timestamp"
 * (timestamp form, see guild). */
DEFINE_ROUNDTRIP_TEST(roundtrip_message, discord_message, discord_message,
                      "message-with-embeds.json", message_rt_paths)

static const char *const role_rt_paths[] = {
    "id", "name", "color", "hoist", "position", "permissions", "managed",
    "mentionable",
};
/* Excluded: "icon"/"unicode_emoji" (null in the fixture). */
DEFINE_ROUNDTRIP_TEST(roundtrip_role, discord_role, discord_role,
                      "role-basic.json", role_rt_paths)

static const char *const emoji_rt_paths[] = {
    "id", "name", "roles.0", "user.id", "user.username", "require_colons",
    "managed", "animated", "available",
};
DEFINE_ROUNDTRIP_TEST(roundtrip_emoji, discord_emoji, discord_emoji,
                      "emoji-custom.json", emoji_rt_paths)

static const char *const interaction_rt_paths[] = {
    "id", "application_id", "type", "data.custom_id", "data.component_type",
    "guild_id", "channel_id", "member.user.id", "member.user.username",
    "message.id", "message.content", "message.author.id", "token",
    "version", "locale",
};
/* The slash-command fixture is excluded from round-tripping entirely:
 * data.options[].value is a json_char* (polymorphic raw token), which
 * decodes with its quotes stripped and re-encodes as a bare token —
 * a decoded string value would produce malformed JSON.  The component
 * interaction exercises the same envelope without that field.
 * Excluded paths: "member.joined_at"/"message.timestamp" (timestamp
 * form, see guild). */
DEFINE_ROUNDTRIP_TEST(roundtrip_interaction, discord_interaction,
                      discord_interaction,
                      "interaction-message-component.json",
                      interaction_rt_paths)

SUITE(roundtrip)
{
    RUN_TEST(roundtrip_user);
    RUN_TEST(roundtrip_guild);
    RUN_TEST(roundtrip_member);
    RUN_TEST(roundtrip_channel);
    RUN_TEST(roundtrip_message);
    RUN_TEST(roundtrip_role);
    RUN_TEST(roundtrip_emoji);
    RUN_TEST(roundtrip_interaction);
}

/* ── seeded regression: discord_modify_guild_sticker.reason ──────── */

/* Pins commit 7eec9aef: the reason field exists on the params struct
 * (GENCODECS_RECIPE == DATA guard in gencodecs/api/sticker.PRE.h) but
 * is the X-Audit-Log-Reason header param and must never reach the
 * JSON body. */
TEST modify_guild_sticker_reason_not_encoded(void)
{
    size_t len, out_len = 0;
    char *js = load("modify-guild-sticker-params.json", &len);
    char *out_buf = NULL;
    struct discord_modify_guild_sticker params = { 0 };
    test_json out;

    ASSERT_NEQ(NULL, js);
    ASSERT_GT(discord_modify_guild_sticker_from_json(js, len, &params), 0);
    params.reason = "audit log reason";

    ASSERT_EQ(CCORD_OK,
              discord_modify_guild_sticker_to_json(&out_buf, &out_len,
                                                   &params));
    ASSERT_EQ(0, test_json_load(&out, out_buf, out_len));
    ASSERT_JSON_PATH_STR(&out, "name", "fake_sticker");
    ASSERT_JSON_PATH_STR(&out, "description",
                         "A sticker used by the codec regression suite");
    ASSERT_JSON_PATH_STR(&out, "tags", "wave");
    ASSERT_JSON_ABSENT(&out, "reason");

    test_json_unload(&out);
    params.reason = NULL; /* not owned; _cleanup must not free it */
    discord_modify_guild_sticker_cleanup(&params);
    free(out_buf);
    free(js);
    PASS();
}

SUITE(regression_modify_guild_sticker)
{
    RUN_TEST(modify_guild_sticker_reason_not_encoded);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(params_encode);
    RUN_SUITE(roundtrip);
    RUN_SUITE(regression_modify_guild_sticker);
    GREATEST_MAIN_END();
}
