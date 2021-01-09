/*
 * Copyright (c) 2020 Lucas Müller
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h> //for access()
#include <string.h>
#include <locale.h>

#include <libjscon.h>


FILE *select_output(int argc, char *argv[]);
char *get_json_text(char filename[]);
jscon_item_t *callback_test(jscon_item_t *item);

int main(int argc, char *argv[])
{
    char *locale = setlocale(LC_CTYPE, "");
    assert(NULL != locale);

    FILE *f_out = select_output(argc, argv);
    char *json_text = get_json_text(argv[1]);
    char *buffer = NULL;

    jscon_item_t *item[3] = {NULL};
    int integer1=0, integer2=0;
    char str1[25] = {0};

    jscon_scanf(json_text, 
                "%s[t]" \
                "%d[s]" \
                "%d[op]" \
                "%ji[d][user]",
                 str1,
                 &integer1,
                 &integer2,
                 &item[0]);

#if 0    
    for (size_t i=0; i < 3; ++i){
        if (NULL == item[i])
            continue;

        buffer = jscon_stringify(item[i], JSCON_ANY);
        assert(NULL != buffer);

        fprintf(stdout, "%s: %s\n", jscon_get_key(item[i]), buffer);

        free(buffer);
        jscon_destroy(item[i]);
    }

    fprintf(stdout, "s: %d\n", integer1);
    fprintf(stdout, "op: %d\n", integer2);
    fprintf(stdout, "t: %s\n", str1);
    fprintf(stdout, "user: %p\n", (void*)item[0]);

    //jscon_parse_cb(&callback_test);
    jscon_item_t *root = jscon_parse(json_text);
    assert(NULL != root);

    jscon_item_t *property1 = jscon_dettach(jscon_get_branch(root, "author"));

    if (NULL != property1){
        buffer = jscon_stringify(property1, JSCON_ANY);
        assert(NULL != buffer);

        fprintf(stdout, "%s: %s\n", jscon_get_key(property1), buffer);
        free(buffer);
        jscon_destroy(property1);
    }

    fprintf(stdout, "key: s, index: %ld\n", jscon_get_index(root, "s"));
    fprintf(stdout, "key: op, index: %ld\n", jscon_get_index(root, "op"));
    fprintf(stdout, "key: d, index: %ld\n", jscon_get_index(root, "d"));

    jscon_item_t *current_item = NULL, *tmp;
    jscon_item_t *walk = jscon_iter_composite_r(root, &current_item);
    do {
        tmp = jscon_get_branch(walk, "m");
        if (NULL != tmp){
            buffer = jscon_stringify(tmp, JSCON_ANY);
            assert(NULL != buffer);

            fwrite(buffer, 1, strlen(buffer), stderr);
            fputc('\n', stderr);
            free(buffer);
        }

        walk = jscon_iter_composite_r(NULL, &current_item);
    } while (NULL != walk);

    walk = root;
    for (int i=0; i < 5 && walk; ++i){
        fprintf(stderr, "%s\n", jscon_get_key(walk));
        walk = jscon_iter_next(walk);
    }

    walk = root;
    do {
        fprintf(stderr, "%s\n", jscon_get_key(walk));
        walk = jscon_iter_next(walk);
    } while (NULL != walk);

    buffer = jscon_stringify(root, JSCON_ANY);
    assert(NULL != buffer);

    fwrite(buffer, 1, strlen(buffer), f_out);
    free(buffer);

    jscon_destroy(root);
#endif
    free(json_text);
    fclose(f_out);

    return EXIT_SUCCESS;
}

FILE *select_output(int argc, char *argv[])
{
    char *p_arg=NULL;
    while (argc--){
        p_arg = *argv++;
        if ((*p_arg++ == '-') && (*p_arg++ == 'o') && (*p_arg == '\0')){
            assert(1 == argc); //check if theres exactly one arg left

            char *file = *argv;
            assert(access(file, W_OK)); //check if file exists

            return fopen(file, "w");
        }
    }

    return fopen("data.txt", "w");
}

/* returns file size in long format */
static long
fetch_filesize(FILE *p_file)
{
    fseek(p_file, 0, SEEK_END);
    long filesize = ftell(p_file);
    assert(filesize > 0);
    fseek(p_file, 0, SEEK_SET);

    return filesize;
}

/* returns file content */
static char*
read_file(FILE* p_file, long filesize)
{
    char *buffer = malloc(filesize+1);
    assert(NULL != buffer);

    //read file into buffer
    fread(buffer,1,filesize,p_file);
    buffer[filesize] = 0;

    return buffer;
}

/* returns buffer containing file content */
char*
get_json_text(char filename[])
{
    FILE *file = fopen(filename, "rb");
    assert(NULL != file);

    long filesize = fetch_filesize(file);
    char *buffer = read_file(file, filesize);

    fclose(file);

    return buffer;
}

#if 0
jscon_item_t *callback_test(jscon_item_t *item)
{
    if (NULL != item && jscon_keycmp(item, "m")){
        fprintf(stdout, "%s\n", jscon_get_string(item));
    }
      
    return item;
}
#endif
