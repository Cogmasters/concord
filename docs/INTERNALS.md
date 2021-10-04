# Work in Progress

**This guide is currently incomplete**

# Introduction

If you are interested in contributing with more than just coding, you found the 
right place! The ultimate goal is to help you understand how Orca works internally, 
and as a result, write your own API endpoint. <!-- This guide will assist you with writing your first endpoint, we will be using the GitHub API but the same techniques should apply to any other API. -->

Before starting make sure you have followed the [build instructions](../README.md#build-instructions)!

## About Orca

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

- `specs/`: This is the folder we write our specs for code-generation, it contains multiple
  JSON templates that are parsed by `specs/specs-gen.c`. To generate code from
  scratch simply run `make specs_gen`, the code will be placed inside of `specs-code/`.

## Examples

The `examples/` folder is where we place our up-to-date bot examples. 

When adding a new feature it is encouraged that the contributor writes an example bot 
to demonstrate said feature, as a sort of makeshift test for other users and developers.

## APIs source-code

`discord-*.c`, `github-*.c`, `reddit-*.c`, and `slack-*.c` are the source 
files that handle all the logic behind their individual API wrapper.

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

For the purposes of this guide, we will be implementing [this](https://docs.github.com/en/rest/reference/repos#get-all-repository-topics) endpoint, which
will allow the programmer to retrieve the topics that are assigned to a repository.

# First steps
Now that we have the endpoint we want to implement, we can begin writing code. For
starters, we will want to edit the ``github.h`` header file so that others can use
our code.

```c
ORCAcode github_get_repository_topics(struct github *client, char* owner, char* repository);
```

Here, we define a function that returns an ``ORCACode``, and takes a structure named ``github``.
``ORCAcode`` is an integer that represents an error code from the request. The ``github``
structure, called the ``client`` in this function, acts as a storage device for information
that is required for sending requests.

Once this is added into ``github.h``, we can begin writing the function code that will
make it work underneath. Here is a skeleton of the function:

```c
ORCAcode github_get_repository_topics(struct github *client, char* owner, char* repository) {
    log_info("===github-get-repository-topics===");

    if (!owner) {
        log_error("missing 'owner'");
        return ORCA_MISSING_PARAMETER;
    }
    
    if (!repository) {
        log_error("missing 'repository'");
        return ORCA_MISSING_PARAMETER;
    }

    return ORCA_OK;
}
```

For starters, we make sure that the function that is being executed is logged. The reason
we do this is simply for purposes of debugging. Knowing **where** functions are running is
critical in debugging.

Next, we verify that the 'owner' and 'repository' strings are provided. These are required
for extracting topics from the correct repository, and so we must not allow the function to
run unless both are provided. Depending on the nature of the error, it may be desirable to
return something other than ``ORCA_MISSING_PARAMETER``. However, for most purposes, this is
fine. If there is a need for another error code, they can be found or added at ``common/types.h``.

When the function ends, we return ``ORCA_OK`` to signal that 'everything went well.'

# Extending our function
Now that the base skeleton is complete, we can continue on in finishing the function.
To start this chapter off, we will be utilizing the ``specs`` system described near the start
of this guide.

If we want this to be useful for users, it would be best to 'output' the response information
to the user, but parsed in a way that is easy to use for the user. To output the information,
however, we will need a location to output it **to.**

As said previously, we will have to utilize the ``specs`` system to generate structures that
can be used to store the topics in. Create a file in ``specs/github`` called ``repository.json.``
In this file, put the following code inside of it:

```json
{
    "title":"Topics Object",
    "namespace": ["github"],
    "comment": "https://docs.github.com/en/rest/reference/repos#get-all-repository-topics",
    "defs":
    [
        {
            "title": "Topic Structure",
            "struct": "topic",
            "fields":
            [
                { "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}
            ]
        }
    ]
}
```

This may seem complicated at first, but in reality it is quite simple. As explained at the
start of this guide, this JSON will be used to generate structures, enumerations, and functions
that are used internally and by the user.

If you have any questions, feel free to join our [Discord server](https://discord.gg/nBUqrWf).
