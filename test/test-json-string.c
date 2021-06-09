TEST expect_unescaped_equal_original(void)
{
  char *str=NULL, *estr=NULL, *unstr=NULL;
  size_t size=0, estr_size=0, unstr_size=0;

  str = orka_load_whole_file("json-data/discord-embed.json", &size);
  estr = json_string_escape(&estr_size, str, size);
  json_string_unescape(&unstr, &unstr_size, estr, estr_size);
  ASSERT_EQ_FMT(size, unstr_size, "%zu");
  ASSERT_STRN_EQ(str, unstr, size);
  PASS();
}

TEST expect_escaped_equal_original(void)
{
  char str[] = {'\\', 'u', 'd', '8', '3', 'd',
                '\\', 'u', 'd', 'c', 'a', 'c',
                0};
  char *estr=NULL, *unstr=NULL;
  size_t size=strlen(str), estr_size=0, unstr_size=0;

  json_string_unescape(&unstr, &unstr_size, str, size);
  estr = json_string_escape(&estr_size, unstr, unstr_size);
  ASSERT_EQ_FMT(size, estr_size, "%zu");
  ASSERT_STRN_EQ(str, estr, size);
  PASS();
}
