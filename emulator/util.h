#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdbool.h>
#include <stdint.h>

bool util_check_bit(const uint8_t value, const uint8_t n);

void util_set_bit(uint8_t* byte, const uint8_t n);
void util_unset_bit(uint8_t* byte, const uint8_t n);

#endif
