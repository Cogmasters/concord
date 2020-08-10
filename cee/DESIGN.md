# Cee: a single file C library to provide similiar functionalities of C++ STL


## goals
*  Easy to maniupate strings 
*  Ready to use vector, set, map, stack, and dict


## The design principles

*  Standard C functions should be directly appliable to memory layout equivalent cee structs,
   e.g. all C standard string functions can be applied directly to `cee_str *`.
   
*  Easy to build correct POC by using the default settings,
   e.g. memory leaks are considered benign in POC.

*  Easy things should be easy and hard things should be possible,
   e.g. memory leaks can be detected and fixed with the help of
   https://cee.studio, ASAN, or valgrind


## Later iterations

* Memory leak removal is considered as an optimization, it should be
   handled in later iterations.
* Performance optimziation should be easy to do.
