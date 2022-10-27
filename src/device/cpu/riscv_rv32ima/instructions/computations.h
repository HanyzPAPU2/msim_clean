/*
 * Copyright (c) 2022 Jan Papesch
 * All rights reserved.
 *
 * Distributed under the terms of GPL.
 *
 *
 *  RISC-V arithmetic instructions (includes AMO instructions from A extension)
 *
 */

#ifndef RISCV_RV32IMA_INSTR_COMPUTATIONS_H_
#define RISCV_RV32IMA_INSTR_COMPUTATIONS_H_

#include "../instr.h"
#include "../cpu.h"

extern rv_exc_t add_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t sub_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t sll_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t slt_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t sltu_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t xor_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t srl_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t sra_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t or_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t and_instr(rv_cpu_t *cpu, rv_instr_t instr);

extern rv_exc_t addi_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t slti_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t sltiu_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t andi_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t ori_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t xori_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t slli_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t srli_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t srai_instr(rv_cpu_t *cpu, rv_instr_t instr);

extern rv_exc_t lui_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t auipc_instr(rv_cpu_t *cpu, rv_instr_t instr);

/* M extension */

extern rv_exc_t mul_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t mulh_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t mulhsu_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t mulhu_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t div_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t divu_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t rem_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t remu_instr(rv_cpu_t *cpu, rv_instr_t instr);

/* A extension atomic operations */

extern rv_exc_t amoswap_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t amoadd_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t amoxor_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t amoand_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t amoor_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t amomin_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t amomax_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t amominu_instr(rv_cpu_t *cpu, rv_instr_t instr);
extern rv_exc_t amomaxu_instr(rv_cpu_t *cpu, rv_instr_t instr);

#endif // RISCV_RV32IMA_INSTR_COMPUTATIONS_H_