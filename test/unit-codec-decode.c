#include "test-utils.h"
#include "codec-harness.h"

/* Field-by-field decode checks for the reflect-c data codecs, driven by
 * the fixtures under test/fixtures/.  Every test pairs the decode with
 * discord_data_cleanup() so the suite stays clean under leak checking. */

static struct discord *g_client;

/* ── user ─────────────────────────────────────────────────────────── */

TEST user_basic(void)
{
    size_t len;
    char *js = test_load_json_fixture("user-basic.json", &len);
    struct discord_user u = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_user, g_client, js, len, &u));
    ASSERT_EQ(1000000000000000001ULL, u.id);
    ASSERT_STR_EQ("wumpus", u.username);
    ASSERT_STR_EQ("0001", u.discriminator);
    ASSERT_STR_EQ("33ecab261d4681afa4d85a04691c4a01", u.avatar);
    ASSERT_EQ(false, u.bot);
    /* JSON key "system"; renamed in the struct ("system" is reserved) */
    ASSERT_EQ(false, u.System);
    ASSERT_EQ(true, u.mfa_enabled);
    ASSERT_STR_EQ("06c16474723fe537c283b8efa61a30c8", u.banner);
    ASSERT_EQ(16711680, u.accent_color);
    ASSERT_STR_EQ("en-US", u.locale);
    ASSERT_EQ(true, u.verified);
    ASSERT_STR_EQ("wumpus@example.com", u.email);
    ASSERT_EQ(64ULL, u.flags);
    ASSERT_EQ(1, u.premium_type);
    ASSERT_EQ(64ULL, u.public_flags);

    discord_data_cleanup(g_client, &u);
    free(js);
    PASS();
}

TEST user_bot(void)
{
    size_t len;
    char *js = test_load_json_fixture("user-bot.json", &len);
    struct discord_user u = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_user, g_client, js, len, &u));
    ASSERT_EQ(true, u.bot);
    ASSERT_STR_EQ("helperbot", u.username);
    ASSERT_EQ(NULL, u.avatar);
    ASSERT_EQ(65536ULL, u.public_flags);

    discord_data_cleanup(g_client, &u);
    free(js);
    PASS();
}

TEST user_missing_optionals_default(void)
{
    size_t len;
    char *js = test_load_json_fixture("user-missing-optionals.json", &len);
    struct discord_user u = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_user, g_client, js, len, &u));
    ASSERT_EQ(1000000000000000001ULL, u.id);
    ASSERT_EQ(NULL, u.avatar);
    ASSERT_EQ(NULL, u.banner);
    ASSERT_EQ(NULL, u.locale);
    ASSERT_EQ(NULL, u.email);
    ASSERT_EQ(false, u.bot);
    ASSERT_EQ(false, u.verified);
    ASSERT_EQ(0, u.accent_color);
    ASSERT_EQ(0ULL, u.flags);
    ASSERT_EQ(0, u.premium_type);

    discord_data_cleanup(g_client, &u);
    free(js);
    PASS();
}

TEST user_explicit_nulls(void)
{
    size_t len;
    char *js = test_load_json_fixture("user-nulls.json", &len);
    struct discord_user u = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_user, g_client, js, len, &u));
    ASSERT_STR_EQ("wumpus", u.username);
    ASSERT_EQ(NULL, u.avatar);
    ASSERT_EQ(NULL, u.banner);
    ASSERT_EQ(NULL, u.locale);
    ASSERT_EQ(NULL, u.email);
    ASSERT_EQ(0, u.accent_color);

    discord_data_cleanup(g_client, &u);
    free(js);
    PASS();
}

TEST user_unknown_keys_ignored(void)
{
    size_t len;
    char *js = test_load_json_fixture("user-extra-keys.json", &len);
    struct discord_user u = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_user, g_client, js, len, &u));
    ASSERT_EQ(1000000000000000001ULL, u.id);
    ASSERT_STR_EQ("wumpus", u.username);
    ASSERT_STR_EQ("33ecab261d4681afa4d85a04691c4a01", u.avatar);

    discord_data_cleanup(g_client, &u);
    free(js);
    PASS();
}

SUITE(user_decode)
{
    RUN_TEST(user_basic);
    RUN_TEST(user_bot);
    RUN_TEST(user_missing_optionals_default);
    RUN_TEST(user_explicit_nulls);
    RUN_TEST(user_unknown_keys_ignored);
}

/* ── guild ────────────────────────────────────────────────────────── */

TEST guild_basic(void)
{
    size_t len;
    char *js = test_load_json_fixture("guild-basic.json", &len);
    struct discord_guild g = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_guild, g_client, js, len, &g));
    ASSERT_EQ(1000000000000000010ULL, g.id);
    ASSERT_STR_EQ("Concord Test Guild", g.name);
    ASSERT_STR_EQ("8342729096ea3675442027381ff50dfe", g.icon);
    ASSERT_EQ(NULL, g.discovery_splash);
    ASSERT_EQ(1000000000000000001ULL, g.owner_id);
    ASSERT_EQ(0ULL, g.afk_channel_id);
    ASSERT_EQ(300, g.afk_timeout);
    ASSERT_EQ(true, g.widget_enabled);
    ASSERT_EQ(2, g.verification_level);
    ASSERT_EQ(1, g.default_message_notifications);
    ASSERT_EQ(2, g.explicit_content_filter);
    ASSERT_NEQ(NULL, g.roles);
    ASSERT_EQ(2, g.roles->size);
    ASSERT_STR_EQ("@everyone", g.roles->array[0].name);
    ASSERT_STR_EQ("moderator", g.roles->array[1].name);
    ASSERT_EQ(66321471ULL, g.roles->array[1].permissions);
    ASSERT_NEQ(NULL, g.emojis);
    ASSERT_EQ(1, g.emojis->size);
    ASSERT_STR_EQ("concord", g.emojis->array[0].name);
    ASSERT_NEQ(NULL, g.features);
    ASSERT_EQ(2, g.features->size);
    ASSERT_STR_EQ("COMMUNITY", g.features->array[0]);
    ASSERT_EQ(1, g.mfa_level);
    ASSERT_STR_EQ("concord", g.vanity_url_code);
    ASSERT_EQ(2, g.premium_tier);
    ASSERT_EQ(14, g.premium_subscription_count);
    ASSERT_STR_EQ("en-US", g.preferred_locale);
    ASSERT_EQ(425, g.approximate_member_count);
    ASSERT_EQ(true, g.premium_progress_bar_enabled);

    discord_data_cleanup(g_client, &g);
    free(js);
    PASS();
}

TEST guild_unavailable_stub(void)
{
    size_t len;
    char *js = test_load_json_fixture("guild-unavailable.json", &len);
    struct discord_guild g = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_guild, g_client, js, len, &g));
    ASSERT_EQ(1000000000000000011ULL, g.id);
    ASSERT_EQ(true, g.unavailable);
    ASSERT_EQ(NULL, g.name);
    ASSERT_EQ(NULL, g.roles);

    discord_data_cleanup(g_client, &g);
    free(js);
    PASS();
}

TEST guild_hazards(void)
{
    size_t len;
    char *js = test_load_json_fixture("guild-hazards.json", &len);
    struct discord_guild g = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_guild, g_client, js, len, &g));
    ASSERT_STR_EQ("Concord Test Guild", g.name);
    ASSERT_EQ(NULL, g.icon);
    ASSERT_EQ(0ULL, g.afk_channel_id);
    ASSERT_EQ(NULL, g.vanity_url_code);
    ASSERT_EQ(NULL, g.description);
    ASSERT_NEQ(NULL, g.roles);
    ASSERT_EQ(0, g.roles->size);
    ASSERT_NEQ(NULL, g.emojis);
    ASSERT_EQ(0, g.emojis->size);
    ASSERT_NEQ(NULL, g.features);
    ASSERT_EQ(0, g.features->size);

    discord_data_cleanup(g_client, &g);
    free(js);
    PASS();
}

SUITE(guild_decode)
{
    RUN_TEST(guild_basic);
    RUN_TEST(guild_unavailable_stub);
    RUN_TEST(guild_hazards);
}

/* ── guild member ─────────────────────────────────────────────────── */

TEST member_basic(void)
{
    size_t len;
    char *js = test_load_json_fixture("guild-member-basic.json", &len);
    struct discord_guild_member m = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_guild_member, g_client, js, len, &m));
    ASSERT_NEQ(NULL, m.user);
    ASSERT_EQ(1000000000000000003ULL, m.user->id);
    ASSERT_STR_EQ("memberperson", m.user->username);
    ASSERT_STR_EQ("NOT API SUPPORT", m.nick);
    ASSERT_NEQ(NULL, m.roles);
    ASSERT_EQ(2, m.roles->size);
    ASSERT_EQ(1000000000000000030ULL, m.roles->array[0]);
    ASSERT(m.joined_at != 0);
    ASSERT_EQ(0ULL, m.premium_since);
    ASSERT_EQ(false, m.deaf);
    /* wire key is "mute" (regression: spec used to read "muted") */
    ASSERT_EQ(true, m.muted);
    ASSERT_EQ(false, m.pending);

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

TEST member_without_user(void)
{
    size_t len;
    char *js = test_load_json_fixture("guild-member-hazards.json", &len);
    struct discord_guild_member m = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_guild_member, g_client, js, len, &m));
    ASSERT_EQ(NULL, m.user);
    ASSERT_EQ(NULL, m.nick);
    ASSERT(m.joined_at != 0);

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

TEST member_hazards(void)
{
    size_t len;
    char *js = test_load_json_fixture("guild-member-hazards.json", &len);
    struct discord_guild_member m = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_guild_member, g_client, js, len, &m));
    ASSERT_NEQ(NULL, m.roles);
    ASSERT_EQ(0, m.roles->size);
    ASSERT_EQ(0ULL, m.premium_since);
    ASSERT_EQ(false, m.muted);

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

SUITE(member_decode)
{
    RUN_TEST(member_basic);
    RUN_TEST(member_without_user);
    RUN_TEST(member_hazards);
}

/* ── channel ──────────────────────────────────────────────────────── */

TEST channel_text(void)
{
    size_t len;
    char *js = test_load_json_fixture("channel-text.json", &len);
    struct discord_channel c = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_channel, g_client, js, len, &c));
    ASSERT_EQ(1000000000000000020ULL, c.id);
    ASSERT_EQ(DISCORD_CHANNEL_GUILD_TEXT, c.type);
    ASSERT_EQ(1000000000000000010ULL, c.guild_id);
    ASSERT_EQ(6, c.position);
    ASSERT_STR_EQ("general", c.name);
    ASSERT_STR_EQ("Concord development chat", c.topic);
    ASSERT_EQ(false, c.nsfw);
    ASSERT_EQ(1000000000000000100ULL, c.last_message_id);
    ASSERT_EQ(2, c.rate_limit_per_user);
    ASSERT_EQ(1000000000000000024ULL, c.parent_id);
    ASSERT_NEQ(NULL, c.permission_overwrites);
    ASSERT_EQ(1, c.permission_overwrites->size);
    ASSERT_EQ(1000000000000000030ULL, c.permission_overwrites->array[0].id);
    ASSERT_EQ(2048ULL, c.permission_overwrites->array[0].allow);
    ASSERT_EQ(8192ULL, c.permission_overwrites->array[0].deny);

    discord_data_cleanup(g_client, &c);
    free(js);
    PASS();
}

TEST channel_hazards(void)
{
    size_t len;
    char *js = test_load_json_fixture("channel-hazards.json", &len);
    struct discord_channel c = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_channel, g_client, js, len, &c));
    ASSERT_STR_EQ("empty-channel", c.name);
    ASSERT_EQ(NULL, c.topic);
    ASSERT_EQ(0ULL, c.last_message_id);
    ASSERT_EQ(0ULL, c.parent_id);
    ASSERT_NEQ(NULL, c.permission_overwrites);
    ASSERT_EQ(0, c.permission_overwrites->size);

    discord_data_cleanup(g_client, &c);
    free(js);
    PASS();
}

SUITE(channel_decode)
{
    RUN_TEST(channel_text);
    RUN_TEST(channel_hazards);
}

/* ── message ──────────────────────────────────────────────────────── */

TEST message_plain(void)
{
    size_t len;
    char *js = test_load_json_fixture("message-plain.json", &len);
    struct discord_message m = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_message, g_client, js, len, &m));
    ASSERT_EQ(1000000000000000100ULL, m.id);
    ASSERT_EQ(1000000000000000020ULL, m.channel_id);
    ASSERT_NEQ(NULL, m.author);
    ASSERT_EQ(1000000000000000001ULL, m.author->id);
    ASSERT_STR_EQ("wumpus", m.author->username);
    ASSERT_STR_EQ("Hello, concord!", m.content);
    ASSERT(m.timestamp != 0);
    ASSERT_EQ(0ULL, m.edited_timestamp);
    ASSERT_EQ(false, m.tts);
    ASSERT_EQ(false, m.mention_everyone);
    ASSERT_EQ(false, m.pinned);
    ASSERT_EQ(DISCORD_MESSAGE_DEFAULT, m.type);

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

TEST message_with_embeds(void)
{
    size_t len;
    char *js = test_load_json_fixture("message-with-embeds.json", &len);
    struct discord_message m = { 0 };
    struct discord_embed *e;

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_message, g_client, js, len, &m));
    ASSERT_NEQ(NULL, m.embeds);
    ASSERT_EQ(2, m.embeds->size);
    e = &m.embeds->array[0];
    ASSERT_STR_EQ("Concord", e->title);
    ASSERT_STR_EQ("rich", e->type);
    ASSERT_STR_EQ("Discord API library written in C", e->description);
    ASSERT_STR_EQ("https://github.com/Cogmasters/concord", e->url);
    ASSERT(e->timestamp != 0);
    ASSERT_EQ(3447003, e->color);
    ASSERT_NEQ(NULL, e->footer);
    ASSERT_STR_EQ("concord footer", e->footer->text);
    ASSERT_NEQ(NULL, e->image);
    ASSERT_EQ(640, e->image->width);
    ASSERT_NEQ(NULL, e->author);
    ASSERT_STR_EQ("Cogmasters", e->author->name);
    ASSERT_NEQ(NULL, e->fields);
    ASSERT_EQ(2, e->fields->size);
    ASSERT_STR_EQ("Language", e->fields->array[0].name);
    ASSERT_STR_EQ("C", e->fields->array[0].value);
    /* JSON key "inline"; renamed in the struct (C99 keyword clash) */
    ASSERT_EQ(true, e->fields->array[0].Inline);
    ASSERT_EQ(false, e->fields->array[1].Inline);
    ASSERT_STR_EQ("Second embed", m.embeds->array[1].title);

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

TEST message_with_attachments(void)
{
    size_t len;
    char *js = test_load_json_fixture("message-with-attachments.json", &len);
    struct discord_message m = { 0 };
    struct discord_attachment *a;

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_message, g_client, js, len, &m));
    ASSERT_NEQ(NULL, m.attachments);
    ASSERT_EQ(2, m.attachments->size);
    a = &m.attachments->array[0];
    ASSERT_EQ(1000000000000000110ULL, a->id);
    ASSERT_STR_EQ("screenshot.png", a->filename);
    ASSERT_STR_EQ("image/png", a->content_type);
    ASSERT_EQ(102400, (int)a->size);
    ASSERT_EQ(480, a->height);
    ASSERT_EQ(640, a->width);
    a = &m.attachments->array[1];
    ASSERT_STR_EQ("notes.txt", a->filename);
    ASSERT_EQ(0, a->height);

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

TEST message_with_components(void)
{
    size_t len;
    char *js = test_load_json_fixture("message-with-components.json", &len);
    struct discord_message m = { 0 };
    struct discord_component *row, *btn;

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_message, g_client, js, len, &m));
    ASSERT_NEQ(NULL, m.components);
    ASSERT_EQ(1, m.components->size);
    row = &m.components->array[0];
    ASSERT_EQ(DISCORD_COMPONENT_ACTION_ROW, row->type);
    ASSERT_NEQ(NULL, row->components);
    ASSERT_EQ(2, row->components->size);
    btn = &row->components->array[0];
    ASSERT_EQ(DISCORD_COMPONENT_BUTTON, btn->type);
    ASSERT_EQ(DISCORD_BUTTON_PRIMARY, btn->style);
    ASSERT_STR_EQ("Click me", btn->label);
    ASSERT_STR_EQ("btn_click", btn->custom_id);
    btn = &row->components->array[1];
    ASSERT_EQ(DISCORD_BUTTON_LINK, btn->style);
    ASSERT_STR_EQ("https://example.invalid/docs", btn->url);
    ASSERT_EQ(NULL, btn->custom_id);

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

TEST message_hazards(void)
{
    size_t len;
    char *js = test_load_json_fixture("message-hazards.json", &len);
    struct discord_message m = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_message, g_client, js, len, &m));
    ASSERT_EQ(0ULL, m.edited_timestamp);
    ASSERT_NEQ(NULL, m.mentions);
    ASSERT_EQ(0, m.mentions->size);
    ASSERT_STR_EQ("abc123nonce", m.nonce);

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

TEST message_long_content(void)
{
    size_t len;
    char *js = test_load_json_fixture("message-long-content.json", &len);
    struct discord_message m = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_message, g_client, js, len, &m));
    ASSERT_NEQ(NULL, m.content);
    ASSERT_EQ(2000, (int)strlen(m.content));
    ASSERT_NEQ(NULL, m.embeds);
    ASSERT_EQ(1, m.embeds->size);
    ASSERT_NEQ(NULL, m.embeds->array[0].description);
    ASSERT_EQ(4096, (int)strlen(m.embeds->array[0].description));

    discord_data_cleanup(g_client, &m);
    free(js);
    PASS();
}

SUITE(message_decode)
{
    RUN_TEST(message_plain);
    RUN_TEST(message_with_embeds);
    RUN_TEST(message_with_attachments);
    RUN_TEST(message_with_components);
    RUN_TEST(message_hazards);
    RUN_TEST(message_long_content);
}

/* ── role ─────────────────────────────────────────────────────────── */

TEST role_basic(void)
{
    size_t len;
    char *js = test_load_json_fixture("role-basic.json", &len);
    struct discord_role r = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_role, g_client, js, len, &r));
    ASSERT_EQ(1000000000000000030ULL, r.id);
    ASSERT_STR_EQ("moderator", r.name);
    ASSERT_EQ(3447003, r.color);
    ASSERT_EQ(true, r.hoist);
    ASSERT_EQ(NULL, r.icon);
    ASSERT_EQ(NULL, r.unicode_emoji);
    ASSERT_EQ(1, r.position);
    ASSERT_EQ(66321471ULL, r.permissions);
    ASSERT_EQ(false, r.managed);
    ASSERT_EQ(true, r.mentionable);

    discord_data_cleanup(g_client, &r);
    free(js);
    PASS();
}

TEST role_hazards(void)
{
    size_t len;
    char *js = test_load_json_fixture("role-hazards.json", &len);
    struct discord_role r = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_role, g_client, js, len, &r));
    ASSERT_STR_EQ("minimal-role", r.name);
    ASSERT_EQ(0ULL, r.permissions);
    ASSERT_EQ(NULL, r.unicode_emoji);
    ASSERT_EQ(NULL, r.tags);

    discord_data_cleanup(g_client, &r);
    free(js);
    PASS();
}

SUITE(role_decode)
{
    RUN_TEST(role_basic);
    RUN_TEST(role_hazards);
}

/* ── emoji ────────────────────────────────────────────────────────── */

TEST emoji_custom(void)
{
    size_t len;
    char *js = test_load_json_fixture("emoji-custom.json", &len);
    struct discord_emoji e = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_emoji, g_client, js, len, &e));
    ASSERT_EQ(1000000000000000040ULL, e.id);
    ASSERT_STR_EQ("concord", e.name);
    ASSERT_NEQ(NULL, e.roles);
    ASSERT_EQ(1, e.roles->size);
    ASSERT_NEQ(NULL, e.user);
    ASSERT_STR_EQ("wumpus", e.user->username);
    ASSERT_EQ(true, e.require_colons);
    ASSERT_EQ(false, e.animated);
    ASSERT_EQ(true, e.available);

    discord_data_cleanup(g_client, &e);
    free(js);
    PASS();
}

TEST emoji_standard(void)
{
    size_t len;
    char *js = test_load_json_fixture("emoji-standard.json", &len);
    struct discord_emoji e = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_emoji, g_client, js, len, &e));
    ASSERT_EQ(0ULL, e.id); /* "id": null */
    ASSERT_STR_EQ("\xF0\x9F\x94\xA5", e.name);
    ASSERT_EQ(NULL, e.user);

    discord_data_cleanup(g_client, &e);
    free(js);
    PASS();
}

TEST emoji_hazards(void)
{
    size_t len;
    char *js = test_load_json_fixture("emoji-hazards.json", &len);
    struct discord_emoji e = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_emoji, g_client, js, len, &e));
    ASSERT_STR_EQ("minimal", e.name);
    ASSERT_EQ(true, e.animated);
    ASSERT_EQ(NULL, e.roles);
    ASSERT_EQ(false, e.require_colons);

    discord_data_cleanup(g_client, &e);
    free(js);
    PASS();
}

SUITE(emoji_decode)
{
    RUN_TEST(emoji_custom);
    RUN_TEST(emoji_standard);
    RUN_TEST(emoji_hazards);
}

/* ── interaction ──────────────────────────────────────────────────── */

TEST interaction_slash_command(void)
{
    size_t len;
    char *js = test_load_json_fixture("interaction-slash-command.json", &len);
    struct discord_interaction i = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_interaction, g_client, js, len, &i));
    ASSERT_EQ(1000000000000000200ULL, i.id);
    ASSERT_EQ(1000000000000000201ULL, i.application_id);
    ASSERT_EQ(DISCORD_INTERACTION_APPLICATION_COMMAND, i.type);
    ASSERT_NEQ(NULL, i.data);
    ASSERT_STR_EQ("ping", i.data->name);
    ASSERT_NEQ(NULL, i.data->options);
    ASSERT_EQ(1, i.data->options->size);
    ASSERT_STR_EQ("target", i.data->options->array[0].name);
    ASSERT_STR_EQ("wumpus", i.data->options->array[0].value);
    ASSERT_EQ(1000000000000000010ULL, i.guild_id);
    ASSERT_NEQ(NULL, i.member);
    ASSERT_NEQ(NULL, i.member->user);
    ASSERT_EQ(1000000000000000003ULL, i.member->user->id);
    ASSERT_EQ(NULL, i.user);
    ASSERT_STR_EQ("faketoken_aW50ZXJhY3Rpb24", i.token);
    ASSERT_EQ(1, i.version);
    ASSERT_STR_EQ("en-US", i.locale);

    discord_data_cleanup(g_client, &i);
    free(js);
    PASS();
}

TEST interaction_message_component(void)
{
    size_t len;
    char *js = test_load_json_fixture("interaction-message-component.json", &len);
    struct discord_interaction i = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_interaction, g_client, js, len, &i));
    ASSERT_EQ(DISCORD_INTERACTION_MESSAGE_COMPONENT, i.type);
    ASSERT_NEQ(NULL, i.data);
    ASSERT_STR_EQ("btn_click", i.data->custom_id);
    ASSERT_EQ(DISCORD_COMPONENT_BUTTON, i.data->component_type);
    ASSERT_NEQ(NULL, i.message);
    ASSERT_EQ(1000000000000000103ULL, i.message->id);
    ASSERT_STR_EQ("pick an action", i.message->content);

    discord_data_cleanup(g_client, &i);
    free(js);
    PASS();
}

TEST interaction_dm_shaped(void)
{
    size_t len;
    char *js = test_load_json_fixture("interaction-hazards.json", &len);
    struct discord_interaction i = { 0 };

    ASSERT_NEQ(NULL, js);
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_interaction, g_client, js, len, &i));
    ASSERT_EQ(NULL, i.member);
    ASSERT_NEQ(NULL, i.user);
    ASSERT_STR_EQ("dmuser", i.user->username);
    ASSERT_EQ(0ULL, i.guild_id);
    ASSERT_EQ(NULL, i.guild_locale);

    discord_data_cleanup(g_client, &i);
    free(js);
    PASS();
}

SUITE(interaction_decode)
{
    RUN_TEST(interaction_slash_command);
    RUN_TEST(interaction_message_component);
    RUN_TEST(interaction_dm_shaped);
}

/* ── gateway envelope payloads ────────────────────────────────────── */

/* Decode the "d" payload of a gateway envelope fixture the way the
 * dispatcher would: locate "d" with jsmn-find, then run the generated
 * decoder over that slice. */
static int
envelope_payload(const char *fixture, char **p_js, size_t *p_len,
                 const char **p_d, size_t *p_d_len, jsmnf_table **p_table)
{
    jsmnf_loader loader;
    size_t table_len = 0;
    const jsmnf_pair *d;

    *p_table = NULL;
    if (!(*p_js = test_load_json_fixture(fixture, p_len))) return -1;
    jsmnf_init(&loader);
    if (jsmnf_load_auto(&loader, *p_js, *p_len, p_table, &table_len) < 1)
        return -1;
    if (!(d = jsmnf_find(loader.root, "d", 1))) return -1;
    *p_d = *p_js + d->v->start;
    *p_d_len = (size_t)(d->v->end - d->v->start);
    return 0;
}

TEST gateway_ready_payload(void)
{
    char *js;
    const char *d;
    size_t len, d_len;
    jsmnf_table *table;
    struct discord_ready r = { 0 };

    ASSERT_EQ(0, envelope_payload("gateway-ready.json", &js, &len,
                                  &d, &d_len, &table));
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_ready, g_client, d, d_len, &r));
    ASSERT_EQ(10, r.v);
    ASSERT_NEQ(NULL, r.user);
    ASSERT_STR_EQ("helperbot", r.user->username);
    ASSERT_NEQ(NULL, r.guilds);
    ASSERT_EQ(2, r.guilds->size);
    ASSERT_EQ(true, r.guilds->array[0].unavailable);
    ASSERT_STR_EQ("fake_session_33ecab261d4681af", r.session_id);
    ASSERT_NEQ(NULL, r.shard);
    ASSERT_EQ(2, r.shard->size);
    ASSERT_EQ(0, r.shard->array[0]);
    ASSERT_EQ(1, r.shard->array[1]);

    discord_data_cleanup(g_client, &r);
    free(table);
    free(js);
    PASS();
}

TEST gateway_message_create_payload(void)
{
    char *js;
    const char *d;
    size_t len, d_len;
    jsmnf_table *table;
    struct discord_message m = { 0 };

    ASSERT_EQ(0, envelope_payload("gateway-message-create.json", &js, &len,
                                  &d, &d_len, &table));
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_message, g_client, d, d_len, &m));
    ASSERT_EQ(1000000000000000105ULL, m.id);
    ASSERT_EQ(1000000000000000010ULL, m.guild_id);
    ASSERT_STR_EQ("gateway event message", m.content);
    ASSERT_NEQ(NULL, m.member);
    ASSERT_STR_EQ("NOT API SUPPORT", m.member->nick);
    ASSERT_EQ(NULL, m.member->user); /* MESSAGE_CREATE member omits user */

    discord_data_cleanup(g_client, &m);
    free(table);
    free(js);
    PASS();
}

TEST gateway_guild_create_payload(void)
{
    char *js;
    const char *d;
    size_t len, d_len;
    jsmnf_table *table;
    struct discord_guild g = { 0 };

    ASSERT_EQ(0, envelope_payload("gateway-guild-create.json", &js, &len,
                                  &d, &d_len, &table));
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_guild, g_client, d, d_len, &g));
    ASSERT_EQ(1000000000000000010ULL, g.id);
    ASSERT(g.joined_at != 0);
    ASSERT_EQ(2, g.member_count);
    ASSERT_NEQ(NULL, g.members);
    ASSERT_EQ(2, g.members->size);
    ASSERT_NEQ(NULL, g.members->array[1].user);
    ASSERT_EQ(true, g.members->array[1].user->bot);
    ASSERT_NEQ(NULL, g.channels);
    ASSERT_EQ(1, g.channels->size);
    ASSERT_STR_EQ("general", g.channels->array[0].name);

    discord_data_cleanup(g_client, &g);
    free(table);
    free(js);
    PASS();
}

SUITE(gateway_payload_decode)
{
    RUN_TEST(gateway_ready_payload);
    RUN_TEST(gateway_message_create_payload);
    RUN_TEST(gateway_guild_create_payload);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    if (!(g_client = codec_harness_init())) {
        fprintf(stderr, "codec harness init failed\n");
        return EXIT_FAILURE;
    }
    RUN_SUITE(user_decode);
    RUN_SUITE(guild_decode);
    RUN_SUITE(member_decode);
    RUN_SUITE(channel_decode);
    RUN_SUITE(message_decode);
    RUN_SUITE(role_decode);
    RUN_SUITE(emoji_decode);
    RUN_SUITE(interaction_decode);
    RUN_SUITE(gateway_payload_decode);
    codec_harness_cleanup();
    GREATEST_MAIN_END();
}
