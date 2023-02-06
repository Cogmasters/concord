#include <stdint.h>
#include <stdio.h>

#include "cthreads.h"
#include "greatest.h"

void *thread_func(void *data) {
  PASS();

  return NULL;
}

TEST create_thread() {
  struct cthreads_thread thread;
  struct cthreads_args args;
  int ret;

  ret = cthreads_thread_create(&thread, NULL, thread_func, NULL, &args);
  ASSERT_EQ(0, ret);

  ret = cthreads_join(&thread, 0);
  ASSERT_EQ(0, ret);

  PASS();
}

TEST mutexes() {
  struct cthreads_mutex mutex;
  int ret;

  ret = cthreads_mutex_init(&mutex, NULL);
  ASSERT_EQ(0, ret);

  ret = cthreads_mutex_lock(&mutex);
  ASSERT_EQ(0, ret);

  ret = cthreads_mutex_unlock(&mutex);
  ASSERT_EQ(0, ret);

  ret = cthreads_mutex_destroy(&mutex);
  ASSERT_EQ(0, ret);

  PASS();
}

TEST locks() {
  struct cthreads_rwlock rwlock;
  int ret;

  ret = cthreads_rwlock_init(&rwlock);
  ASSERT_EQ(0, ret);

  ret = cthreads_rwlock_rdlock(&rwlock);
  ASSERT_EQ(0, ret);

  ret = cthreads_rwlock_unlock(&rwlock);
  ASSERT_EQ(0, ret);

  ret = cthreads_rwlock_wrlock(&rwlock);
  ASSERT_EQ(0, ret);

  ret = cthreads_rwlock_destroy(&rwlock);
  ASSERT_EQ(0, ret);

  PASS();
}

TEST equal() {
  struct cthreads_thread thread1;
  struct cthreads_thread thread2;
  int ret;

  thread1 = cthreads_self();
  thread2 = cthreads_self();

  ret = cthreads_equal(thread1, thread2);
  ASSERT_EQ(1, ret);

  PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_TEST(create_thread);
  RUN_TEST(mutexes);
  RUN_TEST(locks);
  RUN_TEST(equal);

  GREATEST_MAIN_END();

  return 0;
}