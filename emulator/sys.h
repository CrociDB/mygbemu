#ifndef _SYS_H_
#define _SYS_H_

#include <stdio.h>
#include "log.h"

static const char* SYS_NAME = "MyGBEmu";
static const char* SYS_VERSION = "v0.1";
static const char* SYS_USAGE = "\t $ mygbemu rom.gb\n";

void sys_usage();
void sys_error(const char* msg);

#endif
