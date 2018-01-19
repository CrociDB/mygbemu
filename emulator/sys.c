#include "sys.h"
#include <stdlib.h>

void sys_usage()
{
    printf("%s v%s - Usage: \n", SYS_NAME, SYS_VERSION);
    printf(SYS_USAGE);
}

void sys_error(const char* msg)
{
    printf("%s v%s - Error: %s \n", SYS_NAME, SYS_VERSION, msg);
    exit(-1);
}
