#ifndef REDDIT_H
#define REDDIT_H

#include <stdbool.h>
#include "json-actor-boxed.h"
#include "common.h"
#include "logconf.h"

/* see specs/reddit/ for specs */
#include "specs-code/reddit/one-specs.h"

#define REDDIT_BASE_API_URL   "https://www.reddit.com"
#define REDDIT_BASE_OAUTH_URL "https://oauth.reddit.com"

struct reddit *reddit_init(const char username[],
                           const char password[],
                           const char client_id[],
                           const char client_secret[]);

struct reddit *reddit_config_init(const char config_file[]);

void reddit_cleanup(struct reddit *client);

ORCAcode reddit_access_token(struct reddit *client,
                             struct reddit_access_token_params *params,
                             struct sized_buffer *ret);

ORCAcode reddit_comment(struct reddit *client,
                        struct reddit_comment_params *params,
                        struct sized_buffer *ret);

ORCAcode reddit_search(struct reddit *client,
                       struct reddit_search_params *params,
                       char subreddit[],
                       struct sized_buffer *ret);

#endif /* REDDIT_H */
