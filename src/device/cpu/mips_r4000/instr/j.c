static r4k_exc_t instr_j(r4k_cpu_t *cpu, r4k_instr_t instr)
{
	cpu->pc_next.ptr =
	    (cpu->pc_next.ptr & TARGET_COMB) | (instr.j.target << TARGET_SHIFT);
	cpu->branch = BRANCH_COND;
	return r4k_excJump;
}

static void mnemonics_j(ptr64_t addr, r4k_instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "j");
	disassemble_target(addr, instr, mnemonics, comments);
}
