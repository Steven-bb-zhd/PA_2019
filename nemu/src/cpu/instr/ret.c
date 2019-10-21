#include "cpu/instr.h"

make_instr_func(ret_near){
    OPERAND opr_eip;
    printf("eip=%x\n",eip);
    opr_eip.type=OPR_MEM;
    opr_eip.data_size=data_size;
    //printf("cpu.esp=%x\n",cpu.esp);
    opr_eip.addr=cpu.esp;
    opr_eip.sreg=SREG_CS;
    operand_read(&opr_eip);
    printf("opr_eip=%x\n",opr_eip.val);
    cpu.esp+=data_size/8;
    if(data_size==16){
        cpu.eip=opr_eip.val&0xffff;
    }
    else
    {
        cpu.esi=opr_eip.val;
    }
    
    //eip=opr_eip.val;
    return 0;
}