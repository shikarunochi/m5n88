////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80Data_DEFINED
#define Z80Data_DEFINED

////////////////////////////////////////////////////////////
// include

#include "Z80Config.h"

////////////////////////////////////////////////////////////
// CZ80Data

class CZ80Data {
// enum
public:
	// flag
	enum {
		C_FLAG   = 0x01,
		N_FLAG   = 0x02,
		P_V_FLAG = 0x04,
		U1_FLAG  = 0x08,
		H_FLAG   = 0x10,
		U2_FLAG  = 0x20,
		Z_FLAG   = 0x40,
		S_FLAG   = 0x80
	};

// attribute
public:
	static bool m_bInitialized;

#ifdef Z80CFG_USE_FLAGTBL
	//static uint8_t m_abtFlags_INC_8[256];
	//static uint8_t m_abtFlags_DEC_8[256];
	//static uint8_t m_abtFlags_LOGICAL_8[256];
	//static uint8_t m_abtFlags_BIT_b[8][256];
	//static uint8_t m_abtFlags_ADD_8[2][256][256];
	//static uint8_t m_abtFlags_SUB_8[2][256][256];
	//static uint8_t m_abtFlags_DAA[8][256];
	//static uint8_t m_abtResult_DAA[8][256];
	static uint8_t* m_abtFlags_INC_8;
	static uint8_t* m_abtFlags_DEC_8;
	static uint8_t* m_abtFlags_LOGICAL_8;
	static uint8_t* m_abtFlags_BIT_b;
	static uint8_t* m_abtFlags_ADD_8;
	static uint8_t* m_abtFlags_SUB_8;
	static uint8_t* m_abtFlags_DAA;
	static uint8_t* m_abtResult_DAA;
#else // Z80CFG_NOUSE_FLAGTBL
	static uint8_t m_abtParityTable[256];
#endif // Z80CFG_USE/NOUSE_FLAGTBL

// initialize
protected:
	static uint8_t MakeParity(int nData);
#ifdef Z80CFG_USE_FLAGTBL
	static void SetFlags_INC_8(int nData);
	static void SetFlags_DEC_8(int nData);
	static void SetFlags_LOGICAL_8(int nData);
	static void SetFlags_BIT_b(int nBit, int nData);
	static void SetFlags_ADD_8(int nCarry, int nData1, int nData2);
	static void SetFlags_SUB_8(int nCarry, int nData1, int nData2);
	static void SetFlags_DAA(int nFlags, int nData);
#endif // Z80CFG_USE_FLAGTBL

public:
	static void Initialize();
};

#endif // Z80Data_DEFINED
