#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct task_s *task_init();
void task_cleanup(struct task_s *task);

void task_start(struct task_s *task,
                uint64_t timeout_ms,
                uint64_t repeat_ms,
                void *data,
                void (*callback)(void *data));

void task_stop(struct task_s *task);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SCHEDULER_H */
