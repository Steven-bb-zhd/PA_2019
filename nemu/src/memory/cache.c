#include "memory/cache.h"
#include "time.h"
#include "memory/memory.h"

Cacheline cache_block[1024];

void init_caache(){
    for(int i=0;i<1024;++i){
        cache_block[i].valid_bit=0;
    }
}

uint32_t notfind(paddr_t paddr , size_t len , Cacheline* cache, uint32_t tag){
    uint32_t group=(paddr>>6)&0x7f;
    for(int i=0;i<8;++i){
        if(cache_block[8*group+i].valid_bit==0){
            cache_block[8*group+i].valid_bit=1;
            cache_block[8*group+i].tag=tag;
            uint32_t addr_temp=0;
            addr_temp=paddr&0xffffffc0;
            for(int j=0;j<64;++j){
                cache_block[8*group+i].data[j]=hw_mem_read(addr_temp,1);
                addr_temp+=1;
            }
            return 8*group+i;
        }
    }
    srand((unsigned)time(0));
    int x=0;
    x=rand()%8;
    cache_block[8*group+x].valid_bit=1;
    cache_block[8*group+x].tag=tag;
    uint32_t addr_temp=0;
    addr_temp=paddr&0xffffffc0;
    for(int j=0;j<64;++j){
        cache_block[8*group+x].data[j]=hw_mem_read(addr_temp,1);
        addr_temp+=1;
    }
    return 8*group+x;
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
        group_addr=notfind(paddr,len,cache,sign);
    }
    uint32_t res=0;
    memcpy(&res,cache[group_addr].data+rel,len);
    return res;
}

void cache_write(paddr_t paddr , size_t len , uint32_t data, Cacheline * cache){
    hw_mem_write(paddr,len,data);
    uint32_t group=(paddr>>6)&0x7f;
    uint32_t sign=(paddr>>13)&0x7ffff;
    uint32_t rel=paddr&0x3f;
    for(int i=0;i<8;++i){
        if(cache_block[8*group+i].tag==sign&&cache_block[8*group+i].valid_bit){
            if(rel+len<=64){
                memcpy(cache_block[8*group+i].data+rel,&data,len);
            }
            else{
                uint32_t over_limit=0;
                over_limit=64-rel;
                uint32_t data2=0;
                data2=data>>(8*over_limit);
                cache_write(paddr+over_limit,len-over_limit,data2,cache);
            }
        }
    }
}