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
#include "libdiscord.h"

#define JSON_TEXT "{" \
  "\"username\":\"john_doe\"," \
  "\"public_flags\":128," \
  "\"id\":\"111111111111111111\"," \
  "\"discriminator\":\"1111\"," \
  "\"avatar\":\"aaa1aa11111a111a11a11a11a1aa111a\"" \
"}"

int main(void)
{
  char *locale = setlocale(LC_CTYPE, "");
  assert(NULL != locale);

  discord_user_t *user = discord_user_init();

  json_scanf(JSON_TEXT,
     "%s[id]" \
     "%s[username]" \
     "%s[discriminator]" \
     "%s[avatar]" \
     "%d[public_flags]",
      user->id,
      user->username,
      user->discriminator,
      user->avatar,
      &user->public_flags);

  fprintf(stderr,
          "{"\
            "\"username\":\"%s\"," \
            "\"public_flags\":%d," \
            "\"id\":\"%s\"," \
            "\"discriminator\":\"%s\"," \
            "\"avatar\":\"%s\"" \
           "}",
          user->username,
          user->public_flags,
          user->id, 
          user->discriminator,
          user->avatar);

  discord_user_cleanup(user);

  return EXIT_SUCCESS;
}
