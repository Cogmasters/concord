# KNOWN BUGS

This file outlines the known bugs that are yet to be fixed

## Solaris
- Concord does not work on Solaris versions prior to 9, due to dependance
on newer C library functions. 

## z/OS
- If you use the IBM Metal C/C++ compiler, you need to force the usage of
the ASCII character set. No Makefile parameters or documentation notes
for this have been made.


## Big-endian CPUs
### [curl_websocket.c](./core/curl-websocket.c)
- There are several bugs in the CWS codebase that causes dependance on
little-endian CPUs. Despite making the obvious corrections (sus_imp0stor
rectified the issues), an unsolved bug (1/20/23) was spotted in the CWS
codebase that caused all opened websocket connections to close -- a fix
is under development and will be out soon.



