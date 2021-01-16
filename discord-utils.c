#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <libdiscord.h>
#include "discord-common.h"

void*
Discord_utils_set_data(discord_t *client, void *data) {
  return client->data = data;
}

void*
Discord_utils_get_data(discord_t *client) {
  return client->data;
}

static void
timestamp_str(char str[], int len)
{
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);

  int ret = strftime(str, len, "%c", tm);
  ASSERT_S(ret != 0, "Could not retrieve string timestamp");
}

static void
curl_dump(const char *text, FILE *f_dump, unsigned char *ptr, size_t size)
{
  const unsigned int WIDTH = 0x10;

  char timestr[64];
  timestamp_str(timestr, sizeof(timestr));
 
  fprintf(f_dump, "\r\r\r\r%s %10.10ld bytes (0x%8.8lx) - %s\n%s\n",
          text, (long)size, (long)size, timestr, ptr);
 
  for(size_t i=0; i < size; i += WIDTH)
  {
    fprintf(f_dump, "%4.4lx: ", (long)i);
 
    //show hex to the left
    for(size_t c = 0; c < WIDTH; c++) {
      if(i+c < size)
        fprintf(f_dump, "%02x ", ptr[i+c]);
      else
        fputs("   ", f_dump);
    }
 
    //show data on the right
    for(size_t c = 0; (c < WIDTH) && (i+c < size); c++) {
      char x = (ptr[i+c] >= 0x20 && ptr[i+c] < 0x80) ? ptr[i+c] : '.';
      fputc(x, f_dump);
    }
 
    fputc('\n', f_dump); //newline
  }

  fflush(f_dump);
}

void
Discord_utils_json_dump(const char *text, struct _settings_s *settings, const char *data)
{
  if (NULL == settings->f_json_dump) return;
  FILE *f_dump = settings->f_json_dump;

  char timestr[64];
  timestamp_str(timestr, sizeof(timestr));

  fprintf(f_dump, "\r\r\r\r%s - %s\n%s\n", text, timestr, data);
  fflush(f_dump);
}

int
Discord_utils_debug_cb(
    CURL *ehandle,
    curl_infotype type,
    char *data,
    size_t size,
    void *p_userdata)
{
  struct _settings_s *settings = p_userdata;
  if (NULL == settings->f_curl_dump) return 0;
  FILE *f_dump = settings->f_curl_dump;

  const char *text;
  switch (type) {
  case CURLINFO_TEXT:
   {
      char timestr[64];
      timestamp_str(timestr, sizeof(timestr));

      fprintf(f_dump, "\r\r\r\rCURL INFO - %s\n%s\n", timestr, data);
      fflush(f_dump);
   }
  /* fallthrough */
  default:
      return 0;
  case CURLINFO_HEADER_OUT:
      text = "SEND HEADER";
      break;
  case CURLINFO_DATA_OUT:
      text = "SEND DATA";
      break;
  case CURLINFO_SSL_DATA_OUT:
      text = "SEND SSL DATA";
      break;
  case CURLINFO_HEADER_IN:
      text = "RECEIVE HEADER";
      break;
  case CURLINFO_DATA_IN:
      text = "RECEIVE DATA";
      break;
  case CURLINFO_SSL_DATA_IN:
      text = "RECEIVE SSL DATA";
      break;
  }

  curl_dump(text, f_dump, (unsigned char*)data, size);

  return 0;

  (void)ehandle;
}
