////////////////////////////////////////////////////////////
// PC-8801 Emulator
//
// Written by Manuke
//
// Assisted by apaslothy
// (PC-8001mkII/SR,PCG-8800,InternationalMode Support)

#ifndef PC88_DEFINED
#define PC88_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88;

////////////////////////////////////////////////////////////
// include

#include "PC88Z80Main.h"
#include "PC88Z80Sub.h"
#include "PC88Timer.h"
#include "PC88Crtc.h"
#include "PC88Usart.h"
#include "PC88Calendar.h"
#include "PC88Opna.h"
#include "PC88Ppi.h"
#include "PC88Fdc.h"
#include "PC88Pcg.h"

#include "DiskImageCollection.h"
#include <set>

////////////////////////////////////////////////////////////
// declaration of CPC88

class CPC88 {
// typedef
public:
	// type of system file open callback function
	typedef File (*SysFileOpenCallback)(const std::string& strName);
	// type of output debug log callback function
	typedef void (*OutputDebugLogCallback)(int nLogMode);

// enum
public:
	// multi OP code execute count
	enum {
		MULTI_OP_CODE_COUNT = 10
	};
	// debug execute mode
	enum {
		DEBUGEXEC_NONE  = -1,
		DEBUGEXEC_MAIN  = 0,
		DEBUGEXEC_SUB   = 1
	};
	// debug step mode
	enum {
		DEBUGSTEP_TRACE = 0,
		DEBUGSTEP_STEP  = 1,
		DEBUGSTEP_STEP2 = 2
	};
	// debug log command
	enum {
		DEBUGLOG_START         = 0,
		DEBUGLOG_END           = 1,
		DEBUGLOG_CHANGE_CPU    = 2,
		DEBUGLOG_RESET         = 3,
		DEBUGLOG_READ_MEMIMAGE = 4,
		DEBUGLOG_EXECUTE       = 5
	};

// attribute
protected:
	// CPU/peripheral
	// main CPU
	static CPC88Z80Main m_z80Main;
	// sub CPU
	static CPC88Z80Sub m_z80Sub;
	// timer
	static CPC88Timer m_timer;
	// CRTC
	static CPC88Crtc m_crtc;
	// USART
	static CPC88Usart m_usart;
	// calendar clock
	static CPC88Calendar m_calendar;
	// OPNA
	static CPC88Opna m_opna;
	// PPI
	static CPC88Ppi m_ppi;
	// FDC
	static CPC88Fdc m_fdc;
	// PCG
	static CPC88Pcg m_pcg;

	// dip-switch setting
	// fast ROM emulation
	static bool m_bFastROMEmulation;
	// BASIC mode
	static int m_nBasicMode;
	// hi-speed mode
	static bool m_bHighSpeedMode;
	// base clock
	static int m_nBaseClock;
	// sub CPU disable
	static bool m_bSubSystemDisable;
	// execute multi OP code at once
	static bool m_bMultiOpCode;
	// hi-resolution mode
	static bool m_bHiresolution;
	// wait emulation
	static bool m_bWaitEmulation;
	// old-machine compatible mode
	static bool m_bOldCompatible;
	// PCG enable
	static bool m_bPcgEnable;
	// international display mode
	static bool m_bOptionFont;

	// debug
	// debug execute mode
	static int m_nDebugExecMode;
	// debug stopped
	static bool m_bDebugStopped;
	// backup of fast ROM emulation mode
	static bool m_bFastROMEmulationBackup;
	// debug program-counter
	static uint16_t m_wDebugPC;
	// debug program-counter(next command)
	static uint16_t m_wDebugPCNext;
	// temporary break point at interrupt trace
	static uint16_t m_wDebugPCTraceInt;
	// temporary break point at step wait
	static uint16_t m_wDebugPCStepWait;
	// executable step next OP code
	static bool m_bDebugStepExecuteOpCode;
	// executable step2 next OP code
	static bool m_bDebugStepExecuteOpCode2;
	// step execute mode
	static int m_nDebugStepMode;
	// interrupt tracing
	static bool m_bDebugTraceInt;
	// temporary break point at interrupt trace registered
	static bool m_bDebugTraceIntBreakPoint;
	// step waiting
	static bool m_bDebugStepWait;
	// temporary break point at step wait registered
	static bool m_bDebugStepWaitBreakPoint;
	// mnemonic updated
	static bool m_bMnemonicUpdated;
	// main/sub CPU break point
	static std::set<uint16_t> m_setBreakPoint[2];

	// other
	// interrupt vector
	static int m_nIntVect;
	// main CPU left clock
	static int m_nLeftClock;
	// sub CPU left clock
	static int m_nLeftClockSub;
	// disk image collection
	static CDiskImageCollection m_dicDisks;

	// output debug log callback function
	static OutputDebugLogCallback m_pOutputDebugLogCallback;
	// system file open callback function
	static SysFileOpenCallback m_pSysFileOpenCallback;

public:
	// CPU/peripheral
	// main CPU
	static CPC88Z80Main& Z80Main() {
		return m_z80Main;
	}
	// sub CPU
	static CPC88Z80Sub& Z80Sub() {
		return m_z80Sub;
	}
	// timer
	static CPC88Timer& Timer() {
		return m_timer;
	}
	// CRTC
	static CPC88Crtc& Crtc() {
		return m_crtc;
	}
	// USART
	static CPC88Usart& Usart() {
		return m_usart;
	}
	// calendar clock
	static CPC88Calendar& Calendar() {
		return m_calendar;
	}
	// OPNA
	static CPC88Opna& Opna() {
		return m_opna;
	}
	// PPI
	static CPC88Ppi& Ppi() {
		return m_ppi;
	}
	// FDC
	static CPC88Fdc& Fdc() {
		return m_fdc;
	}
	// PCG
	static CPC88Pcg& Pcg() {
		return m_pcg;
	}

	// dip-switch setting
	// is fast ROM emulation
	static bool IsFastROMEmulation() {
		return m_bFastROMEmulation;
	}
	// set fast ROM emulation
	static void SetFastROMEmulation(bool bFastROMEmulation) {
		m_bFastROMEmulation = bFastROMEmulation;
		Z80Main().SetFastROMEmulation(m_bFastROMEmulation);
		Z80Sub().SetFastROMEmulation(m_bFastROMEmulation);
	}
	// get BASIC mode
	static int GetBasicMode() {
		return m_nBasicMode;
	}
	// set BASIC mode
	static void SetBasicMode(int nBasicMode) {
		m_nBasicMode = nBasicMode;
	}
	// is hi-speed mode
	static bool IsHighSpeedMode() {
		return m_bHighSpeedMode;
	}
	// set hi-speed mode
	static void SetHighSpeedMode(bool bHighSpeedMode) {
		m_bHighSpeedMode = bHighSpeedMode;
	}
	// get base clock
	static int GetBaseClock() {
		return m_nBaseClock;
	}
	// set base clock
	static void SetBaseClock(int nBaseClock) {
		m_nBaseClock = nBaseClock;
	}
	// is sub CPU disable
	static bool IsSubSystemDisable() {
		return m_bSubSystemDisable;
	}
	// set sub CPU disable
	static void SetSubSystemDisable(bool bSubSystemDisable) {
		m_bSubSystemDisable = bSubSystemDisable;
	}
	// is sub CPU disable now
	static bool IsSubSystemDisableNow() {
		return Z80Main().IsSubSystemDisable();
	}
	// is execute multi OP code at once
	static bool IsMultiOpCode() {
		return m_bMultiOpCode;
	}
	// set execute multi OP code at once
	static void SetMultiOpCode(bool bMultiOpCode) {
		m_bMultiOpCode = bMultiOpCode;
	}
	// is hi-resolution mode
	static bool IsHiresolution() {
		return m_bHiresolution;
	}
	// set hi-resolution mode
	static void SetHiresolution(bool bHiresolution) {
		m_bHiresolution = bHiresolution;
	}
	// is wait emulation
	static bool IsWaitEmulation() {
		return m_bWaitEmulation;
	}
	// set wait emulation
	static void SetWaitEmulation(bool bWaitEmulation) {
		m_bWaitEmulation = bWaitEmulation;
	}
	// is old-machine compatible mode
	static bool IsOldCompatible() {
		return m_bOldCompatible;
	}
	// set old-machine compatible mode
	static void SetOldCompatible(bool bOldCompatible) {
		m_bOldCompatible = bOldCompatible;
	}
	// is PCG enable
	static bool IsPcgEnable() {
		return m_bPcgEnable;
	}
	// set PCG enable
	static void SetPcgEnable(bool bPcgEnable) {
		m_bPcgEnable = bPcgEnable;
	}
	// is international display mode
	static bool IsOptionFont() {
		return m_bOptionFont;
	}
	// set international display mode
	static void SetOptionFont(bool bOptionFont) {
		m_bOptionFont = bOptionFont;
	}

	// debug
	// is debugging
	static bool IsDebugMode() {
		return m_nDebugExecMode != DEBUGEXEC_NONE;
	}
	// is main CPU debugging
	static bool IsDebugMain() {
		return m_nDebugExecMode == DEBUGEXEC_MAIN;
	}
	// is sub CPU debugging
	static bool IsDebugSub() {
		return m_nDebugExecMode == DEBUGEXEC_SUB;
	}
	// get debug execute mode
	static int GetDebugExecMode() {
		return m_nDebugExecMode;
	}
	// is debug stopped
	static bool IsDebugStopped() {
		return m_bDebugStopped;
	}
	// get debug program-counter
	static uint16_t GetDebugPC() {
		return m_wDebugPC;
	}
	// is mnemonic updated
	static bool IsMnemonicUpdated() {
		return m_bMnemonicUpdated;
	}
	// set mnemonic updated
	static void SetMnemonicUpdated(bool bMnemonicUpdated) {
		m_bMnemonicUpdated  = bMnemonicUpdated;
	}
	// get break point
	static std::set<uint16_t>* GetBreakPoint(bool bMain) {
		return &m_setBreakPoint[bMain? 0: 1];
	}

	// other
	// get interrupt vector
	static int GetIntVect() {
		return m_nIntVect;
	}
	// set interrupt vector
	static void SetIntVect(int nIntVect) {
		m_nIntVect = nIntVect;
	}
	// get main CPU left clock
	static int GetLeftClock() {
		return m_nLeftClock;
	}
	// add main CPU left clock
	static void AddLeftClock(int nClock) {
		m_nLeftClock += nClock;
	}
	// get sub CPU left clock
	static int GetLeftClockSub() {
		return m_nLeftClockSub;
	}
	// add sub CPU left clock
	static void AddLeftClockSub(int nClock) {
		m_nLeftClockSub += nClock;
	}
	// get disk image collection
	static CDiskImageCollection& GetDiskImageCollection() {
		return m_dicDisks;
	}

	// set output debug log callback function
	static void SetOutputDebugLogCallback(
		OutputDebugLogCallback pOutputDebugLogCallback)
	{
		m_pOutputDebugLogCallback = pOutputDebugLogCallback;
	}
	// output debug log
	static void OutputDebugLog(int nLogMode) {
		m_pOutputDebugLogCallback(nLogMode);
	}
	// set system file open callback function
	static void SetSysFileOpenCallback(
		SysFileOpenCallback pSysFileOpenCallback)
	{
		m_pSysFileOpenCallback = pSysFileOpenCallback;
	}
	// open system file
	static File SysFileOpen(const std::string& strName) {
		return m_pSysFileOpenCallback(strName);
	}

// create & destroy
public:
	// default constructor
	CPC88();
	// destructor
	~CPC88();

// initialize
public:
	// initialize at first
	static void Initialize();
	// reset
	static void Reset();
	// load memory image
	static void LoadMemoryImage(const std::string& fstrFileName);
	// read from file
	static bool FileRead(uint8_t* pbtBuf, size_t nSize, File fpt);

// execute
public:
	// change main CPU interrupt vector
	static void IntVectChangeMain();
	// change sub CPU interrupt vector
	static void IntVectChangeSub();
	// PPI:ATN activate
	static void PpiATNActivate();
	// PCG:current text font ROM get
	static uint8_t PcgCurTextFontRomGet(int nAddress);
	// execute main CPU 1 OP code
	static int ExecuteOneOpCodeMain() {
		int nClock = Z80Main().ExecuteOneOpCode();
		Crtc().PassClock(nClock);
		Usart().PassClock(nClock);
		Timer().PassClock(nClock);
		Calendar().PassClock(nClock);
		Opna().PassClock(nClock);
		return nClock;
	}
	// execute main CPU 1OP code(VRAM wait)
	static int ExecuteOneOpCodeMainVWait() {
		int nClock = Z80Main().ExecuteOneOpCode();
		Crtc().PassClockVWait(nClock);
		Usart().PassClock(nClock);
		Timer().PassClock(nClock);
		Calendar().PassClock(nClock);
		Opna().PassClock(nClock);
		return nClock;
	}
	// execute main CPU multi OP code
	static int ExecuteMultiOpCodeMain() {
		int nClock = Z80Main().ExecuteMultiOpCode(MULTI_OP_CODE_COUNT);
		Crtc().PassClock(nClock);
		Usart().PassClock(nClock);
		Timer().PassClock(nClock);
		Calendar().PassClock(nClock);
		Opna().PassClock(nClock);
		delay(1);
		return nClock;
	}
	// execute main CP multi OP code(VRAMwait)
	static int ExecuteMultiOpCodeMainVWait() {
		int nClock = Z80Main().ExecuteMultiOpCode(MULTI_OP_CODE_COUNT);
		nClock += Crtc().PassClockVWait(nClock);
		Usart().PassClock(nClock);
		Timer().PassClock(nClock);
		Calendar().PassClock(nClock);
		Opna().PassClock(nClock);
		return nClock;
	}
	// execute sub CPU 1 OP code
	static int ExecuteOneOpCodeSub() {
		int nClock = Z80Sub().ExecuteOneOpCode();
		Fdc().PassClock(nClock);
		return nClock;
	}
	// execute 1CPU
	static void Execute1CPU(int nExecuteClock);
	// execute 2CPU
	static void Execute2CPU(int nExecuteClock);
	// execute 2CPU(8MHz mode)
	static void Execute2CPU8M(int nExecuteClock);
	// execute 1CPU(multi OP code)
	static void Execute1CPUMulti(int nExecuteClock);
	// execute 2CPU(multi OP code)
	static void Execute2CPUMulti(int nExecuteClock);
	// execute 2CPU(multi OP code / 8MHz mode)
	static void Execute2CPUMulti8M(int nExecuteClock);
	// execute 1CPU(VRAM wait)
	static void Execute1CPUVWait(int nExecuteClock);
	// execute 2CPU(VRAM wait)
	static void Execute2CPUVWait(int nExecuteClock);
	// execute 2CPU(8MHz mode / VRAM wait)
	static void Execute2CPU8MVWait(int nExecuteClock);
	// execute 1CPU(multi OP code / VRAM wait)
	static void Execute1CPUMultiVWait(int nExecuteClock);
	// execute 2CPU(multi OP code / VRAM wait)
	static void Execute2CPUMultiVWait(int nExecuteClock);
	// execute 2CPU(multi OP code / 8MHz mode / VRAM wait)
	static void Execute2CPUMulti8MVWait(int nExecuteClock);
	// execute
	static void Execute(int nExecuteClock);

// debug
public:
	// set debug execute mode
	static void SetDebugExecMode(int nDebugExecMode);
	// set debug stop mode
	static void SetDebugStop(bool bStopped);
	// update mnemonic
	static void UpdateMnemonic();
	// get debug target Z80 adapter
	static CZ80Adapter* GetDebugAdapter();
	// is program-counter equals break point
	static bool IsBreakPoint(uint16_t wPC);
	// register break point
	static void RegisterBreakPoint(uint16_t wPC);
	// remove break point
	static void RemoveBreakPoint(uint16_t wPC);
	// remove temporary break point
	static void RemoveTmpBreakPoint();
	// restore temporary break point
	static void RestoreTmpBreakPoint();
	// debug execute
	static void DebugExecute(int nExecuteClock);
	// debug execute step/trace
	static void DebugExecuteStepTrace(int nDebugStepMode);
	// abort debug execute step/trace
	static void DebugExecuteStepTraceAbort();
};

#endif // PC88_DEFINED
