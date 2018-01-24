#ifndef _CPU_H_
#define _CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef union _reg16_t
{
    struct
    {
        uint8_t lo;
        uint8_t hi;
    };
    uint16_t word;
} reg16_t;

typedef struct _cpu_t
{
    uint8_t m;
    uint8_t t;
    
    struct
    {
        reg16_t af, bc, de, hl;
        reg16_t sp, pc;
    } reg;
    
} cpu_t;

cpu_t* cpu_create();
void cpu_reset(cpu_t* cpu);

#endif
