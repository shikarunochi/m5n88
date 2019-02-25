////////////////////////////////////////////////////////////
// PC-8801 Main CPU Emulator
//
// Written by Manuke
//
// Assisted by apaslothy
// (PC-8001mkII/SR,PCG-8800,InternationalMode Support)

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Z80Main.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Z80Main

////////////////////////////////////////////////////////////
// attribute

// peripheral

// timer

CPC88Timer* CPC88Z80Main::m_pTimer;

// CRTC

CPC88Crtc* CPC88Z80Main::m_pCrtc;

// USART

CPC88Usart* CPC88Z80Main::m_pUsart;

// calendar clock

CPC88Calendar* CPC88Z80Main::m_pCalendar;

// OPNA

CPC88Opna* CPC88Z80Main::m_pOpna;

// PPI

CPC88Ppi* CPC88Z80Main::m_pPpi;

// PCG

CPC88Pcg* CPC88Z80Main::m_pPcg;

// parallel device

CParallelDevice* CPC88Z80Main::m_pParallelDevice;

// memory

// N88-BASIC ROM

uint8_t* CPC88Z80Main::m_abtN88BasicRom;

// N-BASIC ROM

uint8_t* CPC88Z80Main::m_abtNBasicRom;

// IE ROM

uint8_t* CPC88Z80Main::m_abtIERom;

// N80-BASIC ROM

uint8_t* CPC88Z80Main::m_abtN80BasicRom;

// N80-BASIC 4TH ROM

uint8_t* CPC88Z80Main::m_abtN80Basic4thRom;

// N80V2-BASIC ROM

uint8_t* CPC88Z80Main::m_abtN80V2BasicRom;

// N80V2 IE ROM

uint8_t* CPC88Z80Main::m_abtN80V2IERom;

// main RAM

uint8_t* CPC88Z80Main::m_abtMainRam;

// expansion RAM

uint8_t* CPC88Z80Main::m_abtExRam;

// fast text VRAM

uint8_t* CPC88Z80Main::m_abtFastTVRam;

// graphic VRAM

uint8_t* CPC88Z80Main::m_abtGVRam;

// graphic VRAM(pixel access)

uint8_t* CPC88Z80Main::m_abtGVRamX;

// kanji font

// kanji address

uint16_t CPC88Z80Main::m_awKanjiAddress[2];

// kanji ROM

uint8_t* CPC88Z80Main::m_abtKanjiRom;

// N80V2 font

// PC-8001mkIISR CG ROM

uint8_t* CPC88Z80Main::m_abtFont80SRRom;

// international font ROM

uint8_t* CPC88Z80Main::m_abtOptionFontRom;

// dip-switch setting

// fast ROM emulation

bool CPC88Z80Main::m_bFastROMEmulation;

// wait emulation

bool CPC88Z80Main::m_bWaitEmulation;

// old-machine compatible mode

bool CPC88Z80Main::m_bOldCompatible;

// PCG enable

bool CPC88Z80Main::m_bPcgEnable;

// international display mode

bool CPC88Z80Main:: m_bOptionFont;

// BASIC mode

int CPC88Z80Main::m_nBasicMode;

// N80/N80V2-BASIC mode

bool CPC88Z80Main::m_bN80BasicMode;

// hi-speed mode

bool CPC88Z80Main::m_bHighSpeedMode;

// base clock

int CPC88Z80Main::m_nBaseClock;

// 8MHz-H mode

bool CPC88Z80Main::m_bClock8MHzH;

// always memory wait

bool CPC88Z80Main::m_bAlwaysMemWait;

// M1 wait

bool CPC88Z80Main::m_bM1Wait;

// text VRAM wait

bool CPC88Z80Main::m_bTVRamWait;

// graphic VRAM wait

bool CPC88Z80Main::m_bGVRamWait;

// 40 columns mode

bool CPC88Z80Main::m_bBootWidth40;

// 20 rows mode

bool CPC88Z80Main::m_bBootHeight20;

// sub CPU disable

bool CPC88Z80Main::m_bSubSystemDisable;

// video art board disable

bool CPC88Z80Main::m_bVABDisable;

// memory bank changing and other

// text window offset

uint16_t CPC88Z80Main::m_wTextWindowOfs;

// all RAM mode

bool CPC88Z80Main::m_bAllRamMode;

// expansion RAM card number

int CPC88Z80Main::m_nExRamCardNo;

// expansion RAM bank number

int CPC88Z80Main::m_nExRamBankNo;

// expansion RAM access mode

uint8_t CPC88Z80Main::m_btExRamAccessMode;

// backup of expansion RAM access mode

uint8_t CPC88Z80Main::m_abtExRamAccessModeBackup;

// N88-BASIC ROM mode

bool CPC88Z80Main::m_bNBasicRomMode;

// N80V2-BASIC ROM mode

bool CPC88Z80Main::m_bN80V2BasicRomMode;

// N/N80-BASIC mode

bool CPC88Z80Main::m_bNMode;

// disable IE ROM

bool CPC88Z80Main::m_bDisableIERom;

// IE ROM bank

int CPC88Z80Main::m_nIERomBank;

// fast text VRAM using mode

bool CPC88Z80Main::m_bFastTVRamUse;

// fast text VRAM disable

bool CPC88Z80Main::m_bFastTVRamDisable;

// fast graphic VRAM using mode

bool CPC88Z80Main::m_bFastGVRamUse;

// accessing graphic VRAM

bool CPC88Z80Main::m_bAccessingGVRam;

// graphic VRAM bank

int CPC88Z80Main::m_nGVRamBank;

// standard memory read procedure

// N-BASIC ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryNBasicRom_N;

// N80-BASIC ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN80BasicRom_N;

// N80-BASIC 4TH ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN80Basic4thRom_N;

// N80V2-BASIC ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN80V2BasicRom_N;

// N88-BASIC ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN88BasicRom_N;

// IE0 ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryIERom0_N;

// IE1 ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryIERom1_N;

// IE2 ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryIERom2_N;

// IE3 ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryIERom3_N;

// N80V2 IE ROM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN80V2IERom_N;

// main RAM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryMainRam_N;

// main RAM read(text window / normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryMainRamTW_N;

// expansion RAM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryExRam_N;

// expansion RAM read(video art board / normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryExRamVAB_N;

// graphic VRAM0 read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryGVRam0_N;

// graphic VRAM1 read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryGVRam1_N;

// graphic VRAM2 read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryGVRam2_N;

// extend graphic VRAM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryGVRamEx_N;

// fast text VRAM read(normal)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryFastTVRam_N;

// M1-cycle memory read procedure

// N-BASIC ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryNBasicRom_M1;

// N80-BASIC ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN80BasicRom_M1;

// N80-BASIC 4TH ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN80Basic4thRom_M1;

// N80V2-BASIC ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN80V2BasicRom_M1;

// N88-BASIC ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN88BasicRom_M1;

// N88-BASIC ROM read(Bank7 / M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN88BasicRomB7_M1;

// IE0 ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryIERom0_M1;

// IE1 ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryIERom1_M1;

// IE2 ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryIERom2_M1;

// IE3 ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryIERom3_M1;

// N80V2 IE ROM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryN80V2IERom_M1;

// main RAM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryMainRam_M1;

// main RAM read(text window / M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryMainRamTW_M1;

// expansion RAM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryExRam_M1;

// expansion RAM read(video art board / M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryExRamVAB_M1;

// graphic VRAM0 read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryGVRam0_M1;

// graphic VRAM1 read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryGVRam1_M1;

// graphic VRAM2 read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryGVRam2_M1;

// extend graphic VRAM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryGVRamEx_M1;

// fast text VRAM read(M1)

CPC88Z80Main::RPROC CPC88Z80Main::ReadMemoryFastTVRam_M1;

// standard memory write procedure

// main RAM write(normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryMainRam_N;

// main RAM write(text window / normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryMainRamTW_N;

// expansion RAM write(normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryExRam_N;

// expansion RAM write(video art board / normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryExRamVAB_N;

// RAM write disable(normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryDisable_N;

// graphic VRAM0 write(normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryGVRam0_N;

// graphic VRAM1 write(normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryGVRam1_N;

// graphic VRAM2 write(normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryGVRam2_N;

// extend graphic VRAM write(ALU / normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryGVRamExALU_N;

// extend graphic VRAM write(ALL / normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryGVRamExAll_N;

// extend graphic VRAM write(1 -> 0 / normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryGVRamEx1to0_N;

// extend graphic VRAM write(0 -> 1 / normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryGVRamEx0to1_N;

// fast text VRAM write(normal)

CPC88Z80Main::WPROC CPC88Z80Main::WriteMemoryFastTVRam_N;

// interrupt

// timer interrupt masking

bool CPC88Z80Main::m_bTimerInterruptMask;

// v-sync interrupt masking

bool CPC88Z80Main::m_bVSyncInterruptMask;

// USART interrupt masking

bool CPC88Z80Main::m_bUsartInterruptMask;

// PSG interrupt masking

bool CPC88Z80Main::m_bPsgInterruptMask;

// interrupt level

int CPC88Z80Main::m_nInterruptLevel;

// priority interrupt

bool CPC88Z80Main::m_bPriorityInterrupt;

// interrupt counter

int CPC88Z80Main::m_nInterruptCounter;

// text

// text VRAM offset

uint16_t CPC88Z80Main::m_wTVRamOfs;

// text VRAM overlay disable

bool CPC88Z80Main::m_bTVRamOverlayDisable;

// text VRAM updated

bool CPC88Z80Main::m_bTVRamUpdate;

// hiragana display mode

bool CPC88Z80Main::m_bHiraMode;

// graphic

// graphic display 200 line mode

bool CPC88Z80Main::m_bGraphicDisplay200Line;

// graphic display 320 line mode

bool CPC88Z80Main::m_bGraphicDisplay320Line;

// graphic display enable

bool CPC88Z80Main::m_bGraphicDisplayEnable;

// graphic flashing mode

bool CPC88Z80Main::m_bGraphicFlashing;

// graphic display color

bool CPC88Z80Main::m_bGraphicDisplayColor;

// N80BASIC graphic color mode

bool CPC88Z80Main::m_bN80GraphicColorMode;

// graphic display analog

bool CPC88Z80Main::m_bGraphicDisplayAnalog;

// extend graphic access GVAM mode

bool CPC88Z80Main::m_bGraphicExGVAM;

// extend graphic access GAM mode

bool CPC88Z80Main::m_bGraphicExGAM;

// graphic data multiplexer control

int CPC88Z80Main::m_nGraphicExGDM;

// graphic ALU mode

int CPC88Z80Main::m_anGraphicExALU[3];

// graphic VRAM compare data

uint8_t CPC88Z80Main::m_abtGraphicExPlaneCompare[3];

// graphic VRAM pre-fetch data

uint8_t CPC88Z80Main::m_abtGraphicExPreFetch[3];

// graphic VRAM overlay disable

bool CPC88Z80Main::m_abGVRamOverlayDisable[6];

// color palette

int CPC88Z80Main::m_anColorPalette[PALETTE_COUNT];

// N80 graphic palette

uint8_t CPC88Z80Main::m_btN80GraphicPalette;

// video output control

int CPC88Z80Main::m_nAVC;

// graphic VRAM updated

bool CPC88Z80Main::m_bGVRamUpdate;

// color palette updated

bool CPC88Z80Main::m_bPaletteUpdate;

// display priority graphic VRAM1 > graphic VRAM0

bool CPC88Z80Main::m_bGraphicPriority;

// display priority text VRAM < graphic VRAM

bool CPC88Z80Main::m_bTextPriority;

// video art board mode1

uint8_t CPC88Z80Main::m_btVABMode1;

// video art board mode2

uint8_t CPC88Z80Main::m_btVABMode2;

// video art board updated

bool CPC88Z80Main::m_bVABUpdate;

// DMA

// DMA write flip-flop on

bool CPC88Z80Main::m_bDMAWriteFF_64;

// key

// key matrics

uint8_t CPC88Z80Main::m_abtKeyMatrics[15];

// interrupt vector change callback function

CPC88Z80Main::IntVectChangeCallback CPC88Z80Main::m_pIntVectChangeCallback;

// beep output callback function

CPC88Z80Main::BeepOutputCallback CPC88Z80Main::m_pBeepOutputCallback;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88Z80Main::CPC88Z80Main() :
	CZ80_1()
{
	m_pIntVectChangeCallback = NULL;
	m_pBeepOutputCallback = NULL;
}

// destructor

CPC88Z80Main::~CPC88Z80Main() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88Z80Main::RamInitialize(){
	// N88-BASIC ROM
	m_abtN88BasicRom = (uint8_t*)ps_malloc(32768);
	// N-BASIC ROM
	m_abtNBasicRom = (uint8_t*)ps_malloc(32768);
	// IE ROM
	m_abtIERom = (uint8_t*)ps_malloc(4 * 8192);
	// N80-BASIC ROM
	m_abtN80BasicRom = (uint8_t*)ps_malloc(32768);
	// N80-BASIC 4TH ROM
	m_abtN80Basic4thRom = (uint8_t*)ps_malloc(8192);
	// N80V2-BASIC ROM
	m_abtN80V2BasicRom = (uint8_t*)ps_malloc(32768);
	// N80V2 IE ROM
	m_abtN80V2IERom = (uint8_t*)ps_malloc(8192);
	// main RAM
	m_abtMainRam = (uint8_t*)ps_malloc(65536);
	// expansion RAM
	m_abtExRam = (uint8_t*)ps_malloc(EX_RAM_COUNT * 32768*4);
	// fast text VRAM
	m_abtFastTVRam = (uint8_t*)ps_malloc(4096);
	// graphic VRAM
	m_abtGVRam = (uint8_t*)ps_malloc(3 * 16384);
	// graphic VRAM(pixel access)
	m_abtGVRamX = (uint8_t*)ps_malloc(16384*8);

	// kanji font
	// kanji address
	//m_awKanjiAddress[2];
	// kanji ROM
	m_abtKanjiRom = (uint8_t*)ps_malloc(2 * 131072);
	//m_abtKanjiRom = (uint8_t*)ps_malloc(1 * 131072);

	// N80V2 font
	// PC-8001mkIISR CG ROM
	m_abtFont80SRRom = (uint8_t*)ps_malloc(8192);
	// international font ROM
	m_abtOptionFontRom = (uint8_t*)ps_malloc(2048);
}

void CPC88Z80Main::Initialize() {

	CZ80_1::Initialize();
	SetFastROMEmulation(true);
	SetWaitEmulation(false);
	SetOldCompatible(false);
	SetPcgEnable(false);
	SetOptionFont(false);
	SetBasicMode(BASICMODE_N88V1);
	SetHighSpeedMode(false);
	SetBaseClock(4);
	SetClock8MHzH(false);
	SetBootWidth40(false);
	SetBootHeight20(false);
	SetSubSystemDisable(false);
	SetVABDisable(false);
	int i;

	for (i = 0; i < 65536; i += 128) {
		memset(m_abtMainRam+i, 0x00, 16);
		memset(m_abtMainRam+i+16, 0xFF, 16);
		memset(m_abtMainRam+i+32, 0x00, 16);
		memset(m_abtMainRam+i+48, 0xFF, 16+16);
		memset(m_abtMainRam+i+80, 0x00, 16);
		memset(m_abtMainRam+i+96, 0xFF, 16);
		memset(m_abtMainRam+i+112, 0x00, 16);
	}
	memset(m_abtExRam, 0, EX_RAM_COUNT * 32768*4);
	for (i = 0; i < 4096; i += 128) {
		memset(m_abtFastTVRam+i, 0x00, 16);
		memset(m_abtFastTVRam+i+16, 0xFF, 16);
		memset(m_abtFastTVRam+i+32, 0x00, 16);
		memset(m_abtFastTVRam+i+48, 0xFF, 16+16);
		memset(m_abtFastTVRam+i+80, 0x00, 16);
		memset(m_abtFastTVRam+i+96, 0xFF, 16);
		memset(m_abtFastTVRam+i+112, 0x00, 16);
	}
	//for (i = 0; i < 3; i++) {
		memset(m_abtGVRam, 0x00, 16384 * 3);
	//}
	memset(m_abtGVRamX, 0x00, 16384*8);
	memset(m_abtKeyMatrics, 0xFF, sizeof(m_abtKeyMatrics));
}

// reset

void CPC88Z80Main::Reset() {
	Serial.println("Z80Main::Reset");
	CZ80_1::Reset();
	// check fast/slow mode
	Serial.print("BASIC MODE: ");
	Serial.println(GetBasicMode());

	switch (GetBasicMode()) {
	case BASICMODE_N88V2:
		m_bFastTVRamUse = true;
		m_bFastGVRamUse = true;
		break;
	case BASICMODE_N80V1:
		m_bFastTVRamUse = false;
		m_bFastGVRamUse = false;
		break;
	case BASICMODE_N80V2:
		m_bFastTVRamUse = false;
		m_bFastGVRamUse = true;
		break;
	default:
		m_bFastTVRamUse = IsHighSpeedMode();
		m_bFastGVRamUse = IsHighSpeedMode();
		break;
	}
	// check wait mode
	if (IsWaitEmulation()) {
		m_bAlwaysMemWait = ((GetBaseClock() == 8) && !IsClock8MHzH());
		switch (GetBasicMode()) {
		case BASICMODE_N88V2:
			m_bM1Wait = false;
			m_bTVRamWait = false;
			m_bGVRamWait = false;
			break;
		case BASICMODE_N80V1:
			m_bM1Wait = true;
			m_bTVRamWait = true;
			m_bGVRamWait = true;
			break;
		case BASICMODE_N80V2:
			m_bM1Wait = false;
			m_bTVRamWait = true;
			m_bGVRamWait = false;
			break;
		default:
			m_bM1Wait = !IsHighSpeedMode();
			m_bTVRamWait = !IsHighSpeedMode();
			m_bGVRamWait = !IsHighSpeedMode();
			break;
		}
	} else {
		m_bAlwaysMemWait = false;
		m_bM1Wait = false;
		m_bTVRamWait = false;
		m_bGVRamWait = false;
	}

	if (!IsAlwaysMemWait()) {
		// standard memory read : no wait
		ReadMemoryNBasicRom_N = ReadMemoryNBasicRom;
		ReadMemoryN80BasicRom_N = ReadMemoryN80BasicRom;
		ReadMemoryN80Basic4thRom_N = ReadMemoryN80Basic4thRom;
		ReadMemoryN80V2BasicRom_N = ReadMemoryN80V2BasicRom;
		ReadMemoryN88BasicRom_N = ReadMemoryN88BasicRom;
		ReadMemoryIERom0_N = ReadMemoryIERom0;
		ReadMemoryIERom1_N = ReadMemoryIERom1;
		ReadMemoryIERom2_N = ReadMemoryIERom2;
		ReadMemoryIERom3_N = ReadMemoryIERom3;
		ReadMemoryN80V2IERom_N = ReadMemoryN80V2IERom;
		ReadMemoryMainRam_N = ReadMemoryMainRam;
		ReadMemoryMainRamTW_N = ReadMemoryMainRamTW;
		ReadMemoryExRam_N = ReadMemoryExRam;
		ReadMemoryExRamVAB_N = ReadMemoryExRamVAB;
		ReadMemoryGVRam0_N = ReadMemoryGVRam0;
		ReadMemoryGVRam1_N = ReadMemoryGVRam1;
		ReadMemoryGVRam2_N = ReadMemoryGVRam2;
		ReadMemoryGVRamEx_N = ReadMemoryGVRamEx;
		ReadMemoryFastTVRam_N = ReadMemoryFastTVRam;
		// standard memory write : no wait
		WriteMemoryMainRam_N = WriteMemoryMainRam;
		WriteMemoryMainRamTW_N = WriteMemoryMainRamTW;
		WriteMemoryExRam_N = WriteMemoryExRam;
		WriteMemoryExRamVAB_N = WriteMemoryExRamVAB;
		WriteMemoryDisable_N = WriteMemoryDisable;
		WriteMemoryGVRam0_N = WriteMemoryGVRam0;
		WriteMemoryGVRam1_N = WriteMemoryGVRam1;
		WriteMemoryGVRam2_N = WriteMemoryGVRam2;
		WriteMemoryGVRamExALU_N = WriteMemoryGVRamExALU;
		WriteMemoryGVRamExAll_N = WriteMemoryGVRamExAll;
		WriteMemoryGVRamEx1to0_N = WriteMemoryGVRamEx1to0;
		WriteMemoryGVRamEx0to1_N = WriteMemoryGVRamEx0to1;
		WriteMemoryFastTVRam_N = WriteMemoryFastTVRam;
	} else {
		// standard memory read : wait
		ReadMemoryNBasicRom_N = ReadMemoryNBasicRom_Wait;
		ReadMemoryN80BasicRom_N = ReadMemoryN80BasicRom_Wait;
		ReadMemoryN80Basic4thRom_N = ReadMemoryN80Basic4thRom_Wait;
		ReadMemoryN80V2BasicRom_N = ReadMemoryN80V2BasicRom_Wait;
		ReadMemoryN88BasicRom_N = ReadMemoryN88BasicRom_Wait;
		ReadMemoryIERom0_N = ReadMemoryIERom0_Wait;
		ReadMemoryIERom1_N = ReadMemoryIERom1_Wait;
		ReadMemoryIERom2_N = ReadMemoryIERom2_Wait;
		ReadMemoryIERom3_N = ReadMemoryIERom3_Wait;
		ReadMemoryN80V2IERom_N = ReadMemoryN80V2IERom_Wait;
		ReadMemoryMainRam_N = ReadMemoryMainRam_Wait;
		ReadMemoryMainRamTW_N = ReadMemoryMainRamTW_Wait;
		ReadMemoryExRam_N = ReadMemoryExRam_Wait;
		ReadMemoryExRamVAB_N = ReadMemoryExRamVAB_Wait;
		ReadMemoryGVRam0_N = ReadMemoryGVRam0_Wait;
		ReadMemoryGVRam1_N = ReadMemoryGVRam1_Wait;
		ReadMemoryGVRam2_N = ReadMemoryGVRam2_Wait;
		ReadMemoryGVRamEx_N = ReadMemoryGVRamEx_Wait;
		ReadMemoryFastTVRam_N = ReadMemoryFastTVRam_Wait;
		// standard memory write : wait
		WriteMemoryMainRam_N = WriteMemoryMainRam_Wait;
		WriteMemoryMainRamTW_N = WriteMemoryMainRamTW_Wait;
		WriteMemoryExRam_N = WriteMemoryExRam_Wait;
		WriteMemoryExRamVAB_N = WriteMemoryExRamVAB_Wait;
		WriteMemoryDisable_N = WriteMemoryDisable_Wait;
		WriteMemoryGVRam0_N = WriteMemoryGVRam0_Wait;
		WriteMemoryGVRam1_N = WriteMemoryGVRam1_Wait;
		WriteMemoryGVRam2_N = WriteMemoryGVRam2_Wait;
		WriteMemoryGVRamExALU_N = WriteMemoryGVRamExALU_Wait;
		WriteMemoryGVRamExAll_N = WriteMemoryGVRamExAll_Wait;
		WriteMemoryGVRamEx1to0_N = WriteMemoryGVRamEx1to0_Wait;
		WriteMemoryGVRamEx0to1_N = WriteMemoryGVRamEx0to1_Wait;
		WriteMemoryFastTVRam_N = WriteMemoryFastTVRam_Wait;
	}
	
	if (!IsM1Wait()) {
		// M1-cycle memory read : no wait
		ReadMemoryNBasicRom_M1 = ReadMemoryNBasicRom_N;
		ReadMemoryN80BasicRom_M1 = ReadMemoryN80BasicRom_N;
		ReadMemoryN80Basic4thRom_M1 = ReadMemoryN80Basic4thRom_N;
		ReadMemoryN80V2BasicRom_M1 = ReadMemoryN80V2BasicRom_N;
		ReadMemoryN88BasicRom_M1 = ReadMemoryN88BasicRom_N;
		ReadMemoryIERom0_M1 = ReadMemoryIERom0_N;
		ReadMemoryIERom1_M1 = ReadMemoryIERom1_N;
		ReadMemoryIERom2_M1 = ReadMemoryIERom2_N;
		ReadMemoryIERom3_M1 = ReadMemoryIERom3_N;
		ReadMemoryN80V2IERom_M1 = ReadMemoryN80V2IERom_N;
		ReadMemoryMainRam_M1 = ReadMemoryMainRam_N;
		ReadMemoryMainRamTW_M1 = ReadMemoryMainRamTW_N;
		ReadMemoryExRam_M1 = ReadMemoryExRam_N;
		ReadMemoryExRamVAB_M1 = ReadMemoryExRamVAB_N;
		ReadMemoryGVRam0_M1 = ReadMemoryGVRam0_N;
		ReadMemoryGVRam1_M1 = ReadMemoryGVRam1_N;
		ReadMemoryGVRam2_M1 = ReadMemoryGVRam2_N;
		ReadMemoryGVRamEx_M1 = ReadMemoryGVRamEx_N;
	} else {
		// M1-cycle memory read : wait
		ReadMemoryNBasicRom_M1 = ReadMemoryNBasicRom_Wait;
		ReadMemoryN80BasicRom_M1 = ReadMemoryN80BasicRom_Wait;
		ReadMemoryN80Basic4thRom_M1 = ReadMemoryN80Basic4thRom_Wait;
		ReadMemoryN80V2BasicRom_M1 = ReadMemoryN80V2BasicRom_Wait;
		ReadMemoryN88BasicRom_M1 = ReadMemoryN88BasicRom_Wait;
		ReadMemoryIERom0_M1 = ReadMemoryIERom0_Wait;
		ReadMemoryIERom1_M1 = ReadMemoryIERom1_Wait;
		ReadMemoryIERom2_M1 = ReadMemoryIERom2_Wait;
		ReadMemoryIERom3_M1 = ReadMemoryIERom3_Wait;
		ReadMemoryN80V2IERom_M1 = ReadMemoryN80V2IERom_Wait;
		ReadMemoryMainRam_M1 = ReadMemoryMainRam_Wait;
		ReadMemoryMainRamTW_M1 = ReadMemoryMainRamTW_Wait;
		ReadMemoryExRam_M1 = ReadMemoryExRam_Wait;
		ReadMemoryExRamVAB_M1 = ReadMemoryExRamVAB_Wait;
		ReadMemoryGVRam0_M1 = ReadMemoryGVRam0_Wait;
		ReadMemoryGVRam1_M1 = ReadMemoryGVRam1_Wait;
		ReadMemoryGVRam2_M1 = ReadMemoryGVRam2_Wait;
		ReadMemoryGVRamEx_M1 = ReadMemoryGVRamEx_Wait;
	}


	if (!IsWaitEmulation()) {
		// fast text VRAM M1-cycle : no wait
		ReadMemoryFastTVRam_M1 = ReadMemoryFastTVRam_N;
	} else {
		// fast text VRAM M1-cycle : wait(all mode)
		ReadMemoryFastTVRam_M1 = ReadMemoryFastTVRam_Wait;
	}
	if (!m_bFastROMEmulation) {
		// no fast ROM emulation
		ReadMemoryN88BasicRomB7_M1 = ReadMemoryN88BasicRom_M1;
	} else {
		// fast ROM emulation
		ReadMemoryN88BasicRomB7_M1 = ReadMemoryN88BasicRomB7_FastEmu;
	}
	// check N80/N80V2-BASIC mode
	m_bN80BasicMode = (GetBasicMode() == BASICMODE_N80V1) ||
		(GetBasicMode() == BASICMODE_N80V2);
	// memory-I/O read/write table
	int nBlock;
	m_bNMode = (GetBasicMode() == BASICMODE_N) ||
		(GetBasicMode() == BASICMODE_N80V1) ||
		(GetBasicMode() == BASICMODE_N80V2);

	if (m_bNMode) {
		for (nBlock = 0; nBlock < 8; nBlock++) {
			switch(GetBasicMode()) {
			case BASICMODE_N:
				SetReadMemoryProc(nBlock, ReadMemoryNBasicRom_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryNBasicRom_M1);
				SetWriteMemoryProc(nBlock, WriteMemoryMainRam_N);
				break;
			case BASICMODE_N80V1:
				SetReadMemoryProc(nBlock, ReadMemoryN80BasicRom_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryN80BasicRom_M1);
				SetWriteMemoryProc(nBlock, WriteMemoryDisable_N);
				break;
			case BASICMODE_N80V2:
				SetReadMemoryProc(nBlock, ReadMemoryN80V2BasicRom_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryN80V2BasicRom_M1);
				SetWriteMemoryProc(nBlock, WriteMemoryDisable_N);
				break;
			}
		}
		SetReadMemoryProc(8, ReadMemoryMainRam_N);
		SetReadMemoryM1Proc(8, ReadMemoryMainRam_M1);
		SetWriteMemoryProc(8, WriteMemoryMainRam_N);
	} else {
		for (nBlock = 0; nBlock < 8; nBlock++) {
			SetReadMemoryProc(nBlock, ReadMemoryN88BasicRom_N);
			SetReadMemoryM1Proc(nBlock, ReadMemoryN88BasicRom_M1);
			SetWriteMemoryProc(nBlock, WriteMemoryMainRam_N);
		}
		SetReadMemoryM1Proc(7, ReadMemoryN88BasicRomB7_M1);
		//SetReadMemoryM1Proc(8, ReadMemoryN88BasicRomB7_M1);
		SetReadMemoryProc(8, ReadMemoryMainRamTW_N);
		SetReadMemoryM1Proc(8, ReadMemoryMainRamTW_M1);
		SetWriteMemoryProc(8, WriteMemoryMainRamTW_N);


	}

	for (nBlock = 9; nBlock < 15; nBlock++) {
		SetReadMemoryProc(nBlock, ReadMemoryMainRam_N);
		SetReadMemoryM1Proc(nBlock, ReadMemoryMainRam_M1);
		SetWriteMemoryProc(nBlock, WriteMemoryMainRam_N);
	}

	if (!m_bFastTVRamUse) {
		SetReadMemoryProc(15, ReadMemoryMainRam_N);
		SetReadMemoryM1Proc(15, ReadMemoryMainRam_M1);
		SetWriteMemoryProc(15, WriteMemoryMainRam_N);
	} else {
		SetReadMemoryProc(15, ReadMemoryFastTVRam_N);
		SetReadMemoryM1Proc(15, ReadMemoryFastTVRam_M1);
		SetWriteMemoryProc(15, WriteMemoryFastTVRam_N);
	}
	for (nBlock = 0; nBlock < 15; nBlock++) {
		SetReadIOProc(nBlock, ReadIO_00_0E);
		SetWriteIOProc(nBlock, WriteNONE);
	}
	for (; nBlock < 256; nBlock++) {
		SetReadIOProc(nBlock, ReadNONE);
		SetWriteIOProc(nBlock, WriteNONE);
	}
	if (IsPcgEnable()) {
		// PCG mode
		SetWriteIOProc(0x00, WriteIO_00_03_PCG);
		SetWriteIOProc(0x01, WriteIO_00_03_PCG);
		SetWriteIOProc(0x02, WriteIO_00_03_PCG);
		SetWriteIOProc(0x03, WriteIO_00_03_PCG);
		SetWriteIOProc(0x0C, WriteIO_0C_0F_PCG);
		SetWriteIOProc(0x0D, WriteIO_0C_0F_PCG);
		SetWriteIOProc(0x0E, WriteIO_0C_0F_PCG);
		SetWriteIOProc(0x0F, WriteIO_0C_0F_PCG);
	} else {
		// not PCG mode
		SetWriteIOProc(0x00, WriteIO_00_Ex);
		SetWriteIOProc(0x01, WriteNONE);
		SetWriteIOProc(0x02, WriteNONE);
		SetWriteIOProc(0x03, WriteNONE);
		SetWriteIOProc(0x0C, WriteNONE);
		SetWriteIOProc(0x0D, WriteNONE);
		SetWriteIOProc(0x0E, WriteNONE);
		SetWriteIOProc(0x0F, WriteNONE);
	}
	SetWriteIOProc(0x10, WriteIO_10);
	SetReadIOProc(0x20, ReadIO_20);
	SetWriteIOProc(0x20, WriteIO_20);
	SetReadIOProc(0x21, ReadIO_21);
	SetWriteIOProc(0x21, WriteIO_21);
	SetReadIOProc(0x30, ReadIO_30);
	SetWriteIOProc(0x30, WriteIO_30);
	SetReadIOProc(0x31, ReadIO_31);
	SetWriteIOProc(0x31, WriteIO_31);
	SetReadIOProc(0x32, ReadIO_32);
	SetWriteIOProc(0x32, WriteIO_32);
	SetWriteIOProc(0x34, WriteIO_34);
	SetWriteIOProc(0x35, WriteIO_35);
	SetReadIOProc(0x40, ReadIO_40);
	SetWriteIOProc(0x40, WriteIO_40);
	SetReadIOProc(0x44, ReadIO_44);
	SetWriteIOProc(0x44, WriteIO_44);
	SetReadIOProc(0x45, ReadIO_45);
	SetWriteIOProc(0x45, WriteIO_45);
	SetReadIOProc(0x50, ReadIO_50);
	SetWriteIOProc(0x50, WriteIO_50);
	SetReadIOProc(0x51, ReadIO_51);
	SetWriteIOProc(0x51, WriteIO_51);
	SetWriteIOProc(0x52, WriteIO_52);
	SetWriteIOProc(0x53, WriteIO_53);
	for (nBlock = 0x54; nBlock <= 0x5B; nBlock++) {
		SetWriteIOProc(nBlock, WriteIO_54_5B);
	}
	SetReadIOProc(0x5C, ReadIO_5C);
	SetWriteIOProc(0x5C, WriteIO_5C_5F);
	SetWriteIOProc(0x5D, WriteIO_5C_5F);
	SetWriteIOProc(0x5E, WriteIO_5C_5F);
	SetWriteIOProc(0x5F, WriteIO_5C_5F);
	SetWriteIOProc(0x64, WriteIO_64);
	SetWriteIOProc(0x68, WriteIO_68);
	SetReadIOProc(0x6E, ReadIO_6E);
	SetReadIOProc(0x70, ReadIO_70);
	SetWriteIOProc(0x70, WriteIO_70);
	SetReadIOProc(0x71, ReadIO_71);
	SetWriteIOProc(0x71, WriteIO_71);
	SetWriteIOProc(0x78, WriteIO_78);
	SetReadIOProc(0xB4, ReadIO_B4);
	SetWriteIOProc(0xB4, WriteIO_B4);
	SetReadIOProc(0xB5, ReadIO_B5);
	SetWriteIOProc(0xB5, WriteIO_B5);
	SetReadIOProc(0xE2, ReadIO_E2);
	SetWriteIOProc(0xE2, WriteIO_E2);
	SetReadIOProc(0xE3, ReadIO_E3);
	SetWriteIOProc(0xE3, WriteIO_E3);
	SetWriteIOProc(0xE4, WriteIO_E4);
	SetWriteIOProc(0xE6, WriteIO_E6);
	SetReadIOProc(0xE8, ReadIO_E8);
	SetWriteIOProc(0xE8, WriteIO_E8);
	SetReadIOProc(0xE9, ReadIO_E9);
	SetWriteIOProc(0xE9, WriteIO_E9);
	SetReadIOProc(0xEC, ReadIO_EC);
	SetWriteIOProc(0xEC, WriteIO_EC);
	SetReadIOProc(0xED, ReadIO_ED);
	SetWriteIOProc(0xED, WriteIO_ED);
	SetReadIOProc(0xFC, ReadIO_FC);
	SetWriteIOProc(0xFC, WriteIO_FC);
	SetReadIOProc(0xFD, ReadIO_FD);
	SetWriteIOProc(0xFD, WriteIO_FD);
	SetReadIOProc(0xFE, ReadIO_FE);
	SetWriteIOProc(0xFE, WriteIO_FE);
	SetWriteIOProc(0xFF, WriteIO_FF);

	if (IsN80BasicMode()) {
		// change N80 mode I/O port
		SetWriteIOProc(0x31, WriteIO_31_N80);
		SetReadIOProc(0x32, ReadNONE);
		SetWriteIOProc(0x32, WriteNONE);
		SetReadIOProc(0x33, ReadIO_33_N80);
		SetWriteIOProc(0x33, WriteIO_33_N80);
		SetWriteIOProc(0x35, WriteIO_35_N80);
		SetWriteIOProc(0x53, WriteIO_53_N80);
		SetWriteIOProc(0x5C, WriteIO_5C_5F_N80);
		if (GetBasicMode() == BASICMODE_N80V2) {
			SetWriteIOProc(0x5D, WriteIO_5C_5F_N80);
			SetWriteIOProc(0x5E, WriteIO_5C_5F_N80);
		}
		SetWriteIOProc(0x5F, WriteIO_5C_5F_N80);
		SetReadIOProc(0x70, ReadNONE);
		SetWriteIOProc(0x70, WriteNONE);
		SetWriteIOProc(0x71, WriteIO_71_N80);
		SetWriteIOProc(0x78, WriteNONE);
		SetWriteIOProc(0xE2, WriteIO_E2_N80);
		SetWriteIOProc(0xE3, WriteIO_E3_N80);
	}
	// kanji ROM
	m_awKanjiAddress[0] = m_awKanjiAddress[1] = 0;
	// memory bank changing and other
	m_wTextWindowOfs = 0x0000;
	m_bAllRamMode = false;
	m_nExRamCardNo = 0;
	m_nExRamBankNo = 0;
	m_btExRamAccessMode = m_abtExRamAccessModeBackup = 0x00;
	m_bNBasicRomMode = (GetBasicMode() == BASICMODE_N);
	m_bN80V2BasicRomMode = (GetBasicMode() == BASICMODE_N80V2);
	m_bDisableIERom = true;
	m_nIERomBank = 0;
	m_nGVRamBank = 3;
	m_bFastTVRamDisable = false;
	// interrupt
	m_bTimerInterruptMask = true;
	m_bVSyncInterruptMask = true;
	m_bUsartInterruptMask = true;
	m_bPsgInterruptMask = true;
	m_nInterruptLevel = 0;
	m_bPriorityInterrupt = false;
	m_nInterruptCounter = 0;
	// text
	m_wTVRamOfs = uint16_t(m_bNBasicRomMode? 0xF300: 0xF3C8);
	m_bTVRamOverlayDisable = false;
	m_bTVRamUpdate = true;
	m_bHiraMode = false;
	// graphic
	m_bGraphicDisplay200Line = !m_bNBasicRomMode;
	m_bGraphicDisplay320Line = false;
	m_bGraphicDisplayEnable = true;
	m_bGraphicFlashing = false;
	m_bGraphicDisplayColor = true;
	m_bGraphicDisplayAnalog = (GetBasicMode() == BASICMODE_N88V2);
	m_bGraphicExGVAM = false;
	m_bGraphicExGAM = false;
	m_nGraphicExGDM = 0;
	for (int nPlane = 0; nPlane < 3; nPlane++) {
		m_anGraphicExALU[nPlane] = 0;
		m_abtGraphicExPlaneCompare[nPlane] = 0x00;
		m_abtGraphicExPreFetch[nPlane] = 0x00;
	}
	for (int nPlane2 = 0; nPlane2 < 6; nPlane2++) {
		m_abGVRamOverlayDisable[nPlane2] = false;
	}
	for (int nPalNo = 0; nPalNo < 8; nPalNo++) {
		m_anColorPalette[nPalNo] =
			(((nPalNo & 1) != 0)? 0x0007: 0) |
			(((nPalNo & 2) != 0)? 0x0038: 0) |
			(((nPalNo & 4) != 0)? 0x01C0: 0);
	}
	m_anColorPalette[BACKGROUND_PALETTE] = 0x0000;
	m_nAVC = 2;
	m_bGVRamUpdate = true;
	m_bPaletteUpdate = true;
	m_bGraphicPriority = false;
	m_bTextPriority = false;
	m_btVABMode1 = 0;
	m_btVABMode2 = 0;
	m_bVABUpdate = true;
	m_bAccessingGVRam = false;
	// DMA
	m_bDMAWriteFF_64 = false;
	// beep off
	
	//m_pBeepOutputCallback(false, false);

	// old-machine compatible mode
	if (IsOldCompatible()) {
		// set I/O port mask
		switch(GetBasicMode()) {
		case BASICMODE_N88V1:
			SetWriteIOProc(0x34, WriteNONE);
			SetWriteIOProc(0x35, WriteNONE);
			SetReadIOProc(0x44, ReadNONE);
			SetWriteIOProc(0x44, WriteNONE);
			SetReadIOProc(0x45, ReadNONE);
			SetWriteIOProc(0x45, WriteNONE);
			break;
		case BASICMODE_N80V1:
			SetWriteIOProc(0x33, WriteNONE);
			SetWriteIOProc(0x34, WriteNONE);
			SetWriteIOProc(0x35, WriteNONE);
			SetReadIOProc(0x44, ReadNONE);
			SetWriteIOProc(0x44, WriteNONE);
			SetReadIOProc(0x45, ReadNONE);
			SetWriteIOProc(0x45, WriteNONE);
			SetWriteIOProc(0x52, WriteNONE);
			SetWriteIOProc(0x53, WriteNONE);
			for (nBlock = 0x54; nBlock <= 0x5B; nBlock++) {
				SetWriteIOProc(nBlock, WriteIO_54_5B);
			}
			SetWriteIOProc(0x5D, WriteNONE);
			SetWriteIOProc(0x5E, WriteNONE);
			break;
		case BASICMODE_N:
			SetWriteIOProc(0x31, WriteNONE);
			SetWriteIOProc(0x32, WriteNONE);
			SetWriteIOProc(0x34, WriteNONE);
			SetWriteIOProc(0x35, WriteNONE);
			SetReadIOProc(0x44, ReadNONE);
			SetWriteIOProc(0x44, WriteNONE);
			SetReadIOProc(0x45, ReadNONE);
			SetWriteIOProc(0x45, WriteNONE);
			SetWriteIOProc(0x52, WriteNONE);
			SetWriteIOProc(0x53, WriteNONE);
			for (nBlock = 0x54; nBlock <= 0x5B; nBlock++) {
				SetWriteIOProc(nBlock, WriteIO_54_5B);
			}
			SetWriteIOProc(0x5C, WriteNONE);
			SetWriteIOProc(0x5D, WriteNONE);
			SetWriteIOProc(0x5E, WriteNONE);
			SetWriteIOProc(0x5F, WriteNONE);
			SetReadIOProc(0x70, ReadNONE);
			SetWriteIOProc(0x70, WriteNONE);
			SetWriteIOProc(0x78, WriteNONE);
			m_bGraphicDisplayEnable = false;
			break;
		}
	}
}

////////////////////////////////////////////////////////////
// memory bank changing

// ROM/RAM bank

void CPC88Z80Main::MemBankRomRamMode(
	bool bAllRamMode, bool bNBasicRomMode)
{
	m_bAllRamMode = bAllRamMode;
	m_bNBasicRomMode = bNBasicRomMode;
	int nBlock;
	if (m_bAllRamMode) {
		for (nBlock = 0; nBlock < 9; nBlock++) {
			SetReadMemoryProc(nBlock, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(nBlock, ReadMemoryMainRam_M1);
		}
		SetWriteMemoryProc(8, WriteMemoryMainRam_N);
	} else {
		if (m_bNBasicRomMode) {
			for (nBlock = 0; nBlock < 6; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryNBasicRom_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryNBasicRom_M1);
			}
			SetReadMemoryProc(8, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(8, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(8, WriteMemoryMainRam_N);
		} else {
			for (nBlock = 0; nBlock < 6; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryN88BasicRom_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryN88BasicRom_M1);
			}
			SetReadMemoryProc(8, ReadMemoryMainRamTW_N);
			SetReadMemoryM1Proc(8, ReadMemoryMainRamTW_M1);
			SetWriteMemoryProc(8, WriteMemoryMainRamTW_N);
		}
		MemBankIERomMode(m_bDisableIERom, m_nIERomBank);
	}
	if ((m_btExRamAccessMode & 0x01) != 0) {
		if ((m_nExRamCardNo == EX_RAM_VAB) && !m_bVABDisable) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryExRamVAB_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryExRamVAB_M1);
			}
		} else if (m_nExRamCardNo < EX_RAM_COUNT) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryExRam_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryExRam_M1);
			}
		}
	}
}

// ROM/RAM bank(N80)

void CPC88Z80Main::MemBankRomRamMode_N80(
	bool bAllRamMode, int nIERomBank)
{
	m_bAllRamMode = bAllRamMode;
	m_nIERomBank = nIERomBank;
	int nBlock;
	if (m_bAllRamMode) {
		for (nBlock = 0; nBlock < 8; nBlock++) {
			SetReadMemoryProc(nBlock, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(nBlock, ReadMemoryMainRam_M1);
		}
	} else {
		if (m_bN80V2BasicRomMode) {
			for (nBlock = 0; nBlock < 6; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryN80V2BasicRom_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryN80V2BasicRom_M1);
			}
		} else {
			for (nBlock = 0; nBlock < 6; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryN80BasicRom_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryN80BasicRom_M1);
			}
		}
		MemBankIERomMode_N80(m_bDisableIERom);
	}
	MemBankExRamWriteMode_N80();
	if ((m_btExRamAccessMode & 0x01) != 0) {
		if ((m_nExRamCardNo == EX_RAM_VAB) && !m_bVABDisable) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryExRamVAB_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryExRamVAB_M1);
			}
		} else if (m_nExRamCardNo == 0) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryMainRam_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryMainRam_M1);
			}
		} else if (m_nExRamCardNo < EX_RAM_COUNT) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetReadMemoryProc(nBlock, ReadMemoryExRam_N);
				SetReadMemoryM1Proc(nBlock, ReadMemoryExRam_M1);
			}
		}
	}
}

// expansion RAM write bank

void CPC88Z80Main::MemBankExRamWriteMode() {
	int nBlock;
	for (nBlock = 0; nBlock < 8; nBlock++) {
		SetWriteMemoryProc(nBlock, WriteMemoryMainRam_N);
	}
	if ((m_btExRamAccessMode & 0x10) != 0) {
		if ((m_nExRamCardNo == EX_RAM_VAB) && !m_bVABDisable) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetWriteMemoryProc(nBlock, WriteMemoryExRamVAB_N);
			}
		} else if (m_nExRamCardNo < EX_RAM_COUNT) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetWriteMemoryProc(nBlock, WriteMemoryExRam_N);
			}
		}
	}
}

// expansion RAM write bank(N80)

void CPC88Z80Main::MemBankExRamWriteMode_N80() {
	int nBlock;
	if (m_bAllRamMode) {
		for (nBlock = 0; nBlock < 8; nBlock++) {
			SetWriteMemoryProc(nBlock, WriteMemoryMainRam_N);
		}
	} else {
		for (nBlock = 0; nBlock < 8; nBlock++) {
			SetWriteMemoryProc(nBlock, WriteMemoryDisable_N);
		}
	}
	if ((m_btExRamAccessMode & 0x10) != 0) {
		if ((m_nExRamCardNo == EX_RAM_VAB) && !m_bVABDisable) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetWriteMemoryProc(nBlock, WriteMemoryExRamVAB_N);
			}
		} else if ((m_nExRamCardNo > 0) && (m_nExRamCardNo < EX_RAM_COUNT)) {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetWriteMemoryProc(nBlock, WriteMemoryExRam_N);
			}
		} else {
			for (nBlock = 0; nBlock < 8; nBlock++) {
				SetWriteMemoryProc(nBlock, WriteMemoryMainRam_N);
			}
		}
	}
}

// IE ROM bank

void CPC88Z80Main::MemBankIERomMode(
	bool bDisableIERom, int nIERomBank)
{
	m_bDisableIERom = bDisableIERom;
	m_nIERomBank = nIERomBank;
	if (!m_bAllRamMode) {
		if (m_bDisableIERom) {
			if (m_bNBasicRomMode) {
				SetReadMemoryProc(6, ReadMemoryNBasicRom_N);
				SetReadMemoryM1Proc(6, ReadMemoryNBasicRom_M1);
				SetReadMemoryProc(7, ReadMemoryNBasicRom_N);
				SetReadMemoryM1Proc(7, ReadMemoryNBasicRom_M1);
			} else {
				SetReadMemoryProc(6, ReadMemoryN88BasicRom_N);
				SetReadMemoryM1Proc(6, ReadMemoryN88BasicRom_M1);
				SetReadMemoryProc(7, ReadMemoryN88BasicRom_N);
				SetReadMemoryM1Proc(7, ReadMemoryN88BasicRomB7_M1);
			}
		} else {
			switch (m_nIERomBank) {
			case 0:
				SetReadMemoryProc(6, ReadMemoryIERom0_N);
				SetReadMemoryM1Proc(6, ReadMemoryIERom0_M1);
				SetReadMemoryProc(7, ReadMemoryIERom0_N);
				SetReadMemoryM1Proc(7, ReadMemoryIERom0_M1);
				break;
			case 1:
				SetReadMemoryProc(6, ReadMemoryIERom1_N);
				SetReadMemoryM1Proc(6, ReadMemoryIERom1_M1);
				SetReadMemoryProc(7, ReadMemoryIERom1_N);
				SetReadMemoryM1Proc(7, ReadMemoryIERom1_M1);
				break;
			case 2:
				SetReadMemoryProc(6, ReadMemoryIERom2_N);
				SetReadMemoryM1Proc(6, ReadMemoryIERom2_M1);
				SetReadMemoryProc(7, ReadMemoryIERom2_N);
				SetReadMemoryM1Proc(7, ReadMemoryIERom2_M1);
				break;
			case 3:
				SetReadMemoryProc(6, ReadMemoryIERom3_N);
				SetReadMemoryM1Proc(6, ReadMemoryIERom3_M1);
				SetReadMemoryProc(7, ReadMemoryIERom3_N);
				SetReadMemoryM1Proc(7, ReadMemoryIERom3_M1);
				break;
			}
		}
	}
}

// IE ROM bank(N80)

void CPC88Z80Main::MemBankIERomMode_N80(
	bool bDisableIERom)
{
	m_bDisableIERom = bDisableIERom;
	if (!m_bAllRamMode) {
		if (m_bN80V2BasicRomMode) {
			if (m_bDisableIERom) {
				SetReadMemoryProc(6, ReadMemoryN80V2BasicRom_N);
				SetReadMemoryM1Proc(6, ReadMemoryN80V2BasicRom_M1);
				SetReadMemoryProc(7, ReadMemoryN80V2BasicRom_N);
				SetReadMemoryM1Proc(7, ReadMemoryN80V2BasicRom_M1);
			} else {
				SetReadMemoryProc(6, ReadMemoryN80V2IERom_N);
				SetReadMemoryM1Proc(6, ReadMemoryN80V2IERom_M1);
				SetReadMemoryProc(7, ReadMemoryN80V2IERom_N);
				SetReadMemoryM1Proc(7, ReadMemoryN80V2IERom_M1);
			}
		} else {
			if (m_nIERomBank == 0) {
				SetReadMemoryProc(6, ReadMemoryN80Basic4thRom_N);
				SetReadMemoryM1Proc(6, ReadMemoryN80Basic4thRom_M1);
				SetReadMemoryProc(7, ReadMemoryN80Basic4thRom_N);
				SetReadMemoryM1Proc(7, ReadMemoryN80Basic4thRom_M1);
			} else {
				SetReadMemoryProc(6, ReadMemoryN80BasicRom_N);
				SetReadMemoryM1Proc(6, ReadMemoryN80BasicRom_M1);
				SetReadMemoryProc(7, ReadMemoryN80BasicRom_N);
				SetReadMemoryM1Proc(7, ReadMemoryN80BasicRom_M1);
			}
		}
	}
}

// graphic VRAM bank

void CPC88Z80Main::MemBankGVRamMode(int nGVRamBank) {
	m_nGVRamBank = nGVRamBank;
	if (!m_bGraphicExGVAM) {
		switch (m_nGVRamBank) {
		case 0:
			m_bAccessingGVRam = true;
			SetReadMemoryProc(12, ReadMemoryGVRam0_N);
			SetReadMemoryM1Proc(12, ReadMemoryGVRam0_M1);
			SetWriteMemoryProc(12, WriteMemoryGVRam0_N);
			SetReadMemoryProc(13, ReadMemoryGVRam0_N);
			SetReadMemoryM1Proc(13, ReadMemoryGVRam0_M1);
			SetWriteMemoryProc(13, WriteMemoryGVRam0_N);
			SetReadMemoryProc(14, ReadMemoryGVRam0_N);
			SetReadMemoryM1Proc(14, ReadMemoryGVRam0_M1);
			SetWriteMemoryProc(14, WriteMemoryGVRam0_N);
			SetReadMemoryProc(15, ReadMemoryGVRam0_N);
			SetReadMemoryM1Proc(15, ReadMemoryGVRam0_M1);
			SetWriteMemoryProc(15, WriteMemoryGVRam0_N);
			break;
		case 1:
			m_bAccessingGVRam = true;
			SetReadMemoryProc(12, ReadMemoryGVRam1_N);
			SetReadMemoryM1Proc(12, ReadMemoryGVRam1_M1);
			SetWriteMemoryProc(12, WriteMemoryGVRam1_N);
			SetReadMemoryProc(13, ReadMemoryGVRam1_N);
			SetReadMemoryM1Proc(13, ReadMemoryGVRam1_M1);
			SetWriteMemoryProc(13, WriteMemoryGVRam1_N);
			SetReadMemoryProc(14, ReadMemoryGVRam1_N);
			SetReadMemoryM1Proc(14, ReadMemoryGVRam1_M1);
			SetWriteMemoryProc(14, WriteMemoryGVRam1_N);
			SetReadMemoryProc(15, ReadMemoryGVRam1_N);
			SetReadMemoryM1Proc(15, ReadMemoryGVRam1_M1);
			SetWriteMemoryProc(15, WriteMemoryGVRam1_N);
			break;
		case 2:
			m_bAccessingGVRam = true;
			SetReadMemoryProc(12, ReadMemoryGVRam2_N);
			SetReadMemoryM1Proc(12, ReadMemoryGVRam2_M1);
			SetWriteMemoryProc(12, WriteMemoryGVRam2_N);
			SetReadMemoryProc(13, ReadMemoryGVRam2_N);
			SetReadMemoryM1Proc(13, ReadMemoryGVRam2_M1);
			SetWriteMemoryProc(13, WriteMemoryGVRam2_N);
			SetReadMemoryProc(14, ReadMemoryGVRam2_N);
			SetReadMemoryM1Proc(14, ReadMemoryGVRam2_M1);
			SetWriteMemoryProc(14, WriteMemoryGVRam2_N);
			SetReadMemoryProc(15, ReadMemoryGVRam2_N);
			SetReadMemoryM1Proc(15, ReadMemoryGVRam2_M1);
			SetWriteMemoryProc(15, WriteMemoryGVRam2_N);
			break;
		default:
			m_bAccessingGVRam = false;
			SetReadMemoryProc(12, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(12, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(12, WriteMemoryMainRam_N);
			SetReadMemoryProc(13, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(13, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(13, WriteMemoryMainRam_N);
			SetReadMemoryProc(14, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(14, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(14, WriteMemoryMainRam_N);
			MemBankFastTVRamMode(m_bFastTVRamDisable);
			break;
		}
	}
}

// graphic VRAM bank(N80)

void CPC88Z80Main::MemBankGVRamMode_N80(int nGVRamBank) {
	m_nGVRamBank = nGVRamBank;
	if (!m_bGraphicExGVAM) {
		switch (m_nGVRamBank) {
		case 0:
			m_bAccessingGVRam = true;
			SetReadMemoryProc(8, ReadMemoryGVRam0_N);
			SetReadMemoryM1Proc(8, ReadMemoryGVRam0_M1);
			SetWriteMemoryProc(8, WriteMemoryGVRam0_N);
			SetReadMemoryProc(9, ReadMemoryGVRam0_N);
			SetReadMemoryM1Proc(9, ReadMemoryGVRam0_M1);
			SetWriteMemoryProc(9, WriteMemoryGVRam0_N);
			SetReadMemoryProc(10, ReadMemoryGVRam0_N);
			SetReadMemoryM1Proc(10, ReadMemoryGVRam0_M1);
			SetWriteMemoryProc(10, WriteMemoryGVRam0_N);
			SetReadMemoryProc(11, ReadMemoryGVRam0_N);
			SetReadMemoryM1Proc(11, ReadMemoryGVRam0_M1);
			SetWriteMemoryProc(11, WriteMemoryGVRam0_N);
			break;
		case 1:
			m_bAccessingGVRam = true;
			SetReadMemoryProc(8, ReadMemoryGVRam1_N);
			SetReadMemoryM1Proc(8, ReadMemoryGVRam1_M1);
			SetWriteMemoryProc(8, WriteMemoryGVRam1_N);
			SetReadMemoryProc(9, ReadMemoryGVRam1_N);
			SetReadMemoryM1Proc(9, ReadMemoryGVRam1_M1);
			SetWriteMemoryProc(9, WriteMemoryGVRam1_N);
			SetReadMemoryProc(10, ReadMemoryGVRam1_N);
			SetReadMemoryM1Proc(10, ReadMemoryGVRam1_M1);
			SetWriteMemoryProc(10, WriteMemoryGVRam1_N);
			SetReadMemoryProc(11, ReadMemoryGVRam1_N);
			SetReadMemoryM1Proc(11, ReadMemoryGVRam1_M1);
			SetWriteMemoryProc(11, WriteMemoryGVRam1_N);
			break;
		case 2:
			m_bAccessingGVRam = true;
			SetReadMemoryProc(8, ReadMemoryGVRam2_N);
			SetReadMemoryM1Proc(8, ReadMemoryGVRam2_M1);
			SetWriteMemoryProc(8, WriteMemoryGVRam2_N);
			SetReadMemoryProc(9, ReadMemoryGVRam2_N);
			SetReadMemoryM1Proc(9, ReadMemoryGVRam2_M1);
			SetWriteMemoryProc(9, WriteMemoryGVRam2_N);
			SetReadMemoryProc(10, ReadMemoryGVRam2_N);
			SetReadMemoryM1Proc(10, ReadMemoryGVRam2_M1);
			SetWriteMemoryProc(10, WriteMemoryGVRam2_N);
			SetReadMemoryProc(11, ReadMemoryGVRam2_N);
			SetReadMemoryM1Proc(11, ReadMemoryGVRam2_M1);
			SetWriteMemoryProc(11, WriteMemoryGVRam2_N);
			break;
		default:
			m_bAccessingGVRam = false;
			SetReadMemoryProc(8, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(8, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(8, WriteMemoryMainRam_N);
			SetReadMemoryProc(9, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(9, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(9, WriteMemoryMainRam_N);
			SetReadMemoryProc(10, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(10, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(10, WriteMemoryMainRam_N);
			SetReadMemoryProc(11, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(11, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(11, WriteMemoryMainRam_N);
			break;
		}
	}
}

// extend graphic VRAM bank

void CPC88Z80Main::MemBankGVRamModeEx(
	bool bGraphicExGAM, int nGraphicExGDM)
{
	m_bGraphicExGAM = bGraphicExGAM;
	m_nGraphicExGDM = nGraphicExGDM;
	if (m_bGraphicExGVAM) {
		if (m_bGraphicExGAM) {
			m_bAccessingGVRam = true;
			SetReadMemoryProc(12, ReadMemoryGVRamEx_N);
			SetReadMemoryM1Proc(12, ReadMemoryGVRamEx_M1);
			SetReadMemoryProc(13, ReadMemoryGVRamEx_N);
			SetReadMemoryM1Proc(13, ReadMemoryGVRamEx_M1);
			SetReadMemoryProc(14, ReadMemoryGVRamEx_N);
			SetReadMemoryM1Proc(14, ReadMemoryGVRamEx_M1);
			SetReadMemoryProc(15, ReadMemoryGVRamEx_N);
			SetReadMemoryM1Proc(15, ReadMemoryGVRamEx_M1);
			switch (m_nGraphicExGDM) {
			case 0:
				SetWriteMemoryProc(12, WriteMemoryGVRamExALU_N);
				SetWriteMemoryProc(13, WriteMemoryGVRamExALU_N);
				SetWriteMemoryProc(14, WriteMemoryGVRamExALU_N);
				SetWriteMemoryProc(15, WriteMemoryGVRamExALU_N);
				break;
			case 1:
				SetWriteMemoryProc(12, WriteMemoryGVRamExAll_N);
				SetWriteMemoryProc(13, WriteMemoryGVRamExAll_N);
				SetWriteMemoryProc(14, WriteMemoryGVRamExAll_N);
				SetWriteMemoryProc(15, WriteMemoryGVRamExAll_N);
				break;
			case 2:
				SetWriteMemoryProc(12, WriteMemoryGVRamEx1to0_N);
				SetWriteMemoryProc(13, WriteMemoryGVRamEx1to0_N);
				SetWriteMemoryProc(14, WriteMemoryGVRamEx1to0_N);
				SetWriteMemoryProc(15, WriteMemoryGVRamEx1to0_N);
				break;
			case 3:
				SetWriteMemoryProc(12, WriteMemoryGVRamEx0to1_N);
				SetWriteMemoryProc(13, WriteMemoryGVRamEx0to1_N);
				SetWriteMemoryProc(14, WriteMemoryGVRamEx0to1_N);
				SetWriteMemoryProc(15, WriteMemoryGVRamEx0to1_N);
				break;
			}
		} else {
			m_bAccessingGVRam = false;
			SetReadMemoryProc(12, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(12, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(12, WriteMemoryMainRam_N);
			SetReadMemoryProc(13, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(13, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(13, WriteMemoryMainRam_N);
			SetReadMemoryProc(14, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(14, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(14, WriteMemoryMainRam_N);
			MemBankFastTVRamMode(m_bFastTVRamDisable);
		}
	}
}

// extend graphic VRAM bank(N80)

void CPC88Z80Main::MemBankGVRamModeEx_N80(
	bool bGraphicExGAM, int nGraphicExGDM)
{
	m_bGraphicExGAM = bGraphicExGAM;
	m_nGraphicExGDM = nGraphicExGDM;
	if (m_bGraphicExGVAM) {
		if (m_bGraphicExGAM) {
			m_bAccessingGVRam = true;
			SetReadMemoryProc(8, ReadMemoryGVRamEx_N);
			SetReadMemoryM1Proc(8, ReadMemoryGVRamEx_M1);
			SetReadMemoryProc(9, ReadMemoryGVRamEx_N);
			SetReadMemoryM1Proc(9, ReadMemoryGVRamEx_M1);
			SetReadMemoryProc(10, ReadMemoryGVRamEx_N);
			SetReadMemoryM1Proc(10, ReadMemoryGVRamEx_M1);
			SetReadMemoryProc(11, ReadMemoryGVRamEx_N);
			SetReadMemoryM1Proc(11, ReadMemoryGVRamEx_M1);
			switch (m_nGraphicExGDM) {
			case 0:
				SetWriteMemoryProc( 8, WriteMemoryGVRamExALU_N);
				SetWriteMemoryProc( 9, WriteMemoryGVRamExALU_N);
				SetWriteMemoryProc(10, WriteMemoryGVRamExALU_N);
				SetWriteMemoryProc(11, WriteMemoryGVRamExALU_N);
				break;
			case 1:
				SetWriteMemoryProc( 8, WriteMemoryGVRamExAll_N);
				SetWriteMemoryProc( 9, WriteMemoryGVRamExAll_N);
				SetWriteMemoryProc(10, WriteMemoryGVRamExAll_N);
				SetWriteMemoryProc(11, WriteMemoryGVRamExAll_N);
				break;
			case 2:
				SetWriteMemoryProc( 8, WriteMemoryGVRamEx1to0_N);
				SetWriteMemoryProc( 9, WriteMemoryGVRamEx1to0_N);
				SetWriteMemoryProc(10, WriteMemoryGVRamEx1to0_N);
				SetWriteMemoryProc(11, WriteMemoryGVRamEx1to0_N);
				break;
			case 3:
				SetWriteMemoryProc( 8, WriteMemoryGVRamEx0to1_N);
				SetWriteMemoryProc( 9, WriteMemoryGVRamEx0to1_N);
				SetWriteMemoryProc(10, WriteMemoryGVRamEx0to1_N);
				SetWriteMemoryProc(11, WriteMemoryGVRamEx0to1_N);
				break;
			}
		} else {
			m_bAccessingGVRam = false;
			SetReadMemoryProc(8, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(8, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(8, WriteMemoryMainRam_N);
			SetReadMemoryProc(9, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(9, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(9, WriteMemoryMainRam_N);
			SetReadMemoryProc(10, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(10, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(10, WriteMemoryMainRam_N);
			SetReadMemoryProc(11, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(11, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(11, WriteMemoryMainRam_N);
		}
	}
}

// fast text VRAM bank

void CPC88Z80Main::MemBankFastTVRamMode(bool bFastTVRamDisable) {
	m_bFastTVRamDisable = bFastTVRamDisable;
	if ((!m_bGraphicExGVAM && (m_nGVRamBank == 3)) ||
		(m_bGraphicExGVAM && !m_bGraphicExGAM))
	{
		if (m_bFastTVRamDisable || !m_bFastTVRamUse) {
			SetReadMemoryProc(15, ReadMemoryMainRam_N);
			SetReadMemoryM1Proc(15, ReadMemoryMainRam_M1);
			SetWriteMemoryProc(15, WriteMemoryMainRam_N);
		} else {
			SetReadMemoryProc(15, ReadMemoryFastTVRam_N);
			SetReadMemoryM1Proc(15, ReadMemoryFastTVRam_M1);
			SetWriteMemoryProc(15, WriteMemoryFastTVRam_N);
		}
	}
}

////////////////////////////////////////////////////////////
// memory operation

// dummy read

uint8_t CPC88Z80Main::ReadNONE(int /*nAddress*/) {
	return 0xFF;
}

// dummy write

void CPC88Z80Main::WriteNONE(int /*nAddress*/, uint8_t /*btData*/) {
}

// N-BASIC ROM read

uint8_t CPC88Z80Main::ReadMemoryNBasicRom(int nAddress) {
	return m_abtNBasicRom[nAddress];
}

// N-BASIC ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryNBasicRom_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtNBasicRom[nAddress];
}

// N80-BASIC ROM read

uint8_t CPC88Z80Main::ReadMemoryN80BasicRom(int nAddress) {
	return m_abtN80BasicRom[nAddress];
}

// N80-BASIC ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryN80BasicRom_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtN80BasicRom[nAddress];
}

// N80-BASIC 4TH ROM read

uint8_t CPC88Z80Main::ReadMemoryN80Basic4thRom(int nAddress) {
	return m_abtN80Basic4thRom[nAddress & 0x1FFF];
}

// N80-BASIC 4TH ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryN80Basic4thRom_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtN80Basic4thRom[nAddress & 0x1FFF];
}

// N80V2-BASIC ROM read

uint8_t CPC88Z80Main::ReadMemoryN80V2BasicRom(int nAddress) {
	return m_abtN80V2BasicRom[nAddress];
}

// N80V2-BASIC ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryN80V2BasicRom_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtN80V2BasicRom[nAddress];
}

// N88-BASIC ROM read

uint8_t CPC88Z80Main::ReadMemoryN88BasicRom(int nAddress) {
	return m_abtN88BasicRom[nAddress];
}

// N88-BASIC ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryN88BasicRom_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtN88BasicRom[nAddress];
}

// N88-BASIC ROM read(bank7 fast ROM emulation)

uint8_t CPC88Z80Main::ReadMemoryN88BasicRomB7_FastEmu(int nAddress) {
	if (nAddress == 0x7F87) {
		uint16_t wQueueTable = ReadMemoryW(0xE6CB);
		wQueueTable += 6;
		uint8_t btPutOfs = ReadMemory(wQueueTable),
			btGetOfs = ReadMemory(uint16_t(wQueueTable+1)),
			btBackChar = ReadMemory(uint16_t(wQueueTable+2));
		if (btBackChar != 0) {
			RegA().Set(btBackChar);
			UpdateRegF(C_FLAG | Z_FLAG, Z_FLAG);
			return 0xC9;
		} else if (btPutOfs != btGetOfs) {
			uint8_t btQueueLength = ReadMemory(uint16_t(wQueueTable+3));
			btGetOfs++;
			btGetOfs &= btQueueLength;
			WriteMemory(uint16_t(wQueueTable+1), btGetOfs);
			uint16_t wQueueAddress = ReadMemoryW(uint16_t(wQueueTable+4));
			uint8_t btData2 = ReadMemory(uint16_t(wQueueAddress+btGetOfs));
			RegA().Set(btData2);
			UpdateRegF(C_FLAG | Z_FLAG, Z_FLAG);
			return 0xC9;
		} else if (Usart().IsExistData() && !Usart().IsWaiting()) {
			RegA().Set(Usart().ReadData());
			UpdateRegF(C_FLAG | Z_FLAG, Z_FLAG);
			return 0xC9;
		}
	}
	return m_abtN88BasicRom[nAddress];
}

// IE0 ROM read

uint8_t CPC88Z80Main::ReadMemoryIERom0(int nAddress) {
	return m_abtIERom[0 * 8192 + (nAddress & 0x1FFF)];
}

// IE0 ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryIERom0_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtIERom[0 * 8192 + (nAddress & 0x1FFF)];
}

// IE1 ROM read

uint8_t CPC88Z80Main::ReadMemoryIERom1(int nAddress) {
	return m_abtIERom[1 * 8192 + (nAddress & 0x1FFF)];
}

// IE1 ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryIERom1_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtIERom[1 * 8192 + (nAddress & 0x1FFF)];
}

// IE2 ROM read

uint8_t CPC88Z80Main::ReadMemoryIERom2(int nAddress) {
	return m_abtIERom[2 * 8192 + (nAddress & 0x1FFF)];
}

// IE2 ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryIERom2_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtIERom[2 * 8192 + (nAddress & 0x1FFF)];
}

// IE3 ROM read

uint8_t CPC88Z80Main::ReadMemoryIERom3(int nAddress) {
	return m_abtIERom[3 * 8192 + (nAddress & 0x1FFF)];
}

// IE3 ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryIERom3_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtIERom[3 * 8192 + (nAddress & 0x1FFF)];
}

// N80V2 IE ROM read

uint8_t CPC88Z80Main::ReadMemoryN80V2IERom(int nAddress) {
	return m_abtN80V2IERom[nAddress & 0x1FFF];
}

// N80V2 IE ROM read(wait)

uint8_t CPC88Z80Main::ReadMemoryN80V2IERom_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtN80V2IERom[nAddress & 0x1FFF];
}

// main RAM read

uint8_t CPC88Z80Main::ReadMemoryMainRam(int nAddress) {
	return m_abtMainRam[nAddress];
}

// main RAM read(wait)

uint8_t CPC88Z80Main::ReadMemoryMainRam_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtMainRam[nAddress];
}

// main RAM write

void CPC88Z80Main::WriteMemoryMainRam(int nAddress, uint8_t btData) {
	m_abtMainRam[nAddress] = btData;
}

// main RAM write(wait)

void CPC88Z80Main::WriteMemoryMainRam_Wait(int nAddress, uint8_t btData) {
	AddExecClock(1);
	m_abtMainRam[nAddress] = btData;
}

// main RAM read(text window)

uint8_t CPC88Z80Main::ReadMemoryMainRamTW(int nAddress) {
	if ((nAddress & 0xFC00) == 0x8000) {
		return m_abtMainRam[m_wTextWindowOfs+(nAddress & 0x03FF)];
	}
	return m_abtMainRam[nAddress];
}

// main RAM read(text window / wait)

uint8_t CPC88Z80Main::ReadMemoryMainRamTW_Wait(int nAddress) {
	AddExecClock(1);
	if ((nAddress & 0xFC00) == 0x8000) {
		return m_abtMainRam[m_wTextWindowOfs+(nAddress & 0x03FF)];
	}
	return m_abtMainRam[nAddress];
}

// main RAM write(text window)

void CPC88Z80Main::WriteMemoryMainRamTW(int nAddress, uint8_t btData) {
	if ((nAddress & 0xFC00) == 0x8000) {
		m_abtMainRam[m_wTextWindowOfs+(nAddress & 0x03FF)] = btData;
	} else {
		m_abtMainRam[nAddress] = btData;
	}
}

// main RAM write(text window / wait)

void CPC88Z80Main::WriteMemoryMainRamTW_Wait(int nAddress, uint8_t btData) {
	AddExecClock(1);
	if ((nAddress & 0xFC00) == 0x8000) {
		m_abtMainRam[m_wTextWindowOfs+(nAddress & 0x03FF)] = btData;
	} else {
		m_abtMainRam[nAddress] = btData;
	}
}

// expansion RAM read

uint8_t CPC88Z80Main::ReadMemoryExRam(int nAddress) {
	return m_abtExRam[m_nExRamCardNo * 32768*4 + m_nExRamBankNo*32768+nAddress];
}

// expansion RAM read(wait)

uint8_t CPC88Z80Main::ReadMemoryExRam_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtExRam[m_nExRamCardNo * 32768*4 + m_nExRamBankNo*32768+nAddress];
}

// expansion RAM write

void CPC88Z80Main::WriteMemoryExRam(int nAddress, uint8_t btData) {
	m_abtExRam[m_nExRamCardNo * 32768*4 + m_nExRamBankNo*32768+nAddress] = btData;
}

// expansion RAM write(wait)

void CPC88Z80Main::WriteMemoryExRam_Wait(int nAddress, uint8_t btData) {
	AddExecClock(1);
	m_abtExRam[m_nExRamCardNo * 32768*4 + m_nExRamBankNo*32768+nAddress] = btData;
}

// expansion RAM read(video art board)

uint8_t CPC88Z80Main::ReadMemoryExRamVAB(int nAddress) {
	return m_abtExRam[m_nExRamCardNo * 32768*4 + m_nExRamBankNo*32768+nAddress];
}

// expansion RAM read(video art board / wait)

uint8_t CPC88Z80Main::ReadMemoryExRamVAB_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtExRam[m_nExRamCardNo * 32768*4 + m_nExRamBankNo*32768+nAddress];
}

// expansion RAM write(video art board)

void CPC88Z80Main::WriteMemoryExRamVAB(int nAddress, uint8_t btData) {
	m_abtExRam[m_nExRamCardNo * 32768*4 + m_nExRamBankNo*32768+nAddress] = btData;
	SetVABUpdate(true);
}

// expansion RAM write(video art board / wait)

void CPC88Z80Main::WriteMemoryExRamVAB_Wait(int nAddress, uint8_t btData) {
	AddExecClock(1);
	m_abtExRam[m_nExRamCardNo * 32768*4 + m_nExRamBankNo*32768+nAddress] = btData;
	SetVABUpdate(true);
}

// RAM write disable

void CPC88Z80Main::WriteMemoryDisable(int, uint8_t) {
}

// RAM write disable(wait)

void CPC88Z80Main::WriteMemoryDisable_Wait(int, uint8_t) {
	AddExecClock(1);
}

// graphic VRAM0 read

uint8_t CPC88Z80Main::ReadMemoryGVRam0(int nAddress) {
	return m_abtGVRam[0 * 16384 + (nAddress & 0x3FFF)];
}

// graphic VRAM0 read(wait)

uint8_t CPC88Z80Main::ReadMemoryGVRam0_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtGVRam[0 * 16384 + (nAddress & 0x3FFF)];
}

// graphic VRAM0 write

void CPC88Z80Main::WriteMemoryGVRam0(int nAddress, uint8_t btData) {
	m_abtGVRam[0 * 16384 + (nAddress & 0x3FFF)] = btData;
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// graphic VRAM0 write(wait)

void CPC88Z80Main::WriteMemoryGVRam0_Wait(int nAddress, uint8_t btData) {
	AddExecClock(1);
	m_abtGVRam[0 * 16384 + (nAddress & 0x3FFF)] = btData;
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// graphic VRAM1 read

uint8_t CPC88Z80Main::ReadMemoryGVRam1(int nAddress) {
	return m_abtGVRam[1 * 16384 + (nAddress & 0x3FFF)];
}

// graphic VRAM1 read(wait)

uint8_t CPC88Z80Main::ReadMemoryGVRam1_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtGVRam[1 * 16384 + (nAddress & 0x3FFF)];
}

// graphic VRAM1 write

void CPC88Z80Main::WriteMemoryGVRam1(int nAddress, uint8_t btData) {
	m_abtGVRam[1 * 16384 + (nAddress & 0x3FFF)] = btData;
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// graphic VRAM1 write(wait)

void CPC88Z80Main::WriteMemoryGVRam1_Wait(int nAddress, uint8_t btData) {
	AddExecClock(1);
	m_abtGVRam[1 * 16384 + (nAddress & 0x3FFF)] = btData;
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// graphic VRAM2 read

uint8_t CPC88Z80Main::ReadMemoryGVRam2(int nAddress) {
	return m_abtGVRam[2 * 16384 + (nAddress & 0x3FFF)];
}

// graphic VRAM2 read(wait)

uint8_t CPC88Z80Main::ReadMemoryGVRam2_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtGVRam[2 * 16384 + (nAddress & 0x3FFF)];
}

// graphic VRAM2 write

void CPC88Z80Main::WriteMemoryGVRam2(int nAddress, uint8_t btData) {
	m_abtGVRam[2 * 16384 + (nAddress & 0x3FFF)] = btData;
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// graphic VRAM2 write(wait)

void CPC88Z80Main::WriteMemoryGVRam2_Wait(int nAddress, uint8_t btData) {
	AddExecClock(1);
	m_abtGVRam[2 * 16384 + (nAddress & 0x3FFF)] = btData;
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// extend graphic VRAM read

uint8_t CPC88Z80Main::ReadMemoryGVRamEx(int nAddress) {
	int nAddress2 = nAddress & 0x3FFF;
	m_abtGraphicExPreFetch[0] = m_abtGVRam[0 * 16384 + nAddress2];
	m_abtGraphicExPreFetch[1] = m_abtGVRam[1 * 16384 + nAddress2];
	m_abtGraphicExPreFetch[2] = m_abtGVRam[2 * 16384 + nAddress2];
	return uint8_t(
		(m_abtGraphicExPreFetch[0] ^ m_abtGraphicExPlaneCompare[0]) &
		(m_abtGraphicExPreFetch[1] ^ m_abtGraphicExPlaneCompare[1]) &
		(m_abtGraphicExPreFetch[2] ^ m_abtGraphicExPlaneCompare[2]));
}

// extend graphic VRAM read(wait)

uint8_t CPC88Z80Main::ReadMemoryGVRamEx_Wait(int nAddress) {
	AddExecClock(1);
	int nAddress2 = nAddress & 0x3FFF;
	m_abtGraphicExPreFetch[0] = m_abtGVRam[0 * 16384 + nAddress2];
	m_abtGraphicExPreFetch[1] = m_abtGVRam[1 * 16384 + nAddress2];
	m_abtGraphicExPreFetch[2] = m_abtGVRam[2 * 16384 + nAddress2];
	return uint8_t(
		(m_abtGraphicExPreFetch[0] ^ m_abtGraphicExPlaneCompare[0]) &
		(m_abtGraphicExPreFetch[1] ^ m_abtGraphicExPlaneCompare[1]) &
		(m_abtGraphicExPreFetch[2] ^ m_abtGraphicExPlaneCompare[2]));
}

// extend graphic VRAM write(ALU)

void CPC88Z80Main::WriteMemoryGVRamExALU(int nAddress, uint8_t btData) {
	int nAddress2 = nAddress & 0x3FFF;
	for (int nPlane = 0; nPlane < 3; nPlane++) {
		switch (m_anGraphicExALU[nPlane]) {
		case 0:
			m_abtGVRam[nPlane * 16384 + nAddress2] &= uint8_t(~btData);
			break;
		case 1:
			m_abtGVRam[nPlane * 16384 + nAddress2] |= btData;
			break;
		case 2:
			m_abtGVRam[nPlane * 16384 + nAddress2] ^= btData;
			break;
		}
	}
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// extend graphic VRAM write(ALU / wait)

void CPC88Z80Main::WriteMemoryGVRamExALU_Wait(int nAddress, uint8_t btData) {
	AddExecClock(1);
	int nAddress2 = nAddress & 0x3FFF;
	for (int nPlane = 0; nPlane < 3; nPlane++) {
		switch (m_anGraphicExALU[nPlane]) {
		case 0:
			m_abtGVRam[nPlane * 16384 + nAddress2] &= uint8_t(~btData);
			break;
		case 1:
			m_abtGVRam[nPlane * 16384 + nAddress2] |= btData;
			break;
		case 2:
			m_abtGVRam[nPlane * 16384 + nAddress2] ^= btData;
			break;
		}
	}
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// extend graphic VRAM write(ALL)

void CPC88Z80Main::WriteMemoryGVRamExAll(int nAddress, uint8_t /*btData*/) {
	int nAddress2 = nAddress & 0x3FFF;
	m_abtGVRam[0 * 16384 + nAddress2] = m_abtGraphicExPreFetch[0];
	m_abtGVRam[1 * 16384 + nAddress2] = m_abtGraphicExPreFetch[1];
	m_abtGVRam[2 * 16384 + nAddress2] = m_abtGraphicExPreFetch[2];
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// extend graphic VRAM write(ALL / wait)

void CPC88Z80Main::WriteMemoryGVRamExAll_Wait(int nAddress, uint8_t /*btData*/) {
	AddExecClock(1);
	int nAddress2 = nAddress & 0x3FFF;
	m_abtGVRam[0 * 16384 + nAddress2] = m_abtGraphicExPreFetch[0];
	m_abtGVRam[1 * 16384 + nAddress2] = m_abtGraphicExPreFetch[1];
	m_abtGVRam[2 * 16384 + nAddress2] = m_abtGraphicExPreFetch[2];
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// extend graphic VRAM write(1 -> 0)

void CPC88Z80Main::WriteMemoryGVRamEx1to0(int nAddress, uint8_t /*btData*/) {
	m_abtGVRam[0 * 16384 + (nAddress & 0x3FFF)] = m_abtGraphicExPreFetch[1];
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// extend graphic VRAM write(1 -> 0 / wait)

void CPC88Z80Main::WriteMemoryGVRamEx1to0_Wait(int nAddress, uint8_t /*btData*/) {
	AddExecClock(1);
	m_abtGVRam[0 * 16384 + (nAddress & 0x3FFF)] = m_abtGraphicExPreFetch[1];
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// extend graphic VRAM write(0 -> 1)

void CPC88Z80Main::WriteMemoryGVRamEx0to1(int nAddress, uint8_t /*btData*/) {
	m_abtGVRam[1 * 16384 + (nAddress & 0x3FFF)] = m_abtGraphicExPreFetch[0];
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// extend graphic VRAM write(0 -> 1 / wait)

void CPC88Z80Main::WriteMemoryGVRamEx0to1_Wait(int nAddress, uint8_t /*btData*/) {
	AddExecClock(1);
	m_abtGVRam[1 * 16384 + (nAddress & 0x3FFF)] = m_abtGraphicExPreFetch[0];
	UpdateGVRamX(nAddress);
	SetGVRamUpdate(true);
}

// fast text VRAM read

uint8_t CPC88Z80Main::ReadMemoryFastTVRam(int nAddress) {
	return m_abtFastTVRam[nAddress & 0x0FFF];
}

// fast text VRAM read(wait)

uint8_t CPC88Z80Main::ReadMemoryFastTVRam_Wait(int nAddress) {
	AddExecClock(1);
	return m_abtFastTVRam[nAddress & 0x0FFF];
}

// fast text VRAM write

void CPC88Z80Main::WriteMemoryFastTVRam(int nAddress, uint8_t btData) {
	//Serial.print("TextWrite:");
	//Serial.print(nAddress, HEX);
	//Serial.print(":");
	//Serial.println(btData, HEX);
	m_abtFastTVRam[nAddress & 0x0FFF] = btData;
}

// fast text VRAM write(wait)

void CPC88Z80Main::WriteMemoryFastTVRam_Wait(int nAddress, uint8_t btData) {
	Serial.print("TextWrite Wait:");
	Serial.print(nAddress, HEX);
	Serial.print(":");
	Serial.println(btData, HEX);
	AddExecClock(1);
	m_abtFastTVRam[nAddress & 0x0FFF] = btData;
}

// I/O port 00-0E read

uint8_t CPC88Z80Main::ReadIO_00_0E(int nAddress) {
	return m_abtKeyMatrics[nAddress];
}

// I/O port 00 write(fast tape loading)

void CPC88Z80Main::WriteIO_00_Ex(int /*nAddress*/, uint8_t /*btData*/) {
	int nData;
	do {
		if ((nData = Usart().ReadData2()) < 0) {
			return;
		}
	} while (nData != 0x3A);
	if ((nData = Usart().ReadData2()) < 0) {
		return;
	}
	int nAddressX = uint16_t(nData*256);
	uint8_t btSum = uint8_t(nData);
	if ((nData = Usart().ReadData2()) < 0) {
		return;
	}
	uint16_t wAddress = uint16_t(nAddressX+nData);
	btSum = uint8_t(btSum+nData);
	if ((nData = Usart().ReadData2()) < 0) {
		return;
	}
	btSum = uint8_t(btSum+nData);
	if (btSum != 0) {
		return;
	}
	while (true) {
		do {
			if ((nData = Usart().ReadData2()) < 0) {
				return;
			}
		} while (nData != 0x3A);
		if ((nData = Usart().ReadData2()) < 0) {
			return;
		}
		int nCount = nData;
		if (nCount <= 0) {
			break;
		}
		btSum = uint8_t(nData);
		for (int i = 0; i < nCount; i++) {
			if ((nData = Usart().ReadData2()) < 0) {
				return;
			}
			btSum = uint8_t(btSum+nData);
			WriteMemory(wAddress, uint8_t(nData));
			wAddress++;
		}
		if ((nData = Usart().ReadData2()) < 0) {
			return;
		}
		btSum = uint8_t(btSum+nData);
		if (btSum != 0) {
			return;
		}
	}
}

// I/O port 00-02 write(PCG)

void CPC88Z80Main::WriteIO_00_03_PCG(int nAddress, uint8_t btData) {
	Pcg().WritePcgPort(nAddress, btData);
}

// I/O port 0C-0F write(PCG)

void CPC88Z80Main::WriteIO_0C_0F_PCG(int nAddress, uint8_t btData) {
	Pcg().WriteITimerPort(nAddress-0x0C, btData);
}

// I/O port 10 write

void CPC88Z80Main::WriteIO_10(int /*nAddress*/, uint8_t btData) {
	Calendar().SetCalendarCommand(btData & 0x07);
	Calendar().SetCalendarDataOut((btData & 0x08) != 0);
	//ParallelDevice().SetData(btData);
}

// I/O port 20 read

uint8_t CPC88Z80Main::ReadIO_20(int /*nAddress*/) {
	return Usart().ReadData();
}

// I/O port 20 write

void CPC88Z80Main::WriteIO_20(int /*nAddress*/, uint8_t btData) {
	Usart().WriteData(btData);
}

// I/O port 21 read

uint8_t CPC88Z80Main::ReadIO_21(int /*nAddress*/) {
	return Usart().ReadStatus();
}

// I/O port 21 write

void CPC88Z80Main::WriteIO_21(int /*nAddress*/, uint8_t btData) {
	Usart().WriteControl(btData);
}

// I/O port 30 read

uint8_t CPC88Z80Main::ReadIO_30(int /*nAddress*/) {
	return uint8_t(
		((GetBasicMode() != BASICMODE_N)? 0x01: 0) |
		((GetBasicMode() != BASICMODE_N80V2)? 0x02: 0) |
		0xC0 |
		(IsBootWidth40()? 0x04: 0) |
		(IsBootHeight20()? 0x08: 0));
}

// I/O port 30 write

void CPC88Z80Main::WriteIO_30(int /*nAddress*/, uint8_t btData) {
	Crtc().SetWidth80((btData & 0x01) != 0);
	Usart().SetSpaceCarrier((btData & 0x04) != 0);
	Usart().SetMotorOn((btData & 0x08) != 0);
	Usart().SetChannelMode((btData >> 4) & 0x03);
}

// I/O port 31 read

uint8_t CPC88Z80Main::ReadIO_31(int /*nAddress*/) {
	return uint8_t(
		0x39 |
		(IsHighSpeedMode()? 0x40: 0) |
		((GetBasicMode() != BASICMODE_N88V2)? 0x80: 0));
}

// I/O port 31 write

void CPC88Z80Main::WriteIO_31(int /*nAddress*/, uint8_t btData) {
	bool bG200Line = (btData & 0x01) != 0,
		bGEnable = (btData & 0x08) != 0,
		bGColor = (btData & 0x10) != 0;
	if ((bG200Line != IsGraphicDisplay200Line()) ||
		(bGEnable != IsGraphicDisplayEnable()) ||
		(bGColor != IsGraphicDisplayColor()))
	{
		SetGVRamUpdate(true);
	}
	SetGraphicDisplay200Line(bG200Line);
	MemBankRomRamMode(
		(btData & 0x02) != 0,
		(btData & 0x04) != 0);
	SetGraphicDisplayEnable(bGEnable);
	Crtc().SetGraphicDisplayEnable(bGEnable);
	SetGraphicDisplayColor(bGColor);
}

// I/O port 31 write(N80)

void CPC88Z80Main::WriteIO_31_N80(int /*nAddress*/, uint8_t btData) {
	bool bGEnable = (btData & 0x08) != 0,
		bGColor = (btData & 0x10) != 0,
		bGUpdate;
	bGUpdate = (bGEnable != IsGraphicDisplayEnable()) ||
		(bGColor != IsGraphicDisplayColor());
	bool bG320Line, bN80GColor, bN80GUpdate;
	uint8_t btN80GPalette = (uint8_t)((btData >> 5) & 0x07);
	if (IsN80V2BasicRomMode()) {
		bG320Line = (btData & 0x04) != 0;
		bN80GColor = (btData & 0x10) != 0;
	} else {
		bG320Line = (btData & 0x10) != 0;
		bN80GColor = (btData & 0x04) != 0;
		bGColor = bN80GColor || bG320Line;
	}
	bN80GUpdate = (bN80GColor != IsN80GraphicColorMode()) ||
		(btN80GPalette != GetN80GraphicPalette()) ||
		(bG320Line != IsGraphicDisplay320Line());
	if (bN80GUpdate) {
		if (IsN80V2BasicRomMode()) {
			if (!bN80GColor) {
				WriteIO_52(0x52, (uint8_t)(btN80GPalette << 4));
			}
		} else {
			if (bG320Line) {
				uint8_t btPal = (uint8_t)(bN80GColor? 1: 0);
				for (int i = 0; i < 3; i++) {
					WriteIO_54_5B(0x54+i, btPal);
					WriteIO_54_5B(0x58+i, btPal);
					btPal += 2;
				}
				WriteIO_54_5B(0x57, btN80GPalette);
				WriteIO_54_5B(0x5B, btN80GPalette);
			} else {
				if (bN80GColor) {
					for (int i = 0; i < 8; i++)
						WriteIO_54_5B(
							0x54+i, (uint8_t)(((i & 1) != 0)? btN80GPalette: 0));
				} else {
					WriteIO_52(0x52, (uint8_t)(btN80GPalette << 4));
				}
			}
		}
	}
	bGUpdate = bGUpdate || bN80GUpdate;
	SetGraphicDisplay320Line(bG320Line);
	SetN80GraphicPalette(btN80GPalette);
	SetN80GraphicColorMode(bN80GColor);
	if (bGUpdate) {
		SetGVRamUpdate(true);
		SetGraphicDisplayEnable(bGEnable);
		Crtc().SetGraphicDisplayEnable(bGEnable);
		SetGraphicDisplayColor(bGColor);
	}
	MemBankRomRamMode_N80(
		(btData & 0x02) != 0,
		btData & 0x01);
}

// I/O port 32 read

uint8_t CPC88Z80Main::ReadIO_32(int /*nAddress*/) {
	return uint8_t(
		(GetIERomBank() & 0x03) |
		((m_nAVC & 0x03) << 2) |
		(IsFastTVRamDisable()? 0x10: 0) |
		(IsGraphicDisplayAnalog()? 0x20: 0) |
		(IsGraphicExGVAM()? 0x40: 0) |
		(IsPsgInterruptMask()? 0x80: 0));
}

// I/O port 32 write

void CPC88Z80Main::WriteIO_32(int /*nAddress*/, uint8_t btData) {
	bool bGraphicExGVAM = ((btData & 0x40) != 0);
	if (bGraphicExGVAM != IsGraphicExGVAM()) {
		m_nGVRamBank = 3;
		SetGraphicExGVAM(bGraphicExGVAM);
		if (!IsGraphicExGVAM()) {
			MemBankGVRamMode(m_nGVRamBank);
		} else {
			MemBankGVRamModeEx(m_bGraphicExGAM, m_nGraphicExGDM);
		}
		Crtc().SetCPUAccessingGVRam(
			!IsFastGVRamUse() &&
			IsAccessingGVRam() && !IsGraphicFlashing());
	}
	MemBankIERomMode(m_bDisableIERom, btData & 0x03);
	m_nAVC = (btData >> 2) & 0x03;
	MemBankFastTVRamMode((btData & 0x10) != 0);
	SetGraphicDisplayAnalog((btData & 0x20) != 0);
	SetPsgInterruptMask((btData & 0x80) != 0);
	m_pIntVectChangeCallback();
}

// I/O port 33 read(N80)

uint8_t CPC88Z80Main::ReadIO_33_N80(int /*nAddress*/) {
	return uint8_t(
		(IsPsgInterruptMask()? 0x02: 0) |
		(IsGraphicPriority()? 0x04: 0) |
		(IsTextPriority()? 0x08: 0) |
		(IsHiraMode()? 0x10: 0) |
		(IsGraphicExGVAM()? 0x40: 0) |
		(IsN80V2BasicRomMode()? 0x80: 0));
}

// I/O port 33 write(N80)

void CPC88Z80Main::WriteIO_33_N80(int /*nAddress*/, uint8_t btData) {
	bool bN80V2BasicRomMode = (btData & 0x80) != 0,
		bGraphicExGVAM = (btData & 0x40) != 0,
		bHiraMode = (btData & 0x10) != 0,
		bTextPriority = (btData & 0x08) != 0,
		bGraphicPriority = (btData & 0x04) != 0;
	if (bGraphicExGVAM != IsGraphicExGVAM()) {
		SetGraphicExGVAM(bGraphicExGVAM);
		if (!IsGraphicExGVAM()) {
			MemBankGVRamMode_N80(m_nGVRamBank);
		} else {
			MemBankGVRamModeEx_N80(m_bGraphicExGAM, m_nGraphicExGDM);
		}
		Crtc().SetCPUAccessingGVRam(
			!IsFastGVRamUse() &&
			IsAccessingGVRam() && !IsGraphicFlashing());
	}
	if (bN80V2BasicRomMode != IsN80V2BasicRomMode()) {
		SetN80V2BasicRomMode(bN80V2BasicRomMode);
		MemBankRomRamMode_N80(IsAllRamMode(), m_nIERomBank);
	}
	if (bGraphicPriority != IsGraphicPriority()) {
		SetGVRamUpdate(true);
	}
	if (bHiraMode != IsHiraMode()) {
		SetTVRamUpdate(true);
	}
	if (bTextPriority != IsTextPriority()) {
		SetTVRamUpdate(true);
	}
	SetGraphicPriority(bGraphicPriority);
	SetTextPriority(bTextPriority);
	SetHiraMode(bHiraMode);
	SetPsgInterruptMask((btData & 0x02) != 0);
	m_pIntVectChangeCallback();
}

// I/O port 34 write

void CPC88Z80Main::WriteIO_34(int /*nAddress*/, uint8_t btData) {
	SetGraphicExALU(0, (btData & 0x01) | ((btData & 0x10) >> 3));
	SetGraphicExALU(1, ((btData & 0x02) >> 1) | ((btData & 0x20) >> 4));
	SetGraphicExALU(2, ((btData & 0x04) >> 2) | ((btData & 0x40) >> 5));
}

// I/O port 35 write

void CPC88Z80Main::WriteIO_35(int /*nAddress*/, uint8_t btData) {
	int nGraphicExGDM = (btData >> 4) & 0x03;
	bool bGraphicExGAM = ((btData & 0x80) != 0);
	SetGraphicExPlaneCompare(0, uint8_t(((btData & 0x01) != 0)? 0x00: 0xFF));
	SetGraphicExPlaneCompare(1, uint8_t(((btData & 0x02) != 0)? 0x00: 0xFF));
	SetGraphicExPlaneCompare(2, uint8_t(((btData & 0x04) != 0)? 0x00: 0xFF));
	MemBankGVRamModeEx(bGraphicExGAM, nGraphicExGDM);
	Crtc().SetCPUAccessingGVRam(
		!IsFastGVRamUse() &&
		IsAccessingGVRam() && !IsGraphicFlashing());
}

// I/O port 35 write(N80)

void CPC88Z80Main::WriteIO_35_N80(int /*nAddress*/, uint8_t btData) {
	int nGraphicExGDM = (btData >> 4) & 0x03;
	bool bGraphicExGAM = ((btData & 0x80) != 0);
	SetGraphicExPlaneCompare(0, uint8_t(((btData & 0x01) != 0)? 0x00: 0xFF));
	SetGraphicExPlaneCompare(1, uint8_t(((btData & 0x02) != 0)? 0x00: 0xFF));
	SetGraphicExPlaneCompare(2, uint8_t(((btData & 0x04) != 0)? 0x00: 0xFF));
	MemBankGVRamModeEx_N80(bGraphicExGAM, nGraphicExGDM);
	Crtc().SetCPUAccessingGVRam(
		!IsFastGVRamUse() &&
		IsAccessingGVRam() && !IsGraphicFlashing());
}

// I/O port 40 read

uint8_t CPC88Z80Main::ReadIO_40(int /*nAddress*/) {
	return uint8_t(
		0xC4 |
		//(ParallelDevice().IsBusy()? 0x01: 0) |
		(!Crtc().IsHiresolution()? 0x02: 0) |
		(IsSubSystemDisable()? 0x08: 0) |
		(Calendar().IsCalendarDataIn()? 0x10: 0) |
		(Crtc().IsVSync()? 0x20: 0));
}

// I/O port 40 write

void CPC88Z80Main::WriteIO_40(int /*nAddress*/, uint8_t btData) {

	//ParallelDevice().SetStrobe((btData & 0x01) != 0);
	Calendar().SetCalendarStrobe((btData & 0x02) != 0);
	Calendar().SetCalendarShift((btData & 0x04) != 0);
	Crtc().SetSyncPulse((btData & 0x08) != 0);
	SetGraphicFlashing((btData & 0x10) != 0);
	Crtc().SetCPUAccessingGVRam(
		!IsFastGVRamUse() &&
		IsAccessingGVRam() && !IsGraphicFlashing());
	//m_pBeepOutputCallback((btData & 0x20) != 0, (btData & 0x80) != 0);
}

// I/O port 44 read

uint8_t CPC88Z80Main::ReadIO_44(int /*nAddress*/) {
	return Opna().ReadStatus();
}

// I/O port 44 write

void CPC88Z80Main::WriteIO_44(int /*nAddress*/, uint8_t btData) {
	Opna().WriteAddress(btData);
}

// I/O port 45 read

uint8_t CPC88Z80Main::ReadIO_45(int /*nAddress*/) {
	return Opna().ReadData();
}

// I/O port 45 write

void CPC88Z80Main::WriteIO_45(int /*nAddress*/, uint8_t btData) {
	Opna().WriteData(btData);
}

// I/O port 50 read

uint8_t CPC88Z80Main::ReadIO_50(int /*nAddress*/) {
	return Crtc().ReadParam();
}

// I/O port 50 write

void CPC88Z80Main::WriteIO_50(int /*nAddress*/, uint8_t btData) {
	Crtc().WriteParam(btData);
}

// I/O port 51 read

uint8_t CPC88Z80Main::ReadIO_51(int /*nAddress*/) {
	return Crtc().ReadStatus();
}

// I/O port 51 write

void CPC88Z80Main::WriteIO_51(int /*nAddress*/, uint8_t btData) {
	Crtc().WriteCommand(btData);
}

// I/O port 52 write

void CPC88Z80Main::WriteIO_52(int /*nAddress*/, uint8_t btData) {
	SetColorPalette(
		BACKGROUND_PALETTE,
		(((btData & 0x10) != 0)? 0x0007: 0) |
			(((btData & 0x20) != 0)? 0x0038: 0) |
			(((btData & 0x40) != 0)? 0x01C0: 0));
	SetPaletteUpdate(true);
}

// I/O port 53 write

void CPC88Z80Main::WriteIO_53(int /*nAddress*/, uint8_t btData) {
	bool bTDisable = (btData & 0x01) != 0,
		bGDisable0 = (btData & 0x02) != 0,
		bGDisable1 = (btData & 0x04) != 0,
		bGDisable2 = (btData & 0x08) != 0;
	if (bTDisable != IsTVRamOverlayDisable()) {
		SetTVRamUpdate(true);
	}
	if ((bGDisable0 != IsGVRamOverlayDisable(0)) ||
		(bGDisable1 != IsGVRamOverlayDisable(1)) ||
		(bGDisable2 != IsGVRamOverlayDisable(2)))
	{
		SetGVRamUpdate(true);
	}
	SetTVRamOverlayDisable(bTDisable);
	SetGVRamOverlayDisable(0, bGDisable0);
	SetGVRamOverlayDisable(1, bGDisable1);
	SetGVRamOverlayDisable(2, bGDisable2);
}

// I/O port 53 write(N80)

void CPC88Z80Main::WriteIO_53_N80(int /*nAddress*/, uint8_t btData) {
	bool bTDisable = (btData & 0x01) != 0,
		bGDisable0 = (btData & 0x02) != 0,
		bGDisable1 = (btData & 0x04) != 0,
		bGDisable2 = (btData & 0x08) != 0,
		bGDisable3 = (btData & 0x10) != 0,
		bGDisable4 = (btData & 0x20) != 0,
		bGDisable5 = (btData & 0x40) != 0;
	if (bTDisable != IsTVRamOverlayDisable()) {
		SetTVRamUpdate(true);
	}
	if (bGDisable0 != IsGVRamOverlayDisable(0) ||
		bGDisable1 != IsGVRamOverlayDisable(1) ||
		bGDisable2 != IsGVRamOverlayDisable(2) ||
		bGDisable3 != IsGVRamOverlayDisable(3) ||
		bGDisable4 != IsGVRamOverlayDisable(4) ||
		bGDisable5 != IsGVRamOverlayDisable(5))
	{
		SetGVRamUpdate(true);
	}
	SetTVRamOverlayDisable(bTDisable);
	SetGVRamOverlayDisable(0, bGDisable0);
	SetGVRamOverlayDisable(1, bGDisable1);
	SetGVRamOverlayDisable(2, bGDisable2);
	SetGVRamOverlayDisable(3, bGDisable3);
	SetGVRamOverlayDisable(4, bGDisable4);
	SetGVRamOverlayDisable(5, bGDisable5);
}

// I/O port 54-5B write

void CPC88Z80Main::WriteIO_54_5B(int nAddress, uint8_t btData) {
	if (IsGraphicDisplayAnalog()) {
		if ((btData & 0x80) == 0) {
			if ((btData & 0x40) == 0) {
				SetColorPalette(
					nAddress-0x54,
					(GetColorPalette(nAddress-0x54) & 0x01C0) |
						(btData & 0x003F));
			} else {
				SetColorPalette(
					nAddress-0x54,
					(GetColorPalette(nAddress-0x54) & 0x003F) |
						((btData & 0x0007) << 6));
			}
		} else if (nAddress == 0x54) {
			if ((btData & 0x40) == 0) {
				SetColorPalette(
					BACKGROUND_PALETTE,
					(GetColorPalette(BACKGROUND_PALETTE) & 0x01C0) |
						(btData & 0x003F));
			} else {
				SetColorPalette(
					BACKGROUND_PALETTE,
					(GetColorPalette(BACKGROUND_PALETTE) & 0x003F) |
						((btData & 0x0007) << 6));
			}
		}
	} else {
		SetColorPalette(
			nAddress-0x54,
			(((btData & 1) != 0)? 0x0007: 0) |
				(((btData & 2) != 0)? 0x0038: 0) |
				(((btData & 4) != 0)? 0x01C0: 0));
	}
	SetPaletteUpdate(true);
}

// I/O port 5C read

uint8_t CPC88Z80Main::ReadIO_5C(int /*nAddress*/) {
	return uint8_t((0x01 << GetGVRamBank()) | 0xF8);
}

// I/O port 5C-5F write

void CPC88Z80Main::WriteIO_5C_5F(int nAddress, uint8_t /*btData*/) {
	if (!IsGraphicExGVAM()) {
		MemBankGVRamMode(nAddress-0x5C);
		Crtc().SetCPUAccessingGVRam(
			!IsFastGVRamUse() &&
			IsAccessingGVRam() && !IsGraphicFlashing());
	}
}

// I/O port 5C-5F write(N80)

void CPC88Z80Main::WriteIO_5C_5F_N80(int nAddress, uint8_t /*btData*/) {
	MemBankGVRamMode_N80(nAddress-0x5C);
	Crtc().SetCPUAccessingGVRam(
		!IsFastGVRamUse() &&
		IsAccessingGVRam() && !IsGraphicFlashing());
}

// I/O port 64 write

void CPC88Z80Main::WriteIO_64(int /*nAddress*/, uint8_t btData) {
	if (!IsDMAWriteFF_64()) {
		SetTVRamOfs(uint16_t((GetTVRamOfs() & 0xFF00) | btData));
	} else {
		SetTVRamOfs(uint16_t((GetTVRamOfs() & 0x00FF) | (btData << 8)));
	}
	SetDMAWriteFF_64(!IsDMAWriteFF_64());
	SetTVRamUpdate(true);
}

// I/O port 68 write

void CPC88Z80Main::WriteIO_68(int /*nAddress*/, uint8_t btData) {
	SetDMAWriteFF_64(false);
	Crtc().SetDMAStarted((btData & 0x84) == 0x84);
	SetTVRamUpdate(true);
}

// I/O port 6E read

uint8_t CPC88Z80Main::ReadIO_6E(int /*nAddress*/) {
	return uint8_t((GetBaseClock() == 4)? 0x80: 0);
}

// I/O port 70 read

uint8_t CPC88Z80Main::ReadIO_70(int /*nAddress*/) {
	return GetTextWindowOfs();
}

// I/O port 70 write

void CPC88Z80Main::WriteIO_70(int /*nAddress*/, uint8_t btData) {
	SetTextWindowOfs(btData);
}

// I/O port 71 read

uint8_t CPC88Z80Main::ReadIO_71(int /*nAddress*/) {
	return uint8_t(0xFE | (m_bDisableIERom? 0x01: 0));
}

// I/O port 71 write

void CPC88Z80Main::WriteIO_71(int /*nAddress*/, uint8_t btData) {
	MemBankIERomMode((btData & 0x01) != 0, m_nIERomBank);
}

// I/O port 71 write(N80)

void CPC88Z80Main::WriteIO_71_N80(int /*nAddress*/, uint8_t btData) {
	MemBankIERomMode_N80((btData & 0x01) != 0);
}

// I/O port 78 write

void CPC88Z80Main::WriteIO_78(int /*nAddress*/, uint8_t /*btData*/) {
	IncTextWindowOfs();
}

// I/O port B4 read

uint8_t CPC88Z80Main::ReadIO_B4(int /*nAddress*/) {
	uint8_t btData = 0xFF;
	if (!m_bVABDisable && (m_nExRamCardNo == EX_RAM_VAB)) {
		btData = m_btVABMode1;
	}
	return btData;
}

// I/O port B4 write

void CPC88Z80Main::WriteIO_B4(int /*nAddress*/, uint8_t btData) {
	if (!m_bVABDisable) {
		if ((m_btVABMode1 & 0x40) != (btData & 0x40)) {
			SetVABUpdate(true);
			SetGVRamUpdate(true);
		}
		m_btVABMode1 = btData;
	}
}

// I/O port B5 read

uint8_t CPC88Z80Main::ReadIO_B5(int /*nAddress*/) {
	uint8_t btData = 0xFF;
	if (!m_bVABDisable && (m_nExRamCardNo == EX_RAM_VAB)) {
		btData = m_btVABMode2;
	}
	return btData;
}

// I/O port B5 write

void CPC88Z80Main::WriteIO_B5(int /*nAddress*/, uint8_t btData) {
	if (!m_bVABDisable) {
		m_btVABMode2 = btData;
	}
}

// I/O port E2 read

uint8_t CPC88Z80Main::ReadIO_E2(int /*nAddress*/) {
	return (uint8_t)(~m_btExRamAccessMode);
}

// I/O port E2 write

void CPC88Z80Main::WriteIO_E2(int /*nAddress*/, uint8_t btData) {
	m_btExRamAccessMode = (uint8_t)(btData & 0x11);
	m_abtExRamAccessModeBackup = m_btExRamAccessMode;
	MemBankRomRamMode(IsAllRamMode(), IsNBasicRomMode());
	MemBankExRamWriteMode();
}

// I/O port E2 write(N80)

void CPC88Z80Main::WriteIO_E2_N80(int /*nAddress*/, uint8_t btData) {
	m_btExRamAccessMode = (uint8_t)(btData & 0x11);
	m_abtExRamAccessModeBackup = m_btExRamAccessMode;
	MemBankRomRamMode_N80(IsAllRamMode(), m_nIERomBank);
	MemBankExRamWriteMode_N80();
}

// I/O port E3 read

uint8_t CPC88Z80Main::ReadIO_E3(int /*nAddress*/) {
	uint8_t btData = 0xFF;
	if (m_nExRamCardNo < EX_RAM_COUNT) {
		btData = (uint8_t)(
			0xF0 |
			((m_nExRamCardNo & 0x03) << 2) |
			(m_nExRamBankNo & 0x03));
	}
	return btData;
}

// I/O port E3 write

void CPC88Z80Main::WriteIO_E3(int /*nAddress*/, uint8_t btData) {
	m_nExRamCardNo = (btData >> 2) & 0x03;
	m_nExRamBankNo = btData & 0x03;
	if (m_nExRamCardNo < EX_RAM_COUNT) {
		m_btExRamAccessMode = m_abtExRamAccessModeBackup;
	} else {
		m_btExRamAccessMode = 0x00;
	}
	MemBankRomRamMode(IsAllRamMode(), IsNBasicRomMode());
	MemBankExRamWriteMode();
}

// I/O port E3 write(N80)

void CPC88Z80Main::WriteIO_E3_N80(int /*nAddress*/, uint8_t btData) {
	m_nExRamCardNo = (btData >> 2) & 0x03;
	m_nExRamBankNo = btData & 0x03;
	if (m_nExRamCardNo < EX_RAM_COUNT) {
		m_btExRamAccessMode = m_abtExRamAccessModeBackup;
	} else {
		m_btExRamAccessMode = 0x00;
	}
	MemBankRomRamMode_N80(IsAllRamMode(), m_nIERomBank);
	MemBankExRamWriteMode_N80();
}

// I/O port E4 write

void CPC88Z80Main::WriteIO_E4(int /*nAddress*/, uint8_t btData) {
	SetInterruptLevel(btData & 0x07);
	SetPriorityInterrupt((btData & 0x08) != 0);
	m_pIntVectChangeCallback();
}

// I/O port E6 write

void CPC88Z80Main::WriteIO_E6(int /*nAddress*/, uint8_t btData) {
	SetTimerInterruptMask((btData & 0x01) == 0, true);
	SetVSyncInterruptMask((btData & 0x02) == 0, true);
	SetUsartInterruptMask((btData & 0x04) == 0, true);
	m_pIntVectChangeCallback();
}

// I/O port E8 read

uint8_t CPC88Z80Main::ReadIO_E8(int /*nAddress*/) {
	return m_abtKanjiRom[0 * 131072 + GetKanjiAddress(0)*2+1];
}

// I/O port E8 write

void CPC88Z80Main::WriteIO_E8(int /*nAddress*/, uint8_t btData) {
	SetKanjiAddress(0, uint16_t((GetKanjiAddress(0) & 0xFF00) | btData));
}

// I/O port E9 read

uint8_t CPC88Z80Main::ReadIO_E9(int /*nAddress*/) {
	return m_abtKanjiRom[0 * 131072 + GetKanjiAddress(0)*2];
}

// I/O port E9 write

void CPC88Z80Main::WriteIO_E9(int /*nAddress*/, uint8_t btData) {
	SetKanjiAddress(0, uint16_t((GetKanjiAddress(0) & 0x00FF) | (btData << 8)));
}

// I/O port EC read

uint8_t CPC88Z80Main::ReadIO_EC(int /*nAddress*/) {
	return m_abtKanjiRom[1 * 131072 + GetKanjiAddress(1)*2+1];
}

// I/O port EC write

void CPC88Z80Main::WriteIO_EC(int /*nAddress*/, uint8_t btData) {
	SetKanjiAddress(1, uint16_t((GetKanjiAddress(1) & 0xFF00) | btData));
}

// I/O port ED read

uint8_t CPC88Z80Main::ReadIO_ED(int /*nAddress*/) {
	return m_abtKanjiRom[1 * 131072 + GetKanjiAddress(1)*2];
}

// I/O port ED write

void CPC88Z80Main::WriteIO_ED(int /*nAddress*/, uint8_t btData) {
	SetKanjiAddress(1, uint16_t((GetKanjiAddress(1) & 0x00FF) | (btData << 8)));
}

// I/O port FC read

uint8_t CPC88Z80Main::ReadIO_FC(int /*nAddress*/) {
	return Ppi().ReadPortA(CPC88Ppi::SIDE_MAIN);
}

// I/O port FC write

void CPC88Z80Main::WriteIO_FC(int /*nAddress*/, uint8_t btData) {
	Ppi().WritePortA(CPC88Ppi::SIDE_MAIN, btData);
}

// I/O port FD read

uint8_t CPC88Z80Main::ReadIO_FD(int /*nAddress*/) {
	return Ppi().ReadPortB(CPC88Ppi::SIDE_MAIN);
}

// I/O port FD write

void CPC88Z80Main::WriteIO_FD(int /*nAddress*/, uint8_t btData) {
	Ppi().WritePortB(CPC88Ppi::SIDE_MAIN, btData);
}

// I/O port FE read

uint8_t CPC88Z80Main::ReadIO_FE(int /*nAddress*/) {
	return Ppi().ReadPortC(CPC88Ppi::SIDE_MAIN);
}

// I/O port FE write

void CPC88Z80Main::WriteIO_FE(int /*nAddress*/, uint8_t btData) {
	Ppi().WritePortC(CPC88Ppi::SIDE_MAIN, btData);
}

// I/O port FF write

void CPC88Z80Main::WriteIO_FF(int /*nAddress*/, uint8_t btData) {
	Ppi().WriteCommand(CPC88Ppi::SIDE_MAIN, btData);
}

////////////////////////////////////////////////////////////
// interrupt

// occurred interrupt

int CPC88Z80Main::DoInterrupt(uint8_t btIntVect) {
	m_nInterruptCounter++;
	switch (btIntVect) {
	case 0x00:
		Usart().SetReceiveInterruptRequest(false);
		break;
	case 0x02:
		Crtc().SetVSyncInterruptRequest(false);
		break;
	case 0x04:
		Timer().SetTimerInterruptRequest(false);
		break;
	case 0x08:
		Opna().SetOpnaInterruptRequest(false);
		break;
	}
	SetInterruptLevel(0);
	SetPriorityInterrupt(false);
	m_pIntVectChangeCallback();
	return CZ80_1::DoInterrupt(btIntVect);
}
