#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "reddit.h"

#include "json-actor-boxed.h" /* ja_str and functions */
#include "json-actor.h" /* json_extract() */
#include "orka-utils.h" /* orka_load_whole_file() */

#define SEARCH_PARAMS_FILE "test-reddit-api.json"


char* concat_strlist(NTL_T(ja_str) str_list, const char separator[], const size_t len)
{
  char *buf = calloc(1, len);
  char *cur = buf, * const end = cur + len;
  for (size_t i=0; str_list[i]; ++i) {
    cur += snprintf(cur, end-cur, "%s%s", *str_list[i], separator);
    if (cur > end) {
      fprintf(stderr, "Surpass threshold of %zu characters\n", len);
      exit(EXIT_FAILURE);
    }
  }
  return buf;
}

void load_search_params(
    struct reddit_search_params *params, 
    struct sized_buffer *sr)
{
  struct sized_buffer settings={0};
  settings.start = orka_load_whole_file(SEARCH_PARAMS_FILE, &settings.size);
  assert(NULL != settings.start && "Missing search config file!");

  NTL_T(ja_str) ja_q=NULL;
  NTL_T(ja_str) ja_sr=NULL;
  json_extract(settings.start, settings.size,
      "(keywords):F"
      "(restrict_sr):b"
      "(subreddits):F",
      &ja_str_list_from_json, &ja_q,
      &params->restrict_sr, 
      &ja_str_list_from_json, &ja_sr);
  assert(NULL != ja_q && "Missing ja_q");
  assert(NULL != ja_sr && "Missing ja_sr");

  params->q = concat_strlist(ja_q, " ", 512);
  assert(NULL != params->q && "Missing keywords");

  sr->size = 1024;
  sr->start = concat_strlist(ja_sr, "+", sr->size);
  assert(NULL != sr && "Missing subreddits");

#if 0
  ja_str_list_free(ja_q);
  ja_str_list_free(ja_sr);
#endif
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct reddit *client = reddit_config_init(config_file);

  reddit_access_token(client); 

  struct sized_buffer sr={0};
  struct reddit_search_params params={
    .limit = 100
  };
  load_search_params(&params, &sr);

  struct sized_buffer json_resp={0};
  reddit_search(client, &params, sr.start, &json_resp);

  FILE *f_out = fopen("reddit-search.out", "w+");
  fwrite(json_resp.start, 1, json_resp.size, f_out);
  fclose(f_out);

  free(params.q);
  free(sr.start);
  reddit_cleanup(client);
}
