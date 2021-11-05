#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#include "scheduler.h"
#include "cee-utils.h"

struct task_s {
  bool keepalive;

  uint64_t timeout_ms;
  uint64_t repeat_ms;
  void *data;
  void (*callback)(void *data);

  pthread_t tid;
  pthread_mutex_t lock;
};

struct task_s *
task_init()
{
  struct task_s *new_task = calloc(1, sizeof *new_task);
  if (pthread_mutex_init(&new_task->lock, NULL))
    ERR("Couldn't initialize mutex");
  return new_task;
}

void
task_cleanup(struct task_s *task)
{
  task_stop(task);
  pthread_mutex_destroy(&task->lock);
  free(task);
}

static bool
is_alive(struct task_s *task)
{
  pthread_mutex_lock(&task->lock);
  bool alive = task->keepalive;
  pthread_mutex_unlock(&task->lock);
  return alive;
}

static void *
event_run(void *p_task)
{
  struct task_s *task = p_task;

  cee_sleep_ms(task->timeout_ms);
  while (is_alive(task)) {
    (*task->callback)(task->data);
    if (!task->repeat_ms) break; /* EARLY BREAK */
    cee_sleep_ms(task->repeat_ms);
  }
  pthread_exit(NULL);
}

void
task_start(struct task_s *task,
           uint64_t timeout_ms,
           uint64_t repeat_ms,
           void *data,
           void (*callback)(void *data))
{
  if (!callback) return;

  if (is_alive(task)) {
    task_stop(task);
  }

  pthread_mutex_lock(&task->lock);

  task->keepalive = true;
  /* add values associated with task */
  task->timeout_ms = timeout_ms;
  task->repeat_ms = repeat_ms;
  task->data = data;
  task->callback = callback;

  if (pthread_create(&task->tid, NULL, &event_run, task))
    ERR("Couldn't create thread");

  pthread_mutex_unlock(&task->lock);
}

void
task_stop(struct task_s *task)
{
  pthread_mutex_lock(&task->lock);
  task->keepalive = false;

  if (task->tid) {
    pthread_cancel(task->tid);
    pthread_join(task->tid, NULL);
  }

  pthread_mutex_unlock(&task->lock);
}
