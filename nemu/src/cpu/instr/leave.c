#include "cpu/instr.h"

make_instr_func(leave){
    OPERAND opr_ebp;
    int len=1;
    opr_ebp.type=OPR_MEM;
    opr_ebp.data_size=data_size;
    opr_ebp.sreg=SREG_SS;
    cpu.esp=cpu.ebp;
    opr_ebp.addr=cpu.esp;
    operand_read(&opr_ebp);
    cpu.ebp=opr_ebp.val;
    cpu.esp+=data_size/4;
    print_asm_0("leave","",len);
    return len;
}