#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "orka-utils.h"
#include "json-actor.c"
#include "greatest.h"

GREATEST_MAIN_DEFS();

SUITE(json_inject_extract);

#define A "Íñdîæ"
#define B "m\u00fcller"
#define C "的"
#define D "😊"
#define UTF8_JSON "{\"a\":\""A"\",\"b\":\""B"\",\"c\":\""C"\",\"d\":\""D"\"}"

static char start_string_single[4096] = "{\"a\":\"\"}";

static char A1[16] = "", B1[16] = "void", C1[16] = "{<|", D1[16] = "23450";
static char start_string[4096];


TEST expect_json_inject_to_be_working_none(void)
{ 
  //skip for now in case we want to add this in later
  SKIP();

  //setup
  char start_string[4096] = "{}";
  
  char payload[4096];
  json_inject(payload, sizeof(payload), "");
  ASSERT_STR_EQ(start_string, payload);
  PASS();
}

TEST expect_json_extract_to_be_working_single(void)
{ 
  char a[16] = "sample";
  
  json_extract(start_string_single, sizeof(start_string_single), "(a):s", a);
  ASSERT_STR_EQ("", a);
  PASS();
}

TEST expect_json_inject_to_be_working_single(void)
{
  //setup
  char A1[16] = "";
  
  char payload[4096];
  json_inject(payload, sizeof(payload), "(a):s", A1);
  ASSERT_STR_EQ(start_string_single, payload);
  PASS();
}

TEST expect_json_extract_to_be_working_ascii(void)
{
  char a[16], b[16], c[16], d[16];

  json_extract(start_string, sizeof(start_string), "(a):s,(b):s,(c):s,(d):s", a, b, c, d);
  ASSERT_STR_EQ(A1, a);
  ASSERT_STR_EQ(B1, b);
  ASSERT_STR_EQ(C1, c);
  ASSERT_STR_EQ(D1, d);
  PASS();
}

TEST expect_json_inject_to_be_working_ascii(void)
{
  char payload[4096];
  json_inject(payload, sizeof(payload), \
      "(a):s,(b):s,(c):s,(d):s", A1, B1, C1, D1);
  ASSERT_STR_EQ(start_string, payload);
  PASS();
}

TEST expect_doubly_encoded_equal_original_extract(void) 
{
  char a[16], b[16], c[16], d[16];
  json_extract(UTF8_JSON, sizeof(UTF8_JSON), \
      "(a):s,(b):s,(c):s,(d):s", a, b, c, d);
  ASSERT_STR_EQ(A, a);
  ASSERT_STR_EQ(B, b);
  ASSERT_STR_EQ(C, c);
  ASSERT_STR_EQ(D, d);
  PASS();
}

TEST expect_doubly_encoded_equal_original_inject(void)
{
  char payload[4096];
  json_inject(payload, sizeof(payload), \
      "(a):s,(b):s,(c):s,(d):s", A, B, C, D);
  ASSERT_STR_EQ(UTF8_JSON, payload);
  PASS();
}

SUITE(json_inject_suite)
{
  sprintf(start_string, "{\"a\":\"%s\",\"b\":\"%s\",\"c\":\"%s\",\"d\":\"%s\"}", A1, B1, C1, D1);
  RUN_TEST(expect_json_inject_to_be_working_none);
  RUN_TEST(expect_json_inject_to_be_working_single);
  RUN_TEST(expect_json_inject_to_be_working_ascii);
  RUN_TEST(expect_doubly_encoded_equal_original_inject);
}

SUITE(json_extract_suite)
{
  sprintf(start_string, "{\"a\":\"%s\",\"b\":\"%s\",\"c\":\"%s\",\"d\":\"%s\"}", A1, B1, C1, D1);
  RUN_TEST(expect_json_extract_to_be_working_single);
  RUN_TEST(expect_json_extract_to_be_working_ascii);
  RUN_TEST(expect_doubly_encoded_equal_original_extract);
}

SUITE(json_inject_extract) {
  sprintf(start_string, "{\"a\":\"%s\",\"b\":\"%s\",\"c\":\"%s\",\"d\":\"%s\"}", A1, B1, C1, D1);
  RUN_SUITE(json_inject_suite);
  RUN_SUITE(json_extract_suite);
};

int main(int argc, char **argv)
{
  GREATEST_MAIN_BEGIN();

  RUN_SUITE(json_inject_extract);

  GREATEST_MAIN_END();
}
