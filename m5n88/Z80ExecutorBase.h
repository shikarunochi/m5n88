////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80ExecutorBase_DEFINED
#define Z80ExecutorBase_DEFINED

////////////////////////////////////////////////////////////
// TZ80ExecutorBase

template <
	class TZ,
	class TB,
	class TR, class TCR, class TRP, class TCRP>
class TZ80ExecutorBase {
// typedef
protected:
	typedef TZ TTZ80;
	typedef TB TBOOL;
	typedef TR TREGREF;
	typedef TCR TCREGREF;
	typedef TRP TREGPREF;
	typedef TCRP TCREGPREF;

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

// attribute
protected:
	TTZ80* m_pz80;

public:
	TTZ80& Z80() {
		return *m_pz80;
	}

// construct/destruct
public:
	TZ80ExecutorBase(TTZ80& z80) :
		m_pz80(&z80)
	{
	}
	TZ80ExecutorBase(const TZ80ExecutorBase& z80eb) :
		m_pz80(z80eb.m_pz80)
	{
	}

// execute
public:
	int ExecuteOneOpCode() {
		SetExecClock(0);
		CopyEnableInterrupt();
		uint8_t btX;
		FetchByteM1(btX);
		IncRegR();
		Exec_X(btX);

		//Serial.println("1:HERE?");
		return GetExecClock();
	}

// execute procedure
protected:
	// base OP code
	void Exec_X(uint8_t btOpCode) {
		uint8_t btN, btE, btX;
		uint16_t wNN;
		switch (btOpCode) {
		case 0x00:
			Exec_NOP();
			break;
		case 0x01:
			FetchWord(wNN);
			Exec_LD_ss_nn(RegBC(), wNN);
			break;
		case 0x02:
			Exec_LD_Qss_A(RegBC());
			break;
		case 0x03:
			Exec_INC_ss(RegBC());
			break;
		case 0x04:
			Exec_INC_r(RegB());
			break;
		case 0x05:
			Exec_DEC_r(RegB());
			break;
		case 0x06:
			FetchByte(btN);
			Exec_LD_r_n(RegB(), btN);
			break;
		case 0x07:
			Exec_RLCA();
			break;
		case 0x08:
			Exec_EX_AF_AF2();
			break;
		case 0x09:
			Exec_ADD_HL_ss(RegBC());
			break;
		case 0x0A:
			Exec_LD_A_Qss(RegBC());
			break;
		case 0x0B:
			Exec_DEC_ss(RegBC());
			break;
		case 0x0C:
			Exec_INC_r(RegC());
			break;
		case 0x0D:
			Exec_DEC_r(RegC());
			break;
		case 0x0E:
			FetchByte(btN);
			Exec_LD_r_n(RegC(), btN);
			break;
		case 0x0F:
			Exec_RRCA();
			break;
		case 0x10:
			FetchByte(btE);
			Exec_DJNZ_e(btE);
			break;
		case 0x11:
			FetchWord(wNN);
			Exec_LD_ss_nn(RegDE(), wNN);
			break;
		case 0x12:
			Exec_LD_Qss_A(RegDE());
			break;
		case 0x13:
			Exec_INC_ss(RegDE());
			break;
		case 0x14:
			Exec_INC_r(RegD());
			break;
		case 0x15:
			Exec_DEC_r(RegD());
			break;
		case 0x16:
			FetchByte(btN);
			Exec_LD_r_n(RegD(), btN);
			break;
		case 0x17:
			Exec_RLA();
			break;
		case 0x18:
			FetchByte(btE);
			Exec_JR_e(btE);
			break;
		case 0x19:
			Exec_ADD_HL_ss(RegDE());
			break;
		case 0x1A:
			Exec_LD_A_Qss(RegDE());
			break;
		case 0x1B:
			Exec_DEC_ss(RegDE());
			break;
		case 0x1C:
			Exec_INC_r(RegE());
			break;
		case 0x1D:
			Exec_DEC_r(RegE());
			break;
		case 0x1E:
			FetchByte(btN);
			Exec_LD_r_n(RegE(), btN);
			break;
		case 0x1F:
			Exec_RRA();
			break;
		case 0x20:
			FetchByte(btE);
			Exec_JR_cc_e(FlagNZ(), btE);
			break;
		case 0x21:
			FetchWord(wNN);
			Exec_LD_ss_nn(RegHL(), wNN);
			break;
		case 0x22:
			FetchWord(wNN);
			Exec_LD_Qnn_ss(wNN, RegHL());
			break;
		case 0x23:
			Exec_INC_ss(RegHL());
			break;
		case 0x24:
			Exec_INC_r(RegH());
			break;
		case 0x25:
			Exec_DEC_r(RegH());
			break;
		case 0x26:
			FetchByte(btN);
			Exec_LD_r_n(RegH(), btN);
			break;
		case 0x27:
			Exec_DAA();
			break;
		case 0x28:
			FetchByte(btE);
			Exec_JR_cc_e(FlagZ(), btE);
			break;
		case 0x29:
			Exec_ADD_HL_ss(RegHL());
			break;
		case 0x2A:
			FetchWord(wNN);
			Exec_LD_ss_Qnn(RegHL(), wNN);
			break;
		case 0x2B:
			Exec_DEC_ss(RegHL());
			break;
		case 0x2C:
			Exec_INC_r(RegL());
			break;
		case 0x2D:
			Exec_DEC_r(RegL());
			break;
		case 0x2E:
			FetchByte(btN);
			Exec_LD_r_n(RegL(), btN);
			break;
		case 0x2F:
			Exec_CPL();
			break;
		case 0x30:
			FetchByte(btE);
			Exec_JR_cc_e(FlagNC(), btE);
			break;
		case 0x31:
			FetchWord(wNN);
			Exec_LD_ss_nn(RegSP(), wNN);
			break;
		case 0x32:
			FetchWord(wNN);
			Exec_LD_Qnn_A(wNN);
			break;
		case 0x33:
			Exec_INC_ss(RegSP());
			break;
		case 0x34:
			Exec_INC_QHL();
			break;
		case 0x35:
			Exec_DEC_QHL();
			break;
		case 0x36:
			FetchByte(btN);
			Exec_LD_QHL_n(btN);
			break;
		case 0x37:
			Exec_SCF();
			break;
		case 0x38:
			FetchByte(btE);
			Exec_JR_cc_e(FlagC(), btE);
			break;
		case 0x39:
			Exec_ADD_HL_ss(RegSP());
			break;
		case 0x3A:
			FetchWord(wNN);
			Exec_LD_A_Qnn(wNN);
			break;
		case 0x3B:
			Exec_DEC_ss(RegSP());
			break;
		case 0x3C:
			Exec_INC_r(RegA());
			break;
		case 0x3D:
			Exec_DEC_r(RegA());
			break;
		case 0x3E:
			FetchByte(btN);
			Exec_LD_r_n(RegA(), btN);
			break;
		case 0x3F:
			Exec_CCF();
			break;
		case 0x40:
			Exec_LD_r_r2(RegB(), RegB());
			break;
		case 0x41:
			Exec_LD_r_r2(RegB(), RegC());
			break;
		case 0x42:
			Exec_LD_r_r2(RegB(), RegD());
			break;
		case 0x43:
			Exec_LD_r_r2(RegB(), RegE());
			break;
		case 0x44:
			Exec_LD_r_r2(RegB(), RegH());
			break;
		case 0x45:
			Exec_LD_r_r2(RegB(), RegL());
			break;
		case 0x46:
			Exec_LD_r_QHL(RegB());
			break;
		case 0x47:
			Exec_LD_r_r2(RegB(), RegA());
			break;
		case 0x48:
			Exec_LD_r_r2(RegC(), RegB());
			break;
		case 0x49:
			Exec_LD_r_r2(RegC(), RegC());
			break;
		case 0x4A:
			Exec_LD_r_r2(RegC(), RegD());
			break;
		case 0x4B:
			Exec_LD_r_r2(RegC(), RegE());
			break;
		case 0x4C:
			Exec_LD_r_r2(RegC(), RegH());
			break;
		case 0x4D:
			Exec_LD_r_r2(RegC(), RegL());
			break;
		case 0x4E:
			Exec_LD_r_QHL(RegC());
			break;
		case 0x4F:
			Exec_LD_r_r2(RegC(), RegA());
			break;
		case 0x50:
			Exec_LD_r_r2(RegD(), RegB());
			break;
		case 0x51:
			Exec_LD_r_r2(RegD(), RegC());
			break;
		case 0x52:
			Exec_LD_r_r2(RegD(), RegD());
			break;
		case 0x53:
			Exec_LD_r_r2(RegD(), RegE());
			break;
		case 0x54:
			Exec_LD_r_r2(RegD(), RegH());
			break;
		case 0x55:
			Exec_LD_r_r2(RegD(), RegL());
			break;
		case 0x56:
			Exec_LD_r_QHL(RegD());
			break;
		case 0x57:
			Exec_LD_r_r2(RegD(), RegA());
			break;
		case 0x58:
			Exec_LD_r_r2(RegE(), RegB());
			break;
		case 0x59:
			Exec_LD_r_r2(RegE(), RegC());
			break;
		case 0x5A:
			Exec_LD_r_r2(RegE(), RegD());
			break;
		case 0x5B:
			Exec_LD_r_r2(RegE(), RegE());
			break;
		case 0x5C:
			Exec_LD_r_r2(RegE(), RegH());
			break;
		case 0x5D:
			Exec_LD_r_r2(RegE(), RegL());
			break;
		case 0x5E:
			Exec_LD_r_QHL(RegE());
			break;
		case 0x5F:
			Exec_LD_r_r2(RegE(), RegA());
			break;
		case 0x60:
			Exec_LD_r_r2(RegH(), RegB());
			break;
		case 0x61:
			Exec_LD_r_r2(RegH(), RegC());
			break;
		case 0x62:
			Exec_LD_r_r2(RegH(), RegD());
			break;
		case 0x63:
			Exec_LD_r_r2(RegH(), RegE());
			break;
		case 0x64:
			Exec_LD_r_r2(RegH(), RegH());
			break;
		case 0x65:
			Exec_LD_r_r2(RegH(), RegL());
			break;
		case 0x66:
			Exec_LD_r_QHL(RegH());
			break;
		case 0x67:
			Exec_LD_r_r2(RegH(), RegA());
			break;
		case 0x68:
			Exec_LD_r_r2(RegL(), RegB());
			break;
		case 0x69:
			Exec_LD_r_r2(RegL(), RegC());
			break;
		case 0x6A:
			Exec_LD_r_r2(RegL(), RegD());
			break;
		case 0x6B:
			Exec_LD_r_r2(RegL(), RegE());
			break;
		case 0x6C:
			Exec_LD_r_r2(RegL(), RegH());
			break;
		case 0x6D:
			Exec_LD_r_r2(RegL(), RegL());
			break;
		case 0x6E:
			Exec_LD_r_QHL(RegL());
			break;
		case 0x6F:
			Exec_LD_r_r2(RegL(), RegA());
			break;
		case 0x70:
			Exec_LD_QHL_r(RegB());
			break;
		case 0x71:
			Exec_LD_QHL_r(RegC());
			break;
		case 0x72:
			Exec_LD_QHL_r(RegD());
			break;
		case 0x73:
			Exec_LD_QHL_r(RegE());
			break;
		case 0x74:
			Exec_LD_QHL_r(RegH());
			break;
		case 0x75:
			Exec_LD_QHL_r(RegL());
			break;
		case 0x76:
			Exec_HALT();
			break;
		case 0x77:
			Exec_LD_QHL_r(RegA());
			break;
		case 0x78:
			Exec_LD_r_r2(RegA(), RegB());
			break;
		case 0x79:
			Exec_LD_r_r2(RegA(), RegC());
			break;
		case 0x7A:
			Exec_LD_r_r2(RegA(), RegD());
			break;
		case 0x7B:
			Exec_LD_r_r2(RegA(), RegE());
			break;
		case 0x7C:
			Exec_LD_r_r2(RegA(), RegH());
			break;
		case 0x7D:
			Exec_LD_r_r2(RegA(), RegL());
			break;
		case 0x7E:
			Exec_LD_r_QHL(RegA());
			break;
		case 0x7F:
			Exec_LD_r_r2(RegA(), RegA());
			break;
		case 0x80:
			Exec_ADD_A_r(RegB());
			break;
		case 0x81:
			Exec_ADD_A_r(RegC());
			break;
		case 0x82:
			Exec_ADD_A_r(RegD());
			break;
		case 0x83:
			Exec_ADD_A_r(RegE());
			break;
		case 0x84:
			Exec_ADD_A_r(RegH());
			break;
		case 0x85:
			Exec_ADD_A_r(RegL());
			break;
		case 0x86:
			Exec_ADD_A_QHL();
			break;
		case 0x87:
			Exec_ADD_A_r(RegA());
			break;
		case 0x88:
			Exec_ADC_A_r(RegB());
			break;
		case 0x89:
			Exec_ADC_A_r(RegC());
			break;
		case 0x8A:
			Exec_ADC_A_r(RegD());
			break;
		case 0x8B:
			Exec_ADC_A_r(RegE());
			break;
		case 0x8C:
			Exec_ADC_A_r(RegH());
			break;
		case 0x8D:
			Exec_ADC_A_r(RegL());
			break;
		case 0x8E:
			Exec_ADC_A_QHL();
			break;
		case 0x8F:
			Exec_ADC_A_r(RegA());
			break;
		case 0x90:
			Exec_SUB_r(RegB());
			break;
		case 0x91:
			Exec_SUB_r(RegC());
			break;
		case 0x92:
			Exec_SUB_r(RegD());
			break;
		case 0x93:
			Exec_SUB_r(RegE());
			break;
		case 0x94:
			Exec_SUB_r(RegH());
			break;
		case 0x95:
			Exec_SUB_r(RegL());
			break;
		case 0x96:
			Exec_SUB_QHL();
			break;
		case 0x97:
			Exec_SUB_r(RegA());
			break;
		case 0x98:
			Exec_SBC_A_r(RegB());
			break;
		case 0x99:
			Exec_SBC_A_r(RegC());
			break;
		case 0x9A:
			Exec_SBC_A_r(RegD());
			break;
		case 0x9B:
			Exec_SBC_A_r(RegE());
			break;
		case 0x9C:
			Exec_SBC_A_r(RegH());
			break;
		case 0x9D:
			Exec_SBC_A_r(RegL());
			break;
		case 0x9E:
			Exec_SBC_A_QHL();
			break;
		case 0x9F:
			Exec_SBC_A_r(RegA());
			break;
		case 0xA0:
			Exec_AND_r(RegB());
			break;
		case 0xA1:
			Exec_AND_r(RegC());
			break;
		case 0xA2:
			Exec_AND_r(RegD());
			break;
		case 0xA3:
			Exec_AND_r(RegE());
			break;
		case 0xA4:
			Exec_AND_r(RegH());
			break;
		case 0xA5:
			Exec_AND_r(RegL());
			break;
		case 0xA6:
			Exec_AND_QHL();
			break;
		case 0xA7:
			Exec_AND_r(RegA());
			break;
		case 0xA8:
			Exec_XOR_r(RegB());
			break;
		case 0xA9:
			Exec_XOR_r(RegC());
			break;
		case 0xAA:
			Exec_XOR_r(RegD());
			break;
		case 0xAB:
			Exec_XOR_r(RegE());
			break;
		case 0xAC:
			Exec_XOR_r(RegH());
			break;
		case 0xAD:
			Exec_XOR_r(RegL());
			break;
		case 0xAE:
			Exec_XOR_QHL();
			break;
		case 0xAF:
			Exec_XOR_r(RegA());
			break;
		case 0xB0:
			Exec_OR_r(RegB());
			break;
		case 0xB1:
			Exec_OR_r(RegC());
			break;
		case 0xB2:
			Exec_OR_r(RegD());
			break;
		case 0xB3:
			Exec_OR_r(RegE());
			break;
		case 0xB4:
			Exec_OR_r(RegH());
			break;
		case 0xB5:
			Exec_OR_r(RegL());
			break;
		case 0xB6:
			Exec_OR_QHL();
			break;
		case 0xB7:
			Exec_OR_r(RegA());
			break;
		case 0xB8:
			Exec_CP_r(RegB());
			break;
		case 0xB9:
			Exec_CP_r(RegC());
			break;
		case 0xBA:
			Exec_CP_r(RegD());
			break;
		case 0xBB:
			Exec_CP_r(RegE());
			break;
		case 0xBC:
			Exec_CP_r(RegH());
			break;
		case 0xBD:
			Exec_CP_r(RegL());
			break;
		case 0xBE:
			Exec_CP_QHL();
			break;
		case 0xBF:
			Exec_CP_r(RegA());
			break;
		case 0xC0:
			Exec_RET_cc(FlagNZ());
			break;
		case 0xC1:
			Exec_POP_ss(RegBC());
			break;
		case 0xC2:
			FetchWord(wNN);
			Exec_JP_cc_nn(FlagNZ(), wNN);
			break;
		case 0xC3:
			FetchWord(wNN);
			Exec_JP_nn(wNN);
			break;
		case 0xC4:
			FetchWord(wNN);
			Exec_CALL_cc_nn(FlagNZ(), wNN);
			break;
		case 0xC5:
			Exec_PUSH_ss(RegBC());
			break;
		case 0xC6:
			FetchByte(btN);
			Exec_ADD_A_n(btN);
			break;
		case 0xC7:
			Exec_RST_n(0x00);
			break;
		case 0xC8:
			Exec_RET_cc(FlagZ());
			break;
		case 0xC9:
			Exec_RET();
			break;
		case 0xCA:
			FetchWord(wNN);
			Exec_JP_cc_nn(FlagZ(), wNN);
			break;
		case 0xCB:
			FetchByteM1(btX);
			IncRegR();
			Exec_CB_X(btX);
			break;
		case 0xCC:
			FetchWord(wNN);
			Exec_CALL_cc_nn(FlagZ(), wNN);
			break;
		case 0xCD:
			FetchWord(wNN);
			Exec_CALL_nn(wNN);
			break;
		case 0xCE:
			FetchByte(btN);
			Exec_ADC_A_n(btN);
			break;
		case 0xCF:
			Exec_RST_n(0x08);
			break;
		case 0xD0:
			Exec_RET_cc(FlagNC());
			break;
		case 0xD1:
			Exec_POP_ss(RegDE());
			break;
		case 0xD2:
			FetchWord(wNN);
			Exec_JP_cc_nn(FlagNC(), wNN);
			break;
		case 0xD3:
			//Serial.println("0xD3");
			FetchByte(btN);
			Exec_OUT_Qn_A(btN);
			break;
		case 0xD4:
			FetchWord(wNN);
			Exec_CALL_cc_nn(FlagNC(), wNN);
			break;
		case 0xD5:
			Exec_PUSH_ss(RegDE());
			break;
		case 0xD6:
			FetchByte(btN);
			Exec_SUB_n(btN);
			break;
		case 0xD7:
			Exec_RST_n(0x10);
			break;
		case 0xD8:
			Exec_RET_cc(FlagC());
			break;
		case 0xD9:
			Exec_EXX();
			break;
		case 0xDA:
			FetchWord(wNN);
			Exec_JP_cc_nn(FlagC(), wNN);
			break;
		case 0xDB:
			FetchByte(btN);
			Exec_IN_A_Qn(btN);
			break;
		case 0xDC:
			FetchWord(wNN);
			Exec_CALL_cc_nn(FlagC(), wNN);
			break;
		case 0xDD:
			FetchByteM1(btX);
			IncRegR();
			Exec_DD_X(btX);
			break;
		case 0xDE:
			FetchByte(btN);
			Exec_SBC_A_n(btN);
			break;
		case 0xDF:
			Exec_RST_n(0x18);
			break;
		case 0xE0:
			Exec_RET_cc(FlagPO());
			break;
		case 0xE1:
			Exec_POP_ss(RegHL());
			break;
		case 0xE2:
			FetchWord(wNN);
			Exec_JP_cc_nn(FlagPO(), wNN);
			break;
		case 0xE3:
			Exec_EX_QSP_HL();
			break;
		case 0xE4:
			FetchWord(wNN);
			Exec_CALL_cc_nn(FlagPO(), wNN);
			break;
		case 0xE5:
			Exec_PUSH_ss(RegHL());
			break;
		case 0xE6:
			FetchByte(btN);
			Exec_AND_n(btN);
			break;
		case 0xE7:
			Exec_RST_n(0x20);
			break;
		case 0xE8:
			Exec_RET_cc(FlagPE());
			break;
		case 0xE9:
			Exec_JP_QHL();
			break;
		case 0xEA:
			FetchWord(wNN);
			Exec_JP_cc_nn(FlagPE(), wNN);
			break;
		case 0xEB:
			Exec_EX_DE_HL();
			break;
		case 0xEC:
			FetchWord(wNN);
			Exec_CALL_cc_nn(FlagPE(), wNN);
			break;
		case 0xED:
			FetchByteM1(btX);
			IncRegR();
			Exec_ED_X(btX);
			break;
		case 0xEE:
			FetchByte(btN);
			Exec_XOR_n(btN);
			break;
		case 0xEF:
			Exec_RST_n(0x28);
			break;
		case 0xF0:
			Exec_RET_cc(FlagP());
			break;
		case 0xF1:
			Exec_POP_ss(RegAF());
			break;
		case 0xF2:
			FetchWord(wNN);
			Exec_JP_cc_nn(FlagP(), wNN);
			break;
		case 0xF3:
			Exec_DI();
			break;
		case 0xF4:
			FetchWord(wNN);
			Exec_CALL_cc_nn(FlagP(), wNN);
			break;
		case 0xF5:
			Exec_PUSH_ss(RegAF());
			break;
		case 0xF6:
			FetchByte(btN);
			Exec_OR_n(btN);
			break;
		case 0xF7:
			Exec_RST_n(0x30);
			break;
		case 0xF8:
			Exec_RET_cc(FlagM());
			break;
		case 0xF9:
			Exec_LD_SP_HL();
			break;
		case 0xFA:
			FetchWord(wNN);
			Exec_JP_cc_nn(FlagM(), wNN);
			break;
		case 0xFB:
			Exec_EI();
			break;
		case 0xFC:
			FetchWord(wNN);
			Exec_CALL_cc_nn(FlagM(), wNN);
			break;
		case 0xFD:
			FetchByteM1(btX);
			IncRegR();
			Exec_FD_X(btX);
			break;
		case 0xFE:
			FetchByte(btN);
			Exec_CP_n(btN);
			break;
		case 0xFF:
			Exec_RST_n(0x38);
			break;
		}
		//Serial.println("4:HERE?");
	}
	// extend OP code(CBH)
	void Exec_CB_X(uint8_t btOpCode) {
		AddExecClock(CLOCK_CB_X);
		switch (btOpCode) {
		case 0x00:
			Exec_RLC_r(RegB());
			break;
		case 0x01:
			Exec_RLC_r(RegC());
			break;
		case 0x02:
			Exec_RLC_r(RegD());
			break;
		case 0x03:
			Exec_RLC_r(RegE());
			break;
		case 0x04:
			Exec_RLC_r(RegH());
			break;
		case 0x05:
			Exec_RLC_r(RegL());
			break;
		case 0x06:
			Exec_RLC_QHL();
			break;
		case 0x07:
			Exec_RLC_r(RegA());
			break;
		case 0x08:
			Exec_RRC_r(RegB());
			break;
		case 0x09:
			Exec_RRC_r(RegC());
			break;
		case 0x0A:
			Exec_RRC_r(RegD());
			break;
		case 0x0B:
			Exec_RRC_r(RegE());
			break;
		case 0x0C:
			Exec_RRC_r(RegH());
			break;
		case 0x0D:
			Exec_RRC_r(RegL());
			break;
		case 0x0E:
			Exec_RRC_QHL();
			break;
		case 0x0F:
			Exec_RRC_r(RegA());
			break;
		case 0x10:
			Exec_RL_r(RegB());
			break;
		case 0x11:
			Exec_RL_r(RegC());
			break;
		case 0x12:
			Exec_RL_r(RegD());
			break;
		case 0x13:
			Exec_RL_r(RegE());
			break;
		case 0x14:
			Exec_RL_r(RegH());
			break;
		case 0x15:
			Exec_RL_r(RegL());
			break;
		case 0x16:
			Exec_RL_QHL();
			break;
		case 0x17:
			Exec_RL_r(RegA());
			break;
		case 0x18:
			Exec_RR_r(RegB());
			break;
		case 0x19:
			Exec_RR_r(RegC());
			break;
		case 0x1A:
			Exec_RR_r(RegD());
			break;
		case 0x1B:
			Exec_RR_r(RegE());
			break;
		case 0x1C:
			Exec_RR_r(RegH());
			break;
		case 0x1D:
			Exec_RR_r(RegL());
			break;
		case 0x1E:
			Exec_RR_QHL();
			break;
		case 0x1F:
			Exec_RR_r(RegA());
			break;
		case 0x20:
			Exec_SLA_r(RegB());
			break;
		case 0x21:
			Exec_SLA_r(RegC());
			break;
		case 0x22:
			Exec_SLA_r(RegD());
			break;
		case 0x23:
			Exec_SLA_r(RegE());
			break;
		case 0x24:
			Exec_SLA_r(RegH());
			break;
		case 0x25:
			Exec_SLA_r(RegL());
			break;
		case 0x26:
			Exec_SLA_QHL();
			break;
		case 0x27:
			Exec_SLA_r(RegA());
			break;
		case 0x28:
			Exec_SRA_r(RegB());
			break;
		case 0x29:
			Exec_SRA_r(RegC());
			break;
		case 0x2A:
			Exec_SRA_r(RegD());
			break;
		case 0x2B:
			Exec_SRA_r(RegE());
			break;
		case 0x2C:
			Exec_SRA_r(RegH());
			break;
		case 0x2D:
			Exec_SRA_r(RegL());
			break;
		case 0x2E:
			Exec_SRA_QHL();
			break;
		case 0x2F:
			Exec_SRA_r(RegA());
			break;
		case 0x30:
			Exec_SLL_r(RegB());
			break;
		case 0x31:
			Exec_SLL_r(RegC());
			break;
		case 0x32:
			Exec_SLL_r(RegD());
			break;
		case 0x33:
			Exec_SLL_r(RegE());
			break;
		case 0x34:
			Exec_SLL_r(RegH());
			break;
		case 0x35:
			Exec_SLL_r(RegL());
			break;
		case 0x36:
			Exec_SLL_QHL();
			break;
		case 0x37:
			Exec_SLL_r(RegA());
			break;
		case 0x38:
			Exec_SRL_r(RegB());
			break;
		case 0x39:
			Exec_SRL_r(RegC());
			break;
		case 0x3A:
			Exec_SRL_r(RegD());
			break;
		case 0x3B:
			Exec_SRL_r(RegE());
			break;
		case 0x3C:
			Exec_SRL_r(RegH());
			break;
		case 0x3D:
			Exec_SRL_r(RegL());
			break;
		case 0x3E:
			Exec_SRL_QHL();
			break;
		case 0x3F:
			Exec_SRL_r(RegA());
			break;
		case 0x40:
			Exec_BIT_b_r(0, RegB());
			break;
		case 0x41:
			Exec_BIT_b_r(0, RegC());
			break;
		case 0x42:
			Exec_BIT_b_r(0, RegD());
			break;
		case 0x43:
			Exec_BIT_b_r(0, RegE());
			break;
		case 0x44:
			Exec_BIT_b_r(0, RegH());
			break;
		case 0x45:
			Exec_BIT_b_r(0, RegL());
			break;
		case 0x46:
			Exec_BIT_b_QHL(0);
			break;
		case 0x47:
			Exec_BIT_b_r(0, RegA());
			break;
		case 0x48:
			Exec_BIT_b_r(1, RegB());
			break;
		case 0x49:
			Exec_BIT_b_r(1, RegC());
			break;
		case 0x4A:
			Exec_BIT_b_r(1, RegD());
			break;
		case 0x4B:
			Exec_BIT_b_r(1, RegE());
			break;
		case 0x4C:
			Exec_BIT_b_r(1, RegH());
			break;
		case 0x4D:
			Exec_BIT_b_r(1, RegL());
			break;
		case 0x4E:
			Exec_BIT_b_QHL(1);
			break;
		case 0x4F:
			Exec_BIT_b_r(1, RegA());
			break;
		case 0x50:
			Exec_BIT_b_r(2, RegB());
			break;
		case 0x51:
			Exec_BIT_b_r(2, RegC());
			break;
		case 0x52:
			Exec_BIT_b_r(2, RegD());
			break;
		case 0x53:
			Exec_BIT_b_r(2, RegE());
			break;
		case 0x54:
			Exec_BIT_b_r(2, RegH());
			break;
		case 0x55:
			Exec_BIT_b_r(2, RegL());
			break;
		case 0x56:
			Exec_BIT_b_QHL(2);
			break;
		case 0x57:
			Exec_BIT_b_r(2, RegA());
			break;
		case 0x58:
			Exec_BIT_b_r(3, RegB());
			break;
		case 0x59:
			Exec_BIT_b_r(3, RegC());
			break;
		case 0x5A:
			Exec_BIT_b_r(3, RegD());
			break;
		case 0x5B:
			Exec_BIT_b_r(3, RegE());
			break;
		case 0x5C:
			Exec_BIT_b_r(3, RegH());
			break;
		case 0x5D:
			Exec_BIT_b_r(3, RegL());
			break;
		case 0x5E:
			Exec_BIT_b_QHL(3);
			break;
		case 0x5F:
			Exec_BIT_b_r(3, RegA());
			break;
		case 0x60:
			Exec_BIT_b_r(4, RegB());
			break;
		case 0x61:
			Exec_BIT_b_r(4, RegC());
			break;
		case 0x62:
			Exec_BIT_b_r(4, RegD());
			break;
		case 0x63:
			Exec_BIT_b_r(4, RegE());
			break;
		case 0x64:
			Exec_BIT_b_r(4, RegH());
			break;
		case 0x65:
			Exec_BIT_b_r(4, RegL());
			break;
		case 0x66:
			Exec_BIT_b_QHL(4);
			break;
		case 0x67:
			Exec_BIT_b_r(4, RegA());
			break;
		case 0x68:
			Exec_BIT_b_r(5, RegB());
			break;
		case 0x69:
			Exec_BIT_b_r(5, RegC());
			break;
		case 0x6A:
			Exec_BIT_b_r(5, RegD());
			break;
		case 0x6B:
			Exec_BIT_b_r(5, RegE());
			break;
		case 0x6C:
			Exec_BIT_b_r(5, RegH());
			break;
		case 0x6D:
			Exec_BIT_b_r(5, RegL());
			break;
		case 0x6E:
			Exec_BIT_b_QHL(5);
			break;
		case 0x6F:
			Exec_BIT_b_r(5, RegA());
			break;
		case 0x70:
			Exec_BIT_b_r(6, RegB());
			break;
		case 0x71:
			Exec_BIT_b_r(6, RegC());
			break;
		case 0x72:
			Exec_BIT_b_r(6, RegD());
			break;
		case 0x73:
			Exec_BIT_b_r(6, RegE());
			break;
		case 0x74:
			Exec_BIT_b_r(6, RegH());
			break;
		case 0x75:
			Exec_BIT_b_r(6, RegL());
			break;
		case 0x76:
			Exec_BIT_b_QHL(6);
			break;
		case 0x77:
			Exec_BIT_b_r(6, RegA());
			break;
		case 0x78:
			Exec_BIT_b_r(7, RegB());
			break;
		case 0x79:
			Exec_BIT_b_r(7, RegC());
			break;
		case 0x7A:
			Exec_BIT_b_r(7, RegD());
			break;
		case 0x7B:
			Exec_BIT_b_r(7, RegE());
			break;
		case 0x7C:
			Exec_BIT_b_r(7, RegH());
			break;
		case 0x7D:
			Exec_BIT_b_r(7, RegL());
			break;
		case 0x7E:
			Exec_BIT_b_QHL(7);
			break;
		case 0x7F:
			Exec_BIT_b_r(7, RegA());
			break;
		case 0x80:
			Exec_RES_b_r(0, RegB());
			break;
		case 0x81:
			Exec_RES_b_r(0, RegC());
			break;
		case 0x82:
			Exec_RES_b_r(0, RegD());
			break;
		case 0x83:
			Exec_RES_b_r(0, RegE());
			break;
		case 0x84:
			Exec_RES_b_r(0, RegH());
			break;
		case 0x85:
			Exec_RES_b_r(0, RegL());
			break;
		case 0x86:
			Exec_RES_b_QHL(0);
			break;
		case 0x87:
			Exec_RES_b_r(0, RegA());
			break;
		case 0x88:
			Exec_RES_b_r(1, RegB());
			break;
		case 0x89:
			Exec_RES_b_r(1, RegC());
			break;
		case 0x8A:
			Exec_RES_b_r(1, RegD());
			break;
		case 0x8B:
			Exec_RES_b_r(1, RegE());
			break;
		case 0x8C:
			Exec_RES_b_r(1, RegH());
			break;
		case 0x8D:
			Exec_RES_b_r(1, RegL());
			break;
		case 0x8E:
			Exec_RES_b_QHL(1);
			break;
		case 0x8F:
			Exec_RES_b_r(1, RegA());
			break;
		case 0x90:
			Exec_RES_b_r(2, RegB());
			break;
		case 0x91:
			Exec_RES_b_r(2, RegC());
			break;
		case 0x92:
			Exec_RES_b_r(2, RegD());
			break;
		case 0x93:
			Exec_RES_b_r(2, RegE());
			break;
		case 0x94:
			Exec_RES_b_r(2, RegH());
			break;
		case 0x95:
			Exec_RES_b_r(2, RegL());
			break;
		case 0x96:
			Exec_RES_b_QHL(2);
			break;
		case 0x97:
			Exec_RES_b_r(2, RegA());
			break;
		case 0x98:
			Exec_RES_b_r(3, RegB());
			break;
		case 0x99:
			Exec_RES_b_r(3, RegC());
			break;
		case 0x9A:
			Exec_RES_b_r(3, RegD());
			break;
		case 0x9B:
			Exec_RES_b_r(3, RegE());
			break;
		case 0x9C:
			Exec_RES_b_r(3, RegH());
			break;
		case 0x9D:
			Exec_RES_b_r(3, RegL());
			break;
		case 0x9E:
			Exec_RES_b_QHL(3);
			break;
		case 0x9F:
			Exec_RES_b_r(3, RegA());
			break;
		case 0xA0:
			Exec_RES_b_r(4, RegB());
			break;
		case 0xA1:
			Exec_RES_b_r(4, RegC());
			break;
		case 0xA2:
			Exec_RES_b_r(4, RegD());
			break;
		case 0xA3:
			Exec_RES_b_r(4, RegE());
			break;
		case 0xA4:
			Exec_RES_b_r(4, RegH());
			break;
		case 0xA5:
			Exec_RES_b_r(4, RegL());
			break;
		case 0xA6:
			Exec_RES_b_QHL(4);
			break;
		case 0xA7:
			Exec_RES_b_r(4, RegA());
			break;
		case 0xA8:
			Exec_RES_b_r(5, RegB());
			break;
		case 0xA9:
			Exec_RES_b_r(5, RegC());
			break;
		case 0xAA:
			Exec_RES_b_r(5, RegD());
			break;
		case 0xAB:
			Exec_RES_b_r(5, RegE());
			break;
		case 0xAC:
			Exec_RES_b_r(5, RegH());
			break;
		case 0xAD:
			Exec_RES_b_r(5, RegL());
			break;
		case 0xAE:
			Exec_RES_b_QHL(5);
			break;
		case 0xAF:
			Exec_RES_b_r(5, RegA());
			break;
		case 0xB0:
			Exec_RES_b_r(6, RegB());
			break;
		case 0xB1:
			Exec_RES_b_r(6, RegC());
			break;
		case 0xB2:
			Exec_RES_b_r(6, RegD());
			break;
		case 0xB3:
			Exec_RES_b_r(6, RegE());
			break;
		case 0xB4:
			Exec_RES_b_r(6, RegH());
			break;
		case 0xB5:
			Exec_RES_b_r(6, RegL());
			break;
		case 0xB6:
			Exec_RES_b_QHL(6);
			break;
		case 0xB7:
			Exec_RES_b_r(6, RegA());
			break;
		case 0xB8:
			Exec_RES_b_r(7, RegB());
			break;
		case 0xB9:
			Exec_RES_b_r(7, RegC());
			break;
		case 0xBA:
			Exec_RES_b_r(7, RegD());
			break;
		case 0xBB:
			Exec_RES_b_r(7, RegE());
			break;
		case 0xBC:
			Exec_RES_b_r(7, RegH());
			break;
		case 0xBD:
			Exec_RES_b_r(7, RegL());
			break;
		case 0xBE:
			Exec_RES_b_QHL(7);
			break;
		case 0xBF:
			Exec_RES_b_r(7, RegA());
			break;
		case 0xC0:
			Exec_SET_b_r(0, RegB());
			break;
		case 0xC1:
			Exec_SET_b_r(0, RegC());
			break;
		case 0xC2:
			Exec_SET_b_r(0, RegD());
			break;
		case 0xC3:
			Exec_SET_b_r(0, RegE());
			break;
		case 0xC4:
			Exec_SET_b_r(0, RegH());
			break;
		case 0xC5:
			Exec_SET_b_r(0, RegL());
			break;
		case 0xC6:
			Exec_SET_b_QHL(0);
			break;
		case 0xC7:
			Exec_SET_b_r(0, RegA());
			break;
		case 0xC8:
			Exec_SET_b_r(1, RegB());
			break;
		case 0xC9:
			Exec_SET_b_r(1, RegC());
			break;
		case 0xCA:
			Exec_SET_b_r(1, RegD());
			break;
		case 0xCB:
			Exec_SET_b_r(1, RegE());
			break;
		case 0xCC:
			Exec_SET_b_r(1, RegH());
			break;
		case 0xCD:
			Exec_SET_b_r(1, RegL());
			break;
		case 0xCE:
			Exec_SET_b_QHL(1);
			break;
		case 0xCF:
			Exec_SET_b_r(1, RegA());
			break;
		case 0xD0:
			Exec_SET_b_r(2, RegB());
			break;
		case 0xD1:
			Exec_SET_b_r(2, RegC());
			break;
		case 0xD2:
			Exec_SET_b_r(2, RegD());
			break;
		case 0xD3:
			Exec_SET_b_r(2, RegE());
			break;
		case 0xD4:
			Exec_SET_b_r(2, RegH());
			break;
		case 0xD5:
			Exec_SET_b_r(2, RegL());
			break;
		case 0xD6:
			Exec_SET_b_QHL(2);
			break;
		case 0xD7:
			Exec_SET_b_r(2, RegA());
			break;
		case 0xD8:
			Exec_SET_b_r(3, RegB());
			break;
		case 0xD9:
			Exec_SET_b_r(3, RegC());
			break;
		case 0xDA:
			Exec_SET_b_r(3, RegD());
			break;
		case 0xDB:
			Exec_SET_b_r(3, RegE());
			break;
		case 0xDC:
			Exec_SET_b_r(3, RegH());
			break;
		case 0xDD:
			Exec_SET_b_r(3, RegL());
			break;
		case 0xDE:
			Exec_SET_b_QHL(3);
			break;
		case 0xDF:
			Exec_SET_b_r(3, RegA());
			break;
		case 0xE0:
			Exec_SET_b_r(4, RegB());
			break;
		case 0xE1:
			Exec_SET_b_r(4, RegC());
			break;
		case 0xE2:
			Exec_SET_b_r(4, RegD());
			break;
		case 0xE3:
			Exec_SET_b_r(4, RegE());
			break;
		case 0xE4:
			Exec_SET_b_r(4, RegH());
			break;
		case 0xE5:
			Exec_SET_b_r(4, RegL());
			break;
		case 0xE6:
			Exec_SET_b_QHL(4);
			break;
		case 0xE7:
			Exec_SET_b_r(4, RegA());
			break;
		case 0xE8:
			Exec_SET_b_r(5, RegB());
			break;
		case 0xE9:
			Exec_SET_b_r(5, RegC());
			break;
		case 0xEA:
			Exec_SET_b_r(5, RegD());
			break;
		case 0xEB:
			Exec_SET_b_r(5, RegE());
			break;
		case 0xEC:
			Exec_SET_b_r(5, RegH());
			break;
		case 0xED:
			Exec_SET_b_r(5, RegL());
			break;
		case 0xEE:
			Exec_SET_b_QHL(5);
			break;
		case 0xEF:
			Exec_SET_b_r(5, RegA());
			break;
		case 0xF0:
			Exec_SET_b_r(6, RegB());
			break;
		case 0xF1:
			Exec_SET_b_r(6, RegC());
			break;
		case 0xF2:
			Exec_SET_b_r(6, RegD());
			break;
		case 0xF3:
			Exec_SET_b_r(6, RegE());
			break;
		case 0xF4:
			Exec_SET_b_r(6, RegH());
			break;
		case 0xF5:
			Exec_SET_b_r(6, RegL());
			break;
		case 0xF6:
			Exec_SET_b_QHL(6);
			break;
		case 0xF7:
			Exec_SET_b_r(6, RegA());
			break;
		case 0xF8:
			Exec_SET_b_r(7, RegB());
			break;
		case 0xF9:
			Exec_SET_b_r(7, RegC());
			break;
		case 0xFA:
			Exec_SET_b_r(7, RegD());
			break;
		case 0xFB:
			Exec_SET_b_r(7, RegE());
			break;
		case 0xFC:
			Exec_SET_b_r(7, RegH());
			break;
		case 0xFD:
			Exec_SET_b_r(7, RegL());
			break;
		case 0xFE:
			Exec_SET_b_QHL(7);
			break;
		case 0xFF:
			Exec_SET_b_r(7, RegA());
			break;
		}
		//Serial.println("5:HERE?");
	}
	// extend OP code(EDH)
	void Exec_ED_X(uint8_t btOpCode) {
		uint16_t wNN;
		AddExecClock(CLOCK_ED_X);
		switch (btOpCode) {
		case 0x40:
			Exec_IN_r_QC(RegB());
			break;
		case 0x41:
			Exec_OUT_QC_r(RegB());
			break;
		case 0x42:
			Exec_SBC_HL_ss(RegBC());
			break;
		case 0x43:
			FetchWord(wNN);
			Exec_LD_Qnn_ss(wNN, RegBC());
			break;
		case 0x44:
		case 0x4C:
		case 0x54:
		case 0x5C:
		case 0x64:
		case 0x6C:
		case 0x74:
		case 0x7C:
			Exec_NEG();
			break;
		case 0x45:
		case 0x55:
		case 0x65:
		case 0x75:
			Exec_RETN();
			break;
		case 0x46:
		case 0x66:
			Exec_IM0();
			break;
		case 0x47:
			Exec_LD_I_A();
			break;
		case 0x48:
			Exec_IN_r_QC(RegC());
			break;
		case 0x49:
			Exec_OUT_QC_r(RegC());
			break;
		case 0x4A:
			Exec_ADC_HL_ss(RegBC());
			break;
		case 0x4B:
			FetchWord(wNN);
			Exec_LD_ss_Qnn(RegBC(), wNN);
			break;
		case 0x4D:
		case 0x5D:
		case 0x6D:
		case 0x7D:
			Exec_RETI();
			break;
		case 0x4E:
		case 0x6E:
			Exec_IMx();
			break;
		case 0x4F:
			Exec_LD_R_A();
			break;
		case 0x50:
			Exec_IN_r_QC(RegD());
			break;
		case 0x51:
			Exec_OUT_QC_r(RegD());
			break;
		case 0x52:
			Exec_SBC_HL_ss(RegDE());
			break;
		case 0x53:
			FetchWord(wNN);
			Exec_LD_Qnn_ss(wNN, RegDE());
			break;
		case 0x56:
		case 0x76:
			Exec_IM1();
			break;
		case 0x57:
			Exec_LD_A_I();
			break;
		case 0x58:
			Exec_IN_r_QC(RegE());
			break;
		case 0x59:
			Exec_OUT_QC_r(RegE());
			break;
		case 0x5A:
			Exec_ADC_HL_ss(RegDE());
			break;
		case 0x5B:
			FetchWord(wNN);
			Exec_LD_ss_Qnn(RegDE(), wNN);
			break;
		case 0x5E:
		case 0x7E:
			Exec_IM2();
			break;
		case 0x5F:
			Exec_LD_A_R();
			break;
		case 0x60:
			Exec_IN_r_QC(RegH());
			break;
		case 0x61:
			Exec_OUT_QC_r(RegH());
			break;
		case 0x62:
			Exec_SBC_HL_ss(RegHL());
			break;
		case 0x63:
			FetchWord(wNN);
			Exec_LD_Qnn_ss(wNN, RegHL());
			break;
		case 0x67:
			Exec_RRD();
			break;
		case 0x68:
			Exec_IN_r_QC(RegL());
			break;
		case 0x69:
			Exec_OUT_QC_r(RegL());
			break;
		case 0x6A:
			Exec_ADC_HL_ss(RegHL());
			break;
		case 0x6B:
			FetchWord(wNN);
			Exec_LD_ss_Qnn(RegHL(), wNN);
			break;
		case 0x6F:
			Exec_RLD();
			break;
		case 0x70:
			Exec_IN_F_QC();
			break;
		case 0x71:
			Exec_OUT_QC_0();
			break;
		case 0x72:
			Exec_SBC_HL_ss(RegSP());
			break;
		case 0x73:
			FetchWord(wNN);
			Exec_LD_Qnn_ss(wNN, RegSP());
			break;
		case 0x77:
		case 0x7F:
			Exec_NOP();
			break;
		case 0x78:
			Exec_IN_r_QC(RegA());
			break;
		case 0x79:
			Exec_OUT_QC_r(RegA());
			break;
		case 0x7A:
			Exec_ADC_HL_ss(RegSP());
			break;
		case 0x7B:
			FetchWord(wNN);
			Exec_LD_ss_Qnn(RegSP(), wNN);
			break;
		case 0xA0:
			Exec_LDI();
			break;
		case 0xA1:
			Exec_CPI();
			break;
		case 0xA2:
			Exec_INI();
			break;
		case 0xA3:
			Exec_OUTI();
			break;
		case 0xA8:
			Exec_LDD();
			break;
		case 0xA9:
			Exec_CPD();
			break;
		case 0xAA:
			Exec_IND();
			break;
		case 0xAB:
			Exec_OUTD();
			break;
		case 0xB0:
			Exec_LDIR();
			break;
		case 0xB1:
			Exec_CPIR();
			break;
		case 0xB2:
			Exec_INIR();
			break;
		case 0xB3:
			Exec_OTIR();
			break;
		case 0xB8:
			Exec_LDDR();
			break;
		case 0xB9:
			Exec_CPDR();
			break;
		case 0xBA:
			Exec_INDR();
			break;
		case 0xBB:
			Exec_OTDR();
			break;
		}
	}
	// extend OP code(DDH)
	void Exec_DD_X(uint8_t btOpCode) {
		uint8_t btN, btD, btX;
		uint16_t wNN;
		AddExecClock(CLOCK_DD_X);
		switch (btOpCode) {
		case 0x09:
			Exec_ADD_IX_ss(RegBC());
			break;
		case 0x19:
			Exec_ADD_IX_ss(RegDE());
			break;
		case 0x21:
			FetchWord(wNN);
			Exec_LD_IX_nn(wNN);
			break;
		case 0x22:
			FetchWord(wNN);
			Exec_LD_Qnn_IX(wNN);
			break;
		case 0x23:
			Exec_INC_IX();
			break;
		case 0x24:
			Exec_INC_r(RegIXH());
			break;
		case 0x25:
			Exec_DEC_r(RegIXH());
			break;
		case 0x26:
			FetchByte(btN);
			Exec_LD_r_n(RegIXH(), btN);
			break;
		case 0x29:
			Exec_ADD_IX_ss(RegIX());
			break;
		case 0x2A:
			FetchWord(wNN);
			Exec_LD_IX_Qnn(wNN);
			break;
		case 0x2B:
			Exec_DEC_IX();
			break;
		case 0x2C:
			Exec_INC_r(RegIXL());
			break;
		case 0x2D:
			Exec_DEC_r(RegIXL());
			break;
		case 0x2E:
			FetchByte(btN);
			Exec_LD_r_n(RegIXL(), btN);
			break;
		case 0x34:
			FetchByte(btD);
			Exec_INC_QIXd(btD);
			break;
		case 0x35:
			FetchByte(btD);
			Exec_DEC_QIXd(btD);
			break;
		case 0x36:
			FetchByte(btD);
			FetchByte(btN);
			Exec_LD_QIXd_n(btD, btN);
			break;
		case 0x39:
			Exec_ADD_IX_ss(RegSP());
			break;
		case 0x44:
			Exec_LD_r_r2(RegB(), RegIXH());
			break;
		case 0x45:
			Exec_LD_r_r2(RegB(), RegIXL());
			break;
		case 0x46:
			FetchByte(btD);
			Exec_LD_r_QIXd(RegB(), btD);
			break;
		case 0x4C:
			Exec_LD_r_r2(RegC(), RegIXH());
			break;
		case 0x4D:
			Exec_LD_r_r2(RegC(), RegIXL());
			break;
		case 0x4E:
			FetchByte(btD);
			Exec_LD_r_QIXd(RegC(), btD);
			break;
		case 0x54:
			Exec_LD_r_r2(RegD(), RegIXH());
			break;
		case 0x55:
			Exec_LD_r_r2(RegD(), RegIXL());
			break;
		case 0x56:
			FetchByte(btD);
			Exec_LD_r_QIXd(RegD(), btD);
			break;
		case 0x5C:
			Exec_LD_r_r2(RegE(), RegIXH());
			break;
		case 0x5D:
			Exec_LD_r_r2(RegE(), RegIXL());
			break;
		case 0x5E:
			FetchByte(btD);
			Exec_LD_r_QIXd(RegE(), btD);
			break;
		case 0x60:
			Exec_LD_r_r2(RegIXH(), RegB());
			break;
		case 0x61:
			Exec_LD_r_r2(RegIXH(), RegC());
			break;
		case 0x62:
			Exec_LD_r_r2(RegIXH(), RegD());
			break;
		case 0x63:
			Exec_LD_r_r2(RegIXH(), RegE());
			break;
		case 0x64:
			Exec_LD_r_r2(RegIXH(), RegIXH());
			break;
		case 0x65:
			Exec_LD_r_r2(RegIXH(), RegIXL());
			break;
		case 0x66:
			FetchByte(btD);
			Exec_LD_r_QIXd(RegH(), btD);
			break;
		case 0x67:
			Exec_LD_r_r2(RegIXH(), RegA());
			break;
		case 0x68:
			Exec_LD_r_r2(RegIXL(), RegB());
			break;
		case 0x69:
			Exec_LD_r_r2(RegIXL(), RegC());
			break;
		case 0x6A:
			Exec_LD_r_r2(RegIXL(), RegD());
			break;
		case 0x6B:
			Exec_LD_r_r2(RegIXL(), RegE());
			break;
		case 0x6C:
			Exec_LD_r_r2(RegIXL(), RegIXH());
			break;
		case 0x6D:
			Exec_LD_r_r2(RegIXL(), RegIXL());
			break;
		case 0x6E:
			FetchByte(btD);
			Exec_LD_r_QIXd(RegL(), btD);
			break;
		case 0x6F:
			Exec_LD_r_r2(RegIXL(), RegA());
			break;
		case 0x70:
			FetchByte(btD);
			Exec_LD_QIXd_r(btD, RegB());
			break;
		case 0x71:
			FetchByte(btD);
			Exec_LD_QIXd_r(btD, RegC());
			break;
		case 0x72:
			FetchByte(btD);
			Exec_LD_QIXd_r(btD, RegD());
			break;
		case 0x73:
			FetchByte(btD);
			Exec_LD_QIXd_r(btD, RegE());
			break;
		case 0x74:
			FetchByte(btD);
			Exec_LD_QIXd_r(btD, RegH());
			break;
		case 0x75:
			FetchByte(btD);
			Exec_LD_QIXd_r(btD, RegL());
			break;
		case 0x77:
			FetchByte(btD);
			Exec_LD_QIXd_r(btD, RegA());
			break;
		case 0x7C:
			Exec_LD_r_r2(RegA(), RegIXH());
			break;
		case 0x7D:
			Exec_LD_r_r2(RegA(), RegIXL());
			break;
		case 0x7E:
			FetchByte(btD);
			Exec_LD_r_QIXd(RegA(), btD);
			break;
		case 0x84:
			Exec_ADD_A_r(RegIXH());
			break;
		case 0x85:
			Exec_ADD_A_r(RegIXL());
			break;
		case 0x86:
			FetchByte(btD);
			Exec_ADD_A_QIXd(btD);
			break;
		case 0x8C:
			Exec_ADC_A_r(RegIXH());
			break;
		case 0x8D:
			Exec_ADC_A_r(RegIXL());
			break;
		case 0x8E:
			FetchByte(btD);
			Exec_ADC_A_QIXd(btD);
			break;
		case 0x94:
			Exec_SUB_r(RegIXH());
			break;
		case 0x95:
			Exec_SUB_r(RegIXL());
			break;
		case 0x96:
			FetchByte(btD);
			Exec_SUB_QIXd(btD);
			break;
		case 0x9C:
			Exec_SBC_A_r(RegIXH());
			break;
		case 0x9D:
			Exec_SBC_A_r(RegIXL());
			break;
		case 0x9E:
			FetchByte(btD);
			Exec_SBC_A_QIXd(btD);
			break;
		case 0xA4:
			Exec_AND_r(RegIXH());
			break;
		case 0xA5:
			Exec_AND_r(RegIXL());
			break;
		case 0xA6:
			FetchByte(btD);
			Exec_AND_QIXd(btD);
			break;
		case 0xAC:
			Exec_XOR_r(RegIXH());
			break;
		case 0xAD:
			Exec_XOR_r(RegIXL());
			break;
		case 0xAE:
			FetchByte(btD);
			Exec_XOR_QIXd(btD);
			break;
		case 0xB4:
			Exec_OR_r(RegIXH());
			break;
		case 0xB5:
			Exec_OR_r(RegIXL());
			break;
		case 0xB6:
			FetchByte(btD);
			Exec_OR_QIXd(btD);
			break;
		case 0xBC:
			Exec_CP_r(RegIXH());
			break;
		case 0xBD:
			Exec_CP_r(RegIXL());
			break;
		case 0xBE:
			FetchByte(btD);
			Exec_CP_QIXd(btD);
			break;
		case 0xCB:
			FetchByte(btD);
			FetchByteM1(btX);
			IncRegR();
			Exec_DD_CB_X(btD, btX);
			break;
		case 0xE1:
			Exec_POP_IX();
			break;
		case 0xE3:
			Exec_EX_QSP_IX();
			break;
		case 0xE5:
			Exec_PUSH_IX();
			break;
		case 0xE9:
			Exec_JP_QIX();
			break;
		case 0xF9:
			Exec_LD_SP_IX();
			break;
		default:
			Exec_X(btOpCode);
			break;
		}
	}
	// extend OP code(DDH-CBH)
	void Exec_DD_CB_X(uint8_t btD, uint8_t btOpCode) {
		AddExecClock(CLOCK_DD_CB_X);
		switch (btOpCode) {
		case 0x00:
			Exec_RLC_r_QIXd(RegB(), btD);
			break;
		case 0x01:
			Exec_RLC_r_QIXd(RegC(), btD);
			break;
		case 0x02:
			Exec_RLC_r_QIXd(RegD(), btD);
			break;
		case 0x03:
			Exec_RLC_r_QIXd(RegE(), btD);
			break;
		case 0x04:
			Exec_RLC_r_QIXd(RegH(), btD);
			break;
		case 0x05:
			Exec_RLC_r_QIXd(RegL(), btD);
			break;
		case 0x06:
			Exec_RLC_QIXd(btD);
			break;
		case 0x07:
			Exec_RLC_r_QIXd(RegA(), btD);
			break;
		case 0x08:
			Exec_RRC_r_QIXd(RegB(), btD);
			break;
		case 0x09:
			Exec_RRC_r_QIXd(RegC(), btD);
			break;
		case 0x0A:
			Exec_RRC_r_QIXd(RegD(), btD);
			break;
		case 0x0B:
			Exec_RRC_r_QIXd(RegE(), btD);
			break;
		case 0x0C:
			Exec_RRC_r_QIXd(RegH(), btD);
			break;
		case 0x0D:
			Exec_RRC_r_QIXd(RegL(), btD);
			break;
		case 0x0E:
			Exec_RRC_QIXd(btD);
			break;
		case 0x0F:
			Exec_RRC_r_QIXd(RegA(), btD);
			break;
		case 0x10:
			Exec_RL_r_QIXd(RegB(), btD);
			break;
		case 0x11:
			Exec_RL_r_QIXd(RegC(), btD);
			break;
		case 0x12:
			Exec_RL_r_QIXd(RegD(), btD);
			break;
		case 0x13:
			Exec_RL_r_QIXd(RegE(), btD);
			break;
		case 0x14:
			Exec_RL_r_QIXd(RegH(), btD);
			break;
		case 0x15:
			Exec_RL_r_QIXd(RegL(), btD);
			break;
		case 0x16:
			Exec_RL_QIXd(btD);
			break;
		case 0x17:
			Exec_RL_r_QIXd(RegA(), btD);
			break;
		case 0x18:
			Exec_RR_r_QIXd(RegB(), btD);
			break;
		case 0x19:
			Exec_RR_r_QIXd(RegC(), btD);
			break;
		case 0x1A:
			Exec_RR_r_QIXd(RegD(), btD);
			break;
		case 0x1B:
			Exec_RR_r_QIXd(RegE(), btD);
			break;
		case 0x1C:
			Exec_RR_r_QIXd(RegH(), btD);
			break;
		case 0x1D:
			Exec_RR_r_QIXd(RegL(), btD);
			break;
		case 0x1E:
			Exec_RR_QIXd(btD);
			break;
		case 0x1F:
			Exec_RR_r_QIXd(RegA(), btD);
			break;
		case 0x20:
			Exec_SLA_r_QIXd(RegB(), btD);
			break;
		case 0x21:
			Exec_SLA_r_QIXd(RegC(), btD);
			break;
		case 0x22:
			Exec_SLA_r_QIXd(RegD(), btD);
			break;
		case 0x23:
			Exec_SLA_r_QIXd(RegE(), btD);
			break;
		case 0x24:
			Exec_SLA_r_QIXd(RegH(), btD);
			break;
		case 0x25:
			Exec_SLA_r_QIXd(RegL(), btD);
			break;
		case 0x26:
			Exec_SLA_QIXd(btD);
			break;
		case 0x27:
			Exec_SLA_r_QIXd(RegA(), btD);
			break;
		case 0x28:
			Exec_SRA_r_QIXd(RegB(), btD);
			break;
		case 0x29:
			Exec_SRA_r_QIXd(RegC(), btD);
			break;
		case 0x2A:
			Exec_SRA_r_QIXd(RegD(), btD);
			break;
		case 0x2B:
			Exec_SRA_r_QIXd(RegE(), btD);
			break;
		case 0x2C:
			Exec_SRA_r_QIXd(RegH(), btD);
			break;
		case 0x2D:
			Exec_SRA_r_QIXd(RegL(), btD);
			break;
		case 0x2E:
			Exec_SRA_QIXd(btD);
			break;
		case 0x2F:
			Exec_SRA_r_QIXd(RegA(), btD);
			break;
		case 0x30:
			Exec_SLL_r_QIXd(RegB(), btD);
			break;
		case 0x31:
			Exec_SLL_r_QIXd(RegC(), btD);
			break;
		case 0x32:
			Exec_SLL_r_QIXd(RegD(), btD);
			break;
		case 0x33:
			Exec_SLL_r_QIXd(RegE(), btD);
			break;
		case 0x34:
			Exec_SLL_r_QIXd(RegH(), btD);
			break;
		case 0x35:
			Exec_SLL_r_QIXd(RegL(), btD);
			break;
		case 0x36:
			Exec_SLL_QIXd(btD);
			break;
		case 0x37:
			Exec_SLL_r_QIXd(RegA(), btD);
			break;
		case 0x38:
			Exec_SRL_r_QIXd(RegB(), btD);
			break;
		case 0x39:
			Exec_SRL_r_QIXd(RegC(), btD);
			break;
		case 0x3A:
			Exec_SRL_r_QIXd(RegD(), btD);
			break;
		case 0x3B:
			Exec_SRL_r_QIXd(RegE(), btD);
			break;
		case 0x3C:
			Exec_SRL_r_QIXd(RegH(), btD);
			break;
		case 0x3D:
			Exec_SRL_r_QIXd(RegL(), btD);
			break;
		case 0x3E:
			Exec_SRL_QIXd(btD);
			break;
		case 0x3F:
			Exec_SRL_r_QIXd(RegA(), btD);
			break;
		case 0x40:
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x45:
		case 0x46:
		case 0x47:
			Exec_BIT_b_QIXd(0, btD);
			break;
		case 0x48:
		case 0x49:
		case 0x4A:
		case 0x4B:
		case 0x4C:
		case 0x4D:
		case 0x4E:
		case 0x4F:
			Exec_BIT_b_QIXd(1, btD);
			break;
		case 0x50:
		case 0x51:
		case 0x52:
		case 0x53:
		case 0x54:
		case 0x55:
		case 0x56:
		case 0x57:
			Exec_BIT_b_QIXd(2, btD);
			break;
		case 0x58:
		case 0x59:
		case 0x5A:
		case 0x5B:
		case 0x5C:
		case 0x5D:
		case 0x5E:
		case 0x5F:
			Exec_BIT_b_QIXd(3, btD);
			break;
		case 0x60:
		case 0x61:
		case 0x62:
		case 0x63:
		case 0x64:
		case 0x65:
		case 0x66:
		case 0x67:
			Exec_BIT_b_QIXd(4, btD);
			break;
		case 0x68:
		case 0x69:
		case 0x6A:
		case 0x6B:
		case 0x6C:
		case 0x6D:
		case 0x6E:
		case 0x6F:
			Exec_BIT_b_QIXd(5, btD);
			break;
		case 0x70:
		case 0x71:
		case 0x72:
		case 0x73:
		case 0x74:
		case 0x75:
		case 0x76:
		case 0x77:
			Exec_BIT_b_QIXd(6, btD);
			break;
		case 0x78:
		case 0x79:
		case 0x7A:
		case 0x7B:
		case 0x7C:
		case 0x7D:
		case 0x7E:
		case 0x7F:
			Exec_BIT_b_QIXd(7, btD);
			break;
		case 0x80:
			Exec_RES_b_r_QIXd(0, RegB(), btD);
			break;
		case 0x81:
			Exec_RES_b_r_QIXd(0, RegC(), btD);
			break;
		case 0x82:
			Exec_RES_b_r_QIXd(0, RegD(), btD);
			break;
		case 0x83:
			Exec_RES_b_r_QIXd(0, RegE(), btD);
			break;
		case 0x84:
			Exec_RES_b_r_QIXd(0, RegH(), btD);
			break;
		case 0x85:
			Exec_RES_b_r_QIXd(0, RegL(), btD);
			break;
		case 0x86:
			Exec_RES_b_QIXd(0, btD);
			break;
		case 0x87:
			Exec_RES_b_r_QIXd(0, RegA(), btD);
			break;
		case 0x88:
			Exec_RES_b_r_QIXd(1, RegB(), btD);
			break;
		case 0x89:
			Exec_RES_b_r_QIXd(1, RegC(), btD);
			break;
		case 0x8A:
			Exec_RES_b_r_QIXd(1, RegD(), btD);
			break;
		case 0x8B:
			Exec_RES_b_r_QIXd(1, RegE(), btD);
			break;
		case 0x8C:
			Exec_RES_b_r_QIXd(1, RegH(), btD);
			break;
		case 0x8D:
			Exec_RES_b_r_QIXd(1, RegL(), btD);
			break;
		case 0x8E:
			Exec_RES_b_QIXd(1, btD);
			break;
		case 0x8F:
			Exec_RES_b_r_QIXd(1, RegA(), btD);
			break;
		case 0x90:
			Exec_RES_b_r_QIXd(2, RegB(), btD);
			break;
		case 0x91:
			Exec_RES_b_r_QIXd(2, RegC(), btD);
			break;
		case 0x92:
			Exec_RES_b_r_QIXd(2, RegD(), btD);
			break;
		case 0x93:
			Exec_RES_b_r_QIXd(2, RegE(), btD);
			break;
		case 0x94:
			Exec_RES_b_r_QIXd(2, RegH(), btD);
			break;
		case 0x95:
			Exec_RES_b_r_QIXd(2, RegL(), btD);
			break;
		case 0x96:
			Exec_RES_b_QIXd(2, btD);
			break;
		case 0x97:
			Exec_RES_b_r_QIXd(2, RegA(), btD);
			break;
		case 0x98:
			Exec_RES_b_r_QIXd(3, RegB(), btD);
			break;
		case 0x99:
			Exec_RES_b_r_QIXd(3, RegC(), btD);
			break;
		case 0x9A:
			Exec_RES_b_r_QIXd(3, RegD(), btD);
			break;
		case 0x9B:
			Exec_RES_b_r_QIXd(3, RegE(), btD);
			break;
		case 0x9C:
			Exec_RES_b_r_QIXd(3, RegH(), btD);
			break;
		case 0x9D:
			Exec_RES_b_r_QIXd(3, RegL(), btD);
			break;
		case 0x9E:
			Exec_RES_b_QIXd(3, btD);
			break;
		case 0x9F:
			Exec_RES_b_r_QIXd(3, RegA(), btD);
			break;
		case 0xA0:
			Exec_RES_b_r_QIXd(4, RegB(), btD);
			break;
		case 0xA1:
			Exec_RES_b_r_QIXd(4, RegC(), btD);
			break;
		case 0xA2:
			Exec_RES_b_r_QIXd(4, RegD(), btD);
			break;
		case 0xA3:
			Exec_RES_b_r_QIXd(4, RegE(), btD);
			break;
		case 0xA4:
			Exec_RES_b_r_QIXd(4, RegH(), btD);
			break;
		case 0xA5:
			Exec_RES_b_r_QIXd(4, RegL(), btD);
			break;
		case 0xA6:
			Exec_RES_b_QIXd(4, btD);
			break;
		case 0xA7:
			Exec_RES_b_r_QIXd(4, RegA(), btD);
			break;
		case 0xA8:
			Exec_RES_b_r_QIXd(5, RegB(), btD);
			break;
		case 0xA9:
			Exec_RES_b_r_QIXd(5, RegC(), btD);
			break;
		case 0xAA:
			Exec_RES_b_r_QIXd(5, RegD(), btD);
			break;
		case 0xAB:
			Exec_RES_b_r_QIXd(5, RegE(), btD);
			break;
		case 0xAC:
			Exec_RES_b_r_QIXd(5, RegH(), btD);
			break;
		case 0xAD:
			Exec_RES_b_r_QIXd(5, RegL(), btD);
			break;
		case 0xAE:
			Exec_RES_b_QIXd(5, btD);
			break;
		case 0xAF:
			Exec_RES_b_r_QIXd(5, RegA(), btD);
			break;
		case 0xB0:
			Exec_RES_b_r_QIXd(6, RegB(), btD);
			break;
		case 0xB1:
			Exec_RES_b_r_QIXd(6, RegC(), btD);
			break;
		case 0xB2:
			Exec_RES_b_r_QIXd(6, RegD(), btD);
			break;
		case 0xB3:
			Exec_RES_b_r_QIXd(6, RegE(), btD);
			break;
		case 0xB4:
			Exec_RES_b_r_QIXd(6, RegH(), btD);
			break;
		case 0xB5:
			Exec_RES_b_r_QIXd(6, RegL(), btD);
			break;
		case 0xB6:
			Exec_RES_b_QIXd(6, btD);
			break;
		case 0xB7:
			Exec_RES_b_r_QIXd(6, RegA(), btD);
			break;
		case 0xB8:
			Exec_RES_b_r_QIXd(7, RegB(), btD);
			break;
		case 0xB9:
			Exec_RES_b_r_QIXd(7, RegC(), btD);
			break;
		case 0xBA:
			Exec_RES_b_r_QIXd(7, RegD(), btD);
			break;
		case 0xBB:
			Exec_RES_b_r_QIXd(7, RegE(), btD);
			break;
		case 0xBC:
			Exec_RES_b_r_QIXd(7, RegH(), btD);
			break;
		case 0xBD:
			Exec_RES_b_r_QIXd(7, RegL(), btD);
			break;
		case 0xBE:
			Exec_RES_b_QIXd(7, btD);
			break;
		case 0xBF:
			Exec_RES_b_r_QIXd(7, RegA(), btD);
			break;
		case 0xC0:
			Exec_SET_b_r_QIXd(0, RegB(), btD);
			break;
		case 0xC1:
			Exec_SET_b_r_QIXd(0, RegC(), btD);
			break;
		case 0xC2:
			Exec_SET_b_r_QIXd(0, RegD(), btD);
			break;
		case 0xC3:
			Exec_SET_b_r_QIXd(0, RegE(), btD);
			break;
		case 0xC4:
			Exec_SET_b_r_QIXd(0, RegH(), btD);
			break;
		case 0xC5:
			Exec_SET_b_r_QIXd(0, RegL(), btD);
			break;
		case 0xC6:
			Exec_SET_b_QIXd(0, btD);
			break;
		case 0xC7:
			Exec_SET_b_r_QIXd(0, RegA(), btD);
			break;
		case 0xC8:
			Exec_SET_b_r_QIXd(1, RegB(), btD);
			break;
		case 0xC9:
			Exec_SET_b_r_QIXd(1, RegC(), btD);
			break;
		case 0xCA:
			Exec_SET_b_r_QIXd(1, RegD(), btD);
			break;
		case 0xCB:
			Exec_SET_b_r_QIXd(1, RegE(), btD);
			break;
		case 0xCC:
			Exec_SET_b_r_QIXd(1, RegH(), btD);
			break;
		case 0xCD:
			Exec_SET_b_r_QIXd(1, RegL(), btD);
			break;
		case 0xCE:
			Exec_SET_b_QIXd(1, btD);
			break;
		case 0xCF:
			Exec_SET_b_r_QIXd(1, RegA(), btD);
			break;
		case 0xD0:
			Exec_SET_b_r_QIXd(2, RegB(), btD);
			break;
		case 0xD1:
			Exec_SET_b_r_QIXd(2, RegC(), btD);
			break;
		case 0xD2:
			Exec_SET_b_r_QIXd(2, RegD(), btD);
			break;
		case 0xD3:
			Exec_SET_b_r_QIXd(2, RegE(), btD);
			break;
		case 0xD4:
			Exec_SET_b_r_QIXd(2, RegH(), btD);
			break;
		case 0xD5:
			Exec_SET_b_r_QIXd(2, RegL(), btD);
			break;
		case 0xD6:
			Exec_SET_b_QIXd(2, btD);
			break;
		case 0xD7:
			Exec_SET_b_r_QIXd(2, RegA(), btD);
			break;
		case 0xD8:
			Exec_SET_b_r_QIXd(3, RegB(), btD);
			break;
		case 0xD9:
			Exec_SET_b_r_QIXd(3, RegC(), btD);
			break;
		case 0xDA:
			Exec_SET_b_r_QIXd(3, RegD(), btD);
			break;
		case 0xDB:
			Exec_SET_b_r_QIXd(3, RegE(), btD);
			break;
		case 0xDC:
			Exec_SET_b_r_QIXd(3, RegH(), btD);
			break;
		case 0xDD:
			Exec_SET_b_r_QIXd(3, RegL(), btD);
			break;
		case 0xDE:
			Exec_SET_b_QIXd(3, btD);
			break;
		case 0xDF:
			Exec_SET_b_r_QIXd(3, RegA(), btD);
			break;
		case 0xE0:
			Exec_SET_b_r_QIXd(4, RegB(), btD);
			break;
		case 0xE1:
			Exec_SET_b_r_QIXd(4, RegC(), btD);
			break;
		case 0xE2:
			Exec_SET_b_r_QIXd(4, RegD(), btD);
			break;
		case 0xE3:
			Exec_SET_b_r_QIXd(4, RegE(), btD);
			break;
		case 0xE4:
			Exec_SET_b_r_QIXd(4, RegH(), btD);
			break;
		case 0xE5:
			Exec_SET_b_r_QIXd(4, RegL(), btD);
			break;
		case 0xE6:
			Exec_SET_b_QIXd(4, btD);
			break;
		case 0xE7:
			Exec_SET_b_r_QIXd(4, RegA(), btD);
			break;
		case 0xE8:
			Exec_SET_b_r_QIXd(5, RegB(), btD);
			break;
		case 0xE9:
			Exec_SET_b_r_QIXd(5, RegC(), btD);
			break;
		case 0xEA:
			Exec_SET_b_r_QIXd(5, RegD(), btD);
			break;
		case 0xEB:
			Exec_SET_b_r_QIXd(5, RegE(), btD);
			break;
		case 0xEC:
			Exec_SET_b_r_QIXd(5, RegH(), btD);
			break;
		case 0xED:
			Exec_SET_b_r_QIXd(5, RegL(), btD);
			break;
		case 0xEE:
			Exec_SET_b_QIXd(5, btD);
			break;
		case 0xEF:
			Exec_SET_b_r_QIXd(5, RegA(), btD);
			break;
		case 0xF0:
			Exec_SET_b_r_QIXd(6, RegB(), btD);
			break;
		case 0xF1:
			Exec_SET_b_r_QIXd(6, RegC(), btD);
			break;
		case 0xF2:
			Exec_SET_b_r_QIXd(6, RegD(), btD);
			break;
		case 0xF3:
			Exec_SET_b_r_QIXd(6, RegE(), btD);
			break;
		case 0xF4:
			Exec_SET_b_r_QIXd(6, RegH(), btD);
			break;
		case 0xF5:
			Exec_SET_b_r_QIXd(6, RegL(), btD);
			break;
		case 0xF6:
			Exec_SET_b_QIXd(6, btD);
			break;
		case 0xF7:
			Exec_SET_b_r_QIXd(6, RegA(), btD);
			break;
		case 0xF8:
			Exec_SET_b_r_QIXd(7, RegB(), btD);
			break;
		case 0xF9:
			Exec_SET_b_r_QIXd(7, RegC(), btD);
			break;
		case 0xFA:
			Exec_SET_b_r_QIXd(7, RegD(), btD);
			break;
		case 0xFB:
			Exec_SET_b_r_QIXd(7, RegE(), btD);
			break;
		case 0xFC:
			Exec_SET_b_r_QIXd(7, RegH(), btD);
			break;
		case 0xFD:
			Exec_SET_b_r_QIXd(7, RegL(), btD);
			break;
		case 0xFE:
			Exec_SET_b_QIXd(7, btD);
			break;
		case 0xFF:
			Exec_SET_b_r_QIXd(7, RegA(), btD);
			break;
		}
	}
	// extend OP code(FDH)
	void Exec_FD_X(uint8_t btOpCode) {
		uint8_t btN, btD, btX;
		uint16_t wNN;
		AddExecClock(CLOCK_FD_X);
		switch (btOpCode) {
		case 0x09:
			Exec_ADD_IY_ss(RegBC());
			break;
		case 0x19:
			Exec_ADD_IY_ss(RegDE());
			break;
		case 0x21:
			FetchWord(wNN);
			Exec_LD_IY_nn(wNN);
			break;
		case 0x22:
			FetchWord(wNN);
			Exec_LD_Qnn_IY(wNN);
			break;
		case 0x23:
			Exec_INC_IY();
			break;
		case 0x24:
			Exec_INC_r(RegIYH());
			break;
		case 0x25:
			Exec_DEC_r(RegIYH());
			break;
		case 0x26:
			FetchByte(btN);
			Exec_LD_r_n(RegIYH(), btN);
			break;
		case 0x29:
			Exec_ADD_IY_ss(RegIY());
			break;
		case 0x2A:
			FetchWord(wNN);
			Exec_LD_IY_Qnn(wNN);
			break;
		case 0x2B:
			Exec_DEC_IY();
			break;
		case 0x2C:
			Exec_INC_r(RegIYL());
			break;
		case 0x2D:
			Exec_DEC_r(RegIYL());
			break;
		case 0x2E:
			FetchByte(btN);
			Exec_LD_r_n(RegIYL(), btN);
			break;
		case 0x34:
			FetchByte(btD);
			Exec_INC_QIYd(btD);
			break;
		case 0x35:
			FetchByte(btD);
			Exec_DEC_QIYd(btD);
			break;
		case 0x36:
			FetchByte(btD);
			FetchByte(btN);
			Exec_LD_QIYd_n(btD, btN);
			break;
		case 0x39:
			Exec_ADD_IY_ss(RegSP());
			break;
		case 0x44:
			Exec_LD_r_r2(RegB(), RegIYH());
			break;
		case 0x45:
			Exec_LD_r_r2(RegB(), RegIYL());
			break;
		case 0x46:
			FetchByte(btD);
			Exec_LD_r_QIYd(RegB(), btD);
			break;
		case 0x4C:
			Exec_LD_r_r2(RegC(), RegIYH());
			break;
		case 0x4D:
			Exec_LD_r_r2(RegC(), RegIYL());
			break;
		case 0x4E:
			FetchByte(btD);
			Exec_LD_r_QIYd(RegC(), btD);
			break;
		case 0x54:
			Exec_LD_r_r2(RegD(), RegIYH());
			break;
		case 0x55:
			Exec_LD_r_r2(RegD(), RegIYL());
			break;
		case 0x56:
			FetchByte(btD);
			Exec_LD_r_QIYd(RegD(), btD);
			break;
		case 0x5C:
			Exec_LD_r_r2(RegE(), RegIYH());
			break;
		case 0x5D:
			Exec_LD_r_r2(RegE(), RegIYL());
			break;
		case 0x5E:
			FetchByte(btD);
			Exec_LD_r_QIYd(RegE(), btD);
			break;
		case 0x60:
			Exec_LD_r_r2(RegIYH(), RegB());
			break;
		case 0x61:
			Exec_LD_r_r2(RegIYH(), RegC());
			break;
		case 0x62:
			Exec_LD_r_r2(RegIYH(), RegD());
			break;
		case 0x63:
			Exec_LD_r_r2(RegIYH(), RegE());
			break;
		case 0x64:
			Exec_LD_r_r2(RegIYH(), RegIYH());
			break;
		case 0x65:
			Exec_LD_r_r2(RegIYH(), RegIYL());
			break;
		case 0x66:
			FetchByte(btD);
			Exec_LD_r_QIYd(RegH(), btD);
			break;
		case 0x67:
			Exec_LD_r_r2(RegIYH(), RegA());
			break;
		case 0x68:
			Exec_LD_r_r2(RegIYL(), RegB());
			break;
		case 0x69:
			Exec_LD_r_r2(RegIYL(), RegC());
			break;
		case 0x6A:
			Exec_LD_r_r2(RegIYL(), RegD());
			break;
		case 0x6B:
			Exec_LD_r_r2(RegIYL(), RegE());
			break;
		case 0x6C:
			Exec_LD_r_r2(RegIYL(), RegIYH());
			break;
		case 0x6D:
			Exec_LD_r_r2(RegIYL(), RegIYL());
			break;
		case 0x6E:
			FetchByte(btD);
			Exec_LD_r_QIYd(RegL(), btD);
			break;
		case 0x6F:
			Exec_LD_r_r2(RegIYL(), RegA());
			break;
		case 0x70:
			FetchByte(btD);
			Exec_LD_QIYd_r(btD, RegB());
			break;
		case 0x71:
			FetchByte(btD);
			Exec_LD_QIYd_r(btD, RegC());
			break;
		case 0x72:
			FetchByte(btD);
			Exec_LD_QIYd_r(btD, RegD());
			break;
		case 0x73:
			FetchByte(btD);
			Exec_LD_QIYd_r(btD, RegE());
			break;
		case 0x74:
			FetchByte(btD);
			Exec_LD_QIYd_r(btD, RegH());
			break;
		case 0x75:
			FetchByte(btD);
			Exec_LD_QIYd_r(btD, RegL());
			break;
		case 0x77:
			FetchByte(btD);
			Exec_LD_QIYd_r(btD, RegA());
			break;
		case 0x7C:
			Exec_LD_r_r2(RegA(), RegIYH());
			break;
		case 0x7D:
			Exec_LD_r_r2(RegA(), RegIYL());
			break;
		case 0x7E:
			FetchByte(btD);
			Exec_LD_r_QIYd(RegA(), btD);
			break;
		case 0x84:
			Exec_ADD_A_r(RegIYH());
			break;
		case 0x85:
			Exec_ADD_A_r(RegIYL());
			break;
		case 0x86:
			FetchByte(btD);
			Exec_ADD_A_QIYd(btD);
			break;
		case 0x8C:
			Exec_ADC_A_r(RegIYH());
			break;
		case 0x8D:
			Exec_ADC_A_r(RegIYL());
			break;
		case 0x8E:
			FetchByte(btD);
			Exec_ADC_A_QIYd(btD);
			break;
		case 0x94:
			Exec_SUB_r(RegIYH());
			break;
		case 0x95:
			Exec_SUB_r(RegIYL());
			break;
		case 0x96:
			FetchByte(btD);
			Exec_SUB_QIYd(btD);
			break;
		case 0x9C:
			Exec_SBC_A_r(RegIYH());
			break;
		case 0x9D:
			Exec_SBC_A_r(RegIYL());
			break;
		case 0x9E:
			FetchByte(btD);
			Exec_SBC_A_QIYd(btD);
			break;
		case 0xA4:
			Exec_AND_r(RegIYH());
			break;
		case 0xA5:
			Exec_AND_r(RegIYL());
			break;
		case 0xA6:
			FetchByte(btD);
			Exec_AND_QIYd(btD);
			break;
		case 0xAC:
			Exec_XOR_r(RegIYH());
			break;
		case 0xAD:
			Exec_XOR_r(RegIYL());
			break;
		case 0xAE:
			FetchByte(btD);
			Exec_XOR_QIYd(btD);
			break;
		case 0xB4:
			Exec_OR_r(RegIYH());
			break;
		case 0xB5:
			Exec_OR_r(RegIYL());
			break;
		case 0xB6:
			FetchByte(btD);
			Exec_OR_QIYd(btD);
			break;
		case 0xBC:
			Exec_CP_r(RegIYH());
			break;
		case 0xBD:
			Exec_CP_r(RegIYL());
			break;
		case 0xBE:
			FetchByte(btD);
			Exec_CP_QIYd(btD);
			break;
		case 0xCB:
			FetchByte(btD);
			FetchByteM1(btX);
			IncRegR();
			Exec_FD_CB_X(btD, btX);
			break;
		case 0xE1:
			Exec_POP_IY();
			break;
		case 0xE3:
			Exec_EX_QSP_IY();
			break;
		case 0xE5:
			Exec_PUSH_IY();
			break;
		case 0xE9:
			Exec_JP_QIY();
			break;
		case 0xF9:
			Exec_LD_SP_IY();
			break;
		default:
			Exec_X(btOpCode);
			break;
		}
	}
	// extend OP code(FDH-CBH)
	void Exec_FD_CB_X(uint8_t btD, uint8_t btOpCode) {
		AddExecClock(CLOCK_FD_CB_X);
		switch (btOpCode) {
		case 0x00:
			Exec_RLC_r_QIYd(RegB(), btD);
			break;
		case 0x01:
			Exec_RLC_r_QIYd(RegC(), btD);
			break;
		case 0x02:
			Exec_RLC_r_QIYd(RegD(), btD);
			break;
		case 0x03:
			Exec_RLC_r_QIYd(RegE(), btD);
			break;
		case 0x04:
			Exec_RLC_r_QIYd(RegH(), btD);
			break;
		case 0x05:
			Exec_RLC_r_QIYd(RegL(), btD);
			break;
		case 0x06:
			Exec_RLC_QIYd(btD);
			break;
		case 0x07:
			Exec_RLC_r_QIYd(RegA(), btD);
			break;
		case 0x08:
			Exec_RRC_r_QIYd(RegB(), btD);
			break;
		case 0x09:
			Exec_RRC_r_QIYd(RegC(), btD);
			break;
		case 0x0A:
			Exec_RRC_r_QIYd(RegD(), btD);
			break;
		case 0x0B:
			Exec_RRC_r_QIYd(RegE(), btD);
			break;
		case 0x0C:
			Exec_RRC_r_QIYd(RegH(), btD);
			break;
		case 0x0D:
			Exec_RRC_r_QIYd(RegL(), btD);
			break;
		case 0x0E:
			Exec_RRC_QIYd(btD);
			break;
		case 0x0F:
			Exec_RRC_r_QIYd(RegA(), btD);
			break;
		case 0x10:
			Exec_RL_r_QIYd(RegB(), btD);
			break;
		case 0x11:
			Exec_RL_r_QIYd(RegC(), btD);
			break;
		case 0x12:
			Exec_RL_r_QIYd(RegD(), btD);
			break;
		case 0x13:
			Exec_RL_r_QIYd(RegE(), btD);
			break;
		case 0x14:
			Exec_RL_r_QIYd(RegH(), btD);
			break;
		case 0x15:
			Exec_RL_r_QIYd(RegL(), btD);
			break;
		case 0x16:
			Exec_RL_QIYd(btD);
			break;
		case 0x17:
			Exec_RL_r_QIYd(RegA(), btD);
			break;
		case 0x18:
			Exec_RR_r_QIYd(RegB(), btD);
			break;
		case 0x19:
			Exec_RR_r_QIYd(RegC(), btD);
			break;
		case 0x1A:
			Exec_RR_r_QIYd(RegD(), btD);
			break;
		case 0x1B:
			Exec_RR_r_QIYd(RegE(), btD);
			break;
		case 0x1C:
			Exec_RR_r_QIYd(RegH(), btD);
			break;
		case 0x1D:
			Exec_RR_r_QIYd(RegL(), btD);
			break;
		case 0x1E:
			Exec_RR_QIYd(btD);
			break;
		case 0x1F:
			Exec_RR_r_QIYd(RegA(), btD);
			break;
		case 0x20:
			Exec_SLA_r_QIYd(RegB(), btD);
			break;
		case 0x21:
			Exec_SLA_r_QIYd(RegC(), btD);
			break;
		case 0x22:
			Exec_SLA_r_QIYd(RegD(), btD);
			break;
		case 0x23:
			Exec_SLA_r_QIYd(RegE(), btD);
			break;
		case 0x24:
			Exec_SLA_r_QIYd(RegH(), btD);
			break;
		case 0x25:
			Exec_SLA_r_QIYd(RegL(), btD);
			break;
		case 0x26:
			Exec_SLA_QIYd(btD);
			break;
		case 0x27:
			Exec_SLA_r_QIYd(RegA(), btD);
			break;
		case 0x28:
			Exec_SRA_r_QIYd(RegB(), btD);
			break;
		case 0x29:
			Exec_SRA_r_QIYd(RegC(), btD);
			break;
		case 0x2A:
			Exec_SRA_r_QIYd(RegD(), btD);
			break;
		case 0x2B:
			Exec_SRA_r_QIYd(RegE(), btD);
			break;
		case 0x2C:
			Exec_SRA_r_QIYd(RegH(), btD);
			break;
		case 0x2D:
			Exec_SRA_r_QIYd(RegL(), btD);
			break;
		case 0x2E:
			Exec_SRA_QIYd(btD);
			break;
		case 0x2F:
			Exec_SRA_r_QIYd(RegA(), btD);
			break;
		case 0x30:
			Exec_SLL_r_QIYd(RegB(), btD);
			break;
		case 0x31:
			Exec_SLL_r_QIYd(RegC(), btD);
			break;
		case 0x32:
			Exec_SLL_r_QIYd(RegD(), btD);
			break;
		case 0x33:
			Exec_SLL_r_QIYd(RegE(), btD);
			break;
		case 0x34:
			Exec_SLL_r_QIYd(RegH(), btD);
			break;
		case 0x35:
			Exec_SLL_r_QIYd(RegL(), btD);
			break;
		case 0x36:
			Exec_SLL_QIYd(btD);
			break;
		case 0x37:
			Exec_SLL_r_QIYd(RegA(), btD);
			break;
		case 0x38:
			Exec_SRL_r_QIYd(RegB(), btD);
			break;
		case 0x39:
			Exec_SRL_r_QIYd(RegC(), btD);
			break;
		case 0x3A:
			Exec_SRL_r_QIYd(RegD(), btD);
			break;
		case 0x3B:
			Exec_SRL_r_QIYd(RegE(), btD);
			break;
		case 0x3C:
			Exec_SRL_r_QIYd(RegH(), btD);
			break;
		case 0x3D:
			Exec_SRL_r_QIYd(RegL(), btD);
			break;
		case 0x3E:
			Exec_SRL_QIYd(btD);
			break;
		case 0x3F:
			Exec_SRL_r_QIYd(RegA(), btD);
			break;
		case 0x40:
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x45:
		case 0x46:
		case 0x47:
			Exec_BIT_b_QIYd(0, btD);
			break;
		case 0x48:
		case 0x49:
		case 0x4A:
		case 0x4B:
		case 0x4C:
		case 0x4D:
		case 0x4E:
		case 0x4F:
			Exec_BIT_b_QIYd(1, btD);
			break;
		case 0x50:
		case 0x51:
		case 0x52:
		case 0x53:
		case 0x54:
		case 0x55:
		case 0x56:
		case 0x57:
			Exec_BIT_b_QIYd(2, btD);
			break;
		case 0x58:
		case 0x59:
		case 0x5A:
		case 0x5B:
		case 0x5C:
		case 0x5D:
		case 0x5E:
		case 0x5F:
			Exec_BIT_b_QIYd(3, btD);
			break;
		case 0x60:
		case 0x61:
		case 0x62:
		case 0x63:
		case 0x64:
		case 0x65:
		case 0x66:
		case 0x67:
			Exec_BIT_b_QIYd(4, btD);
			break;
		case 0x68:
		case 0x69:
		case 0x6A:
		case 0x6B:
		case 0x6C:
		case 0x6D:
		case 0x6E:
		case 0x6F:
			Exec_BIT_b_QIYd(5, btD);
			break;
		case 0x70:
		case 0x71:
		case 0x72:
		case 0x73:
		case 0x74:
		case 0x75:
		case 0x76:
		case 0x77:
			Exec_BIT_b_QIYd(6, btD);
			break;
		case 0x78:
		case 0x79:
		case 0x7A:
		case 0x7B:
		case 0x7C:
		case 0x7D:
		case 0x7E:
		case 0x7F:
			Exec_BIT_b_QIYd(7, btD);
			break;
		case 0x80:
			Exec_RES_b_r_QIYd(0, RegB(), btD);
			break;
		case 0x81:
			Exec_RES_b_r_QIYd(0, RegC(), btD);
			break;
		case 0x82:
			Exec_RES_b_r_QIYd(0, RegD(), btD);
			break;
		case 0x83:
			Exec_RES_b_r_QIYd(0, RegE(), btD);
			break;
		case 0x84:
			Exec_RES_b_r_QIYd(0, RegH(), btD);
			break;
		case 0x85:
			Exec_RES_b_r_QIYd(0, RegL(), btD);
			break;
		case 0x86:
			Exec_RES_b_QIYd(0, btD);
			break;
		case 0x87:
			Exec_RES_b_r_QIYd(0, RegA(), btD);
			break;
		case 0x88:
			Exec_RES_b_r_QIYd(1, RegB(), btD);
			break;
		case 0x89:
			Exec_RES_b_r_QIYd(1, RegC(), btD);
			break;
		case 0x8A:
			Exec_RES_b_r_QIYd(1, RegD(), btD);
			break;
		case 0x8B:
			Exec_RES_b_r_QIYd(1, RegE(), btD);
			break;
		case 0x8C:
			Exec_RES_b_r_QIYd(1, RegH(), btD);
			break;
		case 0x8D:
			Exec_RES_b_r_QIYd(1, RegL(), btD);
			break;
		case 0x8E:
			Exec_RES_b_QIYd(1, btD);
			break;
		case 0x8F:
			Exec_RES_b_r_QIYd(1, RegA(), btD);
			break;
		case 0x90:
			Exec_RES_b_r_QIYd(2, RegB(), btD);
			break;
		case 0x91:
			Exec_RES_b_r_QIYd(2, RegC(), btD);
			break;
		case 0x92:
			Exec_RES_b_r_QIYd(2, RegD(), btD);
			break;
		case 0x93:
			Exec_RES_b_r_QIYd(2, RegE(), btD);
			break;
		case 0x94:
			Exec_RES_b_r_QIYd(2, RegH(), btD);
			break;
		case 0x95:
			Exec_RES_b_r_QIYd(2, RegL(), btD);
			break;
		case 0x96:
			Exec_RES_b_QIYd(2, btD);
			break;
		case 0x97:
			Exec_RES_b_r_QIYd(2, RegA(), btD);
			break;
		case 0x98:
			Exec_RES_b_r_QIYd(3, RegB(), btD);
			break;
		case 0x99:
			Exec_RES_b_r_QIYd(3, RegC(), btD);
			break;
		case 0x9A:
			Exec_RES_b_r_QIYd(3, RegD(), btD);
			break;
		case 0x9B:
			Exec_RES_b_r_QIYd(3, RegE(), btD);
			break;
		case 0x9C:
			Exec_RES_b_r_QIYd(3, RegH(), btD);
			break;
		case 0x9D:
			Exec_RES_b_r_QIYd(3, RegL(), btD);
			break;
		case 0x9E:
			Exec_RES_b_QIYd(3, btD);
			break;
		case 0x9F:
			Exec_RES_b_r_QIYd(3, RegA(), btD);
			break;
		case 0xA0:
			Exec_RES_b_r_QIYd(4, RegB(), btD);
			break;
		case 0xA1:
			Exec_RES_b_r_QIYd(4, RegC(), btD);
			break;
		case 0xA2:
			Exec_RES_b_r_QIYd(4, RegD(), btD);
			break;
		case 0xA3:
			Exec_RES_b_r_QIYd(4, RegE(), btD);
			break;
		case 0xA4:
			Exec_RES_b_r_QIYd(4, RegH(), btD);
			break;
		case 0xA5:
			Exec_RES_b_r_QIYd(4, RegL(), btD);
			break;
		case 0xA6:
			Exec_RES_b_QIYd(4, btD);
			break;
		case 0xA7:
			Exec_RES_b_r_QIYd(4, RegA(), btD);
			break;
		case 0xA8:
			Exec_RES_b_r_QIYd(5, RegB(), btD);
			break;
		case 0xA9:
			Exec_RES_b_r_QIYd(5, RegC(), btD);
			break;
		case 0xAA:
			Exec_RES_b_r_QIYd(5, RegD(), btD);
			break;
		case 0xAB:
			Exec_RES_b_r_QIYd(5, RegE(), btD);
			break;
		case 0xAC:
			Exec_RES_b_r_QIYd(5, RegH(), btD);
			break;
		case 0xAD:
			Exec_RES_b_r_QIYd(5, RegL(), btD);
			break;
		case 0xAE:
			Exec_RES_b_QIYd(5, btD);
			break;
		case 0xAF:
			Exec_RES_b_r_QIYd(5, RegA(), btD);
			break;
		case 0xB0:
			Exec_RES_b_r_QIYd(6, RegB(), btD);
			break;
		case 0xB1:
			Exec_RES_b_r_QIYd(6, RegC(), btD);
			break;
		case 0xB2:
			Exec_RES_b_r_QIYd(6, RegD(), btD);
			break;
		case 0xB3:
			Exec_RES_b_r_QIYd(6, RegE(), btD);
			break;
		case 0xB4:
			Exec_RES_b_r_QIYd(6, RegH(), btD);
			break;
		case 0xB5:
			Exec_RES_b_r_QIYd(6, RegL(), btD);
			break;
		case 0xB6:
			Exec_RES_b_QIYd(6, btD);
			break;
		case 0xB7:
			Exec_RES_b_r_QIYd(6, RegA(), btD);
			break;
		case 0xB8:
			Exec_RES_b_r_QIYd(7, RegB(), btD);
			break;
		case 0xB9:
			Exec_RES_b_r_QIYd(7, RegC(), btD);
			break;
		case 0xBA:
			Exec_RES_b_r_QIYd(7, RegD(), btD);
			break;
		case 0xBB:
			Exec_RES_b_r_QIYd(7, RegE(), btD);
			break;
		case 0xBC:
			Exec_RES_b_r_QIYd(7, RegH(), btD);
			break;
		case 0xBD:
			Exec_RES_b_r_QIYd(7, RegL(), btD);
			break;
		case 0xBE:
			Exec_RES_b_QIYd(7, btD);
			break;
		case 0xBF:
			Exec_RES_b_r_QIYd(7, RegA(), btD);
			break;
		case 0xC0:
			Exec_SET_b_r_QIYd(0, RegB(), btD);
			break;
		case 0xC1:
			Exec_SET_b_r_QIYd(0, RegC(), btD);
			break;
		case 0xC2:
			Exec_SET_b_r_QIYd(0, RegD(), btD);
			break;
		case 0xC3:
			Exec_SET_b_r_QIYd(0, RegE(), btD);
			break;
		case 0xC4:
			Exec_SET_b_r_QIYd(0, RegH(), btD);
			break;
		case 0xC5:
			Exec_SET_b_r_QIYd(0, RegL(), btD);
			break;
		case 0xC6:
			Exec_SET_b_QIYd(0, btD);
			break;
		case 0xC7:
			Exec_SET_b_r_QIYd(0, RegA(), btD);
			break;
		case 0xC8:
			Exec_SET_b_r_QIYd(1, RegB(), btD);
			break;
		case 0xC9:
			Exec_SET_b_r_QIYd(1, RegC(), btD);
			break;
		case 0xCA:
			Exec_SET_b_r_QIYd(1, RegD(), btD);
			break;
		case 0xCB:
			Exec_SET_b_r_QIYd(1, RegE(), btD);
			break;
		case 0xCC:
			Exec_SET_b_r_QIYd(1, RegH(), btD);
			break;
		case 0xCD:
			Exec_SET_b_r_QIYd(1, RegL(), btD);
			break;
		case 0xCE:
			Exec_SET_b_QIYd(1, btD);
			break;
		case 0xCF:
			Exec_SET_b_r_QIYd(1, RegA(), btD);
			break;
		case 0xD0:
			Exec_SET_b_r_QIYd(2, RegB(), btD);
			break;
		case 0xD1:
			Exec_SET_b_r_QIYd(2, RegC(), btD);
			break;
		case 0xD2:
			Exec_SET_b_r_QIYd(2, RegD(), btD);
			break;
		case 0xD3:
			Exec_SET_b_r_QIYd(2, RegE(), btD);
			break;
		case 0xD4:
			Exec_SET_b_r_QIYd(2, RegH(), btD);
			break;
		case 0xD5:
			Exec_SET_b_r_QIYd(2, RegL(), btD);
			break;
		case 0xD6:
			Exec_SET_b_QIYd(2, btD);
			break;
		case 0xD7:
			Exec_SET_b_r_QIYd(2, RegA(), btD);
			break;
		case 0xD8:
			Exec_SET_b_r_QIYd(3, RegB(), btD);
			break;
		case 0xD9:
			Exec_SET_b_r_QIYd(3, RegC(), btD);
			break;
		case 0xDA:
			Exec_SET_b_r_QIYd(3, RegD(), btD);
			break;
		case 0xDB:
			Exec_SET_b_r_QIYd(3, RegE(), btD);
			break;
		case 0xDC:
			Exec_SET_b_r_QIYd(3, RegH(), btD);
			break;
		case 0xDD:
			Exec_SET_b_r_QIYd(3, RegL(), btD);
			break;
		case 0xDE:
			Exec_SET_b_QIYd(3, btD);
			break;
		case 0xDF:
			Exec_SET_b_r_QIYd(3, RegA(), btD);
			break;
		case 0xE0:
			Exec_SET_b_r_QIYd(4, RegB(), btD);
			break;
		case 0xE1:
			Exec_SET_b_r_QIYd(4, RegC(), btD);
			break;
		case 0xE2:
			Exec_SET_b_r_QIYd(4, RegD(), btD);
			break;
		case 0xE3:
			Exec_SET_b_r_QIYd(4, RegE(), btD);
			break;
		case 0xE4:
			Exec_SET_b_r_QIYd(4, RegH(), btD);
			break;
		case 0xE5:
			Exec_SET_b_r_QIYd(4, RegL(), btD);
			break;
		case 0xE6:
			Exec_SET_b_QIYd(4, btD);
			break;
		case 0xE7:
			Exec_SET_b_r_QIYd(4, RegA(), btD);
			break;
		case 0xE8:
			Exec_SET_b_r_QIYd(5, RegB(), btD);
			break;
		case 0xE9:
			Exec_SET_b_r_QIYd(5, RegC(), btD);
			break;
		case 0xEA:
			Exec_SET_b_r_QIYd(5, RegD(), btD);
			break;
		case 0xEB:
			Exec_SET_b_r_QIYd(5, RegE(), btD);
			break;
		case 0xEC:
			Exec_SET_b_r_QIYd(5, RegH(), btD);
			break;
		case 0xED:
			Exec_SET_b_r_QIYd(5, RegL(), btD);
			break;
		case 0xEE:
			Exec_SET_b_QIYd(5, btD);
			break;
		case 0xEF:
			Exec_SET_b_r_QIYd(5, RegA(), btD);
			break;
		case 0xF0:
			Exec_SET_b_r_QIYd(6, RegB(), btD);
			break;
		case 0xF1:
			Exec_SET_b_r_QIYd(6, RegC(), btD);
			break;
		case 0xF2:
			Exec_SET_b_r_QIYd(6, RegD(), btD);
			break;
		case 0xF3:
			Exec_SET_b_r_QIYd(6, RegE(), btD);
			break;
		case 0xF4:
			Exec_SET_b_r_QIYd(6, RegH(), btD);
			break;
		case 0xF5:
			Exec_SET_b_r_QIYd(6, RegL(), btD);
			break;
		case 0xF6:
			Exec_SET_b_QIYd(6, btD);
			break;
		case 0xF7:
			Exec_SET_b_r_QIYd(6, RegA(), btD);
			break;
		case 0xF8:
			Exec_SET_b_r_QIYd(7, RegB(), btD);
			break;
		case 0xF9:
			Exec_SET_b_r_QIYd(7, RegC(), btD);
			break;
		case 0xFA:
			Exec_SET_b_r_QIYd(7, RegD(), btD);
			break;
		case 0xFB:
			Exec_SET_b_r_QIYd(7, RegE(), btD);
			break;
		case 0xFC:
			Exec_SET_b_r_QIYd(7, RegH(), btD);
			break;
		case 0xFD:
			Exec_SET_b_r_QIYd(7, RegL(), btD);
			break;
		case 0xFE:
			Exec_SET_b_QIYd(7, btD);
			break;
		case 0xFF:
			Exec_SET_b_r_QIYd(7, RegA(), btD);
			break;
		}
	}

// substitute function
protected:
	inline TREGPREF RegAF();
	inline TREGREF RegA();
	inline TREGREF RegF();
	inline TREGPREF RegBC();
	inline TREGREF RegB();
	inline TREGREF RegC();
	inline TREGPREF RegDE();
	inline TREGREF RegD();
	inline TREGREF RegE();
	inline TREGPREF RegHL();
	inline TREGREF RegH();
	inline TREGREF RegL();
	inline TREGPREF RegIX();
	inline TREGREF RegIXH();
	inline TREGREF RegIXL();
	inline TREGPREF RegIY();
	inline TREGREF RegIYH();
	inline TREGREF RegIYL();
	inline TREGPREF RegSP();
	inline TBOOL FlagNZ();
	inline TBOOL FlagZ();
	inline TBOOL FlagNC();
	inline TBOOL FlagC();
	inline TBOOL FlagPO();
	inline TBOOL FlagPE();
	inline TBOOL FlagP();
	inline TBOOL FlagM();
	inline void IncRegR();
	inline void FetchByte(uint8_t& btData);
	inline void FetchWord(uint16_t& wData);
	inline void FetchByteM1(uint8_t& btData);
	inline int GetExecClock();
	inline void SetExecClock(int nExecClock);
	inline void AddExecClock(int nExecClock);

// differentiation OP code process
protected:
	// 8bit load
	inline void Exec_LD_r_r2(TREGREF reg, TCREGREF reg2);
	inline void Exec_LD_r_n(TREGREF reg, uint8_t btN);
	inline void Exec_LD_A_Qss(TCREGPREF regp);
	inline void Exec_LD_Qss_A(TCREGPREF regp);
	inline void Exec_LD_A_Qnn(uint16_t wNN);
	inline void Exec_LD_Qnn_A(uint16_t wNN);
	inline void Exec_LD_r_QHL(TREGREF reg);
	inline void Exec_LD_QHL_r(TCREGREF reg);
	inline void Exec_LD_QHL_n(uint8_t btN);
	inline void Exec_LD_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_LD_QIXd_r(uint8_t btD, TCREGREF reg);
	inline void Exec_LD_QIXd_n(uint8_t btD, uint8_t btN);
	inline void Exec_LD_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_LD_QIYd_r(uint8_t btD, TCREGREF reg);
	inline void Exec_LD_QIYd_n(uint8_t btD, uint8_t btN);
	inline void Exec_LD_A_I();
	inline void Exec_LD_I_A();
	inline void Exec_LD_A_R();
	inline void Exec_LD_R_A();
	// 16bit load
	inline void Exec_LD_ss_nn(TREGPREF regp, uint16_t wNN);
	inline void Exec_LD_ss_Qnn(TREGPREF regp, uint16_t wNN);
	inline void Exec_LD_Qnn_ss(uint16_t wNN, TCREGPREF regp);
	inline void Exec_LD_HL_Qnn(uint16_t wNN);
	inline void Exec_LD_Qnn_HL(uint16_t wNN);
	inline void Exec_LD_IX_nn(uint16_t wNN);
	inline void Exec_LD_IX_Qnn(uint16_t wNN);
	inline void Exec_LD_Qnn_IX(uint16_t wNN);
	inline void Exec_LD_IY_nn(uint16_t wNN);
	inline void Exec_LD_IY_Qnn(uint16_t wNN);
	inline void Exec_LD_Qnn_IY(uint16_t wNN);
	inline void Exec_LD_SP_HL();
	inline void Exec_LD_SP_IX();
	inline void Exec_LD_SP_IY();
	inline void Exec_PUSH_ss(TREGPREF regp);
	inline void Exec_PUSH_IX();
	inline void Exec_PUSH_IY();
	inline void Exec_POP_ss(TREGPREF regp);
	inline void Exec_POP_IX();
	inline void Exec_POP_IY();
	// exchange
	inline void Exec_EX_AF_AF2();
	inline void Exec_EX_DE_HL();
	inline void Exec_EXX();
	inline void Exec_EX_QSP_HL();
	inline void Exec_EX_QSP_IX();
	inline void Exec_EX_QSP_IY();
	// 8bit calculate
	inline void Exec_INC_r(TREGREF reg);
	inline void Exec_INC_QHL();
	inline void Exec_INC_QIXd(uint8_t btD);
	inline void Exec_INC_QIYd(uint8_t btD);
	inline void Exec_DEC_r(TREGREF reg);
	inline void Exec_DEC_QHL();
	inline void Exec_DEC_QIXd(uint8_t btD);
	inline void Exec_DEC_QIYd(uint8_t btD);
	inline void Exec_ADD_A_r(TCREGREF reg);
	inline void Exec_ADD_A_n(uint8_t btN);
	inline void Exec_ADD_A_QHL();
	inline void Exec_ADD_A_QIXd(uint8_t btD);
	inline void Exec_ADD_A_QIYd(uint8_t btD);
	inline void Exec_ADC_A_r(TCREGREF reg);
	inline void Exec_ADC_A_n(uint8_t btN);
	inline void Exec_ADC_A_QHL();
	inline void Exec_ADC_A_QIXd(uint8_t btD);
	inline void Exec_ADC_A_QIYd(uint8_t btD);
	inline void Exec_SUB_r(TCREGREF reg);
	inline void Exec_SUB_n(uint8_t btN);
	inline void Exec_SUB_QHL();
	inline void Exec_SUB_QIXd(uint8_t btD);
	inline void Exec_SUB_QIYd(uint8_t btD);
	inline void Exec_SBC_A_r(TCREGREF reg);
	inline void Exec_SBC_A_n(uint8_t btN);
	inline void Exec_SBC_A_QHL();
	inline void Exec_SBC_A_QIXd(uint8_t btD);
	inline void Exec_SBC_A_QIYd(uint8_t btD);
	inline void Exec_AND_r(TCREGREF reg);
	inline void Exec_AND_n(uint8_t btN);
	inline void Exec_AND_QHL();
	inline void Exec_AND_QIXd(uint8_t btD);
	inline void Exec_AND_QIYd(uint8_t btD);
	inline void Exec_OR_r(TCREGREF reg);
	inline void Exec_OR_n(uint8_t btN);
	inline void Exec_OR_QHL();
	inline void Exec_OR_QIXd(uint8_t btD);
	inline void Exec_OR_QIYd(uint8_t btD);
	inline void Exec_XOR_r(TCREGREF reg);
	inline void Exec_XOR_n(uint8_t btN);
	inline void Exec_XOR_QHL();
	inline void Exec_XOR_QIXd(uint8_t btD);
	inline void Exec_XOR_QIYd(uint8_t btD);
	inline void Exec_CP_r(TCREGREF reg);
	inline void Exec_CP_n(uint8_t btN);
	inline void Exec_CP_QHL();
	inline void Exec_CP_QIXd(uint8_t btD);
	inline void Exec_CP_QIYd(uint8_t btD);
	// rotate/shift
	inline void Exec_RLCA();
	inline void Exec_RLC_r(TREGREF reg);
	inline void Exec_RLC_QHL();
	inline void Exec_RLC_QIXd(uint8_t btD);
	inline void Exec_RLC_QIYd(uint8_t btD);
	inline void Exec_RLC_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_RLC_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_RLA();
	inline void Exec_RL_r(TREGREF reg);
	inline void Exec_RL_QHL();
	inline void Exec_RL_QIXd(uint8_t btD);
	inline void Exec_RL_QIYd(uint8_t btD);
	inline void Exec_RL_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_RL_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_RRCA();
	inline void Exec_RRC_r(TREGREF reg);
	inline void Exec_RRC_QHL();
	inline void Exec_RRC_QIXd(uint8_t btD);
	inline void Exec_RRC_QIYd(uint8_t btD);
	inline void Exec_RRC_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_RRC_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_RRA();
	inline void Exec_RR_r(TREGREF reg);
	inline void Exec_RR_QHL();
	inline void Exec_RR_QIXd(uint8_t btD);
	inline void Exec_RR_QIYd(uint8_t btD);
	inline void Exec_RR_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_RR_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_SLA_r(TREGREF reg);
	inline void Exec_SLA_QHL();
	inline void Exec_SLA_QIXd(uint8_t btD);
	inline void Exec_SLA_QIYd(uint8_t btD);
	inline void Exec_SLA_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_SLA_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_SRA_r(TREGREF reg);
	inline void Exec_SRA_QHL();
	inline void Exec_SRA_QIXd(uint8_t btD);
	inline void Exec_SRA_QIYd(uint8_t btD);
	inline void Exec_SRA_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_SRA_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_SLL_r(TREGREF reg);
	inline void Exec_SLL_QHL();
	inline void Exec_SLL_QIXd(uint8_t btD);
	inline void Exec_SLL_QIYd(uint8_t btD);
	inline void Exec_SLL_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_SLL_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_SRL_r(TREGREF reg);
	inline void Exec_SRL_QHL();
	inline void Exec_SRL_QIXd(uint8_t btD);
	inline void Exec_SRL_QIYd(uint8_t btD);
	inline void Exec_SRL_r_QIXd(TREGREF reg, uint8_t btD);
	inline void Exec_SRL_r_QIYd(TREGREF reg, uint8_t btD);
	inline void Exec_RLD();
	inline void Exec_RRD();
	// bit operate/test
	inline void Exec_BIT_b_r(uint8_t btB, TCREGREF reg);
	inline void Exec_BIT_b_QHL(uint8_t btB);
	inline void Exec_BIT_b_QIXd(uint8_t btB, uint8_t btD);
	inline void Exec_BIT_b_QIYd(uint8_t btB, uint8_t btD);
	inline void Exec_SET_b_r(uint8_t btB, TREGREF reg);
	inline void Exec_SET_b_QHL(uint8_t btB);
	inline void Exec_SET_b_QIXd(uint8_t btB, uint8_t btD);
	inline void Exec_SET_b_QIYd(uint8_t btB, uint8_t btD);
	inline void Exec_SET_b_r_QIXd(uint8_t btB, TREGREF reg, uint8_t btD);
	inline void Exec_SET_b_r_QIYd(uint8_t btB, TREGREF reg, uint8_t btD);
	inline void Exec_RES_b_r(uint8_t btB, TREGREF reg);
	inline void Exec_RES_b_QHL(uint8_t btB);
	inline void Exec_RES_b_QIXd(uint8_t btB, uint8_t btD);
	inline void Exec_RES_b_QIYd(uint8_t btB, uint8_t btD);
	inline void Exec_RES_b_r_QIXd(uint8_t btB, TREGREF reg, uint8_t btD);
	inline void Exec_RES_b_r_QIYd(uint8_t btB, TREGREF reg, uint8_t btD);
	// 16bit calculate
	inline void Exec_INC_ss(TREGPREF regp);
	inline void Exec_INC_IX();
	inline void Exec_INC_IY();
	inline void Exec_DEC_ss(TREGPREF regp);
	inline void Exec_DEC_IX();
	inline void Exec_DEC_IY();
	inline void Exec_ADD_HL_ss(TCREGPREF regp);
	inline void Exec_ADD_IX_ss(TCREGPREF regp);
	inline void Exec_ADD_IY_ss(TCREGPREF regp);
	inline void Exec_ADC_HL_ss(TCREGPREF regp);
	inline void Exec_SBC_HL_ss(TCREGPREF regp);
	// other calculate/CPU control
	inline void Exec_DAA();
	inline void Exec_CPL();
	inline void Exec_NEG();
	inline void Exec_CCF();
	inline void Exec_SCF();
	inline void Exec_DI();
	inline void Exec_EI();
	inline void Exec_NOP();
	inline void Exec_HALT();
	inline void Exec_IM0();
	inline void Exec_IM1();
	inline void Exec_IM2();
	inline void Exec_IMx();
	// branch
	inline void Exec_JP_nn(uint16_t wNN);
	inline void Exec_JP_QHL();
	inline void Exec_JP_QIX();
	inline void Exec_JP_QIY();
	inline void Exec_JP_cc_nn(TBOOL flgCC, uint16_t wNN);
	inline void Exec_JR_e(uint8_t btE);
	inline void Exec_JR_cc_e(TBOOL flgCC, uint8_t btE);
	inline void Exec_DJNZ_e(uint8_t btE);
	inline void Exec_CALL_nn(uint16_t wNN);
	inline void Exec_CALL_cc_nn(TBOOL flgCC, uint16_t wNN);
	inline void Exec_RET();
	inline void Exec_RET_cc(TBOOL flgCC);
	inline void Exec_RST_n(uint8_t btN);
	inline void Exec_RETI();
	inline void Exec_RETN();
	// input/output
	inline void Exec_IN_A_Qn(uint8_t btN);
	inline void Exec_IN_r_QC(TREGREF reg);
	inline void Exec_IN_F_QC();
	inline void Exec_OUT_Qn_A(uint8_t btN);
	inline void Exec_OUT_QC_r(TCREGREF reg);
	inline void Exec_OUT_QC_0();
	// block
	inline void Exec_LDI();
	inline void Exec_LDD();
	inline void Exec_CPI();
	inline void Exec_CPD();
	inline void Exec_INI();
	inline void Exec_IND();
	inline void Exec_OUTI();
	inline void Exec_OUTD();
	inline void Exec_LDIR();
	inline void Exec_LDDR();
	inline void Exec_CPIR();
	inline void Exec_CPDR();
	inline void Exec_INIR();
	inline void Exec_INDR();
	inline void Exec_OTIR();
	inline void Exec_OTDR();

// calculate
protected:
	// 8bit load
	inline void Calc_INC_8(uint8_t& btData);
	inline void Calc_DEC_8(uint8_t& btData);
	inline void Calc_ADD_8(uint8_t& btDst, uint8_t btSrc);
	inline void Calc_ADC_8(uint8_t& btDst, uint8_t btSrc);
	inline void Calc_SUB_8(uint8_t& btDst, uint8_t btSrc);
	inline void Calc_SBC_8(uint8_t& btDst, uint8_t btSrc);
	inline void Calc_AND_8(uint8_t& btDst, uint8_t btSrc);
	inline void Calc_OR_8(uint8_t& btDst, uint8_t btSrc);
	inline void Calc_XOR_8(uint8_t& btDst, uint8_t btSrc);
	inline void Calc_CP_8(uint8_t btDst, uint8_t btSrc);
	// rotate/shift
	inline void Calc_RLCA(uint8_t& btData);
	inline void Calc_RLA(uint8_t& btData);
	inline void Calc_RRCA(uint8_t& btData);
	inline void Calc_RRA(uint8_t& btData);
	inline void Calc_RLC(uint8_t& btData);
	inline void Calc_RL(uint8_t& btData);
	inline void Calc_RRC(uint8_t& btData);
	inline void Calc_RR(uint8_t& btData);
	inline void Calc_SLA(uint8_t& btData);
	inline void Calc_SRA(uint8_t& btData);
	inline void Calc_SLL(uint8_t& btData);
	inline void Calc_SRL(uint8_t& btData);
	inline void Calc_RLD(uint8_t& btData1, uint8_t& btData2);
	inline void Calc_RRD(uint8_t& btData1, uint8_t& btData2);
	// bit operate/test
	inline void Calc_BIT_b(uint8_t btB, uint8_t btData);
	inline void Calc_SET_b(uint8_t btB, uint8_t& btData);
	inline void Calc_RES_b(uint8_t btB, uint8_t& btData);
	// 16bit calculate
	inline void Calc_INC_16(uint16_t& wData);
	inline void Calc_DEC_16(uint16_t& wData);
	inline void Calc_ADD_16(uint16_t& wDst, uint16_t wSrc);
	inline void Calc_ADC_16(uint16_t& wDst, uint16_t wSrc);
	inline void Calc_SBC_16(uint16_t& wDst, uint16_t wSrc);
	// other calculate
	inline void Calc_DAA(uint8_t& btData);
	inline void Calc_CPL(uint8_t& btData);
	inline void Calc_NEG(uint8_t& btData);
	inline void Calc_CCF();
	inline void Calc_SCF();
	// others
	inline void Calc_LD_A_IR(uint8_t& btDst, uint8_t btSrc);
	inline void Calc_IN_r_QC(uint8_t btData);
	inline void Calc_LDI_LDD(uint16_t wCounter);
	inline void Calc_CPI_CPD(uint16_t wCounter, uint8_t btDst, uint8_t btSrc);
	inline void Calc_INI_IND_OUTI_OUTD(uint8_t btCounter);

// interrupt
public:
	// interrupt flag process
	void CopyEnableInterrupt();
	// occurred interrupt
	int DoInterrupt(uint8_t btIntVect);
	// occurred NMI
	int DoNMInterrupt();
};

#endif // Z80ExecutorBase_DEFINED
