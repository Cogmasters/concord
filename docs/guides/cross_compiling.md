# Cross Compiling Concord

Unlike most Autoconf-based projects, Concord uses normal Makefiles. As such,
cross-compilation can be rather daunting at first. Fortunately, once you 
understand it, you won't have any trouble (unless your compiler malfunctions
or is misconfigured). 

## Step 1: getting a cross compiler
Debian-based Linux distros have cross compilers available in their package
repositories. For example, to get an ARM cross compiler suitable for building
for an old 32-bit Raspberry Pi, run `apt-get install gcc-arm-linux-gnueabihf`.
Search the Debian package repositories for "gcc" to see other cross compilers
available. 

If you aren't on Debian, you can use cross-compilers from [here](https://mirrors.edge.kernel.org/pub/tools/crosstool/), although, do note that these compilers
might take a fair bit of work to get working perfectly. If you do use one of
these, ensure that `$PATH` gets updated to include the compiler's bin directory,
or you won't be able to invoke the compiler.

## Step 2: cross-compiling Concord
For this example, we will assume that your host system is a standard x86_64
PC, and uses the target triplet `x86_64-pc-linux-gnu`. We will be
cross-compiling to a 64-bit Raspberry Pi 4, with the target triplet
`aarch64-linux-gnu`. Now, when GCC cross-compilers are made, all of the built
executables for the compiler are prefixed with the target tripet. This means
that our actual C compiler command is `aarch64-linux-gnu-gcc`. This will be
our `CC` value.

The gencodecs system that Concord uses requires that the system C compiler is
available. This means we have to set `HOSTCC` when we compile. Since our
target triplet is `x86_64-pc-linux-gnu`, this means that our host C compiler
is named `x86_64-pc-linux-gnu-gcc`. However, since this is the primary C
compiler on the system, we can just use `gcc` for `CC`. 

Finally, we will install Concord to the Raspberry Pi by directly accessing its
root filesystem via NFS. The Pi's Linux image has been mounted read-write into
`/mnt`. Since we want Concord to go into `/usr/local`, our target `PREFIX`
path for `make install` is `/mnt/usr/local`. 

Okay, we can now run the commands to actually compile.

```console
cd gencodecs
make HOSTCC=gcc CC=aarch64-linux-gnu-gcc
cd ..
make CC=aarch64-linux-gnu-gcc
make install PREFIX=/mnt/usr/local
```

Easy as that! Granted, you can perform a compilation with fewer typed commands
if you `export` those three variables beforehand, but, this guide was written
with maximum learning in mind (and demonstrating why gencodecs needs the
split compilation procedure). 


