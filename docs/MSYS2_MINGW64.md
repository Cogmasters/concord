# Concord on Windows with Mingw64 or Msys2
At the present, there are a few issues that prevent Concord from working properly on Mingw64 or Msys2. The first issue is
neither environment's libcurl implementation will natively fetch SSL certificates from the Windows SSL root chain by 
default. There is a way to rectify this, but it is rather inopportune and should not be done. However, neither environment
can easily link against a Windows-native MSVC-compiled version of libcurl. This is due to object file differences. It *is*
possible, but __highly__ unrecommended. For now, please consider using Cygwin. 

#### WSL is not considered Windows, but Linux entirely. 
