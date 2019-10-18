#include "cpu/instr.h"

make_instr_func(call_near){
    OPERAND rel,opr_eip;
    //int len=1;
    rel.type=OPR_IMM;
    rel.sreg=SREG_CS;
    rel.data_size=data_size;
    rel.addr=eip+1;
    operand_read(&rel);
    cpu.esp-=data_size/8;
    opr_eip.type=OPR_MEM;
    opr_eip.data_size=data_size;
    opr_eip.addr=cpu.esp;
    int offset=sign_ext(rel.val,rel.data_size);
    operand_read(&opr_eip);
    cpu.eip+=offset;
    opr_eip.val=cpu.eip;
    operand_write(&opr_eip);
    return 1+data_size/8;
}