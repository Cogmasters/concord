/*
 * Copyright (C) 2016 Gustavo Sverzut Barbieri
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef BEARSSL
#include <bearssl_hash.h>

static void
_cws_sha1(const void *input, const size_t input_len, void *output)
{
    br_sha1_context cxt;
    br_sha1_init(&cxt);
    br_sha1_update(&cxt, input, input_len);
    br_sha1_out(&cxt, output);
}
#elif defined(MBEDTLS)
#include "mbedtls/sha1.h"
static void
_cws_sha1(const void *input, const size_t input_len, void *output)
{
    mbedtls_sha1(input, input_len, output);
}
#elif defined(WOLFSSL)
#include <stdint.h>
#include "wolfssl/wolfcrypt/sha.h"
static void
_cws_sha1(const void *input, const size_t input_len, void *output)
{
    Sha sha;
    wc_InitSha(&sha);
    wc_ShaUpdate(&sha, input, input_len);
    wc_ShaFinal(&sha, output);
}
#else

#include <openssl/evp.h>

static void
_cws_sha1(const void *input, const size_t input_len, void *output)
{
    static const EVP_MD *md = NULL;
    EVP_MD_CTX *ctx;

    ctx = EVP_MD_CTX_new();

    if (!md) {
        OpenSSL_add_all_digests();
        md = EVP_get_digestbyname("sha1");
    }

    EVP_MD_CTX_init(ctx);
    EVP_DigestInit_ex(ctx, md, NULL);

    EVP_DigestUpdate(ctx, input, input_len);
    EVP_DigestFinal_ex(ctx, output, NULL);

    EVP_MD_CTX_free(ctx);
}

#endif

static inline void
_cws_debug(const char *prefix, const void *buffer, size_t len)
{
    const uint8_t *bytes = buffer;
    size_t i;
    if (prefix)
        fprintf(stderr, "%s:", prefix);
    for (i = 0; i < len; i++) {
        uint8_t b = bytes[i];
        if (isprint(b))
            fprintf(stderr, " %#04x(%c)", b, b);
        else
            fprintf(stderr, " %#04x", b);
    }
    if (prefix)
        fprintf(stderr, "\n");
}

static void
_cws_encode_base64(const uint8_t *input, const size_t input_len, char *output)
{
    static const char base64_map[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    size_t i, o;
    uint8_t c;

    for (i = 0, o = 0; i + 3 <= input_len; i += 3) {
        c = (input[i] & (((1 << 6) - 1) << 2)) >> 2;
        output[o++] = base64_map[c];

        c = (input[i] & ((1 << 2) - 1)) << 4;
        c |= (input[i + 1] & (((1 << 4) - 1) << 4)) >> 4;
        output[o++] = base64_map[c];

        c = (input[i + 1] & ((1 << 4) - 1)) << 2;
        c |= (input[i + 2] & (((1 << 2) - 1) << 6)) >> 6;
        output[o++] = base64_map[c];

        c = input[i + 2] & ((1 << 6) - 1);
        output[o++] = base64_map[c];
    }

    if (i + 1 == input_len) {
        c = (input[i] & (((1 << 6) - 1) << 2)) >> 2;
        output[o++] = base64_map[c];

        c = (input[i] & ((1 << 2) - 1)) << 4;
        output[o++] = base64_map[c];

        output[o++] = base64_map[64];
        output[o++] = base64_map[64];
    } else if (i + 2 == input_len) {
        c = (input[i] & (((1 << 6) - 1) << 2)) >> 2;
        output[o++] = base64_map[c];

        c = (input[i] & ((1 << 2) - 1)) << 4;
        c |= (input[i + 1] & (((1 << 4) - 1) << 4)) >> 4;
        output[o++] = base64_map[c];

        c = (input[i + 1] & ((1 << 4) - 1)) << 2;
        output[o++] = base64_map[c];

        output[o++] = base64_map[64];
    }
}

static void
_cws_get_random(void *buffer, size_t len)
{
    uint8_t *bytes = buffer;
    uint8_t *bytes_end = bytes + len;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd >= 0) {
        do {
            ssize_t r = read(fd, bytes, bytes_end - bytes);
            if (r < 0) {
                close(fd);
                goto fallback;
            }
            bytes += r;
        } while (bytes < bytes_end);
        close(fd);
    } else {
      fallback:
        for (; bytes < bytes_end; bytes++)
            *bytes = random() & 0xff;
    }
}

static inline void
_cws_trim(const char **p_buffer, size_t *p_len)
{
    const char *buffer = *p_buffer;
    size_t len = *p_len;

    while (len > 0 && isspace(buffer[0])) {
        buffer++;
        len--;
    }

    while (len > 0 && isspace(buffer[len - 1]))
        len--;

    *p_buffer = buffer;
    *p_len = len;
}

static inline bool
_cws_header_has_prefix(const char *buffer, const size_t buflen, const char *prefix)
{
    const size_t prefixlen = strlen(prefix);
    if (buflen < prefixlen)
        return false;
    return strncasecmp(buffer, prefix, prefixlen) == 0;
}

static inline void
_cws_hton(void *mem, uint8_t len)
{
#if __BYTE_ORDER__ != __BIG_ENDIAN
    uint8_t *bytes;
    uint8_t i, mid;

    if (len % 2) return;

    mid = len / 2;
    bytes = mem;
    for (i = 0; i < mid; i++) {
        uint8_t tmp = bytes[i];
        bytes[i] = bytes[len - i - 1];
        bytes[len - i - 1] = tmp;
    }
#endif
}

static inline void
_cws_ntoh(void *mem, uint8_t len)
{
#if __BYTE_ORDER__ != __BIG_ENDIAN
    uint8_t *bytes;
    uint8_t i, mid;

    if (len % 2) return;

    mid = len / 2;
    bytes = mem;
    for (i = 0; i < mid; i++) {
        uint8_t tmp = bytes[i];
        bytes[i] = bytes[len - i - 1];
        bytes[len - i - 1] = tmp;
    }
#endif
}
