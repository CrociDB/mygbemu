#include "sys.h"
#include "cartridge.h"

#include <string.h>

cartridge_t* cartridge_load(const char* filename)
{
    cartridge_t* c = NULL;
    FILE *file = NULL;

    fopen_s(&file, filename, "rb");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        uint32_t total = ftell(file);
        fseek(file, 0, SEEK_SET);
        if (total > 0)
        {
            c = (cartridge_t*)malloc(sizeof(cartridge_t));
            c->rom = (uint8_t*)malloc(sizeof(uint8_t) * total);
            c->size = total;
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
    if (c)
    {
        free(c->title);
        free(c->rom);
        free(c);
    }
}


