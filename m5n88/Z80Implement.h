////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80Implement_DEFINED
#define Z80Implement_DEFINED

////////////////////////////////////////////////////////////
// attribute

#ifdef Z80CFG_USE_TEMPLATE

#ifdef Z80CFG_TEMPLATE_STATICVAR_NORMAL
#define Z80TEMPLATE_EXPLICIT_SV	Z80TEMPLATE_EXPLICIT_SP
#define CZ80X					CZ80
#else // Z80CFG_TEMPLATE_STATICVAR_SPECIAL
#define Z80TEMPLATE_EXPLICIT_SV	template <int TID, int TMB, int TIOB>
#define CZ80X	TZ80<TID, TMB, TIOB>
#endif // Z80CFG_TEMPLATE_STATICVAR

Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpAF;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpAF2;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpBC;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpBC2;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpDE;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpDE2;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpHL;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpHL2;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpIX;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpIY;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpSP;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpPC;
Z80TEMPLATE_EXPLICIT_SV
URegisterPair CZ80X::m_regpIR;
Z80TEMPLATE_EXPLICIT_SV
uint8_t CZ80X::m_btR2;
Z80TEMPLATE_EXPLICIT_SV
int CZ80X::m_nInterruptMode;
Z80TEMPLATE_EXPLICIT_SV
bool CZ80X::m_bEnableInterrupt;
Z80TEMPLATE_EXPLICIT_SV
bool CZ80X::m_bEnableInterrupt2;
Z80TEMPLATE_EXPLICIT_SV
bool CZ80X::m_bEnableInterruptReserve;
Z80TEMPLATE_EXPLICIT_SV
bool CZ80X::m_bHalting;
Z80TEMPLATE_EXPLICIT_SV
int CZ80X::m_nIntVect;
Z80TEMPLATE_EXPLICIT_SV
int CZ80X::m_nExecClock;
Z80TEMPLATE_EXPLICIT_SV
int CZ80X::m_nProgressClock;

Z80TEMPLATE_EXPLICIT_SV
char CZ80X::m_szMnemonic[256];
Z80TEMPLATE_EXPLICIT_SV
bool CZ80X::m_bStepExecuteOpCode;
Z80TEMPLATE_EXPLICIT_SV
bool CZ80X::m_bStepExecuteOpCode2;

Z80TEMPLATE_EXPLICIT_SV
CZ80X* CZ80X::m_pThis;
Z80TEMPLATE_EXPLICIT_SV
CZ80Adapter* CZ80X::m_pAdapter;

Z80TEMPLATE_EXPLICIT_SV
CZ80Super::RPROC CZ80X::m_arpMemRTable[65536/MEM_BLOCK];
///CZ80Super::RPROC *CZ80X::m_arpMemRTable;
Z80TEMPLATE_EXPLICIT_SV
CZ80Super::WPROC CZ80X::m_awpMemWTable[65536/MEM_BLOCK];
//CZ80Super::WPROC *CZ80X::m_awpMemWTable;
Z80TEMPLATE_EXPLICIT_SV
CZ80Super::RPROC CZ80X::m_arpMemRM1Table[65536/MEM_BLOCK];
//CZ80Super::RPROC *CZ80X::m_arpMemRM1Table;
Z80TEMPLATE_EXPLICIT_SV
CZ80Super::RPROC CZ80X::m_arpIORTable[IOADDR_COUNT/IO_BLOCK];
//CZ80Super::RPROC *CZ80X::m_arpIORTable;
Z80TEMPLATE_EXPLICIT_SV
CZ80Super::WPROC CZ80X::m_awpIOWTable[IOADDR_COUNT/IO_BLOCK];
//CZ80Super::WPROC *CZ80X::m_awpIOWTable;

#undef Z80TEMPLATE_EXPLICIT_SV
#undef CZ80X

#endif // Z80CFG_USE_TEMPLATE

////////////////////////////////////////////////////////////
// interrupt
// (declare before include for g++.)

// RETI

Z80TEMPLATE_EXPLICIT_SP
void CZ80::FinishInterrupt() {
}

// RETN

Z80TEMPLATE_EXPLICIT_SP
void CZ80::FinishNMInterrupt() {
}

////////////////////////////////////////////////////////////
// HALT
// (declare before include for g++.)

// process HALT

Z80TEMPLATE_EXPLICIT_SP
void CZ80::ProcessHALT() {
}

////////////////////////////////////////////////////////////
// include

#ifdef Z80CFG_USE_TEMPLATE
#include "Z80Executor2.h"
#include "Z80ExecutorBase2.h"
#else // Z80CFG_NOUSE_TEMPLATE
#include "Z80ExecutorBase.h"
#include "Z80Executor.h"
#include "Z80DisAssembler.h"
#endif // Z80CFG_USE/NOUSE_TEMPLATE

////////////////////////////////////////////////////////////
// CZ80

////////////////////////////////////////////////////////////
// construct/destruct

Z80TEMPLATE_EXPLICIT_SP
CZ80::CZ80PureName() {
#ifdef Z80CFG_USE_TEMPLATE
	m_pThis = this;
	m_pAdapter = new TZ80Adapter<CZ80>(this);
#endif // Z80CFG_USE_TEMPLATE
}

Z80TEMPLATE_EXPLICIT_SP
CZ80::~CZ80PureName() {
#ifdef Z80CFG_USE_TEMPLATE
	if (m_pAdapter != NULL) {
		delete m_pAdapter;
		m_pAdapter = NULL;
	}
#endif // Z80CFG_USE_TEMPLATE
}

////////////////////////////////////////////////////////////
// initialize

Z80TEMPLATE_EXPLICIT_SP
void CZ80::Initialize() {
	//int heapSize = heap_caps_get_free_size(MALLOC_CAP_8BIT);
	//Serial.print("heap:");
	//Serial.println(heapSize);
	Serial.println("CZ80:Initialize");
	//CZ80::m_arpMemRTable = (RPROC*)ps_malloc(65536/MEM_BLOCK); 
	//CZ80::m_awpMemWTable = (WPROC*)ps_malloc(65536/MEM_BLOCK);
	//CZ80::m_arpMemRM1Table = (RPROC*)ps_malloc(65536/MEM_BLOCK);
	//CZ80::m_arpIORTable = (RPROC*)ps_malloc(IOADDR_COUNT/IO_BLOCK);
	//CZ80::m_awpIOWTable = (WPROC*)ps_malloc(IOADDR_COUNT/IO_BLOCK);
	CZ80Data::Initialize();
#ifdef Z80CFG_USE_TEMPLATE
	CZ80Executor2::Initialize();
#endif // Z80CFG_USE_TEMPLATE
}

Z80TEMPLATE_EXPLICIT_SP
void CZ80::Reset() {
	RegAF().Set(0);
	RegAF2().Set(0);
	RegBC().Set(0);
	RegBC2().Set(0);
	RegDE().Set(0);
	RegDE2().Set(0);
	RegHL().Set(0);
	RegHL2().Set(0);
	RegIX().Set(0);
	RegIY().Set(0);
	RegSP().Set(0);
	RegPC().Set(0);
	SetRegR(0);
	SetRegI(0);
	SetInterruptMode(0);
	SetEnableInterrupt(false);
	SetEnableInterrupt2(false);
	SetEnableInterruptReserve(false);
	SetHalting(false);
	SetIntVect(-1);
	SetProgressClock(0);
}

////////////////////////////////////////////////////////////
// interrupt

// occurred interrupt

Z80TEMPLATE_EXPLICIT_SP
int CZ80::DoInterrupt(uint8_t btIntVect) {
#ifdef Z80CFG_USE_TEMPLATE
	return CZ80Executor2::DoInterrupt(btIntVect);
#else // Z80CFG_NOUSE_TEMPLATE
	CZ80Executor z80Executor(*Z80THIS);
	return z80Executor.DoInterrupt(btIntVect);
#endif // Z80CFG_USE/NOUSE_TEMPLATE
}

// occurred NMI

Z80TEMPLATE_EXPLICIT_SP
int CZ80::DoNMInterrupt() {
#ifdef Z80CFG_USE_TEMPLATE
	return CZ80Executor2::DoNMInterrupt();
#else // Z80CFG_NOUSE_TEMPLATE
	CZ80Executor z80Executor(*Z80THIS);
	return z80Executor.DoNMInterrupt();
#endif // Z80CFG_USE/NOUSE_TEMPLATE
}

////////////////////////////////////////////////////////////
// execute

Z80TEMPLATE_EXPLICIT_SP
int CZ80::ExecuteOneOpCode() {
#ifdef Z80CFG_USE_TEMPLATE
	if ((m_nIntVect >= 0) && m_bEnableInterrupt) {
		m_nExecClock = Z80THIS->DoInterrupt(uint8_t(m_nIntVect));
	} else {
		m_nExecClock = 0;
		m_bEnableInterrupt = m_bEnableInterruptReserve;
		uint8_t btX;
		FetchByteM1(btX);
		IncRegR();
		CZ80Executor2::m_nOpCode = btX;
		do {
			int nOpCode = CZ80Executor2::m_nOpCode;
			CZ80Executor2::m_nOpCode = -1;
			(CZ80Executor2::m_aepExecuteTable[nOpCode])();
		} while (CZ80Executor2::m_nOpCode >= 0);
	}
	//Serial.println("3:HERE?");
	return m_nExecClock;
#else // Z80CFG_NOUSE_TEMPLATE
	int nClock;
	if ((m_nIntVect >= 0) && m_bEnableInterrupt) {
		nClock = DoInterrupt(uint8_t(m_nIntVect));
	} else {
		CZ80Executor z80Executor(*Z80THIS);
		nClock = z80Executor.ExecuteOneOpCode();
	}
	return nClock;
#endif // Z80CFG_USE/NOUSE_TEMPLATE
}

Z80TEMPLATE_EXPLICIT_SP
int CZ80::ExecuteMultiOpCode(int nOpCodeCount) {
#ifdef Z80CFG_USE_TEMPLATE
	m_nExecClock = 0;
	int nCount = 0;
	//Serial.print("ExecuteMultiOpCode:");Serial.println(nOpCodeCount);
	do {
		if ((m_nIntVect >= 0) && m_bEnableInterrupt) {
			m_nExecClock += Z80THIS->DoInterrupt(uint8_t(m_nIntVect));
		} else {
			m_bEnableInterrupt = m_bEnableInterruptReserve;
			uint8_t btX;
			FetchByteM1(btX);
			IncRegR();
			CZ80Executor2::m_nOpCode = btX;
			do {
				int nOpCode = CZ80Executor2::m_nOpCode;
				CZ80Executor2::m_nOpCode = -1;
				//Serial.print("ExecuteMultiOpCode 5:");
				//Serial.println(nOpCode, HEX);
				(CZ80Executor2::m_aepExecuteTable[nOpCode])();
			} while (CZ80Executor2::m_nOpCode >= 0);
		}
		m_nProgressClock = m_nExecClock;
	} while (++nCount < nOpCodeCount);
	m_nProgressClock = 0;
	return m_nExecClock;
#else // Z80CFG_NOUSE_TEMPLATE
	int nClock = 0;
	int nCount = 0;
	CZ80Executor z80Executor(*Z80THIS);
	do {
		if ((m_nIntVect >= 0) && m_bEnableInterrupt) {
			nClock += DoInterrupt(uint8_t(m_nIntVect));
		} else {
			nClock += z80Executor.ExecuteOneOpCode();
		}
		m_nProgressClock = nClock;
	} while (++nCount < nOpCodeCount);
	m_nProgressClock = 0;
	return nClock;
#endif // Z80CFG_USE/NOUSE_TEMPLATE
}

////////////////////////////////////////////////////////////
// dis-assemble

Z80TEMPLATE_EXPLICIT_SP
void CZ80::FormatMnemonicV(const char* pszFormat, va_list argList) {
	vsprintf(m_szMnemonic, pszFormat, argList);
}

Z80TEMPLATE_EXPLICIT_SP
void CZ80::FormatMnemonic(const char* pszFormat, ...) {
	va_list argList;
	va_start(argList, pszFormat);
	FormatMnemonicV(pszFormat, argList);
	va_end(argList);
}

Z80TEMPLATE_EXPLICIT_SP
int CZ80::DisAssemble() {
#ifdef Z80CFG_USE_TEMPLATE
	return m_pAdapter->DisAssemble();
#else // Z80CFG_NOUSE_TEMPLATE
	strcpy(m_szMnemonic, "???");
	m_bStepExecuteOpCode = m_bStepExecuteOpCode2 = false;
	CZ80DisAssembler z80DisAssembler(*Z80THIS);
	return z80DisAssembler.ExecuteOneOpCode();
#endif // Z80CFG_USE/NOUSE_TEMPLATE
}

#endif // Z80Implement_DEFINED
