#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	OPERAND opr_eip,opr_cs,opr_eflags;

	opr_eflags.data_size=32;
	opr_eflags.type=OPR_MEM;
	opr_eflags.sreg=SREG_SS;
	cpu.esp-=4;
	opr_eflags.addr=cpu.esp;
	operand_write(&opr_eflags);

	opr_cs.data_size=16;
	opr_cs.type=OPR_MEM;
	opr_cs.sreg=SREG_SS;
	cpu.esp-=2;
	opr_cs.addr=cpu.esp;
	operand_write(&opr_cs);
	printf("Please implement raise_intr()");
	assert(0);
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
