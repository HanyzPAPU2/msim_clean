#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#include "debug.h"
#include "cpu.h"
#include "csr.h"
#include "../../../assert.h"
#include "../../../fault.h"
#include "../../../utils.h"
#include "../../../env.h"
#include "mnemonics.h"

char *rv_reg_name_table[__rv_regname_type_count][RV_REG_COUNT] = {
    {
         "x0",  "x1",  "x2",  "x2",  "x4",  "x5",  "x6",  "x7",
         "x8",  "x9", "x10", "x11", "x12", "x13", "x14", "x15",
        "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
        "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31"
    },
    {
         "zero", "ra", "sp",  "gp",  "tp", "t0", "t1", "t2",
        "s0/fp", "s1", "a0",  "a1",  "a2", "a3", "a4", "a5",
           "a6", "a7", "s2",  "s3",  "s4", "s5", "s6", "s7",
           "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
    }
};

char *rv_csr_name_table[0x1000] = {
    [csr_cycle] = "cycle",
    [csr_time]  = "time",
    [csr_instret] = "instret",

    [csr_hpmcounter3  ]  = 	"hpmcounter3",
	[csr_hpmcounter4  ]  = 	"hpmcounter4",
	[csr_hpmcounter5  ]  = 	"hpmcounter5",
	[csr_hpmcounter6  ]  = 	"hpmcounter6",
	[csr_hpmcounter7  ]  = 	"hpmcounter7",
	[csr_hpmcounter8  ]  = 	"hpmcounter8",
	[csr_hpmcounter9  ]  = 	"hpmcounter9",
	[csr_hpmcounter10 ]  = 	"hpmcounter10",
	[csr_hpmcounter11 ]  = 	"hpmcounter11",
	[csr_hpmcounter12 ]  = 	"hpmcounter12",
	[csr_hpmcounter13 ]  = 	"hpmcounter13",
	[csr_hpmcounter14 ]  = 	"hpmcounter14",
	[csr_hpmcounter15 ]  = 	"hpmcounter15",
	[csr_hpmcounter16 ]  = 	"hpmcounter16",
	[csr_hpmcounter17 ]  = 	"hpmcounter17",
	[csr_hpmcounter18 ]  = 	"hpmcounter18",
	[csr_hpmcounter19 ]  = 	"hpmcounter19",
	[csr_hpmcounter20 ]  = 	"hpmcounter20",
	[csr_hpmcounter21 ]  = 	"hpmcounter21",
	[csr_hpmcounter22 ]  = 	"hpmcounter22",
	[csr_hpmcounter23 ]  = 	"hpmcounter23",
	[csr_hpmcounter24 ]  = 	"hpmcounter24",
	[csr_hpmcounter25 ]  = 	"hpmcounter25",
	[csr_hpmcounter26 ]  = 	"hpmcounter26",
	[csr_hpmcounter27 ]  = 	"hpmcounter27",
	[csr_hpmcounter28 ]  = 	"hpmcounter28",
	[csr_hpmcounter29 ]  = 	"hpmcounter29",
	[csr_hpmcounter30 ]  = 	"hpmcounter30",
	[csr_hpmcounter31 ]  = 	"hpmcounter31",

    [csr_cycleh 	]	 =	"cycleh",
	[csr_timeh 		]    = 	"timeh",
	[csr_instreth 	]    =	"instreth",
	[csr_hpmcounter3h  ] = 	"hpmcounter3h",
	[csr_hpmcounter4h  ] = 	"hpmcounter4h",
	[csr_hpmcounter5h  ] = 	"hpmcounter5h",
	[csr_hpmcounter6h  ] = 	"hpmcounter6h",
	[csr_hpmcounter7h  ] = 	"hpmcounter7h",
	[csr_hpmcounter8h  ] = 	"hpmcounter8h",
	[csr_hpmcounter9h  ] = 	"hpmcounter9h",
	[csr_hpmcounter10h ] =	"hpmcounter10h",
	[csr_hpmcounter11h ] = 	"hpmcounter11h",
	[csr_hpmcounter12h ] = 	"hpmcounter12h",
	[csr_hpmcounter13h ] = 	"hpmcounter13h",
	[csr_hpmcounter14h ] = 	"hpmcounter14h",
	[csr_hpmcounter15h ] = 	"hpmcounter15h",
	[csr_hpmcounter16h ] = 	"hpmcounter16h",
	[csr_hpmcounter17h ] = 	"hpmcounter17h",
	[csr_hpmcounter18h ] = 	"hpmcounter18h",
	[csr_hpmcounter19h ] = 	"hpmcounter19h",
	[csr_hpmcounter20h ] = 	"hpmcounter20h",
	[csr_hpmcounter21h ] = 	"hpmcounter21h",
	[csr_hpmcounter22h ] = 	"hpmcounter22h",
	[csr_hpmcounter23h ] = 	"hpmcounter23h",
	[csr_hpmcounter24h ] = 	"hpmcounter24h",
	[csr_hpmcounter25h ] = 	"hpmcounter25h",
	[csr_hpmcounter26h ] = 	"hpmcounter26h",
	[csr_hpmcounter27h ] = 	"hpmcounter27h",
	[csr_hpmcounter28h ] = 	"hpmcounter28h",
	[csr_hpmcounter29h ] = 	"hpmcounter29h",
	[csr_hpmcounter30h ] = 	"hpmcounter30h",
	[csr_hpmcounter31h ] = 	"hpmcounter31h",

    [csr_sstatus]        =  "sstatus", 	
	[csr_sie]            = 	"sie",
    [csr_stvec]          = 	"stvec",    
	[csr_scounteren]     =  "scounteren",

    [csr_senvcfg]        =  "senvcfg",

    [csr_sscratch] 	     = 	"sscratch",
	[csr_sepc]		     = 	"sepc",
	[csr_scause] 	 	 = 	"scause",
	[csr_stval]          =  "stval",
	[csr_sip]            =  "sip",

    [csr_satp]           =  "satp",
    [csr_scontext]       =  "scontext",

    [csr_mvendorid]      =    "mvendorid",
	[csr_marchid]        =    "marchid",
	[csr_mimpid]         =    "mimpid",
	[csr_mhartid]        =    "mhartid",
	[csr_mconfigptr]     =    "mconfigptr",

	[csr_mstatus]        =    "mstatus",
	[csr_misa]           =    "misa",
	[csr_medeleg]        =    "medeleg",
	[csr_mideleg]        =    "mideleg",
	[csr_mie]            =    "mie",
	[csr_mtvec]          =    "mtvec",
	[csr_mcounteren]     =    "mcounteren",
	[csr_mstatush]       =    "mstatush",

	[csr_mscratch]       =    "mscratch",
	[csr_mepc]           =    "mepc",
	[csr_mcause]         =    "mcause",
	[csr_mtval]          =    "mtval",
	[csr_mip]            =    "mip",
	[csr_mtinst]         =    "mtinst",
	[csr_mtval2]         =    "mtval2",

	[csr_menvcfg]        =    "menvcfg",
	[csr_mevncfgh]       =    "mevncfgh",
	[csr_mseccfg]        =    "mseccfg",
	[csr_mseccfgh]       =    "mseccfgh",

	[csr_pmpcfg0]        =    "pmpcfg0",    
	[csr_pmpcfg1]        =    "pmpcfg1",
	[csr_pmpcfg2]        =    "pmpcfg2",
	[csr_pmpcfg3]        =    "pmpcfg3",
	[csr_pmpcfg4]        =    "pmpcfg4",
	[csr_pmpcfg5]        =    "pmpcfg5",
	[csr_pmpcfg6]        =    "pmpcfg6",
	[csr_pmpcfg7]        =    "pmpcfg7",
	[csr_pmpcfg8]        =    "pmpcfg8",
	[csr_pmpcfg9]        =    "pmpcfg9",
	[csr_pmpcfg10]       =    "pmpcfg10",
	[csr_pmpcfg11]       =    "pmpcfg11",
	[csr_pmpcfg12]       =    "pmpcfg12",
	[csr_pmpcfg13]       =    "pmpcfg13",
	[csr_pmpcfg14]       =    "pmpcfg14",
	[csr_pmpcfg15]       =    "pmpcfg15",

	[csr_pmpaddr0]       =    "pmpaddr0",
    [csr_pmpaddr1]       =    "pmpaddr1",
    [csr_pmpaddr2]       =    "pmpaddr2",
    [csr_pmpaddr3]       =    "pmpaddr3",
    [csr_pmpaddr4]       =    "pmpaddr4",
    [csr_pmpaddr5]       =    "pmpaddr5",
    [csr_pmpaddr6]       =    "pmpaddr6",
    [csr_pmpaddr7]       =    "pmpaddr7",
    [csr_pmpaddr8]       =    "pmpaddr8",
    [csr_pmpaddr9]       =    "pmpaddr9",
    [csr_pmpaddr10]      =    "pmpaddr10",
    [csr_pmpaddr11]      =    "pmpaddr11",
    [csr_pmpaddr12]      =    "pmpaddr12",
    [csr_pmpaddr13]      =    "pmpaddr13",
    [csr_pmpaddr14]      =    "pmpaddr14",
    [csr_pmpaddr15]      =    "pmpaddr15",
    [csr_pmpaddr16]      =    "pmpaddr16",
    [csr_pmpaddr17]      =    "pmpaddr17",
    [csr_pmpaddr18]      =    "pmpaddr18",
    [csr_pmpaddr19]      =    "pmpaddr19",
    [csr_pmpaddr20]      =    "pmpaddr20",
    [csr_pmpaddr21]      =    "pmpaddr21",
    [csr_pmpaddr22]      =    "pmpaddr22",
    [csr_pmpaddr23]      =    "pmpaddr23",
    [csr_pmpaddr24]      =    "pmpaddr24",
    [csr_pmpaddr25]      =    "pmpaddr25",
    [csr_pmpaddr26]      =    "pmpaddr26",
    [csr_pmpaddr27]      =    "pmpaddr27",
    [csr_pmpaddr28]      =    "pmpaddr28",
    [csr_pmpaddr29]      =    "pmpaddr29",
    [csr_pmpaddr30]      =    "pmpaddr30",
    [csr_pmpaddr31]      =    "pmpaddr31",
    [csr_pmpaddr32]      =    "pmpaddr32",
    [csr_pmpaddr33]      =    "pmpaddr33",
    [csr_pmpaddr34]      =    "pmpaddr34",
    [csr_pmpaddr35]      =    "pmpaddr35",
    [csr_pmpaddr36]      =    "pmpaddr36",
    [csr_pmpaddr37]      =    "pmpaddr37",
    [csr_pmpaddr38]      =    "pmpaddr38",
    [csr_pmpaddr39]      =    "pmpaddr39",
    [csr_pmpaddr40]      =    "pmpaddr40",
    [csr_pmpaddr41]      =    "pmpaddr41",
    [csr_pmpaddr42]      =    "pmpaddr42",
    [csr_pmpaddr43]      =    "pmpaddr43",
    [csr_pmpaddr44]      =    "pmpaddr44",
    [csr_pmpaddr45]      =    "pmpaddr45",
    [csr_pmpaddr46]      =    "pmpaddr46",
    [csr_pmpaddr47]      =    "pmpaddr47",
    [csr_pmpaddr48]      =    "pmpaddr48",
    [csr_pmpaddr49]      =    "pmpaddr49",
    [csr_pmpaddr50]      =    "pmpaddr50",
    [csr_pmpaddr51]      =    "pmpaddr51",
    [csr_pmpaddr52]      =    "pmpaddr52",
    [csr_pmpaddr53]      =    "pmpaddr53",
    [csr_pmpaddr54]      =    "pmpaddr54",
    [csr_pmpaddr55]      =    "pmpaddr55",
    [csr_pmpaddr56]      =    "pmpaddr56",
    [csr_pmpaddr57]      =    "pmpaddr57",
    [csr_pmpaddr58]      =    "pmpaddr58",
    [csr_pmpaddr59]      =    "pmpaddr59",
    [csr_pmpaddr60]      =    "pmpaddr60",
    [csr_pmpaddr61]      =    "pmpaddr61",
    [csr_pmpaddr62]      =    "pmpaddr62",
    [csr_pmpaddr63]      =    "pmpaddr63",

	[csr_mcycle] 		 =	"mcycle",
	[csr_minstret] 	     =	"minstret",
	
	[csr_mhpmcounter3]   = 	"mhpmcounter3",
	[csr_mhpmcounter4]   = 	"mhpmcounter4",
	[csr_mhpmcounter5]   = 	"mhpmcounter5",
	[csr_mhpmcounter6]   = 	"mhpmcounter6",
	[csr_mhpmcounter7]   = 	"mhpmcounter7",
	[csr_mhpmcounter8]   = 	"mhpmcounter8",
	[csr_mhpmcounter9]   = 	"mhpmcounter9",
	[csr_mhpmcounter10]  = 	"mhpmcounter10",
	[csr_mhpmcounter11]  = 	"mhpmcounter11",
	[csr_mhpmcounter12]  = 	"mhpmcounter12",
	[csr_mhpmcounter13]  = 	"mhpmcounter13",
	[csr_mhpmcounter14]  = 	"mhpmcounter14",
	[csr_mhpmcounter15]  = 	"mhpmcounter15",
	[csr_mhpmcounter16]  = 	"mhpmcounter16",
	[csr_mhpmcounter17]  = 	"mhpmcounter17",
	[csr_mhpmcounter18]  = 	"mhpmcounter18",
	[csr_mhpmcounter19]  = 	"mhpmcounter19",
	[csr_mhpmcounter20]  = 	"mhpmcounter20",
	[csr_mhpmcounter21]  = 	"mhpmcounter21",
	[csr_mhpmcounter22]  = 	"mhpmcounter22",
	[csr_mhpmcounter23]  = 	"mhpmcounter23",
	[csr_mhpmcounter24]  = 	"mhpmcounter24",
	[csr_mhpmcounter25]  = 	"mhpmcounter25",
	[csr_mhpmcounter26]  = 	"mhpmcounter26",
	[csr_mhpmcounter27]  = 	"mhpmcounter27",
	[csr_mhpmcounter28]  = 	"mhpmcounter28",
	[csr_mhpmcounter29]  = 	"mhpmcounter29",
	[csr_mhpmcounter30]  = 	"mhpmcounter30",
	[csr_mhpmcounter31]  = 	"mhpmcounter31",

	[csr_mcycleh]        =	"mcycleh",
	[csr_minstreth] 	 =	"minstreth",

	[csr_mhpmcounter3h]   = 	"mhpmcounter3h",
	[csr_mhpmcounter4h]   = 	"mhpmcounter4h",
	[csr_mhpmcounter5h]   = 	"mhpmcounter5h",
	[csr_mhpmcounter6h]   = 	"mhpmcounter6h",
	[csr_mhpmcounter7h]   = 	"mhpmcounter7h",
	[csr_mhpmcounter8h]   = 	"mhpmcounter8h",
	[csr_mhpmcounter9h]   = 	"mhpmcounter9h",
	[csr_mhpmcounter10h]  = 	"mhpmcounter10h",
	[csr_mhpmcounter11h]  = 	"mhpmcounter11h",
	[csr_mhpmcounter12h]  = 	"mhpmcounter12h",
	[csr_mhpmcounter13h]  = 	"mhpmcounter13h",
	[csr_mhpmcounter14h]  = 	"mhpmcounter14h",
	[csr_mhpmcounter15h]  = 	"mhpmcounter15h",
	[csr_mhpmcounter16h]  = 	"mhpmcounter16h",
	[csr_mhpmcounter17h]  = 	"mhpmcounter17h",
	[csr_mhpmcounter18h]  = 	"mhpmcounter18h",
	[csr_mhpmcounter19h]  = 	"mhpmcounter19h",
	[csr_mhpmcounter20h]  = 	"mhpmcounter20h",
	[csr_mhpmcounter21h]  = 	"mhpmcounter21h",
	[csr_mhpmcounter22h]  = 	"mhpmcounter22h",
	[csr_mhpmcounter23h]  = 	"mhpmcounter23h",
	[csr_mhpmcounter24h]  = 	"mhpmcounter24h",
	[csr_mhpmcounter25h]  = 	"mhpmcounter25h",
	[csr_mhpmcounter26h]  = 	"mhpmcounter26h",
	[csr_mhpmcounter27h]  = 	"mhpmcounter27h",
	[csr_mhpmcounter28h]  = 	"mhpmcounter28h",
	[csr_mhpmcounter29h]  = 	"mhpmcounter29h",
	[csr_mhpmcounter30h]  = 	"mhpmcounter30h",
	[csr_mhpmcounter31h]  = 	"mhpmcounter31h",

	[csr_mcountinhibit]  =    "mcountinhibit",
	
	[csr_mhmpevent3]     =	"mhmpevent3",
	[csr_mhmpevent4]     =	"mhmpevent4",
	[csr_mhmpevent5]     =	"mhmpevent5",
	[csr_mhmpevent6]     =	"mhmpevent6",
	[csr_mhmpevent7]     =	"mhmpevent7",
	[csr_mhmpevent8]     =	"mhmpevent8",
	[csr_mhmpevent9]     =	"mhmpevent9",
	[csr_mhmpevent10]    =	"mhmpevent10",
	[csr_mhmpevent11]    =	"mhmpevent11",
	[csr_mhmpevent12]    =	"mhmpevent12",
	[csr_mhmpevent13]    =	"mhmpevent13",
	[csr_mhmpevent14]    =	"mhmpevent14",
	[csr_mhmpevent15]    =	"mhmpevent15",
	[csr_mhmpevent16]    =	"mhmpevent16",
	[csr_mhmpevent17]    =	"mhmpevent17",
	[csr_mhmpevent18]    =	"mhmpevent18",
	[csr_mhmpevent19]    =	"mhmpevent19",
	[csr_mhmpevent20]    =	"mhmpevent20",
	[csr_mhmpevent21]    =	"mhmpevent21",
	[csr_mhmpevent22]    =	"mhmpevent22",
	[csr_mhmpevent23]    =	"mhmpevent23",
	[csr_mhmpevent24]    =	"mhmpevent24",
	[csr_mhmpevent25]    =	"mhmpevent25",
	[csr_mhmpevent26]    =	"mhmpevent26",
	[csr_mhmpevent27]    =	"mhmpevent27",
	[csr_mhmpevent28]    =	"mhmpevent28",
	[csr_mhmpevent29]    =	"mhmpevent29",
	[csr_mhmpevent30]    =	"mhmpevent30",
	[csr_mhmpevent31]    =	"mhmpevent31",

	[csr_tselect]        =    "tselect",
	[csr_tdata1]         =    "tdata1",
	[csr_tdata2]         =    "tdata2",
	[csr_tdata3]         =    "tdata3",
	[csr_mcontext]       =    "mcontext",
	
	[csr_dcsr]           =    "dcsr",
	[csr_dpc]            =    "dpc",
	[csr_dscratch0]      =    "dscratch0",
	[csr_dscratch1]      =    "dscratch1" 
};

char** rv_regnames;
char** rv_csrnames;

static rv_regname_type_t curr_regname_type = rv_regname_abi;

void rv_debug_init(void){
    rv_regnames = rv_reg_name_table[curr_regname_type];
    rv_csrnames = rv_csr_name_table;
}

bool rv_debug_change_regnames(unsigned int type){
    if(type >= __rv_regname_type_count){
        error("Index out of range 0..%u", __rv_regname_type_count - 1);
        return false;
    }
    curr_regname_type = (rv_regname_type_t)type;
    rv_regnames = rv_reg_name_table[curr_regname_type];
    return true;
}

void rv_reg_dump(rv_cpu_t *cpu){

    ASSERT(cpu != NULL);

    printf("processor %u\n", cpu->csr.mhartid);
    
    for(unsigned int i=0; i<RV_REG_COUNT; i+=4){
        printf(" %5s: %8x %5s: %8x %5s: %8x %5s: %8x\n",
            rv_regnames[i],   cpu->regs[i],
            rv_regnames[i+1], cpu->regs[i+1],
            rv_regnames[i+2], cpu->regs[i+2],
            rv_regnames[i+3], cpu->regs[i+3]
        );
    }
    
    printf(" %5s: %08x\n", "pc", cpu->pc);
}

static void idump_common(uint32_t addr, rv_instr_t instr, string_t *s_opc,
    string_t *s_mnemonics, string_t *s_comments){

    string_printf(s_opc, "%08x", instr.val);

    rv_mnemonics_func_t mnem_func = rv_decode_mnemonics(instr);

    mnem_func(addr, instr, s_mnemonics, s_comments);
}

void rv_idump(rv_cpu_t *cpu, uint32_t addr, rv_instr_t instr){
    string_t s_cpu;
	string_t s_addr;
	string_t s_opc;
	string_t s_mnemonics;
	string_t s_comments;

	string_init(&s_cpu);
	string_init(&s_addr);
	string_init(&s_opc);
	string_init(&s_mnemonics);
	string_init(&s_comments);

    if(cpu != NULL){
        string_printf(&s_cpu, "cpu%u", cpu->csr.mhartid);
    }

    string_printf(&s_addr, "0x%08x", addr);

    idump_common(addr, instr, &s_opc, &s_mnemonics, &s_comments);

    if(cpu != NULL)
        printf("%-5s ", s_cpu.str);
    if(iaddr)
        printf("%-10s ", s_addr.str);
    if(iopc)        
        printf("%-8s ", s_opc.str);
    
    printf("%-24s", s_mnemonics.str);

    if(icmt && s_comments.size > 0 && s_comments.str[0] != 0){
        printf("    [ %s ]", s_comments.str);
    }
    
    printf("\n");
}

static void print_64_reg(uint64_t val, const char* name){
	printf("%s 0x%016lx (%sh = 0x%08x, %s = 0x%08x)\n", name, val, name, (uint32_t)(val >> 32), name, (uint32_t)val);
}

static void print_cycle(rv_cpu_t *cpu){
	print_64_reg(cpu->csr.cycle, "cycle");
}

static uint64_t current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    uint64_t milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}

static void print_time(rv_cpu_t *cpu) {
	printf("(not accurate) ");
	print_64_reg(current_timestamp(), "time");
}

static void print_instret(rv_cpu_t *cpu){
	print_64_reg(cpu->csr.instret, "instret");
}

static void print_hpm(rv_cpu_t *cpu, int hpm){
	ASSERT((hpm >= 3 && hpm < 32));
	string_t s;
	string_init(&s);
	printf("before sprintf\n");
	string_printf(&s, "hpmcounter%i", hpm);
	printf("after sprintf\n");
	print_64_reg(cpu->csr.hpmcounters[hpm - 3], s.str);
}

void rv_csr_dump_all(rv_cpu_t *cpu){
	printf("dumping all CSRs!\n");
	
}

bool rv_csr_dump(rv_cpu_t *cpu, int csr){
	ASSERT((csr >= 0 && csr < 0x1000));
	ASSERT(cpu != NULL);

	if(rv_csr_name_table[csr] == NULL){
		printf("Invalid CSR!\n");
		return false;
	}

	printf("%s (0x%03x):\n", rv_csr_name_table[csr] ,csr);

	switch(csr){
		case csr_cycle:
		case csr_cycleh:
		case csr_mcycle:
		case csr_mcycleh:
			print_cycle(cpu);
			break;
		case csr_time:
		case csr_timeh:
			print_time(cpu);
			break;
		case csr_instret:
		case csr_instreth:
		case csr_minstret:
		case csr_minstreth:
			print_instret(cpu);
			break;
		case csr_hpmcounter3:
		case csr_hpmcounter4:
		case csr_hpmcounter5:
		case csr_hpmcounter6:
		case csr_hpmcounter7:
		case csr_hpmcounter8:
		case csr_hpmcounter9:
		case csr_hpmcounter10:
		case csr_hpmcounter11:
		case csr_hpmcounter12:
		case csr_hpmcounter13:
		case csr_hpmcounter14:
		case csr_hpmcounter15:
		case csr_hpmcounter16:
		case csr_hpmcounter17:
		case csr_hpmcounter18:
		case csr_hpmcounter19:
		case csr_hpmcounter20:
		case csr_hpmcounter21:
		case csr_hpmcounter22:
		case csr_hpmcounter23:
		case csr_hpmcounter24:
		case csr_hpmcounter25:
		case csr_hpmcounter26:
		case csr_hpmcounter27:
		case csr_hpmcounter28:
		case csr_hpmcounter29:
		case csr_hpmcounter30:
		case csr_hpmcounter31:
		case csr_hpmcounter3h:
		case csr_hpmcounter4h:
		case csr_hpmcounter5h:
		case csr_hpmcounter6h:
		case csr_hpmcounter7h:
		case csr_hpmcounter8h:
		case csr_hpmcounter9h:
		case csr_hpmcounter10h:
		case csr_hpmcounter11h:
		case csr_hpmcounter12h:
		case csr_hpmcounter13h:
		case csr_hpmcounter14h:
		case csr_hpmcounter15h:
		case csr_hpmcounter16h:
		case csr_hpmcounter17h:
		case csr_hpmcounter18h:
		case csr_hpmcounter19h:
		case csr_hpmcounter20h:
		case csr_hpmcounter21h:
		case csr_hpmcounter22h:
		case csr_hpmcounter23h:
		case csr_hpmcounter24h:
		case csr_hpmcounter25h:
		case csr_hpmcounter26h:
		case csr_hpmcounter27h:
		case csr_hpmcounter28h:
		case csr_hpmcounter29h:
		case csr_hpmcounter30h:
		case csr_hpmcounter31h:
		case csr_mhpmcounter3:
		case csr_mhpmcounter4:
		case csr_mhpmcounter5:
		case csr_mhpmcounter6:
		case csr_mhpmcounter7:
		case csr_mhpmcounter8:
		case csr_mhpmcounter9:
		case csr_mhpmcounter10:
		case csr_mhpmcounter11:
		case csr_mhpmcounter12:
		case csr_mhpmcounter13:
		case csr_mhpmcounter14:
		case csr_mhpmcounter15:
		case csr_mhpmcounter16:
		case csr_mhpmcounter17:
		case csr_mhpmcounter18:
		case csr_mhpmcounter19:
		case csr_mhpmcounter20:
		case csr_mhpmcounter21:
		case csr_mhpmcounter22:
		case csr_mhpmcounter23:
		case csr_mhpmcounter24:
		case csr_mhpmcounter25:
		case csr_mhpmcounter26:
		case csr_mhpmcounter27:
		case csr_mhpmcounter28:
		case csr_mhpmcounter29:
		case csr_mhpmcounter30:
		case csr_mhpmcounter31:
		case csr_mhpmcounter3h:
		case csr_mhpmcounter4h:
		case csr_mhpmcounter5h:
		case csr_mhpmcounter6h:
		case csr_mhpmcounter7h:
		case csr_mhpmcounter8h:
		case csr_mhpmcounter9h:
		case csr_mhpmcounter10h:
		case csr_mhpmcounter11h:
		case csr_mhpmcounter12h:
		case csr_mhpmcounter13h:
		case csr_mhpmcounter14h:
		case csr_mhpmcounter15h:
		case csr_mhpmcounter16h:
		case csr_mhpmcounter17h:
		case csr_mhpmcounter18h:
		case csr_mhpmcounter19h:
		case csr_mhpmcounter20h:
		case csr_mhpmcounter21h:
		case csr_mhpmcounter22h:
		case csr_mhpmcounter23h:
		case csr_mhpmcounter24h:
		case csr_mhpmcounter25h:
		case csr_mhpmcounter26h:
		case csr_mhpmcounter27h:
		case csr_mhpmcounter28h:
		case csr_mhpmcounter29h:
		case csr_mhpmcounter30h:
		case csr_mhpmcounter31h:
			print_hpm(cpu, csr & 0x1F);
			break;
		default:
			printf("Invalid CSR number!\n");
			return false;
	}
	return true;
}

bool rv_csr_dump_by_name(rv_cpu_t *cpu, const char* name){
	for(int i = 0; i < 0x1000; ++i){
		if(rv_csr_name_table[i] == NULL) continue;

		if(strcmp(name, rv_csr_name_table[i]) == 0){
			return rv_csr_dump(cpu, i);
		}
	}
	printf("Specified name is not a valid CSR!\n");
	return false;
}
