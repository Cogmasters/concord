# orca-internals.md
If you are interested in contributing to Orca with more in mind than just 
coding, you found the right place! The ultimate goal is to help you understand 
how Orca works internally, and as a result, write your own API endpoint.

# Introduction
Orca is a collection of REST API wrappers that are written in C. Orca currently 
covers the Discord, GitHub, Reddit, and the Slack API. While this guide will only
use one of those APIs, it is worth noting the existence of the other source files.

This guide will cover writing an endpoint for the GitHub API. To get started, 
make sure you have installed Orca using the installation instructions for your 
platform of choice [here](https://github.com/cee-studio/orca).

# A Tour of Orca
While Orca is not complex, it is still a decent sized project. Searching the 
documentation may be confusing to new potential contributors when looking for 
certain things. This part of the guide will cover each of the major folders and 
the files they contain.

## Orca specs
``specs`` and ``specs-code`` and their contents are important parts of Orca's
internal workings. These two folders, also denoted as "the specs," are a method 
of code generation.

``specs`` is the folder where many "templates" are stored for structures,
enumerations, and more. They are written in JSON and are used to generate their
C code equivalents. This system is better than writing the structures and
enumerations in a header file because it allows for the generation of functions
to convert JSON objects to actual structures.

## Examples
The ``examples`` folder is where all the examples of bots are stored. It will 
provide a demonstration of how to write code that is in-line with Orca's existing
code base.

When you finish adding an endpoint, it is encouraged to write a bot that uses
the endpoint inside of this folder as a sort of makeshift test for other users
or developers.

## discord*.c, github*.c, reddit*.c, and slack*.c
`discord*.c`, `github*.c`, `reddit*.c`, and `slack*.c` are the source 
files that handle all the logic behind their individual API wrapper.

# Choosing an Endpoint
Now that all the boring reading stuff is out of the way, we can get to the fun
stuff: implementing an endpoint. First things first, we have to choose an endpoint
to implement. If you are following this guide and do not plan to implement a
GitHub API endpoint, don't fret, this guide aims to remain as website-independent 
as possible.

To find an endpoint to implement, head over to your chosen website's API 
documentation. This will at least require a simple Google search, but it may
require a bit of digging in some occasions. For this guide, we can use the 
GitHub API reference found [here](https://docs.github.com/en/rest/reference).

If you have any questions, feel free to join the Discord server for Orca, [SaiphCee](https://discord.gg/evbfgCUtSW).
