#ifndef FIXTURE_SERVER_H
#define FIXTURE_SERVER_H

#include <stddef.h>
#include <stdint.h>

/* In-process loopback HTTP/1.1 fixture server for hermetic tests.
 *
 * Each instance owns one acceptor/IO thread that multiplexes its open
 * connections with poll() — required because libcurl keeps connections
 * alive and reuses them across requests. Requests are parsed and answered
 * sequentially within that thread, so journal ordering is deterministic.
 * A scripted `delay_ms` blocks the whole instance for its duration; no
 * planned test needs another response to progress during a delay.
 *
 * No globals: multiple instances may run in one process.
 *
 * Typical usage:
 *
 *   struct fixture_server *fs = fixture_server_start();
 *   fixture_server_script(fs, &(struct fs_script){
 *       .method = "GET", .path = "/users/@me",
 *       .status = 200, .body_fixture = "user-basic.json",
 *   });
 *   ... point a client at http://127.0.0.1:<fixture_server_port(fs)> ...
 *   const struct fs_request *r = fixture_server_request(fs, 0);
 *   ... assert on r->method / r->path / fs_request_header(...) ...
 *   fixture_server_stop(fs);
 */

struct fs_header {
    const char *name;
    const char *value;
};

enum fs_drop {
    FS_DROP_NONE = 0,
    /* journal the request, then close the socket without responding.
     * NOTE: when this happens on a reused (keep-alive) connection libcurl
     * transparently retries on a fresh connection, inflating journal
     * counts — integration tests should prefer FS_DROP_MID_BODY */
    FS_DROP_BEFORE_RESPONSE,
    /* send the response headers (full Content-Length advertised) plus half
     * the body, then close: deterministic CURLE_PARTIAL_FILE */
    FS_DROP_MID_BODY,
};

/* a scripted response; matched by registration order, first hit wins.
 * All pointed-to data is deep-copied at registration time, so compound
 * literals are safe. */
struct fs_script {
    const char *method; /**< exact match, e.g. "GET"; NULL matches any */
    const char *path; /**< exact match, e.g. "/users/@me" */
    int status; /**< HTTP status code of the response */
    const struct fs_header *headers; /**< extra response headers */
    size_t n_headers;
    const char *body; /**< literal response body; wins over body_fixture */
    const char *body_fixture; /**< file under test/fixtures/ to serve */
    long delay_ms; /**< sleep before responding */
    enum fs_drop drop;
    int times; /**< consume after N matches; 0 = unlimited */
};

/* a journaled request (owned by the server; valid until reset/stop) */
struct fs_request {
    char method[16];
    char path[512];
    char *headers_raw; /**< full raw header block, NUL-terminated */
    char *body;
    size_t body_len;
    uint64_t recv_ms; /**< CLOCK_MONOTONIC ms when fully received */
};

struct fixture_server;

/* bind 127.0.0.1:0, spawn the IO thread; NULL on failure */
struct fixture_server *fixture_server_start(void);
/* the bound ephemeral port */
unsigned short fixture_server_port(const struct fixture_server *fs);
/* register a scripted response (deep-copied); unmatched requests get a
 * default 404 with a JSON body */
void fixture_server_script(struct fixture_server *fs,
                           const struct fs_script *script);
/* clear all scripts and the journal */
void fixture_server_reset(struct fixture_server *fs);
/* shut down the IO thread, close sockets, free everything */
void fixture_server_stop(struct fixture_server *fs);

/* number of requests fully received so far */
size_t fixture_server_request_count(struct fixture_server *fs);
/* the Nth journaled request, or NULL; pointer stable until reset/stop */
const struct fs_request *fixture_server_request(struct fixture_server *fs,
                                                size_t n);
/* journal hits on an exact path */
size_t fixture_server_count_path(struct fixture_server *fs,
                                 const char *path);
/* recv_ms of the Nth (0-indexed) journaled request on `path`; 0 if absent */
uint64_t fixture_server_nth_recv_ms(struct fixture_server *fs,
                                    const char *path,
                                    size_t nth);
/* number of TCP connections accepted so far */
size_t fixture_server_connection_count(struct fixture_server *fs);

/* case-insensitive header lookup inside a journaled request; returns a
 * pointer into headers_raw (not NUL-terminated, use *value_len) or NULL */
const char *fs_request_header(const struct fs_request *r,
                              const char *name,
                              size_t *value_len);

#endif /* FIXTURE_SERVER_H */
