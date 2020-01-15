#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	OPERAND temp_32;
      OPERAND temp_16;
      temp_32.data_size=data_size; 
      temp_16.data_size=16;
      temp_32.type=OPR_MEM;
      temp_16.type=OPR_MEM;
      temp_32.sreg=SREG_CS;
      temp_16.sreg=SREG_CS;
      
      //push eflags
      cpu.esp=cpu.esp-4;
      temp_32.addr=cpu.esp;
      temp_32.val=cpu.eflags.val;
      operand_write(&temp_32);

      //push cs
      cpu.esp=cpu.esp-2;
      temp_16.addr=cpu.esp;
      temp_16.val=cpu.cs.val;
      operand_write(&temp_16);

      //push eip
      cpu.esp=cpu.esp-4;
      temp_32.addr=cpu.esp;
      temp_32.val=cpu.eip;
      operand_write(&temp_32);


      unsigned gateaddr=cpu.idtr.base+intr_no*8;
      GateDesc gatedesc;
      gatedesc.val[0]=laddr_read(gateaddr,4);
      gatedesc.val[1]=laddr_read(gateaddr+4,4);

      if(intr_no>=32){
	    cpu.eflags.IF=0;
      }

      cpu.cs.val=gatedesc.selector;
      cpu.eip=(gatedesc.offset_15_0&0xffff)+((gatedesc.offset_31_16<<16)&0xffff0000);
       //printf("Please implement raise_intr()");
       //assert(0);

#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
