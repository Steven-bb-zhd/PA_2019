#include "cpu/instr.h"

make_instr_func(pusha_v){
    OPERAND reg[8];
    for(int i=0;i<8;++i){
        reg[i].data_size=data_size;
    }

}