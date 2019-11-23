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
    uint32_t x=0;
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

uint32_t cache_read (paddr_t paddr , size_t len , Cacheline* cache){
    uint32_t group_num=(paddr>>6)&0x7f;
    uint32_t tag=(paddr>>13)&0x7ffff;
    uint32_t rel=paddr&0x3f;
    if(rel==61||rel==62||rel==63){
        uint32_t res=0;
        res=hw_mem_read(paddr,len);
        return res;
    }
    bool find=false;
    for(int i=0;i<8;++i){
        if(cache_block[8*group_num+i].valid_bit&&(cache_block[8*group_num+i].tag==tag)){
            find=true;
            uint32_t res=0;
            memcpy((void*)res,(void*)cache_block[8*group_num+i].data+rel,len);
            return res;
        }
    }
    if(!find){
        uint32_t key=notfind(paddr,len,cache,tag);
        uint32_t res=0;
        memcpy((void*)res,(void*)cache_block[key].data+rel,len);
        return res;
    }
}

void cache_write (paddr_t paddr , size_t len , uint32_t data, Cacheline * cache){
    hw_mem_write(paddr,len,data);
    uint32_t group_num=(paddr>>6)&0x7f;
    uint32_t tag=(paddr>>13)&0x7ffff;
    uint32_t rel=paddr&0x3f;
    for(int i=0;i<8;++i){
        if(cache_block[8*group_num+i].valid_bit&&(cache_block[8*group_num+i].tag==tag)){
            if((len+rel)<=64){
                memcpy(cache_block[8*group_num+i].data+rel,&data,len);
            }
            else{
                uint32_t over=0;
                over=len+rel-64;
                uint32_t over_data=0;
                if(over==3)
                    over_data=(data&0xffffff00)>>8;
                else if(over==2)
                    over_data=(data&0xffff0000)>>16;
                else if(over==1)
                    over_data=(data&0xff000000)>>24;
                cache_write(paddr+4-over,over,over_data,cache);
            }
        }
    }
}