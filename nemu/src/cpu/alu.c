#include "cpu/cpu.h"

void set_CF_add(uint32_t src,uint32_t result,size_t data_size)
{
	if(data_size==8){
		src=src&0xff;
		result=result&(0xffffffff>>(32-data_size));
	}
	else if(data_size==16)
		{
			src=src&0xffff;
			result=result&(0xffffffff>>16);
		}
	cpu.eflags.CF=result<src;
	return;
}

void set_CF_adc(uint32_t src,uint32_t result,uint32_t dest,size_t data_size)
{
	if(data_size==8){
		src=src&0xff;
		dest=dest&0xff;
		result=result&(0xffffffff>>(32-data_size));
	}
	else if(data_size==16)
		{
			src=src&0xffff;
			dest=dest&0xffff;
			result=result&(0xffffffff>>16);
		}
	if(!cpu.eflags.CF)
		set_CF_add(src,result,data_size);
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
		//cpu.eflags.SF=sign(result);
		//result=(result&(0xffffffff>>24));
		uint32_t temp=result;
		temp>>=7;
		cpu.eflags.SF=temp&0x1;
		//cpu.eflags.SF=result&0x80;
	}
	else if(data_size==16)
	{
		//cpu.eflags.SF=sign(result);
		//result=(result&(0xffffffff>>16));
		uint32_t temp=result;
		temp>>=15;
		cpu.eflags.SF=temp&0x1;
		
	}
	else
	{
		//cpu.eflags.SF=sign(result);
		uint32_t temp=result;
		temp>>=31;
		cpu.eflags.SF=temp&0x1;
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
		result=result&0xff;
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
	uint32_t res=0;
	res=src+dest+cpu.eflags.CF;
	if(data_size==8)
		res=res&0xff;
	else if(data_size==16)
		res=res&0xffff;
	set_CF_adc(src,res,dest,data_size);
	set_PF(res,data_size);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_add(res,src,dest,data_size);
	return res;
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

void set_CF_sub(uint32_t result, uint32_t dest,size_t data_size)
{
	if(data_size==8)
	{
		dest=dest&0xff;
		result=result&0xff;
	}
	else if(data_size==16)
	{
		dest=dest&0xffff;
		result=result&0xffff;
	}
	cpu.eflags.CF = dest < result;
}

void set_CF_sbb(uint32_t src,uint32_t dest, uint32_t result, size_t data_size)
{
	if(data_size==8)
	{
		dest=dest&0xff;
		src=src&0xff;
		result=result&0xff;
	}
	else if(data_size==16)
	{
		dest=dest&0xffff;
		src=src&0xffff;
		result=result&0xffff;
	}
	if(!cpu.eflags.CF){
		set_CF_sub(result,dest,data_size);
	}
	else
	{
		if(dest<=result)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
	}
}

void set_OF_sub(uint32_t result, uint32_t dest, uint32_t src, size_t data_size){
	if(data_size==8)
	{
		dest=dest&0xff;
		src=src&0xff;
		result=result&0xff;
	}
	else if(data_size==16)
	{
		dest=dest&0xffff;
		src=src&0xffff;
		result=result&0xffff;
	}
	uint32_t src_neg = ~(src+1)+1;
	set_OF_add(result,src_neg,dest,data_size);
	return;
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t res=0;
	res=dest-src;
	if(data_size==8)
		res=res&0xff;
	else if(data_size==16)
		res=res&0xffff;
	set_CF_sub(res,dest,data_size);
	set_PF(res,data_size);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_sub(res,dest,src,data_size);
	return res;
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
	uint32_t res=0;
	res=dest-src-cpu.eflags.CF;
	if(data_size==8)
		res=res&0xff;
	else if(data_size==16)
		res=res&0xffff;
	set_CF_sbb(src,dest,res,data_size);
	set_PF(res,data_size);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_sub(res,dest,src,data_size);
	return res;
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

	uint32_t res=0;
	if(data_size==8)
	{
		src=src&0xff;
		dest=dest&0xff;
	}
	else if(data_size==16)
	{
		src=src&0xffff;
		dest=dest&0xffff;
	}
	res=dest&src;
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	set_PF(res,data_size);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res;
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
	uint32_t res=0;
	if(data_size==8)
	{
		src=src&0xff;
		dest=dest&0xff;
	}
	else if(data_size==16)
	{
		src=src&0xffff;
		dest=dest&0xffff;
	}
	res=dest^src;
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	set_PF(res,data_size);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res;
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
	uint32_t res=0;
	if(data_size==8)
	{
		src=src&0xff;
		dest=dest&0xff;
	}
	else if(data_size==16)
	{
		src=src&0xffff;
		dest=dest&0xffff;
	}
	res=dest|src;
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	set_PF(res,data_size);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res;
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
	uint32_t res=0;
	if (src==0){
		if(data_size==8){
			res=dest&0xff;
		}
		else if(data_size==16)
		{
			res=dest&0xffff;
		}
		else{
			res=dest;
		}
		set_PF(res,data_size);
		set_ZF(res,data_size);
		set_SF(res,data_size);
		return res;
	}
	else{
		if(data_size==8){
			uint8_t dest_low_8_bits = dest&0xff;
			dest_low_8_bits<<=src-1;
			uint8_t temp=dest_low_8_bits;
			temp>>=7;
			uint8_t CF_flags=temp&0x1;
			dest_low_8_bits<<=1;
			uint8_t OF_flags=(dest_low_8_bits&0x80)>>7;
			cpu.eflags.CF=CF_flags;
			res=dest_low_8_bits&0xffffffff;
			if(src==1)
				cpu.eflags.OF=CF_flags!=OF_flags;
		}
		else if(data_size==16)
		{
			uint16_t dest_low_16_bits=dest&0xffff;
			dest_low_16_bits<<=src-1;
			uint16_t temp=dest_low_16_bits;
			temp>>=15;
			uint16_t CF_flags=temp&0x1;
			dest_low_16_bits<<=1;
			uint16_t OF_flags=(dest_low_16_bits&0x8000)>>7;
			cpu.eflags.CF=CF_flags;
			res=dest_low_16_bits&0xffffffff;
			if(src==1)
				cpu.eflags.OF=CF_flags!=OF_flags;
		}
		else{
			dest<<=src-1;
			uint32_t temp=dest;
			temp>>=31;
			uint32_t CF_flags=temp&0x1;
			dest<<=1;
			uint32_t OF_flags=(dest&0x80000000)>>31;
			cpu.eflags.CF=CF_flags;
			res=dest;
			if(src==1)
				cpu.eflags.OF=CF_flags!=OF_flags;
		}
		set_PF(res,data_size);
		set_ZF(res,data_size);
		set_SF(res,data_size);
		return res;
	}
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
	uint32_t res=0;
	if (src==0){
		if(data_size==8){
			res=dest&0xff;
		}
		else if(data_size==16)
		{
			res=dest&0xffff;
		}
		else{
			res=dest;
		}
		set_PF(res,data_size);
		set_ZF(res,data_size);
		set_SF(res,data_size);
		return res;
	}
	else{
		if(data_size==8)
		{
			uint8_t dest_low_8_bits = dest&0xff;
			dest_low_8_bits>>=src-1;
			uint8_t temp=dest_low_8_bits;
			temp>>=7;
			uint8_t CF_flags=temp&0x1;
			dest_low_8_bits>>=1;
			uint8_t OF_flags=(dest_low_8_bits&0x80)>>7;
			cpu.eflags.CF=CF_flags;
			res=dest_low_8_bits&0xffffffff;
			if(src==1)
				cpu.eflags.OF=CF_flags!=OF_flags;
		}
		else if(data_size==16)
		{
			uint16_t dest_low_16_bits=dest&0xffff;
			dest_low_16_bits>>=src-1;
			uint16_t temp=dest_low_16_bits;
			temp>>=15;
			uint16_t CF_flags=temp&0x1;
			dest_low_16_bits>>=1;
			uint16_t OF_flags=(dest_low_16_bits&0x8000)>>7;
			cpu.eflags.CF=CF_flags;
			res=dest_low_16_bits&0xffffffff;
			if(src==1)
				cpu.eflags.OF=CF_flags!=OF_flags;
		}
		else{
			dest>>=src-1;
			uint32_t temp=dest;
			temp>>=31;
			uint32_t CF_flags=temp&0x1;
			dest>>=1;
			uint32_t OF_flags=(dest&0x80000000)>>31;
			cpu.eflags.CF=CF_flags;
			res=dest;
			if(src==1)
				cpu.eflags.OF=CF_flags!=OF_flags;
		}
		set_PF(res,data_size);
		set_ZF(res,data_size);
		set_SF(res,data_size);
		return res;
	}
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
	return alu_shl(src,dest,data_size);
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}
