#include <dirent.h>

#include "test-utils.h"

/* The corpus currently holds 30 fixtures; a lower bound guards against the
 * whitelist .gitignore silently dropping the directory on a fresh clone. */
#define FIXTURES_MIN_COUNT 25

TEST all_fixtures_parse(void)
{
    DIR *dir = opendir("fixtures");
    struct dirent *ent;
    int seen = 0;

    ASSERT_NEQm("cannot open test/fixtures", NULL, dir);
    while ((ent = readdir(dir)) != NULL) {
        char path[512];
        char *buf = NULL;
        size_t len = 0;
        jsmn_parser parser;
        jsmntok_t *tokens = NULL;
        unsigned ntokens_max = 0;
        long ntokens;

        const char *dot = strrchr(ent->d_name, '.');
        if (!dot || 0 != strcmp(dot, ".json")) continue;

        snprintf(path, sizeof(path), "fixtures/%s", ent->d_name);
        if (0 != test_load_fixture(path, &buf, &len)) {
            closedir(dir);
            FAILm("fixture unreadable");
        }
        jsmn_init(&parser);
        ntokens = jsmn_parse_auto(&parser, buf, len, &tokens, &ntokens_max);
        free(tokens);
        free(buf);
        if (ntokens < 1) {
            fprintf(stderr, "malformed JSON: %s\n", path);
            closedir(dir);
            FAILm("fixture is not valid JSON");
        }
        ++seen;
    }
    closedir(dir);
    ASSERT_GTEm("fixture corpus incomplete (gitignore?)",
                seen, FIXTURES_MIN_COUNT);
    PASS();
}

TEST hello_envelope_lookup(void)
{
    char *buf = NULL;
    size_t len = 0;
    jsmnf_loader loader;
    jsmnf_table *table = NULL;
    size_t table_len = 0;
    const jsmnf_pair *op, *interval;

    ASSERT_EQ(0, test_load_fixture("fixtures/gateway-hello.json", &buf, &len));
    jsmnf_init(&loader);
    ASSERT_GTE(jsmnf_load_auto(&loader, buf, len, &table, &table_len), 1L);

    op = jsmnf_find(loader.root, "op", 2);
    ASSERT_NEQ(NULL, op);
    ASSERT_EQ(2, op->v->end - op->v->start);
    ASSERT_EQ(0, strncmp("10", buf + op->v->start, 2));

    interval = jsmnf_find_path(loader.root, (char *[]){ "d",
                               "heartbeat_interval" }, 2);
    ASSERT_NEQ(NULL, interval);

    free(table);
    free(buf);
    PASS();
}

SUITE(fixtures_smoke)
{
    RUN_TEST(all_fixtures_parse);
    RUN_TEST(hello_envelope_lookup);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(fixtures_smoke);
    GREATEST_MAIN_END();
}
