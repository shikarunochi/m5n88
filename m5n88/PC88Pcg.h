////////////////////////////////////////////////////////////
// PCG-8800 Emulator
//
// Written by Manuke
//
// Assisted by apaslothy
// (PCG-8800 Support)

#ifndef PC88Pcg_DEFINED
#define PC88Pcg_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Pcg;

////////////////////////////////////////////////////////////
// declaration of CPC88Pcg

class CPC88Pcg {
// typedef
public:
	// type of current text font ROM get callback function
	typedef uint8_t (*CurTextFontRomGetCallback)(
		int nAddress);
	// type of PCG sound output callback function
	typedef void (*PcgSoundOutputCallback)(
		int nChannel, int nCounter);

// attribute
protected:
	// PCG RAM
	static uint8_t m_abtPcgRam[2][1024];

	// PCG bank
	static int m_anPcgBank[2];
	// PCG displaying
	static bool m_abPcgDisplay[2];
	// PCG updated
	static bool m_abPcgUpdate[2];
	// PCG address
	static int m_nPcgAddress;
	// PCG data
	static uint8_t m_btPcgData;
	// PCG data setting bank
	static int m_nPcgSetBank;
	// PCG sound port status
	static bool m_abPcgSoundPortStatus[3];

	// interval timer(8253) counter setting mode
	static int m_anITimerMode[3];
	// interval timer(8253) counter
	static int m_anITimerCounter[3];
	// interval timer(8253) counter setting flag
	static bool m_abITimerMsb[3];
	// interval timer(8253) counter BCD
	static bool m_abITimerBcd[3];

	// current text font ROM get callback function
	static CurTextFontRomGetCallback m_pCurTextFontRomGetCallback;

	// PCG sound output callback function
	static PcgSoundOutputCallback m_pPcgSoundOutputCallback;

public:
	// get PCG RAM buffer
	static uint8_t* GetPcgRamPtr(int nBank) {
		return m_abtPcgRam[nBank];
	}
	// get PCG RAM content
	static uint8_t GetPcgRam(int nBank, int nAddress) {
		return m_abtPcgRam[nBank][nAddress];
	}
	// get current text font ROM or RAM content
	static uint8_t GetCurTextFontData(int nPos, int nAddress) {
		return m_abPcgDisplay[nPos]?
			m_abtPcgRam[m_anPcgBank[nPos]][nAddress]:
			m_pCurTextFontRomGetCallback(nPos*1024+nAddress);
	}

	// is PCG updated
	static bool IsPcgUpdate(int nBank) {
		return m_abPcgUpdate[nBank];
	}
	// set PCG updated
	static void SetPcgUpdate(int nBank, bool bPcgUpdate) {
		m_abPcgUpdate[nBank] = bPcgUpdate;
	}

	// interval timer(8253) counter value
	static int GetITimerCounterValue(int nChannel) {
		int nITimerCounter = -1;
		if (m_abPcgSoundPortStatus[nChannel]) {
			nITimerCounter = m_anITimerCounter[nChannel];
			if (m_abITimerBcd[nChannel]) {
				nITimerCounter =
					((nITimerCounter >> 12) & 0x0F)*1000+
					((nITimerCounter >> 8) & 0x0F)*100+
					((nITimerCounter >> 4) & 0x0F)*10+
					(nITimerCounter & 0x0F);
			}
		}
		return nITimerCounter;
	}

	// set current text font ROM get callback function
	static void SetCurTextFontRomGetCallback(
		CurTextFontRomGetCallback pCurTextFontRomGetCallback)
	{
		m_pCurTextFontRomGetCallback = pCurTextFontRomGetCallback;
	}

	// set PCG sound output callback function
	static void SetPcgSoundOutputCallback(
		PcgSoundOutputCallback pPcgSoundOutputCallback)
	{
		m_pPcgSoundOutputCallback = pPcgSoundOutputCallback;
	}

// create & destroy
public:
	// default constructor
	CPC88Pcg();
	// destructor
	~CPC88Pcg();

// initialize
public:
	// initialize at first
	static void Initialize();
	// reset
	static void Reset();

// operation
public:
	// PCG port write
	static void WritePcgPort(int nAddress, uint8_t btData);
	// interval timer(8253) port write
	static void WriteITimerPort(int nAddress, uint8_t btData);
};

#endif // PC88Pcg_DEFINED
