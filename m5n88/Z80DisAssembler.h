////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80DisAssembler_DEFINED
#define Z80DisAssembler_DEFINED

////////////////////////////////////////////////////////////
// CZ80DisAssembler

#define CZ80DisAssembler \
	TZ80ExecutorBase< \
		CZ80, \
		const char*, \
		const char*, const char*, const char*, const char*>

////////////////////////////////////////////////////////////
// substitute function

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGPREF CZ80DisAssembler::RegAF() {
	return "AF";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegA() {
	return "A";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegF() {
	return "F";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGPREF CZ80DisAssembler::RegBC() {
	return "BC";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegB() {
	return "B";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegC() {
	return "C";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGPREF CZ80DisAssembler::RegDE() {
	return "DE";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegD() {
	return "D";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegE() {
	return "E";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGPREF CZ80DisAssembler::RegHL() {
	return "HL";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegH() {
	return "H";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegL() {
	return "L";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGPREF CZ80DisAssembler::RegIX() {
	return "IX";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegIXH() {
	return "IXH";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegIXL() {
	return "IXL";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGPREF CZ80DisAssembler::RegIY() {
	return "IY";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegIYH() {
	return "IYH";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGREF CZ80DisAssembler::RegIYL() {
	return "IYL";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TREGPREF CZ80DisAssembler::RegSP() {
	return "SP";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TBOOL CZ80DisAssembler::FlagNZ() {
	return "NZ";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TBOOL CZ80DisAssembler::FlagZ() {
	return "Z";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TBOOL CZ80DisAssembler::FlagNC() {
	return "NC";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TBOOL CZ80DisAssembler::FlagC() {
	return "C";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TBOOL CZ80DisAssembler::FlagPO() {
	return "PO";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TBOOL CZ80DisAssembler::FlagPE() {
	return "PE";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TBOOL CZ80DisAssembler::FlagP() {
	return "P";
}

Z80TEMPLATE_EXPLICIT_AW
inline CZ80DisAssembler::TBOOL CZ80DisAssembler::FlagM() {
	return "M";
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::IncRegR() {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::FetchByte(uint8_t& btData) {
	Z80().FetchByte(btData);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::FetchWord(uint16_t& wData) {
	Z80().FetchWord(wData);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::FetchByteM1(uint8_t& btData) {
	Z80().FetchByteM1(btData);
}

Z80TEMPLATE_EXPLICIT_AW
inline int CZ80DisAssembler::GetExecClock() {
	return Z80().GetExecClock();
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::SetExecClock(int nExecClock) {
	Z80().SetExecClock(nExecClock);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::AddExecClock(int nExecClock) {
	Z80().AddExecClock(nExecClock);
}

////////////////////////////////////////////////////////////
// calculate

// 8bit load

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_INC_8(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_DEC_8(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_ADD_8(uint8_t& /*btDst*/, uint8_t /*btSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_ADC_8(uint8_t& /*btDst*/, uint8_t /*btSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SUB_8(uint8_t& /*btDst*/, uint8_t /*btSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SBC_8(uint8_t& /*btDst*/, uint8_t /*btSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_AND_8(uint8_t& /*btDst*/, uint8_t /*btSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_OR_8(uint8_t& /*btDst*/, uint8_t /*btSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_XOR_8(uint8_t& /*btDst*/, uint8_t /*btSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_CP_8(uint8_t /*btDst*/, uint8_t /*btSrc*/) {
}

// rotate/shift

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RLCA(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RLA(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RRCA(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RRA(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RLC(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RL(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RRC(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RR(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SLA(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SRA(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SLL(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SRL(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RLD(uint8_t& /*btData1*/, uint8_t& /*btData2*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RRD(uint8_t& /*btData1*/, uint8_t& /*btData2*/) {
}

// bit operate/test

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_BIT_b(uint8_t /*btB*/, uint8_t /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SET_b(uint8_t /*btB*/, uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_RES_b(uint8_t /*btB*/, uint8_t& /*btData*/) {
}

// 16bit calculate

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_INC_16(uint16_t& /*wData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_DEC_16(uint16_t& /*wData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_ADD_16(uint16_t& /*wDst*/, uint16_t /*wSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_ADC_16(uint16_t& /*wDst*/, uint16_t /*wSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SBC_16(uint16_t& /*wDst*/, uint16_t /*wSrc*/) {
}

// other calculate

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_DAA(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_CPL(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_NEG(uint8_t& /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_CCF() {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_SCF() {
}

// others

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_LD_A_IR(uint8_t& /*btDst*/, uint8_t /*btSrc*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_IN_r_QC(uint8_t /*btData*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_LDI_LDD(uint16_t /*wCounter*/) {
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_CPI_CPD(
	uint16_t /*wCounter*/, uint8_t /*btDst*/, uint8_t /*btSrc*/)
{
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Calc_INI_IND_OUTI_OUTD(uint8_t /*btCounter*/) {
}

////////////////////////////////////////////////////////////
// differentiation OP code process

// 8bit load

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_r_r2(TREGREF reg, TCREGREF reg2) {
	Z80().FormatMnemonic("LD\t%s, %s", reg, reg2);
	AddExecClock(CLOCK_LD_r_r2);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_r_n(TREGREF reg, uint8_t btN) {
	Z80().FormatMnemonic("LD\t%s, 0%02XH", reg, btN);
	AddExecClock(CLOCK_LD_r_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_A_Qss(TCREGPREF regp) {
	Z80().FormatMnemonic("LD\tA, (%s)", regp);
	AddExecClock(CLOCK_LD_A_Qss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_Qss_A(TCREGPREF regp) {
	Z80().FormatMnemonic("LD\t(%s), A", regp);
	AddExecClock(CLOCK_LD_Qss_A);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_A_Qnn(uint16_t wNN) {
	Z80().FormatMnemonic("LD\tA, (0%04XH)", wNN);
	AddExecClock(CLOCK_LD_A_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_Qnn_A(uint16_t wNN) {
	Z80().FormatMnemonic("LD\t(0%04XH), A", wNN);
	AddExecClock(CLOCK_LD_Qnn_A);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_r_QHL(TREGREF reg) {
	Z80().FormatMnemonic("LD\t%s, (HL)", reg);
	AddExecClock(CLOCK_LD_r_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_QHL_r(TCREGREF reg) {
	Z80().FormatMnemonic("LD\t(HL), %s", reg);
	AddExecClock(CLOCK_LD_QHL_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_QHL_n(uint8_t btN) {
	Z80().FormatMnemonic("LD\t(HL), 0%02XH", btN);
	AddExecClock(CLOCK_LD_QHL_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("LD\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_LD_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_QIXd_r(uint8_t btD, TCREGREF reg) {
	Z80().FormatMnemonic("LD\t(IX%+d), %s", (int8_t)btD, reg);
	AddExecClock(CLOCK_LD_QIXd_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_QIXd_n(uint8_t btD, uint8_t btN) {
	Z80().FormatMnemonic("LD\t(IX%+d), 0%02XH", (int8_t)btD, btN);
	AddExecClock(CLOCK_LD_QIXd_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("LD\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_LD_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_QIYd_r(uint8_t btD, TCREGREF reg) {
	Z80().FormatMnemonic("LD\t(IY%+d), %s", (int8_t)btD, reg);
	AddExecClock(CLOCK_LD_QIYd_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_QIYd_n(uint8_t btD, uint8_t btN) {
	Z80().FormatMnemonic("LD\t(IY%+d), 0%02XH", (int8_t)btD, btN);
	AddExecClock(CLOCK_LD_QIYd_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_A_I() {
	Z80().FormatMnemonic("LD\tA, I");
	AddExecClock(CLOCK_LD_A_I);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_I_A() {
	Z80().FormatMnemonic("LD\tI, A");
	AddExecClock(CLOCK_LD_I_A);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_A_R() {
	Z80().FormatMnemonic("LD\tA, R");
	AddExecClock(CLOCK_LD_A_R);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_R_A() {
	Z80().FormatMnemonic("LD\tR, A");
	AddExecClock(CLOCK_LD_R_A);
}

// 16bit load

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_ss_nn(TREGPREF regp, uint16_t wNN) {
	Z80().FormatMnemonic("LD\t%s, 0%04XH", regp, wNN);
	AddExecClock(CLOCK_LD_ss_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_ss_Qnn(TREGPREF regp, uint16_t wNN) {
	Z80().FormatMnemonic("LD\t%s, (0%04XH)", regp, wNN);
	AddExecClock(CLOCK_LD_ss_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_Qnn_ss(uint16_t wNN, TCREGPREF regp) {
	Z80().FormatMnemonic("LD\t(0%04XH), %s", wNN, regp);
	AddExecClock(CLOCK_LD_Qnn_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_HL_Qnn(uint16_t wNN) {
	Z80().FormatMnemonic("LD\tHL, (0%04XH)", wNN);
	AddExecClock(CLOCK_LD_HL_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_Qnn_HL(uint16_t wNN) {
	Z80().FormatMnemonic("LD\t(0%04XH), HL", wNN);
	AddExecClock(CLOCK_LD_Qnn_HL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_IX_nn(uint16_t wNN) {
	Z80().FormatMnemonic("LD\tIX, 0%04XH", wNN);
	AddExecClock(CLOCK_LD_IX_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_IX_Qnn(uint16_t wNN) {
	Z80().FormatMnemonic("LD\tIX, (0%04XH)", wNN);
	AddExecClock(CLOCK_LD_IX_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_Qnn_IX(uint16_t wNN) {
	Z80().FormatMnemonic("LD\t(0%04XH), IX", wNN);
	AddExecClock(CLOCK_LD_Qnn_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_IY_nn(uint16_t wNN) {
	Z80().FormatMnemonic("LD\tIY, 0%04XH", wNN);
	AddExecClock(CLOCK_LD_IY_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_IY_Qnn(uint16_t wNN) {
	Z80().FormatMnemonic("LD\tIY, (0%04XH)", wNN);
	AddExecClock(CLOCK_LD_IY_Qnn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_Qnn_IY(uint16_t wNN) {
	Z80().FormatMnemonic("LD\t(0%04XH), IY", wNN);
	AddExecClock(CLOCK_LD_Qnn_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_SP_HL() {
	Z80().FormatMnemonic("LD\tSP, HL");
	AddExecClock(CLOCK_LD_SP_HL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_SP_IX() {
	Z80().FormatMnemonic("LD\tSP, IX");
	AddExecClock(CLOCK_LD_SP_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LD_SP_IY() {
	Z80().FormatMnemonic("LD\tSP, IY");
	AddExecClock(CLOCK_LD_SP_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_PUSH_ss(TREGPREF regp) {
	Z80().FormatMnemonic("PUSH\t%s", regp);
	AddExecClock(CLOCK_PUSH_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_PUSH_IX() {
	Z80().FormatMnemonic("PUSH\tIX");
	AddExecClock(CLOCK_PUSH_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_PUSH_IY() {
	Z80().FormatMnemonic("PUSH\tIY");
	AddExecClock(CLOCK_PUSH_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_POP_ss(TREGPREF regp) {
	Z80().FormatMnemonic("POP\t%s", regp);
	AddExecClock(CLOCK_POP_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_POP_IX() {
	Z80().FormatMnemonic("POP\tIX");
	AddExecClock(CLOCK_POP_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_POP_IY() {
	Z80().FormatMnemonic("POP\tIY");
	AddExecClock(CLOCK_POP_IY);
}

// exchange

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_EX_AF_AF2() {
	Z80().FormatMnemonic("EX\tAF, AF'");
	AddExecClock(CLOCK_EX_AF_AF2);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_EX_DE_HL() {
	Z80().FormatMnemonic("EX\tDE, HL");
	AddExecClock(CLOCK_EX_DE_HL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_EXX() {
	Z80().FormatMnemonic("EXX");
	AddExecClock(CLOCK_EXX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_EX_QSP_HL() {
	Z80().FormatMnemonic("EX\t(SP), HL");
	AddExecClock(CLOCK_EX_QSP_HL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_EX_QSP_IX() {
	Z80().FormatMnemonic("EX\t(SP), IX");
	AddExecClock(CLOCK_EX_QSP_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_EX_QSP_IY() {
	Z80().FormatMnemonic("EX\t(SP), IY");
	AddExecClock(CLOCK_EX_QSP_IY);
}

// 8bit calculate

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INC_r(TREGREF reg) {
	Z80().FormatMnemonic("INC\t%s", reg);
	AddExecClock(CLOCK_INC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INC_QHL() {
	Z80().FormatMnemonic("INC\t(HL)");
	AddExecClock(CLOCK_INC_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INC_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("INC\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_INC_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INC_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("INC\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_INC_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DEC_r(TREGREF reg) {
	Z80().FormatMnemonic("DEC\t%s", reg);
	AddExecClock(CLOCK_DEC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DEC_QHL() {
	Z80().FormatMnemonic("DEC\t(HL)");
	AddExecClock(CLOCK_DEC_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DEC_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("DEC\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_DEC_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DEC_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("DEC\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_DEC_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADD_A_r(TCREGREF reg) {
	Z80().FormatMnemonic("ADD\tA, %s", reg);
	AddExecClock(CLOCK_ADD_A_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADD_A_n(uint8_t btN) {
	Z80().FormatMnemonic("ADD\tA, 0%02XH", btN);
	AddExecClock(CLOCK_ADD_A_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADD_A_QHL() {
	Z80().FormatMnemonic("ADD\tA, (HL)");
	AddExecClock(CLOCK_ADD_A_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADD_A_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("ADD\tA, (IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_ADD_A_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADD_A_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("ADD\tA, (IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_ADD_A_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADC_A_r(TCREGREF reg) {
	Z80().FormatMnemonic("ADC\tA, %s", reg);
	AddExecClock(CLOCK_ADC_A_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADC_A_n(uint8_t btN) {
	Z80().FormatMnemonic("ADC\tA, 0%02XH", btN);
	AddExecClock(CLOCK_ADC_A_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADC_A_QHL() {
	Z80().FormatMnemonic("ADC\tA, (HL)");
	AddExecClock(CLOCK_ADC_A_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADC_A_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("ADC\tA, (IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_ADC_A_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADC_A_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("ADC\tA, (IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_ADC_A_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SUB_r(TCREGREF reg) {
	Z80().FormatMnemonic("SUB\t%s", reg);
	AddExecClock(CLOCK_SUB_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SUB_n(uint8_t btN) {
	Z80().FormatMnemonic("SUB\t0%02XH", btN);
	AddExecClock(CLOCK_SUB_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SUB_QHL() {
	Z80().FormatMnemonic("SUB\t(HL)");
	AddExecClock(CLOCK_SUB_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SUB_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("SUB\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SUB_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SUB_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("SUB\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SUB_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SBC_A_r(TCREGREF reg) {
	Z80().FormatMnemonic("SBC\tA, %s", reg);
	AddExecClock(CLOCK_SBC_A_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SBC_A_n(uint8_t btN) {
	Z80().FormatMnemonic("SBC\tA, 0%02XH", btN);
	AddExecClock(CLOCK_SBC_A_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SBC_A_QHL() {
	Z80().FormatMnemonic("SBC\tA, (HL)");
	AddExecClock(CLOCK_SBC_A_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SBC_A_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("SBC\tA, (IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SBC_A_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SBC_A_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("SBC\tA, (IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SBC_A_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_AND_r(TCREGREF reg) {
	Z80().FormatMnemonic("AND\t%s", reg);
	AddExecClock(CLOCK_AND_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_AND_n(uint8_t btN) {
	Z80().FormatMnemonic("AND\t0%02XH", btN);
	AddExecClock(CLOCK_AND_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_AND_QHL() {
	Z80().FormatMnemonic("AND\t(HL)");
	AddExecClock(CLOCK_AND_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_AND_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("AND\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_AND_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_AND_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("AND\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_AND_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OR_r(TCREGREF reg) {
	Z80().FormatMnemonic("OR\t%s", reg);
	AddExecClock(CLOCK_OR_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OR_n(uint8_t btN) {
	Z80().FormatMnemonic("OR\t0%02XH", btN);
	AddExecClock(CLOCK_OR_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OR_QHL() {
	Z80().FormatMnemonic("OR\t(HL)");
	AddExecClock(CLOCK_OR_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OR_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("OR\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_OR_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OR_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("OR\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_OR_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_XOR_r(TCREGREF reg) {
	Z80().FormatMnemonic("XOR\t%s", reg);
	AddExecClock(CLOCK_XOR_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_XOR_n(uint8_t btN) {
	Z80().FormatMnemonic("XOR\t0%02XH", btN);
	AddExecClock(CLOCK_XOR_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_XOR_QHL() {
	Z80().FormatMnemonic("XOR\t(HL)");
	AddExecClock(CLOCK_XOR_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_XOR_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("XOR\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_XOR_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_XOR_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("XOR\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_XOR_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CP_r(TCREGREF reg) {
	Z80().FormatMnemonic("CP\t%s", reg);
	AddExecClock(CLOCK_CP_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CP_n(uint8_t btN) {
	Z80().FormatMnemonic("CP\t0%02XH", btN);
	AddExecClock(CLOCK_CP_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CP_QHL() {
	Z80().FormatMnemonic("CP\t(HL)");
	AddExecClock(CLOCK_CP_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CP_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("CP\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_CP_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CP_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("CP\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_CP_QIYd);
}

// rotate/shift

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLCA() {
	Z80().FormatMnemonic("RLCA");
	AddExecClock(CLOCK_RLCA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLC_r(TREGREF reg) {
	Z80().FormatMnemonic("RLC\t%s", reg);
	AddExecClock(CLOCK_RLC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLC_QHL() {
	Z80().FormatMnemonic("RLC\t(HL)");
	AddExecClock(CLOCK_RLC_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLC_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("RLC\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_RLC_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLC_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("RLC\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_RLC_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLC_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RLC\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_RLC_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLC_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RLC\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_RLC_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLA() {
	Z80().FormatMnemonic("RLA");
	AddExecClock(CLOCK_RLA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RL_r(TREGREF reg) {
	Z80().FormatMnemonic("RL\t%s", reg);
	AddExecClock(CLOCK_RL_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RL_QHL() {
	Z80().FormatMnemonic("RL\t(HL)");
	AddExecClock(CLOCK_RL_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RL_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("RL\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_RL_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RL_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("RL\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_RL_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RL_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RL\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_RL_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RL_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RL\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_RL_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRCA() {
	Z80().FormatMnemonic("RRCA");
	AddExecClock(CLOCK_RRCA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRC_r(TREGREF reg) {
	Z80().FormatMnemonic("RRC\t%s", reg);
	AddExecClock(CLOCK_RRC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRC_QHL() {
	Z80().FormatMnemonic("RRC\t(HL)");
	AddExecClock(CLOCK_RRC_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRC_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("RRC\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_RRC_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRC_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("RRC\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_RRC_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRC_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RRC\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_RRC_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRC_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RRC\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_RRC_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRA() {
	Z80().FormatMnemonic("RRA");
	AddExecClock(CLOCK_RRA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RR_r(TREGREF reg) {
	Z80().FormatMnemonic("RR\t%s", reg);
	AddExecClock(CLOCK_RR_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RR_QHL() {
	Z80().FormatMnemonic("RR\t(HL)");
	AddExecClock(CLOCK_RR_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RR_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("RR\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_RR_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RR_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("RR\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_RR_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RR_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RR\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_RR_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RR_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RR\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_RR_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLA_r(TREGREF reg) {
	Z80().FormatMnemonic("SLA\t%s", reg);
	AddExecClock(CLOCK_SLA_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLA_QHL() {
	Z80().FormatMnemonic("SLA\t(HL)");
	AddExecClock(CLOCK_SLA_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLA_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("SLA\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SLA_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLA_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("SLA\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SLA_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLA_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SLA\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_SLA_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLA_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SLA\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_SLA_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRA_r(TREGREF reg) {
	Z80().FormatMnemonic("SRA\t%s", reg);
	AddExecClock(CLOCK_SRA_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRA_QHL() {
	Z80().FormatMnemonic("SRA\t(HL)");
	AddExecClock(CLOCK_SRA_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRA_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("SRA\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SRA_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRA_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("SRA\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SRA_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRA_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SRA\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_SRA_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRA_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SRA\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_SRA_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLL_r(TREGREF reg) {
	Z80().FormatMnemonic("SLL\t%s", reg);
	AddExecClock(CLOCK_SLL_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLL_QHL() {
	Z80().FormatMnemonic("SLL\t(HL)");
	AddExecClock(CLOCK_SLL_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLL_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("SLL\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SLL_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLL_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("SLL\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SLL_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLL_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SLL\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_SLL_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SLL_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SLL\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_SLL_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRL_r(TREGREF reg) {
	Z80().FormatMnemonic("SRL\t%s", reg);
	AddExecClock(CLOCK_SRL_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRL_QHL() {
	Z80().FormatMnemonic("SRL\t(HL)");
	AddExecClock(CLOCK_SRL_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRL_QIXd(uint8_t btD) {
	Z80().FormatMnemonic("SRL\t(IX%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SRL_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRL_QIYd(uint8_t btD) {
	Z80().FormatMnemonic("SRL\t(IY%+d)", (int8_t)btD);
	AddExecClock(CLOCK_SRL_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRL_r_QIXd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SRL\t%s, (IX%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_SRL_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SRL_r_QIYd(TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SRL\t%s, (IY%+d)", reg, (int8_t)btD);
	AddExecClock(CLOCK_SRL_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RLD() {
	Z80().FormatMnemonic("RLD");
	AddExecClock(CLOCK_RLD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RRD() {
	Z80().FormatMnemonic("RRD");
	AddExecClock(CLOCK_RRD);
}

// bit operate/test

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_BIT_b_r(uint8_t btB, TCREGREF reg) {
	Z80().FormatMnemonic("BIT\t%d, %s", btB, reg);
	AddExecClock(CLOCK_BIT_b_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_BIT_b_QHL(uint8_t btB) {
	Z80().FormatMnemonic("BIT\t%d, (HL)", btB);
	AddExecClock(CLOCK_BIT_b_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_BIT_b_QIXd(uint8_t btB, uint8_t btD) {
	Z80().FormatMnemonic("BIT\t%d, (IX%+d)", btB, (int8_t)btD);
	AddExecClock(CLOCK_BIT_b_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_BIT_b_QIYd(uint8_t btB, uint8_t btD) {
	Z80().FormatMnemonic("BIT\t%d, (IY%+d)", btB, (int8_t)btD);
	AddExecClock(CLOCK_BIT_b_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SET_b_r(uint8_t btB, TREGREF reg) {
	Z80().FormatMnemonic("SET\t%d, %s", btB, reg);
	AddExecClock(CLOCK_SET_b_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SET_b_QHL(uint8_t btB) {
	Z80().FormatMnemonic("SET\t%d, (HL)", btB);
	AddExecClock(CLOCK_SET_b_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SET_b_QIXd(uint8_t btB, uint8_t btD) {
	Z80().FormatMnemonic("SET\t%d, (IX%+d)", btB, (int8_t)btD);
	AddExecClock(CLOCK_SET_b_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SET_b_QIYd(uint8_t btB, uint8_t btD) {
	Z80().FormatMnemonic("SET\t%d, (IY%+d)", btB, (int8_t)btD);
	AddExecClock(CLOCK_SET_b_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline
void CZ80DisAssembler::Exec_SET_b_r_QIXd(uint8_t btB, TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SET\t%d, %s, (IX%+d)", btB, reg, (int8_t)btD);
	AddExecClock(CLOCK_SET_b_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline
void CZ80DisAssembler::Exec_SET_b_r_QIYd(uint8_t btB, TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("SET\t%d, %s, (IY%+d)", btB, reg, (int8_t)btD);
	AddExecClock(CLOCK_SET_b_r_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RES_b_r(uint8_t btB, TREGREF reg) {
	Z80().FormatMnemonic("RES\t%d, %s", btB, reg);
	AddExecClock(CLOCK_RES_b_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RES_b_QHL(uint8_t btB) {
	Z80().FormatMnemonic("RES\t%d, (HL)", btB);
	AddExecClock(CLOCK_RES_b_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RES_b_QIXd(uint8_t btB, uint8_t btD) {
	Z80().FormatMnemonic("RES\t%d, (IX%+d)", btB, (int8_t)btD);
	AddExecClock(CLOCK_RES_b_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RES_b_QIYd(uint8_t btB, uint8_t btD) {
	Z80().FormatMnemonic("RES\t%d, (IY%+d)", btB, (int8_t)btD);
	AddExecClock(CLOCK_RES_b_QIYd);
}

Z80TEMPLATE_EXPLICIT_AW
inline
void CZ80DisAssembler::Exec_RES_b_r_QIXd(uint8_t btB, TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RES\t%d, %s, (IX%+d)", btB, reg, (int8_t)btD);
	AddExecClock(CLOCK_RES_b_r_QIXd);
}

Z80TEMPLATE_EXPLICIT_AW
inline
void CZ80DisAssembler::Exec_RES_b_r_QIYd(uint8_t btB, TREGREF reg, uint8_t btD) {
	Z80().FormatMnemonic("RES\t%d, %s, (IY%+d)", btB, reg, (int8_t)btD);
	AddExecClock(CLOCK_RES_b_r_QIYd);
}

// 16bit calculate

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INC_ss(TREGPREF regp) {
	Z80().FormatMnemonic("INC\t%s", regp);
	AddExecClock(CLOCK_INC_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INC_IX() {
	Z80().FormatMnemonic("INC\tIX");
	AddExecClock(CLOCK_INC_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INC_IY() {
	Z80().FormatMnemonic("INC\tIY");
	AddExecClock(CLOCK_INC_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DEC_ss(TREGPREF regp) {
	Z80().FormatMnemonic("DEC\t%s", regp);
	AddExecClock(CLOCK_DEC_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DEC_IX() {
	Z80().FormatMnemonic("DEC\tIX");
	AddExecClock(CLOCK_DEC_IX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DEC_IY() {
	Z80().FormatMnemonic("DEC\tIY");
	AddExecClock(CLOCK_DEC_IY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADD_HL_ss(TCREGPREF regp) {
	Z80().FormatMnemonic("ADD\tHL, %s", regp);
	AddExecClock(CLOCK_ADD_HL_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADD_IX_ss(TCREGPREF regp) {
	Z80().FormatMnemonic("ADD\tIX, %s", regp);
	AddExecClock(CLOCK_ADD_IX_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADD_IY_ss(TCREGPREF regp) {
	Z80().FormatMnemonic("ADD\tIY, %s", regp);
	AddExecClock(CLOCK_ADD_IY_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_ADC_HL_ss(TCREGPREF regp) {
	Z80().FormatMnemonic("ADC\tHL, %s", regp);
	AddExecClock(CLOCK_ADC_HL_ss);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SBC_HL_ss(TCREGPREF regp) {
	Z80().FormatMnemonic("SBC\tHL, %s", regp);
	AddExecClock(CLOCK_SBC_HL_ss);
}

// other calculate/CPU control

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DAA() {
	Z80().FormatMnemonic("DAA");
	AddExecClock(CLOCK_DAA);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CPL() {
	Z80().FormatMnemonic("CPL");
	AddExecClock(CLOCK_CPL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_NEG() {
	Z80().FormatMnemonic("NEG");
	AddExecClock(CLOCK_NEG);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CCF() {
	Z80().FormatMnemonic("CCF");
	AddExecClock(CLOCK_CCF);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_SCF() {
	Z80().FormatMnemonic("SCF");
	AddExecClock(CLOCK_SCF);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DI() {
	Z80().FormatMnemonic("DI");
	AddExecClock(CLOCK_DI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_EI() {
	Z80().FormatMnemonic("EI");
	AddExecClock(CLOCK_EI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_NOP() {
	Z80().FormatMnemonic("NOP");
	AddExecClock(CLOCK_NOP);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_HALT() {
	Z80().FormatMnemonic("HALT");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_HALT);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_IM0() {
	Z80().FormatMnemonic("IM0");
	AddExecClock(CLOCK_IM0);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_IM1() {
	Z80().FormatMnemonic("IM1");
	AddExecClock(CLOCK_IM1);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_IM2() {
	Z80().FormatMnemonic("IM2");
	AddExecClock(CLOCK_IM2);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_IMx() {
	Z80().FormatMnemonic("IM?");
	AddExecClock(CLOCK_IMx);
}

// branch

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_JP_nn(uint16_t wNN) {
	Z80().FormatMnemonic("JP\t0%04XH", wNN);
	AddExecClock(CLOCK_JP_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_JP_QHL() {
	Z80().FormatMnemonic("JP\t(HL)");
	AddExecClock(CLOCK_JP_QHL);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_JP_QIX() {
	Z80().FormatMnemonic("JP\t(IX)");
	AddExecClock(CLOCK_JP_QIX);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_JP_QIY() {
	Z80().FormatMnemonic("JP\t(IY)");
	AddExecClock(CLOCK_JP_QIY);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_JP_cc_nn(TBOOL flgCC, uint16_t wNN) {
	Z80().FormatMnemonic("JP\t%s, 0%04XH", flgCC, wNN);
	Z80().SetStepExecuteOpCode2(true);
	AddExecClock(CLOCK_JP_cc_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_JR_e(uint8_t btE) {
	Z80().FormatMnemonic("JR\t0%04XH", uint16_t(Z80().RegPC()+(int8_t)btE));
	AddExecClock(CLOCK_JR_e);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_JR_cc_e(TBOOL flgCC, uint8_t btE) {
	Z80().FormatMnemonic(
		"JR\t%s, 0%04XH", flgCC, uint16_t(Z80().RegPC()+(int8_t)btE));
	Z80().SetStepExecuteOpCode2(true);
	AddExecClock(CLOCK_JR_cc_e_1);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_DJNZ_e(uint8_t btE) {
	Z80().FormatMnemonic(
		"DJNZ\t0%04XH", uint16_t(Z80().RegPC()+(int8_t)btE));
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_DJNZ_e_1);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CALL_nn(uint16_t wNN) {
	Z80().FormatMnemonic("CALL\t0%04XH", wNN);
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_CALL_nn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CALL_cc_nn(TBOOL flgCC, uint16_t wNN) {
	Z80().FormatMnemonic("CALL\t%s, 0%04XH", flgCC, wNN);
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_CALL_cc_nn_1);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RET() {
	Z80().FormatMnemonic("RET");
	AddExecClock(CLOCK_RET);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RET_cc(TBOOL flgCC) {
	Z80().FormatMnemonic("RET\t%s", flgCC);
	AddExecClock(CLOCK_RET_cc_1);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RST_n(uint8_t btN) {
	Z80().FormatMnemonic("RST\t%02XH", btN);
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_RST_n);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RETI() {
	Z80().FormatMnemonic("RETI");
	AddExecClock(CLOCK_RETI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_RETN() {
	Z80().FormatMnemonic("RETN");
	AddExecClock(CLOCK_RETN);
}

// input/output

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_IN_A_Qn(uint8_t btN) {
	Z80().FormatMnemonic("IN\tA, (0%02XH)", btN);
	AddExecClock(CLOCK_IN_A_Qn);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_IN_r_QC(TREGREF reg) {
	Z80().FormatMnemonic("IN\t%s, (C)", reg);
	AddExecClock(CLOCK_IN_r_QC);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_IN_F_QC() {
	Z80().FormatMnemonic("IN\tF, (C)");
	AddExecClock(CLOCK_IN_F_QC);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OUT_Qn_A(uint8_t btN) {
	Z80().FormatMnemonic("OUT\t(0%02XH), A", btN);
	AddExecClock(CLOCK_OUT_Qn_A);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OUT_QC_r(TCREGREF reg) {
	Z80().FormatMnemonic("OUT\t(C), %s", reg);
	AddExecClock(CLOCK_OUT_QC_r);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OUT_QC_0() {
	Z80().FormatMnemonic("OUT\t(C), 0");
	AddExecClock(CLOCK_OUT_QC_0);
}

// block

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LDI() {
	Z80().FormatMnemonic("LDI");
	AddExecClock(CLOCK_LDI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LDD() {
	Z80().FormatMnemonic("LDD");
	AddExecClock(CLOCK_LDD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CPI() {
	Z80().FormatMnemonic("CPI");
	AddExecClock(CLOCK_CPI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CPD() {
	Z80().FormatMnemonic("CPD");
	AddExecClock(CLOCK_CPD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INI() {
	Z80().FormatMnemonic("INI");
	AddExecClock(CLOCK_INI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_IND() {
	Z80().FormatMnemonic("IND");
	AddExecClock(CLOCK_IND);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OUTI() {
	Z80().FormatMnemonic("OUTI");
	AddExecClock(CLOCK_OUTI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OUTD() {
	Z80().FormatMnemonic("OUTD");
	AddExecClock(CLOCK_OUTD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LDIR() {
	Z80().FormatMnemonic("LDIR");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_LDI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_LDDR() {
	Z80().FormatMnemonic("LDDR");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_LDD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CPIR() {
	Z80().FormatMnemonic("CPIR");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_CPI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_CPDR() {
	Z80().FormatMnemonic("CPDR");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_CPD);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INIR() {
	Z80().FormatMnemonic("INIR");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_INI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_INDR() {
	Z80().FormatMnemonic("INDR");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_IND);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OTIR() {
	Z80().FormatMnemonic("OTIR");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_OUTI);
}

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::Exec_OTDR() {
	Z80().FormatMnemonic("OTDR");
	Z80().SetStepExecuteOpCode(true);
	AddExecClock(CLOCK_OUTD);
}

////////////////////////////////////////////////////////////
// interrupt

// interrupt flag process

Z80TEMPLATE_EXPLICIT_AW
inline void CZ80DisAssembler::CopyEnableInterrupt() {
}

// occurred interrupt

Z80TEMPLATE_EXPLICIT_AW
inline int CZ80DisAssembler::DoInterrupt(uint8_t /*btIntVect*/) {
	return CLOCK_INTERRUPT2;
}

// occurred NMI

Z80TEMPLATE_EXPLICIT_AW
inline int CZ80DisAssembler::DoNMInterrupt() {
	return CLOCK_NMINTERRUPT;
}

#endif // Z80DisAssembler_DEFINED
