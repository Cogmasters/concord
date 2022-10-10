# Debugging

## Debugging? What it is and why?

Debugging is one of **the most important things** when it comes to C programming, not only Concord. It is important **because a debugger will show you where the error** (like, a segmentation fault or core dump) **came from**, since you cannot know it with ease without it.

We will be focusing on two popular tools for debugging, `GDB` and `Valgrind`.

Now, you could say "`But, doesn't the compiler already tell me the errors?`". Well, it does, but it is not perfect; some errors are only detectable during runtime and are completely uncheckable by the compiler!

## Debugging (segmentation faults and core dumps)

For this guide, we are going to use GDB, an easy debugging tool for those types of errors.

### Installing GDB

Before we use GDB, we must install it. We can easily do this with apt (or whatever package manager you have on your system), but first, let's check if your machine already has it:

```console
$ gdb
```

In case this command failed, we can proceed with the installation of GDB (you need to run `apt` with root permissions, and this command only works on Debian-based systems):

```console
# apt install gdb
```

### Notes before debugging

For better debugging results, **you must disable all types of compiler optimizations** (-O1, -O2, -O3, -Ofast and etc) and **enable the `-g` flag**.

This is important, enabling **optimization flags will just make debugging harder** and can make it impossible to get a backtrace if they are enabled.

### Proceeding with debugging

Since we now installed `GDB`, we can use it. For example, if the file that you want to debug is named `ConcordGuides`, the command that you will need to execute is:

```console
$ gdb ./ConcordGuides
``` 

After we execute this command, you should see some copyright messages; just press `c` and `enter`, and you are now inside GDB's shell.

To start debugging, just **use the command `r`** (shorter version of `run`) and GDB **will start running and debugging your program**. You will **need to wait until your program/bot crashes** to see the results.

After your program/bot crashes, you can run the command `bt` to **see the backtrace of the crash**. You will need to find which line of your code is throwing the segmentation fault/coredump (please note that the crash doesn't always come from your program, it could be from a library), and see what's wrong with it.

Sadly it doesn't say what is wrong, or the error message, but it already helps a lot.

If you want to know more GDB commands, you should take a look at [Beej's Quick Guide to GDB](https://beej.us/guide/bggdb/).

## Debugging (memory leaks)

Valgrind is an **awesome tool for debugging memory leaks**, and it's the tool that we are going to use here.

### Installing Valgrind

Before trying to install Valgrind, we first need to check if you already have it, use the command below:

```console
$ valgrind
```

If Valgrind fails to execute, it means that you don't have it; we must proceed with installing it (run apt as root, and, again, this only applies to Debian systems):

```console
# apt install valgrind
```

### Proceeding with debugging

Now that we have Valgrind, we can proceed with debugging our program/bot. Use the command below to start debugging (expecting the file of your program/bot to be called ConcordGuides):

```console
$ valgrind --leak-check=full ./ConcordGuides
```

Then Valgrind will start to debug (NOTE: This will cause the program/bot to use much more resources than before, don't worry, it's normal)

After it, you can execute commands that you suspect that is generating a memory leak, after it, you can stop the program/bot process and see the results of it.

NOTE: Concord itself may cause some memory leaks if you don't use discord_shutdown when finalizing the bot's process. You can enable Concord to handle this for you by compiling Concord with:

```console
$ CFLAGS="-DCCORD_SIGINTCATCH" make
```

Done, now you will see the backtrace of where a memory leak happened.

This is a simple guide intended to be used by people that want just the basics of it, however, if you want to get more knowledge on it, you should take a look at [Valgrind's Quick Start](https://valgrind.org/docs/manual/quick-start.html).