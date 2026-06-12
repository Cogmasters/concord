#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "discord.h"
#include "discord-internal.h"

#include "fixture-server.h"
#include "test-client.h" /* TEST_DUMMY_TOKEN; boot is done by hand here */
#include "test-utils.h"

/* Hermetic regression suite for GitHub issue #227: messages routed
 * through client->logger (the "CLIENT" context) must honor the
 * discord_config.log directives. On the unfixed code the CLIENT logger
 * is created before _discord_init() applies the config via
 * logmod_set_options() — which only affects loggers created afterwards
 * — so it runs with zeroed options forever: log.quiet is ignored (the
 * "Exits main gateway loop" message from discord_run() prints to
 * stdout) and log.trace never receives its messages.
 *
 * The suite boots by hand like unit-base-url: a token boot performs a
 * synchronous GET /users/@me, so the fixture server is scripted before
 * construction. */

static struct discord *
boot_with_log_config(struct fixture_server *fs, FILE *trace)
{
    static char base_url[64]; /* must outlive the client; borrowed by it */

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
    snprintf(base_url, sizeof base_url, "http://127.0.0.1:%hu",
             fixture_server_port(fs));

    return discord_from_config(&(struct discord_config){
        /* discord_cleanup() frees config.token and fcloses log.trace:
         * token must be heap'd, trace is owned by the client */
        .token = strdup(TEST_DUMMY_TOKEN),
        .base_url = base_url,
        .log = { .quiet = true, .trace = trace },
    });
}

/* Emit MARKER at INFO level through LOGGER with stdout redirected to a
 * temporary file; whatever reached stdout is copied into OUT. The
 * window is kept tight so only the logmod_log() call is captured.
 * Returns 0 on success, -1 on harness failure. */
static int
log_with_stdout_captured(const struct logmod_logger *logger,
                         const char *marker,
                         char *out,
                         size_t outsz)
{
    FILE *cap = tmpfile();
    int saved_fd;
    size_t n;

    if (!cap) return -1;
    fflush(stdout);
    if ((saved_fd = dup(STDOUT_FILENO)) == -1) {
        fclose(cap);
        return -1;
    }
    if (dup2(fileno(cap), STDOUT_FILENO) == -1) {
        close(saved_fd);
        fclose(cap);
        return -1;
    }
    logmod_log(INFO, logger, "%s", marker);
    fflush(stdout);
    dup2(saved_fd, STDOUT_FILENO);
    close(saved_fd);
    rewind(cap);
    n = fread(out, 1, outsz - 1, cap);
    out[n] = '\0';
    fclose(cap);
    return 0;
}

static void
file_contents(FILE *f, char *out, size_t outsz)
{
    size_t n;
    fflush(f);
    rewind(f);
    n = fread(out, 1, outsz - 1, f);
    out[n] = '\0';
}

/* config.log.quiet = true must silence the client logger's console
 * output (issue #227: the discord_run() exit message prints to stdout
 * regardless) */
TEST
client_logger_honors_quiet(void)
{
    struct fixture_server *fs = fixture_server_start();
    FILE *trace = tmpfile();
    struct discord *client;
    char captured[1024];

    ASSERT_NEQ(NULL, fs);
    ASSERT_NEQ(NULL, trace);
    client = boot_with_log_config(fs, trace);
    ASSERT_NEQ(NULL, client);

    ASSERT_EQ(0, log_with_stdout_captured(client->logger,
                                          "issue227-quiet-marker", captured,
                                          sizeof captured));
    ASSERT_EQm(captured, NULL, strstr(captured, "issue227-quiet-marker"));

    discord_cleanup(client);
    fixture_server_stop(fs);
    PASS();
}

/* config.log.trace must receive client-logger messages (issue #227:
 * the exit message is absent from the log file, leaving a counter gap) */
TEST
client_logger_writes_to_trace_file(void)
{
    struct fixture_server *fs = fixture_server_start();
    FILE *trace = tmpfile();
    struct discord *client;
    char captured[1024], traced[4096];

    ASSERT_NEQ(NULL, fs);
    ASSERT_NEQ(NULL, trace);
    client = boot_with_log_config(fs, trace);
    ASSERT_NEQ(NULL, client);

    /* stdout stays captured so an unfixed run doesn't pollute the test
     * harness output */
    ASSERT_EQ(0, log_with_stdout_captured(client->logger,
                                          "issue227-trace-marker", captured,
                                          sizeof captured));
    file_contents(trace, traced, sizeof traced);
    ASSERT_NEQm("marker missing from trace logfile", NULL,
                strstr(traced, "issue227-trace-marker"));

    discord_cleanup(client);
    fixture_server_stop(fs);
    PASS();
}

/* guard rail: a logger created after _discord_init() inherits the
 * config-derived defaults — proves the capture harness and the option
 * plumbing are sound on unfixed code */
TEST
late_logger_honors_log_config(void)
{
    struct fixture_server *fs = fixture_server_start();
    FILE *trace = tmpfile();
    struct discord *client;
    struct logmod_logger *late;
    char captured[1024], traced[4096];

    ASSERT_NEQ(NULL, fs);
    ASSERT_NEQ(NULL, trace);
    client = boot_with_log_config(fs, trace);
    ASSERT_NEQ(NULL, client);

    late = logmod_get_logger(&client->logmod, "TESTLATE");
    ASSERT_NEQ(NULL, late);
    ASSERT_EQ(0, log_with_stdout_captured(late, "issue227-late-marker",
                                          captured, sizeof captured));
    ASSERT_EQm(captured, NULL, strstr(captured, "issue227-late-marker"));
    file_contents(trace, traced, sizeof traced);
    ASSERT_NEQm("marker missing from trace logfile", NULL,
                strstr(traced, "issue227-late-marker"));

    discord_cleanup(client);
    fixture_server_stop(fs);
    PASS();
}

SUITE(client_log)
{
    RUN_TEST(client_logger_honors_quiet);
    RUN_TEST(client_logger_writes_to_trace_file);
    RUN_TEST(late_logger_honors_log_config);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(client_log);
    GREATEST_MAIN_END();
}
