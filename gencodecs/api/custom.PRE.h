/** @CCORD_pub_list{strings} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(strings)
    LISTTYPE_PTR(char, *)
LIST_END
#endif

/** @CCORD_pub_list{json_values} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(json_values)
    LISTTYPE_PTR(json_char, *)
LIST_END
#endif

/** @CCORD_pub_list{snowflakes} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(snowflakes)
    LISTTYPE(u64snowflake)
LIST_END
#endif

/** @CCORD_pub_list{bitmasks} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(bitmasks)
    LISTTYPE(u64bitmask)
LIST_END
#endif

/** @CCORD_pub_list{integers} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(integers)
    LISTTYPE(int)
LIST_END
#endif
