#include <stdio.h>
#include <string.h>

#include "user-agent.h"

void
load(char *str, size_t len, void *ptr)
{
    fprintf(stderr, "%.*s\n", (int)len, str);
}

int
commit(char *base_url, struct logconf *conf)
{
    struct ua_attr ua_attr = { 0 };
    struct user_agent *ua;

    struct ua_resp_handle handle = { .ok_cb = load, .ok_obj = NULL };
    struct ua_conn_attr conn_attr = { 0 };
    struct ua_info info = { 0 };

    /* base url */
    ua_attr.conf = conf;
    ua = ua_init(&ua_attr);
    ua_set_url(ua, base_url);

    conn_attr.body = "{ }";
    conn_attr.body_size = 3;

    conn_attr.method = HTTP_POST;
    conn_attr.endpoint = "/echo?m=POST";
    ua_easy_run(ua, &info, &handle, &conn_attr);

    conn_attr.method = HTTP_PATCH;
    conn_attr.endpoint = "/echo?m=PATCH";
    ua_easy_run(ua, &info, &handle, &conn_attr);

    conn_attr.method = HTTP_GET;
    conn_attr.endpoint = "/echo?m=GET";
    ua_easy_run(ua, &info, &handle, &conn_attr);

    conn_attr.method = HTTP_PUT;
    conn_attr.endpoint = "/echo?m=PUT";
    ua_easy_run(ua, &info, &handle, &conn_attr);

    conn_attr.method = HTTP_DELETE;
    conn_attr.endpoint = "/echo?m=DELETE";
    ua_easy_run(ua, &info, &handle, &conn_attr);

    return 0;
}

int
main(int argc, char *argv[])
{
    char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    struct logconf conf;
    FILE *fp = fopen(config_file, "rb");
    logconf_setup(&conf, "CEE_HTTP", fp);
    fclose(fp);

    commit("https://cee.studio", &conf);

    return 0;
}
