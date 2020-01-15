#include "cpu/instr.h"

make_instr_func(lidt)
{
    OPERAND rel;
    int len=1;
    rel.data_size=data_size;
    len+=modrm_rm(eip+1,&rel);
    uint16_t limit=0;
    uint32_t base=0;
    limit=laddr_read(rel.addr,2);
    cpu.idtr.limit=limit;
    if(data_size==16){
        base=laddr_read(rel.addr+2,3);
        //printf("base_16=%x\n",base);
        cpu.idtr.base=base&0xffffff;
    }
    else{
        base=laddr_read(rel.addr+2,4);
        //printf("base_32=%x\n",base);
        cpu.idtr.base=base;
    }
    return len;
}