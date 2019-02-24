////////////////////////////////////////////////////////////
// PC-8801 Emulator
//
// Written by Manuke
//
// Assisted by apaslothy
// (PC-8001mkII/SR,PCG-8800,InternationalMode Support)

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88.h"

////////////////////////////////////////////////////////////
// implementation of CPC88

////////////////////////////////////////////////////////////
// attribute

// CPU/peripheral

// main CPU

CPC88Z80Main CPC88::m_z80Main;

// sub CPU

CPC88Z80Sub CPC88::m_z80Sub;

// timer

CPC88Timer CPC88::m_timer;

// CRTC

CPC88Crtc CPC88::m_crtc;

// USART

CPC88Usart CPC88::m_usart;

// calendar clock

CPC88Calendar CPC88::m_calendar;

// OPNA

CPC88Opna CPC88::m_opna;

// PPI

CPC88Ppi CPC88::m_ppi;

// FDC

CPC88Fdc CPC88::m_fdc;

// PCG

CPC88Pcg CPC88::m_pcg;

// dip-switch setting

// fast ROM emulation

bool CPC88::m_bFastROMEmulation;

// BASIC mode

int CPC88::m_nBasicMode;

// hi-speed mode

bool CPC88::m_bHighSpeedMode;

// base clock

int CPC88::m_nBaseClock;

// sub CPU disable

bool CPC88::m_bSubSystemDisable;

// execute multi OP code at once

bool CPC88::m_bMultiOpCode;

// hi-resolution mode

bool CPC88::m_bHiresolution;

// wait emulation

bool CPC88::m_bWaitEmulation;

// old-machine compatible mode

bool CPC88::m_bOldCompatible;

// PCG enable

bool CPC88::m_bPcgEnable;

// international display mode

bool CPC88::m_bOptionFont;

// debug

// debug execute mode

int CPC88::m_nDebugExecMode;

// debug stopped

bool CPC88::m_bDebugStopped;

// backup of fast ROM emulation mode

bool CPC88::m_bFastROMEmulationBackup;

// debug program-counter

uint16_t CPC88::m_wDebugPC;

// debug program-counter(next command)

uint16_t CPC88::m_wDebugPCNext;

// temporary break point at interrupt trace

uint16_t CPC88::m_wDebugPCTraceInt;

// temporary break point at step wait

uint16_t CPC88::m_wDebugPCStepWait;

// executable step next OP code

bool CPC88::m_bDebugStepExecuteOpCode;

// executable step2 next OP code

bool CPC88::m_bDebugStepExecuteOpCode2;

// step execute mode

int CPC88::m_nDebugStepMode;

// interrupt tracing

bool CPC88::m_bDebugTraceInt;

// temporary break point at interrupt trace registered

bool CPC88::m_bDebugTraceIntBreakPoint;

// step waiting

bool CPC88::m_bDebugStepWait;

// temporary break point at step wait registered

bool CPC88::m_bDebugStepWaitBreakPoint;

// mnemonic updated

bool CPC88::m_bMnemonicUpdated;

// main/sub CPU break point

std::set<uint16_t> CPC88::m_setBreakPoint[2];

// other

// interrupt vector

int CPC88::m_nIntVect;

// main CPU left clock

int CPC88::m_nLeftClock;

// sub CPU left clock

int CPC88::m_nLeftClockSub;

// disk image collection

CDiskImageCollection CPC88::m_dicDisks;

// Output Debug Log Callback function

CPC88::OutputDebugLogCallback CPC88::m_pOutputDebugLogCallback;

// system file open callback function

CPC88::SysFileOpenCallback CPC88::m_pSysFileOpenCallback;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88::CPC88() {
}

// destructor

CPC88::~CPC88() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88::Initialize() {
	Serial.println("RamInitail");
	Z80Main().RamInitialize();
	Z80Sub().RamInitialize();
	Serial.println("RamInitail End");
	File fpt;
	bool bExistNBasic = false;
	fpt = SysFileOpen("pc88.rom");
	if (fpt.available()) {
		Serial.println("Open ROM1");
		bExistNBasic = true;
		FileRead(Z80Main().GetN88BasicRomPtr(), 0x8000, fpt);
		FileRead(Z80Main().GetNBasicRomPtr()+0x6000, 0x2000, fpt);
		//fseek(fpt, 0x2000, SEEK_CUR);
		for(int index = 0;index < 0x2000;index++){
			fpt.read();
		}
		FileRead(Z80Main().GetIERomPtr(0), 0x2000, fpt);
		FileRead(Z80Main().GetIERomPtr(1), 0x2000, fpt);
		FileRead(Z80Main().GetIERomPtr(2), 0x2000, fpt);
		FileRead(Z80Main().GetIERomPtr(3), 0x2000, fpt);
		FileRead(Z80Sub().GetSubRomPtr(), 0x2000, fpt);
		FileRead(Z80Main().GetNBasicRomPtr(), 0x6000, fpt);
		fpt.close();
	} else {
		fpt = SysFileOpen("n88.rom");
		if(fpt.available()==false){
			fpt = SysFileOpen("8801-n88.rom");
		}
		if(fpt.available()){
			FileRead(Z80Main().GetN88BasicRomPtr(), 0x8000, fpt);
			fpt.close();
		}
		fpt = SysFileOpen("n80.rom");
		if(fpt.available()==false){
			fpt = SysFileOpen("8801-n80.rom");
		}
		if(fpt.available())
		{
			bExistNBasic = true;
			FileRead(Z80Main().GetNBasicRomPtr(), 0x8000, fpt);
			fpt.close();
		}
		fpt = SysFileOpen("n88_0.rom");
		if(fpt.available()==false){
			fpt = SysFileOpen("8801-4th.rom");
		}
		if(fpt.available())
		{
			FileRead(Z80Main().GetIERomPtr(0), 0x2000, fpt);
			fpt.close();
		}
		fpt = SysFileOpen("n88_1.rom");
		if(fpt.available()){
			FileRead(Z80Main().GetIERomPtr(1), 0x2000, fpt);
			fpt.close();
		}
		fpt = SysFileOpen("n88_2.rom");
		if(fpt.available()){
			FileRead(Z80Main().GetIERomPtr(2), 0x2000, fpt);
			fpt.close();
		}
		fpt = SysFileOpen("n88_3.rom");
		if(fpt.available()){
			FileRead(Z80Main().GetIERomPtr(3), 0x2000, fpt);
			fpt.close();
		}
		fpt = SysFileOpen("disk.rom");
		if(fpt.available()){
			FileRead(Z80Sub().GetSubRomPtr(), 0x2000, fpt);
			fpt.close();
		}
	}
	fpt = SysFileOpen("n80_2.rom");
	if(fpt.available()){
		FileRead(Z80Main().GetN80BasicRomPtr(), 0x8000, fpt);
		fpt.close();
		if (!bExistNBasic) {
			memcpy(
				Z80Main().GetNBasicRomPtr(),
				Z80Main().GetN80BasicRomPtr(),
				0x6000);
		}
	}
	fpt = SysFileOpen("e8.rom");
	if(fpt.available()){
		FileRead(Z80Main().GetN80Basic4thRomPtr(), 0x2000, fpt);
		fpt.close();
	}
	fpt = SysFileOpen("n80_3.rom");
	if(fpt.available()){
		FileRead(Z80Main().GetN80V2BasicRomPtr(), 0x8000, fpt);
		FileRead(Z80Main().GetN80V2IERomPtr(), 0x2000, fpt);
		fpt.close();
	}
	bool kanjiEnable = false;
	fpt = SysFileOpen("kanji1.rom");
	if(fpt.available()){
		FileRead(Z80Main().GetKanjiRomPtr(0), 0x20000, fpt);
		kanjiEnable = true;
		fpt.close();
	} else {
		fpt = SysFileOpen("pc88.fnt");
		if(fpt.available()==false){
			fpt = SysFileOpen("font.rom");
		}
		if(fpt.available())
		{
			FileRead(Z80Main().GetKanjiRomPtr(0)+0x1000, 0x800, fpt);
			FileRead(Z80Main().GetKanjiRomPtr(0), 0x1000, fpt);
			fpt.close();
			kanjiEnable = true;
			memset(Z80Main().GetKanjiRomPtr(0)+0x1800, 0xFF, 0x20000-0x1800);
		} else {
			fpt = SysFileOpen("pc-8801.fon");
			if(fpt.available()){
				FileRead(Z80Main().GetKanjiRomPtr(0)+0x1000, 0x800, fpt);
				fpt.close();
				kanjiEnable = true;
				memset(Z80Main().GetKanjiRomPtr(0), 0x00, 0x1000);
				memset(Z80Main().GetKanjiRomPtr(0)+0x1800, 0xFF, 0x20000-0x1800);
			}
		}
	}
	if(kanjiEnable == false){
		memset(Z80Main().GetKanjiRomPtr(0), 0xFF, 0x20000);
		memset(Z80Main().GetKanjiRomPtr(0)+0x1000, 0x00, 8);
		memset(Z80Main().GetKanjiRomPtr(0)+0x1100, 0x00, 8);
	}
	memset(Z80Main().GetKanjiRomPtr(0)+0x1300, 0x00, 8);
	memset(Z80Main().GetKanjiRomPtr(0)+0x17E0, 0x00, 8);
	fpt = SysFileOpen("kanji2.rom");
	if(fpt.available()){
		FileRead(Z80Main().GetKanjiRomPtr(1), 0x20000, fpt);
		fpt.close();
	} else {
		memset(Z80Main().GetKanjiRomPtr(1), 0xFF, 0x20000);
	}
	int i;
	for (i = 0; i < 4; i++) {
		memcpy(
			Z80Main().GetFont80SRRomPtr()+i*0x800, 
			Z80Main().GetKanjiRomPtr(0)+0x1000,
			0x800);
	}
	fpt = SysFileOpen("font80sr.rom");
	if(fpt.available()){
		FileRead(Z80Main().GetFont80SRRomPtr(), 0x2000, fpt);
		fpt.close();
	} else {
		fpt = SysFileOpen("hirafont.rom");
		if(fpt.available()){
			FileRead(Z80Main().GetFont80SRRomPtr() + 0x0d00, 0x200, fpt);
			fpt.close();
		}
	}
	memcpy(Z80Main().GetOptionFontRomPtr(),
		Z80Main().GetKanjiRomPtr(0)+0x1000,
		0x800);
	fpt = SysFileOpen("optfont.rom");
	if(fpt.available()){
		uint8_t abtTemp[0x800];
		FileRead(abtTemp, 0x800, fpt);
		fpt.close();
		uint8_t *pbtOptionRom = Z80Main().GetOptionFontRomPtr();
		for (int nCode = 0; nCode < 256; nCode++) {
			for (int y = 0; y < 8; y++) {
				if (abtTemp[nCode*8+y] != 0) {
					for (int y1 = 0; y1 < 8; y1++) {
						pbtOptionRom[nCode*8+y1] = abtTemp[nCode*8+y1];
					}
					break;
				}
			}
		}
	}

Serial.println("ROM Read End!");

	Z80Main().SetPeripheral(
		Timer(), Crtc(), Usart(), Calendar(), Opna(), Ppi(), Pcg());
	Z80Sub().SetPeripheral(Ppi(), Fdc());
	Z80Main().SetIntVectChangeCallback(IntVectChangeMain);
	Z80Sub().SetIntVectChangeCallback(IntVectChangeSub);
	Timer().SetIntVectChangeCallback(IntVectChangeMain);
	Crtc().SetIntVectChangeCallback(IntVectChangeMain);
	Usart().SetIntVectChangeCallback(IntVectChangeMain);
	Opna().SetIntVectChangeCallback(IntVectChangeMain);
	Ppi().SetATNActivateCallback(PpiATNActivate);
	Fdc().SetIntVectChangeCallback(IntVectChangeSub);
	Pcg().SetCurTextFontRomGetCallback(PcgCurTextFontRomGet);

	Z80Main().Initialize();
	Z80Sub().Initialize();

	Timer().Initialize();
	Crtc().Initialize();
	Usart().Initialize();
	Calendar().Initialize();
	Opna().Initialize();
	Ppi().Initialize();
	Fdc().Initialize();
	Pcg().Initialize();
	m_bFastROMEmulation = true;
	//m_bFastROMEmulation = false;
	//m_nBasicMode = CPC88Z80Main::BASICMODE_N88V2;
	m_nBasicMode = CPC88Z80Main::BASICMODE_N88V1;
	//m_nBasicMode = CPC88Z80Main::BASICMODE_N;
	m_bHighSpeedMode = true;
	//m_bHighSpeedMode = false;
	m_nBaseClock = 4;
	m_bSubSystemDisable = false;
	m_bMultiOpCode = true;
	//m_bMultiOpCode = false;
	m_bHiresolution = true;
	m_bWaitEmulation = false;
	m_bOldCompatible = false;
	m_bPcgEnable = false;
	m_bOptionFont = false;
	m_nIntVect = -1;
	m_nDebugExecMode = DEBUGEXEC_NONE;
	m_bDebugStopped = true;
	m_bFastROMEmulationBackup = true;
	m_wDebugPC = m_wDebugPCNext = 0;
	m_wDebugPCTraceInt = m_wDebugPCStepWait = 0;
	m_bDebugStepExecuteOpCode = m_bDebugStepExecuteOpCode2 = false;
	m_nDebugStepMode = DEBUGSTEP_TRACE;
	m_bDebugTraceInt = m_bDebugTraceIntBreakPoint = false;
	m_bDebugStepWait = m_bDebugStepWaitBreakPoint = false;
	m_bMnemonicUpdated = true;
	for (i = 0; i < 2; i++) {
		m_setBreakPoint[i].clear();
	}
}

// reset

void CPC88::Reset() {
	Serial.println("CPC88::Reset!");
	m_bSubSystemDisable = (m_dicDisks.size() <= 0);
	Z80Main().SetFastROMEmulation(m_bFastROMEmulation);
	Z80Main().SetWaitEmulation(m_bWaitEmulation);
	Z80Main().SetOldCompatible(m_bOldCompatible);
	Z80Main().SetPcgEnable(m_bPcgEnable);
	Z80Main().SetOptionFont(m_bOptionFont);
	Z80Main().SetBasicMode(m_nBasicMode);
	Z80Main().SetHighSpeedMode(m_bHighSpeedMode);
	Z80Main().SetBaseClock(m_nBaseClock);
	Z80Main().SetBootWidth40(false);
	Z80Main().SetBootHeight20(false);
	Z80Main().SetSubSystemDisable(m_bSubSystemDisable);

	Z80Main().Reset();

	Z80Sub().SetFastROMEmulation(m_bFastROMEmulation);
	Z80Sub().SetWaitEmulation(m_bWaitEmulation);
	Z80Sub().Reset();
	Timer().SetBaseClock(m_nBaseClock);
	Timer().Reset();
	Crtc().SetHiresolution(m_bHiresolution);
	Crtc().SetBaseClock(m_nBaseClock);
	Crtc().SetTVRamWait(Z80Main().IsTVRamWait());
	Crtc().SetWaitOnDMA(Z80Main().IsAlwaysMemWait());
	Crtc().SetGVRamWait(Z80Main().IsGVRamWait());
	Crtc().Reset();
	Usart().SetBaseClock(m_nBaseClock);
	Usart().Reset();
	Calendar().SetBaseClock(m_nBaseClock);
	Calendar().Reset();
	Opna().SetBaseClock(m_nBaseClock);
	Opna().Reset();
	Ppi().Reset();
	Fdc().Reset();
	//Pcg().Reset();
	m_nLeftClock = m_nLeftClockSub = 0;
	m_nIntVect = -1;
	IntVectChangeMain();
	IntVectChangeSub();
	if (IsDebugMode() && IsDebugStopped()) {
		UpdateMnemonic();
	}
}

// load memory image

void CPC88::LoadMemoryImage(const std::string& fstrFileName) {
	File fpt;
	fpt = SD.open("/memoryImage");//TODO
	if (fpt.available()) {
		uint8_t abtBuffer[0x7F40];
		FileRead(abtBuffer, sizeof(abtBuffer), fpt);
		fpt.close();
		SetBasicMode(CPC88Z80Main::BASICMODE_N);
		SetHighSpeedMode(false);
		Reset();
		int nAddress;
		for (nAddress = 0x8000; nAddress < 0xFF40; nAddress++) {
			Z80Main().WriteMemory(uint16_t(nAddress), abtBuffer[nAddress-0x8000]);
		}
		for (; nAddress < 0x10000; nAddress++) {
			Z80Main().WriteMemory(uint16_t(nAddress), 0x00);
		}
		Crtc().SetWidth80(false);
		Crtc().SetDMAStarted(true);
		Crtc().SetGraphicDisplayEnable(false);
		Crtc().WriteCommand(0x00);
		Crtc().WriteParam(0xCE);
		Crtc().WriteParam(0x93);
		Crtc().WriteParam(0x73);
		Crtc().WriteParam(0x38);
		Crtc().WriteParam(0x13);
		Crtc().WriteCommand(0x43);
		Crtc().WriteCommand(0x20);
		Z80Main().SetGraphicDisplayEnable(false);
		Z80Main().SetInterruptMode(2);
		Z80Main().RegHL().Set((uint16_t)Z80Main().ReadMemoryW(0xEA63));
		Z80Main().RegSP().Set((uint16_t)Z80Main().ReadMemoryW(0xFF3E));
		Z80Main().RegPC().Set(0xFF3D);
	}
}

// read from file
bool CPC88::FileRead(uint8_t* pbtBuf, size_t nSize, File fpt) {
	int offset = 0;
	Serial.print("nSize:");
	Serial.println(nSize);
	while (fpt.available()) {
      *(pbtBuf + offset) = fpt.read();
      offset++;
	  //Serial.print(offset);
	  if(offset >= nSize){
		  return true;
	  }
 	}
	return false;
	//return fread(pbtBuf, nSize, 1, fpt) != 1;
}

////////////////////////////////////////////////////////////
// execute

// change main CPU interrupt vector

void CPC88::IntVectChangeMain() {
	m_nIntVect = -1;
	if (Usart().IsReceiveInterruptRequest()) {
		if (!Z80Main().IsUsartInterruptMask() &&
			(Z80Main().IsPriorityInterrupt() ||
				(Z80Main().GetInterruptLevel() > 0)))
		{
			m_nIntVect = 0*2;
		}
	}
	if ((m_nIntVect < 0) &&
		Crtc().IsVSyncInterruptRequest())
	{
		if (!Z80Main().IsVSyncInterruptMask() &&
			(Z80Main().IsPriorityInterrupt() ||
				(Z80Main().GetInterruptLevel() > 1)))
		{
			m_nIntVect = 1*2;
		}
	}
	if ((m_nIntVect < 0) &&
		Timer().IsTimerInterruptRequest())
	{
		if (!Z80Main().IsTimerInterruptMask() &&
			(Z80Main().IsPriorityInterrupt() ||
				(Z80Main().GetInterruptLevel() > 2)))
		{
			m_nIntVect = 2*2;
		}
	}
	if ((m_nIntVect < 0) &&
		Opna().IsOpnaInterruptRequest())
	{
		if (!Z80Main().IsPsgInterruptMask() &&
			(Z80Main().IsPriorityInterrupt() ||
				(Z80Main().GetInterruptLevel() > 4)))
		{
			m_nIntVect = 4*2;
		}
	}
	Z80Main().SetIntVect(m_nIntVect);
}

// change sub CPU interrupt vector

void CPC88::IntVectChangeSub() {
	Z80Sub().SetIntVect(Fdc().IsFdcInterruptRequest()? 0*2: -1);
}

// PPI:ATN activate
//     (cancel sub CPU freezing)

void CPC88::PpiATNActivate() {
	if (Z80Sub().IsFreezeCPU()) {
		Z80Sub().SetFreezeCPU(false);
	}
}

// PCG:current text font ROM get

uint8_t CPC88::PcgCurTextFontRomGet(int nAddress) {
	return Z80Main().GetCurTextFontRom(nAddress);
}

// execute 1CPU

void CPC88::Execute1CPU(int nExecuteClock) {
	int nLeftClock = nExecuteClock+m_nLeftClock;
	while (nLeftClock > 0) {
		nLeftClock -= ExecuteOneOpCodeMain();
	}
	m_nLeftClock = nLeftClock;
}

// execute 2CPU

void CPC88::Execute2CPU(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	while (m_nLeftClock > 0) {
		int nClock = ExecuteOneOpCodeMain();
		m_nLeftClock -= nClock;
		m_nLeftClockSub += nClock;
		if (!Z80Sub().IsFreezeCPU()) {
			while (m_nLeftClockSub > 0) {
				m_nLeftClockSub -= ExecuteOneOpCodeSub();
			}
		} else {
			m_nLeftClockSub = 0;
		}
	}
}

// execute 2CPU(8MHz mode)

void CPC88::Execute2CPU8M(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	while (m_nLeftClock > 0) {
		int nClock = ExecuteOneOpCodeMain();
		m_nLeftClock -= nClock;
		m_nLeftClockSub += nClock;
		if (!Z80Sub().IsFreezeCPU()) {
			while (m_nLeftClockSub > 0) {
				m_nLeftClockSub -= ExecuteOneOpCodeSub()*2;
			}
		} else {
			m_nLeftClockSub = 0;
		}
	}
}

// execute 1CPU(multi OP code)

void CPC88::Execute1CPUMulti(int nExecuteClock) {
	int nLeftClock = nExecuteClock+m_nLeftClock;
	while (nLeftClock > 0) {
		nLeftClock -= ExecuteMultiOpCodeMain();
	}
	m_nLeftClock = nLeftClock;
}

// execute 2CPU(multi OP code)

void CPC88::Execute2CPUMulti(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	while (m_nLeftClock > 0) {
		int nClock;
		if (Z80Sub().IsFreezeCPU()) {
			nClock = ExecuteMultiOpCodeMain();
			m_nLeftClock -= nClock;
			m_nLeftClockSub = 0;
		} else {
			int nOpCodeCount = MULTI_OP_CODE_COUNT;
			do {
				//Serial.println("Execute2CPUMulti:2");
				nClock = ExecuteOneOpCodeMain();
				m_nLeftClock -= nClock;
				m_nLeftClockSub += nClock;
				while (m_nLeftClockSub > 0) {
					//Serial.println("Execute2CPUMulti:2Sub");
					m_nLeftClockSub -= ExecuteOneOpCodeSub();
				}
				//Serial.println("Execute2CPUMulti:2SubEnd");
			} while (--nOpCodeCount > 0);
			//Serial.println("Execute2CPUMulti:2-END");
		}
	}
}

// execute 2CPU(multi OP code / 8MHz mode)

void CPC88::Execute2CPUMulti8M(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	while (m_nLeftClock > 0) {
		int nClock;
		if (Z80Sub().IsFreezeCPU()) {
			nClock = ExecuteMultiOpCodeMain();
			m_nLeftClock -= nClock;
			m_nLeftClockSub = 0;
		} else {
			int nOpCodeCount = MULTI_OP_CODE_COUNT;
			do {
				nClock = ExecuteOneOpCodeMain();
				m_nLeftClock -= nClock;
				m_nLeftClockSub += nClock;
				while (m_nLeftClockSub > 0) {
					m_nLeftClockSub -= ExecuteOneOpCodeSub()*2;
				}
			} while (--nOpCodeCount > 0);
		}
	}
}

// execute 1CPU(VRAM wait)

void CPC88::Execute1CPUVWait(int nExecuteClock) {
	int nLeftClock = nExecuteClock+m_nLeftClock;
	while (nLeftClock > 0) {
		nLeftClock -= ExecuteOneOpCodeMainVWait();
	}
	m_nLeftClock = nLeftClock;
}

// execute 2CPU(VRAM wait)

void CPC88::Execute2CPUVWait(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	while (m_nLeftClock > 0) {
		int nClock = ExecuteOneOpCodeMainVWait();
		m_nLeftClock -= nClock;
		m_nLeftClockSub += nClock;
		if (!Z80Sub().IsFreezeCPU()) {
			while (m_nLeftClockSub > 0) {
				m_nLeftClockSub -= ExecuteOneOpCodeSub();
			}
		} else {
			m_nLeftClockSub = 0;
		}
	}
}

// execute 2CPU(8MHz mode / VRAM wait)

void CPC88::Execute2CPU8MVWait(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	while (m_nLeftClock > 0) {
		int nClock = ExecuteOneOpCodeMainVWait();
		m_nLeftClock -= nClock;
		m_nLeftClockSub += nClock;
		if (!Z80Sub().IsFreezeCPU()) {
			while (m_nLeftClockSub > 0) {
				m_nLeftClockSub -= ExecuteOneOpCodeSub()*2;
			}
		} else {
			m_nLeftClockSub = 0;
		}
	}
}

// execute 1CPU(multi OP code / VRAM wait)

void CPC88::Execute1CPUMultiVWait(int nExecuteClock) {
	int nLeftClock = nExecuteClock+m_nLeftClock;
	while (nLeftClock > 0) {
		nLeftClock -= ExecuteMultiOpCodeMainVWait();
	}
	m_nLeftClock = nLeftClock;
}

// execute 2CPU(multi OP code / VRAM wait)

void CPC88::Execute2CPUMultiVWait(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	while (m_nLeftClock > 0) {
		int nClock;
		if (Z80Sub().IsFreezeCPU()) {
			nClock = ExecuteMultiOpCodeMainVWait();
			m_nLeftClock -= nClock;
			m_nLeftClockSub = 0;
		} else {
			int nOpCodeCount = MULTI_OP_CODE_COUNT;
			do {
				nClock = ExecuteOneOpCodeMainVWait();
				m_nLeftClock -= nClock;
				m_nLeftClockSub += nClock;
				while (m_nLeftClockSub > 0) {
					m_nLeftClockSub -= ExecuteOneOpCodeSub();
				}
			} while (--nOpCodeCount > 0);
		}
	}
}

// execute 2CPU(multi OP code / 8MHz mode / VRAM wait)

void CPC88::Execute2CPUMulti8MVWait(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	while (m_nLeftClock > 0) {
		int nClock;
		if (Z80Sub().IsFreezeCPU()) {
			nClock = ExecuteMultiOpCodeMainVWait();
			m_nLeftClock -= nClock;
			m_nLeftClockSub = 0;
		} else {
			int nOpCodeCount = MULTI_OP_CODE_COUNT;
			do {
				nClock = ExecuteOneOpCodeMainVWait();
				m_nLeftClock -= nClock;
				m_nLeftClockSub += nClock;
				while (m_nLeftClockSub > 0) {
					m_nLeftClockSub -= ExecuteOneOpCodeSub()*2;
				}
			} while (--nOpCodeCount > 0);
		}
	}
}

// execute

void CPC88::Execute(int nExecuteClock) {
	//Serial.println("CPC88::Execute 1");
	if (!Crtc().IsVRamWait()) {
		if (!m_bMultiOpCode) {
			if (Z80Main().IsSubSystemDisable()) {
				//Serial.println("CPC88::Execute 2");
				Execute1CPU(nExecuteClock);
			} else if (Z80Main().GetBaseClock() != 8) {
				//Serial.println("CPC88::Execute 3");
				Execute2CPU(nExecuteClock);
			} else {
				//Serial.println("CPC88::Execute 4");
				Execute2CPU8M(nExecuteClock);
			}
		} else {
			if (Z80Main().IsSubSystemDisable()) {
				//Serial.println("CPC88::Execute 5");
				Execute1CPUMulti(nExecuteClock);
			} else if (Z80Main().GetBaseClock() != 8) {
				//Serial.println("CPC88::Execute 6");
				Execute2CPUMulti(nExecuteClock);
			} else {
				//Serial.println("CPC88::Execute 7");
				Execute2CPUMulti8M(nExecuteClock);
			}
		}
	} else {
		if (!m_bMultiOpCode) {
			if (Z80Main().IsSubSystemDisable()) {
				//Serial.println("CPC88::Execute 8");
				Execute1CPUVWait(nExecuteClock);
			} else if (Z80Main().GetBaseClock() != 8) {
				//Serial.println("CPC88::Execute 9");
				Execute2CPUVWait(nExecuteClock);
			} else {
				//Serial.println("CPC88::Execute 10");
				Execute2CPU8MVWait(nExecuteClock);
			}
		} else {
			if (Z80Main().IsSubSystemDisable()) {
				//Serial.println("CPC88::Execute 11");
				Execute1CPUMultiVWait(nExecuteClock);
			} else if (Z80Main().GetBaseClock() != 8) {
				//Serial.println("CPC88::Execute 12");
				Execute2CPUMultiVWait(nExecuteClock);
			} else {
				//Serial.println("CPC88::Execute 13");
				Execute2CPUMulti8MVWait(nExecuteClock);
			}
		}
	}
}

////////////////////////////////////////////////////////////
// debug

// set debug execute mode

void CPC88::SetDebugExecMode(int nDebugExecMode) {
	if (nDebugExecMode != m_nDebugExecMode) {
		if (m_nDebugExecMode == DEBUGEXEC_NONE) {
			m_bFastROMEmulationBackup = m_bFastROMEmulation;
			SetFastROMEmulation(false);
		} else if (nDebugExecMode == DEBUGEXEC_NONE) {
			SetFastROMEmulation(m_bFastROMEmulationBackup);
		}
		m_nDebugExecMode = nDebugExecMode;
		SetDebugStop(true);
	}
}

// set debug stop mode

void CPC88::SetDebugStop(bool bStopped) {
	if (bStopped != m_bDebugStopped) {
		m_bDebugStopped = bStopped;
		if (IsDebugStopped()) {
			DebugExecuteStepTraceAbort();
		}
	}
	UpdateMnemonic();
}

// update mnemonic

void CPC88::UpdateMnemonic() {
	if (IsDebugMode() && IsDebugStopped()) {
		CZ80Adapter* pZ80A = GetDebugAdapter();
		m_wDebugPC = pZ80A->RegPC().Get();
		pZ80A->DisAssemble();
		m_wDebugPCNext = pZ80A->RegPC().Get();
		m_bDebugStepExecuteOpCode = pZ80A->IsStepExecuteOpCode();
		m_bDebugStepExecuteOpCode2 = pZ80A->IsStepExecuteOpCode2();
		pZ80A->RegPC().Set(m_wDebugPC);
	}
	SetMnemonicUpdated(true);
}

// get debug target Z80 adapter

CZ80Adapter* CPC88::GetDebugAdapter() {
	CZ80Adapter* pZ80A;
	if (IsDebugMain()) {
		pZ80A = Z80Main().GetAdapter();
	} else {
		pZ80A = Z80Sub().GetAdapter();
	}
	return pZ80A;
}

// is program-counter equals break point

bool CPC88::IsBreakPoint(uint16_t wPC) {
	int nCPU = IsDebugMain()? 0: 1;
	return m_setBreakPoint[nCPU].find(wPC) != m_setBreakPoint[nCPU].end();
}

// register break point

void CPC88::RegisterBreakPoint(uint16_t wPC) {
	int nCPU = IsDebugMain()? 0: 1;
	m_setBreakPoint[nCPU].insert(wPC);
}

// remove break point

void CPC88::RemoveBreakPoint(uint16_t wPC) {
	int nCPU = IsDebugMain()? 0: 1;
	m_setBreakPoint[nCPU].erase(wPC);
}

// remove temporary break point

void CPC88::RemoveTmpBreakPoint() {
	if (m_bDebugTraceInt && m_bDebugTraceIntBreakPoint) {
		RemoveBreakPoint(m_wDebugPCTraceInt);
		m_bDebugTraceIntBreakPoint = false;
	}
	if (m_bDebugStepWait && m_bDebugStepWaitBreakPoint) {
		RemoveBreakPoint(m_wDebugPCStepWait);
		m_bDebugStepWaitBreakPoint = false;
	}
}

// restore temporary break point

void CPC88::RestoreTmpBreakPoint() {
	if (m_bDebugTraceInt && !IsBreakPoint(m_wDebugPCTraceInt)) {
		RegisterBreakPoint(m_wDebugPCTraceInt);
		m_bDebugTraceIntBreakPoint = true;
	}
	if (m_bDebugStepWait&& !IsBreakPoint(m_wDebugPCStepWait)) {
		RegisterBreakPoint(m_wDebugPCStepWait);
		m_bDebugStepWaitBreakPoint = true;
	}
}

// debug execute

void CPC88::DebugExecute(int nExecuteClock) {
	m_nLeftClock += nExecuteClock;
	int nSubShift = (Z80Main().GetBaseClock() != 8)? 0: 1;
	uint16_t wPC;
	int nClock;
	while (m_nLeftClock > 0) {
		if (IsDebugMain()) {
			if (!Crtc().IsVRamWait()) {
				nClock = ExecuteOneOpCodeMain();
			} else {
				nClock = ExecuteOneOpCodeMainVWait();
			}
			m_nLeftClock -= nClock;
			m_nLeftClockSub += nClock;
			while (m_nLeftClockSub > 0) {
				m_nLeftClockSub -= ExecuteOneOpCodeSub() << nSubShift;
			}
			wPC = Z80Main().RegPC().Get();
		} else {
			m_nLeftClockSub -= ExecuteOneOpCodeSub() << nSubShift;
			while (m_nLeftClockSub <= 0) {
				if (!Crtc().IsVRamWait()) {
					nClock = ExecuteOneOpCodeMain();
				} else {
					nClock = ExecuteOneOpCodeMainVWait();
				}
				m_nLeftClock -= nClock;
				m_nLeftClockSub += nClock;
			}
			wPC = Z80Sub().RegPC().Get();
		}
		OutputDebugLog(DEBUGLOG_EXECUTE);
		if (IsBreakPoint(wPC)) {
			if (m_bDebugTraceInt && (wPC == m_wDebugPCTraceInt)) {
				// restart step execute at interrupt
				SetDebugStop(true);
				DebugExecuteStepTrace(m_nDebugStepMode);
				if (IsDebugStopped()) {
					break;
				}
			} else {
				SetDebugStop(true);
				break;
			}
		}
	}
}

// debug execute step/trace

void CPC88::DebugExecuteStepTrace(int nDebugStepMode) {
	bool bInterrupt = false;
	DebugExecuteStepTraceAbort();
	int nSubShift = (Z80Main().GetBaseClock() != 8)? 0: 1;
	uint16_t wPC;
	int nClock;
	int nInterruptCounter;
	if (IsDebugMain()) {
		nInterruptCounter = Z80Main().GetInterruptCounter();
		if (!Crtc().IsVRamWait()) {
			nClock = ExecuteOneOpCodeMain();
		} else {
			nClock = ExecuteOneOpCodeMainVWait();
		}
		m_nLeftClockSub += nClock;
		while (m_nLeftClockSub > 0) {
			m_nLeftClockSub -= ExecuteOneOpCodeSub() << nSubShift;
		}
		wPC = Z80Main().RegPC().Get();
		if (nInterruptCounter != Z80Main().GetInterruptCounter()) {
			bInterrupt = true;
		}
	} else {
		m_nLeftClockSub -= ExecuteOneOpCodeSub() << nSubShift;
		while (m_nLeftClockSub <= 0) {
			if (!Crtc().IsVRamWait()) {
				nClock = ExecuteOneOpCodeMain();
			} else {
				nClock = ExecuteOneOpCodeMainVWait();
			}
			m_nLeftClockSub += nClock;
		}
		wPC = Z80Sub().RegPC().Get();
	}
	OutputDebugLog(DEBUGLOG_EXECUTE);
	if (bInterrupt) {
		// interrupted in executing step/trace
		m_nDebugStepMode = nDebugStepMode;
		m_bDebugTraceInt = true;
		m_wDebugPCTraceInt = m_wDebugPC;
		if (!IsBreakPoint(m_wDebugPCTraceInt)) {
			RegisterBreakPoint(m_wDebugPCTraceInt);
			m_bDebugTraceIntBreakPoint = true;
		}
		SetDebugStop(false);
	} else if (
		(((nDebugStepMode == DEBUGSTEP_STEP) &&
				m_bDebugStepExecuteOpCode) ||
			((nDebugStepMode == DEBUGSTEP_STEP2) &&
				(m_bDebugStepExecuteOpCode || m_bDebugStepExecuteOpCode2))) &&
		(wPC != m_wDebugPCNext))
	{
		// not reach next command at step execute
		m_nDebugStepMode = nDebugStepMode;
		m_bDebugStepWait = true;
		m_wDebugPCStepWait = m_wDebugPCNext;
		if (!IsBreakPoint(m_wDebugPCStepWait)) {
			RegisterBreakPoint(m_wDebugPCStepWait);
			m_bDebugStepWaitBreakPoint = true;
		}
		SetDebugStop(false);
	} else {
		UpdateMnemonic();
	}
}

// abort debug execute step/trace

void CPC88::DebugExecuteStepTraceAbort() {
	if (m_bDebugTraceInt) {
		if (m_bDebugTraceIntBreakPoint) {
			RemoveBreakPoint(m_wDebugPCTraceInt);
			m_bDebugTraceIntBreakPoint = false;
		}
		m_bDebugTraceInt = false;
	}
	if (m_bDebugStepWait) {
		if (m_bDebugStepWaitBreakPoint) {
			RemoveBreakPoint(m_wDebugPCStepWait);
			m_bDebugStepWaitBreakPoint = false;
		}
		m_bDebugStepWait = false;
	}
}
