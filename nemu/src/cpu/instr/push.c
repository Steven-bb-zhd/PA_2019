#include "cpu/instr.h"

make_instr_fun(push_ebp_v){
    OPERAND opr_ebp;
    int len=1;
    opr_ebp.type=OPR_MEM;
    opr_ebp.data_size=data_size;
    opr_ebp.val=cpu.ebp;
    opr_ebp.sreg=SREG_SS;
    cpu.esp-=data_size/8;
    opr_ebp.addr=cpu.esp;
    print_asm_0("push   ebp","",len);
    return len;
}