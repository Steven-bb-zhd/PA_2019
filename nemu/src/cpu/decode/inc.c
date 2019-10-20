#include "cpu/instr.h"

static void instr_execute_1op(){
    operand_read(&opr_src);
    opr_src.val=alu_add(1,opr_src.val,data_size);
    operand_write(&opr_src);
}

make_instr_impl_1op(inc,rm,v)

/*make_instr_func(inc_rm_v){
    OPERAND rm;
    int len=1;
    rm.data_size=data_size;
    len+=modrm_rm(eip+1,&rm);
    operand_read(&rm);
    rm.val=alu_add(1,rm.val,rm.data_size);
    operand_write(&rm);
    print_asm_1("inc","",len,&rm);
    return len;
}*/