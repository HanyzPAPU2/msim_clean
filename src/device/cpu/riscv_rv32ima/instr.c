/*
 * Copyright (c) 2022 Jan Papesch
 * All rights reserved.
 *
 * Distributed under the terms of GPL.
 *
 *
 *  RISC-V Instruction decoding
 *
 */

#include <stdio.h>
#include "instr.h"
#include "cpu.h"
#include "../../../assert.h"
#include "../../../main.h"

#include "instructions/computations.h"
#include "instructions/mem_ops.h"
#include "instructions/control_transfer.h"
#include "instructions/system.h"

rv_exc_t rv_illegal_instr(rv_cpu_t *cpu, rv_instr_t instr){
    return machine_undefined ? rv_exc_none : rv_exc_illegal_instruction;
}

static rv_instr_func_t decode_LOAD(rv_instr_t instr) {
    ASSERT(instr.i.opcode == rv_opcLOAD);
    switch(instr.i.funct3){
        case rv_func_LB:
            return rv_lb_instr;
        case rv_func_LH:
            return rv_lh_instr;
        case rv_func_LW:
            return rv_lw_instr;
        case rv_func_LBU:
            return rv_lbu_instr;
        case rv_func_LHU:
            return rv_lhu_instr;
        default:
            return rv_illegal_instr;
    }
}

static rv_instr_func_t decode_MISC_MEM(rv_instr_t instr) {
    ASSERT(instr.r.opcode == rv_opcMISC_MEM);
    if(instr.i.funct3 == 0){
        return rv_fence_instr;
    }
    return rv_illegal_instr; 
}

static rv_instr_func_t decode_OP_IMM(rv_instr_t instr) {
    ASSERT(instr.i.opcode == rv_opcOP_IMM);

    switch(instr.i.funct3){
        case rv_func_ADDI:
            return rv_addi_instr;
        case rv_func_SLTI:
            return rv_slti_instr;
        case rv_func_SLTIU:
            return rv_sltiu_instr;
        case rv_func_XORI:
            return rv_xori_instr;
        case rv_func_ORI:
            return rv_ori_instr;
        case rv_func_ANDI:
            return rv_andi_instr;
        case rv_func_SLLI:{
            if(instr.i.imm >> 5 == 0){
                return rv_slli_instr;
            } else{
                return rv_illegal_instr;
            }
        }
        case rv_func_SRI: {
            switch(instr.i.imm >> 5){
                case rv_SRAI:
                    return rv_srai_instr;
                case rv_SRLI:
                    return rv_srli_instr;
                default:
                    return rv_illegal_instr; 
            }
        }
        default:
            return rv_illegal_instr; 
    }
}

static rv_instr_func_t decode_AUIPC(rv_instr_t instr) {
    ASSERT(instr.r.opcode == rv_opcAUIPC);
    return rv_auipc_instr; 
}

static rv_instr_func_t decode_STORE(rv_instr_t instr) {
    ASSERT(instr.s.opcode == rv_opcSTORE);
    switch(instr.s.funct3){
        case rv_func_SB:
            return rv_sb_instr;
        case rv_func_SH:
            return rv_sh_instr;
        case rv_func_SW:
            return rv_sw_instr;
        default:
            return rv_illegal_instr;
    }
}

static rv_instr_func_t decode_AMO(rv_instr_t instr) {
    ASSERT(instr.r.opcode == rv_opcAMO);

    // only 32 bit width is supported
    if(instr.r.funct3 != RV_AMO_32_WLEN){
        return rv_illegal_instr;
    }

    switch(RV_AMO_FUNCT(instr)){
        case rv_funcLR:
            return instr.r.rs2 == 0 ? rv_lr_instr : rv_illegal_instr;
        case rv_funcSC:
            return rv_sc_instr;
        case rv_funcAMOSWAP:
            return rv_amoswap_instr;
        case rv_funcAMOADD:
            return rv_amoadd_instr;
        case rv_funcAMOXOR:
            return rv_amoxor_instr;
        case rv_funcAMOAND:
            return rv_amoand_instr;
        case rv_funcAMOOR:
            return rv_amoor_instr;
        case rv_funcAMOMIN:
            return rv_amomin_instr;
        case rv_funcAMOMAX:
            return rv_amomax_instr;
        case rv_funcAMOMINU:
            return rv_amominu_instr;
        case rv_funcAMOMAXU:
            return rv_amomaxu_instr;
        default:
            return rv_illegal_instr; 
    }
}

static rv_instr_func_t decode_OP(rv_instr_t instr) {
    ASSERT(instr.r.opcode == rv_opcOP);
    uint32_t funct = RV_R_FUNCT(instr);
    switch(funct){
        case rv_func_ADD:
            return rv_add_instr;
        case rv_func_SUB:
            return rv_sub_instr;
        case rv_func_SLL:
            return rv_sll_instr;
        case rv_func_SLT:
            return rv_slt_instr;
        case rv_func_SLTU:
            return rv_sltu_instr;
        case rv_func_XOR:
            return rv_xor_instr;
        case rv_func_SRL:
            return rv_srl_instr;
        case rv_func_SRA:
            return rv_sra_instr;
        case rv_func_OR:
            return rv_or_instr;
        case rv_func_AND:
            return rv_and_instr;
        // M extension
        case rv_func_MUL:
            return rv_mul_instr;
        case rv_func_MULH:
            return rv_mulh_instr;
        case rv_func_MULHSU:
            return rv_mulhsu_instr;
        case rv_func_MULHU:
            return rv_mulhu_instr;
        case rv_func_DIV:
            return rv_div_instr;
        case rv_func_DIVU:
            return rv_divu_instr;
        case rv_func_REM:
            return rv_rem_instr;
        case rv_func_REMU:
            return rv_remu_instr;
        default:
            return rv_illegal_instr;
    }    
}

static rv_instr_func_t decode_LUI(rv_instr_t instr) {
    ASSERT(instr.r.opcode == rv_opcLUI);
    return rv_lui_instr; 
}

static rv_instr_func_t decode_BRANCH(rv_instr_t instr) {
    ASSERT(instr.b.opcode == rv_opcBRANCH);
    switch(instr.b.funct3){
        case rv_func_BEQ:
            return rv_beq_instr;
        case rv_func_BNE:
            return rv_bne_instr;
        case rv_func_BLT:
            return rv_blt_instr;
        case rv_func_BLTU:
            return rv_bltu_instr;
        case rv_func_BGE:
            return rv_bge_instr;
        case rv_func_BGEU:
            return rv_bgeu_instr;
        default: 
            return rv_illegal_instr; 
    }
}

static rv_instr_func_t decode_JALR(rv_instr_t instr) {
    ASSERT(instr.i.opcode == rv_opcJALR);

    if(instr.i.funct3 != 0) {
        return rv_illegal_instr;
    }    
    return rv_jalr_instr; 
}

static rv_instr_func_t decode_JAL(rv_instr_t instr) {
    ASSERT(instr.r.opcode == rv_opcJAL);
    return rv_jal_instr; 
}


static rv_instr_func_t decode_PRIV(rv_instr_t instr){
    ASSERT(instr.i.opcode == rv_opcSYSTEM);
    ASSERT(instr.i.funct3 == rv_funcPRIV);

    if (instr.r.funct7 == rv_privSFENCEVMA_FUNCT7) {
        return rv_sfence_instr;
    }

    switch (instr.i.imm & 0xFFF) {
        case rv_privEBREAK:
            return rv_break_instr;
        case rv_privEHALT:
            return machine_specific_instructions ? rv_halt_instr : rv_illegal_instr;
        case rv_privEDUMP:
            return machine_specific_instructions ? rv_dump_instr : rv_illegal_instr;
        case rv_privETRACES:
            return machine_specific_instructions ? rv_trace_set_instr : rv_illegal_instr;
        case rv_privETRACER:
            return machine_specific_instructions ? rv_trace_reset_instr : rv_illegal_instr;
        case rv_privECSRRD:
            return machine_specific_instructions ? rv_csr_rd_instr : rv_illegal_instr;
        case rv_privECALL:
            return rv_call_instr;
        case rv_privSRET:
            return rv_sret_instr;
        case rv_privMRET:
            return rv_mret_instr;
        case rv_privWFI:
            return rv_wfi_instr;
        default:
            return rv_illegal_instr;
    }
}

static rv_instr_func_t decode_SYSTEM(rv_instr_t instr) {
    ASSERT(instr.i.opcode == rv_opcSYSTEM);
    switch (instr.i.funct3) {
        case rv_funcPRIV:
            return decode_PRIV(instr);
        case rv_funcCSRRW:
            return rv_csrrw_instr;
        case rv_funcCSRRS:
            return rv_csrrs_instr;
        case rv_funcCSRRC:
            return rv_csrrc_instr;
        case rv_funcCSRRWI:
            return rv_csrrwi_instr;
        case rv_funcCSRRSI:
            return rv_csrrsi_instr;
        case rv_funcCSRRCI:
            return rv_csrrci_instr;
        default:
            return rv_illegal_instr;
    }
}

rv_instr_func_t rv_instr_decode(rv_instr_t instr){
    // opcode is at the same spot in all encodings, so any can be chosen
    switch (instr.r.opcode) {
        case rv_opcLOAD: 
            return decode_LOAD(instr);
        case rv_opcMISC_MEM:
            return decode_MISC_MEM(instr);
        case rv_opcOP_IMM:
            return decode_OP_IMM(instr);
        case rv_opcAUIPC:
            return decode_AUIPC(instr);
        case rv_opcSTORE:
            return decode_STORE(instr);
        case rv_opcAMO:
            return decode_AMO(instr);
        case rv_opcOP:
            return decode_OP(instr);
        case rv_opcLUI:
            return decode_LUI(instr);
        case rv_opcBRANCH:
            return decode_BRANCH(instr);
        case rv_opcJALR:
            return decode_JALR(instr);
        case rv_opcJAL:
            return decode_JAL(instr);
        case rv_opcSYSTEM: 
            return decode_SYSTEM(instr);
        default: {
            return rv_illegal_instr;
        }
    }
}