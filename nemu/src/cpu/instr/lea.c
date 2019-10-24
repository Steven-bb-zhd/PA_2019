#include "cpu/instr.h"

make_instr_func(lea) {
   OPERAND m,r;
   int len=1;
   r.type=OPR_REG;
   m.type=OPR_MEM;
   r.data_size=data_size;
   m.data_size=data_size;
   len+=modrm_r_rm(eip+1,&r,&m);
   //operand_read(&m);
   r.val=m.addr;
   printf("r.val=%x\n",r.val);
   operand_write(&r);
   print_asm_2("lea","",len,&m,&r);
   return len;
}