#ifndef REDDIT_H
#define REDDIT_H

struct reddit* reddit_config_init(const char config_file[]);
void reddit_cleanup(struct reddit *client);

void reddit_access_token(struct reddit *client);

#endif // REDDIT_H
