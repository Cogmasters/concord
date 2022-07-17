# Internals (WIP)

**This guide is currently incomplete**

## Introduction

If you are interested in contributing with more than just coding, you found the 
right place! The ultimate goal is to help you understand how Concord works internally, 
and as a result, write your own API endpoint.

Before starting make sure you have followed the [build instructions](../README.md#build-instructions)!

## About Concord

Concord is a Discord API wrappers written entirely in C.

# A Tour of Concord

While Concord is not complex, it is still a decently sized project. Navigating the 
documentation may be confusing to new potential contributors when searching for 
certain things. This section aims to assist you with understanding each of the 
major folders and files.

## Gencodecs

Wrapping an API object in C can quickly get overwhelming and repetitive, considering 
one have to address many things modern languages would take for granted, such as the 
encoding or decoding of an object with JSON. For this purpose we created our own tool
for wrapping and generating API objects.

- `gencodecs/`: This is the folder we write our definitions for code-generation, it 
    contains gencodecs macros that are fed to `gencodecs/Makefile`. The generated
    code will be located at `gencodecs/discord-codecs.h` and `gencodecs/discord-codecs.c`.

## Examples

The `examples/` folder is where we place our up-to-date bot examples. 

When adding a new feature it is encouraged that the contributor writes an example bot 
to demonstrate said feature, as a sort of makeshift test for other users and developers.

## API source-code

The `src/` folder is where we place all of our Discord API wrapping logic. 

## Common source-code

The `core/` folder is where we place all of Concord core's logic, such as handling of the
WebSockets and REST protocols, threadpool management, etc.

If you have any questions, feel free to join our [Discord server](https://discord.gg/Y7Xa6MA82v).
