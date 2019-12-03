#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	uint32_t dir=(laddr>>22)&0x3ff;
	uint32_t page=(laddr>>12)&0x3ff;
	uint32_t offset=laddr&0xfff;
	uint32_t dir_base=cpu.cr3.pdbr<<12;
	uint32_t dir_entry=hw_mem_read(dir_base+(dir*sizeof(PDE)),4);
	PDE pde_read;
	pde_read.val=dir_entry;
	uint32_t d_present=dir_entry&0x1;
	assert(d_present==1);
	assert(pde_read.present);
	//dir_entry&=0xfffff000;
	uint32_t pg_base=pde_read.page_frame+(page*sizeof(PTE));
	uint32_t pg_tbl=hw_mem_read(pg_base,4);
	PTE pte_read;
	pte_read.val=pg_tbl;
	uint32_t p_present=pg_tbl&0x1;
	assert(p_present==1);
	assert(pte_read.present==1);
	//pg_tbl&=0xfffff000;
	uint32_t res=pte_read.page_frame|offset;
	return res;
	printf("\nPlease implement page_translate()\n");
	assert(0);
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
