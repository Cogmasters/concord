#ifndef OSNAME_H
#define OSNAME_H 1

/* 
 * HackerSmacker's "Detect-It-All" OS Detector
 */

enum OSClass {
	UNIX,
	WINDOWS,
	DOS,
	OS2,
	S370,
	DEC,
	MACINTOSH,
	AMIGA,
	OTHER
};

/* IBM AIX */
#ifdef _AIX 
#define OSNAME "AIX"
#define OSCLASS UNIX
#endif

/* Google Android */
#ifdef __ANDROID__
#define OSNAME "Android"
#define OSCLASS UNIX
#endif

/* Amdahl UTS */
#ifdef UTS
#define OSNAME "UTS"
#define OSCLASS UNIX
#endif

/* Apollo/Domain Aegis */
#ifdef aegis
#define OSNAME "Aegis"
#define OSCLASS UNIX
#endif

/* Be Software Inc. BeOS */
#ifdef __BEOS__
#define OSNAME "BeOS"
#define OSCLASS OTHER
#endif

/* Haiku Project */
#ifdef __HAIKU__
#define OSNAME "Haiku"
#define OSCLASS OTHER
#endif

/* FreeBSD */
#ifdef __FreeBSD__
#define OSNAME "FreeBSD"
#define OSCLASS UNIX
#endif

/* NetBSD */
#ifdef __NetBSD__
#define OSNAME "NetBSD"
#define OSCLASS UNIX
#endif

/* OpenBSD */
#ifdef __OpenBSD__
#define OSNAME "OpenBSD"
#define OSCLASS UNIX
#endif

/* BSDi BSD/OS or BSD/386 */
#ifdef __bsdi__
#define OSNAME "BSD/OS"
#define OSCLASS UNIX
#endif

/* DragonFly BSD */
#ifdef __DragonFly__
#define OSNAME "DragonFly BSD"
#define OSCLASS UNIX
#endif

/* Convex OS */
#ifdef __convex__
#define OSNAME "ConvexOS"
#define OSCLASS UNIX
#endif

/* Windows NT running Cygwin */
#ifdef __CYGWIN__
#define OSNAME "Windows NT (Cygwin)"
#define OSCLASS UNIX
#endif

/* Data General UNIX */
#if defined __DGUX__ || DGUX
#define OSNAME "DG/UX"
#define OSCLASS UNIX
#endif

/* Sequent Labs DYNIX/ptx */
#if defined __SEQUENT__ || sequent
#define OSNAME "DYNIX/ptx"
#define OSCLASS UNIX
#endif

/* eCos */
#ifdef __ECOS
#define OSNAME "eCos"
#define OSCLASS OTHER
#endif

/* OS/2 running EMX */
#ifdef __EMX__
#define OSNAME "OS/2 (EMX)"
#define OSCLASS UNIX
#endif

/* GNU/Hurd */
#ifdef __gnu_hurd__
#define OSNAME "GNU/Hurd"
#define OSCLASS UNIX
#endif

/* Linux */
/* Any of these macros here can imply Linux. */
#if defined __gnu_linux__ || defined __linux__ || defined linux
#define OSNAME "GNU/Linux"
#define OSCLASS UNIX
#endif

/* HP-UX (GNU C and aCC macros) */
#if defined _hpux || defined hpux || defined __hpux
#define OSNAME "HP-UX"
#define OSCLASS UNIX
#endif

/* IBM OS/400 (PASE) */
#ifdef __OS400__
#define OSNAME "OS/400"
#define OSCLASS OTHER
#endif

/* Silicon Graphics IRIX */
#if defined __sgi || defined sgi
#define OSNAME "IRIX"
#define OSCLASS UNIX
#endif

/* Green Hills INTEGRITY */
#ifdef __INTEGRITY
#define OSNAME "INTEGRITY"
#define OSCLASS OTHER
#endif

/* Lynx Software LynxOS */
#ifdef __Lynx__
#define OSNAME "LynxOS"
#define OSCLASS OTHER
#endif

/* Traditional Mac OS (before the Mach/UNIX OS X) */
/* Either macro can imply this */
#if defined macintosh || defined Macintosh
#define OSNAME "Classic Mac OS"
#define OSTYPE MACINTOSH
#endif

/* Apple OS X */
/* Requires both __APPLE__ and __MACH__ but not __osf or __osf__ */
#if defined __APPLE__ && defined __MACH__
#define OSNAME "Mac OS X"
#define OSCLASS UNIX
#endif

/* Microware OS-9 */
#if defined __OS9000 || defined _OSK
#define OSNAME "OS-9"
#define OSCLASS OTHER
#endif

/* MorphOS */
#ifdef __MORPHOS__
#define OSNAME "MorphOS"
#define OSCLASS AMIGA
#endif

/* AmigaOS */
#if defined AMIGA || defined __amigaos__
#define OSNAME "AmigaOS"
#define OSCLASS AMIGA
#endif

/* HP MPE/iX or MPE/XL */
#if defined mpeix || defined __mpexl
#define OSNAME "MPE"
#define OSCLASS OTHER
#endif

/* MS-DOS (any compiler) */
#if defined MSDOS || defined __MSDOS__ || defined _MSDOS || defined __DOS__
#define OSNAME "MS-DOS"
#define OSCLASS DOS
#endif

/* Tandem NonStop OS */
#ifdef __TANDEM
#define OSNAME "NonStop OS"
#define OSCLASS OTHER
#endif

/* IBM OS/2 (any compiler) */
#if defined OS2 || defined _OS2 || defined __OS2__ || defined __TOS_OS2__ 
#define OSNAME "OS/2"
#define OSCLASS OS2
#endif

/* Plan 9 */
#ifdef EPLAN9
#define OSNAME "Plan 9"
#define OSCLASS OTHER
#endif

/* Quantum Software Systems QNX */
#if defined __QNX__ || defined __QNXNTO__ 
#define OSNAME "QNX"
#define OSCLASS UNIX
#endif

/* SCO UNIX (note: this macro does not work on all compilers) */
#ifdef M_I386
#define OSNAME "SCO UNIX"
#define OSCLASS UNIX
#endif

/* Solaris (based on SVR4) and SunOS (based on BSD) */
#if defined sun || defined __sun
#if defined __SVR4 || defined __svr4
#define OSNAME "Solaris"
#define OSCLASS UNIX
#endif
#define OSNAME "SunOS"
#define OSCLASS UNIX
#endif

/* Stratus VOS and OpenVOS */
#ifdef __VOS__
#define OSNAME "VOS"
#define OSCLASS OTHER
#endif

/* Digital Equipment Corp. OSF/1 */
#if defined __osf__ || defined __osf
#define OSNAME "OSF/1"
#define OSCLASS UNIX
#endif

/* Digital Equipment Corp. ULTRIX */
#if defined ultrix || defined __ultrix || defined __ultrix__ || __SYSTYPE_BSD
#define OSNAME "ULTRIX"
#define OSCLASS UNIX
#endif

/* SCO UnixWare 7 */
#if defined sco || defined _UNIXWARE7
#define OSNAME "UnixWare"
#define OSCLASS UNIX
#endif

/* Digital Equipment Corp. VMS (Compaq/HP/VSI OpenVMS) */
#if defined VMS || defined __VMS
#define OSNAME "VMS"
#define OSCLASS VMS
#endif

/* IBM VM/CMS (VM/370, VM/SP, VM/HPO, VM/XA, VM/ESA, z/VM) */
#ifdef __VM__
#define OSNAME "VM/CMS"
#define OSCLASS S370
#endif

/* IBM MVS (MVS/370, MVS/SP, MVS/XA, MVS/ESA, OS/390, z/OS) */
#ifdef __MVS__
#define OSNAME "MVS"
#define OSCLASS S370
#endif

/* IBM VSE (DOS/VS, DOS/VSE, VSE/SP, VSE/ESA, z/VSE, VSEn) */
/* Note that the other two 370 OSes define __EDC_LE too, we must 
 * distinguish between the two with a macro that rules them out. */
#ifdef __EDC_LE
#ifndef __VM__
#define OSNAME "VSE"
#define OSCLASS S370
#endif
#ifndef __MVS__ 
#define OSNAME "VSE"
#define OSCLASS S370
#endif
#endif

/* Burroughs/Unisys MCP */
#if defined __MCP__
#define OSNAME "MCP"
#define OSCLASS OTHER
#endif

/* Novell NetWare */
#if defined _NETWARE_ || defined __NETWARE__
#define OSNAME "NetWare"
#define OSCLASS OTHER
#endif

/* NeXT Software NeXTSTEP/OPENSTEP */
/* Note that __MACH__ is defined on a lot of systems, so
 * we must rule out OS X, Hurd, and OSF/1 with the other
 * macros here. */
#if defined __MACH__ && defined NeXT
#ifndef __APPLE__
#define OSNAME "NeXTSTEP"
#define OSCLASS UNIX
#endif
#endif

/* Pyramid DC/OSx */
#ifdef pyr
#define OSNAME "DC/OSx"
#define OSCLASS UNIX
#endif

/* Siemens SINIX and Reliant UNIX */
#if defined sinux || defined sinix
#define OSNAME "Reliant UNIX"
#define OSCLASS UNIX
#endif

/* Cray UNICOS */
#ifdef _UNICOS
#define OSNAME "UNICOS"
#define OSCLASS UNIX
#endif

/* Cray UNICOS/mp */
#if defined _CRAY || defined _crayx1
#define OSNAME "UNICOS/mp"
#define OSCLASS UNIX
#endif

/* Windows NT running U/Win */
#ifdef _UWIN
#define OSNAME "Windows NT (U/Win)"
#define OSCLASS WINDOWS
#endif

/* Windows NT running Interix */
/* This is also called the "Subsystem for UNIX-Based Applications" */
#ifdef __INTERIX
#define OSNANE "Windows NT (Interix)"
#define OSCLASS UNIX
#endif

/* VxWorks */
#if defined __VXWORKS__ || defined __vxworks
#define OSNAME "VxWorks"
#define OSCLASS OTHER
#endif

/* Windows CE and Windows Embedded Compact */
#ifdef _WIN32_WCE
#define OSNAME "Windows CE"
#define OSCLASS WINDOWS
#endif

/* Windows 9x and Windows NT */
#if defined _WIN32 | defined _WIN64 | defined __WIN32__
#define OSNAME "Windows NT"
#define OSCLASS WINDOWS
#endif

/* 16-bit Windows */
#ifdef _WIN16
#define OSNAME "Windows 3.x"
#define OSCLASS WINDOWS
#endif

/* MINIX */
#ifdef __minix
#define OSNAME "Minix"
#define OSCLASS UNIX
#endif

/* Fall-through case */
#ifndef OSNAME
#define OSNAME "POSIX"
#define OSCLASS UNIX
#endif

#endif
