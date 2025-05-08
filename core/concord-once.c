#include <string.h>
#include <signal.h>
#include <curl/curl.h>
#include <pthread.h>
#include <unistd.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#include "concord-error.h"
#include "concord-once.h"
#define LOGMOD_FALLBACK_APPLICATION_ID "CORE"
#define LOGMOD_FALLBACK_CONTEXT_ID     "ONCE"
#define LOGMOD_STATIC
#include "logmod.h"

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static int shutdown_fds[] = { -1, -1 };
static size_t shutdown_fds_size = sizeof(shutdown_fds) / sizeof *shutdown_fds;

struct ccord_init_cb_node {
    ccord_once_cb callback;
    int flags;
    struct ccord_init_cb_node *next;
};

static struct ccord_init_cb_node *init_cb_list = NULL;

CCORDcode
ccord_once_set_callback(ccord_once_cb callback, long flags)
{
    if (!callback) {
        logmod_log(ERROR, NULL, "Callback function is NULL");
        return CCORD_BAD_PARAMETER;
    }

    struct ccord_init_cb_node *new_node = malloc(sizeof(*new_node));
    if (!new_node) {
        logmod_log(ERROR, NULL, "Memory allocation failed for callback node");
        return CCORD_OUT_OF_MEMORY;
    }

    new_node->callback = callback;
    new_node->flags = flags;
    new_node->next = NULL;

    pthread_mutex_lock(&lock);
    /* Add to the end of the list to maintain registration order */
    if (!init_cb_list) {
        init_cb_list = new_node;
    }
    else {
        struct ccord_init_cb_node *current = init_cb_list;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    pthread_mutex_unlock(&lock);

    return CCORD_OK;
}

void
ccord_shutdown_async(void)
{
    char b = 0;
    write(shutdown_fds[1], &b, sizeof b);
}

int
ccord_shutting_down(void)
{
    struct pollfd pfd = { .fd = shutdown_fds[0], .events = POLLIN };
    if (-1 == shutdown_fds[0]) return 0;
    poll(&pfd, 1, 0);
    return !!(pfd.revents & POLLIN);
}

#ifdef CCORD_SIGINTCATCH
/* shutdown gracefully on SIGINT received */
static void
_ccord_sigint_handler(int signum)
{
    (void)signum;
    static const char err_str[] =
        "\nSIGINT: Disconnecting running concord client(s) ...\n";
    write(STDERR_FILENO, err_str, sizeof(err_str) - 1);
    ccord_shutdown_async();
}
#endif /* CCORD_SIGINTCATCH */

static CCORDcode
_check_curl_compatibility(void)
{
    const curl_version_info_data *curl_info =
        curl_version_info(CURLVERSION_NOW);

    // check version 8.7.1 for websockets support
    if (curl_info->version_num < 0x080701) {
        logmod_log(FATAL, NULL,
                   "libcurl version 8.7.1 or higher required (found %s)",
                   curl_info->version);
        return CCORD_CURL_OUTDATED_VERSION;
    }

    _Bool wss_enabled = 0;
    for (const char *const *proto = curl_info->protocols; *proto; ++proto) {
        if (0 == strncmp(*proto, "wss", 3)) wss_enabled = 1;
    }
    if (!wss_enabled) {
        logmod_log(FATAL, NULL,
                   "libcurl must be compiled with websockets support");
        logmod_log(
            FATAL, NULL,
            "Please recompile libcurl with the --enable-websockets flag");
        return CCORD_CURL_WEBSOCKETS_MISSING;
    }
    return CCORD_OK;
}

static void _ccord_once_cleanup_nolock(void);

CCORDcode
ccord_once(_Bool *const once)
{
    if (!once) {
        logmod_log(ERROR, NULL, "Expected static flag is NULL");
        return CCORD_BAD_PARAMETER;
    }
    if (*once) {
        logmod_log(
            WARN, NULL,
            "ccord_once() with flag %p already initialized, skipping ...",
            (void *)once);
        return CCORD_OK;
    }

    CCORDcode code;
    if ((code = _check_curl_compatibility()) != CCORD_OK) {
        logmod_log(ERROR, NULL,
                   "libcurl compatibility check failed: %s (code %d)",
                   ccord_strerror(code), code);
        return code;
    }

    pthread_mutex_lock(&lock);
#ifdef CCORD_SIGINTCATCH
    signal(SIGINT, &_ccord_sigint_handler);
#endif
    if (0 != pipe(shutdown_fds)) {
        logmod_log(ERROR, NULL, "Failed to create shutdown pipe");
        goto fail_pipe_init;
    }
    for (int i = 0; i < shutdown_fds_size; i++) {
        const int on = 1;

#ifdef FIOCLEX
        if (0 != ioctl(shutdown_fds[i], FIOCLEX, NULL)) {
            logmod_log(ERROR, NULL,
                       "Failed to make shutdown pipe close on execute");
            goto fail_pipe_init;
        }
#endif
/*BSD based systems and glibc use unsigned long for ioctl*/
#if defined __FreeBSD__ || defined __NetBSD__ || defined __DragonFly__        \
    || defined __bsdi__ || defined __APPLE__ || defined __GLIBC__
        if (0 != ioctl(shutdown_fds[i], FIONBIO, &on)) {
#elif OSCLASS == UNIX
        if (0 != ioctl(shutdown_fds[i], (int)FIONBIO, &on)) {
#else
        if (0 != ioctl(shutdown_fds[i], FIONBIO, &on)) {
#endif
            logmod_log(ERROR, NULL,
                       "Failed to make shutdown pipe nonblocking");
            goto fail_pipe_init;
        }
    }

    /* Execute all registered user initialization callbacks */
    struct ccord_init_cb_node *current = init_cb_list;
    while (current) {
        if ((code = current->callback(current->flags)) != CCORD_OK) {
            logmod_log(ERROR, NULL,
                       "User initialization callback failed: %s (code %d)",
                       ccord_strerror(code), code);
            goto fail_pipe_init;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&lock);
    *once = 1;
    return code;

fail_pipe_init:
    _ccord_once_cleanup_nolock();
    pthread_mutex_unlock(&lock);
    return CCORD_GLOBAL_INIT;
}

static void
_ccord_once_cleanup_nolock(void)
{
    struct ccord_init_cb_node *current = init_cb_list;
    while (current) {
        struct ccord_init_cb_node *next = current->next;
        free(current);
        current = next;
    }
    init_cb_list = NULL;
    for (size_t i = 0; i < shutdown_fds_size; ++i) {
        close(shutdown_fds[i]);
        shutdown_fds[i] = -1;
    }
}

void
ccord_once_cleanup(void)
{
    pthread_mutex_lock(&lock);
    _ccord_once_cleanup_nolock();
    pthread_mutex_unlock(&lock);
}

int
ccord_dup_shutdown_fd(void)
{
    int fd = -1;
    if (-1 == shutdown_fds[0]) return -1;
    if (-1 != (fd = dup(shutdown_fds[0]))) {
        const int on = 1;

#ifdef FIOCLEX
        if (0 != ioctl(fd, FIOCLEX, NULL)) {
            close(fd);
            return -1;
        }
#endif

/*BSD based systems and glibc use unsigned long for ioctl*/
#if defined __FReeBSD__ || defined __NetBSD__ || defined __DragonFly__        \
    || defined __bsdi__ || defined __APPLE__ || defined __GLIBC__
        if (0 != ioctl(fd, FIONBIO, &on)) {
#elif OSCLASS == UNIX
        if (0 != ioctl(fd, (int)FIONBIO, &on)) {
#else
        if (0 != ioctl(fd, FIONBIO, &on)) {
#endif
            close(fd);
            return -1;
        }
    }
    return fd;
}
