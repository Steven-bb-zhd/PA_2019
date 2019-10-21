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
    print_asm_1("pop    ebx","",len,&opr_ebx);
    return len;
}

make_instr_func(pop_ebp_v){
    OPERAND opr_ebp;
    int len=1;
    opr_ebp.type=OPR_MEM;
    opr_ebp.data_size=data_size;
    opr_ebp.sreg=SREG_SS;
    opr_ebp.addr=cpu.esp;
    cpu.esp+=data_size/8;
    operand_read(&opr_ebp);
    if(data_size==16){
        cpu.ebp=(opr_ebp.val&0xffff)|(cpu.ebp&0xffff0000);
    }
    else
    {
        cpu.ebp=opr_ebp.val;
    }
    print_asm_1("pop    ebp","",len,&opr_ebp);
    return len;
}