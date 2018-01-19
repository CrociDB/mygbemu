#include "main.h"

void sys_usage()
{
    printf(SYS_USAGE_INSTRUCTIONS);
}

int main(int argc, const char* argv) 
{
    if (argc < 2)
    {
        sys_usage();
        exit(-1);
    }

    

    return 0;
}