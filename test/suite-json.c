#include "json-actor.h"
#include "json-scanf.h"

SUITE(json);

#include "test-json-utf8.c"
#include "test-json-string.c"
#include "test-json-parser.c"

GREATEST_SUITE(json) {
  RUN_TEST(expect_doubly_encoded_equal_original);
  RUN_TEST(expect_unescaped_equal_original);
  RUN_TEST(expect_escaped_equal_original);
  RUN_TEST(expect_stringify_equal_original);
};
