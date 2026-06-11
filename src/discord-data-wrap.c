#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord_codecs.h"
#include "cog-utils.h"

static bool
_is_zero(const void *ptr, size_t size)
{
    static const unsigned char zeros[sizeof(long double)] = { 0 };
    return !ptr || memcmp(ptr, zeros, size) == 0;
}

static bool
_is_optional(const struct discord_data_wrap *member)
{
    return member && (member->tmpl->attrs & CONCORD_OPTIONAL);
}

// TODO: temporary until lists are refactored
static bool
_is_list_type(const struct discord_data_wrap *member)
{
    if (member->tmpl->type != REFLECTC_TYPES(struct)) return false;
    if (member->members.length != 3) return false;

    const struct discord_data_wrap *size_field = &member->members.array[0];
    const struct discord_data_wrap *array_field = &member->members.array[1];
    const struct discord_data_wrap *realsize_field = &member->members.array[2];

    if (size_field->tmpl->name.length != 4
        || memcmp(size_field->tmpl->name.buf, "size", 4) != 0)
        return false;
    if (array_field->tmpl->name.length != 5
        || memcmp(array_field->tmpl->name.buf, "array", 5) != 0)
        return false;
    if (realsize_field->tmpl->name.length != 8
        || memcmp(realsize_field->tmpl->name.buf, "realsize", 8) != 0)
        return false;

    if (size_field->tmpl->type != REFLECTC_TYPES(int)) return false;
    if (realsize_field->tmpl->type != REFLECTC_TYPES(int)) return false;

    if (reflectc_get_pointer_depth(array_field) < 2) return false;

    return true;
}

static bool
_is_list_empty(const struct discord_data_wrap *member)
{
    if (!_is_list_type(member)) return false;

    const struct discord_data_wrap *size_field = &member->members.array[0];
    const int *size_ptr = (const int *)reflectc_get(size_field);
    return size_ptr && *size_ptr == 0;
}

static bool
_optional_should_skip(const struct discord_data_wrap *member)
{
    if (!_is_optional(member)) return false;

    unsigned depth = reflectc_get_pointer_depth(member);
    if (depth >= 2 && reflectc_is_null(member)) {
        return true;
    }

    if (depth < 2) {
        if (_is_list_empty(member)) return true;
        const void *value = reflectc_get(member);
        if (_is_zero(value, member->tmpl->size)) return true;
    }

    if (depth == 2 && member->tmpl->type == REFLECTC_TYPES(struct)
        && !reflectc_is_null(member))
    {
        const void *resolved = reflectc_resolve(member);
        if (resolved && member->members.length > 0 && _is_list_type(member)) {
            const struct discord_data_wrap *size_field =
                &member->members.array[0];
            const int *size_ptr = (const int *)reflectc_get(size_field);
            if (size_ptr && *size_ptr == 0) return true;
        }
    }

    return false;
}

static CCORDcode
_ensure_ptr_struct_allocated(const struct discord_data_wrap *member,
                             void **out_resolved)
{
    if (reflectc_get_pointer_depth(member) < 2) {
        if (out_resolved) *out_resolved = (void *)reflectc_resolve(member);
        return CCORD_OK;
    }

    void *resolved = (void *)reflectc_resolve(member);
    if (!resolved) {
        if (!member->tmpl->from_cb || !member->registry) {
            return CCORD_INTERNAL_ERROR;
        }

        struct discord_data_wrap *temp_wrap =
            member->tmpl->from_cb(member->registry, NULL, NULL);
        if (!temp_wrap || !temp_wrap->tmpl) {
            return CCORD_INTERNAL_ERROR;
        }

        resolved = calloc(1, temp_wrap->tmpl->size);
        free(temp_wrap);
        if (!resolved) return CCORD_OUT_OF_MEMORY;

        memcpy((void *)member->ptr_value, &resolved, sizeof(void *));
    }

    if (out_resolved) *out_resolved = resolved;
    return CCORD_OK;
}

static void
_set_list_sizes(struct discord_data_wrap *list_wrap, int value)
{
    if (!list_wrap) return;
    if (list_wrap->members.length >= 1) {
        struct discord_data_wrap *size_field =
            (struct discord_data_wrap *)&list_wrap->members.array[0];
        reflectc_set(size_field, &value, sizeof(value));
    }
    if (list_wrap->members.length >= 3) {
        struct discord_data_wrap *realsize_field =
            (struct discord_data_wrap *)&list_wrap->members.array[2];
        reflectc_set(realsize_field, &value, sizeof(value));
    }
}

static CCORDcode
_list_elem_size(const struct discord_data_wrap *array_field,
                struct reflectc *registry,
                size_t *out_size)
{
    if (!array_field || !array_field->tmpl || !out_size) {
        return CCORD_INTERNAL_ERROR;
    }

    size_t elem_size = array_field->tmpl->size;
    unsigned depth = reflectc_get_pointer_depth(array_field);

    if (array_field->tmpl->type == REFLECTC_TYPES(struct)
        && array_field->tmpl->from_cb)
    {
        struct discord_data_wrap *temp_wrap =
            array_field->tmpl->from_cb(registry, NULL, NULL);
        if (!temp_wrap || !temp_wrap->tmpl) {
            return CCORD_INTERNAL_ERROR;
        }
        elem_size = temp_wrap->tmpl->size;
        free(temp_wrap);
    }
    else if (depth >= 2) {
        if (array_field->tmpl->type == REFLECTC_TYPES(char)) {
            elem_size = sizeof(char *);
        }
        else {
            switch ((int)array_field->tmpl->type) {
            case REFLECTC_TYPES(bool):
                elem_size = sizeof(bool);
                break;
            case REFLECTC_TYPES(short):
                elem_size = sizeof(short);
                break;
            case REFLECTC_TYPES(int):
                elem_size = sizeof(int);
                break;
            case REFLECTC_TYPES(long):
                elem_size = sizeof(long);
                break;
            case REFLECTC_TYPES(size_t):
                elem_size = sizeof(size_t);
                break;
            case REFLECTC_TYPES(float):
                elem_size = sizeof(float);
                break;
            case REFLECTC_TYPES(double):
                elem_size = sizeof(double);
                break;
            case REFLECTC_TYPES(enum):
                elem_size = sizeof(int);
                break;
            case REFLECTC_TYPES(u64snowflake):
            case REFLECTC_TYPES(u64bitmask):
            case REFLECTC_TYPES(u64unix_ms):
                elem_size = sizeof(uint64_t);
                break;
            default:
                break;
            }
        }
    }

    *out_size = elem_size;
    return CCORD_OK;
}

static CCORDcode
_get_list_wrap_for_member(const struct discord_data_wrap *member,
                          struct discord_data_wrap **out_wrap,
                          bool *out_needs_cleanup)
{
    if (!out_wrap || !out_needs_cleanup) return CCORD_INTERNAL_ERROR;

    *out_wrap = NULL;
    *out_needs_cleanup = false;

    if (!member || member->tmpl->type != REFLECTC_TYPES(struct)) {
        return CCORD_OK;
    }

    unsigned depth = reflectc_get_pointer_depth(member);
    if (depth >= 2) {
        void *resolved = NULL;
        CCORDcode alloc_code = _ensure_ptr_struct_allocated(member, &resolved);
        if (alloc_code != CCORD_OK) return alloc_code;
        if (!member->tmpl->from_cb || !member->registry) {
            return CCORD_INTERNAL_ERROR;
        }
        struct discord_data_wrap *wrap =
            member->tmpl->from_cb(member->registry, resolved, NULL);
        if (!wrap) return CCORD_INTERNAL_ERROR;
        *out_wrap = wrap;
        *out_needs_cleanup = true;
        return CCORD_OK;
    }

    if (member->members.length == 0) {
        if (!reflectc_expand(member->registry,
                             (struct discord_data_wrap *)member))
        {
            return CCORD_INTERNAL_ERROR;
        }
    }

    *out_wrap = (struct discord_data_wrap *)member;
    return CCORD_OK;
}

static CCORDcode
_jsonbcode_to_ccord(jsonbcode code)
{
    if (code >= JSONB_OK) {
        return CCORD_OK;
    }
    switch (code) {
    case JSONB_ERROR_NOMEM:
        return CCORD_OUT_OF_MEMORY;
    case JSONB_ERROR_OVERFLOW:
    case JSONB_ERROR_STACK:
    case JSONB_ERROR_INPUT:
    default:
        return CCORD_BAD_ENCODE;
    }
}

static CCORDcode
_jsonb_write_unix_ms(struct jsonb *jb,
                     char *p_buf[],
                     size_t *p_bufsize,
                     uint64_t value)
{
    char iso[32];
    const int iso_len = cog_unix_ms_to_iso8601(iso, sizeof(iso), value);
    if (iso_len > 0) {
        jsonbcode code =
            jsonb_string_auto(jb, p_buf, p_bufsize, iso, (size_t)iso_len);
        return _jsonbcode_to_ccord(code);
    }

    char numstr[32];
    snprintf(numstr, sizeof(numstr), "%" PRIu64, value);
    jsonbcode code =
        jsonb_string_auto(jb, p_buf, p_bufsize, numstr, strlen(numstr));
    return _jsonbcode_to_ccord(code);
}

static bool
_parse_u64_string(const char *json, size_t len, uint64_t *out)
{
    return cog_strtou64((char *)json, len, out);
}

static bool
_parse_u64unix_ms_string(const char *json, size_t len, uint64_t *out)
{
    return cog_iso8601_to_unix_ms(json, len, out)
           || _parse_u64_string(json, len, out);
}

static CCORDcode
_jsonb_write_list_element(struct jsonb *jb,
                          const struct discord_data_wrap *array_field,
                          const void *elem_ptr,
                          char *p_buf[],
                          size_t *p_bufsize)
{
    const struct reflectc_template *tmpl = array_field->tmpl;
    jsonbcode code;

    if (!tmpl) return CCORD_INTERNAL_ERROR;

    switch ((int)tmpl->type) {
    case REFLECTC_TYPES(bool): {
        const bool value = *(const bool *)elem_ptr;
        code = jsonb_bool_auto(jb, p_buf, p_bufsize, value);
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(float): {
        const float value = *(const float *)elem_ptr;
        code = jsonb_number_auto(jb, p_buf, p_bufsize, value);
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(double): {
        const double value = *(const double *)elem_ptr;
        code = jsonb_number_auto(jb, p_buf, p_bufsize, value);
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(enum):
    case REFLECTC_TYPES(short):
    case REFLECTC_TYPES(int):
    case REFLECTC_TYPES(size_t):
    case REFLECTC_TYPES(long): {
        long long value = 0ULL;
        memcpy(&value, elem_ptr, tmpl->size);
        code = jsonb_number_auto(jb, p_buf, p_bufsize, (double)value);
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(char): {
        unsigned depth = reflectc_get_pointer_depth(array_field);
        if (depth >= 2) {
            const char *str = *(char *const *)elem_ptr;
            if (!str) {
                code = jsonb_null_auto(jb, p_buf, p_bufsize);
            }
            else {
                code =
                    jsonb_string_auto(jb, p_buf, p_bufsize, str, strlen(str));
            }
            return _jsonbcode_to_ccord(code);
        }
        else {
            const char value = *(const char *)elem_ptr;
            code = jsonb_number_auto(jb, p_buf, p_bufsize, (double)value);
            return _jsonbcode_to_ccord(code);
        }
    }
    case REFLECTC_TYPES(u64unix_ms): {
        uint64_t value = 0ULL;
        memcpy(&value, elem_ptr, sizeof(value));
        return _jsonb_write_unix_ms(jb, p_buf, p_bufsize, value);
    }
    default: {
        if (tmpl->size == sizeof(uint64_t)) {
            uint64_t value = 0ULL;
            memcpy(&value, elem_ptr, sizeof(value));
            char numstr[32];
            snprintf(numstr, sizeof(numstr), "%" PRIu64, value);
            code =
                jsonb_token_auto(jb, p_buf, p_bufsize, numstr, strlen(numstr));
            return _jsonbcode_to_ccord(code);
        }
        code = jsonb_null_auto(jb, p_buf, p_bufsize);
        return _jsonbcode_to_ccord(code);
    }
    }
}

static CCORDcode
_json_parse_list_element(const struct discord_data_wrap *array_field,
                         struct reflectc *registry,
                         const jsmnf_pair *elem,
                         const char *json,
                         size_t length,
                         void *elem_ptr)
{
    if (!array_field || !array_field->tmpl || !elem) return CCORD_OK;

    if (array_field->tmpl->type == REFLECTC_TYPES(struct)
        && array_field->tmpl->from_cb)
    {
        struct reflectc *ctx = registry ? registry : array_field->registry;
        struct discord_data_wrap *elem_wrap =
            array_field->tmpl->from_cb(ctx, elem_ptr, NULL);
        if (!elem_wrap) return CCORD_INTERNAL_ERROR;
        CCORDcode code =
            discord_data_wrap_from_jsmnf(elem, json, length, elem_wrap);
        reflectc_cleanup(ctx, elem_wrap);
        return code;
    }

    switch (elem->v->type) {
    case JSMN_STRING: {
        unsigned depth = reflectc_get_pointer_depth(array_field);
        if (array_field->tmpl->type == REFLECTC_TYPES(char) && depth >= 2) {
            char **slot = (char **)elem_ptr;
            if (!slot) return CCORD_INTERNAL_ERROR;
            size_t len = (size_t)(elem->v->end - elem->v->start);
            if (!*slot) {
                *slot = calloc(1u, len + 1u);
                if (!*slot) return CCORD_OUT_OF_MEMORY;
            }
            memcpy(*slot, json + elem->v->start, len);
            (*slot)[len] = '\0';
            return CCORD_OK;
        }
        if ((int)array_field->tmpl->type == (int)REFLECTC_TYPES(u64unix_ms)
            && (depth == 1 || depth >= 2))
        {
            uint64_t value = 0;
            const size_t len = (size_t)(elem->v->end - elem->v->start);
            if (_parse_u64unix_ms_string(json + elem->v->start, len, &value)) {
                memcpy(elem_ptr, &value, sizeof(value));
            }
            return CCORD_OK;
        }
        if (array_field->tmpl->size == sizeof(uint64_t)
            && ((int)array_field->tmpl->type
                    == (int)REFLECTC_TYPES(u64bitmask)
                || (int)array_field->tmpl->type
                       == (int)REFLECTC_TYPES(u64snowflake))
            && (depth == 1 || depth >= 2))
        {
            uint64_t value = 0;
            if (_parse_u64_string(json + elem->v->start,
                                  (size_t)(elem->v->end - elem->v->start),
                                  &value))
            {
                memcpy(elem_ptr, &value, sizeof(value));
            }
            return CCORD_OK;
        }
        return CCORD_OK;
    }
    case JSMN_PRIMITIVE: {
        switch (json[elem->v->start]) {
        case 't':
        case 'f': {
            const bool value = json[elem->v->start] == 't';
            if (array_field->tmpl->type == REFLECTC_TYPES(bool)) {
                memcpy(elem_ptr, &value, sizeof(value));
            }
            return CCORD_OK;
        }
        case 'n':
            return CCORD_OK;
        default: {
            switch ((int)array_field->tmpl->type) {
            case REFLECTC_TYPES(u64bitmask):
            case REFLECTC_TYPES(u64snowflake):
            case REFLECTC_TYPES(u64unix_ms): {
                uint64_t value =
                    (uint64_t)strtoull(json + elem->v->start, NULL, 10);
                memcpy(elem_ptr, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(float): {
                const float value = strtof(json + elem->v->start, NULL);
                memcpy(elem_ptr, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(double): {
                const double value = strtod(json + elem->v->start, NULL);
                memcpy(elem_ptr, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(int): {
                const int value = (int)strtol(json + elem->v->start, NULL, 10);
                memcpy(elem_ptr, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(enum): {
                const int value = (int)strtol(json + elem->v->start, NULL, 10);
                memcpy(elem_ptr, &value, array_field->tmpl->size);
            } break;
            case REFLECTC_TYPES(long): {
                const long value = strtol(json + elem->v->start, NULL, 10);
                memcpy(elem_ptr, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(size_t): {
                const size_t value =
                    (size_t)strtoull(json + elem->v->start, NULL, 10);
                memcpy(elem_ptr, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(short): {
                const short value =
                    (short)strtol(json + elem->v->start, NULL, 10);
                memcpy(elem_ptr, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(char): {
                const char value =
                    (char)strtol(json + elem->v->start, NULL, 10);
                memcpy(elem_ptr, &value, sizeof(value));
            } break;
            default:
                break;
            }
            return CCORD_OK;
        }
        }
    }
    default:
        return CCORD_OK;
    }
}

CCORDcode
discord_data_wrap_to_jsonb(struct jsonb *jb,
                           const struct discord_data_wrap *member,
                           char *p_buf[],
                           size_t *p_bufsize)
{
    if (_optional_should_skip(member)) {
        return JSONB_OK;
    }
    if (reflectc_is_null(member)) {
        jsonbcode code = jsonb_null_auto(jb, p_buf, p_bufsize);
        return _jsonbcode_to_ccord(code);
    }

    const void *value = reflectc_get(member);

    switch ((int)member->tmpl->type) {
    case REFLECTC_TYPES(char): {
        const char *resolved = (const char *)value;
        if (!resolved) {
            break;
        }
        jsonbcode code = jsonb_string_auto(jb, p_buf, p_bufsize, resolved,
                                           strlen(resolved));
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(json_char): {
        /* raw-JSON passthrough: emit the buffer as a bare token,
         * matching the legacy codecs' jsonb_token behavior; an empty
         * buffer would be an invalid token, emit null instead */
        const char *resolved = (const char *)value;
        jsonbcode code;
        if (!resolved) {
            break;
        }
        if (!*resolved) {
            code = jsonb_null_auto(jb, p_buf, p_bufsize);
        }
        else {
            code = jsonb_token_auto(jb, p_buf, p_bufsize, resolved,
                                    strlen(resolved));
        }
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(enum):
    case REFLECTC_TYPES(short):
    case REFLECTC_TYPES(int):
    case REFLECTC_TYPES(size_t):
    case REFLECTC_TYPES(long): {
        long long resolved = 0ULL;
        memcpy(&resolved, value, member->tmpl->size);
        jsonbcode code =
            jsonb_number_auto(jb, p_buf, p_bufsize, (double)resolved);
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(float): {
        const float resolved = *(const float *)value;
        jsonbcode code =
            jsonb_number_auto(jb, p_buf, p_bufsize, (float)resolved);
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(double): {
        const double resolved = *(const double *)value;
        jsonbcode code = jsonb_number_auto(jb, p_buf, p_bufsize, resolved);
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(bool): {
        const bool resolved = *(const bool *)value;
        if (resolved == false && _is_optional(member)) {
            break;
        }
        jsonbcode code = jsonb_bool_auto(jb, p_buf, p_bufsize, resolved);
        return _jsonbcode_to_ccord(code);
    }
    case REFLECTC_TYPES(u64unix_ms): {
        uint64_t resolved = 0ULL;
        memcpy(&resolved, value, sizeof(resolved));
        return _jsonb_write_unix_ms(jb, p_buf, p_bufsize, resolved);
    }
    case REFLECTC_TYPES(struct): {
        jsonbcode code;
        /* lazily hydrate, mirroring the decode path: a registry-cached
         * wrap may not have this member's children populated yet */
        if (member->members.length == 0 && member->registry
            && reflectc_resolve(member))
        {
            reflectc_expand(member->registry, member);
        }
        if (_is_list_type(member)) {
            const struct discord_data_wrap *size_field =
                &member->members.array[0];
            const struct discord_data_wrap *array_field =
                &member->members.array[1];
            const int *size_ptr = (const int *)reflectc_get(size_field);
            const size_t size =
                (size_ptr && *size_ptr > 0) ? (size_t)*size_ptr : 0u;
            const char *array_ptr = (const char *)reflectc_get(array_field);
            size_t elem_size = 0;

            if (size > 0 && array_ptr) {
                CCORDcode elem_size_code =
                    _list_elem_size(array_field, member->registry, &elem_size);
                if (elem_size_code != CCORD_OK) {
                    return elem_size_code;
                }
            }

            code = jsonb_array_auto(jb, p_buf, p_bufsize);
            if (code < JSONB_OK) {
                return _jsonbcode_to_ccord(code);
            }

            for (size_t i = 0; i < size && array_ptr; ++i) {
                const void *elem_ptr = array_ptr + (i * elem_size);

                if (array_field->tmpl->type == REFLECTC_TYPES(struct)
                    && array_field->tmpl->from_cb)
                {
                    struct discord_data_wrap *elem_wrap =
                        array_field->tmpl->from_cb(NULL, (void *)elem_ptr,
                                                   NULL);
                    if (!elem_wrap) {
                        return CCORD_INTERNAL_ERROR;
                    }
                    code = discord_data_wrap_to_jsonb(jb, elem_wrap, p_buf,
                                                      p_bufsize);
                    reflectc_cleanup(NULL, elem_wrap);
                    if (code < JSONB_OK) {
                        return _jsonbcode_to_ccord(code);
                    }
                }
                else {
                    CCORDcode elem_code = _jsonb_write_list_element(
                        jb, array_field, elem_ptr, p_buf, p_bufsize);
                    if (elem_code != CCORD_OK) {
                        return elem_code;
                    }
                }
            }

            code = jsonb_array_pop_auto(jb, p_buf, p_bufsize);
            return _jsonbcode_to_ccord(code);
        }
        if (reflectc_length(member) > 1) {
            code = jsonb_array_auto(jb, p_buf, p_bufsize);
            if (code < JSONB_OK) {
                return _jsonbcode_to_ccord(code);
            }
            for (size_t i = 0; i < member->length; ++i) {
                code = discord_data_wrap_to_jsonb(
                    jb, &member->members.array[i], p_buf, p_bufsize);
                if (code < JSONB_OK) {
                    return _jsonbcode_to_ccord(code);
                }
            }
            code = jsonb_array_pop_auto(jb, p_buf, p_bufsize);
            return _jsonbcode_to_ccord(code);
        }
        else {
            code = jsonb_object_auto(jb, p_buf, p_bufsize);
            if (code < JSONB_OK) {
                return _jsonbcode_to_ccord(code);
            }
            for (size_t i = 0; i < member->members.length; ++i) {
                const struct discord_data_wrap *f = &member->members.array[i];
                if (_optional_should_skip(f)) continue;
                /* struct-only fields (e.g. audit-log reason: sent as the
                 * X-Audit-Log-Reason header) never enter the JSON body */
                if (f->tmpl->attrs & CONCORD_NO_JSON) continue;

                /* unset (NULL) strings are omitted; empty strings are
                 * legitimate values and encode as "" */
                if ((f->tmpl->type == REFLECTC_TYPES(char)
                     || (int)f->tmpl->type == (int)REFLECTC_TYPES(json_char))
                    && reflectc_get_pointer_depth(f) >= 2)
                {
                    const char *resolved = (const char *)reflectc_get(f);
                    if (!resolved) {
                        continue;
                    }
                }

                /* serialized name: recipe alias when declared (e.g.
                 * muted -> "mute"), the C member name otherwise */
                size_t key_len;
                const char *key_name = reflectc_alias(f, &key_len);
                if ((code = jsonb_key_auto(jb, p_buf, p_bufsize, key_name,
                                           key_len))
                    < JSONB_OK)
                {
                    return _jsonbcode_to_ccord(code);
                }
                if ((code =
                         discord_data_wrap_to_jsonb(jb, f, p_buf, p_bufsize))
                    < JSONB_OK)
                {
                    return _jsonbcode_to_ccord(code);
                }
            }
            code = jsonb_object_pop_auto(jb, p_buf, p_bufsize);
            return _jsonbcode_to_ccord(code);
        }
    } break;
    case REFLECTC_TYPES(union):
    default: {
        if (member->tmpl->size == sizeof(uint64_t)) {
            uint64_t resolved = 0ULL;
            memcpy(&resolved, value, sizeof(uint64_t));
            char numstr[32];
            snprintf(numstr, sizeof(numstr), "%" PRIu64, resolved);
            jsonbcode code = jsonb_string_auto(jb, p_buf, p_bufsize, numstr,
                                               strlen(numstr));
            return _jsonbcode_to_ccord(code);
        }
        jsonbcode code = jsonb_null_auto(jb, p_buf, p_bufsize);
        return _jsonbcode_to_ccord(code);
    }
    }
    return JSONB_OK;
}

CCORDcode
discord_data_wrap_to_json(const struct discord_data_wrap *root,
                          char *p_buf[],
                          size_t *p_bufsize)
{
    struct jsonb jb;
    jsonb_init(&jb);
    CCORDcode code = discord_data_wrap_to_jsonb(&jb, root, p_buf, p_bufsize);
    if (code == CCORD_OK && p_bufsize) {
        *p_bufsize = jb.pos;
    }
    return code;
}

static void
_json_parse_assign_null(const struct discord_data_wrap *member)
{
    unsigned depth = reflectc_get_pointer_depth(member);
    const void *value = NULL;

    if (depth < 2) {
        return;
    }
    memcpy((void *)member->ptr_value, &value, member->tmpl->size);
}

/* ── deep free ─────────────────────────────────────────────────────────
 * discord_data_wrap_from_json() allocates strings (reflectc_string),
 * nested structs (_ensure_ptr_struct_allocated) and list arrays; the
 * reflect-c wrap cleanup only releases wrap machinery.  These walkers
 * release the decoded data itself.  Contract (same as the legacy
 * generated _cleanup functions): every non-NULL pointer member is owned
 * and freed — never call this on hand-built structs pointing at
 * literals or stack objects. */

static void _data_deep_free_wrap(struct reflectc *registry,
                                 const struct discord_data_wrap *wrap);

static void
_data_deep_free_list(struct reflectc *registry,
                     const struct discord_data_wrap *list)
{
    const struct discord_data_wrap *size_field = &list->members.array[0];
    struct discord_data_wrap *array_field =
        (struct discord_data_wrap *)&list->members.array[1];
    const int *size_ptr = (const int *)reflectc_get(size_field);
    const int size = size_ptr ? *size_ptr : 0;
    char **array_slot = (char **)array_field->ptr_value;
    char *array_ptr = array_slot ? *array_slot : NULL;

    if (array_ptr && size > 0) {
        size_t elem_size = 0;
        if (_list_elem_size(array_field, registry, &elem_size) == CCORD_OK
            && elem_size > 0)
        {
            for (int i = 0; i < size; ++i) {
                void *elem_ptr = array_ptr + ((size_t)i * elem_size);
                switch ((int)array_field->tmpl->type) {
                case REFLECTC_TYPES(struct):
                    if (array_field->tmpl->from_cb) {
                        struct discord_data_wrap *w =
                            (struct discord_data_wrap *)
                                array_field->tmpl->from_cb(NULL, elem_ptr,
                                                           NULL);
                        if (w) {
                            _data_deep_free_wrap(registry, w);
                            reflectc_cleanup(NULL, w);
                        }
                    }
                    break;
                case REFLECTC_TYPES(char):
                case REFLECTC_TYPES(json_char):
                    if (reflectc_get_pointer_depth(array_field) >= 2) {
                        char **slot = (char **)elem_ptr;
                        free(*slot);
                        *slot = NULL;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    free(array_ptr);
    if (array_slot) *array_slot = NULL;
    _set_list_sizes((struct discord_data_wrap *)list, 0);
}

static void
_data_deep_free_wrap(struct reflectc *registry,
                     const struct discord_data_wrap *wrap)
{
    if (!wrap) return;

    for (size_t i = 0; i < wrap->members.length; ++i) {
        struct discord_data_wrap *m =
            (struct discord_data_wrap *)&wrap->members.array[i];
        const unsigned depth = reflectc_get_pointer_depth(m);

        if (!m->tmpl || !m->ptr_value) continue;

        /* embedded char buf[N] (depth counts dimensions): nothing owned */
        if (m->tmpl->dimensions.buf
            && strchr(m->tmpl->dimensions.buf, '['))
            continue;

        switch ((int)m->tmpl->type) {
        case REFLECTC_TYPES(char):
        case REFLECTC_TYPES(json_char):
            if (depth == 2) {
                char **slot = (char **)m->ptr_value;
                free(*slot);
                *slot = NULL;
            }
            break;
        case REFLECTC_TYPES(struct): {
            void *target = reflectc_resolve(m);
            if (!target) break;
            /* never descend through cached child wraps: their targets may
             * be stale (e.g. re-decoded in place); wrap the CURRENT
             * target fresh so every inner pointer read is live */
            if (m->tmpl->from_cb) {
                struct discord_data_wrap *w =
                    (struct discord_data_wrap *)m->tmpl->from_cb(NULL, target,
                                                                 NULL);
                if (w) {
                    if (_is_list_type(w)) {
                        _data_deep_free_list(registry, w);
                    }
                    else {
                        _data_deep_free_wrap(registry, w);
                    }
                    reflectc_cleanup(NULL, w);
                }
            }
            if (depth == 2) {
                void **slot = (void **)m->ptr_value;
                free(*slot);
                *slot = NULL;
            }
        } break;
        default:
            break;
        }
    }
}

void
discord_data_free(struct reflectc *registry, void *data)
{
    struct discord_data_wrap *w;

    if (!registry || !data) return;
    if (!(w = (struct discord_data_wrap *)reflectc_find(registry, data)))
        return;
    /* the root may itself be a list container (top-level array decode) */
    if (_is_list_type(w)) {
        _data_deep_free_list(registry, w);
    }
    else {
        _data_deep_free_wrap(registry, w);
    }
    reflectc_cleanup(registry, w);
}

void
discord_data_release(struct reflectc *registry, void *data)
{
    struct discord_data_wrap *w;

    if (!registry || !data) return;
    if (!(w = (struct discord_data_wrap *)reflectc_find(registry, data)))
        return;
    reflectc_cleanup(registry, w);
}

CCORDcode
discord_data_wrap_from_jsmnf(const struct jsmnf_pair *p,
                             const char *json,
                             size_t length,
                             const struct discord_data_wrap *member)
{
    if (!p || !member) {
        return CCORD_OK;
    }

    switch (p->v->type) {
    case JSMN_STRING: {
        unsigned depth = reflectc_get_pointer_depth(member);
        /* json_char*: raw-JSON passthrough; for strings the token span
         * excludes the quotes, matching the legacy codecs */
        if ((int)member->tmpl->type == (int)REFLECTC_TYPES(json_char)
            && depth == 2)
        {
            reflectc_string(member, json + p->v->start,
                            (size_t)(p->v->end - p->v->start));
            return CCORD_OK;
        }
        if (member->tmpl->type != REFLECTC_TYPES(char) || depth != 2) {
            if ((int)member->tmpl->type == (int)REFLECTC_TYPES(u64unix_ms)
                && depth == 1)
            {
                uint64_t value = 0;
                const size_t len = (size_t)(p->v->end - p->v->start);
                if (_parse_u64unix_ms_string(json + p->v->start, len, &value)) {
                    reflectc_set(member, &value, sizeof(value));
                }
                return CCORD_OK;
            }
            /* Handle numeric strings for u64 types (snowflakes, bitmasks) */
            if (member->tmpl->size == sizeof(uint64_t) && depth == 1) {
                uint64_t value = 0;
                if (_parse_u64_string(json + p->v->start,
                                      (size_t)(p->v->end - p->v->start),
                                      &value))
                {
                    reflectc_set(member, &value, sizeof(value));
                }
            }
            return CCORD_OK;
        }
        reflectc_string(member, json + p->v->start,
                        (size_t)(p->v->end - p->v->start));
        return CCORD_OK;
    }
    case JSMN_PRIMITIVE: {
        switch (json[p->v->start]) {
        case 't':
        case 'f': {
            const bool value = json[p->v->start] == 't';
            if (member->tmpl->type != REFLECTC_TYPES(bool)) {
                return CCORD_OK;
            }
            reflectc_set(member, &value, sizeof(value));
            return CCORD_OK;
        } break;
        case 'n':
            _json_parse_assign_null(member);
            return CCORD_OK;
        default: {
            switch ((int)member->tmpl->type) {
            case REFLECTC_TYPES(u64bitmask):
            case REFLECTC_TYPES(u64snowflake):
            case REFLECTC_TYPES(u64unix_ms): {
                uint64_t value =
                    (uint64_t)strtoull(json + p->v->start, NULL, 10);
                reflectc_set(member, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(float): {
                const float value = strtof(json + p->v->start, NULL);
                reflectc_set(member, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(double): {
                const double value = strtod(json + p->v->start, NULL);
                reflectc_set(member, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(int): {
                const int value = (int)strtol(json + p->v->start, NULL, 10);
                reflectc_set(member, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(enum): {
                const int value = (int)strtol(json + p->v->start, NULL, 10);
                reflectc_set(member, &value, member->tmpl->size);
            } break;
            case REFLECTC_TYPES(long): {
                const long value = strtol(json + p->v->start, NULL, 10);
                reflectc_set(member, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(size_t): {
                const size_t value =
                    (size_t)strtoull(json + p->v->start, NULL, 10);
                reflectc_set(member, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(json_char): {
                /* raw-JSON passthrough of the primitive token */
                if (reflectc_get_pointer_depth(member) == 2) {
                    reflectc_string(member, json + p->v->start,
                                    (size_t)(p->v->end - p->v->start));
                }
            } break;
            case REFLECTC_TYPES(short): {
                const short value =
                    (short)strtol(json + p->v->start, NULL, 10);
                reflectc_set(member, &value, sizeof(value));
            } break;
            case REFLECTC_TYPES(char): {
                const char value = (char)strtol(json + p->v->start, NULL, 10);
                reflectc_set(member, &value, sizeof(value));
            } break;
            default:
                return CCORD_OK;
            }
            return CCORD_OK;
        } break;
        }
    }
    case JSMN_OBJECT:
        if ((int)member->tmpl->type == (int)REFLECTC_TYPES(json_char)
            && reflectc_get_pointer_depth(member) == 2)
        {
            /* raw-JSON passthrough of the whole object */
            reflectc_string(member, json + p->v->start,
                            (size_t)(p->v->end - p->v->start));
            return CCORD_OK;
        }
        if (member->tmpl->type != REFLECTC_TYPES(struct)) {
            return CCORD_OK;
        }

        unsigned depth = reflectc_get_pointer_depth(member);
        if (depth >= 2) {
            CCORDcode alloc_code = _ensure_ptr_struct_allocated(member, NULL);
            if (alloc_code != CCORD_OK) return alloc_code;
        }
        if (depth >= 2 || member->members.length == 0) {
            if (!reflectc_expand(member->registry, member)) {
                return CCORD_INTERNAL_ERROR;
            }
        }

        for (size_t i = 0; i < p->capacity; ++i) {
            const size_t pos = reflectc_get_pos(member, p->buckets[i].key.buf,
                                                p->buckets[i].key.length);
            if (pos != SIZE_MAX) {
                if (member->members.array[pos].tmpl->attrs & CONCORD_NO_JSON)
                    continue;
                const jsmnf_pair *p_m = jsmnf_find(p, p->buckets[i].key.buf,
                                                   p->buckets[i].key.length);
                const struct discord_data_wrap *m =
                    member->members.array + pos;

                if (!p_m) {
                    _json_parse_assign_null(m);
                    continue;
                }
                CCORDcode code =
                    discord_data_wrap_from_jsmnf(p_m, json, length, m);
                if (code != CCORD_OK) {
                    return code;
                }
            }
        }
        return CCORD_OK;
    case JSMN_ARRAY: {
        if ((int)member->tmpl->type == (int)REFLECTC_TYPES(json_char)
            && reflectc_get_pointer_depth(member) == 2)
        {
            /* raw-JSON passthrough of the whole array */
            reflectc_string(member, json + p->v->start,
                            (size_t)(p->v->end - p->v->start));
            return CCORD_OK;
        }
        struct discord_data_wrap *list_wrap = NULL;
        bool needs_cleanup = false;
        CCORDcode wrap_code =
            _get_list_wrap_for_member(member, &list_wrap, &needs_cleanup);
        if (wrap_code != CCORD_OK) return wrap_code;

        if (!list_wrap) return CCORD_OK;

        if (p->length == 0) {
            if (_is_list_type(list_wrap)) {
                _set_list_sizes(list_wrap, 0);
            }
            if (needs_cleanup) {
                reflectc_cleanup(member->registry, list_wrap);
            }
            return CCORD_OK;
        }

        if (!_is_list_type(list_wrap)) {
            if (needs_cleanup) {
                reflectc_cleanup(member->registry, list_wrap);
            }
            return CCORD_OK;
        }

        if (list_wrap->members.length >= 2 && p->length > 0) {
            struct discord_data_wrap *array_field =
                (struct discord_data_wrap *)&list_wrap->members.array[1];

            size_t elem_size = 0;
            CCORDcode elem_size_code =
                _list_elem_size(array_field, member->registry, &elem_size);
            if (elem_size_code != CCORD_OK) return elem_size_code;
            void *array_ptr = calloc(p->length, elem_size);
            if (!array_ptr) {
                return CCORD_OUT_OF_MEMORY;
            }

            if (array_field->ptr_value) {
                memcpy((void *)array_field->ptr_value, &array_ptr,
                       sizeof(array_ptr));
            }
            else {
                return CCORD_INTERNAL_ERROR;
            }

            int array_size = (int)p->length;
            _set_list_sizes(list_wrap, array_size);

            for (size_t i = 0; i < p->length; ++i) {
                void *elem_ptr = (char *)array_ptr + (i * elem_size);
                CCORDcode code = _json_parse_list_element(
                    array_field, member->registry, &p->fields[i], json, length,
                    elem_ptr);
                if (code != CCORD_OK) {
                    if (needs_cleanup) {
                        reflectc_cleanup(member->registry, list_wrap);
                    }
                    return code;
                }
            }
        }
        if (needs_cleanup) {
            reflectc_cleanup(member->registry, list_wrap);
        }
    }
        return CCORD_OK;
    default:
        return CCORD_OK;
    }
    return CCORD_OK;
}

static CCORDcode
_jsmncode_to_ccord(long code)
{
    if (code > 0) {
        return CCORD_OK;
    }
    switch ((int)code) {
    case JSMN_ERROR_NOMEM:
        return CCORD_OUT_OF_MEMORY;
    case JSMN_ERROR_INVAL:
    case JSMN_ERROR_PART:
    default:
        return CCORD_BAD_DECODE;
    }
}

CCORDcode
discord_data_wrap_from_json(const char *json,
                            size_t len,
                            struct discord_data_wrap *root)
{
    jsmnf_table *pairs = NULL;
    size_t pairs_len = 0;
    jsmnf_loader l;
    jsmnf_init(&l);
    long code = jsmnf_load_auto(&l, json, len, &pairs, &pairs_len);
    if (code <= 0) {
        CCORDcode err = _jsmncode_to_ccord(code);
        free(pairs);
        return err;
    }
    CCORDcode result = discord_data_wrap_from_jsmnf(l.root, json, len, root);
    free(pairs);
    return result;
}
