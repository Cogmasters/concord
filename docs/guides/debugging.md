# Debugging Concord Applications

## Introduction

Debugging is an essential skill for C programmers. While compilers catch many errors at compile-time, runtime issues like segmentation faults, memory leaks, and race conditions require specialized tools to diagnose and fix.

This guide covers the two most important debugging tools for Concord development:
- **GDB** - For tracking down crashes and runtime errors
- **Valgrind** - For detecting memory leaks and other memory-related issues

## Prerequisites for Effective Debugging

Before starting to debug, make sure your code is compiled with these flags:

```console
$ CFLAGS="-g -O0" make
```

- `-g` adds debugging symbols that tools need to show meaningful information
- `-O0` disables compiler optimizations that can make debugging more difficult

## Using GDB to Debug Crashes

### Installation

GDB is available on most platforms:

```console
# Debian/Ubuntu
$ sudo apt install gdb

# Fedora/RHEL/CentOS
$ sudo dnf install gdb

# Arch/Manjaro
$ sudo pacman -S gdb

# macOS
$ brew install gdb

# FreeBSD
$ pkg install gdb
```

### Basic GDB Usage

1. Start your application under GDB:

```console
$ gdb ./your_bot
```

2. Run your application:

```console
(gdb) run
```

3. When a crash occurs, get a backtrace:

```console
(gdb) bt
```

This will show the call stack at the point of the crash, helping you identify where the problem occurred.

### Useful GDB Commands

| Command | Description |
|---------|-------------|
| `run` or `r` | Start your program |
| `bt` | Show backtrace (call stack) |
| `frame N` | Switch to frame N in the backtrace |
| `print VARIABLE` | Display the value of a variable |
| `list` | Show source code around current line |
| `break FUNCTION` | Set breakpoint at function |
| `break FILE:LINE` | Set breakpoint at specific line |
| `continue` or `c` | Continue execution after stop |
| `next` or `n` | Execute next line (step over function calls) |
| `step` or `s` | Execute next line (step into function calls) |
| `quit` or `q` | Exit GDB |

## Using Valgrind to Find Memory Issues

### Installation

Valgrind is available on most Unix-like platforms:

```console
# Debian/Ubuntu
$ sudo apt install valgrind

# Fedora/RHEL/CentOS
$ sudo dnf install valgrind

# Arch/Manjaro
$ sudo pacman -S valgrind

# macOS
$ brew install valgrind

# FreeBSD
$ pkg install valgrind
```

### Basic Valgrind Usage

Run your application with memory leak checking enabled:

```console
$ valgrind --leak-check=full --show-leak-kinds=all ./your_bot
```

When you exit your application, Valgrind will report any memory leaks detected.

### Understanding Valgrind Output

Valgrind's output includes:

1. **Definitely Lost**: Memory that was allocated but never freed
2. **Indirectly Lost**: Memory that was allocated but became unreachable when parent pointers were lost
3. **Possibly Lost**: Memory that Valgrind cannot determine if it is accessible
4. **Still Reachable**: Memory that was still accessible at program exit (not necessarily a problem)

For each leak, Valgrind shows a backtrace indicating where the memory was allocated.

### Concord-specific Valgrind Tips

Concord uses many asynchronous operations that can complicate memory management. When using Valgrind with Concord:

1. Ensure you call `discord_shutdown()` before exiting, or compile with the SIGINT handler:

```console
$ CFLAGS="-DCCORD_SIGINTCATCH" make
```

2. Be aware that some false positives may occur due to libcurl's internal memory management

## Advanced Debugging Techniques

### Address Sanitizer (ASan)

For faster and more detailed memory error detection than Valgrind, consider using Address Sanitizer:

```console
$ CFLAGS="-g -fsanitize=address -fno-omit-frame-pointer" LDFLAGS="-fsanitize=address" make
```

Run your program normally, and ASan will report memory errors as they occur.

### Thread Sanitizer (TSan)

For detecting race conditions and threading issues:

```console
$ CFLAGS="-g -fsanitize=thread -fno-omit-frame-pointer" LDFLAGS="-fsanitize=thread" make
```

### Core Dumps Analysis

If your program crashes, the system might generate a core dump file. To enable core dumps:

```console
$ ulimit -c unlimited
```

After a crash, you can analyze the core dump with GDB:

```console
$ gdb ./your_bot core
```

### Discord-Specific Debugging

To enable verbose logging of HTTP and WebSocket communications:

```console
$ CFLAGS="-DCCORD_DEBUG_HTTP -DCCORD_DEBUG_WEBSOCKETS" make
```

You can also configure logging in your `config.json`:

```json
{
  "log": {
    "level": "TRACE",
    "trace": "debug.log",
    "http": "http.log",
    "ws": "ws.log"
  }
}
```

## Common Issues and Solutions

### SIGSEGV (Segmentation Fault)

Common causes:
- Dereferencing NULL pointers
- Accessing freed memory
- Buffer overflows
- Stack overflows

Diagnosis: Use GDB to get a backtrace and examine variables at the point of crash.

### Memory Leaks

Common causes:
- Forgetting to free allocated memory
- Losing the pointer to allocated memory
- Not calling `discord_shutdown()`

Diagnosis: Use Valgrind to identify where the memory was allocated.

### Deadlocks

Common causes:
- Circular waits for resources
- Improper lock ordering

Diagnosis: Use GDB to examine the state of all threads when the program hangs.

## Further Reading

- [GDB Documentation](https://sourceware.org/gdb/current/onlinedocs/gdb/)
- [Beej's Quick Guide to GDB](https://beej.us/guide/bggdb/)
- [Valgrind User Manual](https://valgrind.org/docs/manual/manual.html)
- [Valgrind Quick Start](https://valgrind.org/docs/manual/quick-start.html)
- [Address Sanitizer Wiki](https://github.com/google/sanitizers/wiki/AddressSanitizer)