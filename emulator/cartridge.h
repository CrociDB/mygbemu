#ifndef _CARTRIDGE_H_
#define _CARTRIDGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _cartridge_t
{
    uint8_t* title;
    uint8_t* rom;
    uint32_t size;
} cartridge_t;

cartridge_t* cartridge_load(const char* filename);
void cartridge_free(cartridge_t* c);
void cartridge_run(cartridge_t* c);

#endif
