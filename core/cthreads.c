#include <stdio.h>
#include <stdlib.h>

#include "cthreads.h"

#if _WIN32
#include <windows.h>
DWORD WINAPI __cthreads_win_thread_create_wrapper(void *data) {
    struct cthreads_args *args = data;
    args->func(args->data);

    return TRUE;
}
#else
#include <pthread.h>
#endif

int cthreads_thread_create(struct cthreads_thread *thread, struct cthreads_thread_attr *attr, void *(*func)(void *data), void *data, struct cthreads_args *args) {
    #ifdef _WIN32
        args->func = func;
        args->data = data;

        if (attr) thread->wThread = CreateThread(NULL, attr->stacksize ? attr->stacksize : 0,
                                                 __cthreads_win_thread_create_wrapper, args, 
                                                 attr->dwCreationFlags ? (DWORD)attr->dwCreationFlags : 0, NULL);
        else thread->wThread = CreateThread(NULL, 0, __cthreads_win_thread_create_wrapper, args, 0, NULL);

        return thread->wThread ? 0 : 1;
    #else
        pthread_attr_t pAttr;

        if (attr) {
            if (pthread_attr_init(&pAttr)) return 1;
            if (attr->detachstate) pthread_attr_setdetachstate(&pAttr, attr->detachstate);
            if (attr->guardsize) pthread_attr_setguardsize(&pAttr, attr->guardsize);
            #if !defined __ANDROID__
                if (attr->inheritsched) pthread_attr_setinheritsched(&pAttr, attr->inheritsched);
            #endif
            if (attr->schedpolicy) pthread_attr_setschedpolicy(&pAttr, attr->schedpolicy);
            if (attr->scope) pthread_attr_setscope(&pAttr, attr->scope);
            if (attr->stack) pthread_attr_setstack(&pAttr, attr->stackaddr, attr->stack);
            if (attr->stacksize) pthread_attr_setstacksize(&pAttr, attr->stacksize);
        }

        return pthread_create(&thread->pThread, attr ? &pAttr : NULL, func, data);
    #endif
}

int cthreads_thread_detach(struct cthreads_thread *thread) {
    #ifdef _WIN32
        return CloseHandle(thread->wThread);
    #else
        return pthread_detach(thread->pThread);
    #endif
}

void cthreads_thread_close(void *code) {
    #ifdef _WIN32
        #ifdef __WATCOMC__
            ExitThread((DWORD)code);
        #else
            ExitThread((DWORD)(uintptr_t)code);
        #endif
    #else
        pthread_exit(code);
    #endif
}

int cthreads_mutex_init(struct cthreads_mutex *mutex, struct cthreads_mutex_attr *attr) {
    #ifdef _WIN32
        return (attr ? mutex->wMutex = CreateMutex(NULL, attr->bInitialOwner ? TRUE : FALSE, 
                                           attr->lpName ? (LPCSTR)attr->lpName : NULL);
        : CreateMutex(NULL, FALSE, NULL)) ? 0 : 1;
    #else
        pthread_mutexattr_t pAttr;
        if (attr) {
            if (pthread_mutexattr_init(&pAttr)) return 1;
            if (attr->pshared) pthread_mutexattr_setpshared(&pAttr, attr->pshared);
            if (attr->type) pthread_mutexattr_settype(&pAttr, attr->type);
            #if (defined __linux__ || defined __FreeBSD__) && !defined __ANDROID__
                if (attr->robust) pthread_mutexattr_setrobust(&pAttr, attr->robust);
            #endif
            #if !defined __ANDROID__
                if (attr->protocol) pthread_mutexattr_setprotocol(&pAttr, attr->protocol);
                if (attr->prioceiling) pthread_mutexattr_setprioceiling(&pAttr, attr->prioceiling);
            #endif
        }

        return pthread_mutex_init(&mutex->pMutex, attr ? &pAttr : NULL);
    #endif
}

int cthreads_mutex_lock(struct cthreads_mutex *mutex) {
    #ifdef _WIN32
        return WaitForSingleObject(mutex->wMutex, INFINITE) == WAIT_OBJECT_0 ? 0 : 1; // Needs to re-see
    #else
        return pthread_mutex_lock(&mutex->pMutex);
    #endif
}

int cthreads_mutex_trylock(struct cthreads_mutex *mutex) {
    #ifdef _WIN32
        return WaitForSingleObject(mutex->wMutex, 0) == WAIT_OBJECT_0 ? 0 : 1; // Needs to re-see
    #else
        return pthread_mutex_trylock(&mutex->pMutex);
    #endif
}

int cthreads_mutex_unlock(struct cthreads_mutex *mutex) {
    #ifdef _WIN32
        return ReleaseMutex(mutex->wMutex) == 0 ? 1 : 0; // Needs to re-see
    #else
        return pthread_mutex_unlock(&mutex->pMutex);
    #endif
}

int cthreads_mutex_destroy(struct cthreads_mutex *mutex) {
    #ifdef _WIN32
        return CloseHandle(mutex->wMutex) == 0 ? 1 : 0; // Needs to re-see
    #else
        return pthread_mutex_destroy(&mutex->pMutex);
    #endif
}

int cthreads_cond_init(struct cthreads_cond *cond, struct cthreads_cond_attr *attr) {
    #ifdef _WIN32
        if (attr) cond->wCond = CreateEvent(NULL, attr->bManualReset ? TRUE : FALSE, 
                                            attr->bInitialState ? TRUE : FALSE,
                                            attr->lpName ? (LPTSTR)attr->lpName : NULL);
        else cond->wCond = CreateEvent(NULL, FALSE, FALSE, NULL);

        if (cond->wCond == NULL) return 1;
        return 0;
    #else
        pthread_condattr_t pAttr;
        if (attr) {
            if (pthread_condattr_init(&pAttr) != 0) return 1;
            if (attr->pshared) pthread_condattr_setpshared(&pAttr, attr->pshared);
            if (attr->clock) pthread_condattr_setclock(&pAttr, attr->clock);
        }

        return pthread_cond_init(&cond->pCond, attr ? &pAttr : NULL);
    #endif
}

int cthreads_cond_signal(struct cthreads_cond *cond) {
    #ifdef _WIN32
        return SetEvent(cond->wCond) == 0 ? 1 : 0; // Needs to re-see
    #else
        return pthread_cond_signal(&cond->pCond);
    #endif
}

int cthreads_cond_broadcast(struct cthreads_cond *cond) {
    #ifdef _WIN32
        return SetEvent(cond->wCond) == 0 ? 1 : 0; // Needs to re-see
    #else
        return pthread_cond_broadcast(&cond->pCond);
    #endif
}

int cthreads_cond_destroy(struct cthreads_cond *cond) {
    #ifdef _WIN32
        return CloseHandle(cond->wCond) == 0 ? 1 : 0; // Needs to re-see
    #else
        return pthread_cond_destroy(&cond->pCond);
    #endif
}

int cthreads_cond_wait(struct cthreads_cond *cond, struct cthreads_mutex *mutex) {
    #ifdef _WIN32
        return SleepConditionVariableCS(&cond->wCond, &mutex->wMutex, INFINITE) == 0 ? 1 : 0;
    #else
        return pthread_cond_wait(&cond->pCond, &mutex->pMutex);
    #endif
}

int cthreads_join(struct cthreads_thread *thread, void *code) {
    #ifdef _WIN32
        if (WaitForSingleObject(thread->wThread, INFINITE) == WAIT_FAILED) return 1;

        return GetExitCodeThread(thread->wThread, (LPDWORD)&code) == 0 ? 1 : 0;
    #else
        return pthread_join(thread->pThread, code ? &code : NULL);
    #endif
}

int cthreads_rwlock_init(struct cthreads_rwlock *rwlock) {
    #ifdef _WIN32
        return (rwlock->wRWLock = CreateMutex(NULL, FALSE, NULL)) == NULL ? 1 : 0; // Needs to re-see
    #else
        return pthread_rwlock_init(&rwlock->pRWLock, NULL);
    #endif
}

int cthreads_rwlock_rdlock(struct cthreads_rwlock *rwlock) {
    #ifdef _WIN32
        return WaitForSingleObject(rwlock->wRWLock, INFINITE) == WAIT_FAILED ? 1 : 0; // Needs to re-see
    #else
        return pthread_rwlock_rdlock(&rwlock->pRWLock);
    #endif
}

int cthreads_rwlock_unlock(struct cthreads_rwlock *rwlock) {
    #ifdef _WIN32
        return ReleaseMutex(rwlock->wRWLock) == 0 ? 1 : 0; // Needs to re-see
    #else
        return pthread_rwlock_unlock(&rwlock->pRWLock);
    #endif
}

int cthreads_rwlock_wrlock(struct cthreads_rwlock *rwlock) {
    #ifdef _WIN32
        return WaitForSingleObject(rwlock->wRWLock, INFINITE) == WAIT_FAILED ? 1 : 0; // Needs to re-see
    #else
        return pthread_rwlock_wrlock(&rwlock->pRWLock);
    #endif
}

int cthreads_rwlock_destroy(struct cthreads_rwlock *rwlock) {
    #ifdef _WIN32
        return CloseHandle(rwlock->wRWLock) == 0 ? 1 : 0; // Needs to re-see
    #else
        return pthread_rwlock_destroy(&rwlock->pRWLock);
    #endif
}

int cthreads_equal(struct cthreads_thread thread1, struct cthreads_thread thread2) {
    #ifdef _WIN32
        return GetThreadId(thread1.wThread) == GetThreadId(thread2.wThread);
    #else
        return pthread_equal(thread1.pThread, thread2.pThread);
    #endif
}

struct cthreads_thread cthreads_self() {
    struct cthreads_thread t;

    #ifdef _WIN32
        t.wThread = GetCurrentThread();
    #else
        t.pThread = pthread_self();
    #endif

    return t;
}
