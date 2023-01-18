# Installing Concord on Termux

## Termux? What's that?

Termux is a terminal emulator and a Linux environment app for Android devices. It contains a Linux environment, giving you some Linux commands and a lot of Linux features (such as a C compiler).

## Installing Concord

### Installing required packages

First, we need to update the package list:

```console
$ pkg update
```

WARN: **Don't use `apt` on Termux! Use `pkg` instead.**

After that, we will need `git`, `binutils`, `make` and `clang`. We can install them with:

```console
$ pkg install -y git binutils make clang
```

NOTE: **We are not installing `libcurl` because it's already installed with Termux.**

When done installing the packages, we will clone the `Concord` source code, which can be done with:

```console
$ git clone https://github.com/Cogmasters/concord && cd concord
```

And finally, we can proceed with compiling Concord! See the command below:

```console
$ make && make install
```

It is that easy! Now you can proceed using Concord, and don't forget to include the `-pthread -ldiscord -lcurl` flags when compiling your bot.