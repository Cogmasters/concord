#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> /* strcasecmp() */
#include <stdarg.h>
#include <unistd.h> /* getpid() */

#include "logconf.h"

#define JSMN_STRICT
#define JSMN_HEADER
#include "jsmn.h"
#include "jsmn-find.h"

static int
get_log_level(char level[])
{
    if (0 == strcasecmp(level, "TRACE")) return LOG_TRACE;
    if (0 == strcasecmp(level, "DEBUG")) return LOG_DEBUG;
    if (0 == strcasecmp(level, "INFO")) return LOG_INFO;
    if (0 == strcasecmp(level, "WARN")) return LOG_WARN;
    if (0 == strcasecmp(level, "ERROR")) return LOG_ERROR;
    if (0 == strcasecmp(level, "FATAL")) return LOG_FATAL;
    ERR("Log level doesn't exist: %s", level);
    return 0; /* make compiler happy */
}

static void
log_nocolor_cb(log_Event *ev)
{
    char buf[16];

    buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

    fprintf(ev->udata, "%s %-5s %s:%d: ", buf, level_strings[ev->level],
            ev->file, ev->line);

    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);
}

static void
log_color_cb(log_Event *ev)
{
    char buf[16];

    buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

    fprintf(ev->udata, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ", buf,
            level_colors[ev->level], level_strings[ev->level], ev->file,
            ev->line);

    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);
}

/** @todo this doesn't disable `logconf_http()` logging */
static bool
module_is_disabled(struct logconf *conf)
{
    int i;

    for (i = 0; i < conf->disable_modules.size; ++i) {
        if (0 == strcmp(conf->id, conf->disable_modules.ids[i])) {
            memset(conf->L, 0, sizeof *conf->L);
            /* silence output for all levels but fatal*/
            logconf_set_quiet(conf, true);
            logconf_add_callback(conf, &log_nocolor_cb, stderr, LOG_FATAL);
            return true;
        }
    }
    return false;
}

static void
lock(struct logconf *conf)
{
    if (conf->L->lock) conf->L->lock(true, conf->L->udata);
}

static void
unlock(struct logconf *conf)
{
    if (conf->L->lock) conf->L->lock(false, conf->L->udata);
}

void
logconf_http(struct logconf *conf,
             struct loginfo *p_info,
             char url[],
             struct sized_buffer header,
             struct sized_buffer body,
             char label_fmt[],
             ...)
{
    uint64_t tstamp_ms;
    int counter;

    if (!conf) return;

    tstamp_ms = cog_timestamp_ms();

    lock(conf);
    counter = ++*conf->counter;
    unlock(conf);

    if (conf->http && conf->http->f) {
        char timestr[64], label[512];
        va_list label_args;
        int len;

        va_start(label_args, label_fmt);
        len = vsnprintf(label, sizeof(label), label_fmt, label_args);
        ASSERT_S((size_t)len < sizeof(label), "Out of bounds write attempt");
        va_end(label_args);

        cog_unix_ms_to_iso8601(timestr, sizeof(timestr), tstamp_ms);

        /* Print to output */
        fprintf(conf->http->f,
                "%s [%s] - %s - %s\n"
                "%.*s%s%.*s\n"
                "@@@_%d_@@@\n",
                /* 1st LINE ARGS */
                label, conf->id, timestr, url,
                /* 2nd LINE ARGS */
                (int)header.size, header.start, header.size ? "\n" : "",
                (int)body.size, body.start,
                /* 3rd LINE ARGS */
                counter);

        fflush(conf->http->f);
    }

    if (p_info) {
        memset(p_info, 0, sizeof *p_info);
        p_info->counter = counter;
        p_info->tstamp_ms = tstamp_ms;
    }
}

void
logconf_setup(struct logconf *conf, const char id[], FILE *fp)
{
    struct {
        char level[16];
        char filename[1028];
        bool quiet, use_color, overwrite;
        struct {
            bool enable;
            char filename[1028];
        } http;
    } l = { 0 };

    jsmnf *root = jsmnf_init();
    int ret;

    memset(conf, 0, sizeof *conf);

    ret = snprintf(conf->id, sizeof(conf->id), "%s", id);
    ASSERT_S((size_t)ret < sizeof(conf->id), "Out of bounds write attempt");

    conf->pid = getpid();
    conf->counter = calloc(1, sizeof *conf->counter);
    conf->L = calloc(1, sizeof *conf->L);

    if (!fp) return;

    conf->logger = calloc(1, sizeof *conf->logger);
    conf->http = calloc(1, sizeof *conf->http);

    conf->file.start = cog_load_whole_file_fp(fp, &conf->file.size);

    if (jsmnf_start(root, conf->file.start, conf->file.size) >= 0) {
        jsmnf *f;

        f = jsmnf_find(root, "logging", sizeof("logging") - 1);
        if (f) {
            jsmnf *f1;

            f1 = jsmnf_find(f, "level", sizeof("level") - 1);
            if (f1)
                snprintf(l.level, sizeof(l.level), "%.*s",
                         f1->val->end - f1->val->start,
                         conf->file.start + f1->val->start);
            f1 = jsmnf_find(f, "filename", sizeof("filename") - 1);
            if (f1)
                snprintf(l.filename, sizeof(l.filename), "%.*s",
                         f1->val->end - f1->val->start,
                         conf->file.start + f1->val->start);
            f1 = jsmnf_find(f, "quiet", sizeof("quiet") - 1);
            if (f1) l.quiet = ('t' == conf->file.start[f1->val->start]);
            f1 = jsmnf_find(f, "use_color", sizeof("use_color") - 1);
            if (f1) l.use_color = ('t' == conf->file.start[f1->val->start]);
            f1 = jsmnf_find(f, "overwrite", sizeof("overwrite") - 1);
            if (f1) l.overwrite = ('t' == conf->file.start[f1->val->start]);
            f1 = jsmnf_find(f, "http", sizeof("http") - 1);
            if (f1) {
                jsmnf *f2;

                f2 = jsmnf_find(f1, "enable", sizeof("enable") - 1);
                if (f2)
                    l.http.enable = ('t' == conf->file.start[f2->val->start]);
                f2 = jsmnf_find(f1, "filename", sizeof("filename") - 1);
                if (f2)
                    snprintf(l.http.filename, sizeof(l.http.filename), "%.*s",
                             f2->val->end - f2->val->start,
                             conf->file.start + f2->val->start);
            }
            f1 = jsmnf_find(f, "disable_modules",
                            sizeof("disable_modules") - 1);
            if (f1) {
                size_t nelems = HASH_COUNT(root->child);

                if (nelems) {
                    jsmnf *f2, *tmp;
                    int i = 0;

                    conf->disable_modules.ids =
                        calloc(1, nelems * sizeof(char *));
                    HASH_ITER(hh, f1->child, f2, tmp)
                    {
                        if (f2 && f2->val->type == JSMN_STRING) {
                            jsmnf_unescape(conf->disable_modules.ids + i,
                                           conf->file.start + f2->val->start,
                                           f2->val->end - f2->val->start);
                            ++i;
                        }
                    }
                    conf->disable_modules.size = i;
                }
            }
        }
    }
    jsmnf_cleanup(root);

    /* skip everything else if this module is disabled */
    if (module_is_disabled(conf)) return;

    /* SET LOGGER CONFIGS */
    if (*l.filename) {
        conf->logger->fname = strdup(l.filename);
        conf->logger->f =
            fopen(conf->logger->fname, l.overwrite ? "w+" : "a+");
        ASSERT_S(NULL != conf->logger->f, "Could not create logger file");

        logconf_add_callback(conf,
                             l.use_color ? &log_color_cb : &log_nocolor_cb,
                             conf->logger->f, get_log_level(l.level));
    }

    /* SET HTTP DUMP CONFIGS */
    if (l.http.enable && *l.http.filename) {
        conf->http->fname = strdup(l.http.filename);
        conf->http->f = fopen(conf->http->fname, l.overwrite ? "w+" : "a+");
        ASSERT_S(NULL != conf->http->f, "Could not create http logger file");
    }

    /* disable default log.c callbacks */
    logconf_set_quiet(conf, true);

    /* make sure fatal still prints to stderr */
    logconf_add_callback(conf, l.use_color ? &log_color_cb : &log_nocolor_cb,
                         stderr, l.quiet ? LOG_FATAL : get_log_level(l.level));
}

void
logconf_branch(struct logconf *branch, struct logconf *orig, const char id[])
{
    if (!orig) {
        logconf_setup(branch, id, NULL);
        return;
    }

    lock(orig);
    memcpy(branch, orig, sizeof(struct logconf));
    unlock(orig);

    branch->is_branch = true;
    if (id) {
        int len = snprintf(branch->id, sizeof(branch->id), "%s", id);
        ASSERT_S((size_t)len < sizeof(branch->id),
                 "Out of bounds write attempt");
    }
    branch->pid = getpid();
}

void
logconf_cleanup(struct logconf *conf)
{
    if (!conf->is_branch) {
        if (conf->file.start) {
            free(conf->file.start);
        }
        if (conf->logger) {
            if (conf->logger->fname) free(conf->logger->fname);
            if (conf->logger->f) fclose(conf->logger->f);
            free(conf->logger);
        }
        if (conf->http) {
            if (conf->http->fname) free(conf->http->fname);
            if (conf->http->f) fclose(conf->http->f);
            free(conf->http);
        }
        if (conf->disable_modules.ids) {
            int i;

            for (i = 0; i < conf->disable_modules.size; ++i)
                free(conf->disable_modules.ids[i]);
            free(conf->disable_modules.ids);
        }
        free(conf->counter);
        free(conf->L);
    }
    memset(conf, 0, sizeof *conf);
}

struct sized_buffer
logconf_get_field(struct logconf *conf, char *const path[], int depth)
{
    struct sized_buffer field = { 0 };
    jsmnf *root;

    if (!conf->file.size) return field; /* empty field */

    root = jsmnf_init();
    if (jsmnf_start(root, conf->file.start, conf->file.size) >= 0) {
        jsmnf *f = jsmnf_find_path(root, path, depth);

        if (f) {
            field.start = conf->file.start + f->val->start;
            field.size = f->val->end - f->val->start;
        }
    }
    jsmnf_cleanup(root);

    return field;
}

void
logconf_set_lock(struct logconf *conf, log_LockFn fn, void *udata)
{
    _log_set_lock(conf->L, fn, udata);
}

void
logconf_set_level(struct logconf *conf, int level)
{
    _log_set_level(conf->L, level);
}

void
logconf_set_quiet(struct logconf *conf, bool enable)
{
    _log_set_quiet(conf->L, enable);
}

void
logconf_add_callback(struct logconf *conf,
                     log_LogFn fn,
                     void *udata,
                     int level)
{
    _log_add_callback(conf->L, fn, udata, level);
}

int
logconf_add_fp(struct logconf *conf, FILE *fp, int level)
{
    return _log_add_fp(conf->L, fp, level);
}
