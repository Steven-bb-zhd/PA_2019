#include "cpu/instr.h"

static void instr_execute_1op_cc_pass()
{
	operand_read(&opr_src);
	cpu.eip += sign_ext(opr_src.val, opr_src.data_size);
}

static void instr_execute_1op_cc_fail() {/* Do nothing */}

#define jcc_helper(suffix) \
	make_instr_impl_1op_cc(j, i, suffix, e) \
	make_instr_impl_1op_cc(j, i, suffix, a) \
	make_instr_impl_1op_cc(j, i, suffix, b) \
	make_instr_impl_1op_cc(j, i, suffix, g) \
	make_instr_impl_1op_cc(j, i, suffix, l) \
	make_instr_impl_1op_cc(j, i, suffix, o) \
	make_instr_impl_1op_cc(j, i, suffix, p) \
	make_instr_impl_1op_cc(j, i, suffix, s) \
	make_instr_impl_1op_cc(j, i, suffix, ae) \
	make_instr_impl_1op_cc(j, i, suffix, ge) \
	make_instr_impl_1op_cc(j, i, suffix, le) \
	make_instr_impl_1op_cc(j, i, suffix, na) \
	make_instr_impl_1op_cc(j, i, suffix, ne) \
	make_instr_impl_1op_cc(j, i, suffix, no) \
	make_instr_impl_1op_cc(j, i, suffix, np) \
	make_instr_impl_1op_cc(j, i, suffix, ns) \

jcc_helper(near)
jcc_helper(short_)
make_instr_impl_1op_cc(j, i, short_, ecxz)
make_instr_impl_1op_cc(j,i,short_,ge);

make_instr_func(jna_short){
	OPERAND imm;
	int len=1;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	len+=1;
	if(cpu.eflags.CF==1||cpu.eflags.ZF==1){
		len+=(int8_t)imm.val;
	}
	return len;
}

make_instr_func(je_short){
	OPERAND imm;
	int len=1;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	len+=1;
	print_asm_1("je","",len,&imm);
	if(cpu.eflags.ZF==1)
		len+=(int8_t)imm.val;
	return len;
}

make_instr_func(jg_b){
	OPERAND imm;
	int len=1;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	len+=1;
	print_asm_1("jg","",len,&imm);
	if(cpu.eflags.ZF==0&&(cpu.eflags.SF==cpu.eflags.OF)){
		len+=(int8_t)imm.val;
	}
	return len;
}

make_instr_func(jng_b){
	OPERAND imm;
	int len=1;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	len+=1;
	print_asm_1("jng_b","",len,&imm);
	if(cpu.eflags.ZF==1||(cpu.eflags.SF!=cpu.eflags.OF)){
		len+=(int8_t)imm.val;
	}
	return len;
}

make_instr_func(jne_b){
	OPERAND imm;
	int len=1;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	len+=1;
	print_asm_1("jne","",len,&imm);
	if(cpu.eflags.ZF==0)
		len+=(int8_t)imm.val;
	return len;
}

make_instr_func(jl_b){
	OPERAND imm;
	int len=1;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	len+=1;
	print_asm_1("jl","",len,&imm);
	if(cpu.eflags.SF!=cpu.eflags.OF)
		len+=(int8_t)imm.val;
	return len;
}

make_instr_func(jbe_v){
	OPERAND imm;
	int len=1;
	imm.type=OPR_IMM;
	imm.data_size=data_size;
	imm.addr=eip+1;
	operand_read(&imm);
	len+=data_size/8;
	print_asm_1("jbe_v","",len,&imm);
	if(cpu.eflags.ZF==1||cpu.eflags.CF==1){
		if(data_size==16)
			len+=(int16_t)imm.val;
		else
			len+=(int32_t)imm.val;
	}
	return len;
}