#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#include "scheduler.h"
#include "orka-utils.h"


struct task_s {
  bool keepalive;

  uint64_t timeout_ms;
  uint64_t repeat_ms;
  void *data;
  void (*callback)(void *data);  

  pthread_t tid;
  pthread_mutex_t lock;
};

struct task_s*
task_init()
{
  struct task_s *new_task = malloc(sizeof *new_task);
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
keepalive(struct task_s *task)
{
  pthread_mutex_lock(&task->lock);
  bool status = task->keepalive;
  pthread_mutex_unlock(&task->lock);
  return status;
}

static void*
event_run(void *p_task)
{
  struct task_s *task = p_task;

  orka_sleep_ms(task->timeout_ms);
  while (keepalive(task)) {
    (*task->callback)(task->data);
    if (!task->repeat_ms) break; /* EARLY BREAK */
    orka_sleep_ms(task->repeat_ms);
  }
  pthread_exit(NULL);
}

static void noop_task(void *a){return;}

void
task_start(
  struct task_s *task,
  uint64_t timeout_ms, 
  uint64_t repeat_ms, 
  void *data,
  void (*callback)(void *data))
{
  task->keepalive = true;
  
  // add values associated with task
  task->timeout_ms = timeout_ms;
  task->repeat_ms = repeat_ms;
  task->data = data;
  if (callback)
    task->callback = callback;
  else
    task->callback = &noop_task;

  if (pthread_create(&task->tid, NULL, &event_run, task))
    ERR("Couldn't create thread");
}

void
task_stop(struct task_s *task)
{
  pthread_mutex_lock(&task->lock);
  task->keepalive = false;
  pthread_mutex_unlock(&task->lock);

  pthread_cancel(task->tid);
  pthread_join(task->tid, NULL);
}
