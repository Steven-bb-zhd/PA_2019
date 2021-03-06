#include "cpu/instr.h"

static void instr_execute_2op(){
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_src.val=sign_ext(opr_src.val,opr_src.data_size);
    opr_dest.val=sign_ext(opr_dest.val,opr_dest.data_size);
    opr_dest.val=alu_and(opr_src.val,opr_dest.val,data_size);
    operand_write(&opr_dest);
}

/*make_instr_func(and_i2rm_bv){
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
    rm.val=alu_and(imm.val,rm.val,rm.data_size);
    operand_write(&rm);
    print_asm_2("and","",len,&imm,&rm);
    return len;
}*/

make_instr_impl_2op(and,i,rm,v)
make_instr_impl_2op(and,i,rm,b)
make_instr_impl_2op(and,r,rm,v)
make_instr_impl_2op(and,r,rm,b)
make_instr_impl_2op(and,rm,r,v)
make_instr_impl_2op(and,rm,r,b)
make_instr_impl_2op(and,i,rm,bv);
make_instr_impl_2op(and,i,a,v)
make_instr_impl_2op(and,i,a,b)