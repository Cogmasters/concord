/**
 * Simple test for Discord gateway zlib decompression helper.
 *
 * This does not require a live Discord connection, it just verifies that
 * a buffer compressed with zlib can be decompressed back to its original
 * contents by the library helper.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zlib.h>

/* public header brings in all Discord core types */
#include "discord.h"

/* forward declaration of the internal helper we want to test */
bool discord_gateway_zlib_inflate(const void *compressed,
                                  size_t compressed_len,
                                  char **out,
                                  size_t *out_len);

int
main(void)
{
    const char json[] = "{\"op\":10,\"d\":{\"heartbeat_interval\":45000}}";
    const size_t json_len = sizeof(json) - 1;

    /* compress the JSON payload with zlib */
    z_stream def = { 0 };
    if (Z_OK != deflateInit(&def, Z_DEFAULT_COMPRESSION)) {
        fprintf(stderr, "Failed to initialize zlib deflate\n");
        return EXIT_FAILURE;
    }

    unsigned char comp_buf[256];
    def.next_in = (Bytef *)json;
    def.avail_in = (uInt)json_len;
    def.next_out = comp_buf;
    def.avail_out = (uInt)sizeof(comp_buf);

    int ret = deflate(&def, Z_FINISH);
    if (ret != Z_STREAM_END) {
        fprintf(stderr, "deflate did not finish as expected (ret=%d)\n", ret);
        deflateEnd(&def);
        return EXIT_FAILURE;
    }
    size_t comp_len = sizeof(comp_buf) - def.avail_out;
    deflateEnd(&def);

    /* now try to decompress using the library helper */
    char *out = NULL;
    size_t out_len = 0;

    if (!discord_gateway_zlib_inflate(comp_buf, comp_len, &out, &out_len)) {
        fprintf(stderr, "discord_gateway_zlib_inflate() failed\n");
        return EXIT_FAILURE;
    }

    if (out_len != json_len || memcmp(out, json, json_len) != 0) {
        fprintf(stderr, "Decompressed payload does not match original\n");
        free(out);
        return EXIT_FAILURE;
    }

    free(out);
    return EXIT_SUCCESS;
}


