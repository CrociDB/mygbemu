#include "util.h"

// Check if the nth bit of a byte is one
bool util_check_bit(const uint8_t value, const uint8_t n)
{
    return (value & (1 << n)) != 0;
}

// Set the nth bit of the given byte to one
void util_set_bit(uint8_t* byte, const uint8_t n)
{
    (*byte) = (*byte) | (0x01 << n);
}

// Set the nth bit of the given byte to zero
void util_unset_bit(uint8_t* byte, const uint8_t n)
{
    (*byte) = (*byte) & ~(0x01 << n);
}
