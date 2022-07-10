/** @CCORD_pub_list{strings} */
PUB_LIST(strings)
    LISTTYPE_PTR(char, *)
LIST_END

/** @CCORD_pub_list{json_values} */
PUB_LIST(json_values)
    LISTTYPE_PTR(json_char, *)
LIST_END

/** @CCORD_pub_list{snowflakes} */
PUB_LIST(snowflakes)
    LISTTYPE(u64snowflake)
LIST_END

/** @CCORD_pub_list{integers} */
PUB_LIST(integers)
    LISTTYPE(int)
LIST_END
