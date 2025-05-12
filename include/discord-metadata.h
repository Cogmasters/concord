#ifndef DISCORD_METADATA_H
#define DISCORD_METADATA_H

#include "mida.h"

typedef struct discord_metadata {
    size_t size; /**< size of the data */
    size_t length; /**< length of the data */
} DiscordMD;

#define DISCORD_METADATA(_data) MIDA(DiscordMD, _data)

void *__discord_metadata_injection(void *data,
                                   const size_t size,
                                   const size_t length);

#define discord_malloc(_count, _element_size)                                 \
    __discord_metadata_injection(                                             \
        mida_malloc(DiscordMD, _count, _element_size), _count *_element_size, \
        _count)

#define discord_calloc(_count, _element_size)                                 \
    __discord_metadata_injection(                                             \
        mida_calloc(DiscordMD, _count, _element_size), _count *_element_size, \
        _count)

#define discord_realloc(_base, _count, _element_size)                         \
    __discord_metadata_injection(                                             \
        mida_realloc(DiscordMD, _base, _count, _element_size),                \
        _count *_element_size, _count)

#define discord_free(_data) mida_free(DiscordMD, _data)

#define discord_primitives(_type, ...)                                        \
    (_type *)__discord_metadata_injection(                                    \
        mida_array(DiscordMD, __VA_ARGS__), sizeof((_type[])__VA_ARGS__),     \
        sizeof((_type[])__VA_ARGS__) / sizeof(_type))

#define discord_array(_type, ...)                                             \
    (struct discord_##_type *)__discord_metadata_injection(                   \
        mida_array(struct discord_##_type, __VA_ARGS__),                      \
        sizeof((struct discord_##_type[])__VA_ARGS__),                        \
        sizeof((struct discord_##_type[])__VA_ARGS__)                         \
            / sizeof(struct discord_##_type))

#define discord_struct(_type, ...) discord_array(_type, { __VA_ARGS__ })

#define discord_wrap(_data, _length)                                          \
    __discord_metadata_injection(                                             \
        mida_wrap(DiscordMD, _data, mida_bytemap(DiscordMD, sizeof(_data))),  \
        sizeof(_data), _length)

#define discord_length(_data) (const size_t)(DISCORD_METADATA(_data)->length)

#define discord_size(_data) (const size_t)(DISCORD_METADATA(_data)->size)

#endif /* DISCORD_METADATA_H */
