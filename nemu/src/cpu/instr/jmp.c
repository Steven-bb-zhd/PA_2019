#include "cpu/instr.h"

make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}

make_instr_func(jmp_short){
        OPERAND rel;
        int len=1;
        rel.data_size=8;
        rel.sreg=SREG_CS;
        rel.type=OPR_IMM;
        rel.addr=eip+len;
        len+=1;
        operand_read(&rel);
        int offset=sign_ext(rel.val,rel.data_size);

        cpu.eip=cpu.eip+offset;

        return 1+data_size/8;

}

make_instr_func(jmp_near_indirect){
        OPERAND rm;
        int len=1;
        rm.data_size=data_size;
        rm.type=OPR_MEM;
        len+=modrm_rm(eip+len,&rm);
        operand_read(&rm);
        print_asm_1("jmp rm","",len,&rm);
        if(data_size==16)
        {
                rm.val&=0xffff;
                cpu.eip=rm.val;
        }
        else
        {
                cpu.eip=rm.val;
        }
        
        return 0;
}