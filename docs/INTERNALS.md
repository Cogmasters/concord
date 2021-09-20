# orca-internals.md
This is a guide on how Orca works internally. Orca is a collection of
REST API wrappers that is written in C. While Orca is not insanely complex,
it is still a fairly large project. This guide aims to introduce new users
who may be interested in contributing to Orca with more information than
simply coding guidelines. The intention behind this is to guide the user
through implementing their own API endpoint.

Through reading this guide, if you have any questions, feel free to join the
Discord server for Orca, [SaiphCee](https://discord.gg/evbfgCUtSW).

# Introduction
There are many APIs out there. Orca currently only covers the Discord API,
and some of the GitHub API, but there are already-existing projects in Orca
for Reddit and the Slack API.

For the purposes of this guide, we will choose to write an endpoint for the
GitHub API. To get started, make sure you have installed Orca using the
installation instructions for your platform of choice [here](https://github.com/cee-studio/orca).

# A tour of Orca
Orca is a fairly large project. Because of this, it may be confusing to new
potential contributors where to look for certain things. In this guide I will
go over each of the major folders and files that will be used for.

## Orca specs
These two folders and their contents are some of the most important parts of
Orca's internal workings. These two folders, or 'the specs' as you may hear
them be called, are a method of code generation.

``specs`` is the folder where many 'templates' are stored for structures,
enumerations, and more. They are written in JSON and are used to generate their
C code equivalents. This system is better than writing the structures and
enumerations in a header file because it allows for the generation of functions
to convert JSON objects to actual structures.

## Examples
This folder is where all the examples of bots are stored. It will be useful if
you are a regular user of Orca, but it might also give you a demonstration of
how to write code that is in-line with Orca's existing code base.

When you finish adding an endpoint, it is encouraged to write a bot that uses
the endpoint inside of this folder as a sort of makeshift test for other users
or developers.

## discord*.c, github*.c, reddit*.c, and slack*.c
These are the source files that handle all the actual logic behind their individual
API wrapper. For the purposes of this guide, we will only be using the GitHub
source files, however it is worth noting the existence of the other source files.

# Choosing an endpoint
Now that all the boring reading stuff is out of the way, we can get to the fun
stuff, implementing an endpoint. First things first, we have to choose an endpoint
to implement. If you are following this guide and do not plan to implement a
GitHub API endpoint, I will try to keep it as website-independent as possible to
cover the most use cases.

To find an endpoint to implement, head over to your website of choice's API
documentation. This will at least require a simple Google search, but it may
require a bit of digging to find in some occasions. For our use case, we can use
the GitHub API reference found [here](https://docs.github.com/en/rest/reference).
