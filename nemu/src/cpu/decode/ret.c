#include "cpu/instr.h"

make_instr_func(ret_near){
    OPERAND opr_eip;
    opr_eip.type=OPR_MEM;
    opr_eip.data_size=data_size;
    opr_eip.addr=cpu.esp;
    opr_eip.sreg=SREG_SS;
    operand_read(&opr_eip);
    cpu.esp+=data_size/8;
    cpu.eip=opr_eip.val;
    return 5;
}