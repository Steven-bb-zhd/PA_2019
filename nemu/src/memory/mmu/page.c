#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	/*/uint32_t dir=(laddr>>22)&0x3ff;
	uint32_t page=(laddr>>12)&0x3ff;
	uint32_t offset=laddr&0xfff;
	uint32_t dir_base=cpu.cr3.pdbr<<12;
	uint32_t dir_entry=hw_mem_read(dir_base+dir,4);
	uint32_t d_present=(dir_entry>>31)&0x1;
	assert(d_present==1);
	dir_entry&=0xfffff000;
	uint32_t pg_base=dir_entry+page;
	uint32_t pg_tbl=hw_mem_read(pg_base,4);
	uint32_t p_present=(pg_tbl>>31)&0x1;
	assert(p_present==1);
	pg_tbl&=0xfffff000;
	uint32_t res=pg_tbl+offset;
	return res;*/
	printf("\nPlease implement page_translate()\n");
	assert(0);
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
