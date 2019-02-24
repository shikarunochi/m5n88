////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80_DEFINED
#define Z80_DEFINED

////////////////////////////////////////////////////////////
// include

#include "Z80Config.h"
#include "Z80Register.h"
#include "Z80Data.h"
#include "Z80Adapter.h"

////////////////////////////////////////////////////////////
// CZ80 super class

class CZ80Super {
// typedef
public:
#ifdef Z80CFG_USE_TEMPLATE
	typedef uint8_t (*RPROC)(int nAddress);
	typedef void (*WPROC)(int nAddress, uint8_t btData);
#endif // Z80CFG_USE_TEMPLATE
};

////////////////////////////////////////////////////////////
// CZ80

#ifdef Z80CFG_USE_TEMPLATE
#define CZ80PureName	TZ80

template <int TID, int TMB, int TIOB>
class TZ80 : public CZ80Super
#else // Z80CFG_NOUSE_TEMPLATE
#define CZ80PureName	CZ80

class CZ80 : public CZ80Super
#endif // Z80CFG_USE/NOUSE_TEMPLATE
{
// enum
public:
	// flag
	enum {
		C_FLAG   = CZ80Data::C_FLAG,
		N_FLAG   = CZ80Data::N_FLAG,
		P_V_FLAG = CZ80Data::P_V_FLAG,
		U1_FLAG  = CZ80Data::U1_FLAG,
		H_FLAG   = CZ80Data::H_FLAG,
		U2_FLAG  = CZ80Data::U2_FLAG,
		Z_FLAG   = CZ80Data::Z_FLAG,
		S_FLAG   = CZ80Data::S_FLAG
	};
#ifdef Z80CFG_USE_TEMPLATE
	// block size
	enum {
		MEM_BLOCK = TMB,
		IO_BLOCK  = TIOB,
	};
#endif // Z80CFG_USE_TEMPLATE
	// I/O address count
	enum {
#ifdef Z80CFG_IOADDR_WIDTH_8
		IOADDR_COUNT = 256
#else // Z80CFG_IOADDR_WIDTH_16
		IOADDR_COUNT = 65536
#endif // Z80CFG_IOADDR_WIDTH
	};

// typedef
public:
#ifdef Z80CFG_USE_TEMPLATE
	typedef TZ80<TID, TMB, TIOB> CThisClass;
#else // Z80CFG_NOUSE_TEMPLATE
	typedef CZ80 CThisClass;
#endif // Z80CFG_USE/NOUSE_TEMPLATE
#ifdef Z80CFG_USE_TEMPLATE
	using CZ80Super::RPROC;
	using CZ80Super::WPROC;
#endif // Z80CFG_USE_TEMPLATE

// attribute
public:
	Z80STATIC URegisterPair m_regpAF, m_regpAF2;
	Z80STATIC URegisterPair m_regpBC, m_regpBC2;
	Z80STATIC URegisterPair m_regpDE, m_regpDE2;
	Z80STATIC URegisterPair m_regpHL, m_regpHL2;
	Z80STATIC URegisterPair m_regpIX, m_regpIY;
	Z80STATIC URegisterPair m_regpSP, m_regpPC;
	Z80STATIC URegisterPair m_regpIR;
	Z80STATIC uint8_t m_btR2;
	Z80STATIC int m_nInterruptMode;
	Z80STATIC bool m_bEnableInterrupt, m_bEnableInterrupt2;
	Z80STATIC bool m_bEnableInterruptReserve;
	Z80STATIC bool m_bHalting;
	Z80STATIC int m_nIntVect;
	Z80STATIC int m_nExecClock;
	Z80STATIC int m_nProgressClock;

	Z80STATIC char m_szMnemonic[256];
	Z80STATIC bool m_bStepExecuteOpCode, m_bStepExecuteOpCode2;

#ifdef Z80CFG_USE_TEMPLATE
	static CThisClass* m_pThis;
	Z80STATIC CZ80Adapter* m_pAdapter;

	Z80STATIC RPROC m_arpMemRTable[65536/MEM_BLOCK];
	Z80STATIC WPROC m_awpMemWTable[65536/MEM_BLOCK];
	Z80STATIC RPROC m_arpMemRM1Table[65536/MEM_BLOCK];
	Z80STATIC RPROC m_arpIORTable[IOADDR_COUNT/IO_BLOCK];
	Z80STATIC WPROC m_awpIOWTable[IOADDR_COUNT/IO_BLOCK];
#endif // Z80CFG_USE_TEMPLATE

public:
#ifdef Z80CFG_USE_FLAGTBL
	static uint8_t GetFlags_INC_8(uint8_t btData) {
		return CZ80Data::m_abtFlags_INC_8[btData];
	}
	static uint8_t GetFlags_DEC_8(uint8_t btData) {
		return CZ80Data::m_abtFlags_DEC_8[btData];
	}
	static uint8_t GetFlags_LOGICAL_8(uint8_t btData) {
		return CZ80Data::m_abtFlags_LOGICAL_8[btData];
	}
	static uint8_t GetFlags_BIT_b(uint8_t btBit, uint8_t btData) {
		return CZ80Data::m_abtFlags_BIT_b[btBit * 256 + btData];
	}
	static uint8_t GetFlags_ADD_8(int nCarry, uint8_t btDst, uint8_t btSrc) {
		return CZ80Data::m_abtFlags_ADD_8[nCarry * 256 * 256 + btDst * 256 + btSrc];
	}
	static uint8_t GetFlags_SUB_8(int nCarry, uint8_t btDst, uint8_t btSrc) {
		return CZ80Data::m_abtFlags_SUB_8[nCarry * 256 * 256 + btDst * 256 + btSrc];
	}
	static uint8_t GetFlags_DAA(int nFlags, uint8_t btData) {
		return CZ80Data::m_abtFlags_DAA[nFlags * 256 + btData];
	}
	static uint8_t GetResult_DAA(int nFlags, uint8_t btData) {
		return CZ80Data::m_abtResult_DAA[nFlags * 256 + btData];
	}
#else // Z80CFG_NOUSE_FLAGTBL
	static uint8_t GetParityTable(uint8_t btData) {
		return CZ80Data::m_abtParityTable[btData];
	}
#endif // Z80CFG_USE/NOUSE_FLAGTBL
#ifdef Z80CFG_USE_TEMPLATE
	Z80STATIC CZ80Adapter* GetAdapter() {
		return m_pAdapter;
	}
	Z80STATIC void SetReadMemoryProc(int nBank, RPROC rpMem) {
		m_arpMemRTable[nBank] = rpMem;
	}
	Z80STATIC void SetWriteMemoryProc(int nBank, WPROC wpMem) {
		m_awpMemWTable[nBank] = wpMem;
	}
	Z80STATIC void SetReadMemoryM1Proc(int nBank, RPROC rpMemM1) {
		m_arpMemRM1Table[nBank] = rpMemM1;
	}
	Z80STATIC void SetReadIOProc(int nBank, RPROC rpIO) {
		m_arpIORTable[nBank] = rpIO;
	}
	Z80STATIC void SetWriteIOProc(int nBank, WPROC wpIO) {
		m_awpIOWTable[nBank] = wpIO;
	}
#endif // Z80CFG_USE_TEMPLATE

// construct/destruct
public:
	CZ80PureName();
	virtual ~CZ80PureName();

// initialize
public:
	virtual void Initialize();
	virtual void Reset();

// memory-I/O operation
public:
#ifdef Z80CFG_USE_TEMPLATE
	static uint8_t ReadMemory(int nAddress) {
		return (m_arpMemRTable[nAddress/MEM_BLOCK])(nAddress);
	}
	static void WriteMemory(int nAddress, uint8_t btData) {
		(m_awpMemWTable[nAddress/MEM_BLOCK])(nAddress, btData);
	}
	static uint8_t ReadMemoryM1(int nAddress) {
		return (m_arpMemRM1Table[nAddress/MEM_BLOCK])(nAddress);
	}
	static uint8_t ReadIO(int nAddress) {
		return (m_arpIORTable[nAddress/IO_BLOCK])(nAddress);
	}
	static void WriteIO(int nAddress, uint8_t btData) {
		(m_awpIOWTable[nAddress/IO_BLOCK])(nAddress, btData);
	}
#else // Z80CFG_NOUSE_TEMPLATE
	virtual uint8_t ReadMemory(int nAddress) = 0;
	virtual void WriteMemory(int nAddress, uint8_t btData) = 0;
	virtual uint8_t ReadMemoryM1(int nAddress) = 0;
	virtual uint8_t ReadIO(int nAddress) = 0;
	virtual void WriteIO(int nAddress, uint8_t btData) = 0;
#endif // Z80CFG_USE/NOUSE_TEMPLATE
	Z80STATIC uint16_t ReadMemoryW(int nAddress) {
		return uint16_t(
			ReadMemory(nAddress) |
			(ReadMemory(uint16_t(nAddress+1)) << 8));
	}
	Z80STATIC void WriteMemoryW(int nAddress, uint16_t wData) {
		WriteMemory(nAddress, uint8_t(wData));
		WriteMemory(uint16_t(nAddress+1), uint8_t(wData >> 8));
	}

// register operation
public:
	// AF register
	Z80STATIC URegisterPair& RegAF() {
		return m_regpAF;
	}
	Z80STATIC CRegister& RegA() {
		return m_regpAF.Hi();
	}
	Z80STATIC CRegister& RegF() {
		return m_regpAF.Lo();
	}
	Z80STATIC int MaskRegF(int nMaskFlag) {
		return RegF().Get() & nMaskFlag;
	}
	Z80STATIC bool TestRegF(int nTestFlag) {
		return MaskRegF(nTestFlag) != 0;
	}
	Z80STATIC void UpdateRegF(int nClear, int nSet) {
		RegF().Set(uint8_t((RegF().Get() & ~nClear) | nSet));
	}
	Z80STATIC void SetRegF(int nBitSet) {
		RegF().Ref() |= uint8_t(nBitSet);
	}
	Z80STATIC void ResetRegF(int nBitReset) {
		RegF().Ref() &= uint8_t(~nBitReset);
	}
	Z80STATIC void InvertRegF(int nBitInvert) {
		RegF().Ref() ^= uint8_t(nBitInvert);
	}
	// AF2 register
	Z80STATIC URegisterPair& RegAF2() {
		return m_regpAF2;
	}
	Z80STATIC bool TestRegF2(int nTestFlag) {
		return (m_regpAF2.Lo().Get() & nTestFlag) != 0;
	}
	// BC register
	Z80STATIC URegisterPair& RegBC() {
		return m_regpBC;
	}
	Z80STATIC CRegister& RegB() {
		return m_regpBC.Hi();
	}
	Z80STATIC CRegister& RegC() {
		return m_regpBC.Lo();
	}
	// BC2 register
	Z80STATIC URegisterPair& RegBC2() {
		return m_regpBC2;
	}
	// DE register
	Z80STATIC URegisterPair& RegDE() {
		return m_regpDE;
	}
	Z80STATIC CRegister& RegD() {
		return m_regpDE.Hi();
	}
	Z80STATIC CRegister& RegE() {
		return m_regpDE.Lo();
	}
	// DE2 register
	URegisterPair& RegDE2() {
		return m_regpDE2;
	}
	// HL register
	Z80STATIC URegisterPair& RegHL() {
		return m_regpHL;
	}
	Z80STATIC CRegister& RegH() {
		return m_regpHL.Hi();
	}
	Z80STATIC CRegister& RegL() {
		return m_regpHL.Lo();
	}
	// HL2 register
	Z80STATIC URegisterPair& RegHL2() {
		return m_regpHL2;
	}
	// IX register
	Z80STATIC URegisterPair& RegIX() {
		return m_regpIX;
	}
	Z80STATIC uint16_t GetRegIXd(uint8_t btDsp) {
		return uint16_t(int32_t(RegIX().Get())+(int8_t)btDsp);
	}
	Z80STATIC CRegister& RegIXH() {
		return m_regpIX.Hi();
	}
	Z80STATIC CRegister& RegIXL() {
		return m_regpIX.Lo();
	}
	// IY register
	Z80STATIC URegisterPair& RegIY() {
		return m_regpIY;
	}
	Z80STATIC uint16_t GetRegIYd(uint8_t btDsp) {
		return uint16_t(int32_t(RegIY().Get())+(int8_t)btDsp);
	}
	Z80STATIC CRegister& RegIYH() {
		return m_regpIY.Hi();
	}
	Z80STATIC CRegister& RegIYL() {
		return m_regpIY.Lo();
	}
	// SP register
	Z80STATIC URegisterPair& RegSP() {
		return m_regpSP;
	}
	Z80STATIC void PushReg(const URegisterPair& regpPush) {
		WriteMemory(--RegSP().Ref(), regpPush.GetHi());
		WriteMemory(--RegSP().Ref(), regpPush.GetLo());
	}
	Z80STATIC void PopReg(URegisterPair& regpPop) {
		regpPop.SetLo(ReadMemory(RegSP().Ref()++));
		regpPop.SetHi(ReadMemory(RegSP().Ref()++));
	}
	// PC register
	Z80STATIC URegisterPair& RegPC() {
		return m_regpPC;
	}
	Z80STATIC void AddRegPC(uint8_t btE) {
		m_regpPC.Set(uint16_t(m_regpPC.Get()+(int)(int8_t)btE));
	}
	Z80STATIC void FetchByte(uint8_t& btData) {
		btData = ReadMemory(RegPC().Get());
		RegPC().Ref()++;
	}
	Z80STATIC void FetchWord(uint16_t& wData) {
		wData = ReadMemory(RegPC().Get());
		RegPC().Ref()++;
		wData |= (ReadMemory(RegPC().Get()) << 8);
		RegPC().Ref()++;
	}

	Z80STATIC void FetchByteM1(uint8_t& btData) {
		btData = ReadMemoryM1(RegPC().Get());
		/*
		Serial.print("FetchByteM1:");
		Serial.print(RegPC().Get(),HEX);
		Serial.print(" : ");
		Serial.print(btData,HEX);
		Serial.print(" ::: ");
		Serial.print("F:");
		Serial.print(RegF().Get(),HEX);Serial.print(":");
		Serial.print("A:");
		Serial.print(RegA().Get(),HEX);Serial.print(":");
		Serial.print("BC:");
		Serial.print(RegBC().Get(),HEX);Serial.print(":");
		Serial.print("DE:");
		Serial.print(RegDE().Get(),HEX);Serial.print(":");
		Serial.print("HL:");
		Serial.print(RegHL().Get(),HEX);Serial.print(":");
		Serial.print("IX:");
		Serial.print(RegIX().Get(),HEX);Serial.print(":");
		Serial.print("IY:");
		Serial.print(RegIY().Get(),HEX);Serial.print(":");

		Serial.print("BC2:");
		Serial.print(RegBC2().Get(),HEX);Serial.print(":");
		Serial.print("HL2:");
		Serial.print(RegHL2().Get(),HEX);Serial.print(":");
		Serial.print("SP:");
		Serial.print(RegSP().Get(),HEX);Serial.print(":");
		Serial.print("(BC):");
		Serial.print(ReadMemoryM1(RegB().Get()),HEX);
		Serial.print(ReadMemoryM1(RegC().Get()),HEX);Serial.print(":");
		Serial.print("(DE):");
		Serial.print(ReadMemoryM1(RegD().Get()),HEX);
		Serial.print(ReadMemoryM1(RegE().Get()),HEX);Serial.print(":");
		Serial.print("(HL):");
		Serial.print(ReadMemoryM1(RegH().Get()),HEX);
		Serial.print(ReadMemoryM1(RegL().Get()),HEX);Serial.print(":");
		Serial.print("(SP):");
		Serial.println(ReadMemoryM1(RegSP().Get()),HEX);Serial.print(":");
		*/
		RegPC().Ref()++;
	}
	// I register
	Z80STATIC uint8_t GetRegI() {
		return m_regpIR.GetHi();
	}
	Z80STATIC void SetRegI(uint8_t btData) {
		m_regpIR.SetHi(btData);
	}
	// R register
	Z80STATIC uint8_t GetRegR() {
		return uint8_t(((m_regpIR.GetLo()) & 0x7F) | m_btR2);
	}
	Z80STATIC void SetRegR(uint8_t btData) {
		m_regpIR.SetLo(btData);
		m_btR2 = uint8_t(btData & 0x80);
	}
	Z80STATIC void IncRegR() {
		m_regpIR.RefLo()++;
	}
	// interrupt mode
	Z80STATIC int GetInterruptMode() {
		return m_nInterruptMode;
	}
	Z80STATIC void SetInterruptMode(int nInterruptMode) {
		m_nInterruptMode = nInterruptMode;
	}
	// interrupt register
	Z80STATIC bool IsEnableInterrupt() {
		return m_bEnableInterrupt;
	}
	Z80STATIC void SetEnableInterrupt(bool bEnableInterrupt) {
		m_bEnableInterrupt = bEnableInterrupt;
	}
	Z80STATIC bool IsEnableInterrupt2() {
		return m_bEnableInterrupt2;
	}
	Z80STATIC void SetEnableInterrupt2(bool bEnableInterrupt2) {
		m_bEnableInterrupt2 = bEnableInterrupt2;
	}
	Z80STATIC bool IsEnableInterruptReserve() {
		return m_bEnableInterruptReserve;
	}
	Z80STATIC void SetEnableInterruptReserve(bool bEnableInterruptReserve) {
		m_bEnableInterruptReserve = bEnableInterruptReserve;
	}
	// HALT
	Z80STATIC bool IsHalting() {
		return m_bHalting;
	}
	Z80STATIC void SetHalting(bool bHalting) {
		m_bHalting = bHalting;
	}
	// interrupt vector
	Z80STATIC int GetIntVect() {
		return m_nIntVect;
	}
	Z80STATIC void SetIntVect(int nIntVect) {
		m_nIntVect = nIntVect;
	}

// interrupt
public:
	// occurred interrupt
	virtual int DoInterrupt(uint8_t btIntVect);
	// occurred NMI
	virtual int DoNMInterrupt();
	// RETI
	virtual void FinishInterrupt();
	// RETN
	virtual void FinishNMInterrupt();

// HALT
public:
	// process HALT
	virtual void ProcessHALT();

// execute
public:
	Z80STATIC int GetExecClock() {
		return m_nExecClock;
	}
	Z80STATIC void SetExecClock(int nExecClock) {
		m_nExecClock = nExecClock;
	}
	Z80STATIC void AddExecClock(int nExecClock) {
		m_nExecClock += nExecClock;
	}
	Z80STATIC int GetProgressClock() {
		return m_nProgressClock;
	}
	Z80STATIC void SetProgressClock(int nProgressClock) {
		m_nProgressClock = nProgressClock;
	}
#ifdef Z80CFG_USE_TEMPLATE
	Z80STATIC void Exec_X(uint8_t& btExtra, uint8_t& btX);
	Z80STATIC void Exec_CB_X(uint8_t& btExtra, uint8_t& btX);
	Z80STATIC void Exec_ED_X(uint8_t& btExtra, uint8_t& btX);
	Z80STATIC void Exec_DD_X(uint8_t& btExtra, uint8_t& btX, uint8_t& btD);
	Z80STATIC void Exec_DD_CB_X(uint8_t& btExtra, uint8_t& btX, uint8_t btD);
	Z80STATIC void Exec_FD_X(uint8_t& btExtra, uint8_t& btX, uint8_t& btD);
	Z80STATIC void Exec_FD_CB_X(uint8_t& btExtra, uint8_t& btX, uint8_t btD);
#endif // Z80CFG_USE_TEMPLATE
	Z80STATIC int ExecuteOneOpCode();
	Z80STATIC int ExecuteMultiOpCode(int nOpCodeCount);

// dis-assemble
public:
	Z80STATIC const char* GetMnemonic() {
		return m_szMnemonic;
	}
	Z80STATIC bool IsStepExecuteOpCode() {
		return m_bStepExecuteOpCode;
	}
	Z80STATIC void SetStepExecuteOpCode(bool bStepExecuteOpCode) {
		m_bStepExecuteOpCode = bStepExecuteOpCode;
	}
	Z80STATIC bool IsStepExecuteOpCode2() {
		return m_bStepExecuteOpCode2;
	}
	Z80STATIC void SetStepExecuteOpCode2(bool bStepExecuteOpCode2) {
		m_bStepExecuteOpCode2 = bStepExecuteOpCode2;
	}
	virtual void FormatMnemonicV(const char* pszFormat, va_list argList);
	void FormatMnemonic(const char* pszFormat, ...);
	int DisAssemble();
};

#include "Z80Template.h"

#endif // Z80_DEFINED
