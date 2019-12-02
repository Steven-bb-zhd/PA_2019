#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	assert(sreg>=0&&sreg<=6);
	uint32_t laddr=0;
	laddr=cpu.segReg[sreg].base+offset;
	return laddr;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	SegDesc segdesc;
	memcpy(&segdesc,hw_mem+cpu.gdtr.base+8*(cpu.segReg[sreg].index),8);
	uint32_t base=((segdesc.base_31_24<<24)|(segdesc.base_23_16<<16)|(segdesc.base_15_0));
	uint32_t limit=((segdesc.limit_19_16<<16)|(segdesc.limit_15_0));
	printf("%x\n",segdesc.present);
	assert(segdesc.present==1);
	assert(segdesc.granularity==1);
	assert(limit==0xfffff);
	assert(base==0);
	cpu.segReg[sreg].base=base;
	cpu.segReg[sreg].limit=limit;
	//cpu.segReg[sreg].type=segdesc.type;
	cpu.segReg[sreg].privilege_level=segdesc.privilege_level;
}
