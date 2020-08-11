# The Design Goals and Principles

## Goals
*  Easy to maniupate strings 
*  Ready to use vector, set, map, stack, and dict

## Design principles

*  Standard C functions should be directly appliable to memory layout equivalent cee structs,
   e.g. all C standard string functions can be applied directly to `cee_str *`.
   
*  Easy to build correct Proof of Concept (POC) by using the default settings,
   e.g. memory leaks are considered benign in POC.

*  Easy things should be easy and hard things should be possible.

*  Memory leak removal is considered as an optimization, it should be
   handled easily in later iterations with advanced tooling like 
   https://cee.studio, valgrind, or ASAN.

*  Performance optimziation should be easy to do by removing abstraction
