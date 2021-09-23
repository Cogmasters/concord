# Work in Progress

**This guide is currently incomplete**

# Introduction

If you are interested in contributing with more than just coding, you found the 
right place! The ultimate goal is to help you understand how Orca works internally, 
and as a result, write your own API endpoint. <!-- This guide will assist you with writing your first endpoint, we will be using the GitHub API but the same techniques should apply to any other API. -->

Before starting make sure you have followed the [build instructions](../README.md#build-instructions)!

# About Orca

Orca is a collection of REST API wrappers that are written in C. Orca currently 
covers the Discord API (and GitHub, Reddit, and Slack to some degree).

# A Tour of Orca

While Orca is not complex, it is still a decently sized project. Navigating the 
documentation may be confusing to new potential contributors when searching for 
certain things. This section aims to assist you with understanding each of the 
major folders and files.

## Orca Specs

Wrapping an API object in C can quickly get overwhelming and repetitive, considering 
one have to address many things modern languages would take for granted, such as the 
encoding or decoding of an object with JSON. For this purpose we created our own specs
for wrapping and generating API objects.

- `specs/`
  This is the folder we write our specs for code-generation, it contains multiple
  JSON templates that cane be parsed by `specs/specs-gen.c`. To generate code from
  scratch simply run `make specs_gen`, the code will be placed inside of `specs-code/`.

## Examples

The `examples/` folder is where place our up-to-date bot examples. 

When adding a new feature, it is encouraged that the contributor writes an example bot 
to demonstrate said feature, as a sort of makeshift test for other users and developers.

## APIs source-code

`discord-*.c`, `github-*.c`, `reddit-*.c`, and `slack-*.c` are the source 
files that handle all the logic behind their individual API wrapper.

<!-- THIS IS A WORK IN PROGRESS

# Choosing an Endpoint

Now that the boring reading stuff is out of the way, we can get to the fun
part: implementing an endpoint. First things first, we have to choose an endpoint
to implement. If you are following this guide and do not plan to implement a
GitHub API endpoint, don't fret, this guide aims to remain as website-independent 
as possible.

To find an endpoint to implement, head over to your chosen website's API 
documentation. This will at least require a simple Google search, but it may
require a bit of digging in some occasions. For this guide, we can use the 
GitHub API reference found [here](https://docs.github.com/en/rest/reference).

-->

If you have any questions, feel free to join our [Discord server](https://discord.gg/nBUqrWf).
