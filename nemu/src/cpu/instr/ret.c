#include "cpu/instr.h"

make_instr_func(ret_near){
    OPERAND opr_eip;
    int len=1;
    //printf("eip=%x\n",eip);
    opr_eip.type=OPR_MEM;
    opr_eip.data_size=data_size;
    //printf("cpu.esp=%x\n",cpu.esp);
    opr_eip.addr=cpu.esp;
    opr_eip.sreg=SREG_CS;
    operand_read(&opr_eip);
    //printf("opr_eip=%x\n",opr_eip.val);
    cpu.esp+=data_size/8;
    print_asm_0("ret_near","",len);
    //printf("cpu.esp=%x\n",cpu.esp);
    if(data_size==16){
        cpu.eip=opr_eip.val&0xffff;
    }
    else
    {
        cpu.eip=opr_eip.val;
    }
    
    //eip=opr_eip.val;
    return 0;
}

make_instr_func(ret_near_imm16){
    OPERAND imm,opr_eip;
    int len=1;
    imm.type=OPR_IMM;
    imm.data_size=16;
    imm.addr=eip+len;
    opr_eip.addr=cpu.esp;
    operand_read(&imm);
    len+=1;
    opr_eip.type=OPR_MEM;
    opr_eip.data_size=data_size;
    cpu.esp+=data_size/8;
    imm.val=sign_ext(imm.val,32);
    cpu.esp+=imm.val;
    operand_read(&opr_eip);
    print_asm_1("ret_near_imm16","",len,&imm);
    cpu.eip=opr_eip.val;
    return 0;
}