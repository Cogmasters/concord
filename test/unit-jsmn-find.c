#include <string.h>

#include "test-utils.h"

/* Parse JS into stack-allocated tables; returns number of pairs or < 0 */
static long
parse(const char *js, size_t len,
      jsmntok_t toks[], size_t ntoks,
      jsmnf_loader *loader, jsmnf_table table[], size_t ntable)
{
    jsmn_parser p;
    jsmn_init(&p);
    if (jsmn_parse(&p, js, len, toks, (unsigned int)ntoks) < 1) return -1;
    jsmnf_init(loader);
    return jsmnf_load(loader, js, len, table, ntable);
}

TEST top_level_hit(void)
{
    const char *js = "{\"foo\":\"bar\"}";
    size_t len = strlen(js);
    jsmntok_t toks[16]; jsmnf_table tb[16]; jsmnf_loader ld;

    ASSERT_GTE(parse(js, len, toks, 16, &ld, tb, 16), 1L);
    const jsmnf_pair *f = jsmnf_find(ld.root, "foo", 3);
    ASSERT_NEQ(NULL, f);
    ASSERT_EQ(3, f->v->end - f->v->start);
    ASSERT_EQ(0, strncmp("bar", js + f->v->start, 3));
    PASS();
}

TEST top_level_miss(void)
{
    const char *js = "{\"foo\":\"bar\"}";
    size_t len = strlen(js);
    jsmntok_t toks[16]; jsmnf_table tb[16]; jsmnf_loader ld;

    ASSERT_GTE(parse(js, len, toks, 16, &ld, tb, 16), 1L);
    ASSERT_EQ(NULL, jsmnf_find(ld.root, "missing", 7));
    PASS();
}

TEST nested_key(void)
{
    const char *js = "{\"a\":{\"b\":\"deep\"}}";
    size_t len = strlen(js);
    jsmntok_t toks[16]; jsmnf_table tb[16]; jsmnf_loader ld;

    ASSERT_GTE(parse(js, len, toks, 16, &ld, tb, 16), 1L);
    const jsmnf_pair *outer = jsmnf_find(ld.root, "a", 1);
    ASSERT_NEQ(NULL, outer);
    const jsmnf_pair *inner = jsmnf_find(outer, "b", 1);
    ASSERT_NEQ(NULL, inner);
    ASSERT_EQ(4, inner->v->end - inner->v->start);
    ASSERT_EQ(0, strncmp("deep", js + inner->v->start, 4));
    PASS();
}

TEST array_element(void)
{
    const char *js = "[\"x\",\"y\",\"z\"]";
    size_t len = strlen(js);
    jsmntok_t toks[16]; jsmnf_table tb[16]; jsmnf_loader ld;

    ASSERT_GTE(parse(js, len, toks, 16, &ld, tb, 16), 1L);
    /* Array elements are accessed by index string */
    const jsmnf_pair *e1 = jsmnf_find(ld.root, "1", 1);
    ASSERT_NEQ(NULL, e1);
    ASSERT_EQ(1, e1->v->end - e1->v->start);
    ASSERT_EQ(0, strncmp("y", js + e1->v->start, 1));
    PASS();
}

TEST malformed_json(void)
{
    const char *js = "{bad json";
    jsmn_parser p;
    jsmntok_t toks[8];
    jsmn_init(&p);
    int r = jsmn_parse(&p, js, strlen(js), toks, 8);
    ASSERT_LT(r, 1);
    PASS();
}

SUITE(jsmn_find)
{
    RUN_TEST(top_level_hit);
    RUN_TEST(top_level_miss);
    RUN_TEST(nested_key);
    RUN_TEST(array_element);
    RUN_TEST(malformed_json);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(jsmn_find);
    GREATEST_MAIN_END();
}
