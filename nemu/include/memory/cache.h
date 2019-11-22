#include "nemu.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct 
{
    uint8_t valid_bit;
    uint32_t In_addr;
    uint32_t Group_Num;
    uint32_t tag;
    uint8_t data[64];
}Cacheline;

Cacheline cacheblock[1024];

void init_cache();
uint32_t cache_read (paddr_t paddr , size_t len , Cacheline* cache);
void cache_write (paddr_t paddr , size_t len , uint32_t data, Cacheline * cache);