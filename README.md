# A project to support using C for high-level programming

The project is spawned from our internal projects to replace our C++ backend
with C code. We hope it serves the following goals:

1. Demonstrate how to implement/use containers in C

2. Make C easy to use for developing "high-level" programs

3. Create more opportunities for C lovers who want to use C but cannot
(or don't want) get into embedded system developments


Software development is a process, developers have different primary
concerns at different phases of the process. We need to provide
sufficient support for using C in each phase. The following are the
primary phases:

* Proof of Concept (POC):
  The default settings should be easy to use to support a quick POC development. 
  The correctness of a POC is the primary concern, but performance and 
  memory usage are not.

* Testing:
  The primary concern, every line essential code should be tested efficiently. 
  Immediate coverage feedback should be provided to support the primary concern. 

* Optimizations:

   - Memory leak removal is considered as an optimization, API and
     tools should be provided to help diagnose and fix memory leaks and double free
   
   - Peformance critical parts can be replaced easily with more C
     idiomatic implementations.



Other considerations:
1. Readability and debuggability triumph over everything else
2. Use minimum syntax sugar, use modern IDE auto-completion
3. No premature abstraction, no premature optimization

Contirubtion are welcome, Join our discord: https://discord.gg/nBUqrWf
