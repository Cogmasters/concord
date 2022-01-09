#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <poll.h>

#include "io_poller.h"
#include "cog-utils.h"

struct io_curlm {
  CURLM *multi;
  struct io_poller *io_poller;
  int *fds;
  int fds_cnt;
  int fds_cap;
  io_poller_curl_cb cb;
  int64_t timeout;
  void *user_data;
  int running;
  bool should_perform;
};

struct io_poller_element {
  void *user_data;
  io_poller_cb cb;
};

struct io_poller {
  struct io_poller_element *elements;
  struct pollfd *pollfds;
  int cap;
  int cnt;

  struct io_curlm **curlm;
  int curlm_cap;
  int curlm_cnt;
};

struct io_poller *
io_poller_create(void)
{
  struct io_poller *io = calloc(1, sizeof *io);
  io->cap = 0x2000;
  io->elements = calloc(io->cap, sizeof *io->elements);
  io->pollfds = calloc(io->cap, sizeof *io->pollfds);
  return io;
}

void
io_poller_destroy(struct io_poller *io)
{
  for (int i=0; i<io->curlm_cnt; i++) {
    free(io->curlm[i]->fds);
    free(io->curlm[i]);
  }
  free(io->curlm);
  free(io->elements);
  free(io->pollfds);
  free(io);
}


int
io_poller_poll(struct io_poller *io, int milliseconds)
{
  const int64_t now = cog_timestamp_ms();
  const int64_t millis = now + (milliseconds == -1 ? 0 : milliseconds);
  for (int i=0; i<io->curlm_cnt; i++) {
    struct io_curlm *io_curlm = io->curlm[i];
    if (io_curlm->should_perform) {
      milliseconds = 0;
      break;
    }
    if (io_curlm->timeout != -1)
      if (milliseconds == -1 || io_curlm->timeout < millis)
        milliseconds = io_curlm->timeout < now ? 0 : io_curlm->timeout - now;
  }
  return poll(io->pollfds, io->cnt, milliseconds);
}


void
io_poller_perform(struct io_poller *io)
{
  const int64_t now = cog_timestamp_ms();
  for (int i=0; i<io->cnt; i++) {
    int events;
    if ((events = io->pollfds[i].revents)) {
      struct io_poller_element *element = &io->elements[i];
      element->cb(element->user_data, events);
    }
  }
  for (int i=0; i<io->curlm_cnt; i++) {
    if (io->curlm[i]->should_perform || now >= io->curlm[i]->timeout) {
      io->curlm[i]->should_perform = false;
      if (io->curlm[i]->cb) {
        io->curlm[i]->cb(io->curlm[i]->multi, io->curlm[i]->user_data);
      } else {
        curl_multi_socket_all(io->curlm[i]->multi, &io->curlm[i]->running);
      }
    }
  }
}

bool
io_poller_fd_add(struct io_poller *io, int fd, int events, io_poller_cb cb, void *user_data)
{
  int index = 0;
  for (; index<io->cnt; index++)
    if (fd == io->pollfds[index].fd)
      goto modify;

  if (io->cnt == io->cap) {
    size_t cap = io->cap << 1;
    void *tmp;

    tmp = realloc(io->pollfds, cap * sizeof *io->pollfds);
    if (!tmp)
      return false;
    io->pollfds = tmp;

    tmp = realloc(io->elements, cap * sizeof *io->elements);
    if (!tmp)
      return false;
    io->elements = tmp;

    memset(&io->elements[io->cap], 0, (cap - io->cap) * sizeof *io->elements);
    memset(&io->pollfds[io->cap], 0, (cap - io->cap) * sizeof *io->pollfds);
    io->cap = cap;
  }

  io->cnt++;

  modify:
  io->pollfds[index].fd = fd;
  io->pollfds[index].events = events;
  io->pollfds[index].revents = 0;
  io->elements[index].cb = cb;
  io->elements[index].user_data = user_data;
  return true;
}

bool
io_poller_fd_del(struct io_poller *io, int fd)
{
  int index = 0;
  for (; index<io->cnt; index++)
    if (fd == io->pollfds[index].fd)
      goto modify;
  return false;

  modify:
  if (index < --io->cnt) {
    memcpy(&io->pollfds[index], &io->pollfds[io->cnt], sizeof *io->pollfds);
    memcpy(&io->elements[index], &io->elements[io->cnt], sizeof *io->elements);
  }
  memset(&io->pollfds[io->cnt], 0, sizeof *io->pollfds);
  memset(&io->elements[io->cnt], 0, sizeof *io->elements);
  return true;
}



static void
io_curl_cb(void *user_data, int events)
{
  (void) events;
  struct io_curlm *io_curlm = user_data;
  io_curlm->should_perform = true;
}

static int
curl_socket_cb(CURL *easy,
               curl_socket_t fd,
               int what,
               void *userp,
               void *socketp)
{
  (void) easy;
  (void) socketp;
  struct io_curlm *io_curlm = userp;
  int index = -1;
  for (int i=0; i<io_curlm->fds_cnt; i++) {
    if (io_curlm->fds[i] == fd) {
      index = i;
      break;
    }
  }
  
  int events = 0;
  switch (what) {
  case CURL_POLL_IN:
    events = POLLIN;
    break;
  case CURL_POLL_OUT:
    events = POLLOUT;
    break;
  case CURL_POLL_INOUT:
    events = POLLIN | POLLOUT;
    break;
  case CURL_POLL_REMOVE:
    io_poller_fd_del(io_curlm->io_poller, fd);
    if (index != -1)
      memmove(&io_curlm->fds[index], &io_curlm->fds[index + 1], (--io_curlm->fds_cnt - index) * sizeof *io_curlm->fds);
    return 0;
  }
  if (index == -1) {
    if (io_curlm->fds_cnt == io_curlm->fds_cap) {
      int cap = io_curlm->fds_cap << 1;
      if (!cap) cap = 8;
      void *tmp = realloc(io_curlm->fds, cap * sizeof *io_curlm->fds);
      if (tmp) {
        io_curlm->fds = tmp;
        io_curlm->fds_cap = cap;
      } else return CURLM_OUT_OF_MEMORY;
    }
    io_curlm->fds[io_curlm->fds_cnt++] = fd;
  }
  io_poller_fd_add(io_curlm->io_poller, fd, events, io_curl_cb, io_curlm);
  return CURLM_OK;
}

static int
curl_timer_cb(CURLM *multi, long timeout_ms, void *userp)
{
  (void) multi;
  struct io_curlm *io_curlm = userp;
  if (timeout_ms == -1) {
    io_curlm->timeout = -1;
  } else {
    io_curlm->timeout = cog_timestamp_ms() + timeout_ms;
  }
  return CURLM_OK;
}

bool
io_poller_curlm_add(struct io_poller *io, CURLM *multi, io_poller_curl_cb cb, void *user_data)
{
  struct io_curlm *io_curlm = calloc(1, sizeof *io_curlm);
  io_curlm->io_poller = io;
  io_curlm->cb = cb;
  io_curlm->multi = multi;
  io_curlm->user_data = user_data;
  io_curlm->timeout = -1;
  io_curlm->should_perform = true;

  if (io->curlm_cnt == io->curlm_cap) {
    size_t cap = io->curlm_cap << 1;
    if (!cap) cap = 8;
    void *tmp = realloc(io->curlm, cap * sizeof *io->curlm);
    if (!tmp) 
      return free(io_curlm), false;
    io->curlm = tmp;
    io->curlm_cap = cap;
  }
  io->curlm[io->curlm_cnt++] = io_curlm;
  curl_multi_setopt(multi, CURLMOPT_TIMERFUNCTION, curl_timer_cb);
  curl_multi_setopt(multi, CURLMOPT_TIMERDATA, io_curlm);
  curl_multi_setopt(multi, CURLMOPT_SOCKETFUNCTION, curl_socket_cb);
  curl_multi_setopt(multi, CURLMOPT_SOCKETDATA, io_curlm);
  return true;
}

bool
io_poller_curlm_del(struct io_poller *io, CURLM *multi)
{
  for (int i=0; i<io->curlm_cnt; i++) {
    if (io->curlm[i]->multi == multi) {
      int *fds = io->curlm[i]->fds;
      int fds_cnt = io->curlm[i]->fds_cnt;
      for (int i=0; i<fds_cnt; i++)
        io_poller_fd_del(io, fds[i]);
      free(fds);
      curl_multi_setopt(multi, CURLMOPT_TIMERFUNCTION, NULL);
      curl_multi_setopt(multi, CURLMOPT_TIMERDATA, NULL);
      curl_multi_setopt(multi, CURLMOPT_SOCKETFUNCTION, NULL);
      curl_multi_setopt(multi, CURLMOPT_SOCKETDATA, NULL);
      free(io->curlm[i]);
      memmove(&io->curlm[i], &io->curlm[i + 1], (--io->curlm_cnt - i) * sizeof *io->curlm);
      return true;
    }
  }
  return false;
}
