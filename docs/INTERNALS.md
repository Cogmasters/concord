# Concord Internals Guide

## Introduction

If you are interested in contributing with more than just coding, you've found the 
right place! This guide aims to help you understand how Concord works internally, 
and as a result, enable you to extend its functionality by implementing new API endpoints
or improving existing ones.

Before starting, make sure you have followed the [build instructions](../README.md#build-instructions)!

## About Concord

Concord is a Discord API wrapper written entirely in C99. It provides asynchronous, 
minimal-dependency access to Discord's REST API and Gateway events. The library is
designed with the following principles in mind:

- **Low-level API access**: Concord provides a direct translation of Discord's API to C
- **Performance**: Minimizing memory footprint and CPU usage is a priority
- **Portability**: Works across multiple platforms with minimal dependencies
- **Comprehensive coverage**: Aims to support all Discord API features

## Project Structure

Here's a breakdown of the main directories and their purpose:

```
concord/
├── core/           # Core functionality (WebSockets, REST, etc.)
├── discord/        # Discord API public header files
├── docs/           # Documentation, guides, and roadmaps
├── examples/       # Example bots demonstrating various features
├── gencodecs/      # Code generation for API objects
├── include/        # Public API headers
├── licenses/       # License files
├── src/            # Discord API implementation
└── test/           # Test utilities and cases
```

## Core Components

### Gencodecs

Wrapping an API object in C can quickly get overwhelming and repetitive, considering 
one has to address many things modern languages take for granted, such as encoding 
or decoding an object with JSON. For this purpose, we created our own tool
for wrapping and generating API objects.

- `gencodecs/`: This folder contains definitions for code-generation, with 
  gencodecs macros that are fed to `gencodecs/Makefile`. The generated
  code will be located at `gencodecs/discord-codecs.h` and `gencodecs/discord-codecs.c`.

When implementing a new API endpoint, you'll typically need to:

1. Define the request/response structures in gencodecs
2. Generate the code with the Makefile
3. Use the generated structures in your implementation

### Examples

The `examples/` folder contains up-to-date bot examples demonstrating various features.

When adding a new feature, we strongly encourage contributors to write an example bot 
to demonstrate its usage. These examples serve as practical tests and documentation
for other users and developers.

Good examples should:
- Be minimal but complete
- Include comments explaining key concepts
- Handle errors gracefully
- Follow our [coding guidelines](CODING_GUIDELINES.md)

### API Source Code

The `src/` folder contains all Discord API wrapping logic organized by resource type. 
The organization generally follows Discord's API documentation structure.

When implementing a new endpoint:
1. Identify the appropriate file for your endpoint (e.g., guild-related endpoints go in `guild.c`)
2. Follow the pattern used by similar endpoints in that file
3. Implement both synchronous and asynchronous versions where appropriate
4. Add proper documentation comments

### Common Source Code

The `core/` folder contains Concord's core logic, including:

- WebSockets handling (connecting to Discord's Gateway)
- REST API client (making HTTP requests to Discord's API)
- Thread pool management
- Event handling
- JSON parsing and generation
- Logging systems

Understanding these components is essential when implementing new API features, as they
provide the foundation for all Discord interactions.

## Development Workflow

### Implementing a New API Endpoint

When implementing a new Discord API endpoint, follow these general steps:

1. **Research**: Understand the endpoint from Discord's API documentation
2. **Structure Definition**: Define request/response structures in gencodecs
3. **Implementation**: Write the function in the appropriate source file
4. **Documentation**: Add Doxygen comments for your function
5. **Testing**: Create or update examples to test your implementation
6. **Update Roadmap**: Mark your endpoint as implemented in [DISCORD_ROADMAP.md](DISCORD_ROADMAP.md)

### Debugging Tips

When debugging issues in Concord:

1. Use the logging system to trace execution flow:
   ```c
   logmod_log(INFO, NULL, "Processing data: %s", data);
   ```

2. For memory-related issues, use Valgrind as described in our [debugging guide](guides/debugging.md)

3. For segmentation faults, use GDB to identify the exact location:
   ```bash
   gdb ./yourbot
   (gdb) run
   # When the segfault occurs:
   (gdb) bt
   ```

4. Enable verbose logging in your bot configuration:
   ```json
   {
     "log": {
       "level": "TRACE",
       "trace": "debug.log"
     }
   }
   ```

## Contribution Process

1. Fork the repository
2. Create a feature branch with a descriptive name
3. Implement your changes following our [coding guidelines](CODING_GUIDELINES.md)
4. Test thoroughly
5. Submit a pull request with [semantic commit messages](CONTRIBUTING.md#semantic-commit-messages)

## Getting Help

If you have any questions about Concord's internals or need assistance with development,
feel free to:

- Join our [Discord server](https://discord.gg/Y7Xa6MA82v)
- Open an issue on GitHub for technical discussions
- Review existing code for patterns and approaches

Remember that everyone in the community was once new to the project - don't hesitate
to ask questions!
