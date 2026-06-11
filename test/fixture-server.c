#include <errno.h>
#include <poll.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "fixture-server.h"

#define FS_MAX_CONNS    16
#define FS_DEFAULT_BODY "{\"message\": \"404: Not Found\", \"code\": 0}"

struct _fs_script {
    char *method;
    char *path;
    int status;
    struct fs_header *headers; /* deep-copied name/value strings */
    size_t n_headers;
    char *body;
    size_t body_len;
    long delay_ms;
    enum fs_drop drop;
    int times; /* 0 = unlimited */
    int used;
};

struct _fs_conn {
    int fd;
    char *buf;
    size_t len;
    size_t cap;
};

struct fixture_server {
    int listen_fd;
    int stop_pipe[2];
    unsigned short port;
    pthread_t thread;
    pthread_mutex_t lock; /* guards scripts + journal + counters */

    struct _fs_script *scripts;
    size_t n_scripts, cap_scripts;

    /* entries are individually allocated so pointers handed out by
     * fixture_server_request() survive journal growth */
    struct fs_request **journal;
    size_t n_journal, cap_journal;

    size_t n_conns_accepted;

    struct _fs_conn conns[FS_MAX_CONNS];
};

static uint64_t
_fs_monotonic_ms(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000 + (uint64_t)ts.tv_nsec / 1000000;
}

static void
_fs_sleep_ms(long ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000000L };

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR)
        continue;
}

/* load a file from test/fixtures/ (cwd is test/, mirroring
 * test_load_json_fixture() without dragging test-utils.h in) */
static char *
_fs_load_fixture(const char *name, size_t *p_len)
{
    char path[1024];
    FILE *fp;
    char *buf = NULL;
    long size;

    snprintf(path, sizeof path, "fixtures/%s", name);
    if (!(fp = fopen(path, "rb"))) {
        fprintf(stderr, "fixture-server: can't open %s: %s\n", path,
                strerror(errno));
        return NULL;
    }
    if (fseek(fp, 0, SEEK_END) == 0 && (size = ftell(fp)) >= 0
        && fseek(fp, 0, SEEK_SET) == 0 && (buf = malloc((size_t)size + 1)))
    {
        if (fread(buf, 1, (size_t)size, fp) == (size_t)size) {
            buf[size] = '\0';
            *p_len = (size_t)size;
        }
        else {
            free(buf);
            buf = NULL;
        }
    }
    fclose(fp);
    return buf;
}

static const char *
_fs_status_reason(int status)
{
    switch (status) {
    case 200:
        return "OK";
    case 201:
        return "Created";
    case 204:
        return "No Content";
    case 400:
        return "Bad Request";
    case 401:
        return "Unauthorized";
    case 403:
        return "Forbidden";
    case 404:
        return "Not Found";
    case 405:
        return "Method Not Allowed";
    case 429:
        return "Too Many Requests";
    case 500:
        return "Internal Server Error";
    default:
        return "Status";
    }
}

static void *_fs_thread_main(void *p_fs);

struct fixture_server *
fixture_server_start(void)
{
    struct fixture_server *fs = calloc(1, sizeof *fs);
    struct sockaddr_in addr = { 0 };
    socklen_t addrlen = sizeof addr;
    int i;

    if (!fs) return NULL;
    for (i = 0; i < FS_MAX_CONNS; ++i)
        fs->conns[i].fd = -1;

    if ((fs->listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return free(fs), NULL;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = 0;
    if (bind(fs->listen_fd, (struct sockaddr *)&addr, sizeof addr) == -1
        || listen(fs->listen_fd, 16) == -1
        || getsockname(fs->listen_fd, (struct sockaddr *)&addr, &addrlen)
               == -1
        || pipe(fs->stop_pipe) == -1)
    {
        close(fs->listen_fd);
        return free(fs), NULL;
    }
    fs->port = ntohs(addr.sin_port);
    pthread_mutex_init(&fs->lock, NULL);
    if (pthread_create(&fs->thread, NULL, _fs_thread_main, fs) != 0) {
        close(fs->listen_fd);
        close(fs->stop_pipe[0]);
        close(fs->stop_pipe[1]);
        pthread_mutex_destroy(&fs->lock);
        return free(fs), NULL;
    }
    return fs;
}

unsigned short
fixture_server_port(const struct fixture_server *fs)
{
    return fs->port;
}

void
fixture_server_script(struct fixture_server *fs, const struct fs_script *s)
{
    struct _fs_script copy = { 0 };
    size_t i;

    copy.method = s->method ? strdup(s->method) : NULL;
    copy.path = s->path ? strdup(s->path) : NULL;
    copy.status = s->status;
    copy.delay_ms = s->delay_ms;
    copy.drop = s->drop;
    copy.times = s->times;
    if (s->n_headers) {
        copy.headers = calloc(s->n_headers, sizeof *copy.headers);
        for (i = 0; i < s->n_headers; ++i) {
            copy.headers[i].name = strdup(s->headers[i].name);
            copy.headers[i].value = strdup(s->headers[i].value);
        }
        copy.n_headers = s->n_headers;
    }
    if (s->body) {
        copy.body_len = strlen(s->body);
        copy.body = malloc(copy.body_len + 1);
        memcpy(copy.body, s->body, copy.body_len + 1);
    }
    else if (s->body_fixture) {
        copy.body = _fs_load_fixture(s->body_fixture, &copy.body_len);
    }

    pthread_mutex_lock(&fs->lock);
    if (fs->n_scripts == fs->cap_scripts) {
        fs->cap_scripts = fs->cap_scripts ? fs->cap_scripts * 2 : 8;
        fs->scripts =
            realloc(fs->scripts, fs->cap_scripts * sizeof *fs->scripts);
    }
    fs->scripts[fs->n_scripts++] = copy;
    pthread_mutex_unlock(&fs->lock);
}

static void
_fs_scripts_free(struct fixture_server *fs)
{
    size_t i, j;

    for (i = 0; i < fs->n_scripts; ++i) {
        struct _fs_script *s = &fs->scripts[i];

        free(s->method);
        free(s->path);
        for (j = 0; j < s->n_headers; ++j) {
            free((char *)s->headers[j].name);
            free((char *)s->headers[j].value);
        }
        free(s->headers);
        free(s->body);
    }
    free(fs->scripts);
    fs->scripts = NULL;
    fs->n_scripts = fs->cap_scripts = 0;
}

static void
_fs_journal_free(struct fixture_server *fs)
{
    size_t i;

    for (i = 0; i < fs->n_journal; ++i) {
        free(fs->journal[i]->headers_raw);
        free(fs->journal[i]->body);
        free(fs->journal[i]);
    }
    free(fs->journal);
    fs->journal = NULL;
    fs->n_journal = fs->cap_journal = 0;
}

void
fixture_server_reset(struct fixture_server *fs)
{
    pthread_mutex_lock(&fs->lock);
    _fs_scripts_free(fs);
    _fs_journal_free(fs);
    fs->n_conns_accepted = 0;
    pthread_mutex_unlock(&fs->lock);
}

size_t
fixture_server_request_count(struct fixture_server *fs)
{
    size_t n;

    pthread_mutex_lock(&fs->lock);
    n = fs->n_journal;
    pthread_mutex_unlock(&fs->lock);
    return n;
}

const struct fs_request *
fixture_server_request(struct fixture_server *fs, size_t n)
{
    const struct fs_request *r = NULL;

    pthread_mutex_lock(&fs->lock);
    if (n < fs->n_journal) r = fs->journal[n];
    pthread_mutex_unlock(&fs->lock);
    return r;
}

size_t
fixture_server_count_path(struct fixture_server *fs, const char *path)
{
    size_t i, n = 0;

    pthread_mutex_lock(&fs->lock);
    for (i = 0; i < fs->n_journal; ++i)
        if (0 == strcmp(fs->journal[i]->path, path)) ++n;
    pthread_mutex_unlock(&fs->lock);
    return n;
}

uint64_t
fixture_server_nth_recv_ms(struct fixture_server *fs,
                           const char *path,
                           size_t nth)
{
    uint64_t recv_ms = 0;
    size_t i, n = 0;

    pthread_mutex_lock(&fs->lock);
    for (i = 0; i < fs->n_journal; ++i) {
        if (0 == strcmp(fs->journal[i]->path, path) && n++ == nth) {
            recv_ms = fs->journal[i]->recv_ms;
            break;
        }
    }
    pthread_mutex_unlock(&fs->lock);
    return recv_ms;
}

size_t
fixture_server_connection_count(struct fixture_server *fs)
{
    size_t n;

    pthread_mutex_lock(&fs->lock);
    n = fs->n_conns_accepted;
    pthread_mutex_unlock(&fs->lock);
    return n;
}

/* case-insensitive header lookup in a NUL-terminated raw header block */
static const char *
_fs_find_header(const char *block, const char *name, size_t *value_len)
{
    const size_t name_len = strlen(name);
    const char *line = block;

    while (line && *line) {
        const char *eol = strstr(line, "\r\n");
        const size_t line_len = eol ? (size_t)(eol - line) : strlen(line);

        if (line_len > name_len + 1 && line[name_len] == ':'
            && strncasecmp(line, name, name_len) == 0)
        {
            const char *value = line + name_len + 1;
            const char *end = line + line_len;

            while (value < end && *value == ' ')
                ++value;
            if (value_len) *value_len = (size_t)(end - value);
            return value;
        }
        line = eol ? eol + 2 : NULL;
    }
    if (value_len) *value_len = 0;
    return NULL;
}

const char *
fs_request_header(const struct fs_request *r,
                  const char *name,
                  size_t *value_len)
{
    return _fs_find_header(r->headers_raw, name, value_len);
}

/* ---- IO thread ---------------------------------------------------- */

static void
_fs_conn_close(struct _fs_conn *conn)
{
    if (conn->fd != -1) close(conn->fd);
    free(conn->buf);
    conn->fd = -1;
    conn->buf = NULL;
    conn->len = conn->cap = 0;
}

static int
_fs_write_all(int fd, const char *buf, size_t len)
{
    while (len) {
        ssize_t n = write(fd, buf, len);

        if (n <= 0) return -1;
        buf += n;
        len -= (size_t)n;
    }
    return 0;
}

/* find the matching script (consuming a 'times' slot) under fs->lock;
 * returns a shallow snapshot since script storage is stable until reset */
static const struct _fs_script *
_fs_match(struct fixture_server *fs, const char *method, const char *path)
{
    size_t i;

    for (i = 0; i < fs->n_scripts; ++i) {
        struct _fs_script *s = &fs->scripts[i];

        if (s->times > 0 && s->used >= s->times) continue;
        if (s->method && strcmp(s->method, method) != 0) continue;
        if (s->path && strcmp(s->path, path) != 0) continue;
        s->used++;
        return s;
    }
    return NULL;
}

static void
_fs_journal_add(struct fixture_server *fs,
                const char *method,
                const char *path,
                const char *headers,
                size_t headers_len,
                const char *body,
                size_t body_len)
{
    struct fs_request *r = calloc(1, sizeof *r);

    if (fs->n_journal == fs->cap_journal) {
        fs->cap_journal = fs->cap_journal ? fs->cap_journal * 2 : 16;
        fs->journal =
            realloc(fs->journal, fs->cap_journal * sizeof *fs->journal);
    }
    fs->journal[fs->n_journal++] = r;
    snprintf(r->method, sizeof r->method, "%s", method);
    snprintf(r->path, sizeof r->path, "%s", path);
    r->headers_raw = malloc(headers_len + 1);
    memcpy(r->headers_raw, headers, headers_len);
    r->headers_raw[headers_len] = '\0';
    if (body_len) {
        r->body = malloc(body_len + 1);
        memcpy(r->body, body, body_len);
        r->body[body_len] = '\0';
    }
    r->body_len = body_len;
    r->recv_ms = _fs_monotonic_ms();
}

/* serve one fully-buffered request; returns 0 to keep the connection,
 * -1 to close it */
static int
_fs_serve(struct fixture_server *fs,
          struct _fs_conn *conn,
          const char *method,
          const char *path,
          const char *headers,
          size_t headers_len,
          const char *body,
          size_t body_len)
{
    const struct _fs_script *script;
    char head[2048];
    int head_len, status, ret = -1;
    bool matched;
    char *resp_body = NULL;
    struct fs_header *resp_headers = NULL;
    size_t resp_body_len = 0, n_resp_headers = 0, i;
    long delay_ms;
    enum fs_drop drop;

    /* deep-copy the matched script's response under the lock: a
     * concurrent fixture_server_reset() may free the script's
     * allocations while this thread is still writing them out */
    pthread_mutex_lock(&fs->lock);
    _fs_journal_add(fs, method, path, headers, headers_len, body, body_len);
    script = _fs_match(fs, method, path);
    matched = script != NULL;
    if (script) {
        status = script->status;
        resp_body_len = script->body_len;
        resp_body = malloc(resp_body_len + 1);
        memcpy(resp_body, script->body ? script->body : "", resp_body_len);
        resp_body[resp_body_len] = '\0';
        if (script->n_headers) {
            resp_headers = calloc(script->n_headers, sizeof *resp_headers);
            for (i = 0; i < script->n_headers; ++i) {
                resp_headers[i].name = strdup(script->headers[i].name);
                resp_headers[i].value = strdup(script->headers[i].value);
            }
            n_resp_headers = script->n_headers;
        }
        delay_ms = script->delay_ms;
        drop = script->drop;
    }
    else {
        status = 404;
        resp_body = strdup(FS_DEFAULT_BODY);
        resp_body_len = strlen(FS_DEFAULT_BODY);
        delay_ms = 0;
        drop = FS_DROP_NONE;
    }
    pthread_mutex_unlock(&fs->lock);

    if (delay_ms > 0) _fs_sleep_ms(delay_ms);
    if (drop == FS_DROP_BEFORE_RESPONSE) goto cleanup;

    head_len = snprintf(head, sizeof head, "HTTP/1.1 %d %s\r\n", status,
                        _fs_status_reason(status));
    if (matched) {
        for (i = 0; i < n_resp_headers; ++i)
            head_len +=
                snprintf(head + head_len, sizeof head - (size_t)head_len,
                         "%s: %s\r\n", resp_headers[i].name,
                         resp_headers[i].value);
    }
    else {
        head_len += snprintf(head + head_len,
                             sizeof head - (size_t)head_len,
                             "Content-Type: application/json\r\n");
    }
    head_len += snprintf(head + head_len, sizeof head - (size_t)head_len,
                         "Content-Length: %zu\r\n\r\n", resp_body_len);
    if (head_len >= (int)sizeof head) {
        fprintf(stderr, "fixture-server: response header overflow\n");
        goto cleanup;
    }

    if (_fs_write_all(conn->fd, head, (size_t)head_len) == -1) goto cleanup;
    if (drop == FS_DROP_MID_BODY) {
        _fs_write_all(conn->fd, resp_body, resp_body_len / 2);
        goto cleanup;
    }
    if (_fs_write_all(conn->fd, resp_body, resp_body_len) == -1) goto cleanup;
    ret = 0;

cleanup:
    for (i = 0; i < n_resp_headers; ++i) {
        free((char *)resp_headers[i].name);
        free((char *)resp_headers[i].value);
    }
    free(resp_headers);
    free(resp_body);
    return ret;
}

/* parse and serve as many complete requests as the buffer holds;
 * returns 0 to keep the connection, -1 to close it */
static int
_fs_conn_process(struct fixture_server *fs, struct _fs_conn *conn)
{
    while (conn->len) {
        char method[16] = "", path[512] = "";
        const char *headers_start, *headers_end, *body;
        size_t headers_len, content_length = 0, total;
        const char *line_end, *cl;

        conn->buf[conn->len] = '\0';

        if (!(headers_end = strstr(conn->buf, "\r\n\r\n")))
            return 0; /* incomplete header block: keep reading */

        if (sscanf(conn->buf, "%15s %511s", method, path) != 2) {
            fprintf(stderr, "fixture-server: malformed request line\n");
            return -1;
        }
        if (!(line_end = strstr(conn->buf, "\r\n"))) return -1;
        headers_start = line_end + 2;
        headers_len = (size_t)(headers_end - headers_start);

        /* only Content-Length framing is supported; fail loudly on
         * anything else (libcurl won't send chunked requests here) */
        if (strcmp(method, "GET") != 0) {
            /* bound the lookup to the header block by NUL-terminating it
             * in place for the probe's duration */
            char *const block_end = conn->buf + (headers_end - conn->buf);
            int expect;
            size_t v_len;

            *block_end = '\0';
            if (_fs_find_header(headers_start, "Transfer-Encoding", &v_len))
            {
                fprintf(stderr,
                        "fixture-server: unsupported Transfer-Encoding\n");
                return -1;
            }
            if ((cl = _fs_find_header(headers_start, "Content-Length",
                                      &v_len)))
                content_length = (size_t)strtoul(cl, NULL, 10);
            expect =
                _fs_find_header(headers_start, "Expect", &v_len) != NULL;
            *block_end = '\r';

            /* libcurl awaits the interim response before sending the
             * body on large uploads */
            if (expect
                && _fs_write_all(conn->fd, "HTTP/1.1 100 Continue\r\n\r\n",
                                 25)
                       == -1)
                return -1;
        }

        body = headers_end + 4;
        total = (size_t)(body - conn->buf) + content_length;
        if (conn->len < total) return 0; /* body incomplete: keep reading */

        if (_fs_serve(fs, conn, method, path, headers_start, headers_len,
                      body, content_length)
            == -1)
            return -1;

        /* consume the request; loop in case another one is buffered */
        memmove(conn->buf, conn->buf + total, conn->len - total);
        conn->len -= total;
    }
    return 0;
}

static int
_fs_conn_read(struct fixture_server *fs, struct _fs_conn *conn)
{
    ssize_t n;

    if (conn->cap - conn->len < 4096) {
        conn->cap = conn->cap ? conn->cap * 2 : 8192;
        conn->buf = realloc(conn->buf, conn->cap);
    }
    n = read(conn->fd, conn->buf + conn->len, conn->cap - conn->len - 1);
    if (n <= 0) return -1; /* peer closed or error */
    conn->len += (size_t)n;
    return _fs_conn_process(fs, conn);
}

static void *
_fs_thread_main(void *p_fs)
{
    struct fixture_server *fs = p_fs;

    while (1) {
        struct pollfd pfds[2 + FS_MAX_CONNS];
        int i, nfds = 2;

        pfds[0].fd = fs->stop_pipe[0];
        pfds[0].events = POLLIN;
        pfds[1].fd = fs->listen_fd;
        pfds[1].events = POLLIN;
        for (i = 0; i < FS_MAX_CONNS; ++i) {
            if (fs->conns[i].fd == -1) continue;
            pfds[nfds].fd = fs->conns[i].fd;
            pfds[nfds].events = POLLIN;
            ++nfds;
        }

        if (poll(pfds, (nfds_t)nfds, -1) == -1) {
            if (errno == EINTR) continue;
            break;
        }

        if (pfds[0].revents) break; /* stop requested */

        if (pfds[1].revents & POLLIN) {
            int fd = accept(fs->listen_fd, NULL, NULL);

            if (fd != -1) {
                for (i = 0; i < FS_MAX_CONNS; ++i) {
                    if (fs->conns[i].fd == -1) {
                        fs->conns[i].fd = fd;
                        break;
                    }
                }
                if (i == FS_MAX_CONNS) {
                    fprintf(stderr, "fixture-server: too many connections\n");
                    close(fd);
                }
                else {
                    pthread_mutex_lock(&fs->lock);
                    fs->n_conns_accepted++;
                    pthread_mutex_unlock(&fs->lock);
                }
            }
        }

        for (i = 2; i < nfds; ++i) {
            int j;

            if (!pfds[i].revents) continue;
            for (j = 0; j < FS_MAX_CONNS; ++j) {
                if (fs->conns[j].fd == pfds[i].fd) {
                    if (_fs_conn_read(fs, &fs->conns[j]) == -1)
                        _fs_conn_close(&fs->conns[j]);
                    break;
                }
            }
        }
    }
    return NULL;
}

void
fixture_server_stop(struct fixture_server *fs)
{
    int i;
    char byte = 0;

    if (!fs) return;
    if (write(fs->stop_pipe[1], &byte, 1) != 1) {
        fprintf(stderr, "fixture-server: failed to signal stop\n");
    }
    pthread_join(fs->thread, NULL);

    for (i = 0; i < FS_MAX_CONNS; ++i)
        _fs_conn_close(&fs->conns[i]);
    close(fs->listen_fd);
    close(fs->stop_pipe[0]);
    close(fs->stop_pipe[1]);
    _fs_scripts_free(fs);
    _fs_journal_free(fs);
    pthread_mutex_destroy(&fs->lock);
    free(fs);
}
