////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80Adapter_DEFINED
#define Z80Adapter_DEFINED

////////////////////////////////////////////////////////////
// include
#include <stdarg.h>
#include "Z80Config.h"
#include "Z80Register.h"
#include "Z80Data.h"

////////////////////////////////////////////////////////////
// CZ80Adapter

#ifdef Z80CFG_USE_TEMPLATE
class CZ80Adapter {
// enum
public:
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

// construct/destruct
public:
	CZ80Adapter();
	virtual ~CZ80Adapter();

// initialize
public:
	virtual void Initialize() = 0;
	virtual void Reset() = 0;

// memory-I/O operation
public:
	virtual uint8_t ReadMemory(int nAddress) = 0;
	virtual void WriteMemory(int nAddress, uint8_t btData) = 0;
	virtual uint8_t ReadMemoryM1(int nAddress) = 0;
	virtual uint8_t ReadIO(int nAddress) = 0;
	virtual void WriteIO(int nAddress, uint8_t btData) = 0;
	uint16_t ReadMemoryW(int nAddress) {
		return uint16_t(
			ReadMemory(nAddress) |
			(ReadMemory(uint16_t(nAddress+1)) << 8));
	}
	void WriteMemoryW(int nAddress, uint16_t wData) {
		WriteMemory(nAddress, uint8_t(wData));
		WriteMemory(uint16_t(nAddress+1), uint8_t(wData >> 8));
	}

// register operation
public:
	// AF register
	virtual URegisterPair& RegAF() = 0;
	CRegister& RegA() {
		return RegAF().Hi();
	}
	CRegister& RegF() {
		return RegAF().Lo();
	}
	int MaskRegF(int nMaskFlag) {
		return RegF().Get() & nMaskFlag;
	}
	bool TestRegF(int nTestFlag) {
		return MaskRegF(nTestFlag) != 0;
	}
	void UpdateRegF(int nClear, int nSet) {
		RegF().Set(uint8_t((RegF().Get() & ~nClear) | nSet));
	}
	void SetRegF(int nBitSet) {
		RegF().Ref() |= uint8_t(nBitSet);
	}
	void ResetRegF(int nBitReset) {
		RegF().Ref() &= uint8_t(~nBitReset);
	}
	void InvertRegF(int nBitInvert) {
		RegF().Ref() ^= uint8_t(nBitInvert);
	}
	// AF2 register
	virtual URegisterPair& RegAF2() = 0;
	bool TestRegF2(int nTestFlag) {
		return (RegAF2().Lo().Get() & nTestFlag) != 0;
	}
	// BC register
	virtual URegisterPair& RegBC() = 0;
	CRegister& RegB() {
		return RegBC().Hi();
	}
	CRegister& RegC() {
		return RegBC().Lo();
	}
	// BC2 register
	virtual URegisterPair& RegBC2() = 0;
	// DE register
	virtual URegisterPair& RegDE() = 0;
	CRegister& RegD() {
		return RegDE().Hi();
	}
	CRegister& RegE() {
		return RegDE().Lo();
	}
	// DE2 register
	virtual URegisterPair& RegDE2() = 0;
	// HL register
	virtual URegisterPair& RegHL() = 0;
	CRegister& RegH() {
		return RegHL().Hi();
	}
	CRegister& RegL() {
		return RegHL().Lo();
	}
	// HL2 register
	virtual URegisterPair& RegHL2() = 0;
	// IX register
	virtual URegisterPair& RegIX() = 0;
	uint16_t GetRegIXd(uint8_t btDsp) {
		return uint16_t(int32_t(RegIX().Get())+(int8_t)btDsp);
	}
	CRegister& RegIXH() {
		return RegIX().Hi();
	}
	CRegister& RegIXL() {
		return RegIX().Lo();
	}
	// IY register
	virtual URegisterPair& RegIY() = 0;
	uint16_t GetRegIYd(uint8_t btDsp) {
		return uint16_t(int32_t(RegIY().Get())+(int8_t)btDsp);
	}
	CRegister& RegIYH() {
		return RegIY().Hi();
	}
	CRegister& RegIYL() {
		return RegIY().Lo();
	}
	// SP register
	virtual URegisterPair& RegSP() = 0;
	void PushReg(const URegisterPair& regpPush) {
		WriteMemory(--RegSP().Ref(), regpPush.GetHi());
		WriteMemory(--RegSP().Ref(), regpPush.GetLo());
	}
	void PopReg(URegisterPair& regpPop) {
		regpPop.SetLo(ReadMemory(RegSP().Ref()++));
		regpPop.SetHi(ReadMemory(RegSP().Ref()++));
	}
	// PC register
	virtual URegisterPair& RegPC() = 0;
	void AddRegPC(uint8_t btE) {
		RegPC().Set(uint16_t(RegPC().Get()+(int)(int8_t)btE));
	}
	void FetchByte(uint8_t& btData) {
		btData = ReadMemory(RegPC().Get());
		RegPC().Ref()++;
	}
	void FetchWord(uint16_t& wData) {
		wData = ReadMemory(RegPC().Get());
		RegPC().Ref()++;
		wData |= (ReadMemory(RegPC().Get()) << 8);
		RegPC().Ref()++;
	}
	void FetchByteM1(uint8_t& btData) {
		btData = ReadMemoryM1(RegPC().Get());
		RegPC().Ref()++;
	}
	// I register
	virtual uint8_t GetRegI() = 0;
	virtual void SetRegI(uint8_t btData) = 0;
	// R register
	virtual uint8_t GetRegR() = 0;
	virtual void SetRegR(uint8_t btData) = 0;
	virtual void IncRegR() = 0;
	// interrupt mode
	virtual int GetInterruptMode() = 0;
	virtual void SetInterruptMode(int nInterruptMode) = 0;
	// interrupt register
	virtual bool IsEnableInterrupt() = 0;
	virtual void SetEnableInterrupt(bool bEnableInterrupt) = 0;
	virtual bool IsEnableInterrupt2() = 0;
	virtual void SetEnableInterrupt2(bool bEnableInterrupt2) = 0;
	virtual bool IsEnableInterruptReserve() = 0;
	virtual void SetEnableInterruptReserve(bool bEnableInterruptReserve) = 0;
	// HALT
	virtual bool IsHalting() = 0;
	virtual void SetHalting(bool bHalting) = 0;

// interrupt
public:
	// occurred interrupt
	virtual int DoInterrupt(uint8_t btIntVect) = 0;
	// occurred NMI
	virtual int DoNMInterrupt() = 0;
	// RETI
	virtual void FinishInterrupt() = 0;
	// RETN
	virtual void FinishNMInterrupt() = 0;

// HALT
public:
	// process HALT
	virtual void ProcessHALT() = 0;

// execute
public:
	virtual int GetExecClock() = 0;
	virtual void SetExecClock(int nExecClock) = 0;
	virtual void AddExecClock(int nExecClock) = 0;
	virtual int ExecuteOneOpCode() = 0;

// dis-assemble
public:
	virtual const char* GetMnemonic() const = 0;
	virtual bool IsStepExecuteOpCode() = 0;
	virtual void SetStepExecuteOpCode(bool bStepExecuteOpCode) = 0;
	virtual bool IsStepExecuteOpCode2() = 0;
	virtual void SetStepExecuteOpCode2(bool bStepExecuteOpCode2) = 0;
	virtual void FormatMnemonicV(const char* pszFormat, va_list argList) = 0;
	void FormatMnemonic(const char* pszFormat, ...);
	int DisAssemble();
};

////////////////////////////////////////////////////////////
// TZ80Adapter

template <class TZ80S>
class TZ80Adapter : public CZ80Adapter {
// attribute
protected:
	TZ80S* m_pZ80Substance;

// construct/destruct
public:
	TZ80Adapter(TZ80S* pZ80Substance) :
		m_pZ80Substance(pZ80Substance)
	{
	}
	virtual ~TZ80Adapter() {
	}

// initialize
public:
	virtual void Initialize() {
		m_pZ80Substance->Initialize();
	}
	virtual void Reset() {
		m_pZ80Substance->Reset();
	}

// memory-I/O operation
public:
	virtual uint8_t ReadMemory(int nAddress) {
		return m_pZ80Substance->ReadMemory(nAddress);
	}
	virtual void WriteMemory(int nAddress, uint8_t btData) {
		m_pZ80Substance->WriteMemory(nAddress, btData);
	}
	virtual uint8_t ReadMemoryM1(int nAddress) {
		return m_pZ80Substance->ReadMemoryM1(nAddress);
	}
	virtual uint8_t ReadIO(int nAddress) {
		return m_pZ80Substance->ReadIO(nAddress);
	}
	virtual void WriteIO(int nAddress, uint8_t btData) {
		m_pZ80Substance->WriteIO(nAddress, btData);
	}

// register operation
public:
	// AF register
	virtual URegisterPair& RegAF() {
		return m_pZ80Substance->RegAF();
	}
	// AF2 register
	virtual URegisterPair& RegAF2() {
		return m_pZ80Substance->RegAF2();
	}
	// BC register
	virtual URegisterPair& RegBC() {
		return m_pZ80Substance->RegBC();
	}
	// BC2 register
	virtual URegisterPair& RegBC2() {
		return m_pZ80Substance->RegBC2();
	}
	// DE register
	virtual URegisterPair& RegDE() {
		return m_pZ80Substance->RegDE();
	}
	// DE2 register
	virtual URegisterPair& RegDE2() {
		return m_pZ80Substance->RegDE2();
	}
	// HL register
	virtual URegisterPair& RegHL() {
		return m_pZ80Substance->RegHL();
	}
	// HL2 register
	virtual URegisterPair& RegHL2() {
		return m_pZ80Substance->RegHL2();
	}
	// IX register
	virtual URegisterPair& RegIX() {
		return m_pZ80Substance->RegIX();
	}
	// IY register
	virtual URegisterPair& RegIY() {
		return m_pZ80Substance->RegIY();
	}
	// SP register
	virtual URegisterPair& RegSP() {
		return m_pZ80Substance->RegSP();
	}
	// PC register
	virtual URegisterPair& RegPC() {
		return m_pZ80Substance->RegPC();
	}
	// I register
	virtual uint8_t GetRegI() {
		return m_pZ80Substance->GetRegI();
	}
	virtual void SetRegI(uint8_t btData) {
		m_pZ80Substance->SetRegI(btData);
	}
	// R register
	virtual uint8_t GetRegR() {
		return m_pZ80Substance->GetRegR();
	}
	virtual void SetRegR(uint8_t btData) {
		m_pZ80Substance->SetRegR(btData);
	}
	virtual void IncRegR() {
		m_pZ80Substance->IncRegR();
	}
	// interrupt mode
	virtual int GetInterruptMode() {
		return m_pZ80Substance->GetInterruptMode();
	}
	virtual void SetInterruptMode(int nInterruptMode) {
		m_pZ80Substance->SetInterruptMode(nInterruptMode);
	}
	// interrupt register
	virtual bool IsEnableInterrupt() {
		return m_pZ80Substance->IsEnableInterrupt();
	}
	virtual void SetEnableInterrupt(bool bEnableInterrupt) {
		m_pZ80Substance->SetEnableInterrupt(bEnableInterrupt);
	}
	virtual bool IsEnableInterrupt2() {
		return m_pZ80Substance->IsEnableInterrupt2();
	}
	virtual void SetEnableInterrupt2(bool bEnableInterrupt2) {
		m_pZ80Substance->SetEnableInterrupt2(bEnableInterrupt2);
	}
	virtual bool IsEnableInterruptReserve() {
		return m_pZ80Substance->IsEnableInterruptReserve();
	}
	virtual void SetEnableInterruptReserve(bool bEnableInterruptReserve) {
		m_pZ80Substance->SetEnableInterruptReserve(
			bEnableInterruptReserve);
	}
	// HALT
	virtual bool IsHalting() {
		return m_pZ80Substance->IsHalting();
	}
	virtual void SetHalting(bool bHalting) {
		m_pZ80Substance->SetHalting(bHalting);
	}

// interrupt
public:
	// occurred interrupt
	virtual int DoInterrupt(uint8_t btIntVect) {
		return m_pZ80Substance->DoInterrupt(btIntVect);
	}
	// occurred NMI
	virtual int DoNMInterrupt() {
		return m_pZ80Substance->DoNMInterrupt();
	}
	// RETI
	virtual void FinishInterrupt() {
		m_pZ80Substance->FinishInterrupt();
	}
	// RETN
	virtual void FinishNMInterrupt() {
		m_pZ80Substance->FinishNMInterrupt();
	}

// HALT
public:
	// process HALT
	virtual void ProcessHALT() {
		m_pZ80Substance->ProcessHALT();
	}

// execute
public:
	virtual int GetExecClock() {
		return m_pZ80Substance->GetExecClock();
	}
	virtual void SetExecClock(int nExecClock) {
		m_pZ80Substance->SetExecClock(nExecClock);
	}
	virtual void AddExecClock(int nExecClock) {
		m_pZ80Substance->AddExecClock(nExecClock);
	}
	virtual int ExecuteOneOpCode() {
		return m_pZ80Substance->ExecuteOneOpCode();
	}

// dis-assemble
public:
	virtual const char* GetMnemonic() const {
		return m_pZ80Substance->GetMnemonic();
	}
	virtual bool IsStepExecuteOpCode() {
		return m_pZ80Substance->IsStepExecuteOpCode();
	}
	virtual void SetStepExecuteOpCode(bool bStepExecuteOpCode) {
		m_pZ80Substance->SetStepExecuteOpCode(bStepExecuteOpCode);
	}
	virtual bool IsStepExecuteOpCode2() {
		return m_pZ80Substance->IsStepExecuteOpCode2();
	}
	virtual void SetStepExecuteOpCode2(bool bStepExecuteOpCode2) {
		m_pZ80Substance->SetStepExecuteOpCode2(bStepExecuteOpCode2);
	}
	virtual void FormatMnemonicV(const char* pszFormat, va_list argList) {
		m_pZ80Substance->FormatMnemonicV(pszFormat, argList);
	}
};
#endif // Z80CFG_USE_TEMPLATE

#endif // Z80Adapter_DEFINED
