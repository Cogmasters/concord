#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <stdlib.h>

#include "concord-error.h"
#include "concord-notifier.h"
#define LOGMOD_FALLBACK_APPLICATION_ID "CORE"
#define LOGMOD_FALLBACK_CONTEXT_ID     "NOTIFIER"
#define LOGMOD_STATIC
#include "logmod.h"

void
ccord_notifier_notify(int notifier_pipe[2])
{
    char b = 0;
    write(notifier_pipe[1], &b, sizeof b);
}

_Bool
ccord_notifier_is_notifying(int notifier_pipe[2])
{
    struct pollfd pfd = { .fd = notifier_pipe[0], .events = POLLIN };
    if (notifier_pipe[0] == -1) {
        return 0;
    }
    if (poll(&pfd, 1, 0) == -1) {
        logmod_log(ERROR, NULL, "Failed to poll notifier pipe");
        return 0;
    }
    return !!(pfd.revents & POLLIN);
}

/* pipes don't reliably support the FIONBIO/FIOCLEX ioctls everywhere
 * (macOS rejects them), so use the portable fcntl flags instead */
static int
_ccord_notifier_setup_fd(int fd)
{
    int flags;
    if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1) return -1;
    if ((flags = fcntl(fd, F_GETFL)) == -1
        || fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        return -1;
    }
    return 0;
}

CCORDcode
ccord_notifier_open(int notifier_pipe[2])
{
    notifier_pipe[0] = notifier_pipe[1] = -1;
    if (pipe(notifier_pipe) == -1) {
        logmod_log(ERROR, NULL, "Failed to create notifier pipe");
        goto fail_pipe_init;
    }
    for (int i = 0; i < 2; ++i) {
        if (_ccord_notifier_setup_fd(notifier_pipe[i]) == -1) {
            logmod_log(ERROR, NULL,
                       "Failed to make notifier pipe nonblocking and "
                       "close-on-exec");
            goto fail_pipe_init;
        }
    }
    return CCORD_OK;

fail_pipe_init:
    ccord_notifier_close(notifier_pipe);
    return CCORD_ERRNO;
}

void
ccord_notifier_close(int notifier_pipe[2])
{
    for (int i = 0; i < 2; ++i) {
        close(notifier_pipe[i]);
        notifier_pipe[i] = -1;
    }
}

int
ccord_notifier_listen(const int notifier_pipe[2])
{
    int fd = -1;
    if (notifier_pipe[0] == -1) {
        return -1;
    }
    if ((fd = dup(notifier_pipe[0])) != -1) {
        if (_ccord_notifier_setup_fd(fd) == -1) {
            close(fd);
            return -1;
        }
    }
    return fd;
}
