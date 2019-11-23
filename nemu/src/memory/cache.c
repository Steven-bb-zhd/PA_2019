#include "memory/cache.h"
#include "time.h"
#include "memory/memory.h"

Cacheline cache_block[1024];

void init_caache(){
    for(int i=0;i<1024;++i){
        cache_block[i].valid_bit=0;
    }
}

uint32_t addcache(paddr_t paddr , size_t len , Cacheline* cache){
    uint32_t group=(paddr>>6)&0x7f;
    for(int i=0;i<8;++i){
        if(cache_block[8*group+i].valid_bit==0){
            cache_block[8*group+i].valid_bit=1;
            uint32_t addr_temp=0;   
        }
    }
}

uint32_t cache_read(paddr_t paddr , size_t len , Cacheline* cache){
    uint32_t group=(paddr>>6)&0x7f;
    uint32_t sign=(paddr>>13)&0x7ffff;
    uint32_t rel=paddr&0x3f;
    if(rel==61||rel==62||rel==63){
        uint32_t res = hw_mem_read(paddr,len);
        return res;
    }
    uint32_t group_addr=0;
    bool find=false;
    for(int i=0;i<8;++i){
        if(cache_block[group*8+i].tag==sign){
            if(cache_block[group*8+i].valid_bit){
                find = true;
                group_addr=group*8+i;
                break;
            }
        }
    }
    if(!find){

    }
}