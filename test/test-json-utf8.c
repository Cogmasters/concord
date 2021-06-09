#define A "Íñdîæ"
#define B "m\u00fcller"
#define C "的"
#define D "😊"
#define UTF8_JSON "{\"a\":\""A"\",\"b\":\""B"\",\"c\":\""C"\",\"d\":\""D"\"}"

TEST expect_doubly_encoded_equal_original(void) 
{
  char a[16], b[16], c[16], d[16];
  json_extract(UTF8_JSON, sizeof(UTF8_JSON), \
      "(a):s,(b):s,(c):s,(d):s", a, b, c, d);
  ASSERT_STR_EQ(A, a);
  ASSERT_STR_EQ(B, b);
  ASSERT_STR_EQ(C, c);
  ASSERT_STR_EQ(D, d);

  char payload[4096];
  json_inject(payload, sizeof(payload), \
      "(a):s,(b):s,(c):s,(d):s", a, b, c, d);
  ASSERT_STR_EQ(UTF8_JSON, payload);
  PASS();
}
