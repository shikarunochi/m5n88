////////////////////////////////////////////////////////////
// PC-8801 CRTC Emulator
//
// Written by Manuke

#ifndef PC88Crtc_DEFINED
#define PC88Crtc_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Crtc;

////////////////////////////////////////////////////////////
// declaration of CPC88Crtc

class CPC88Crtc {
// typedef
public:
	// type of interrupt vector change callback function
	typedef void (*IntVectChangeCallback)();

// enum
public:
	// horizontal timing rate
	enum {
		HORZ_RATE = 64
	};
	// interrupt bit
	enum {
		INTERRUPT_BIT = 0x02
	};
	// CRTC mode
	enum {
		MODE_NONE                 = 0,
		MODE_RESET                = 1,
		MODE_READ_LIGHT_PEN       = 2,
		MODE_LOAD_CURSOR_POSITION = 3
	};
	// attribute mode
	enum {
		ATTR_NONE               = 1,
		ATTR_NONETRANSPARENT    = 5,
		ATTR_NONETRANSPARENT_SC = 4,
		ATTR_TRANSPARENT_MONO   = 0,
		ATTR_TRANSPARENT_COLOR  = 2
	};
	// v-sync timing(1us unit)
	enum {
		VTIMING_L20_VCYCLE = 16270,
		VTIMING_L20_VSYNC  = 3755,
		VTIMING_L25_VCYCLE = 16020,
		VTIMING_L25_VSYNC  = 3505,
		VTIMING_H20_VCYCLE = 17720,
		VTIMING_H20_VSYNC  = 1611,
		VTIMING_H25_VCYCLE = 18050,
		VTIMING_H25_VSYNC  = 1933
	};
	// h-sync timing(1us/HORZ_RATE unit)
	enum {
		HTIMING_L_HCYCLE = (6258*HORZ_RATE)/100,
		HTIMING_L_HSYNC  = (1788*HORZ_RATE)/100,
		HTIMING_L_HBACKP = (894*HORZ_RATE)/100,
		HTIMING_H_HCYCLE = (4028*HORZ_RATE)/100,
		HTIMING_H_HSYNC  = (988*HORZ_RATE)/100,
		HTIMING_H_HBACKP = (380*HORZ_RATE)/100
	};
	// text VRAM wait(clock unit)
	enum {
		TVRAM_WAIT   = 120*6,
		TVRAM_WAIT_W = 120*10
	};
	// graphic VRAM wait(percent)
	enum {
		GVRAM_WAIT_L20_TA = 120,
		GVRAM_WAIT_L20_TD = 164,
		GVRAM_WAIT_L25_TA = 112,
		GVRAM_WAIT_L25_TD = 170,
		GVRAM_WAIT_H20_TA = 304,
		GVRAM_WAIT_H20_TD = 365,
		GVRAM_WAIT_H25_TA = 263,
		GVRAM_WAIT_H25_TD = 337
	};

// attribute
protected:
	// base clock
	static int m_nBaseClock;
	// hi-resolution mode
	static bool m_bHiresolution;
	// screen line count
	static int m_nScreenLineCount;
	// command mode
	static int m_nCommandMode;
	// command counter
	static int m_nCommandCounter;
	// screen counter
	static int m_nScreenCounter;
	// v-sync counter
	static int m_nVSyncCounter;
	// v-cycle timing
	static int m_nVCycleTiming;
	// v-sync timing
	static int m_nVSyncTiming;
	// v-display timing
	static int m_nVDisplayTiming;
	// scan line counter
	static int m_nScanLineCounter;
	// h-sync counter
	static int m_nHSyncCounter;
	// character line counter
	static int m_nCharLineCounter;
	// h-cycle timing
	static int m_nHCycleTiming;
	// h-sync timing
	static int m_nHSyncTiming;
	// h-display timing
	static int m_nHDisplayTiming;
	// v/h-sync timing
	static int m_nVHSyncTiming;
	// DMA character mode
	static bool m_bC_B;
	// character count per line
	static int m_nCharPerLine;
	// line count per screen
	static int m_nLinePerScreen;
	// v-dot count per character
	static int m_nVDotPerChar;
	// attribute count per line
	static int m_nAttrPerLine;
	// v-sync length
	static int m_nVSyncLength;
	// h-sync length
	static int m_nHSyncLength;
	// attribute mode
	static int m_nAttrMode;
	// cursor blink time
	static int m_nCursorBlinkTime;
	// attribute blink time
	static int m_nAttrBlinkTime;
	// display every other line
	static bool m_bDispEveryOtherLine;
	// cursor blink mode
	static bool m_bCursorBlinkMode;
	// cursor block mode
	static bool m_bCursorBlockMode;
	// cursor enable
	static bool m_bCursorEnable;
	// cursor x-position
	static int m_nCursorX;
	// cursor y-position
	static int m_nCursorY;
	// display started
	static bool m_bDisplayStarted;
	// DMA started
	static bool m_bDMAStarted;
	// reverse display
	static bool m_bReverseDisp;
	// v-sync interrupt enable
	static bool m_bVSyncInterruptEnable;
	// special character interrupt enable
	static bool m_bSpCharInterruptEnable;
	// v-sync interrupt requested
	static bool m_bVSyncInterruptRequest;
	// special character interrupt requested
	static bool m_bSpCharInterruptRequest;
	// 80 columns mode
	static bool m_bWidth80;
	// sync pulse active
	static bool m_bSyncPulse;
	// CRTC updated
	static bool m_bCrtcUpdate;
	// last text attribute
	static uint8_t m_btLastTextAttr;
	// graphic display enable
	static bool m_bGraphicDisplayEnable;
	// CPU accessing graphic VRAM
	static bool m_bCPUAccessingGVRam;
	// text VRAM wait
	static bool m_bTVRamWait;
	// wait on DMA accessing
	static bool m_bWaitOnDMA;
	// graphic VRAM wait
	static bool m_bGVRamWait;
	// text VRAM wait active
	static bool m_bTVRamWaitActive;
	// graphic VRAM wait active
	static bool m_bGVRamWaitActive;
	// text VRAM wait clock
	static int m_nTVRamWaitClock;
	// graphic VRAM wait rate(DMA active)
	static int m_nGVRamWaitRateTA;
	// graphic VRAM wait rate(DMA inactive)
	static int m_nGVRamWaitRateTD;
	// graphic VRAM wait excess
	static int m_nGVRamWaitExcess;

	// interrupt vector change callback function
	static IntVectChangeCallback m_pIntVectChangeCallback;

public:
	// set base clock
	static void SetBaseClock(int nBaseClock) {
		m_nBaseClock = nBaseClock;
	}
	// is hi-resolution mode
	static bool IsHiresolution() {
		return m_bHiresolution;
	}
	// set hi-resolution mode
	static void SetHiresolution(bool bHiresolution) {
		m_bHiresolution = bHiresolution;
	}
	// get screen counter
	static int GetScreenCounter() {
		return m_nScreenCounter;
	}
	// get v-sync counter
	static int GetVSyncCounter() {
		return m_nVSyncCounter;
	}
	// is DMA character mode
	static bool IsC_B() {
		return m_bC_B;
	}
	// getcharacter count per line
	static int GetCharPerLine() {
		return m_nCharPerLine;
	}
	// get line count per screen
	static int GetLinePerScreen() {
		return m_nLinePerScreen;
	}
	// get v-dot count per character
	static int GetVDotPerChar() {
		return m_nVDotPerChar;
	}
	// get attribute count per line
	static int GetAttrPerLine() {
		return m_nAttrPerLine;
	}
	// get v-sync length
	static int GetVSyncLength() {
		return m_nVSyncLength;
	}
	// get h-sync length
	static int GetHSyncLength() {
		return m_nHSyncLength;
	}
	// get attribute mode
	static int GetAttrMode() {
		return m_nAttrMode;
	}
	// get cursor blink time
	static int GetCursorBlinkTime() {
		return m_nCursorBlinkTime;
	}
	// get attribute blink time
	static int GetAttrBlinkTime() {
		return m_nAttrBlinkTime;
	}
	// is display every other line
	static bool IsDispEveryOtherLine() {
		return m_bDispEveryOtherLine;
	}
	// is cursor blink mode
	static bool IsCursorBlinkMode() {
		return m_bCursorBlinkMode;
	}
	// is cursor block mode
	static bool IsCursorBlockMode() {
		return m_bCursorBlockMode;
	}
	// is cursor enable
	static bool IsCursorEnable() {
		return m_bCursorEnable;
	}
	// get cursor x-position
	static int GetCursorX() {
		return m_nCursorX;
	}
	// get cursor y-position
	static int GetCursorY() {
		return m_nCursorY;
	}
	// is display started
	static bool IsDisplayStarted() {
		return m_bDisplayStarted;
	}
	// is DMA started
	static bool IsDMAStarted() {
		return m_bDMAStarted;
	}
	// set DMA started
	static void SetDMAStarted(bool bDMAStarted) {
		m_bDMAStarted = bDMAStarted;
		UpdateTVRamWaitActive();
	}
	// is display active
	static bool IsDisplayActive() {
		return m_bDisplayStarted && m_bDMAStarted;
	}
	// is reverse display
	static bool IsReverseDisp() {
		return m_bReverseDisp;
	}
	// is v-sync interrupt enable
	static bool IsVSyncInterruptEnable() {
		return m_bVSyncInterruptEnable;
	}
	// is special character interrupt enable
	static bool IsSpCharInterruptEnable() {
		return m_bSpCharInterruptEnable;
	}
	// is v-sync interrupt requested
	static bool IsVSyncInterruptRequest() {
		return m_bVSyncInterruptRequest;
	}
	// set v-sync interrupt requested
	static void SetVSyncInterruptRequest(bool bVSyncInterruptRequest) {
		m_bVSyncInterruptRequest = bVSyncInterruptRequest;
	}
	// is special character interrupt requested
	static bool IsSpCharInterruptRequest() {
		return m_bSpCharInterruptRequest;
	}
	// set special character interrupt requested
	static void SetSpCharInterruptRequest(bool bSpCharInterruptRequest) {
		m_bSpCharInterruptRequest = bSpCharInterruptRequest;
	}
	// is 80 columns mode
	static bool IsWidth80() {
		return m_bWidth80;
	}
	// set 80 columns mode
	static void SetWidth80(bool bWidth80) {
		if (bWidth80 != m_bWidth80) {
			m_bWidth80 = bWidth80;
			m_bCrtcUpdate = true;
		}
	}
	// is sync pulse active
	static bool IsSyncPulse() {
		return m_bSyncPulse;
	}
	// set sync pulse active
	static void SetSyncPulse(bool bSyncPulse) {
		if (bSyncPulse && !m_bSyncPulse) {
			UpdateInterruptRequest(false, false);
			m_nScreenCounter = m_nVCycleTiming;
		}
		m_bSyncPulse = bSyncPulse;
	}
	// is 25 line mode
	static bool IsHeight25() {
		return m_nVDotPerChar%8 == 0;
	}
	// is color mode
	static bool IsColorMode() {
		return m_nAttrMode == ATTR_TRANSPARENT_COLOR;
	}
	// is cursor blinking
	static bool IsCursorBlinking() {
		return (m_nVSyncCounter%m_nCursorBlinkTime) > m_nCursorBlinkTime/2;
	}
	// is attribute blinking
	static bool IsAttrBlinking() {
		return (m_nVSyncCounter%m_nAttrBlinkTime) > (m_nAttrBlinkTime*3)/4;
	}
	// is v-sync area
	static bool IsVSync() {
		return m_nScreenCounter > m_nVDisplayTiming;
	}
	// is CRTC updated
	static bool IsCrtcUpdate() {
		return m_bCrtcUpdate;
	}
	// set CRTC updated
	static void SetCrtcUpdate(bool bCrtcUpdate) {
		m_bCrtcUpdate = bCrtcUpdate;
	}
	// get last text attribute
	static uint8_t GetLastTextAttr() {
		return m_btLastTextAttr;
	}
	// set last text attribute
	static void SetLastTextAttr(uint8_t btLastTextAttr) {
		m_btLastTextAttr = btLastTextAttr;
	}
	// is graphic display enable
	static bool IsGraphicDisplayEnable() {
		return m_bGraphicDisplayEnable;
	}
	// set graphic display enable
	static void SetGraphicDisplayEnable(bool bGraphicDisplayEnable) {
		m_bGraphicDisplayEnable = bGraphicDisplayEnable;
		UpdateGVRamWaitActive();
	}
	// is CPU accessing graphic VRAM
	static bool IsCPUAccessingGVRam() {
		return m_bCPUAccessingGVRam;
	}
	// set CPU accessing graphic VRAM
	static void SetCPUAccessingGVRam(bool bCPUAccessingGVRam) {
		m_bCPUAccessingGVRam = bCPUAccessingGVRam;
		UpdateGVRamWaitActive();
	}
	// is text VRAM wait
	static bool IsTVRamWait() {
		return m_bTVRamWait;
	}
	// set text VRAM wait
	static void SetTVRamWait(bool bTVRamWait) {
		m_bTVRamWait = bTVRamWait;
	}
	// is wait on DMA accessing
	static bool IsWaitOnDMA() {
		return m_bWaitOnDMA;
	}
	// set wait on DMA accessing
	static void SetWaitOnDMA(bool bWaitOnDMA) {
		m_bWaitOnDMA = bWaitOnDMA;
	}
	// is graphic VRAM wait
	static bool IsGVRamWait() {
		return m_bGVRamWait;
	}
	// set graphic VRAM wait
	static void SetGVRamWait(bool bGVRamWait) {
		m_bGVRamWait = bGVRamWait;
	}
	// is VRAM wait
	static bool IsVRamWait() {
		return m_bTVRamWait || m_bGVRamWait;
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
	CPC88Crtc();
	// destructor
	~CPC88Crtc();

// initialize
public:
	// initialize at first
	static void Initialize();
	// reset
	static void Reset();

// operation
protected:
	// update interrupt request
	static void UpdateInterruptRequest(
		bool bVSyncInterruptRequest,
		bool bSpCharInterruptRequest)
	{
		m_bSpCharInterruptRequest = bSpCharInterruptRequest;
		if (bVSyncInterruptRequest != m_bVSyncInterruptRequest) {
			m_bVSyncInterruptRequest = bVSyncInterruptRequest;
			m_pIntVectChangeCallback();
		}
	}
	// reset counter
	static void ResetCounter() {
		m_nScreenCounter = m_nVCycleTiming;
		m_nVSyncCounter = 0;
		m_nScanLineCounter = m_nVSyncTiming*HORZ_RATE+m_nHCycleTiming;
		m_nHSyncCounter = 0;
		m_nCharLineCounter = 0;
		m_nGVRamWaitExcess = 0;
	}
	// update timings
	static void UpdateTimings() {
		if (m_bHiresolution) {
			if (IsHeight25()) {
				m_nVCycleTiming = VTIMING_H25_VCYCLE;
				m_nVSyncTiming = VTIMING_H25_VSYNC;
				m_nGVRamWaitRateTA = GVRAM_WAIT_H25_TA;
				m_nGVRamWaitRateTD = GVRAM_WAIT_H25_TD;
			} else {
				m_nVCycleTiming = VTIMING_H20_VCYCLE;
				m_nVSyncTiming = VTIMING_H20_VSYNC;
				m_nGVRamWaitRateTA = GVRAM_WAIT_H20_TA;
				m_nGVRamWaitRateTD = GVRAM_WAIT_H20_TD;
			}
			m_nHCycleTiming = HTIMING_H_HCYCLE;
			m_nHSyncTiming = HTIMING_H_HSYNC;
		} else {
			if (IsHeight25()) {
				m_nVCycleTiming = VTIMING_L25_VCYCLE;
				m_nVSyncTiming = VTIMING_L25_VSYNC;
				m_nGVRamWaitRateTA = GVRAM_WAIT_L25_TA;
				m_nGVRamWaitRateTD = GVRAM_WAIT_L25_TD;
			} else {
				m_nVCycleTiming = VTIMING_L20_VCYCLE;
				m_nVSyncTiming = VTIMING_L20_VSYNC;
				m_nGVRamWaitRateTA = GVRAM_WAIT_L20_TA;
				m_nGVRamWaitRateTD = GVRAM_WAIT_L20_TD;
			}
			m_nHCycleTiming = HTIMING_L_HCYCLE;
			m_nHSyncTiming = HTIMING_L_HSYNC;
		}
		m_nVCycleTiming *= m_nBaseClock;
		m_nVSyncTiming *= m_nBaseClock;
		m_nVDisplayTiming = m_nVCycleTiming-m_nVSyncTiming;
		m_nHCycleTiming *= m_nBaseClock;
		m_nHSyncTiming *= m_nBaseClock;
		m_nHDisplayTiming = m_nHCycleTiming-m_nHSyncTiming;
		m_nVHSyncTiming = m_nHCycleTiming+
			(m_nVCycleTiming*HORZ_RATE-
				m_nHCycleTiming*m_nScreenLineCount);
	}
	// update text VRAM wait active
	static void UpdateTVRamWaitActive() {
		m_bTVRamWaitActive = m_bTVRamWait &&
			m_bDMAStarted &&
			m_bDisplayStarted;
	}
	// update graphic VRAM wait active
	static void UpdateGVRamWaitActive() {
		bool bGVRamWaitActiveNew = m_bGVRamWait &&
			m_bGraphicDisplayEnable &&
			m_bCPUAccessingGVRam;
		if (bGVRamWaitActiveNew && !m_bGVRamWaitActive) {
			if (m_bTVRamWaitActive) {
				m_nGVRamWaitExcess += m_nGVRamWaitRateTA/2;
			} else {
				m_nGVRamWaitExcess += m_nGVRamWaitRateTD/2;
			}
		}
		m_bGVRamWaitActive = bGVRamWaitActiveNew;
	}

public:
	// pass clock
	static void PassClock(int nClock) {
		if ((m_nScreenCounter -= nClock) <= 0) {
			UpdateInterruptRequest(true, m_bSpCharInterruptRequest);
			do {
				m_nVSyncCounter = uint16_t(m_nVSyncCounter+1);
				m_nScreenCounter += m_nVCycleTiming;
			} while (m_nScreenCounter <= 0);
		}
	}
	// pass clock(VRAM wait)
	static int PassClockVWait(int nClock) {
		int nExtendClock = 0;
		if (m_bGVRamWaitActive) {
			if (m_bTVRamWaitActive) {
				m_nGVRamWaitExcess += nClock*m_nGVRamWaitRateTA;
			} else {
				m_nGVRamWaitExcess += nClock*m_nGVRamWaitRateTD;
			}
			nExtendClock = m_nGVRamWaitExcess/100;
			m_nGVRamWaitExcess -= nExtendClock*100;
		}
		if ((m_nScanLineCounter -= (nClock+nExtendClock)*HORZ_RATE) <= 0) {
			do {
				if (++m_nHSyncCounter >= m_nScreenLineCount) {
					m_nHSyncCounter = 0;
					m_nScanLineCounter += m_nVHSyncTiming;
				} else {
					m_nScanLineCounter += m_nHCycleTiming;
				}
				if (++m_nCharLineCounter >= m_nVDotPerChar) {
					m_nCharLineCounter = 0;
					if (m_bTVRamWaitActive) {
						nExtendClock += m_nTVRamWaitClock;
						m_nScanLineCounter -= m_nTVRamWaitClock*HORZ_RATE;
					}
				}
			} while (m_nScanLineCounter <= 0);
		}
		if ((m_nScreenCounter -= (nClock+nExtendClock)) <= 0) {
			UpdateInterruptRequest(true, m_bSpCharInterruptRequest);
			do {
				m_nVSyncCounter = uint16_t(m_nVSyncCounter+1);
				m_nScreenCounter += m_nVCycleTiming;
			} while (m_nScreenCounter <= 0);
		}
		return nExtendClock;
	}
	// read status
	static uint8_t ReadStatus() {
		return uint8_t(
			(m_bDisplayStarted? 0x10: 0) |
			(m_bVSyncInterruptRequest? 0x04: 0) |
			(m_bSpCharInterruptRequest? 0x04: 0));
	}
	// write command
	static void WriteCommand(uint8_t btCommand) {
		m_nCommandMode = MODE_NONE;
		switch (btCommand & 0xE0) {
		case 0x00:
			// RESET / STOP DISPLAY
			m_nCommandMode = MODE_RESET;
			m_bDisplayStarted = false;
			UpdateTVRamWaitActive();
			UpdateInterruptRequest(false, false);
			m_bCrtcUpdate = true;
			break;
		case 0x20:
			// START DISPLAY
			m_bDisplayStarted = true;
			UpdateTVRamWaitActive();
			ResetCounter();
			m_bReverseDisp = ((btCommand & 0x01) != 0);
			m_btLastTextAttr = 0xE0;
			UpdateInterruptRequest(false, false);
			m_bCrtcUpdate = true;
			break;
		case 0x40:
			// SET INTERRUPT MASK
			m_bVSyncInterruptEnable = ((btCommand & 0x01) == 0);
			m_bSpCharInterruptEnable = ((btCommand & 0x02) == 0);
			if ((btCommand & 0x03) != 0) {
				m_bDisplayStarted = false;
				UpdateTVRamWaitActive();
				UpdateInterruptRequest(false, false);
			}
			break;
		case 0x60:
			// READ LIGHT PEN
			m_nCommandMode = MODE_READ_LIGHT_PEN;
			break;
		case 0x80:
			// LOAD CURSOR POSITION
			m_nCommandMode = MODE_LOAD_CURSOR_POSITION;
			m_bCursorEnable = ((btCommand & 0x01) != 0);
			break;
		case 0xA0:
			// RESET INTERRUPT
			UpdateInterruptRequest(false, false);
			break;
		case 0xC0:
			// RESET COUNTERS
			ResetCounter();
			UpdateInterruptRequest(false, false);
			m_bCrtcUpdate = true;
			break;
		}
		m_nCommandCounter = 0;
	}
	// read parameter
	static uint8_t ReadParam() {
		uint8_t btParam = 0x00;
		switch (m_nCommandMode) {
		case MODE_READ_LIGHT_PEN:
			if (++m_nCommandCounter >= 2) {
				m_nCommandMode = MODE_NONE;
			}
			break;
		}
		return btParam;
	}
	// write parameter
	static void WriteParam(uint8_t btParam);
};

#endif // PC88Crtc_DEFINED
