PUB_LIST(strings)
    LISTTYPE_PTR(char, *)
LIST_END

PUB_LIST(json_values)
    LISTTYPE_PTR(json_char, *)
LIST_END

PUB_LIST(snowflakes)
    LISTTYPE(u64snowflake)
LIST_END

PUB_LIST(integers)
    LISTTYPE(int)
LIST_END
