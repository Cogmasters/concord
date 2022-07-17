#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#include "io_poller.h"
#include "chash.h"
#include "cog-utils.h"

#if !defined(IO_POLLER_USE_SELECT) && !defined(IO_POLLER_USE_POLL)            \
    && !defined(IO_POLLER_USE_EPOLL)
#if defined(__MINGW32__)
#define IO_POLLER_USE_SELECT
#elif defined(__linux__)
#define IO_POLLER_USE_EPOLL
#endif
#endif

#if defined(IO_POLLER_USE_SELECT)
#include <sys/select.h>
#elif defined(IO_POLLER_USE_EPOLL)
#include <sys/epoll.h>
#else
#if !defined(IO_POLLER_USE_POLL)
#define IO_POLLER_USE_POLL
#endif
#include <poll.h>
#endif

/** fd_map */
#define FD_MAP_HEAP   1
#define FD_MAP_BUCKET struct fd_map_bucket
#define FD_MAP_FREE_KEY(_key)
#define FD_MAP_HASH(_key, _hash) ((int)(_key))
#define FD_MAP_FREE_VALUE(_value)
#define FD_MAP_COMPARE(_cmp_a, _cmp_b) (_cmp_a == _cmp_b)
#define FD_MAP_INIT(bucket, _key, _value)                                     \
    chash_default_init(bucket, _key, _value)

struct io_poller_element {
    void *user_data;
    io_poller_cb cb;
    enum io_poller_events events;
    enum io_poller_events revents;
    io_poller_socket fd;
#if defined(IO_POLLER_USE_POLL)
    int poll_position;
#endif
};

struct fd_map_bucket {
    io_poller_socket key;
    struct io_poller_element *value;
    int state;
};

struct fd_map {
    int length;
    int capacity;
    struct fd_map_bucket *buckets;
};
/** !fd_map */

/** intptr_map */
#define INTPTR_MAP_HEAP   1
#define INTPTR_MAP_BUCKET struct intptr_map_bucket
#define INTPTR_MAP_FREE_KEY(_key)
#define INTPTR_MAP_HASH(_key, _hash)  ((int)((intptr_t)_key))
#define INTPTR_MAP_FREE_VALUE(_value) free(_value);
#define INTPTR_MAP_COMPARE(_cmp_a, _cmp_b)                                    \
    (((intptr_t)_cmp_a) == ((intptr_t)_cmp_b))
#define INTPTR_MAP_INIT(bucket, _key, _value)                                 \
    chash_default_init(bucket, _key, _value)

struct intptr_map_bucket {
    intptr_t key;
    void *value;
    int state;
};

struct intptr_map {
    int length;
    int capacity;
    struct intptr_map_bucket *buckets;
};
/** !intptr_map */

struct io_curlm {
    CURLM *multi;
    struct io_poller *io_poller;
    struct fd_map *fds;
    io_poller_curl_multi_cb cb;
    int64_t timeout;
    void *user_data;
    enum io_poller_events events;
    int running;
    bool should_perform;
};

struct io_poller {
    void *data;
    struct {
        struct fd_map *ready;
        struct fd_map *watch;
    } fd_map;
    struct intptr_map *curlm_map;
#if defined(IO_POLLER_USE_POLL)
    struct pollfds {
        struct pollfd *pfds;
        struct io_poller_element **vals;
        int cnt;
        int cap;
    } pollfds;
#elif defined(IO_POLLER_USE_SELECT)
    struct {
        fd_set rset, wset;
    } select;
#elif defined(IO_POLLER_USE_EPOLL)
    int epfd;
#endif
    int wakeup_fds[2];
};

static void on_io_poller_wakeup(struct io_poller *io,
                                enum io_poller_events events,
                                void *user_data);

struct io_poller *
io_poller_create(void)
{
    struct io_poller *io = calloc(1, sizeof *io);
    if (io) {
#if defined(IO_POLLER_USE_EPOLL)
        if (-1 == (io->epfd = epoll_create1(0))) {
            free(io);
            return NULL;
        }
#endif
        chash_init(io->fd_map.watch, FD_MAP);
        chash_init(io->fd_map.ready, FD_MAP);
        chash_init(io->curlm_map, INTPTR_MAP);
        if (io->fd_map.watch && io->fd_map.ready && io->curlm_map) {
            if (0 == pipe(io->wakeup_fds)) {
                int flags = fcntl(io->wakeup_fds[0], F_GETFL);
                fcntl(io->wakeup_fds[0], F_SETFL, flags | O_NONBLOCK);

                io_poller_socket_add(io, io->wakeup_fds[0], IO_POLLER_IN,
                                     on_io_poller_wakeup, NULL);

                return io;
            }
        }
        if (io->fd_map.ready) chash_free(io->fd_map.ready, FD_MAP);
        if (io->fd_map.watch) chash_free(io->fd_map.watch, FD_MAP);
        if (io->curlm_map) chash_free(io->curlm_map, INTPTR_MAP);

#if defined(IO_POLLER_USE_EPOLL)
        close(io->epfd);
#endif
        free(io);
    }
    return NULL;
}

void
io_poller_destroy(struct io_poller *io)
{
    close(io->wakeup_fds[0]);
    close(io->wakeup_fds[1]);

    for (int i = 0; i < io->curlm_map->capacity; ++i) {
        if (io->curlm_map->buckets[i].state != CHASH_FILLED) continue;
        io_poller_curlm_del(io, (void *)io->curlm_map->buckets[i].key);
    }
    chash_free(io->curlm_map, INTPTR_MAP);

    for (int i = 0; i < io->fd_map.watch->capacity; ++i) {
        if (io->fd_map.watch->buckets[i].state != CHASH_FILLED) continue;
        io_poller_socket_del(io, io->fd_map.watch->buckets[i].key);
    }
    chash_free(io->fd_map.watch, FD_MAP);
    chash_free(io->fd_map.ready, FD_MAP);
#if defined(IO_POLLER_USE_POLL)
    free(io->pollfds.pfds);
    free(io->pollfds.vals);
#elif defined(IO_POLLER_USE_EPOLL)
    close(io->epfd);
#endif

    free(io);
}

void
io_poller_set_data(struct io_poller *io, void *data)
{
    io->data = data;
}

void *
io_poller_get_data(struct io_poller *io)
{
    return io->data;
}

void
io_poller_wakeup(struct io_poller *io)
{
    char buf = 0;
    (void)!write(io->wakeup_fds[1], &buf, sizeof buf);
}

static void
on_io_poller_wakeup(struct io_poller *io,
                    enum io_poller_events events,
                    void *user_data)
{
    char buf[0x1000];
    (void)!read(io->wakeup_fds[0], buf, sizeof buf);
}

static inline bool
io_poller_fd_map_ready_add(struct fd_map *fd_map,
                           io_poller_socket fd,
                           struct io_poller_element *val)
{
    bool found = chash_contains(fd_map, fd, found, FD_MAP);
    if (!found) chash_assign(fd_map, fd, val, FD_MAP);
    return !found;
}

int
io_poller_poll(struct io_poller *io, int ms)
{
    const int64_t now = cog_timestamp_ms();
    const int64_t millis = now + (ms == -1 ? 0 : ms);
    for (int i = 0; i < io->curlm_map->capacity && ms; i++) {
        if (io->curlm_map->buckets[i].state != CHASH_FILLED) continue;
        struct io_curlm *io_curlm = io->curlm_map->buckets[i].value;
        if (io_curlm->should_perform) {
            ms = 0;
        }
        else if (io_curlm->timeout != -1 && io_curlm->timeout < millis) {
            ms = io_curlm->timeout < now ? 0 : io_curlm->timeout - now;
        }
    }
#if defined(IO_POLLER_USE_SELECT)
    struct timeval tv = { .tv_sec = ms / 1000, .tv_usec = (ms % 1000) * 1000 };
    fd_set rset, wset;
    memcpy(&rset, &io->select.rset, sizeof rset);
    memcpy(&wset, &io->select.wset, sizeof wset);
    int cnt = select(FD_SETSIZE, &rset, &wset, NULL, ms == -1 ? NULL : &tv);
    if (-1 == cnt) return -1;
    for (int i = 0; i < io->fd_map.watch->capacity && cnt; i++) {
        if (io->fd_map.watch->buckets[i].state != CHASH_FILLED) continue;
        struct io_poller_element *val = io->fd_map.watch->buckets[i].value;
        if (FD_ISSET(val->fd, &rset)) val->revents |= IO_POLLER_IN;
        if (FD_ISSET(val->fd, &wset)) val->revents |= IO_POLLER_OUT;
        if (val->revents) {
            io_poller_fd_map_ready_add(io->fd_map.ready, val->fd, val);
            cnt--;
        }
    }
#elif defined(IO_POLLER_USE_POLL)
    int cnt = poll(io->pollfds.pfds, io->pollfds.cnt, ms);
    if (-1 == cnt) return -1;
    for (int i = 0; cnt; i++) {
        struct pollfd *pfd = &io->pollfds.pfds[i];
        if (pfd->revents) {
            cnt--;
            struct io_poller_element *val = io->pollfds.vals[i];
            if (pfd->revents & POLLIN) val->revents |= IO_POLLER_IN;
            if (pfd->revents & POLLOUT) val->revents |= IO_POLLER_OUT;
            io_poller_fd_map_ready_add(io->fd_map.ready, pfd->fd, val);
        }
    }
#elif defined(IO_POLLER_USE_EPOLL)
#define EPOLL_MAX_EVENTS 64
    struct epoll_event events[EPOLL_MAX_EVENTS];
    int cnt = epoll_wait(io->epfd, events, EPOLL_MAX_EVENTS, ms);
    if (cnt == -1) return -1;
    for (int i = 0; i < cnt; i++) {
        struct io_poller_element *val = events[i].data.ptr;
        if (events[i].events & EPOLLIN) val->revents |= IO_POLLER_IN;
        if (events[i].events & EPOLLOUT) val->revents |= IO_POLLER_OUT;
        io_poller_fd_map_ready_add(io->fd_map.ready, val->fd, val);
    }
#endif
    return io->fd_map.ready->length;
}

int
io_poller_perform(struct io_poller *io)
{
    // perform file descriptors
    for (int i = 0; i < io->fd_map.ready->capacity; ++i) {
        if (io->fd_map.ready->buckets[i].state != CHASH_FILLED) continue;
        io_poller_socket fd = io->fd_map.ready->buckets[i].key;
        struct io_poller_element *val = io->fd_map.ready->buckets[i].value;
        chash_delete(io->fd_map.ready, fd, FD_MAP);
        enum io_poller_events revents = val->revents;
        val->revents = 0;
        val->cb(io, revents, val->user_data);
    }

    for (int i = 0; i < io->curlm_map->capacity; i++) {
        if (io->curlm_map->buckets[i].state != CHASH_FILLED) continue;
        struct io_curlm *io_curlm = io->curlm_map->buckets[i].value;
        if (io_curlm->should_perform) {
            io_curlm->should_perform = false;
            int r = io_curlm->cb(io, io_curlm->multi, 0, io_curlm->user_data);
            if (r) return r;
        }
    }

    return 0;
}

void *
io_poller_socket_get_data(struct io_poller *io, io_poller_socket fd)
{

    struct io_poller_element *val;
    int found = chash_contains(io->fd_map.watch, fd, found, FD_MAP);
    if (!found) return NULL;
    val = chash_lookup(io->fd_map.watch, fd, val, FD_MAP);
    return val->user_data;
}

bool
io_poller_socket_add(struct io_poller *io,
                     io_poller_socket fd,
                     enum io_poller_events events,
                     io_poller_cb cb,
                     void *user_data)
{

#if defined(IO_POLLER_USE_SELECT)
    if (fd >= FD_SETSIZE) return false;
#endif
    struct io_poller_element *val;
    int found = chash_contains(io->fd_map.watch, fd, found, FD_MAP);
    if (found) {
        val = chash_lookup(io->fd_map.watch, fd, val, FD_MAP);
    }
    else if (!(val = calloc(1, sizeof *val)))
        return false;

    val->fd = fd;
    val->cb = cb;
    val->events = events;
    val->user_data = user_data;
#if defined(IO_POLLER_USE_SELECT)
    if (events & IO_POLLER_IN)
        FD_SET(fd, &io->select.rset);
    else
        FD_CLR(fd, &io->select.rset);
    if (events & IO_POLLER_OUT)
        FD_SET(fd, &io->select.wset);
    else
        FD_CLR(fd, &io->select.wset);
#elif defined(IO_POLLER_USE_POLL)
    if (!found) {
        if (io->pollfds.cnt == io->pollfds.cap) {
            size_t cap = io->pollfds.cap ? io->pollfds.cap << 1 : 8;
            void *tmp;
            tmp = realloc(io->pollfds.pfds, cap * sizeof *io->pollfds.pfds);
            if (!tmp) {
                free(val);
                return false;
            }
            io->pollfds.pfds = tmp;
            tmp = realloc(io->pollfds.vals, cap * sizeof *io->pollfds.vals);
            if (!tmp) {
                free(val);
                return false;
            }
            io->pollfds.vals = tmp;
            io->pollfds.cap = (int)cap;
        }
        val->poll_position = io->pollfds.cnt++;
        io->pollfds.vals[val->poll_position] = val;
    }
    struct pollfd *pfd = &io->pollfds.pfds[val->poll_position];
    pfd->fd = fd;
    pfd->events = 0;
    if (events & IO_POLLER_IN) pfd->events |= POLLIN;
    if (events & IO_POLLER_OUT) pfd->events |= POLLOUT;

#elif defined(IO_POLLER_USE_EPOLL)
    struct epoll_event event = { .data.ptr = val };
    if (events & IO_POLLER_IN) event.events |= EPOLLIN;
    if (events & IO_POLLER_OUT) event.events |= EPOLLOUT;
    const int ctl = found ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
    if (0 != epoll_ctl(io->epfd, ctl, fd, &event)) goto fail;
#endif
    if (!found) chash_assign(io->fd_map.watch, fd, val, FD_MAP);

    if (found && (val->events & IO_POLLER_UPDATED))
        val->cb(io, IO_POLLER_UPDATED, val->user_data);

    if (!found && val->events & IO_POLLER_ADDED)
        val->cb(io, IO_POLLER_ADDED, val->user_data);

    return true;
fail:
    if (!found) free(val);
    return false;
}

bool
io_poller_socket_del(struct io_poller *io, io_poller_socket fd)
{
    struct io_poller_element *val;
    bool found = chash_contains(io->fd_map.watch, fd, found, FD_MAP);
    if (!found) return false;
    val = chash_lookup(io->fd_map.watch, fd, val, FD_MAP);
#if defined(IO_POLLER_USE_SELECT)
    FD_CLR(fd, &io->select.rset);
    FD_CLR(fd, &io->select.wset);
#elif defined(IO_POLLER_USE_POLL)
    if (--io->pollfds.cnt != val->poll_position) {
        struct io_poller_element *last = io->pollfds.vals[io->pollfds.cnt];
        memcpy(&io->pollfds.pfds[val->poll_position],
               &io->pollfds.pfds[io->pollfds.cnt], sizeof *io->pollfds.pfds);
        io->pollfds.vals[val->poll_position] = last;
        last->poll_position = val->poll_position;
    }
#elif defined(IO_POLLER_USE_EPOLL)
    if (0 != epoll_ctl(io->epfd, EPOLL_CTL_DEL, fd, NULL)) return false;
#endif
    found = chash_contains(io->fd_map.ready, fd, found, FD_MAP);
    if (found) chash_delete(io->fd_map.ready, fd, FD_MAP);
    chash_delete(io->fd_map.watch, fd, FD_MAP);
    if (val->events & IO_POLLER_REMOVED)
        val->cb(io, IO_POLLER_REMOVED, val->user_data);
    free(val);
    return true;
}

static void
io_curl_cb(struct io_poller *io, enum io_poller_events events, void *user_data)
{
    (void)io;
    (void)events;
    ((struct io_curlm *)user_data)->should_perform = true;
}

static int
curl_socket_cb(
    CURL *easy, curl_socket_t fd, int what, void *userp, void *socketp)
{
    (void)easy;
    (void)socketp;
    struct io_curlm *io_curlm = userp;
    enum io_poller_events events = 0;
    switch (what) {
    case CURL_POLL_IN:
        events = IO_POLLER_IN;
        break;
    case CURL_POLL_OUT:
        events = IO_POLLER_OUT;
        break;
    case CURL_POLL_INOUT:
        events = IO_POLLER_IN | IO_POLLER_OUT;
        break;
    case CURL_POLL_REMOVE:
        chash_delete(io_curlm->fds, fd, FD_MAP);
        io_poller_socket_del(io_curlm->io_poller, fd);
        return CURLM_OK;
    }
    bool found = chash_contains(io_curlm->fds, fd, found, FD_MAP);
    if (!found) chash_assign(io_curlm->fds, fd, NULL, FD_MAP);

    io_poller_socket_add(io_curlm->io_poller, fd, events, io_curl_cb,
                         io_curlm);
    return CURLM_OK;
}

static int
curl_timer_cb(CURLM *multi, long timeout_ms, void *userp)
{
    (void)multi;
    struct io_curlm *io_curlm = userp;
    if (timeout_ms == -1) {
        io_curlm->timeout = -1;
    }
    else {
        io_curlm->timeout = cog_timestamp_ms() + timeout_ms;
    }
    return CURLM_OK;
}

void *
io_poller_curlm_get_data(struct io_poller *io, CURLM *multi)
{

    struct io_curlm *io_curlm;
    bool found = chash_contains(io->curlm_map, multi, found, INTPTR_MAP);
    if (!found) return NULL;

    io_curlm =
        chash_lookup(io->curlm_map, (intptr_t)multi, io_curlm, INTPTR_MAP);
    return io_curlm->user_data;
}

bool
io_poller_curlm_add(struct io_poller *io,
                    CURLM *multi,
                    enum io_poller_events events,
                    io_poller_curl_multi_cb cb,
                    void *user_data)
{
    struct io_curlm *io_curlm;
    bool found = chash_contains(io->curlm_map, multi, found, INTPTR_MAP);
    if (!found) {
        if (!(io_curlm = calloc(1, sizeof *io_curlm))) return false;
        io_curlm->multi = multi;
        io_curlm->io_poller = io;
        io_curlm->timeout = -1;
        io_curlm->should_perform = true;
        chash_init(io_curlm->fds, FD_MAP);
        curl_multi_setopt(multi, CURLMOPT_TIMERFUNCTION, curl_timer_cb);
        curl_multi_setopt(multi, CURLMOPT_TIMERDATA, io_curlm);
        curl_multi_setopt(multi, CURLMOPT_SOCKETFUNCTION, curl_socket_cb);
        curl_multi_setopt(multi, CURLMOPT_SOCKETDATA, io_curlm);
        chash_assign(io->curlm_map, (intptr_t)multi, io_curlm, INTPTR_MAP);
    }
    io_curlm->cb = cb;
    io_curlm->events = events;
    io_curlm->user_data = user_data;

    if (!found && (events & IO_POLLER_ADDED))
        cb(io, multi, IO_POLLER_ADDED, user_data);
    if (found && (events & IO_POLLER_UPDATED))
        cb(io, multi, IO_POLLER_UPDATED, user_data);
    return true;
}

bool
io_poller_curlm_del(struct io_poller *io, CURLM *multi)
{
    bool found =
        chash_contains(io->curlm_map, (intptr_t)multi, found, INTPTR_MAP);
    if (!found) return false;
    struct io_curlm *io_curlm =
        chash_lookup(io->curlm_map, (intptr_t)multi, io_curlm, INTPTR_MAP);
    for (int i = 0; i < io_curlm->fds->capacity; i++) {
        if (io_curlm->fds->buckets[i].state != CHASH_FILLED) continue;
        io_poller_socket_del(io, io_curlm->fds->buckets[i].key);
    }
    curl_multi_setopt(multi, CURLMOPT_TIMERFUNCTION, NULL);
    curl_multi_setopt(multi, CURLMOPT_TIMERDATA, NULL);
    curl_multi_setopt(multi, CURLMOPT_SOCKETFUNCTION, NULL);
    curl_multi_setopt(multi, CURLMOPT_SOCKETDATA, NULL);
    chash_free(io_curlm->fds, FD_MAP);
    if (io_curlm->events & IO_POLLER_REMOVED)
        io_curlm->cb(io, multi, IO_POLLER_REMOVED, io_curlm->user_data);
    chash_delete(io->curlm_map, multi, INTPTR_MAP);
    return false;
}

bool
io_poller_curlm_enable_perform(struct io_poller *io, CURLM *multi)
{
    struct io_curlm *io_curlm;
    bool found =
        chash_contains(io->curlm_map, (intptr_t)multi, found, INTPTR_MAP);
    if (!found) return false;
    io_curlm =
        chash_lookup(io->curlm_map, (intptr_t)multi, io_curlm, INTPTR_MAP);
    io_curlm->should_perform = true;

    return true;
}
