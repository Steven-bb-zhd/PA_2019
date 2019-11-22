#include "memory/cache.h"
#include "time.h"
#include "memory/memory.h"


void init_caache(){
    for(int i=0;i<1024;++i){
        cache[i].valid_bit=0;
    }
}

uint32_t cache_read(paddr_t paddr , size_t len , Cacheline* cache){
    uint32_t group=(paddr>>6)&0x7f;
    uint32_t sign=(paddr>>13)&0x7ffff;
    uint32_t rel=paddr&0x3f;
    if(rel==61||rel==62||rel==63){
        
    }
}