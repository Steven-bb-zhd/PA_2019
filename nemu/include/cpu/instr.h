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
int push_ebp_v(uint32_t eip,uint8_t opcode);
int push_ebx_v(uint32_t eip,uint8_t opcode);
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
#endif
