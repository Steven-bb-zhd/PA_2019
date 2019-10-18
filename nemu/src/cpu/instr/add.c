#include "cpu/instr.h"

make_instr_func(add_i2m_bv){
    OPERAND rm,imm;
    int len=1;
    imm.data_size=data_size;
    rm.data_size=data_size;
    len+=modrm_opcode_rm(eip+1,&opcode,&rm);
    operand_read(&rm);

    imm.type=OPR_IMM;
    imm.addr=eip+len;
    operand_read(&imm);

    imm.val=sign_ext(imm.val,data_size);
    rm.val=sign_ext(rm.val,data_size);

    rm.val=alu_add(imm.val,rm.val,data_size);
    operand_read(&rm);
    print_asm_2("add","",len+data_size/8,&imm,&rm);
    return len+data_size/8;

}