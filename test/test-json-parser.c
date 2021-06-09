TEST expect_stringify_equal_original(void)
{
    size_t size=0;
    char *str = orka_load_whole_file("json-data/discord-embed.json", &size);
    json_item_t *root = json_parse(str, size);
    struct sized_buffer sb = json_stringify(root, JSON_ANY);
    ASSERT_STRN_EQ(str, sb.start, sb.size);
    json_cleanup(root);
    free(sb.start);

    str = "{\"a\":12,\"ab\":481}";
    size = sizeof("{\"a\":12,\"ab\":481}");
    root = json_parse(str, size);
    sb = json_stringify(root, JSON_ANY);
    ASSERT_STRN_EQ(str, sb.start, sb.size);
    json_cleanup(root);
    free(sb.start);
    PASS();
}
