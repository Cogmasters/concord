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

#include "json-scanf.h"


FILE *select_output(int argc, char *argv[]);
char *get_json_text(char filename[]);

int main(int argc, char *argv[]) {
    char *locale = setlocale(LC_CTYPE, "");
    assert(NULL != locale);

    //FILE *f_out = select_output(argc, argv);
    //char *json_text = get_json_text(argv[1]);
    //char *buffer = NULL;

    //jscon_item_t *item[3] = {NULL};
    int integer1=0, integer2=0;
    char str1[25] = {0};
    char * str = "{ \"t\":\"abc\", \"s\":10, \"op\":100 }";

    printf("%s\n", str);

    json_scanf2(str,
	       "[t]%s"
	       "[s]%d"
	       "[op]%d",
	       str1,
	       &integer1,
	       &integer2);

    printf ("t %s, s %d, op %d\n", str1, integer1, integer2);

    //free(json_text);
    //fclose(f_out);

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