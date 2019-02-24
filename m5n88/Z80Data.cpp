////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "Z80Data.h"

////////////////////////////////////////////////////////////
// CZ80Data

////////////////////////////////////////////////////////////
// attribute

bool CZ80Data::m_bInitialized = false;

#ifdef Z80CFG_USE_FLAGTBL
//uint8_t CZ80Data::m_abtFlags_INC_8[256];
//uint8_t CZ80Data::m_abtFlags_DEC_8[256];
//uint8_t CZ80Data::m_abtFlags_LOGICAL_8[256];
//uint8_t CZ80Data::m_abtFlags_BIT_b[8][256];
//uint8_t CZ80Data::m_abtFlags_ADD_8[2][256][256];
//uint8_t CZ80Data::m_abtFlags_SUB_8[2][256][256];
//uint8_t CZ80Data::m_abtFlags_DAA[8][256];
//uint8_t CZ80Data::m_abtResult_DAA[8][256];
uint8_t* CZ80Data::m_abtFlags_INC_8;
uint8_t* CZ80Data::m_abtFlags_DEC_8;
uint8_t* CZ80Data::m_abtFlags_LOGICAL_8;
uint8_t* CZ80Data::m_abtFlags_BIT_b;
uint8_t* CZ80Data::m_abtFlags_ADD_8;
uint8_t* CZ80Data::m_abtFlags_SUB_8;
uint8_t* CZ80Data::m_abtFlags_DAA;
uint8_t* CZ80Data::m_abtResult_DAA;

#else // Z80CFG_NOUSE_FLAGTBL
uint8_t CZ80Data::m_abtParityTable[256];
#endif // Z80CFG_USE/NOUSE_FLAGTBL

////////////////////////////////////////////////////////////
// initialize

uint8_t CZ80Data::MakeParity(int nData) {
	uint8_t btParity = (uint8_t)P_V_FLAG;
	for (int nBit = 0; nBit < 8; nBit++) {
		if ((nData & (1 << nBit)) != 0) {
			btParity ^= (uint8_t)P_V_FLAG;
		}
	}
	return btParity;
}

#ifdef Z80CFG_USE_FLAGTBL

void CZ80Data::SetFlags_INC_8(int nData) {
	m_abtFlags_INC_8[nData] = uint8_t(
		((nData == 0)? Z_FLAG: 0) |
			((nData == 128)? P_V_FLAG: 0) |
			(((nData & 0x80) != 0)? S_FLAG: 0) |
			(((nData & 0x0F) == 0)? H_FLAG: 0));
}

void CZ80Data::SetFlags_DEC_8(int nData) {
	m_abtFlags_DEC_8[nData] = uint8_t(
		((nData == 0)? Z_FLAG: 0) |
			((nData == 127)? P_V_FLAG: 0) |
			(((nData & 0x80) != 0)? S_FLAG: 0) |
			N_FLAG |
			(((nData & 0x0F) == 15)? H_FLAG: 0));
}

void CZ80Data::SetFlags_LOGICAL_8(int nData) {
	m_abtFlags_LOGICAL_8[nData] = uint8_t(
		((nData == 0)? Z_FLAG: 0) |
			MakeParity(nData) |
			(((nData & 0x80) != 0)? S_FLAG: 0));
}

void CZ80Data::SetFlags_BIT_b(int nBit, int nData) {
	// undefinition specification:P_V_FLAG
	m_abtFlags_BIT_b[nBit * 256 + nData] = uint8_t(
		H_FLAG |
			(((nData & (1 << nBit)) == 0)? (Z_FLAG | P_V_FLAG): 0) |
			(((nBit == 7) && ((nData & 0x80) != 0))? S_FLAG: 0));
}

void CZ80Data::SetFlags_ADD_8(int nCarry, int nData1, int nData2) {
	int nResult1 = nData1+nData2+nCarry,
		nResult2 = (int)(int8_t)(uint8_t)nData1+
			(int)(int8_t)(uint8_t)nData2+
			nCarry;
	m_abtFlags_ADD_8[nCarry * 256 * 256 + nData1 * 256 + nData2] = uint8_t(
		((nResult1 > 255)? C_FLAG: 0) |
			((uint8_t(nResult1) == 0)? Z_FLAG: 0) |
			(((nResult2 > 127) || (nResult2 < -128))? P_V_FLAG: 0) |
			(nResult1 & S_FLAG) |
			(((nData1 & 0x0F)+(nData2 & 0x0F)+nCarry > 15)? H_FLAG: 0));
}

void CZ80Data::SetFlags_SUB_8(int nCarry, int nData1, int nData2) {
	int nResult1 = nData1-(nData2+nCarry);
	int nResult2 = (int)(int8_t)(uint8_t)nData1-
		(int)(int8_t)(uint8_t)nData2-
		nCarry;
	m_abtFlags_SUB_8[nCarry * 256 * 256 + nData1 * 256 + nData2] = uint8_t(
		((nResult1 < 0)? C_FLAG: 0) |
			((uint8_t(nResult1) == 0)? Z_FLAG: 0) |
			(((nResult2 > 127) || (nResult2 < -128))? P_V_FLAG: 0) |
			(nResult1 & S_FLAG) |
			N_FLAG |
			(((nData1 & 0x0F) < (nData2 & 0x0F)+nCarry)? H_FLAG: 0));
	/*
	Serial.print("FLAGS SUB:");
	Serial.print("[");
	Serial.print(nCarry);
	Serial.print(":");
	Serial.print(nData1);
	Serial.print(":");
	Serial.print(nData2);
	Serial.print("]:[");
	Serial.print(nResult1);
	Serial.print(":");
	Serial.print(nResult2);
	Serial.print("]:[");
	Serial.print(nCarry * 256 * 256 + nData1 * 256 + nData2);
	Serial.print("]:");
	Serial.println(m_abtFlags_SUB_8[nCarry * 256 * 256 + nData1 * 256 + nData2], BIN);
	*/
}

void CZ80Data::SetFlags_DAA(int nFlags, int nData) {
	bool bCarry = ((nFlags & 1) != 0),
		bN = ((nFlags & 2) != 0),
		bHalf = ((nFlags & 4) != 0);
	int nResult = nData;
	uint8_t btFlags = 0;
	if (!bN) {
		if (((nResult & 0x0F) > 0x09) || bHalf) {
			if ((nResult & 0x0F) > 0x09) {
				btFlags |= uint8_t(H_FLAG);
			}
			nResult += 0x06;
		}
		if ((nResult > 0x9F) || bCarry) {
			btFlags |= uint8_t(C_FLAG);
			nResult += 0x60;
		}
	} else {
		if ((nResult > 0x99) || bCarry) {
			btFlags |= uint8_t(C_FLAG);
		}
		if (((nResult & 0x0F) > 0x09) || bHalf) {
			if ((nResult & 0x0F) < 0x06) {
				btFlags |= uint8_t(H_FLAG);
			}
			nResult -= 0x06;
		}
		if ((nResult > 0x9F) || bCarry) {
			nResult -= 0x60;
		}
	}
	m_abtFlags_DAA[nFlags * 256 + nData] = uint8_t(
		btFlags | m_abtFlags_LOGICAL_8[uint8_t(nResult)]);
	m_abtResult_DAA[nFlags * 256 + nData] = uint8_t(nResult);
}

#endif // Z80CFG_USE_FLAGTBL

void CZ80Data::Initialize() {


	if (!m_bInitialized) {
		m_abtFlags_INC_8 = (uint8_t*)ps_malloc(256);
		m_abtFlags_DEC_8 = (uint8_t*)ps_malloc(256);
		m_abtFlags_LOGICAL_8 = (uint8_t*)ps_malloc(256);
		m_abtFlags_BIT_b = (uint8_t*)ps_malloc(8 * 256);
		m_abtFlags_ADD_8 = (uint8_t*)ps_malloc(2 * 256 * 256);
		m_abtFlags_SUB_8 = (uint8_t*)ps_malloc(2 * 256 * 256);
		m_abtFlags_DAA = (uint8_t*)ps_malloc(8 * 256);
		m_abtResult_DAA = (uint8_t*)ps_malloc(8 * 256);
		for (int nData = 0; nData < 256; nData++) {
#ifdef Z80CFG_USE_FLAGTBL
			SetFlags_INC_8(nData);
			SetFlags_DEC_8(nData);
			SetFlags_LOGICAL_8(nData);
			for (int nBit = 0; nBit < 8; nBit++) {
				SetFlags_BIT_b(nBit, nData);
			}
			for (int nData2 = 0; nData2 < 256; nData2++) {
				for (int nCarry = 0; nCarry < 2; nCarry++) {
					SetFlags_ADD_8(nCarry, nData, nData2);
					SetFlags_SUB_8(nCarry, nData, nData2);
				}
			}
			for (int nFlags = 0; nFlags < 8; nFlags++) {
				SetFlags_DAA(nFlags, nData);
			}
#else // Z80CFG_NOUSE_FLAGTBL
			m_abtParityTable[nData] = MakeParity(nData);
#endif // Z80CFG_USE/NOUSE_FLAGTBL
		}
		m_bInitialized = true;
	}
}
