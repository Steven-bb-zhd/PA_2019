#include "cpu/instr.h"

make_instr_func(lgdt)
{
    /* /OPERAND rel;
    rel.data_size=32;
    rel.type=OPR_IMM;
    rel.sreg=SREG_CS;
    rel.addr=eip+2;
    operand_read(&rel);
    uint16_t limit=0;
    uint32_t base=0;
    memcpy(&limit,hw_mem+rel.val,2);
    cpu.gdtr.limit=limit;
    if(data_size==16){
        memcpy(&base,hw_mem+rel.val+2,3);
        //printf("base_16=%x\n",base);
        cpu.gdtr.base=base&0x00ffffffff;
    }
    else{
        memcpy(&base,hw_mem+rel.val+2,4);
        //printf("base_32=%x\n",base);
        cpu.gdtr.base=base;
    }
    return 6;*/
    OPERAND m1, m2;
	int len = 1;

	m1.data_size = 16;
	m2.data_size = 32;
	// combine m1 and m2 to read a 6-bit data;
	len += modrm_rm(eip + 1, &m1);
	modrm_rm(eip + 1, &m2);
	m2.addr = m1.addr + 2;
	operand_read(&m1);
	operand_read(&m2);

	assert(data_size == 16 || data_size == 32);
	if(data_size == 16) {
		cpu.gdtr.base = m2.val & 0x00ffffff;
		cpu.gdtr.limit = m1.val;
	}
	else {
		cpu.gdtr.base = m2.val;
		cpu.gdtr.limit = m1.val;
	}

	return len;
}