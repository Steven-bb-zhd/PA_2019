#include "cpu/instr.h"

make_instr_func(iret_v){
    OPERAND opr_eip,opr_cs,opr_eflags;

    opr_eip.type=OPR_MEM;
    opr_eip.sreg=SREG_SS;
    opr_eip.data_size=32;
    opr_eip.addr=cpu.esp;
    operand_read(&opr_eip);
    cpu.esp+=2;
    cpu.eip=opr_eip.val;

    opr_cs.type=OPR_MEM;
    opr_cs.sreg=SREG_SS;
    opr_cs.data_size=32;
    opr_cs.addr=cpu.esp;
    operand_read(&opr_cs);
    cpu.esp+=4;
    cpu.cs=opr_cs.val&0xffff;


}