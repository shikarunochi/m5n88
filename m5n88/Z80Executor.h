////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80Executor_DEFINED
#define Z80Executor_DEFINED

////////////////////////////////////////////////////////////
// CZ80Executor

#define CZ80Executor \
	TZ80ExecutorBase< \
		CZ80, \
		bool, \
		CRegister&, const CRegister&, URegisterPair&, const URegisterPair&>

////////////////////////////////////////////////////////////
// substitute function

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGPREF CZ80Executor::RegAF() {
	return Z80().RegAF();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegA() {
	return Z80().RegA();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegF() {
	return Z80().RegF();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGPREF CZ80Executor::RegBC() {
	return Z80().RegBC();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegB() {
	return Z80().RegB();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegC() {
	return Z80().RegC();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGPREF CZ80Executor::RegDE() {
	return Z80().RegDE();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegD() {
	return Z80().RegD();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegE() {
	return Z80().RegE();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGPREF CZ80Executor::RegHL() {
	return Z80().RegHL();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegH() {
	return Z80().RegH();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegL() {
	return Z80().RegL();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGPREF CZ80Executor::RegIX() {
	return Z80().RegIX();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegIXH() {
	return Z80().RegIXH();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegIXL() {
	return Z80().RegIXL();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGPREF CZ80Executor::RegIY() {
	return Z80().RegIY();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegIYH() {
	return Z80().RegIYH();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGREF CZ80Executor::RegIYL() {
	return Z80().RegIYL();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TREGPREF CZ80Executor::RegSP() {
	return Z80().RegSP();
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TBOOL CZ80Executor::FlagNZ() {
	return !Z80().TestRegF(CZ80::Z_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TBOOL CZ80Executor::FlagZ() {
	return Z80().TestRegF(CZ80::Z_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TBOOL CZ80Executor::FlagNC() {
	return !Z80().TestRegF(CZ80::C_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TBOOL CZ80Executor::FlagC() {
	return Z80().TestRegF(CZ80::C_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TBOOL CZ80Executor::FlagPO() {
	return !Z80().TestRegF(CZ80::P_V_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TBOOL CZ80Executor::FlagPE() {
	return Z80().TestRegF(CZ80::P_V_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TBOOL CZ80Executor::FlagP() {
	return !Z80().TestRegF(CZ80::S_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80Executor::TBOOL CZ80Executor::FlagM() {
	return Z80().TestRegF(CZ80::S_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::IncRegR() {
	Z80().IncRegR();
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::FetchByte(uint8_t& btData) {
	Z80().FetchByte(btData);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::FetchWord(uint16_t& wData) {
	Z80().FetchWord(wData);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::FetchByteM1(uint8_t& btData) {
	Z80().FetchByteM1(btData);
}

Z80TEMPLATE_EXPLICIT_AW
inline int CZ80Executor::GetExecClock() {
	return Z80().GetExecClock();
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::SetExecClock(int nExecClock) {
	Z80().SetExecClock(nExecClock);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::AddExecClock(int nExecClock) {
	Z80().AddExecClock(nExecClock);
}

////////////////////////////////////////////////////////////
// calculate

// 8bit load

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_INC_8(uint8_t& btData) {
	btData++;
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_INC_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_INC_8(uint8_t& btData) {
	btData++;
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btData == 0)? Z_FLAG: 0) |
			((btData == 128)? P_V_FLAG: 0) |
			(btData & 0x80) |
			(((btData & 0x0F) == 0)? H_FLAG: 0));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_DEC_8(uint8_t& btData) {
	btData--;
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_DEC_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_DEC_8(uint8_t& btData) {
	btData--;
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btData == 0)? Z_FLAG: 0) |
			((btData == 127)? P_V_FLAG: 0) |
			(btData & 0x80) |
			N_FLAG |
			(((btData & 0x0F) == 15)? H_FLAG: 0));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_ADD_8(uint8_t& btDst, uint8_t btSrc) {
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_ADD_8(0, btDst, btSrc));
	btDst = uint8_t(btDst+btSrc);
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_ADD_8(uint8_t& btDst, uint8_t btSrc) {
	int nResult = int(btDst)+int(btSrc);
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((nResult > 255)? C_FLAG: 0) |
			((uint8_t(nResult) == 0)? Z_FLAG: 0) |
			(((((nResult & ~btDst & ~btSrc) |
				(~nResult & btDst & btSrc)) & 0x80) != 0)? P_V_FLAG: 0) |
			(nResult & 0x80) |
			(((btDst & 0x0F)+(btSrc & 0x0F) > 15)? H_FLAG: 0));
	btDst = uint8_t(nResult);
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_ADC_8(uint8_t& btDst, uint8_t btSrc) {
	int nCarry = Z80().MaskRegF(C_FLAG);
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_ADD_8(nCarry, btDst, btSrc));
	btDst = uint8_t(btDst+btSrc+nCarry);
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_ADC_8(uint8_t& btDst, uint8_t btSrc) {
	int nCarry = Z80().MaskRegF(C_FLAG);
	int nSrc = int(btSrc)+nCarry;
	int nResult = int(btDst)+nSrc;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((nResult > 255)? C_FLAG: 0) |
			((uint8_t(nResult) == 0)? Z_FLAG: 0) |
			(((((nResult & ~btDst & ~nSrc) |
				(~nResult & btDst & nSrc)) & 0x80) != 0)? P_V_FLAG: 0) |
			(nResult & 0x80) |
			(((btDst & 0x0F)+(btSrc & 0x0F)+nCarry > 15)? H_FLAG: 0));
	btDst = uint8_t(nResult);
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SUB_8(uint8_t& btDst, uint8_t btSrc) {
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_SUB_8(0, btDst, btSrc));
	btDst = uint8_t(btDst-btSrc);
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SUB_8(uint8_t& btDst, uint8_t btSrc) {
	int nResult = int(btDst)-int(btSrc);
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((nResult < 0)? C_FLAG: 0) |
			((uint8_t(nResult) == 0)? Z_FLAG: 0) |
			(((((nResult & ~btDst & btSrc) |
				(~nResult & btDst & ~btSrc)) & 0x80) != 0)? P_V_FLAG: 0) |
			(nResult & 0x80) |
			N_FLAG |
			(((btDst & 0x0F) < (btSrc & 0x0F))? H_FLAG: 0));
	btDst = uint8_t(nResult);
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SBC_8(uint8_t& btDst, uint8_t btSrc) {
	int nCarry = Z80().MaskRegF(C_FLAG);
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_SUB_8(nCarry, btDst, btSrc));
	btDst = uint8_t(btDst-btSrc-nCarry);
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SBC_8(uint8_t& btDst, uint8_t btSrc) {
	int nCarry = Z80().MaskRegF(C_FLAG);
	int nSrc = int(btSrc)+nCarry;
	int nResult = int(btDst)-nSrc;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((nResult < 0)? C_FLAG: 0) |
			((uint8_t(nResult) == 0)? Z_FLAG: 0) |
			(((((nResult & ~btDst & nSrc) |
				(~nResult & btDst & ~nSrc)) & 0x80) != 0)? P_V_FLAG: 0) |
			(nResult & 0x80) |
			N_FLAG |
			(((btDst & 0x0F) < (btSrc & 0x0F)+nCarry)? H_FLAG: 0));
	btDst = uint8_t(nResult);
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_AND_8(uint8_t& btDst, uint8_t btSrc) {
	btDst &= btSrc;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_LOGICAL_8(btDst) |
			H_FLAG);
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_AND_8(uint8_t& btDst, uint8_t btSrc) {
	btDst &= btSrc;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btDst == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btDst) |
			(btDst & 0x80) |
			H_FLAG);
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_OR_8(uint8_t& btDst, uint8_t btSrc) {
	btDst |= btSrc;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_LOGICAL_8(btDst));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_OR_8(uint8_t& btDst, uint8_t btSrc) {
	btDst |= btSrc;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btDst == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btDst) |
			(btDst & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_XOR_8(uint8_t& btDst, uint8_t btSrc) {
	btDst ^= btSrc;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_LOGICAL_8(btDst));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_XOR_8(uint8_t& btDst, uint8_t btSrc) {
	btDst ^= btSrc;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btDst == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btDst) |
			(btDst & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_CP_8(uint8_t btDst, uint8_t btSrc) {
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_SUB_8(0, btDst, btSrc));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_CP_8(uint8_t btDst, uint8_t btSrc) {
	uint8_t btDst2 = btDst;
	Calc_SUB_8(btDst2, btSrc);
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

// rotate/shift

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RLCA(uint8_t& btData) {
	btData = uint8_t((btData << 1) | (btData >> 7));
	Z80().UpdateRegF(
		C_FLAG | N_FLAG | H_FLAG,
		btData & 0x01);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RLA(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData << 1) | Z80().MaskRegF(C_FLAG));
	Z80().UpdateRegF(
		C_FLAG | N_FLAG | H_FLAG,
		btOrg >> 7);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RRCA(uint8_t& btData) {
	btData = uint8_t((btData >> 1) | (btData << 7));
	Z80().UpdateRegF(
		C_FLAG | N_FLAG | H_FLAG,
		btData >> 7);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RRA(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData >> 1) | (Z80().MaskRegF(C_FLAG) << 7));
	Z80().UpdateRegF(
		C_FLAG | N_FLAG | H_FLAG,
		btOrg & 0x01);
}

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RLC(uint8_t& btData) {
	btData = uint8_t((btData << 1) | (btData >> 7));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btData & 0x01) |
			CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RLC(uint8_t& btData) {
	btData = uint8_t((btData << 1) | (btData >> 7));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btData & 0x01) |
			((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RL(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData << 1) | Z80().MaskRegF(C_FLAG));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg >> 7) |
			CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RL(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData << 1) | Z80().MaskRegF(C_FLAG));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg >> 7) |
			((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RRC(uint8_t& btData) {
	btData = uint8_t((btData >> 1) | (btData << 7));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btData >> 7) |
			CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RRC(uint8_t& btData) {
	btData = uint8_t((btData >> 1) | (btData << 7));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btData >> 7) |
			((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RR(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData >> 1) | (Z80().MaskRegF(C_FLAG) << 7));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg & 0x01) |
			CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RR(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData >> 1) | (Z80().MaskRegF(C_FLAG) << 7));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg & 0x01) |
		((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SLA(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData <<= 1;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg >> 7) |
			CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SLA(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData <<= 1;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg >> 7) |
			((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SRA(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData >> 1) | (btData & 0x80));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg & 0x01) |
			CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SRA(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData >> 1) | (btData & 0x80));
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg & 0x01) |
			((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SLL(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData << 1) | 0x01);
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg >> 7) |
			CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SLL(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData = uint8_t((btData << 1) | 0x01);
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg >> 7) |
			((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SRL(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData >>= 1;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg & 0x01) |
			CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SRL(uint8_t& btData) {
	uint8_t btOrg = btData;
	btData >>= 1;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		(btOrg & 0x01) |
		((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RLD(uint8_t& btData1, uint8_t& btData2) {
	uint8_t btOrg1 = btData1;
	btData1 = uint8_t((btData1 & 0xF0) | (btData2 >> 4));
	btData2 = uint8_t((btOrg1 & 0x0F) | (btData2 << 4));
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_LOGICAL_8(btData1));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RLD(uint8_t& btData1, uint8_t& btData2) {
	uint8_t btOrg1 = btData1;
	btData1 = uint8_t((btData1 & 0xF0) | (btData2 >> 4));
	btData2 = uint8_t((btOrg1 & 0x0F) | (btData2 << 4));
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btData1 == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData1) |
			(btData1 & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RRD(uint8_t& btData1, uint8_t& btData2) {
	uint8_t btOrg1 = btData1;
	btData1 = uint8_t((btData1 & 0xF0) | (btData2 & 0x0F));
	btData2 = uint8_t((btOrg1 << 4) | (btData2 >> 4));
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_LOGICAL_8(btData1));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RRD(uint8_t& btData1, uint8_t& btData2) {
	uint8_t btOrg1 = btData1;
	btData1 = uint8_t((btData1 & 0xF0) | (btData2 & 0x0F));
	btData2 = uint8_t((btOrg1 << 4) | (btData2 >> 4));
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btData1 == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData1) |
			(btData1 & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

// bit operate/test

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_BIT_b(uint8_t btB, uint8_t btData) {
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		CZ80::GetFlags_BIT_b(btB, btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
// undefinition specification:P_V_FLAG
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_BIT_b(uint8_t btB, uint8_t btData) {
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		H_FLAG |
			(((btData & (1 << btB)) == 0)? (Z_FLAG | P_V_FLAG): 0) |
			(((btB == 7) && ((btData & 0x80) != 0))? S_FLAG: 0));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SET_b(uint8_t btB, uint8_t& btData) {
	btData |= uint8_t(1 << btB);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_RES_b(uint8_t btB, uint8_t& btData) {
	btData &= uint8_t(~(1 << btB));
}

// 16bit calculate

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_INC_16(uint16_t& wData) {
	wData++;
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_DEC_16(uint16_t& wData) {
	wData--;
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_ADD_16(uint16_t& wDst, uint16_t wSrc) {
	int32_t nResult = int32_t(wDst)+int32_t(wSrc);
	Z80().UpdateRegF(
		C_FLAG | N_FLAG | H_FLAG,
		((nResult > 65535)? C_FLAG: 0) |
			(((wDst & 0x0FFF)+(wSrc & 0x0FFF) > 4095)? H_FLAG: 0));
	wDst = uint16_t(nResult);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_ADC_16(uint16_t& wDst, uint16_t wSrc) {
	int nCarry = Z80().MaskRegF(C_FLAG);
	int32_t nResult = int32_t(wDst)+int32_t(wSrc)+nCarry,
		nResult2 = int32_t(int16_t(wDst))+int32_t(int16_t(wSrc))+nCarry;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((nResult > 65535)? C_FLAG: 0) |
			((uint16_t(nResult) == 0)? Z_FLAG: 0) |
			(((nResult2 > 32767) || (nResult2 < -32768))? P_V_FLAG: 0) |
			((nResult & 0x8000) >> 8) |
			(((wDst & 0x0FFF)+(wSrc & 0x0FFF)+nCarry > 4095)? H_FLAG: 0));
	wDst = uint16_t(nResult);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SBC_16(uint16_t& wDst, uint16_t wSrc) {
	int nCarry = Z80().MaskRegF(C_FLAG);
	int32_t nResult = int32_t(wDst)-int32_t(wSrc)-nCarry,
		nResult2 = int32_t(int16_t(wDst))-int32_t(int16_t(wSrc))-nCarry;
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((nResult < 0)? C_FLAG: 0) |
			((uint16_t(nResult) == 0)? Z_FLAG: 0) |
			(((nResult2 > 32767) || (nResult2 < -32768))? P_V_FLAG: 0) |
			((nResult & 0x8000) >> 8) |
			N_FLAG |
			(((wDst & 0x0FFF) < (wSrc & 0x0FFF)+nCarry)? H_FLAG: 0));
	wDst = uint16_t(nResult);
}

// other calculate

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_DAA(uint8_t& btData) {
	int nFlags = Z80().MaskRegF(C_FLAG | N_FLAG) |
		(Z80().MaskRegF(H_FLAG) >> 2);
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | H_FLAG,
		CZ80::GetFlags_DAA(nFlags, btData));
	btData = CZ80::GetResult_DAA(nFlags, btData);
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_DAA(uint8_t& btData) {
	int nResult = btData, nCarry = 0, nHalf = 0;
	if (!Z80().TestRegF(N_FLAG)) {
		if (((nResult & 0x0F) > 0x09) || Z80().TestRegF(H_FLAG)) {
			if ((nResult & 0x0F) > 0x09) {
				nHalf = H_FLAG;
			}
			nResult += 0x06;
		}
		if ((nResult > 0x9F) || Z80().TestRegF(C_FLAG)) {
			nCarry = C_FLAG;
			nResult += 0x60;
		}
	} else {
		if ((nResult > 0x99) || Z80().TestRegF(C_FLAG)) {
			nCarry = C_FLAG;
		}
		if (((nResult & 0x0F) > 0x09) || Z80().TestRegF(H_FLAG)) {
			if ((nResult & 0x0F) < 0x06) {
				nHalf = H_FLAG;
			}
			nResult -= 0x06;
		}
		if ((nResult > 0x9F) || Z80().TestRegF(C_FLAG)) {
			nResult -= 0x60;
		}
	}
	btData = uint8_t(nResult);
	Z80().UpdateRegF(
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | H_FLAG,
		nCarry |
			((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80) |
			nHalf);
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_CPL(uint8_t& btData) {
	btData = uint8_t(~btData);
	Z80().SetRegF(N_FLAG | H_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_NEG(uint8_t& btData) {
	uint8_t btTmp = 0;
	Calc_SUB_8(btTmp, btData);
	btData = btTmp;
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_CCF() {
	Z80().UpdateRegF(
		C_FLAG | N_FLAG,
		Z80().MaskRegF(C_FLAG) ^ C_FLAG);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_SCF() {
	Z80().UpdateRegF(
		C_FLAG | N_FLAG | H_FLAG,
		C_FLAG);
}

// others

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_LD_A_IR(uint8_t& btDst, uint8_t btSrc) {
	btDst = btSrc;
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btDst == 0)? Z_FLAG: 0) |
			((Z80().IsEnableInterrupt() || Z80().IsEnableInterrupt2())?
				P_V_FLAG: 0) |
			(btDst & 0x80));
}

#ifdef Z80CFG_USE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_IN_r_QC(uint8_t btData) {
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG,
		CZ80::GetFlags_LOGICAL_8(btData));
}
#else // Z80CFG_NOUSE_FLAGTBL
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_IN_r_QC(uint8_t btData) {
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG,
		((btData == 0)? Z_FLAG: 0) |
			CZ80::GetParityTable(btData) |
			(btData & 0x80));
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_LDI_LDD(uint16_t wCounter) {
	Z80().UpdateRegF(
		P_V_FLAG | N_FLAG | H_FLAG,
		(wCounter != 0)? P_V_FLAG: 0);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_CPI_CPD(uint16_t wCounter, uint8_t btDst, uint8_t btSrc) {
	uint8_t btResult = uint8_t(btDst-btSrc);
	Z80().UpdateRegF(
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG,
		((btResult == 0)? Z_FLAG: 0) |
			((wCounter != 0)? P_V_FLAG: 0) |
			(btResult & 0x80) |
			N_FLAG |
			(((btDst & 0x0F) < (btSrc & 0x0F))? H_FLAG: 0));
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Calc_INI_IND_OUTI_OUTD(uint8_t btCounter) {
	Z80().UpdateRegF(
		Z_FLAG | N_FLAG,
		((btCounter == 0)? Z_FLAG: 0) |
			N_FLAG);
}

////////////////////////////////////////////////////////////
// differentiation OP code process

// 8bit load

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_r_r2(TREGREF reg, TCREGREF reg2) {
	reg.Copy(reg2);
	AddExecClock(CLOCK_LD_r_r2);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_r_n(TREGREF reg, uint8_t btN) {
	reg.Set(btN);
	AddExecClock(CLOCK_LD_r_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_A_Qss(TCREGPREF regp) {
	Z80().RegA().Set(Z80().ReadMemory(regp.Get()));
	AddExecClock(CLOCK_LD_A_Qss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_Qss_A(TCREGPREF regp) {
	Z80().WriteMemory(regp.Get(), Z80().RegA());
	AddExecClock(CLOCK_LD_Qss_A);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_A_Qnn(uint16_t wNN) {
	Z80().RegA().Set(Z80().ReadMemory(wNN));
	AddExecClock(CLOCK_LD_A_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_Qnn_A(uint16_t wNN) {
	Z80().WriteMemory(wNN, Z80().RegA());
	AddExecClock(CLOCK_LD_Qnn_A);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_r_QHL(TREGREF reg) {
	reg.Set(Z80().ReadMemory(Z80().RegHL()));
	AddExecClock(CLOCK_LD_r_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_QHL_r(TCREGREF reg) {
	Z80().WriteMemory(Z80().RegHL(), reg.Get());
	AddExecClock(CLOCK_LD_QHL_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_QHL_n(uint8_t btN) {
	Z80().WriteMemory(Z80().RegHL(), btN);
	AddExecClock(CLOCK_LD_QHL_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_r_QIXd(TREGREF reg, uint8_t btD) {
	reg.Set(Z80().ReadMemory(Z80().GetRegIXd(btD)));
	AddExecClock(CLOCK_LD_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_QIXd_r(uint8_t btD, TCREGREF reg) {
	Z80().WriteMemory(Z80().GetRegIXd(btD), reg.Get());
	AddExecClock(CLOCK_LD_QIXd_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_QIXd_n(uint8_t btD, uint8_t btN) {
	Z80().WriteMemory(Z80().GetRegIXd(btD), btN);
	AddExecClock(CLOCK_LD_QIXd_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_r_QIYd(TREGREF reg, uint8_t btD) {
	reg.Set(Z80().ReadMemory(Z80().GetRegIYd(btD)));
	AddExecClock(CLOCK_LD_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_QIYd_r(uint8_t btD, TCREGREF reg) {
	Z80().WriteMemory(Z80().GetRegIYd(btD), reg.Get());
	AddExecClock(CLOCK_LD_QIYd_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_QIYd_n(uint8_t btD, uint8_t btN) {
	Z80().WriteMemory(Z80().GetRegIYd(btD), btN);
	AddExecClock(CLOCK_LD_QIYd_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_A_I() {
	Calc_LD_A_IR(Z80().RegA(), Z80().GetRegI());
	AddExecClock(CLOCK_LD_A_I);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_I_A() {
	Z80().SetRegI(Z80().RegA().Get());
	AddExecClock(CLOCK_LD_I_A);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_A_R() {
	Calc_LD_A_IR(Z80().RegA(), Z80().GetRegR());
	AddExecClock(CLOCK_LD_A_R);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_R_A() {
	Z80().SetRegR(Z80().RegA().Get());
	AddExecClock(CLOCK_LD_R_A);
}

// 16bit load

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_ss_nn(TREGPREF regp, uint16_t wNN) {
	regp.Set(wNN);
	AddExecClock(CLOCK_LD_ss_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_ss_Qnn(TREGPREF regp, uint16_t wNN) {
	regp.Set(Z80().ReadMemoryW(wNN));
	AddExecClock(CLOCK_LD_ss_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_Qnn_ss(uint16_t wNN, TCREGPREF regp) {
	Z80().WriteMemoryW(wNN, regp.Get());
	AddExecClock(CLOCK_LD_Qnn_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_HL_Qnn(uint16_t wNN) {
	Z80().RegHL().Set(Z80().ReadMemoryW(wNN));
	AddExecClock(CLOCK_LD_HL_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_Qnn_HL(uint16_t wNN) {
	Z80().WriteMemoryW(wNN, Z80().RegHL());
	AddExecClock(CLOCK_LD_Qnn_HL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_IX_nn(uint16_t wNN) {
	Z80().RegIX().Set(wNN);
	AddExecClock(CLOCK_LD_IX_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_IX_Qnn(uint16_t wNN) {
	Z80().RegIX().Set(Z80().ReadMemoryW(wNN));
	AddExecClock(CLOCK_LD_IX_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_Qnn_IX(uint16_t wNN) {
	Z80().WriteMemoryW(wNN, Z80().RegIX());
	AddExecClock(CLOCK_LD_Qnn_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_IY_nn(uint16_t wNN) {
	Z80().RegIY().Set(wNN);
	AddExecClock(CLOCK_LD_IY_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_IY_Qnn(uint16_t wNN) {
	Z80().RegIY().Set(Z80().ReadMemoryW(wNN));
	AddExecClock(CLOCK_LD_IY_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_Qnn_IY(uint16_t wNN) {
	Z80().WriteMemoryW(wNN, Z80().RegIY());
	AddExecClock(CLOCK_LD_Qnn_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_SP_HL() {
	Z80().RegSP().Copy(Z80().RegHL());
	AddExecClock(CLOCK_LD_SP_HL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_SP_IX() {
	Z80().RegSP().Copy(Z80().RegIX());
	AddExecClock(CLOCK_LD_SP_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LD_SP_IY() {
	Z80().RegSP().Copy(Z80().RegIY());
	AddExecClock(CLOCK_LD_SP_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_PUSH_ss(TREGPREF regp) {
	Z80().PushReg(regp);
	AddExecClock(CLOCK_PUSH_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_PUSH_IX() {
	Z80().PushReg(Z80().RegIX());
	AddExecClock(CLOCK_PUSH_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_PUSH_IY() {
	Z80().PushReg(Z80().RegIY());
	AddExecClock(CLOCK_PUSH_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_POP_ss(TREGPREF regp) {
	Z80().PopReg(regp);
	AddExecClock(CLOCK_POP_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_POP_IX() {
	Z80().PopReg(Z80().RegIX());
	AddExecClock(CLOCK_POP_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_POP_IY() {
	Z80().PopReg(Z80().RegIY());
	AddExecClock(CLOCK_POP_IY);
}

// exchange

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_EX_AF_AF2() {
	Z80().RegAF().Swap(Z80().RegAF2());
	AddExecClock(CLOCK_EX_AF_AF2);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_EX_DE_HL() {
	Z80().RegDE().Swap(Z80().RegHL());
	AddExecClock(CLOCK_EX_DE_HL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_EXX() {
	Z80().RegBC().Swap(Z80().RegBC2());
	Z80().RegDE().Swap(Z80().RegDE2());
	Z80().RegHL().Swap(Z80().RegHL2());
	AddExecClock(CLOCK_EXX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_EX_QSP_HL() {
	uint16_t wTmp;
	wTmp = Z80().ReadMemoryW(Z80().RegSP());
	Z80().WriteMemoryW(Z80().RegSP(), Z80().RegHL());
	Z80().RegHL().Set(wTmp);
	AddExecClock(CLOCK_EX_QSP_HL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_EX_QSP_IX() {
	uint16_t wTmp;
	wTmp = Z80().ReadMemoryW(Z80().RegSP());
	Z80().WriteMemoryW(Z80().RegSP(), Z80().RegIX());
	Z80().RegIX().Set(wTmp);
	AddExecClock(CLOCK_EX_QSP_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_EX_QSP_IY() {
	uint16_t wTmp;
	wTmp = Z80().ReadMemoryW(Z80().RegSP());
	Z80().WriteMemoryW(Z80().RegSP(), Z80().RegIY());
	Z80().RegIY().Set(wTmp);
	AddExecClock(CLOCK_EX_QSP_IY);
}

// 8bit calculate

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INC_r(TREGREF reg) {
	Calc_INC_8(reg);
	AddExecClock(CLOCK_INC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INC_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_INC_8(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_INC_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INC_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_INC_8(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_INC_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INC_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_INC_8(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_INC_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DEC_r(TREGREF reg) {
	Calc_DEC_8(reg);
	AddExecClock(CLOCK_DEC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DEC_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_DEC_8(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_DEC_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DEC_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_DEC_8(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_DEC_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DEC_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_DEC_8(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_DEC_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADD_A_r(TCREGREF reg) {
	Calc_ADD_8(Z80().RegA(), reg.Get());
	AddExecClock(CLOCK_ADD_A_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADD_A_n(uint8_t btN) {
	Calc_ADD_8(Z80().RegA(), btN);
	AddExecClock(CLOCK_ADD_A_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADD_A_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_ADD_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_ADD_A_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADD_A_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_ADD_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_ADD_A_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADD_A_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_ADD_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_ADD_A_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADC_A_r(TCREGREF reg) {
	Calc_ADC_8(Z80().RegA(), reg.Get());
	AddExecClock(CLOCK_ADC_A_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADC_A_n(uint8_t btN) {
	Calc_ADC_8(Z80().RegA(), btN);
	AddExecClock(CLOCK_ADC_A_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADC_A_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_ADC_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_ADC_A_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADC_A_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_ADC_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_ADC_A_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADC_A_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_ADC_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_ADC_A_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SUB_r(TCREGREF reg) {
	Calc_SUB_8(Z80().RegA(), reg.Get());
	AddExecClock(CLOCK_SUB_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SUB_n(uint8_t btN) {
	Calc_SUB_8(Z80().RegA(), btN);
	AddExecClock(CLOCK_SUB_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SUB_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_SUB_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_SUB_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SUB_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SUB_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_SUB_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SUB_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SUB_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_SUB_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SBC_A_r(TCREGREF reg) {
	Calc_SBC_8(Z80().RegA(), reg.Get());
	AddExecClock(CLOCK_SBC_A_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SBC_A_n(uint8_t btN) {
	Calc_SBC_8(Z80().RegA(), btN);
	AddExecClock(CLOCK_SBC_A_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SBC_A_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_SBC_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_SBC_A_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SBC_A_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SBC_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_SBC_A_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SBC_A_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SBC_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_SBC_A_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_AND_r(TCREGREF reg) {
	Calc_AND_8(Z80().RegA(), reg.Get());
	AddExecClock(CLOCK_AND_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_AND_n(uint8_t btN) {
	Calc_AND_8(Z80().RegA(), btN);
	AddExecClock(CLOCK_AND_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_AND_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_AND_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_AND_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_AND_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_AND_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_AND_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_AND_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_AND_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_AND_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OR_r(TCREGREF reg) {
	Calc_OR_8(Z80().RegA(), reg.Get());
	AddExecClock(CLOCK_OR_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OR_n(uint8_t btN) {
	Calc_OR_8(Z80().RegA(), btN);
	AddExecClock(CLOCK_OR_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OR_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_OR_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_OR_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OR_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_OR_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_OR_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OR_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_OR_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_OR_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_XOR_r(TCREGREF reg) {
	Calc_XOR_8(Z80().RegA(), reg.Get());
	AddExecClock(CLOCK_XOR_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_XOR_n(uint8_t btN) {
	Calc_XOR_8(Z80().RegA(), btN);
	AddExecClock(CLOCK_XOR_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_XOR_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_XOR_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_XOR_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_XOR_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_XOR_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_XOR_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_XOR_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_XOR_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_XOR_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CP_r(TCREGREF reg) {
	Calc_CP_8(Z80().RegA(), reg.Get());
	AddExecClock(CLOCK_CP_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CP_n(uint8_t btN) {
	Calc_CP_8(Z80().RegA(), btN);
	AddExecClock(CLOCK_CP_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CP_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_CP_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_CP_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CP_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_CP_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_CP_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CP_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_CP_8(Z80().RegA(), btData);
	AddExecClock(CLOCK_CP_QIYd);
}

// rotate/shift

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLCA() {
	Calc_RLCA(Z80().RegA());
	AddExecClock(CLOCK_RLCA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLC_r(TREGREF reg) {
	Calc_RLC(reg);
	AddExecClock(CLOCK_RLC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLC_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_RLC(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_RLC_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLC_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RLC(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_RLC_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLC_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RLC(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_RLC_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLC_r_QIXd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RLC(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RLC_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLC_r_QIYd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RLC(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RLC_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLA() {
	Calc_RLA(Z80().RegA());
	AddExecClock(CLOCK_RLA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RL_r(TREGREF reg) {
	Calc_RL(reg);
	AddExecClock(CLOCK_RL_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RL_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_RL(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_RL_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RL_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RL(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_RL_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RL_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RL(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_RL_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RL_r_QIXd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RL(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RL_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RL_r_QIYd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RL(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RL_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRCA() {
	Calc_RRCA(Z80().RegA());
	AddExecClock(CLOCK_RRCA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRC_r(TREGREF reg) {
	Calc_RRC(reg);
	AddExecClock(CLOCK_RRC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRC_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_RRC(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_RRC_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRC_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RRC(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_RRC_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRC_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RRC(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_RRC_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRC_r_QIXd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RRC(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RRC_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRC_r_QIYd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RRC(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RRC_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRA() {
	Calc_RRA(Z80().RegA());
	AddExecClock(CLOCK_RRA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RR_r(TREGREF reg) {
	Calc_RR(reg);
	AddExecClock(CLOCK_RR_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RR_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_RR(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_RR_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RR_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RR(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_RR_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RR_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RR(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_RR_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RR_r_QIXd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RR(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RR_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RR_r_QIYd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RR(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RR_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLA_r(TREGREF reg) {
	Calc_SLA(reg);
	AddExecClock(CLOCK_SLA_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLA_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_SLA(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_SLA_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLA_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SLA(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_SLA_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLA_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SLA(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_SLA_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLA_r_QIXd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SLA(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SLA_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLA_r_QIYd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SLA(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SLA_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRA_r(TREGREF reg) {
	Calc_SRA(reg);
	AddExecClock(CLOCK_SRA_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRA_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_SRA(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_SRA_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRA_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SRA(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_SRA_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRA_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SRA(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_SRA_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRA_r_QIXd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SRA(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SRA_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRA_r_QIYd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SRA(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SRA_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLL_r(TREGREF reg) {
	Calc_SLL(reg);
	AddExecClock(CLOCK_SLL_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLL_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_SLL(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_SLL_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLL_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SLL(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_SLL_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLL_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SLL(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_SLL_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLL_r_QIXd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SLL(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SLL_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SLL_r_QIYd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SLL(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SLL_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRL_r(TREGREF reg) {
	Calc_SRL(reg);
	AddExecClock(CLOCK_SRL_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRL_QHL() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_SRL(btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_SRL_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRL_QIXd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SRL(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_SRL_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRL_QIYd(uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SRL(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_SRL_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRL_r_QIXd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SRL(btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SRL_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SRL_r_QIYd(TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SRL(btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SRL_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RLD() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_RLD(Z80().RegA(), btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_RLD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RRD() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_RRD(Z80().RegA(), btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_RRD);
}

// bit operate/test

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_BIT_b_r(uint8_t btB, TCREGREF reg) {
	Calc_BIT_b(btB, reg.Get());
	AddExecClock(CLOCK_BIT_b_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_BIT_b_QHL(uint8_t btB) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_BIT_b(btB, btData);
	AddExecClock(CLOCK_BIT_b_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_BIT_b_QIXd(uint8_t btB, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_BIT_b(btB, btData);
	AddExecClock(CLOCK_BIT_b_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_BIT_b_QIYd(uint8_t btB, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_BIT_b(btB, btData);
	AddExecClock(CLOCK_BIT_b_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SET_b_r(uint8_t btB, TREGREF reg) {
	Calc_SET_b(btB, reg);
	AddExecClock(CLOCK_SET_b_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SET_b_QHL(uint8_t btB) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_SET_b(btB, btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_SET_b_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SET_b_QIXd(uint8_t btB, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SET_b(btB, btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_SET_b_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SET_b_QIYd(uint8_t btB, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SET_b(btB, btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_SET_b_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SET_b_r_QIXd(uint8_t btB, TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_SET_b(btB, btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SET_b_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SET_b_r_QIYd(uint8_t btB, TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_SET_b(btB, btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_SET_b_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RES_b_r(uint8_t btB, TREGREF reg) {
	Calc_RES_b(btB, reg);
	AddExecClock(CLOCK_RES_b_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RES_b_QHL(uint8_t btB) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Calc_RES_b(btB, btData);
	Z80().WriteMemory(Z80().RegHL(), btData);
	AddExecClock(CLOCK_RES_b_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RES_b_QIXd(uint8_t btB, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RES_b(btB, btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	AddExecClock(CLOCK_RES_b_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RES_b_QIYd(uint8_t btB, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RES_b(btB, btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	AddExecClock(CLOCK_RES_b_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RES_b_r_QIXd(uint8_t btB, TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIXd(btD));
	Calc_RES_b(btB, btData);
	Z80().WriteMemory(Z80().GetRegIXd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RES_b_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RES_b_r_QIYd(uint8_t btB, TREGREF reg, uint8_t btD) {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().GetRegIYd(btD));
	Calc_RES_b(btB, btData);
	Z80().WriteMemory(Z80().GetRegIYd(btD), btData);
	reg.Set(btData);
	AddExecClock(CLOCK_RES_b_r_QIYd);
}

// 16bit calculate

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INC_ss(TREGPREF regp) {
	Calc_INC_16(regp);
	AddExecClock(CLOCK_INC_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INC_IX() {
	Calc_INC_16(Z80().RegIX());
	AddExecClock(CLOCK_INC_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INC_IY() {
	Calc_INC_16(Z80().RegIY());
	AddExecClock(CLOCK_INC_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DEC_ss(TREGPREF regp) {
	Calc_DEC_16(regp);
	AddExecClock(CLOCK_DEC_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DEC_IX() {
	Calc_DEC_16(Z80().RegIX());
	AddExecClock(CLOCK_DEC_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DEC_IY() {
	Calc_DEC_16(Z80().RegIY());
	AddExecClock(CLOCK_DEC_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADD_HL_ss(TCREGPREF regp) {
	Calc_ADD_16(Z80().RegHL(), regp.Get());
	AddExecClock(CLOCK_ADD_HL_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADD_IX_ss(TCREGPREF regp) {
	Calc_ADD_16(Z80().RegIX(), regp.Get());
	AddExecClock(CLOCK_ADD_IX_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADD_IY_ss(TCREGPREF regp) {
	Calc_ADD_16(Z80().RegIY(), regp.Get());
	AddExecClock(CLOCK_ADD_IY_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_ADC_HL_ss(TCREGPREF regp) {
	Calc_ADC_16(Z80().RegHL(), regp.Get());
	AddExecClock(CLOCK_ADC_HL_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SBC_HL_ss(TCREGPREF regp) {
	Calc_SBC_16(Z80().RegHL(), regp.Get());
	AddExecClock(CLOCK_SBC_HL_ss);
}

// other calculate/CPU control

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DAA() {
	Calc_DAA(Z80().RegA());
	AddExecClock(CLOCK_DAA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CPL() {
	Calc_CPL(Z80().RegA());
	AddExecClock(CLOCK_CPL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_NEG() {
	Calc_NEG(Z80().RegA());
	AddExecClock(CLOCK_NEG);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CCF() {
	Calc_CCF();
	AddExecClock(CLOCK_CCF);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_SCF() {
	Calc_SCF();
	AddExecClock(CLOCK_SCF);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DI() {
	Z80().SetEnableInterrupt(false);
	Z80().SetEnableInterrupt2(false);
	Z80().SetEnableInterruptReserve(false);
	AddExecClock(CLOCK_DI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_EI() {
	Z80().SetEnableInterrupt2(true);
	Z80().SetEnableInterruptReserve(true);
	AddExecClock(CLOCK_EI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_NOP() {
	AddExecClock(CLOCK_NOP);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_HALT() {
	Z80().SetHalting(true);
	Z80().AddRegPC(uint8_t(-1));
	Z80().ProcessHALT();
	AddExecClock(CLOCK_HALT);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IM0() {
	Z80().SetInterruptMode(0);
	AddExecClock(CLOCK_IM0);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IM1() {
	Z80().SetInterruptMode(1);
	AddExecClock(CLOCK_IM1);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IM2() {
	Z80().SetInterruptMode(2);
	AddExecClock(CLOCK_IM2);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IMx() {
	Z80().SetInterruptMode(-1);
	AddExecClock(CLOCK_IMx);
}

// branch

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_JP_nn(uint16_t wNN) {
	Z80().RegPC().Set(wNN);
	AddExecClock(CLOCK_JP_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_JP_QHL() {
	Z80().RegPC().Copy(Z80().RegHL());
	AddExecClock(CLOCK_JP_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_JP_QIX() {
	Z80().RegPC().Copy(Z80().RegIX());
	AddExecClock(CLOCK_JP_QIX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_JP_QIY() {
	Z80().RegPC().Copy(Z80().RegIY());
	AddExecClock(CLOCK_JP_QIY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_JP_cc_nn(TBOOL flgCC, uint16_t wNN) {
	if (flgCC) {
		Z80().RegPC().Set(wNN);
	}
	AddExecClock(CLOCK_JP_cc_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_JR_e(uint8_t btE) {
	Z80().AddRegPC(btE);
	AddExecClock(CLOCK_JR_e);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_JR_cc_e(TBOOL flgCC, uint8_t btE) {
	AddExecClock(CLOCK_JR_cc_e_1);
	if (flgCC) {
		Z80().AddRegPC(btE);
		AddExecClock(CLOCK_JR_cc_e_2);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_DJNZ_e(uint8_t btE) {
	Z80().RegB().Ref()--;
	AddExecClock(CLOCK_DJNZ_e_1);
	if (Z80().RegB().Get() != 0) {
		Z80().AddRegPC(btE);
		AddExecClock(CLOCK_DJNZ_e_2);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CALL_nn(uint16_t wNN) {
	Z80().PushReg(Z80().RegPC());
	Z80().RegPC().Set(wNN);
	AddExecClock(CLOCK_CALL_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CALL_cc_nn(TBOOL flgCC, uint16_t wNN) {
	AddExecClock(CLOCK_CALL_cc_nn_1);
	if (flgCC) {
		AddExecClock(CLOCK_CALL_cc_nn_2);
		Z80().PushReg(Z80().RegPC());
		Z80().RegPC().Set(wNN);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RET() {
	Z80().PopReg(Z80().RegPC());
	AddExecClock(CLOCK_RET);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RET_cc(TBOOL flgCC) {
	AddExecClock(CLOCK_RET_cc_1);
	if (flgCC) {
		AddExecClock(CLOCK_RET_cc_2);
		Z80().PopReg(Z80().RegPC());
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RST_n(uint8_t btN) {
	Z80().PushReg(Z80().RegPC());
	Z80().RegPC().Set(uint16_t(btN));
	AddExecClock(CLOCK_RST_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RETI() {
	Z80().PopReg(Z80().RegPC());
	Z80().FinishInterrupt();
	AddExecClock(CLOCK_RETI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_RETN() {
	Z80().SetEnableInterrupt(Z80().IsEnableInterrupt2());
	Z80().SetEnableInterruptReserve(Z80().IsEnableInterrupt2());
	Z80().PopReg(Z80().RegPC());
	Z80().FinishNMInterrupt();
	AddExecClock(CLOCK_RETN);
}

// input/output

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IN_A_Qn(uint8_t btN) {
	Z80().RegA().Set(Z80().ReadIO(btN));
	AddExecClock(CLOCK_IN_A_Qn);
}

#ifdef Z80CFG_IOADDR_WIDTH_8
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IN_r_QC(TREGREF reg) {
	reg.Set(Z80().ReadIO(Z80().RegC()));
	Calc_IN_r_QC(reg);
	AddExecClock(CLOCK_IN_r_QC);
}
#else // Z80CFG_IOADDR_WIDTH_16
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IN_r_QC(TREGREF reg) {
	reg.Set(Z80().ReadIO(Z80().RegBC()));
	Calc_IN_r_QC(reg);
	AddExecClock(CLOCK_IN_r_QC);
}
#endif // Z80CFG_IOADDR_WIDTH

#ifdef Z80CFG_IOADDR_WIDTH_8
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IN_F_QC() {
	Z80().RegF().Set(Z80().ReadIO(Z80().RegC()));
	Calc_IN_r_QC(Z80().RegF());
	AddExecClock(CLOCK_IN_F_QC);
}
#else // Z80CFG_IOADDR_WIDTH_16
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IN_F_QC() {
	Z80().RegF().Set(Z80().ReadIO(Z80().RegBC()));
	Calc_IN_r_QC(Z80().RegF());
	AddExecClock(CLOCK_IN_F_QC);
}
#endif // Z80CFG_IOADDR_WIDTH

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OUT_Qn_A(uint8_t btN) {
	Z80().WriteIO(btN, Z80().RegA());
	AddExecClock(CLOCK_OUT_Qn_A);
}

#ifdef Z80CFG_IOADDR_WIDTH_8
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OUT_QC_r(TCREGREF reg) {
	Z80().WriteIO(Z80().RegC(), reg.Get());
	AddExecClock(CLOCK_OUT_QC_r);
}
#else // Z80CFG_IOADDR_WIDTH_16
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OUT_QC_r(TCREGREF reg) {
	Z80().WriteIO(Z80().RegBC(), reg.Get());
	AddExecClock(CLOCK_OUT_QC_r);
}
#endif // Z80CFG_IOADDR_WIDTH

#ifdef Z80CFG_IOADDR_WIDTH_8
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OUT_QC_0() {
	Z80().WriteIO(Z80().RegC(), 0);
	AddExecClock(CLOCK_OUT_QC_0);
}
#else // Z80CFG_IOADDR_WIDTH_16
Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OUT_QC_0() {
	Z80().WriteIO(Z80().RegBC(), 0);
	AddExecClock(CLOCK_OUT_QC_0);
}
#endif // Z80CFG_IOADDR_WIDTH

// block

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LDI() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Z80().WriteMemory(Z80().RegDE(), btData);
	Z80().RegHL().Ref()++;
	Z80().RegDE().Ref()++;
	Z80().RegBC().Ref()--;
	Calc_LDI_LDD(Z80().RegBC());
	AddExecClock(CLOCK_LDI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LDD() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Z80().WriteMemory(Z80().RegDE(), btData);
	Z80().RegHL().Ref()--;
	Z80().RegDE().Ref()--;
	Z80().RegBC().Ref()--;
	Calc_LDI_LDD(Z80().RegBC());
	AddExecClock(CLOCK_LDD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CPI() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Z80().RegHL().Ref()++;
	Z80().RegBC().Ref()--;
	Calc_CPI_CPD(Z80().RegBC(), Z80().RegA(), btData);
	AddExecClock(CLOCK_CPI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CPD() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Z80().RegHL().Ref()--;
	Z80().RegBC().Ref()--;
	Calc_CPI_CPD(Z80().RegBC(), Z80().RegA(), btData);
	AddExecClock(CLOCK_CPD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INI() {
	uint8_t btData;
	btData = Z80().ReadIO(Z80().RegC());
	Z80().WriteMemory(Z80().RegHL(), btData);
	Z80().RegHL().Ref()++;
	Z80().RegB().Ref()--;
	Calc_INI_IND_OUTI_OUTD(Z80().RegB());
	AddExecClock(CLOCK_INI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_IND() {
	uint8_t btData;
	btData = Z80().ReadIO(Z80().RegC());
	Z80().WriteMemory(Z80().RegHL(), btData);
	Z80().RegHL().Ref()--;
	Z80().RegB().Ref()--;
	Calc_INI_IND_OUTI_OUTD(Z80().RegB());
	AddExecClock(CLOCK_IND);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OUTI() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Z80().WriteIO(Z80().RegC(), btData);
	Z80().RegHL().Ref()++;
	Z80().RegB().Ref()--;
	Calc_INI_IND_OUTI_OUTD(Z80().RegB());
	AddExecClock(CLOCK_OUTI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OUTD() {
	uint8_t btData;
	btData = Z80().ReadMemory(Z80().RegHL());
	Z80().WriteIO(Z80().RegC(), btData);
	Z80().RegHL().Ref()--;
	Z80().RegB().Ref()--;
	Calc_INI_IND_OUTI_OUTD(Z80().RegB());
	AddExecClock(CLOCK_OUTD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LDIR() {
	Exec_LDI();
	if (Z80().TestRegF(P_V_FLAG)) {
		Z80().AddRegPC(uint8_t(-2));
		AddExecClock(CLOCK_LDIR);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_LDDR() {
	Exec_LDD();
	if (Z80().TestRegF(P_V_FLAG)) {
		Z80().AddRegPC(uint8_t(-2));
		AddExecClock(CLOCK_LDDR);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CPIR() {
	Exec_CPI();
	if (Z80().MaskRegF(Z_FLAG | P_V_FLAG) == P_V_FLAG) {
		Z80().AddRegPC(uint8_t(-2));
		AddExecClock(CLOCK_CPIR);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_CPDR() {
	Exec_CPD();
	if (Z80().MaskRegF(Z_FLAG | P_V_FLAG) == P_V_FLAG) {
		Z80().AddRegPC(uint8_t(-2));
		AddExecClock(CLOCK_CPDR);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INIR() {
	Exec_INI();
	if (!Z80().TestRegF(Z_FLAG)) {
		Z80().AddRegPC(uint8_t(-2));
		AddExecClock(CLOCK_INIR);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_INDR() {
	Exec_IND();
	if (!Z80().TestRegF(Z_FLAG)) {
		Z80().AddRegPC(uint8_t(-2));
		AddExecClock(CLOCK_INDR);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OTIR() {
	Exec_OUTI();
	if (!Z80().TestRegF(Z_FLAG)) {
		Z80().AddRegPC(uint8_t(-2));
		AddExecClock(CLOCK_OTIR);
	}
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::Exec_OTDR() {
	Exec_OUTD();
	if (!Z80().TestRegF(Z_FLAG)) {
		Z80().AddRegPC(uint8_t(-2));
		AddExecClock(CLOCK_OTDR);
	}
}

////////////////////////////////////////////////////////////
// interrupt

// interrupt flag process

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80Executor::CopyEnableInterrupt() {
	Z80().SetEnableInterrupt(Z80().IsEnableInterruptReserve());
}

// occurred interrupt

Z80TEMPLATE_EXPLICIT_AW
inline int CZ80Executor::DoInterrupt(uint8_t btIntVect) {
	Z80().SetEnableInterrupt(false);
	Z80().SetEnableInterrupt2(false);
	Z80().SetEnableInterruptReserve(false);
	if (Z80().IsHalting()) {
		Z80().SetHalting(false);
		Z80().RegPC().Ref()++;
	}
	int nExecClockOrg = GetExecClock();
	SetExecClock(0);
	Z80().PushReg(Z80().RegPC());
	switch (Z80().GetInterruptMode()) {
	case 2:
		{ // dummy block
			URegisterPair regpTmp;
			regpTmp.Set(Z80().GetRegI(), btIntVect);
			Z80().RegPC().Set(Z80().ReadMemoryW(regpTmp));
			AddExecClock(CLOCK_INTERRUPT2);
		}
		break;
	case 1:
		Z80().RegPC().Set(0x38);
		AddExecClock(CLOCK_INTERRUPT1);
		break;
	default:
		// Interruption vector that receives it be only [RST n] and [NOP].
		if (btIntVect != 0x00) {
			Z80().RegPC().Set(uint16_t(btIntVect-0xC7));
		}
		AddExecClock(CLOCK_INTERRUPT0);
		break;
	}
	int nExecClock = GetExecClock();
	SetExecClock(nExecClockOrg);
	return nExecClock;
}

// occurred NMI

Z80TEMPLATE_EXPLICIT_AW
inline int CZ80Executor::DoNMInterrupt() {
	Z80().SetEnableInterrupt2(Z80().IsEnableInterrupt());
	Z80().SetEnableInterrupt(false);
	Z80().SetEnableInterruptReserve(false);
	if (Z80().IsHalting()) {
		Z80().SetHalting(false);
		Z80().RegPC().Ref()++;
	}
	int nExecClockOrg = GetExecClock();
	SetExecClock(0);
	Z80().PushReg(Z80().RegPC());
	Z80().RegPC().Set(0x0066);
	AddExecClock(CLOCK_NMINTERRUPT);
	int nExecClock = GetExecClock();
	SetExecClock(nExecClockOrg);
	return nExecClock;
}

#endif // Z80Executor_DEFINED
