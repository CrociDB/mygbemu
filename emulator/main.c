#include "sys.h"
#include "log.h"
#include "mmu.h"
#include "cpu.h"
#include "cartridge.h"

int main(int argc, const char* argv[]) 
{
    if (argc < 2)
    {
        sys_usage();
        exit(-1);
    }

    log_set_level(LOG_VERBOSE);

    mmu_t* mmu = mmu_create();
    cpu_t* cpu = cpu_create();

    //cartridge_t* rom = cartridge_load(argv[1]);

    mmu_load_bios(mmu);
    //cartridge_free(rom);

    //uint8_t a = mmu_read_addr8(mmu, 0x0104);
    //uint16_t b = mmu_read_addr16(mmu, 0x0104);

    //uint8_t c = mmu_read_byte(mmu, 0x0104);
    //uint16_t d = mmu_read_word(mmu, 0x0104);

    //// Writing test

    ////mmu_write_byte(mmu, 0xE56F, 0xF4);
    //mmu_write_addr8(mmu, 0xE56F, 0xF4);

    //uint8_t test = mmu_read_byte(mmu, 0xE56F);
    //uint8_t test2 = mmu_read_addr8(mmu, 0xE56F);

    //mmu_write_word(mmu, 0xFE62, 0x114A);
    //mmu_write_addr16(mmu, 0xFE62, 0x114A);

    //uint16_t test3 = mmu_read_word(mmu, 0xFE62);
    //uint16_t test4 = mmu_read_addr16(mmu, 0xFE62);

    // Testing memory after OAM

    //mmu_write_byte(mmu, 0xFF00, 0xA2);
    //mmu_write_addr16(mmu, 0xFE00, 0xFF);

    //uint8_t m = mmu_read_byte(mmu, 0xFF00);
    //uint8_t m2 = mmu_read_addr8(mmu, 0xFF00);

    cpu_reset(cpu);

    return 0;
}