#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "discord.h"
#include "discord-internal.h"

#include "fixture-server.h"
#include "test-client.h"
#include "test-utils.h"

/* Hermetic integration tests for the full REST stack — public API call
 * through threadpool, scheduler, curl multi, io_poller, codecs, and back
 * through user callbacks — against the loopback fixture server.
 *
 * Replaces what test/rest.c and test/timeout.c could only verify against
 * live Discord. Notes on intentional divergences from the scope doc:
 * - there is no client-side request timeout (no CURLOPT_TIMEOUT anywhere),
 *   so the "delay exceeds timeout" case became a bounded-delay success
 *   case plus a connection-drop failure case; main() arms alarm(60) so a
 *   regression that hangs the pipeline fails instead of wedging.
 * - responses here carry no X-RateLimit-* headers, keeping every route in
 *   the ratelimiter's 'miss' bucket; throttling behavior is C05 territory
 *   (ratelimit-integration). */

static struct fixture_server *FS;
static struct discord *CLIENT;

struct async_result {
    int done_count;
    int fail_count;
    int settled; /* raised by either callback; awaited by the test */
    CCORDcode code;
    u64snowflake obj_id;
    char json[1024];
    size_t json_len;
};

static void
on_fail(struct discord *client, struct discord_response *resp)
{
    struct async_result *res = resp->data;
    (void)client;

    res->fail_count++;
    res->settled = 1;
    res->code = resp->code;
    if (resp->json.size && resp->json.size < sizeof res->json) {
        memcpy(res->json, resp->json.start, resp->json.size);
        res->json[resp->json.size] = '\0';
    }
    res->json_len = resp->json.size;
}

static void
on_channel_done(struct discord *client,
                struct discord_response *resp,
                const struct discord_channel *channel)
{
    struct async_result *res = resp->data;
    (void)client;

    res->done_count++;
    res->settled = 1;
    res->code = resp->code;
    res->obj_id = channel->id;
}

TEST
boot_request_journaled(void)
{
    const struct fs_request *req = fixture_server_request(FS, 0);
    const char *auth;
    size_t auth_len;
    char expect_auth[128];

    /* _discord_init()'s sync self-fetch was the first request out */
    ASSERT_NEQ(NULL, req);
    ASSERT_STR_EQ("GET", req->method);
    ASSERT_STR_EQ("/users/@me", req->path);
    auth = fs_request_header(req, "Authorization", &auth_len);
    ASSERT_NEQ(NULL, auth);
    snprintf(expect_auth, sizeof expect_auth, "Bot %s", TEST_DUMMY_TOKEN);
    ASSERT_EQ(strlen(expect_auth), auth_len);
    ASSERT_EQ(0, strncmp(expect_auth, auth, auth_len));
    ASSERT_EQ(1000000000000000001ULL, CLIENT->self.id);
    PASS();
}

TEST
sync_fetch_object(void)
{
    struct discord_user user = { 0 };
    struct discord_ret_user ret = { .sync = &user };

    ASSERT_EQ(CCORD_OK, discord_get_current_user(CLIENT, &ret));
    ASSERT_EQ(1000000000000000001ULL, user.id);
    ASSERT_STR_EQ("wumpus", user.username);
    discord_data_cleanup(CLIENT, &user);
    PASS();
}

TEST
sync_fetch_discard(void)
{
    struct discord_ret_user ret = { .sync = DISCORD_SYNC_FLAG };

    ASSERT_EQ(CCORD_OK, discord_get_current_user(CLIENT, &ret));
    PASS();
}

TEST
sync_no_content(void)
{
    struct discord_ret ret = { .sync = true };

    fixture_server_script(FS, &(struct fs_script){
                                  .method = "POST",
                                  .path = "/channels/600/typing",
                                  .status = 204,
                              });

    ASSERT_EQ(CCORD_OK,
              discord_trigger_typing_indicator(CLIENT, 600ULL, &ret));
    ASSERT_EQ((size_t)1, fixture_server_count_path(FS, "/channels/600/typing"));
    PASS();
}

TEST
async_done_fires_once(void)
{
    struct async_result res = { 0 };
    struct discord_ret_channel ret = {
        .done = on_channel_done,
        .fail = on_fail,
        .data = &res,
    };

    fixture_server_script(FS, &(struct fs_script){
                                  .method = "GET",
                                  .path = "/channels/601",
                                  .status = 200,
                                  .body_fixture = "channel-text.json",
                              });

    ASSERT_EQ(CCORD_PENDING, discord_get_channel(CLIENT, 601ULL, &ret));
    ASSERT(test_client_await(CLIENT, &res.settled, 5000));
    ASSERT_EQ(1, res.done_count);
    ASSERT_EQ(0, res.fail_count);
    ASSERT_EQ(CCORD_OK, res.code);
    /* decoded from channel-text.json */
    ASSERT_EQ(1000000000000000020ULL, res.obj_id);
    PASS();
}

TEST
async_fail_fires_once(void)
{
    struct async_result res = { 0 };
    struct discord_ret_channel ret = {
        .done = on_channel_done,
        .fail = on_fail,
        .data = &res,
    };

    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/602",
                .status = 404,
                .body = "{\"message\": \"Unknown Channel\", \"code\": "
                        "10003}",
            });

    ASSERT_EQ(CCORD_PENDING, discord_get_channel(CLIENT, 602ULL, &ret));
    ASSERT(test_client_await(CLIENT, &res.settled, 5000));
    ASSERT_EQ(0, res.done_count);
    ASSERT_EQ(1, res.fail_count);
    ASSERT_EQ(CCORD_DISCORD_JSON_CODE, res.code);
    ASSERT_NEQ(NULL, strstr(res.json, "Unknown Channel"));
    PASS();
}

SUITE(dispatch)
{
    RUN_TEST(boot_request_journaled);
    RUN_TEST(sync_fetch_object);
    RUN_TEST(sync_fetch_discard);
    RUN_TEST(sync_no_content);
    RUN_TEST(async_done_fires_once);
    RUN_TEST(async_fail_fires_once);
}

/* one scripted route per status; sync call with a fail callback capturing
 * the mapped CCORDcode and error body */
static CCORDcode
fetch_status(u64snowflake channel_id,
             int status,
             const char *body,
             struct async_result *res)
{
    struct discord_ret_channel ret = {
        .sync = DISCORD_SYNC_FLAG,
        .fail = on_fail,
        .data = res,
    };
    char path[64];

    snprintf(path, sizeof path, "/channels/%" PRIu64, channel_id);
    fixture_server_script(FS, &(struct fs_script){
                                  .method = "GET",
                                  .path = path,
                                  .status = status,
                                  .body = body,
                              });
    return discord_get_channel(CLIENT, channel_id, &ret);
}

TEST
error_400_json_code(void)
{
    struct async_result res = { 0 };

    ASSERT_EQ(CCORD_DISCORD_JSON_CODE,
              fetch_status(603ULL, 400,
                           "{\"message\": \"Invalid Form Body\", \"code\": "
                           "50035}",
                           &res));
    ASSERT_EQ(1, res.fail_count);
    ASSERT_NEQ(NULL, strstr(res.json, "Invalid Form Body"));
    PASS();
}

TEST
error_401_bad_auth(void)
{
    struct async_result res = { 0 };

    ASSERT_EQ(CCORD_DISCORD_BAD_AUTH,
              fetch_status(604ULL, 401,
                           "{\"message\": \"401: Unauthorized\", \"code\": "
                           "0}",
                           &res));
    ASSERT_EQ(1, res.fail_count);
    /* 401 bodies are not surfaced (info extraction skips the copy) */
    ASSERT_EQ((size_t)0, res.json_len);
    PASS();
}

TEST
error_403_json_code(void)
{
    struct async_result res = { 0 };

    ASSERT_EQ(CCORD_DISCORD_JSON_CODE,
              fetch_status(605ULL, 403,
                           "{\"message\": \"Missing Access\", \"code\": "
                           "50001}",
                           &res));
    ASSERT_EQ(1, res.fail_count);
    ASSERT_NEQ(NULL, strstr(res.json, "Missing Access"));
    PASS();
}

TEST
error_404_json_code(void)
{
    struct async_result res = { 0 };

    ASSERT_EQ(CCORD_DISCORD_JSON_CODE,
              fetch_status(606ULL, 404,
                           "{\"message\": \"Unknown Channel\", \"code\": "
                           "10003}",
                           &res));
    ASSERT_EQ(1, res.fail_count);
    PASS();
}

TEST
error_500_retried_then_http_code(void)
{
    struct async_result res = { 0 };

    /* server errors are retried up to the requestor's retry_limit (3):
     * expect the original attempt plus 3 retries in the journal */
    ASSERT_EQ(CCORD_HTTP_CODE,
              fetch_status(607ULL, 500,
                           "{\"message\": \"Internal Server Error\"}",
                           &res));
    ASSERT_EQ((size_t)4, fixture_server_count_path(FS, "/channels/607"));
    PASS();
}

SUITE(error_mapping)
{
    RUN_TEST(error_400_json_code);
    RUN_TEST(error_401_bad_auth);
    RUN_TEST(error_403_json_code);
    RUN_TEST(error_404_json_code);
    RUN_TEST(error_500_retried_then_http_code);
}

TEST
json_post_body_encoded(void)
{
    struct discord_message msg = { 0 };
    struct discord_ret_message ret = { .sync = &msg };
    const struct fs_request *req;
    const char *ctype;
    size_t ctype_len, base = fixture_server_request_count(FS);
    test_json tj;

    fixture_server_script(FS, &(struct fs_script){
                                  .method = "POST",
                                  .path = "/channels/608/messages",
                                  .status = 200,
                                  .body_fixture = "message-plain.json",
                              });

    ASSERT_EQ(CCORD_OK,
              discord_create_message(
                  CLIENT, 608ULL,
                  &(struct discord_create_message){
                      .content = "Hello, concord!",
                  },
                  &ret));
    /* decoded response */
    ASSERT_EQ(1000000000000000100ULL, msg.id);
    ASSERT_STR_EQ("Hello, concord!", msg.content);
    discord_data_cleanup(CLIENT, &msg);

    /* request-side: params encoder output observed on the wire (the
     * loop-closer with the B03 codec suites) */
    req = fixture_server_request(FS, base);
    ASSERT_NEQ(NULL, req);
    ASSERT_STR_EQ("POST", req->method);
    ctype = fs_request_header(req, "Content-Type", &ctype_len);
    ASSERT_NEQ(NULL, ctype);
    ASSERT_EQ(0, strncmp("application/json", ctype, ctype_len));
    ASSERT_EQ(0, test_json_load(&tj, req->body, req->body_len));
    ASSERT_JSON_PATH_STR(&tj, "content", "Hello, concord!");
    test_json_unload(&tj);
    PASS();
}

TEST
multipart_upload_encoded(void)
{
    struct discord_ret_message ret = { .sync = DISCORD_SYNC_FLAG };
    const struct fs_request *req;
    const char *ctype;
    size_t ctype_len, base = fixture_server_request_count(FS);

    fixture_server_script(FS, &(struct fs_script){
                                  .method = "POST",
                                  .path = "/channels/609/messages",
                                  .status = 200,
                                  .body_fixture =
                                      "message-with-attachments.json",
                              });

    ASSERT_EQ(CCORD_OK,
              discord_create_message(
                  CLIENT, 609ULL,
                  &(struct discord_create_message){
                      .content = "file incoming",
                      .attachments =
                          &(struct discord_attachments){
                              .size = 1,
                              .array =
                                  &(struct discord_attachment){
                                      .content = "hello",
                                      .filename = "hello.txt",
                                      .content_type = "text/plain",
                                  },
                          },
                  },
                  &ret));

    req = fixture_server_request(FS, base);
    ASSERT_NEQ(NULL, req);
    ctype = fs_request_header(req, "Content-Type", &ctype_len);
    ASSERT_NEQ(NULL, ctype);
    ASSERT_EQ(0, strncmp("multipart/form-data", ctype,
                         strlen("multipart/form-data")));
    /* the params JSON rides in the payload_json part, the in-memory
     * attachment in files[0] */
    ASSERT_NEQ(NULL, strstr(req->body, "name=\"payload_json\""));
    ASSERT_NEQ(NULL, strstr(req->body, "\"content\":\"file incoming\""));
    ASSERT_NEQ(NULL, strstr(req->body, "name=\"files[0]\""));
    ASSERT_NEQ(NULL, strstr(req->body, "filename=\"hello.txt\""));
    ASSERT_NEQ(NULL, strstr(req->body, "hello"));
    PASS();
}

TEST
audit_log_reason_header(void)
{
    struct discord_ret_channel ret = { .sync = DISCORD_SYNC_FLAG };
    const struct fs_request *req;
    const char *reason;
    size_t reason_len, base = fixture_server_request_count(FS);

    fixture_server_script(FS, &(struct fs_script){
                                  .method = "DELETE",
                                  .path = "/channels/610",
                                  .status = 200,
                                  .body_fixture = "channel-text.json",
                              });

    ASSERT_EQ(CCORD_OK,
              discord_delete_channel(CLIENT, 610ULL,
                                     &(struct discord_delete_channel){
                                         .reason = "spring cleaning",
                                     },
                                     &ret));

    req = fixture_server_request(FS, base);
    ASSERT_NEQ(NULL, req);
    reason = fs_request_header(req, "X-Audit-Log-Reason", &reason_len);
    ASSERT_NEQ(NULL, reason);
    ASSERT_EQ(strlen("spring cleaning"), reason_len);
    ASSERT_EQ(0, strncmp("spring cleaning", reason, reason_len));
    PASS();
}

SUITE(request_side)
{
    RUN_TEST(json_post_body_encoded);
    RUN_TEST(multipart_upload_encoded);
    RUN_TEST(audit_log_reason_header);
}

TEST
malformed_json_yields_zeroed_object(void)
{
    struct discord_channel channel = { 0 };
    struct discord_ret_channel ret = { .sync = &channel };

    fixture_server_script(FS, &(struct fs_script){
                                  .method = "GET",
                                  .path = "/channels/611",
                                  .status = 200,
                                  .body = "{not json",
                              });

    /* documents CURRENT behavior, not an endorsement: the decoder's return
     * value is ignored by the requestor, so an unparseable 200 body
     * surfaces as CCORD_OK with an untouched output object */
    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 611ULL, &ret));
    ASSERT_EQ(0ULL, channel.id);
    discord_data_cleanup(CLIENT, &channel);
    PASS();
}

TEST
connection_drop_fails_cleanly(void)
{
    struct discord_channel channel = { 0 };
    struct discord_ret_channel ret = { .sync = &channel };

    fixture_server_script(FS, &(struct fs_script){
                                  .method = "GET",
                                  .path = "/channels/612",
                                  .status = 200,
                                  .body = "{\"id\": \"612\", \"name\": "
                                          "\"never-delivered\"}",
                                  .drop = FS_DROP_MID_BODY,
                              });

    ASSERT_EQ(CCORD_CURLE_INTERNAL,
              discord_get_channel(CLIENT, 612ULL, &ret));
    PASS();
}

TEST
bounded_delay_tolerated(void)
{
    struct discord_ret_channel ret = { .sync = DISCORD_SYNC_FLAG };
    const u64unix_ms before = cog_timestamp_ms();

    fixture_server_script(FS, &(struct fs_script){
                                  .method = "GET",
                                  .path = "/channels/613",
                                  .status = 200,
                                  .body_fixture = "channel-text.json",
                                  .delay_ms = 500,
                              });

    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 613ULL, &ret));
    ASSERT(cog_timestamp_ms() - before >= 500);
    PASS();
}

SUITE(resilience)
{
    RUN_TEST(malformed_json_yields_zeroed_object);
    RUN_TEST(connection_drop_fails_cleanly);
    RUN_TEST(bounded_delay_tolerated);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();

    alarm(60); /* no client-side request timeout exists: a pipeline hang
                * must fail the suite, not wedge `make check` */

    FS = fixture_server_start();
    assert(FS != NULL && "couldn't start fixture server");
    CLIENT = test_client_boot(FS);
    assert(CLIENT != NULL && "couldn't boot client against loopback");

    RUN_SUITE(dispatch);
    RUN_SUITE(error_mapping);
    RUN_SUITE(request_side);
    RUN_SUITE(resilience);

    discord_cleanup(CLIENT);
    fixture_server_stop(FS);
    GREATEST_MAIN_END();
}
