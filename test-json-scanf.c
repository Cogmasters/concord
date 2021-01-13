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


int main(void) {
  char *locale = setlocale(LC_CTYPE, "");
  assert(NULL != locale);

  int integer1=0, integer2=0, i3 =0, i4=0, i5=0;
  char str1[25] = {0}, str2[25] = {0};
  char str[] = "{ \"t\":\"abc\", \"s\":10, \"op\":100 "
          ", \"k1\": {  \"v1\": 10 }  "
          ", \"a1\": [ 112, 2, 3 ] "
          ", \"b\": true "
          ", \"nstr\":null }";

  printf("%s\n", str);

  json_scanf(str, sizeof(str),
       "[a1][0]%d [t]%s [s]%d [op]%d [nstr]%s [k1][v1]%d [b]%b",
       &i4, str1, &integer1, &integer2, str2, &i3, &i5);

  printf("t %s, s %d, op %d, nstr %s, i3 %d, i4 %d\n",
         str1, integer1, integer2, str2, i3, i4);

  return EXIT_SUCCESS;
}
