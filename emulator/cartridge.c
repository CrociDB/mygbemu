#include "sys.h"
#include "cartridge.h"

#include <string.h>

cartridge_t* cartridge_load(const char* filename)
{
    cartridge_t* c = NULL;

    FILE *file = fopen(filename, "rb");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        uint8_t total = ftell(file);
        if (total > 0)
        {
            c = (cartridge_t*)malloc(sizeof(cartridge_t));
            c->rom = (uint8_t*)malloc(sizeof(uint8_t));
            c->size = total;
            fseek(file, 0, SEEK_SET);
            if (fread(c->rom, 1, total, file) != total)
            {
                free(c->rom);
                free(c);
                fclose(file);
                sys_error("Problem loading cartridge");
            }
            c->title = _strdup(filename);
        }
        fclose(file);
    } 

    return c;
}

void cartridge_free(cartridge_t* c)
{
    free(c->title);
    free(c->rom);
    free(c);
}


