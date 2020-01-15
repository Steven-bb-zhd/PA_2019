#include "cpu/instr.h"
#include "cpu/intr.h"

make_instr_func(int_){
    OPERAND imm;
    imm.type=OPR_IMM;
    imm.data_size=8;
    imm.sreg=SREG_CS;
    imm.addr=eip+1;
    operand_read(&imm);
    print_asm_1("int","",2,&imm);
    raise_sw_intr(imm.val);
    return 0;
}