#include "cpu/instr.h"

static void instr_execute_1op(){
    operand_read(&opr_src);
    OPERAND temp;
    temp.addr=cpu.esp;
    cpu.esp+=data_size/8;
    temp.val=opr_src.val;
    temp.type=OPR_MEM;
    temp.data_size=data_size;
    temp.val=opr_src.val;
    //opr_dest.addr=opr_src.addr;
    //opr_dest.addr=cpu.esp;
    operand_write(&temp);
}

make_instr_impl_1op(pop,r,v);

make_instr_func(pop_ebx_v){
    OPERAND opr_ebx;
    int len=1;
    opr_ebx.type=OPR_MEM;
    opr_ebx.data_size=data_size;
    opr_ebx.sreg=SREG_SS;
    opr_ebx.addr=cpu.esp;
    operand_read(&opr_ebx);
    cpu.esp+=data_size/8;
    //printf("opr_ebx=%x\n",opr_ebx.val);
    if(data_size==16){
        cpu.ebx=(opr_ebx.val&0xffff)|(cpu.ebx&0xffff0000);
    }
    else
    {
        cpu.ebx=opr_ebx.val;
    }
    print_asm_0("pop    ebx","",len);
    return len;
}

make_instr_func(pop_ebp_v){
    OPERAND opr_ebp;
    int len=1;
    opr_ebp.type=OPR_MEM;
    opr_ebp.data_size=data_size;
    opr_ebp.sreg=SREG_SS;
    opr_ebp.addr=cpu.esp;
    operand_read(&opr_ebp);
    cpu.esp+=data_size/8;
    //printf("opr_ebp=%x\n",opr_ebp.val);
    if(data_size==16){
        cpu.ebp=(opr_ebp.val&0xffff)|(cpu.ebp&0xffff0000);
    }
    else
    {
        cpu.ebp=opr_ebp.val;
    }
    print_asm_0("pop    ebp","",len);
    return len;
}

make_instr_func(pop_edi_v){
    OPERAND opr_edi;
    int len=1;
    opr_edi.type=OPR_MEM;
    opr_edi.data_size=data_size;
    opr_edi.sreg=SREG_SS;
    opr_edi.addr=cpu.esp;
    operand_read(&opr_edi);
    cpu.esp+=data_size/8;
    //printf("opr_ebx=%x\n",opr_ebx.val);
    if(data_size==16){
        cpu.edi=(opr_edi.val&0xffff)|(cpu.edi&0xffff0000);
    }
    else
    {
        cpu.edi=opr_edi.val;
    }
    print_asm_0("pop    edi","",len);
    return len;
}
