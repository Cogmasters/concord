#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

#include "fixture-server.h"
#include "test-client.h" /* TEST_DUMMY_TOKEN; boot is done by hand here */
#include "test-utils.h"

/* Hermetic test for the discord_config.base_url override: a client built
 * with discord_from_config() must resolve REST requests against the
 * configured loopback URL instead of DISCORD_API_BASE_URL.
 *
 * Booting with a token implies a synchronous GET /users/@me during
 * _discord_init(), so the fixture server must be running and scripted
 * before the client is constructed — which doubles as the end-to-end
 * proof that the override is honored. This suite deliberately does not
 * use test_client_boot(): it asserts the boot mechanics themselves. */

TEST
base_url_override(void)
{
    struct fixture_server *fs = fixture_server_start();
    struct discord *client;
    const struct fs_request *req;
    const char *auth;
    size_t auth_len;
    char url[64], expect_auth[128];

    ASSERT_NEQ(NULL, fs);
    fixture_server_script(
        fs, &(struct fs_script){
                .method = "GET",
                .path = "/users/@me",
                .status = 200,
                .body_fixture = "user-basic.json",
                .headers =
                    (const struct fs_header[]){
                        { "Content-Type", "application/json" },
                    },
                .n_headers = 1,
            });
    snprintf(url, sizeof url, "http://127.0.0.1:%hu",
             fixture_server_port(fs));

    client = discord_from_config(&(struct discord_config){
        /* discord_from_config() copies the struct by value and
         * discord_cleanup() frees config.token, so it must be heap'd;
         * base_url is borrowed and copied by ua_set_url() */
        .token = strdup(TEST_DUMMY_TOKEN),
        .base_url = url,
        .log = { .quiet = true },
    });

    /* boot succeeded: the sync self-fetch resolved against loopback */
    ASSERT_NEQ(NULL, client);
    ASSERT_STR_EQ(url, ua_get_url(client->rest.requestor.ua));
    /* the client's user was decoded from the fixture body */
    ASSERT_EQ(1000000000000000001ULL, client->self.id);
    ASSERT_STR_EQ("wumpus", client->self.username);

    /* the request carried the expected route and credentials */
    ASSERT_EQ((size_t)1, fixture_server_request_count(fs));
    req = fixture_server_request(fs, 0);
    ASSERT_STR_EQ("GET", req->method);
    ASSERT_STR_EQ("/users/@me", req->path);
    auth = fs_request_header(req, "Authorization", &auth_len);
    ASSERT_NEQ(NULL, auth);
    snprintf(expect_auth, sizeof expect_auth, "Bot %s", TEST_DUMMY_TOKEN);
    ASSERT_EQ(strlen(expect_auth), auth_len);
    ASSERT_EQ(0, strncmp(expect_auth, auth, auth_len));

    discord_cleanup(client);
    fixture_server_stop(fs);
    PASS();
}

SUITE(base_url)
{
    RUN_TEST(base_url_override);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(base_url);
    GREATEST_MAIN_END();
}
