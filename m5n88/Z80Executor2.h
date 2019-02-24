////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80Executor2_DEFINED
#define Z80Executor2_DEFINED

#define M_RegAF() TTZ80::m_regpAF
#define M_RegA() TTZ80::m_regpAF.m_reg.m_regHi
#define M_RegF() TTZ80::m_regpAF.m_reg.m_regLo
#define M_RegAF2() TTZ80::m_regpAF2

#define M_RegBC() TTZ80::m_regpBC
#define M_RegB() TTZ80::m_regpBC.m_reg.m_regHi
#define M_RegC() TTZ80::m_regpBC.m_reg.m_regLo
#define M_RegBC2() TTZ80::m_regpBC2

#define M_RegDE() TTZ80::m_regpDE
#define M_RegD() TTZ80::m_regpDE.m_reg.m_regHi
#define M_RegE() TTZ80::m_regpDE.m_reg.m_regLo
#define M_RegDE2() TTZ80::m_regpDE2

#define M_RegHL() TTZ80::m_regpHL
#define M_RegH() TTZ80::m_regpHL.m_reg.m_regHi
#define M_RegL() TTZ80::m_regpHL.m_reg.m_regLo
#define M_RegHL2() TTZ80::m_regpHL2

#define M_RegIX() TTZ80::m_regpIX
#define M_RegIXH() TTZ80::m_regpIX.m_reg.m_regHi
#define M_RegIXL() TTZ80::m_regpIX.m_reg.m_regLo

#define M_RegIY() TTZ80::m_regpIY
#define M_RegIYH() TTZ80::m_regpIY.m_reg.m_regHi
#define M_RegIYL() TTZ80::m_regpIY.m_reg.m_regLo

#define M_RegPC() TTZ80::m_regpPC

#define M_RegSP() TTZ80::m_regpSP

#define M_GetRegI() \
	TTZ80::m_regpIR.m_bt.m_btHi

#define M_SetRegI(btData) { \
	TTZ80::m_regpIR.m_bt.m_btHi = btData; \
}

#define M_GetRegR() \
	uint8_t(((TTZ80::m_regpIR.m_bt.m_btLo) & 0x7F) | TTZ80::m_btR2)

#define M_SetRegR(btData) { \
	TTZ80::m_regpIR.m_bt.m_btLo = btData; \
	TTZ80::m_btR2 = uint8_t((btData) & 0x80); \
}

#define M_IncRegR() { \
	TTZ80::m_regpIR.m_bt.m_btLo++; \
}

#define M_SwapReg(regp1, regp2) { \
	uint16_t wTmp; \
	wTmp = regp1.m_w; \
	regp1.m_w = regp2.m_w; \
	regp2.m_w = wTmp; \
}

#ifdef Z80CFG_USE_TEMPLATE
#define M_ReadMemory(nAddress) \
	TTZ80::m_arpMemRTable[(nAddress)/TTZ80::MEM_BLOCK](nAddress)

#define M_WriteMemory(nAddress, btData) \
	TTZ80::m_awpMemWTable[(nAddress)/TTZ80::MEM_BLOCK](nAddress, btData)

#define M_ReadMemoryM1(nAddress) \
	TTZ80::m_arpMemRM1Table[(nAddress)/TTZ80::MEM_BLOCK](nAddress)

#define M_ReadIO(nAddress) \
	TTZ80::m_arpIORTable[(nAddress)/TTZ80::IO_BLOCK](nAddress)

#define M_WriteIO(nAddress, btData) \
	TTZ80::m_awpIOWTable[(nAddress)/TTZ80::IO_BLOCK](nAddress, btData)
#else // Z80CFG_NOUSE_TEMPLATE
#define M_ReadMemory(nAddress) \
	ReadMemory(nAddress)

#define M_WriteMemory(nAddress, btData) \
	WriteMemory(nAddress, btData)

#define M_ReadMemoryM1(nAddress) \
	ReadMemoryM1(nAddress)

#define M_ReadIO(nAddress) \
	ReadIO(nAddress)

#define M_WriteIO(nAddress, btData) \
	WriteIO(nAddress, btData)
#endif // Z80CFG_USE/NOUSE_TEMPLATE

#define M_ReadMemoryW(nAddress) \
	uint16_t( \
		M_ReadMemory(nAddress) | \
		(M_ReadMemory(uint16_t((nAddress)+1)) << 8))

#define M_WriteMemoryW(nAddress, wData) { \
	M_WriteMemory(nAddress, uint8_t(wData)); \
	M_WriteMemory(uint16_t((nAddress)+1), uint8_t((wData) >> 8)); \
}

#define M_MaskRegF(nMaskFlag) \
	(M_RegF().m_bt & (nMaskFlag))

#define M_TestRegF(nTestFlag) \
	((M_RegF().m_bt & (nTestFlag)) != 0)

#define M_UpdateRegF(nClear, nSet) { \
	M_RegF().m_bt = uint8_t((M_RegF().m_bt & ~(nClear)) | (nSet)); \
}

#define M_SetRegF(nBitSet) { \
	M_RegF().m_bt |= uint8_t(nBitSet); \
}

#define M_ResetRegF(nBitReset) { \
	M_RegF().m_bt &= uint8_t(~(nBitReset)); \
}

#define M_InvertRegF(nBitInvert) { \
	M_RegF().m_bt ^= uint8_t(nBitInvert); \
}

#define M_FlagNZ() (!M_TestRegF(Z_FLAG))

#define M_FlagZ() M_TestRegF(Z_FLAG)

#define M_FlagNC() (!M_TestRegF(C_FLAG))

#define M_FlagC() M_TestRegF(C_FLAG)

#define M_FlagPO() (!M_TestRegF(P_V_FLAG))

#define M_FlagPE() M_TestRegF(P_V_FLAG)

#define M_FlagP() (!M_TestRegF(S_FLAG))

#define M_FlagM() M_TestRegF(S_FLAG)

#define M_GetRegIXd(btDsp) uint16_t(int32_t(M_RegIX().m_w)+(int8_t)(btDsp))

#define M_GetRegIYd(btDsp) uint16_t(int32_t(M_RegIY().m_w)+(int8_t)(btDsp))

#define M_PushReg(regpPush) { \
	M_RegSP().m_w--; \
	M_WriteMemory(M_RegSP().m_w, regpPush.m_bt.m_btHi); \
	M_RegSP().m_w--; \
	M_WriteMemory(M_RegSP().m_w, regpPush.m_bt.m_btLo); \
}

#define M_PopReg(regpPop) { \
	regpPop.m_bt.m_btLo = M_ReadMemory(M_RegSP().m_w); \
	M_RegSP().m_w++; \
	regpPop.m_bt.m_btHi = M_ReadMemory(M_RegSP().m_w); \
	M_RegSP().m_w++; \
}

#define M_AddRegPC(btE) { \
	M_RegPC().m_w = uint16_t(M_RegPC().m_w+(int)(int8_t)(btE)); \
}

#define M_FetchByte(btData) { \
	btData = M_ReadMemory(M_RegPC().m_w); \
	M_RegPC().m_w++; \
}
#define M_FetchWord(wData) { \
	wData = M_ReadMemoryW(M_RegPC().m_w); \
	M_RegPC().m_w += 2; \
}
#define M_FetchByteM1(btData) { \
	btData = M_ReadMemoryM1(M_RegPC().m_w); \
	M_RegPC().m_w++; \
}

#define M_GetExecClock() TTZ80::m_nExecClock

#define M_SetExecClock(nExecClock) { \
	TTZ80::m_nExecClock = nExecClock; \
}

#define M_AddExecClock(nExecClock) { \
	TTZ80::m_nExecClock += nExecClock; \
}

#define M_IsHalting() TTZ80::m_bHalting

#define M_SetHalting(bHalting) { \
	TTZ80::m_bHalting = bHalting; \
}

#define M_GetInterruptMode() TTZ80::m_nInterruptMode

#define M_SetInterruptMode(nInterruptMode) { \
	TTZ80::m_nInterruptMode = nInterruptMode; \
}

#define M_IsEnableInterrupt() TTZ80::m_bEnableInterrupt

#define M_SetEnableInterrupt(bEnableInterrupt) { \
	TTZ80::m_bEnableInterrupt = bEnableInterrupt; \
}

#define M_IsEnableInterrupt2() TTZ80::m_bEnableInterrupt2

#define M_SetEnableInterrupt2(bEnableInterrupt2) { \
	TTZ80::m_bEnableInterrupt2 = bEnableInterrupt2; \
}

#define M_IsEnableInterruptReserve() TTZ80::m_bEnableInterruptReserve

#define M_SetEnableInterruptReserve(bEnableInterruptReserve) { \
	TTZ80::m_bEnableInterruptReserve = bEnableInterruptReserve; \
}

#define M_ProcessHALT() { \
	TTZ80::m_pThis->ProcessHALT(); \
}

#define M_FinishInterrupt() { \
	TTZ80::m_pThis->FinishInterrupt(); \
}

#define M_FinishNMInterrupt() { \
	TTZ80::m_pThis->FinishNMInterrupt(); \
}

////////////////////////////////////////////////////////////
// calculate

// 8bit load

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_INC_8(btData) { \
	btData++; \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_INC_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_INC_8(btData) { \
	btData++; \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btData == 0)? Z_FLAG: 0) | \
			((btData == 128)? P_V_FLAG: 0) | \
			(btData & 0x80) | \
			(((btData & 0x0F) == 0)? H_FLAG: 0)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_DEC_8(btData) { \
	btData--; \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_DEC_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_DEC_8(btData) { \
	btData--; \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btData == 0)? Z_FLAG: 0) | \
			((btData == 127)? P_V_FLAG: 0) | \
			(btData & 0x80) | \
			N_FLAG | \
			(((btData & 0x0F) == 15)? H_FLAG: 0)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_ADD_8(btDst, btSrc) { \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_ADD_8[0 * 256 * 256 + btDst * 256 + btSrc]); \
	btDst = uint8_t(btDst+btSrc); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_ADD_8(btDst, btSrc) { \
	int nResult = int(btDst)+int(btSrc); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((nResult > 255)? C_FLAG: 0) | \
			((uint8_t(nResult) == 0)? Z_FLAG: 0) | \
			(((((nResult & ~btDst & ~btSrc) | \
				(~nResult & btDst & btSrc)) & 0x80) != 0)? P_V_FLAG: 0) | \
			(nResult & 0x80) | \
			(((btDst & 0x0F)+(btSrc & 0x0F) > 15)? H_FLAG: 0)); \
	btDst = uint8_t(nResult); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_ADC_8(btDst, btSrc) { \
	int nCarry = M_MaskRegF(C_FLAG); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_ADD_8[nCarry * 256 * 256 + btDst * 256 + btSrc]); \
	btDst = uint8_t(btDst+btSrc+nCarry); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_ADC_8(btDst, btSrc) { \
	int nCarry = M_MaskRegF(C_FLAG); \
	int nSrc = int(btSrc)+nCarry; \
	int nResult = int(btDst)+nSrc; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((nResult > 255)? C_FLAG: 0) | \
			((uint8_t(nResult) == 0)? Z_FLAG: 0) | \
			(((((nResult & ~btDst & ~nSrc) | \
				(~nResult & btDst & nSrc)) & 0x80) != 0)? P_V_FLAG: 0) | \
			(nResult & 0x80) | \
			(((btDst & 0x0F)+(btSrc & 0x0F)+nCarry > 15)? H_FLAG: 0)); \
	btDst = uint8_t(nResult); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_SUB_8(btDst, btSrc) { \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_SUB_8[0 * 256 * 256 + btDst * 256 + btSrc]); \
	btDst = uint8_t(btDst-btSrc); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_SUB_8(btDst, btSrc) { \
	int nResult = int(btDst)-int(btSrc); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((nResult < 0)? C_FLAG: 0) | \
			((uint8_t(nResult) == 0)? Z_FLAG: 0) | \
			(((((nResult & ~btDst & btSrc) | \
				(~nResult & btDst & ~btSrc)) & 0x80) != 0)? P_V_FLAG: 0) | \
			(nResult & 0x80) | \
			N_FLAG | \
			(((btDst & 0x0F) < (btSrc & 0x0F))? H_FLAG: 0)); \
	btDst = uint8_t(nResult); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_SBC_8(btDst, btSrc) { \
	int nCarry = M_MaskRegF(C_FLAG); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_SUB_8[nCarry * 256 * 256 + btDst * 256 + btSrc]); \
	btDst = uint8_t(btDst-btSrc-nCarry); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_SBC_8(btDst, btSrc) { \
	int nCarry = M_MaskRegF(C_FLAG); \
	int nSrc = int(btSrc)+nCarry; \
	int nResult = int(btDst)-nSrc; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((nResult < 0)? C_FLAG: 0) | \
			((uint8_t(nResult) == 0)? Z_FLAG: 0) | \
			(((((nResult & ~btDst & nSrc) | \
				(~nResult & btDst & ~nSrc)) & 0x80) != 0)? P_V_FLAG: 0) | \
			(nResult & 0x80) | \
			N_FLAG | \
			(((btDst & 0x0F) < (btSrc & 0x0F)+nCarry)? H_FLAG: 0)); \
	btDst = uint8_t(nResult); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_AND_8(btDst, btSrc) { \
	btDst &= btSrc; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_LOGICAL_8[btDst] | \
			H_FLAG); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_AND_8(btDst, btSrc) { \
	btDst &= btSrc; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btDst == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btDst] | \
			(btDst & 0x80) | \
			H_FLAG); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_OR_8(btDst, btSrc) { \
	btDst |= btSrc; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_LOGICAL_8[btDst]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_OR_8(btDst, btSrc) { \
	btDst |= btSrc; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btDst == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btDst] | \
			(btDst & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_XOR_8(btDst, btSrc) { \
	btDst ^= btSrc; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_LOGICAL_8[btDst]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_XOR_8(btDst, btSrc) { \
	btDst ^= btSrc; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btDst == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btDst] | \
			(btDst & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_CP_8(btDst, btSrc) { \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_SUB_8[0 * 256 * 256 + btDst * 256 + btSrc]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_CP_8(btDst, btSrc) { \
	uint8_t btDst2 = btDst; \
	M_Calc_SUB_8(btDst2, btSrc); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

// rotate/shift

#define M_Calc_RLCA(btData) { \
	btData = uint8_t((btData << 1) | (btData >> 7)); \
	M_UpdateRegF( \
		C_FLAG | N_FLAG | H_FLAG, \
		btData & 0x01); \
}

#define M_Calc_RLA(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData << 1) | M_MaskRegF(C_FLAG)); \
	M_UpdateRegF( \
		C_FLAG | N_FLAG | H_FLAG, \
		btOrg >> 7); \
}

#define M_Calc_RRCA(btData) { \
	btData = uint8_t((btData >> 1) | (btData << 7)); \
	M_UpdateRegF( \
		C_FLAG | N_FLAG | H_FLAG, \
		btData >> 7); \
}

#define M_Calc_RRA(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData >> 1) | (M_MaskRegF(C_FLAG) << 7)); \
	M_UpdateRegF( \
		C_FLAG | N_FLAG | H_FLAG, \
		btOrg & 0x01); \
}

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_RLC(btData) { \
	btData = uint8_t((btData << 1) | (btData >> 7)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btData & 0x01) | \
			CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_RLC(btData) { \
	btData = uint8_t((btData << 1) | (btData >> 7)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btData & 0x01) | \
			((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_RL(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData << 1) | M_MaskRegF(C_FLAG)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg >> 7) | \
			CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_RL(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData << 1) | M_MaskRegF(C_FLAG)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg >> 7) | \
			((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_RRC(btData) { \
	btData = uint8_t((btData >> 1) | (btData << 7)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btData >> 7) | \
			CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_RRC(btData) { \
	btData = uint8_t((btData >> 1) | (btData << 7)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btData >> 7) | \
			((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_RR(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData >> 1) | (M_MaskRegF(C_FLAG) << 7)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg & 0x01) | \
			CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_RR(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData >> 1) | (M_MaskRegF(C_FLAG) << 7)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg & 0x01) | \
		((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_SLA(btData) { \
	uint8_t btOrg = btData; \
	btData <<= 1; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg >> 7) | \
			CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_SLA(btData) { \
	uint8_t btOrg = btData; \
	btData <<= 1; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg >> 7) | \
			((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_SRA(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData >> 1) | (btData & 0x80)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg & 0x01) | \
			CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_SRA(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData >> 1) | (btData & 0x80)); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg & 0x01) | \
			((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_SLL(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData << 1) | 0x01); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg >> 7) | \
			CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_SLL(btData) { \
	uint8_t btOrg = btData; \
	btData = uint8_t((btData << 1) | 0x01); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg >> 7) | \
			((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_SRL(btData) { \
	uint8_t btOrg = btData; \
	btData >>= 1; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg & 0x01) | \
			CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_SRL(btData) { \
	uint8_t btOrg = btData; \
	btData >>= 1; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		(btOrg & 0x01) | \
		((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_RLD(btData1, btData2) { \
	uint8_t btOrg1 = btData1; \
	btData1 = uint8_t((btData1 & 0xF0) | (btData2 >> 4)); \
	btData2 = uint8_t((btOrg1 & 0x0F) | (btData2 << 4)); \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_LOGICAL_8[btData1]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_RLD(btData1, btData2) { \
	uint8_t btOrg1 = btData1; \
	btData1 = uint8_t((btData1 & 0xF0) | (btData2 >> 4)); \
	btData2 = uint8_t((btOrg1 & 0x0F) | (btData2 << 4)); \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btData1 == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData1] | \
			(btData1 & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_RRD(btData1, btData2) { \
	uint8_t btOrg1 = btData1; \
	btData1 = uint8_t((btData1 & 0xF0) | (btData2 & 0x0F)); \
	btData2 = uint8_t((btOrg1 << 4) | (btData2 >> 4)); \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_LOGICAL_8[btData1]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_RRD(btData1, btData2) { \
	uint8_t btOrg1 = btData1; \
	btData1 = uint8_t((btData1 & 0xF0) | (btData2 & 0x0F)); \
	btData2 = uint8_t((btOrg1 << 4) | (btData2 >> 4)); \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btData1 == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData1] | \
			(btData1 & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

// bit operate/test

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_BIT_b(btB, btData) { \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_BIT_b[btB * 256 + btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
// undefinition specification:P_V_FLAG
#define M_Calc_BIT_b(btB, btData) { \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		H_FLAG | \
			(((btData & (1 << btB)) == 0)? (Z_FLAG | P_V_FLAG): 0) | \
			(((btB == 7) && ((btData & 0x80) != 0))? S_FLAG: 0)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#define M_Calc_SET_b(btB, btData) { \
	btData |= uint8_t(1 << btB); \
}

#define M_Calc_RES_b(btB, btData) { \
	btData &= uint8_t(~(1 << btB)); \
}

// 16bit calculate

#define M_Calc_INC_16(wData) { \
	wData++; \
}

#define M_Calc_DEC_16(wData) { \
	wData--; \
}

#define M_Calc_ADD_16(wDst, wSrc) { \
	int32_t nResult = int32_t(wDst)+int32_t(wSrc); \
	M_UpdateRegF( \
		C_FLAG | N_FLAG | H_FLAG, \
		((nResult > 65535)? C_FLAG: 0) | \
			(((wDst & 0x0FFF)+(wSrc & 0x0FFF) > 4095)? H_FLAG: 0)); \
	wDst = uint16_t(nResult); \
}

#define M_Calc_ADC_16(wDst, wSrc) { \
	int nCarry = M_MaskRegF(C_FLAG); \
	int32_t nResult = int32_t(wDst)+int32_t(wSrc)+nCarry, \
		nResult2 = int32_t(int16_t(wDst))+int32_t(int16_t(wSrc))+nCarry; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((nResult > 65535)? C_FLAG: 0) | \
			((uint16_t(nResult) == 0)? Z_FLAG: 0) | \
			(((nResult2 > 32767) || (nResult2 < -32768))? P_V_FLAG: 0) | \
			((nResult & 0x8000) >> 8) | \
			(((wDst & 0x0FFF)+(wSrc & 0x0FFF)+nCarry > 4095)? H_FLAG: 0)); \
	wDst = uint16_t(nResult); \
}

#define M_Calc_SBC_16(wDst, wSrc) { \
	int nCarry = M_MaskRegF(C_FLAG); \
	int32_t nResult = int32_t(wDst)-int32_t(wSrc)-nCarry, \
		nResult2 = int32_t(int16_t(wDst))-int32_t(int16_t(wSrc))-nCarry; \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((nResult < 0)? C_FLAG: 0) | \
			((uint16_t(nResult) == 0)? Z_FLAG: 0) | \
			(((nResult2 > 32767) || (nResult2 < -32768))? P_V_FLAG: 0) | \
			((nResult & 0x8000) >> 8) | \
			N_FLAG | \
			(((wDst & 0x0FFF) < (wSrc & 0x0FFF)+nCarry)? H_FLAG: 0)); \
	wDst = uint16_t(nResult); \
}

// other calculate

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_DAA(btData) { \
	int nFlags = M_MaskRegF(C_FLAG | N_FLAG) | \
		(M_MaskRegF(H_FLAG) >> 2); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | H_FLAG, \
		CZ80Data::m_abtFlags_DAA[nFlags * 256 + btData]); \
	btData = CZ80Data::m_abtResult_DAA[nFlags * 256 + btData]; \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_DAA(btData) { \
	int nResult = btData, nCarry = 0, nHalf = 0; \
	if (!M_TestRegF(N_FLAG)) { \
		if (((nResult & 0x0F) > 0x09) || M_TestRegF(H_FLAG)) { \
			if ((nResult & 0x0F) > 0x09) { \
				nHalf = H_FLAG; \
			} \
			nResult += 0x06; \
		} \
		if ((nResult > 0x9F) || M_TestRegF(C_FLAG)) { \
			nCarry = C_FLAG; \
			nResult += 0x60; \
		} \
	} else { \
		if ((nResult > 0x99) || M_TestRegF(C_FLAG)) { \
			nCarry = C_FLAG; \
		} \
		if (((nResult & 0x0F) > 0x09) || M_TestRegF(H_FLAG)) { \
			if ((nResult & 0x0F) < 0x06) { \
				nHalf = H_FLAG; \
			} \
			nResult -= 0x06; \
		} \
		if ((nResult > 0x9F) || M_TestRegF(C_FLAG)) { \
			nResult -= 0x60; \
		} \
	} \
	btData = uint8_t(nResult); \
	M_UpdateRegF( \
		C_FLAG | Z_FLAG | P_V_FLAG | S_FLAG | H_FLAG, \
		nCarry | \
			((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80) | \
			nHalf); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#define M_Calc_CPL(btData) { \
	btData = uint8_t(~btData); \
	M_SetRegF(N_FLAG | H_FLAG); \
}

#define M_Calc_NEG(btData) { \
	uint8_t btTmp = 0; \
	M_Calc_SUB_8(btTmp, btData); \
	btData = btTmp; \
}

#define M_Calc_CCF() { \
	M_UpdateRegF( \
		C_FLAG | N_FLAG, \
		M_MaskRegF(C_FLAG) ^ C_FLAG); \
}

#define M_Calc_SCF() { \
	M_UpdateRegF( \
		C_FLAG | N_FLAG | H_FLAG, \
		C_FLAG); \
}

// others

#define M_Calc_LD_A_IR(btDst, btSrc) { \
	btDst = btSrc; \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btDst == 0)? Z_FLAG: 0) | \
			((M_IsEnableInterrupt() || M_IsEnableInterrupt2())? \
				P_V_FLAG: 0) | \
			(btDst & 0x80)); \
}

#ifdef Z80CFG_USE_FLAGTBL
#define M_Calc_IN_r_QC(btData) { \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG, \
		CZ80Data::m_abtFlags_LOGICAL_8[btData]); \
}
#else // Z80CFG_NOUSE_FLAGTBL
#define M_Calc_IN_r_QC(btData) { \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG, \
		((btData == 0)? Z_FLAG: 0) | \
			CZ80Data::m_abtParityTable[btData] | \
			(btData & 0x80)); \
}
#endif // Z80CFG_USE/NOUSE_FLAGTBL

#define M_Calc_LDI_LDD(wCounter) { \
	M_UpdateRegF( \
		P_V_FLAG | N_FLAG | H_FLAG, \
		(wCounter != 0)? P_V_FLAG: 0); \
}

#define M_Calc_CPI_CPD(wCounter, btDst, btSrc) { \
	uint8_t btResult = uint8_t(btDst-btSrc); \
	M_UpdateRegF( \
		Z_FLAG | P_V_FLAG | S_FLAG | N_FLAG | H_FLAG, \
		((btResult == 0)? Z_FLAG: 0) | \
			((wCounter != 0)? P_V_FLAG: 0) | \
			(btResult & 0x80) | \
			N_FLAG | \
			(((btDst & 0x0F) < (btSrc & 0x0F))? H_FLAG: 0)); \
}

#define M_Calc_INI_IND_OUTI_OUTD(btCounter) { \
	M_UpdateRegF( \
		Z_FLAG | N_FLAG, \
		((btCounter == 0)? Z_FLAG: 0) | \
			N_FLAG); \
}

////////////////////////////////////////////////////////////
// differentiation OP code process

// 8bit load

#define M_Exec_LD_r_r2(reg, reg2) { \
	reg.m_bt = reg2.m_bt; \
	M_AddExecClock(CLOCK_LD_r_r2); \
}

#define M_Exec_LD_r_n(reg, btN) { \
	reg.m_bt = btN; \
	M_AddExecClock(CLOCK_LD_r_n); \
}

#define M_Exec_LD_A_Qss(regp) { \
	M_RegA().m_bt = M_ReadMemory(regp.m_w); \
	M_AddExecClock(CLOCK_LD_A_Qss); \
}

#define M_Exec_LD_Qss_A(regp) { \
	M_WriteMemory(regp.m_w, M_RegA().m_bt); \
	M_AddExecClock(CLOCK_LD_Qss_A); \
}

#define M_Exec_LD_A_Qnn(wNN) { \
	M_RegA().m_bt = M_ReadMemory(wNN); \
	M_AddExecClock(CLOCK_LD_A_Qnn); \
}

#define M_Exec_LD_Qnn_A(wNN) { \
	M_WriteMemory(wNN, M_RegA().m_bt); \
	M_AddExecClock(CLOCK_LD_Qnn_A); \
}

#define M_Exec_LD_r_QHL(reg) { \
	reg.m_bt = M_ReadMemory(M_RegHL().m_w); \
	M_AddExecClock(CLOCK_LD_r_QHL); \
}

#define M_Exec_LD_QHL_r(reg) { \
	M_WriteMemory(M_RegHL().m_w, reg.m_bt); \
	M_AddExecClock(CLOCK_LD_QHL_r); \
}

#define M_Exec_LD_QHL_n(btN) { \
	M_WriteMemory(M_RegHL().m_w, btN); \
	M_AddExecClock(CLOCK_LD_QHL_n); \
}

#define M_Exec_LD_r_QIXd(reg, btD) { \
	reg.m_bt = M_ReadMemory(M_GetRegIXd(btD)); \
	M_AddExecClock(CLOCK_LD_r_QIXd); \
}

#define M_Exec_LD_QIXd_r(btD, reg) { \
	M_WriteMemory(M_GetRegIXd(btD), reg.m_bt); \
	M_AddExecClock(CLOCK_LD_QIXd_r); \
}

#define M_Exec_LD_QIXd_n(btD, btN) { \
	M_WriteMemory(M_GetRegIXd(btD), btN); \
	M_AddExecClock(CLOCK_LD_QIXd_n); \
}

#define M_Exec_LD_r_QIYd(reg, btD) { \
	reg.m_bt = M_ReadMemory(M_GetRegIYd(btD)); \
	M_AddExecClock(CLOCK_LD_r_QIYd); \
}

#define M_Exec_LD_QIYd_r(btD, reg) { \
	M_WriteMemory(M_GetRegIYd(btD), reg.m_bt); \
	M_AddExecClock(CLOCK_LD_QIYd_r); \
}

#define M_Exec_LD_QIYd_n(btD, btN) { \
	M_WriteMemory(M_GetRegIYd(btD), btN); \
	M_AddExecClock(CLOCK_LD_QIYd_n); \
}

#define M_Exec_LD_A_I() { \
	M_Calc_LD_A_IR(M_RegA().m_bt, M_GetRegI()); \
	M_AddExecClock(CLOCK_LD_A_I); \
}

#define M_Exec_LD_I_A() { \
	M_SetRegI(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_LD_I_A); \
}

#define M_Exec_LD_A_R() { \
	M_Calc_LD_A_IR(M_RegA().m_bt, M_GetRegR()); \
	M_AddExecClock(CLOCK_LD_A_R); \
}

#define M_Exec_LD_R_A() { \
	M_SetRegR(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_LD_R_A); \
}

// 16bit load

#define M_Exec_LD_ss_nn(regp, wNN) { \
	regp.m_w = wNN; \
	M_AddExecClock(CLOCK_LD_ss_nn); \
}

#define M_Exec_LD_ss_Qnn(regp, wNN) { \
	regp.m_w = M_ReadMemoryW(wNN); \
	M_AddExecClock(CLOCK_LD_ss_Qnn); \
}

#define M_Exec_LD_Qnn_ss(wNN, regp) { \
	M_WriteMemoryW(wNN, regp.m_w); \
	M_AddExecClock(CLOCK_LD_Qnn_ss); \
}

#define M_Exec_LD_HL_Qnn(wNN) { \
	M_RegHL().m_w = M_ReadMemoryW(wNN); \
	M_AddExecClock(CLOCK_LD_HL_Qnn); \
}

#define M_Exec_LD_Qnn_HL(wNN) { \
	M_WriteMemoryW(wNN, M_RegHL().m_w); \
	M_AddExecClock(CLOCK_LD_Qnn_HL); \
}

#define M_Exec_LD_IX_nn(wNN) { \
	M_RegIX().m_w = wNN; \
	M_AddExecClock(CLOCK_LD_IX_nn); \
}

#define M_Exec_LD_IX_Qnn(wNN) { \
	M_RegIX().m_w = M_ReadMemoryW(wNN); \
	M_AddExecClock(CLOCK_LD_IX_Qnn); \
}

#define M_Exec_LD_Qnn_IX(wNN) { \
	M_WriteMemoryW(wNN, M_RegIX().m_w); \
	M_AddExecClock(CLOCK_LD_Qnn_IX); \
}

#define M_Exec_LD_IY_nn(wNN) { \
	M_RegIY().m_w = wNN; \
	M_AddExecClock(CLOCK_LD_IY_nn); \
}

#define M_Exec_LD_IY_Qnn(wNN) { \
	M_RegIY().m_w = M_ReadMemoryW(wNN); \
	M_AddExecClock(CLOCK_LD_IY_Qnn); \
}

#define M_Exec_LD_Qnn_IY(wNN) { \
	M_WriteMemoryW(wNN, M_RegIY().m_w); \
	M_AddExecClock(CLOCK_LD_Qnn_IY); \
}

#define M_Exec_LD_SP_HL() { \
	M_RegSP().m_w = M_RegHL().m_w; \
	M_AddExecClock(CLOCK_LD_SP_HL); \
}

#define M_Exec_LD_SP_IX() { \
	M_RegSP().m_w = M_RegIX().m_w; \
	M_AddExecClock(CLOCK_LD_SP_IX); \
}

#define M_Exec_LD_SP_IY() { \
	M_RegSP().m_w = M_RegIY().m_w; \
	M_AddExecClock(CLOCK_LD_SP_IY); \
}

#define M_Exec_PUSH_ss(regp) { \
	M_PushReg(regp); \
	M_AddExecClock(CLOCK_PUSH_ss); \
}

#define M_Exec_PUSH_IX() { \
	M_PushReg(M_RegIX()); \
	M_AddExecClock(CLOCK_PUSH_IX); \
}

#define M_Exec_PUSH_IY() { \
	M_PushReg(M_RegIY()); \
	M_AddExecClock(CLOCK_PUSH_IY); \
}

#define M_Exec_POP_ss(regp) { \
	M_PopReg(regp); \
	M_AddExecClock(CLOCK_POP_ss); \
}

#define M_Exec_POP_IX() { \
	M_PopReg(M_RegIX()); \
	M_AddExecClock(CLOCK_POP_IX); \
}

#define M_Exec_POP_IY() { \
	M_PopReg(M_RegIY()); \
	M_AddExecClock(CLOCK_POP_IY); \
}

// exchange

#define M_Exec_EX_AF_AF2() { \
	M_SwapReg(M_RegAF(), M_RegAF2()); \
	M_AddExecClock(CLOCK_EX_AF_AF2); \
}

#define M_Exec_EX_DE_HL() { \
	M_SwapReg(M_RegDE(), M_RegHL()); \
	M_AddExecClock(CLOCK_EX_DE_HL); \
}

#define M_Exec_EXX() { \
	M_SwapReg(M_RegBC(), M_RegBC2()); \
	M_SwapReg(M_RegDE(), M_RegDE2()); \
	M_SwapReg(M_RegHL(), M_RegHL2()); \
	M_AddExecClock(CLOCK_EXX); \
}

#define M_Exec_EX_QSP_HL() { \
	uint16_t wTmp; \
	wTmp = M_ReadMemoryW(M_RegSP().m_w); \
	M_WriteMemoryW(M_RegSP().m_w, M_RegHL().m_w); \
	M_RegHL().m_w = wTmp; \
	M_AddExecClock(CLOCK_EX_QSP_HL); \
}

#define M_Exec_EX_QSP_IX() { \
	uint16_t wTmp; \
	wTmp = M_ReadMemoryW(M_RegSP().m_w); \
	M_WriteMemoryW(M_RegSP().m_w, M_RegIX().m_w); \
	M_RegIX().m_w = wTmp; \
	M_AddExecClock(CLOCK_EX_QSP_IX); \
}

#define M_Exec_EX_QSP_IY() { \
	uint16_t wTmp; \
	wTmp = M_ReadMemoryW(M_RegSP().m_w); \
	M_WriteMemoryW(M_RegSP().m_w, M_RegIY().m_w); \
	M_RegIY().m_w = wTmp; \
	M_AddExecClock(CLOCK_EX_QSP_IY); \
}

// 8bit calculate

#define M_Exec_INC_r(reg) { \
	M_Calc_INC_8(reg.m_bt); \
	M_AddExecClock(CLOCK_INC_r); \
}

#define M_Exec_INC_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_INC_8(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_INC_QHL); \
}

#define M_Exec_INC_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_INC_8(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_INC_QIXd); \
}

#define M_Exec_INC_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_INC_8(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_INC_QIYd); \
}

#define M_Exec_DEC_r(reg) { \
	M_Calc_DEC_8(reg.m_bt); \
	M_AddExecClock(CLOCK_DEC_r); \
}

#define M_Exec_DEC_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_DEC_8(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_DEC_QHL); \
}

#define M_Exec_DEC_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_DEC_8(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_DEC_QIXd); \
}

#define M_Exec_DEC_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_DEC_8(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_DEC_QIYd); \
}

#define M_Exec_ADD_A_r(reg) { \
	M_Calc_ADD_8(M_RegA().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_ADD_A_r); \
}

#define M_Exec_ADD_A_n(btN) { \
	M_Calc_ADD_8(M_RegA().m_bt, btN); \
	M_AddExecClock(CLOCK_ADD_A_n); \
}

#define M_Exec_ADD_A_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_ADD_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_ADD_A_QHL); \
}

#define M_Exec_ADD_A_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_ADD_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_ADD_A_QIXd); \
}

#define M_Exec_ADD_A_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_ADD_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_ADD_A_QIYd); \
}

#define M_Exec_ADC_A_r(reg) { \
	M_Calc_ADC_8(M_RegA().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_ADC_A_r); \
}

#define M_Exec_ADC_A_n(btN) { \
	M_Calc_ADC_8(M_RegA().m_bt, btN); \
	M_AddExecClock(CLOCK_ADC_A_n); \
}

#define M_Exec_ADC_A_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_ADC_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_ADC_A_QHL); \
}

#define M_Exec_ADC_A_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_ADC_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_ADC_A_QIXd); \
}

#define M_Exec_ADC_A_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_ADC_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_ADC_A_QIYd); \
}

#define M_Exec_SUB_r(reg) { \
	M_Calc_SUB_8(M_RegA().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_SUB_r); \
}

#define M_Exec_SUB_n(btN) { \
	M_Calc_SUB_8(M_RegA().m_bt, btN); \
	M_AddExecClock(CLOCK_SUB_n); \
}

#define M_Exec_SUB_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_SUB_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_SUB_QHL); \
}

#define M_Exec_SUB_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SUB_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_SUB_QIXd); \
}

#define M_Exec_SUB_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SUB_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_SUB_QIYd); \
}

#define M_Exec_SBC_A_r(reg) { \
	M_Calc_SBC_8(M_RegA().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_SBC_A_r); \
}

#define M_Exec_SBC_A_n(btN) { \
	M_Calc_SBC_8(M_RegA().m_bt, btN); \
	M_AddExecClock(CLOCK_SBC_A_n); \
}

#define M_Exec_SBC_A_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_SBC_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_SBC_A_QHL); \
}

#define M_Exec_SBC_A_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SBC_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_SBC_A_QIXd); \
}

#define M_Exec_SBC_A_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SBC_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_SBC_A_QIYd); \
}

#define M_Exec_AND_r(reg) { \
	M_Calc_AND_8(M_RegA().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_AND_r); \
}

#define M_Exec_AND_n(btN) { \
	M_Calc_AND_8(M_RegA().m_bt, btN); \
	M_AddExecClock(CLOCK_AND_n); \
}

#define M_Exec_AND_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_AND_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_AND_QHL); \
}

#define M_Exec_AND_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_AND_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_AND_QIXd); \
}

#define M_Exec_AND_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_AND_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_AND_QIYd); \
}

#define M_Exec_OR_r(reg) { \
	M_Calc_OR_8(M_RegA().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_OR_r); \
}

#define M_Exec_OR_n(btN) { \
	M_Calc_OR_8(M_RegA().m_bt, btN); \
	M_AddExecClock(CLOCK_OR_n); \
}

#define M_Exec_OR_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_OR_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_OR_QHL); \
}

#define M_Exec_OR_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_OR_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_OR_QIXd); \
}

#define M_Exec_OR_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_OR_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_OR_QIYd); \
}

#define M_Exec_XOR_r(reg) { \
	M_Calc_XOR_8(M_RegA().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_XOR_r); \
}

#define M_Exec_XOR_n(btN) { \
	M_Calc_XOR_8(M_RegA().m_bt, btN); \
	M_AddExecClock(CLOCK_XOR_n); \
}

#define M_Exec_XOR_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_XOR_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_XOR_QHL); \
}

#define M_Exec_XOR_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_XOR_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_XOR_QIXd); \
}

#define M_Exec_XOR_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_XOR_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_XOR_QIYd); \
}

#define M_Exec_CP_r(reg) { \
	M_Calc_CP_8(M_RegA().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_CP_r); \
}

#define M_Exec_CP_n(btN) { \
	M_Calc_CP_8(M_RegA().m_bt, btN); \
	M_AddExecClock(CLOCK_CP_n); \
}

#define M_Exec_CP_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_CP_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_CP_QHL); \
}

#define M_Exec_CP_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_CP_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_CP_QIXd); \
}

#define M_Exec_CP_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_CP_8(M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_CP_QIYd); \
}

// rotate/shift

#define M_Exec_RLCA() { \
	M_Calc_RLCA(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_RLCA); \
}

#define M_Exec_RLC_r(reg) { \
	M_Calc_RLC(reg.m_bt); \
	M_AddExecClock(CLOCK_RLC_r); \
}

#define M_Exec_RLC_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_RLC(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_RLC_QHL); \
}

#define M_Exec_RLC_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RLC(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_RLC_QIXd); \
}

#define M_Exec_RLC_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RLC(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_RLC_QIYd); \
}

#define M_Exec_RLC_r_QIXd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RLC(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RLC_r_QIXd); \
}

#define M_Exec_RLC_r_QIYd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RLC(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RLC_r_QIYd); \
}

#define M_Exec_RLA() { \
	M_Calc_RLA(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_RLA); \
}

#define M_Exec_RL_r(reg) { \
	M_Calc_RL(reg.m_bt); \
	M_AddExecClock(CLOCK_RL_r); \
}

#define M_Exec_RL_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_RL(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_RL_QHL); \
}

#define M_Exec_RL_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RL(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_RL_QIXd); \
}

#define M_Exec_RL_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RL(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_RL_QIYd); \
}

#define M_Exec_RL_r_QIXd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RL(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RL_r_QIXd); \
}

#define M_Exec_RL_r_QIYd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RL(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RL_r_QIYd); \
}

#define M_Exec_RRCA() { \
	M_Calc_RRCA(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_RRCA); \
}

#define M_Exec_RRC_r(reg) { \
	M_Calc_RRC(reg.m_bt); \
	M_AddExecClock(CLOCK_RRC_r); \
}

#define M_Exec_RRC_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_RRC(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_RRC_QHL); \
}

#define M_Exec_RRC_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RRC(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_RRC_QIXd); \
}

#define M_Exec_RRC_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RRC(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_RRC_QIYd); \
}

#define M_Exec_RRC_r_QIXd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RRC(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RRC_r_QIXd); \
}

#define M_Exec_RRC_r_QIYd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RRC(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RRC_r_QIYd); \
}

#define M_Exec_RRA() { \
	M_Calc_RRA(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_RRA); \
}

#define M_Exec_RR_r(reg) { \
	M_Calc_RR(reg.m_bt); \
	M_AddExecClock(CLOCK_RR_r); \
}

#define M_Exec_RR_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_RR(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_RR_QHL); \
}

#define M_Exec_RR_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RR(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_RR_QIXd); \
}

#define M_Exec_RR_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RR(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_RR_QIYd); \
}

#define M_Exec_RR_r_QIXd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RR(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RR_r_QIXd); \
}

#define M_Exec_RR_r_QIYd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RR(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RR_r_QIYd); \
}

#define M_Exec_SLA_r(reg) { \
	M_Calc_SLA(reg.m_bt); \
	M_AddExecClock(CLOCK_SLA_r); \
}

#define M_Exec_SLA_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_SLA(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_SLA_QHL); \
}

#define M_Exec_SLA_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SLA(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_SLA_QIXd); \
}

#define M_Exec_SLA_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SLA(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_SLA_QIYd); \
}

#define M_Exec_SLA_r_QIXd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SLA(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SLA_r_QIXd); \
}

#define M_Exec_SLA_r_QIYd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SLA(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SLA_r_QIYd); \
}

#define M_Exec_SRA_r(reg) { \
	M_Calc_SRA(reg.m_bt); \
	M_AddExecClock(CLOCK_SRA_r); \
}

#define M_Exec_SRA_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_SRA(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_SRA_QHL); \
}

#define M_Exec_SRA_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SRA(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_SRA_QIXd); \
}

#define M_Exec_SRA_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SRA(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_SRA_QIYd); \
}

#define M_Exec_SRA_r_QIXd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SRA(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SRA_r_QIXd); \
}

#define M_Exec_SRA_r_QIYd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SRA(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SRA_r_QIYd); \
}

#define M_Exec_SLL_r(reg) { \
	M_Calc_SLL(reg.m_bt); \
	M_AddExecClock(CLOCK_SLL_r); \
}

#define M_Exec_SLL_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_SLL(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_SLL_QHL); \
}

#define M_Exec_SLL_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SLL(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_SLL_QIXd); \
}

#define M_Exec_SLL_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SLL(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_SLL_QIYd); \
}

#define M_Exec_SLL_r_QIXd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SLL(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SLL_r_QIXd); \
}

#define M_Exec_SLL_r_QIYd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SLL(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SLL_r_QIYd); \
}

#define M_Exec_SRL_r(reg) { \
	M_Calc_SRL(reg.m_bt); \
	M_AddExecClock(CLOCK_SRL_r); \
}

#define M_Exec_SRL_QHL() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_SRL(btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_SRL_QHL); \
}

#define M_Exec_SRL_QIXd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SRL(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_SRL_QIXd); \
}

#define M_Exec_SRL_QIYd(btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SRL(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_SRL_QIYd); \
}

#define M_Exec_SRL_r_QIXd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SRL(btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SRL_r_QIXd); \
}

#define M_Exec_SRL_r_QIYd(reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SRL(btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SRL_r_QIYd); \
}

#define M_Exec_RLD() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_RLD(M_RegA().m_bt, btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_RLD); \
}

#define M_Exec_RRD() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_RRD(M_RegA().m_bt, btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_RRD); \
}

// bit operate/test

#define M_Exec_BIT_b_r(btB, reg) { \
	M_Calc_BIT_b(btB, reg.m_bt); \
	M_AddExecClock(CLOCK_BIT_b_r); \
}

#define M_Exec_BIT_b_QHL(btB) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_BIT_b(btB, btData); \
	M_AddExecClock(CLOCK_BIT_b_QHL); \
}

#define M_Exec_BIT_b_QIXd(btB, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_BIT_b(btB, btData); \
	M_AddExecClock(CLOCK_BIT_b_QIXd); \
}

#define M_Exec_BIT_b_QIYd(btB, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_BIT_b(btB, btData); \
	M_AddExecClock(CLOCK_BIT_b_QIYd); \
}

#define M_Exec_SET_b_r(btB, reg) { \
	M_Calc_SET_b(btB, reg.m_bt); \
	M_AddExecClock(CLOCK_SET_b_r); \
}

#define M_Exec_SET_b_QHL(btB) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_SET_b(btB, btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_SET_b_QHL); \
}

#define M_Exec_SET_b_QIXd(btB, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SET_b(btB, btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_SET_b_QIXd); \
}

#define M_Exec_SET_b_QIYd(btB, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SET_b(btB, btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_SET_b_QIYd); \
}

#define M_Exec_SET_b_r_QIXd(btB, reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_SET_b(btB, btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SET_b_r_QIXd); \
}

#define M_Exec_SET_b_r_QIYd(btB, reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_SET_b(btB, btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_SET_b_r_QIYd); \
}

#define M_Exec_RES_b_r(btB, reg) { \
	M_Calc_RES_b(btB, reg.m_bt); \
	M_AddExecClock(CLOCK_RES_b_r); \
}

#define M_Exec_RES_b_QHL(btB) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_Calc_RES_b(btB, btData); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_AddExecClock(CLOCK_RES_b_QHL); \
}

#define M_Exec_RES_b_QIXd(btB, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RES_b(btB, btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	M_AddExecClock(CLOCK_RES_b_QIXd); \
}

#define M_Exec_RES_b_QIYd(btB, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RES_b(btB, btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	M_AddExecClock(CLOCK_RES_b_QIYd); \
}

#define M_Exec_RES_b_r_QIXd(btB, reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIXd(btD)); \
	M_Calc_RES_b(btB, btData); \
	M_WriteMemory(M_GetRegIXd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RES_b_r_QIXd); \
}

#define M_Exec_RES_b_r_QIYd(btB, reg, btD) { \
	uint8_t btData; \
	btData = M_ReadMemory(M_GetRegIYd(btD)); \
	M_Calc_RES_b(btB, btData); \
	M_WriteMemory(M_GetRegIYd(btD), btData); \
	reg.m_bt = btData; \
	M_AddExecClock(CLOCK_RES_b_r_QIYd); \
}

// 16bit calculate

#define M_Exec_INC_ss(regp) { \
	M_Calc_INC_16(regp.m_w); \
	M_AddExecClock(CLOCK_INC_ss); \
}

#define M_Exec_INC_IX() { \
	M_Calc_INC_16(M_RegIX().m_w); \
	M_AddExecClock(CLOCK_INC_IX); \
}

#define M_Exec_INC_IY() { \
	M_Calc_INC_16(M_RegIY().m_w); \
	M_AddExecClock(CLOCK_INC_IY); \
}

#define M_Exec_DEC_ss(regp) { \
	M_Calc_DEC_16(regp.m_w); \
	M_AddExecClock(CLOCK_DEC_ss); \
}

#define M_Exec_DEC_IX() { \
	M_Calc_DEC_16(M_RegIX().m_w); \
	M_AddExecClock(CLOCK_DEC_IX); \
}

#define M_Exec_DEC_IY() { \
	M_Calc_DEC_16(M_RegIY().m_w); \
	M_AddExecClock(CLOCK_DEC_IY); \
}

#define M_Exec_ADD_HL_ss(regp) { \
	M_Calc_ADD_16(M_RegHL().m_w, regp.m_w); \
	M_AddExecClock(CLOCK_ADD_HL_ss); \
}

#define M_Exec_ADD_IX_ss(regp) { \
	M_Calc_ADD_16(M_RegIX().m_w, regp.m_w); \
	M_AddExecClock(CLOCK_ADD_IX_ss); \
}

#define M_Exec_ADD_IY_ss(regp) { \
	M_Calc_ADD_16(M_RegIY().m_w, regp.m_w); \
	M_AddExecClock(CLOCK_ADD_IY_ss); \
}

#define M_Exec_ADC_HL_ss(regp) { \
	M_Calc_ADC_16(M_RegHL().m_w, regp.m_w); \
	M_AddExecClock(CLOCK_ADC_HL_ss); \
}

#define M_Exec_SBC_HL_ss(regp) { \
	M_Calc_SBC_16(M_RegHL().m_w, regp.m_w); \
	M_AddExecClock(CLOCK_SBC_HL_ss); \
}

// other calculate/CPU control

#define M_Exec_DAA() { \
	M_Calc_DAA(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_DAA); \
}

#define M_Exec_CPL() { \
	M_Calc_CPL(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_CPL); \
}

#define M_Exec_NEG() { \
	M_Calc_NEG(M_RegA().m_bt); \
	M_AddExecClock(CLOCK_NEG); \
}

#define M_Exec_CCF() { \
	M_Calc_CCF(); \
	M_AddExecClock(CLOCK_CCF); \
}

#define M_Exec_SCF() { \
	M_Calc_SCF(); \
	M_AddExecClock(CLOCK_SCF); \
}

#define M_Exec_DI() { \
	M_SetEnableInterrupt(false); \
	M_SetEnableInterrupt2(false); \
	M_SetEnableInterruptReserve(false); \
	M_AddExecClock(CLOCK_DI); \
}

#define M_Exec_EI() { \
	M_SetEnableInterrupt2(true); \
	M_SetEnableInterruptReserve(true); \
	M_AddExecClock(CLOCK_EI); \
}

#define M_Exec_NOP() { \
	M_AddExecClock(CLOCK_NOP); \
}

#define M_Exec_HALT() { \
	M_SetHalting(true); \
	M_AddRegPC(uint8_t(-1)); \
	M_ProcessHALT(); \
	M_AddExecClock(CLOCK_HALT); \
}

#define M_Exec_IM0() { \
	M_SetInterruptMode(0); \
	M_AddExecClock(CLOCK_IM0); \
}

#define M_Exec_IM1() { \
	M_SetInterruptMode(1); \
	M_AddExecClock(CLOCK_IM1); \
}

#define M_Exec_IM2() { \
	M_SetInterruptMode(2); \
	M_AddExecClock(CLOCK_IM2); \
}

#define M_Exec_IMx() { \
	M_SetInterruptMode(-1); \
	M_AddExecClock(CLOCK_IMx); \
}

// branch

#define M_Exec_JP_nn(wNN) { \
	M_RegPC().m_w = wNN; \
	M_AddExecClock(CLOCK_JP_nn); \
}

#define M_Exec_JP_QHL() { \
	M_RegPC().m_w= M_RegHL().m_w; \
	M_AddExecClock(CLOCK_JP_QHL); \
}

#define M_Exec_JP_QIX() { \
	M_RegPC().m_w = M_RegIX().m_w; \
	M_AddExecClock(CLOCK_JP_QIX); \
}

#define M_Exec_JP_QIY() { \
	M_RegPC().m_w = M_RegIY().m_w; \
	M_AddExecClock(CLOCK_JP_QIY); \
}

#define M_Exec_JP_cc_nn(flgCC, wNN) { \
	if (flgCC) { \
		M_RegPC().m_w = wNN; \
	} \
	M_AddExecClock(CLOCK_JP_cc_nn); \
}

#define M_Exec_JR_e(btE) { \
	M_AddRegPC(btE); \
	M_AddExecClock(CLOCK_JR_e); \
}

#define M_Exec_JR_cc_e(flgCC, btE) { \
	M_AddExecClock(CLOCK_JR_cc_e_1); \
	if (flgCC) { \
		M_AddRegPC(btE); \
		M_AddExecClock(CLOCK_JR_cc_e_2-CLOCK_JR_cc_e_1); \
	} \
}

#define M_Exec_DJNZ_e(btE) { \
	M_RegB().m_bt--; \
	M_AddExecClock(CLOCK_DJNZ_e_1); \
	if (M_RegB().m_bt != 0) { \
		M_AddRegPC(btE); \
		M_AddExecClock(CLOCK_DJNZ_e_2-CLOCK_DJNZ_e_1); \
	} \
}

#define M_Exec_CALL_nn(wNN) { \
	M_PushReg(M_RegPC()); \
	M_RegPC().m_w = wNN; \
	M_AddExecClock(CLOCK_CALL_nn); \
}

#define M_Exec_CALL_cc_nn(flgCC, wNN) { \
	M_AddExecClock(CLOCK_CALL_cc_nn_1); \
	if (flgCC) { \
		M_AddExecClock(CLOCK_CALL_cc_nn_2-CLOCK_CALL_cc_nn_1); \
		M_PushReg(M_RegPC()); \
		M_RegPC().m_w = wNN; \
	} \
}

#define M_Exec_RET() { \
	M_PopReg(M_RegPC()); \
	M_AddExecClock(CLOCK_RET); \
}

#define M_Exec_RET_cc(flgCC) { \
	M_AddExecClock(CLOCK_RET_cc_1); \
	if (flgCC) { \
		M_AddExecClock(CLOCK_RET_cc_2-CLOCK_RET_cc_1); \
		M_PopReg(M_RegPC()); \
	} \
}

#define M_Exec_RST_n(btN) { \
	M_PushReg(M_RegPC()); \
	M_RegPC().m_w = uint16_t(btN); \
	M_AddExecClock(CLOCK_RST_n); \
}

#define M_Exec_RETI() { \
	M_PopReg(M_RegPC()); \
	M_FinishInterrupt(); \
	M_AddExecClock(CLOCK_RETI); \
}

#define M_Exec_RETN() { \
	M_SetEnableInterrupt(M_IsEnableInterrupt2()); \
	M_SetEnableInterruptReserve(M_IsEnableInterrupt2()); \
	M_PopReg(M_RegPC()); \
	M_FinishNMInterrupt(); \
	M_AddExecClock(CLOCK_RETN); \
}

// input/output

#define M_Exec_IN_A_Qn(btN) { \
	M_RegA().m_bt = M_ReadIO(btN); \
	M_AddExecClock(CLOCK_IN_A_Qn); \
}

#ifdef Z80CFG_IOADDR_WIDTH_8
#define M_Exec_IN_r_QC(reg) { \
	reg.m_bt = M_ReadIO(M_RegC().m_bt); \
	M_Calc_IN_r_QC(reg.m_bt); \
	M_AddExecClock(CLOCK_IN_r_QC); \
}
#else // Z80CFG_IOADDR_WIDTH_16
#define M_Exec_IN_r_QC(reg) { \
	reg.m_bt = M_ReadIO(M_RegBC().m_w); \
	M_Calc_IN_r_QC(reg.m_bt); \
	M_AddExecClock(CLOCK_IN_r_QC); \
}
#endif // Z80CFG_IOADDR_WIDTH

#ifdef Z80CFG_IOADDR_WIDTH_8
#define M_Exec_IN_F_QC() { \
	M_RegF().m_bt = M_ReadIO(M_RegC().m_bt); \
	M_Calc_IN_r_QC(M_RegF().m_bt); \
	M_AddExecClock(CLOCK_IN_F_QC); \
}
#else // Z80CFG_IOADDR_WIDTH_16
#define M_Exec_IN_F_QC() { \
	M_RegF().m_bt = M_ReadIO(M_RegBC().m_w); \
	M_Calc_IN_r_QC(M_RegF().m_bt); \
	M_AddExecClock(CLOCK_IN_F_QC); \
}
#endif // Z80CFG_IOADDR_WIDTH

#define M_Exec_OUT_Qn_A(btN) { \
	M_WriteIO(btN, M_RegA().m_bt); \
	M_AddExecClock(CLOCK_OUT_Qn_A); \
}

#ifdef Z80CFG_IOADDR_WIDTH_8
#define M_Exec_OUT_QC_r(reg) { \
	M_WriteIO(M_RegC().m_bt, reg.m_bt); \
	M_AddExecClock(CLOCK_OUT_QC_r); \
}
#else // Z80CFG_IOADDR_WIDTH_16
#define M_Exec_OUT_QC_r(reg) { \
	M_WriteIO(M_RegBC().m_w, reg.m_bt); \
	M_AddExecClock(CLOCK_OUT_QC_r); \
}
#endif // Z80CFG_IOADDR_WIDTH

#ifdef Z80CFG_IOADDR_WIDTH_8
#define M_Exec_OUT_QC_0() { \
	M_WriteIO(M_RegC().m_bt, 0); \
	M_AddExecClock(CLOCK_OUT_QC_0); \
}
#else // Z80CFG_IOADDR_WIDTH_16
#define M_Exec_OUT_QC_0() { \
	M_WriteIO(M_RegBC().m_w, 0); \
	M_AddExecClock(CLOCK_OUT_QC_0); \
}
#endif // Z80CFG_IOADDR_WIDTH

// block

#define M_Exec_LDI() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_WriteMemory(M_RegDE().m_w, btData); \
	M_RegHL().m_w++; \
	M_RegDE().m_w++; \
	M_RegBC().m_w--; \
	M_Calc_LDI_LDD(M_RegBC().m_w); \
	M_AddExecClock(CLOCK_LDI); \
}

#define M_Exec_LDD() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_WriteMemory(M_RegDE().m_w, btData); \
	M_RegHL().m_w--; \
	M_RegDE().m_w--; \
	M_RegBC().m_w--; \
	M_Calc_LDI_LDD(M_RegBC().m_w); \
	M_AddExecClock(CLOCK_LDD); \
}

#define M_Exec_CPI() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_RegHL().m_w++; \
	M_RegBC().m_w--; \
	M_Calc_CPI_CPD(M_RegBC().m_w, M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_CPI); \
}

#define M_Exec_CPD() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_RegHL().m_w--; \
	M_RegBC().m_w--; \
	M_Calc_CPI_CPD(M_RegBC().m_w, M_RegA().m_bt, btData); \
	M_AddExecClock(CLOCK_CPD); \
}

#define M_Exec_INI() { \
	uint8_t btData; \
	btData = M_ReadIO(M_RegC().m_bt); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_RegHL().m_w++; \
	M_RegB().m_bt--; \
	M_Calc_INI_IND_OUTI_OUTD(M_RegB().m_bt); \
	M_AddExecClock(CLOCK_INI); \
}

#define M_Exec_IND() { \
	uint8_t btData; \
	btData = M_ReadIO(M_RegC().m_bt); \
	M_WriteMemory(M_RegHL().m_w, btData); \
	M_RegHL().m_w--; \
	M_RegB().m_bt--; \
	M_Calc_INI_IND_OUTI_OUTD(M_RegB().m_bt); \
	M_AddExecClock(CLOCK_IND); \
}

#define M_Exec_OUTI() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_WriteIO(M_RegC().m_bt, btData); \
	M_RegHL().m_w++; \
	M_RegB().m_bt--; \
	M_Calc_INI_IND_OUTI_OUTD(M_RegB().m_bt); \
	M_AddExecClock(CLOCK_OUTI); \
}

#define M_Exec_OUTD() { \
	uint8_t btData; \
	btData = M_ReadMemory(M_RegHL().m_w); \
	M_WriteIO(M_RegC().m_bt, btData); \
	M_RegHL().m_w--; \
	M_RegB().m_bt--; \
	M_Calc_INI_IND_OUTI_OUTD(M_RegB().m_bt); \
	M_AddExecClock(CLOCK_OUTD); \
}

#define M_Exec_LDIR() { \
	M_Exec_LDI(); \
	if (M_TestRegF(P_V_FLAG)) { \
		M_AddRegPC(uint8_t(-2)); \
		M_AddExecClock(CLOCK_LDIR); \
	} \
}

#define M_Exec_LDDR() { \
	M_Exec_LDD(); \
	if (M_TestRegF(P_V_FLAG)) { \
		M_AddRegPC(uint8_t(-2)); \
		M_AddExecClock(CLOCK_LDDR); \
	} \
}

#define M_Exec_CPIR() { \
	M_Exec_CPI(); \
	if (M_MaskRegF(Z_FLAG | P_V_FLAG) == P_V_FLAG) { \
		M_AddRegPC(uint8_t(-2)); \
		M_AddExecClock(CLOCK_CPIR); \
	} \
}

#define M_Exec_CPDR() { \
	M_Exec_CPD(); \
	if (M_MaskRegF(Z_FLAG | P_V_FLAG) == P_V_FLAG) { \
		M_AddRegPC(uint8_t(-2)); \
		M_AddExecClock(CLOCK_CPDR); \
	} \
}

#define M_Exec_INIR() { \
	M_Exec_INI(); \
	if (!M_TestRegF(Z_FLAG)) { \
		M_AddRegPC(uint8_t(-2)); \
		M_AddExecClock(CLOCK_INIR); \
	} \
}

#define M_Exec_INDR() { \
	M_Exec_IND(); \
	if (!M_TestRegF(Z_FLAG)) { \
		M_AddRegPC(uint8_t(-2)); \
		M_AddExecClock(CLOCK_INDR); \
	} \
}

#define M_Exec_OTIR() { \
	M_Exec_OUTI(); \
	if (!M_TestRegF(Z_FLAG)) { \
		M_AddRegPC(uint8_t(-2)); \
		M_AddExecClock(CLOCK_OTIR); \
	} \
}

#define M_Exec_OTDR() { \
	M_Exec_OUTD(); \
	if (!M_TestRegF(Z_FLAG)) { \
		M_AddRegPC(uint8_t(-2)); \
		M_AddExecClock(CLOCK_OTDR); \
	} \
}

#endif // Z80Executor2_DEFINED
