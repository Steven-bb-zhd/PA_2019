#include "cpu/instr.h"

make_instr_func(ret_near){
    OPERAND opr_eip;
    opr_eip.type=OPR_MEM;
    opr_eip.data_size=data_size;
    operand_read(&opr_eip);
    cpu.esp+=data_size/8;
    opr_eip.addr=cpu.esp;
    cpu.eip=eip;
    operand_write(&opr_eip);
    return 1;
}