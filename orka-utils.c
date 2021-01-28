#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "orka-utils.h"

char*
orka_load_whole_file(const char filename[], size_t *len)
{
  FILE *f = fopen(filename,"rb");
  if (!f) {
    char *s = strerror(errno);
    fprintf (stderr, "%s '%s'\n", s, filename);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  *len = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = (char *)malloc(*len);
  fread(string, 1, *len, f);
  fclose(f);
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