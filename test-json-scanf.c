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
#include "ntl.h"


int main(void) {
  char *locale = setlocale(LC_CTYPE, "");
  assert(NULL != locale);

  int integer1=0, integer2=0, i3 =0, i4=0, i5=0;
  char str1[25] = {0}, str2[25] = {0};
  char pretty_str[] =
          "{ |t|:|abc|, |s|:10, |op|:100 "
                  ", |k1|: {  |v1|: 10 }  "
                  ", |a1|: [ 112, 2, 3 ] "
                  ", |b|: true "
                  ", |bigs|: |lllllllllllllllllllllong|"
                  ", |nstr|:null "
                  "}";

  char * str;

  json_asprintf(&str, pretty_str);

  printf("input string: %s\n", str);

  char bigs[128] = {0}, bigS[128] = {0};
  struct sized_buffer tok;

  json_scanf(str, strlen(str),
       "[a1][0]%d [t]%s [s]%d [op]%d [nstr]%s [k1][v1]%d [b]%b"
       "[bigs]%.*s"
       "[bigs]%.*S"
       "[k1]%T"
       ,&i4, str1, &integer1, &integer2, str2, &i3, &i5
          ,128 /* size of bigs */, bigs
          ,128 /* size of bigS */, bigS
          ,&tok
  );

  printf("t %s, s %d, op %d, nstr %s, i3 %d, i4 %d, bigs %s, bigS %s\n",
         str1, integer1, integer2, str2, i3, i4, bigs, bigS);

  char * p = NULL, *q = NULL;
  json_scanf(str, strlen(str), "[bigs]%?s [bigs]%?S", &p, &q);
  if (p) {
    printf("unknown string size: bigs %s\n", p);
    free(p);
  }

  if (q) {
    printf("unknown string size: bigS %s\n", q);
    free(q);
  }

  printf ("tok %.*s\n", (int)tok.size, tok.start);


  char raw_str[] = { '1', '\\', 'n', '2', 0 };
  char t_str[128];
  snprintf(t_str, 128, "{ \"key\":\"%s\", \"a\":10 }", raw_str);
  char * px = NULL;
  printf("%s\n", t_str);
  json_scanf(t_str, strlen(t_str), "[key]%?s", &px);
  printf("%s\n", px);


  snprintf(t_str, 128, "{ \"key\":\"%s\", \"a\":10 }", "XXXXXXXXX");
  printf("%s\n", t_str);
  json_scanf(t_str, strlen(t_str), "[key]%?s", &px);
  printf("%s\n", px);
  return EXIT_SUCCESS;
}
