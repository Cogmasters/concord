#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#include "orka-utils.h"
#include "orka-debug.h"
#include "json-scanf.h"


char*
orka_load_whole_file(const char filename[], size_t *len)
{
  size_t f_size = 0;
  FILE *f = fopen(filename,"rb");
  if (!f) {
    ERR("%s '%s'\n", strerror(errno), filename);
  }

  fseek(f, 0, SEEK_END);
  f_size = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = (char *)malloc(f_size);
  fread(string, 1, f_size, f);
  fclose(f);

  if (len) {
    *len = f_size;
  }

  return string;
}


static char *
stat_to_type(const struct stat *st)
{
  switch (st->st_mode & S_IFMT) {
  case S_IFREG: return "file";
  case S_IFDIR: return "folder";
  default:      return NULL;
  }
}

//@todo rename to orka_list ? this is not referenced in orka-utils.h
int
list(void **p, size_t n, char *path)
{
  DIR *d = opendir(path);
  if (!d) return 0; // EARLY RETURN

  int num_files = 0;
  struct stat st = {0};
  int fd = dirfd(d);
  struct dirent *dir;
  while ((dir = readdir(d)) != NULL) 
  {
    if ((0 == strcmp(dir->d_name, ".") || 0 == strcmp(dir->d_name, "..")))
        continue;

    if (0 == fstatat(fd, dir->d_name, &st, 0)) {
      char *type = stat_to_type(&st);
      if (!type) continue;

      if (0 == strcmp(type, "file")) {
        ++num_files;
        D_PRINT("%s\n", dir->d_name);
      }
      else { // nested folder
        // @todo how should we deal with?
      }
    }
  }

  closedir(d);

  return num_files;
}

int
orka_iso8601_to_unix_ms(char *timestamp, size_t len, void *p_data)
{
  int64_t *recipient = (int64_t*)p_data;
  ASSERT_S(NULL != recipient, "No recipient provided by user");

  struct tm tm;
  double seconds = 0;
  memset(&tm, 0, sizeof(tm));

  /* Creating a temporary buffer and copying the string, because
  sscanf receives a null-terminated string, and there's not
  "snscanf" or something like that */
  char *buf = malloc(len + 1);
  if(NULL == buf) return 0; // ERROR @todo provide default value to recipient ?

  memcpy(buf, timestamp, len);
  buf[len] = '\0';

  char tz_operator = 'Z';
  int tz_hour = 0, tz_min = 0;
  sscanf(buf, "%d-%d-%dT%d:%d:%lf%c%d:%d", // ISO-8601 complete format
    &tm.tm_year, &tm.tm_mon, &tm.tm_mday, // Date
    &tm.tm_hour, &tm.tm_min, &seconds, // Time
    &tz_operator, &tz_hour, &tz_min); // Timezone

  free(buf);

  tm.tm_mon--; // struct tm takes month from 0 to 11
  tm.tm_year -= 1900; // struct tm takes years from 1900

  int64_t res = (((int64_t) mktime(&tm) - timezone) * 1000)
              + (int64_t) round(seconds * 1000.0);
  switch (tz_operator) {
  case '+': // Add hours and minutes
      res += (tz_hour * 60 + tz_min) * 60 * 1000;
      break;
  case '-': // Subtract hours and minutes
      res -= (tz_hour * 60 + tz_min) * 60 * 1000;
      break;
  case 'Z': // UTC, don't do anything
  default: // @todo should we check for error ?
      break;
  }

  *recipient = res;

  return 1; // SUCESS
}

void
orka_sleep_ms(const long long delay_ms)
{
  const struct timespec t = {
    .tv_sec = delay_ms / 1000,
    .tv_nsec = (delay_ms % 1000) * 1e6
  };

  nanosleep(&t, NULL);
}

/* returns current timestamp in milliseconds */
int64_t
orka_timestamp_ms()
{
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);

  return t.tv_sec*1000 + lround(t.tv_nsec/1.0e6);
}

void
orka_timestamp_str(char *p_str, int len)
{
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);

  int ret = strftime(p_str, len, "%c", tm);
  ASSERT_S(ret != 0, "Could not retrieve string timestamp");
}

void
orka_strtoull(char *str, size_t len, void *p_data) 
{
  uint64_t *recipient = (uint64_t*)p_data;
  ASSERT_S(NULL != recipient, "No recipient provided by user");

  *recipient = strtoull(str, NULL, 10);

  (void)len;
}


static
int json_load_array (char *  str, size_t len, struct sized_buffer ***p) {
  return json_scanf(str, len, "[]%A", p);
}

/*
 * the buf has to be a string that starts with '[' and ends with ']', and
 * the buf represents a legit json array
 *
 * see test/test-json-scanf-array.c for usage examples
 */
int
json_array_str_to_ntl(char *str, size_t len,
                      struct ntl_deserializer * ntl_deserializer)
{
  ntl_deserializer->partition_as_sized_bufs = json_load_array;
  return ntl_from_buf(str, len, ntl_deserializer);
}