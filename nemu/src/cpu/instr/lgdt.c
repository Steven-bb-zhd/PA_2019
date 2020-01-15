#include "cpu/instr.h"

make_instr_func(lgdt)
{
    OPERAND rel;
    int len=1;
    rel.data_size=data_size;
    len+=modrm_rm(eip+1,&rel);
    uint16_t limit=0;
    uint32_t base=0;
    limit=laddr_read(rel.addr,2);
    cpu.gdtr.limit=limit;
    if(data_size==16){
        base=laddr_read(rel.addr+2,3);
        //printf("base_16=%x\n",base);
        cpu.gdtr.base=base&0xffffff;
    }
    else{
        base=laddr_read(rel+2,4);
        //printf("base_32=%x\n",base);
        cpu.gdtr.base=base;
    }
    return len;
}