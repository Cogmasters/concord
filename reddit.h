#ifndef REDDIT_H
#define REDDIT_H

#include <stdbool.h>
#include "json-actor-boxed.h"

/// @see specs/discord for generated code specs #include "specs-code/discord/all_opaque_struct.h"
#include "specs-code/reddit/all_enums.h"
#include "specs-code/reddit/all_structs.h"
#include "specs-code/reddit/all_functions.h"

struct reddit* reddit_config_init(const char config_file[]);
void reddit_cleanup(struct reddit *client);

void reddit_access_token(struct reddit *client);

void reddit_search(struct reddit *client, struct reddit_search_params *params, char subreddit[], struct sized_buffer *p_json);

#endif // REDDIT_H
