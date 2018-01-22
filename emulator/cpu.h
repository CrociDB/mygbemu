#ifndef _CPU_H_
#define _CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _cpu_t
{
    // Clock time
    uint8_t m;
    uint8_t t;

    uint16_t sp;
    uint16_t pc;

    // AF
    struct
    {
        union
        {
            struct
            {
                uint8_t f;
                uint8_t a;
            };
            uint16_t af;
        };
    };
    // BC
    struct
    {
        union
        {
            struct
            {
                uint8_t c;
                uint8_t b;
            };
        };
        uint8_t bc;
    };
    // DE
    struct
    {
        union
        {
            struct
            {
                uint8_t e;
                uint8_t d;
            };
            uint16_t de;
        };
    };
    // HL
    struct
    {
        union
        {
            struct
            {
                uint8_t l;
                uint8_t h;
            };
            uint16_t hl;
        };
    };
} cpu_t;

cpu_t* cpu_create();
void cpu_reset(cpu_t* cpu);

#endif
