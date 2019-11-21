#include "stdio.h"
#include "nemu.h"

strcut Cacheline{
    uint8_t valid_bit;
    uint32_t In_addr;
    uint32_t Group_Num;
    uint32_t tag;
    uint8_t data[64];
};