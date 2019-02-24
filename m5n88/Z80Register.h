////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80Register_DEFINED
#define Z80Register_DEFINED

////////////////////////////////////////////////////////////
// include

#include "Z80Config.h"

////////////////////////////////////////////////////////////
// CRegister

class CRegister {
// attribute
public:
	uint8_t m_bt;

	uint8_t Get() const {
		return m_bt;
	}
	void Set(uint8_t bt) {
		m_bt = bt;
	}
	uint8_t& Ref() {
		return m_bt;
	}

// operation
public:
	// Why don't operator= be permitted in union... (;_;)
	void Copy(const CRegister& regOther) {
		m_bt = regOther.m_bt;
	}
	operator uint8_t&() {
		return m_bt;
	}
	void Swap(CRegister& regOther) {
		uint8_t btTmp = m_bt;
		m_bt = regOther.m_bt;
		regOther.m_bt = btTmp;
	}
};

////////////////////////////////////////////////////////////
// URegisterPair

union URegisterPair {
// attribute
public:
	uint16_t m_w;
	struct {
#ifdef Z80CFG_LITTLE_ENDIAN
		uint8_t m_btLo, m_btHi;
#else // Z80CFG_BIG_ENDIAN
		uint8_t m_btHi, m_btLo;
#endif // Z80CFG_LITTLE/BIG_ENDIAN
	} m_bt;
	struct {
#ifdef Z80CFG_LITTLE_ENDIAN
		CRegister m_regLo, m_regHi;
#else // Z80CFG_BIG_ENDIAN
		CRegister m_regHi, m_regLo;
#endif // Z80CFG_LITTLE/BIG_ENDIAN
	} m_reg;

	uint16_t Get() const {
		return m_w;
	}
	uint8_t GetHi() const {
		return m_bt.m_btHi;
	}
	uint8_t GetLo() const {
		return m_bt.m_btLo;
	}
	void Set(uint16_t w) {
		m_w = w;
	}
	void SetHi(uint8_t btHi) {
		m_bt.m_btHi = btHi;
	}
	void SetLo(uint8_t btLo) {
		m_bt.m_btLo = btLo;
	}
	void Set(uint8_t btHi, uint8_t btLo) {
		m_bt.m_btLo = btLo;
		m_bt.m_btHi = btHi;
	}
	uint16_t& Ref() {
		return m_w;
	}
	uint8_t& RefHi() {
		return m_bt.m_btHi;
	}
	uint8_t& RefLo() {
		return m_bt.m_btLo;
	}
	CRegister& Hi() {
		return m_reg.m_regHi;
	}
	CRegister& Lo() {
		return m_reg.m_regLo;
	}

// operation
public:
	URegisterPair& operator=(const URegisterPair& regpOther) {
		m_w = regpOther.m_w;
		return *this;
	}
	void Copy(const URegisterPair& regpOther) {
		m_w = regpOther.m_w;
	}
	operator uint16_t&() {
		return m_w;
	}
	void Swap(URegisterPair& regpOther) {
		uint16_t wTmp = m_w;
		m_w = regpOther.m_w;
		regpOther.m_w = wTmp;
	}
};

#endif // Z80Register_DEFINED
