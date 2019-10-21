#include "cpu/instr.h"

static void instr_execute_1op(){
    operand_read(&opr_src);
    cpu.esp+=data_size/8;
    opr_dest.val=opr_src.val;
    //opr_dest.addr=cpu.esp;
    operand_write(&opr_dest);
}

make_instr_impl_1op(pop,r,v);

make_instr_func(pop_ebx_v){
    OPERAND opr_ebx;
    int len=1;
    opr_ebx.type=OPR_MEM;
    opr_ebx.data_size=data_size;
    opr_ebx.sreg=SREG_SS;
    opr_ebx.addr=cpu.esp;
    cpu.esp+=data_size/8;
    operand_read(&opr_ebx);
    if(data_size==16){
        cpu.ebx=(opr_ebx.val&0xffff)|(cpu.ebx&0xffff0000);
    }
    else
    {
        cpu.ebx=opr_ebx.val;
    }
    return len;
}