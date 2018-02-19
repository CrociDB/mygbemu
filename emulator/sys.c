#include "sys.h"
#include <stdlib.h>

void sys_usage()
{
    printf("%s v%s - Usage: \n", SYS_NAME, SYS_VERSION);
    printf(SYS_USAGE);
}

void sys_error(const char* msg, ...)
{
    char buffer[0xFF];
    va_list argptr;
    va_start(argptr, msg);
#ifdef WINDOWS
    vsprintf_s(buffer, 0xFF, msg, argptr);
#else
    vsprintf(buffer, msg, argptr);
#endif
    printf("%s v%s - Error: %s \n", SYS_NAME, SYS_VERSION, buffer);
    va_end(argptr);

    exit(-1);
}
