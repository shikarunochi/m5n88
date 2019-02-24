////////////////////////////////////////////////////////////
// PC-8801 Sub CPU Emulator
//
// Written by Manuke

#ifndef PC88Z80Sub_DEFINED
#define PC88Z80Sub_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Z80Sub;

////////////////////////////////////////////////////////////
// include

#include "Z80.h"

#include "PC88Ppi.h"
#include "PC88Fdc.h"

////////////////////////////////////////////////////////////
// declaration of CPC88Z80Sub

class CPC88Z80Sub :
	public CZ80_2
{
// typedef
public:
	// type of interrupt vector change callback function
	typedef void (*IntVectChangeCallback)();

// enum
public:
	// fast ROM emulation type
	enum {
		FASTEMULATION_NEGLECT  = 0,
		FASTEMULATION_CONSTANT = 1
	};

// attribute
protected:
	// peripheral
	// PPI
	static CPC88Ppi* m_pPpi;
	// FDC
	static CPC88Fdc* m_pFdc;

	// memory
	// subsystem ROM
	//static uint8_t m_abtSubRom[8192];
	static uint8_t* m_abtSubRom;
	// subsystem RAM
	//static uint8_t m_abtSubRam[16384];
	static uint8_t* m_abtSubRam;

	// dip-switch setting
	// fast ROM emulation
	static bool m_bFastROMEmulation;
	// fast ROM emulation type
	static int m_nFastROMEmulationType;
	// wait emulation
	static bool m_bWaitEmulation;
	// M1 wait
	static bool m_bM1Wait;

	// M1-cycle memory read procedure
	// dummy read(M1)
	static RPROC ReadNONE_M1;
	// subsystem ROM read(M1)
	static RPROC ReadMemorySubRom_M1;
	// subsystem ROM read(bank0 fast ROM emulation / M1)
	static RPROC ReadMemorySubRomB0_FastEmu_M1;
	// subsystem RAM read(M1)
	static RPROC ReadMemorySubRam_M1;

	// CPU freeze
	// CPU freezing
	static bool m_bFreezeCPU;
	// freeze counter
	static int m_nFreezeCounter;

	// interrupt vector change callback function
	static IntVectChangeCallback m_pIntVectChangeCallback;

public:
	// peripheral
	// PPI
	static CPC88Ppi& Ppi() {
		return *m_pPpi;
	}
	// FDC
	static CPC88Fdc& Fdc() {
		return *m_pFdc;
	}

	// memory
	// get subsystem ROM buffer
	static uint8_t* GetSubRomPtr() {
		return m_abtSubRom;
	}
	// get subsystem RAM buffer
	static uint8_t* GetSubRamPtr() {
		return m_abtSubRam;
	}

	// dip-switch setting
	// is fast ROM emulation
	static bool IsFastROMEmulation() {
		return m_bFastROMEmulation;
	}
	// set fast ROM emulation
	static void SetFastROMEmulation(bool bFastROMEmulation) {
		m_bFastROMEmulation = bFastROMEmulation;
		if (!m_bFastROMEmulation) {
			SetReadMemoryM1Proc(0, ReadMemorySubRom_M1);
			SetReadIOProc(0xFE, ReadIO_FE);
		} else {
			if (m_nFastROMEmulationType == FASTEMULATION_NEGLECT) {
				SetReadMemoryM1Proc(0, ReadMemorySubRom_M1);
				SetReadIOProc(0xFE, ReadIO_FE_FastEmu);
			} else if (m_nFastROMEmulationType == FASTEMULATION_CONSTANT) {
				SetReadMemoryM1Proc(0, ReadMemorySubRomB0_FastEmu_M1);
				SetReadIOProc(0xFE, ReadIO_FE);
			}
		}
		if (m_bFreezeCPU) {
			m_bFreezeCPU = false;
			m_nFreezeCounter = 0;
			SetHalting(false);
		}
	}
	// get fast ROM emulation type
	static int GetFastROMEmulationType() {
		return m_nFastROMEmulationType;
	}
	// set fast ROM emulation type
	static void SetFastROMEmulationType(int nFastROMEmulationType) {
		m_nFastROMEmulationType = nFastROMEmulationType;
		SetFastROMEmulation(m_bFastROMEmulation);
	}
	// is wait emulation
	static bool IsWaitEmulation() {
		return m_bWaitEmulation;
	}
	// set wait emulation
	static void SetWaitEmulation(bool bWaitEmulation) {
		m_bWaitEmulation = bWaitEmulation;
	}
	// is M1 wait
	static bool IsM1Wait() {
		return m_bM1Wait;
	}
	// is subsystem ROM supported 2HD
	static bool IsRomType2HD() {
		return m_abtSubRom[0x07EE] == 0xFE;
	}

	// CPU freeze
	// is CPU freezing
	static bool IsFreezeCPU() {
		return m_bFreezeCPU;
	}
	// set CPU freezing
	static void SetFreezeCPU(bool bFreezeCPU) {
		m_bFreezeCPU = bFreezeCPU;
		m_nFreezeCounter = 0;
		SetHalting(m_bFreezeCPU);
	}

	// set interrupt vector change callback function
	static void SetIntVectChangeCallback(
		IntVectChangeCallback pIntVectChangeCallback)
	{
		m_pIntVectChangeCallback = pIntVectChangeCallback;
	}

// create & destroy
public:
	// default constructor
	CPC88Z80Sub();
	// destructor
	virtual ~CPC88Z80Sub();

// initialize
public:
	// set peripheral
	static void SetPeripheral(CPC88Ppi& ppi, CPC88Fdc& fdc) {
		m_pPpi = &ppi;
		m_pFdc = &fdc;
	}
	// initialize at first
	virtual void RamInitialize();
	virtual void Initialize();
	// reset
	virtual void Reset();

// memory operation
protected:
	// dummy read
	static uint8_t ReadNONE(int nAddress);
	// dummy read(Wait)
	static uint8_t ReadNONE_Wait(int nAddress);
	// dummy write
	static void WriteNONE(int nAddress, uint8_t btData);
	// subsystem ROM read
	static uint8_t ReadMemorySubRom(int nAddress);
	// subsystem ROM read(Wait)
	static uint8_t ReadMemorySubRom_Wait(int nAddress);
	// subsystem ROM read(bank0 fast ROM emulation)
	static uint8_t ReadMemorySubRomB0_FastEmu(int nAddress);
	// subsystem ROM read(bank0 fast ROM emulation / wait)
	static uint8_t ReadMemorySubRomB0_FastEmu_Wait(int nAddress);
	// subsystem RAM read
	static uint8_t ReadMemorySubRam(int nAddress);
	// subsystem RAM read(Wait)
	static uint8_t ReadMemorySubRam_Wait(int nAddress);
	// subsystem RAM write
	static void WriteMemorySubRam(int nAddress, uint8_t btData);
	// I/O port F8 read
	static uint8_t ReadIO_F8(int nAddress);
	// I/O port FA read
	static uint8_t ReadIO_FA(int nAddress);
	// I/O port FB read
	static uint8_t ReadIO_FB(int nAddress);
	// I/O port FB write
	static void WriteIO_FB(int nAddress, uint8_t btData);
	// I/O port FC read
	static uint8_t ReadIO_FC(int nAddress);
	// I/O port FC write
	static void WriteIO_FC(int nAddress, uint8_t btData);
	// I/O port FD read
	static uint8_t ReadIO_FD(int nAddress);
	// I/O port FD write
	static void WriteIO_FD(int nAddress, uint8_t btData);
	// I/O port FE read
	static uint8_t ReadIO_FE(int nAddress);
	// I/O port FE read(fast ROM emulation)
	static uint8_t ReadIO_FE_FastEmu(int nAddress);
	// I/O port FE write
	static void WriteIO_FE(int nAddress, uint8_t btData);
	// I/O port FF write
	static void WriteIO_FF(int nAddress, uint8_t btData);

// interrupt
public:
	// occurred interrupt
	virtual int DoInterrupt(uint8_t btIntVect);

// HALT
public:
	// process HALT
	virtual void ProcessHALT();
};

#endif // PC88Z80Sub_DEFINED
