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

    uint8_t a = mmu_read_addr8(mmu, 0x0104);
    uint16_t b = mmu_read_addr16(mmu, 0x0104);

    return 0;
}