#include "cpu/instr.h"

static void instr_execute_1op(){
    operand_read(&opr_src);
    opr_dest.val=!opr_src.val;
    operand_write(&opr_dest);
}