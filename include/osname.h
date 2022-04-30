#ifndef OSNAME_H
#define OSNAME_H 1


/* OS name detection macros */

#if defined _AIX 
#define OSNAME "AIX"
#endif

#if defined __ANDROID__
#define OSNAME "Android"
#endif

#if defined UTS
#define OSNAME "UTS"
#endif

#if defined aegis
#define OSNAME "aegis"
#endif

#if defined __BEOS__
#define OSNAME "__BEOS__"
#endif

#if defined __FreeBSD__
#define OSNAME "FreeBSD"
#endif

#if defined __NetBSD__
#define OSNAME "NetBSD"
#endif

#if defined __OpenBSD__
#define OSNAME "OpenBSD"
#endif

#if defined __bsdi__
#define OSNAME "BSD/OS"
#endif

#if defined __DragonFly__
#define OSNAME "DragonFly BSD"
#endif

#if defined __SYSTYPE_BSD
#define OSNAME "ULTRIX"
#endif

#if defined __convex__
#define OSNAME "ConvexOS"
#endif

#if defined __CYGWIN__
#define OSNAME "Windows NT (Cygwin)"
#endif

#if defined __DGUX__ || DGUX
#define OSNAME "DG/UX"
#endif

#if defined __SEQUENT__ || sequent
#define OSNAME "DYNIX/ptx"
#endif

#if defined __ECOS
#define OSNAME "eCos"
#endif

#if defined __EMX__
#define OSNAME "OS/2 (EMX)"
#endif

#if defined __gnu_hurd__
#define OSNAME "GNU/Hurd"
#endif

#if defined __gnu_linux__ || defined __linux__ || defined linux
#define OSNAME "GNU/Linux"
#endif

#if defined _hpux || defined hpux || defined __hpux
#define OSNAME "hp-ux"
#endif

#if defined __OS400__
#define OSNAME "OS/400"
#endif

#if defined __sgi || defined sgi
#define OSNAME "IRIX"
#endif

#if defined __INTEGRITY
#define OSNAME "INTEGRITY"
#endif

#if defined __Lynx__
#define OSNAME "LynxOS"
#endif

#if defined macintosh || defined Macintosh
#define OSNAME "Classic Mac OS"
#endif

#if defined __APPLE__ && defined __MACH__
#define OSNAME "Mac OS X"
#endif

#if defined __OS9000 || defined _OSK
#define OSNAME "OS-9"
#endif

#if defined __MORPHOS__
#define OSNAME "MorphOS"
#endif

#if defined mpeix || defined __mpexl
#define OSNAME "MPE/iX"
#endif

#if defined MSDOS || defined __MSDOS__ || defined _MSDOS || defined __DOS__
#define OSNAME "MS-DOS"
#endif

#if defined __TANDEM
#define OSNAME "NonStop OS"
#endif

#if defined OS2 || defined _OS2 || defined __OS2__ || defined __TOS_OS2__ 
#define OSNAME "OS/2"
#endif

#if defined EPLAN9
#define OSNAME "Plan 9"
#endif

#if defined __QNX__ || defined __QNXNTO__ 
#define OSNAME "QNX"
#endif

#if defined M_I386
#define OSNAME "SCO UNIX"
#endif

#if defined sun || defined __sun
#if defined __SVR4 || defined __svr4
#define OSNAME "Solaris"
#endif
#define OSNAME "SunOS"
#endif

#if defined __VOS__
#define OSNAME "VOS"
#endif

#if defined __osf__ || defined __osf
#define OSNAME "OSF/1"
#endif

#if defined ultrix || defined __ultrix || defined __ultrix__
#define OSNAME "ULTRIX"
#endif

#if defined sco || defined _UNIXWARE7
#define OSNAME "UnixWare"
#endif

#if defined VMS || defined __VMS
#define OSNAME "VMS"
#endif

#if defined __VM__
#define OSNAME "VM/CMS"
#endif

#if defined __MVS__
#define OSNAME "MVS"
#endif

#if defined __EDC_LE
#if not defined __VM__ || not defined __MVS__
#define OSNAME "VSE"
#endif
#endif

#ifndef OSNAME
#define OSNAME "POSIX"
#endif

#endif
