#include "cpu/instr.h"

make_instr_func(lea) {
   OPERAND m,r;
   int len=1;
   r.type=OPR_MEM;
   m.type=OPR_MEM;
   r.data_size=data_size;
   m.data_size=data_size;
   len+=modrm_r_rm(eip+1,&r,&m);
   operand_read(&m);
   printf("m.addr=%x\n",m.addr);
   r.val=m.addr;
   operand_write(&r);
   return len;
}