#include "sys.h"
#include "cartridge.h"

int main(int argc, const char* argv[]) 
{
    if (argc < 2)
    {
        sys_usage();
        exit(-1);
    }

    cartridge_t *rom = cartridge_load(argv[1]);
    cartridge_free(rom);

    return 0;
}