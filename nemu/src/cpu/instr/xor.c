#include "cpu/instr.h"

make_instr_func(xor_i2rm_bv){
    OPERAND imm,rm;
    int len=1;
    imm.data_size=8;
    rm.data_size=data_size;
    len+=modrm_opcode_rm(eip+1,&opcode,&rm);
    operand_read(&rm);

    imm.type=OPR_IMM;
    imm.addr=eip+len;
    len+=1;
    operand_read(&imm);

    imm.val=sign_ext(imm.val,imm.data_size);
    rm.val=sign_ext(rm.val,rm.data_size);
    rm.val=alu_xor(imm.val,rm.val,rm.data_size);
    operand_write(&rm);
    print_asm_2("xor","",len,&imm,&rm);
    return len;
}