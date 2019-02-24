////////////////////////////////////////////////////////////
// PC-8801 CRTC Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Crtc.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Crtc

////////////////////////////////////////////////////////////
// attribute

// base clock

int CPC88Crtc::m_nBaseClock;

// hi-resolution mode

bool CPC88Crtc::m_bHiresolution;

// screen line count

int CPC88Crtc::m_nScreenLineCount;

// command mode

int CPC88Crtc::m_nCommandMode;

// command counter

int CPC88Crtc::m_nCommandCounter;

// screen counter

int CPC88Crtc::m_nScreenCounter;

// v-sync counter

int CPC88Crtc::m_nVSyncCounter;

// v-cycle timing

int CPC88Crtc::m_nVCycleTiming;

// v-sync timing

int CPC88Crtc::m_nVSyncTiming;

// v-display timing

int CPC88Crtc::m_nVDisplayTiming;

// scan line counter

int CPC88Crtc::m_nScanLineCounter;

// h-sync counter

int CPC88Crtc::m_nHSyncCounter;

// character line counter

int CPC88Crtc::m_nCharLineCounter;

// h-cycle timing

int CPC88Crtc::m_nHCycleTiming;

// h-sync timing

int CPC88Crtc::m_nHSyncTiming;

// h-display timing

int CPC88Crtc::m_nHDisplayTiming;

// v/h-sync timing

int CPC88Crtc::m_nVHSyncTiming;

// DMA character mode

bool CPC88Crtc::m_bC_B;

// character count per line

int CPC88Crtc::m_nCharPerLine;

// line count per screen

int CPC88Crtc::m_nLinePerScreen;

// v-dot count per character

int CPC88Crtc::m_nVDotPerChar;

// attribute count per line

int CPC88Crtc::m_nAttrPerLine;

// v-sync length

int CPC88Crtc::m_nVSyncLength;

// h-sync length

int CPC88Crtc::m_nHSyncLength;

// attribute mode

int CPC88Crtc::m_nAttrMode;

// cursor blink time

int CPC88Crtc::m_nCursorBlinkTime;

// attribute blink time

int CPC88Crtc::m_nAttrBlinkTime;

// display every other line

bool CPC88Crtc::m_bDispEveryOtherLine;

// cursor blink mode

bool CPC88Crtc::m_bCursorBlinkMode;

// cursor block mode

bool CPC88Crtc::m_bCursorBlockMode;

// cursor enable

bool CPC88Crtc::m_bCursorEnable;

// cursor x-position

int CPC88Crtc::m_nCursorX;

// cursor y-position

int CPC88Crtc::m_nCursorY;

// display started

bool CPC88Crtc::m_bDisplayStarted;

// DMA started

bool CPC88Crtc::m_bDMAStarted;

// reverse display

bool CPC88Crtc::m_bReverseDisp;

// v-sync interrupt enable

bool CPC88Crtc::m_bVSyncInterruptEnable;

// special character interrupt enable

bool CPC88Crtc::m_bSpCharInterruptEnable;

// v-sync interrupt requested

bool CPC88Crtc::m_bVSyncInterruptRequest;

// special character interrupt requested

bool CPC88Crtc::m_bSpCharInterruptRequest;

// 80 columns mode

bool CPC88Crtc::m_bWidth80;

// sync pulse active

bool CPC88Crtc::m_bSyncPulse;

// CRTC updated

bool CPC88Crtc::m_bCrtcUpdate;

// last text attribute

uint8_t CPC88Crtc::m_btLastTextAttr;

// graphic display enable

bool CPC88Crtc::m_bGraphicDisplayEnable;

// CPU accessing graphic VRAM

bool CPC88Crtc::m_bCPUAccessingGVRam;

// text VRAM wait

bool CPC88Crtc::m_bTVRamWait;

// wait on DMA accessing

bool CPC88Crtc::m_bWaitOnDMA;

// graphic VRAM wait

bool CPC88Crtc::m_bGVRamWait;

// text VRAM wait active

bool CPC88Crtc::m_bTVRamWaitActive;

// graphic VRAM wait active

bool CPC88Crtc::m_bGVRamWaitActive;

// text VRAM wait clock

int CPC88Crtc::m_nTVRamWaitClock;

// graphic VRAM wait rate(DMA active)

int CPC88Crtc::m_nGVRamWaitRateTA;

// graphic VRAM wait rate(DMA inactive)

int CPC88Crtc::m_nGVRamWaitRateTD;

// graphic VRAM wait excess

int CPC88Crtc::m_nGVRamWaitExcess;

// interrupt vector change callback function

CPC88Crtc::IntVectChangeCallback CPC88Crtc::m_pIntVectChangeCallback;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88Crtc::CPC88Crtc() {
	m_pIntVectChangeCallback = NULL;
}

// destructor

CPC88Crtc::~CPC88Crtc() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88Crtc::Initialize() {
	m_bHiresolution = true;
	m_nBaseClock = 4;
	m_bTVRamWait = m_bGVRamWait = false;
}

// reset

void CPC88Crtc::Reset() {
	m_nScreenLineCount = m_bHiresolution? 400: 200;
	m_nCommandMode = MODE_NONE;
	m_nCommandCounter = 0;
	m_bC_B = FALSE;
	m_nCharPerLine = 80;
	m_nLinePerScreen = 25;
	m_nVDotPerChar = 16;
	m_nAttrPerLine = 20;
	m_nVSyncLength = 8;
	m_nHSyncLength = 8;
	m_nAttrMode = ATTR_TRANSPARENT_MONO;
	m_nCursorBlinkTime = 16;
	m_nAttrBlinkTime = 32;
	m_bDispEveryOtherLine = false;
	m_bCursorBlinkMode = true;
	m_bCursorBlockMode = true;
	m_bCursorEnable = true;
	m_nCursorX = m_nCursorY = 0;
	m_bDisplayStarted = false;
	m_bDMAStarted = false;
	m_bReverseDisp = false;
	m_bVSyncInterruptEnable = m_bSpCharInterruptEnable = false;
	m_bVSyncInterruptRequest = m_bSpCharInterruptRequest = false;
	m_bWidth80 = true;
	m_bSyncPulse = false;
	m_bCrtcUpdate = true;
	m_btLastTextAttr = 0xE0;
	m_bGraphicDisplayEnable = true;
	m_bCPUAccessingGVRam = false;
	m_nTVRamWaitClock = IsWaitOnDMA()? TVRAM_WAIT_W: TVRAM_WAIT;
	UpdateTVRamWaitActive();
	UpdateGVRamWaitActive();
	UpdateTimings();
	ResetCounter();
}

////////////////////////////////////////////////////////////
// operation

// write parameter

void CPC88Crtc::WriteParam(uint8_t btParam) {
	switch (m_nCommandMode) {
	case MODE_RESET:
		switch (m_nCommandCounter) {
		case 0:
			m_bC_B = ((btParam & 0x80) != 0);
			m_nCharPerLine = (btParam & 0x7F)+2;
			break;
		case 1:
			m_nCursorBlinkTime = ((btParam >> 6)+1)*16;
			m_nAttrBlinkTime = m_nCursorBlinkTime*2;
			m_nLinePerScreen = (btParam & 0x3F)+1;
			break;
		case 2:
			m_bDispEveryOtherLine = ((btParam & 0x80) != 0);
			m_bCursorBlinkMode = ((btParam & 0x20) != 0);
			m_bCursorBlockMode = ((btParam & 0x40) != 0);
			m_nVDotPerChar = (btParam & 0x1F)+1;
			UpdateTimings();
			break;
		case 3:
			m_nVSyncLength = (btParam >> 5)+1;
			m_nHSyncLength = (btParam & 0x1F)+2;
			break;
		case 4:
			m_nAttrMode = btParam >> 5;
			m_nAttrPerLine = (btParam & 0x1F)+1;
			break;
		}
		if (++m_nCommandCounter >= 5) {
			m_nCommandMode = MODE_NONE;
		}
		break;
	case MODE_LOAD_CURSOR_POSITION:
		if (m_nCommandCounter == 0) {
			m_nCursorX = btParam;
			m_nCommandCounter++;
		} else {
			m_nCursorY = btParam;
			m_nCommandMode = MODE_NONE;
		}
		break;
	}
}
