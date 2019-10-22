#include "cpu/instr.h"

static void instr_execute_2op(){
	operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_src.val=sign_ext(opr_src.val,opr_src.data_size);
    opr_dest.val=sign_ext(opr_dest.val,opr_dest.data_size);
    opr_dest.val=alu_sub(opr_src.val,opr_dest.val,data_size);
}

make_instr_impl_2op(cmp,i,rm,v)
make_instr_impl_2op(cmp,r,rm,v)

make_instr_func(cmps_v)
{
	OPERAND msi, mdi;
	msi.data_size = mdi.data_size = data_size;
	msi.type = mdi.type = OPR_MEM;
	msi.sreg = mdi.sreg = SREG_DS;
	msi.addr = cpu.gpr[REG_ESI]._32;
	mdi.addr = cpu.gpr[REG_EDI]._32;
	operand_read(&msi);
	operand_read(&mdi);
	alu_sub(mdi.val, msi.val, data_size);
	int incDec = 0;
	incDec = cpu.eflags.DF == 0 ? data_size / 8 : -data_size / 8;
	cpu.gpr[REG_ESI]._32 += incDec;
	cpu.gpr[REG_EDI]._32 += incDec;

	print_asm_0("cmps (%%edi), (%%esi)", "", 1);
	return 1;
}

make_instr_func(cmps_b)
{
	OPERAND msi, mdi;
	msi.data_size = mdi.data_size = 8;
	msi.type = mdi.type = OPR_MEM;
	msi.sreg = mdi.sreg = SREG_DS;
	msi.addr = cpu.gpr[REG_ESI]._32;
	mdi.addr = cpu.gpr[REG_EDI]._32;
	operand_read(&msi);
	operand_read(&mdi);
	alu_sub(mdi.val, msi.val, data_size);
	int incDec = 0;
	incDec = cpu.eflags.DF == 0 ? 1 : -1;
	cpu.gpr[REG_ESI]._32 += incDec;
	cpu.gpr[REG_EDI]._32 += incDec;
	print_asm_0("cmps (%%edi), (%%esi)", "", 1);
	return 1;
}

make_instr_func(cmp_i2rm_bv){
	OPERAND imm,rm;
    int len=1;
    imm.data_size=8;
    rm.data_size=data_size;
    len+=modrm_opcode_rm(eip+len,&opcode,&rm);
    operand_read(&rm);

    imm.type=OPR_IMM;
    imm.addr=eip+len;
    len+=1;
    operand_read(&imm);

    imm.val=sign_ext(imm.val,imm.data_size);
    rm.val=sign_ext(rm.val,rm.data_size);

    rm.val=alu_sub(imm.val,rm.val,rm.data_size);
    operand_write(&rm);
    print_asm_2("cmp_bv","",len,&imm,&rm);
    return len;
}