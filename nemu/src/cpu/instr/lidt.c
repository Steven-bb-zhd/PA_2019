#include "cpu/instr.h"

make_instr_func(lidt){

    OPERAND rel;
    rel.data_size=32;
    rel.type=OPR_IMM;
    
}