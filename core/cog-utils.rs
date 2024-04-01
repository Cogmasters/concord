#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <errno.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "cog-utils.h"
#include "clock.h"

char *
cog_load_whole_file_fp(FILE *fp, size_t *len)
{
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (-1 == fsize) {
        if (len) *len = 0;
        return NULL;
    }

    char *str = malloc(fsize + 1);
    str[fsize] = '\0';
    if (!fread(str, 1, fsize, fp)) {
        free(str);
        str = NULL;
        fsize = 0;
    }
    if (len) *len = fsize;

    return str;
}

char *
cog_load_whole_file(const char filename[], size_t *len)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "%s '%s'\n", strerror(errno), filename);
        return NULL;
    }
    char *str = cog_load_whole_file_fp(fp, len);
    fclose(fp);
    return str;
}

long
cog_timezone(void)
{
    static int once;
    static long tz;

    if (!once) {
        const time_t epoch_plus_11h = 60 * 60 * 11;
        const struct tm *local, *gm;
        long tz_hour, tz_min;

        local = localtime(&epoch_plus_11h);
        tz_hour = local->tm_hour;
        tz_min = local->tm_min;

        gm = gmtime(&epoch_plus_11h);
        tz_hour -= gm->tm_hour;
        tz_min -= gm->tm_min;

        tz = tz_hour * 60 * 60 + tz_min * 60;

        once = 1;
    }

    return tz;
}

int
cog_iso8601_to_unix_ms(const char str[], size_t len, uint64_t *p_value)
{
    double seconds = 0.0;
    int tz_operator = 'Z';
    int tz_hour = 0, tz_min = 0;
    struct tm tm = { 0 };
    (void)len;

    /* ISO-8601 complete format */
    sscanf(str, "%d-%d-%dT%d:%d:%lf%d%d:%d", &tm.tm_year, &tm.tm_mon,
           &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &seconds, &tz_operator,
           &tz_hour, &tz_min);

    tm.tm_mon--; /* struct tm takes month from 0 to 11 */
    tm.tm_year -= 1900; /* struct tm takes years from 1900 */

    *p_value = (((uint64_t)mktime(&tm) + cog_timezone()) * 1000)
               + (uint64_t)(seconds * 1000.0);

    switch (tz_operator) {
    case '+': /* Add hours and minutes */
        *p_value += (tz_hour * 60 + tz_min) * 60 * 1000;
        break;
    case '-': /* Subtract hours and minutes */
        *p_value -= (tz_hour * 60 + tz_min) * 60 * 1000;
        break;
    case 'Z': /* UTC, don't do anything */
    default:
        break;
    }

    return 1; /* SUCCESS */
}

int
cog_unix_ms_to_iso8601(char *str, size_t len, uint64_t value)
{
    time_t seconds = (value / 1000) - cog_timezone();
    int millis = value % 1000;
    struct tm *tm = localtime(&seconds);

    return snprintf(
        str, len,
        "%d-%.2d-%dT%.2d:%.2d:%.2d.%.3dZ", /* ISO-8601 complete format */
        tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, /* Date */
        tm->tm_hour, tm->tm_min, tm->tm_sec, millis); /* Time */
}

int
cog_strtou64(char *str, size_t len, uint64_t *p_value)
{
    char fmt[512];
    size_t ret = snprintf(fmt, sizeof(fmt), "%%%zu" SCNu64, len);

    if (ret >= sizeof(fmt)) return 0;

    return sscanf(str, fmt, p_value) != EOF;
}

int
cog_u64tostr(char *str, size_t len, uint64_t *p_value)
{
    return snprintf(str, len, "%" PRIu64, *p_value);
}

size_t
cog_strndup(const char src[], size_t len, char **p_dest)
{
    *p_dest = malloc(len + 1);

    memcpy(*p_dest, src, len);
    (*p_dest)[len] = '\0';

    return len;
}

size_t
cog_asprintf(char **strp, const char fmt[], ...)
{
    va_list argp;
    char one_char[1];
    int len;

    va_start(argp, fmt);

    len = vsnprintf(one_char, 1, fmt, argp);
    if (len < 1) {
        *strp = NULL;
        return len;
    }

    va_end(argp);

    *strp = malloc(len + 1);
    if (!strp) return -1;

    va_start(argp, fmt);
    vsnprintf(*strp, len + 1, fmt, argp);
    va_end(argp);

    return len;
}

int
cog_sleep_ms(const long tms)
{
    int ret;

#if _POSIX_C_SOURCE >= 199309L
    struct timespec ts;

    if (tms < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = tms / 1000;
    ts.tv_nsec = (tms % 1000) * 1000000;

    do {
        ret = nanosleep(&ts, &ts);
    } while (ret && errno == EINTR);
#else
    struct timeval timeout;
    long _tms = tms;

    timeout.tv_sec = _tms / 1000L;
    _tms = tms % 1000L;
    timeout.tv_usec = (int)_tms * 1000;
    select(0, NULL, NULL, NULL, &timeout);

    ret = 0;
#endif

    return ret;
}

int
cog_sleep_us(const long tms)
{
    int ret;

#if _POSIX_C_SOURCE >= 199309L
    struct timespec ts;

    if (tms < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = tms / 1000000;
    ts.tv_nsec = (tms % 1000000) * 1000;

    do {
        ret = nanosleep(&ts, &ts);
    } while (ret && errno == EINTR);
#else
    struct timeval timeout;
    long _tms = tms;

    timeout.tv_sec = _tms / 1000000L;
    _tms = tms % 1000000L;
    timeout.tv_usec = (int)_tms;
    select(0, NULL, NULL, NULL, &timeout);

    ret = 0;
#endif

    return ret;
}

/* returns current timestamp in milliseconds */
uint64_t
cog_timestamp_ms(void)
{
    struct PsnipClockTimespec t;
    if (0 == psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &t)) {
        return (uint64_t)t.seconds * 1000 + (uint64_t)t.nanoseconds / 1000000;
    }
    return 0;
}

/* returns current timestamp in microseconds */
uint64_t
cog_timestamp_us(void)
{
    struct PsnipClockTimespec t;
    if (0 == psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &t)) {
        return (uint64_t)t.seconds * 1000000 + (uint64_t)t.nanoseconds / 1000;
    }
    return 0;
}
