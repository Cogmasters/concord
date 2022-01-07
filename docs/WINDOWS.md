# Compiling on Windows (Detailed instructions)

Concord supports Windows natively using Cygwin and Mingw64. It is preferred that you use Cygwin if possible, even if it requires runtime dependencies (a variety of DLLs from /bin, namely `cygwin1.dll`). Mingw64 will produce a build that runs without any dependencies. 

## Cygwin and Dependencies

Concord does not have very many dependencies. When you run the Cygwin installer, you will be provided with a long list of packages you can choose to install. The following packages are required at a minimum:
- gcc-core
- make
- libcurl-devel
You might also want to install git and vim. Please note that because Cygwin stores its files on your Windows machine's filesystem, you can run `explorer.exe .` anytime to open a Windows Explorer window in your current directory. You can use any IDE you would like to use, but you will most likely still have to enter `make` to recompile your changes from the Cygwin terminal.

It is also possible to use a clang-based compiler, but there is little reason to do so.

## Microsoft Visual C/C++
As it stands right now, MSVC is not supported at all. 

## Other compilers
The following compilers are **not** supported:
- OpenWatcom
- Turbo C/C++ (or Borland C/C++)
- Pelles C
- Digital Mars
- Intel C++
- AMD Optimizing C++ (Clang-based, but untested)

Generally speaking, the compiler that you use must implement the GNU extensions. This is likely to change in the future, however.
