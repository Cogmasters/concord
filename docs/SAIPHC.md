# Saiph-C

[The Saiph-C SDK](https://www.cee.studio/get_sdk.html) is a compiler for C and C++ programs that allows users to diagnose segmentation faults in an easy and simple manner.

## Installing and Using Saiph-C for Orca

Please run the following commands as *a normal user* (NOT ROOT).

Follow the installation steps [here](https://www.cee.studio/get_sdk.html). After this, there are some additional steps required to compile Orca:

1. Download the additional libraries for Saiph-C from [here](https://github.com/cee-studio/packages) using the following command:
   ```
   git clone https://github.com/cee-studio/packages.git
   ```
2. For Orca, use these commands inside the above `packages` folder to install the libraries instead:
    ```
    CC=sfc make bearssl curl
    ./install.sh
    ```
3. To build Orca:
   ```
    cd orca
    CC=sfc make
   ```


# Using Saiph-C to Diagnose Segfaults

As of the current build of Orca, [Saiph-C](https://www.cee.studio/get_sdk.html) can be used to compile any bots made and will give easy-to-read instructions.

Running the bot after doing [Using Saiph-C](#installing-and-using-saiph-c-for-orca) should be the same as any other C program. However, Saiph-C provides diagnostic information in the case of incorrect memory access.

## Parts of a Saiph-C error

Examples of Saiph-C errors are shown [here](https://www.cee.studio/benefits.html).
As Saiph-C covers many types of memory access errors/warnings, messages are varied, but they should have three parts: [the memory error type](#memory-error-type), [the general information](#general-information), [and the stack trace](#stack-trace).

### Memory Error Type

#### Example:
```
Memory access error: writing to the outside of a memory block; abort!
```

The Memory Error Type Block of a Saiph-C message is the first part of a message and defines the type of memory access violation that has occured; it usually has this format:

```
Memory access <error/warning depending on the memory violation type>: 
<memory violation type>; 
<continue execution or abort depending on the memory violation type>
```

Check [here](https://www.cee.studio/benefits.html) for a list of all the memory violation types.

### General Information

#### Example:
```
# Writing 1 bytes to 0x929e010 may clobber other memory blocks.
#
# The memory-block-to-be-written (start:0x929e010, size:10 bytes) was allocated at
#    file:/prog.c::10, 14
#    [libc-start-main]
# It has been freed at
#    file:/prog.c::11, 3
#    [libc-start-main]
# The allocation/free locations could have been distorted by subsequent reuses.
```

The General Information Block of a Saiph-C message is the second part of a message and further specifies the memory violation that occurs. This can vary from memory violation to memory violation and can even be absent in specific ones.

### Stack Trace

#### Example:
```
# Stack trace (most recent call first) of the read.
# [0]  file:/prog.c::7, 3
# [1]  [libc-start-main]
```
The Stack Trace portion of Saiph-C is the last part of a message and will give a stack trace of the functions that called the erroring line. This is pretty self-explainatory, but it should be noted that **the most recent call is the top-most function**.
