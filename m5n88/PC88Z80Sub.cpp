////////////////////////////////////////////////////////////
// PC-8801 Sub CPU Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Z80Sub.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Z80Sub

////////////////////////////////////////////////////////////
// attribute

// peripheral

// PPI

CPC88Ppi* CPC88Z80Sub::m_pPpi;

// FDC

CPC88Fdc* CPC88Z80Sub::m_pFdc;

// memory

// subsystem ROM

uint8_t* CPC88Z80Sub::m_abtSubRom;

// subsystem RAM

uint8_t* CPC88Z80Sub::m_abtSubRam;

// dip-switch setting

// fast ROM emulation

bool CPC88Z80Sub::m_bFastROMEmulation;

// fast ROM emulation type

int CPC88Z80Sub::m_nFastROMEmulationType;

// wait emulation

bool CPC88Z80Sub::m_bWaitEmulation;

// M1 wait

bool CPC88Z80Sub::m_bM1Wait;

// M1-cycle memory read procedure

// dummy read(M1)

CPC88Z80Sub::RPROC CPC88Z80Sub::ReadNONE_M1;

// subsystem ROM read(M1)

CPC88Z80Sub::RPROC CPC88Z80Sub::ReadMemorySubRom_M1;

// subsystem ROM read(bank0 fast ROM emulation / M1)

CPC88Z80Sub::RPROC CPC88Z80Sub::ReadMemorySubRomB0_FastEmu_M1;

// subsystem RAM read(M1)

CPC88Z80Sub::RPROC CPC88Z80Sub::ReadMemorySubRam_M1;

// CPU freeze

// CPU freezing

bool CPC88Z80Sub::m_bFreezeCPU;

//  freeze counter

int CPC88Z80Sub::m_nFreezeCounter;

// interrupt vector change callback function

CPC88Z80Sub::IntVectChangeCallback CPC88Z80Sub::m_pIntVectChangeCallback;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88Z80Sub::CPC88Z80Sub()  :
	CZ80_2()
{
	m_pIntVectChangeCallback = NULL;
}

// destructor

CPC88Z80Sub::~CPC88Z80Sub() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88Z80Sub::RamInitialize() {
	m_abtSubRom = (uint8_t*)ps_malloc(8192);
	m_abtSubRam = (uint8_t*)ps_malloc(16384);
	Serial.println("SubCPU initialize Memory OK");
}

void CPC88Z80Sub::Initialize() {
	Serial.println("SubCPU initialize");
	CZ80_2::Initialize();
	Serial.println("SubCPU initialize CZ80_2 OK");
	SetFastROMEmulation(true);
	SetFastROMEmulationType(FASTEMULATION_NEGLECT);
	SetWaitEmulation(false);
	SetFreezeCPU(false);
}

// reset

void CPC88Z80Sub::Reset() {
	CZ80_2::Reset();
	// wait check
	if (!IsWaitEmulation()) {
		m_bM1Wait = false;
	} else {
		m_bM1Wait = !IsRomType2HD();
	}
	if (!IsM1Wait()) {
		ReadNONE_M1 = ReadNONE;
		ReadMemorySubRom_M1 = ReadMemorySubRom;
		ReadMemorySubRomB0_FastEmu_M1 = ReadMemorySubRomB0_FastEmu;
		ReadMemorySubRam_M1 = ReadMemorySubRam;
	} else {
		ReadNONE_M1 = ReadNONE_Wait;
		ReadMemorySubRom_M1 = ReadMemorySubRom_Wait;
		ReadMemorySubRomB0_FastEmu_M1 = ReadMemorySubRomB0_FastEmu_Wait;
		ReadMemorySubRam_M1 = ReadMemorySubRam_Wait;
	}
	// memory-I/O read/write table
	int nBlock;
	for (nBlock = 0; nBlock < 16; nBlock++) {
		SetReadMemoryProc(nBlock, ReadNONE);
		SetReadMemoryM1Proc(nBlock, ReadNONE_M1);
		SetWriteMemoryProc(nBlock, WriteNONE);
	}
	SetReadMemoryProc(0, ReadMemorySubRom);
	if (!IsFastROMEmulation() ||
		(GetFastROMEmulationType() != FASTEMULATION_CONSTANT))
	{
		SetReadMemoryM1Proc(0, ReadMemorySubRom_M1);
	} else {
		SetReadMemoryM1Proc(0, ReadMemorySubRomB0_FastEmu_M1);
	}
	SetReadMemoryProc(1, ReadMemorySubRom);
	SetReadMemoryM1Proc(1, ReadMemorySubRom_M1);
	SetReadMemoryProc(4, ReadMemorySubRam);
	SetReadMemoryM1Proc(4, ReadMemorySubRam_M1);
	SetWriteMemoryProc(4, WriteMemorySubRam);
	SetReadMemoryProc(5, ReadMemorySubRam);
	SetReadMemoryM1Proc(5, ReadMemorySubRam_M1);
	SetWriteMemoryProc(5, WriteMemorySubRam);
	SetReadMemoryProc(6, ReadMemorySubRam);
	SetReadMemoryM1Proc(6, ReadMemorySubRam_M1);
	SetWriteMemoryProc(6, WriteMemorySubRam);
	SetReadMemoryProc(7, ReadMemorySubRam);
	SetReadMemoryM1Proc(7, ReadMemorySubRam_M1);
	SetWriteMemoryProc(7, WriteMemorySubRam);
	for (nBlock = 0; nBlock < 256; nBlock++) {
		SetReadIOProc(nBlock, ReadNONE);
		SetWriteIOProc(nBlock, WriteNONE);
	}
	SetReadIOProc(0xF8, ReadIO_F8);
	SetReadIOProc(0xFA, ReadIO_FA);
	SetReadIOProc(0xFB, ReadIO_FB);
	SetWriteIOProc(0xFB, WriteIO_FB);
	SetReadIOProc(0xFC, ReadIO_FC);
	SetWriteIOProc(0xFC, WriteIO_FC);
	SetReadIOProc(0xFD, ReadIO_FD);
	SetWriteIOProc(0xFD, WriteIO_FD);
	if (!IsFastROMEmulation() ||
		(GetFastROMEmulationType() != FASTEMULATION_NEGLECT))
	{
		SetReadIOProc(0xFE, ReadIO_FE);
	} else {
		SetReadIOProc(0xFE, ReadIO_FE_FastEmu);
	}
	SetWriteIOProc(0xFE, WriteIO_FE);
	SetWriteIOProc(0xFF, WriteIO_FF);
	// CPU freeze
	SetFreezeCPU(false);
}

////////////////////////////////////////////////////////////
// memory operation

// dummy read

uint8_t CPC88Z80Sub::ReadNONE(int /*nAddress*/) {
	return 0xFF;
}

// dummy read(Wait)

uint8_t CPC88Z80Sub::ReadNONE_Wait(int /*nAddress*/) {
	AddExecClock(1);
	return 0xFF;
}

// dummy write

void CPC88Z80Sub::WriteNONE(int /*nAddress*/, uint8_t /*btData*/) {
}

// subsystem ROM read

uint8_t CPC88Z80Sub::ReadMemorySubRom(int nAddress) {
	return m_abtSubRom[nAddress & 0x1FFF];
}

// subsystem ROM read(Wait)

uint8_t CPC88Z80Sub::ReadMemorySubRom_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtSubRom[nAddress & 0x1FFF];
}

// subsystem ROM read(bank0 fast ROM emulation)

uint8_t CPC88Z80Sub::ReadMemorySubRomB0_FastEmu(int nAddress) {
	if (nAddress == 0x00CC) {
		if ((Ppi().ReadPortC(CPC88Ppi::SIDE_SUB) & 0x08) == 0) {
			SetFreezeCPU(true);
			return 0x76;
		} else {
			SetFreezeCPU(false);
		}
	}
	return m_abtSubRom[nAddress & 0x1FFF];
}

// subsystem ROM read(bank0 fast ROM emulation / wait)

uint8_t CPC88Z80Sub::ReadMemorySubRomB0_FastEmu_Wait(int nAddress) {
	AddExecClock(1);
	if (nAddress == 0x00CC) {
		if ((Ppi().ReadPortC(CPC88Ppi::SIDE_SUB) & 0x08) == 0) {
			SetFreezeCPU(true);
			return 0x76;
		} else {
			SetFreezeCPU(false);
		}
	}
	return m_abtSubRom[nAddress & 0x1FFF];
}

// subsystem RAM read

uint8_t CPC88Z80Sub::ReadMemorySubRam(int nAddress) {
	return m_abtSubRam[nAddress & 0x3FFF];
}

// subsystem RAM read(Wait)

uint8_t CPC88Z80Sub::ReadMemorySubRam_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtSubRam[nAddress & 0x3FFF];
}

// subsystem RAM write

void CPC88Z80Sub::WriteMemorySubRam(int nAddress, uint8_t btData) {
	m_abtSubRam[nAddress & 0x3FFF] = btData;
}

// I/O port F8 read

uint8_t CPC88Z80Sub::ReadIO_F8(int /*nAddress*/) {
	Fdc().TerminalCount();
	return 0;
}

// I/O port FA read

uint8_t CPC88Z80Sub::ReadIO_FA(int /*nAddress*/) {
	return Fdc().ReadStatusReg();
}

// I/O port FB read

uint8_t CPC88Z80Sub::ReadIO_FB(int /*nAddress*/) {
	return Fdc().ReadDataReg();
}

// I/O port FB write

void CPC88Z80Sub::WriteIO_FB(int /*nAddress*/, uint8_t btData) {
	Fdc().WriteDataReg(btData);
}

// I/O port FC read

uint8_t CPC88Z80Sub::ReadIO_FC(int /*nAddress*/) {
	return Ppi().ReadPortA(CPC88Ppi::SIDE_SUB);
}

// I/O port FC write

void CPC88Z80Sub::WriteIO_FC(int /*nAddress*/, uint8_t btData) {
	Ppi().WritePortA(CPC88Ppi::SIDE_SUB, btData);
}

// I/O port FD read

uint8_t CPC88Z80Sub::ReadIO_FD(int /*nAddress*/) {
	return Ppi().ReadPortB(CPC88Ppi::SIDE_SUB);
}

// I/O port FD write

void CPC88Z80Sub::WriteIO_FD(int /*nAddress*/, uint8_t btData) {
	Ppi().WritePortB(CPC88Ppi::SIDE_SUB, btData);
}

// I/O port FE read

uint8_t CPC88Z80Sub::ReadIO_FE(int /*nAddress*/) {
	return Ppi().ReadPortC(CPC88Ppi::SIDE_SUB);
}

// I/O port FE read(fast ROM emulation)

uint8_t CPC88Z80Sub::ReadIO_FE_FastEmu(int /*nAddress*/) {
	if (Ppi().IsUpdate()) {
		Ppi().SetUpdate(false);
		SetFreezeCPU(false);
	} else {
		if (++m_nFreezeCounter >= 256) {
			m_bFreezeCPU = true;
		}
	}
	return Ppi().ReadPortC(CPC88Ppi::SIDE_SUB);
}

// I/O port FE write

void CPC88Z80Sub::WriteIO_FE(int /*nAddress*/, uint8_t btData) {
	Ppi().WritePortC(CPC88Ppi::SIDE_SUB, btData);
}

// I/O port FF write

void CPC88Z80Sub::WriteIO_FF(int /*nAddress*/, uint8_t btData) {
	Ppi().WriteCommand(CPC88Ppi::SIDE_SUB, btData);
}

////////////////////////////////////////////////////////////
// interrupt

// occurred interrupt

int CPC88Z80Sub::DoInterrupt(uint8_t btIntVect) {
	Fdc().SetFdcInterruptRequest(false);
	m_pIntVectChangeCallback();
	return CZ80_2::DoInterrupt(btIntVect);
}

////////////////////////////////////////////////////////////
// HALF

// process HALT

void CPC88Z80Sub::ProcessHALT() {
	CZ80_2::ProcessHALT();
	if (!IsFreezeCPU()) {
		if (!Fdc().IsFdcInterruptRequest() &&
			(Fdc().GetInterruptWait() <= 0))
		{
			AddExecClock(DoInterrupt(0x00)+Fdc().GetInterruptDelay());
		}
	}
}
