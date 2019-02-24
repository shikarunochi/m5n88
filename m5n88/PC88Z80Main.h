////////////////////////////////////////////////////////////
// PC-8801 Main CPU Emulator
//
// Written by Manuke
//
// Assisted by apaslothy
// (PC-8001mkII/SR,PCG-8800,InternationalMode Support)

#ifndef PC88Z80Main_DEFINED
#define PC88Z80Main_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Z80Main;

////////////////////////////////////////////////////////////
// include

#include "Z80.h"

#include "PC88Timer.h"
#include "PC88Crtc.h"
#include "PC88Usart.h"
#include "PC88Calendar.h"
#include "PC88Opna.h"
#include "PC88Ppi.h"
#include "PC88Pcg.h"

#include "ParallelDevice.h"

////////////////////////////////////////////////////////////
// declaration of CPC88Z80Main

class CPC88Z80Main :
	public CZ80_1
{
// typedef
public:
	// type of interrupt vector change callback function
	typedef void (*IntVectChangeCallback)();
	// type of beep output callback function
	typedef void (*BeepOutputCallback)(
		bool bBeepPortStatus, bool bExBeepPortStatus);

// enum
public:
	// BASIC mode
	enum {
		BASICMODE_N     = 0,
		BASICMODE_N88V1 = 1,
		BASICMODE_N88V2 = 2,
		BASICMODE_N80V1 = 3,
		BASICMODE_N80V2 = 4
	};
	// constant value
	enum {
		PALETTE_COUNT      = 9,
		BACKGROUND_PALETTE = 8
	};
	// expansion RAM
	enum {
		EX_RAM_COUNT = 2,
		EX_RAM_VAB   = 1
	};

// attribute
protected:
	// peripheral
	// timer
	static CPC88Timer* m_pTimer;
	// CRTC
	static CPC88Crtc* m_pCrtc;
	// USART
	static CPC88Usart* m_pUsart;
	// calendar clock
	static CPC88Calendar* m_pCalendar;
	// OPNA
	static CPC88Opna* m_pOpna;
	// PPI
	static CPC88Ppi* m_pPpi;
	// PCG
	static CPC88Pcg* m_pPcg;
	// parallel device
	static CParallelDevice* m_pParallelDevice;

	// memory
	// N88-BASIC ROM
	static uint8_t* m_abtN88BasicRom;
	// N-BASIC ROM
	static uint8_t* m_abtNBasicRom;
	// IE ROM
	static uint8_t* m_abtIERom;
	// N80-BASIC ROM
	static uint8_t* m_abtN80BasicRom;
	// N80-BASIC 4TH ROM
	static uint8_t* m_abtN80Basic4thRom;
	// N80V2-BASIC ROM
	static uint8_t* m_abtN80V2BasicRom;
	// N80V2 IE ROM
	static uint8_t* m_abtN80V2IERom;
	// main RAM
	static uint8_t* m_abtMainRam;
	// expansion RAM
	static uint8_t* m_abtExRam;
	// fast text VRAM
	static uint8_t* m_abtFastTVRam;
	// graphic VRAM
	static uint8_t* m_abtGVRam;
	// graphic VRAM(pixel access)
	static uint8_t* m_abtGVRamX;

	// kanji font
	// kanji address
	static uint16_t m_awKanjiAddress[2];
	// kanji ROM
	static uint8_t* m_abtKanjiRom;

	// N80V2 font
	// PC-8001mkIISR CG ROM
	static uint8_t* m_abtFont80SRRom;
	// international font ROM
	static uint8_t* m_abtOptionFontRom;

	// dip-switch setting
	// fast ROM emulation
	static bool m_bFastROMEmulation;
	// wait emulation
	static bool m_bWaitEmulation;
	// old-machine compatible mode
	static bool m_bOldCompatible;
	// PCG enable
	static bool m_bPcgEnable;
	// international display mode
	static bool m_bOptionFont;
	// BASIC mode
	static int m_nBasicMode;
	// N80/N80V2-BASIC mode
	static bool m_bN80BasicMode;
	// hi-speed mode
	static bool m_bHighSpeedMode;
	// base clock
	static int m_nBaseClock;
	// 8MHz-H mode
	static bool m_bClock8MHzH;
	// always memory wait
	static bool m_bAlwaysMemWait;
	// M1 wait
	static bool m_bM1Wait;
	// text VRAM wait
	static bool m_bTVRamWait;
	// graphic VRAM wait
	static bool m_bGVRamWait;
	// 40 columns mode
	static bool m_bBootWidth40;
	// 20 rows mode
	static bool m_bBootHeight20;
	// sub CPU disable
	static bool m_bSubSystemDisable;
	// video art board disable
	static bool m_bVABDisable;

	// memory bank changing and other
	// text window offset
	static uint16_t m_wTextWindowOfs;
	// all RAM mode
	static bool m_bAllRamMode;
	// expansion RAM card number
	static int m_nExRamCardNo;
	// expansion RAM bank number
	static int m_nExRamBankNo;
	// expansion RAM access mode
	static uint8_t m_btExRamAccessMode;
	// backup of expansion RAM access mode
	static uint8_t m_abtExRamAccessModeBackup;
	// N88-BASIC ROM mode
	static bool m_bNBasicRomMode;
	// N80V2-BASIC ROM mode
	static bool m_bN80V2BasicRomMode;
	// N/N80-BASIC mode
	static bool m_bNMode;
	// disable IE ROM
	static bool m_bDisableIERom;
	// IE ROM bank
	static int m_nIERomBank;
	// fast text VRAM using mode
	static bool m_bFastTVRamUse;
	// fast text VRAM disable
	static bool m_bFastTVRamDisable;
	// fast graphic VRAM using mode
	static bool m_bFastGVRamUse;
	// accessing graphic VRAM
	static bool m_bAccessingGVRam;
	// graphic VRAM bank
	static int m_nGVRamBank;

	// standard memory read procedure
	// N-BASIC ROM read(normal)
	static RPROC ReadMemoryNBasicRom_N;
	// N80-BASIC ROM read(normal)
	static RPROC ReadMemoryN80BasicRom_N;
	// N80-BASIC 4TH ROM read(normal)
	static RPROC ReadMemoryN80Basic4thRom_N;
	// N80V2-BASIC ROM read(normal)
	static RPROC ReadMemoryN80V2BasicRom_N;
	// N88-BASIC ROM read(normal)
	static RPROC ReadMemoryN88BasicRom_N;
	// IE0 ROM read(normal)
	static RPROC ReadMemoryIERom0_N;
	// IE1 ROM read(normal)
	static RPROC ReadMemoryIERom1_N;
	// IE2 ROM read(normal)
	static RPROC ReadMemoryIERom2_N;
	// IE3 ROM read(normal)
	static RPROC ReadMemoryIERom3_N;
	// N80V2 IE ROM read(normal)
	static RPROC ReadMemoryN80V2IERom_N;
	// main RAM read(normal)
	static RPROC ReadMemoryMainRam_N;
	// main RAM read(text window / normal)
	static RPROC ReadMemoryMainRamTW_N;
	// expansion RAM read(normal)
	static RPROC ReadMemoryExRam_N;
	// expansion RAM read(video art board / normal)
	static RPROC ReadMemoryExRamVAB_N;
	// graphic VRAM0 read(normal)
	static RPROC ReadMemoryGVRam0_N;
	// graphic VRAM1 read(normal)
	static RPROC ReadMemoryGVRam1_N;
	// graphic VRAM2 read(normal)
	static RPROC ReadMemoryGVRam2_N;
	// extend graphic VRAM read(normal)
	static RPROC ReadMemoryGVRamEx_N;
	// fast text VRAM read(normal)
	static RPROC ReadMemoryFastTVRam_N;

	// M1-cycle memory read procedure
	// N-BASIC ROM read(M1)
	static RPROC ReadMemoryNBasicRom_M1;
	// N80-BASIC ROM read(M1)
	static RPROC ReadMemoryN80BasicRom_M1;
	// N80-BASIC 4TH ROM read(M1)
	static RPROC ReadMemoryN80Basic4thRom_M1;
	// N80V2-BASIC ROM read(M1)
	static RPROC ReadMemoryN80V2BasicRom_M1;
	// N88-BASIC ROM read(M1)
	static RPROC ReadMemoryN88BasicRom_M1;
	// N88-BASIC ROM read(Bank7 / M1)
	static RPROC ReadMemoryN88BasicRomB7_M1;
	// IE0 ROM read(M1)
	static RPROC ReadMemoryIERom0_M1;
	// IE1 ROM read(M1)
	static RPROC ReadMemoryIERom1_M1;
	// IE2 ROM read(M1)
	static RPROC ReadMemoryIERom2_M1;
	// IE3 ROM read(M1)
	static RPROC ReadMemoryIERom3_M1;
	// N80V2 IE ROM read(M1)
	static RPROC ReadMemoryN80V2IERom_M1;
	// main RAM read(M1)
	static RPROC ReadMemoryMainRam_M1;
	// main RAM read(text window / M1)
	static RPROC ReadMemoryMainRamTW_M1;
	// expansion RAM read(M1)
	static RPROC ReadMemoryExRam_M1;
	// expansion RAM read(video art board / M1)
	static RPROC ReadMemoryExRamVAB_M1;
	// graphic VRAM0 read(M1)
	static RPROC ReadMemoryGVRam0_M1;
	// graphic VRAM1 read(M1)
	static RPROC ReadMemoryGVRam1_M1;
	// graphic VRAM2 read(M1)
	static RPROC ReadMemoryGVRam2_M1;
	// extend graphic VRAM read(M1)
	static RPROC ReadMemoryGVRamEx_M1;
	// fast text VRAM read(M1)
	static RPROC ReadMemoryFastTVRam_M1;

	// standard memory write procedure
	// main RAM write(normal)
	static WPROC WriteMemoryMainRam_N;
	// main RAM write(text window / normal)
	static WPROC WriteMemoryMainRamTW_N;
	// expansion RAM write(normal)
	static WPROC WriteMemoryExRam_N;
	// expansion RAM write(video art board / normal)
	static WPROC WriteMemoryExRamVAB_N;
	// RAM write disable(normal)
	static WPROC WriteMemoryDisable_N;
	// graphic VRAM0 write(normal)
	static WPROC WriteMemoryGVRam0_N;
	// graphic VRAM1 write(normal)
	static WPROC WriteMemoryGVRam1_N;
	// graphic VRAM2 write(normal)
	static WPROC WriteMemoryGVRam2_N;
	// extend graphic VRAM write(ALU / normal)
	static WPROC WriteMemoryGVRamExALU_N;
	// extend graphic VRAM write(ALL / normal)
	static WPROC WriteMemoryGVRamExAll_N;
	// extend graphic VRAM write(1 -> 0 / normal)
	static WPROC WriteMemoryGVRamEx1to0_N;
	// extend graphic VRAM write(0 -> 1 / normal)
	static WPROC WriteMemoryGVRamEx0to1_N;
	// fast text VRAM write(normal)
	static WPROC WriteMemoryFastTVRam_N;

	// interrupt
	// timer interrupt masking
	static bool m_bTimerInterruptMask;
	// v-sync interrupt masking
	static bool m_bVSyncInterruptMask;
	// USART interrupt masking
	static bool m_bUsartInterruptMask;
	// PSG interrupt masking
	static bool m_bPsgInterruptMask;
	// interrupt level
	static int m_nInterruptLevel;
	// priority interrupt
	static bool m_bPriorityInterrupt;
	// interrupt counter
	static int m_nInterruptCounter;

	// text
	// text VRAM offset
	static uint16_t m_wTVRamOfs;
	// text VRAM overlay disable
	static bool m_bTVRamOverlayDisable;
	// text VRAM updated
	static bool m_bTVRamUpdate;
	// hiragana display mode
	static bool m_bHiraMode;

	// graphic
	// graphic display 200 line mode
	static bool m_bGraphicDisplay200Line;
	// graphic display 320 line mode
	static bool m_bGraphicDisplay320Line;
	// graphic display enable
	static bool m_bGraphicDisplayEnable;
	// graphic flashing mode
	static bool m_bGraphicFlashing;
	// graphic display color
	static bool m_bGraphicDisplayColor;
	// N80BASIC graphic color mode
	static bool m_bN80GraphicColorMode;
	// graphic display analog
	static bool m_bGraphicDisplayAnalog;
	// extend graphic access GVAM mode
	static bool m_bGraphicExGVAM;
	// extend graphic access GAM mode
	static bool m_bGraphicExGAM;
	// graphic data multiplexer control
	static int m_nGraphicExGDM;
	// graphic ALU mode
	static int m_anGraphicExALU[3];
	// graphic VRAM compare data
	static uint8_t m_abtGraphicExPlaneCompare[3];
	// graphic VRAM pre-fetch data
	static uint8_t m_abtGraphicExPreFetch[3];
	// graphic VRAM overlay disable
	static bool m_abGVRamOverlayDisable[6];
	// color palette
	static int m_anColorPalette[PALETTE_COUNT];
	// N80 graphic palette
	static uint8_t m_btN80GraphicPalette;
	// video output control
	static int m_nAVC;
	// graphic VRAM updated
	static bool m_bGVRamUpdate;
	// color palette updated
	static bool m_bPaletteUpdate;
	// display priority graphic VRAM1 > graphic VRAM0
	static bool m_bGraphicPriority;
	// display priority text VRAM < graphic VRAM
	static bool m_bTextPriority;
	// video art board mode1
	static uint8_t m_btVABMode1;
	// video art board mode2
	static uint8_t m_btVABMode2;
	// video art board updated
	static bool m_bVABUpdate;

	// DMA
	// DMA write flip-flop on
	static bool m_bDMAWriteFF_64;

	// key
	// key matrics
	static uint8_t m_abtKeyMatrics[15];

	// interrupt vector change callback function
	static IntVectChangeCallback m_pIntVectChangeCallback;

	// beep output callback function
	static BeepOutputCallback m_pBeepOutputCallback;

public:
	// peripheral
	// timer
	static CPC88Timer& Timer() {
		return *m_pTimer;
	}
	// CRTC
	static CPC88Crtc& Crtc() {
		return *m_pCrtc;
	}
	// USART
	static CPC88Usart& Usart() {
		return *m_pUsart;
	}
	// calendar clock
	static CPC88Calendar& Calendar() {
		return *m_pCalendar;
	}
	// OPNA
	static CPC88Opna& Opna() {
		return *m_pOpna;
	}
	// PPI
	static CPC88Ppi& Ppi() {
		return *m_pPpi;
	}
	// PCG
	static CPC88Pcg& Pcg() {
		return *m_pPcg;
	}
	// parallel device
	static CParallelDevice& ParallelDevice() {
		return *m_pParallelDevice;
	}

	// memory
	// get N88-BASIC ROM buffer
	static uint8_t* GetN88BasicRomPtr() {
		return m_abtN88BasicRom;
	}
	// get N-BASIC ROM buffer
	static uint8_t* GetNBasicRomPtr() {
		return m_abtNBasicRom;
	}
	// get IE ROM buffer
	static uint8_t* GetIERomPtr(int nBank) {
		return m_abtIERom + (nBank * 8192);
	}
	// get N80-BASIC ROM buffer
	static uint8_t* GetN80BasicRomPtr() {
		return m_abtN80BasicRom;
	}
	// get N80-BASIC 4TH ROM buffer
	static uint8_t* GetN80Basic4thRomPtr() {
		return m_abtN80Basic4thRom;
	}
	// get N80V2-BASIC ROM buffer
	static uint8_t* GetN80V2BasicRomPtr() {
		return m_abtN80V2BasicRom;
	}
	// get N80V2 IE ROM buffer
	static uint8_t* GetN80V2IERomPtr() {
		return m_abtN80V2IERom;
	}
	// get main RAM buffer
	static uint8_t* GetMainRamPtr() {
		return m_abtMainRam;
	}
	// get expansion RAM buffer
	static uint8_t* GetExRamPtr(int nCard) {
		return m_abtExRam + (nCard * 32768*4);
	}
	// get fast text VRAM buffer
	static uint8_t* GetFastTVRamPtr() {
		return m_abtFastTVRam;
	}

	// kanji font
	// get kanji address
	static uint16_t GetKanjiAddress(int nType) {
		return m_awKanjiAddress[nType];
	}
	// set kanji address
	static void SetKanjiAddress(int nType, uint16_t wKanjiAddress) {
		m_awKanjiAddress[nType] = wKanjiAddress;
	}
	// get kanji ROM buffer
	static uint8_t* GetKanjiRomPtr(int nType) {
		return m_abtKanjiRom + (nType * 131072);
	}
	// get kanji ROM content
	static uint8_t GetKanjiRom(int nType, int nAddress) {
		return m_abtKanjiRom[nType * 131072 + nAddress];
	}

	// N80V2 font
	// get PC-8001mkIISR CG ROM buffer
	static uint8_t* GetFont80SRRomPtr() {
		return m_abtFont80SRRom;
	}
	// get PC-8001mkIISR CG ROM content
	static uint8_t GetFont80SRRom(int nAddress) {
		return m_abtFont80SRRom[nAddress];
	}
	// get international font ROM buffer
	static uint8_t* GetOptionFontRomPtr() {
		return m_abtOptionFontRom;
	}
	// get international font ROM content
	static uint8_t GetOptionFontRom(int nAddress) {
		return m_abtOptionFontRom[nAddress];
	}
	// get current text font ROM content
	static uint8_t GetCurTextFontRom(int nAddress) {
		return m_bOptionFont?
			m_abtOptionFontRom[nAddress]:
			m_abtKanjiRom[0 + 256*16 + nAddress];
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
			ReadMemoryN88BasicRomB7_M1 = ReadMemoryN88BasicRom_M1;
		} else {
			ReadMemoryN88BasicRomB7_M1 = ReadMemoryN88BasicRomB7_FastEmu;
		}
		if (!m_bAllRamMode && m_bDisableIERom && !m_bNBasicRomMode) {
			SetReadMemoryM1Proc(7, ReadMemoryN88BasicRomB7_M1);
		}
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
	// get BASIC mode
	static int GetBasicMode() {
		return m_nBasicMode;
	}
	// set BASIC mode
	static void SetBasicMode(int nBasicMode) {
		m_nBasicMode = nBasicMode;
	}
	// is N80/N80V2-BASIC mode
	static bool IsN80BasicMode() {
		return m_bN80BasicMode;
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
	// is 8MHz-H mode
	static bool IsClock8MHzH() {
		return m_bClock8MHzH;
	}
	// set 8MHz-H mode
	static void SetClock8MHzH(bool bClock8MHzH) {
		m_bClock8MHzH = bClock8MHzH;
	}
	// is always memory wait
	static bool IsAlwaysMemWait() {
		return m_bAlwaysMemWait;
	}
	// is M1 wait
	static bool IsM1Wait() {
		return m_bM1Wait;
	}
	// is text VRAM wait
	static bool IsTVRamWait() {
		return m_bTVRamWait;
	}
	// is graphic VRAM wait
	static bool IsGVRamWait() {
		return m_bGVRamWait;
	}
	// is 40 columns mode
	static bool IsBootWidth40() {
		return m_bBootWidth40;
	}
	// set 40 columns mode
	static void SetBootWidth40(bool bBootWidth40) {
		m_bBootWidth40 = bBootWidth40;
	}
	// is 20 rows mode
	static bool IsBootHeight20() {
		return m_bBootHeight20;
	}
	// set 20 rows mode
	static void SetBootHeight20(bool bBootHeight20) {
		m_bBootHeight20 = bBootHeight20;
	}
	// is sub CPU disable
	static bool IsSubSystemDisable() {
		return m_bSubSystemDisable;
	}
	// set sub CPU disable
	static void SetSubSystemDisable(bool bSubSystemDisable) {
		m_bSubSystemDisable = bSubSystemDisable;
	}
	// is video art board disable
	static bool IsVABDisable() {
		return m_bVABDisable;
	}
	// set video art board disable
	static void SetVABDisable(bool bVABDisable) {
		m_bVABDisable = bVABDisable;
	}

	// memory bank changing and other
	// get text window offset
	static uint8_t GetTextWindowOfs() {
		return uint8_t(m_wTextWindowOfs >> 8);
	}
	// set text window offset
	static void SetTextWindowOfs(uint8_t btTextWindowOfs) {
		m_wTextWindowOfs = uint16_t(btTextWindowOfs << 8);
	}
	// increment text window offset
	static void IncTextWindowOfs() {
		m_wTextWindowOfs += 0x0100;
	}
	// is all RAM mode
	static bool IsAllRamMode() {
		return m_bAllRamMode;
	}
	// set all RAM mode
	static void SetAllRamMode(bool bAllRamMode) {
		m_bAllRamMode = bAllRamMode;
	}
	// is N88-BASIC ROM mode
	static bool IsNBasicRomMode() {
		return m_bNBasicRomMode;
	}
	// set N88-BASIC ROM mode
	static void SetNBasicRomMode(bool bNBasicRomMode) {
		m_bNBasicRomMode = bNBasicRomMode;
	}
	// is N80V2-BASIC ROM mode
	static bool IsN80V2BasicRomMode() {
		return m_bN80V2BasicRomMode;
	}
	// set N80V2-BASIC ROM mode
	static void SetN80V2BasicRomMode(bool bN80V2BasicRomMode) {
		m_bN80V2BasicRomMode = bN80V2BasicRomMode;
	}
	// is disable IE ROM
	static bool IsDisableIERom() {
		return m_bDisableIERom;
	}
	// set disable IE ROM
	static void SetDisableIERom(bool bDisableIERom) {
		m_bDisableIERom = bDisableIERom;
	}
	// get IE ROM bank
	static int GetIERomBank() {
		return m_nIERomBank;
	}
	// set IE ROM bank
	static void SetIERomBank(int nIERomBank) {
		m_nIERomBank = nIERomBank;
	}
	// is fast text VRAM using mode
	static bool IsFastTVRamUse() {
		return m_bFastTVRamUse;
	}
	// is fast text VRAM disable
	static bool IsFastTVRamDisable() {
		return m_bFastTVRamDisable;
	}
	// set fast text VRAM disable
	static void SetFastTVRamDisable(bool bFastTVRamDisable) {
		m_bFastTVRamDisable = bFastTVRamDisable;
	}
	// is fast graphic VRAM using mode
	static bool IsFastGVRamUse() {
		return m_bFastGVRamUse;
	}
	// is accessing graphic VRAM
	static bool IsAccessingGVRam() {
		return m_bAccessingGVRam;
	}
	// get graphic VRAM bank
	static int GetGVRamBank() {
		return m_nGVRamBank;
	}
	// set graphic VRAM bank
	static void SetGVRamBank(int nGVRamBank) {
		m_nGVRamBank = nGVRamBank;
	}

	// interrupt
	// is timer interrupt masking
	static bool IsTimerInterruptMask() {
		return m_bTimerInterruptMask;
	}
	// set timer interrupt masking
	static void SetTimerInterruptMask(
		bool bTimerInterruptMask,
		bool bResetInterruptRequest = false)
	{
		if (bResetInterruptRequest &&
			m_bTimerInterruptMask &&
			!bTimerInterruptMask)
		{
			Timer().SetTimerInterruptRequest(false);
		}
		m_bTimerInterruptMask = bTimerInterruptMask;
	}
	// is v-sync interrupt masking
	static bool IsVSyncInterruptMask() {
		return m_bVSyncInterruptMask;
	}
	// set v-sync interrupt masking
	static void SetVSyncInterruptMask(
		bool bVSyncInterruptMask,
		bool bResetInterruptRequest = false)
	{
		if (bResetInterruptRequest &&
			m_bVSyncInterruptMask &&
			!bVSyncInterruptMask)
		{
			Crtc().SetVSyncInterruptRequest(false);
		}
		m_bVSyncInterruptMask = bVSyncInterruptMask;
	}
	// is USART interrupt masking
	static bool IsUsartInterruptMask() {
		return m_bUsartInterruptMask;
	}
	// set USART interrupt masking
	static void SetUsartInterruptMask(
		bool bUsartInterruptMask,
		bool bResetInterruptRequest = false)
	{
		if (bResetInterruptRequest &&
			m_bUsartInterruptMask &&
			!bUsartInterruptMask)
		{
			Usart().SetReceiveInterruptRequest(false);
		}
		m_bUsartInterruptMask = bUsartInterruptMask;
	}
	// is PSG interrupt masking
	static bool IsPsgInterruptMask() {
		return m_bPsgInterruptMask;
	}
	// set PSG interrupt masking
	static void SetPsgInterruptMask(
		bool bPsgInterruptMask,
		bool bResetInterruptRequest = false)
	{
		if (bResetInterruptRequest &&
			m_bPsgInterruptMask &&
			!bPsgInterruptMask)
		{
			Usart().SetReceiveInterruptRequest(false);
		}
		m_bPsgInterruptMask = bPsgInterruptMask;
	}
	// get interrupt level
	static int GetInterruptLevel() {
		return m_nInterruptLevel;
	}
	// set interrupt level
	static void SetInterruptLevel(int nInterruptLevel) {
		m_nInterruptLevel = nInterruptLevel;
	}
	// is priority interrupt
	static bool IsPriorityInterrupt() {
		return m_bPriorityInterrupt;
	}
	// set priority interrupt
	static void SetPriorityInterrupt(bool bPriorityInterrupt) {
		m_bPriorityInterrupt = bPriorityInterrupt;
	}
	// get interrupt counter
	static int GetInterruptCounter() {
		return m_nInterruptCounter;
	}

	// text
	// get text VRAM content
	static uint8_t GetTVRam(int nAddress) {
		int nAddress2 = uint16_t(nAddress+m_wTVRamOfs);
		uint8_t btData;
		if (m_bFastTVRamUse && (nAddress2 >= 0xF000)) {
			btData = m_abtFastTVRam[nAddress2 & 0x0FFF];
		} else {
			btData = m_abtMainRam[nAddress2];
		}
		return btData;
	}
	// get text VRAM offset
	static uint16_t GetTVRamOfs() {
		return m_wTVRamOfs;
	}
	// set text VRAM offset
	static void SetTVRamOfs(uint16_t wTVRamOfs) {
		m_wTVRamOfs = wTVRamOfs;
	}
	// is text VRAM overlay disable
	static bool IsTVRamOverlayDisable() {
		return m_bTVRamOverlayDisable;
	}
	// set text VRAM overlay disable
	static void SetTVRamOverlayDisable(bool bTVRamOverlayDisable) {
		m_bTVRamOverlayDisable = bTVRamOverlayDisable;
	}
	// is text VRAM updated
	static bool IsTVRamUpdate() {
		return m_bTVRamUpdate;
	}
	// set text VRAM updated
	static void SetTVRamUpdate(bool bTVRamUpdate) {
		m_bTVRamUpdate = bTVRamUpdate;
	}
	// is hiragana display mode
	static bool IsHiraMode() {
		return m_bHiraMode;
	}
	// set hiragana display mode
	static void SetHiraMode(bool bHiraMode) {
		m_bHiraMode = bHiraMode;
	}

	// graphic
	// get graphic VRAM buffer
	static uint8_t* GetGVRamPtr(int nPlane) {
		return m_abtGVRam + (nPlane * 16384);
	}
	// get graphic VRAM(pixel access) buffer
	static uint8_t* GetGVRamXPtr() {
		return m_abtGVRamX;
	}
	// get graphic VRAM content
	static uint8_t GetGVRam(int nPlane, int nAddress) {
		return m_abtGVRam[nPlane * 16384 + nAddress];
	}
	// get graphic VRAM(pixel access) content
	static uint8_t GetGVRamX(int nAddress) {
		return m_abtGVRamX[nAddress];
	}
	// is graphic display 200 line mode
	static bool IsGraphicDisplay200Line() {
		return m_bGraphicDisplay200Line;
	}
	// set graphic display 200 line mode
	static void SetGraphicDisplay200Line(bool bGraphicDisplay200Line) {
		m_bGraphicDisplay200Line = bGraphicDisplay200Line;
	}
	// is graphic display 320 line mode
	static bool IsGraphicDisplay320Line() {
		return m_bGraphicDisplay320Line;
	}
	// set graphic display 320 line mode
	static void SetGraphicDisplay320Line(bool bGraphicDisplay320Line) {
		m_bGraphicDisplay320Line = bGraphicDisplay320Line;
	}
	// is graphic display enable
	static bool IsGraphicDisplayEnable() {
		return m_bGraphicDisplayEnable;
	}
	// set graphic display enable
	static void SetGraphicDisplayEnable(bool bGraphicDisplayEnable) {
		m_bGraphicDisplayEnable = bGraphicDisplayEnable;
	}
	// is graphic flashing mode
	static bool IsGraphicFlashing() {
		return m_bGraphicFlashing;
	}
	// set graphic flashing mode
	static void SetGraphicFlashing(bool bGraphicFlashing) {
		m_bGraphicFlashing = bGraphicFlashing;
	}
	// is graphic display color
	static bool IsGraphicDisplayColor() {
		return m_bGraphicDisplayColor;
	}
	// set graphic display color
	static void SetGraphicDisplayColor(bool bGraphicDisplayColor) {
		m_bGraphicDisplayColor = bGraphicDisplayColor;
	}
	// is N80BASIC graphic color mode
	static bool IsN80GraphicColorMode() {
		return m_bN80GraphicColorMode;
	}
	// set N80BASIC graphic color mode
	static void SetN80GraphicColorMode(bool bN80GraphicColorMode) {
		m_bN80GraphicColorMode = bN80GraphicColorMode;
	}
	// is graphic display analog
	static bool IsGraphicDisplayAnalog() {
		return m_bGraphicDisplayAnalog;
	}
	// set graphic display analog
	static void SetGraphicDisplayAnalog(bool bGraphicDisplayAnalog) {
		m_bGraphicDisplayAnalog = bGraphicDisplayAnalog;
	}
	// is extend graphic access GVAM mode
	static bool IsGraphicExGVAM() {
		return m_bGraphicExGVAM;
	}
	// set extend graphic access GVAM mode
	static void SetGraphicExGVAM(bool bGraphicExGVAM) {
		m_bGraphicExGVAM = bGraphicExGVAM;
	}
	// is extend graphic access GAM mode
	static bool IsGraphicExGAM() {
		return m_bGraphicExGAM;
	}
	// set extend graphic access GAM mode
	static void SetGraphicExGAM(bool bGraphicExGAM) {
		m_bGraphicExGAM = bGraphicExGAM;
	}
	// get graphic data multiplexer control
	static int GetGraphicExGDM() {
		return m_nGraphicExGDM;
	}
	// set graphic data multiplexer control
	static void SetGraphicExGDM(int nGraphicExGDM) {
		m_nGraphicExGDM = nGraphicExGDM;
	}
	// get graphic ALU mode
	static int GetGraphicExALU(int nPlane) {
		return m_anGraphicExALU[nPlane];
	}
	// set graphic ALU mode
	static void SetGraphicExALU(int nPlane, int nGraphicExALU) {
		m_anGraphicExALU[nPlane] = nGraphicExALU;
	}
	// get graphic VRAM compare data
	static uint8_t GetGraphicExPlaneCompare(int nPlane) {
		return m_abtGraphicExPlaneCompare[nPlane];
	}
	// set graphic VRAM compare data
	static void SetGraphicExPlaneCompare(
		int nPlane, uint8_t btGraphicExPlaneCompare)
	{
		m_abtGraphicExPlaneCompare[nPlane] = btGraphicExPlaneCompare;
	}
	// get graphic VRAM pre-fetch data
	static uint8_t GetGraphicExPreFetch(int nPlane) {
		return m_abtGraphicExPreFetch[nPlane];
	}
	// set graphic VRAM pre-fetch data
	static void SetGraphicExPreFetch(
		int nPlane, uint8_t btGraphicExPreFetch)
	{
		m_abtGraphicExPreFetch[nPlane] = btGraphicExPreFetch;
	}
	// is graphic VRAM overlay disable
	static bool IsGVRamOverlayDisable(int nPlane) {
		return m_abGVRamOverlayDisable[nPlane];
	}
	// set graphic VRAM overlay disable
	static void SetGVRamOverlayDisable(
		int nPlane, bool abGVRamOverlayDisable)
	{
		m_abGVRamOverlayDisable[nPlane] = abGVRamOverlayDisable;
	}
	// is display priority graphic VRAM1 > graphic VRAM0
	static bool IsGraphicPriority() {
		return m_bGraphicPriority;
	}
	// set display priority graphic VRAM1 > graphic VRAM0
	static void SetGraphicPriority(bool bGraphicPriority) {
		m_bGraphicPriority = bGraphicPriority;
	}
	// is display priority text VRAM < graphic VRAM
	static bool IsTextPriority() {
		return m_bTextPriority;
	}
	// set display priority text VRAM < graphic VRAM
	static void SetTextPriority(bool bTextPriority) {
		m_bTextPriority = bTextPriority;
	}
	// get color palette
	static int GetColorPalette(int nPalNo) {
		return m_anColorPalette[nPalNo];
	}
	// set color palette
	static void SetColorPalette(int nPalNo, int nColorPalette) {
		m_anColorPalette[nPalNo] = nColorPalette;
	}
	// get N80 graphic palette
	static int GetN80GraphicPalette() {
		return m_btN80GraphicPalette;
	}
	// set N80 graphic palette
	static void SetN80GraphicPalette(uint8_t btN80GraphicPalette) {
		m_btN80GraphicPalette = btN80GraphicPalette;
	}
	// is graphic VRAM updated
	static bool IsGVRamUpdate() {
		return m_bGVRamUpdate;
	}
	// set graphic VRAM updated
	static void SetGVRamUpdate(bool bGVRamUpdate) {
		m_bGVRamUpdate = bGVRamUpdate;
	}
	// is color palette updated
	static bool IsPaletteUpdate() {
		return m_bPaletteUpdate;
	}
	// set color palette updated
	static void SetPaletteUpdate(bool bPaletteUpdate) {
		m_bPaletteUpdate = bPaletteUpdate;
	}
	// get video art board mode1
	static uint8_t GetVABMode1() {
		return m_btVABMode1;
	}
	// set video art board mode1
	static void SetVABMode1(uint8_t btVABMode1) {
		m_btVABMode1 = btVABMode1;
	}
	// get video art board mode2
	static uint8_t GetVABMode2() {
		return m_btVABMode2;
	}
	// set video art board mode2
	static void SetVABMode2(uint8_t btVABMode2) {
		m_btVABMode2 = btVABMode2;
	}
	// is video art board screen active
	static bool IsVABScreenActive() {
		return (m_btVABMode1 & 0x41) == 0x41;
	}
	// is video art board updated
	static bool IsVABUpdate() {
		return m_bVABUpdate;
	}
	// set video art board updated
	static void SetVABUpdate(bool bVABUpdate) {
		m_bVABUpdate = bVABUpdate;
	}

	// DMA
	// is DMA write flip-flop on
	static bool IsDMAWriteFF_64() {
		return m_bDMAWriteFF_64;
	}
	// set DMA write flip-flop on
	static void SetDMAWriteFF_64(bool bDMAWriteFF_64) {
		m_bDMAWriteFF_64 = bDMAWriteFF_64;
	}

	// key
	// is key matrics pressed
	static bool IsKeyMatrics(int nAddress, int nBit) {
		return (m_abtKeyMatrics[nAddress] &= uint8_t(0x01 << nBit)) == 0;
	}
	// set key matrics pressed
	static void SetKeyMatrics(int nAddress, int nBit, bool bPressed) {
		if (bPressed) {
			m_abtKeyMatrics[nAddress] &= uint8_t(~(0x01 << nBit));
		} else {
			m_abtKeyMatrics[nAddress] |= uint8_t(0x01 << nBit);
		}
	}
	// clear key matrics
	static void ClearKeyMatrics() {
		memset(m_abtKeyMatrics, 0xFF, sizeof(m_abtKeyMatrics));
	}

	// set interrupt vector change callback function
	static void SetIntVectChangeCallback(
		IntVectChangeCallback pIntVectChangeCallback)
	{
		m_pIntVectChangeCallback = pIntVectChangeCallback;
	}

	// set beep output callback function
	static void SetBeepOutputCallback(
		BeepOutputCallback pBeepOutputCallback)
	{
		m_pBeepOutputCallback = pBeepOutputCallback;
	}

// create & destroy
public:
	// default constructor
	CPC88Z80Main();
	// destructor
	virtual ~CPC88Z80Main();

// initialize
public:
	// set peripheral
	static void SetPeripheral(
		CPC88Timer& timer, CPC88Crtc& crtc, CPC88Usart& usert,
		CPC88Calendar& calendar, CPC88Opna& opna,
		CPC88Ppi& ppi, CPC88Pcg& pcg)
	{
		m_pTimer = &timer;
		m_pCrtc = &crtc;
		m_pUsart = &usert;
		m_pCalendar = &calendar;
		m_pOpna = &opna;
		m_pPpi = &ppi;
		m_pPcg = &pcg;
	}
	// set parallel device
	static void SetParallelDevice(CParallelDevice& paradev) {
		m_pParallelDevice = &paradev;
	}
	// initialize at first
	virtual void RamInitialize();
	virtual void Initialize();
	// reset
	virtual void Reset();

// memory bank changing
public:
	// ROM/RAM bank
	static void MemBankRomRamMode(
		bool bAllRamMode, bool bNBasicRomMode);
	// ROM/RAM bank(N80)
	static void MemBankRomRamMode_N80(
		bool bAllRamModeode, int nIERomBank);
	// expansion RAM write bank
	static void MemBankExRamWriteMode();
	// expansion RAM write bank(N80)
	static void MemBankExRamWriteMode_N80();
	// IE ROM bank
	static void MemBankIERomMode(
		bool bDisableIERom, int nIERomBank);
	// IE ROM bank(N80)
	static void MemBankIERomMode_N80(
		bool bDisableIERom);
	// graphic VRAM bank
	static void MemBankGVRamMode(int nGVRamBank);
	// graphic VRAM bank(N80)
	static void MemBankGVRamMode_N80(int nGVRamBank);
	// extend graphic VRAM bank
	static void MemBankGVRamModeEx(
		bool bGraphicExGAM, int nGraphicExGDM);
	// extend graphic VRAM bank(N80)
	static void MemBankGVRamModeEx_N80(
		bool bGraphicExGAM, int nGraphicExGDM);
	// fast text VRAM bank
	static void MemBankFastTVRamMode(bool bFastTVRamDisable);

// memory operation
protected:
	// dummy read
	static uint8_t ReadNONE(int nAddress);
	// dummy write
	static void WriteNONE(int nAddress, uint8_t btData);
	// N-BASIC ROM read
	static uint8_t ReadMemoryNBasicRom(int nAddress);
	// N-BASIC ROM read(wait)
	static uint8_t ReadMemoryNBasicRom_Wait(int nAddress);
	// N80-BASIC ROM read
	static uint8_t ReadMemoryN80BasicRom(int nAddress);
	// N80-BASIC ROM read(wait)
	static uint8_t ReadMemoryN80BasicRom_Wait(int nAddress);
	// N80-BASIC 4TH ROM read
	static uint8_t ReadMemoryN80Basic4thRom(int nAddress);
	// N80-BASIC 4TH ROM read(wait)
	static uint8_t ReadMemoryN80Basic4thRom_Wait(int nAddress);
	// N80V2-BASIC ROM read
	static uint8_t ReadMemoryN80V2BasicRom(int nAddress);
	// N80V2-BASIC ROM read(wait)
	static uint8_t ReadMemoryN80V2BasicRom_Wait(int nAddress);
	// N88-BASIC ROM read
	static uint8_t ReadMemoryN88BasicRom(int nAddress);
	// N88-BASIC ROM read(wait)
	static uint8_t ReadMemoryN88BasicRom_Wait(int nAddress);
	// N88-BASIC ROM read(bank7 fast ROM emulation)
	static uint8_t ReadMemoryN88BasicRomB7_FastEmu(int nAddress);
	// IE0 ROM read
	static uint8_t ReadMemoryIERom0(int nAddress);
	// IE0 ROM read(wait)
	static uint8_t ReadMemoryIERom0_Wait(int nAddress);
	// IE1 ROM read
	static uint8_t ReadMemoryIERom1(int nAddress);
	// IE1 ROM read(wait)
	static uint8_t ReadMemoryIERom1_Wait(int nAddress);
	// IE2 ROM read
	static uint8_t ReadMemoryIERom2(int nAddress);
	// IE2 ROM read(wait)
	static uint8_t ReadMemoryIERom2_Wait(int nAddress);
	// IE3 ROM read
	static uint8_t ReadMemoryIERom3(int nAddress);
	// IE3 ROM read(wait)
	static uint8_t ReadMemoryIERom3_Wait(int nAddress);
	// N80V2 IE ROM read
	static uint8_t ReadMemoryN80V2IERom(int nAddress);
	// N80V2 IE ROM read(wait)
	static uint8_t ReadMemoryN80V2IERom_Wait(int nAddress);
	// main RAM read
	static uint8_t ReadMemoryMainRam(int nAddress);
	// main RAM read(wait)
	static uint8_t ReadMemoryMainRam_Wait(int nAddress);
	// main RAM write
	static void WriteMemoryMainRam(int nAddress, uint8_t btData);
	// main RAM write(wait)
	static void WriteMemoryMainRam_Wait(int nAddress, uint8_t btData);
	// main RAM read(text window)
	static uint8_t ReadMemoryMainRamTW(int nAddress);
	// main RAM read(text window / wait)
	static uint8_t ReadMemoryMainRamTW_Wait(int nAddress);
	// main RAM write(text window)
	static void WriteMemoryMainRamTW(int nAddress, uint8_t btData);
	// main RAM write(text window / wait)
	static void WriteMemoryMainRamTW_Wait(int nAddress, uint8_t btData);
	// expansion RAM read
	static uint8_t ReadMemoryExRam(int nAddress);
	// expansion RAM read(wait)
	static uint8_t ReadMemoryExRam_Wait(int nAddress);
	// expansion RAM write
	static void WriteMemoryExRam(int nAddress, uint8_t btData);
	// expansion RAM write(wait)
	static void WriteMemoryExRam_Wait(int nAddress, uint8_t btData);
	// expansion RAM read(video art board)
	static uint8_t ReadMemoryExRamVAB(int nAddress);
	// expansion RAM read(video art board / wait)
	static uint8_t ReadMemoryExRamVAB_Wait(int nAddress);
	// expansion RAM write(video art board)
	static void WriteMemoryExRamVAB(int nAddress, uint8_t btData);
	// expansion RAM write(video art board / wait)
	static void WriteMemoryExRamVAB_Wait(int nAddress, uint8_t btData);
	// RAM write disable
	static void WriteMemoryDisable(int nAddress, uint8_t btData);
	// RAM write disable(wait)
	static void WriteMemoryDisable_Wait(int nAddress, uint8_t btData);
	// graphic VRAM0 read
	static uint8_t ReadMemoryGVRam0(int nAddress);
	// graphic VRAM0 read(wait)
	static uint8_t ReadMemoryGVRam0_Wait(int nAddress);
	// graphic VRAM0 write
	static void WriteMemoryGVRam0(int nAddress, uint8_t btData);
	// graphic VRAM0 write(wait)
	static void WriteMemoryGVRam0_Wait(int nAddress, uint8_t btData);
	// graphic VRAM1 read
	static uint8_t ReadMemoryGVRam1(int nAddress);
	// graphic VRAM1 read(wait)
	static uint8_t ReadMemoryGVRam1_Wait(int nAddress);
	// graphic VRAM1 write
	static void WriteMemoryGVRam1(int nAddress, uint8_t btData);
	// graphic VRAM1 write(wait)
	static void WriteMemoryGVRam1_Wait(int nAddress, uint8_t btData);
	// graphic VRAM2 read
	static uint8_t ReadMemoryGVRam2(int nAddress);
	// graphic VRAM2 read(wait)
	static uint8_t ReadMemoryGVRam2_Wait(int nAddress);
	// graphic VRAM2 write
	static void WriteMemoryGVRam2(int nAddress, uint8_t btData);
	// graphic VRAM2 write(wait)
	static void WriteMemoryGVRam2_Wait(int nAddress, uint8_t btData);
	// extend graphic VRAM read
	static uint8_t ReadMemoryGVRamEx(int nAddress);
	// extend graphic VRAM read(wait)
	static uint8_t ReadMemoryGVRamEx_Wait(int nAddress);
	// extend graphic VRAM write(ALU)
	static void WriteMemoryGVRamExALU(int nAddress, uint8_t btData);
	// extend graphic VRAM write(ALU / wait)
	static void WriteMemoryGVRamExALU_Wait(int nAddress, uint8_t btData);
	// extend graphic VRAM write(ALL)
	static void WriteMemoryGVRamExAll(int nAddress, uint8_t btData);
	// extend graphic VRAM write(ALL / wait)
	static void WriteMemoryGVRamExAll_Wait(int nAddress, uint8_t btData);
	// extend graphic VRAM write(1 -> 0)
	static void WriteMemoryGVRamEx1to0(int nAddress, uint8_t btData);
	// extend graphic VRAM write(1 -> 0 / wait)
	static void WriteMemoryGVRamEx1to0_Wait(int nAddress, uint8_t btData);
	// extend graphic VRAM write(0 -> 1)
	static void WriteMemoryGVRamEx0to1(int nAddress, uint8_t btData);
	// extend graphic VRAM write(0 -> 1 / wait)
	static void WriteMemoryGVRamEx0to1_Wait(int nAddress, uint8_t btData);
	// fast text VRAM read
	static uint8_t ReadMemoryFastTVRam(int nAddress);
	// fast text VRAM read(wait)
	static uint8_t ReadMemoryFastTVRam_Wait(int nAddress);
	// fast text VRAM write
	static void WriteMemoryFastTVRam(int nAddress, uint8_t btData);
	// fast text VRAM write(wait)
	static void WriteMemoryFastTVRam_Wait(int nAddress, uint8_t btData);
	// I/O port 00-0E read
	static uint8_t ReadIO_00_0E(int nAddress);
	// I/O port 00 write(fast tape loading)
	static void WriteIO_00_Ex(int nAddress, uint8_t btData);
	// I/O port 00-02 write(PCG)
	static void WriteIO_00_03_PCG(int nAddress, uint8_t btData);
	// I/O port 0C-0F write(PCG)
	static void WriteIO_0C_0F_PCG(int nAddress, uint8_t btData);
	// I/O port 10 write
	static void WriteIO_10(int nAddress, uint8_t btData);
	// I/O port 20 read
	static uint8_t ReadIO_20(int nAddress);
	// I/O port 20 write
	static void WriteIO_20(int nAddress, uint8_t btData);
	// I/O port 21 read
	static uint8_t ReadIO_21(int nAddress);
	// I/O port 21 write
	static void WriteIO_21(int nAddress, uint8_t btData);
	// I/O port 30 read
	static uint8_t ReadIO_30(int nAddress);
	// I/O port 30 write
	static void WriteIO_30(int nAddress, uint8_t btData);
	// I/O port 31 read
	static uint8_t ReadIO_31(int nAddress);
	// I/O port 31 write
	static void WriteIO_31(int nAddress, uint8_t btData);
	// I/O port 31 write(N80)
	static void WriteIO_31_N80(int nAddress, uint8_t btData);
	// I/O port 32 read
	static uint8_t ReadIO_32(int nAddress);
	// I/O port 32 write
	static void WriteIO_32(int nAddress, uint8_t btData);
	// I/O port 33 read(N80)
	static uint8_t ReadIO_33_N80(int nAddress);
	// I/O port 33 write(N80)
	static void WriteIO_33_N80(int nAddress, uint8_t btData);
	// I/O port 34 write
	static void WriteIO_34(int nAddress, uint8_t btData);
	// I/O port 35 write
	static void WriteIO_35(int nAddress, uint8_t btData);
	// I/O port 35 write(N80)
	static void WriteIO_35_N80(int nAddress, uint8_t btData);
	// I/O port 40 read
	static uint8_t ReadIO_40(int nAddress);
	// I/O port 40 write
	static void WriteIO_40(int nAddress, uint8_t btData);
	// I/O port 44 read
	static uint8_t ReadIO_44(int nAddress);
	// I/O port 44 write
	static void WriteIO_44(int nAddress, uint8_t btData);
	// I/O port 45 read
	static uint8_t ReadIO_45(int nAddress);
	// I/O port 45 write
	static void WriteIO_45(int nAddress, uint8_t btData);
	// I/O port 50 read
	static uint8_t ReadIO_50(int nAddress);
	// I/O port 50 write
	static void WriteIO_50(int nAddress, uint8_t btData);
	// I/O port 51 read
	static uint8_t ReadIO_51(int nAddress);
	// I/O port 51 write
	static void WriteIO_51(int nAddress, uint8_t btData);
	// I/O port 52 write
	static void WriteIO_52(int nAddress, uint8_t btData);
	// I/O port 53 write
	static void WriteIO_53(int nAddress, uint8_t btData);
	// I/O port 53 write(N80)
	static void WriteIO_53_N80(int nAddress, uint8_t btData);
	// I/O port 54-5B write
	static void WriteIO_54_5B(int nAddress, uint8_t btData);
	// I/O port 5C read
	static uint8_t ReadIO_5C(int nAddress);
	// I/O port 5C-5F write
	static void WriteIO_5C_5F(int nAddress, uint8_t btData);
	// I/O port 5C-5F write(N80)
	static void WriteIO_5C_5F_N80(int nAddress, uint8_t btData);
	// I/O port 64 write
	static void WriteIO_64(int nAddress, uint8_t btData);
	// I/O port 68 write
	static void WriteIO_68(int nAddress, uint8_t btData);
	// I/O port 6E read
	static uint8_t ReadIO_6E(int nAddress);
	// I/O port 70 read
	static uint8_t ReadIO_70(int nAddress);
	// I/O port 70 write
	static void WriteIO_70(int nAddress, uint8_t btData);
	// I/O port 71 read
	static uint8_t ReadIO_71(int nAddress);
	// I/O port 71 write
	static void WriteIO_71(int nAddress, uint8_t btData);
	// I/O port 71 write(N80)
	static void WriteIO_71_N80(int nAddress, uint8_t btData);
	// I/O port 78 write
	static void WriteIO_78(int nAddress, uint8_t btData);
	// I/O port B4 read
	static uint8_t ReadIO_B4(int nAddress);
	// I/O port B4 write
	static void WriteIO_B4(int nAddress, uint8_t btData);
	// I/O port B5 read
	static uint8_t ReadIO_B5(int nAddress);
	// I/O port B5 write
	static void WriteIO_B5(int nAddress, uint8_t btData);
	// I/O port E2 read
	static uint8_t ReadIO_E2(int nAddress);
	// I/O port E2 write
	static void WriteIO_E2(int nAddress, uint8_t btData);
	// I/O port E2 write(N80)
	static void WriteIO_E2_N80(int nAddress, uint8_t btData);
	// I/O port E3 read
	static uint8_t ReadIO_E3(int nAddress);
	// I/O port E3 write
	static void WriteIO_E3(int nAddress, uint8_t btData);
	// I/O port E3 write(N80)
	static void WriteIO_E3_N80(int nAddress, uint8_t btData);
	// I/O port E4 write
	static void WriteIO_E4(int nAddress, uint8_t btData);
	// I/O port E6 write
	static void WriteIO_E6(int nAddress, uint8_t btData);
	// I/O port E8 read
	static uint8_t ReadIO_E8(int nAddress);
	// I/O port E8 write
	static void WriteIO_E8(int nAddress, uint8_t btData);
	// I/O port E9 read
	static uint8_t ReadIO_E9(int nAddress);
	// I/O port E9 write
	static void WriteIO_E9(int nAddress, uint8_t btData);
	// I/O port EC read
	static uint8_t ReadIO_EC(int nAddress);
	// I/O port EC write
	static void WriteIO_EC(int nAddress, uint8_t btData);
	// I/O port ED read
	static uint8_t ReadIO_ED(int nAddress);
	// I/O port ED write
	static void WriteIO_ED(int nAddress, uint8_t btData);
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
	// I/O port FE write
	static void WriteIO_FE(int nAddress, uint8_t btData);
	// I/O port FF write
	static void WriteIO_FF(int nAddress, uint8_t btData);

public:

// graphic operation
protected:
	// update graphic VRAM(pixel access)
	static void UpdateGVRamX(int nAddress) {
		int nSrcAddress = nAddress & 0x3FFF;
		uint8_t* pbtGVRamX = m_abtGVRamX+(nSrcAddress << 3);
		uint8_t btBlue = m_abtGVRam[0 * 16384 + nSrcAddress];
		uint8_t btRed = m_abtGVRam[1 * 16384 + nSrcAddress];
		uint8_t btGreen = m_abtGVRam[2 * 16384 + nSrcAddress];
		*(pbtGVRamX++) = uint8_t(
			((btBlue >> 7) & 0x01) |
			((btRed >> 6) & 0x02) |
			((btGreen >> 5) & 0x04));
		*(pbtGVRamX++) = uint8_t(
			((btBlue >> 6) & 0x01) |
			((btRed >> 5) & 0x02) |
			((btGreen >> 4) & 0x04));
		*(pbtGVRamX++) = uint8_t(
			((btBlue >> 5) & 0x01) |
			((btRed >> 4) & 0x02) |
			((btGreen >> 3) & 0x04));
		*(pbtGVRamX++) = uint8_t(
			((btBlue >> 4) & 0x01) |
			((btRed >> 3) & 0x02) |
			((btGreen >> 2) & 0x04));
		*(pbtGVRamX++) = uint8_t(
			((btBlue >> 3) & 0x01) |
			((btRed >> 2) & 0x02) |
			((btGreen >> 1) & 0x04));
		*(pbtGVRamX++) = uint8_t(
			((btBlue >> 2) & 0x01) |
			((btRed >> 1) & 0x02) |
			(btGreen & 0x04));
		*(pbtGVRamX++) = uint8_t(
			((btBlue >> 1) & 0x01) |
			(btRed & 0x02) |
			((btGreen << 1) & 0x04));
		*pbtGVRamX = uint8_t(
			(btBlue & 0x01) |
			((btRed << 1) & 0x02) |
			((btGreen << 2) & 0x04));
	}

// interrupt
public:
	// occurred interrupt
	virtual int DoInterrupt(uint8_t btIntVect);
};

#endif // PC88Z80Main_DEFINED
