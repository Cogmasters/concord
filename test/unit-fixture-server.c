#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "fixture-server.h"
#include "test-utils.h"

/* Self-test for the loopback fixture HTTP server, driven by plain
 * curl_easy handles (the discord client is not involved here). */

struct resp_buf {
    char data[8192];
    size_t len;
    long status;
};

static size_t
_write_cb(char *ptr, size_t size, size_t nmemb, void *p)
{
    struct resp_buf *out = p;
    const size_t n = size * nmemb;

    if (out->len + n < sizeof out->data) {
        memcpy(out->data + out->len, ptr, n);
        out->len += n;
        out->data[out->len] = '\0';
    }
    return n;
}

static CURLcode
fetch(CURL *curl,
      unsigned short port,
      const char *method,
      const char *path,
      const char *body,
      struct curl_slist *headers,
      struct resp_buf *out)
{
    char url[256];
    CURLcode code;

    memset(out, 0, sizeof *out);
    snprintf(url, sizeof url, "http://127.0.0.1:%hu%s", port, path);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    if (body)
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);

    code = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &out->status);
    return code;
}

TEST
scripted_200_fixture_body(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;
    size_t fixture_len;
    char *fixture = test_load_json_fixture("user-basic.json", &fixture_len);

    ASSERT_NEQ(NULL, fs);
    ASSERT_NEQ(NULL, fixture);
    fixture_server_script(fs, &(struct fs_script){
                                  .method = "GET",
                                  .path = "/users/@me",
                                  .status = 200,
                                  .body_fixture = "user-basic.json",
                              });

    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET",
                              "/users/@me", NULL, NULL, &out));
    ASSERT_EQ(200, out.status);
    ASSERT_EQ(fixture_len, out.len);
    ASSERT_STR_EQ(fixture, out.data);

    free(fixture);
    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

TEST
journal_records_request(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;
    struct resp_buf out;
    const struct fs_request *r0, *r1;
    const char *value;
    size_t value_len;

    headers = curl_slist_append(headers, "X-Test: hello");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    fixture_server_script(fs, &(struct fs_script){
                                  .method = "POST",
                                  .path = "/widgets",
                                  .status = 201,
                                  .body = "{\"ok\":true}",
                              });

    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET", "/first",
                              NULL, NULL, &out));
    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "POST",
                              "/widgets", "{\"name\":\"gear\"}", headers,
                              &out));
    ASSERT_EQ(201, out.status);

    ASSERT_EQ((size_t)2, fixture_server_request_count(fs));
    r0 = fixture_server_request(fs, 0);
    r1 = fixture_server_request(fs, 1);
    ASSERT_NEQ(NULL, r0);
    ASSERT_NEQ(NULL, r1);
    ASSERT_STR_EQ("GET", r0->method);
    ASSERT_STR_EQ("/first", r0->path);
    ASSERT_STR_EQ("POST", r1->method);
    ASSERT_STR_EQ("/widgets", r1->path);
    ASSERT(r1->recv_ms >= r0->recv_ms);

    value = fs_request_header(r1, "x-test", &value_len);
    ASSERT_NEQ(NULL, value);
    ASSERT_EQ((size_t)5, value_len);
    ASSERT_EQ(0, strncmp("hello", value, value_len));
    ASSERT_EQ(NULL, fs_request_header(r1, "x-absent", &value_len));

    ASSERT_EQ(strlen("{\"name\":\"gear\"}"), r1->body_len);
    ASSERT_STR_EQ("{\"name\":\"gear\"}", r1->body);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

TEST
default_404_for_unscripted(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;

    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET",
                              "/nowhere", NULL, NULL, &out));
    ASSERT_EQ(404, out.status);
    ASSERT_NEQ(NULL, strstr(out.data, "404: Not Found"));

    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

TEST
delay_holds_response(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;
    double elapsed;

    fixture_server_script(fs, &(struct fs_script){
                                  .path = "/slow",
                                  .status = 200,
                                  .body = "{}",
                                  .delay_ms = 300,
                              });

    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET", "/slow",
                              NULL, NULL, &out));
    ASSERT_EQ(200, out.status);
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
    ASSERT(elapsed >= 0.3);

    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

TEST
drop_mid_body(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;

    fixture_server_script(fs, &(struct fs_script){
                                  .path = "/flaky",
                                  .status = 200,
                                  .body = "{\"data\": \"0123456789\"}",
                                  .drop = FS_DROP_MID_BODY,
                              });

    ASSERT_EQ(CURLE_PARTIAL_FILE, fetch(curl, fixture_server_port(fs), "GET",
                                        "/flaky", NULL, NULL, &out));

    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

TEST
drop_before_response(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;

    fixture_server_script(fs, &(struct fs_script){
                                  .path = "/mute",
                                  .status = 200,
                                  .body = "{}",
                                  .drop = FS_DROP_BEFORE_RESPONSE,
                              });

    /* on a fresh (non-reused) connection the close is a hard failure;
     * the request is still journaled */
    ASSERT_EQ(CURLE_GOT_NOTHING, fetch(curl, fixture_server_port(fs), "GET",
                                       "/mute", NULL, NULL, &out));
    ASSERT_EQ((size_t)1, fixture_server_request_count(fs));

    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

TEST
two_instances_isolated(void)
{
    struct fixture_server *fs1 = fixture_server_start();
    struct fixture_server *fs2 = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;

    ASSERT_NEQ(NULL, fs1);
    ASSERT_NEQ(NULL, fs2);
    ASSERT(fixture_server_port(fs1) != fixture_server_port(fs2));

    fixture_server_script(fs1, &(struct fs_script){
                                   .path = "/which",
                                   .status = 200,
                                   .body = "{\"server\":1}",
                               });
    fixture_server_script(fs2, &(struct fs_script){
                                   .path = "/which",
                                   .status = 200,
                                   .body = "{\"server\":2}",
                               });

    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs1), "GET", "/which",
                              NULL, NULL, &out));
    ASSERT_NEQ(NULL, strstr(out.data, "\"server\":1"));
    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs2), "GET", "/which",
                              NULL, NULL, &out));
    ASSERT_NEQ(NULL, strstr(out.data, "\"server\":2"));

    ASSERT_EQ((size_t)1, fixture_server_request_count(fs1));
    ASSERT_EQ((size_t)1, fixture_server_request_count(fs2));

    curl_easy_cleanup(curl);
    fixture_server_stop(fs1);
    fixture_server_stop(fs2);
    PASS();
}

TEST
keepalive_reuses_connection(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;

    fixture_server_script(fs, &(struct fs_script){
                                  .path = "/ka",
                                  .status = 200,
                                  .body = "{}",
                              });

    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET", "/ka",
                              NULL, NULL, &out));
    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET", "/ka",
                              NULL, NULL, &out));

    /* two requests served over a single accepted connection */
    ASSERT_EQ((size_t)2, fixture_server_request_count(fs));
    ASSERT_EQ((size_t)1, fixture_server_connection_count(fs));

    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

TEST
times_consumes_script(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;

    /* first match consumes the 500; later requests fall through to 200 */
    fixture_server_script(fs, &(struct fs_script){
                                  .path = "/seq",
                                  .status = 500,
                                  .body = "{\"oops\":true}",
                                  .times = 1,
                              });
    fixture_server_script(fs, &(struct fs_script){
                                  .path = "/seq",
                                  .status = 200,
                                  .body = "{\"ok\":true}",
                              });

    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET", "/seq",
                              NULL, NULL, &out));
    ASSERT_EQ(500, out.status);
    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET", "/seq",
                              NULL, NULL, &out));
    ASSERT_EQ(200, out.status);

    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

TEST
reset_clears_state(void)
{
    struct fixture_server *fs = fixture_server_start();
    CURL *curl = curl_easy_init();
    struct resp_buf out;

    fixture_server_script(fs, &(struct fs_script){
                                  .path = "/gone",
                                  .status = 200,
                                  .body = "{}",
                              });
    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET", "/gone",
                              NULL, NULL, &out));
    ASSERT_EQ(200, out.status);

    fixture_server_reset(fs);

    ASSERT_EQ((size_t)0, fixture_server_request_count(fs));
    ASSERT_EQ(CURLE_OK, fetch(curl, fixture_server_port(fs), "GET", "/gone",
                              NULL, NULL, &out));
    ASSERT_EQ(404, out.status);
    ASSERT_EQ((size_t)1, fixture_server_request_count(fs));

    curl_easy_cleanup(curl);
    fixture_server_stop(fs);
    PASS();
}

SUITE(fixture_server)
{
    RUN_TEST(scripted_200_fixture_body);
    RUN_TEST(journal_records_request);
    RUN_TEST(default_404_for_unscripted);
    RUN_TEST(delay_holds_response);
    RUN_TEST(drop_mid_body);
    RUN_TEST(drop_before_response);
    RUN_TEST(two_instances_isolated);
    RUN_TEST(keepalive_reuses_connection);
    RUN_TEST(times_consumes_script);
    RUN_TEST(reset_clears_state);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    curl_global_init(CURL_GLOBAL_DEFAULT);
    RUN_SUITE(fixture_server);
    curl_global_cleanup();
    GREATEST_MAIN_END();
}
