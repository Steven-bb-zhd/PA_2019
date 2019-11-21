#include<stdint.h>

typedef strcut{
    uint8_t valid_bit;
    uint32_t In_addr;
    uint32_t Group_Num;
    uint32_t tag;
    uint8_t data[64];
}Cacheline;