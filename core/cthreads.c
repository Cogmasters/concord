/*
  Licensed under PerformanC's Custom license.
  Available at licenses/LICENSE.performanc

  https://github.com/PerformanC/CThreads
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cthreads.h"

#ifdef _WIN32
#include <windows.h>
DWORD WINAPI __cthreads_winthreads_function_wrapper(void *data) {
  struct cthreads_args *args = data;
  args->func(args->data);

  return TRUE;
}
#else
#include <pthread.h>
#endif

int cthreads_thread_create(struct cthreads_thread *thread, struct cthreads_thread_attr *attr, void *(*func)(void *data), void *data, struct cthreads_args *args) {
  #ifdef _WIN32
    #ifdef CTHREADS_DEBUG
      printf("cthreads_thread_create\n");
    #endif

    args->func = func;
    args->data = data;

    if (attr) thread->wThread = CreateThread(NULL, attr->stacksize ? attr->stacksize : 0,
                                             __cthreads_winthreads_function_wrapper, args, 
                                             attr->dwCreationFlags ? (DWORD)attr->dwCreationFlags : 0, NULL);
    else thread->wThread = CreateThread(NULL, 0, __cthreads_winthreads_function_wrapper, args, 0, NULL);

    return thread->wThread == NULL;
  #else
    pthread_attr_t pAttr;

    (void) args;

    #ifdef CTHREADS_DEBUG
      printf("cthreads_thread_create\n");
    #endif

    if (attr) {
      if (pthread_attr_init(&pAttr)) return 1;
      if (attr->detachstate) pthread_attr_setdetachstate(&pAttr, attr->detachstate);
      if (attr->guardsize) pthread_attr_setguardsize(&pAttr, attr->guardsize);
      #ifdef CTHREADS_THREAD_INHERITSCHED
        if (attr->inheritsched) pthread_attr_setinheritsched(&pAttr, attr->inheritsched);
      #endif
      if (attr->schedpolicy) pthread_attr_setschedpolicy(&pAttr, attr->schedpolicy);
      if (attr->scope) pthread_attr_setscope(&pAttr, attr->scope);
      #ifdef CTHREADS_THREAD_STACK
        if (attr->stack) pthread_attr_setstack(&pAttr, attr->stackaddr, attr->stack);
      #endif
      if (attr->stacksize) pthread_attr_setstacksize(&pAttr, attr->stacksize);
    }

    return pthread_create(&thread->pThread, attr ? &pAttr : NULL, func, data);
  #endif
}

int cthreads_thread_detach(struct cthreads_thread thread) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_thread_detach\n");
  #endif

  #ifdef _WIN32
    return CloseHandle(thread.wThread);
  #else
    return pthread_detach(thread.pThread);
  #endif
}

int cthreads_thread_join(struct cthreads_thread thread, void *code) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_thread_join\n");
  #endif

  #ifdef _WIN32
    if (WaitForSingleObject(thread.wThread, INFINITE) == WAIT_FAILED) return 0;

    return GetExitCodeThread(thread.wThread, (LPDWORD)&code) == 0;
  #else
    return pthread_join(thread.pThread, code ? &code : NULL);
  #endif
}

int cthreads_thread_equal(struct cthreads_thread thread1, struct cthreads_thread thread2) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_thread_equal\n");
  #endif

  #ifdef _WIN32
    return thread1.wThread == thread2.wThread;
  #else
    return pthread_equal(thread1.pThread, thread2.pThread);
  #endif
}

struct cthreads_thread cthreads_thread_self(void) {
  struct cthreads_thread t;

  #ifdef CTHREADS_DEBUG
    printf("cthreads_thread_self\n");
  #endif

  #ifdef _WIN32
    t.wThread = GetCurrentThread();
  #else
    t.pThread = pthread_self();
  #endif

  return t;
}

unsigned long cthreads_thread_id(struct cthreads_thread thread) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_thread_id\n");
  #endif

  #ifdef _WIN32
    return GetThreadId(thread.wThread);
  #else
    return (unsigned long)thread.pThread;
  #endif
}

void cthreads_thread_exit(void *code) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_thread_exit\n");
  #endif

  #ifdef _WIN32
    #if defined  __WATCOMC__ || _MSC_VER || __DMC__
      ExitThread((DWORD)code);
    #else
      ExitThread((DWORD)(uintptr_t)code);
    #endif
  #else
    pthread_exit(code);
  #endif
}

#ifdef CTHREADS_MUTEX_ATTR
  int cthreads_mutex_init(struct cthreads_mutex *mutex, struct cthreads_mutex_attr *attr) {
#else
  int cthreads_mutex_init(struct cthreads_mutex *mutex, void *attr) {
#endif
  #ifdef _WIN32
    #ifdef CTHREADS_DEBUG
      printf("cthreads_mutex_init\n");
    #endif

    (void) attr;

    InitializeCriticalSection(&mutex->wMutex);

    return 0;
  #else
    pthread_mutexattr_t pAttr;

    #ifdef CTHREADS_DEBUG
      printf("cthreads_mutex_init\n");
    #endif
  
    /* CTHREADS_MUTEX_ATTR is always available on non-Windows platforms */
    if (attr) {
      if (pthread_mutexattr_init(&pAttr)) return 1;
      if (attr->pshared) pthread_mutexattr_setpshared(&pAttr, attr->pshared);
      #ifdef CTHREADS_MUTEX_TYPE
        if (attr->type) pthread_mutexattr_settype(&pAttr, attr->type);
      #endif
      #ifdef CTHREADS_MUTEX_ROBUST
        if (attr->robust) pthread_mutexattr_setrobust(&pAttr, attr->robust);
      #endif
      #ifdef CTHREADS_MUTEX_PROTOCOL
        if (attr->protocol) pthread_mutexattr_setprotocol(&pAttr, attr->protocol);
      #endif
      #ifdef CTHREADS_MUTEX_PRIOCEILING
        if (attr->prioceiling) pthread_mutexattr_setprioceiling(&pAttr, attr->prioceiling);
      #endif
    }

    return pthread_mutex_init(&mutex->pMutex, attr ? &pAttr : NULL);
  #endif
}

int cthreads_mutex_lock(struct cthreads_mutex *mutex) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_mutex_lock\n");
  #endif

  #ifdef _WIN32
    EnterCriticalSection(&mutex->wMutex);

    return 0;
  #else
    return pthread_mutex_lock(&mutex->pMutex);
  #endif
}

int cthreads_mutex_trylock(struct cthreads_mutex *mutex) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_mutex_trylock\n");
  #endif

  #ifdef _WIN32
    TryEnterCriticalSection(&mutex->wMutex);

    return 0;
  #else
    return pthread_mutex_trylock(&mutex->pMutex);
  #endif
}

int cthreads_mutex_unlock(struct cthreads_mutex *mutex) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_mutex_unlock\n");
  #endif

  #ifdef _WIN32
    LeaveCriticalSection(&mutex->wMutex);

    return 0;
  #else
    return pthread_mutex_unlock(&mutex->pMutex);
  #endif
}

int cthreads_mutex_destroy(struct cthreads_mutex *mutex) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_mutex_destroy\n");
  #endif

  #ifdef _WIN32
    DeleteCriticalSection(&mutex->wMutex);

    return 0;
  #else
    return pthread_mutex_destroy(&mutex->pMutex);
  #endif
}

#ifdef CTHREADS_COND_ATTR
  int cthreads_cond_init(struct cthreads_cond *cond, struct cthreads_cond_attr *attr) {
#else
  int cthreads_cond_init(struct cthreads_cond *cond, void *attr) {
#endif
  #ifdef CTHREADS_DEBUG
    printf("cthreads_cond_init\n");
  #endif

  #ifdef _WIN32
    (void) attr;

    InitializeConditionVariable(&cond->wCond);

    return 0;
  #else
    pthread_condattr_t pAttr;

    /* CTHREADS_COND_ATTR is always available on non-Windows platforms */
    if (attr) {
      if (pthread_condattr_init(&pAttr) != 0) return 1;
      if (attr->pshared) pthread_condattr_setpshared(&pAttr, attr->pshared);
      #ifdef CTHREADS_COND_CLOCK
        if (attr->clock) pthread_condattr_setclock(&pAttr, attr->clock);
      #endif
    }

    return pthread_cond_init(&cond->pCond, attr ? &pAttr : NULL);
  #endif
}

int cthreads_cond_signal(struct cthreads_cond *cond) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_cond_signal\n");
  #endif

  #ifdef _WIN32
    WakeConditionVariable(&cond->wCond);

    return 0;
  #else
    return pthread_cond_signal(&cond->pCond);
  #endif
}

int cthreads_cond_broadcast(struct cthreads_cond *cond) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_cond_broadcast\n");
  #endif

  #ifdef _WIN32
    WakeAllConditionVariable(&cond->wCond);

    return 0;
  #else
    return pthread_cond_broadcast(&cond->pCond);
  #endif
}

int cthreads_cond_destroy(struct cthreads_cond *cond) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_cond_destroy\n");
  #endif

  #ifdef _WIN32
    return 0;
  #else
    return pthread_cond_destroy(&cond->pCond);
  #endif
}

int cthreads_cond_wait(struct cthreads_cond *cond, struct cthreads_mutex *mutex) {
  #ifdef CTHREADS_DEBUG
    printf("cthreads_cond_wait\n");
  #endif

  #ifdef _WIN32
    return SleepConditionVariableCS(&cond->wCond, &mutex->wMutex, INFINITE) == 0;
  #else
    return pthread_cond_wait(&cond->pCond, &mutex->pMutex);
  #endif
}

#ifdef CTHREADS_RWLOCK
  int cthreads_rwlock_init(struct cthreads_rwlock *rwlock) {
    #ifdef CTHREADS_DEBUG
      printf("cthreads_rwlock_init\n");
    #endif

    #ifdef _WIN32
      rwlock->wRWLock = malloc(sizeof(SRWLOCK));
      if (!rwlock->wRWLock) return 1;

      InitializeSRWLock(rwlock->wRWLock);

      return 0;
    #else
      return pthread_rwlock_init(&rwlock->pRWLock, NULL);
    #endif
  }

  int cthreads_rwlock_rdlock(struct cthreads_rwlock *rwlock) {
    #ifdef CTHREADS_DEBUG
      printf("cthreads_rwlock_rdlock\n");
    #endif

    #ifdef _WIN32
      AcquireSRWLockShared(rwlock->wRWLock);
      rwlock->type = 1;

      return 0;
    #else
      return pthread_rwlock_rdlock(&rwlock->pRWLock);
    #endif
  }

  int cthreads_rwlock_unlock(struct cthreads_rwlock *rwlock) {
    #ifdef CTHREADS_DEBUG
      printf("cthreads_rwlock_unlock\n");
    #endif

    #ifdef _WIN32
      switch (rwlock->type) {
        case 1: {
          ReleaseSRWLockShared(rwlock->wRWLock);

          break;
        }
        case 2: {
          ReleaseSRWLockExclusive(rwlock->wRWLock);

          break;
        }
      }

      rwlock->type = 0;

      return 0;
    #else
      return pthread_rwlock_unlock(&rwlock->pRWLock);
    #endif
  }

  int cthreads_rwlock_wrlock(struct cthreads_rwlock *rwlock) {
    #ifdef CTHREADS_DEBUG
      printf("cthreads_rwlock_wrlock\n");
    #endif

    #ifdef _WIN32
      AcquireSRWLockExclusive(rwlock->wRWLock);
      rwlock->type = 2;

      return 0;
    #else
      return pthread_rwlock_wrlock(&rwlock->pRWLock);
    #endif
  }

  int cthreads_rwlock_destroy(struct cthreads_rwlock *rwlock) {
    #ifdef CTHREADS_DEBUG
      printf("cthreads_rwlock_destroy\n");
    #endif

    #ifdef _WIN32
      free(rwlock->wRWLock);
      rwlock->wRWLock = NULL;
      rwlock->type = 0;

      return 0;
    #else
      return pthread_rwlock_destroy(&rwlock->pRWLock);
    #endif
  }
#endif
