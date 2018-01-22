#include "mmu.h"

mmu_t* mmu_create()
{
    mmu_t* mmu = (mmu_t*)malloc(sizeof(mmu_t));
    return mmu;
}

void mmu_insert_rom(mmu_t* mmu, cartridge_t* cartridge)
{
    memcpy((void*)mmu->addr, (const void*)cartridge->rom, cartridge->size);
}
