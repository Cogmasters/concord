#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "orka-utils.h"
#include <math.h>
#include <time.h>

char*
orka_load_whole_file(const char filename[], size_t *len)
{
  size_t size = 0;
  FILE *f = fopen(filename,"rb");
  if (!f) {
    char *s = strerror(errno);
    fprintf (stderr, "%s '%s'\n", s, filename);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = (char *)malloc(size);
  fread(string, 1, size, f);
  fclose(f);

  if (len)
    *len = size;
  return string;
}


static char *
stat_to_type (const struct stat *st)
{
  switch(st->st_mode & S_IFMT) {
    case S_IFREG:
      return "file";
      break;
    case S_IFDIR:
      return "folder";
      break;
    default:
      return NULL;
      break;
  }
}

int
list(void ** p, size_t n, char * path)
{
  struct dirent * dir;
  DIR * d;

  int total_files = 0;
  d = opendir(path);
  int fd = dirfd(d);
  struct stat st = {0};
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (0 != strcmp(dir->d_name, ".") && 0 != strcmp(dir->d_name, "..")) {
        if (fstatat(fd, dir->d_name, &st, 0) == 0) {
          char * type = stat_to_type(&st);
          if (type) {
            if (0 == strcmp(type, "file")) {
              total_files ++;
              fprintf(stderr, "%s\n", dir->d_name);
            }
            else { // nested folder

            }
          }
        }
      }
    }
    closedir(d);
  }
  return total_files;
}

int orka_iso8601_to_unix_ms(char *timestamp, size_t s, void *p)
{
  struct tm tm;
  double seconds = 0;
  char tz_operator = 'Z';
  int tz_hour = 0;
  int tz_min = 0;
  int64_t result = 0;
  int64_t *recipient = (int64_t*) p;
  char *buf = NULL;
  memset(&tm, 0, sizeof(tm));

  /* Creating a temporary buffer and copying the string, because
  sscanf receives a null-terminated string, and there's not
  "snscanf" or something like that */
  buf = malloc(s + 1);
  if(!buf) return 0;
  memcpy(buf, timestamp, s);
  buf[s] = '\0';

  sscanf(buf, "%d-%d-%dT%d:%d:%lf%c%d:%d", // ISO-8601 complete format
  &tm.tm_year, &tm.tm_mon, &tm.tm_mday, // Date
  &tm.tm_hour, &tm.tm_min, &seconds, // Time
  &tz_operator, &tz_hour, &tz_min); // Timezone

  free(buf);

  tm.tm_mon--; // struct tm takes month from 0 to 11, instead of 1 to 12
  tm.tm_year -= 1900; // struct tm takes years from 1900

  result = (((int64_t) mktime(&tm) - timezone) * 1000) +
  (int64_t) round(seconds * 1000.0);
  switch(tz_operator)
  {
    case 'Z':
      // UTC, don't do nothing
      break;
    case '+':
      // Add hours and minutes
      result += (tz_hour * 60 + tz_min) * 60 * 1000;
      break;
    case '-':
      // Subtract hours and minutes
      result -= (tz_hour * 60 + tz_min) * 60 * 1000;
      break;
  }

  *recipient = result;

  return 1;
}