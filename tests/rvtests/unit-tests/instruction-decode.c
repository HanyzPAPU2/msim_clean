#include <stdint.h>
#include <pcut/pcut.h>
#include "../../../src/device/cpu/riscv_rv32ima/cpu.h"
#include "../../../src/device/cpu/riscv_rv32ima/instr.h"
#include "../../../src/device/cpu/riscv_rv32ima/instructions/computations.h"
#include "../../../src/device/cpu/riscv_rv32ima/instructions/control_transfer.h"
#include "../../../src/device/cpu/riscv_rv32ima/instructions/mem_ops.h"
#include "../../../src/device/cpu/riscv_rv32ima/instructions/system.h"

PCUT_INIT

PCUT_TEST_SUITE(instruction_decoding);

/*******************
 * OP instructions *
 *******************/

PCUT_TEST(op_add_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_ADD;
    instr.r.funct7  = rv_func_ADD >> 3;

    PCUT_ASSERT_EQUALS(rv_add_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_sub_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_SUB;
    instr.r.funct7  = rv_func_SUB >> 3;

    PCUT_ASSERT_EQUALS(rv_sub_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_sll_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_SLL;
    instr.r.funct7  = rv_func_SLL >> 3;

    PCUT_ASSERT_EQUALS(rv_sll_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_slt_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_SLT;
    instr.r.funct7  = rv_func_SLT >> 3;

    PCUT_ASSERT_EQUALS(rv_slt_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_sltu_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_SLTU;
    instr.r.funct7  = rv_func_SLTU >> 3;

    PCUT_ASSERT_EQUALS(rv_sltu_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_xor_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_XOR;
    instr.r.funct7  = rv_func_XOR >> 3;

    PCUT_ASSERT_EQUALS(rv_xor_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_srl_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_SRL;
    instr.r.funct7  = rv_func_SRL >> 3;

    PCUT_ASSERT_EQUALS(rv_srl_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_sra_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_SRA;
    instr.r.funct7  = rv_func_SRA >> 3;

    PCUT_ASSERT_EQUALS(rv_sra_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_or_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_OR;
    instr.r.funct7  = rv_func_OR >> 3;

    PCUT_ASSERT_EQUALS(rv_or_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_and_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_AND;
    instr.r.funct7  = rv_func_AND >> 3;

    PCUT_ASSERT_EQUALS(rv_and_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_mul_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_MUL;
    instr.r.funct7  = rv_func_MUL >> 3;

    PCUT_ASSERT_EQUALS(rv_mul_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_mulh_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_MULH;
    instr.r.funct7  = rv_func_MULH >> 3;

    PCUT_ASSERT_EQUALS(rv_mulh_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_mulhsu_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_MULHSU;
    instr.r.funct7  = rv_func_MULHSU >> 3;

    PCUT_ASSERT_EQUALS(rv_mulhsu_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_mulhu_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_MULHU;
    instr.r.funct7  = rv_func_MULHU >> 3;

    PCUT_ASSERT_EQUALS(rv_mulhu_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_div_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_DIV;
    instr.r.funct7  = rv_func_DIV >> 3;

    PCUT_ASSERT_EQUALS(rv_div_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_divu_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_DIVU;
    instr.r.funct7  = rv_func_DIVU >> 3;

    PCUT_ASSERT_EQUALS(rv_divu_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_rem_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_REM;
    instr.r.funct7  = rv_func_REM >> 3;

    PCUT_ASSERT_EQUALS(rv_rem_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_remu_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0b111 & rv_func_REMU;
    instr.r.funct7  = rv_func_REMU >> 3;

    PCUT_ASSERT_EQUALS(rv_remu_instr, rv_instr_decode(instr));
}

PCUT_TEST(op_illegal_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcOP;
    instr.r.funct3  = 0;
    instr.r.funct7  = 0b1010101;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

/***********************
 * BRANCH instructions *
 ***********************/

PCUT_TEST(branch_beq_decode){
    rv_instr_t instr;
    instr.b.opcode = rv_opcBRANCH;
    instr.b.funct3 = rv_func_BEQ;

    PCUT_ASSERT_EQUALS(rv_beq_instr, rv_instr_decode(instr));
}

PCUT_TEST(branch_bne_decode){
    rv_instr_t instr;
    instr.b.opcode = rv_opcBRANCH;
    instr.b.funct3 = rv_func_BNE;

    PCUT_ASSERT_EQUALS(rv_bne_instr, rv_instr_decode(instr));
}

PCUT_TEST(branch_blt_decode){
    rv_instr_t instr;
    instr.b.opcode = rv_opcBRANCH;
    instr.b.funct3 = rv_func_BLT;

    PCUT_ASSERT_EQUALS(rv_blt_instr, rv_instr_decode(instr));
}

PCUT_TEST(branch_bltu_decode){
    rv_instr_t instr;
    instr.b.opcode = rv_opcBRANCH;
    instr.b.funct3 = rv_func_BLTU;

    PCUT_ASSERT_EQUALS(rv_bltu_instr, rv_instr_decode(instr));
}

PCUT_TEST(branch_bge_decode){
    rv_instr_t instr;
    instr.b.opcode = rv_opcBRANCH;
    instr.b.funct3 = rv_func_BGE;

    PCUT_ASSERT_EQUALS(rv_bge_instr, rv_instr_decode(instr));
}

PCUT_TEST(branch_bgeu_decode){
    rv_instr_t instr;
    instr.b.opcode = rv_opcBRANCH;
    instr.b.funct3 = rv_func_BGEU;

    PCUT_ASSERT_EQUALS(rv_bgeu_instr, rv_instr_decode(instr));
}

PCUT_TEST(branch_illegal_decode){
    rv_instr_t instr;
    instr.b.opcode = rv_opcBRANCH;
    instr.b.funct3 = 0b010;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

/********************
 * JALR instruction *
 ********************/

PCUT_TEST(jalr_decode){
    rv_instr_t instr;
    instr.j.opcode = rv_opcJALR;
    instr.b.funct3 = 0;

    PCUT_ASSERT_EQUALS(rv_jalr_instr, rv_instr_decode(instr));
}

PCUT_TEST(jalr_illegal_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcJALR;
    instr.i.funct3 = 3;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

/*******************
 * JAL instruction *
 *******************/

PCUT_TEST(jal_decode){
    rv_instr_t instr;
    instr.j.opcode = rv_opcJAL;

    PCUT_ASSERT_EQUALS(rv_jal_instr, rv_instr_decode(instr));
}

/*********************
 * LOAD instructions *
 *********************/

PCUT_TEST(lb_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcLOAD;
    instr.i.funct3  = rv_func_LB;

    PCUT_ASSERT_EQUALS(rv_lb_instr, rv_instr_decode(instr));
}

PCUT_TEST(lh_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcLOAD;
    instr.i.funct3  = rv_func_LH;

    PCUT_ASSERT_EQUALS(rv_lh_instr, rv_instr_decode(instr));
}

PCUT_TEST(lw_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcLOAD;
    instr.i.funct3  = rv_func_LW;

    PCUT_ASSERT_EQUALS(rv_lw_instr, rv_instr_decode(instr));
}

PCUT_TEST(lbu_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcLOAD;
    instr.i.funct3  = rv_func_LBU;

    PCUT_ASSERT_EQUALS(rv_lbu_instr, rv_instr_decode(instr));
}

PCUT_TEST(lhu_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcLOAD;
    instr.i.funct3  = rv_func_LHU;

    PCUT_ASSERT_EQUALS(rv_lhu_instr, rv_instr_decode(instr));
}

PCUT_TEST(load_illegal_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcLOAD;
    instr.i.funct3  = 0b111;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

/**********************
 * STORE instructions *
 **********************/

PCUT_TEST(sb_decode){
    rv_instr_t instr;
    instr.s.opcode = rv_opcSTORE;
    instr.s.funct3  = rv_func_SB;

    PCUT_ASSERT_EQUALS(rv_sb_instr, rv_instr_decode(instr));
}

PCUT_TEST(sh_decode){
    rv_instr_t instr;
    instr.s.opcode = rv_opcSTORE;
    instr.s.funct3  = rv_func_SH;

    PCUT_ASSERT_EQUALS(rv_sh_instr, rv_instr_decode(instr));
}

PCUT_TEST(sw_decode){
    rv_instr_t instr;
    instr.s.opcode = rv_opcSTORE;
    instr.s.funct3  = rv_func_SW;

    PCUT_ASSERT_EQUALS(rv_sw_instr, rv_instr_decode(instr));
}

PCUT_TEST(store_illegal_decode){
    rv_instr_t instr;
    instr.s.opcode = rv_opcSTORE;
    instr.s.funct3  = 0b111;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

/*************************
 * MISC MEM instructions *
 *************************/

PCUT_TEST(fence_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcMISC_MEM;
    instr.i.funct3 = 0;

    PCUT_ASSERT_EQUALS(rv_fence_instr, rv_instr_decode(instr));
}

PCUT_TEST(misc_mem_illegal_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcMISC_MEM;
    instr.i.funct3 = 2;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

/***********************
 * OP IMM instructions *
 ***********************/

PCUT_TEST(addi_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_ADDI;

    PCUT_ASSERT_EQUALS(rv_addi_instr, rv_instr_decode(instr));
}

PCUT_TEST(slti_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_SLTI;

    PCUT_ASSERT_EQUALS(rv_slti_instr, rv_instr_decode(instr));
}

PCUT_TEST(sltiu_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_SLTIU;

    PCUT_ASSERT_EQUALS(rv_sltiu_instr, rv_instr_decode(instr));
}

PCUT_TEST(xori_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_XORI;

    PCUT_ASSERT_EQUALS(rv_xori_instr, rv_instr_decode(instr));
}

PCUT_TEST(ori_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_ORI;

    PCUT_ASSERT_EQUALS(rv_ori_instr, rv_instr_decode(instr));
}

PCUT_TEST(andi_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_ANDI;

    PCUT_ASSERT_EQUALS(rv_andi_instr, rv_instr_decode(instr));
}

PCUT_TEST(slli_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_SLLI;
    instr.i.imm = 0;

    PCUT_ASSERT_EQUALS(rv_slli_instr, rv_instr_decode(instr));
}

PCUT_TEST(slli_illegal_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_SLLI;
    instr.i.imm = 1<<6;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

PCUT_TEST(srli_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_SRI;
    instr.i.imm = 0;

    PCUT_ASSERT_EQUALS(rv_srli_instr, rv_instr_decode(instr));
}

PCUT_TEST(srai_decode){
    rv_instr_t instr;
    instr.i.opcode = rv_opcOP_IMM;
    instr.i.funct3 = rv_func_SRI;
    // set bit 30, as in spec
    instr.val |= 1<<30;

    PCUT_ASSERT_EQUALS(rv_srai_instr, rv_instr_decode(instr));
}

/**********************
 * AUIPC instructions *
 **********************/

PCUT_TEST(auipc_decode){
    rv_instr_t instr;
    instr.u.opcode = rv_opcAUIPC;

    PCUT_ASSERT_EQUALS(rv_auipc_instr, rv_instr_decode(instr));
}

/********************
 * AMO instructions *
 ********************/

PCUT_TEST(lr_decode){
    rv_instr_t instr;
    instr.r.opcode = rv_opcAMO;
    instr.r.funct3 = RV_AMO_32_WLEN;
    instr.r.rs2 = 0;
    instr.r.funct7 =  rv_funcLR << 2;

    PCUT_ASSERT_EQUALS(rv_lr_instr, rv_instr_decode(instr));
}

PCUT_TEST(lr_wrong_rs2){
    rv_instr_t instr;
    instr.r.opcode = rv_opcAMO;
    instr.r.funct3 = RV_AMO_32_WLEN;
    instr.r.rs2 = 5;
    instr.r.funct7 =  rv_funcLR << 2;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

PCUT_TEST(amo_wrong_width){
    rv_instr_t instr;
    instr.r.opcode = rv_opcAMO;
    instr.r.funct3 = 0b011;
    instr.r.funct7 =  rv_funcLR << 2;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

PCUT_TEST(amo_wrong_opc){
    rv_instr_t instr;
    instr.r.opcode = rv_opcAMO;
    instr.r.funct3 = RV_AMO_32_WLEN;
    instr.r.funct7 =  0b11111;

    PCUT_ASSERT_EQUALS(rv_illegal_instr, rv_instr_decode(instr));
}

/********************
 * LUI instructions *
 ********************/

PCUT_TEST(lui_decode){
    rv_instr_t instr;
    instr.u.opcode = rv_opcLUI;

    PCUT_ASSERT_EQUALS(rv_lui_instr, rv_instr_decode(instr));
}

PCUT_EXPORT(instruction_decoding);