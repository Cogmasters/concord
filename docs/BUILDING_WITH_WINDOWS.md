# THIS GUIDE IS DEPRECATED

# Building orca with Windows

### Install dependencies:
The first thing you will need is a C compiler. I recommend you to use `gcc`, because you might have problems with other compilers.
First, download `chocolatey`. It's an important tool to software managment, and, in my option, the better and simpler to install `gcc`.
You can find the steps to download it [here](https://chocolatey.org/install).
Then, open the command shell as administrator, type `choco install mingw`, press enter and wait.

The second dependency is `wget`, a tool that allows you to download files from the internet using the terminal.
Orca uses it because some files are in a separate repository, [cee-utils](https://github.com/cee-studio/cee-utils).
Now that you already have chocolatey, open the command shell as administrator, type `choco install mingw`, press enter and wait.

If you want to build orca for Windows, you'll also need curl.
In Ubuntu, you could do this just using apt, but in Windows, you can download it manually [here](https://curl.se/windows/)
Then, copy the file `libcurl-x64.dll` from `CURL_DOWNLOAD_PATH\bin` to your project's binary directory.
In my case, it's `C:\Users\Papaulo\Downloads\curl-7.76.1-win64-mingw\bin`.

You'll also need OpenSSL, which you can download and install the binaries [here](https://slproweb.com/products/Win32OpenSSL.html).
NOTE: don't install "Light" version, or you won't have the static libraries and include headers.
You can choose install directory, but by default it uses `SomeRootDirectory:\Program Files\OpenSSL-Win64`.
SomeRootDirectory can be each disk in your computer, like "C:", "D:", "E:" etc.
It will also ask you if you want to copy DLLs to Windows system directory or OpenSSL binaries.
I always choose the second option, but I don't think it would cause any problem choosing the other.
NOTE: If you have problems with the MSI installer, try the EXE one.

### Add dependencies to Makefile
Now that you successfully installed the dependencies, you have to edit the makefiles to link the include headers and static libraries.
First, go to `Makefile`.
Then, go to the line that defines `LIBDISCORD_CFLAGS`.
First, change `-I./` to `-I.`. Then, add `-I"CURL_DOWNLOAD_PATH\include"`. In my case, it's `-I"C:\Users\Papaulo\Downloads\curl-7.76.1-win64-mingw\include"`.
Do the same for OpenSSL, `-I"OPENSSL_DOWNLOAD_PATH\include"`. In my case, it's `-I"C:\Program Files\OpenSSL-Win64\include"`.

Then, go to the line that defines `LIBDISCORD_LDFLAGS`.
First, add `-L"CURL_DOWNLOAD_PATH\lib"` after `-L./$(LIBIR)`. In my case, it's `-L"C:\Users\Papaulo\Downloads\curl-7.76.1-win64-mingw\lib"`.
Now, add `-L"OPENSSL_DOWNLOAD_PATH\lib"`. In my case, it's `-L"C:\Program Files\OpenSSL-Win64\lib"`.

### Create some files to add strndup
Now, we need to create some files to add strndup, a POSIX function that isn't available in the Windows standard.
Create two files: `strndup.h` and `strndup.c`.
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

Then, go to `discord-user.c` and include `strndup.h`:
```c
#include "strndup.h"
```

Do the same with `common/user-agent.c` and `common/third-party/curl-websocket.c`

Now, go to `Makefile`.
Then, go to the line that defines the variable `OBJS` and add `$(OBJDIR)/strndup.c.o`.

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
