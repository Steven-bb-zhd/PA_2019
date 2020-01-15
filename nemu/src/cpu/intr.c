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
	opr_eflags.val=cpu.eflags;
	cpu.esp-=4;
	opr_eflags.addr=cpu.esp;
	operand_write(&opr_eflags);

	opr_cs.data_size=16;
	opr_cs.type=OPR_MEM;
	opr_cs.sreg=SREG_SS;
	opr_cs.val=cpu.cs;
	cpu.esp-=2;
	opr_cs.addr=cpu.esp;
	operand_write(&opr_cs);

	opr_eip.data_size=32;
	opr_eip.type=OPR_MEM;
	opr_eip.sreg=SREG_SS;
	opr_eip.val=cpu.eip;
	cpu.esp-=4;
	opr_eip.addr=cpu.esp;
	operand_write(&opr_eip);
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
