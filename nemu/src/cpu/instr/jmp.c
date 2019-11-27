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
        print_asm_1("jmp_short","",len,&rel);
        int offset=sign_ext(rel.val,rel.data_size);

        cpu.eip=cpu.eip+offset;

        return 1+rel.data_size/8;

}

make_instr_func(jmp_rm_v){
        OPERAND rm;
        int len=1;
        rm.data_size=data_size;
        rm.type=OPR_MEM;
        len+=modrm_rm(eip+len,&rm);
        operand_read(&rm);
        print_asm_1("jmp rm","",len,&rm);
        if(data_size==16)
        {
                //rm.val=(int32_t)(rm.val<<16)>>16;
                cpu.eip=rm.val&0xffff;
        }
        else
        {
                cpu.eip=rm.val;
        }
        
        return 0;
}

make_instr_func(jmp_far_imm){
        OPERAND seg,offset;
        seg.data_size=16;
        seg.sreg=SREG_CS;
        seg.addr=eip+1+data_size/8;
        seg.type=OPR_IMM;
        operand_read(&seg);
        
        offset.data_size=data_size;
        offset.addr=eip+1;
        offset.type=OPR_IMM;
        offset.sreg=SREG_CS;
        operand_read(&offset);
        
        /////uint16_t index=(seg.val>>3)&0x1fff;
        //cpu.cs.val=seg.val;
        if(data_size==16){
                cpu.eip=(offset.val&0xffff);
        }
        else{
                cpu.eip=offset.val;
        }

        return 0;
}