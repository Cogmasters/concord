#ifdef REFLECTC_PRE_HOOKS
/*#!
#include <inttypes.h>
#include <stdbool.h>
#include "carray.h"
#include "cog-utils.h"
#include "types.h"
#include "concord-error.h"
#define CONCORD_OPTIONAL (1 << 0ull)
#define CONCORD_NO_JSON  (1 << 1ull)
*/
#endif

PUBLIC(struct, strings, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, _, char, **, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, json_values, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, _, json_char, **, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, snowflakes, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, _, u64snowflake, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, bitmasks, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, _, u64bitmask, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, integers, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, _, int, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

#ifdef REFLECTC_POST_HOOKS
/*#!
#define reflectc_wrap(_symbol)        reflectc_wrap

enum {
    REFLECTC_TYPES(u64unix_ms) = REFLECTC_TYPES(EXTEND),
    REFLECTC_TYPES(u64snowflake),
    REFLECTC_TYPES(u64bitmask),
    REFLECTC_TYPES(json_char),
    REFLECTC_TYPES(size_t)
};
*/
#endif
