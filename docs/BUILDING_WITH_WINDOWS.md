# Building orca with Windows

### Install dependencies:
The first thing you will need is a C compiler. I recommend you to use `gcc`, because you might have problems with other compilers.
First, download `chocolatey`. It's an important tool to software managment, and, in my option, the better and simpler to install `gcc`.
You can find the steps to download it [here](https://chocolatey.org/install).
Then, open the command shell as administrator, type `choco install mingw`, press enter and wait.

If you want to build orca for Windows, you'll also need curl.
In Ubuntu, you could do this just using apt, but in Windows, you can download it manually [here](https://curl.se/windows/)
Then, copy the file `libcurl-x64.dll` from `CURL_DOWNLOAD_PATH\bin` to your project's binary directory.
In my case, it's `C:\Users\User\Downloads\curl-7.75.0-win64-mingw\bin`.

You'll also need OpenSSL, which you can download and install the binaries [here](https://slproweb.com/products/Win32OpenSSL.html).
NOTE: don't install "Light" version, or you won't have the static libraries and include headers.
You can choose install directory, but by default it uses `SomeRootDirectory:\Program Files\OpenSSL-Win64`.
SomeRootDirectory can be each disk in your computer, like "C:", "D:", "E:" etc.
It will also ask you if you want to copy DLLs to Windows system directory or OpenSSL binaries.
I always choose the second option, but I don't think it would cause any problem choosing the other.
NOTE: If you have problems with the MSI installer, try the EXE one.

### Add dependencies to makefile
Now that you successfully installed the dependencies, you have to edit the makefiles to link the include headers and static libraries.
First, go to `Makefile`.
Then, go to the line that defines `LIBDISCORD_CFLAGS`.
First, change `-I./` to `-I.`. Then, add `-I"CURL_DOWNLOAD_PATH\include"`. In my case, it's `-I"C:\Users\User\Downloads\curl-7.75.0-win64-mingw\include"`.
Do the same for OpenSSL, `-I"OPENSSL_DOWNLOAD_PATH\include"`. In my case, it's `-I"C:\Program Files\OpenSSL-Win64\include"`.

Then, go to the line that defines `LIBDISCORD_LDFLAGS`.
First, add `-L"CURL_DOWNLOAD_PATH\lib"` after `-L./$(LIBIR)`. In my case, it's `-L"C:\Users\User\Downloads\curl-7.75.0-win64-mingw\lib"`.
Now, add `-L"OPENSSL_DOWNLOAD_PATH\lib"`. In my case, it's `-L"C:\Program Files\OpenSSL-Win64\lib"`.

### Create some files to add POSIX functions
Now, we need to create some files to add some POSIX functions that aren't available on Windows standard.
The first function we're gonna need is `tdestroy`. First, create two files: `tdestroy.h` and `tdestroy.c`.
Inside of `tdestroy.h`, insert the following content:
```h
#ifndef TDESTROY_H
#define TDESTROY_H

#ifdef __cplusplus
extern "C" {
#endif

void tdestroy(void *root, void (*free_node)(void *nodep));

#ifdef __cplusplus
}
#endif

#endif // TDESTROY_H
```
Now, insert the following content inside of `tdestroy.c`:
```c
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "tdestroy.h"

#define USE_MALLOC_LOW_BIT 1
#ifndef USE_MALLOC_LOW_BIT
typedef struct node_t
{
  /* Callers expect this to be the first element in the structure - do not
     move!  */
  const void *key;
  struct node_t *left_node;
  struct node_t *right_node;
  unsigned int is_red:1;
} *node;
#define RED(N) (N)->is_red
#define SETRED(N) (N)->is_red = 1
#define SETBLACK(N) (N)->is_red = 0
#define SETNODEPTR(NP,P) (*NP) = (P)
#define LEFT(N) (N)->left_node
#define LEFTPTR(N) (&(N)->left_node)
#define SETLEFT(N,L) (N)->left_node = (L)
#define RIGHT(N) (N)->right_node
#define RIGHTPTR(N) (&(N)->right_node)
#define SETRIGHT(N,R) (N)->right_node = (R)
#define DEREFNODEPTR(NP) (*(NP))
#else /* USE_MALLOC_LOW_BIT */
typedef struct node_t
{
  /* Callers expect this to be the first element in the structure - do not
     move!  */
  const void *key;
  uintptr_t left_node; /* Includes whether the node is red in low-bit. */
  uintptr_t right_node;
} *node;
#define RED(N) (node)((N)->left_node & ((uintptr_t) 0x1))
#define SETRED(N) (N)->left_node |= ((uintptr_t) 0x1)
#define SETBLACK(N) (N)->left_node &= ~((uintptr_t) 0x1)
#define SETNODEPTR(NP,P) (*NP) = (node)((((uintptr_t)(*NP)) \
                                         & (uintptr_t) 0x1) | (uintptr_t)(P))
#define LEFT(N) (node)((N)->left_node & ~((uintptr_t) 0x1))
#define LEFTPTR(N) (node *)(&(N)->left_node)
#define SETLEFT(N,L) (N)->left_node = (((N)->left_node & (uintptr_t) 0x1) \
                                       | (uintptr_t)(L))
#define RIGHT(N) (node)((N)->right_node)
#define RIGHTPTR(N) (node *)(&(N)->right_node)
#define SETRIGHT(N,R) (N)->right_node = (uintptr_t)(R)
#define DEREFNODEPTR(NP) (node)((uintptr_t)(*(NP)) & ~((uintptr_t) 0x1))
#endif /* USE_MALLOC_LOW_BIT */
typedef const struct node_t *const_node;
#undef DEBUGGING
#ifdef DEBUGGING
/* Routines to check tree invariants.  */
#define CHECK_TREE(a) check_tree(a)
static void
check_tree_recurse (node p, int d_sofar, int d_total)
{
  if (p == NULL)
    {
      assert (d_sofar == d_total);
      return;
    }
  check_tree_recurse (LEFT(p), d_sofar + (LEFT(p) && !RED(LEFT(p))),
                      d_total);
  check_tree_recurse (RIGHT(p), d_sofar + (RIGHT(p) && !RED(RIGHT(p))),
                      d_total);
  if (LEFT(p))
    assert (!(RED(LEFT(p)) && RED(p)));
  if (RIGHT(p))
    assert (!(RED(RIGHT(p)) && RED(p)));
}
static void
check_tree (node root)
{
  int cnt = 0;
  node p;
  if (root == NULL)
    return;
  SETBLACK(root);
  for(p = LEFT(root); p; p = LEFT(p))
    cnt += !RED(p);
  check_tree_recurse (root, 0, cnt);
}
#else
#define CHECK_TREE(a)
#endif

typedef void (*__free_fn_t)(void *nodep);

static void
tdestroy_recurse (node root, __free_fn_t freefct)
{
  if (LEFT(root) != NULL)
    tdestroy_recurse (LEFT(root), freefct);
  if (RIGHT(root) != NULL)
    tdestroy_recurse (RIGHT(root), freefct);
  (*freefct) ((void *) root->key);
  /* Free the node itself.  */
  free (root);
}
void
tdestroy (void *vroot, __free_fn_t freefct)
{
  node root = (node) vroot;
  CHECK_TREE (root);
  if (root != NULL)
    tdestroy_recurse (root, freefct);
}
```

The second function we're gonna need is `strndup`. Create two files: `strndup.h` and `strndup.c`.
Inside of `strndup.h`, insert the following content:
```h
#ifndef STRNDUP_H
#define STRNDUP_H

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

char *
strndup (const char *s, size_t n);

#ifdef __cplusplus
}
#endif

#endif // STRNDUP_H
```

Insert the following content inside of `strndup.c`:
```c
typedef void *PTR;

#include <stddef.h>

extern size_t    strlen (const char*);
extern PTR    malloc (size_t);
extern PTR    memcpy (PTR, const PTR, size_t);

char *
strndup (const char *s, size_t n)
{
  char *result;
  size_t len = strlen (s);

  if (n < len)
    len = n;

  result = (char *) malloc (len + 1);
  if (!result)
    return 0;

  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}
```

Now, go to `discord-ratelimit.c` and include `tdestroy.h`:
```c
#include "tdestroy.h"
```

Then, go to `discord-public-user.c` and include `strndup.h`:
```c
#include "strndup.h"
```

Now, go to `Makefile`.
Then, go to the line that defines the variable `OBJS` and add `$(OBJDIR)/tdestroy.c.o $(OBJDIR)/strndup.c.o`.

### Add native CA to curl options
If we don't wanna get SSL certificate error, we need to add native CA to curl options.
First, go to `common/user-agent.c`. Then, find the function `conn_init` and insert the following code add the end of the function (before returning):
```c
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
```
Then, go to `common/curl-websocket.c`, find the function `cws_new` and insert the following code after setting the other options:
```c
    curl_easy_setopt(easy, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
```

### Compile
```
make CC=YOUR_C_COMPILER
```
YOUR\_C\_COMPILER can be C every compiler, like gcc etc.

### Important notes
When compiling, you must have `undefined reference to random` problem.
If it happens, you can go to the line that the error tells and replace `random()` with `rand()`.
You may also get `undefined reference to dirfd`, `undefined reference to fstatat` and `undefined reference to readlink`.
This function won't be missed, so you can just comment the function.