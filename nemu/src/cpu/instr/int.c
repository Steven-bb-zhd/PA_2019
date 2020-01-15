#include "cpu/instr.h"

make_instr_func(int){
    OPERAND imm;
    imm.type=OPR_IMM;
    imm.data_size=8;
    imm.sreg=SREG_CS;
    imm.addr=eip+1;
    operand_read(&imm);
    raise_sw_intr(imm.val);
    return 0;
}