static r4k_exc_t instr_cfc2(r4k_cpu_t *cpu, r4k_instr_t instr)
{
	if (cp0_status_cu2(cpu)) {
		/* Ignored */
		return r4k_excNone;
	}
	
	/* Coprocessor unusable */
	cp0_cause(cpu).val &= ~cp0_cause_ce_mask;
	cp0_cause(cpu).val |= cp0_cause_ce_cu2;
	return r4k_excCpU;
}

static void mnemonics_cfc2(ptr64_t addr, r4k_instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "cfc2");
	disassemble_rt_rs(instr, mnemonics, comments);
}
