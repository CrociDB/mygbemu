#include "sys.h"
#include "mmu.h"
#include "cartridge.h"

int main(int argc, const char* argv[]) 
{
    if (argc < 2)
    {
        sys_usage();
        exit(-1);
    }

    mmu_t* mmu = mmu_create();

    cartridge_t* rom = cartridge_load(argv[1]);

    mmu_insert_rom(mmu, rom);
    cartridge_free(rom);

    return 0;
}