////////////////////////////////////////////////////////////
// PC-8801 OPNA Emulator
//
// Written by Manuke

#ifndef PC88Opna_DEFINED
#define PC88Opna_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Opna;

////////////////////////////////////////////////////////////
// declaration of CPC88Opna

class CPC88Opna {
// typedef
public:
	// type of interrupt vector change callback function
	typedef void (*IntVectChangeCallback)();

// enum
public:
	// interrupt bit
	enum {
		INTERRUPT_BIT = 0x10
	};

// attribute
protected:
	// base clock
	static int m_nBaseClock;
	// status
	static uint8_t m_btStatus;
	// address
	static int m_nAddress;
	// CH3 mode
	static int m_nCh3Mode;
	// FM synthesis pre-scaler
	static int m_nPreScalerFM;
	// PSG synthesis pre-scaler
	static int m_nPreScalerPSG;
	// timer A active
	static bool m_bTimerAAcvive;
	// timer A set flag
	static bool m_bTimerASetFlag;
	// timer A value
	static int m_nTimerAValue;
	// timer A counter
	static int m_nTimerACounter;
	// timer A counter max value
	static int m_nTimerACounterMax;
	// timer B active
	static bool m_bTimerBAcvive;
	// timer B set flag
	static bool m_bTimerBSetFlag;
	// timer B value
	static int m_nTimerBValue;
	// timer B counter
	static int m_nTimerBCounter;
	// timer B counter max value
	static int m_nTimerBCounterMax;
	// OPNA interrupt requested
	static bool m_bOpnaInterruptRequest;

	// interrupt vector change callback function
	static IntVectChangeCallback m_pIntVectChangeCallback;

public:
	// get base clock
	static int GetBaseClock() {
		return m_nBaseClock;
	}
	// set base clock
	static void SetBaseClock(int nBaseClock) {
		m_nBaseClock = nBaseClock;
	}
	// is OPNA interrupt requested
	static bool IsOpnaInterruptRequest() {
		return m_bOpnaInterruptRequest;
	}
	// set OPNA interrupt requested
	static void SetOpnaInterruptRequest(bool bOpnaInterruptRequest) {
		m_bOpnaInterruptRequest = bOpnaInterruptRequest;
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
	CPC88Opna();
	// destructor
	~CPC88Opna();

// initialize
public:
	// initialize at first
	static void Initialize();
	// reset
	static void Reset();

// operation
protected:
	// update interrupt request
	static void UpdateInterruptRequest(bool bOpnaInterruptRequest) {
		if (bOpnaInterruptRequest != m_bOpnaInterruptRequest) {
			m_bOpnaInterruptRequest = bOpnaInterruptRequest;
			m_pIntVectChangeCallback();
		}
	}

public:
	// pass clock
	static void PassClock(int nClock) {
		if (m_bTimerAAcvive) {
			if ((m_nTimerACounter -= nClock) <= 0) {
				TimerAOverFlow();
			}
		}
		if (m_bTimerBAcvive) {
			if ((m_nTimerBCounter -= nClock) <= 0) {
				TimerBOverFlow();
			}
		}
	}
	// timer A overflow
	static void TimerAOverFlow();
	// timer B overflow
	static void TimerBOverFlow();
	// set timer A counter max value
	static void SetTimerACounterMax();
	// set timer B counter max value
	static void SetTimerBCounterMax();
	// set pre-scaler
	static void SetPreScaler(int nPreScalerFM, int nPreScalerPSG);
	// read status
	static uint8_t ReadStatus() {
		return m_btStatus;
	}
	// read data
	static uint8_t ReadData();
	// write address
	static void WriteAddress(uint8_t btAddress);
	// write data
	static void WriteData(uint8_t btData);
};

#endif // PC88Opna_DEFINED
