#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "nemu.h"
#include "cpu/cpu.h"
#include "cpu/fpu.h"
#include "cpu/modrm.h"
#include "cpu/operand.h"
#include "cpu/instr_helper.h"
#include "memory/memory.h"
#include <stdio.h>
#include <cpu-ref/instr_ref.h>


extern uint8_t data_size;

#include "cpu/instr/mov.h"
#include "cpu/instr/jmp.h"
#include "cpu/instr/shift.h"
#include "cpu/instr/flags.h"
#include "cpu/instr/group.h"
#include "cpu/instr/special.h"
#include "cpu/instr/x87.h"

/* TODO: add more instructions here */
int jmp_near(uint32_t eip,uint8_t opcode);
//int push_ebp_v(uint32_t eip,uint8_t opcode);
//int push_ebx_v(uint32_t eip,uint8_t opcode);
int group_1_bv(uint32_t eip,uint8_t opcode);
int add_i2rm_bv(uint32_t eip,uint8_t opcode);
int adc_i2rm_bv(uint32_t eip,uint8_t opcode);
int or_i2rm_bv(uint32_t eip,uint8_t opcode);
int sub_i2rm_bv(uint32_t eip,uint8_t opcode);
int sbb_i2rm_bv(uint32_t eip,uint8_t opcode);
int and_i2rm_bv(uint32_t eipp,uint8_t opcode);
int xor_i2rm_bv(uint32_t eipp,uint8_t opcode);
int cmp_i2rm_bv(uint32_t eipp,uint8_t opcode);
int call_near(uint32_t eip,uint8_t opcode);
int ret_near(uint32_t eip,uint8_t opcode);
int group_1_v(uint32_t eip,uint8_t opcode);
int add_i2rm_v(uint32_t eip,uint8_t opcode);
int or_i2rm_v(uint32_t eip,uint8_t opcode);
int adc_i2rm_v(uint32_t eip,uint8_t opcode);
int sbb_i2rm_v(uint32_t eip,uint8_t opcode);
int and_i2rm_v(uint32_t eip,uint8_t opcode);
int sub_i2rm_v(uint32_t eip,uint8_t opcode);
int xor_i2rm_v(uint32_t eip,uint8_t opcode);
int cmp_i2rm_v(uint32_t eip,uint8_t opcode);
int jmp_short(uint32_t eip,uint8_t opcode);
int jna_short_(uint32_t eip,uint8_t opcode);
int lea(uint32_t eip,uint8_t opcode);
int cmp_r2rm_v(uint32_t eip,uint8_t opcode);
int je_short_(uint32_t eip,uint8_t opcode);
int inc_rm_v(uint32_t eip,uint8_t opcode);
int dec_rm_v(uint32_t eip,uint8_t opcode);
int push_rm_v(uint32_t eip,uint8_t opcode);
int call_near_indirect(uint32_t eip,uint8_t opcode);
int jmp_rm_v(uint32_t eip,uint8_t opcode);
int test_r2rm_v(uint32_t eip,uint8_t opcode);
int jg_short_(uint32_t eip,uint8_t opcode);
int jle_short_(uint32_t eip,uint8_t opcode);
int jne_short_(uint32_t eip,uint8_t opcode);
int add_r2rm_v(uint32_t eip,uint8_t opcode);
int add_r2rm_b(uint32_t eip,uint8_t opcode);
//int push_edi_v(uint32_t eip,uint8_t opcode);
//int push_ecx_v(uint32_t eip,uint8_t opcode);
//int push_esi_v(uint32_t eip,uint8_t opcode);
int jna_near(uint32_t eip,uint8_t opcde);
//int push_edx_v(uint32_t eip,uint8_t opcode);
int push_r_v(uint32_t eip,uint8_t opcode);
//int push_eax_v(uint32_t eip,uint8_t opcode);
int adc_r2rm_v(uint32_t eip,uint8_t opcode);
int add_i2a_v(uint32_t eip,uint8_t opcode);
int pop_r_v(uint32_t eip,uint8_t opcode);
int pop_ebx_v(uint32_t eip,uint8_t opcode);
int pop_ebp_v(uint32_t eip,uint8_t opcode);
int xor_r2rm_v(uint32_t eip,uint8_t opcode);
int or_r2rm_v(uint32_t eip,uint8_t opcode);
int leave(uint32_t eip,uint8_t opcode);
int dec_r_v(uint32_t eip,uint8_t opcode);
int sub_rm2r_v(uint32_t eip,uint8_t opcode);
int jl_short_(uint32_t eip,uint8_t opcode);
int inc_r_v(uint32_t eip,uint8_t opcode);
int push_i_b(uint32_t eip,uint8_t opcode);
int cmp_rm2r_v(uint32_t eip,uint8_t opcode);
int jge_short_(uint32_t eip,uint8_t opcode);
int jl_near(uint32_t eip,uint8_t opcode);
int jle_near(uint32_t eip,uint8_t opcode);
int sub_r2rm_v(uint32_t eip,uint8_t opcode);
int and_rm2r_v(uint32_t eip,uint8_t opcode);
int and_rm2r_b(uint32_t eip,uint8_t opcode);
int and_r2rm_v(uint32_t eip,uint8_t opcode);
int and_r2rm_b(uint32_t eip,uint8_t opcode);
int test_r2rm_b(uint32_t eip,uint8_t opcode);
int setne_b(uint32_t eip,uint8_t opcode);
int cmp_i2a_b(uint32_t eip,uint8_t opcode);
int add_i2rm_b(uint32_t eip,uint8_t opcode);
int or_i2rm_b(uint32_t eip,uint8_t opcode);
int adc_i2rm_b(uint32_t eip,uint8_t opcode);
int sbb_i2rm_b(uint32_t eip,uint8_t opcode);
int and_i2rm_b(uint32_t eip,uint8_t opcode);
int sub_i2rm_b(uint32_t eip,uint8_t opcode);
int xor_i2rm_b(uint32_t eip,uint8_t opcode);
int cmp_i2rm_b(uint32_t eip,uint8_t opcode);
int or_r2rm_b(uint32_t eip,uint8_t opcode);
int or_rm2r_v(uint32_t eip,uint8_t opcode);
int or_rm2r_b(uint32_t eip,uint8_t opcode);
int not_rm_v(uint32_t eip,uint8_t opcode);
int neg_rm_v(uint32_t eip,uint8_t opcode);
int neg_rm_b(uint32_t eip,uint8_t opcode);
int mul_rm2a_v(uint32_t eip,uint8_t opcode);
int mul_rm2a_b(uint32_t eip,uint8_t opcode);
int imul_rm2a_v(uint32_t eip,uint8_t opcode);
int imul_rm2a_b(uint32_t eip,uint8_t opcode);
int idiv_rm2a_v(uint32_t eip,uint8_t opcode);
int idiv_rm2a_b(uint32_t eip,uint8_t opcode);
int div_rm2a_v(uint32_t eip,uint8_t opcode);
int div_rm2a_b(uint32_t eip,uint8_t opcode);
int test_i2rm_b(uint32_t eip,uint8_t opcode);
int test_i2rm_v(uint32_t eip,uint8_t opcode);
int sbb_r2rm_v(uint32_t eip,uint8_t opcode);
int sbb_r2rm_b(uint32_t eip,uint8_t opcode);
int sbb_rm2r_v(uint32_t eip,uint8_t opcode);
int sbb_rm2r_b(uint32_t eip,uint8_t opcode);
int imul_rm2r_v(uint32_t eip,uint8_t opcode);
int ret_near_imm16(uint32_t eup,uint8_t opcode);
int cmp_r2rm_b(uint32_t eip,uint8_t opcode);
int cmp_rm2r_b(uint32_t eip,uint8_t opcode);
int test_i2a_v(uint32_t eip,uint8_t opcode);
int test_i2a_b(uint32_t eip,uint8_t opcode);
int stos_b(uint32_t eip,uint8_t opcode);
#endif
