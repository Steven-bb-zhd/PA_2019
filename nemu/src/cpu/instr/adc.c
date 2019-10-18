#include "cpu/instr.h"

make_instr_func(adc_i2rm_bv){
    OPERAND imm,rm;
    int len=1;
    imm.data_size=8;
    rm.data_size=data_size;
    len+=modrm_opcode(eip+len,&rm);
    operand_read(&rm);

    imm.type=OPR_IMM;
    imm.addr=eip+len;
    operand_read(&imm);
    len+=1;
    imm.val=sign_ext(imm.val,imm.data_size);
    rm.val=sign_ext(rm.val,rm.data_size);
    rm.val=alu_adc(imm.val,rm.val,rm.data_size);
    operand_write(&rm);
    return len;
}