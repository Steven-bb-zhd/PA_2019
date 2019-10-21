#include "cpu/instr.h"

make_instr_func(push_ebp_v){
    OPERAND opr_ebp;
    int len=1;
    opr_ebp.type=OPR_MEM;
    opr_ebp.data_size=data_size;
    opr_ebp.val=cpu.ebp;
    opr_ebp.sreg=SREG_SS;
    cpu.esp-=data_size/8;
    opr_ebp.addr=cpu.esp;
    operand_write(&opr_ebp);
    print_asm_0("push   ebp","",len);
    return len;
}

make_instr_func(push_ebx_v){
    OPERAND opr_ebx;
    int len=1;
    opr_ebx.type=OPR_MEM;
    opr_ebx.data_size=data_size;
    opr_ebx.sreg=SREG_SS;
    opr_ebx.val=cpu.ebx;
    cpu.esp-=data_size/8;
    opr_ebx.addr=cpu.esp;
    operand_write(&opr_ebx);
    print_asm_0("push   ebx","",len);
    return len;
}

make_instr_func(push_rm_v){
    OPERAND rm;
    int len=1;
    rm.data_size=data_size;
    rm.type=OPR_MEM;
    len+=modrm_opcode_rm(eip+1,&opcode,&rm);
    operand_read(&rm);
    cpu.esp-=data_size/8;
    rm.sreg=SREG_SS;
    rm.addr=cpu.esp;
    operand_write(&rm);
    print_asm_0("push   rm","",len);
    return len;
}

make_instr_func(push_edi_v){
    OPERAND opr_edi;
    int len=1;
    opr_edi.data_size=data_size;
    opr_edi.type=OPR_MEM;
    opr_edi.val=cpu.edi;
    cpu.esp-=data_size/8;
    opr_edi.sreg=SREG_SS;
    opr_edi.addr=cpu.esp;
    operand_write(&opr_edi);
    print_asm_0("push   edi","",len);
    return len;
}

make_instr_func(push_esi_v){
    OPERAND opr_esi;
    int len=1;
    opr_esi.data_size=data_size;
    opr_esi.type=OPR_MEM;
    opr_esi.val=cpu.esi;
    cpu.esp-=data_size/8;
    opr_esi.sreg=SREG_SS;
    opr_esi.addr=cpu.esp;
    operand_write(&opr_esi);
    print_asm_0("push   esi","",len);
    return len;
}

make_instr_func(push_ecx_v){
    OPERAND opr_ecx;
    int len=1;
    opr_ecx.type=OPR_MEM;
    opr_ecx.data_size=data_size;
    opr_ecx.sreg=SREG_SS;
    opr_ecx.val=cpu.ecx;
    cpu.esp-=data_size/8;
    opr_ecx.addr=cpu.esp;
    operand_write(&opr_ecx);
    print_asm_0("push   ecx","",len);
    return len;
}