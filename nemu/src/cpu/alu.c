#include "cpu/cpu.h"

void set_CF_add(uint32_t src,uint32_t result,size_t data_size)
{
	if(data_size==8){
		result=result&(0xffffffff>>(32-data_size));
	}
	else if(data_size==16)
		result=result&(0xffffffff>>16);
	cpu.eflags.CF=result<src;
	return;
}

void set_CF_adc(uint32_t src,uint32_t result,uint32_t dest,size_t data_size)
{
	if(data_size==8){
		result=result&(0xffffffff>>(32-data_size));
	}
	else if(data_size==16)
		result=result&(0xffffffff>>16);
	if(!cpu.eflags.CF)
		set_CF_add(result, src,data_size);
	else{
		if(result <= src || result <= dest)
			cpu.eflags.CF = 1;
		else
		{
			cpu.eflags.CF = 0;
		}
		//cpu.eflags.CF = 0;
	}
	return;

}

void set_PF(uint32_t result,size_t data_size)
{
	uint32_t res_low_8_bits =result &0xff;
	uint32_t sum_low_8_bits =0;
	for(int i=0;i<8;++i){
		sum_low_8_bits += res_low_8_bits&0x1;
		res_low_8_bits>>=1;
	}
	if((sum_low_8_bits%2)==0)
	{
		cpu.eflags.PF=1;
	}
	else
	{
		cpu.eflags.PF=0;
	}
	return;
}

void set_ZF(uint32_t result, size_t data_size){
	if(data_size==8)
		result=(result&(0xffffffff>>24));
	else if(data_size==16)
		result=result&(0xffffffff>>16);
	cpu.eflags.ZF=(result==0);
	return;
}

void set_SF(uint32_t result,size_t data_size){
	if(data_size==8)
	{
		result=(result&(0xffffffff>>24));
		cpu.eflags.SF=result&0x80;
	}
	else if(data_size==16)
	{
		result=(result&(0xffffffff>>16));
		cpu.eflags.SF=result&0x8000;
	}
	else
	{
		cpu.eflags.SF=result&0x80000000;
	}
	return;
}

void set_OF_add(uint32_t result,uint32_t src,uint32_t dest,size_t data_size){
	if(data_size==8)
	{
		src=(src&(0xffffffff>>24));
		result=(result&(0xffffffff>>24));
		dest=(dest&(0xffffffff>>24));
		uint8_t res_8_bits_src=src&0x80;
		uint8_t res_8_bits_dest=dest&0x80;
		uint8_t res_8_bits_result=result&0x80;
		if(res_8_bits_src==res_8_bits_dest){
			if(res_8_bits_src!=res_8_bits_result)
				cpu.eflags.OF = 1;
			else
				cpu.eflags.OF = 0;
		}
		else
			cpu.eflags.OF = 0;
	}
	else if(data_size==16)
	{
		src=(src&(0xffffffff>>16));
		result=(result&(0xffffffff>>16));
		dest=(dest&(0xffffffff>>16));
		uint16_t res_16_bits_src=src&0x8000;
		uint16_t res_16_bits_dest=dest&0x8000;
		uint16_t res_16_bits_result=result&0x8000;
		if(res_16_bits_src==res_16_bits_dest){
			if(res_16_bits_src!=res_16_bits_result)
				cpu.eflags.OF = 1;
			else
				cpu.eflags.OF = 0;
		}
		else
			cpu.eflags.OF = 0;
	}
	else
	{
		uint32_t res_32_bits_src=src&0x80000000;
		uint32_t res_32_bits_dest=dest&0x80000000;
		uint32_t res_32_bits_result=result&0x80000000;
		if(res_32_bits_src==res_32_bits_dest){
			if(res_32_bits_src!=res_32_bits_result)
				cpu.eflags.OF = 1;
			else
				cpu.eflags.OF = 0;
		}
		else
			cpu.eflags.OF = 0;
	}
	
}

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t result = src + dest;
	if(data_size==8)
		result=result&0xff>>24;
	else if(data_size==16)
		result=result&0xffff;
	set_CF_add(src,result,data_size);
	set_PF(result,data_size);
	set_SF(result,data_size);
	set_ZF(result,data_size);
	set_OF_add(result,src,dest,data_size);
	return result;
/* #ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif*/
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}
