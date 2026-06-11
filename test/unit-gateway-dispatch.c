/* Event dispatch routing: delivering a gateway dispatch envelope fires
 * exactly the registered user callback with a correctly decoded
 * struct.  Closes the loop between Track B (codecs in isolation) and
 * the gateway (codecs invoked in context) — field checks here are spot
 * checks proving wiring, not codec correctness (B02 owns that).
 *
 * Callbacks must be registered before tg_connect(): the setters add
 * gateway intents, which is refused while connected. */

#include "gateway-harness.h"
#include "discord-cache.h"

static struct {
    int ready, messages, guilds, interactions;
    int member_adds, member_updates, member_removes, reactions;
    int commands;
    char ready_session[64];
    u64snowflake message_id;
    char message_content[128];
    u64snowflake guild_id;
    int guild_member_count;
    u64snowflake interaction_id;
    char interaction_data_name[64];
    u64snowflake member_user_id;
    char member_nick[64];
    u64snowflake reaction_message_id;
    char reaction_emoji[32];
    char command_args[128];
} rec;

static void
on_ready(struct discord *client, const struct discord_ready *event)
{
    (void)client;
    ++rec.ready;
    snprintf(rec.ready_session, sizeof(rec.ready_session), "%s",
             event->session_id ? event->session_id : "");
}

static void
on_message(struct discord *client, const struct discord_message *event)
{
    (void)client;
    ++rec.messages;
    rec.message_id = event->id;
    snprintf(rec.message_content, sizeof(rec.message_content), "%s",
             event->content ? event->content : "");
}

static void
on_guild_create(struct discord *client, const struct discord_guild *event)
{
    (void)client;
    ++rec.guilds;
    rec.guild_id = event->id;
    rec.guild_member_count = event->member_count;
}

static void
on_interaction(struct discord *client, const struct discord_interaction *event)
{
    (void)client;
    ++rec.interactions;
    rec.interaction_id = event->id;
    snprintf(rec.interaction_data_name, sizeof(rec.interaction_data_name),
             "%s",
             (event->data && event->data->name) ? event->data->name : "");
}

static void
on_member_add(struct discord *client, const struct discord_guild_member *event)
{
    (void)client;
    ++rec.member_adds;
    rec.guild_id = event->guild_id;
    if (event->user) rec.member_user_id = event->user->id;
}

static void
on_member_update(struct discord *client,
                 const struct discord_guild_member_update *event)
{
    (void)client;
    ++rec.member_updates;
    snprintf(rec.member_nick, sizeof(rec.member_nick), "%s",
             event->nick ? event->nick : "");
}

static void
on_member_remove(struct discord *client,
                 const struct discord_guild_member_remove *event)
{
    (void)client;
    ++rec.member_removes;
    if (event->user) rec.member_user_id = event->user->id;
}

static void
on_reaction_add(struct discord *client,
                const struct discord_message_reaction_add *event)
{
    (void)client;
    ++rec.reactions;
    rec.reaction_message_id = event->message_id;
    snprintf(rec.reaction_emoji, sizeof(rec.reaction_emoji), "%s",
             (event->emoji && event->emoji->name) ? event->emoji->name : "");
}

static void
on_command(struct discord *client, const struct discord_message *event)
{
    (void)client;
    ++rec.commands;
    snprintf(rec.command_args, sizeof(rec.command_args), "%s",
             event->content ? event->content : "");
}

static int
boot_reset(struct test_gateway *tg)
{
    memset(&rec, 0, sizeof(rec));
    return tg_boot(tg);
}

TEST
ready_callback_fires(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_set_on_ready(tg.client, on_ready);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));
    ASSERT_EQ(1, rec.ready);
    ASSERT_STR_EQ("fake_session_33ecab261d4681af", rec.ready_session);

    tg_cleanup(&tg);
    PASS();
}

TEST
message_create_routes_exactly_once(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_set_on_message_create(tg.client, on_message);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    ASSERT_EQ(
        0, tg_deliver_event(&tg, "MESSAGE_CREATE", 2, "message-plain.json"));
    ASSERT_EQ(1, rec.messages);
    ASSERT_EQ(1000000000000000100ULL, rec.message_id);
    ASSERT_STR_EQ("Hello, concord!", rec.message_content);

    /* an event with no registered callback is dropped silently and
     * doesn't disturb other counters */
    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-guild-create.json"));
    ASSERT_EQ(1, rec.messages);
    ASSERT_EQ(0, rec.guilds);

    tg_cleanup(&tg);
    PASS();
}

TEST
guild_create_routes(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_set_on_guild_create(tg.client, on_guild_create);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-guild-create.json"));
    ASSERT_EQ(1, rec.guilds);
    ASSERT_EQ(1000000000000000010ULL, rec.guild_id);
    ASSERT_EQ(2, rec.guild_member_count);

    tg_cleanup(&tg);
    PASS();
}

TEST
interaction_create_routes(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_set_on_interaction_create(tg.client, on_interaction);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    ASSERT_EQ(0, tg_deliver_event(&tg, "INTERACTION_CREATE", 2,
                                  "interaction-slash-command.json"));
    ASSERT_EQ(1, rec.interactions);
    ASSERT_EQ(1000000000000000200ULL, rec.interaction_id);
    ASSERT_STR_EQ("ping", rec.interaction_data_name);

    tg_cleanup(&tg);
    PASS();
}

TEST
guild_member_events_route(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_set_on_guild_member_add(tg.client, on_member_add);
    discord_set_on_guild_member_update(tg.client, on_member_update);
    discord_set_on_guild_member_remove(tg.client, on_member_remove);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    ASSERT_EQ(0, tg_deliver_event(&tg, "GUILD_MEMBER_ADD", 2,
                                  "guild-member-add.json"));
    ASSERT_EQ(1, rec.member_adds);
    ASSERT_EQ(1000000000000000010ULL, rec.guild_id);
    ASSERT_EQ(1000000000000000005ULL, rec.member_user_id);

    ASSERT_EQ(0, tg_deliver_event(&tg, "GUILD_MEMBER_UPDATE", 3,
                                  "guild-member-update.json"));
    ASSERT_EQ(1, rec.member_updates);
    ASSERT_STR_EQ("promoted-nick", rec.member_nick);

    rec.member_user_id = 0;
    ASSERT_EQ(0, tg_deliver_event(&tg, "GUILD_MEMBER_REMOVE", 4,
                                  "guild-member-remove.json"));
    ASSERT_EQ(1, rec.member_removes);
    ASSERT_EQ(1000000000000000005ULL, rec.member_user_id);

    /* exactly-once: no cross-firing between the three */
    ASSERT_EQ(1, rec.member_adds);
    ASSERT_EQ(1, rec.member_updates);

    tg_cleanup(&tg);
    PASS();
}

TEST
message_reaction_add_routes(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_set_on_message_reaction_add(tg.client, on_reaction_add);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    ASSERT_EQ(0, tg_deliver_event(&tg, "MESSAGE_REACTION_ADD", 2,
                                  "message-reaction-add.json"));
    ASSERT_EQ(1, rec.reactions);
    ASSERT_EQ(1000000000000000100ULL, rec.reaction_message_id);
    ASSERT_STR_EQ("\xF0\x9F\x94\xA5", rec.reaction_emoji);

    tg_cleanup(&tg);
    PASS();
}

TEST
unknown_event_name_is_harmless(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_set_on_message_create(tg.client, on_message);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    tg_deliver(&tg, "{\"t\":\"FUTURE_EVENT\",\"s\":9,\"op\":0,\"d\":{}}");
    ASSERT_EQ(0, rec.messages);

    /* dispatch still works afterwards */
    ASSERT_EQ(
        0, tg_deliver_event(&tg, "MESSAGE_CREATE", 10, "message-plain.json"));
    ASSERT_EQ(1, rec.messages);

    tg_cleanup(&tg);
    PASS();
}

#define COMMAND_MESSAGE(content)                                              \
    "{\"t\":\"MESSAGE_CREATE\",\"s\":2,\"op\":0,\"d\":{"                      \
    "\"id\":\"1000000000000000150\","                                         \
    "\"channel_id\":\"1000000000000000020\","                                 \
    "\"author\":{\"id\":\"1000000000000000003\","                             \
    "\"username\":\"memberperson\",\"discriminator\":\"0420\","               \
    "\"avatar\":null},"                                                       \
    "\"content\":\"" content "\","                                            \
    "\"timestamp\":\"2021-05-31T19:25:24.166000+00:00\","                     \
    "\"type\":0}}"

TEST
command_prefix_routing(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_set_prefix(tg.client, "!");
    discord_set_on_command(tg.client, "ping", on_command);
    discord_set_on_message_create(tg.client, on_message);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    /* a matched command swallows the event: command callback fires with
     * the arguments, the plain MESSAGE_CREATE callback does not */
    tg_deliver(&tg, COMMAND_MESSAGE("!ping hello"));
    ASSERT_EQ(1, rec.commands);
    ASSERT_STR_EQ("hello", rec.command_args);
    ASSERT_EQ(0, rec.messages);

    /* prefixed but unknown, with no fallback registered: falls through
     * to the plain callback with the full content */
    tg_deliver(&tg, COMMAND_MESSAGE("!nope hello"));
    ASSERT_EQ(1, rec.commands);
    ASSERT_EQ(1, rec.messages);
    ASSERT_STR_EQ("!nope hello", rec.message_content);

    tg_cleanup(&tg);
    PASS();
}

TEST
guild_create_populates_cache(void)
{
    struct test_gateway tg;
    const struct discord_guild *guild;

    ASSERT_EQ(0, boot_reset(&tg));
    discord_cache_enable(tg.client, DISCORD_CACHE_GUILDS);
    ASSERT_EQ(0, tg_connect(&tg));
    /* the cache's READY handler marks it valid for this shard */
    ASSERT_EQ(0, tg_handshake(&tg));

    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-guild-create.json"));
    guild = discord_cache_get_guild(tg.client, 1000000000000000010ULL);
    ASSERT_NEQ(NULL, guild);
    ASSERT_STR_EQ("Concord Test Guild", guild->name);
    /* lookups claim the resource */
    discord_unclaim(tg.client, guild);

    tg_cleanup(&tg);
    PASS();
}

SUITE(gateway_dispatch)
{
    RUN_TEST(ready_callback_fires);
    RUN_TEST(message_create_routes_exactly_once);
    RUN_TEST(guild_create_routes);
    RUN_TEST(interaction_create_routes);
    RUN_TEST(guild_member_events_route);
    RUN_TEST(message_reaction_add_routes);
    RUN_TEST(unknown_event_name_is_harmless);
    RUN_TEST(command_prefix_routing);
    RUN_TEST(guild_create_populates_cache);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(gateway_dispatch);
    GREATEST_MAIN_END();
}
