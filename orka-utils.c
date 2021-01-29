#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "orka-utils.h"
#include <math.h>

char*
orka_load_whole_file(const char filename[], size_t *len)
{
  size_t size = NULL;
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

long long iso8601_to_unix_ms(const char *timestamp)
{
  struct tm tm;
  double seconds = 0;
  char tz_operator = 'Z';
  int tz_hour = 0;
  int tz_min = 0;
  long long result = 0;
  memset(&tm, 0, sizeof(tm));

  sscanf(timestamp, "%d-%d-%dT%d:%d:%lf%c%d:%d", // ISO-8601 complete format
  &tm.tm_year, &tm.tm_mon, &tm.tm_mday, // Date
  &tm.tm_hour, &tm.tm_min, &seconds, // Time
  &tz_operator, &tz_hour, &tz_min); // Timezone

  tm.tm_mon--; // struct tm takes month from 0 to 11, instead of 1 to 12
  tm.tm_year -= 1900; // struct tm takes years from 1900

  result = (((long long) mktime(&tm) - timezone) * 1000) +
  (long long) round(seconds * 1000.0);
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

  return result;
}