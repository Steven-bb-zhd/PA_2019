#include "cpu/instr.h"

make_instr_func(ret_near){
    OPERAND opr_eip;
    opr_eip.type=OPR_MEM;
    opr_eip.data_size=data_size;
    operand_read(&opr_eip);
    cpu.eip=opr_eip.val;
    cpu.esp+=data_size/8;
    opr_eip.addr=cpu.esp;
    operand_write(&opr_eip);
    return 1;
}