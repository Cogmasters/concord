# Orca: a project to support C for high-level programming

Software development is a process, developers have different primary
concerns at different phases of the process. We need to provide
sufficient support for each phase. The following are the primary
phases:

* POC:
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
