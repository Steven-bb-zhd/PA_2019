#include "cpu/instr.h"

make_instr_func(lgdt)
{
    OPERAND rel;
    rel.data_size=32;
    rel.type=OPR_IMM;
    rel.sreg=SREG_CS;
    rel.addr=eip+2;
    operand_read(&rel);
    uint16_t limit=0;
    uint32_t base=0;
    memcpy(&limit,hw_mem+rel.val,2);
    cpu.gdtr.limit=limit;
    if(data_size==16){
        memcpy(&base,hw_mem+rel.val+2,3);
        //printf("base_16=%x\n",base);
        cpu.idtr.base=base&0x00ffffff;
    }
    else{
        memcpy(&base,hw_mem+rel.val+2,4);
        //printf("base_32=%x\n",base);
        cpu.idtr.base=base;
    }
    return 6;
}