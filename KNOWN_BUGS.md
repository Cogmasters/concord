# KNOWN BUGS

This file outlines the known bugs that are yet to be fixed

## Cygwin

### [user-agent.c](core/user-agent.c)

|                                 behavior                                                       |           temporary work-around            |
| ---------------------------------------------------------------------------------------------- | ------------------------------------------ |
| Freeing a libcurl's `struct curl_slist` node at `ua_conn_add_header()` will abort the program. | Free is guarded with a `#ifndef __CYGWIN__ |
