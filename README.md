# A project to support using C for "high-level" programming

The project is spawned from cee.studio's internal project to replace
our C++ backend with C. By releasing it as an open source
project, we hope it serve the following goals:

1. Demonstrate how to implement/use containers in C

2. Make C easy to use for developing "high-level" programs

3. Create more opportunities for C lovers who want to use C but cannot
(or don't want to) get into embedded system developments


We think software development as a process, developers have different
primary concerns at different phases of the process. We intend to
provide sufficient support for using C in each phase. The following
are the primary phases:

* Proof of Concept (POC):
  The default settings should be easy to use to support a quick POC development. 
  The correctness of a POC is the primary concern, but performance and 
  memory usage are not.

* Testing:
  The primary concern, every line of essential code should be tested efficiently. 
  Immediate coverage feedback should be provided to support the primary concern.

* Optimizations:

   - Memory leak removal is considered as an optimization, API and
     tools should be provided to help diagnose and fix memory leaks
   
   - Peformance critical parts can be replaced easily with less abstract but more
     C idiomatic implementations.


The end goal: If you choose C to develop your "high level" programs
(e.g., web app backend), you get the freedom to choose high
development producitivity, or high software performance within the C
ecosystem.


Other considerations:
1. Readability and debuggability triumph over everything else
2. Use minimum syntax sugar, use modern IDE auto-completion
3. No premature abstraction, no premature optimization

Contirubtion are welcome, please join our discord: https://discord.gg/nBUqrWf