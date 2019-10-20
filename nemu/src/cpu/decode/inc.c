#include "cpu/instr.h"

make_instr_func(inc_rm_v){
    OPERAND rm;
    int len=1;
    rm.data_size=data_size;
    len+=modrm_rm(eip+1,&rm);
    operand_read(&rm);
    rm.val=alu_add(1,rm.val,rm.data_size);
    operand_write(&rm);
    print_asm_1("inc","",len,&rm);
    return len;
}