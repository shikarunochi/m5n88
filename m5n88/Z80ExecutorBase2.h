////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke
#include <M5Stack.h>
#ifndef Z80ExecutorBase2_DEFINED
#define Z80ExecutorBase2_DEFINED

////////////////////////////////////////////////////////////
// TZ80ExecutorBase2 super class

class CZ80Executor2Super {
// typedef
public:
	typedef void (*EXECPROC)();
};

////////////////////////////////////////////////////////////
// TZ80ExecutorBase2

template <class TZ>
class TZ80ExecutorBase2 : public CZ80Executor2Super {
// typedef
protected:
	typedef TZ TTZ80;

public:
	using CZ80Executor2Super::EXECPROC;

// enum
public:
	// flag
	enum {
		C_FLAG   = TTZ80::C_FLAG,
		N_FLAG   = TTZ80::N_FLAG,
		P_V_FLAG = TTZ80::P_V_FLAG,
		U1_FLAG  = TTZ80::U1_FLAG,
		H_FLAG   = TTZ80::H_FLAG,
		U2_FLAG  = TTZ80::U2_FLAG,
		Z_FLAG   = TTZ80::Z_FLAG,
		S_FLAG   = TTZ80::S_FLAG
	};
	// execute clock count
	enum {
		// 8bit load
		CLOCK_LD_r_r2		= 4,
		CLOCK_LD_r_n		= 4+3,
		CLOCK_LD_A_Qss		= 4+3,
		CLOCK_LD_Qss_A		= 4+3,
		CLOCK_LD_A_Qnn		= 4+3+3+3,
		CLOCK_LD_Qnn_A		= 4+3+3+3,
		CLOCK_LD_r_QHL		= 4+3,
		CLOCK_LD_QHL_r		= 4+3,
		CLOCK_LD_QHL_n		= 4+3+3,
		CLOCK_LD_r_QIXd		= /*4+*/4+3+5+3,
		CLOCK_LD_QIXd_r		= /*4+*/4+3+5+3,
		CLOCK_LD_QIXd_n		= /*4+*/4+3+5+3,
		CLOCK_LD_r_QIYd		= /*4+*/4+3+5+3,
		CLOCK_LD_QIYd_r		= /*4+*/4+3+5+3,
		CLOCK_LD_QIYd_n		= /*4+*/4+3+5+3,
		CLOCK_LD_A_I		= /*4+*/5,
		CLOCK_LD_I_A		= /*4+*/5,
		CLOCK_LD_A_R		= /*4+*/5,
		CLOCK_LD_R_A		= /*4+*/5,
		// 16bit load
		CLOCK_LD_ss_nn		= 4+3+3,
		CLOCK_LD_ss_Qnn		= /*4+*/4+3+3+3+3,
		CLOCK_LD_Qnn_ss		= /*4+*/4+3+3+3+3,
		CLOCK_LD_HL_Qnn		= 4+3+3+3+3,
		CLOCK_LD_Qnn_HL		= 4+3+3+3+3,
		CLOCK_LD_IX_nn		= /*4+*/4+3+3,
		CLOCK_LD_IX_Qnn		= /*4+*/4+3+3+3+3,
		CLOCK_LD_Qnn_IX		= /*4+*/4+3+3+3+3,
		CLOCK_LD_IY_nn		= /*4+*/4+3+3,
		CLOCK_LD_IY_Qnn		= /*4+*/4+3+3+3+3,
		CLOCK_LD_Qnn_IY		= /*4+*/4+3+3+3+3,
		CLOCK_LD_SP_HL		= 6,
		CLOCK_LD_SP_IX		= /*4+*/6,
		CLOCK_LD_SP_IY		= /*4+*/6,
		CLOCK_PUSH_ss		= 5+3+3,
		CLOCK_PUSH_IX		= /*4+*/5+3+3,
		CLOCK_PUSH_IY		= /*4+*/5+3+3,
		CLOCK_POP_ss		= 4+3+3,
		CLOCK_POP_IX		= /*4+*/4+3+3,
		CLOCK_POP_IY		= /*4+*/4+3+3,
		// exchange
		CLOCK_EX_AF_AF2		= 4,
		CLOCK_EX_DE_HL		= 4,
		CLOCK_EXX			= 4,
		CLOCK_EX_QSP_HL		= 4+3+4+3+5,
		CLOCK_EX_QSP_IX		= /*4+*/4+3+4+3+5,
		CLOCK_EX_QSP_IY		= /*4+*/4+3+4+3+5,
		// 8bit calculate
		CLOCK_INC_r			= 4,
		CLOCK_INC_QHL		= 4+4+3,
		CLOCK_INC_QIXd		= /*4+*/4+3+5+4+3,
		CLOCK_INC_QIYd		= /*4+*/4+3+5+4+3,
		CLOCK_DEC_r			= 4,
		CLOCK_DEC_QHL		= 4+4+3,
		CLOCK_DEC_QIXd		= /*4+*/4+3+5+4+3,
		CLOCK_DEC_QIYd		= /*4+*/4+3+5+4+3,
		CLOCK_ADD_A_r		= 4,
		CLOCK_ADD_A_n		= 4+3,
		CLOCK_ADD_A_QHL		= 4+3,
		CLOCK_ADD_A_QIXd	= /*4+*/+4+3+5+3,
		CLOCK_ADD_A_QIYd	= /*4+*/+4+3+5+3,
		CLOCK_ADC_A_r		= 4,
		CLOCK_ADC_A_n		= 4+3,
		CLOCK_ADC_A_QHL		= 4+3,
		CLOCK_ADC_A_QIXd	= /*4+*/+4+3+5+3,
		CLOCK_ADC_A_QIYd	= /*4+*/+4+3+5+3,
		CLOCK_SUB_r			= 4,
		CLOCK_SUB_n			= 4+3,
		CLOCK_SUB_QHL		= 4+3,
		CLOCK_SUB_QIXd		= /*4+*/+4+3+5+3,
		CLOCK_SUB_QIYd		= /*4+*/+4+3+5+3,
		CLOCK_SBC_A_r		= 4,
		CLOCK_SBC_A_n		= 4+3,
		CLOCK_SBC_A_QHL		= 4+3,
		CLOCK_SBC_A_QIXd	= /*4+*/+4+3+5+3,
		CLOCK_SBC_A_QIYd	= /*4+*/+4+3+5+3,
		CLOCK_AND_r			= 4,
		CLOCK_AND_n			= 4+3,
		CLOCK_AND_QHL		= 4+3,
		CLOCK_AND_QIXd		= /*4+*/+4+3+5+3,
		CLOCK_AND_QIYd		= /*4+*/+4+3+5+3,
		CLOCK_OR_r			= 4,
		CLOCK_OR_n			= 4+3,
		CLOCK_OR_QHL		= 4+3,
		CLOCK_OR_QIXd		= /*4+*/+4+3+5+3,
		CLOCK_OR_QIYd		= /*4+*/+4+3+5+3,
		CLOCK_XOR_r			= 4,
		CLOCK_XOR_n			= 4+3,
		CLOCK_XOR_QHL		= 4+3,
		CLOCK_XOR_QIXd		= /*4+*/+4+3+5+3,
		CLOCK_XOR_QIYd		= /*4+*/+4+3+5+3,
		CLOCK_CP_r			= 4,
		CLOCK_CP_n			= 4+3,
		CLOCK_CP_QHL		= 4+3,
		CLOCK_CP_QIXd		= /*4+*/+4+3+5+3,
		CLOCK_CP_QIYd		= /*4+*/+4+3+5+3,
		// rotate/shift
		CLOCK_RLCA			= 4,
		CLOCK_RLC_r			= /*4+*/4,
		CLOCK_RLC_QHL		= /*4+*/4+4+3,
		CLOCK_RLC_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_RLC_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_RLC_r_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_RLC_r_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_RLA			= 4,
		CLOCK_RL_r			= /*4+*/4,
		CLOCK_RL_QHL		= /*4+*/4+4+3,
		CLOCK_RL_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_RL_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_RL_r_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_RL_r_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_RRCA			= 4,
		CLOCK_RRC_r			= /*4+*/4,
		CLOCK_RRC_QHL		= /*4+*/4+4+3,
		CLOCK_RRC_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_RRC_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_RRC_r_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_RRC_r_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_RRA			= 4,
		CLOCK_RR_r			= /*4+*/4,
		CLOCK_RR_QHL		= /*4+*/4+4+3,
		CLOCK_RR_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_RR_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_RR_r_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_RR_r_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_SLA_r			= /*4+*/4,
		CLOCK_SLA_QHL		= /*4+*/4+4+3,
		CLOCK_SLA_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_SLA_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_SLA_r_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_SLA_r_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_SRA_r			= /*4+*/4,
		CLOCK_SRA_QHL		= /*4+*/4+4+3,
		CLOCK_SRA_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_SRA_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_SRA_r_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_SRA_r_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_SLL_r			= /*4+*/4,
		CLOCK_SLL_QHL		= /*4+*/4+4+3,
		CLOCK_SLL_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_SLL_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_SLL_r_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_SLL_r_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_SRL_r			= /*4+*/4,
		CLOCK_SRL_QHL		= /*4+*/4+4+3,
		CLOCK_SRL_QIXd		= /*4+4+3+*/5+4+3,
		CLOCK_SRL_QIYd		= /*4+4+3+*/5+4+3,
		CLOCK_SRL_r_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_SRL_r_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_RLD			= /*4+*/4+3+4+3,
		CLOCK_RRD			= /*4+*/4+3+4+3,
		// bit operate/test
		CLOCK_BIT_b_r		= /*4+*/4,
		CLOCK_BIT_b_QHL		= /*4+*/4+4,
		CLOCK_BIT_b_QIXd	= /*4+4+3+*/5+4,
		CLOCK_BIT_b_QIYd	= /*4+4+3+*/5+4,
		CLOCK_SET_b_r		= /*4+*/4,
		CLOCK_SET_b_QHL		= /*4+*/4+4+3,
		CLOCK_SET_b_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_SET_b_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_SET_b_r_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_SET_b_r_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_RES_b_r		= /*4+*/4,
		CLOCK_RES_b_QHL		= /*4+*/4+4+3,
		CLOCK_RES_b_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_RES_b_QIYd	= /*4+4+3+*/5+4+3,
		CLOCK_RES_b_r_QIXd	= /*4+4+3+*/5+4+3,
		CLOCK_RES_b_r_QIYd	= /*4+4+3+*/5+4+3,
		// 16bit calculate
		CLOCK_INC_ss		= 6,
		CLOCK_INC_IX		= /*4+*/6,
		CLOCK_INC_IY		= /*4+*/6,
		CLOCK_DEC_ss		= 6,
		CLOCK_DEC_IX		= /*4+*/6,
		CLOCK_DEC_IY		= /*4+*/6,
		CLOCK_ADD_HL_ss		= 4+4+3,
		CLOCK_ADD_IX_ss		= /*4+*/4+4+3,
		CLOCK_ADD_IY_ss		= /*4+*/4+4+3,
		CLOCK_ADC_HL_ss		= /*4+*/4+4+3,
		CLOCK_SBC_HL_ss		= /*4+*/4+4+3,
		// other calculate/CPU control
		CLOCK_DAA			= 4,
		CLOCK_CPL			= 4,
		CLOCK_NEG			= /*4+*/4,
		CLOCK_CCF			= 4,
		CLOCK_SCF			= 4,
		CLOCK_DI			= 4,
		CLOCK_EI			= 4,
		CLOCK_NOP			= 4,
		CLOCK_HALT			= 4,
		CLOCK_IM0			= /*4+*/4,
		CLOCK_IM1			= /*4+*/4,
		CLOCK_IM2			= /*4+*/4,
		CLOCK_IMx			= /*4+*/4,
		// branch
		CLOCK_JP_nn			= 4+3+3,
		CLOCK_JP_QHL		= 4,
		CLOCK_JP_QIX		= /*4+*/4,
		CLOCK_JP_QIY		= /*4+*/4,
		CLOCK_JP_cc_nn		= 4+3+3,
		CLOCK_JR_e			= 4+3+5,
		CLOCK_JR_cc_e_1		= 4+3,
		CLOCK_JR_cc_e_2		= 4+3+5,
		CLOCK_DJNZ_e_1		= 5+3,
		CLOCK_DJNZ_e_2		= 5+3+5,
		CLOCK_CALL_nn		= 4+3+4+3+3,
		CLOCK_CALL_cc_nn_1	= 4+3+3,
		CLOCK_CALL_cc_nn_2	= 4+3+4+3+3,
		CLOCK_RET			= 4+3+3,
		CLOCK_RET_cc_1		= 5,
		CLOCK_RET_cc_2		= 5+3+3,
		CLOCK_RST_n			= 5+3+3,
		CLOCK_RETI			= /*4+*/4+3+3,
		CLOCK_RETN			= /*4+*/4+3+3,
		// input/output
		CLOCK_IN_A_Qn		= 4+3+4,
		CLOCK_IN_r_QC		= /*4+*/4+4,
		CLOCK_IN_F_QC		= /*4+*/4+4,
		CLOCK_OUT_Qn_A		= 4+3+4,
		CLOCK_OUT_QC_r		= /*4+*/4+4,
		CLOCK_OUT_QC_0		= /*4+*/4+4,
		// block
		CLOCK_LDI			= /*4+*/4+3+5,
		CLOCK_LDD			= /*4+*/4+3+5,
		CLOCK_CPI			= /*4+*/4+3+5,
		CLOCK_CPD			= /*4+*/4+3+5,
		CLOCK_INI			= /*4+*/5+3+4,
		CLOCK_IND			= /*4+*/5+3+4,
		CLOCK_OUTI			= /*4+*/5+3+4,
		CLOCK_OUTD			= /*4+*/5+3+4,
		CLOCK_LDIR			= /*4+4+3+5+*/5,
		CLOCK_LDDR			= /*4+4+3+5+*/5,
		CLOCK_CPIR			= /*4+4+3+5+*/5,
		CLOCK_CPDR			= /*4+4+3+5+*/5,
		CLOCK_INIR			= /*4+5+3+4+*/5,
		CLOCK_INDR			= /*4+5+3+4+*/5,
		CLOCK_OTIR			= /*4+5+3+4+*/5,
		CLOCK_OTDR			= /*4+5+3+4+*/5,
		// extend
		CLOCK_CB_X			= 4,
		CLOCK_ED_X			= 4,
		CLOCK_DD_X			= 4,
		CLOCK_DD_CB_X		= /*4+*/4+3,
		CLOCK_FD_X			= 4,
		CLOCK_FD_CB_X		= /*4+*/4+3,
		// interrupt
		CLOCK_INTERRUPT0	= 6+3+3,
		CLOCK_INTERRUPT1	= 6+3+3,
		CLOCK_INTERRUPT2	= 6+3+3+3+3,
		CLOCK_NMINTERRUPT	= 4+3+3
	};
	enum {
		EXTRA_CB	= 0x0100,
		EXTRA_ED	= 0x0200,
		EXTRA_DD	= 0x0300,
		EXTRA_DD_CB	= 0x0400,
		EXTRA_FD	= 0x0500,
		EXTRA_FD_CB	= 0x0600
	};

// attribute
public:
	static int m_nOpCode;
	static uint16_t m_wNN;
	static uint8_t m_btX, m_btN, m_btD, m_btE;

	static EXECPROC m_aepExecuteTable[256*7];
	//static EXECPROC *m_aepExecuteTable;

// initialize
public:
	static void Initialize();
	static void Initialize_X();
	static void Initialize_CB_X();
	static void Initialize_ED_X();
	static void Initialize_DD_X();
	static void Initialize_DD_CB_X();
	static void Initialize_FD_X();
	static void Initialize_FD_CB_X();

// execute procedure
public:
	// Exec_X
	static void Exec_X_00();
	static void Exec_X_01();
	static void Exec_X_02();
	static void Exec_X_03();
	static void Exec_X_04();
	static void Exec_X_05();
	static void Exec_X_06();
	static void Exec_X_07();
	static void Exec_X_08();
	static void Exec_X_09();
	static void Exec_X_0A();
	static void Exec_X_0B();
	static void Exec_X_0C();
	static void Exec_X_0D();
	static void Exec_X_0E();
	static void Exec_X_0F();
	static void Exec_X_10();
	static void Exec_X_11();
	static void Exec_X_12();
	static void Exec_X_13();
	static void Exec_X_14();
	static void Exec_X_15();
	static void Exec_X_16();
	static void Exec_X_17();
	static void Exec_X_18();
	static void Exec_X_19();
	static void Exec_X_1A();
	static void Exec_X_1B();
	static void Exec_X_1C();
	static void Exec_X_1D();
	static void Exec_X_1E();
	static void Exec_X_1F();
	static void Exec_X_20();
	static void Exec_X_21();
	static void Exec_X_22();
	static void Exec_X_23();
	static void Exec_X_24();
	static void Exec_X_25();
	static void Exec_X_26();
	static void Exec_X_27();
	static void Exec_X_28();
	static void Exec_X_29();
	static void Exec_X_2A();
	static void Exec_X_2B();
	static void Exec_X_2C();
	static void Exec_X_2D();
	static void Exec_X_2E();
	static void Exec_X_2F();
	static void Exec_X_30();
	static void Exec_X_31();
	static void Exec_X_32();
	static void Exec_X_33();
	static void Exec_X_34();
	static void Exec_X_35();
	static void Exec_X_36();
	static void Exec_X_37();
	static void Exec_X_38();
	static void Exec_X_39();
	static void Exec_X_3A();
	static void Exec_X_3B();
	static void Exec_X_3C();
	static void Exec_X_3D();
	static void Exec_X_3E();
	static void Exec_X_3F();
	static void Exec_X_40();
	static void Exec_X_41();
	static void Exec_X_42();
	static void Exec_X_43();
	static void Exec_X_44();
	static void Exec_X_45();
	static void Exec_X_46();
	static void Exec_X_47();
	static void Exec_X_48();
	static void Exec_X_49();
	static void Exec_X_4A();
	static void Exec_X_4B();
	static void Exec_X_4C();
	static void Exec_X_4D();
	static void Exec_X_4E();
	static void Exec_X_4F();
	static void Exec_X_50();
	static void Exec_X_51();
	static void Exec_X_52();
	static void Exec_X_53();
	static void Exec_X_54();
	static void Exec_X_55();
	static void Exec_X_56();
	static void Exec_X_57();
	static void Exec_X_58();
	static void Exec_X_59();
	static void Exec_X_5A();
	static void Exec_X_5B();
	static void Exec_X_5C();
	static void Exec_X_5D();
	static void Exec_X_5E();
	static void Exec_X_5F();
	static void Exec_X_60();
	static void Exec_X_61();
	static void Exec_X_62();
	static void Exec_X_63();
	static void Exec_X_64();
	static void Exec_X_65();
	static void Exec_X_66();
	static void Exec_X_67();
	static void Exec_X_68();
	static void Exec_X_69();
	static void Exec_X_6A();
	static void Exec_X_6B();
	static void Exec_X_6C();
	static void Exec_X_6D();
	static void Exec_X_6E();
	static void Exec_X_6F();
	static void Exec_X_70();
	static void Exec_X_71();
	static void Exec_X_72();
	static void Exec_X_73();
	static void Exec_X_74();
	static void Exec_X_75();
	static void Exec_X_76();
	static void Exec_X_77();
	static void Exec_X_78();
	static void Exec_X_79();
	static void Exec_X_7A();
	static void Exec_X_7B();
	static void Exec_X_7C();
	static void Exec_X_7D();
	static void Exec_X_7E();
	static void Exec_X_7F();
	static void Exec_X_80();
	static void Exec_X_81();
	static void Exec_X_82();
	static void Exec_X_83();
	static void Exec_X_84();
	static void Exec_X_85();
	static void Exec_X_86();
	static void Exec_X_87();
	static void Exec_X_88();
	static void Exec_X_89();
	static void Exec_X_8A();
	static void Exec_X_8B();
	static void Exec_X_8C();
	static void Exec_X_8D();
	static void Exec_X_8E();
	static void Exec_X_8F();
	static void Exec_X_90();
	static void Exec_X_91();
	static void Exec_X_92();
	static void Exec_X_93();
	static void Exec_X_94();
	static void Exec_X_95();
	static void Exec_X_96();
	static void Exec_X_97();
	static void Exec_X_98();
	static void Exec_X_99();
	static void Exec_X_9A();
	static void Exec_X_9B();
	static void Exec_X_9C();
	static void Exec_X_9D();
	static void Exec_X_9E();
	static void Exec_X_9F();
	static void Exec_X_A0();
	static void Exec_X_A1();
	static void Exec_X_A2();
	static void Exec_X_A3();
	static void Exec_X_A4();
	static void Exec_X_A5();
	static void Exec_X_A6();
	static void Exec_X_A7();
	static void Exec_X_A8();
	static void Exec_X_A9();
	static void Exec_X_AA();
	static void Exec_X_AB();
	static void Exec_X_AC();
	static void Exec_X_AD();
	static void Exec_X_AE();
	static void Exec_X_AF();
	static void Exec_X_B0();
	static void Exec_X_B1();
	static void Exec_X_B2();
	static void Exec_X_B3();
	static void Exec_X_B4();
	static void Exec_X_B5();
	static void Exec_X_B6();
	static void Exec_X_B7();
	static void Exec_X_B8();
	static void Exec_X_B9();
	static void Exec_X_BA();
	static void Exec_X_BB();
	static void Exec_X_BC();
	static void Exec_X_BD();
	static void Exec_X_BE();
	static void Exec_X_BF();
	static void Exec_X_C0();
	static void Exec_X_C1();
	static void Exec_X_C2();
	static void Exec_X_C3();
	static void Exec_X_C4();
	static void Exec_X_C5();
	static void Exec_X_C6();
	static void Exec_X_C7();
	static void Exec_X_C8();
	static void Exec_X_C9();
	static void Exec_X_CA();
	static void Exec_X_CB();
	static void Exec_X_CC();
	static void Exec_X_CD();
	static void Exec_X_CE();
	static void Exec_X_CF();
	static void Exec_X_D0();
	static void Exec_X_D1();
	static void Exec_X_D2();
	static void Exec_X_D3();
	static void Exec_X_D4();
	static void Exec_X_D5();
	static void Exec_X_D6();
	static void Exec_X_D7();
	static void Exec_X_D8();
	static void Exec_X_D9();
	static void Exec_X_DA();
	static void Exec_X_DB();
	static void Exec_X_DC();
	static void Exec_X_DD();
	static void Exec_X_DE();
	static void Exec_X_DF();
	static void Exec_X_E0();
	static void Exec_X_E1();
	static void Exec_X_E2();
	static void Exec_X_E3();
	static void Exec_X_E4();
	static void Exec_X_E5();
	static void Exec_X_E6();
	static void Exec_X_E7();
	static void Exec_X_E8();
	static void Exec_X_E9();
	static void Exec_X_EA();
	static void Exec_X_EB();
	static void Exec_X_EC();
	static void Exec_X_ED();
	static void Exec_X_EE();
	static void Exec_X_EF();
	static void Exec_X_F0();
	static void Exec_X_F1();
	static void Exec_X_F2();
	static void Exec_X_F3();
	static void Exec_X_F4();
	static void Exec_X_F5();
	static void Exec_X_F6();
	static void Exec_X_F7();
	static void Exec_X_F8();
	static void Exec_X_F9();
	static void Exec_X_FA();
	static void Exec_X_FB();
	static void Exec_X_FC();
	static void Exec_X_FD();
	static void Exec_X_FE();
	static void Exec_X_FF();
	// Exec_CB_X
	static void Exec_CB_X_00();
	static void Exec_CB_X_01();
	static void Exec_CB_X_02();
	static void Exec_CB_X_03();
	static void Exec_CB_X_04();
	static void Exec_CB_X_05();
	static void Exec_CB_X_06();
	static void Exec_CB_X_07();
	static void Exec_CB_X_08();
	static void Exec_CB_X_09();
	static void Exec_CB_X_0A();
	static void Exec_CB_X_0B();
	static void Exec_CB_X_0C();
	static void Exec_CB_X_0D();
	static void Exec_CB_X_0E();
	static void Exec_CB_X_0F();
	static void Exec_CB_X_10();
	static void Exec_CB_X_11();
	static void Exec_CB_X_12();
	static void Exec_CB_X_13();
	static void Exec_CB_X_14();
	static void Exec_CB_X_15();
	static void Exec_CB_X_16();
	static void Exec_CB_X_17();
	static void Exec_CB_X_18();
	static void Exec_CB_X_19();
	static void Exec_CB_X_1A();
	static void Exec_CB_X_1B();
	static void Exec_CB_X_1C();
	static void Exec_CB_X_1D();
	static void Exec_CB_X_1E();
	static void Exec_CB_X_1F();
	static void Exec_CB_X_20();
	static void Exec_CB_X_21();
	static void Exec_CB_X_22();
	static void Exec_CB_X_23();
	static void Exec_CB_X_24();
	static void Exec_CB_X_25();
	static void Exec_CB_X_26();
	static void Exec_CB_X_27();
	static void Exec_CB_X_28();
	static void Exec_CB_X_29();
	static void Exec_CB_X_2A();
	static void Exec_CB_X_2B();
	static void Exec_CB_X_2C();
	static void Exec_CB_X_2D();
	static void Exec_CB_X_2E();
	static void Exec_CB_X_2F();
	static void Exec_CB_X_30();
	static void Exec_CB_X_31();
	static void Exec_CB_X_32();
	static void Exec_CB_X_33();
	static void Exec_CB_X_34();
	static void Exec_CB_X_35();
	static void Exec_CB_X_36();
	static void Exec_CB_X_37();
	static void Exec_CB_X_38();
	static void Exec_CB_X_39();
	static void Exec_CB_X_3A();
	static void Exec_CB_X_3B();
	static void Exec_CB_X_3C();
	static void Exec_CB_X_3D();
	static void Exec_CB_X_3E();
	static void Exec_CB_X_3F();
	static void Exec_CB_X_40();
	static void Exec_CB_X_41();
	static void Exec_CB_X_42();
	static void Exec_CB_X_43();
	static void Exec_CB_X_44();
	static void Exec_CB_X_45();
	static void Exec_CB_X_46();
	static void Exec_CB_X_47();
	static void Exec_CB_X_48();
	static void Exec_CB_X_49();
	static void Exec_CB_X_4A();
	static void Exec_CB_X_4B();
	static void Exec_CB_X_4C();
	static void Exec_CB_X_4D();
	static void Exec_CB_X_4E();
	static void Exec_CB_X_4F();
	static void Exec_CB_X_50();
	static void Exec_CB_X_51();
	static void Exec_CB_X_52();
	static void Exec_CB_X_53();
	static void Exec_CB_X_54();
	static void Exec_CB_X_55();
	static void Exec_CB_X_56();
	static void Exec_CB_X_57();
	static void Exec_CB_X_58();
	static void Exec_CB_X_59();
	static void Exec_CB_X_5A();
	static void Exec_CB_X_5B();
	static void Exec_CB_X_5C();
	static void Exec_CB_X_5D();
	static void Exec_CB_X_5E();
	static void Exec_CB_X_5F();
	static void Exec_CB_X_60();
	static void Exec_CB_X_61();
	static void Exec_CB_X_62();
	static void Exec_CB_X_63();
	static void Exec_CB_X_64();
	static void Exec_CB_X_65();
	static void Exec_CB_X_66();
	static void Exec_CB_X_67();
	static void Exec_CB_X_68();
	static void Exec_CB_X_69();
	static void Exec_CB_X_6A();
	static void Exec_CB_X_6B();
	static void Exec_CB_X_6C();
	static void Exec_CB_X_6D();
	static void Exec_CB_X_6E();
	static void Exec_CB_X_6F();
	static void Exec_CB_X_70();
	static void Exec_CB_X_71();
	static void Exec_CB_X_72();
	static void Exec_CB_X_73();
	static void Exec_CB_X_74();
	static void Exec_CB_X_75();
	static void Exec_CB_X_76();
	static void Exec_CB_X_77();
	static void Exec_CB_X_78();
	static void Exec_CB_X_79();
	static void Exec_CB_X_7A();
	static void Exec_CB_X_7B();
	static void Exec_CB_X_7C();
	static void Exec_CB_X_7D();
	static void Exec_CB_X_7E();
	static void Exec_CB_X_7F();
	static void Exec_CB_X_80();
	static void Exec_CB_X_81();
	static void Exec_CB_X_82();
	static void Exec_CB_X_83();
	static void Exec_CB_X_84();
	static void Exec_CB_X_85();
	static void Exec_CB_X_86();
	static void Exec_CB_X_87();
	static void Exec_CB_X_88();
	static void Exec_CB_X_89();
	static void Exec_CB_X_8A();
	static void Exec_CB_X_8B();
	static void Exec_CB_X_8C();
	static void Exec_CB_X_8D();
	static void Exec_CB_X_8E();
	static void Exec_CB_X_8F();
	static void Exec_CB_X_90();
	static void Exec_CB_X_91();
	static void Exec_CB_X_92();
	static void Exec_CB_X_93();
	static void Exec_CB_X_94();
	static void Exec_CB_X_95();
	static void Exec_CB_X_96();
	static void Exec_CB_X_97();
	static void Exec_CB_X_98();
	static void Exec_CB_X_99();
	static void Exec_CB_X_9A();
	static void Exec_CB_X_9B();
	static void Exec_CB_X_9C();
	static void Exec_CB_X_9D();
	static void Exec_CB_X_9E();
	static void Exec_CB_X_9F();
	static void Exec_CB_X_A0();
	static void Exec_CB_X_A1();
	static void Exec_CB_X_A2();
	static void Exec_CB_X_A3();
	static void Exec_CB_X_A4();
	static void Exec_CB_X_A5();
	static void Exec_CB_X_A6();
	static void Exec_CB_X_A7();
	static void Exec_CB_X_A8();
	static void Exec_CB_X_A9();
	static void Exec_CB_X_AA();
	static void Exec_CB_X_AB();
	static void Exec_CB_X_AC();
	static void Exec_CB_X_AD();
	static void Exec_CB_X_AE();
	static void Exec_CB_X_AF();
	static void Exec_CB_X_B0();
	static void Exec_CB_X_B1();
	static void Exec_CB_X_B2();
	static void Exec_CB_X_B3();
	static void Exec_CB_X_B4();
	static void Exec_CB_X_B5();
	static void Exec_CB_X_B6();
	static void Exec_CB_X_B7();
	static void Exec_CB_X_B8();
	static void Exec_CB_X_B9();
	static void Exec_CB_X_BA();
	static void Exec_CB_X_BB();
	static void Exec_CB_X_BC();
	static void Exec_CB_X_BD();
	static void Exec_CB_X_BE();
	static void Exec_CB_X_BF();
	static void Exec_CB_X_C0();
	static void Exec_CB_X_C1();
	static void Exec_CB_X_C2();
	static void Exec_CB_X_C3();
	static void Exec_CB_X_C4();
	static void Exec_CB_X_C5();
	static void Exec_CB_X_C6();
	static void Exec_CB_X_C7();
	static void Exec_CB_X_C8();
	static void Exec_CB_X_C9();
	static void Exec_CB_X_CA();
	static void Exec_CB_X_CB();
	static void Exec_CB_X_CC();
	static void Exec_CB_X_CD();
	static void Exec_CB_X_CE();
	static void Exec_CB_X_CF();
	static void Exec_CB_X_D0();
	static void Exec_CB_X_D1();
	static void Exec_CB_X_D2();
	static void Exec_CB_X_D3();
	static void Exec_CB_X_D4();
	static void Exec_CB_X_D5();
	static void Exec_CB_X_D6();
	static void Exec_CB_X_D7();
	static void Exec_CB_X_D8();
	static void Exec_CB_X_D9();
	static void Exec_CB_X_DA();
	static void Exec_CB_X_DB();
	static void Exec_CB_X_DC();
	static void Exec_CB_X_DD();
	static void Exec_CB_X_DE();
	static void Exec_CB_X_DF();
	static void Exec_CB_X_E0();
	static void Exec_CB_X_E1();
	static void Exec_CB_X_E2();
	static void Exec_CB_X_E3();
	static void Exec_CB_X_E4();
	static void Exec_CB_X_E5();
	static void Exec_CB_X_E6();
	static void Exec_CB_X_E7();
	static void Exec_CB_X_E8();
	static void Exec_CB_X_E9();
	static void Exec_CB_X_EA();
	static void Exec_CB_X_EB();
	static void Exec_CB_X_EC();
	static void Exec_CB_X_ED();
	static void Exec_CB_X_EE();
	static void Exec_CB_X_EF();
	static void Exec_CB_X_F0();
	static void Exec_CB_X_F1();
	static void Exec_CB_X_F2();
	static void Exec_CB_X_F3();
	static void Exec_CB_X_F4();
	static void Exec_CB_X_F5();
	static void Exec_CB_X_F6();
	static void Exec_CB_X_F7();
	static void Exec_CB_X_F8();
	static void Exec_CB_X_F9();
	static void Exec_CB_X_FA();
	static void Exec_CB_X_FB();
	static void Exec_CB_X_FC();
	static void Exec_CB_X_FD();
	static void Exec_CB_X_FE();
	static void Exec_CB_X_FF();
	// Exec_ED_X
	static void Exec_ED_X_40();
	static void Exec_ED_X_41();
	static void Exec_ED_X_42();
	static void Exec_ED_X_43();
	static void Exec_ED_X_44_x();
	static void Exec_ED_X_45_x();
	static void Exec_ED_X_46_x();
	static void Exec_ED_X_47();
	static void Exec_ED_X_48();
	static void Exec_ED_X_49();
	static void Exec_ED_X_4A();
	static void Exec_ED_X_4B();
	static void Exec_ED_X_4D_x();
	static void Exec_ED_X_4E_x();
	static void Exec_ED_X_4F();
	static void Exec_ED_X_50();
	static void Exec_ED_X_51();
	static void Exec_ED_X_52();
	static void Exec_ED_X_53();
	static void Exec_ED_X_56_x();
	static void Exec_ED_X_57();
	static void Exec_ED_X_58();
	static void Exec_ED_X_59();
	static void Exec_ED_X_5A();
	static void Exec_ED_X_5B();
	static void Exec_ED_X_5E_x();
	static void Exec_ED_X_5F();
	static void Exec_ED_X_60();
	static void Exec_ED_X_61();
	static void Exec_ED_X_62();
	static void Exec_ED_X_63();
	static void Exec_ED_X_67();
	static void Exec_ED_X_68();
	static void Exec_ED_X_69();
	static void Exec_ED_X_6A();
	static void Exec_ED_X_6B();
	static void Exec_ED_X_6F();
	static void Exec_ED_X_70();
	static void Exec_ED_X_71();
	static void Exec_ED_X_72();
	static void Exec_ED_X_73();
	static void Exec_ED_X_77_x();
	static void Exec_ED_X_78();
	static void Exec_ED_X_79();
	static void Exec_ED_X_7A();
	static void Exec_ED_X_7B();
	static void Exec_ED_X_A0();
	static void Exec_ED_X_A1();
	static void Exec_ED_X_A2();
	static void Exec_ED_X_A3();
	static void Exec_ED_X_A8();
	static void Exec_ED_X_A9();
	static void Exec_ED_X_AA();
	static void Exec_ED_X_AB();
	static void Exec_ED_X_B0();
	static void Exec_ED_X_B1();
	static void Exec_ED_X_B2();
	static void Exec_ED_X_B3();
	static void Exec_ED_X_B8();
	static void Exec_ED_X_B9();
	static void Exec_ED_X_BA();
	static void Exec_ED_X_BB();
	static void Exec_ED_X_default();
	// Exec_DD_X
	static void Exec_DD_X_09();
	static void Exec_DD_X_19();
	static void Exec_DD_X_21();
	static void Exec_DD_X_22();
	static void Exec_DD_X_23();
	static void Exec_DD_X_24();
	static void Exec_DD_X_25();
	static void Exec_DD_X_26();
	static void Exec_DD_X_29();
	static void Exec_DD_X_2A();
	static void Exec_DD_X_2B();
	static void Exec_DD_X_2C();
	static void Exec_DD_X_2D();
	static void Exec_DD_X_2E();
	static void Exec_DD_X_34();
	static void Exec_DD_X_35();
	static void Exec_DD_X_36();
	static void Exec_DD_X_39();
	static void Exec_DD_X_44();
	static void Exec_DD_X_45();
	static void Exec_DD_X_46();
	static void Exec_DD_X_4C();
	static void Exec_DD_X_4D();
	static void Exec_DD_X_4E();
	static void Exec_DD_X_54();
	static void Exec_DD_X_55();
	static void Exec_DD_X_56();
	static void Exec_DD_X_5C();
	static void Exec_DD_X_5D();
	static void Exec_DD_X_5E();
	static void Exec_DD_X_60();
	static void Exec_DD_X_61();
	static void Exec_DD_X_62();
	static void Exec_DD_X_63();
	static void Exec_DD_X_64();
	static void Exec_DD_X_65();
	static void Exec_DD_X_66();
	static void Exec_DD_X_67();
	static void Exec_DD_X_68();
	static void Exec_DD_X_69();
	static void Exec_DD_X_6A();
	static void Exec_DD_X_6B();
	static void Exec_DD_X_6C();
	static void Exec_DD_X_6D();
	static void Exec_DD_X_6E();
	static void Exec_DD_X_6F();
	static void Exec_DD_X_70();
	static void Exec_DD_X_71();
	static void Exec_DD_X_72();
	static void Exec_DD_X_73();
	static void Exec_DD_X_74();
	static void Exec_DD_X_75();
	static void Exec_DD_X_77();
	static void Exec_DD_X_7C();
	static void Exec_DD_X_7D();
	static void Exec_DD_X_7E();
	static void Exec_DD_X_84();
	static void Exec_DD_X_85();
	static void Exec_DD_X_86();
	static void Exec_DD_X_8C();
	static void Exec_DD_X_8D();
	static void Exec_DD_X_8E();
	static void Exec_DD_X_94();
	static void Exec_DD_X_95();
	static void Exec_DD_X_96();
	static void Exec_DD_X_9C();
	static void Exec_DD_X_9D();
	static void Exec_DD_X_9E();
	static void Exec_DD_X_A4();
	static void Exec_DD_X_A5();
	static void Exec_DD_X_A6();
	static void Exec_DD_X_AC();
	static void Exec_DD_X_AD();
	static void Exec_DD_X_AE();
	static void Exec_DD_X_B4();
	static void Exec_DD_X_B5();
	static void Exec_DD_X_B6();
	static void Exec_DD_X_BC();
	static void Exec_DD_X_BD();
	static void Exec_DD_X_BE();
	static void Exec_DD_X_CB();
	static void Exec_DD_X_E1();
	static void Exec_DD_X_E3();
	static void Exec_DD_X_E5();
	static void Exec_DD_X_E9();
	static void Exec_DD_X_F9();
	// Exec_DD_CB_X
	static void Exec_DD_CB_X_00();
	static void Exec_DD_CB_X_01();
	static void Exec_DD_CB_X_02();
	static void Exec_DD_CB_X_03();
	static void Exec_DD_CB_X_04();
	static void Exec_DD_CB_X_05();
	static void Exec_DD_CB_X_06();
	static void Exec_DD_CB_X_07();
	static void Exec_DD_CB_X_08();
	static void Exec_DD_CB_X_09();
	static void Exec_DD_CB_X_0A();
	static void Exec_DD_CB_X_0B();
	static void Exec_DD_CB_X_0C();
	static void Exec_DD_CB_X_0D();
	static void Exec_DD_CB_X_0E();
	static void Exec_DD_CB_X_0F();
	static void Exec_DD_CB_X_10();
	static void Exec_DD_CB_X_11();
	static void Exec_DD_CB_X_12();
	static void Exec_DD_CB_X_13();
	static void Exec_DD_CB_X_14();
	static void Exec_DD_CB_X_15();
	static void Exec_DD_CB_X_16();
	static void Exec_DD_CB_X_17();
	static void Exec_DD_CB_X_18();
	static void Exec_DD_CB_X_19();
	static void Exec_DD_CB_X_1A();
	static void Exec_DD_CB_X_1B();
	static void Exec_DD_CB_X_1C();
	static void Exec_DD_CB_X_1D();
	static void Exec_DD_CB_X_1E();
	static void Exec_DD_CB_X_1F();
	static void Exec_DD_CB_X_20();
	static void Exec_DD_CB_X_21();
	static void Exec_DD_CB_X_22();
	static void Exec_DD_CB_X_23();
	static void Exec_DD_CB_X_24();
	static void Exec_DD_CB_X_25();
	static void Exec_DD_CB_X_26();
	static void Exec_DD_CB_X_27();
	static void Exec_DD_CB_X_28();
	static void Exec_DD_CB_X_29();
	static void Exec_DD_CB_X_2A();
	static void Exec_DD_CB_X_2B();
	static void Exec_DD_CB_X_2C();
	static void Exec_DD_CB_X_2D();
	static void Exec_DD_CB_X_2E();
	static void Exec_DD_CB_X_2F();
	static void Exec_DD_CB_X_30();
	static void Exec_DD_CB_X_31();
	static void Exec_DD_CB_X_32();
	static void Exec_DD_CB_X_33();
	static void Exec_DD_CB_X_34();
	static void Exec_DD_CB_X_35();
	static void Exec_DD_CB_X_36();
	static void Exec_DD_CB_X_37();
	static void Exec_DD_CB_X_38();
	static void Exec_DD_CB_X_39();
	static void Exec_DD_CB_X_3A();
	static void Exec_DD_CB_X_3B();
	static void Exec_DD_CB_X_3C();
	static void Exec_DD_CB_X_3D();
	static void Exec_DD_CB_X_3E();
	static void Exec_DD_CB_X_3F();
	static void Exec_DD_CB_X_46_x();
	static void Exec_DD_CB_X_4E_x();
	static void Exec_DD_CB_X_56_x();
	static void Exec_DD_CB_X_5E_x();
	static void Exec_DD_CB_X_66_x();
	static void Exec_DD_CB_X_6E_x();
	static void Exec_DD_CB_X_76_x();
	static void Exec_DD_CB_X_7E_x();
	static void Exec_DD_CB_X_80();
	static void Exec_DD_CB_X_81();
	static void Exec_DD_CB_X_82();
	static void Exec_DD_CB_X_83();
	static void Exec_DD_CB_X_84();
	static void Exec_DD_CB_X_85();
	static void Exec_DD_CB_X_86();
	static void Exec_DD_CB_X_87();
	static void Exec_DD_CB_X_88();
	static void Exec_DD_CB_X_89();
	static void Exec_DD_CB_X_8A();
	static void Exec_DD_CB_X_8B();
	static void Exec_DD_CB_X_8C();
	static void Exec_DD_CB_X_8D();
	static void Exec_DD_CB_X_8E();
	static void Exec_DD_CB_X_8F();
	static void Exec_DD_CB_X_90();
	static void Exec_DD_CB_X_91();
	static void Exec_DD_CB_X_92();
	static void Exec_DD_CB_X_93();
	static void Exec_DD_CB_X_94();
	static void Exec_DD_CB_X_95();
	static void Exec_DD_CB_X_96();
	static void Exec_DD_CB_X_97();
	static void Exec_DD_CB_X_98();
	static void Exec_DD_CB_X_99();
	static void Exec_DD_CB_X_9A();
	static void Exec_DD_CB_X_9B();
	static void Exec_DD_CB_X_9C();
	static void Exec_DD_CB_X_9D();
	static void Exec_DD_CB_X_9E();
	static void Exec_DD_CB_X_9F();
	static void Exec_DD_CB_X_A0();
	static void Exec_DD_CB_X_A1();
	static void Exec_DD_CB_X_A2();
	static void Exec_DD_CB_X_A3();
	static void Exec_DD_CB_X_A4();
	static void Exec_DD_CB_X_A5();
	static void Exec_DD_CB_X_A6();
	static void Exec_DD_CB_X_A7();
	static void Exec_DD_CB_X_A8();
	static void Exec_DD_CB_X_A9();
	static void Exec_DD_CB_X_AA();
	static void Exec_DD_CB_X_AB();
	static void Exec_DD_CB_X_AC();
	static void Exec_DD_CB_X_AD();
	static void Exec_DD_CB_X_AE();
	static void Exec_DD_CB_X_AF();
	static void Exec_DD_CB_X_B0();
	static void Exec_DD_CB_X_B1();
	static void Exec_DD_CB_X_B2();
	static void Exec_DD_CB_X_B3();
	static void Exec_DD_CB_X_B4();
	static void Exec_DD_CB_X_B5();
	static void Exec_DD_CB_X_B6();
	static void Exec_DD_CB_X_B7();
	static void Exec_DD_CB_X_B8();
	static void Exec_DD_CB_X_B9();
	static void Exec_DD_CB_X_BA();
	static void Exec_DD_CB_X_BB();
	static void Exec_DD_CB_X_BC();
	static void Exec_DD_CB_X_BD();
	static void Exec_DD_CB_X_BE();
	static void Exec_DD_CB_X_BF();
	static void Exec_DD_CB_X_C0();
	static void Exec_DD_CB_X_C1();
	static void Exec_DD_CB_X_C2();
	static void Exec_DD_CB_X_C3();
	static void Exec_DD_CB_X_C4();
	static void Exec_DD_CB_X_C5();
	static void Exec_DD_CB_X_C6();
	static void Exec_DD_CB_X_C7();
	static void Exec_DD_CB_X_C8();
	static void Exec_DD_CB_X_C9();
	static void Exec_DD_CB_X_CA();
	static void Exec_DD_CB_X_CB();
	static void Exec_DD_CB_X_CC();
	static void Exec_DD_CB_X_CD();
	static void Exec_DD_CB_X_CE();
	static void Exec_DD_CB_X_CF();
	static void Exec_DD_CB_X_D0();
	static void Exec_DD_CB_X_D1();
	static void Exec_DD_CB_X_D2();
	static void Exec_DD_CB_X_D3();
	static void Exec_DD_CB_X_D4();
	static void Exec_DD_CB_X_D5();
	static void Exec_DD_CB_X_D6();
	static void Exec_DD_CB_X_D7();
	static void Exec_DD_CB_X_D8();
	static void Exec_DD_CB_X_D9();
	static void Exec_DD_CB_X_DA();
	static void Exec_DD_CB_X_DB();
	static void Exec_DD_CB_X_DC();
	static void Exec_DD_CB_X_DD();
	static void Exec_DD_CB_X_DE();
	static void Exec_DD_CB_X_DF();
	static void Exec_DD_CB_X_E0();
	static void Exec_DD_CB_X_E1();
	static void Exec_DD_CB_X_E2();
	static void Exec_DD_CB_X_E3();
	static void Exec_DD_CB_X_E4();
	static void Exec_DD_CB_X_E5();
	static void Exec_DD_CB_X_E6();
	static void Exec_DD_CB_X_E7();
	static void Exec_DD_CB_X_E8();
	static void Exec_DD_CB_X_E9();
	static void Exec_DD_CB_X_EA();
	static void Exec_DD_CB_X_EB();
	static void Exec_DD_CB_X_EC();
	static void Exec_DD_CB_X_ED();
	static void Exec_DD_CB_X_EE();
	static void Exec_DD_CB_X_EF();
	static void Exec_DD_CB_X_F0();
	static void Exec_DD_CB_X_F1();
	static void Exec_DD_CB_X_F2();
	static void Exec_DD_CB_X_F3();
	static void Exec_DD_CB_X_F4();
	static void Exec_DD_CB_X_F5();
	static void Exec_DD_CB_X_F6();
	static void Exec_DD_CB_X_F7();
	static void Exec_DD_CB_X_F8();
	static void Exec_DD_CB_X_F9();
	static void Exec_DD_CB_X_FA();
	static void Exec_DD_CB_X_FB();
	static void Exec_DD_CB_X_FC();
	static void Exec_DD_CB_X_FD();
	static void Exec_DD_CB_X_FE();
	static void Exec_DD_CB_X_FF();
	// Exec_FD_X
	static void Exec_FD_X_09();
	static void Exec_FD_X_19();
	static void Exec_FD_X_21();
	static void Exec_FD_X_22();
	static void Exec_FD_X_23();
	static void Exec_FD_X_24();
	static void Exec_FD_X_25();
	static void Exec_FD_X_26();
	static void Exec_FD_X_29();
	static void Exec_FD_X_2A();
	static void Exec_FD_X_2B();
	static void Exec_FD_X_2C();
	static void Exec_FD_X_2D();
	static void Exec_FD_X_2E();
	static void Exec_FD_X_34();
	static void Exec_FD_X_35();
	static void Exec_FD_X_36();
	static void Exec_FD_X_39();
	static void Exec_FD_X_44();
	static void Exec_FD_X_45();
	static void Exec_FD_X_46();
	static void Exec_FD_X_4C();
	static void Exec_FD_X_4D();
	static void Exec_FD_X_4E();
	static void Exec_FD_X_54();
	static void Exec_FD_X_55();
	static void Exec_FD_X_56();
	static void Exec_FD_X_5C();
	static void Exec_FD_X_5D();
	static void Exec_FD_X_5E();
	static void Exec_FD_X_60();
	static void Exec_FD_X_61();
	static void Exec_FD_X_62();
	static void Exec_FD_X_63();
	static void Exec_FD_X_64();
	static void Exec_FD_X_65();
	static void Exec_FD_X_66();
	static void Exec_FD_X_67();
	static void Exec_FD_X_68();
	static void Exec_FD_X_69();
	static void Exec_FD_X_6A();
	static void Exec_FD_X_6B();
	static void Exec_FD_X_6C();
	static void Exec_FD_X_6D();
	static void Exec_FD_X_6E();
	static void Exec_FD_X_6F();
	static void Exec_FD_X_70();
	static void Exec_FD_X_71();
	static void Exec_FD_X_72();
	static void Exec_FD_X_73();
	static void Exec_FD_X_74();
	static void Exec_FD_X_75();
	static void Exec_FD_X_77();
	static void Exec_FD_X_7C();
	static void Exec_FD_X_7D();
	static void Exec_FD_X_7E();
	static void Exec_FD_X_84();
	static void Exec_FD_X_85();
	static void Exec_FD_X_86();
	static void Exec_FD_X_8C();
	static void Exec_FD_X_8D();
	static void Exec_FD_X_8E();
	static void Exec_FD_X_94();
	static void Exec_FD_X_95();
	static void Exec_FD_X_96();
	static void Exec_FD_X_9C();
	static void Exec_FD_X_9D();
	static void Exec_FD_X_9E();
	static void Exec_FD_X_A4();
	static void Exec_FD_X_A5();
	static void Exec_FD_X_A6();
	static void Exec_FD_X_AC();
	static void Exec_FD_X_AD();
	static void Exec_FD_X_AE();
	static void Exec_FD_X_B4();
	static void Exec_FD_X_B5();
	static void Exec_FD_X_B6();
	static void Exec_FD_X_BC();
	static void Exec_FD_X_BD();
	static void Exec_FD_X_BE();
	static void Exec_FD_X_CB();
	static void Exec_FD_X_E1();
	static void Exec_FD_X_E3();
	static void Exec_FD_X_E5();
	static void Exec_FD_X_E9();
	static void Exec_FD_X_F9();
	// Exec_FD_CB_X
	static void Exec_FD_CB_X_00();
	static void Exec_FD_CB_X_01();
	static void Exec_FD_CB_X_02();
	static void Exec_FD_CB_X_03();
	static void Exec_FD_CB_X_04();
	static void Exec_FD_CB_X_05();
	static void Exec_FD_CB_X_06();
	static void Exec_FD_CB_X_07();
	static void Exec_FD_CB_X_08();
	static void Exec_FD_CB_X_09();
	static void Exec_FD_CB_X_0A();
	static void Exec_FD_CB_X_0B();
	static void Exec_FD_CB_X_0C();
	static void Exec_FD_CB_X_0D();
	static void Exec_FD_CB_X_0E();
	static void Exec_FD_CB_X_0F();
	static void Exec_FD_CB_X_10();
	static void Exec_FD_CB_X_11();
	static void Exec_FD_CB_X_12();
	static void Exec_FD_CB_X_13();
	static void Exec_FD_CB_X_14();
	static void Exec_FD_CB_X_15();
	static void Exec_FD_CB_X_16();
	static void Exec_FD_CB_X_17();
	static void Exec_FD_CB_X_18();
	static void Exec_FD_CB_X_19();
	static void Exec_FD_CB_X_1A();
	static void Exec_FD_CB_X_1B();
	static void Exec_FD_CB_X_1C();
	static void Exec_FD_CB_X_1D();
	static void Exec_FD_CB_X_1E();
	static void Exec_FD_CB_X_1F();
	static void Exec_FD_CB_X_20();
	static void Exec_FD_CB_X_21();
	static void Exec_FD_CB_X_22();
	static void Exec_FD_CB_X_23();
	static void Exec_FD_CB_X_24();
	static void Exec_FD_CB_X_25();
	static void Exec_FD_CB_X_26();
	static void Exec_FD_CB_X_27();
	static void Exec_FD_CB_X_28();
	static void Exec_FD_CB_X_29();
	static void Exec_FD_CB_X_2A();
	static void Exec_FD_CB_X_2B();
	static void Exec_FD_CB_X_2C();
	static void Exec_FD_CB_X_2D();
	static void Exec_FD_CB_X_2E();
	static void Exec_FD_CB_X_2F();
	static void Exec_FD_CB_X_30();
	static void Exec_FD_CB_X_31();
	static void Exec_FD_CB_X_32();
	static void Exec_FD_CB_X_33();
	static void Exec_FD_CB_X_34();
	static void Exec_FD_CB_X_35();
	static void Exec_FD_CB_X_36();
	static void Exec_FD_CB_X_37();
	static void Exec_FD_CB_X_38();
	static void Exec_FD_CB_X_39();
	static void Exec_FD_CB_X_3A();
	static void Exec_FD_CB_X_3B();
	static void Exec_FD_CB_X_3C();
	static void Exec_FD_CB_X_3D();
	static void Exec_FD_CB_X_3E();
	static void Exec_FD_CB_X_3F();
	static void Exec_FD_CB_X_46_x();
	static void Exec_FD_CB_X_4E_x();
	static void Exec_FD_CB_X_56_x();
	static void Exec_FD_CB_X_5E_x();
	static void Exec_FD_CB_X_66_x();
	static void Exec_FD_CB_X_6E_x();
	static void Exec_FD_CB_X_76_x();
	static void Exec_FD_CB_X_7E_x();
	static void Exec_FD_CB_X_80();
	static void Exec_FD_CB_X_81();
	static void Exec_FD_CB_X_82();
	static void Exec_FD_CB_X_83();
	static void Exec_FD_CB_X_84();
	static void Exec_FD_CB_X_85();
	static void Exec_FD_CB_X_86();
	static void Exec_FD_CB_X_87();
	static void Exec_FD_CB_X_88();
	static void Exec_FD_CB_X_89();
	static void Exec_FD_CB_X_8A();
	static void Exec_FD_CB_X_8B();
	static void Exec_FD_CB_X_8C();
	static void Exec_FD_CB_X_8D();
	static void Exec_FD_CB_X_8E();
	static void Exec_FD_CB_X_8F();
	static void Exec_FD_CB_X_90();
	static void Exec_FD_CB_X_91();
	static void Exec_FD_CB_X_92();
	static void Exec_FD_CB_X_93();
	static void Exec_FD_CB_X_94();
	static void Exec_FD_CB_X_95();
	static void Exec_FD_CB_X_96();
	static void Exec_FD_CB_X_97();
	static void Exec_FD_CB_X_98();
	static void Exec_FD_CB_X_99();
	static void Exec_FD_CB_X_9A();
	static void Exec_FD_CB_X_9B();
	static void Exec_FD_CB_X_9C();
	static void Exec_FD_CB_X_9D();
	static void Exec_FD_CB_X_9E();
	static void Exec_FD_CB_X_9F();
	static void Exec_FD_CB_X_A0();
	static void Exec_FD_CB_X_A1();
	static void Exec_FD_CB_X_A2();
	static void Exec_FD_CB_X_A3();
	static void Exec_FD_CB_X_A4();
	static void Exec_FD_CB_X_A5();
	static void Exec_FD_CB_X_A6();
	static void Exec_FD_CB_X_A7();
	static void Exec_FD_CB_X_A8();
	static void Exec_FD_CB_X_A9();
	static void Exec_FD_CB_X_AA();
	static void Exec_FD_CB_X_AB();
	static void Exec_FD_CB_X_AC();
	static void Exec_FD_CB_X_AD();
	static void Exec_FD_CB_X_AE();
	static void Exec_FD_CB_X_AF();
	static void Exec_FD_CB_X_B0();
	static void Exec_FD_CB_X_B1();
	static void Exec_FD_CB_X_B2();
	static void Exec_FD_CB_X_B3();
	static void Exec_FD_CB_X_B4();
	static void Exec_FD_CB_X_B5();
	static void Exec_FD_CB_X_B6();
	static void Exec_FD_CB_X_B7();
	static void Exec_FD_CB_X_B8();
	static void Exec_FD_CB_X_B9();
	static void Exec_FD_CB_X_BA();
	static void Exec_FD_CB_X_BB();
	static void Exec_FD_CB_X_BC();
	static void Exec_FD_CB_X_BD();
	static void Exec_FD_CB_X_BE();
	static void Exec_FD_CB_X_BF();
	static void Exec_FD_CB_X_C0();
	static void Exec_FD_CB_X_C1();
	static void Exec_FD_CB_X_C2();
	static void Exec_FD_CB_X_C3();
	static void Exec_FD_CB_X_C4();
	static void Exec_FD_CB_X_C5();
	static void Exec_FD_CB_X_C6();
	static void Exec_FD_CB_X_C7();
	static void Exec_FD_CB_X_C8();
	static void Exec_FD_CB_X_C9();
	static void Exec_FD_CB_X_CA();
	static void Exec_FD_CB_X_CB();
	static void Exec_FD_CB_X_CC();
	static void Exec_FD_CB_X_CD();
	static void Exec_FD_CB_X_CE();
	static void Exec_FD_CB_X_CF();
	static void Exec_FD_CB_X_D0();
	static void Exec_FD_CB_X_D1();
	static void Exec_FD_CB_X_D2();
	static void Exec_FD_CB_X_D3();
	static void Exec_FD_CB_X_D4();
	static void Exec_FD_CB_X_D5();
	static void Exec_FD_CB_X_D6();
	static void Exec_FD_CB_X_D7();
	static void Exec_FD_CB_X_D8();
	static void Exec_FD_CB_X_D9();
	static void Exec_FD_CB_X_DA();
	static void Exec_FD_CB_X_DB();
	static void Exec_FD_CB_X_DC();
	static void Exec_FD_CB_X_DD();
	static void Exec_FD_CB_X_DE();
	static void Exec_FD_CB_X_DF();
	static void Exec_FD_CB_X_E0();
	static void Exec_FD_CB_X_E1();
	static void Exec_FD_CB_X_E2();
	static void Exec_FD_CB_X_E3();
	static void Exec_FD_CB_X_E4();
	static void Exec_FD_CB_X_E5();
	static void Exec_FD_CB_X_E6();
	static void Exec_FD_CB_X_E7();
	static void Exec_FD_CB_X_E8();
	static void Exec_FD_CB_X_E9();
	static void Exec_FD_CB_X_EA();
	static void Exec_FD_CB_X_EB();
	static void Exec_FD_CB_X_EC();
	static void Exec_FD_CB_X_ED();
	static void Exec_FD_CB_X_EE();
	static void Exec_FD_CB_X_EF();
	static void Exec_FD_CB_X_F0();
	static void Exec_FD_CB_X_F1();
	static void Exec_FD_CB_X_F2();
	static void Exec_FD_CB_X_F3();
	static void Exec_FD_CB_X_F4();
	static void Exec_FD_CB_X_F5();
	static void Exec_FD_CB_X_F6();
	static void Exec_FD_CB_X_F7();
	static void Exec_FD_CB_X_F8();
	static void Exec_FD_CB_X_F9();
	static void Exec_FD_CB_X_FA();
	static void Exec_FD_CB_X_FB();
	static void Exec_FD_CB_X_FC();
	static void Exec_FD_CB_X_FD();
	static void Exec_FD_CB_X_FE();
	static void Exec_FD_CB_X_FF();

// interrupt
public:
	// occurred interrupt
	static int DoInterrupt(uint8_t btIntVect);
	// occurred NMI
	static int DoNMInterrupt();
};

#define CZ80Executor2	TZ80ExecutorBase2< CZ80 >

////////////////////////////////////////////////////////////
// attribute

#ifdef Z80CFG_TEMPLATE_STATICVAR_NORMAL
#define Z80TEMPLATE_EXPLICIT_SV	Z80TEMPLATE_EXPLICIT_AW
#define CZ80Executor2X			CZ80Executor2
#else // Z80CFG_TEMPLATE_STATICVAR_SPECIAL
#define Z80TEMPLATE_EXPLICIT_SV	template <class TZ>
#define CZ80Executor2X			TZ80ExecutorBase2<TZ>
#endif // Z80CFG_TEMPLATE_STATICVAR

Z80TEMPLATE_EXPLICIT_SV
int CZ80Executor2X::m_nOpCode;
Z80TEMPLATE_EXPLICIT_SV
uint16_t CZ80Executor2X::m_wNN;
Z80TEMPLATE_EXPLICIT_SV
uint8_t CZ80Executor2X::m_btX;
Z80TEMPLATE_EXPLICIT_SV
uint8_t CZ80Executor2X::m_btN;
Z80TEMPLATE_EXPLICIT_SV
uint8_t CZ80Executor2X::m_btD;
Z80TEMPLATE_EXPLICIT_SV
uint8_t CZ80Executor2X::m_btE;

Z80TEMPLATE_EXPLICIT_SV
CZ80Executor2Super::EXECPROC CZ80Executor2X::m_aepExecuteTable[256*7];
//CZ80Executor2Super::EXECPROC *CZ80Executor2X::m_aepExecuteTable;

////////////////////////////////////////////////////////////
// execute procedure

// Exec_X

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_00() {
	M_Exec_NOP();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_01() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_nn(M_RegBC(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_02() {
	M_Exec_LD_Qss_A(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_03() {
	M_Exec_INC_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_04() {
	M_Exec_INC_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_05() {
	M_Exec_DEC_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_06() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegB(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_07() {
	M_Exec_RLCA();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_08() {
	M_Exec_EX_AF_AF2();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_09() {
	M_Exec_ADD_HL_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_0A() {
	M_Exec_LD_A_Qss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_0B() {
	M_Exec_DEC_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_0C() {
	M_Exec_INC_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_0D() {
	M_Exec_DEC_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_0E() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegC(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_0F() {
	M_Exec_RRCA();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_10() {
	M_FetchByte(m_btE);
	M_Exec_DJNZ_e(m_btE);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_11() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_nn(M_RegDE(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_12() {
	M_Exec_LD_Qss_A(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_13() {
	M_Exec_INC_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_14() {
	M_Exec_INC_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_15() {
	M_Exec_DEC_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_16() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegD(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_17() {
	M_Exec_RLA();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_18() {
	M_FetchByte(m_btE);
	M_Exec_JR_e(m_btE);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_19() {
	M_Exec_ADD_HL_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_1A() {
	M_Exec_LD_A_Qss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_1B() {
	M_Exec_DEC_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_1C() {
	M_Exec_INC_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_1D() {
	M_Exec_DEC_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_1E() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegE(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_1F() {
	M_Exec_RRA();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_20() {
	M_FetchByte(m_btE);
	M_Exec_JR_cc_e(M_FlagNZ(), m_btE);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_21() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_nn(M_RegHL(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_22() {
	M_FetchWord(m_wNN);
	M_Exec_LD_Qnn_ss(m_wNN, M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_23() {
	M_Exec_INC_ss(M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_24() {
	M_Exec_INC_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_25() {
	M_Exec_DEC_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_26() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegH(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_27() {
	M_Exec_DAA();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_28() {
	M_FetchByte(m_btE);
	M_Exec_JR_cc_e(M_FlagZ(), m_btE);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_29() {
	M_Exec_ADD_HL_ss(M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_2A() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_Qnn(M_RegHL(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_2B() {
	M_Exec_DEC_ss(M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_2C() {
	M_Exec_INC_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_2D() {
	M_Exec_DEC_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_2E() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegL(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_2F() {
	M_Exec_CPL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_30() {
	M_FetchByte(m_btE);
	M_Exec_JR_cc_e(M_FlagNC(), m_btE);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_31() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_nn(M_RegSP(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_32() {
	M_FetchWord(m_wNN);
	M_Exec_LD_Qnn_A(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_33() {
	M_Exec_INC_ss(M_RegSP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_34() {
	M_Exec_INC_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_35() {
	M_Exec_DEC_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_36() {
	M_FetchByte(m_btN);
	M_Exec_LD_QHL_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_37() {
	M_Exec_SCF();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_38() {
	M_FetchByte(m_btE);
	M_Exec_JR_cc_e(M_FlagC(), m_btE);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_39() {
	M_Exec_ADD_HL_ss(M_RegSP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_3A() {
	M_FetchWord(m_wNN);
	M_Exec_LD_A_Qnn(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_3B() {
	M_Exec_DEC_ss(M_RegSP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_3C() {
	M_Exec_INC_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_3D() {
	M_Exec_DEC_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_3E() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegA(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_3F() {
	M_Exec_CCF();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_40() {
	M_Exec_LD_r_r2(M_RegB(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_41() {
	M_Exec_LD_r_r2(M_RegB(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_42() {
	M_Exec_LD_r_r2(M_RegB(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_43() {
	M_Exec_LD_r_r2(M_RegB(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_44() {
	M_Exec_LD_r_r2(M_RegB(), M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_45() {
	M_Exec_LD_r_r2(M_RegB(), M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_46() {
	M_Exec_LD_r_QHL(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_47() {
	M_Exec_LD_r_r2(M_RegB(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_48() {
	M_Exec_LD_r_r2(M_RegC(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_49() {
	M_Exec_LD_r_r2(M_RegC(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_4A() {
	M_Exec_LD_r_r2(M_RegC(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_4B() {
	M_Exec_LD_r_r2(M_RegC(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_4C() {
	M_Exec_LD_r_r2(M_RegC(), M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_4D() {
	M_Exec_LD_r_r2(M_RegC(), M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_4E() {
	M_Exec_LD_r_QHL(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_4F() {
	M_Exec_LD_r_r2(M_RegC(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_50() {
	M_Exec_LD_r_r2(M_RegD(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_51() {
	M_Exec_LD_r_r2(M_RegD(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_52() {
	M_Exec_LD_r_r2(M_RegD(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_53() {
	M_Exec_LD_r_r2(M_RegD(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_54() {
	M_Exec_LD_r_r2(M_RegD(), M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_55() {
	M_Exec_LD_r_r2(M_RegD(), M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_56() {
	M_Exec_LD_r_QHL(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_57() {
	M_Exec_LD_r_r2(M_RegD(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_58() {
	M_Exec_LD_r_r2(M_RegE(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_59() {
	M_Exec_LD_r_r2(M_RegE(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_5A() {
	M_Exec_LD_r_r2(M_RegE(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_5B() {
	M_Exec_LD_r_r2(M_RegE(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_5C() {
	M_Exec_LD_r_r2(M_RegE(), M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_5D() {
	M_Exec_LD_r_r2(M_RegE(), M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_5E() {
	M_Exec_LD_r_QHL(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_5F() {
	M_Exec_LD_r_r2(M_RegE(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_60() {
	M_Exec_LD_r_r2(M_RegH(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_61() {
	M_Exec_LD_r_r2(M_RegH(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_62() {
	M_Exec_LD_r_r2(M_RegH(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_63() {
	M_Exec_LD_r_r2(M_RegH(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_64() {
	M_Exec_LD_r_r2(M_RegH(), M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_65() {
	M_Exec_LD_r_r2(M_RegH(), M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_66() {
	M_Exec_LD_r_QHL(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_67() {
	M_Exec_LD_r_r2(M_RegH(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_68() {
	M_Exec_LD_r_r2(M_RegL(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_69() {
	M_Exec_LD_r_r2(M_RegL(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_6A() {
	M_Exec_LD_r_r2(M_RegL(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_6B() {
	M_Exec_LD_r_r2(M_RegL(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_6C() {
	M_Exec_LD_r_r2(M_RegL(), M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_6D() {
	M_Exec_LD_r_r2(M_RegL(), M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_6E() {
	M_Exec_LD_r_QHL(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_6F() {
	M_Exec_LD_r_r2(M_RegL(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_70() {
	M_Exec_LD_QHL_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_71() {
	M_Exec_LD_QHL_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_72() {
	M_Exec_LD_QHL_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_73() {
	M_Exec_LD_QHL_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_74() {
	M_Exec_LD_QHL_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_75() {
	M_Exec_LD_QHL_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_76() {
	M_Exec_HALT();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_77() {
	M_Exec_LD_QHL_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_78() {
	M_Exec_LD_r_r2(M_RegA(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_79() {
	M_Exec_LD_r_r2(M_RegA(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_7A() {
	M_Exec_LD_r_r2(M_RegA(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_7B() {
	M_Exec_LD_r_r2(M_RegA(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_7C() {
	M_Exec_LD_r_r2(M_RegA(), M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_7D() {
	M_Exec_LD_r_r2(M_RegA(), M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_7E() {
	M_Exec_LD_r_QHL(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_7F() {
	M_Exec_LD_r_r2(M_RegA(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_80() {
	M_Exec_ADD_A_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_81() {
	M_Exec_ADD_A_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_82() {
	M_Exec_ADD_A_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_83() {
	M_Exec_ADD_A_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_84() {
	M_Exec_ADD_A_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_85() {
	M_Exec_ADD_A_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_86() {
	M_Exec_ADD_A_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_87() {
	M_Exec_ADD_A_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_88() {
	M_Exec_ADC_A_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_89() {
	M_Exec_ADC_A_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_8A() {
	M_Exec_ADC_A_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_8B() {
	M_Exec_ADC_A_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_8C() {
	M_Exec_ADC_A_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_8D() {
	M_Exec_ADC_A_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_8E() {
	M_Exec_ADC_A_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_8F() {
	M_Exec_ADC_A_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_90() {
	M_Exec_SUB_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_91() {
	M_Exec_SUB_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_92() {
	M_Exec_SUB_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_93() {
	M_Exec_SUB_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_94() {
	M_Exec_SUB_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_95() {
	M_Exec_SUB_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_96() {
	M_Exec_SUB_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_97() {
	M_Exec_SUB_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_98() {
	M_Exec_SBC_A_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_99() {
	M_Exec_SBC_A_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_9A() {
	M_Exec_SBC_A_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_9B() {
	M_Exec_SBC_A_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_9C() {
	M_Exec_SBC_A_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_9D() {
	M_Exec_SBC_A_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_9E() {
	M_Exec_SBC_A_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_9F() {
	M_Exec_SBC_A_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A0() {
	M_Exec_AND_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A1() {
	M_Exec_AND_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A2() {
	M_Exec_AND_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A3() {
	M_Exec_AND_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A4() {
	M_Exec_AND_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A5() {
	M_Exec_AND_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A6() {
	M_Exec_AND_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A7() {
	M_Exec_AND_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A8() {
	M_Exec_XOR_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_A9() {
	M_Exec_XOR_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_AA() {
	M_Exec_XOR_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_AB() {
	M_Exec_XOR_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_AC() {
	M_Exec_XOR_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_AD() {
	M_Exec_XOR_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_AE() {
	M_Exec_XOR_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_AF() {
	M_Exec_XOR_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B0() {
	M_Exec_OR_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B1() {
	M_Exec_OR_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B2() {
	M_Exec_OR_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B3() {
	M_Exec_OR_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B4() {
	M_Exec_OR_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B5() {
	M_Exec_OR_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B6() {
	M_Exec_OR_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B7() {
	M_Exec_OR_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B8() {
	M_Exec_CP_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_B9() {
	M_Exec_CP_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_BA() {
	M_Exec_CP_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_BB() {
	M_Exec_CP_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_BC() {
	M_Exec_CP_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_BD() {
	M_Exec_CP_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_BE() {
	M_Exec_CP_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_BF() {
	M_Exec_CP_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C0() {
	M_Exec_RET_cc(M_FlagNZ());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C1() {
	M_Exec_POP_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C2() {
	M_FetchWord(m_wNN);
	M_Exec_JP_cc_nn(M_FlagNZ(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C3() {
	M_FetchWord(m_wNN);
	M_Exec_JP_nn(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C4() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_cc_nn(M_FlagNZ(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C5() {
	M_Exec_PUSH_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C6() {
	M_FetchByte(m_btN);
	M_Exec_ADD_A_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C7() {
	M_Exec_RST_n(0x00);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C8() {
	M_Exec_RET_cc(M_FlagZ());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_C9() {
	M_Exec_RET();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_CA() {
	M_FetchWord(m_wNN);
	M_Exec_JP_cc_nn(M_FlagZ(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_CB() {
	M_FetchByteM1(m_btX);
	m_nOpCode = EXTRA_CB | m_btX;
	M_AddExecClock(CLOCK_CB_X);
	M_IncRegR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_CC() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_cc_nn(M_FlagZ(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_CD() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_nn(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_CE() {
	M_FetchByte(m_btN);
	M_Exec_ADC_A_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_CF() {
	M_Exec_RST_n(0x08);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D0() {
	M_Exec_RET_cc(M_FlagNC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D1() {
	M_Exec_POP_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D2() {
	M_FetchWord(m_wNN);
	M_Exec_JP_cc_nn(M_FlagNC(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D3() {
	M_FetchByte(m_btN);
	//Serial.print("EXEC D3!:");
	//Serial.print(m_btN, HEX);
	//Serial.print("REGA=");
	//Serial.println(M_RegA().m_bt, HEX);
	
	M_Exec_OUT_Qn_A(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D4() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_cc_nn(M_FlagNC(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D5() {
	M_Exec_PUSH_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D6() {
	M_FetchByte(m_btN);
	M_Exec_SUB_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D7() {
	M_Exec_RST_n(0x10);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D8() {
	M_Exec_RET_cc(M_FlagC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_D9() {
	M_Exec_EXX();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_DA() {
	M_FetchWord(m_wNN);
	M_Exec_JP_cc_nn(M_FlagC(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_DB() {
	M_FetchByte(m_btN);
	M_Exec_IN_A_Qn(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_DC() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_cc_nn(M_FlagC(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_DD() {
	M_FetchByteM1(m_btX);
	//Serial.println(m_btX,HEX);
	m_nOpCode = EXTRA_DD | m_btX;
	M_AddExecClock(CLOCK_DD_X);
	M_IncRegR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_DE() {
	M_FetchByte(m_btN);
	M_Exec_SBC_A_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_DF() {
	M_Exec_RST_n(0x18);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E0() {
	M_Exec_RET_cc(M_FlagPO());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E1() {
	M_Exec_POP_ss(M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E2() {
	M_FetchWord(m_wNN);
	M_Exec_JP_cc_nn(M_FlagPO(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E3() {
	M_Exec_EX_QSP_HL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E4() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_cc_nn(M_FlagPO(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E5() {
	M_Exec_PUSH_ss(M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E6() {
	M_FetchByte(m_btN);
	M_Exec_AND_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E7() {
	M_Exec_RST_n(0x20);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E8() {
	M_Exec_RET_cc(M_FlagPE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_E9() {
	M_Exec_JP_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_EA() {
	M_FetchWord(m_wNN);
	M_Exec_JP_cc_nn(M_FlagPE(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_EB() {
	M_Exec_EX_DE_HL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_EC() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_cc_nn(M_FlagPE(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_ED() {
	M_FetchByteM1(m_btX);
	m_nOpCode = EXTRA_ED | m_btX;
	M_AddExecClock(CLOCK_ED_X);
	M_IncRegR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_EE() {
	M_FetchByte(m_btN);
	M_Exec_XOR_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_EF() {
	M_Exec_RST_n(0x28);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F0() {
	M_Exec_RET_cc(M_FlagP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F1() {
	M_Exec_POP_ss(M_RegAF());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F2() {
	M_FetchWord(m_wNN);
	M_Exec_JP_cc_nn(M_FlagP(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F3() {
	M_Exec_DI();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F4() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_cc_nn(M_FlagP(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F5() {
	M_Exec_PUSH_ss(M_RegAF());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F6() {
	M_FetchByte(m_btN);
	M_Exec_OR_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F7() {
	M_Exec_RST_n(0x30);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F8() {
	M_Exec_RET_cc(M_FlagM());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_F9() {
	M_Exec_LD_SP_HL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_FA() {
	M_FetchWord(m_wNN);
	M_Exec_JP_cc_nn(M_FlagM(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_FB() {
	M_Exec_EI();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_FC() {
	M_FetchWord(m_wNN);
	M_Exec_CALL_cc_nn(M_FlagM(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_FD() {
	M_FetchByteM1(m_btX);
	m_nOpCode = EXTRA_FD | m_btX;
	M_AddExecClock(CLOCK_FD_X);
	M_IncRegR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_FE() {
	M_FetchByte(m_btN);
	M_Exec_CP_n(m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_X_FF() {
	M_Exec_RST_n(0x38);
}

// Exec_CB_X

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_00() {
	M_Exec_RLC_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_01() {
	M_Exec_RLC_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_02() {
	M_Exec_RLC_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_03() {
	M_Exec_RLC_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_04() {
	M_Exec_RLC_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_05() {
	M_Exec_RLC_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_06() {
	M_Exec_RLC_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_07() {
	M_Exec_RLC_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_08() {
	M_Exec_RRC_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_09() {
	M_Exec_RRC_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_0A() {
	M_Exec_RRC_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_0B() {
	M_Exec_RRC_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_0C() {
	M_Exec_RRC_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_0D() {
	M_Exec_RRC_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_0E() {
	M_Exec_RRC_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_0F() {
	M_Exec_RRC_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_10() {
	M_Exec_RL_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_11() {
	M_Exec_RL_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_12() {
	M_Exec_RL_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_13() {
	M_Exec_RL_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_14() {
	M_Exec_RL_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_15() {
	M_Exec_RL_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_16() {
	M_Exec_RL_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_17() {
	M_Exec_RL_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_18() {
	M_Exec_RR_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_19() {
	M_Exec_RR_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_1A() {
	M_Exec_RR_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_1B() {
	M_Exec_RR_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_1C() {
	M_Exec_RR_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_1D() {
	M_Exec_RR_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_1E() {
	M_Exec_RR_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_1F() {
	M_Exec_RR_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_20() {
	M_Exec_SLA_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_21() {
	M_Exec_SLA_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_22() {
	M_Exec_SLA_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_23() {
	M_Exec_SLA_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_24() {
	M_Exec_SLA_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_25() {
	M_Exec_SLA_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_26() {
	M_Exec_SLA_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_27() {
	M_Exec_SLA_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_28() {
	M_Exec_SRA_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_29() {
	M_Exec_SRA_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_2A() {
	M_Exec_SRA_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_2B() {
	M_Exec_SRA_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_2C() {
	M_Exec_SRA_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_2D() {
	M_Exec_SRA_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_2E() {
	M_Exec_SRA_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_2F() {
	M_Exec_SRA_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_30() {
	M_Exec_SLL_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_31() {
	M_Exec_SLL_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_32() {
	M_Exec_SLL_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_33() {
	M_Exec_SLL_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_34() {
	M_Exec_SLL_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_35() {
	M_Exec_SLL_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_36() {
	M_Exec_SLL_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_37() {
	M_Exec_SLL_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_38() {
	M_Exec_SRL_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_39() {
	M_Exec_SRL_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_3A() {
	M_Exec_SRL_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_3B() {
	M_Exec_SRL_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_3C() {
	M_Exec_SRL_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_3D() {
	M_Exec_SRL_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_3E() {
	M_Exec_SRL_QHL();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_3F() {
	M_Exec_SRL_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_40() {
	M_Exec_BIT_b_r(0, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_41() {
	M_Exec_BIT_b_r(0, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_42() {
	M_Exec_BIT_b_r(0, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_43() {
	M_Exec_BIT_b_r(0, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_44() {
	M_Exec_BIT_b_r(0, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_45() {
	M_Exec_BIT_b_r(0, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_46() {
	M_Exec_BIT_b_QHL(0);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_47() {
	M_Exec_BIT_b_r(0, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_48() {
	M_Exec_BIT_b_r(1, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_49() {
	M_Exec_BIT_b_r(1, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_4A() {
	M_Exec_BIT_b_r(1, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_4B() {
	M_Exec_BIT_b_r(1, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_4C() {
	M_Exec_BIT_b_r(1, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_4D() {
	M_Exec_BIT_b_r(1, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_4E() {
	M_Exec_BIT_b_QHL(1);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_4F() {
	M_Exec_BIT_b_r(1, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_50() {
	M_Exec_BIT_b_r(2, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_51() {
	M_Exec_BIT_b_r(2, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_52() {
	M_Exec_BIT_b_r(2, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_53() {
	M_Exec_BIT_b_r(2, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_54() {
	M_Exec_BIT_b_r(2, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_55() {
	M_Exec_BIT_b_r(2, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_56() {
	M_Exec_BIT_b_QHL(2);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_57() {
	M_Exec_BIT_b_r(2, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_58() {
	M_Exec_BIT_b_r(3, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_59() {
	M_Exec_BIT_b_r(3, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_5A() {
	M_Exec_BIT_b_r(3, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_5B() {
	M_Exec_BIT_b_r(3, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_5C() {
	M_Exec_BIT_b_r(3, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_5D() {
	M_Exec_BIT_b_r(3, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_5E() {
	M_Exec_BIT_b_QHL(3);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_5F() {
	M_Exec_BIT_b_r(3, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_60() {
	M_Exec_BIT_b_r(4, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_61() {
	M_Exec_BIT_b_r(4, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_62() {
	M_Exec_BIT_b_r(4, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_63() {
	M_Exec_BIT_b_r(4, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_64() {
	M_Exec_BIT_b_r(4, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_65() {
	M_Exec_BIT_b_r(4, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_66() {
	M_Exec_BIT_b_QHL(4);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_67() {
	M_Exec_BIT_b_r(4, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_68() {
	M_Exec_BIT_b_r(5, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_69() {
	M_Exec_BIT_b_r(5, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_6A() {
	M_Exec_BIT_b_r(5, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_6B() {
	M_Exec_BIT_b_r(5, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_6C() {
	M_Exec_BIT_b_r(5, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_6D() {
	M_Exec_BIT_b_r(5, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_6E() {
	M_Exec_BIT_b_QHL(5);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_6F() {
	M_Exec_BIT_b_r(5, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_70() {
	M_Exec_BIT_b_r(6, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_71() {
	M_Exec_BIT_b_r(6, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_72() {
	M_Exec_BIT_b_r(6, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_73() {
	M_Exec_BIT_b_r(6, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_74() {
	M_Exec_BIT_b_r(6, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_75() {
	M_Exec_BIT_b_r(6, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_76() {
	M_Exec_BIT_b_QHL(6);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_77() {
	M_Exec_BIT_b_r(6, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_78() {
	M_Exec_BIT_b_r(7, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_79() {
	M_Exec_BIT_b_r(7, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_7A() {
	M_Exec_BIT_b_r(7, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_7B() {
	M_Exec_BIT_b_r(7, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_7C() {
	M_Exec_BIT_b_r(7, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_7D() {
	M_Exec_BIT_b_r(7, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_7E() {
	M_Exec_BIT_b_QHL(7);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_7F() {
	M_Exec_BIT_b_r(7, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_80() {
	M_Exec_RES_b_r(0, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_81() {
	M_Exec_RES_b_r(0, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_82() {
	M_Exec_RES_b_r(0, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_83() {
	M_Exec_RES_b_r(0, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_84() {
	M_Exec_RES_b_r(0, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_85() {
	M_Exec_RES_b_r(0, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_86() {
	M_Exec_RES_b_QHL(0);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_87() {
	M_Exec_RES_b_r(0, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_88() {
	M_Exec_RES_b_r(1, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_89() {
	M_Exec_RES_b_r(1, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_8A() {
	M_Exec_RES_b_r(1, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_8B() {
	M_Exec_RES_b_r(1, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_8C() {
	M_Exec_RES_b_r(1, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_8D() {
	M_Exec_RES_b_r(1, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_8E() {
	M_Exec_RES_b_QHL(1);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_8F() {
	M_Exec_RES_b_r(1, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_90() {
	M_Exec_RES_b_r(2, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_91() {
	M_Exec_RES_b_r(2, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_92() {
	M_Exec_RES_b_r(2, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_93() {
	M_Exec_RES_b_r(2, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_94() {
	M_Exec_RES_b_r(2, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_95() {
	M_Exec_RES_b_r(2, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_96() {
	M_Exec_RES_b_QHL(2);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_97() {
	M_Exec_RES_b_r(2, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_98() {
	M_Exec_RES_b_r(3, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_99() {
	M_Exec_RES_b_r(3, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_9A() {
	M_Exec_RES_b_r(3, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_9B() {
	M_Exec_RES_b_r(3, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_9C() {
	M_Exec_RES_b_r(3, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_9D() {
	M_Exec_RES_b_r(3, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_9E() {
	M_Exec_RES_b_QHL(3);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_9F() {
	M_Exec_RES_b_r(3, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A0() {
	M_Exec_RES_b_r(4, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A1() {
	M_Exec_RES_b_r(4, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A2() {
	M_Exec_RES_b_r(4, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A3() {
	M_Exec_RES_b_r(4, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A4() {
	M_Exec_RES_b_r(4, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A5() {
	M_Exec_RES_b_r(4, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A6() {
	M_Exec_RES_b_QHL(4);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A7() {
	M_Exec_RES_b_r(4, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A8() {
	M_Exec_RES_b_r(5, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_A9() {
	M_Exec_RES_b_r(5, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_AA() {
	M_Exec_RES_b_r(5, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_AB() {
	M_Exec_RES_b_r(5, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_AC() {
	M_Exec_RES_b_r(5, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_AD() {
	M_Exec_RES_b_r(5, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_AE() {
	M_Exec_RES_b_QHL(5);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_AF() {
	M_Exec_RES_b_r(5, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B0() {
	M_Exec_RES_b_r(6, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B1() {
	M_Exec_RES_b_r(6, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B2() {
	M_Exec_RES_b_r(6, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B3() {
	M_Exec_RES_b_r(6, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B4() {
	M_Exec_RES_b_r(6, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B5() {
	M_Exec_RES_b_r(6, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B6() {
	M_Exec_RES_b_QHL(6);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B7() {
	M_Exec_RES_b_r(6, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B8() {
	M_Exec_RES_b_r(7, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_B9() {
	M_Exec_RES_b_r(7, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_BA() {
	M_Exec_RES_b_r(7, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_BB() {
	M_Exec_RES_b_r(7, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_BC() {
	M_Exec_RES_b_r(7, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_BD() {
	M_Exec_RES_b_r(7, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_BE() {
	M_Exec_RES_b_QHL(7);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_BF() {
	M_Exec_RES_b_r(7, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C0() {
	M_Exec_SET_b_r(0, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C1() {
	M_Exec_SET_b_r(0, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C2() {
	M_Exec_SET_b_r(0, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C3() {
	M_Exec_SET_b_r(0, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C4() {
	M_Exec_SET_b_r(0, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C5() {
	M_Exec_SET_b_r(0, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C6() {
	M_Exec_SET_b_QHL(0);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C7() {
	M_Exec_SET_b_r(0, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C8() {
	M_Exec_SET_b_r(1, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_C9() {
	M_Exec_SET_b_r(1, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_CA() {
	M_Exec_SET_b_r(1, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_CB() {
	M_Exec_SET_b_r(1, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_CC() {
	M_Exec_SET_b_r(1, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_CD() {
	M_Exec_SET_b_r(1, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_CE() {
	M_Exec_SET_b_QHL(1);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_CF() {
	M_Exec_SET_b_r(1, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D0() {
	M_Exec_SET_b_r(2, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D1() {
	M_Exec_SET_b_r(2, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D2() {
	M_Exec_SET_b_r(2, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D3() {
	M_Exec_SET_b_r(2, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D4() {
	M_Exec_SET_b_r(2, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D5() {
	M_Exec_SET_b_r(2, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D6() {
	M_Exec_SET_b_QHL(2);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D7() {
	M_Exec_SET_b_r(2, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D8() {
	M_Exec_SET_b_r(3, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_D9() {
	M_Exec_SET_b_r(3, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_DA() {
	M_Exec_SET_b_r(3, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_DB() {
	M_Exec_SET_b_r(3, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_DC() {
	M_Exec_SET_b_r(3, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_DD() {
	M_Exec_SET_b_r(3, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_DE() {
	M_Exec_SET_b_QHL(3);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_DF() {
	M_Exec_SET_b_r(3, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E0() {
	M_Exec_SET_b_r(4, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E1() {
	M_Exec_SET_b_r(4, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E2() {
	M_Exec_SET_b_r(4, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E3() {
	M_Exec_SET_b_r(4, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E4() {
	M_Exec_SET_b_r(4, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E5() {
	M_Exec_SET_b_r(4, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E6() {
	M_Exec_SET_b_QHL(4);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E7() {
	M_Exec_SET_b_r(4, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E8() {
	M_Exec_SET_b_r(5, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_E9() {
	M_Exec_SET_b_r(5, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_EA() {
	M_Exec_SET_b_r(5, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_EB() {
	M_Exec_SET_b_r(5, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_EC() {
	M_Exec_SET_b_r(5, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_ED() {
	M_Exec_SET_b_r(5, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_EE() {
	M_Exec_SET_b_QHL(5);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_EF() {
	M_Exec_SET_b_r(5, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F0() {
	M_Exec_SET_b_r(6, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F1() {
	M_Exec_SET_b_r(6, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F2() {
	M_Exec_SET_b_r(6, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F3() {
	M_Exec_SET_b_r(6, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F4() {
	M_Exec_SET_b_r(6, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F5() {
	M_Exec_SET_b_r(6, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F6() {
	M_Exec_SET_b_QHL(6);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F7() {
	M_Exec_SET_b_r(6, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F8() {
	M_Exec_SET_b_r(7, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_F9() {
	M_Exec_SET_b_r(7, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_FA() {
	M_Exec_SET_b_r(7, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_FB() {
	M_Exec_SET_b_r(7, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_FC() {
	M_Exec_SET_b_r(7, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_FD() {
	M_Exec_SET_b_r(7, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_FE() {
	M_Exec_SET_b_QHL(7);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_CB_X_FF() {
	M_Exec_SET_b_r(7, M_RegA());
}

// Exec_ED_X

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_40() {
	M_Exec_IN_r_QC(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_41() {
	M_Exec_OUT_QC_r(M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_42() {
	M_Exec_SBC_HL_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_43() {
	M_FetchWord(m_wNN);
	M_Exec_LD_Qnn_ss(m_wNN, M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_44_x() {
// case 44, 4C, 54, 5C, 64, 6C, 74, 7C
	M_Exec_NEG();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_45_x() {
// case 45, 55, 65, 75
	M_Exec_RETN();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_46_x() {
// case 46, 66
	M_Exec_IM0();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_47() {
	M_Exec_LD_I_A();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_48() {
	M_Exec_IN_r_QC(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_49() {
	M_Exec_OUT_QC_r(M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_4A() {
	M_Exec_ADC_HL_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_4B() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_Qnn(M_RegBC(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_4D_x() {
// 4D, 5D, 6D, 7D
	M_Exec_RETI();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_4E_x() {
// case 4E, 6E
	M_Exec_IMx();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_4F() {
	M_Exec_LD_R_A();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_50() {
	M_Exec_IN_r_QC(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_51() {
	M_Exec_OUT_QC_r(M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_52() {
	M_Exec_SBC_HL_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_53() {
	M_FetchWord(m_wNN);
	M_Exec_LD_Qnn_ss(m_wNN, M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_56_x() {
// case 56, 76
	M_Exec_IM1();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_57() {
	M_Exec_LD_A_I();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_58() {
	M_Exec_IN_r_QC(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_59() {
	M_Exec_OUT_QC_r(M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_5A() {
	M_Exec_ADC_HL_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_5B() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_Qnn(M_RegDE(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_5E_x() {
// case 5E, 7E
	M_Exec_IM2();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_5F() {
	M_Exec_LD_A_R();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_60() {
	M_Exec_IN_r_QC(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_61() {
	M_Exec_OUT_QC_r(M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_62() {
	M_Exec_SBC_HL_ss(M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_63() {
	M_FetchWord(m_wNN);
	M_Exec_LD_Qnn_ss(m_wNN, M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_67() {
	M_Exec_RRD();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_68() {
	M_Exec_IN_r_QC(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_69() {
	M_Exec_OUT_QC_r(M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_6A() {
	M_Exec_ADC_HL_ss(M_RegHL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_6B() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_Qnn(M_RegHL(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_6F() {
	M_Exec_RLD();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_70() {
	M_Exec_IN_F_QC();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_71() {
	M_Exec_OUT_QC_0();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_72() {
	M_Exec_SBC_HL_ss(M_RegSP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_73() {
	M_FetchWord(m_wNN);
	M_Exec_LD_Qnn_ss(m_wNN, M_RegSP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_77_x() {
// case 77, 7F
	M_Exec_NOP();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_78() {
	M_Exec_IN_r_QC(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_79() {
	M_Exec_OUT_QC_r(M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_7A() {
	M_Exec_ADC_HL_ss(M_RegSP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_7B() {
	M_FetchWord(m_wNN);
	M_Exec_LD_ss_Qnn(M_RegSP(), m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_A0() {
	M_Exec_LDI();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_A1() {
	M_Exec_CPI();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_A2() {
	M_Exec_INI();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_A3() {
	M_Exec_OUTI();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_A8() {
	M_Exec_LDD();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_A9() {
	M_Exec_CPD();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_AA() {
	M_Exec_IND();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_AB() {
	M_Exec_OUTD();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_B0() {
	M_Exec_LDIR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_B1() {
	M_Exec_CPIR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_B2() {
	M_Exec_INIR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_B3() {
	M_Exec_OTIR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_B8() {
	M_Exec_LDDR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_B9() {
	M_Exec_CPDR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_BA() {
	M_Exec_INDR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_BB() {
	M_Exec_OTDR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_ED_X_default() {
}

// Exec_DD_X

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_09() {
	M_Exec_ADD_IX_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_19() {
	M_Exec_ADD_IX_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_21() {
	M_FetchWord(m_wNN);
	M_Exec_LD_IX_nn(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_22() {
	M_FetchWord(m_wNN);
	M_Exec_LD_Qnn_IX(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_23() {
	M_Exec_INC_IX();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_24() {
	M_Exec_INC_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_25() {
	M_Exec_DEC_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_26() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegIXH(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_29() {
	M_Exec_ADD_IX_ss(M_RegIX());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_2A() {
	M_FetchWord(m_wNN);
	M_Exec_LD_IX_Qnn(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_2B() {
	M_Exec_DEC_IX();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_2C() {
	M_Exec_INC_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_2D() {
	M_Exec_DEC_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_2E() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegIXL(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_34() {
	M_FetchByte(m_btD);
	M_Exec_INC_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_35() {
	M_FetchByte(m_btD);
	M_Exec_DEC_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_36() {
	M_FetchByte(m_btD);
	M_FetchByte(m_btN);
	M_Exec_LD_QIXd_n(m_btD, m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_39() {
	M_Exec_ADD_IX_ss(M_RegSP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_44() {
	M_Exec_LD_r_r2(M_RegB(), M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_45() {
	M_Exec_LD_r_r2(M_RegB(), M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_46() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_4C() {
	M_Exec_LD_r_r2(M_RegC(), M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_4D() {
	M_Exec_LD_r_r2(M_RegC(), M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_4E() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_54() {
	M_Exec_LD_r_r2(M_RegD(), M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_55() {
	M_Exec_LD_r_r2(M_RegD(), M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_56() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_5C() {
	M_Exec_LD_r_r2(M_RegE(), M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_5D() {
	M_Exec_LD_r_r2(M_RegE(), M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_5E() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_60() {
	M_Exec_LD_r_r2(M_RegIXH(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_61() {
	M_Exec_LD_r_r2(M_RegIXH(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_62() {
	M_Exec_LD_r_r2(M_RegIXH(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_63() {
	M_Exec_LD_r_r2(M_RegIXH(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_64() {
	M_Exec_LD_r_r2(M_RegIXH(), M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_65() {
	M_Exec_LD_r_r2(M_RegIXH(), M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_66() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_67() {
	M_Exec_LD_r_r2(M_RegIXH(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_68() {
	M_Exec_LD_r_r2(M_RegIXL(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_69() {
	M_Exec_LD_r_r2(M_RegIXL(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_6A() {
	M_Exec_LD_r_r2(M_RegIXL(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_6B() {
	M_Exec_LD_r_r2(M_RegIXL(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_6C() {
	M_Exec_LD_r_r2(M_RegIXL(), M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_6D() {
	M_Exec_LD_r_r2(M_RegIXL(), M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_6E() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_6F() {
	M_Exec_LD_r_r2(M_RegIXL(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_70() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIXd_r(m_btD, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_71() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIXd_r(m_btD, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_72() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIXd_r(m_btD, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_73() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIXd_r(m_btD, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_74() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIXd_r(m_btD, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_75() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIXd_r(m_btD, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_77() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIXd_r(m_btD, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_7C() {
	M_Exec_LD_r_r2(M_RegA(), M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_7D() {
	M_Exec_LD_r_r2(M_RegA(), M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_7E() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_84() {
	M_Exec_ADD_A_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_85() {
	M_Exec_ADD_A_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_86() {
	M_FetchByte(m_btD);
	M_Exec_ADD_A_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_8C() {
	M_Exec_ADC_A_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_8D() {
	M_Exec_ADC_A_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_8E() {
	M_FetchByte(m_btD);
	M_Exec_ADC_A_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_94() {
	M_Exec_SUB_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_95() {
	M_Exec_SUB_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_96() {
	M_FetchByte(m_btD);
	M_Exec_SUB_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_9C() {
	M_Exec_SBC_A_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_9D() {
	M_Exec_SBC_A_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_9E() {
	M_FetchByte(m_btD);
	M_Exec_SBC_A_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_A4() {
	M_Exec_AND_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_A5() {
	M_Exec_AND_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_A6() {
	M_FetchByte(m_btD);
	M_Exec_AND_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_AC() {
	M_Exec_XOR_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_AD() {
	M_Exec_XOR_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_AE() {
	M_FetchByte(m_btD);
	M_Exec_XOR_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_B4() {
	M_Exec_OR_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_B5() {
	M_Exec_OR_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_B6() {
	M_FetchByte(m_btD);
	M_Exec_OR_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_BC() {
	M_Exec_CP_r(M_RegIXH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_BD() {
	M_Exec_CP_r(M_RegIXL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_BE() {
	M_FetchByte(m_btD);
	M_Exec_CP_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_CB() {
	M_FetchByte(m_btD);
	M_FetchByteM1(m_btX)
	m_nOpCode = EXTRA_DD_CB | m_btX;
	M_AddExecClock(CLOCK_DD_CB_X);
	M_IncRegR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_E1() {
	M_Exec_POP_IX();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_E3() {
	M_Exec_EX_QSP_IX();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_E5() {
	M_Exec_PUSH_IX();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_E9() {
	M_Exec_JP_QIX();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_X_F9() {
	M_Exec_LD_SP_IX();
}

// Exec_DD_CB_X

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_00() {
	M_Exec_RLC_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_01() {
	M_Exec_RLC_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_02() {
	M_Exec_RLC_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_03() {
	M_Exec_RLC_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_04() {
	M_Exec_RLC_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_05() {
	M_Exec_RLC_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_06() {
	M_Exec_RLC_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_07() {
	M_Exec_RLC_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_08() {
	M_Exec_RRC_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_09() {
	M_Exec_RRC_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_0A() {
	M_Exec_RRC_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_0B() {
	M_Exec_RRC_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_0C() {
	M_Exec_RRC_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_0D() {
	M_Exec_RRC_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_0E() {
	M_Exec_RRC_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_0F() {
	M_Exec_RRC_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_10() {
	M_Exec_RL_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_11() {
	M_Exec_RL_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_12() {
	M_Exec_RL_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_13() {
	M_Exec_RL_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_14() {
	M_Exec_RL_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_15() {
	M_Exec_RL_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_16() {
	M_Exec_RL_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_17() {
	M_Exec_RL_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_18() {
	M_Exec_RR_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_19() {
	M_Exec_RR_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_1A() {
	M_Exec_RR_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_1B() {
	M_Exec_RR_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_1C() {
	M_Exec_RR_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_1D() {
	M_Exec_RR_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_1E() {
	M_Exec_RR_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_1F() {
	M_Exec_RR_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_20() {
	M_Exec_SLA_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_21() {
	M_Exec_SLA_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_22() {
	M_Exec_SLA_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_23() {
	M_Exec_SLA_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_24() {
	M_Exec_SLA_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_25() {
	M_Exec_SLA_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_26() {
	M_Exec_SLA_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_27() {
	M_Exec_SLA_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_28() {
	M_Exec_SRA_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_29() {
	M_Exec_SRA_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_2A() {
	M_Exec_SRA_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_2B() {
	M_Exec_SRA_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_2C() {
	M_Exec_SRA_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_2D() {
	M_Exec_SRA_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_2E() {
	M_Exec_SRA_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_2F() {
	M_Exec_SRA_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_30() {
	M_Exec_SLL_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_31() {
	M_Exec_SLL_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_32() {
	M_Exec_SLL_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_33() {
	M_Exec_SLL_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_34() {
	M_Exec_SLL_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_35() {
	M_Exec_SLL_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_36() {
	M_Exec_SLL_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_37() {
	M_Exec_SLL_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_38() {
	M_Exec_SRL_r_QIXd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_39() {
	M_Exec_SRL_r_QIXd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_3A() {
	M_Exec_SRL_r_QIXd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_3B() {
	M_Exec_SRL_r_QIXd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_3C() {
	M_Exec_SRL_r_QIXd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_3D() {
	M_Exec_SRL_r_QIXd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_3E() {
	M_Exec_SRL_QIXd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_3F() {
	M_Exec_SRL_r_QIXd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_46_x() {
// case 40, 41, 42, 43, 44, 45, 46, 47
	M_Exec_BIT_b_QIXd(0, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_4E_x() {
// case 48, 49, 4A, 4B, 4C, 4D, 4E, 4F
	M_Exec_BIT_b_QIXd(1, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_56_x() {
// case 50, 51, 52, 53, 54, 55, 56, 57
	M_Exec_BIT_b_QIXd(2, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_5E_x() {
// case 58, 59, 5A, 5B, 5C, 5D, 5E, 5F
	M_Exec_BIT_b_QIXd(3, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_66_x() {
// case 60, 61, 62, 63, 64, 65, 66, 67
	M_Exec_BIT_b_QIXd(4, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_6E_x() {
// case 68, 69, 6A, 6B, 6C, 6D, 6E, 6F
	M_Exec_BIT_b_QIXd(5, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_76_x() {
// case 70, 71, 72, 73, 74, 75, 76, 77
	M_Exec_BIT_b_QIXd(6, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_7E_x() {
// case 78, 79, 7A, 7B, 7C, 7D, 7E, 7F
	M_Exec_BIT_b_QIXd(7, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_80() {
	M_Exec_RES_b_r_QIXd(0, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_81() {
	M_Exec_RES_b_r_QIXd(0, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_82() {
	M_Exec_RES_b_r_QIXd(0, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_83() {
	M_Exec_RES_b_r_QIXd(0, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_84() {
	M_Exec_RES_b_r_QIXd(0, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_85() {
	M_Exec_RES_b_r_QIXd(0, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_86() {
	M_Exec_RES_b_QIXd(0, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_87() {
	M_Exec_RES_b_r_QIXd(0, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_88() {
	M_Exec_RES_b_r_QIXd(1, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_89() {
	M_Exec_RES_b_r_QIXd(1, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_8A() {
	M_Exec_RES_b_r_QIXd(1, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_8B() {
	M_Exec_RES_b_r_QIXd(1, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_8C() {
	M_Exec_RES_b_r_QIXd(1, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_8D() {
	M_Exec_RES_b_r_QIXd(1, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_8E() {
	M_Exec_RES_b_QIXd(1, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_8F() {
	M_Exec_RES_b_r_QIXd(1, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_90() {
	M_Exec_RES_b_r_QIXd(2, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_91() {
	M_Exec_RES_b_r_QIXd(2, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_92() {
	M_Exec_RES_b_r_QIXd(2, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_93() {
	M_Exec_RES_b_r_QIXd(2, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_94() {
	M_Exec_RES_b_r_QIXd(2, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_95() {
	M_Exec_RES_b_r_QIXd(2, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_96() {
	M_Exec_RES_b_QIXd(2, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_97() {
	M_Exec_RES_b_r_QIXd(2, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_98() {
	M_Exec_RES_b_r_QIXd(3, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_99() {
	M_Exec_RES_b_r_QIXd(3, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_9A() {
	M_Exec_RES_b_r_QIXd(3, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_9B() {
	M_Exec_RES_b_r_QIXd(3, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_9C() {
	M_Exec_RES_b_r_QIXd(3, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_9D() {
	M_Exec_RES_b_r_QIXd(3, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_9E() {
	M_Exec_RES_b_QIXd(3, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_9F() {
	M_Exec_RES_b_r_QIXd(3, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A0() {
	M_Exec_RES_b_r_QIXd(4, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A1() {
	M_Exec_RES_b_r_QIXd(4, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A2() {
	M_Exec_RES_b_r_QIXd(4, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A3() {
	M_Exec_RES_b_r_QIXd(4, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A4() {
	M_Exec_RES_b_r_QIXd(4, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A5() {
	M_Exec_RES_b_r_QIXd(4, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A6() {
	M_Exec_RES_b_QIXd(4, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A7() {
	M_Exec_RES_b_r_QIXd(4, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A8() {
	M_Exec_RES_b_r_QIXd(5, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_A9() {
	M_Exec_RES_b_r_QIXd(5, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_AA() {
	M_Exec_RES_b_r_QIXd(5, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_AB() {
	M_Exec_RES_b_r_QIXd(5, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_AC() {
	M_Exec_RES_b_r_QIXd(5, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_AD() {
	M_Exec_RES_b_r_QIXd(5, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_AE() {
	M_Exec_RES_b_QIXd(5, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_AF() {
	M_Exec_RES_b_r_QIXd(5, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B0() {
	M_Exec_RES_b_r_QIXd(6, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B1() {
	M_Exec_RES_b_r_QIXd(6, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B2() {
	M_Exec_RES_b_r_QIXd(6, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B3() {
	M_Exec_RES_b_r_QIXd(6, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B4() {
	M_Exec_RES_b_r_QIXd(6, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B5() {
	M_Exec_RES_b_r_QIXd(6, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B6() {
	M_Exec_RES_b_QIXd(6, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B7() {
	M_Exec_RES_b_r_QIXd(6, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B8() {
	M_Exec_RES_b_r_QIXd(7, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_B9() {
	M_Exec_RES_b_r_QIXd(7, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_BA() {
	M_Exec_RES_b_r_QIXd(7, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_BB() {
	M_Exec_RES_b_r_QIXd(7, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_BC() {
	M_Exec_RES_b_r_QIXd(7, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_BD() {
	M_Exec_RES_b_r_QIXd(7, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_BE() {
	M_Exec_RES_b_QIXd(7, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_BF() {
	M_Exec_RES_b_r_QIXd(7, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C0() {
	M_Exec_SET_b_r_QIXd(0, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C1() {
	M_Exec_SET_b_r_QIXd(0, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C2() {
	M_Exec_SET_b_r_QIXd(0, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C3() {
	M_Exec_SET_b_r_QIXd(0, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C4() {
	M_Exec_SET_b_r_QIXd(0, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C5() {
	M_Exec_SET_b_r_QIXd(0, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C6() {
	M_Exec_SET_b_QIXd(0, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C7() {
	M_Exec_SET_b_r_QIXd(0, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C8() {
	M_Exec_SET_b_r_QIXd(1, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_C9() {
	M_Exec_SET_b_r_QIXd(1, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_CA() {
	M_Exec_SET_b_r_QIXd(1, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_CB() {
	M_Exec_SET_b_r_QIXd(1, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_CC() {
	M_Exec_SET_b_r_QIXd(1, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_CD() {
	M_Exec_SET_b_r_QIXd(1, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_CE() {
	M_Exec_SET_b_QIXd(1, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_CF() {
	M_Exec_SET_b_r_QIXd(1, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D0() {
	M_Exec_SET_b_r_QIXd(2, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D1() {
	M_Exec_SET_b_r_QIXd(2, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D2() {
	M_Exec_SET_b_r_QIXd(2, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D3() {
	M_Exec_SET_b_r_QIXd(2, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D4() {
	M_Exec_SET_b_r_QIXd(2, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D5() {
	M_Exec_SET_b_r_QIXd(2, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D6() {
	M_Exec_SET_b_QIXd(2, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D7() {
	M_Exec_SET_b_r_QIXd(2, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D8() {
	M_Exec_SET_b_r_QIXd(3, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_D9() {
	M_Exec_SET_b_r_QIXd(3, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_DA() {
	M_Exec_SET_b_r_QIXd(3, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_DB() {
	M_Exec_SET_b_r_QIXd(3, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_DC() {
	M_Exec_SET_b_r_QIXd(3, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_DD() {
	M_Exec_SET_b_r_QIXd(3, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_DE() {
	M_Exec_SET_b_QIXd(3, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_DF() {
	M_Exec_SET_b_r_QIXd(3, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E0() {
	M_Exec_SET_b_r_QIXd(4, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E1() {
	M_Exec_SET_b_r_QIXd(4, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E2() {
	M_Exec_SET_b_r_QIXd(4, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E3() {
	M_Exec_SET_b_r_QIXd(4, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E4() {
	M_Exec_SET_b_r_QIXd(4, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E5() {
	M_Exec_SET_b_r_QIXd(4, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E6() {
	M_Exec_SET_b_QIXd(4, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E7() {
	M_Exec_SET_b_r_QIXd(4, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E8() {
	M_Exec_SET_b_r_QIXd(5, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_E9() {
	M_Exec_SET_b_r_QIXd(5, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_EA() {
	M_Exec_SET_b_r_QIXd(5, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_EB() {
	M_Exec_SET_b_r_QIXd(5, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_EC() {
	M_Exec_SET_b_r_QIXd(5, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_ED() {
	M_Exec_SET_b_r_QIXd(5, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_EE() {
	M_Exec_SET_b_QIXd(5, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_EF() {
	M_Exec_SET_b_r_QIXd(5, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F0() {
	M_Exec_SET_b_r_QIXd(6, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F1() {
	M_Exec_SET_b_r_QIXd(6, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F2() {
	M_Exec_SET_b_r_QIXd(6, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F3() {
	M_Exec_SET_b_r_QIXd(6, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F4() {
	M_Exec_SET_b_r_QIXd(6, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F5() {
	M_Exec_SET_b_r_QIXd(6, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F6() {
	M_Exec_SET_b_QIXd(6, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F7() {
	M_Exec_SET_b_r_QIXd(6, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F8() {
	M_Exec_SET_b_r_QIXd(7, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_F9() {
	M_Exec_SET_b_r_QIXd(7, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_FA() {
	M_Exec_SET_b_r_QIXd(7, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_FB() {
	M_Exec_SET_b_r_QIXd(7, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_FC() {
	M_Exec_SET_b_r_QIXd(7, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_FD() {
	M_Exec_SET_b_r_QIXd(7, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_FE() {
	M_Exec_SET_b_QIXd(7, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_DD_CB_X_FF() {
	M_Exec_SET_b_r_QIXd(7, M_RegA(), m_btD);
}

// Exec_FD_X

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_09() {
	M_Exec_ADD_IY_ss(M_RegBC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_19() {
	M_Exec_ADD_IY_ss(M_RegDE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_21() {
	M_FetchWord(m_wNN);
	M_Exec_LD_IY_nn(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_22() {
	M_FetchWord(m_wNN);
	M_Exec_LD_Qnn_IY(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_23() {
	M_Exec_INC_IY();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_24() {
	M_Exec_INC_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_25() {
	M_Exec_DEC_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_26() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegIYH(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_29() {
	M_Exec_ADD_IY_ss(M_RegIY());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_2A() {
	M_FetchWord(m_wNN);
	M_Exec_LD_IY_Qnn(m_wNN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_2B() {
	M_Exec_DEC_IY();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_2C() {
	M_Exec_INC_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_2D() {
	M_Exec_DEC_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_2E() {
	M_FetchByte(m_btN);
	M_Exec_LD_r_n(M_RegIYL(), m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_34() {
	M_FetchByte(m_btD);
	M_Exec_INC_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_35() {
	M_FetchByte(m_btD);
	M_Exec_DEC_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_36() {
	M_FetchByte(m_btD);
	M_FetchByte(m_btN);
	M_Exec_LD_QIYd_n(m_btD, m_btN);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_39() {
	M_Exec_ADD_IY_ss(M_RegSP());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_44() {
	M_Exec_LD_r_r2(M_RegB(), M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_45() {
	M_Exec_LD_r_r2(M_RegB(), M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_46() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_4C() {
	M_Exec_LD_r_r2(M_RegC(), M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_4D() {
	M_Exec_LD_r_r2(M_RegC(), M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_4E() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_54() {
	M_Exec_LD_r_r2(M_RegD(), M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_55() {
	M_Exec_LD_r_r2(M_RegD(), M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_56() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_5C() {
	M_Exec_LD_r_r2(M_RegE(), M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_5D() {
	M_Exec_LD_r_r2(M_RegE(), M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_5E() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_60() {
	M_Exec_LD_r_r2(M_RegIYH(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_61() {
	M_Exec_LD_r_r2(M_RegIYH(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_62() {
	M_Exec_LD_r_r2(M_RegIYH(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_63() {
	M_Exec_LD_r_r2(M_RegIYH(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_64() {
	M_Exec_LD_r_r2(M_RegIYH(), M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_65() {
	M_Exec_LD_r_r2(M_RegIYH(), M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_66() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_67() {
	M_Exec_LD_r_r2(M_RegIYH(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_68() {
	M_Exec_LD_r_r2(M_RegIYL(), M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_69() {
	M_Exec_LD_r_r2(M_RegIYL(), M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_6A() {
	M_Exec_LD_r_r2(M_RegIYL(), M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_6B() {
	M_Exec_LD_r_r2(M_RegIYL(), M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_6C() {
	M_Exec_LD_r_r2(M_RegIYL(), M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_6D() {
	M_Exec_LD_r_r2(M_RegIYL(), M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_6E() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_6F() {
	M_Exec_LD_r_r2(M_RegIYL(), M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_70() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIYd_r(m_btD, M_RegB());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_71() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIYd_r(m_btD, M_RegC());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_72() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIYd_r(m_btD, M_RegD());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_73() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIYd_r(m_btD, M_RegE());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_74() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIYd_r(m_btD, M_RegH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_75() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIYd_r(m_btD, M_RegL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_77() {
	M_FetchByte(m_btD);
	M_Exec_LD_QIYd_r(m_btD, M_RegA());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_7C() {
	M_Exec_LD_r_r2(M_RegA(), M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_7D() {
	M_Exec_LD_r_r2(M_RegA(), M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_7E() {
	M_FetchByte(m_btD);
	M_Exec_LD_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_84() {
	M_Exec_ADD_A_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_85() {
	M_Exec_ADD_A_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_86() {
	M_FetchByte(m_btD);
	M_Exec_ADD_A_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_8C() {
	M_Exec_ADC_A_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_8D() {
	M_Exec_ADC_A_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_8E() {
	M_FetchByte(m_btD);
	M_Exec_ADC_A_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_94() {
	M_Exec_SUB_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_95() {
	M_Exec_SUB_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_96() {
	M_FetchByte(m_btD);
	M_Exec_SUB_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_9C() {
	M_Exec_SBC_A_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_9D() {
	M_Exec_SBC_A_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_9E() {
	M_FetchByte(m_btD);
	M_Exec_SBC_A_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_A4() {
	M_Exec_AND_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_A5() {
	M_Exec_AND_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_A6() {
	M_FetchByte(m_btD);
	M_Exec_AND_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_AC() {
	M_Exec_XOR_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_AD() {
	M_Exec_XOR_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_AE() {
	M_FetchByte(m_btD);
	M_Exec_XOR_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_B4() {
	M_Exec_OR_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_B5() {
	M_Exec_OR_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_B6() {
	M_FetchByte(m_btD);
	M_Exec_OR_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_BC() {
	M_Exec_CP_r(M_RegIYH());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_BD() {
	M_Exec_CP_r(M_RegIYL());
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_BE() {
	M_FetchByte(m_btD);
	M_Exec_CP_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_CB() {
	M_FetchByte(m_btD);
	M_FetchByteM1(m_btX);
	m_nOpCode = EXTRA_FD_CB | m_btX;
	M_AddExecClock(CLOCK_FD_CB_X);
	M_IncRegR();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_E1() {
	M_Exec_POP_IY();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_E3() {
	M_Exec_EX_QSP_IY();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_E5() {
	M_Exec_PUSH_IY();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_E9() {
	M_Exec_JP_QIY();
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_X_F9() {
	M_Exec_LD_SP_IY();
}

// Exec_FD_CB_X

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_00() {
	M_Exec_RLC_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_01() {
	M_Exec_RLC_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_02() {
	M_Exec_RLC_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_03() {
	M_Exec_RLC_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_04() {
	M_Exec_RLC_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_05() {
	M_Exec_RLC_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_06() {
	M_Exec_RLC_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_07() {
	M_Exec_RLC_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_08() {
	M_Exec_RRC_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_09() {
	M_Exec_RRC_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_0A() {
	M_Exec_RRC_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_0B() {
	M_Exec_RRC_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_0C() {
	M_Exec_RRC_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_0D() {
	M_Exec_RRC_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_0E() {
	M_Exec_RRC_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_0F() {
	M_Exec_RRC_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_10() {
	M_Exec_RL_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_11() {
	M_Exec_RL_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_12() {
	M_Exec_RL_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_13() {
	M_Exec_RL_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_14() {
	M_Exec_RL_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_15() {
	M_Exec_RL_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_16() {
	M_Exec_RL_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_17() {
	M_Exec_RL_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_18() {
	M_Exec_RR_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_19() {
	M_Exec_RR_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_1A() {
	M_Exec_RR_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_1B() {
	M_Exec_RR_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_1C() {
	M_Exec_RR_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_1D() {
	M_Exec_RR_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_1E() {
	M_Exec_RR_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_1F() {
	M_Exec_RR_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_20() {
	M_Exec_SLA_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_21() {
	M_Exec_SLA_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_22() {
	M_Exec_SLA_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_23() {
	M_Exec_SLA_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_24() {
	M_Exec_SLA_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_25() {
	M_Exec_SLA_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_26() {
	M_Exec_SLA_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_27() {
	M_Exec_SLA_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_28() {
	M_Exec_SRA_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_29() {
	M_Exec_SRA_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_2A() {
	M_Exec_SRA_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_2B() {
	M_Exec_SRA_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_2C() {
	M_Exec_SRA_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_2D() {
	M_Exec_SRA_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_2E() {
	M_Exec_SRA_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_2F() {
	M_Exec_SRA_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_30() {
	M_Exec_SLL_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_31() {
	M_Exec_SLL_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_32() {
	M_Exec_SLL_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_33() {
	M_Exec_SLL_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_34() {
	M_Exec_SLL_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_35() {
	M_Exec_SLL_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_36() {
	M_Exec_SLL_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_37() {
	M_Exec_SLL_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_38() {
	M_Exec_SRL_r_QIYd(M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_39() {
	M_Exec_SRL_r_QIYd(M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_3A() {
	M_Exec_SRL_r_QIYd(M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_3B() {
	M_Exec_SRL_r_QIYd(M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_3C() {
	M_Exec_SRL_r_QIYd(M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_3D() {
	M_Exec_SRL_r_QIYd(M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_3E() {
	M_Exec_SRL_QIYd(m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_3F() {
	M_Exec_SRL_r_QIYd(M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_46_x() {
// case 40, 41, 42, 43, 44, 45, 46, 47
	M_Exec_BIT_b_QIYd(0, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_4E_x() {
// case 48, 49, 4A, 4B, 4C, 4D, 4E, 4F
	M_Exec_BIT_b_QIYd(1, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_56_x() {
// case 50, 51, 52, 53, 54, 55, 56, 57
	M_Exec_BIT_b_QIYd(2, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_5E_x() {
// case 58, 59, 5A, 5B, 5C, 5D, 5E, 5F
	M_Exec_BIT_b_QIYd(3, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_66_x() {
// case 60, 61, 62, 63, 64, 65, 66, 67
	M_Exec_BIT_b_QIYd(4, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_6E_x() {
// case 68, 69, 6A, 6B, 6C, 6D, 6E, 6F
	M_Exec_BIT_b_QIYd(5, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_76_x() {
// case 70, 71, 72, 73, 74, 75, 76, 77
	M_Exec_BIT_b_QIYd(6, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_7E_x() {
// case 78, 79, 7A, 7B, 7C, 7D, 7E, 7F
	M_Exec_BIT_b_QIYd(7, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_80() {
	M_Exec_RES_b_r_QIYd(0, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_81() {
	M_Exec_RES_b_r_QIYd(0, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_82() {
	M_Exec_RES_b_r_QIYd(0, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_83() {
	M_Exec_RES_b_r_QIYd(0, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_84() {
	M_Exec_RES_b_r_QIYd(0, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_85() {
	M_Exec_RES_b_r_QIYd(0, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_86() {
	M_Exec_RES_b_QIYd(0, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_87() {
	M_Exec_RES_b_r_QIYd(0, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_88() {
	M_Exec_RES_b_r_QIYd(1, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_89() {
	M_Exec_RES_b_r_QIYd(1, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_8A() {
	M_Exec_RES_b_r_QIYd(1, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_8B() {
	M_Exec_RES_b_r_QIYd(1, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_8C() {
	M_Exec_RES_b_r_QIYd(1, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_8D() {
	M_Exec_RES_b_r_QIYd(1, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_8E() {
	M_Exec_RES_b_QIYd(1, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_8F() {
	M_Exec_RES_b_r_QIYd(1, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_90() {
	M_Exec_RES_b_r_QIYd(2, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_91() {
	M_Exec_RES_b_r_QIYd(2, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_92() {
	M_Exec_RES_b_r_QIYd(2, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_93() {
	M_Exec_RES_b_r_QIYd(2, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_94() {
	M_Exec_RES_b_r_QIYd(2, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_95() {
	M_Exec_RES_b_r_QIYd(2, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_96() {
	M_Exec_RES_b_QIYd(2, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_97() {
	M_Exec_RES_b_r_QIYd(2, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_98() {
	M_Exec_RES_b_r_QIYd(3, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_99() {
	M_Exec_RES_b_r_QIYd(3, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_9A() {
	M_Exec_RES_b_r_QIYd(3, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_9B() {
	M_Exec_RES_b_r_QIYd(3, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_9C() {
	M_Exec_RES_b_r_QIYd(3, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_9D() {
	M_Exec_RES_b_r_QIYd(3, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_9E() {
	M_Exec_RES_b_QIYd(3, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_9F() {
	M_Exec_RES_b_r_QIYd(3, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A0() {
	M_Exec_RES_b_r_QIYd(4, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A1() {
	M_Exec_RES_b_r_QIYd(4, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A2() {
	M_Exec_RES_b_r_QIYd(4, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A3() {
	M_Exec_RES_b_r_QIYd(4, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A4() {
	M_Exec_RES_b_r_QIYd(4, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A5() {
	M_Exec_RES_b_r_QIYd(4, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A6() {
	M_Exec_RES_b_QIYd(4, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A7() {
	M_Exec_RES_b_r_QIYd(4, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A8() {
	M_Exec_RES_b_r_QIYd(5, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_A9() {
	M_Exec_RES_b_r_QIYd(5, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_AA() {
	M_Exec_RES_b_r_QIYd(5, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_AB() {
	M_Exec_RES_b_r_QIYd(5, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_AC() {
	M_Exec_RES_b_r_QIYd(5, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_AD() {
	M_Exec_RES_b_r_QIYd(5, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_AE() {
	M_Exec_RES_b_QIYd(5, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_AF() {
	M_Exec_RES_b_r_QIYd(5, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B0() {
	M_Exec_RES_b_r_QIYd(6, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B1() {
	M_Exec_RES_b_r_QIYd(6, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B2() {
	M_Exec_RES_b_r_QIYd(6, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B3() {
	M_Exec_RES_b_r_QIYd(6, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B4() {
	M_Exec_RES_b_r_QIYd(6, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B5() {
	M_Exec_RES_b_r_QIYd(6, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B6() {
	M_Exec_RES_b_QIYd(6, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B7() {
	M_Exec_RES_b_r_QIYd(6, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B8() {
	M_Exec_RES_b_r_QIYd(7, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_B9() {
	M_Exec_RES_b_r_QIYd(7, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_BA() {
	M_Exec_RES_b_r_QIYd(7, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_BB() {
	M_Exec_RES_b_r_QIYd(7, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_BC() {
	M_Exec_RES_b_r_QIYd(7, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_BD() {
	M_Exec_RES_b_r_QIYd(7, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_BE() {
	M_Exec_RES_b_QIYd(7, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_BF() {
	M_Exec_RES_b_r_QIYd(7, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C0() {
	M_Exec_SET_b_r_QIYd(0, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C1() {
	M_Exec_SET_b_r_QIYd(0, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C2() {
	M_Exec_SET_b_r_QIYd(0, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C3() {
	M_Exec_SET_b_r_QIYd(0, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C4() {
	M_Exec_SET_b_r_QIYd(0, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C5() {
	M_Exec_SET_b_r_QIYd(0, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C6() {
	M_Exec_SET_b_QIYd(0, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C7() {
	M_Exec_SET_b_r_QIYd(0, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C8() {
	M_Exec_SET_b_r_QIYd(1, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_C9() {
	M_Exec_SET_b_r_QIYd(1, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_CA() {
	M_Exec_SET_b_r_QIYd(1, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_CB() {
	M_Exec_SET_b_r_QIYd(1, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_CC() {
	M_Exec_SET_b_r_QIYd(1, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_CD() {
	M_Exec_SET_b_r_QIYd(1, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_CE() {
	M_Exec_SET_b_QIYd(1, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_CF() {
	M_Exec_SET_b_r_QIYd(1, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D0() {
	M_Exec_SET_b_r_QIYd(2, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D1() {
	M_Exec_SET_b_r_QIYd(2, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D2() {
	M_Exec_SET_b_r_QIYd(2, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D3() {
	M_Exec_SET_b_r_QIYd(2, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D4() {
	M_Exec_SET_b_r_QIYd(2, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D5() {
	M_Exec_SET_b_r_QIYd(2, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D6() {
	M_Exec_SET_b_QIYd(2, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D7() {
	M_Exec_SET_b_r_QIYd(2, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D8() {
	M_Exec_SET_b_r_QIYd(3, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_D9() {
	M_Exec_SET_b_r_QIYd(3, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_DA() {
	M_Exec_SET_b_r_QIYd(3, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_DB() {
	M_Exec_SET_b_r_QIYd(3, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_DC() {
	M_Exec_SET_b_r_QIYd(3, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_DD() {
	M_Exec_SET_b_r_QIYd(3, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_DE() {
	M_Exec_SET_b_QIYd(3, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_DF() {
	M_Exec_SET_b_r_QIYd(3, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E0() {
	M_Exec_SET_b_r_QIYd(4, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E1() {
	M_Exec_SET_b_r_QIYd(4, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E2() {
	M_Exec_SET_b_r_QIYd(4, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E3() {
	M_Exec_SET_b_r_QIYd(4, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E4() {
	M_Exec_SET_b_r_QIYd(4, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E5() {
	M_Exec_SET_b_r_QIYd(4, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E6() {
	M_Exec_SET_b_QIYd(4, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E7() {
	M_Exec_SET_b_r_QIYd(4, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E8() {
	M_Exec_SET_b_r_QIYd(5, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_E9() {
	M_Exec_SET_b_r_QIYd(5, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_EA() {
	M_Exec_SET_b_r_QIYd(5, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_EB() {
	M_Exec_SET_b_r_QIYd(5, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_EC() {
	M_Exec_SET_b_r_QIYd(5, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_ED() {
	M_Exec_SET_b_r_QIYd(5, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_EE() {
	M_Exec_SET_b_QIYd(5, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_EF() {
	M_Exec_SET_b_r_QIYd(5, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F0() {
	M_Exec_SET_b_r_QIYd(6, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F1() {
	M_Exec_SET_b_r_QIYd(6, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F2() {
	M_Exec_SET_b_r_QIYd(6, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F3() {
	M_Exec_SET_b_r_QIYd(6, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F4() {
	M_Exec_SET_b_r_QIYd(6, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F5() {
	M_Exec_SET_b_r_QIYd(6, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F6() {
	M_Exec_SET_b_QIYd(6, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F7() {
	M_Exec_SET_b_r_QIYd(6, M_RegA(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F8() {
	M_Exec_SET_b_r_QIYd(7, M_RegB(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_F9() {
	M_Exec_SET_b_r_QIYd(7, M_RegC(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_FA() {
	M_Exec_SET_b_r_QIYd(7, M_RegD(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_FB() {
	M_Exec_SET_b_r_QIYd(7, M_RegE(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_FC() {
	M_Exec_SET_b_r_QIYd(7, M_RegH(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_FD() {
	M_Exec_SET_b_r_QIYd(7, M_RegL(), m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_FE() {
	M_Exec_SET_b_QIYd(7, m_btD);
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Exec_FD_CB_X_FF() {
	M_Exec_SET_b_r_QIYd(7, M_RegA(), m_btD);
}

////////////////////////////////////////////////////////////
// interrupt

// occurred interrupt

Z80TEMPLATE_EXPLICIT_AW
int CZ80Executor2::DoInterrupt(uint8_t btIntVect) {
	M_SetEnableInterrupt(false);
	M_SetEnableInterrupt2(false);
	M_SetEnableInterruptReserve(false);
	if (M_IsHalting()) {
		M_SetHalting(false);
		M_RegPC().m_w++;
	}
	int nExecClockOrg = M_GetExecClock();
	M_SetExecClock(0);
	switch (M_GetInterruptMode()) {
	case 2:
		{ // dummy block
			M_PushReg(M_RegPC());
			uint16_t wTmp = uint16_t((M_GetRegI() << 8) | btIntVect);
			M_RegPC().m_w = M_ReadMemoryW(wTmp);
			M_AddExecClock(CLOCK_INTERRUPT2);
		}
		break;
	case 1:
		M_PushReg(M_RegPC());
		M_RegPC().m_w = 0x38;
		M_AddExecClock(CLOCK_INTERRUPT1);
		break;
	default:
		// Interruption vector that receives it be only [RST n] and NOP].
		if (btIntVect != 0x00) {
			M_PushReg(M_RegPC());
			M_RegPC().m_w = uint16_t(btIntVect-0xC7);
		}
		M_AddExecClock(CLOCK_INTERRUPT0);
		break;
	}
	int nExecClock = M_GetExecClock();
	M_SetExecClock(nExecClockOrg);
	return nExecClock;
}

// occurred NMI

Z80TEMPLATE_EXPLICIT_AW
int CZ80Executor2::DoNMInterrupt() {
	M_SetEnableInterrupt2(M_IsEnableInterrupt());
	M_SetEnableInterrupt(false);
	M_SetEnableInterruptReserve(false);
	if (M_IsHalting()) {
		M_SetHalting(false);
		M_RegPC().m_w++;
	}
	int nExecClockOrg = M_GetExecClock();
	M_SetExecClock(0);
	M_PushReg(M_RegPC());
	M_RegPC().m_w = 0x0066;
	M_AddExecClock(CLOCK_NMINTERRUPT);
	int nExecClock = M_GetExecClock();
	M_SetExecClock(nExecClockOrg);
	return nExecClock;
}

////////////////////////////////////////////////////////////
// initialize

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Initialize_X() {
	// Exec_X
	m_aepExecuteTable[0x0000] = Exec_X_00;
	m_aepExecuteTable[0x0001] = Exec_X_01;
	m_aepExecuteTable[0x0002] = Exec_X_02;
	m_aepExecuteTable[0x0003] = Exec_X_03;
	m_aepExecuteTable[0x0004] = Exec_X_04;
	m_aepExecuteTable[0x0005] = Exec_X_05;
	m_aepExecuteTable[0x0006] = Exec_X_06;
	m_aepExecuteTable[0x0007] = Exec_X_07;
	m_aepExecuteTable[0x0008] = Exec_X_08;
	m_aepExecuteTable[0x0009] = Exec_X_09;
	m_aepExecuteTable[0x000A] = Exec_X_0A;
	m_aepExecuteTable[0x000B] = Exec_X_0B;
	m_aepExecuteTable[0x000C] = Exec_X_0C;
	m_aepExecuteTable[0x000D] = Exec_X_0D;
	m_aepExecuteTable[0x000E] = Exec_X_0E;
	m_aepExecuteTable[0x000F] = Exec_X_0F;
	m_aepExecuteTable[0x0010] = Exec_X_10;
	m_aepExecuteTable[0x0011] = Exec_X_11;
	m_aepExecuteTable[0x0012] = Exec_X_12;
	m_aepExecuteTable[0x0013] = Exec_X_13;
	m_aepExecuteTable[0x0014] = Exec_X_14;
	m_aepExecuteTable[0x0015] = Exec_X_15;
	m_aepExecuteTable[0x0016] = Exec_X_16;
	m_aepExecuteTable[0x0017] = Exec_X_17;
	m_aepExecuteTable[0x0018] = Exec_X_18;
	m_aepExecuteTable[0x0019] = Exec_X_19;
	m_aepExecuteTable[0x001A] = Exec_X_1A;
	m_aepExecuteTable[0x001B] = Exec_X_1B;
	m_aepExecuteTable[0x001C] = Exec_X_1C;
	m_aepExecuteTable[0x001D] = Exec_X_1D;
	m_aepExecuteTable[0x001E] = Exec_X_1E;
	m_aepExecuteTable[0x001F] = Exec_X_1F;
	m_aepExecuteTable[0x0020] = Exec_X_20;
	m_aepExecuteTable[0x0021] = Exec_X_21;
	m_aepExecuteTable[0x0022] = Exec_X_22;
	m_aepExecuteTable[0x0023] = Exec_X_23;
	m_aepExecuteTable[0x0024] = Exec_X_24;
	m_aepExecuteTable[0x0025] = Exec_X_25;
	m_aepExecuteTable[0x0026] = Exec_X_26;
	m_aepExecuteTable[0x0027] = Exec_X_27;
	m_aepExecuteTable[0x0028] = Exec_X_28;
	m_aepExecuteTable[0x0029] = Exec_X_29;
	m_aepExecuteTable[0x002A] = Exec_X_2A;
	m_aepExecuteTable[0x002B] = Exec_X_2B;
	m_aepExecuteTable[0x002C] = Exec_X_2C;
	m_aepExecuteTable[0x002D] = Exec_X_2D;
	m_aepExecuteTable[0x002E] = Exec_X_2E;
	m_aepExecuteTable[0x002F] = Exec_X_2F;
	m_aepExecuteTable[0x0030] = Exec_X_30;
	m_aepExecuteTable[0x0031] = Exec_X_31;
	m_aepExecuteTable[0x0032] = Exec_X_32;
	m_aepExecuteTable[0x0033] = Exec_X_33;
	m_aepExecuteTable[0x0034] = Exec_X_34;
	m_aepExecuteTable[0x0035] = Exec_X_35;
	m_aepExecuteTable[0x0036] = Exec_X_36;
	m_aepExecuteTable[0x0037] = Exec_X_37;
	m_aepExecuteTable[0x0038] = Exec_X_38;
	m_aepExecuteTable[0x0039] = Exec_X_39;
	m_aepExecuteTable[0x003A] = Exec_X_3A;
	m_aepExecuteTable[0x003B] = Exec_X_3B;
	m_aepExecuteTable[0x003C] = Exec_X_3C;
	m_aepExecuteTable[0x003D] = Exec_X_3D;
	m_aepExecuteTable[0x003E] = Exec_X_3E;
	m_aepExecuteTable[0x003F] = Exec_X_3F;
	m_aepExecuteTable[0x0040] = Exec_X_40;
	m_aepExecuteTable[0x0041] = Exec_X_41;
	m_aepExecuteTable[0x0042] = Exec_X_42;
	m_aepExecuteTable[0x0043] = Exec_X_43;
	m_aepExecuteTable[0x0044] = Exec_X_44;
	m_aepExecuteTable[0x0045] = Exec_X_45;
	m_aepExecuteTable[0x0046] = Exec_X_46;
	m_aepExecuteTable[0x0047] = Exec_X_47;
	m_aepExecuteTable[0x0048] = Exec_X_48;
	m_aepExecuteTable[0x0049] = Exec_X_49;
	m_aepExecuteTable[0x004A] = Exec_X_4A;
	m_aepExecuteTable[0x004B] = Exec_X_4B;
	m_aepExecuteTable[0x004C] = Exec_X_4C;
	m_aepExecuteTable[0x004D] = Exec_X_4D;
	m_aepExecuteTable[0x004E] = Exec_X_4E;
	m_aepExecuteTable[0x004F] = Exec_X_4F;
	m_aepExecuteTable[0x0050] = Exec_X_50;
	m_aepExecuteTable[0x0051] = Exec_X_51;
	m_aepExecuteTable[0x0052] = Exec_X_52;
	m_aepExecuteTable[0x0053] = Exec_X_53;
	m_aepExecuteTable[0x0054] = Exec_X_54;
	m_aepExecuteTable[0x0055] = Exec_X_55;
	m_aepExecuteTable[0x0056] = Exec_X_56;
	m_aepExecuteTable[0x0057] = Exec_X_57;
	m_aepExecuteTable[0x0058] = Exec_X_58;
	m_aepExecuteTable[0x0059] = Exec_X_59;
	m_aepExecuteTable[0x005A] = Exec_X_5A;
	m_aepExecuteTable[0x005B] = Exec_X_5B;
	m_aepExecuteTable[0x005C] = Exec_X_5C;
	m_aepExecuteTable[0x005D] = Exec_X_5D;
	m_aepExecuteTable[0x005E] = Exec_X_5E;
	m_aepExecuteTable[0x005F] = Exec_X_5F;
	m_aepExecuteTable[0x0060] = Exec_X_60;
	m_aepExecuteTable[0x0061] = Exec_X_61;
	m_aepExecuteTable[0x0062] = Exec_X_62;
	m_aepExecuteTable[0x0063] = Exec_X_63;
	m_aepExecuteTable[0x0064] = Exec_X_64;
	m_aepExecuteTable[0x0065] = Exec_X_65;
	m_aepExecuteTable[0x0066] = Exec_X_66;
	m_aepExecuteTable[0x0067] = Exec_X_67;
	m_aepExecuteTable[0x0068] = Exec_X_68;
	m_aepExecuteTable[0x0069] = Exec_X_69;
	m_aepExecuteTable[0x006A] = Exec_X_6A;
	m_aepExecuteTable[0x006B] = Exec_X_6B;
	m_aepExecuteTable[0x006C] = Exec_X_6C;
	m_aepExecuteTable[0x006D] = Exec_X_6D;
	m_aepExecuteTable[0x006E] = Exec_X_6E;
	m_aepExecuteTable[0x006F] = Exec_X_6F;
	m_aepExecuteTable[0x0070] = Exec_X_70;
	m_aepExecuteTable[0x0071] = Exec_X_71;
	m_aepExecuteTable[0x0072] = Exec_X_72;
	m_aepExecuteTable[0x0073] = Exec_X_73;
	m_aepExecuteTable[0x0074] = Exec_X_74;
	m_aepExecuteTable[0x0075] = Exec_X_75;
	m_aepExecuteTable[0x0076] = Exec_X_76;
	m_aepExecuteTable[0x0077] = Exec_X_77;
	m_aepExecuteTable[0x0078] = Exec_X_78;
	m_aepExecuteTable[0x0079] = Exec_X_79;
	m_aepExecuteTable[0x007A] = Exec_X_7A;
	m_aepExecuteTable[0x007B] = Exec_X_7B;
	m_aepExecuteTable[0x007C] = Exec_X_7C;
	m_aepExecuteTable[0x007D] = Exec_X_7D;
	m_aepExecuteTable[0x007E] = Exec_X_7E;
	m_aepExecuteTable[0x007F] = Exec_X_7F;
	m_aepExecuteTable[0x0080] = Exec_X_80;
	m_aepExecuteTable[0x0081] = Exec_X_81;
	m_aepExecuteTable[0x0082] = Exec_X_82;
	m_aepExecuteTable[0x0083] = Exec_X_83;
	m_aepExecuteTable[0x0084] = Exec_X_84;
	m_aepExecuteTable[0x0085] = Exec_X_85;
	m_aepExecuteTable[0x0086] = Exec_X_86;
	m_aepExecuteTable[0x0087] = Exec_X_87;
	m_aepExecuteTable[0x0088] = Exec_X_88;
	m_aepExecuteTable[0x0089] = Exec_X_89;
	m_aepExecuteTable[0x008A] = Exec_X_8A;
	m_aepExecuteTable[0x008B] = Exec_X_8B;
	m_aepExecuteTable[0x008C] = Exec_X_8C;
	m_aepExecuteTable[0x008D] = Exec_X_8D;
	m_aepExecuteTable[0x008E] = Exec_X_8E;
	m_aepExecuteTable[0x008F] = Exec_X_8F;
	m_aepExecuteTable[0x0090] = Exec_X_90;
	m_aepExecuteTable[0x0091] = Exec_X_91;
	m_aepExecuteTable[0x0092] = Exec_X_92;
	m_aepExecuteTable[0x0093] = Exec_X_93;
	m_aepExecuteTable[0x0094] = Exec_X_94;
	m_aepExecuteTable[0x0095] = Exec_X_95;
	m_aepExecuteTable[0x0096] = Exec_X_96;
	m_aepExecuteTable[0x0097] = Exec_X_97;
	m_aepExecuteTable[0x0098] = Exec_X_98;
	m_aepExecuteTable[0x0099] = Exec_X_99;
	m_aepExecuteTable[0x009A] = Exec_X_9A;
	m_aepExecuteTable[0x009B] = Exec_X_9B;
	m_aepExecuteTable[0x009C] = Exec_X_9C;
	m_aepExecuteTable[0x009D] = Exec_X_9D;
	m_aepExecuteTable[0x009E] = Exec_X_9E;
	m_aepExecuteTable[0x009F] = Exec_X_9F;
	m_aepExecuteTable[0x00A0] = Exec_X_A0;
	m_aepExecuteTable[0x00A1] = Exec_X_A1;
	m_aepExecuteTable[0x00A2] = Exec_X_A2;
	m_aepExecuteTable[0x00A3] = Exec_X_A3;
	m_aepExecuteTable[0x00A4] = Exec_X_A4;
	m_aepExecuteTable[0x00A5] = Exec_X_A5;
	m_aepExecuteTable[0x00A6] = Exec_X_A6;
	m_aepExecuteTable[0x00A7] = Exec_X_A7;
	m_aepExecuteTable[0x00A8] = Exec_X_A8;
	m_aepExecuteTable[0x00A9] = Exec_X_A9;
	m_aepExecuteTable[0x00AA] = Exec_X_AA;
	m_aepExecuteTable[0x00AB] = Exec_X_AB;
	m_aepExecuteTable[0x00AC] = Exec_X_AC;
	m_aepExecuteTable[0x00AD] = Exec_X_AD;
	m_aepExecuteTable[0x00AE] = Exec_X_AE;
	m_aepExecuteTable[0x00AF] = Exec_X_AF;
	m_aepExecuteTable[0x00B0] = Exec_X_B0;
	m_aepExecuteTable[0x00B1] = Exec_X_B1;
	m_aepExecuteTable[0x00B2] = Exec_X_B2;
	m_aepExecuteTable[0x00B3] = Exec_X_B3;
	m_aepExecuteTable[0x00B4] = Exec_X_B4;
	m_aepExecuteTable[0x00B5] = Exec_X_B5;
	m_aepExecuteTable[0x00B6] = Exec_X_B6;
	m_aepExecuteTable[0x00B7] = Exec_X_B7;
	m_aepExecuteTable[0x00B8] = Exec_X_B8;
	m_aepExecuteTable[0x00B9] = Exec_X_B9;
	m_aepExecuteTable[0x00BA] = Exec_X_BA;
	m_aepExecuteTable[0x00BB] = Exec_X_BB;
	m_aepExecuteTable[0x00BC] = Exec_X_BC;
	m_aepExecuteTable[0x00BD] = Exec_X_BD;
	m_aepExecuteTable[0x00BE] = Exec_X_BE;
	m_aepExecuteTable[0x00BF] = Exec_X_BF;
	m_aepExecuteTable[0x00C0] = Exec_X_C0;
	m_aepExecuteTable[0x00C1] = Exec_X_C1;
	m_aepExecuteTable[0x00C2] = Exec_X_C2;
	m_aepExecuteTable[0x00C3] = Exec_X_C3;
	m_aepExecuteTable[0x00C4] = Exec_X_C4;
	m_aepExecuteTable[0x00C5] = Exec_X_C5;
	m_aepExecuteTable[0x00C6] = Exec_X_C6;
	m_aepExecuteTable[0x00C7] = Exec_X_C7;
	m_aepExecuteTable[0x00C8] = Exec_X_C8;
	m_aepExecuteTable[0x00C9] = Exec_X_C9;
	m_aepExecuteTable[0x00CA] = Exec_X_CA;
	m_aepExecuteTable[0x00CB] = Exec_X_CB;
	m_aepExecuteTable[0x00CC] = Exec_X_CC;
	m_aepExecuteTable[0x00CD] = Exec_X_CD;
	m_aepExecuteTable[0x00CE] = Exec_X_CE;
	m_aepExecuteTable[0x00CF] = Exec_X_CF;
	m_aepExecuteTable[0x00D0] = Exec_X_D0;
	m_aepExecuteTable[0x00D1] = Exec_X_D1;
	m_aepExecuteTable[0x00D2] = Exec_X_D2;
	m_aepExecuteTable[0x00D3] = Exec_X_D3;
	m_aepExecuteTable[0x00D4] = Exec_X_D4;
	m_aepExecuteTable[0x00D5] = Exec_X_D5;
	m_aepExecuteTable[0x00D6] = Exec_X_D6;
	m_aepExecuteTable[0x00D7] = Exec_X_D7;
	m_aepExecuteTable[0x00D8] = Exec_X_D8;
	m_aepExecuteTable[0x00D9] = Exec_X_D9;
	m_aepExecuteTable[0x00DA] = Exec_X_DA;
	m_aepExecuteTable[0x00DB] = Exec_X_DB;
	m_aepExecuteTable[0x00DC] = Exec_X_DC;
	m_aepExecuteTable[0x00DD] = Exec_X_DD;
	m_aepExecuteTable[0x00DE] = Exec_X_DE;
	m_aepExecuteTable[0x00DF] = Exec_X_DF;
	m_aepExecuteTable[0x00E0] = Exec_X_E0;
	m_aepExecuteTable[0x00E1] = Exec_X_E1;
	m_aepExecuteTable[0x00E2] = Exec_X_E2;
	m_aepExecuteTable[0x00E3] = Exec_X_E3;
	m_aepExecuteTable[0x00E4] = Exec_X_E4;
	m_aepExecuteTable[0x00E5] = Exec_X_E5;
	m_aepExecuteTable[0x00E6] = Exec_X_E6;
	m_aepExecuteTable[0x00E7] = Exec_X_E7;
	m_aepExecuteTable[0x00E8] = Exec_X_E8;
	m_aepExecuteTable[0x00E9] = Exec_X_E9;
	m_aepExecuteTable[0x00EA] = Exec_X_EA;
	m_aepExecuteTable[0x00EB] = Exec_X_EB;
	m_aepExecuteTable[0x00EC] = Exec_X_EC;
	m_aepExecuteTable[0x00ED] = Exec_X_ED;
	m_aepExecuteTable[0x00EE] = Exec_X_EE;
	m_aepExecuteTable[0x00EF] = Exec_X_EF;
	m_aepExecuteTable[0x00F0] = Exec_X_F0;
	m_aepExecuteTable[0x00F1] = Exec_X_F1;
	m_aepExecuteTable[0x00F2] = Exec_X_F2;
	m_aepExecuteTable[0x00F3] = Exec_X_F3;
	m_aepExecuteTable[0x00F4] = Exec_X_F4;
	m_aepExecuteTable[0x00F5] = Exec_X_F5;
	m_aepExecuteTable[0x00F6] = Exec_X_F6;
	m_aepExecuteTable[0x00F7] = Exec_X_F7;
	m_aepExecuteTable[0x00F8] = Exec_X_F8;
	m_aepExecuteTable[0x00F9] = Exec_X_F9;
	m_aepExecuteTable[0x00FA] = Exec_X_FA;
	m_aepExecuteTable[0x00FB] = Exec_X_FB;
	m_aepExecuteTable[0x00FC] = Exec_X_FC;
	m_aepExecuteTable[0x00FD] = Exec_X_FD;
	m_aepExecuteTable[0x00FE] = Exec_X_FE;
	m_aepExecuteTable[0x00FF] = Exec_X_FF;
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Initialize_CB_X() {
	// Exec_CB_X
	m_aepExecuteTable[0x0100] = Exec_CB_X_00;
	m_aepExecuteTable[0x0101] = Exec_CB_X_01;
	m_aepExecuteTable[0x0102] = Exec_CB_X_02;
	m_aepExecuteTable[0x0103] = Exec_CB_X_03;
	m_aepExecuteTable[0x0104] = Exec_CB_X_04;
	m_aepExecuteTable[0x0105] = Exec_CB_X_05;
	m_aepExecuteTable[0x0106] = Exec_CB_X_06;
	m_aepExecuteTable[0x0107] = Exec_CB_X_07;
	m_aepExecuteTable[0x0108] = Exec_CB_X_08;
	m_aepExecuteTable[0x0109] = Exec_CB_X_09;
	m_aepExecuteTable[0x010A] = Exec_CB_X_0A;
	m_aepExecuteTable[0x010B] = Exec_CB_X_0B;
	m_aepExecuteTable[0x010C] = Exec_CB_X_0C;
	m_aepExecuteTable[0x010D] = Exec_CB_X_0D;
	m_aepExecuteTable[0x010E] = Exec_CB_X_0E;
	m_aepExecuteTable[0x010F] = Exec_CB_X_0F;
	m_aepExecuteTable[0x0110] = Exec_CB_X_10;
	m_aepExecuteTable[0x0111] = Exec_CB_X_11;
	m_aepExecuteTable[0x0112] = Exec_CB_X_12;
	m_aepExecuteTable[0x0113] = Exec_CB_X_13;
	m_aepExecuteTable[0x0114] = Exec_CB_X_14;
	m_aepExecuteTable[0x0115] = Exec_CB_X_15;
	m_aepExecuteTable[0x0116] = Exec_CB_X_16;
	m_aepExecuteTable[0x0117] = Exec_CB_X_17;
	m_aepExecuteTable[0x0118] = Exec_CB_X_18;
	m_aepExecuteTable[0x0119] = Exec_CB_X_19;
	m_aepExecuteTable[0x011A] = Exec_CB_X_1A;
	m_aepExecuteTable[0x011B] = Exec_CB_X_1B;
	m_aepExecuteTable[0x011C] = Exec_CB_X_1C;
	m_aepExecuteTable[0x011D] = Exec_CB_X_1D;
	m_aepExecuteTable[0x011E] = Exec_CB_X_1E;
	m_aepExecuteTable[0x011F] = Exec_CB_X_1F;
	m_aepExecuteTable[0x0120] = Exec_CB_X_20;
	m_aepExecuteTable[0x0121] = Exec_CB_X_21;
	m_aepExecuteTable[0x0122] = Exec_CB_X_22;
	m_aepExecuteTable[0x0123] = Exec_CB_X_23;
	m_aepExecuteTable[0x0124] = Exec_CB_X_24;
	m_aepExecuteTable[0x0125] = Exec_CB_X_25;
	m_aepExecuteTable[0x0126] = Exec_CB_X_26;
	m_aepExecuteTable[0x0127] = Exec_CB_X_27;
	m_aepExecuteTable[0x0128] = Exec_CB_X_28;
	m_aepExecuteTable[0x0129] = Exec_CB_X_29;
	m_aepExecuteTable[0x012A] = Exec_CB_X_2A;
	m_aepExecuteTable[0x012B] = Exec_CB_X_2B;
	m_aepExecuteTable[0x012C] = Exec_CB_X_2C;
	m_aepExecuteTable[0x012D] = Exec_CB_X_2D;
	m_aepExecuteTable[0x012E] = Exec_CB_X_2E;
	m_aepExecuteTable[0x012F] = Exec_CB_X_2F;
	m_aepExecuteTable[0x0130] = Exec_CB_X_30;
	m_aepExecuteTable[0x0131] = Exec_CB_X_31;
	m_aepExecuteTable[0x0132] = Exec_CB_X_32;
	m_aepExecuteTable[0x0133] = Exec_CB_X_33;
	m_aepExecuteTable[0x0134] = Exec_CB_X_34;
	m_aepExecuteTable[0x0135] = Exec_CB_X_35;
	m_aepExecuteTable[0x0136] = Exec_CB_X_36;
	m_aepExecuteTable[0x0137] = Exec_CB_X_37;
	m_aepExecuteTable[0x0138] = Exec_CB_X_38;
	m_aepExecuteTable[0x0139] = Exec_CB_X_39;
	m_aepExecuteTable[0x013A] = Exec_CB_X_3A;
	m_aepExecuteTable[0x013B] = Exec_CB_X_3B;
	m_aepExecuteTable[0x013C] = Exec_CB_X_3C;
	m_aepExecuteTable[0x013D] = Exec_CB_X_3D;
	m_aepExecuteTable[0x013E] = Exec_CB_X_3E;
	m_aepExecuteTable[0x013F] = Exec_CB_X_3F;
	m_aepExecuteTable[0x0140] = Exec_CB_X_40;
	m_aepExecuteTable[0x0141] = Exec_CB_X_41;
	m_aepExecuteTable[0x0142] = Exec_CB_X_42;
	m_aepExecuteTable[0x0143] = Exec_CB_X_43;
	m_aepExecuteTable[0x0144] = Exec_CB_X_44;
	m_aepExecuteTable[0x0145] = Exec_CB_X_45;
	m_aepExecuteTable[0x0146] = Exec_CB_X_46;
	m_aepExecuteTable[0x0147] = Exec_CB_X_47;
	m_aepExecuteTable[0x0148] = Exec_CB_X_48;
	m_aepExecuteTable[0x0149] = Exec_CB_X_49;
	m_aepExecuteTable[0x014A] = Exec_CB_X_4A;
	m_aepExecuteTable[0x014B] = Exec_CB_X_4B;
	m_aepExecuteTable[0x014C] = Exec_CB_X_4C;
	m_aepExecuteTable[0x014D] = Exec_CB_X_4D;
	m_aepExecuteTable[0x014E] = Exec_CB_X_4E;
	m_aepExecuteTable[0x014F] = Exec_CB_X_4F;
	m_aepExecuteTable[0x0150] = Exec_CB_X_50;
	m_aepExecuteTable[0x0151] = Exec_CB_X_51;
	m_aepExecuteTable[0x0152] = Exec_CB_X_52;
	m_aepExecuteTable[0x0153] = Exec_CB_X_53;
	m_aepExecuteTable[0x0154] = Exec_CB_X_54;
	m_aepExecuteTable[0x0155] = Exec_CB_X_55;
	m_aepExecuteTable[0x0156] = Exec_CB_X_56;
	m_aepExecuteTable[0x0157] = Exec_CB_X_57;
	m_aepExecuteTable[0x0158] = Exec_CB_X_58;
	m_aepExecuteTable[0x0159] = Exec_CB_X_59;
	m_aepExecuteTable[0x015A] = Exec_CB_X_5A;
	m_aepExecuteTable[0x015B] = Exec_CB_X_5B;
	m_aepExecuteTable[0x015C] = Exec_CB_X_5C;
	m_aepExecuteTable[0x015D] = Exec_CB_X_5D;
	m_aepExecuteTable[0x015E] = Exec_CB_X_5E;
	m_aepExecuteTable[0x015F] = Exec_CB_X_5F;
	m_aepExecuteTable[0x0160] = Exec_CB_X_60;
	m_aepExecuteTable[0x0161] = Exec_CB_X_61;
	m_aepExecuteTable[0x0162] = Exec_CB_X_62;
	m_aepExecuteTable[0x0163] = Exec_CB_X_63;
	m_aepExecuteTable[0x0164] = Exec_CB_X_64;
	m_aepExecuteTable[0x0165] = Exec_CB_X_65;
	m_aepExecuteTable[0x0166] = Exec_CB_X_66;
	m_aepExecuteTable[0x0167] = Exec_CB_X_67;
	m_aepExecuteTable[0x0168] = Exec_CB_X_68;
	m_aepExecuteTable[0x0169] = Exec_CB_X_69;
	m_aepExecuteTable[0x016A] = Exec_CB_X_6A;
	m_aepExecuteTable[0x016B] = Exec_CB_X_6B;
	m_aepExecuteTable[0x016C] = Exec_CB_X_6C;
	m_aepExecuteTable[0x016D] = Exec_CB_X_6D;
	m_aepExecuteTable[0x016E] = Exec_CB_X_6E;
	m_aepExecuteTable[0x016F] = Exec_CB_X_6F;
	m_aepExecuteTable[0x0170] = Exec_CB_X_70;
	m_aepExecuteTable[0x0171] = Exec_CB_X_71;
	m_aepExecuteTable[0x0172] = Exec_CB_X_72;
	m_aepExecuteTable[0x0173] = Exec_CB_X_73;
	m_aepExecuteTable[0x0174] = Exec_CB_X_74;
	m_aepExecuteTable[0x0175] = Exec_CB_X_75;
	m_aepExecuteTable[0x0176] = Exec_CB_X_76;
	m_aepExecuteTable[0x0177] = Exec_CB_X_77;
	m_aepExecuteTable[0x0178] = Exec_CB_X_78;
	m_aepExecuteTable[0x0179] = Exec_CB_X_79;
	m_aepExecuteTable[0x017A] = Exec_CB_X_7A;
	m_aepExecuteTable[0x017B] = Exec_CB_X_7B;
	m_aepExecuteTable[0x017C] = Exec_CB_X_7C;
	m_aepExecuteTable[0x017D] = Exec_CB_X_7D;
	m_aepExecuteTable[0x017E] = Exec_CB_X_7E;
	m_aepExecuteTable[0x017F] = Exec_CB_X_7F;
	m_aepExecuteTable[0x0180] = Exec_CB_X_80;
	m_aepExecuteTable[0x0181] = Exec_CB_X_81;
	m_aepExecuteTable[0x0182] = Exec_CB_X_82;
	m_aepExecuteTable[0x0183] = Exec_CB_X_83;
	m_aepExecuteTable[0x0184] = Exec_CB_X_84;
	m_aepExecuteTable[0x0185] = Exec_CB_X_85;
	m_aepExecuteTable[0x0186] = Exec_CB_X_86;
	m_aepExecuteTable[0x0187] = Exec_CB_X_87;
	m_aepExecuteTable[0x0188] = Exec_CB_X_88;
	m_aepExecuteTable[0x0189] = Exec_CB_X_89;
	m_aepExecuteTable[0x018A] = Exec_CB_X_8A;
	m_aepExecuteTable[0x018B] = Exec_CB_X_8B;
	m_aepExecuteTable[0x018C] = Exec_CB_X_8C;
	m_aepExecuteTable[0x018D] = Exec_CB_X_8D;
	m_aepExecuteTable[0x018E] = Exec_CB_X_8E;
	m_aepExecuteTable[0x018F] = Exec_CB_X_8F;
	m_aepExecuteTable[0x0190] = Exec_CB_X_90;
	m_aepExecuteTable[0x0191] = Exec_CB_X_91;
	m_aepExecuteTable[0x0192] = Exec_CB_X_92;
	m_aepExecuteTable[0x0193] = Exec_CB_X_93;
	m_aepExecuteTable[0x0194] = Exec_CB_X_94;
	m_aepExecuteTable[0x0195] = Exec_CB_X_95;
	m_aepExecuteTable[0x0196] = Exec_CB_X_96;
	m_aepExecuteTable[0x0197] = Exec_CB_X_97;
	m_aepExecuteTable[0x0198] = Exec_CB_X_98;
	m_aepExecuteTable[0x0199] = Exec_CB_X_99;
	m_aepExecuteTable[0x019A] = Exec_CB_X_9A;
	m_aepExecuteTable[0x019B] = Exec_CB_X_9B;
	m_aepExecuteTable[0x019C] = Exec_CB_X_9C;
	m_aepExecuteTable[0x019D] = Exec_CB_X_9D;
	m_aepExecuteTable[0x019E] = Exec_CB_X_9E;
	m_aepExecuteTable[0x019F] = Exec_CB_X_9F;
	m_aepExecuteTable[0x01A0] = Exec_CB_X_A0;
	m_aepExecuteTable[0x01A1] = Exec_CB_X_A1;
	m_aepExecuteTable[0x01A2] = Exec_CB_X_A2;
	m_aepExecuteTable[0x01A3] = Exec_CB_X_A3;
	m_aepExecuteTable[0x01A4] = Exec_CB_X_A4;
	m_aepExecuteTable[0x01A5] = Exec_CB_X_A5;
	m_aepExecuteTable[0x01A6] = Exec_CB_X_A6;
	m_aepExecuteTable[0x01A7] = Exec_CB_X_A7;
	m_aepExecuteTable[0x01A8] = Exec_CB_X_A8;
	m_aepExecuteTable[0x01A9] = Exec_CB_X_A9;
	m_aepExecuteTable[0x01AA] = Exec_CB_X_AA;
	m_aepExecuteTable[0x01AB] = Exec_CB_X_AB;
	m_aepExecuteTable[0x01AC] = Exec_CB_X_AC;
	m_aepExecuteTable[0x01AD] = Exec_CB_X_AD;
	m_aepExecuteTable[0x01AE] = Exec_CB_X_AE;
	m_aepExecuteTable[0x01AF] = Exec_CB_X_AF;
	m_aepExecuteTable[0x01B0] = Exec_CB_X_B0;
	m_aepExecuteTable[0x01B1] = Exec_CB_X_B1;
	m_aepExecuteTable[0x01B2] = Exec_CB_X_B2;
	m_aepExecuteTable[0x01B3] = Exec_CB_X_B3;
	m_aepExecuteTable[0x01B4] = Exec_CB_X_B4;
	m_aepExecuteTable[0x01B5] = Exec_CB_X_B5;
	m_aepExecuteTable[0x01B6] = Exec_CB_X_B6;
	m_aepExecuteTable[0x01B7] = Exec_CB_X_B7;
	m_aepExecuteTable[0x01B8] = Exec_CB_X_B8;
	m_aepExecuteTable[0x01B9] = Exec_CB_X_B9;
	m_aepExecuteTable[0x01BA] = Exec_CB_X_BA;
	m_aepExecuteTable[0x01BB] = Exec_CB_X_BB;
	m_aepExecuteTable[0x01BC] = Exec_CB_X_BC;
	m_aepExecuteTable[0x01BD] = Exec_CB_X_BD;
	m_aepExecuteTable[0x01BE] = Exec_CB_X_BE;
	m_aepExecuteTable[0x01BF] = Exec_CB_X_BF;
	m_aepExecuteTable[0x01C0] = Exec_CB_X_C0;
	m_aepExecuteTable[0x01C1] = Exec_CB_X_C1;
	m_aepExecuteTable[0x01C2] = Exec_CB_X_C2;
	m_aepExecuteTable[0x01C3] = Exec_CB_X_C3;
	m_aepExecuteTable[0x01C4] = Exec_CB_X_C4;
	m_aepExecuteTable[0x01C5] = Exec_CB_X_C5;
	m_aepExecuteTable[0x01C6] = Exec_CB_X_C6;
	m_aepExecuteTable[0x01C7] = Exec_CB_X_C7;
	m_aepExecuteTable[0x01C8] = Exec_CB_X_C8;
	m_aepExecuteTable[0x01C9] = Exec_CB_X_C9;
	m_aepExecuteTable[0x01CA] = Exec_CB_X_CA;
	m_aepExecuteTable[0x01CB] = Exec_CB_X_CB;
	m_aepExecuteTable[0x01CC] = Exec_CB_X_CC;
	m_aepExecuteTable[0x01CD] = Exec_CB_X_CD;
	m_aepExecuteTable[0x01CE] = Exec_CB_X_CE;
	m_aepExecuteTable[0x01CF] = Exec_CB_X_CF;
	m_aepExecuteTable[0x01D0] = Exec_CB_X_D0;
	m_aepExecuteTable[0x01D1] = Exec_CB_X_D1;
	m_aepExecuteTable[0x01D2] = Exec_CB_X_D2;
	m_aepExecuteTable[0x01D3] = Exec_CB_X_D3;
	m_aepExecuteTable[0x01D4] = Exec_CB_X_D4;
	m_aepExecuteTable[0x01D5] = Exec_CB_X_D5;
	m_aepExecuteTable[0x01D6] = Exec_CB_X_D6;
	m_aepExecuteTable[0x01D7] = Exec_CB_X_D7;
	m_aepExecuteTable[0x01D8] = Exec_CB_X_D8;
	m_aepExecuteTable[0x01D9] = Exec_CB_X_D9;
	m_aepExecuteTable[0x01DA] = Exec_CB_X_DA;
	m_aepExecuteTable[0x01DB] = Exec_CB_X_DB;
	m_aepExecuteTable[0x01DC] = Exec_CB_X_DC;
	m_aepExecuteTable[0x01DD] = Exec_CB_X_DD;
	m_aepExecuteTable[0x01DE] = Exec_CB_X_DE;
	m_aepExecuteTable[0x01DF] = Exec_CB_X_DF;
	m_aepExecuteTable[0x01E0] = Exec_CB_X_E0;
	m_aepExecuteTable[0x01E1] = Exec_CB_X_E1;
	m_aepExecuteTable[0x01E2] = Exec_CB_X_E2;
	m_aepExecuteTable[0x01E3] = Exec_CB_X_E3;
	m_aepExecuteTable[0x01E4] = Exec_CB_X_E4;
	m_aepExecuteTable[0x01E5] = Exec_CB_X_E5;
	m_aepExecuteTable[0x01E6] = Exec_CB_X_E6;
	m_aepExecuteTable[0x01E7] = Exec_CB_X_E7;
	m_aepExecuteTable[0x01E8] = Exec_CB_X_E8;
	m_aepExecuteTable[0x01E9] = Exec_CB_X_E9;
	m_aepExecuteTable[0x01EA] = Exec_CB_X_EA;
	m_aepExecuteTable[0x01EB] = Exec_CB_X_EB;
	m_aepExecuteTable[0x01EC] = Exec_CB_X_EC;
	m_aepExecuteTable[0x01ED] = Exec_CB_X_ED;
	m_aepExecuteTable[0x01EE] = Exec_CB_X_EE;
	m_aepExecuteTable[0x01EF] = Exec_CB_X_EF;
	m_aepExecuteTable[0x01F0] = Exec_CB_X_F0;
	m_aepExecuteTable[0x01F1] = Exec_CB_X_F1;
	m_aepExecuteTable[0x01F2] = Exec_CB_X_F2;
	m_aepExecuteTable[0x01F3] = Exec_CB_X_F3;
	m_aepExecuteTable[0x01F4] = Exec_CB_X_F4;
	m_aepExecuteTable[0x01F5] = Exec_CB_X_F5;
	m_aepExecuteTable[0x01F6] = Exec_CB_X_F6;
	m_aepExecuteTable[0x01F7] = Exec_CB_X_F7;
	m_aepExecuteTable[0x01F8] = Exec_CB_X_F8;
	m_aepExecuteTable[0x01F9] = Exec_CB_X_F9;
	m_aepExecuteTable[0x01FA] = Exec_CB_X_FA;
	m_aepExecuteTable[0x01FB] = Exec_CB_X_FB;
	m_aepExecuteTable[0x01FC] = Exec_CB_X_FC;
	m_aepExecuteTable[0x01FD] = Exec_CB_X_FD;
	m_aepExecuteTable[0x01FE] = Exec_CB_X_FE;
	m_aepExecuteTable[0x01FF] = Exec_CB_X_FF;
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Initialize_ED_X() {
	// Exec_ED_X
	m_aepExecuteTable[0x0200] = Exec_ED_X_default;
	m_aepExecuteTable[0x0201] = Exec_ED_X_default;
	m_aepExecuteTable[0x0202] = Exec_ED_X_default;
	m_aepExecuteTable[0x0203] = Exec_ED_X_default;
	m_aepExecuteTable[0x0204] = Exec_ED_X_default;
	m_aepExecuteTable[0x0205] = Exec_ED_X_default;
	m_aepExecuteTable[0x0206] = Exec_ED_X_default;
	m_aepExecuteTable[0x0207] = Exec_ED_X_default;
	m_aepExecuteTable[0x0208] = Exec_ED_X_default;
	m_aepExecuteTable[0x0209] = Exec_ED_X_default;
	m_aepExecuteTable[0x020A] = Exec_ED_X_default;
	m_aepExecuteTable[0x020B] = Exec_ED_X_default;
	m_aepExecuteTable[0x020C] = Exec_ED_X_default;
	m_aepExecuteTable[0x020D] = Exec_ED_X_default;
	m_aepExecuteTable[0x020E] = Exec_ED_X_default;
	m_aepExecuteTable[0x020F] = Exec_ED_X_default;
	m_aepExecuteTable[0x0210] = Exec_ED_X_default;
	m_aepExecuteTable[0x0211] = Exec_ED_X_default;
	m_aepExecuteTable[0x0212] = Exec_ED_X_default;
	m_aepExecuteTable[0x0213] = Exec_ED_X_default;
	m_aepExecuteTable[0x0214] = Exec_ED_X_default;
	m_aepExecuteTable[0x0215] = Exec_ED_X_default;
	m_aepExecuteTable[0x0216] = Exec_ED_X_default;
	m_aepExecuteTable[0x0217] = Exec_ED_X_default;
	m_aepExecuteTable[0x0218] = Exec_ED_X_default;
	m_aepExecuteTable[0x0219] = Exec_ED_X_default;
	m_aepExecuteTable[0x021A] = Exec_ED_X_default;
	m_aepExecuteTable[0x021B] = Exec_ED_X_default;
	m_aepExecuteTable[0x021C] = Exec_ED_X_default;
	m_aepExecuteTable[0x021D] = Exec_ED_X_default;
	m_aepExecuteTable[0x021E] = Exec_ED_X_default;
	m_aepExecuteTable[0x021F] = Exec_ED_X_default;
	m_aepExecuteTable[0x0220] = Exec_ED_X_default;
	m_aepExecuteTable[0x0221] = Exec_ED_X_default;
	m_aepExecuteTable[0x0222] = Exec_ED_X_default;
	m_aepExecuteTable[0x0223] = Exec_ED_X_default;
	m_aepExecuteTable[0x0224] = Exec_ED_X_default;
	m_aepExecuteTable[0x0225] = Exec_ED_X_default;
	m_aepExecuteTable[0x0226] = Exec_ED_X_default;
	m_aepExecuteTable[0x0227] = Exec_ED_X_default;
	m_aepExecuteTable[0x0228] = Exec_ED_X_default;
	m_aepExecuteTable[0x0229] = Exec_ED_X_default;
	m_aepExecuteTable[0x022A] = Exec_ED_X_default;
	m_aepExecuteTable[0x022B] = Exec_ED_X_default;
	m_aepExecuteTable[0x022C] = Exec_ED_X_default;
	m_aepExecuteTable[0x022D] = Exec_ED_X_default;
	m_aepExecuteTable[0x022E] = Exec_ED_X_default;
	m_aepExecuteTable[0x022F] = Exec_ED_X_default;
	m_aepExecuteTable[0x0230] = Exec_ED_X_default;
	m_aepExecuteTable[0x0231] = Exec_ED_X_default;
	m_aepExecuteTable[0x0232] = Exec_ED_X_default;
	m_aepExecuteTable[0x0233] = Exec_ED_X_default;
	m_aepExecuteTable[0x0234] = Exec_ED_X_default;
	m_aepExecuteTable[0x0235] = Exec_ED_X_default;
	m_aepExecuteTable[0x0236] = Exec_ED_X_default;
	m_aepExecuteTable[0x0237] = Exec_ED_X_default;
	m_aepExecuteTable[0x0238] = Exec_ED_X_default;
	m_aepExecuteTable[0x0239] = Exec_ED_X_default;
	m_aepExecuteTable[0x023A] = Exec_ED_X_default;
	m_aepExecuteTable[0x023B] = Exec_ED_X_default;
	m_aepExecuteTable[0x023C] = Exec_ED_X_default;
	m_aepExecuteTable[0x023D] = Exec_ED_X_default;
	m_aepExecuteTable[0x023E] = Exec_ED_X_default;
	m_aepExecuteTable[0x023F] = Exec_ED_X_default;
	m_aepExecuteTable[0x0240] = Exec_ED_X_40;
	m_aepExecuteTable[0x0241] = Exec_ED_X_41;
	m_aepExecuteTable[0x0242] = Exec_ED_X_42;
	m_aepExecuteTable[0x0243] = Exec_ED_X_43;
	m_aepExecuteTable[0x0244] = Exec_ED_X_44_x;
	m_aepExecuteTable[0x0245] = Exec_ED_X_45_x;
	m_aepExecuteTable[0x0246] = Exec_ED_X_46_x;
	m_aepExecuteTable[0x0247] = Exec_ED_X_47;
	m_aepExecuteTable[0x0248] = Exec_ED_X_48;
	m_aepExecuteTable[0x0249] = Exec_ED_X_49;
	m_aepExecuteTable[0x024A] = Exec_ED_X_4A;
	m_aepExecuteTable[0x024B] = Exec_ED_X_4B;
	m_aepExecuteTable[0x024C] = Exec_ED_X_44_x;
	m_aepExecuteTable[0x024D] = Exec_ED_X_4D_x;
	m_aepExecuteTable[0x024E] = Exec_ED_X_4E_x;
	m_aepExecuteTable[0x024F] = Exec_ED_X_4F;
	m_aepExecuteTable[0x0250] = Exec_ED_X_50;
	m_aepExecuteTable[0x0251] = Exec_ED_X_51;
	m_aepExecuteTable[0x0252] = Exec_ED_X_52;
	m_aepExecuteTable[0x0253] = Exec_ED_X_53;
	m_aepExecuteTable[0x0254] = Exec_ED_X_44_x;
	m_aepExecuteTable[0x0255] = Exec_ED_X_45_x;
	m_aepExecuteTable[0x0256] = Exec_ED_X_56_x;
	m_aepExecuteTable[0x0257] = Exec_ED_X_57;
	m_aepExecuteTable[0x0258] = Exec_ED_X_58;
	m_aepExecuteTable[0x0259] = Exec_ED_X_59;
	m_aepExecuteTable[0x025A] = Exec_ED_X_5A;
	m_aepExecuteTable[0x025B] = Exec_ED_X_5B;
	m_aepExecuteTable[0x025C] = Exec_ED_X_44_x;
	m_aepExecuteTable[0x025D] = Exec_ED_X_4D_x;
	m_aepExecuteTable[0x025E] = Exec_ED_X_5E_x;
	m_aepExecuteTable[0x025F] = Exec_ED_X_5F;
	m_aepExecuteTable[0x0260] = Exec_ED_X_60;
	m_aepExecuteTable[0x0261] = Exec_ED_X_61;
	m_aepExecuteTable[0x0262] = Exec_ED_X_62;
	m_aepExecuteTable[0x0263] = Exec_ED_X_63;
	m_aepExecuteTable[0x0264] = Exec_ED_X_44_x;
	m_aepExecuteTable[0x0265] = Exec_ED_X_45_x;
	m_aepExecuteTable[0x0266] = Exec_ED_X_46_x;
	m_aepExecuteTable[0x0267] = Exec_ED_X_67;
	m_aepExecuteTable[0x0268] = Exec_ED_X_68;
	m_aepExecuteTable[0x0269] = Exec_ED_X_69;
	m_aepExecuteTable[0x026A] = Exec_ED_X_6A;
	m_aepExecuteTable[0x026B] = Exec_ED_X_6B;
	m_aepExecuteTable[0x026C] = Exec_ED_X_44_x;
	m_aepExecuteTable[0x026D] = Exec_ED_X_4D_x;
	m_aepExecuteTable[0x026E] = Exec_ED_X_4E_x;
	m_aepExecuteTable[0x026F] = Exec_ED_X_6F;
	m_aepExecuteTable[0x0270] = Exec_ED_X_70;
	m_aepExecuteTable[0x0271] = Exec_ED_X_71;
	m_aepExecuteTable[0x0272] = Exec_ED_X_72;
	m_aepExecuteTable[0x0273] = Exec_ED_X_73;
	m_aepExecuteTable[0x0274] = Exec_ED_X_44_x;
	m_aepExecuteTable[0x0275] = Exec_ED_X_45_x;
	m_aepExecuteTable[0x0276] = Exec_ED_X_56_x;
	m_aepExecuteTable[0x0277] = Exec_ED_X_77_x;
	m_aepExecuteTable[0x0278] = Exec_ED_X_78;
	m_aepExecuteTable[0x0279] = Exec_ED_X_79;
	m_aepExecuteTable[0x027A] = Exec_ED_X_7A;
	m_aepExecuteTable[0x027B] = Exec_ED_X_7B;
	m_aepExecuteTable[0x027C] = Exec_ED_X_44_x;
	m_aepExecuteTable[0x027D] = Exec_ED_X_4D_x;
	m_aepExecuteTable[0x027E] = Exec_ED_X_5E_x;
	m_aepExecuteTable[0x027F] = Exec_ED_X_77_x;
	m_aepExecuteTable[0x0280] = Exec_ED_X_default;
	m_aepExecuteTable[0x0281] = Exec_ED_X_default;
	m_aepExecuteTable[0x0282] = Exec_ED_X_default;
	m_aepExecuteTable[0x0283] = Exec_ED_X_default;
	m_aepExecuteTable[0x0284] = Exec_ED_X_default;
	m_aepExecuteTable[0x0285] = Exec_ED_X_default;
	m_aepExecuteTable[0x0286] = Exec_ED_X_default;
	m_aepExecuteTable[0x0287] = Exec_ED_X_default;
	m_aepExecuteTable[0x0288] = Exec_ED_X_default;
	m_aepExecuteTable[0x0289] = Exec_ED_X_default;
	m_aepExecuteTable[0x028A] = Exec_ED_X_default;
	m_aepExecuteTable[0x028B] = Exec_ED_X_default;
	m_aepExecuteTable[0x028C] = Exec_ED_X_default;
	m_aepExecuteTable[0x028D] = Exec_ED_X_default;
	m_aepExecuteTable[0x028E] = Exec_ED_X_default;
	m_aepExecuteTable[0x028F] = Exec_ED_X_default;
	m_aepExecuteTable[0x0290] = Exec_ED_X_default;
	m_aepExecuteTable[0x0291] = Exec_ED_X_default;
	m_aepExecuteTable[0x0292] = Exec_ED_X_default;
	m_aepExecuteTable[0x0293] = Exec_ED_X_default;
	m_aepExecuteTable[0x0294] = Exec_ED_X_default;
	m_aepExecuteTable[0x0295] = Exec_ED_X_default;
	m_aepExecuteTable[0x0296] = Exec_ED_X_default;
	m_aepExecuteTable[0x0297] = Exec_ED_X_default;
	m_aepExecuteTable[0x0298] = Exec_ED_X_default;
	m_aepExecuteTable[0x0299] = Exec_ED_X_default;
	m_aepExecuteTable[0x029A] = Exec_ED_X_default;
	m_aepExecuteTable[0x029B] = Exec_ED_X_default;
	m_aepExecuteTable[0x029C] = Exec_ED_X_default;
	m_aepExecuteTable[0x029D] = Exec_ED_X_default;
	m_aepExecuteTable[0x029E] = Exec_ED_X_default;
	m_aepExecuteTable[0x029F] = Exec_ED_X_default;
	m_aepExecuteTable[0x02A0] = Exec_ED_X_A0;
	m_aepExecuteTable[0x02A1] = Exec_ED_X_A1;
	m_aepExecuteTable[0x02A2] = Exec_ED_X_A2;
	m_aepExecuteTable[0x02A3] = Exec_ED_X_A3;
	m_aepExecuteTable[0x02A4] = Exec_ED_X_default;
	m_aepExecuteTable[0x02A5] = Exec_ED_X_default;
	m_aepExecuteTable[0x02A6] = Exec_ED_X_default;
	m_aepExecuteTable[0x02A7] = Exec_ED_X_default;
	m_aepExecuteTable[0x02A8] = Exec_ED_X_A8;
	m_aepExecuteTable[0x02A9] = Exec_ED_X_A9;
	m_aepExecuteTable[0x02AA] = Exec_ED_X_AA;
	m_aepExecuteTable[0x02AB] = Exec_ED_X_AB;
	m_aepExecuteTable[0x02AC] = Exec_ED_X_default;
	m_aepExecuteTable[0x02AD] = Exec_ED_X_default;
	m_aepExecuteTable[0x02AE] = Exec_ED_X_default;
	m_aepExecuteTable[0x02AF] = Exec_ED_X_default;
	m_aepExecuteTable[0x02B0] = Exec_ED_X_B0;
	m_aepExecuteTable[0x02B1] = Exec_ED_X_B1;
	m_aepExecuteTable[0x02B2] = Exec_ED_X_B2;
	m_aepExecuteTable[0x02B3] = Exec_ED_X_B3;
	m_aepExecuteTable[0x02B4] = Exec_ED_X_default;
	m_aepExecuteTable[0x02B5] = Exec_ED_X_default;
	m_aepExecuteTable[0x02B6] = Exec_ED_X_default;
	m_aepExecuteTable[0x02B7] = Exec_ED_X_default;
	m_aepExecuteTable[0x02B8] = Exec_ED_X_B8;
	m_aepExecuteTable[0x02B9] = Exec_ED_X_B9;
	m_aepExecuteTable[0x02BA] = Exec_ED_X_BA;
	m_aepExecuteTable[0x02BB] = Exec_ED_X_BB;
	m_aepExecuteTable[0x02BC] = Exec_ED_X_default;
	m_aepExecuteTable[0x02BD] = Exec_ED_X_default;
	m_aepExecuteTable[0x02BE] = Exec_ED_X_default;
	m_aepExecuteTable[0x02BF] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C0] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C1] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C2] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C3] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C4] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C5] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C6] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C7] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C8] = Exec_ED_X_default;
	m_aepExecuteTable[0x02C9] = Exec_ED_X_default;
	m_aepExecuteTable[0x02CA] = Exec_ED_X_default;
	m_aepExecuteTable[0x02CB] = Exec_ED_X_default;
	m_aepExecuteTable[0x02CC] = Exec_ED_X_default;
	m_aepExecuteTable[0x02CD] = Exec_ED_X_default;
	m_aepExecuteTable[0x02CE] = Exec_ED_X_default;
	m_aepExecuteTable[0x02CF] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D0] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D1] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D2] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D3] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D4] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D5] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D6] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D7] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D8] = Exec_ED_X_default;
	m_aepExecuteTable[0x02D9] = Exec_ED_X_default;
	m_aepExecuteTable[0x02DA] = Exec_ED_X_default;
	m_aepExecuteTable[0x02DB] = Exec_ED_X_default;
	m_aepExecuteTable[0x02DC] = Exec_ED_X_default;
	m_aepExecuteTable[0x02DD] = Exec_ED_X_default;
	m_aepExecuteTable[0x02DE] = Exec_ED_X_default;
	m_aepExecuteTable[0x02DF] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E0] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E1] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E2] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E3] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E4] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E5] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E6] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E7] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E8] = Exec_ED_X_default;
	m_aepExecuteTable[0x02E9] = Exec_ED_X_default;
	m_aepExecuteTable[0x02EA] = Exec_ED_X_default;
	m_aepExecuteTable[0x02EB] = Exec_ED_X_default;
	m_aepExecuteTable[0x02EC] = Exec_ED_X_default;
	m_aepExecuteTable[0x02ED] = Exec_ED_X_default;
	m_aepExecuteTable[0x02EE] = Exec_ED_X_default;
	m_aepExecuteTable[0x02EF] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F0] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F1] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F2] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F3] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F4] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F5] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F6] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F7] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F8] = Exec_ED_X_default;
	m_aepExecuteTable[0x02F9] = Exec_ED_X_default;
	m_aepExecuteTable[0x02FA] = Exec_ED_X_default;
	m_aepExecuteTable[0x02FB] = Exec_ED_X_default;
	m_aepExecuteTable[0x02FC] = Exec_ED_X_default;
	m_aepExecuteTable[0x02FD] = Exec_ED_X_default;
	m_aepExecuteTable[0x02FE] = Exec_ED_X_default;
	m_aepExecuteTable[0x02FF] = Exec_ED_X_default;
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Initialize_DD_X() {
	// Exec_DD_X
	m_aepExecuteTable[0x0300] = Exec_X_00;
	m_aepExecuteTable[0x0301] = Exec_X_01;
	m_aepExecuteTable[0x0302] = Exec_X_02;
	m_aepExecuteTable[0x0303] = Exec_X_03;
	m_aepExecuteTable[0x0304] = Exec_X_04;
	m_aepExecuteTable[0x0305] = Exec_X_05;
	m_aepExecuteTable[0x0306] = Exec_X_06;
	m_aepExecuteTable[0x0307] = Exec_X_07;
	m_aepExecuteTable[0x0308] = Exec_X_08;
	m_aepExecuteTable[0x0309] = Exec_DD_X_09;
	m_aepExecuteTable[0x030A] = Exec_X_0A;
	m_aepExecuteTable[0x030B] = Exec_X_0B;
	m_aepExecuteTable[0x030C] = Exec_X_0C;
	m_aepExecuteTable[0x030D] = Exec_X_0D;
	m_aepExecuteTable[0x030E] = Exec_X_0E;
	m_aepExecuteTable[0x030F] = Exec_X_0F;
	m_aepExecuteTable[0x0310] = Exec_X_10;
	m_aepExecuteTable[0x0311] = Exec_X_11;
	m_aepExecuteTable[0x0312] = Exec_X_12;
	m_aepExecuteTable[0x0313] = Exec_X_13;
	m_aepExecuteTable[0x0314] = Exec_X_14;
	m_aepExecuteTable[0x0315] = Exec_X_15;
	m_aepExecuteTable[0x0316] = Exec_X_16;
	m_aepExecuteTable[0x0317] = Exec_X_17;
	m_aepExecuteTable[0x0318] = Exec_X_18;
	m_aepExecuteTable[0x0319] = Exec_DD_X_19;
	m_aepExecuteTable[0x031A] = Exec_X_1A;
	m_aepExecuteTable[0x031B] = Exec_X_1B;
	m_aepExecuteTable[0x031C] = Exec_X_1C;
	m_aepExecuteTable[0x031D] = Exec_X_1D;
	m_aepExecuteTable[0x031E] = Exec_X_1E;
	m_aepExecuteTable[0x031F] = Exec_X_1F;
	m_aepExecuteTable[0x0320] = Exec_X_20;
	m_aepExecuteTable[0x0321] = Exec_DD_X_21;
	m_aepExecuteTable[0x0322] = Exec_DD_X_22;
	m_aepExecuteTable[0x0323] = Exec_DD_X_23;
	m_aepExecuteTable[0x0324] = Exec_DD_X_24;
	m_aepExecuteTable[0x0325] = Exec_DD_X_25;
	m_aepExecuteTable[0x0326] = Exec_DD_X_26;
	m_aepExecuteTable[0x0327] = Exec_X_27;
	m_aepExecuteTable[0x0328] = Exec_X_28;
	m_aepExecuteTable[0x0329] = Exec_DD_X_29;
	m_aepExecuteTable[0x032A] = Exec_DD_X_2A;
	m_aepExecuteTable[0x032B] = Exec_DD_X_2B;
	m_aepExecuteTable[0x032C] = Exec_DD_X_2C;
	m_aepExecuteTable[0x032D] = Exec_DD_X_2D;
	m_aepExecuteTable[0x032E] = Exec_DD_X_2E;
	m_aepExecuteTable[0x032F] = Exec_X_2F;
	m_aepExecuteTable[0x0330] = Exec_X_30;
	m_aepExecuteTable[0x0331] = Exec_X_31;
	m_aepExecuteTable[0x0332] = Exec_X_32;
	m_aepExecuteTable[0x0333] = Exec_X_33;
	m_aepExecuteTable[0x0334] = Exec_DD_X_34;
	m_aepExecuteTable[0x0335] = Exec_DD_X_35;
	m_aepExecuteTable[0x0336] = Exec_DD_X_36;
	m_aepExecuteTable[0x0337] = Exec_X_37;
	m_aepExecuteTable[0x0338] = Exec_X_38;
	m_aepExecuteTable[0x0339] = Exec_DD_X_39;
	m_aepExecuteTable[0x033A] = Exec_X_3A;
	m_aepExecuteTable[0x033B] = Exec_X_3B;
	m_aepExecuteTable[0x033C] = Exec_X_3C;
	m_aepExecuteTable[0x033D] = Exec_X_3D;
	m_aepExecuteTable[0x033E] = Exec_X_3E;
	m_aepExecuteTable[0x033F] = Exec_X_3F;
	m_aepExecuteTable[0x0340] = Exec_X_40;
	m_aepExecuteTable[0x0341] = Exec_X_41;
	m_aepExecuteTable[0x0342] = Exec_X_42;
	m_aepExecuteTable[0x0343] = Exec_X_43;
	m_aepExecuteTable[0x0344] = Exec_DD_X_44;
	m_aepExecuteTable[0x0345] = Exec_DD_X_45;
	m_aepExecuteTable[0x0346] = Exec_DD_X_46;
	m_aepExecuteTable[0x0347] = Exec_X_47;
	m_aepExecuteTable[0x0348] = Exec_X_48;
	m_aepExecuteTable[0x0349] = Exec_X_49;
	m_aepExecuteTable[0x034A] = Exec_X_4A;
	m_aepExecuteTable[0x034B] = Exec_X_4B;
	m_aepExecuteTable[0x034C] = Exec_DD_X_4C;
	m_aepExecuteTable[0x034D] = Exec_DD_X_4D;
	m_aepExecuteTable[0x034E] = Exec_DD_X_4E;
	m_aepExecuteTable[0x034F] = Exec_X_4F;
	m_aepExecuteTable[0x0350] = Exec_X_50;
	m_aepExecuteTable[0x0351] = Exec_X_51;
	m_aepExecuteTable[0x0352] = Exec_X_52;
	m_aepExecuteTable[0x0353] = Exec_X_53;
	m_aepExecuteTable[0x0354] = Exec_DD_X_54;
	m_aepExecuteTable[0x0355] = Exec_DD_X_55;
	m_aepExecuteTable[0x0356] = Exec_DD_X_56;
	m_aepExecuteTable[0x0357] = Exec_X_57;
	m_aepExecuteTable[0x0358] = Exec_X_58;
	m_aepExecuteTable[0x0359] = Exec_X_59;
	m_aepExecuteTable[0x035A] = Exec_X_5A;
	m_aepExecuteTable[0x035B] = Exec_X_5B;
	m_aepExecuteTable[0x035C] = Exec_DD_X_5C;
	m_aepExecuteTable[0x035D] = Exec_DD_X_5D;
	m_aepExecuteTable[0x035E] = Exec_DD_X_5E;
	m_aepExecuteTable[0x035F] = Exec_X_5F;
	m_aepExecuteTable[0x0360] = Exec_DD_X_60;
	m_aepExecuteTable[0x0361] = Exec_DD_X_61;
	m_aepExecuteTable[0x0362] = Exec_DD_X_62;
	m_aepExecuteTable[0x0363] = Exec_DD_X_63;
	m_aepExecuteTable[0x0364] = Exec_DD_X_64;
	m_aepExecuteTable[0x0365] = Exec_DD_X_65;
	m_aepExecuteTable[0x0366] = Exec_DD_X_66;
	m_aepExecuteTable[0x0367] = Exec_DD_X_67;
	m_aepExecuteTable[0x0368] = Exec_DD_X_68;
	m_aepExecuteTable[0x0369] = Exec_DD_X_69;
	m_aepExecuteTable[0x036A] = Exec_DD_X_6A;
	m_aepExecuteTable[0x036B] = Exec_DD_X_6B;
	m_aepExecuteTable[0x036C] = Exec_DD_X_6C;
	m_aepExecuteTable[0x036D] = Exec_DD_X_6D;
	m_aepExecuteTable[0x036E] = Exec_DD_X_6E;
	m_aepExecuteTable[0x036F] = Exec_DD_X_6F;
	m_aepExecuteTable[0x0370] = Exec_DD_X_70;
	m_aepExecuteTable[0x0371] = Exec_DD_X_71;
	m_aepExecuteTable[0x0372] = Exec_DD_X_72;
	m_aepExecuteTable[0x0373] = Exec_DD_X_73;
	m_aepExecuteTable[0x0374] = Exec_DD_X_74;
	m_aepExecuteTable[0x0375] = Exec_DD_X_75;
	m_aepExecuteTable[0x0376] = Exec_X_76;
	m_aepExecuteTable[0x0377] = Exec_DD_X_77;
	m_aepExecuteTable[0x0378] = Exec_X_78;
	m_aepExecuteTable[0x0379] = Exec_X_79;
	m_aepExecuteTable[0x037A] = Exec_X_7A;
	m_aepExecuteTable[0x037B] = Exec_X_7B;
	m_aepExecuteTable[0x037C] = Exec_DD_X_7C;
	m_aepExecuteTable[0x037D] = Exec_DD_X_7D;
	m_aepExecuteTable[0x037E] = Exec_DD_X_7E;
	m_aepExecuteTable[0x037F] = Exec_X_7F;
	m_aepExecuteTable[0x0380] = Exec_X_80;
	m_aepExecuteTable[0x0381] = Exec_X_81;
	m_aepExecuteTable[0x0382] = Exec_X_82;
	m_aepExecuteTable[0x0383] = Exec_X_83;
	m_aepExecuteTable[0x0384] = Exec_DD_X_84;
	m_aepExecuteTable[0x0385] = Exec_DD_X_85;
	m_aepExecuteTable[0x0386] = Exec_DD_X_86;
	m_aepExecuteTable[0x0387] = Exec_X_87;
	m_aepExecuteTable[0x0388] = Exec_X_88;
	m_aepExecuteTable[0x0389] = Exec_X_89;
	m_aepExecuteTable[0x038A] = Exec_X_8A;
	m_aepExecuteTable[0x038B] = Exec_X_8B;
	m_aepExecuteTable[0x038C] = Exec_DD_X_8C;
	m_aepExecuteTable[0x038D] = Exec_DD_X_8D;
	m_aepExecuteTable[0x038E] = Exec_DD_X_8E;
	m_aepExecuteTable[0x038F] = Exec_X_8F;
	m_aepExecuteTable[0x0390] = Exec_X_90;
	m_aepExecuteTable[0x0391] = Exec_X_91;
	m_aepExecuteTable[0x0392] = Exec_X_92;
	m_aepExecuteTable[0x0393] = Exec_X_93;
	m_aepExecuteTable[0x0394] = Exec_DD_X_94;
	m_aepExecuteTable[0x0395] = Exec_DD_X_95;
	m_aepExecuteTable[0x0396] = Exec_DD_X_96;
	m_aepExecuteTable[0x0397] = Exec_X_97;
	m_aepExecuteTable[0x0398] = Exec_X_98;
	m_aepExecuteTable[0x0399] = Exec_X_99;
	m_aepExecuteTable[0x039A] = Exec_X_9A;
	m_aepExecuteTable[0x039B] = Exec_X_9B;
	m_aepExecuteTable[0x039C] = Exec_DD_X_9C;
	m_aepExecuteTable[0x039D] = Exec_DD_X_9D;
	m_aepExecuteTable[0x039E] = Exec_DD_X_9E;
	m_aepExecuteTable[0x039F] = Exec_X_9F;
	m_aepExecuteTable[0x03A0] = Exec_X_A0;
	m_aepExecuteTable[0x03A1] = Exec_X_A1;
	m_aepExecuteTable[0x03A2] = Exec_X_A2;
	m_aepExecuteTable[0x03A3] = Exec_X_A3;
	m_aepExecuteTable[0x03A4] = Exec_DD_X_A4;
	m_aepExecuteTable[0x03A5] = Exec_DD_X_A5;
	m_aepExecuteTable[0x03A6] = Exec_DD_X_A6;
	m_aepExecuteTable[0x03A7] = Exec_X_A7;
	m_aepExecuteTable[0x03A8] = Exec_X_A8;
	m_aepExecuteTable[0x03A9] = Exec_X_A9;
	m_aepExecuteTable[0x03AA] = Exec_X_AA;
	m_aepExecuteTable[0x03AB] = Exec_X_AB;
	m_aepExecuteTable[0x03AC] = Exec_DD_X_AC;
	m_aepExecuteTable[0x03AD] = Exec_DD_X_AD;
	m_aepExecuteTable[0x03AE] = Exec_DD_X_AE;
	m_aepExecuteTable[0x03AF] = Exec_X_AF;
	m_aepExecuteTable[0x03B0] = Exec_X_B0;
	m_aepExecuteTable[0x03B1] = Exec_X_B1;
	m_aepExecuteTable[0x03B2] = Exec_X_B2;
	m_aepExecuteTable[0x03B3] = Exec_X_B3;
	m_aepExecuteTable[0x03B4] = Exec_DD_X_B4;
	m_aepExecuteTable[0x03B5] = Exec_DD_X_B5;
	m_aepExecuteTable[0x03B6] = Exec_DD_X_B6;
	m_aepExecuteTable[0x03B7] = Exec_X_B7;
	m_aepExecuteTable[0x03B8] = Exec_X_B8;
	m_aepExecuteTable[0x03B9] = Exec_X_B9;
	m_aepExecuteTable[0x03BA] = Exec_X_BA;
	m_aepExecuteTable[0x03BB] = Exec_X_BB;
	m_aepExecuteTable[0x03BC] = Exec_DD_X_BC;
	m_aepExecuteTable[0x03BD] = Exec_DD_X_BD;
	m_aepExecuteTable[0x03BE] = Exec_DD_X_BE;
	m_aepExecuteTable[0x03BF] = Exec_X_BF;
	m_aepExecuteTable[0x03C0] = Exec_X_C0;
	m_aepExecuteTable[0x03C1] = Exec_X_C1;
	m_aepExecuteTable[0x03C2] = Exec_X_C2;
	m_aepExecuteTable[0x03C3] = Exec_X_C3;
	m_aepExecuteTable[0x03C4] = Exec_X_C4;
	m_aepExecuteTable[0x03C5] = Exec_X_C5;
	m_aepExecuteTable[0x03C6] = Exec_X_C6;
	m_aepExecuteTable[0x03C7] = Exec_X_C7;
	m_aepExecuteTable[0x03C8] = Exec_X_C8;
	m_aepExecuteTable[0x03C9] = Exec_X_C9;
	m_aepExecuteTable[0x03CA] = Exec_X_CA;
	m_aepExecuteTable[0x03CB] = Exec_DD_X_CB;
	m_aepExecuteTable[0x03CC] = Exec_X_CC;
	m_aepExecuteTable[0x03CD] = Exec_X_CD;
	m_aepExecuteTable[0x03CE] = Exec_X_CE;
	m_aepExecuteTable[0x03CF] = Exec_X_CF;
	m_aepExecuteTable[0x03D0] = Exec_X_D0;
	m_aepExecuteTable[0x03D1] = Exec_X_D1;
	m_aepExecuteTable[0x03D2] = Exec_X_D2;
	m_aepExecuteTable[0x03D3] = Exec_X_D3;
	m_aepExecuteTable[0x03D4] = Exec_X_D4;
	m_aepExecuteTable[0x03D5] = Exec_X_D5;
	m_aepExecuteTable[0x03D6] = Exec_X_D6;
	m_aepExecuteTable[0x03D7] = Exec_X_D7;
	m_aepExecuteTable[0x03D8] = Exec_X_D8;
	m_aepExecuteTable[0x03D9] = Exec_X_D9;
	m_aepExecuteTable[0x03DA] = Exec_X_DA;
	m_aepExecuteTable[0x03DB] = Exec_X_DB;
	m_aepExecuteTable[0x03DC] = Exec_X_DC;
	m_aepExecuteTable[0x03DD] = Exec_X_DD;
	m_aepExecuteTable[0x03DE] = Exec_X_DE;
	m_aepExecuteTable[0x03DF] = Exec_X_DF;
	m_aepExecuteTable[0x03E0] = Exec_X_E0;
	m_aepExecuteTable[0x03E1] = Exec_DD_X_E1;
	m_aepExecuteTable[0x03E2] = Exec_X_E2;
	m_aepExecuteTable[0x03E3] = Exec_DD_X_E3;
	m_aepExecuteTable[0x03E4] = Exec_X_E4;
	m_aepExecuteTable[0x03E5] = Exec_DD_X_E5;
	m_aepExecuteTable[0x03E6] = Exec_X_E6;
	m_aepExecuteTable[0x03E7] = Exec_X_E7;
	m_aepExecuteTable[0x03E8] = Exec_X_E8;
	m_aepExecuteTable[0x03E9] = Exec_DD_X_E9;
	m_aepExecuteTable[0x03EA] = Exec_X_EA;
	m_aepExecuteTable[0x03EB] = Exec_X_EB;
	m_aepExecuteTable[0x03EC] = Exec_X_EC;
	m_aepExecuteTable[0x03ED] = Exec_X_ED;
	m_aepExecuteTable[0x03EE] = Exec_X_EE;
	m_aepExecuteTable[0x03EF] = Exec_X_EF;
	m_aepExecuteTable[0x03F0] = Exec_X_F0;
	m_aepExecuteTable[0x03F1] = Exec_X_F1;
	m_aepExecuteTable[0x03F2] = Exec_X_F2;
	m_aepExecuteTable[0x03F3] = Exec_X_F3;
	m_aepExecuteTable[0x03F4] = Exec_X_F4;
	m_aepExecuteTable[0x03F5] = Exec_X_F5;
	m_aepExecuteTable[0x03F6] = Exec_X_F6;
	m_aepExecuteTable[0x03F7] = Exec_X_F7;
	m_aepExecuteTable[0x03F8] = Exec_X_F8;
	m_aepExecuteTable[0x03F9] = Exec_DD_X_F9;
	m_aepExecuteTable[0x03FA] = Exec_X_FA;
	m_aepExecuteTable[0x03FB] = Exec_X_FB;
	m_aepExecuteTable[0x03FC] = Exec_X_FC;
	m_aepExecuteTable[0x03FD] = Exec_X_FD;
	m_aepExecuteTable[0x03FE] = Exec_X_FE;
	m_aepExecuteTable[0x03FF] = Exec_X_FF;
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Initialize_DD_CB_X() {
	// Exec_DD_CB_X
	m_aepExecuteTable[0x0400] = Exec_DD_CB_X_00;
	m_aepExecuteTable[0x0401] = Exec_DD_CB_X_01;
	m_aepExecuteTable[0x0402] = Exec_DD_CB_X_02;
	m_aepExecuteTable[0x0403] = Exec_DD_CB_X_03;
	m_aepExecuteTable[0x0404] = Exec_DD_CB_X_04;
	m_aepExecuteTable[0x0405] = Exec_DD_CB_X_05;
	m_aepExecuteTable[0x0406] = Exec_DD_CB_X_06;
	m_aepExecuteTable[0x0407] = Exec_DD_CB_X_07;
	m_aepExecuteTable[0x0408] = Exec_DD_CB_X_08;
	m_aepExecuteTable[0x0409] = Exec_DD_CB_X_09;
	m_aepExecuteTable[0x040A] = Exec_DD_CB_X_0A;
	m_aepExecuteTable[0x040B] = Exec_DD_CB_X_0B;
	m_aepExecuteTable[0x040C] = Exec_DD_CB_X_0C;
	m_aepExecuteTable[0x040D] = Exec_DD_CB_X_0D;
	m_aepExecuteTable[0x040E] = Exec_DD_CB_X_0E;
	m_aepExecuteTable[0x040F] = Exec_DD_CB_X_0F;
	m_aepExecuteTable[0x0410] = Exec_DD_CB_X_10;
	m_aepExecuteTable[0x0411] = Exec_DD_CB_X_11;
	m_aepExecuteTable[0x0412] = Exec_DD_CB_X_12;
	m_aepExecuteTable[0x0413] = Exec_DD_CB_X_13;
	m_aepExecuteTable[0x0414] = Exec_DD_CB_X_14;
	m_aepExecuteTable[0x0415] = Exec_DD_CB_X_15;
	m_aepExecuteTable[0x0416] = Exec_DD_CB_X_16;
	m_aepExecuteTable[0x0417] = Exec_DD_CB_X_17;
	m_aepExecuteTable[0x0418] = Exec_DD_CB_X_18;
	m_aepExecuteTable[0x0419] = Exec_DD_CB_X_19;
	m_aepExecuteTable[0x041A] = Exec_DD_CB_X_1A;
	m_aepExecuteTable[0x041B] = Exec_DD_CB_X_1B;
	m_aepExecuteTable[0x041C] = Exec_DD_CB_X_1C;
	m_aepExecuteTable[0x041D] = Exec_DD_CB_X_1D;
	m_aepExecuteTable[0x041E] = Exec_DD_CB_X_1E;
	m_aepExecuteTable[0x041F] = Exec_DD_CB_X_1F;
	m_aepExecuteTable[0x0420] = Exec_DD_CB_X_20;
	m_aepExecuteTable[0x0421] = Exec_DD_CB_X_21;
	m_aepExecuteTable[0x0422] = Exec_DD_CB_X_22;
	m_aepExecuteTable[0x0423] = Exec_DD_CB_X_23;
	m_aepExecuteTable[0x0424] = Exec_DD_CB_X_24;
	m_aepExecuteTable[0x0425] = Exec_DD_CB_X_25;
	m_aepExecuteTable[0x0426] = Exec_DD_CB_X_26;
	m_aepExecuteTable[0x0427] = Exec_DD_CB_X_27;
	m_aepExecuteTable[0x0428] = Exec_DD_CB_X_28;
	m_aepExecuteTable[0x0429] = Exec_DD_CB_X_29;
	m_aepExecuteTable[0x042A] = Exec_DD_CB_X_2A;
	m_aepExecuteTable[0x042B] = Exec_DD_CB_X_2B;
	m_aepExecuteTable[0x042C] = Exec_DD_CB_X_2C;
	m_aepExecuteTable[0x042D] = Exec_DD_CB_X_2D;
	m_aepExecuteTable[0x042E] = Exec_DD_CB_X_2E;
	m_aepExecuteTable[0x042F] = Exec_DD_CB_X_2F;
	m_aepExecuteTable[0x0430] = Exec_DD_CB_X_30;
	m_aepExecuteTable[0x0431] = Exec_DD_CB_X_31;
	m_aepExecuteTable[0x0432] = Exec_DD_CB_X_32;
	m_aepExecuteTable[0x0433] = Exec_DD_CB_X_33;
	m_aepExecuteTable[0x0434] = Exec_DD_CB_X_34;
	m_aepExecuteTable[0x0435] = Exec_DD_CB_X_35;
	m_aepExecuteTable[0x0436] = Exec_DD_CB_X_36;
	m_aepExecuteTable[0x0437] = Exec_DD_CB_X_37;
	m_aepExecuteTable[0x0438] = Exec_DD_CB_X_38;
	m_aepExecuteTable[0x0439] = Exec_DD_CB_X_39;
	m_aepExecuteTable[0x043A] = Exec_DD_CB_X_3A;
	m_aepExecuteTable[0x043B] = Exec_DD_CB_X_3B;
	m_aepExecuteTable[0x043C] = Exec_DD_CB_X_3C;
	m_aepExecuteTable[0x043D] = Exec_DD_CB_X_3D;
	m_aepExecuteTable[0x043E] = Exec_DD_CB_X_3E;
	m_aepExecuteTable[0x043F] = Exec_DD_CB_X_3F;
	m_aepExecuteTable[0x0440] = Exec_DD_CB_X_46_x;
	m_aepExecuteTable[0x0441] = Exec_DD_CB_X_46_x;
	m_aepExecuteTable[0x0442] = Exec_DD_CB_X_46_x;
	m_aepExecuteTable[0x0443] = Exec_DD_CB_X_46_x;
	m_aepExecuteTable[0x0444] = Exec_DD_CB_X_46_x;
	m_aepExecuteTable[0x0445] = Exec_DD_CB_X_46_x;
	m_aepExecuteTable[0x0446] = Exec_DD_CB_X_46_x;
	m_aepExecuteTable[0x0447] = Exec_DD_CB_X_46_x;
	m_aepExecuteTable[0x0448] = Exec_DD_CB_X_4E_x;
	m_aepExecuteTable[0x0449] = Exec_DD_CB_X_4E_x;
	m_aepExecuteTable[0x044A] = Exec_DD_CB_X_4E_x;
	m_aepExecuteTable[0x044B] = Exec_DD_CB_X_4E_x;
	m_aepExecuteTable[0x044C] = Exec_DD_CB_X_4E_x;
	m_aepExecuteTable[0x044D] = Exec_DD_CB_X_4E_x;
	m_aepExecuteTable[0x044E] = Exec_DD_CB_X_4E_x;
	m_aepExecuteTable[0x044F] = Exec_DD_CB_X_4E_x;
	m_aepExecuteTable[0x0450] = Exec_DD_CB_X_56_x;
	m_aepExecuteTable[0x0451] = Exec_DD_CB_X_56_x;
	m_aepExecuteTable[0x0452] = Exec_DD_CB_X_56_x;
	m_aepExecuteTable[0x0453] = Exec_DD_CB_X_56_x;
	m_aepExecuteTable[0x0454] = Exec_DD_CB_X_56_x;
	m_aepExecuteTable[0x0455] = Exec_DD_CB_X_56_x;
	m_aepExecuteTable[0x0456] = Exec_DD_CB_X_56_x;
	m_aepExecuteTable[0x0457] = Exec_DD_CB_X_56_x;
	m_aepExecuteTable[0x0458] = Exec_DD_CB_X_5E_x;
	m_aepExecuteTable[0x0459] = Exec_DD_CB_X_5E_x;
	m_aepExecuteTable[0x045A] = Exec_DD_CB_X_5E_x;
	m_aepExecuteTable[0x045B] = Exec_DD_CB_X_5E_x;
	m_aepExecuteTable[0x045C] = Exec_DD_CB_X_5E_x;
	m_aepExecuteTable[0x045D] = Exec_DD_CB_X_5E_x;
	m_aepExecuteTable[0x045E] = Exec_DD_CB_X_5E_x;
	m_aepExecuteTable[0x045F] = Exec_DD_CB_X_5E_x;
	m_aepExecuteTable[0x0460] = Exec_DD_CB_X_66_x;
	m_aepExecuteTable[0x0461] = Exec_DD_CB_X_66_x;
	m_aepExecuteTable[0x0462] = Exec_DD_CB_X_66_x;
	m_aepExecuteTable[0x0463] = Exec_DD_CB_X_66_x;
	m_aepExecuteTable[0x0464] = Exec_DD_CB_X_66_x;
	m_aepExecuteTable[0x0465] = Exec_DD_CB_X_66_x;
	m_aepExecuteTable[0x0466] = Exec_DD_CB_X_66_x;
	m_aepExecuteTable[0x0467] = Exec_DD_CB_X_66_x;
	m_aepExecuteTable[0x0468] = Exec_DD_CB_X_6E_x;
	m_aepExecuteTable[0x0469] = Exec_DD_CB_X_6E_x;
	m_aepExecuteTable[0x046A] = Exec_DD_CB_X_6E_x;
	m_aepExecuteTable[0x046B] = Exec_DD_CB_X_6E_x;
	m_aepExecuteTable[0x046C] = Exec_DD_CB_X_6E_x;
	m_aepExecuteTable[0x046D] = Exec_DD_CB_X_6E_x;
	m_aepExecuteTable[0x046E] = Exec_DD_CB_X_6E_x;
	m_aepExecuteTable[0x046F] = Exec_DD_CB_X_6E_x;
	m_aepExecuteTable[0x0470] = Exec_DD_CB_X_76_x;
	m_aepExecuteTable[0x0471] = Exec_DD_CB_X_76_x;
	m_aepExecuteTable[0x0472] = Exec_DD_CB_X_76_x;
	m_aepExecuteTable[0x0473] = Exec_DD_CB_X_76_x;
	m_aepExecuteTable[0x0474] = Exec_DD_CB_X_76_x;
	m_aepExecuteTable[0x0475] = Exec_DD_CB_X_76_x;
	m_aepExecuteTable[0x0476] = Exec_DD_CB_X_76_x;
	m_aepExecuteTable[0x0477] = Exec_DD_CB_X_76_x;
	m_aepExecuteTable[0x0478] = Exec_DD_CB_X_7E_x;
	m_aepExecuteTable[0x0479] = Exec_DD_CB_X_7E_x;
	m_aepExecuteTable[0x047A] = Exec_DD_CB_X_7E_x;
	m_aepExecuteTable[0x047B] = Exec_DD_CB_X_7E_x;
	m_aepExecuteTable[0x047C] = Exec_DD_CB_X_7E_x;
	m_aepExecuteTable[0x047D] = Exec_DD_CB_X_7E_x;
	m_aepExecuteTable[0x047E] = Exec_DD_CB_X_7E_x;
	m_aepExecuteTable[0x047F] = Exec_DD_CB_X_7E_x;
	m_aepExecuteTable[0x0480] = Exec_DD_CB_X_80;
	m_aepExecuteTable[0x0481] = Exec_DD_CB_X_81;
	m_aepExecuteTable[0x0482] = Exec_DD_CB_X_82;
	m_aepExecuteTable[0x0483] = Exec_DD_CB_X_83;
	m_aepExecuteTable[0x0484] = Exec_DD_CB_X_84;
	m_aepExecuteTable[0x0485] = Exec_DD_CB_X_85;
	m_aepExecuteTable[0x0486] = Exec_DD_CB_X_86;
	m_aepExecuteTable[0x0487] = Exec_DD_CB_X_87;
	m_aepExecuteTable[0x0488] = Exec_DD_CB_X_88;
	m_aepExecuteTable[0x0489] = Exec_DD_CB_X_89;
	m_aepExecuteTable[0x048A] = Exec_DD_CB_X_8A;
	m_aepExecuteTable[0x048B] = Exec_DD_CB_X_8B;
	m_aepExecuteTable[0x048C] = Exec_DD_CB_X_8C;
	m_aepExecuteTable[0x048D] = Exec_DD_CB_X_8D;
	m_aepExecuteTable[0x048E] = Exec_DD_CB_X_8E;
	m_aepExecuteTable[0x048F] = Exec_DD_CB_X_8F;
	m_aepExecuteTable[0x0490] = Exec_DD_CB_X_90;
	m_aepExecuteTable[0x0491] = Exec_DD_CB_X_91;
	m_aepExecuteTable[0x0492] = Exec_DD_CB_X_92;
	m_aepExecuteTable[0x0493] = Exec_DD_CB_X_93;
	m_aepExecuteTable[0x0494] = Exec_DD_CB_X_94;
	m_aepExecuteTable[0x0495] = Exec_DD_CB_X_95;
	m_aepExecuteTable[0x0496] = Exec_DD_CB_X_96;
	m_aepExecuteTable[0x0497] = Exec_DD_CB_X_97;
	m_aepExecuteTable[0x0498] = Exec_DD_CB_X_98;
	m_aepExecuteTable[0x0499] = Exec_DD_CB_X_99;
	m_aepExecuteTable[0x049A] = Exec_DD_CB_X_9A;
	m_aepExecuteTable[0x049B] = Exec_DD_CB_X_9B;
	m_aepExecuteTable[0x049C] = Exec_DD_CB_X_9C;
	m_aepExecuteTable[0x049D] = Exec_DD_CB_X_9D;
	m_aepExecuteTable[0x049E] = Exec_DD_CB_X_9E;
	m_aepExecuteTable[0x049F] = Exec_DD_CB_X_9F;
	m_aepExecuteTable[0x04A0] = Exec_DD_CB_X_A0;
	m_aepExecuteTable[0x04A1] = Exec_DD_CB_X_A1;
	m_aepExecuteTable[0x04A2] = Exec_DD_CB_X_A2;
	m_aepExecuteTable[0x04A3] = Exec_DD_CB_X_A3;
	m_aepExecuteTable[0x04A4] = Exec_DD_CB_X_A4;
	m_aepExecuteTable[0x04A5] = Exec_DD_CB_X_A5;
	m_aepExecuteTable[0x04A6] = Exec_DD_CB_X_A6;
	m_aepExecuteTable[0x04A7] = Exec_DD_CB_X_A7;
	m_aepExecuteTable[0x04A8] = Exec_DD_CB_X_A8;
	m_aepExecuteTable[0x04A9] = Exec_DD_CB_X_A9;
	m_aepExecuteTable[0x04AA] = Exec_DD_CB_X_AA;
	m_aepExecuteTable[0x04AB] = Exec_DD_CB_X_AB;
	m_aepExecuteTable[0x04AC] = Exec_DD_CB_X_AC;
	m_aepExecuteTable[0x04AD] = Exec_DD_CB_X_AD;
	m_aepExecuteTable[0x04AE] = Exec_DD_CB_X_AE;
	m_aepExecuteTable[0x04AF] = Exec_DD_CB_X_AF;
	m_aepExecuteTable[0x04B0] = Exec_DD_CB_X_B0;
	m_aepExecuteTable[0x04B1] = Exec_DD_CB_X_B1;
	m_aepExecuteTable[0x04B2] = Exec_DD_CB_X_B2;
	m_aepExecuteTable[0x04B3] = Exec_DD_CB_X_B3;
	m_aepExecuteTable[0x04B4] = Exec_DD_CB_X_B4;
	m_aepExecuteTable[0x04B5] = Exec_DD_CB_X_B5;
	m_aepExecuteTable[0x04B6] = Exec_DD_CB_X_B6;
	m_aepExecuteTable[0x04B7] = Exec_DD_CB_X_B7;
	m_aepExecuteTable[0x04B8] = Exec_DD_CB_X_B8;
	m_aepExecuteTable[0x04B9] = Exec_DD_CB_X_B9;
	m_aepExecuteTable[0x04BA] = Exec_DD_CB_X_BA;
	m_aepExecuteTable[0x04BB] = Exec_DD_CB_X_BB;
	m_aepExecuteTable[0x04BC] = Exec_DD_CB_X_BC;
	m_aepExecuteTable[0x04BD] = Exec_DD_CB_X_BD;
	m_aepExecuteTable[0x04BE] = Exec_DD_CB_X_BE;
	m_aepExecuteTable[0x04BF] = Exec_DD_CB_X_BF;
	m_aepExecuteTable[0x04C0] = Exec_DD_CB_X_C0;
	m_aepExecuteTable[0x04C1] = Exec_DD_CB_X_C1;
	m_aepExecuteTable[0x04C2] = Exec_DD_CB_X_C2;
	m_aepExecuteTable[0x04C3] = Exec_DD_CB_X_C3;
	m_aepExecuteTable[0x04C4] = Exec_DD_CB_X_C4;
	m_aepExecuteTable[0x04C5] = Exec_DD_CB_X_C5;
	m_aepExecuteTable[0x04C6] = Exec_DD_CB_X_C6;
	m_aepExecuteTable[0x04C7] = Exec_DD_CB_X_C7;
	m_aepExecuteTable[0x04C8] = Exec_DD_CB_X_C8;
	m_aepExecuteTable[0x04C9] = Exec_DD_CB_X_C9;
	m_aepExecuteTable[0x04CA] = Exec_DD_CB_X_CA;
	m_aepExecuteTable[0x04CB] = Exec_DD_CB_X_CB;
	m_aepExecuteTable[0x04CC] = Exec_DD_CB_X_CC;
	m_aepExecuteTable[0x04CD] = Exec_DD_CB_X_CD;
	m_aepExecuteTable[0x04CE] = Exec_DD_CB_X_CE;
	m_aepExecuteTable[0x04CF] = Exec_DD_CB_X_CF;
	m_aepExecuteTable[0x04D0] = Exec_DD_CB_X_D0;
	m_aepExecuteTable[0x04D1] = Exec_DD_CB_X_D1;
	m_aepExecuteTable[0x04D2] = Exec_DD_CB_X_D2;
	m_aepExecuteTable[0x04D3] = Exec_DD_CB_X_D3;
	m_aepExecuteTable[0x04D4] = Exec_DD_CB_X_D4;
	m_aepExecuteTable[0x04D5] = Exec_DD_CB_X_D5;
	m_aepExecuteTable[0x04D6] = Exec_DD_CB_X_D6;
	m_aepExecuteTable[0x04D7] = Exec_DD_CB_X_D7;
	m_aepExecuteTable[0x04D8] = Exec_DD_CB_X_D8;
	m_aepExecuteTable[0x04D9] = Exec_DD_CB_X_D9;
	m_aepExecuteTable[0x04DA] = Exec_DD_CB_X_DA;
	m_aepExecuteTable[0x04DB] = Exec_DD_CB_X_DB;
	m_aepExecuteTable[0x04DC] = Exec_DD_CB_X_DC;
	m_aepExecuteTable[0x04DD] = Exec_DD_CB_X_DD;
	m_aepExecuteTable[0x04DE] = Exec_DD_CB_X_DE;
	m_aepExecuteTable[0x04DF] = Exec_DD_CB_X_DF;
	m_aepExecuteTable[0x04E0] = Exec_DD_CB_X_E0;
	m_aepExecuteTable[0x04E1] = Exec_DD_CB_X_E1;
	m_aepExecuteTable[0x04E2] = Exec_DD_CB_X_E2;
	m_aepExecuteTable[0x04E3] = Exec_DD_CB_X_E3;
	m_aepExecuteTable[0x04E4] = Exec_DD_CB_X_E4;
	m_aepExecuteTable[0x04E5] = Exec_DD_CB_X_E5;
	m_aepExecuteTable[0x04E6] = Exec_DD_CB_X_E6;
	m_aepExecuteTable[0x04E7] = Exec_DD_CB_X_E7;
	m_aepExecuteTable[0x04E8] = Exec_DD_CB_X_E8;
	m_aepExecuteTable[0x04E9] = Exec_DD_CB_X_E9;
	m_aepExecuteTable[0x04EA] = Exec_DD_CB_X_EA;
	m_aepExecuteTable[0x04EB] = Exec_DD_CB_X_EB;
	m_aepExecuteTable[0x04EC] = Exec_DD_CB_X_EC;
	m_aepExecuteTable[0x04ED] = Exec_DD_CB_X_ED;
	m_aepExecuteTable[0x04EE] = Exec_DD_CB_X_EE;
	m_aepExecuteTable[0x04EF] = Exec_DD_CB_X_EF;
	m_aepExecuteTable[0x04F0] = Exec_DD_CB_X_F0;
	m_aepExecuteTable[0x04F1] = Exec_DD_CB_X_F1;
	m_aepExecuteTable[0x04F2] = Exec_DD_CB_X_F2;
	m_aepExecuteTable[0x04F3] = Exec_DD_CB_X_F3;
	m_aepExecuteTable[0x04F4] = Exec_DD_CB_X_F4;
	m_aepExecuteTable[0x04F5] = Exec_DD_CB_X_F5;
	m_aepExecuteTable[0x04F6] = Exec_DD_CB_X_F6;
	m_aepExecuteTable[0x04F7] = Exec_DD_CB_X_F7;
	m_aepExecuteTable[0x04F8] = Exec_DD_CB_X_F8;
	m_aepExecuteTable[0x04F9] = Exec_DD_CB_X_F9;
	m_aepExecuteTable[0x04FA] = Exec_DD_CB_X_FA;
	m_aepExecuteTable[0x04FB] = Exec_DD_CB_X_FB;
	m_aepExecuteTable[0x04FC] = Exec_DD_CB_X_FC;
	m_aepExecuteTable[0x04FD] = Exec_DD_CB_X_FD;
	m_aepExecuteTable[0x04FE] = Exec_DD_CB_X_FE;
	m_aepExecuteTable[0x04FF] = Exec_DD_CB_X_FF;
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Initialize_FD_X() {
	// Exec_FD_X
	m_aepExecuteTable[0x0500] = Exec_X_00;
	m_aepExecuteTable[0x0501] = Exec_X_01;
	m_aepExecuteTable[0x0502] = Exec_X_02;
	m_aepExecuteTable[0x0503] = Exec_X_03;
	m_aepExecuteTable[0x0504] = Exec_X_04;
	m_aepExecuteTable[0x0505] = Exec_X_05;
	m_aepExecuteTable[0x0506] = Exec_X_06;
	m_aepExecuteTable[0x0507] = Exec_X_07;
	m_aepExecuteTable[0x0508] = Exec_X_08;
	m_aepExecuteTable[0x0509] = Exec_FD_X_09;
	m_aepExecuteTable[0x050A] = Exec_X_0A;
	m_aepExecuteTable[0x050B] = Exec_X_0B;
	m_aepExecuteTable[0x050C] = Exec_X_0C;
	m_aepExecuteTable[0x050D] = Exec_X_0D;
	m_aepExecuteTable[0x050E] = Exec_X_0E;
	m_aepExecuteTable[0x050F] = Exec_X_0F;
	m_aepExecuteTable[0x0510] = Exec_X_10;
	m_aepExecuteTable[0x0511] = Exec_X_11;
	m_aepExecuteTable[0x0512] = Exec_X_12;
	m_aepExecuteTable[0x0513] = Exec_X_13;
	m_aepExecuteTable[0x0514] = Exec_X_14;
	m_aepExecuteTable[0x0515] = Exec_X_15;
	m_aepExecuteTable[0x0516] = Exec_X_16;
	m_aepExecuteTable[0x0517] = Exec_X_17;
	m_aepExecuteTable[0x0518] = Exec_X_18;
	m_aepExecuteTable[0x0519] = Exec_FD_X_19;
	m_aepExecuteTable[0x051A] = Exec_X_1A;
	m_aepExecuteTable[0x051B] = Exec_X_1B;
	m_aepExecuteTable[0x051C] = Exec_X_1C;
	m_aepExecuteTable[0x051D] = Exec_X_1D;
	m_aepExecuteTable[0x051E] = Exec_X_1E;
	m_aepExecuteTable[0x051F] = Exec_X_1F;
	m_aepExecuteTable[0x0520] = Exec_X_20;
	m_aepExecuteTable[0x0521] = Exec_FD_X_21;
	m_aepExecuteTable[0x0522] = Exec_FD_X_22;
	m_aepExecuteTable[0x0523] = Exec_FD_X_23;
	m_aepExecuteTable[0x0524] = Exec_FD_X_24;
	m_aepExecuteTable[0x0525] = Exec_FD_X_25;
	m_aepExecuteTable[0x0526] = Exec_FD_X_26;
	m_aepExecuteTable[0x0527] = Exec_X_27;
	m_aepExecuteTable[0x0528] = Exec_X_28;
	m_aepExecuteTable[0x0529] = Exec_FD_X_29;
	m_aepExecuteTable[0x052A] = Exec_FD_X_2A;
	m_aepExecuteTable[0x052B] = Exec_FD_X_2B;
	m_aepExecuteTable[0x052C] = Exec_FD_X_2C;
	m_aepExecuteTable[0x052D] = Exec_FD_X_2D;
	m_aepExecuteTable[0x052E] = Exec_FD_X_2E;
	m_aepExecuteTable[0x052F] = Exec_X_2F;
	m_aepExecuteTable[0x0530] = Exec_X_30;
	m_aepExecuteTable[0x0531] = Exec_X_31;
	m_aepExecuteTable[0x0532] = Exec_X_32;
	m_aepExecuteTable[0x0533] = Exec_X_33;
	m_aepExecuteTable[0x0534] = Exec_FD_X_34;
	m_aepExecuteTable[0x0535] = Exec_FD_X_35;
	m_aepExecuteTable[0x0536] = Exec_FD_X_36;
	m_aepExecuteTable[0x0537] = Exec_X_37;
	m_aepExecuteTable[0x0538] = Exec_X_38;
	m_aepExecuteTable[0x0539] = Exec_FD_X_39;
	m_aepExecuteTable[0x053A] = Exec_X_3A;
	m_aepExecuteTable[0x053B] = Exec_X_3B;
	m_aepExecuteTable[0x053C] = Exec_X_3C;
	m_aepExecuteTable[0x053D] = Exec_X_3D;
	m_aepExecuteTable[0x053E] = Exec_X_3E;
	m_aepExecuteTable[0x053F] = Exec_X_3F;
	m_aepExecuteTable[0x0540] = Exec_X_40;
	m_aepExecuteTable[0x0541] = Exec_X_41;
	m_aepExecuteTable[0x0542] = Exec_X_42;
	m_aepExecuteTable[0x0543] = Exec_X_43;
	m_aepExecuteTable[0x0544] = Exec_FD_X_44;
	m_aepExecuteTable[0x0545] = Exec_FD_X_45;
	m_aepExecuteTable[0x0546] = Exec_FD_X_46;
	m_aepExecuteTable[0x0547] = Exec_X_47;
	m_aepExecuteTable[0x0548] = Exec_X_48;
	m_aepExecuteTable[0x0549] = Exec_X_49;
	m_aepExecuteTable[0x054A] = Exec_X_4A;
	m_aepExecuteTable[0x054B] = Exec_X_4B;
	m_aepExecuteTable[0x054C] = Exec_FD_X_4C;
	m_aepExecuteTable[0x054D] = Exec_FD_X_4D;
	m_aepExecuteTable[0x054E] = Exec_FD_X_4E;
	m_aepExecuteTable[0x054F] = Exec_X_4F;
	m_aepExecuteTable[0x0550] = Exec_X_50;
	m_aepExecuteTable[0x0551] = Exec_X_51;
	m_aepExecuteTable[0x0552] = Exec_X_52;
	m_aepExecuteTable[0x0553] = Exec_X_53;
	m_aepExecuteTable[0x0554] = Exec_FD_X_54;
	m_aepExecuteTable[0x0555] = Exec_FD_X_55;
	m_aepExecuteTable[0x0556] = Exec_FD_X_56;
	m_aepExecuteTable[0x0557] = Exec_X_57;
	m_aepExecuteTable[0x0558] = Exec_X_58;
	m_aepExecuteTable[0x0559] = Exec_X_59;
	m_aepExecuteTable[0x055A] = Exec_X_5A;
	m_aepExecuteTable[0x055B] = Exec_X_5B;
	m_aepExecuteTable[0x055C] = Exec_FD_X_5C;
	m_aepExecuteTable[0x055D] = Exec_FD_X_5D;
	m_aepExecuteTable[0x055E] = Exec_FD_X_5E;
	m_aepExecuteTable[0x055F] = Exec_X_5F;
	m_aepExecuteTable[0x0560] = Exec_FD_X_60;
	m_aepExecuteTable[0x0561] = Exec_FD_X_61;
	m_aepExecuteTable[0x0562] = Exec_FD_X_62;
	m_aepExecuteTable[0x0563] = Exec_FD_X_63;
	m_aepExecuteTable[0x0564] = Exec_FD_X_64;
	m_aepExecuteTable[0x0565] = Exec_FD_X_65;
	m_aepExecuteTable[0x0566] = Exec_FD_X_66;
	m_aepExecuteTable[0x0567] = Exec_FD_X_67;
	m_aepExecuteTable[0x0568] = Exec_FD_X_68;
	m_aepExecuteTable[0x0569] = Exec_FD_X_69;
	m_aepExecuteTable[0x056A] = Exec_FD_X_6A;
	m_aepExecuteTable[0x056B] = Exec_FD_X_6B;
	m_aepExecuteTable[0x056C] = Exec_FD_X_6C;
	m_aepExecuteTable[0x056D] = Exec_FD_X_6D;
	m_aepExecuteTable[0x056E] = Exec_FD_X_6E;
	m_aepExecuteTable[0x056F] = Exec_FD_X_6F;
	m_aepExecuteTable[0x0570] = Exec_FD_X_70;
	m_aepExecuteTable[0x0571] = Exec_FD_X_71;
	m_aepExecuteTable[0x0572] = Exec_FD_X_72;
	m_aepExecuteTable[0x0573] = Exec_FD_X_73;
	m_aepExecuteTable[0x0574] = Exec_FD_X_74;
	m_aepExecuteTable[0x0575] = Exec_FD_X_75;
	m_aepExecuteTable[0x0576] = Exec_X_76;
	m_aepExecuteTable[0x0577] = Exec_FD_X_77;
	m_aepExecuteTable[0x0578] = Exec_X_78;
	m_aepExecuteTable[0x0579] = Exec_X_79;
	m_aepExecuteTable[0x057A] = Exec_X_7A;
	m_aepExecuteTable[0x057B] = Exec_X_7B;
	m_aepExecuteTable[0x057C] = Exec_FD_X_7C;
	m_aepExecuteTable[0x057D] = Exec_FD_X_7D;
	m_aepExecuteTable[0x057E] = Exec_FD_X_7E;
	m_aepExecuteTable[0x057F] = Exec_X_7F;
	m_aepExecuteTable[0x0580] = Exec_X_80;
	m_aepExecuteTable[0x0581] = Exec_X_81;
	m_aepExecuteTable[0x0582] = Exec_X_82;
	m_aepExecuteTable[0x0583] = Exec_X_83;
	m_aepExecuteTable[0x0584] = Exec_FD_X_84;
	m_aepExecuteTable[0x0585] = Exec_FD_X_85;
	m_aepExecuteTable[0x0586] = Exec_FD_X_86;
	m_aepExecuteTable[0x0587] = Exec_X_87;
	m_aepExecuteTable[0x0588] = Exec_X_88;
	m_aepExecuteTable[0x0589] = Exec_X_89;
	m_aepExecuteTable[0x058A] = Exec_X_8A;
	m_aepExecuteTable[0x058B] = Exec_X_8B;
	m_aepExecuteTable[0x058C] = Exec_FD_X_8C;
	m_aepExecuteTable[0x058D] = Exec_FD_X_8D;
	m_aepExecuteTable[0x058E] = Exec_FD_X_8E;
	m_aepExecuteTable[0x058F] = Exec_X_8F;
	m_aepExecuteTable[0x0590] = Exec_X_90;
	m_aepExecuteTable[0x0591] = Exec_X_91;
	m_aepExecuteTable[0x0592] = Exec_X_92;
	m_aepExecuteTable[0x0593] = Exec_X_93;
	m_aepExecuteTable[0x0594] = Exec_FD_X_94;
	m_aepExecuteTable[0x0595] = Exec_FD_X_95;
	m_aepExecuteTable[0x0596] = Exec_FD_X_96;
	m_aepExecuteTable[0x0597] = Exec_X_97;
	m_aepExecuteTable[0x0598] = Exec_X_98;
	m_aepExecuteTable[0x0599] = Exec_X_99;
	m_aepExecuteTable[0x059A] = Exec_X_9A;
	m_aepExecuteTable[0x059B] = Exec_X_9B;
	m_aepExecuteTable[0x059C] = Exec_FD_X_9C;
	m_aepExecuteTable[0x059D] = Exec_FD_X_9D;
	m_aepExecuteTable[0x059E] = Exec_FD_X_9E;
	m_aepExecuteTable[0x059F] = Exec_X_9F;
	m_aepExecuteTable[0x05A0] = Exec_X_A0;
	m_aepExecuteTable[0x05A1] = Exec_X_A1;
	m_aepExecuteTable[0x05A2] = Exec_X_A2;
	m_aepExecuteTable[0x05A3] = Exec_X_A3;
	m_aepExecuteTable[0x05A4] = Exec_FD_X_A4;
	m_aepExecuteTable[0x05A5] = Exec_FD_X_A5;
	m_aepExecuteTable[0x05A6] = Exec_FD_X_A6;
	m_aepExecuteTable[0x05A7] = Exec_X_A7;
	m_aepExecuteTable[0x05A8] = Exec_X_A8;
	m_aepExecuteTable[0x05A9] = Exec_X_A9;
	m_aepExecuteTable[0x05AA] = Exec_X_AA;
	m_aepExecuteTable[0x05AB] = Exec_X_AB;
	m_aepExecuteTable[0x05AC] = Exec_FD_X_AC;
	m_aepExecuteTable[0x05AD] = Exec_FD_X_AD;
	m_aepExecuteTable[0x05AE] = Exec_FD_X_AE;
	m_aepExecuteTable[0x05AF] = Exec_X_AF;
	m_aepExecuteTable[0x05B0] = Exec_X_B0;
	m_aepExecuteTable[0x05B1] = Exec_X_B1;
	m_aepExecuteTable[0x05B2] = Exec_X_B2;
	m_aepExecuteTable[0x05B3] = Exec_X_B3;
	m_aepExecuteTable[0x05B4] = Exec_FD_X_B4;
	m_aepExecuteTable[0x05B5] = Exec_FD_X_B5;
	m_aepExecuteTable[0x05B6] = Exec_FD_X_B6;
	m_aepExecuteTable[0x05B7] = Exec_X_B7;
	m_aepExecuteTable[0x05B8] = Exec_X_B8;
	m_aepExecuteTable[0x05B9] = Exec_X_B9;
	m_aepExecuteTable[0x05BA] = Exec_X_BA;
	m_aepExecuteTable[0x05BB] = Exec_X_BB;
	m_aepExecuteTable[0x05BC] = Exec_FD_X_BC;
	m_aepExecuteTable[0x05BD] = Exec_FD_X_BD;
	m_aepExecuteTable[0x05BE] = Exec_FD_X_BE;
	m_aepExecuteTable[0x05BF] = Exec_X_BF;
	m_aepExecuteTable[0x05C0] = Exec_X_C0;
	m_aepExecuteTable[0x05C1] = Exec_X_C1;
	m_aepExecuteTable[0x05C2] = Exec_X_C2;
	m_aepExecuteTable[0x05C3] = Exec_X_C3;
	m_aepExecuteTable[0x05C4] = Exec_X_C4;
	m_aepExecuteTable[0x05C5] = Exec_X_C5;
	m_aepExecuteTable[0x05C6] = Exec_X_C6;
	m_aepExecuteTable[0x05C7] = Exec_X_C7;
	m_aepExecuteTable[0x05C8] = Exec_X_C8;
	m_aepExecuteTable[0x05C9] = Exec_X_C9;
	m_aepExecuteTable[0x05CA] = Exec_X_CA;
	m_aepExecuteTable[0x05CB] = Exec_FD_X_CB;
	m_aepExecuteTable[0x05CC] = Exec_X_CC;
	m_aepExecuteTable[0x05CD] = Exec_X_CD;
	m_aepExecuteTable[0x05CE] = Exec_X_CE;
	m_aepExecuteTable[0x05CF] = Exec_X_CF;
	m_aepExecuteTable[0x05D0] = Exec_X_D0;
	m_aepExecuteTable[0x05D1] = Exec_X_D1;
	m_aepExecuteTable[0x05D2] = Exec_X_D2;
	m_aepExecuteTable[0x05D3] = Exec_X_D3;
	m_aepExecuteTable[0x05D4] = Exec_X_D4;
	m_aepExecuteTable[0x05D5] = Exec_X_D5;
	m_aepExecuteTable[0x05D6] = Exec_X_D6;
	m_aepExecuteTable[0x05D7] = Exec_X_D7;
	m_aepExecuteTable[0x05D8] = Exec_X_D8;
	m_aepExecuteTable[0x05D9] = Exec_X_D9;
	m_aepExecuteTable[0x05DA] = Exec_X_DA;
	m_aepExecuteTable[0x05DB] = Exec_X_DB;
	m_aepExecuteTable[0x05DC] = Exec_X_DC;
	m_aepExecuteTable[0x05DD] = Exec_X_DD;
	m_aepExecuteTable[0x05DE] = Exec_X_DE;
	m_aepExecuteTable[0x05DF] = Exec_X_DF;
	m_aepExecuteTable[0x05E0] = Exec_X_E0;
	m_aepExecuteTable[0x05E1] = Exec_FD_X_E1;
	m_aepExecuteTable[0x05E2] = Exec_X_E2;
	m_aepExecuteTable[0x05E3] = Exec_FD_X_E3;
	m_aepExecuteTable[0x05E4] = Exec_X_E4;
	m_aepExecuteTable[0x05E5] = Exec_FD_X_E5;
	m_aepExecuteTable[0x05E6] = Exec_X_E6;
	m_aepExecuteTable[0x05E7] = Exec_X_E7;
	m_aepExecuteTable[0x05E8] = Exec_X_E8;
	m_aepExecuteTable[0x05E9] = Exec_FD_X_E9;
	m_aepExecuteTable[0x05EA] = Exec_X_EA;
	m_aepExecuteTable[0x05EB] = Exec_X_EB;
	m_aepExecuteTable[0x05EC] = Exec_X_EC;
	m_aepExecuteTable[0x05ED] = Exec_X_ED;
	m_aepExecuteTable[0x05EE] = Exec_X_EE;
	m_aepExecuteTable[0x05EF] = Exec_X_EF;
	m_aepExecuteTable[0x05F0] = Exec_X_F0;
	m_aepExecuteTable[0x05F1] = Exec_X_F1;
	m_aepExecuteTable[0x05F2] = Exec_X_F2;
	m_aepExecuteTable[0x05F3] = Exec_X_F3;
	m_aepExecuteTable[0x05F4] = Exec_X_F4;
	m_aepExecuteTable[0x05F5] = Exec_X_F5;
	m_aepExecuteTable[0x05F6] = Exec_X_F6;
	m_aepExecuteTable[0x05F7] = Exec_X_F7;
	m_aepExecuteTable[0x05F8] = Exec_X_F8;
	m_aepExecuteTable[0x05F9] = Exec_FD_X_F9;
	m_aepExecuteTable[0x05FA] = Exec_X_FA;
	m_aepExecuteTable[0x05FB] = Exec_X_FB;
	m_aepExecuteTable[0x05FC] = Exec_X_FC;
	m_aepExecuteTable[0x05FD] = Exec_X_FD;
	m_aepExecuteTable[0x05FE] = Exec_X_FE;
	m_aepExecuteTable[0x05FF] = Exec_X_FF;
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Initialize_FD_CB_X() {
	// Exec_FD_CB_X
	m_aepExecuteTable[0x0600] = Exec_FD_CB_X_00;
	m_aepExecuteTable[0x0601] = Exec_FD_CB_X_01;
	m_aepExecuteTable[0x0602] = Exec_FD_CB_X_02;
	m_aepExecuteTable[0x0603] = Exec_FD_CB_X_03;
	m_aepExecuteTable[0x0604] = Exec_FD_CB_X_04;
	m_aepExecuteTable[0x0605] = Exec_FD_CB_X_05;
	m_aepExecuteTable[0x0606] = Exec_FD_CB_X_06;
	m_aepExecuteTable[0x0607] = Exec_FD_CB_X_07;
	m_aepExecuteTable[0x0608] = Exec_FD_CB_X_08;
	m_aepExecuteTable[0x0609] = Exec_FD_CB_X_09;
	m_aepExecuteTable[0x060A] = Exec_FD_CB_X_0A;
	m_aepExecuteTable[0x060B] = Exec_FD_CB_X_0B;
	m_aepExecuteTable[0x060C] = Exec_FD_CB_X_0C;
	m_aepExecuteTable[0x060D] = Exec_FD_CB_X_0D;
	m_aepExecuteTable[0x060E] = Exec_FD_CB_X_0E;
	m_aepExecuteTable[0x060F] = Exec_FD_CB_X_0F;
	m_aepExecuteTable[0x0610] = Exec_FD_CB_X_10;
	m_aepExecuteTable[0x0611] = Exec_FD_CB_X_11;
	m_aepExecuteTable[0x0612] = Exec_FD_CB_X_12;
	m_aepExecuteTable[0x0613] = Exec_FD_CB_X_13;
	m_aepExecuteTable[0x0614] = Exec_FD_CB_X_14;
	m_aepExecuteTable[0x0615] = Exec_FD_CB_X_15;
	m_aepExecuteTable[0x0616] = Exec_FD_CB_X_16;
	m_aepExecuteTable[0x0617] = Exec_FD_CB_X_17;
	m_aepExecuteTable[0x0618] = Exec_FD_CB_X_18;
	m_aepExecuteTable[0x0619] = Exec_FD_CB_X_19;
	m_aepExecuteTable[0x061A] = Exec_FD_CB_X_1A;
	m_aepExecuteTable[0x061B] = Exec_FD_CB_X_1B;
	m_aepExecuteTable[0x061C] = Exec_FD_CB_X_1C;
	m_aepExecuteTable[0x061D] = Exec_FD_CB_X_1D;
	m_aepExecuteTable[0x061E] = Exec_FD_CB_X_1E;
	m_aepExecuteTable[0x061F] = Exec_FD_CB_X_1F;
	m_aepExecuteTable[0x0620] = Exec_FD_CB_X_20;
	m_aepExecuteTable[0x0621] = Exec_FD_CB_X_21;
	m_aepExecuteTable[0x0622] = Exec_FD_CB_X_22;
	m_aepExecuteTable[0x0623] = Exec_FD_CB_X_23;
	m_aepExecuteTable[0x0624] = Exec_FD_CB_X_24;
	m_aepExecuteTable[0x0625] = Exec_FD_CB_X_25;
	m_aepExecuteTable[0x0626] = Exec_FD_CB_X_26;
	m_aepExecuteTable[0x0627] = Exec_FD_CB_X_27;
	m_aepExecuteTable[0x0628] = Exec_FD_CB_X_28;
	m_aepExecuteTable[0x0629] = Exec_FD_CB_X_29;
	m_aepExecuteTable[0x062A] = Exec_FD_CB_X_2A;
	m_aepExecuteTable[0x062B] = Exec_FD_CB_X_2B;
	m_aepExecuteTable[0x062C] = Exec_FD_CB_X_2C;
	m_aepExecuteTable[0x062D] = Exec_FD_CB_X_2D;
	m_aepExecuteTable[0x062E] = Exec_FD_CB_X_2E;
	m_aepExecuteTable[0x062F] = Exec_FD_CB_X_2F;
	m_aepExecuteTable[0x0630] = Exec_FD_CB_X_30;
	m_aepExecuteTable[0x0631] = Exec_FD_CB_X_31;
	m_aepExecuteTable[0x0632] = Exec_FD_CB_X_32;
	m_aepExecuteTable[0x0633] = Exec_FD_CB_X_33;
	m_aepExecuteTable[0x0634] = Exec_FD_CB_X_34;
	m_aepExecuteTable[0x0635] = Exec_FD_CB_X_35;
	m_aepExecuteTable[0x0636] = Exec_FD_CB_X_36;
	m_aepExecuteTable[0x0637] = Exec_FD_CB_X_37;
	m_aepExecuteTable[0x0638] = Exec_FD_CB_X_38;
	m_aepExecuteTable[0x0639] = Exec_FD_CB_X_39;
	m_aepExecuteTable[0x063A] = Exec_FD_CB_X_3A;
	m_aepExecuteTable[0x063B] = Exec_FD_CB_X_3B;
	m_aepExecuteTable[0x063C] = Exec_FD_CB_X_3C;
	m_aepExecuteTable[0x063D] = Exec_FD_CB_X_3D;
	m_aepExecuteTable[0x063E] = Exec_FD_CB_X_3E;
	m_aepExecuteTable[0x063F] = Exec_FD_CB_X_3F;
	m_aepExecuteTable[0x0640] = Exec_FD_CB_X_46_x;
	m_aepExecuteTable[0x0641] = Exec_FD_CB_X_46_x;
	m_aepExecuteTable[0x0642] = Exec_FD_CB_X_46_x;
	m_aepExecuteTable[0x0643] = Exec_FD_CB_X_46_x;
	m_aepExecuteTable[0x0644] = Exec_FD_CB_X_46_x;
	m_aepExecuteTable[0x0645] = Exec_FD_CB_X_46_x;
	m_aepExecuteTable[0x0646] = Exec_FD_CB_X_46_x;
	m_aepExecuteTable[0x0647] = Exec_FD_CB_X_46_x;
	m_aepExecuteTable[0x0648] = Exec_FD_CB_X_4E_x;
	m_aepExecuteTable[0x0649] = Exec_FD_CB_X_4E_x;
	m_aepExecuteTable[0x064A] = Exec_FD_CB_X_4E_x;
	m_aepExecuteTable[0x064B] = Exec_FD_CB_X_4E_x;
	m_aepExecuteTable[0x064C] = Exec_FD_CB_X_4E_x;
	m_aepExecuteTable[0x064D] = Exec_FD_CB_X_4E_x;
	m_aepExecuteTable[0x064E] = Exec_FD_CB_X_4E_x;
	m_aepExecuteTable[0x064F] = Exec_FD_CB_X_4E_x;
	m_aepExecuteTable[0x0650] = Exec_FD_CB_X_56_x;
	m_aepExecuteTable[0x0651] = Exec_FD_CB_X_56_x;
	m_aepExecuteTable[0x0652] = Exec_FD_CB_X_56_x;
	m_aepExecuteTable[0x0653] = Exec_FD_CB_X_56_x;
	m_aepExecuteTable[0x0654] = Exec_FD_CB_X_56_x;
	m_aepExecuteTable[0x0655] = Exec_FD_CB_X_56_x;
	m_aepExecuteTable[0x0656] = Exec_FD_CB_X_56_x;
	m_aepExecuteTable[0x0657] = Exec_FD_CB_X_56_x;
	m_aepExecuteTable[0x0658] = Exec_FD_CB_X_5E_x;
	m_aepExecuteTable[0x0659] = Exec_FD_CB_X_5E_x;
	m_aepExecuteTable[0x065A] = Exec_FD_CB_X_5E_x;
	m_aepExecuteTable[0x065B] = Exec_FD_CB_X_5E_x;
	m_aepExecuteTable[0x065C] = Exec_FD_CB_X_5E_x;
	m_aepExecuteTable[0x065D] = Exec_FD_CB_X_5E_x;
	m_aepExecuteTable[0x065E] = Exec_FD_CB_X_5E_x;
	m_aepExecuteTable[0x065F] = Exec_FD_CB_X_5E_x;
	m_aepExecuteTable[0x0660] = Exec_FD_CB_X_66_x;
	m_aepExecuteTable[0x0661] = Exec_FD_CB_X_66_x;
	m_aepExecuteTable[0x0662] = Exec_FD_CB_X_66_x;
	m_aepExecuteTable[0x0663] = Exec_FD_CB_X_66_x;
	m_aepExecuteTable[0x0664] = Exec_FD_CB_X_66_x;
	m_aepExecuteTable[0x0665] = Exec_FD_CB_X_66_x;
	m_aepExecuteTable[0x0666] = Exec_FD_CB_X_66_x;
	m_aepExecuteTable[0x0667] = Exec_FD_CB_X_66_x;
	m_aepExecuteTable[0x0668] = Exec_FD_CB_X_6E_x;
	m_aepExecuteTable[0x0669] = Exec_FD_CB_X_6E_x;
	m_aepExecuteTable[0x066A] = Exec_FD_CB_X_6E_x;
	m_aepExecuteTable[0x066B] = Exec_FD_CB_X_6E_x;
	m_aepExecuteTable[0x066C] = Exec_FD_CB_X_6E_x;
	m_aepExecuteTable[0x066D] = Exec_FD_CB_X_6E_x;
	m_aepExecuteTable[0x066E] = Exec_FD_CB_X_6E_x;
	m_aepExecuteTable[0x066F] = Exec_FD_CB_X_6E_x;
	m_aepExecuteTable[0x0670] = Exec_FD_CB_X_76_x;
	m_aepExecuteTable[0x0671] = Exec_FD_CB_X_76_x;
	m_aepExecuteTable[0x0672] = Exec_FD_CB_X_76_x;
	m_aepExecuteTable[0x0673] = Exec_FD_CB_X_76_x;
	m_aepExecuteTable[0x0674] = Exec_FD_CB_X_76_x;
	m_aepExecuteTable[0x0675] = Exec_FD_CB_X_76_x;
	m_aepExecuteTable[0x0676] = Exec_FD_CB_X_76_x;
	m_aepExecuteTable[0x0677] = Exec_FD_CB_X_76_x;
	m_aepExecuteTable[0x0678] = Exec_FD_CB_X_7E_x;
	m_aepExecuteTable[0x0679] = Exec_FD_CB_X_7E_x;
	m_aepExecuteTable[0x067A] = Exec_FD_CB_X_7E_x;
	m_aepExecuteTable[0x067B] = Exec_FD_CB_X_7E_x;
	m_aepExecuteTable[0x067C] = Exec_FD_CB_X_7E_x;
	m_aepExecuteTable[0x067D] = Exec_FD_CB_X_7E_x;
	m_aepExecuteTable[0x067E] = Exec_FD_CB_X_7E_x;
	m_aepExecuteTable[0x067F] = Exec_FD_CB_X_7E_x;
	m_aepExecuteTable[0x0680] = Exec_FD_CB_X_80;
	m_aepExecuteTable[0x0681] = Exec_FD_CB_X_81;
	m_aepExecuteTable[0x0682] = Exec_FD_CB_X_82;
	m_aepExecuteTable[0x0683] = Exec_FD_CB_X_83;
	m_aepExecuteTable[0x0684] = Exec_FD_CB_X_84;
	m_aepExecuteTable[0x0685] = Exec_FD_CB_X_85;
	m_aepExecuteTable[0x0686] = Exec_FD_CB_X_86;
	m_aepExecuteTable[0x0687] = Exec_FD_CB_X_87;
	m_aepExecuteTable[0x0688] = Exec_FD_CB_X_88;
	m_aepExecuteTable[0x0689] = Exec_FD_CB_X_89;
	m_aepExecuteTable[0x068A] = Exec_FD_CB_X_8A;
	m_aepExecuteTable[0x068B] = Exec_FD_CB_X_8B;
	m_aepExecuteTable[0x068C] = Exec_FD_CB_X_8C;
	m_aepExecuteTable[0x068D] = Exec_FD_CB_X_8D;
	m_aepExecuteTable[0x068E] = Exec_FD_CB_X_8E;
	m_aepExecuteTable[0x068F] = Exec_FD_CB_X_8F;
	m_aepExecuteTable[0x0690] = Exec_FD_CB_X_90;
	m_aepExecuteTable[0x0691] = Exec_FD_CB_X_91;
	m_aepExecuteTable[0x0692] = Exec_FD_CB_X_92;
	m_aepExecuteTable[0x0693] = Exec_FD_CB_X_93;
	m_aepExecuteTable[0x0694] = Exec_FD_CB_X_94;
	m_aepExecuteTable[0x0695] = Exec_FD_CB_X_95;
	m_aepExecuteTable[0x0696] = Exec_FD_CB_X_96;
	m_aepExecuteTable[0x0697] = Exec_FD_CB_X_97;
	m_aepExecuteTable[0x0698] = Exec_FD_CB_X_98;
	m_aepExecuteTable[0x0699] = Exec_FD_CB_X_99;
	m_aepExecuteTable[0x069A] = Exec_FD_CB_X_9A;
	m_aepExecuteTable[0x069B] = Exec_FD_CB_X_9B;
	m_aepExecuteTable[0x069C] = Exec_FD_CB_X_9C;
	m_aepExecuteTable[0x069D] = Exec_FD_CB_X_9D;
	m_aepExecuteTable[0x069E] = Exec_FD_CB_X_9E;
	m_aepExecuteTable[0x069F] = Exec_FD_CB_X_9F;
	m_aepExecuteTable[0x06A0] = Exec_FD_CB_X_A0;
	m_aepExecuteTable[0x06A1] = Exec_FD_CB_X_A1;
	m_aepExecuteTable[0x06A2] = Exec_FD_CB_X_A2;
	m_aepExecuteTable[0x06A3] = Exec_FD_CB_X_A3;
	m_aepExecuteTable[0x06A4] = Exec_FD_CB_X_A4;
	m_aepExecuteTable[0x06A5] = Exec_FD_CB_X_A5;
	m_aepExecuteTable[0x06A6] = Exec_FD_CB_X_A6;
	m_aepExecuteTable[0x06A7] = Exec_FD_CB_X_A7;
	m_aepExecuteTable[0x06A8] = Exec_FD_CB_X_A8;
	m_aepExecuteTable[0x06A9] = Exec_FD_CB_X_A9;
	m_aepExecuteTable[0x06AA] = Exec_FD_CB_X_AA;
	m_aepExecuteTable[0x06AB] = Exec_FD_CB_X_AB;
	m_aepExecuteTable[0x06AC] = Exec_FD_CB_X_AC;
	m_aepExecuteTable[0x06AD] = Exec_FD_CB_X_AD;
	m_aepExecuteTable[0x06AE] = Exec_FD_CB_X_AE;
	m_aepExecuteTable[0x06AF] = Exec_FD_CB_X_AF;
	m_aepExecuteTable[0x06B0] = Exec_FD_CB_X_B0;
	m_aepExecuteTable[0x06B1] = Exec_FD_CB_X_B1;
	m_aepExecuteTable[0x06B2] = Exec_FD_CB_X_B2;
	m_aepExecuteTable[0x06B3] = Exec_FD_CB_X_B3;
	m_aepExecuteTable[0x06B4] = Exec_FD_CB_X_B4;
	m_aepExecuteTable[0x06B5] = Exec_FD_CB_X_B5;
	m_aepExecuteTable[0x06B6] = Exec_FD_CB_X_B6;
	m_aepExecuteTable[0x06B7] = Exec_FD_CB_X_B7;
	m_aepExecuteTable[0x06B8] = Exec_FD_CB_X_B8;
	m_aepExecuteTable[0x06B9] = Exec_FD_CB_X_B9;
	m_aepExecuteTable[0x06BA] = Exec_FD_CB_X_BA;
	m_aepExecuteTable[0x06BB] = Exec_FD_CB_X_BB;
	m_aepExecuteTable[0x06BC] = Exec_FD_CB_X_BC;
	m_aepExecuteTable[0x06BD] = Exec_FD_CB_X_BD;
	m_aepExecuteTable[0x06BE] = Exec_FD_CB_X_BE;
	m_aepExecuteTable[0x06BF] = Exec_FD_CB_X_BF;
	m_aepExecuteTable[0x06C0] = Exec_FD_CB_X_C0;
	m_aepExecuteTable[0x06C1] = Exec_FD_CB_X_C1;
	m_aepExecuteTable[0x06C2] = Exec_FD_CB_X_C2;
	m_aepExecuteTable[0x06C3] = Exec_FD_CB_X_C3;
	m_aepExecuteTable[0x06C4] = Exec_FD_CB_X_C4;
	m_aepExecuteTable[0x06C5] = Exec_FD_CB_X_C5;
	m_aepExecuteTable[0x06C6] = Exec_FD_CB_X_C6;
	m_aepExecuteTable[0x06C7] = Exec_FD_CB_X_C7;
	m_aepExecuteTable[0x06C8] = Exec_FD_CB_X_C8;
	m_aepExecuteTable[0x06C9] = Exec_FD_CB_X_C9;
	m_aepExecuteTable[0x06CA] = Exec_FD_CB_X_CA;
	m_aepExecuteTable[0x06CB] = Exec_FD_CB_X_CB;
	m_aepExecuteTable[0x06CC] = Exec_FD_CB_X_CC;
	m_aepExecuteTable[0x06CD] = Exec_FD_CB_X_CD;
	m_aepExecuteTable[0x06CE] = Exec_FD_CB_X_CE;
	m_aepExecuteTable[0x06CF] = Exec_FD_CB_X_CF;
	m_aepExecuteTable[0x06D0] = Exec_FD_CB_X_D0;
	m_aepExecuteTable[0x06D1] = Exec_FD_CB_X_D1;
	m_aepExecuteTable[0x06D2] = Exec_FD_CB_X_D2;
	m_aepExecuteTable[0x06D3] = Exec_FD_CB_X_D3;
	m_aepExecuteTable[0x06D4] = Exec_FD_CB_X_D4;
	m_aepExecuteTable[0x06D5] = Exec_FD_CB_X_D5;
	m_aepExecuteTable[0x06D6] = Exec_FD_CB_X_D6;
	m_aepExecuteTable[0x06D7] = Exec_FD_CB_X_D7;
	m_aepExecuteTable[0x06D8] = Exec_FD_CB_X_D8;
	m_aepExecuteTable[0x06D9] = Exec_FD_CB_X_D9;
	m_aepExecuteTable[0x06DA] = Exec_FD_CB_X_DA;
	m_aepExecuteTable[0x06DB] = Exec_FD_CB_X_DB;
	m_aepExecuteTable[0x06DC] = Exec_FD_CB_X_DC;
	m_aepExecuteTable[0x06DD] = Exec_FD_CB_X_DD;
	m_aepExecuteTable[0x06DE] = Exec_FD_CB_X_DE;
	m_aepExecuteTable[0x06DF] = Exec_FD_CB_X_DF;
	m_aepExecuteTable[0x06E0] = Exec_FD_CB_X_E0;
	m_aepExecuteTable[0x06E1] = Exec_FD_CB_X_E1;
	m_aepExecuteTable[0x06E2] = Exec_FD_CB_X_E2;
	m_aepExecuteTable[0x06E3] = Exec_FD_CB_X_E3;
	m_aepExecuteTable[0x06E4] = Exec_FD_CB_X_E4;
	m_aepExecuteTable[0x06E5] = Exec_FD_CB_X_E5;
	m_aepExecuteTable[0x06E6] = Exec_FD_CB_X_E6;
	m_aepExecuteTable[0x06E7] = Exec_FD_CB_X_E7;
	m_aepExecuteTable[0x06E8] = Exec_FD_CB_X_E8;
	m_aepExecuteTable[0x06E9] = Exec_FD_CB_X_E9;
	m_aepExecuteTable[0x06EA] = Exec_FD_CB_X_EA;
	m_aepExecuteTable[0x06EB] = Exec_FD_CB_X_EB;
	m_aepExecuteTable[0x06EC] = Exec_FD_CB_X_EC;
	m_aepExecuteTable[0x06ED] = Exec_FD_CB_X_ED;
	m_aepExecuteTable[0x06EE] = Exec_FD_CB_X_EE;
	m_aepExecuteTable[0x06EF] = Exec_FD_CB_X_EF;
	m_aepExecuteTable[0x06F0] = Exec_FD_CB_X_F0;
	m_aepExecuteTable[0x06F1] = Exec_FD_CB_X_F1;
	m_aepExecuteTable[0x06F2] = Exec_FD_CB_X_F2;
	m_aepExecuteTable[0x06F3] = Exec_FD_CB_X_F3;
	m_aepExecuteTable[0x06F4] = Exec_FD_CB_X_F4;
	m_aepExecuteTable[0x06F5] = Exec_FD_CB_X_F5;
	m_aepExecuteTable[0x06F6] = Exec_FD_CB_X_F6;
	m_aepExecuteTable[0x06F7] = Exec_FD_CB_X_F7;
	m_aepExecuteTable[0x06F8] = Exec_FD_CB_X_F8;
	m_aepExecuteTable[0x06F9] = Exec_FD_CB_X_F9;
	m_aepExecuteTable[0x06FA] = Exec_FD_CB_X_FA;
	m_aepExecuteTable[0x06FB] = Exec_FD_CB_X_FB;
	m_aepExecuteTable[0x06FC] = Exec_FD_CB_X_FC;
	m_aepExecuteTable[0x06FD] = Exec_FD_CB_X_FD;
	m_aepExecuteTable[0x06FE] = Exec_FD_CB_X_FE;
	m_aepExecuteTable[0x06FF] = Exec_FD_CB_X_FF;
}

Z80TEMPLATE_EXPLICIT_AW
void CZ80Executor2::Initialize() {
	//m_aepExecuteTable = (EXECPROC*)ps_malloc(256*7);
	Initialize_X();
	Initialize_CB_X();
	Initialize_ED_X();
	Initialize_DD_X();
	Initialize_DD_CB_X();
	Initialize_FD_X();
	Initialize_FD_CB_X();
}

#endif // Z80ExecutorBase2_DEFINED
