#include "cpu/instr.h"

static void instr_execute_2op(){
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_src.val=sign_ext(opr_src.val,opr_src.data_size);
    opr_dest.val=sign_ext(opr_dest.val,opr_dest.data_size);
    opr_dest.val=alu_add(opr_src.val,opr_dest.val,data_size);
    operand_write(&opr_dest);
}

/*make_instr_func(add_i2rm_bv){
    OPERAND rm,imm;
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

    rm.val=alu_add(imm.val,rm.val,rm.data_size);
    operand_write(&rm);
    print_asm_2("add","",len,&imm,&rm);
    return len;

}*/


make_instr_impl_2op(add,i,rm,bv)
make_instr_impl_2op(add,i,rm,v)
make_instr_impl_2op(add,i,rm,b)
make_instr_impl_2op(add,r,rm,v)
make_instr_impl_2op(add,r,rm,b)
make_instr_impl_2op(add,i,a,v)