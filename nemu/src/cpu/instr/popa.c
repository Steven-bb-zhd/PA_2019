#include "cpu/instr.h"

make_instr_func(popa_v){
    print_asm_0("popa","",1);
    OPERAND reg[8];
    for(int i=0;i<8;++i){
        reg[i].data_size=data_size;
        reg[i].sreg=SREG_SS;
        reg[i].type=OPR_MEM;
    }

    for (int i = 7; i >= 0; --i){
        reg[i].addr=cpu.esp;
        cpu.esp += data_size / 8;
        operand_read(&reg[i]);
    }
}