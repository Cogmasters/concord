#ifndef CONCORD_IO_POLLER_H
#define CONCORD_IO_POLLER_H

#include <stdbool.h>
#include <curl/curl.h>

struct io_poller;
typedef void (*io_poller_cb)(void *user_data, int events);

struct io_poller *io_poller_create(void);
void io_poller_destroy(struct io_poller *io);
void io_poller_poll(struct io_poller *io, int milliseconds);
void io_poller_perform(struct io_poller *io);

bool io_poller_fd_add(struct io_poller *io, int fd, int events, io_poller_cb cb, void *user_data);
bool io_poller_fd_del(struct io_poller *io, int fd);

typedef void (*io_poller_curl_cb)(CURLM *multi, void *user_data);
bool io_poller_curlm_add(struct io_poller *io, CURLM *multi, io_poller_curl_cb cb, void *user_data);
bool io_poller_curlm_del(struct io_poller *io, CURLM *multi);

#endif//CONCORD_IO_POLLER_H 