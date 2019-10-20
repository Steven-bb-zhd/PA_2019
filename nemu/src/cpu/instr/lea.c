#include "cpu/instr.h"

make_instr_func(lea) {
   OPERAND m,r;
   int len=1;
   r.data_size=data_size;
   m.data_size=data_size;
   len+=modrm_r_rm(eip+1,&r,&m);
   operand_read(&m);
   r.addr=m.addr;
   operand_write(&r);
   return len;
}