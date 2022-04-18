# Concord on systems besides Linux

For the most part, Concord can be made to work on the following UNIXes:

* AIX 6.0+
* IRIX 6.5+
* HP-UX 11.11+ (with GCC)
* Solaris 9+ 
* Tru64 5.1B+
* z/OS 2.1+ (under USS)
* Windows XP+ (under Cygwin)
* FreeBSD 9+
* NetBSD 8.1+
* OpenBSD 6.5+
* GNU/Hurd 0.9+
* OS X 10.9+

Concord *is* written in plain C99, but System V C compiler support for C99 can be rather spotty at times. Here is a list of caveats on various systems:

#### AIX
You will need to use `c99`, as provided by IBM XL C/C++. Alternatively, you can use GNU C from any "precompiled open-source software for AIX" repository. 

#### IRIX
It is recommended that you do use the MIPSpro compiler. You will need to add `-c99` to the `CFLAGS` variable in the Makefile before calling `make`.

#### HP-UX 11.11
libcurl and openssl are more difficult to compile on here than Concord. You can acquire pre-made packages of these from the HP-UX Porting and Archive Centre website. If you have HP aCC, it can compile Concord. However, it is recommended that you just use GNU C in lieu of aCC, as it has somewhat lackluster C99 support.

#### Solaris
Sun Studio can be made to compiler Concord. Sun Studio 11 (from 2008) was the tested compiler, but you will encounter some issues with gencodecs. Of course, use `c99` for your `$CC`. 

#### Tru64 (OSF/1)
The default compiler is NOT C99 capable, but GCC 4.4.7 can be compiled on OSF/1. Once you install that, libcurl, openssl, and Concord can be built. 

#### z/OS
z/OS UNIX System Services (USS) implemnts a plain POSIX UNIX environment under MVS. Modern versions of XL C/C++ include C99 support. Provided you already have openssl and libcurl installed, Concord installation is easy. Furthermore, once installed, you can run Concord bots as MVS batch jobs using the `BPXBATCH` facility. If you do choose to do that, please note that you will need to likely produce a shell script that sets the current working directory *before* running the bot. 

#### Windows
Please see the Windows guides in the `docs` directory for more information. Native Windows support will come out *some day*, but for now, `winpthreads` (from Mingw) works. Please note that you will likely run into trouble with Mingw's `libcurl` looking for certificates in the wrong place, as it wants to use the native Windows certificate chain system. If you get errors regarding that, please consider compiling Concord NOT using the native certificate storage system. 

#### FreeBSD, NetBSD, OpenBSD
OpenBSD might be a little tricker than the others, but Concord compiles perfectly on these. All CPUs are supported as well. For instance, one of the Concord authors was able to successfully run a bot on a semi-outdated version of NetBSD for DEC VAX systems. It is recommended that you install the dependencies from packages, but you can absolutely compile those too.

#### GNU/Hurd
Works without any trouble. Please note that this is a bad operating system to run any production workload on, but it works nonetheless.

#### OS X
You can run Concord on your Mac without any trouble. The system-provided libcurl works. You will, of course, need to install Xcode. Once you do that, just run `make; make install` and you're done.

## Operating systems that will NOT be able to run Concord

* MS-DOS (bad networking, networking doesn't work in DPMI mode, and a lackluster filesystem)
* QNX 6.x (the official QNX `qcc` compiler is not C99 capable)
* Windows NT 4 and older (Watcom is not a supported compiler *yet*)
