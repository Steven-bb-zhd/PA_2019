#include "cpu/instr.h"

make_instr_func(pusha){
    print_asm_0("pusha","",1);
    OPERAND reg[8];
    for(int i=0;i<8;++i){
        reg[i].type=OPR_REG;
        reg[i].data_size=data_size;
        reg[i].addr=i;
        reg[i].sreg=SREG_SS;
        operand_read(&reg[i]);
    }

    if(data_size==16){
        reg[REG_ESP].val=cpu.esp&0xffff;
    }
    else
    {
        reg[REG_ESP].val=cpu.esp;
    }
    for(int i=0;i<8;++i){
        reg[i].type=OPR_MEM;
        cpu.esp -= data_size / 8;
        reg[i].addr=cpu.esp;
        operand_write(&reg[i]);
    }
    
    return 1;

}