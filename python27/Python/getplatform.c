
#include "Python.h"

#ifdef __ANDROID__
#include <sys/utsname.h>
#include <string.h>

char _PLATFORM[SYS_NMLN*2+2]={0}; // taken as base linux-armv7l-2.6

const char *
Py_GetPlatform(void)
{
    if (_PLATFORM[0]!=0)
        return _PLATFORM;

    struct utsname u;
    int i;
    if ( uname(&u) < 0 )
        return "unknown";

    strcat (_PLATFORM, u.sysname);
    strcat (_PLATFORM, "-");
    strcat (_PLATFORM, u.machine);
    for (i=0; _PLATFORM[i]; i++)
        _PLATFORM[i]=tolower(_PLATFORM[i]);
    return _PLATFORM;
}
#else

#ifndef PLATFORM
#define PLATFORM "unknown"
#endif

const char *
Py_GetPlatform(void)
{
    return PLATFORM;
}
#endif
